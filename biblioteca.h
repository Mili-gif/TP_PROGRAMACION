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
int verificarNombreApellido(char[],int);
int verificarCalleDomicilio(registroPersona_t[], int);
int verificaAlturaDomicilio(registroPersona_t[], int);
int verificarProvincia(registroPersona_t[], int);
int verificarDNI(registroPersona_t[],int );
int verificarPasaporte(registroPersona_t[],int);
int verificarMail(registroPersona_t[], int);
int verificarCelular(registroPersona_t[], int);
void alias(int, registroPersona_t[]);
