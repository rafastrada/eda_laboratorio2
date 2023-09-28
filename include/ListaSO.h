#ifndef LISTASO_H
#define LISTASO_H


#include "Envio.h"
#include "Costos.h"

// Constantes
#define LSO_TAM_ARREGLO 300

// Definicion de la lista
// (el orden de la lista es CRECIENTE)
typedef struct {
    Envio arreglo[LSO_TAM_ARREGLO];

    // Indice del ultimo elemento en la lista
    // (Si la lista esta vacia, entonces vale -1)
    int limite_superior;
} ListaSO;

// --- INICIALIZAR
void LSO_init(ListaSO *);

// --- LOCALIZAR
int LSO_localizar(ListaSO *,char [], int *, Costos_estructura *);

// --- ALTA
int LSO_alta(ListaSO *,Envio *, Costos_estructura *);

// --- BAJA
int LSO_baja(ListaSO *,Envio *, Costos_estructura *);

void LSO_mostrarLista(ListaSO *);


#endif // LISTASO_H
