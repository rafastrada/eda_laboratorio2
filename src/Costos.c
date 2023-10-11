#include "Costos.h"


void Costos_estructura_init(Costos_estructura *costos) {
    // inicia los valores en cero
    costos->Evocacion_exitosa.cantidad = 0;
    costos->Evocacion_exitosa.sumatoria_vector = 0;
    costos->Evocacion_exitosa.maximo = 0;
    costos->Evocacion_exitosa.media = 0;

    costos->Evocacion_fallida.cantidad = 0;
    costos->Evocacion_fallida.sumatoria_vector = 0;
    costos->Evocacion_fallida.maximo = 0;
    costos->Evocacion_fallida.media = 0;

    costos->Alta.cantidad = 0;
    costos->Alta.sumatoria_vector = 0;
    costos->Alta.maximo = 0;
    costos->Alta.media = 0;

    costos->Baja.cantidad = 0;
    costos->Baja.sumatoria_vector = 0;
    costos->Baja.maximo = 0;
    costos->Baja.media = 0;
};

void Costos_estructura_calculoMedias(Costos_estructura *costos) {
    if (costos->Evocacion_exitosa.cantidad != 0) {
        costos->Evocacion_exitosa.media =
        costos->Evocacion_exitosa.sumatoria_vector /
        ((float)costos->Evocacion_exitosa.cantidad);
    } else costos->Evocacion_exitosa.media = 0;

    if (costos->Evocacion_fallida.cantidad != 0) {
        costos->Evocacion_fallida.media =
        costos->Evocacion_fallida.sumatoria_vector /
        ((float)costos->Evocacion_fallida.cantidad);
    } else costos->Evocacion_fallida.media = 0;

    if (costos->Alta.cantidad != 0) {
        costos->Alta.media =
        costos->Alta.sumatoria_vector /
        ((float)costos->Alta.cantidad);
    } else costos->Alta.media = 0;

    if (costos->Baja.cantidad != 0) {
        costos->Baja.media =
        costos->Baja.sumatoria_vector /
        ((float)costos->Baja.cantidad);
    } else costos->Baja.media = 0;
}
