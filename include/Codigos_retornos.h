#ifndef CODIGOS_RETORNOS_H_INCLUDED
#define CODIGOS_RETORNOS_H_INCLUDED

/*
    Cabecera con los codigos de retornos de las funciones
    basicas de las estructuras.
    Como todas estas funciones (alta, baja, localizar, etc.)
    devuelven los mismos estados agrupamos en una misma cabecera
    los enumerados para todas las estructuras.
*/

enum Localizar_retornos {LOCALIZACION_ERROR_NO_EXISTE, LOCALIZACION_EXITOSA};

enum Alta_retornos {ALTA_ERROR_CODIGO_EXISTENTE, ALTA_EXITOSA , ALTA_ERROR_LISTA_LLENA};

enum Baja_retornos {BAJA_ERROR_NO_EXISTE, BAJA_EXITOSA, BAJA_CANCELADA};

enum Modificacion_retornos {MODIFICACION_CANCELADA, MODIFICACION_EXITOSA, MODIFICACION_ERROR_NO_EXISTE};

enum Consulta_retornos {CONSULTA_ERROR_NO_EXISTE, CONSULTA_EXITOSA};

enum Evocar_retornos {EVOCAR_NO_EXISTE, EVOCAR_EXITOSO};

#endif // CODIGOS_RETORNOS_H_INCLUDED
