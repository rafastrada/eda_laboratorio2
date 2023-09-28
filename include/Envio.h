#ifndef ENVIO_H
#define ENVIO_H

// Tamanos de arreglos
#define ENVIO_TAM_CODIGO_DE_ENVIO 8
#define ENVIO_TAM_NOMBRE_APELLIDO 81
#define ENVIO_TAM_DOMICILIO 81
#define ENVIO_TAM_FECHA 11

// Limites de algunos campos
#define ENVIO_DNI_MINIMO 1000000
#define ENVIO_DNI_MAXIMO 99999999
#define ENVIO_FECHA_MINIMA "2000-01-01"


// Definicion de objeto Envio
typedef struct {
    char codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
    unsigned int dni_receptor;
    char nombre_apellido_receptor[ENVIO_TAM_NOMBRE_APELLIDO];
    char domicilio_receptor[ENVIO_TAM_DOMICILIO];
    unsigned int dni_remitente;
    char nombre_apellido_remitente[ENVIO_TAM_NOMBRE_APELLIDO];
    char fecha_envio[ENVIO_TAM_FECHA];
    char fecha_recepcion[ENVIO_TAM_FECHA];
} Envio;

// Funciones para el objeto Envio
void Envio_init(Envio *);
int Envio_sonIguales(Envio *,Envio *);

// Funciones de control
int Envio_esCorrecto_fecha(char []);
int Envio_esCorrecto_codigo(char []);
#define Envio_esCorrecto_dni(X) ((X) >= ENVIO_DNI_MINIMO && (X) <= ENVIO_DNI_MAXIMO) // NO pasar punteros


#define Envio_imprimir(E) printf("Codigo de Envio:\t\t\t%s\n"\
                                   "DNI de Receptor:\t\t\t%u\n"\
                                   "Nombre y Apellido de Receptor:\t\t%s\n"\
                                   "Domicilio de Receptor:\t\t\t%s\n"\
                                   "DNI de Remitente:\t\t\t%u\n"\
                                   "Nombre y Apellido de Remitente:\t\t%s\n"\
                                   "Fecha de Envio:\t\t\t\t%s\n"\
                                   "Fecha de Recepcion:\t\t\t%s\n\n",\
                                   (E).codigo_envio,\
                                   (E).dni_receptor,\
                                   (E).nombre_apellido_receptor,\
                                   (E).domicilio_receptor,\
                                   (E).dni_remitente,\
                                   (E).nombre_apellido_remitente,\
                                   (E).fecha_envio,\
                                   (E).fecha_recepcion)


#endif // ENVIO_H
