#ifndef LISTASO_H
#define LISTASO_H


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
} ListaSO;

// --- INICIALIZAR
void LSO_init(ListaSO *);

// --- LOCALIZAR
int LSO_localizar(ListaSO *,char [], int *);

// --- ALTA
int LSO_alta(ListaSO *,Envio);

// --- BAJA
int LSO_baja(ListaSO *,char [],int (*)(Envio));

// --- MODIFICAR
int LSO_modificacion(ListaSO *,char [], int (*)(Envio *));

// --- CONSULTA
int LSO_consulta(ListaSO *, char [],Envio *);

#endif // LISTASO_H
