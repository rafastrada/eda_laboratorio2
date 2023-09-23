#ifndef ARBOLBB_H
#define ARBOLBB_H


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
void ABB_init(ArbolBB *);

#endif // ARBOLBB_H
