#include "ListaSO.h"
#include "stdlib.h"

void LSO_init(ListaSO *lista) {
    lista->limite_superior = -1;
}

int LSO_localizar(ListaSO *lista,char codigo_envio[], int *exito) {
    // Busca en 'lista' el elemento con el campo 'codigo_envio',
    // si lo encuentra, la funcion devuelve el indice del arreglo,
    // si el elemento no se encuentra en la lista, devuelve la posicion donde deberia encontrarse.

    // Variable de resultado de localizacion
    *exito = LOCALIZACION_ERROR_NO_EXISTE;

    // Contador
    int contador = 0;

    // Mientras no se pase el ultimo elemento y
    // el codigo de envio sea mayor o igual que el de Lista(contador)
    while ((contador <= lista->limite_superior) && strcmp(lista->arreglo[contador].codigo_envio,codigo_envio) < 0 ) {
        contador++;
    }

    // Si 'contador' supera el ultimo elemento, no se encontro el elemento
    if (contador <= lista->limite_superior) {
        // Si 'codigo_envio' es distinto del de Lista(contador), no se encontro el elemento
        if (strcmp(lista->arreglo[contador].codigo_envio,codigo_envio) == 0) *exito = LOCALIZACION_EXITOSA;
    }

    return contador;
}


int LSO_alta(ListaSO *lista, Envio nuevo) {

    // Variable de retorno
    int salida = ALTA_ERROR_LISTA_LLENA;
    // Variable de exito de localizar
    int exito_localizar;

    // Comprueba si existe un ENVIO con CODIGO DE ENVIO similar
    // y obtiene la posicion en donde deberia ir el elemento
    int posicion_nuevo = LSO_localizar(lista,nuevo.codigo_envio,&exito_localizar);

    // Se procesa el ALTA
    if (exito_localizar == LOCALIZACION_ERROR_NO_EXISTE) {
        // Si la lista NO esta llena
        if (!(lista->limite_superior >= (LISTA_TAM_ARREGLO - 1))) {
            // Se actualiza el limite superior
            lista->limite_superior++;

            // Se desplazan los elementos hacia la derecha
            for (int i=lista->limite_superior; i > posicion_nuevo; i--) {
                lista->arreglo[i] = lista->arreglo[i-1];
            }

            // Se agrega el nuevo elemento a la lista
            lista->arreglo[posicion_nuevo] = nuevo;

            // Se actualiza la salida
            salida = ALTA_EXITOSA;
        }
    }
    else salida = ALTA_ERROR_CODIGO_EXISTENTE;

    return salida;
}


int LSO_baja(ListaSO *lista,char codigo_envio[], int (*manejo_confirmacion)(Envio)) {

    int posicion, salida = BAJA_ERROR_NO_EXISTE;
    int exito_localizar;

    // Se captura el resultado de la localizacion y su respectiva
    // posicion para 'codigo_envio'
    posicion = LSO_localizar(lista,codigo_envio,&exito_localizar);

    if (exito_localizar == LOCALIZACION_EXITOSA) {
        int confirmacion = 1;

        // 'manejo_confirmacion' es un puntero a una funcion que devuelve
        // si se confirma la baja o no
        if (manejo_confirmacion != NULL) confirmacion = manejo_confirmacion((lista->arreglo[posicion]));

        // Permite cancelar la baja por medio de la funcion 'manejo_confirmacion'
        if (confirmacion) {
            for (int i=posicion; i<lista->limite_superior; i++) {
                lista->arreglo[i] = lista->arreglo[i+1];
            }

            // Reduce el limite superior en UNO
            lista->limite_superior--;
            // Actualiza el valor de salida
            salida = BAJA_EXITOSA;
        }
        else salida = BAJA_CANCELADA;
    }

    return salida;
}

int LSO_modificacion(ListaSO *lista,char codigo_envio[],int (*manejo_remplazo)(Envio *)) {

    int posicion, exito_localizar, salida = MODIFICACION_CANCELADA; // salida por defecto

    // Se busca el 'codigo_envio' en la lista
    posicion = LSO_localizar(lista,codigo_envio,&exito_localizar);

    // Si existe el elemento, se procesa la modificacion
    if (exito_localizar == LOCALIZACION_EXITOSA) {
        // Variable para confirmar la modificacion del elemento
        // (por defecto NO se lleva a cabo la modificacion)
        int confirmacion = 0;
        // Objeto ENVIO temporal intermedio para modificar sus campos
        Envio temporal = lista->arreglo[posicion];

        // 'manejo_remplazo' es puntero a una funcion que modificara los campos de 'temporal'
        // para posteriormente aplicarlos en la lista. Su retorno sirve para confirmar o
        // cancelar la modificacion.
        // NOTA: LA FUNCION NO DEBE MODIFICAR EL CODIGO DE ENVIO
        if (manejo_remplazo != NULL) confirmacion = manejo_remplazo(&temporal);

        // Se guardan los cambios en caso de confirmacion
        if (confirmacion) {
                lista->arreglo[posicion] = temporal;
                //Se actualiza la salida
                salida = MODIFICACION_EXITOSA;
        }
    }
    else salida = MODIFICACION_ERROR_NO_EXISTE;

    return salida;
}

int LSO_consulta(ListaSO *lista, char codigo_envio[], Envio *consultado) {
    int posicion, exito_localizar, salida = CONSULTA_ERROR_NO_EXISTE;

    // Se busca el elemento en la lista, y se captura su posicion
    posicion = LSO_localizar(lista,codigo_envio,&exito_localizar);

    // Si el elemento existe, se procesa.
    // Caso contrario la funcion continua y retorna 'CONSULTA_ERROR_NO_EXISTE'
    if (exito_localizar == LOCALIZACION_EXITOSA) {
        // Se devuelve por puntero el elemento buscado
        *consultado = lista->arreglo[posicion];
        // Se actualiza la salida de la funcion
        salida = CONSULTA_EXITOSA;
    }
    return salida;
}
