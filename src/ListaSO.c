#include "ListaSO.h"
#include "stdlib.h"
#include "Codigos_retornos.h"

void LSO_init(ListaSO *lista) {
    lista->limite_superior = -1;
}

int LSO_localizar(ListaSO *lista,char codigo_envio[], int *contador, int *celdas_consultadas) {
    // Busca en 'lista' el elemento con el campo 'codigo_envio',
    // si lo encuentra, la funcion devuelve el indice del arreglo,
    // si el elemento no se encuentra en la lista, devuelve la posicion donde deberia encontrarse.;

    // Contador
    *contador = 0;

    // Mientras no se pase el ultimo elemento y
    // el codigo de envio sea mayor o igual que el de Lista(contador)
    while (((*contador) <= lista->limite_superior) && strcmp(lista->arreglo[*contador].codigo_envio,codigo_envio) < 0 ) {
        (*contador)++;
    }

    // se devuelve la cantidad de celdas consultadas
    *celdas_consultadas = *contador + 1;

    // Si 'contador' supera el ultimo elemento, no se encontro el elemento
    if (*contador <= lista->limite_superior) {
        // Si 'codigo_envio' es distinto del de Lista(contador), no se encontro el elemento
        if (strcmp(lista->arreglo[*contador].codigo_envio,codigo_envio) == 0) return LOCALIZACION_EXITOSA;
        else return LOCALIZACION_ERROR_NO_EXISTE;
    }
    else return LOCALIZACION_ERROR_NO_EXISTE;
}


int LSO_alta(ListaSO *lista, Envio *nuevo, Costos_estructura *costos) {

    // Variable de retorno
    int salida = ALTA_ERROR_LISTA_LLENA, celdas_consultadas;
    // Variable de posicion del nuevo elemento
    int posicion_nuevo;

    // Comprueba si existe un ENVIO con CODIGO DE ENVIO similar
    // y obtiene la posicion en donde deberia ir el elemento
    int exito_localizar = LSO_localizar(lista,nuevo->codigo_envio,&posicion_nuevo,&celdas_consultadas);

    // Se procesa el ALTA
    if (exito_localizar == LOCALIZACION_ERROR_NO_EXISTE) {
        // Si la lista NO esta llena
        if (!(lista->limite_superior >= (LSO_TAM_ARREGLO - 1))) {
            // Se actualiza el limite superior
            lista->limite_superior++;

            int celdas_desplazadas = 0;     // para calculo de costos

            // Se desplazan los elementos hacia la derecha
            for (int i=lista->limite_superior; i > posicion_nuevo; i--) {
                lista->arreglo[i] = lista->arreglo[i-1];
                celdas_desplazadas++;
            }

            // Se agrega el nuevo elemento a la lista
            lista->arreglo[posicion_nuevo] = *nuevo;

            // Se actualiza la salida
            salida = ALTA_EXITOSA;

            // se guarda el costo del alta
            (costos->Alta.cantidad)++;
            costos->Alta.sumatoria_vector += celdas_desplazadas;
            if (costos->Alta.maximo < celdas_desplazadas) costos->Alta.maximo = celdas_desplazadas;
        }
    }
    else salida = ALTA_ERROR_CODIGO_EXISTENTE;

    return salida;
}


int LSO_baja(ListaSO *lista,Envio *elemento, Costos_estructura *costos) {

    int posicion, salida = BAJA_ERROR_NO_EXISTE, celdas_consultadas;
    int exito_localizar;

    // Se captura el resultado de la localizacion y su respectiva
    // posicion para 'codigo_envio'
    exito_localizar = LSO_localizar(lista,elemento->codigo_envio,&posicion,&celdas_consultadas);

    if (exito_localizar == LOCALIZACION_EXITOSA) {
        // si el elemento localizado es igual campo por campo ...
        if (Envio_sonIguales(elemento,&(lista->arreglo[posicion]))) {
            int celdas_desplazadas = 0;

            for (int i=posicion; i<lista->limite_superior; i++) {
                lista->arreglo[i] = lista->arreglo[i+1];
                celdas_desplazadas++;
            }

            // Reduce el limite superior en UNO
            lista->limite_superior--;
            // Actualiza el valor de salida
            salida = BAJA_EXITOSA;

            // se refleja el costo de la operacion
            (costos->Baja.cantidad)++;
            costos->Baja.sumatoria_vector += celdas_desplazadas;
            if (costos->Baja.maximo < celdas_desplazadas) costos->Baja.maximo = celdas_desplazadas;
        }
        else salida = BAJA_CANCELADA;
    }

    return salida;
}

int LSO_mostrarLista(ListaSO *lista) {
    // La funcion devuelve la cantidad de elementos de la lista
    if (lista->limite_superior > -1) {
        for (int i = 0; i<= lista->limite_superior; i++){
            printf("\n");
            Envio_imprimir(lista->arreglo[i]);
            // muestra de a 5 elementos en la lista
            if (((i+1) % 4) == 0) system("pause");
        }

        return lista->limite_superior + 1;
    }
    else return 0;
}

int LSO_evocar(ListaSO *lista, char codigo_envio[], Costos_estructura *costos) {
    int celdas_consultadas, posicion;   // 'posicion' esta para cumplir los parametros requeridos por 'localizar'

    if (LSO_localizar(lista,codigo_envio,&posicion,&celdas_consultadas) == LOCALIZACION_EXITOSA) {
        (costos->Evocacion_exitosa).cantidad++;
        costos->Evocacion_exitosa.sumatoria_vector += (float)celdas_consultadas;
        if (costos->Evocacion_exitosa.maximo < (float)celdas_consultadas) costos->Evocacion_exitosa.maximo = (float)celdas_consultadas;

        return EVOCAR_EXITOSO;
    }
    else {
        (costos->Evocacion_fallida).cantidad++;
        costos->Evocacion_fallida.sumatoria_vector += (float)celdas_consultadas;
        if (costos->Evocacion_fallida.maximo < (float)celdas_consultadas) costos->Evocacion_fallida.maximo = (float)celdas_consultadas;

        return EVOCAR_NO_EXISTE;
    }
}
