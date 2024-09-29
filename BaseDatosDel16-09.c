//Base de datos para la aplicacion del HomeBanking

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CLIENTES 2
#define MAX_CARACT 20
#define MAX_CARACT_MAIL 40
#define MAX_NUM_CELU 10
#define NUM_CARACT_DNI 8
#define NUM_CARACT_PASAPORTE 9
#define NUM_CARACT_CUIL 11
#define MAX_CARACT_CLAVE_ALFANUMERICA 6
#define NUM_MIN_CBU 1111111111111111
#define NUM_MAX_CBU 9999999999999999
#define MAX_CARACT_CBU 22 //DESPUES DE 6 CEROS COMIENZA MI NUM AZAR A PARTIR DE LA POSICION 7
#define NUM_MIN_CLAVES_CAJERO_TELEFONICA 1111
#define NUM_MAX_CLAVES_CAJERO_TELEFONICA 9999

typedef enum {
    Avellaneda=1,
    Berazategui,
    CABA,
    Campana,
    Canuelas,
    Ensenada,
    Escobar,
    Ezeiza,
    FlorencioVarela,
    GralRodriguez,
    GralSanMartin, 
    Hurlingham, 
    Ituzaingo, 
    JoseCPaz, 
    LaMatanza, 
    LaPlata, 
    Lanus, 
    LomasDeZamora, 
    Lujan, 
    MalvinasArgentinas,
    MarcosPaz, 
    Merlo, 
    Moreno, 
    Moron, 
    Quilmes, 
    Pilar, 
    SanFernando, 
    SanIsidro, 
    SanMiguel, 
    SanVicente, 
    Tigre, 
    VicenteLopez, 
    Zarate
}ciudadesEnBsAs_t;

typedef enum {
    DNI=1,
    PASAPORTE,
    CUIL
}tipoDocumentoPersona_t;

typedef struct{
    
	char provincia[MAX_CARACT];
	ciudadesEnBsAs_t ciudadesBsAs;
	char calle[MAX_CARACT];
	unsigned short numero; //De 0 a 65.535// En los scanf o printf %hu
}domicilio_t;

typedef struct{
    unsigned short int claveCajero;//De 0 a 65.535
	char claveAlfaNumerica[MAX_CARACT_CLAVE_ALFANUMERICA];//Falta cargarlo. PREGUNTAR AL PROFE
	char claveMobile[MAX_CARACT];
	unsigned short int claveTelefonica; //De 0 a 65.535
}contrasenias_t;

typedef struct {
	char nombres[MAX_CARACT];
	char apellido[MAX_CARACT];
	tipoDocumentoPersona_t tipoDocumento;
	char documentoCliente[MAX_CARACT];//Todos los tipos de documento segun el cliente
	domicilio_t domicilioCliente;//Todos los datos del domicilio del cliente
	char mail[MAX_CARACT_MAIL];
	char celular[MAX_NUM_CELU];
	contrasenias_t contraseniasUsuario; //Todas las contrasenias que debe tener cada cliente
	char cbu[MAX_CARACT_CBU];//ESTE DATO SE DEBE GENERAR AUTOMATICAMENTE DEBE ESTAR EN UNA FUNCION
	char alias[MAX_CARACT]; //ESTE DATO SE DEBE GENERAR AUTOMATICAMENTE DEBE ESTAR EN UNA FUNCION
	

}registroPersona_t;

//PROTOTIPO DE FUNCIONES
void cargarDatosEnElRegistro(registroPersona_t clientes[MAX_CLIENTES]);
void mostrarDatosDelRegistro(registroPersona_t clientes[MAX_CLIENTES]);
void tiposDeDocumento(registroPersona_t clientes[MAX_CLIENTES], tipoDocumentoPersona_t opcionDocumento, int i);
void mostrarMensajeDeLasCiudades(void);
void ciudadesEnBsAs(registroPersona_t clientes[MAX_CLIENTES], int i);
void cargarStringCBU(registroPersona_t clientes[MAX_CLIENTES], int i);

int main(void) {
    
	registroPersona_t clientes[MAX_CLIENTES];
    cargarDatosEnElRegistro(clientes);
    srand(time(NULL));//PARA ACTIVAR EL NUMERO ALAZAR USARLO PARA LA CLAVE CAJERO. CREAR CBU.
    printf("MUESTRA LOS DATOS INGRESADOS");
    mostrarDatosDelRegistro(clientes);
	return 0;
}

void cargarStringCBU(registroPersona_t clientes[MAX_CLIENTES], int i){
    for(int j=0; j<MAX_CARACT_CBU; j++){
        
        clientes[i].cbu[j]=0;
    }
}

void mostrarMensajeDeLasCiudades(void){
     printf("Ingrese en la ciudad en la que vive. Siendo:\n");
    for(int i = Avellaneda; i <= Zarate; i++){
        printf("[%d] ", i);
        switch (i){
            case Avellaneda: 
                printf("Avellaneda\n"); 
                break;
            case Berazategui:  
                printf("Berazategui\n"); 
                break;
            case CABA: 
                printf("CABA\n"); 
                break;
            case Campana: 
                printf("Campana\n"); 
                break;
            case Canuelas: 
                printf("Cañuelas\n"); 
                break;
            case Ensenada: 
                printf("Ensenada\n"); 
                    break;
            case Escobar: 
                printf("Escobar\n"); 
                break;
            case Ezeiza: 
                printf("Ezeiza\n"); 
                break;
            case FlorencioVarela: 
                printf("Florencio Varela\n"); 
                break;
            case GralRodriguez: 
                printf("Gral. Rodríguez\n"); 
                break;
            case GralSanMartin: 
                printf("Gral. San Martín\n"); 
                break;
            case Hurlingham: 
                printf("Hurlingham\n"); 
                break;
            case Ituzaingo: 
                printf("Ituzaingó\n"); 
                break;
            case JoseCPaz: 
                printf("José C. Paz\n"); 
                break;
            case LaMatanza: 
                printf("La Matanza\n"); 
                break;
            case LaPlata: 
                printf("La Plata\n"); 
                break;
            case Lanus: 
                printf("Lanús\n"); 
                break;
            case LomasDeZamora: 
                printf("Lomas de Zamora\n"); 
                break;
            case Lujan: 
                printf("Luján\n"); 
                break;
            case MalvinasArgentinas: 
                printf("Malvinas Argentinas\n"); 
                break;
            case MarcosPaz: 
                printf("Marcos Paz\n"); 
                break;
            case Merlo: 
                printf("Merlo\n");
                break;
            case Moreno: 
                printf("Moreno\n"); 
                break;
            case Moron: 
                printf("Morón\n"); 
                break;
            case Quilmes: 
                printf("Quilmes\n");
                break;
            case Pilar: 
                printf("Pilar\n"); 
                break;
            case SanFernando: 
                printf("San Fernando\n");
                break;
            case SanIsidro: 
                printf("San Isidro\n"); 
                break;
            case SanMiguel: 
                printf("San Miguel\n");
                break;
            case SanVicente:
                printf("San Vicente\n"); 
                break;
            case Tigre: 
                printf("Tigre\n");
                break;
            case VicenteLopez: 
                printf("Vicente López\n"); 
                break;
            case Zarate: 
                printf("Zárate\n"); 
                break;
            default: break;
        }
    }
    printf("\n");
}

void ciudadesEnBsAs(registroPersona_t clientes[MAX_CLIENTES], int i){
    int aux;
    
    scanf("%d", &aux);
    if(aux>=Avellaneda && aux<=Zarate){
        clientes[i].domicilioCliente.ciudadesBsAs=aux;
    }else{
        printf("Opcion no valida");
    }
    
}

void tiposDeDocumento(registroPersona_t clientes[MAX_CLIENTES], tipoDocumentoPersona_t opcionDocumento, int i){
   switch(opcionDocumento){
           case 1:
            printf("\nIngrese su numero de DNI: \n");
            break;
            
           case 2:
            printf("\nIngrese los caracteres de su Pasaporte: \n");
            break;
            
           case 3:
            printf("\nIngrese su numero de Cuil: \n");
            break;
            
            default:
                printf("\nOpcion no valida");
    }
    scanf("%s", clientes[i].documentoCliente);
}

void cargarDatosEnElRegistro(registroPersona_t clientes[MAX_CLIENTES]){
    int opcionDocumento;
   for(int i=0; i<MAX_CLIENTES; i++){
       
        printf("Ingrese su nombre \n");
        scanf("%s", clientes[i].nombres);
        //fflush(stdin);
        printf("Ingrese su apellido\n");
        scanf("%s", clientes[i].apellido);
        //fflush(stdin);
        printf("Ingrese tipo de documento. \n[1] DNI\n[2] PASAPORTE \n[3] CUIL\n");
        scanf("%d", &opcionDocumento);
        clientes[i].tipoDocumento= opcionDocumento;
        tiposDeDocumento(clientes, clientes[i].tipoDocumento, i);
        printf("Ingrese el nombre de su provincia\n");//SOLAMENTE ESTA DISPONIBLE BUENOS AIRES//
        gets(clientes[i].domicilioCliente.provincia);
        //fflush(stdin);
        mostrarMensajeDeLasCiudades();
        ciudadesEnBsAs(clientes, i);
        printf("Ingrese el nombre de su calle \n");
        scanf("%s", clientes[i].domicilioCliente.calle);
        fflush(stdin);
        printf("Ingrese el numero de su domicilio \n");
        scanf("%hu", &clientes[i].domicilioCliente.numero);
        //fflush(stdin);
        printf("Ingrese su mail\n");
        scanf("%s", clientes[i].mail);
        //fflush(stdin);
        printf("Ingrese su celular\n");
        scanf("%s", clientes[i].celular);
        //fflush(stdin);
        clientes[i].contraseniasUsuario.claveCajero=(rand()%(NUM_MAX_CLAVES_CAJERO_TELEFONICA-NUM_MIN_CLAVES_CAJERO_TELEFONICA+1)+NUM_MIN_CLAVES_CAJERO_TELEFONICA);//PARA QUE ME GENERE UN NUM ALAZAR
        /*for(int j=0; j<MAX_CARACT_CLAVE_ALFANUMERICA;j++){
            clientes[i].contraseniasUsuario.claveAlfaNumerica
            PREGUNTARLE AL PROFE COMO CARGAR EL VECTOR 
        }*/
        //falta cargar la clave alfanumerica
        printf("Ingrese su claveMobile, Debe tener al menos 8 caracteres y al menos 1 caracter especial\n");
        scanf("%s", clientes[i].contraseniasUsuario.claveMobile);//Preguntar como corroborar que esta bien.
        cargarStringCBU(clientes, i);//INICIALIZO EL STRING CON CEROS
        clientes[i].contraseniasUsuario.claveTelefonica=(rand()%(NUM_MAX_CLAVES_CAJERO_TELEFONICA-NUM_MIN_CLAVES_CAJERO_TELEFONICA+1)+NUM_MIN_CLAVES_CAJERO_TELEFONICA);
       // clientes[i].cbu=(rand()%(NUM_MAX_CBU - NUM_MIN_CBU+1)+NUM_MIN_CBU);CONSULTAR QUE ESTA MAL EN ESTA LINEA DEL CODIGO
        //Preguntarle al profe como cargar el NUM AZAR desde la posicion 7 del string
    }
}

void mostrarDatosDelRegistro(registroPersona_t clientes[MAX_CLIENTES]){
    for(int i=0; i<MAX_CLIENTES; i++){
        printf("Datos del cliente nro %d \n", i+1);
        printf("Nombre:  %s \n", clientes[i].nombres);
        printf("Apellido: %s \n", clientes[i].apellido);
        printf("Tipo de documento: %s \n", clientes[i].documentoCliente);
        printf("Provincia: %u \n", clientes[i].domicilioCliente.ciudadesBsAs);
        printf("Calle de su domicilio: %s", clientes[i].domicilioCliente.calle);
        printf("Nro: %hu \n", clientes[i].domicilioCliente.numero);
        printf("Mail: %s \n", clientes[i].mail);
        printf("Celular: %s \n", clientes[i].celular);
        printf("\n");
    }
}
