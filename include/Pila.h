#ifndef PILA_H
#define PILA_H

// tipo de elemento de la pila
#include "ArbolBB.h"

#define PILA_TAM_ARREGLO 300

typedef struct {
    ABB_Hoja* arreglo[PILA_TAM_ARREGLO];
    int tope;
} Pila;

void Pila_init(Pila *);

enum Pila_agregar_retornos {PILA_AGREGAR_EXITO, PILA_AGREGAR_ERROR_LLENA};
int Pila_agregar(Pila *, ABB_Hoja *);

enum Pila_quitar_retornos {PILA_QUITAR_EXITO, PILA_QUITAR_ERROR_VACIA};
int Pila_quitar(Pila *, ABB_Hoja **);

#endif // PILA_H
