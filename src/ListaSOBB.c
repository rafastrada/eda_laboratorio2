#include "ListaSOBB.h"
#include "stdlib.h"
#include "Codigos_retornos.h"

void LSOBB_init(ListaSOBB *lista) {

    lista->limite_superior = -1;
}

/*Para la lista con busqueda binaria (LSOBB) la consigna a utilizar sera biseccion, lımite inferior exclusivo, lımite
superior inclusivo, testigo y segmento mas grande a la derecha.*/

int LSOBB_localizar(ListaSOBB *lista, char codigo_envio[], int *contador,Costos_estructura *costos) {
    // Busca en 'lista' el elemento con el campo 'codigo_envio',
    // si lo encuentra, la funcion devuelve el indice del arreglo,
    // si el elemento no se encuentra en la lista, devuelve la posicion donde deberia encontrarse.

    int salida = LOCALIZACION_ERROR_NO_EXISTE;
    // Para calculos de costos
    int auxiliar[LISTASOBB_TAM_ARREGLO], i, celdas_consultadas;

    for(i = 0; i <= lista->limite_superior; i++){
        auxiliar[i] = 0;
    }

    // Limite inferior exclusivo
    int li = -1;

    // Limite superior inclusivo
    int ls = lista->limite_superior;

    // Testigo: (limite inferior + 1), limite superior
    int m = ceil((li + 1 + ls) / 2.0);

    // Mientras el limite inferior sea menor al limite superior
    while (li + 1 < ls) {

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

        if(auxiliar[m] != 1){
            celdas_consultadas ++;
            auxiliar[m] = 1;
        }
    }

    // Suma otra celda consultada por la proxima comparacion
    if(auxiliar[m] != 1){
        celdas_consultadas ++;
        auxiliar[m] = 1;
    }

    // Si codigo de envio es igual a el codigo de envio de arreglo(m)
    if (strcmp(lista->arreglo[m].codigo_envio,codigo_envio) == 0) {

        // Pasa ubicacion por parametro
        *contador = m;
        salida = LOCALIZACION_EXITOSA;

        // costos de exito de localizacion
        (costos->Localizacion_exitosa.cantidad)++;
        costos->Localizacion_exitosa.sumatoria_vector += celdas_consultadas;
        if (costos->Localizacion_exitosa.maximo < celdas_consultadas) costos->Localizacion_exitosa.maximo = celdas_consultadas;

    }else{

        // Si el codigo de envio es menor al codigo de arreglo(m)
        if (strcmp(codigo_envio, lista->arreglo[m].codigo_envio) < 0)
            *contador = m;
        else
            *contador = m + 1;

        // costos de fracaso de localizacion
        (costos->Localizacion_fallida.cantidad)++;
        costos->Localizacion_fallida.sumatoria_vector += celdas_consultadas;
        if (costos->Localizacion_fallida.maximo < celdas_consultadas) costos->Localizacion_fallida.maximo = celdas_consultadas;
    }

    return salida;
}


int LSOBB_alta(ListaSOBB *lista, Envio *nuevo, Costos_estructura *costos) {

    // Variable de retorno
    int salida = ALTA_ERROR_LISTA_LLENA;
    // Variable de exito de localizar
    int posicion_nuevo, celdas_desplazadas = 0;

    // Comprueba si existe un ENVIO con CODIGO DE ENVIO similar
    // y obtiene la posicion en donde deberia ir el elemento
    int exito_localizar = LSOBB_localizar(lista,nuevo->codigo_envio,&posicion_nuevo, costos);

    // Se procesa el ALTA
    if (exito_localizar == LOCALIZACION_ERROR_NO_EXISTE) {
        // Si la lista NO esta llena
        if (!(lista->limite_superior >= (LISTASOBB_TAM_ARREGLO - 1))) {
            // Se actualiza el limite superior
            lista->limite_superior++;

            // Se desplazan los elementos hacia la derecha
            for (int i=lista->limite_superior; i > posicion_nuevo; i--) {
                lista->arreglo[i] = lista->arreglo[i-1];
                celdas_desplazadas ++;
            }

            // Se agrega el nuevo elemento a la lista
            lista->arreglo[posicion_nuevo] = *nuevo;

            // Se actualiza la salida
            salida = ALTA_EXITOSA;
            (costos->Alta.cantidad)++;
            costos->Alta.sumatoria_vector += celdas_desplazadas;
            if (costos->Alta.maximo < celdas_desplazadas) costos->Alta.maximo = celdas_desplazadas;

        }
    }
    else salida = ALTA_ERROR_CODIGO_EXISTENTE;

    return salida;
}


int LSOBB_baja(ListaSOBB *lista,Envio *elemento, Costos_estructura *costos) {

    int posicion, salida = BAJA_ERROR_NO_EXISTE;
    int exito_localizar, celdas_desplazadas;

    // Se captura el resultado de la localizacion y su respectiva
    // posicion para 'codigo_envio'
    exito_localizar = LSOBB_localizar(lista,elemento->codigo_envio,&posicion, costos);

    if (exito_localizar == LOCALIZACION_EXITOSA){

        if(Envio_sonIguales(elemento, &(lista->arreglo[posicion]))){
            for (int i= posicion; i<lista->limite_superior; i++){
                lista->arreglo[i] = lista->arreglo[i+1];
                celdas_desplazadas++;
            }
            // Reduce el limite superior en UNO
            lista->limite_superior--;

            // Actualiza el valor de salida
            salida = BAJA_EXITOSA;
            (costos->Baja.cantidad)++;
            costos->Baja.sumatoria_vector += celdas_desplazadas;
            if (costos->Baja.maximo < celdas_desplazadas) costos->Baja.maximo = celdas_desplazadas;
        }
    }
    return salida;
}

int LSOBB_mostrarLista(ListaSOBB *lista) {
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
}
