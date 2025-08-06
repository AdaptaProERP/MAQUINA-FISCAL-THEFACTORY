// Programa   : DLL_TFHK_REPORT
// Fecha/Hora : 24/06/2024 12:54:03
// Propósito  : Genera Arreglo con Valor S1, Totales
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cS1,lMemo)
   LOCAL aData:={},cMemo:="",aData:={}

   DEFAULT lMemo:=.T.

   IF Empty(oDp:cImpLetra)
     EJECUTAR("DPSERIEFISCALLOAD")
   ENDIF

   EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))

   EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"REPORT","U0Z") // Generar reporte ZETA en TXT

 				
RETURN 
// EOF


