//Libreria para el parcial
#include <stdio.h>
#include <string.h>/**        para usar funciones para strings       **/
#include <ctype.h> /**        para usar funciones para cadenas       **/
#include <stdlib.h> 
#include <ctype.h>/* proporciona un conjunto de funciones que se utilizan para realizar operaciones con caracteres*/
///////////////////////DEFINICIONES///////////////////////////////
#define LONGITUD_SUBE 16 // tamaño fijo de lops numero de la sube
#define MAX_NOMBRE 31 // Tamaño máximo para el nombre (como en el ejemplo de "alumno" [1])
#define MAX_APELLIDO 21 // Tamaño máximo para el apellido
#define MAX_ALIAS 21 // Tamaño máximo para el alias
#define MIN_NUMERO_EMPRESA 0// Rango de eleccion para la empresas 
#define MAX_NUMERO_EMPRESA 3// Rango de eleccion para la empresas 
#define MAX_CELULAR 15
#define MIN_NRO_CELULAR 1111111111 // Tamaño minimo  para el número de celular
#define MAX_NRO_CELULAR 1199999999 // Tamaño máximo para el número de celular
#define MIN_NRO_CELULAR_CODE_15 1511111111 // Tamaño minimo  para el número de celular
#define MAX_NRO_CELULAR_CODE_15 1599999999 // Tamaño máximo para el número de celular

//Estructura del menu
typedef enum{
    Menu_Perfil=1,
    Transferir,
    Ingresar_dinero_Depositar,
    Movimientos_de_cuentas,
    Pagos_y_servicios,
    SALIR
}opcion_t;//LAS OPCIONES PARA EL MENU PRINCIPAL
typedef enum{
    Recargas=1,
    Servicios,
    Exit
}opcion_pagos_servicios_t ;
typedef enum{
    Transporte=1,
    Celular,
    volver
}opcion_pagos_servicios_recargas_t ;
typedef struct {
    char alias[MAX_ALIAS];
    int saldo;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char celular[MAX_CELULAR];
} cliente_t;


/*////////////////////////////////////PROTOTIPO DE FUNCIONES ///////////////////*/
int menu(void);
void pausa(void);
int menu_pagos_servicios(cliente_t *cliente1);
void menu_recargas(cliente_t *cliente1);
void barraSeparadora(void);
void cargar_sube(cliente_t *cliente1);
void restar_saldo(cliente_t *cliente, float cantidad);
int cargar_celular(cliente_t *cliente1);
int validar_sube(char num_sube[]);
int validar_saldo(float monto_a_cargar, float saldo_actual);
int validar_empresa(int *empresa);
void validar_celular( long *numer_celular);

/*////////////////////////////////////////////////////////////////////////*/
/*/////////////////////CODIGO PRINCIPAL /////////////////////////////*/

int main(){
    // Crear un cliente
    cliente_t cliente1 = {"Juanito", 20000, "Juan", "Perez", "123456789"};
    int opcion_menu_interno = menu();
    do{
        /*opcion_menu_interno = menu();*/
        switch (opcion_menu_interno){
            case Menu_Perfil:
                printf("fuera de servicio");
                system("pause");
                break;
            
            case Transferir:
                    printf("fuera de servicio");
                    system("pause");
                break;
            
            case Ingresar_dinero_Depositar:
                    printf("fuera de servicio");
                    system("pause");
                break;
            
            case Movimientos_de_cuentas:
                    printf("fuera de servicio");
                    system("pause");
                break;
            
            case Pagos_y_servicios:
                    menu_pagos_servicios(&cliente1);
                break;
            default:
            printf("La opcion ingresada es invalida\n");
            system("pause");
        }
    } while (opcion_menu_interno != SALIR);

    return 0 ;
}
/*/////////////////////////////////////////////////////////////////////////*/
/*/////////////////////////////FUNCIOPNES DE MENUS /////////////////////////////////*/
int menu (void){
    system("cls");
    barraSeparadora();
    int op;
    do{ //Lo que va dentro de los printf va a depender del menu que pida el parcial
        printf("\n\t MENU DE OPCIONES DE CLIENTES\n");
        printf("\n\n\t Perfil <1>\n");
        printf("\n\n\t Transferir <2>\n");
        printf("\n\n\t Ingresar dinero <3>\n");
        printf("\n\n\t Movimientos de la cuenta  <4>\n");
        printf("\n\n\t Pagos y servicios <5>\n");
        printf("\n\n\t Salir <6>\n");
        printf("\n\n\t Ingrese Opcion [1-6] :\n");
        scanf("%d", &op);
    } while (op < Menu_Perfil || op > SALIR);
    return op;
    barraSeparadora();
}
int menu_pagos_servicios(cliente_t *cliente1){
    system("cls");
    int opcion_pag_ser=0;
    do{
        barraSeparadora();
        printf("\n\t ingrese una opcion [1 al 3]");
        printf("\n\t Recargas  <1>");
        printf("\n\t Servicios <2>");
        printf("\n\t volver al menu de inicio <3>\n");
        scanf("%d",&opcion_pag_ser);
        barraSeparadora();
        system("pause");
        switch (opcion_pag_ser){
            case Recargas:
                    menu_recargas(cliente1);
                    
                    break;
            case Servicios:
                    printf(" esta es la obcion de servicios");
                    system("pause");
                break;
            case Exit:
                    menu();//vuelve al menu principal 
                break;
            }
    }while (opcion_pag_ser < Recargas  || opcion_pag_ser > Exit);   
    return 0;
}
void menu_recargas(cliente_t *cliente1){
    system("cls");
    barraSeparadora();
    int opciones_recargas;
    printf("\t\t\t RECARGAS");
    printf("\n\t Transporte <1>");
    printf("\n\t celular <2>");
    printf("\n\t Sarir de este menu <3>\n");
    scanf("%d", &opciones_recargas);
    system("pause");
    barraSeparadora();
    do{
        switch (opciones_recargas){
            case Transporte:
                cargar_sube(cliente1);
                break;
            
            case Celular:
                cargar_celular(cliente1);
                break;
            case volver:
                menu_pagos_servicios (cliente1); 
                break;
            }
    } while (opciones_recargas< Transporte|| opciones_recargas > volver );
}
///////////////////////////////////////////////////////////////////////////////
void cargar_sube(cliente_t *cliente1) {
    char num_sube[LONGITUD_SUBE + 1]; // +1 para el carácter nulo
    int es_valido = 0;
    int monto_a_cargar,saldo_valido;
    do{
        printf("\n\tingrese el numero de su Sube: ");
        scanf("%s", num_sube);
        es_valido = validar_sube(num_sube);
        if (!es_valido) {
            printf("\n\tEl numero no es valido\n");
        }
    }while (!es_valido);
    do{
        printf("\n\t Ingrese el monto a cargar (ingrese 16 digitos)\n");
        scanf("%d",&monto_a_cargar);
        saldo_valido=validar_saldo(monto_a_cargar,cliente1->saldo);
        if (!saldo_valido){
            printf("\n\tEl saldo no es valido");
        }
    } while (!saldo_valido);
    printf("el saldo se ha cargado correctamente\n");
    restar_saldo(cliente1,monto_a_cargar);
    printf("%d",cliente1->saldo);
    system("pause");
    menu_recargas(cliente1);    
}
void restar_saldo(cliente_t *cliente, float cantidad) {
    if (cliente->saldo >= cantidad) {
        cliente->saldo -= cantidad;
    } else {
        printf("Saldo insuficiente.\n");
    }
}
int cargar_celular(cliente_t *cliente1){
    int empresa;
    long  long numero_celular;
    printf("\n\t Ingrese su operador de servicio [1 al 3]\n");
    printf("\n\t\t Claro <1>\n");
    printf("\n\t\t Movistar <2>\n");
    printf("\n\t\t Personal <3>\n");
    scanf("%d",&empresa);
    validar_empresa(&empresa);
    printf("\n\tIngrese numero de celular Ejemplo:1176073290\n");
    scanf("%ld",&numero_celular);
    validar_celular(&numero_celular);
    

}


///////////////////////////////validaciones //////////////////////////////////
int validar_sube(char num_sube[]) {
    if (strlen(num_sube) != LONGITUD_SUBE) {
    return 0; 
    }

    for (int i = 0; i < LONGITUD_SUBE; i++) {
        if (!isdigit(num_sube[i])) {
        return 0;
        }
    }
    return 1;
}
int validar_saldo(float monto_a_cargar, float saldo_actual) {
    if (monto_a_cargar > saldo_actual) {
        return 0; // El monto no es válido, es superior al saldo actual
    } else {
        return 1; // El monto es válido
    }
}
int validar_empresa(int *empresa) {
    while ((*empresa < MIN_NUMERO_EMPRESA) || (*empresa > MAX_NUMERO_EMPRESA)) {
        printf("\tEmpresa invalida porfavor vuelva a intentarlo\n");
        printf("\n\t Ingrese su operador de servicio [1 al 3]\n");
        printf("\n\t\tClaro <1>\n");
        printf("\n\t\tMovistar <2>\n");
        printf("\n\t\tpersonal <3>\n");
        scanf("%d", empresa); 
    }
    return *empresa;
}
void validar_celular( long *numer_celular) {
    do {
        if (*numer_celular < MIN_NRO_CELULAR || *numer_celular > MAX_NRO_CELULAR) {
            printf("Numero de celular invalido. Intente nuevamente.\n");
            scanf("%ld",numer_celular);
        }
    } while (*numer_celular < MIN_NRO_CELULAR || *numer_celular > MAX_NRO_CELULAR);

}


void barraSeparadora(void){
    printf("--------------------------------------------------------------------------\n");
}