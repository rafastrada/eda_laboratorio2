#include "ArbolBB.h"
#include <stdlib.h>
#include "Codigos_retornos.h"

void ABB_init(ArbolBB *arbol) {
    // inicia la raiz del arbol apuntando a un nodo externo
    arbol->raiz = NULL;
}

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
    if (visor != NULL) return LOCALIZACION_EXITOSA;
    else return LOCALIZACION_ERROR_NO_EXISTE;
}

int ABB_alta(ArbolBB *arbol, Envio *nuevo) {
    // @todo : terminar
}
