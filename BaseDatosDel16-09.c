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
#define NUM_MIN_DIGITO_CBU 0
#define NUM_MAX_DIGITO_CBU 9
#define MAX_CARACT_CBU 22 //DESPUES DE 6 CEROS COMIENZA MI NUM AZAR A PARTIR DE LA POSICION 7
#define NUM_MIN_CLAVES_CAJERO_TELEFONICA 1111
#define NUM_MAX_CLAVES_CAJERO_TELEFONICA 9999
#define MAX_CIUDADES_AMBA 32
#define MAX_CARAC_ALIAS 32

typedef enum {
    DNI=1,
    PASAPORTE,
    CUIL
}tipoDocumentoPersona_t;
typedef struct{
    
	char provincia[MAX_CARACT];
	int ciudadesBsAs;
	char calle[MAX_CARACT];
	unsigned short numero; //De 0 a 65.535// En los scanf o printf %hu
}domicilio_t;
typedef struct{
    unsigned short int claveCajero;//De 0 a 65.535
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
	unsigned long celular;//(unsigned long): 0 a 18,446,744,073,709,551,615 
	contrasenias_t contraseniasUsuario; //Todas las contrasenias que debe tener cada cliente
	char cbu[MAX_CARACT_CBU];//ESTE DATO SE DEBE GENERAR AUTOMATICAMENTE DEBE ESTAR EN UNA FUNCION
	char alias[MAX_CARACT]; //ESTE DATO SE DEBE GENERAR AUTOMATICAMENTE DEBE ESTAR EN UNA FUNCION
	

}registroPersona_t;
typedef enum {
    REGISTRARSE=1,
    INICIAR_SESION,
    SALIR
}opcion_t;
//PROTOTIPO DE FUNCIONES
int menu(void);
void cargarDatosEnElRegistro(registroPersona_t [], int);
void mostrarDatosDelRegistro(registroPersona_t []);
void tiposDeDocumento(registroPersona_t [], tipoDocumentoPersona_t , int);
void mostrarMensajeDeLasCiudades(void);
void ciudadesEnBsAs(registroPersona_t [], int);
void cargarStringCBU(registroPersona_t [], int);
void cargarContranias(registroPersona_t [], int );
int verificarMail(registroPersona_t [], int);
int verificarCelular(registroPersona_t [], int);
void alias(int, registroPersona_t []);
int verificarClaveMobile(registroPersona_t [], int);

int main(void) {
    int opcionUsuario,cont=0;
    
    registroPersona_t clientes[MAX_CLIENTES];
    srand(time(NULL));//PARA ACTIVAR EL NUMERO ALAZAR USARLO PARA LA CLAVE CAJERO. CREAR CBU.
    do{
        opcionUsuario= menu();
        switch(opcionUsuario){
        case REGISTRARSE://Opcion para Registrarse
            cargarDatosEnElRegistro(clientes, cont);
            cont++;
            break;
        case INICIAR_SESION://Opcion para Iniciar sesion
            printf("FALTA DESARROLLAR ESTA PARTE DEL CODIGO");
            break;
    }while(opcionUsuario!=SALIR);
    //printf("MUESTRA LOS DATOS INGRESADOS");
    //mostrarDatosDelRegistro(clientes);
	return 0;
}

int menu(void){
    printf("Bienvenido al programa\n");
    int opcionUsuario;
    do{
        printf("\n\t\t\t MENU DE OPCIONES DE CLIENTES\n");
        printf("\n\n\t\t\t Registrarse <1>\n");
        printf("\n\n\t\t\t Iniciar Sesion <2>\n");
        printf("\n\n\t\t\t Salir <3>\n");
        scanf("%d", &opcionUsuario);
    }while(opcionUsuario<1 ||opcionUsuario>3);
    return opcionUsuario;
}
void cargarDatosEnElRegistro(registroPersona_t clientes[MAX_CLIENTES],int cont){
    int opcionDocumento=0, banderaMail=0, banderaCelular=0, banderaClaveMobile=0;
    printf("Ingrese su nombre \n");
    scanf("%s", clientes[cont].nombres);
    //fflush(stdin);
    printf("Ingrese su apellido\n");
    scanf("%s", clientes[cont].apellido);
    //fflush(stdin);
    printf("Ingrese tipo de documento. \n[1] DNI\n[2] PASAPORTE \n[3] CUIL\n");
    scanf("%d", &opcionDocumento);
    clientes[cont].tipoDocumento= opcionDocumento;
    tiposDeDocumento(clientes, clientes[cont].tipoDocumento, cont);
    fflush(stdin);
    printf("Ingrese el nombre de su provincia\n");//SOLAMENTE ESTA DISPONIBLE BUENOS AIRES//
    gets(clientes[cont].domicilioCliente.provincia);
    //fflush(stdin);
    mostrarMensajeDeLasCiudades();
    ciudadesEnBsAs(clientes, cont);
    printf("Ingrese el nombre de su calle \n");
    scanf("%s", clientes[cont].domicilioCliente.calle);
    fflush(stdin);
    printf("Ingrese el numero de su domicilio \n");
    scanf("%hu", &clientes[cont].domicilioCliente.numero);
    //fflush(stdin);

    do{
        printf("Ingrese su mail\n");
        scanf("%s", clientes[cont].mail);
        banderaMail= verificarMail(clientes, cont);
    }while(banderaMail==0);
    fflush(stdin);
    do{
        printf("Ingrese su celular\n");
        scanf("%lu", &clientes[cont].celular);
        banderaCelular= verificarCelular(clientes,cont);
    }while(banderaCelular==0);

    cargarContranias(clientes, cont);
    do{
        printf("Ingrese su claveMobile:\n");
        printf("Esta debe tener al menos:\n8 caracteres en ellos se deben encontrar:\n1 caracter especial\n1 numero\n1 mayuscula\n1 minuscula\n");
        scanf("%s", clientes[cont].contraseniasUsuario.claveMobile);
        banderaClaveMobile= verificarClaveMobile(clientes, cont);
    }while(banderaClaveMobile==0);
    //fflush(stdin);
    
    cargarStringCBU(clientes, cont);
    printf("Su CBU es: %s\n", clientes[cont].cbu);
    alias(cont,clientes);
}
int verificarClaveMobile(registroPersona_t clientes[], int cont){
    int banderaMayuscula=0, banderaCaracterEspecial=0, banderaCaracterArroba=0, banderaMinuscula=0,banderaNro=0;
    int banderaClaveMobile=0;
    if(sizeof(clientes[cont].contraseniasUsuario.claveMobile)<8){//CONSULTAR POR ESTA LINEA
        printf("El tamaño de la cadena es invalido.\n Intenlo nuevamente");
    }else{ 
        for(int i=0; i<MAX_CARACT;i++){
            if(clientes[cont].contraseniasUsuario.claveMobile[i] =='@'){
                banderaCaracterArroba=1;
                //printf("SE ENCONTRO UN ARROBA\n");
            }else if(clientes[cont].contraseniasUsuario.claveMobile[i]>='A' && clientes[cont].contraseniasUsuario.claveMobile[i]<='Z'){
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(clientes[cont].contraseniasUsuario.claveMobile[i]>='a' && clientes[cont].contraseniasUsuario.claveMobile[i]<='z'){
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(clientes[cont].contraseniasUsuario.claveMobile[i]=='-' || clientes[cont].contraseniasUsuario.claveMobile[i]=='_' || clientes[cont].mail[i]=='.'){
                //printf("SE ENCONTRO UN CARAC_ESPECIALES\n");
                banderaCaracterEspecial=1;
            }else if(clientes[cont].contraseniasUsuario.claveMobile[i]>='0' &&clientes[cont].contraseniasUsuario.claveMobile[i]<='9'){
                banderaNro=1;
                //printf("SE ENCONTRO UN NRO\n");
            }
        }
        if(banderaCaracterArroba==1 && banderaMayuscula>=1 && banderaCaracterEspecial>=1 && banderaMinuscula>=1 && banderaNro>=1){
            banderaClaveMobile=1;
            printf("La ClaveMobile es valido\n");
        }else{
            printf("La ClaveMobile no cumple con alguna condicion.\nIntentelo nuevamente:\n");
        }
        return banderaClaveMobile;
    }
}
int verificarCelular(registroPersona_t clientes[], int cont){
    int banderaValidaCelular=0;
    unsigned long minNumCelular, maxNumCelular;
    minNumCelular=1111111111;
    maxNumCelular=1199999999;
    if(clientes[cont].celular>minNumCelular||clientes[cont].celular<maxNumCelular){
        printf("El nro de celular es valido\n");
        banderaValidaCelular=1;
    }else{
        printf("El nro de celular no es valido\nIntentenlo nuevamente:\n");
    }
    return banderaValidaCelular;
}
int verificarMail(registroPersona_t clientes[], int cont){
    int banderaMayuscula=0, banderaCaracterEspecial=0, banderaCaracterArroba=0, banderaMinuscula=0;
    int banderaMail=0;
    for(int i=0; i<MAX_CARACT;i++){
        if(clientes[cont].mail[i] =='@'){
            banderaCaracterArroba=1;
            //printf("SE ENCONTRO UN ARROBA\n");
        }else if(clientes[cont].mail[i]>='A' && clientes[cont].mail[i]<='Z'){
            banderaMayuscula=1+banderaMayuscula;
            //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
        }else if(clientes[cont].mail[i]>='a' && clientes[cont].mail[i]<='z'){
            banderaMinuscula=1+banderaMinuscula;
            //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
        }else if(clientes[cont].mail[i]=='-' || clientes[cont].mail[i]=='_' || clientes[cont].mail[i]=='.'){
            //printf("SE ENCONTRO UN CARAC_ESPECIALES\n");
            banderaCaracterEspecial=1;
        }
    }
    if(banderaCaracterArroba==1 && banderaMayuscula>=1 && banderaCaracterEspecial>=1 && banderaMinuscula>=1){
        banderaMail=1;
        printf("El mail es valido\n");
    }else{
        printf("El mail no cumple con alguna condicion.\nIntentelo nuevamente:\n");
    }
    return banderaMail;
}
void cargarContranias(registroPersona_t clientes[], int cont){
    clientes[cont].contraseniasUsuario.claveCajero=(rand()%(NUM_MAX_CLAVES_CAJERO_TELEFONICA-NUM_MIN_CLAVES_CAJERO_TELEFONICA+1)+NUM_MIN_CLAVES_CAJERO_TELEFONICA);//PARA QUE ME GENERE UN NUM ALAZAR
    //printf("contraseniasUsuario.claveCajero: %d\n",clientes[cont].contraseniasUsuario.claveCajero);
    clientes[cont].contraseniasUsuario.claveTelefonica=(rand()%(NUM_MAX_CLAVES_CAJERO_TELEFONICA-NUM_MIN_CLAVES_CAJERO_TELEFONICA+1)+NUM_MIN_CLAVES_CAJERO_TELEFONICA);//PARA QUE ME GENERE UN NUM ALAZAR
    //printf("contraseniasUsuario.claveTelefonica: %d\n",clientes[cont].contraseniasUsuario.claveTelefonica);
}
void cargarStringCBU(registroPersona_t clientes[], int cont){
    srand(time(NULL));
    for(int j=0; j<MAX_CARACT_CBU; j++){ 
        clientes[cont].cbu[j]=(rand()%(NUM_MAX_DIGITO_CBU - NUM_MIN_DIGITO_CBU+1)+NUM_MIN_DIGITO_CBU)+'0';//Le sumo cero xq sino me reconoce los digitos como nros sino que me lo pasa a ascii
        //printf("%c\n", clientes[cont].cbu[j]);
    }
    clientes[cont].cbu[MAX_CARACT_CBU]='\0';//Esto es porque sino me imprime basura al final del cbu
}
void mostrarMensajeDeLasCiudades(void){
    printf("Ingrese en la ciudad en la que vive. Siendo:\n");
    char ciudadesAmba[MAX_CIUDADES_AMBA][30] = {"Avellaneda", "Berazategui", "CABA","Campana", "Canuelas",
    "Ensenada", "Escobar","Ezeiza", "FlorencioVarela", "GralRodriguez", "GralSanMartin", "Hurlingham",
    "Ituzaingo", "JoseCPaz", "LaMatanza", "Lanus", "LomasDeZamora","Lujan","MalvinasArgentinas", 
    "MarcosPaz", "Merlo", "Moreno", "Moron", "Quilmes","Pilar","SanFernando","SanIsidro",
    "SanMiguel", "SanVicente", "Tigre", "VicenteLopez", "Zarate"};
    for(int i=0; i<MAX_CIUDADES_AMBA; i++){
        printf("[%d]  %s\n",i, ciudadesAmba[i]);
    }
}
void ciudadesEnBsAs(registroPersona_t clientes[MAX_CLIENTES], int cont){
    int aux;
    
    scanf("%d", &aux);
    if(aux>=0 && aux<MAX_CIUDADES_AMBA){
        clientes[cont].domicilioCliente.ciudadesBsAs=aux;
    }else{
        printf("Opcion no valida");
    }
    
}
void tiposDeDocumento(registroPersona_t clientes[MAX_CLIENTES], tipoDocumentoPersona_t opcionDocumento, int cont){
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
    scanf("%s", clientes[cont].documentoCliente);
}
void alias(int cont,registroPersona_t clientes[]){//Esta funcion crea un alias con palabras azar
    int aux1,aux2;
    char auxAlias[MAX_CARACT]={0};
    char aliasPalabarasRandom[MAX_CARAC_ALIAS][MAX_CARACT] = {"Perro", "Gato", "CABA","Loro", "Ave",
    "Ensalada", "Cebolla","Resaltador", "Cargador", "Zapato", "Pelota", "Mate",
    "Taza", "Mouse", "Lata", "Goma", "Lapiz","Plato","Malvinas", 
    "Monitor", "Lampara", "Morron", "Lapicera", "Cartuchera","Jabon","Alfajor","Sidra",
    "Botella", "Galletitas", "Tigre", "Leon", "Calendario"};
    aux1=(rand()%(MAX_CARAC_ALIAS-1)+1);
    strcat(auxAlias,aliasPalabarasRandom[aux1]);
    strcat(auxAlias,".");
    aux2=(rand()%(MAX_CARAC_ALIAS-1)+1);
    strcat(auxAlias,aliasPalabarasRandom[aux2]);
    //printf("%s", auxAlias);
    strcpy(clientes[cont].alias,auxAlias);
    printf("Su alias es: \n %s", clientes[cont].alias);

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
        printf("Celular: %lu \n", clientes[i].celular);
        printf("\n");
    }
}
