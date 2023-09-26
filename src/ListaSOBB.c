#include "ListaSOBB.h"
#include "stdlib.h"
#include "Codigos_retornos.h"

void LSOBB_init(ListaSOBB *lista) {

    strcpy(lista->arreglo[0].codigo_envio,"0");
    lista->limite_superior = -1;
}

/*Para la lista con busqueda binaria (LSOBB) la consigna a utilizar sera biseccion, lımite inferior exclusivo, lımite
superior inclusivo, testigo y segmento mas grande a la derecha.*/

int LSOBB_localizar(ListaSOBB *lista, char codigo_envio[], int *contador) {
    // Busca en 'lista' el elemento con el campo 'codigo_envio',
    // si lo encuentra, la funcion devuelve el indice del arreglo,
    // si el elemento no se encuentra en la lista, devuelve la posicion donde deberia encontrarse.

    // Limite inferior exclusivo
    int li = -1;

    // Limite superior inclusivo
    int ls = lista-> limite_superior + 1;

    // Testigo: (limite inferior + 1), limite superior
    int m = ceil((li + 1 + ls) / 2.0);

    // Mientras el limite inferior sea menor al limite superior
    while (li+1 < ls) {

        //Si el codigo de envio es menor al codigo de arreglo(m)
        if (strcmp(codigo_envio, lista->arreglo[m].codigo_envio) < 0) {
            //Actualiza el limite superior
            ls = m - 1;
        }else{
            //Actualiza el limite inferior
            li = m - 1;
        }

        //Actualizando testigo
        m = ceil((li + 1 + ls) / 2.0);

    }

    // Si codigo de envio es igual a el codigo de envio de arreglo(i)
    if (strcmp(lista->arreglo[m].codigo_envio,codigo_envio) == 0) {

        // Pasa ubicacion por parametro
        *contador = m;
        return LOCALIZACION_EXITOSA;

    }else{

        // Si el codigo de envio es menor al codigo de arreglo(i)
        if (strcmp(codigo_envio, lista->arreglo[m].codigo_envio) < 0)
            *contador = m;
        else
            *contador = m+1;
    }
    return LOCALIZACION_ERROR_NO_EXISTE;
}


int LSOBB_alta(ListaSOBB *lista, Envio nuevo) {

    // Variable de retorno
    int salida = ALTA_ERROR_LISTA_LLENA;
    // Variable de exito de localizar
    int posicion_nuevo;

    // Comprueba si existe un ENVIO con CODIGO DE ENVIO similar
    // y obtiene la posicion en donde deberia ir el elemento
    int exito_localizar = LSO_localizar(lista,nuevo.codigo_envio,&posicion_nuevo);

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


int LSOBB_baja(ListaSOBB *lista,char codigo_envio[], int (*manejo_confirmacion)(Envio)) {

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

int LSOBB_modificacion(ListaSOBB *lista,char codigo_envio[],int (*manejo_remplazo)(Envio *)) {

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

int LSOBB_consulta(ListaSOBB *lista, char codigo_envio[], Envio *consultado) {
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
