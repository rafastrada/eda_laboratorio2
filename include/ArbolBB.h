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
int ABB_localizar(ArbolBB *,char [], ABB_Hoja **, ABB_Hoja ***);

// ALTA
int ABB_alta(ArbolBB *,Envio *);

// Baja
int ABB_baja(ArbolBB *,Envio *);

// Consulta
int ABB_consulta(ArbolBB *, char [], Envio *);

// Barrido preorden
int ABB_mostrarArbol_preorden(ArbolBB *);

// Liberar la memoria del arbol antes de cerrar el programa
void ABB_liberarMemoria(ArbolBB *);


#define ABB_imprimirHoja(H) printf("Codigo de Envio:\t\t\t%s\n"\
                                   "DNI de Receptor:\t\t\t%u\n"\
                                   "Nombre y Apellido de Receptor:\t\t%s\n"\
                                   "Domicilio de Receptor:\t\t\t%s\n"\
                                   "DNI de Remitente:\t\t\t%u\n"\
                                   "Nombre y Apellido de Remitente:\t\t%s\n"\
                                   "Fecha de Envio:\t\t\t\t%s\n"\
                                   "Fecha de Recepcion:\t\t\t%s\n"\
                                   "\t|\n"\
                                   "\t\\__Cod. de hijo Izq: %s\n"\
                                   "\t\\__Cod. de hijo Der: %s\n\n",\
                                   ((H)->envio).codigo_envio,\
                                   ((H)->envio).dni_receptor,\
                                   ((H)->envio).nombre_apellido_receptor,\
                                   ((H)->envio).domicilio_receptor,\
                                   ((H)->envio).dni_remitente,\
                                   ((H)->envio).nombre_apellido_remitente,\
                                   ((H)->envio).fecha_envio,\
                                   ((H)->envio).fecha_recepcion,\
                                   ((H)->menores->envio).codigo_envio,\
                                   ((H)->mayores->envio).codigo_envio)


#endif // ARBOLBB_H
