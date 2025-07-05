/**
EJEMPLO DE INTEGRACIÓN PARA OBTENER LA INFORMACION DE UNA IMPRESORA FISCAL - C++

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

		 1.- En su código fuente defina las variables de tipo LPCSTR necesarias para la extracción de la información.
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
			  * Método GetPrinterStatus():
               --------------------------------------------------------------------------------------------------------
               Obtiene un reporte del Status y Error de la impresora en un objeto del tipo PrinterStatus que
               contiene el código y una descripción tanto para el Status como para el Error actual.
               tal como es descrito en los manuales de integración de las respectivas impresoras, y en
               el manual general de protocolos y comandos del protocolo TFHKA, tal y como se muestra a continuación:
                                           
               PrinterStatus GetPrinterStatus()

               --------------------------------------------------------------------------------------------------------
              * Método GetSVPrinterData():
               --------------------------------------------------------------------------------------------------------
               Obtiene el estado SV (información del modelo y país de la impresora).
               tal como es descrito en los manuales de integración de las respectivas impresoras, y en
               el manual general de protocolos y comandos del protocolo TFHKA, tal y como se muestra a continuación:
                                           
               SVPrinterData GetSVPrinterData() throws PrinterException

               Excepción Arroja la excepción PrinterException

               --------------------------------------------------------------------------------------------------------
             * Método GetS1PrinterData():
               --------------------------------------------------------------------------------------------------------
               Sube al PC el estado S1 (información de parámetros generales de la impresora).
               tal como es descrito en los manuales de integración de las respectivas impresoras, y en
               el manual general de protocolos y comandos del protocolo TFHKA, tal y como se muestra a continuación:
                                           
               S1PrinterData GetS1PrinterData() throws PrinterException

               --------------------------------------------------------------------------------------------------------
             * PRINTEREXCEPTION
               --------------------------------------------------------------------------------------------------------
               Representa un tipo de excepción que arrojan algunos métodos de creación de objetos de las
               estructuras anteriormente definidas cuando ocurre un error en la transacción con la impresora
               fiscal. Está compuesto por los siguientes elementos:

                    ● PrinterStatus StatusError: Retorna un objeto que contiene información del Status y el Error
                        al momento de generarse la excepción.
                    ● Message: Contiene la descripción de la excepción arrojada

			   --------------------------------------------------------------------------------------------------------
**/

/**
###################################  EJEMPLO DE PROGRAMA C++ QUE USA LA LIBRERIA tfhkaif ###################################

 A continuación se presenta el código de ejemplo de una aplicación C++ de cónsola que utiliza directamente los objetos
									(Clases, atributos y métodos) que ofrece la libreria.

###########################################################################################################################
**/

#include <iostream>
#include <fstream>
#include <string>

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
	cout << "\t*** EJEMPLO DE INTEGRACION C++ - OBTENER LA INFORMACION DE UNA IMPRESORA FISCAL ***" << endl;

	/** PASO 2: DEFINIR LA INFORMACIÓN A UTILIZAR EN EL PROCESO **/

		string nombreArchivos1 = "s1_response.txt";
		string nombreArchivos2 = "s2_response.txt";
		string nombreArchivos2E = "s2E_response.txt";
		string nombreArchivos21 = "s21_response.txt";
		string nombreArchivos22 = "s22_response.txt";
		string nombreArchivos23 = "s23_response.txt";
		string nombreArchivos24 = "s24_response.txt";
		string nombreArchivos3 = "s3_response.txt";
		string nombreArchivos4 = "s4_response.txt";
		string nombreArchivos5 = "s5_response.txt";
		string nombreArchivosv = "sv_response.txt";
		string nombreArchivosU0X = "U0X_response.txt";
		string nombreArchivosU0Z = "U0Z_response.txt";
		string linea;

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

			/*cout << "\n\tIndique el Puerto por el cual va a conectarse: "; cin >> pu; cout << endl;*/

			puerto = pu.c_str();
			
			PORTOPEN = dllTfhkaif.OpenFpctrl((LPCSTR)puerto);

			if (PORTOPEN)    // Verificación de puerto abierto (Establece si podemos establecer comunicación con la impresora
			{
				cout << "\tPUERTO '" << puerto << "' ABIERTO !!!" << endl;

				Sleep(5000);

				/*cout << "\n\tSe procede con el env\241o de la secuencia de comandos para extraer\n\tparte de la informaci\242n de la impresora:\n" << endl;*/

				/** debe asegurarse que el Flag 50 tenga el valor de 00 sino debe cambiarlo  **/
				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S1",  (LPCSTR)nombreArchivos1.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S1" << endl : cout << "\t*** Comando Enviado: " << "S1" << endl;
				//
				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S1 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;
				//
				//ifstream archivos1(nombreArchivos1.c_str());
				//
				///*Obtener línea de archivo, y almacenar contenido en "linea"*/
				//while (getline(archivos1, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* N\243mero de Cajero asignado: " << linea.substr(2, 2) << endl;
				//	cout << "\t\t* Total de ventas diarias: " << linea.substr(4, 17) << endl;
				//	cout << "\t\t* N\243mero de la \243ltima factura: " << linea.substr(21, 8) << endl;
				//	cout << "\t\t* Cantidad de facturas emitidas en el d\241a: " << linea.substr(29, 5) << endl;
				//	cout << "\t\t* N\243mero de la \243ltima nota de d\202bito: " << linea.substr(34, 8) << endl;
				//	cout << "\t\t* Cantidad de notas de d\202bito emitidas en el d\241a: " << linea.substr(42, 5) << endl;
				//	cout << "\t\t* N\243mero de la \243ltima nota de cr\202dito: " << linea.substr(47, 8) << endl;
				//	cout << "\t\t* Cantidad de notas de cr\202dito emitidas en el d\241a: " << linea.substr(55, 5) << endl;
				//	cout << "\t\t* N\243mero del \243ltimo documento no fiscal: " << linea.substr(60, 8) << endl;
				//	cout << "\t\t* Cantidad de documentos no fiscales emitidos en el d\241a: " << linea.substr(68, 5) << endl;
				//	cout << "\t\t* Contador de reportes de Memoria Fiscal: " << linea.substr(73, 4) << endl;
				//	cout << "\t\t* Contador de cierres diarios Z: " << linea.substr(77, 4) << endl;
				//	cout << "\t\t* RIF: " << linea.substr(81, 11) << endl;
				//	cout << "\t\t* N\243mero de Registro de la M\240quina: " << linea.substr(92, 10) << endl;
				//	cout << "\t\t* Hora actual de la impresora (HHMMSS): " << linea.substr(102, 6) << endl;
				//	cout << "\t\t* Fecha actual de la impresora (DDMMAA): " << linea.substr(108, 6) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S2", (LPCSTR)nombreArchivos2.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S2" << endl : cout << "\t*** Comando Enviado: " << "S2" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S2 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos2(nombreArchivos2.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos2, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Subtotal Base Imponibles: " << linea.substr(2, 14) << endl;
				//	cout << "\t\t* Subtotal de Impuesto: " << linea.substr(16, 14) << endl;
				//	cout << "\t\t* Valor tasa IGTF: " << linea.substr(30, 14) << endl;
				//	cout << "\t\t* Cantidad de Art\241culos: " << linea.substr(44, 6) << endl;
				//	cout << "\t\t* Monto a pagar: " << linea.substr(50, 14) << endl;
				//	cout << "\t\t* Cantidad de pagos realizados: " << linea.substr(64, 4) << endl;
				//	cout << "\t\t* Tipo de documento: " << linea.substr(68, 1) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S2E", (LPCSTR)nombreArchivos2E.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S2E" << endl : cout << "\t*** Comando Enviado: " << "S2E" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S2E DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos2E(nombreArchivos2E.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos2E, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Subtotal de exento: " << linea.substr(2, 14) << endl;
				//	cout << "\t\t* Subtotal de Impuesto: " << linea.substr(16, 14) << endl;
				//	cout << "\t\t* Valor tasa IGTF: " << linea.substr(30, 14) << endl;
				//	cout << "\t\t* Cantidad de Art\241culos: " << linea.substr(44, 6) << endl;
				//	cout << "\t\t* Monto a pagar: " << linea.substr(50, 14) << endl;
				//	cout << "\t\t* Cantidad de pagos realizados: " << linea.substr(64, 4) << endl;
				//	cout << "\t\t* Tipo de documento: " << linea.substr(68, 1) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S21", (LPCSTR)nombreArchivos21.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S21" << endl : cout << "\t*** Comando Enviado: " << "S21" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S21 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos21(nombreArchivos21.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos21, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Subtotal de base imponible tasa 1: " << linea.substr(2, 14) << endl;
				//	cout << "\t\t* Subtotal de impuesto Tasa 1: " << linea.substr(16, 14) << endl;
				//	cout << "\t\t* Valor tasa IGTF: " << linea.substr(30, 14) << endl;
				//	cout << "\t\t* Cantidad de Art\241culos: " << linea.substr(44, 6) << endl;
				//	cout << "\t\t* Monto a pagar: " << linea.substr(50, 14) << endl;
				//	cout << "\t\t* Cantidad de pagos realizados: " << linea.substr(64, 4) << endl;
				//	cout << "\t\t* Tipo de documento: " << linea.substr(68, 1) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S22", (LPCSTR)nombreArchivos22.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S22" << endl : cout << "\t*** Comando Enviado: " << "S22" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S22 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos22(nombreArchivos22.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos22, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Subtotal de base imponible tasa 2: " << linea.substr(2, 14) << endl;
				//	cout << "\t\t* Subtotal de impuesto Tasa 2: " << linea.substr(16, 14) << endl;
				//	cout << "\t\t* Valor tasa IGTF: " << linea.substr(30, 14) << endl;
				//	cout << "\t\t* Cantidad de Art\241culos: " << linea.substr(44, 6) << endl;
				//	cout << "\t\t* Monto a pagar: " << linea.substr(50, 14) << endl;
				//	cout << "\t\t* Cantidad de pagos realizados: " << linea.substr(64, 4) << endl;
				//	cout << "\t\t* Tipo de documento: " << linea.substr(68, 1) << endl;
				//}

				//Sleep(5000);
			
				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S23", (LPCSTR)nombreArchivos23.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S23" << endl : cout << "\t*** Comando Enviado: " << "S23" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S23 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos23(nombreArchivos23.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos23, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Subtotal de base imponible tasa 3: " << linea.substr(2, 14) << endl;
				//	cout << "\t\t* Subtotal de impuesto Tasa 3: " << linea.substr(16, 14) << endl;
				//	cout << "\t\t* Valor tasa IGTF: " << linea.substr(30, 14) << endl;
				//	cout << "\t\t* Cantidad de Art\241culos: " << linea.substr(44, 6) << endl;
				//	cout << "\t\t* Monto a pagar: " << linea.substr(50, 14) << endl;
				//	cout << "\t\t* Cantidad de pagos realizados: " << linea.substr(64, 4) << endl;
				//	cout << "\t\t* Tipo de documento: " << linea.substr(68, 1) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S24", (LPCSTR)nombreArchivos24.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S24" << endl : cout << "\t*** Comando Enviado: " << "S24" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S24 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos24(nombreArchivos24.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos24, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Subtotal de base imponible tasa 4: " << linea.substr(2, 14) << endl;
				//	cout << "\t\t* Subtotal de impuesto Tasa 4: " << linea.substr(16, 14) << endl;
				//	cout << "\t\t* Valor tasa IGTF: " << linea.substr(30, 14) << endl;
				//	cout << "\t\t* Cantidad de Art\241culos: " << linea.substr(44, 6) << endl;
				//	cout << "\t\t* Monto a pagar: " << linea.substr(50, 14) << endl;
				//	cout << "\t\t* Cantidad de pagos realizados: " << linea.substr(64, 4) << endl;
				//	cout << "\t\t* Tipo de documento: " << linea.substr(68, 1) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S3", (LPCSTR)nombreArchivos3.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S3" << endl : cout << "\t*** Comando Enviado: " << "S3" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S3 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos3(nombreArchivos3.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos3, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Tipo de Tasa 1: " << linea.substr(2, 1) << endl;
				//	cout << "\t\t* Tipo de Tasa 2: " << linea.substr(7, 1) << endl;
				//	cout << "\t\t* Tipo de Tasa 3: " << linea.substr(12, 1) << endl;
				//	cout << "\t\t* Valor de tasa 1: " << linea.substr(3, 4) << endl;
				//	cout << "\t\t* Valor de tasa 2: " << linea.substr(8, 4) << endl;
				//	cout << "\t\t* Valor de tasa 3: " << linea.substr(13, 4) << endl;
				//	cout << "\t\t* Flag 00: " << linea.substr(17, 2) << endl;
				//	cout << "\t\t* Flag 01: " << linea.substr(19, 2) << endl;
				//	cout << "\t\t* Flag 02: " << linea.substr(21, 2) << endl;
				//	cout << "\t\t* Flag 03: " << linea.substr(23, 2) << endl;
				//	cout << "\t\t* Flag 04: " << linea.substr(25, 2) << endl;
				//	cout << "\t\t* Flag 05: " << linea.substr(27, 2) << endl;
				//	cout << "\t\t* Flag 06: " << linea.substr(29, 2) << endl;
				//	cout << "\t\t* Flag 07: " << linea.substr(31, 2) << endl;
				//	cout << "\t\t* Flag 08: " << linea.substr(33, 2) << endl;
				//	cout << "\t\t* Flag 09: " << linea.substr(35, 2) << endl;
				//	cout << "\t\t* Flag 10: " << linea.substr(37, 2) << endl;
				//	cout << "\t\t* Flag 11: " << linea.substr(39, 2) << endl;
				//	cout << "\t\t* Flag 12: " << linea.substr(41, 2) << endl;
				//	cout << "\t\t* Flag 13: " << linea.substr(43, 2) << endl;
				//	cout << "\t\t* Flag 14: " << linea.substr(45, 2) << endl;
				//	cout << "\t\t* Flag 15: " << linea.substr(47, 2) << endl;
				//	cout << "\t\t* Flag 16: " << linea.substr(49, 2) << endl;
				//	cout << "\t\t* Flag 17: " << linea.substr(51, 2) << endl;
				//	cout << "\t\t* Flag 18: " << linea.substr(53, 2) << endl;
				//	cout << "\t\t* Flag 19: " << linea.substr(55, 2) << endl;
				//	cout << "\t\t* Flag 20: " << linea.substr(57, 2) << endl;
				//	cout << "\t\t* Flag 21: " << linea.substr(59, 2) << endl;
				//	cout << "\t\t* Flag 22: " << linea.substr(61, 2) << endl;
				//	cout << "\t\t* Flag 23: " << linea.substr(63, 2) << endl;
				//	cout << "\t\t* Flag 24: " << linea.substr(65, 2) << endl;
				//	cout << "\t\t* Flag 25: " << linea.substr(67, 2) << endl;
				//	cout << "\t\t* Flag 26: " << linea.substr(69, 2) << endl;
				//	cout << "\t\t* Flag 27: " << linea.substr(71, 2) << endl;
				//	cout << "\t\t* Flag 28: " << linea.substr(73, 2) << endl;
				//	cout << "\t\t* Flag 29: " << linea.substr(75, 2) << endl;
				//	cout << "\t\t* Flag 30: " << linea.substr(77, 2) << endl;
				//	cout << "\t\t* Flag 31: " << linea.substr(79, 2) << endl;
				//	cout << "\t\t* Flag 32: " << linea.substr(81, 2) << endl;
				//	cout << "\t\t* Flag 33: " << linea.substr(83, 2) << endl;
				//	cout << "\t\t* Flag 34: " << linea.substr(85, 2) << endl;
				//	cout << "\t\t* Flag 35: " << linea.substr(87, 2) << endl;
				//	cout << "\t\t* Flag 36: " << linea.substr(89, 2) << endl;
				//	cout << "\t\t* Flag 37: " << linea.substr(91, 2) << endl;
				//	cout << "\t\t* Flag 38: " << linea.substr(93, 2) << endl;
				//	cout << "\t\t* Flag 39: " << linea.substr(95, 2) << endl;
				//	cout << "\t\t* Flag 40: " << linea.substr(97, 2) << endl;
				//	cout << "\t\t* Flag 41: " << linea.substr(99, 2) << endl;
				//	cout << "\t\t* Flag 42: " << linea.substr(101, 2) << endl;
				//	cout << "\t\t* Flag 43: " << linea.substr(103, 2) << endl;
				//	cout << "\t\t* Flag 44: " << linea.substr(105, 2) << endl;
				//	cout << "\t\t* Flag 45: " << linea.substr(107, 2) << endl;
				//	cout << "\t\t* Flag 46: " << linea.substr(109, 2) << endl;
				//	cout << "\t\t* Flag 47: " << linea.substr(111, 2) << endl;
				//	cout << "\t\t* Flag 48: " << linea.substr(113, 2) << endl;
				//	cout << "\t\t* Flag 49: " << linea.substr(115, 2) << endl;
				//	cout << "\t\t* Flag 50: " << linea.substr(117, 2) << endl;
				//	cout << "\t\t* Flag 51: " << linea.substr(119, 2) << endl;
				//	cout << "\t\t* Flag 52: " << linea.substr(121, 2) << endl;
				//	cout << "\t\t* Flag 53: " << linea.substr(123, 2) << endl;
				//	cout << "\t\t* Flag 54: " << linea.substr(125, 2) << endl;
				//	cout << "\t\t* Flag 55: " << linea.substr(127, 2) << endl;
				//	cout << "\t\t* Flag 56: " << linea.substr(129, 2) << endl;
				//	cout << "\t\t* Flag 57: " << linea.substr(131, 2) << endl;
				//	cout << "\t\t* Flag 58: " << linea.substr(133, 2) << endl;
				//	cout << "\t\t* Flag 59: " << linea.substr(135, 2) << endl;
				//	cout << "\t\t* Flag 60: " << linea.substr(137, 2) << endl;
				//	cout << "\t\t* Flag 61: " << linea.substr(139, 2) << endl;
				//	cout << "\t\t* Flag 62: " << linea.substr(141, 2) << endl;
				//	cout << "\t\t* Flag 63: " << linea.substr(143, 2) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S4", (LPCSTR)nombreArchivos4.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S4" << endl : cout << "\t*** Comando Enviado: " << "S4" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S4 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos4(nombreArchivos4.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos4, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Medio de pago 1: " << linea.substr(2, 13) << endl;
				//	cout << "\t\t* Medio de pago 2: " << linea.substr(15, 13) << endl;
				//	cout << "\t\t* Medio de pago 3: " << linea.substr(28, 13) << endl;
				//	cout << "\t\t* Medio de pago 4: " << linea.substr(41, 13) << endl;
				//	cout << "\t\t* Medio de pago 5: " << linea.substr(54, 13) << endl;
				//	cout << "\t\t* Medio de pago 6: " << linea.substr(67, 13) << endl;
				//	cout << "\t\t* Medio de pago 7: " << linea.substr(80, 13) << endl;
				//	cout << "\t\t* Medio de pago 8: " << linea.substr(93, 13) << endl;
				//	cout << "\t\t* Medio de pago 9: " << linea.substr(106, 13) << endl;
				//	cout << "\t\t* Medio de pago 10: " << linea.substr(119, 13) << endl;
				//	cout << "\t\t* Medio de pago 11: " << linea.substr(132, 13) << endl;
				//	cout << "\t\t* Medio de pago 12: " << linea.substr(145, 13) << endl;
				//	cout << "\t\t* Medio de pago 13: " << linea.substr(158, 13) << endl;
				//	cout << "\t\t* Medio de pago 14: " << linea.substr(171, 13) << endl;
				//	cout << "\t\t* Medio de pago 15: " << linea.substr(184, 13) << endl;
				//	cout << "\t\t* Medio de pago 16: " << linea.substr(197, 13) << endl;
				//	cout << "\t\t* Medio de pago 17: " << linea.substr(210, 13) << endl;
				//	cout << "\t\t* Medio de pago 18: " << linea.substr(223, 13) << endl;
				//	cout << "\t\t* Medio de pago 19: " << linea.substr(236, 13) << endl;
				//	cout << "\t\t* Medio de pago 20: " << linea.substr(249, 13) << endl;
				//	cout << "\t\t* Medio de pago 21: " << linea.substr(262, 13) << endl;
				//	cout << "\t\t* Medio de pago 22: " << linea.substr(275, 13) << endl;
				//	cout << "\t\t* Medio de pago 23: " << linea.substr(288, 13) << endl;
				//	cout << "\t\t* Medio de pago 24: " << linea.substr(301, 13) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "S5", (LPCSTR)nombreArchivos5.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "S5" << endl : cout << "\t*** Comando Enviado: " << "S5" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tINFORMACION DE ESTATUS S5 DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivos5(nombreArchivos5.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivos5, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Status: " << linea.substr(0, 2) << endl;
				//	cout << "\t\t* RIF: " << linea.substr(2, 11) << endl;
				//	cout << "\t\t* N\243mero de Registro: " << linea.substr(13, 10) << endl;
				//	cout << "\t\t* N\243mero de la Memoria de auditor\241a: " << linea.substr(23, 4) << endl;
				//	cout << "\t\t* Capacidad de la Memoria de auditor\241a en MB: " << linea.substr(27, 4) << endl;
				//	cout << "\t\t* Espacio Disponible en la memoria en MB: " << linea.substr(31, 4) << endl;
				//	cout << "\t\t* N\243mero de documentos registrados: " << linea.substr(35, 6) << endl;
				//}

				//BRESP = dllTfhkaif.UploadReportCmd(dllTfhkaif.status, dllTfhkaif.error, "U0X", (LPCSTR)nombreArchivosU0X.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "U0X" << endl : cout << "\t*** Comando Enviado: " << "U0X" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tEXTRACCION DEL REPORTE X DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivosU0X(nombreArchivosU0X.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivosU0X, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* N\243mero del proximo Reporte Z: " << linea.substr(0, 4) << endl;
				//	cout << "\t\t* Fecha del \243ltimo Reporte Z emitido: " << linea.substr(4, 6) << endl;
				//	cout << "\t\t* Hora de \243ltimo Reporte Z emitido: " << linea.substr(10, 4) << endl;
				//	cout << "\t\t* N\243mero de \243ltima factura: " << linea.substr(14, 8) << endl;
				//	cout << "\t\t* Fecha de emision de la \243ltima factura: " << linea.substr(22, 6) << endl;
				//	cout << "\t\t* Hora de emision de la \243ltima facutra: " << linea.substr(28, 4) << endl;
				//	cout << "\t\t* N\243mero de \243ltima nota de credito: " << linea.substr(32, 8) << endl;
				//	cout << "\t\t* N\243mero de \243ltima nota de dedito: " << linea.substr(40, 8) << endl;
				//	cout << "\t\t* N\243mero de \243ltimo Documento no fiscal: " << linea.substr(48, 8) << endl;
				//	cout << "\t\t* Acumulado de exento: " << linea.substr(56, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 1: " << linea.substr(69, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 1: " << linea.substr(82, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa2: " << linea.substr(95, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 2: " << linea.substr(108, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 3: " << linea.substr(121, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 3: " << linea.substr(134, 13) << endl;
				//	cout << "\t\t* Acumulado exento Nota de Debito: " << linea.substr(147, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 1 Nota de debito: " << linea.substr(160, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 1 Nota de debito: " << linea.substr(173, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 2 Nota de debito: " << linea.substr(186, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 2 Nota de debito: " << linea.substr(199, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 3 Nota de debito: " << linea.substr(212, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 3 Nota de debito: " << linea.substr(225, 13) << endl;
				//	cout << "\t\t* Acumulado exento Nota de credito: " << linea.substr(238, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 1 Nota de credito: " << linea.substr(251, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 1 Nota de credito: " << linea.substr(264, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 2 Nota de credito: " << linea.substr(277, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 2 Nota de credito: " << linea.substr(290, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 3 Nota de credito: " << linea.substr(303, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 3 Nota de credito: " << linea.substr(316, 13) << endl;
				//}
				//
				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadReportCmd(dllTfhkaif.status, dllTfhkaif.error, "U0Z", (LPCSTR)nombreArchivosU0Z.c_str());
				//!BRESP ? cout << "\t!!! Comando No Aceptado: " << "U0Z" << endl : cout << "\t*** Comando Enviado: " << "U0Z" << endl;

				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tEXTRACCION DEL REPORTE Z DE LA IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;

				//ifstream archivosU0Z(nombreArchivosU0Z.c_str());

				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivosU0Z, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* N\243mero del proximo Reporte Z: " << linea.substr(0, 4) << endl;
				//	cout << "\t\t* Fecha del \243ltimo Reporte Z emitido: " << linea.substr(4, 6) << endl;
				//	cout << "\t\t* Hora de \243ltimo Reporte Z emitido: " << linea.substr(10, 4) << endl;
				//	cout << "\t\t* N\243mero de \243ltima factura: " << linea.substr(14, 8) << endl;
				//	cout << "\t\t* Fecha de emision de la \243ltima factura: " << linea.substr(22, 6) << endl;
				//	cout << "\t\t* Hora de emision de la \243ltima facutra: " << linea.substr(28, 4) << endl;
				//	cout << "\t\t* N\243mero de \243ltima nota de credito: " << linea.substr(32, 8) << endl;
				//	cout << "\t\t* N\243mero de \243ltima nota de dedito: " << linea.substr(40, 8) << endl;
				//	cout << "\t\t* N\243mero de \243ltimo Documento no fiscal: " << linea.substr(48, 8) << endl;
				//	cout << "\t\t* Acumulado de exento: " << linea.substr(56, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 1: " << linea.substr(69, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 1: " << linea.substr(82, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa2: " << linea.substr(95, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 2: " << linea.substr(108, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 3: " << linea.substr(121, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 3: " << linea.substr(134, 13) << endl;
				//	cout << "\t\t* Acumulado exento Nota de Debito: " << linea.substr(147, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 1 Nota de debito: " << linea.substr(160, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 1 Nota de debito: " << linea.substr(173, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 2 Nota de debito: " << linea.substr(186, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 2 Nota de debito: " << linea.substr(199, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 3 Nota de debito: " << linea.substr(212, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 3 Nota de debito: " << linea.substr(225, 13) << endl;
				//	cout << "\t\t* Acumulado exento Nota de credito: " << linea.substr(238, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 1 Nota de credito: " << linea.substr(251, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 1 Nota de credito: " << linea.substr(264, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 2 Nota de credito: " << linea.substr(277, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 2 Nota de credito: " << linea.substr(290, 13) << endl;
				//	cout << "\t\t* Acumulado Base Imponible Tasa 3 Nota de credito: " << linea.substr(303, 13) << endl;
				//	cout << "\t\t* Acumulado Impuesto Tasa 3 Nota de credito: " << linea.substr(316, 13) << endl;
				//}

				//Sleep(5000);

				//BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "SV", (LPCSTR)nombreArchivosv.c_str());
				//!BRESP ? cout << "\n\t!!! Comando No Aceptado: " << "SV" << endl : cout << "\n\t*** Comando Enviado: " << "SV" << endl;

				//ifstream archivosv(nombreArchivosv.c_str());
				//linea = "";
				//cout << "\t----------------------------------------------------------------------" << endl;
				//cout << "\tMODELO DE IMPRESORA FISCAL" << endl;
				//cout << "\t----------------------------------------------------------------------" << endl;
				//// Obtener línea de archivo, y almacenar contenido en "linea"
				//while (getline(archivosv, linea)) {
				//	// Lo vamos imprimiendo
				//	cout << "\t\t* Serial: "<<linea.substr(2,3)<<endl;
				//	cout << "\t\t* Pa\241s: " << linea.substr(5, 7) << endl;
				//}

				//Sleep(5000);

				BRESP = dllTfhkaif.UploadStatusCmd(dllTfhkaif.status, dllTfhkaif.error, "SV", (LPCSTR)nombreArchivosv.c_str());
				!BRESP ? cout << "\n\t!!! Comando No Aceptado: " << "SV" << endl : cout << "\n\t*** Comando Enviado: " << "SV" << endl;

				ifstream archivosv(nombreArchivosv.c_str());
				linea = "";
				cout << "\t----------------------------------------------------------------------" << endl;
				cout << "\tMODELO DE IMPRESORA FISCAL" << endl;
				cout << "\t----------------------------------------------------------------------" << endl;
				// Obtener línea de archivo, y almacenar contenido en "linea"
				while (getline(archivosv, linea)) {
					// Lo vamos imprimiendo
					cout << "\t\t* Serial: "<<linea.substr(2,3)<<endl;
					cout << "\t\t* Pa\241s: " << linea.substr(5, 7) << endl;
				}

				Sleep(5000);
				
				BRESP = dllTfhkaif.ReadFpStatus(dllTfhkaif.status, dllTfhkaif.error);
				!BRESP ? cout << "\n\t!!! Comando No Aceptado: " << "FPStatus" << endl : cout << "\n\t*** Comando Enviado: " << "FPStatus" << endl;
				
				cout << "\t----------------------------------------------------------------------" << endl;
				cout << "\tINFORMACION DE ESTATUS Y ERROR DE LA IMPRESORA FISCAL" << endl;
				cout << "\t----------------------------------------------------------------------" << endl;
				cout << "\t\t* Status: " << dllTfhkaif.status << "\n\t\t* Error: " << dllTfhkaif.error << endl;
				cout << "\t----------------------------------------------------------------------" << endl;
				
				Sleep(5000);

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