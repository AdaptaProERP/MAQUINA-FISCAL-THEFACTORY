// Programa   : DLL_TFHK_SETIGTF
// Fecha/Hora : 24/06/2024 12:54:03
// Propósito  : Genera Arreglo con Valor S2, Alícuotas
//              https://github.com/AdaptaProERP/MAQUINA-FISCAL-THEFACTORY/blob/main/Ejemplo_Informacion_de_Impresora_Fiscal.cpp
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cCmd)
   LOCAL aData:={},cMemo:=""

   DEFAULT cCmd:="PJ6319"

   IF Empty(oDp:cImpLetra)
      EJECUTAR("DPSERIEFISCALLOAD")
   ENDIF

   oDp:lImpFisModVal:=.T.

   EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))

   EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"CMD",cCmd) 

//   EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"CMD","D" )  // Imprime la trama de la impresora


RETURN 
// EOF




