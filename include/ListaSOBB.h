#ifndef LISTASOBB_H
#define LISTASOBB_H

#include "Envio.h"

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
void LSOBB_init(ListaSO *);

// --- LOCALIZAR
int LSOBB_localizar(ListaSO *,char [], int *);

// --- ALTA
int LSOBB_alta(ListaSO *,Envio);

// --- BAJA
int LSOBB_baja(ListaSO *,char [],int (*)(Envio));

// --- MODIFICAR
int LSOBB_modificacion(ListaSO *,char [], int (*)(Envio *));

// --- CONSULTA
int LSOBB_consulta(ListaSO *, char [],Envio *);

#endif // LISTASOBB_H
