//Base de datos para la aplicacion del HomeBanking

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CLIENTES 5
#define MIN_CARACTERES 3
#define MAX_LETRAS_PASAPORTE 3
#define MAX_CARACT_PASAPORTE 7
#define MAX_CARACT 20
#define MAX_CARACT_MAIL 40
#define MAX_NUM_CELU 10
#define NUM_MIN_CARACT_DNI 7
#define NUM_MAX_CARACT_DNI 8
#define NUM_CARACT_CUIL 11
#define MIN_CARACT_CLAVE_MOBILE_MAIL 8
#define NUM_MIN_DIGITO_CBU_DNI 0
#define NUM_MAX_DIGITO_CBU_DNI 9
#define MAX_CARACT_CBU 22 //DESPUES DE 6 CEROS COMIENZA MI NUM AZAR A PARTIR DE LA POSICION 7
#define NUM_MIN_CLAVES_CAJERO_TELEFONICA 1111
#define NUM_MAX_CLAVES_CAJERO_TELEFONICA 9999
#define MAX_CIUDADES_AMBA 32
#define MAX_CARAC_ALIAS 32//DESPUES AGREGAR MAS PALABRAS PARA EL ALIAS
#define NRO_DNI_MINIMO 1111111
#define NRO_DNI_MAXIMO 99999999
#define MIN_NRO_CELULAR 1111111111
#define MAX_NRO_CELULAR 1199999999
#define ALTURA_MIN_CALLE 1
#define ALTURA_MAX_CALLE 35000
#define DIGITOS_CELULAR 10
typedef enum 
{
    DNI=1,
    PASAPORTE
}tipoDocumentoPersona_t;
typedef struct
{
	char provincia[MAX_CARACT];
	int ciudadesBsAs;
	char calle[MAX_CARACT];
	unsigned short numero; //De 0 a 65.535// En los scanf o printf %hu
}domicilio_t;
typedef struct
{
    unsigned short int claveCajero;//De 0 a 65.535
	char claveMobile[MAX_CARACT];
	unsigned short int claveTelefonica; //De 0 a 65.535
}contrasenias_t;
typedef struct 
{
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
void barraSeparadora(void);
void cargarDatosEnElRegistro(registroPersona_t[], int);
void mostrarDatosDelRegistro(registroPersona_t[]);
void tiposDeDocumento(registroPersona_t [], tipoDocumentoPersona_t , int);
void mostrarMensajeDeLasCiudades(void);
void ciudadesEnBsAs(registroPersona_t[], int);
void mensajeParaUsuarioAdvertencias(void);
void cargarCBU(registroPersona_t[], int);
void cargarContrasenias(registroPersona_t[], int );
int verificarClaveMobile(registroPersona_t[], int);
void mensajeFaltanCondiones(int, int, int, int,int);
int verificarNombre(registroPersona_t[],int);
int verificarApellido(registroPersona_t[],int);
int verificarCalleDomicilio(registroPersona_t[], int);
int verificaAlturaDomicilio(registroPersona_t[], int);
int verificarProvincia(registroPersona_t[], int);
int verificarDNI(registroPersona_t[],int );
int verificarPasaporte(registroPersona_t[],int);
int verificarMail(registroPersona_t[], int);
int verificarCelular(registroPersona_t[], int);
void alias(int, registroPersona_t[]);

int main(void) 
{
    int opcionUsuario,cont=0;
    registroPersona_t cliente[MAX_CLIENTES];
    srand(time(NULL));//PARA ACTIVAR EL NUMERO ALAZAR USARLO PARA LA CLAVE CAJERO. CREAR CBU.
    do
    {
        opcionUsuario= menu();
        switch(opcionUsuario)
        {
            case REGISTRARSE://Opcion para Registrarse
                    cargarDatosEnElRegistro(cliente, cont);
                    cont++;
                break;
                
            case INICIAR_SESION://Opcion para Iniciar sesion
                    printf("FALTA DESARROLLAR ESTA PARTE DEL CODIGO");
                break;
        }
    }while(opcionUsuario!=SALIR);
    //printf("MUESTRA LOS DATOS INGRESADOS");
    //mostrarDatosDelRegistro(clientes);
	return 0;
}
int menu(void)
{
    int opcionUsuario=0;
    printf("Bienvenido al programa\n");
    do
    {
        printf("\n\t\t\t MENU DE OPCIONES DE CLIENTES\n");
        printf("\n\n\t\t\t Registrarse <1>\n");
        printf("\n\n\t\t\t Iniciar Sesion <2>\n");
        printf("\n\n\t\t\t Salir <3>\n");
        scanf("%d", &opcionUsuario);
    }while(opcionUsuario<1 ||opcionUsuario>3);
    return opcionUsuario;
}
void cargarDatosEnElRegistro(registroPersona_t cliente[MAX_CLIENTES],int cont)
{
    int opcionDocumento=0, EsMailValido=0,EsCelularValido=0, EsClaveMobileValido=0,EsNombreValido=0;
    int EsAlturaValida=0, EsDniValido=0, EsPasaporteValido=0, EsProvinciaValida=0 ,EsCalleValida=0;
    int EsApellidoValido;
    do
    {
        barraSeparadora();
        printf("Ingrese su nombre \n");
        scanf("%s",cliente[cont].nombres);
        EsNombreValido=verificarNombre(cliente, cont);
    }while(EsNombreValido==0);
    //fflush(stdin);
    do
    {
        barraSeparadora();
        printf("Ingrese su apellido\n");
        scanf("%s",cliente[cont].apellido);//Uso esta por si el apellido tiene mas de una palabra
        EsApellidoValido=verificarApellido(cliente, cont);
    }while(EsApellidoValido==0);
    barraSeparadora();
    fflush(stdin);//Limpio
    printf("Ingrese tipo de documento. \n[1] DNI\n[2] PASAPORTE \n[3] CUIL\n");
    scanf("%d", &opcionDocumento);
    switch(opcionDocumento)
    {
        case DNI:
            do 
            {
                cliente[cont].tipoDocumento= opcionDocumento;
                tiposDeDocumento(cliente, opcionDocumento,cont);
                EsDniValido= verificarDNI(cliente,cont);
            }while(EsDniValido==0);
        break;
        case PASAPORTE:
            do{
                cliente[cont].tipoDocumento= opcionDocumento;
                printf("Recuerde que el pasaporte consta de 3 letras y 4 nros, en ese orden.\n");
                tiposDeDocumento(cliente, opcionDocumento,cont);
                EsPasaporteValido=verificarPasaporte(cliente, cont);
            }while(EsPasaporteValido==0);
        
    }
    fflush(stdin);//Limpio
    do
    {
        barraSeparadora();
        printf("Ingrese el nombre de su provincia\n");//SOLAMENTE ESTA DISPONIBLE BUENOS AIRES//
        scanf("%s",cliente[cont].domicilioCliente.provincia);
        EsProvinciaValida= verificarProvincia(cliente, cont);
    } while (EsProvinciaValida==0);
    barraSeparadora();
    fflush(stdin);
    mostrarMensajeDeLasCiudades();
    ciudadesEnBsAs(cliente, cont);//La verificacion esta en esta misma funcion
    do{
        barraSeparadora();
        printf("Ingrese el nombre de su calle \n");
        scanf("%s",cliente[cont].domicilioCliente.calle);
        EsCalleValida= verificarCalleDomicilio(cliente, cont);
    }while(EsCalleValida==0);
    fflush(stdin);//Limpio
    do
    {   
        barraSeparadora();
        printf("Ingrese el numero de su domicilio \n");
        scanf("%hu", &cliente[cont].domicilioCliente.numero);
        EsAlturaValida= verificaAlturaDomicilio(cliente, cont);
    } while (EsAlturaValida==0);
    //fflush(stdin);
    do
    {
        barraSeparadora();
        mensajeParaUsuarioAdvertencias();
        printf("Ingrese su mail\n");
        scanf("%s", cliente[cont].mail);
        EsMailValido= verificarMail(cliente, cont);
    }while(EsMailValido==0);
    fflush(stdin);//Limpio
    do
    {
        barraSeparadora();
        printf("Ingrese su celular\n");
        scanf("%lu", &cliente[cont].celular);
        EsCelularValido= verificarCelular(cliente,cont);
    }while(EsCelularValido==0);
    cargarContrasenias(cliente, cont);
    do
    {
        barraSeparadora();
        printf("Ingrese su claveMobile:\n");
        mensajeParaUsuarioAdvertencias();
        printf("1 nro\n1 Mayuscula\n");
        scanf("%s", cliente[cont].contraseniasUsuario.claveMobile);
        EsClaveMobileValido= verificarClaveMobile(cliente, cont);
    }while(EsClaveMobileValido==0);
    barraSeparadora();
    fflush(stdin);//Limpio
    cargarCBU(cliente, cont);
    printf("Su CBU es: %s\n", cliente[cont].cbu);
    barraSeparadora();
    alias(cont,cliente);
    barraSeparadora();
    fflush(stdin);//Limpio
}
int verificarCalleDomicilio(registroPersona_t cliente[MAX_CLIENTES], int cont)
{
    int caracteresIngresadosPorUsuario=0, letrasEncontradas=0, banderaCalle=0, aux=0, aux2=0;
    int banderaMayuscula=0,banderaMinuscula=0,banderaEspacio=0;
    if(strlen(cliente[cont].domicilioCliente.calle)>=MIN_CARACTERES)
    {
        caracteresIngresadosPorUsuario=(strlen(cliente[cont].domicilioCliente.calle));//PARA VER CUANTOS CARACTERES INGRESO EL USUARIO
        for(int i=0; i<caracteresIngresadosPorUsuario;i++)
        {
            if(cliente[cont].domicilioCliente.calle[i]>='A' && cliente[cont].domicilioCliente.calle[i]<='Z')
            {
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(cliente[cont].domicilioCliente.calle[i]>='a' && cliente[cont].domicilioCliente.calle[i]<='z')
            {
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(cliente[cont].domicilioCliente.calle[i]== ' ')
            {
                banderaEspacio=1+banderaEspacio;
                //printf("SE ENCONTRO UN ESPACIO\n");
            }
        }
        
        letrasEncontradas=(banderaMayuscula+banderaMinuscula+banderaEspacio);//PARA VER CUANTAS LETRAS INGRESO EL USUARIO
        if(caracteresIngresadosPorUsuario==letrasEncontradas)
        {
            //printf("La calle es valida\n");
            banderaCalle=1;
        }else{
            aux=(caracteresIngresadosPorUsuario-letrasEncontradas);
            printf("Usted ingreso %d caracteres que no son una letra\nIntentelo nuevamente:\n", aux);
        }
    }else 
    {
        aux=strlen(cliente[cont].domicilioCliente.calle);
        aux2=MIN_CARACTERES-aux;
       printf("Usted ingreso un nombre de %d caracter.\n Le faltan %d caracteres.\nEl minimo son 3 caracteres \nIntentelo nuevamente\n", aux, aux2);
    }
    return banderaCalle;
}
int verificaAlturaDomicilio(registroPersona_t cliente[MAX_CLIENTES], int cont)
{
    int banderaAlturaDomicilio=0;
    if (cliente[cont].domicilioCliente.numero>ALTURA_MIN_CALLE && cliente[cont].domicilioCliente.numero<ALTURA_MAX_CALLE)
    {
        //printf("La altura es valida\n");
        banderaAlturaDomicilio=1;
    }else{
            printf("La altura no puede ser mayor a 35.000 \nIntentelo nuevamente:");
        }
    
    return banderaAlturaDomicilio;
}
int verificarNombre(registroPersona_t cliente[MAX_CLIENTES],int cont)
{
    int banderaNombre=0, aux=0, aux2=0,banderaMayuscula=0,banderaMinuscula=0;
    int banderaEspacio=0, letrasEncontradas=0, caracteresIngresadosPorUsuario=0;
    if(strlen(cliente[cont].nombres)>=MIN_CARACTERES)
    {
        caracteresIngresadosPorUsuario=(strlen(cliente[cont].nombres));//PARA VER CUANTOS CARACTERES INGRESO EL USUARIO
        for(int i=0; i<caracteresIngresadosPorUsuario;i++){
            if(cliente[cont].nombres[i]>='A' && cliente[cont].nombres[i]<='Z')
            {
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(cliente[cont].nombres[i]>='a' && cliente[cont].nombres[i]<='z')
            {
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(cliente[cont].nombres[i]== ' ')
            {
                banderaEspacio=1+banderaEspacio;
                //printf("SE ENCONTRO UN ESPACIO\n");
            }
        }
        
        letrasEncontradas=(banderaMayuscula+banderaMinuscula+banderaEspacio);//PARA VER CUANTAS LETRAS INGRESO EL USUARIO
        if(caracteresIngresadosPorUsuario==letrasEncontradas){
            banderaNombre=1;
        }else{
            aux=(caracteresIngresadosPorUsuario-letrasEncontradas);
            printf("Usted ingreso %d caracteres que no son una letra\nIntentelo nuevamente:\n", aux);
        }
        
        //printf("%zu",strlen(clientes[cont].nombres));
    }else 
    {
        aux=strlen(cliente[cont].nombres);
        aux2=MIN_CARACTERES-aux;
       printf("Usted ingreso un nombre de %d caracter.\n Le faltan %d caracteres.\nEl minimo son 3 caracteres \nIntentelo nuevamente\n", aux, aux2);
    }
    return banderaNombre;
}
int verificarApellido(registroPersona_t cliente[MAX_CLIENTES],int cont)
{
    int banderaApellido=0,letrasEncontradas=0, caracteresIngresadosPorUsuario=0;
    int banderaEspacio=0, aux2=0, banderaMinuscula=0, banderaMayuscula=0, aux=0;
    if(strlen(cliente[cont].apellido)>=3)
    {
        caracteresIngresadosPorUsuario=(strlen(cliente[cont].apellido));//PARA VER CUANTOS CARACTERES INGRESO EL USUARIO
        for(int i=0; i<caracteresIngresadosPorUsuario;i++){
            if(cliente[cont].apellido[i]>='A' && cliente[cont].apellido[i]<='Z')
            {
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(cliente[cont].apellido[i]>='a' && cliente[cont].apellido[i]<='z')
            {
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(cliente[cont].apellido[i]== ' ')
            {
                banderaEspacio=1+banderaEspacio;
                //printf("SE ENCONTRO UN ESPACIO\n");
            }
        }
        
        letrasEncontradas=(banderaMayuscula+banderaMinuscula+banderaEspacio);//PARA VER CUANTAS LETRAS INGRESO EL USUARIO
        if(caracteresIngresadosPorUsuario==letrasEncontradas){
            //printf("El apellido es valido\n");
            banderaApellido=1;
        }else{
            aux=caracteresIngresadosPorUsuario-letrasEncontradas;
            printf("Usted ingreso %d caracteres que no son letras\nIntentelo nuevamente\n", aux);
        }

    }else 
    {
        aux=strlen(cliente[cont].apellido);
        aux2=MIN_CARACTERES-aux;
       printf("Usted ingreso un apellido de %d caracter.\n Le faltan %d caracteres.\nEl minimo son 3 caracteres \nIntentelo nuevamente\n", aux, aux2); 
    }    
        
    return banderaApellido;
}
int verificarProvincia(registroPersona_t cliente[MAX_CLIENTES], int cont)
{
    int caracteresIngresadosPorUsuario=0, letrasEncontradas=0, banderaProvincia=0, aux=0, aux2=0;
    int banderaMayuscula=0,banderaMinuscula=0, banderaEspacio=0;
    if(strlen(cliente[cont].domicilioCliente.provincia)>=MIN_CARACTERES)
    {
        caracteresIngresadosPorUsuario=(strlen(cliente[cont].domicilioCliente.provincia));//PARA VER CUANTOS CARACTERES INGRESO EL USUARIO
        for(int i=0; i<caracteresIngresadosPorUsuario;i++)
        {
            if(cliente[cont].domicilioCliente.provincia[i]>='A' && cliente[cont].domicilioCliente.provincia[i]<='Z')
            {
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(cliente[cont].domicilioCliente.provincia[i]>='a' && cliente[cont].domicilioCliente.provincia[i]<='z')
            {
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(cliente[cont].domicilioCliente.provincia[i]== ' ')
            {
                banderaEspacio=1+banderaEspacio;
                //printf("SE ENCONTRO UN ESPACIO\n");
            }
        }
        letrasEncontradas=(banderaMayuscula+banderaMinuscula+banderaEspacio);//PARA VER CUANTAS LETRAS INGRESO EL USUARIO
        if(caracteresIngresadosPorUsuario==letrasEncontradas)
        {
            //printf("La provincia es valida\n");
            banderaProvincia=1;
        }else{
            aux=(caracteresIngresadosPorUsuario-letrasEncontradas);
            printf("Usted ingreso %d caracteres que no son una letra\nIntentelo nuevamente:\n", aux);
        }
    }else 
    {
        aux=strlen(cliente[cont].domicilioCliente.provincia);
        aux2=MIN_CARACTERES-aux;
       printf("Usted ingreso un nombre de %d caracter.\n Le faltan %d caracteres.\nEl minimo son 3 caracteres \nIntentelo nuevamente\n", aux, aux2);
    }
    return banderaProvincia;
}
int verificarDNI(registroPersona_t cliente[MAX_CLIENTES],int cont)
{
    int banderaDni=0, banderaNro=0, caracteresIngresadosUsuario=0, nrosEncontrados=0, DiferenciaEntreNrosEncontradosYNrosIngresados=0;

    for(int i=0; i<NUM_MAX_CARACT_DNI;i++)//Ciclo para ver cuantos nros hay
    {
        if(cliente[cont].documentoCliente[i]>='0' && cliente[cont].documentoCliente[i]<='9')
        {
            //printf("Se encontro un NRO\n");
            banderaNro=(banderaNro+1);
        }
    }
    caracteresIngresadosUsuario=(strlen(cliente[cont].documentoCliente));
    nrosEncontrados=banderaNro;
    DiferenciaEntreNrosEncontradosYNrosIngresados=(caracteresIngresadosUsuario-nrosEncontrados);
    if(strlen(cliente[cont].documentoCliente)>=NUM_MIN_CARACT_DNI && strlen(cliente[cont].documentoCliente)==NUM_MAX_CARACT_DNI)//Es funcion me devuelve la cant de caracteres sin contar el null
    {
        if(caracteresIngresadosUsuario==nrosEncontrados)
        {
            //printf("El DNI es valido");
            banderaDni=1;
        }else
        {
            printf("Usted ingreso %d caracteres que no son numeros\nIntentelo nuevamente\n", DiferenciaEntreNrosEncontradosYNrosIngresados);
        }
    }else if(strlen(cliente[cont].documentoCliente)<NUM_MIN_CARACT_DNI)
    {
        DiferenciaEntreNrosEncontradosYNrosIngresados=(NUM_MIN_CARACT_DNI-caracteresIngresadosUsuario);
        printf("El documento que usted ingreso le faltan %d caracteres.\nIngreselo nuevamente\n",DiferenciaEntreNrosEncontradosYNrosIngresados );
    }else if(strlen(cliente[cont].documentoCliente)>NUM_MAX_CARACT_DNI)
    {
        printf("El documento que usted ingreso le sobran %d caracteres.\nIngreselo nuevamente\n",DiferenciaEntreNrosEncontradosYNrosIngresados);
    }
    return banderaDni;
}
int verificarPasaporte(registroPersona_t cliente[MAX_CLIENTES],int cont) 
{
    int banderaPasaporte=0,banderaLetra=0, banderNro=0;
    if(strlen(cliente[cont].documentoCliente)==MAX_CARACT_PASAPORTE)
    {
        for(int i=0; i<MAX_LETRAS_PASAPORTE;i++)//Verificos que haya 3 letras
        {
            if((cliente[cont].documentoCliente[i]>='A'&& cliente[cont].documentoCliente[i]<='Z' )||
               (cliente[cont].documentoCliente[i]>='a'&& cliente[cont].documentoCliente[i]<='z'))
            {
                banderaLetra=(banderaLetra+1);
                //printf("Se encontro LETRA\n");
            }   
        }
        for(int p=MAX_LETRAS_PASAPORTE; p<MAX_CARACT_PASAPORTE;p++)//Verificos que haya 4 nros
        {
            if(cliente[cont].documentoCliente[p]>='0'&& cliente[cont].documentoCliente[p]<='9')
            {
                banderNro=(banderNro+1);
                //printf("Se encontro NRO\n");
            }
        }
        if(banderaLetra==3 && banderNro==4)
        {
            //printf("El pasaporte es valido\n");
            banderaPasaporte=1;
        }else if(banderaLetra<3)
        {
            printf("Le falto ingresar letras\n");
        }else if(banderNro<4)
        {
            printf("Le falto ingresar nros\n");
        }
        
    }else{
        printf("El pasaporte que ingresaste no tiene 7 digitos\nIntentelo nuevamente");
    }
    return banderaPasaporte;
}
int verificarClaveMobile(registroPersona_t cliente[], int cont)
{
    int banderaMayuscula=0, banderaCaracterEspecial=0, banderaCaracterArroba=0, banderaMinuscula=0,banderaNro=0;
    int banderaClaveMobile=0, caracteresIngresadosUsuario=0, caracteresFaltantes=0;
    if(strlen(cliente[cont].contraseniasUsuario.claveMobile)<MIN_CARACT_CLAVE_MOBILE_MAIL)
    {
        caracteresIngresadosUsuario=(strlen(cliente[cont].contraseniasUsuario.claveMobile));
        caracteresFaltantes=(MIN_CARACT_CLAVE_MOBILE_MAIL-caracteresIngresadosUsuario);
        printf("La contrasenia es corta, le faltan %d caracteres.\n Intentelo nuevamente", caracteresFaltantes);
    }else
    {
        for(int i=0; i<MAX_CARACT;i++)
        {
            if(cliente[cont].contraseniasUsuario.claveMobile[i] =='@')
            {
                banderaCaracterArroba=1;
                //printf("SE ENCONTRO UN ARROBA\n");
            }else if(cliente[cont].contraseniasUsuario.claveMobile[i]>='A' && cliente[cont].contraseniasUsuario.claveMobile[i]<='Z')
            {
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(cliente[cont].contraseniasUsuario.claveMobile[i]>='a' && cliente[cont].contraseniasUsuario.claveMobile[i]<='z')
            {
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(cliente[cont].contraseniasUsuario.claveMobile[i]=='.' || cliente[cont].contraseniasUsuario.claveMobile[i]=='_' || cliente[cont].mail[i]=='-')
            {
                //printf("SE ENCONTRO UN CARAC_ESPECIALES\n");
                banderaCaracterEspecial=1;
            }else if(cliente[cont].contraseniasUsuario.claveMobile[i]>='0' && cliente[cont].contraseniasUsuario.claveMobile[i]<='9')
            {
                banderaNro=1;
                //printf("SE ENCONTRO UN NRO\n");
            }
        }
        if(banderaCaracterArroba==1 && banderaMayuscula>=1 && banderaCaracterEspecial>=1 && banderaMinuscula>=1 && banderaNro>=1)
        {
            banderaClaveMobile=1;
            //printf("La ClaveMobile es valida\n");
        }else
        {
            printf("Usted no cumple con las siguientes condiciones:\n");
            mensajeFaltanCondiones(banderaCaracterArroba, banderaMayuscula, banderaCaracterEspecial, banderaMinuscula,  banderaNro);
        }
    }
    return banderaClaveMobile;
}
void barraSeparadora(void)
{
    printf("--------------------------------------------------------------------------\n");
}
void mensajeFaltanCondiones(int banderaCaracterArroba, int banderaMayuscula, int banderaCaracterEspecial, int banderaMinuscula, int banderaNro)
{
    if(banderaCaracterArroba==0)
    {
        printf("@\n");
    }
    if(banderaMayuscula==0)
    {
        printf("Le falta escribir al menos una mayuscula\n");
    }
    if(banderaCaracterEspecial==0)
    {
        printf("Le falta escribir al menos un caracter especial\n");
    }
    if(banderaMinuscula==0)
    {
        printf("Le falta escribir al menos una minuscula\n");
    }
    if(banderaNro==0)
    {
        printf("Le falta escribir al menos un numero\n");
    }
}
int verificarCelular(registroPersona_t cliente[], int cont)
{
    int banderaValidaCelular=0, aux=0, aux2=0;
    if(cliente[cont].celular>MIN_NRO_CELULAR && cliente[cont].celular<MAX_NRO_CELULAR)
    {
        //printf("El nro de celular es valido\n");
        banderaValidaCelular=1;
    }else
    {
        //aux=strlen(cliente[cont].celular);
        //aux2= DIGITOS_CELULAR-aux;
        if(cliente[cont].celular<MIN_NRO_CELULAR)
        {
            printf("El nro de celular que usted ingreso le faltan %d caracteres\nIntentenlo nuevamente:\n", aux2);
        }else
        {
            printf("El nro de celular que usted ingreso le sobran %d caracteres\nIntentenlo nuevamente:\n", aux2);
        }
    }
    return banderaValidaCelular;
}
void mensajeParaUsuarioAdvertencias(void){
    printf("Debe tener al menos:\n8 caracteres en ellos se deben encontrar:\n");
    printf("1 caracter especial, estos pueden ser: . - _ \n1 minuscula\n1 arroba\n");
}
int verificarMail(registroPersona_t cliente[], int cont)
{
    int banderaCaracterEspecial=0, banderaCaracterArroba=0, banderaMinuscula=0;
    int banderaMail=0, aux, aux2;
    int banderaMayuscula=1, banderaNro=1;//ESTAS 2 LAS INICIALIZO XQ NO OBLIGATORIAS EN EL MAIL
    //PORQUE SINO NO PODRIA REUTILIZAR LA FUNCION
    if(strlen(cliente[cont].mail)<MIN_CARACT_CLAVE_MOBILE_MAIL)
    {
        aux=strlen(cliente[cont].mail);
        aux2=MIN_CARACT_CLAVE_MOBILE_MAIL-aux;
       printf("Usted ingreso un mail de %d caracter.\n Le faltan %d caracteres.\nEl minimo son 3 caracteres \nIntentelo nuevamente\n", aux, aux2);  
    }else
    {
        for(int i=0; i<MAX_CARACT;i++)
        {
            if(cliente[cont].mail[i] =='@')
            {
                banderaCaracterArroba=1;
                //printf("SE ENCONTRO UN ARROBA\n");
            }else if(cliente[cont].mail[i]>='A' && cliente[cont].mail[i]<='Z')
            {
                banderaMayuscula=1+banderaMayuscula;
                //printf("SE ENCONTRO UN CARAC_MAYUSCULAS\n");
            }else if(cliente[cont].mail[i]>='a' && cliente[cont].mail[i]<='z')
            {
                banderaMinuscula=1+banderaMinuscula;
                //printf("SE ENCONTRO UN CARAC_MINUSCULA\n");
            }else if(cliente[cont].mail[i]=='-' || cliente[cont].mail[i]=='_' || cliente[cont].mail[i]=='.')
            {
                //printf("SE ENCONTRO UN CARAC_ESPECIALES\n");
                banderaCaracterEspecial=1;
            }
        }
        if(banderaCaracterArroba==1 && banderaCaracterEspecial>=1 && banderaMinuscula>=1)
        {
            banderaMail=1;
            //printf("El mail es valido\n");
        }else
        {
            printf("El mail que ingreso no es valido:\n");
            mensajeFaltanCondiones(banderaCaracterArroba, banderaMayuscula, banderaCaracterEspecial, banderaMinuscula,  banderaNro);
        }
    }
    return banderaMail;

}
void cargarContrasenias(registroPersona_t cliente[], int cont)
{
    cliente[cont].contraseniasUsuario.claveCajero=(rand()%(NUM_MAX_CLAVES_CAJERO_TELEFONICA-NUM_MIN_CLAVES_CAJERO_TELEFONICA+1)+NUM_MIN_CLAVES_CAJERO_TELEFONICA);//PARA QUE ME GENERE UN NUM ALAZAR
    //printf("contraseniasUsuario.claveCajero: %d\n",clientes[cont].contraseniasUsuario.claveCajero);
    cliente[cont].contraseniasUsuario.claveTelefonica=(rand()%(NUM_MAX_CLAVES_CAJERO_TELEFONICA-NUM_MIN_CLAVES_CAJERO_TELEFONICA+1)+NUM_MIN_CLAVES_CAJERO_TELEFONICA);//PARA QUE ME GENERE UN NUM ALAZAR
    //printf("contraseniasUsuario.claveTelefonica: %d\n",clientes[cont].contraseniasUsuario.claveTelefonica);
}
void cargarCBU(registroPersona_t cliente[], int cont)
{
    //srand(time(NULL));
    for(int j=0; j<MAX_CARACT_CBU; j++)
    {
        cliente[cont].cbu[j]=(rand()%(NUM_MAX_DIGITO_CBU_DNI - NUM_MIN_DIGITO_CBU_DNI+1)+NUM_MIN_DIGITO_CBU_DNI)+'0';//Le sumo cero xq sino me reconoce los digitos como nros sino que me lo pasa a ascii
        //printf("%c\n", cliente[cont].cbu[j]);
    }
    cliente[cont].cbu[MAX_CARACT_CBU]='\0';//Esto es porque sino me imprime basura al final del cbu
}
void mostrarMensajeDeLasCiudades(void)
{
    printf("Ingrese en la ciudad en la que vive. Siendo:\n");
    char ciudadesAmba[MAX_CIUDADES_AMBA][30] = {"Avellaneda", "Berazategui", "CABA","Campana", "Canuelas",
    "Ensenada", "Escobar","Ezeiza", "FlorencioVarela", "GralRodriguez", "GralSanMartin", "Hurlingham",
    "Ituzaingo", "JoseCPaz", "LaMatanza", "Lanus", "LomasDeZamora","Lujan","MalvinasArgentinas",
    "MarcosPaz", "Merlo", "Moreno", "Moron", "Quilmes","Pilar","SanFernando","SanIsidro",
    "SanMiguel", "SanVicente", "Tigre", "VicenteLopez", "Zarate"};
    for(int i=0; i<MAX_CIUDADES_AMBA; i++)
    {
        printf("[%d]  %s\n",i, ciudadesAmba[i]);
    }
}
void ciudadesEnBsAs(registroPersona_t cliente[MAX_CLIENTES], int cont)
{
    int aux=0, banderaCiudades=0;
    do
    {
        scanf("%d", &aux);
        if(aux>=0 && aux<MAX_CIUDADES_AMBA)
        {
            cliente[cont].domicilioCliente.ciudadesBsAs=aux;
            banderaCiudades=1;
        }else if(aux<0)
        {
            printf("La opcion que usted ingreso es un nro negativo y esta fuera del rango.\n El nro que ingrese debe ser del 0 hasta el 31\nIntentelo nuevamente:");
        }else{
            printf("La opcion que usted ingreso es mayor que 31.\n El nro que ingrese debe ser del 0 hasta el 31\nIntentelo nuevamente:");
        }
    }while(banderaCiudades==0);
}
void tiposDeDocumento(registroPersona_t cliente[MAX_CLIENTES], tipoDocumentoPersona_t opcionDocumento, int cont)
{
   switch(opcionDocumento)
    {
        case DNI:
            printf("\nIngrese su numero de DNI:\n");
            scanf("%s", cliente[cont].documentoCliente);
        break;

       case PASAPORTE:
            printf("\nIngrese los caracteres de su Pasaporte:\n");
            scanf("%s", cliente[cont].documentoCliente);
            break;
        default:
            printf("\nOpcion no valida");
    }
}
void alias(int cont,registroPersona_t cliente[])
{//Esta funcion crea un alias con palabras azar
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
    strcpy(cliente[cont].alias,auxAlias);
    printf("Su alias es: %s\n", cliente[cont].alias);

}
void mostrarDatosDelRegistro(registroPersona_t cliente[MAX_CLIENTES])
{
    for(int i=0; i<MAX_CLIENTES; i++)
    {
        printf("Datos del cliente nro %d \n", i+1);
        printf("Nombre:  %s \n", cliente[i].nombres);
        printf("Apellido: %s \n", cliente[i].apellido);
        printf("Tipo de documento: %s \n", cliente[i].documentoCliente);
        printf("Provincia: %u \n", cliente[i].domicilioCliente.ciudadesBsAs);
        printf("Calle de su domicilio: %s", cliente[i].domicilioCliente.calle);
        printf("Nro: %hu \n", cliente[i].domicilioCliente.numero);
        printf("Mail: %s \n", cliente[i].mail);
        printf("Celular: %lu \n", cliente[i].celular);
        printf("\n");
    }
}
