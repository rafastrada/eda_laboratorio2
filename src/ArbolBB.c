#include "ArbolBB.h"
#include <stdlib.h>
#include <stdio.h>
#include "Codigos_retornos.h"

void ABB_initArbol(ArbolBB *arbol) {
    // inicia la raiz del arbol apuntando a un nodo externo
    arbol->raiz = NULL;
}

void ABB_initHoja(ABB_Hoja *hoja) {
    // inicia los punteros en NULL
    hoja->menores = NULL;
    hoja->mayores = NULL;
}

int ABB_localizar(ArbolBB *arbol, char codigo_envio[], ABB_Hoja **ubicacion, ABB_Hoja ***ubicacion_puntero_padre) {
    /*
        La funcion devuelve por el parametro 'ubicacion' la direccion del nodo del elemento buscado
        (el nodo con el elemento o el nodo externo donde deberia encontrarse).
        El parametro 'ubicacion_puntero_padre' devuelve la direccion del PUNTERO que apunta al nodo del elemento buscado.
    */

    // se inicia la busqueda en la raiz
    *ubicacion = arbol->raiz, *ubicacion_puntero_padre = &(arbol->raiz);

    // mientras no se llegue a un nodo externo y
    // el codigo buscado no coincida con el apuntado
    while (*ubicacion != NULL &&
        strcmp(codigo_envio, (*ubicacion)->envio.codigo_envio) != 0) {

        // si el codigo buscado es mayor que el apuntado...
        if (strcmp(codigo_envio,(*ubicacion)->envio.codigo_envio) > 0) {
            *ubicacion_puntero_padre = &((*ubicacion)->mayores); // se guarda el puntero de la hoja padre
            *ubicacion = (*ubicacion)->mayores;
        }
        else {
            *ubicacion_puntero_padre = &((*ubicacion)->menores);
            *ubicacion = (*ubicacion)->menores;
        }
    }

    // si no se apunta un nodo externo (null), entonces se encontro el elemento
    // @todo : la comparacion es por codigo o por todos los campos?
    if (*ubicacion != NULL) return LOCALIZACION_EXITOSA;
    else return LOCALIZACION_ERROR_NO_EXISTE;
}

int ABB_alta(ArbolBB *arbol, Envio *nuevo) {
    ABB_Hoja *ubicacion, **ubicacion_puntero_padre;
    int salida;

    // si el nuevo elemento no se encuentra en el arbol, se procede a agregarlo
    if (ABB_localizar(arbol,nuevo->codigo_envio,&ubicacion,&ubicacion_puntero_padre) == LOCALIZACION_ERROR_NO_EXISTE) {
        // Como la localizacion no encontro el elemento, 'ubicacion' vale NULL, por lo que utilizamos el
        // puntero del padre que apuntaba la ubicacion que le corresponde a dicho elemento


        // se solicita memoria para el nuevo elemento
        *ubicacion_puntero_padre = (ABB_Hoja*) malloc(sizeof(ABB_Hoja));

        // si hay memoria disponible, se agrega el elemento
        if (*ubicacion_puntero_padre != NULL) {
            ABB_initHoja(*ubicacion_puntero_padre);  // se inician los hijos de la hoja nueva en NULL
            (*ubicacion_puntero_padre)->envio = *nuevo;     // se copian los campos uno a uno
            // se actualiza la salida
            salida = ALTA_EXITOSA;
        }
        // caso que no haya memoria disponible
        else salida = ALTA_ERROR_LISTA_LLENA;
    }
    // caso que ya existiese un ENVIO similar
    else salida = ALTA_ERROR_CODIGO_EXISTENTE;

    return salida;
}

int ABB_baja(ArbolBB *arbol, Envio *elemento) {
    ABB_Hoja *ubicacion, **ubicacion_puntero_padre;
    int salida;

    // Caso: si el elemento se encuentra en el arbol
    if (ABB_localizar(arbol,elemento->codigo_envio,&ubicacion,&ubicacion_puntero_padre) == LOCALIZACION_EXITOSA) {
        // si el envio es igual campo por campo
        if (Envio_sonIguales(elemento,&(ubicacion->envio))) {
            // @todo : terminar
            // Caso: el nodo a eliminar tiene 2 hijos
            if (ubicacion->menores != NULL && ubicacion->mayores != NULL) {
                //Se busca el menor de los mayores (y el puntero del padre)
                ABB_Hoja *hoja_remplazo = ubicacion->mayores, **hoja_remplazo_padre = &(ubicacion->mayores);
                while (hoja_remplazo->menores != NULL) {
                    hoja_remplazo_padre = &(hoja_remplazo->menores);
                    hoja_remplazo = hoja_remplazo->menores;
                }

                // Llegado al menor de los mayores, se copia sus datos al nodo a eliminar
                ubicacion->envio = hoja_remplazo->envio;
                // luego se redirije su puntero padre a su hijo
                // (si no tuviese, el valor que recibiria es NULL)
                *hoja_remplazo_padre = hoja_remplazo->mayores;

                // y finalmente se libera la memoria del lugar que ocupaba el menor de los mayores
                free(hoja_remplazo);

            }
            // Caso: menos de 2 hijos
            else {
                // se actualiza el puntero del padre hacia el hijo del elemento
                // (en el caso que no tuviese hijos, 'ubicacion_hijo' valdria NULL y se asignara este valor
                // al padre del elemento eliminado, y sigue siendo correcto)
                if (ubicacion->menores != NULL) *ubicacion_puntero_padre = ubicacion->menores;
                else *ubicacion_puntero_padre = ubicacion->mayores;

                // se borra de la memoria el elemento
                free(ubicacion);
            }
        }
    }
}

int ABB_consulta(ArbolBB *arbol, char codigo_envio[], Envio *consultado) {
    // Busca por el codigo pasado por parametro el ENVIO asociado.
    // Si este existe, se copia a 'consultado'

    ABB_Hoja *ubicacion, **ubicacion_puntero_padre;

    if (ABB_localizar(arbol,codigo_envio,&ubicacion,&ubicacion_puntero_padre) == LOCALIZACION_EXITOSA) {
        *consultado = ubicacion->envio;
        return CONSULTA_EXITOSA;
    }
    else return CONSULTA_ERROR_NO_EXISTE;
}
