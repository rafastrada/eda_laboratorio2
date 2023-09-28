#include <stdio.h>
#include <stdlib.h>
#include "Envio.h"
#include "ListaSO.h"


// --- CADENAS GLOBALES
#define PANTALLA_BARRA "-----------------------------------------------------------------------\n"
#define PANTALLA_PRINCIPAL_OPERACIONES "\
1. Comparacion de Estructuras\n\
2. Mostrar Estructura\n\
3. Salir del programa\n"


// --- DEFINICION DE MACROS
// controla si una variable tipo 'char' es distinta de 's' y 'n' (util para entradas de tipo SI o NO)
#define entradaDistintaSino(X) ((X) != 's' && (X) != 'n')
// impresion de un envio en el formato por defecto (debe recibir un ENVIO por valor, NO puntero)
#define imprimirEnvio(E) printf("Codigo de Envio:\t\t\t%s\n"\
                                 "DNI del Receptor:\t\t\t%u\n"\
                                 "Nombre y Apellido del Receptor:\t\t%s\n"\
                                 "Domicilio del Receptor:\t\t\t%s\n"\
                                 "DNI del Remitente:\t\t\t%u\n"\
                                 "Nombre y Apellido del Remitente:\t%s\n"\
                                 "Fecha de Envio:\t\t\t\t%s\n"\
                                 "Fecha de Recepcion:\t\t\t%s\n",\
                                 (E).codigo_envio,(E).dni_receptor,\
                                 (E).nombre_apellido_receptor,(E).domicilio_receptor,\
                                 (E).dni_remitente,(E).nombre_apellido_remitente,\
                                 (E).fecha_envio,(E).fecha_recepcion);

//memorizacion previa


enum Memorizacion_previa {ERROR_ABRIR_FICHERO, MEMORIZACION_EXITOSA, MEMORIZACION_PARCIAL};

int Lectura_Operaciones(int *cant_repetidos, int *cargados){
    FILE *fichero;
    int resultado, repetidos = 0, indice = 0, operacion;

    Envio nuevo_envio; Envio_init(&nuevo_envio); //variable temporal

    fichero = fopen("Operaciones-Envios.txt","r"); //abrir el archivo
    if (fichero == NULL)

        return ERROR_ABRIR_FICHERO;

    else {
        while(!feof(fichero)){

            fscanf(fichero, "%d", &operacion);

            if(operacion == 1 || operacion == 2){

                fscanf(fichero," %[^\n]",nuevo_envio.codigo_envio);
                strcpy(nuevo_envio.codigo_envio,strupr(nuevo_envio.codigo_envio));

                fscanf(fichero,"%d",&nuevo_envio.dni_receptor);

                fscanf(fichero," %[^\n]",nuevo_envio.nombre_apellido_receptor);
                strcpy(nuevo_envio.nombre_apellido_receptor,strupr(nuevo_envio.nombre_apellido_receptor));

                fscanf(fichero," %[^\n]",nuevo_envio.domicilio_receptor);
                strcpy(nuevo_envio.domicilio_receptor,strupr(nuevo_envio.domicilio_receptor));

                fscanf(fichero,"%d",&nuevo_envio.dni_remitente);

                fscanf(fichero," %[^\n]",nuevo_envio.nombre_apellido_remitente);
                strcpy(nuevo_envio.nombre_apellido_remitente,strupr(nuevo_envio.nombre_apellido_remitente));

                fscanf(fichero," %[^\n]",nuevo_envio.fecha_envio);

                fscanf(fichero," %[^\n]",nuevo_envio.fecha_recepcion);

                if(operacion == 1){
                    resultado = LSO_alta( , nuevo_envio, );
                    resultado = LSOBB_alta( , nuevo_envio, );
                    resultado = ABB_alta( , nuevo_envio, );
                }else{
                    resultado = LSO_alta( , nuevo_envio, );
                    resultado = LSOBB_alta( , nuevo_envio, );
                    resultado = ABB_alta( , nuevo_envio, );
                }
            }

            if (resultado_alta == ALTA_ERROR_LISTA_LLENA){
                fclose(fichero);
                break;
            }
            if (resultado_alta == ALTA_ERROR_CODIGO_EXISTENTE){
                repetidos ++;
            }
            indice ++;
        }
    }

    *cargados = indice;
    *cant_repetidos = repetidos;
    fclose(fichero);

    if(resultado_alta == ALTA_ERROR_LISTA_LLENA){
        return MEMORIZACION_PARCIAL;
    }
    return MEMORIZACION_EXITOSA;
}

//Mostrar Lista
void Mostrar_Lista(Lista lista){
    int cantidad_envios = lista.limite_superior, contador = 0;
    if(cantidad_envios > -1){
        for(contador; contador <= cantidad_envios; contador++){
            printf("\nPosicion %d\n%s", contador, PANTALLA_BARRA);
            imprimirEnvio(lista.arreglo[contador]);
            if(contador % 5 == 0 && contador != 0){
                system("pause");
            }
        }
    }else{
    printf("La lista esta vacia\n\n");
    }
}

// Funcion para manejar la confirmacion de una BAJA
int confirmacionBaja(Envio envio) {
    // La funcion devuelve 1 si se ha confirmado la BAJA
    //                      0 si se ha cancelado

    printf("\nSe ha encontrado el Envio solicitado, se imprime a continuacion...\n\n");
    imprimirEnvio(envio);

    printf("\nEsta seguro que quiere eliminarlo? [S/N] >> ");

    //captura de la entrada del usuario
    fflush(stdin);
    char seleccion_usuario = getchar();

    while (entradaDistintaSino(seleccion_usuario)) {
        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
        fflush(stdin); seleccion_usuario = getchar();
    }

    if (seleccion_usuario == 's') return 1;
    else return 0;
}

int main()
{
    // Declaracion e inicializacion de la estructura LISTA
    Lista lista_envios; Lista_init(&lista_envios);

    // INICIO DEL PROGRAMA
    char seleccion_usuario_menu_principal = ' '; // variable para guardar la opcion elegida por usuario
    do {
        system("cls");  // limpa la pantalla

        printf("%sEL REVOLEO\tAdministracion de envios\n%s"
               "MENU PRINCIPAL\nElija una operacion:\n\n"
               "%s\n"
               ">> ",
               PANTALLA_BARRA,PANTALLA_BARRA,
               PANTALLA_PRINCIPAL_OPERACIONES);

        // Se captura la opcion ingresada por el usuario
        fflush(stdin); seleccion_usuario_menu_principal = getchar();

        // SELECCION DE OPERACION
        // ----------------------------------------------------------
        switch (seleccion_usuario_menu_principal) {

            // Buscar un envio por CODIGO DE ENVIO
            case '1': {
                // variables para ambito de funcion de consulta
                char seleccion_usuario_menu_buscar, codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
                int resultado_consulta, entrada_correcta;
                Envio envio_consultado;

                do {
                    // Imprime pantalla
                    system("cls");
                    printf(PANTALLA_BARRA
                           "Buscar un ENVIO por su CODIGO\n"
                           PANTALLA_BARRA
                           "Ingrese el CODIGO del ENVIO que desea consultar >>\t");



                    //Captura de respuesta de usuario
                    fflush(stdin); seleccion_usuario_menu_buscar = getchar();
                    while (entradaDistintaSino(seleccion_usuario_menu_buscar)) {
                        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
                        fflush(stdin); seleccion_usuario_menu_buscar = getchar();
                    }
                } while (seleccion_usuario_menu_buscar == 's'); break; // termina el switch
            }
            // Agregar un nuevo ENVIO
            case '2': {
                // variable para respuesta de usuario
                char seleccion_usuario_menu_alta;
                int entrada_correcta;     // para controles
                do {


                    // Captura de respuesta del usuario
                    fflush(stdin); seleccion_usuario_menu_alta = getchar();
                    while (entradaDistintaSino(seleccion_usuario_menu_alta)) {
                        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
                        fflush(stdin); seleccion_usuario_menu_alta = getchar();
                    }
                } while (seleccion_usuario_menu_alta == 's'); break; // termina el switch
            }
            case '4':{
                system("cls");
                int resultado, repetidos = 0, cant, cargas;
                resultado = Memorizacion_previa(&lista_envios, &repetidos, &cargas);

                if(resultado == MEMORIZACION_EXITOSA){
                    printf("La memorizacion fue exitosa.\n\n");
                }
                if(resultado == MEMORIZACION_PARCIAL){
                    printf("La memorizacion fue exitosa parcialmente.\n La cantidad de envios en el archivo era mayor al maximo de la lista\n\n ");
                }
                if(resultado == ERROR_ABRIR_FICHERO) {
                    printf("Existe un problema al intentar abrir el archivo.\n Por favor revisar el archivo \"Envios.txt\" \n");
                }
                if(resultado != ERROR_ABRIR_FICHERO) {
                    printf("Se intentaron cargar %d Envios \n", cargas);
                    printf("De los cuales:\n \t Envios repetidos: %d \n \t Envios cargados correctamente: %d \n ", repetidos, cargas - repetidos);
                }

            system("pause"); break;
            }

            case '5':{
            system("cls");
            printf(
                           "%sMostrando Estructura\n%s\n",
                           PANTALLA_BARRA,PANTALLA_BARRA);
            Mostrar_Lista(lista_envios);
            system("pause");
            }
        }

    } while (seleccion_usuario_menu_principal != '3');


    return 0;
}
