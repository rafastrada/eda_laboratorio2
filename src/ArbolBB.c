/*#include "ArbolBB.h"
#include <stdlib.h>
#include <stdio.h>
#include "Codigos_retornos.h"

void ABB_init(ArbolBB *arbol) {
    // inicia la raiz del arbol apuntando a un nodo externo
    arbol->raiz = NULL;
}*/

int ABB_localizar(ArbolBB *arbol, char codigo_envio[], ABB_Hoja **ubicacion, ABB_Hoja **ubicacion_padre) {
    ABB_Hoja *visor, *visor_anterior;

    // se inicia la busqueda en la raiz
    visor = arbol->raiz; visor_anterior = visor;

    // mientras no se llegue a un nodo externo y
    // el codigo buscado no coincida con el apuntado
    while (visor != NULL &&
        strcmp(codigo_envio, visor->envio.codigo_envio) != 0) {
        // se guarda la hoja padre
        visor_anterior = visor;
        // si el codigo buscado es mayor que el apuntado...
        if (strcmp(codigo_envio,visor->envio.codigo_envio) > 0) visor = visor->mayores;
        else visor = visor->menores;
    }

    // se devuelven por parametros la ubicacion donde debe encontrarse el elemento
    // y su padre (necesario para altas y bajas)
    *ubicacion = visor; *ubicacion_padre = visor_anterior;

    // si no se apunta un nodo externo (null), entonces se encontro el elemento
    // @todo : la comparacion es por codigo o por todos los campos?
    if (visor != NULL) return LOCALIZACION_EXITOSA;
    else return LOCALIZACION_ERROR_NO_EXISTE;
}

int ABB_alta(ArbolBB *arbol, Envio *nuevo) {
    ABB_Hoja *ubicacion, *ubicacion_padre;
    int salida;

    // si el nuevo elemento no se encuentra en el arbol, se procede a agregarlo
    if (ABB_localizar(arbol,nuevo->codigo_envio,&ubicacion,&ubicacion_padre) == LOCALIZACION_ERROR_NO_EXISTE) {
        // se determina en cual de las hojas hijas debe ir el nuevo elemento
        if (strcmp(nuevo->codigo_envio,ubicacion_padre->envio.codigo_envio) < 0) ubicacion = ubicacion_padre->menores;
        else ubicacion = ubicacion_padre->mayores

        // se solicita memoria para el nuevo elemento
        ubicacion = (ABB_Hoja*) malloc(sizeof(ABB_Hoja));
        // si hay memoria disponible, se agrega el elemento
        if (ubicacion_padre->menores != NULL) {
            Envio_copiar(nuevo,&(ubicacion->envio));
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
    ABB_Hoja *ubicacion, *ubicacion_padre;
    int salida;

    if (ABB_localizar(arbol,elemento->codigo_envio,&ubicacion,&ubicacion_padre) == LOCALIZACION_EXITOSA) {
        // si el envio es igual campo por campo
        if (Envio_sonIguales(elemento,&(ubicacion->envio))) {
            // @todo : terminar
        }
    }
}
