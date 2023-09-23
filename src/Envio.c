#include "Envio.h"

#include <string.h>

// Funciones

void Envio_init(Envio *envio) {
    // Inicializa los campos de la estructura ENVIO
    strcpy(envio->codigo_envio,"");
    envio->dni_receptor = ENVIO_DNI_MINIMO;
    envio->dni_remitente = ENVIO_DNI_MINIMO;
    strcpy(envio->domicilio_receptor,"");
    strcpy(envio->fecha_envio,ENVIO_FECHA_MINIMA);
    strcpy(envio->fecha_recepcion,ENVIO_FECHA_MINIMA);
    strcpy(envio->nombre_apellido_receptor,"");
    strcpy(envio->nombre_apellido_remitente,"");
}

void Envio_copiar(Envio *origen,Envio *destino) {
    // Copia los campos de ORIGEN a DESTINO
    strcpy(destino->codigo_envio,origen->codigo_envio);
    destino->dni_receptor = origen->dni_receptor;
    strcpy(destino->nombre_apellido_receptor,origen->nombre_apellido_receptor);
    strcpy(destino->domicilio_receptor,origen->domicilio_receptor);
    destino->dni_remitente = origen->dni_remitente;
    strcpy(destino->nombre_apellido_remitente,origen->nombre_apellido_remitente);
    strcpy(destino->fecha_envio,origen->fecha_envio);
    strcpy(destino->fecha_recepcion,origen->fecha_recepcion);
}

// controles

int Envio_esCorrecto_fecha(char fecha[]) {
    // Devuelve 1 si el formato de la fecha es correcto
    // |A|A|A|A|-|M|M|-|D|D|\0|
    //  0 1 2 3 4 5 6 7 8 9 10
    //          ^     ^

    // tiene 10 caracteres?
    if (strlen(fecha) == 10) {
        // recorre la cadena
        for (int i=0 ; i < 10; i++) {
            // controla que contenga solo numeros y guiones
            if (strchr("0123456789-",fecha[i]) != NULL) {
                // guion esta en posiciones 4 o 7
                if ((fecha[i] != '-' && (i == 4 || i == 7)) ||  // guion no esta en 4,7 OR
                    (i != 4 && i != 7 && fecha[i] == '-')      // hay guion fuera de 4,7
                    ) return 0;
            }
            else return 0;
        }
    }
    else return 0;

    return 1;
}

int Envio_esCorrecto_codigo(char codigo_envio[]) {
    // Devuelve 1 si el formato del CODIGO de ENVIO es correcto

    // tiene 7 caracteres?
    if (strlen(codigo_envio) == 7) {
        // recorre la cadena
        for (int i = 0; i < 7; i++) {
            // solo contiene letras y numeros
            if (strchr("ABCDEFGHIJKLMNOPQRSTUVXYZ0123456789",codigo_envio[i]) == NULL) return 0;
        }
    }
    else return 0;

    return 1;
}
