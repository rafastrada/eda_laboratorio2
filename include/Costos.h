#ifndef COSTOS_H
#define COSTOS_H

struct vector_costos {
    unsigned int cantidad;      // elementos de vector
    float sumatoria_vector;     // suma de todos los elementos
    float maximo;               // costo maximo del vector
    float media;                // media del vector
};

typedef struct {
    struct vector_costos Evocacion_exitosa;
    struct vector_costos Evocacion_fallida;
    struct vector_costos Alta;
    struct vector_costos Baja;
} Costos_estructura;

void Costos_estructura_init(Costos_estructura *);
void Costos_estructura_calculoMedias(Costos_estructura *);

#endif // COSTOS_H
