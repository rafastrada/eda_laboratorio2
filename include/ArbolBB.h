#ifndef ARBOLBB_H
#define ARBOLBB_H

#include "Envio.h"


// definicion incompleta para reconocer el puntero hacia si mismo
typedef struct hoja ABB_Hoja;
struct hoja {
    Envio envio;
    ABB_Hoja *menores, *mayores;
};

// Estructura
typedef struct {
    ABB_Hoja *raiz;
} ArbolBB;


// Inicializacion de estructura
void ABB_initArbol(ArbolBB *);

// Inicializacion de hoja
void ABB_initHoja(ABB_Hoja *);

// Localizar
int ABB_localizar(ArbolBB *,char [], ABB_Hoja **, ABB_Hoja **);

// ALTA
int ABB_alta(ArbolBB *,Envio *);

// Baja
int ABB_baja(ArbolBB *,Envio *);

// Consulta
int ABB_consulta(ArbolBB *, char [], Envio *);


#endif // ARBOLBB_H
