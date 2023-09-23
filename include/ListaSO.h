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
enum Lista_localizar_retornos {LOCALIZACION_ERROR_NO_EXISTE, LOCALIZACION_EXITOSA};
int LSO_localizar(ListaSO *,char [], int *);

// --- ALTA
enum Lista_alta_retornos {ALTA_ERROR_CODIGO_EXISTENTE, ALTA_EXITOSA , ALTA_ERROR_LISTA_LLENA};
int LSO_alta(ListaSO *,Envio);

// --- BAJA
enum Lista_baja_retornos {BAJA_ERROR_NO_EXISTE, BAJA_EXITOSA, BAJA_CANCELADA};
int LSO_baja(ListaSO *,char [],int (*)(Envio));

// --- MODIFICAR
enum Lista_modificacion_retornos {MODIFICACION_CANCELADA, MODIFICACION_EXITOSA, MODIFICACION_ERROR_NO_EXISTE};
int LSO_modificacion(ListaSO *,char [], int (*)(Envio *));

// --- CONSULTA
enum Lista_consulta_retornos {CONSULTA_ERROR_NO_EXISTE, CONSULTA_EXITOSA};
int LSO_consulta(ListaSO *, char [],Envio *);

#endif // LISTASO_H
