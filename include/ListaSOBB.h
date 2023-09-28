#ifndef LISTASOBB_H
#define LISTASOBB_H

#include "Envio.h"
#include "Costos.h"

// Constantes
#define LISTA_TAM_ARREGLO 300

// Definicion de la lista
// (el orden de la lista es CRECIENTE)
typedef struct {
    Envio arreglo[LISTA_TAM_ARREGLO];

    // Indice del ultimo elemento en la lista
    // (Si la lista esta vacia, entonces vale -1)
    int limite_superior;
} ListaSOBB;

// --- INICIALIZAR
void LSOBB_init(ListaSOBB *);

// --- LOCALIZAR
int LSOBB_localizar(ListaSOBB *,char [], int *,int *);

// --- ALTA
int LSOBB_alta(ListaSOBB *,Envio,Costos_estructura *);

// --- BAJA
int LSOBB_baja(ListaSOBB *,char [],int (*)(Envio),Costos_estructura *);

// --- MODIFICAR
int LSOBB_modificacion(ListaSOBB *,char [], int (*)(Envio *));

// --- CONSULTA
int LSOBB_consulta(ListaSOBB *, char [],Envio *);

#endif // LISTASOBB_H
