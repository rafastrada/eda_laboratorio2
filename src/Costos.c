#include "Costos.h"


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
};
