#include "Pila.h"

void Pila_init(Pila *pila) {
    // el tope tiene el indice del ultimo elemento
    pila->tope = -1;
}

int Pila_agregar(Pila *pila, ABB_Hoja *puntero) {
    // si pila no esta llena
    if (pila->tope < (PILA_TAM_ARREGLO - 1)) {
        pila->tope++;
        pila->arreglo[pila->tope] = puntero;
    }
    else return PILA_AGREGAR_ERROR_LLENA;

    return PILA_AGREGAR_EXITO;
}

int Pila_quitar(Pila *pila, ABB_Hoja **puntero) {
    // guarda en la direccion pasada por parametro el elemento
    // de la pila

    // si pila no esta vacia
    if (pila->tope > -1) {
        *puntero = pila->arreglo[pila->tope];
        pila->tope--;
    }
    else return PILA_QUITAR_ERROR_VACIA;
    return PILA_QUITAR_EXITO;
}
