#ifndef COSTOS_H
#define COSTOS_H

struct vector_costos {
    unsigned int cantidad;      // elementos de vector
    float sumatoria_vector;     // suma de todos los elementos
    float maximo;               // costo maximo del vector
    float media;                // media del vector
};

typedef struct {
    struct vector_costos Localizacion_exitosa;
    struct vector_costos Localizacion_fallida;
    struct vector_costos Alta;
    struct vector_costos Baja;
} Costos_estructura;

void Costos_estructura_init(Costos_estructura *costos) {
    // inicia los valores en cero
    costos->Localizacion_exitosa.cantidad = 0;
    costos->Localizacion_exitosa.sumatoria_vector = 0;
    costos->Localizacion_exitosa.maximo = 0;
    costos->Localizacion_exitosa.media = 0;

    costos->Localizacion_fallida.cantidad = 0;
    costos->Localizacion_fallida.sumatoria_vector = 0;
    costos->Localizacion_fallida.maximo = 0;
    costos->Localizacion_fallida.media = 0;

    costos->Alta.cantidad = 0;
    costos->Alta.sumatoria_vector = 0;
    costos->Alta.maximo = 0;
    costos->Alta.media = 0;

    costos->Baja.cantidad = 0;
    costos->Baja.sumatoria_vector = 0;
    costos->Baja.maximo = 0;
    costos->Baja.media = 0;
}

#endif // COSTOS_H
