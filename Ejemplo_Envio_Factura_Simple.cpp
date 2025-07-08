/**
EJEMPLO DE INTEGRACIÓN PARA GENERAR FACTURA SIMPLE - C++

OBJETIVO: Ejemplificar el proceso de conexión, acceso y uso de las propiedades y métodos ofrecidos por la
		  libreria tfhkaif a través del lenguaje de programación C ++ de la plataforma .Net
____________________________________________________________________________________________________________________________
FORMA DE TRABAJO SUGERIDA
.........................................................................................................................
* PASO 1
.........................................................................................................................
	 AGREGAR REFERENCIA AL ARCHIVO DE ENCABEZADO "Tfhkaif.h"

	   * EXPLICACIÓN:

		 1.- En el código fuente de su archivo .cpp principal agregue la referencia al archivo de encabezado "Tfhkaif.h",
			 a través de la directiva #include, de la siguiente manera: #include "Tfhkaif.h".
		 2.- El archivo de encabezado "Tfhkaif.h", contiene la definición de la clase  "Tfhkaif", a través de la cual, una vez,
			 instanciada, es posible acceder a los métodos públicos de la librería "tfhkaif.dll".

			 IMPORTANTE:
			 -----------------------------------------------------------------------------------------------------------------
			  La directiva #include inserta una copia del archivo de encabezado directamente en el archivo .cpp antes de la
			  compilación.
			 -----------------------------------------------------------------------------------------------------------------
.........................................................................................................................
* PASO 2
.........................................................................................................................
	 DEFINIR LA INFORMACIÓN A UTILIZAR EN EL PROCESO

	   * EXPLICACIÓN:

		 1.- En su código fuente defina las variables de tipo LPCSTR donde almacenar y asígneles la información correspondiente.
		 2.- Cualquier información adicional consulte el MANUAL DE PROTOCOLOS Y COMANDOS. El cual debe solicitar departamento de
			 integracion y soporte.

.........................................................................................................................
* PASO 3
.........................................................................................................................
	 INSTANCIAR LA CLASE "Tfhkaif" Y VERIFICAR SI SE ENCUENTRAN DISPONIBLES LOS MÉTODOS DE LA LIBRERÍA

	   * EXPLICACIÓN:

		 1.- En su código fuente cree un objeto de tipo "Tfhkaif", la cual se encuentra definida en el archivo de encabezado "Tfhkaif.h",
			 incluido en el paso 1.
		 2.- Verificar si los métodos de la librería están disponibles a través de la clase instanciada.

.........................................................................................................................
* PASO 4
.........................................................................................................................
	  UTILIZAR LOS MÉTODOS Y ATRIBUTOS QUE OFRECE LA LIBRERÍA "tfhkaif" Y MANEJAR LA RESPUESTA

	   * EXPLICACIÓN:

		 1.- En su código fuente defina las Clases, variables, funciones y objetos que se requieran para utilizar
			 directamente los métodos y atributos que la libreria Tfhkaif pone a su disposición.
			 Dichos objetos pueden ser accedidos a través del objeto de tipo "Tfhka" creado en el paso 3.

			 Estructura de funciones:

				<tipo de retorno> <Nombre de la función> ([parámetro 1, [parámetro 2]...])

				tipo de retorno:        Tipo de valor que devolverá la función al ser invocada, puede ser int, bool, string, double, etc.,
										o bien "void" si no regresará nada.

				Nombre de la función:   Identificador o nombre que se le da a la función.

				parámetro:              Datos de entrada con los que trabajará la función, puede no llevar.

			 Actualmente, la libreria tfhkaif ofrece los métodos que se describen y detallan a continuación:

			 * Método OpenFpctrl():
			   --------------------------------------------------------------------------------------------------------
			   Permite realizar la apertura del puerto de comunicaciones por el cual se establecerá comunicación
			   con la impresora. Este método se ejecuta en el constructor único de la clase, pero puede ser
			   ejecutado nuevamente de ser requerido, tal y como se muestra a continuación:

			   BOOLEAN OpenFpctrl(String IpPortName)

			   --------------------------------------------------------------------------------------------------------
				* Método CloseFpCtrl():
			   --------------------------------------------------------------------------------------------------------
			   Permite cerrar del puerto COM asociado, abierto anteriormente, pero puede ser
			   ejecutado nuevamente de ser requerido, tal y como se muestra a continuación:

			   VOID CloseFpctrl()

			   --------------------------------------------------------------------------------------------------------
			 * Método SendCmd():
			   --------------------------------------------------------------------------------------------------------
			   Permite realizar el envío de comandos hacia la impresora, en forma de tramas de caracteres
			   ASCII, tal como es descrito en los manuales de integración de las respectivas impresoras, y en
			   el manual general de protocolos y comandos del protocolo TFHKA, tal y como se muestra a continuación:

			   BOOL SendCmd(String Cmd)

			   --------------------------------------------------------------------------------------------------------
**/

/**
###################################  EJEMPLO DE PROGRAMA C++ QUE USA LA LIBRERIA tfhkaif ###################################

 A continuación se presenta el código de ejemplo de una aplicación C++ de cónsola que utiliza directamente los objetos
									(Clases, atributos y métodos) que ofrece la libreria.

###########################################################################################################################
**/

#include <iostream>

/** PASO 1:  AGREGAR REFERENCIA AL ARCHIVO DE ENCABEZADO "Tfhkaif.h" **/

#include "Tfhkaif.h"

using namespace std;

//Declaración de Variables globales
string pu;									 // Variable para capturar la entrada de datos desde el teclado, para el puerto
const char* puerto = NULL;					// Variable para almacenar la información del puerto capturada desde teclado en la variable pu
bool PORTOPEN = false;					   // Variable de control booleana para supervisión del puerto
bool BRESP = false;						  // Variable de control booleana para supervisión respuesta de comando

int main() 
{
	cout << "\t*** EJEMPLO DE INTEGRACION C++ - FACTURA SIMPLE ***" << endl;

	/** PASO 2: DEFINIR LA INFORMACIÓN A UTILIZAR EN EL PROCESO **/

	LPCSTR COMMAND_FLAG50 = "PJ5000";                          //Comando para establecer el Flag 50 en 00
	LPCSTR COMMAND_FLAG21 = "PJ2100";                          //Comando para establecer el Flag 21 en 00
	LPCSTR RIF = "iR*J-312171197";                             //Información del Registro de Identficación Fiscal
	LPCSTR SOCIAL_REASON = "iS*THE FACTORY HKA, C.A.";         //Información de Razón Social
	LPCSTR ADDRESS_LINE1 = "i00DIRECCION: LA CALIFORNIA";      //Información de Dirección linea 1
	LPCSTR ADDRESS_LINE2 = "i01CARACAS";                       //Información de Dirección linea 2
	LPCSTR PLU1 = " 000000001000001000Producto1";              //Información  de PLU: Tasa Exento  , cantidad 1, monto 0.10 bs, nombre del PLU
	LPCSTR PLU2 = "!000000001000001000Producto2";              //Información  de PLU: Tasa General , cantidad 1, monto 0.10 bs, nombre del PLU
	LPCSTR PLU3 = "\"000000001000001000Producto3";             //Información  de PLU: Tasa Reducida, cantidad 1, monto 0.10 bs, nombre del PLU
	LPCSTR PLU4 = "#000000001000001000Producto4";              //Información  de PLU: Tasa Ampliada, cantidad 1, monto 0.10 bs, nombre del PLU
	LPCSTR PLU5 = "$000000001000001000Producto5";              //Información  de PLU: Tasa Percibida, cantidad 1, monto 0.10 bs, nombre del PLU
	LPCSTR COMMAND_SUBTOTAL = "3";                             //Comando de subtotal de factura
	LPCSTR COMMAND_PAGOTOTAL = "101";                          //comando de Totalizar  Factura
	LPCSTR COMMAND_COMMENT = "@EJEMPLO DE FACTURA";            //Comando envio para Introducir un comentario

	/**PASO 3: INSTANCIAR LA CLASE "Tfhkaif" Y VERIFICAR SI SE ENCUENTRAN DISPONIBLES LOS MÉTODOS DE LA LIBRERÍA **/
	
	try
	{
		Tfhkaif dllTfhkaif = Tfhkaif();

		/** para verificar si están disponibles los métodos de la librería a través e la clase, validamos una función que retorne un tipo booleano
		tal como "OpenFpctrl" **/

		if (!dllTfhkaif.OpenFpctrl) {
			cout << "\tNo ha sido posible acceder a las funciones de la librer\241a...\n\n";
			system("pause");
		}
		else
		{
			/** PASO 4: UTILIZAR LOS MÉTODOS Y ATRIBUTOS QUE OFRECE LA LIBRERÍA "tfhkaif" Y MANEJAR LA RESPUESTA **/

			cout << "\n\tIndique el Puerto por el cual va a conectarse: "; cin >> pu; cout << endl;

			puerto = pu.c_str();
			PORTOPEN = dllTfhkaif.OpenFpctrl((LPCSTR)puerto);

			if (PORTOPEN)    // Verificación de puerto abierto (Establece si podemos establecer comunicación con la impresora
			{
				cout << "\tPUERTO '" << puerto << "' ABIERTO !!!" << endl;

				cout << "\n\tSe procede con el env\241o de la secuencia de comandos para generar un factura simple,\n\tsin configuraci\242n de IGTF:\n" << endl;

				/** debe asegurarse que el Flag 21 tenga el valor de 00 sino debe cambiarlo  **/
				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, COMMAND_FLAG21);

				/** debe asegurarse que el Flag 50 tenga el valor de 00 sino debe cambiarlo  **/
				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, COMMAND_FLAG50);

				!BRESP ? cout << "\t!!! Comando No Aceptado: " << COMMAND_FLAG50 << endl : cout << "\t*** Comando Enviado: " << COMMAND_FLAG50 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, SOCIAL_REASON);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << SOCIAL_REASON << endl : cout << "\t*** Comando Enviado: " << SOCIAL_REASON << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, RIF);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << RIF << endl : cout << "\t*** Comando Enviado: " << RIF << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, ADDRESS_LINE1);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << ADDRESS_LINE1 << endl : cout << "\t*** Comando Enviado: " << ADDRESS_LINE1 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, ADDRESS_LINE2);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << ADDRESS_LINE2 << endl : cout << "\t*** Comando Enviado: " << ADDRESS_LINE2 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, COMMAND_COMMENT);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << COMMAND_COMMENT << endl : cout << "\t*** Comando Enviado: " << COMMAND_COMMENT << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, PLU1);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << PLU1 << endl : cout << "\t*** Comando Enviado: " << PLU1 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, PLU2);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << PLU2 << endl : cout << "\t*** Comando Enviado: " << PLU2 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, PLU3);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << PLU3 << endl : cout << "\t*** Comando Enviado: " << PLU3 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, PLU4);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << PLU4 << endl : cout << "\t*** Comando Enviado: " << PLU4 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, PLU5);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << PLU5 << endl : cout << "\t*** Comando Enviado: " << PLU5 << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, COMMAND_COMMENT);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << COMMAND_COMMENT << endl : cout << "\t*** Comando Enviado: " << COMMAND_COMMENT << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, COMMAND_SUBTOTAL);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << COMMAND_SUBTOTAL << endl : cout << "\t*** Comando Enviado: " << COMMAND_SUBTOTAL << endl;

				BRESP = dllTfhkaif.SendCmd(dllTfhkaif.status, dllTfhkaif.error, COMMAND_PAGOTOTAL);
				!BRESP ? cout << "\t!!! Comando No Aceptado: " << COMMAND_PAGOTOTAL << endl : cout << "\t*** Comando Enviado: " << COMMAND_PAGOTOTAL << endl;

				dllTfhkaif.CloseFpctrl();

				cout << "\n\tLa Ejecuci\242n del ejemplo ha finalizado !!!" << endl << endl;

				system("pause");
			}
			else
			{
				cout << "\tPUERTO: '" << puerto << "' NO ACCESIBLE.\n" << endl;
				cout << "\tNO SE PUDO ESTABLECER COMUNICACION CON LA IMPRESORA..." << endl << endl;
				system("pause");
			}
		}
	}
	catch (const std::exception& ex)
	{
		cout << "\tOCURRIO UNA EXCEPCION:\n\t Detalles del Error: \n\t" << ex.what();
		system("pause");
	}

	return 0;
}