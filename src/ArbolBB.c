#include "ArbolBB.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Codigos_retornos.h"
#include "Pila.h"

void ABB_initArbol(ArbolBB *arbol) {
    // inicia la raiz del arbol apuntando a un nodo externo
    arbol->raiz = NULL;
}

void ABB_initHoja(ABB_Hoja *hoja) {
    // inicia los punteros en NULL
    hoja->menores = NULL;
    hoja->mayores = NULL;
}

int ABB_localizar(ArbolBB *arbol, char codigo_envio[], ABB_Hoja **ubicacion, ABB_Hoja ***ubicacion_puntero_padre, Costos_estructura *costos) {
    /*
        La funcion devuelve por el parametro 'ubicacion' la direccion del nodo del elemento buscado
        (el nodo con el elemento o el nodo externo donde deberia encontrarse).
        El parametro 'ubicacion_puntero_padre' devuelve la direccion del PUNTERO que apunta al nodo del elemento buscado.
    */
    int celdas_consultadas = 0;     // para calculo de costos

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

        celdas_consultadas++;   // una celda consultada
    }

    celdas_consultadas++;   // se añade la consulta a la celda que cierra el bucle anterior

    // si no se apunta un nodo externo (null), entonces se encontro el elemento
    if (*ubicacion != NULL) {
        // se refleja el costo de la localizacion exitosa
        (costos->Localizacion_exitosa.cantidad)++;
        costos->Localizacion_exitosa.sumatoria_vector += celdas_consultadas;
        if (costos->Localizacion_exitosa.maximo < celdas_consultadas) costos->Localizacion_exitosa.maximo = celdas_consultadas;

        return LOCALIZACION_EXITOSA;
    }
    else {
        // se refleja el costo del fracaso de la localizacion
        (costos->Localizacion_fallida.cantidad)++;
        costos->Localizacion_fallida.sumatoria_vector += celdas_consultadas;
        if (costos->Localizacion_fallida.maximo < celdas_consultadas) costos->Localizacion_fallida.maximo = celdas_consultadas;

        return LOCALIZACION_ERROR_NO_EXISTE;
    }
}

int ABB_alta(ArbolBB *arbol, Envio *nuevo, Costos_estructura *costos) {
    ABB_Hoja *ubicacion, **ubicacion_puntero_padre;
    int salida;

    // si el nuevo elemento no se encuentra en el arbol, se procede a agregarlo
    if (ABB_localizar(arbol,nuevo->codigo_envio,&ubicacion,&ubicacion_puntero_padre,costos) == LOCALIZACION_ERROR_NO_EXISTE) {
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

            // costo de alta exitosa
            (costos->Alta.cantidad)++;
            costos->Alta.sumatoria_vector += 1.5;   // 0.5 por el puntero actualizado + 1.0 por la copia de los datos
            if (costos->Alta.maximo < 1.5) costos->Alta.maximo = 1.5;   // operacion redundante despues de la primera alta
            // @todo : quitar 'if' redundante de operacion de alta?
        }
        // caso que no haya memoria disponible
        else salida = ALTA_ERROR_LISTA_LLENA;
    }
    // caso que ya existiese un ENVIO similar
    else salida = ALTA_ERROR_CODIGO_EXISTENTE;

    return salida;
}

int ABB_baja(ArbolBB *arbol, Envio *elemento, Costos_estructura *costos) {
    ABB_Hoja *ubicacion, **ubicacion_puntero_padre;
    int salida;

    // Caso: si el elemento se encuentra en el arbol
    if (ABB_localizar(arbol,elemento->codigo_envio,&ubicacion,&ubicacion_puntero_padre,costos) == LOCALIZACION_EXITOSA) {
        // si el envio es igual campo por campo
        if (Envio_sonIguales(elemento,&(ubicacion->envio))) {
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

                // costo para nodo con 2 hijos
                costos->Baja.sumatoria_vector += 1.5;   // 0.5 por actualizar un puntero + 1.0 por copiar los datos del menor de los mayores
                if (costos->Baja.maximo < 1.5) costos->Baja.maximo = 1.5;
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

                // costo para nodo con 1 o 0 hijos
                costos->Baja.sumatoria_vector += 0.5;   // se actualiza un solo puntero
                if (costos->Baja.maximo < 0.5) costos->Baja.maximo = 0.5;
            }
            (costos->Baja.cantidad)++;      // un costo mas en el vector

			salida = BAJA_EXITOSA;
        }
		else salida = BAJA_ERROR_NO_EXISTE;
    }

	return salida;
}


int ABB_mostrarArbol_preorden(ArbolBB *arbol) {
    // la funcion devuelve la cantidad de elementos recorridos del arbol
    // (0 si el arbol esta vacio)

    // se inicia el cursor en la raiz
    ABB_Hoja *cursor_hoja = arbol->raiz;

    // si el arbol no esta vacio
    if (cursor_hoja != NULL) {
        int contador = 0;
	char *codigo_mayor, *codigo_menor, texto_null[] = "(null)";
        // se inicia una pila para almacenar punteros
        Pila pila_punteros; Pila_init(&pila_punteros);

        Pila_agregar(&pila_punteros, cursor_hoja);

        // mientras la pila no este vacia
        while (pila_punteros.tope > -1) {
            // se quita el tope de la pila
            Pila_quitar(&pila_punteros,&cursor_hoja);

            // Impresion por pantalla
            contador++;
		if (cursor_hoja->mayores != NULL) codigo_mayor = (cursor_hoja->mayores->envio).codigo_envio;
		else codigo_mayor = texto_null;
		if (cursor_hoja->menores != NULL) codigo_menor = (cursor_hoja->menores->envio).codigo_envio;
		else codigo_menor = texto_null;
            ABB_imprimirHoja(cursor_hoja,codigo_menor,codigo_mayor);

            //se muestra de a 5 elementos del arbol
            if (contador % 3 == 0) system("pause");

            // se agrega la rama derecha a la pila, para recorrerse despues de la izquierda
            if (cursor_hoja->mayores != NULL) Pila_agregar(&pila_punteros,cursor_hoja->mayores);
            // se agrega la rama izq al ultimo, para ser la primera en revisarle
            if (cursor_hoja->menores != NULL) Pila_agregar(&pila_punteros,cursor_hoja->menores);
        }

        return contador;
    }
    else return 0;
}


void ABB_liberarMemoria(ArbolBB *arbol) {
    //realizar un recorrido preorden por el arbol para liberar la memoria
    // de cada una de las hojas, ya que si se usa 'malloc', antes de
    // cerrar el programa debe ser liberada con 'free'
    ABB_Hoja *cursor_hoja = arbol->raiz;

    if (cursor_hoja != NULL) {
        Pila pila_punteros; Pila_init(&pila_punteros);
        Pila_agregar(&pila_punteros,cursor_hoja);

        while (pila_punteros.tope > -1) {
            Pila_quitar(&pila_punteros, &cursor_hoja);

            // agregar ramas a la pila
            if (cursor_hoja->mayores != NULL) Pila_agregar(&pila_punteros,cursor_hoja->mayores);
            if (cursor_hoja->menores != NULL) Pila_agregar(&pila_punteros,cursor_hoja->menores);

            free(cursor_hoja);
        }
    }
}
