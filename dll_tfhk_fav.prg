// Programa   : DLL_TFHK_FAV
// Fecha/Hora : 24/06/2024 12:54:03
// Prop�sito  : Devuelve Ultimo N�mero de Factura, impresora THEFACTORY
// Creado Por : Juan Navas
// Llamado por:
// Aplicaci�n :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(lSay,nLen,cSerie)
   LOCAL cNumero:=SPACE(10),nLenC

   IF Empty(oDp:cImpLetra)
      EJECUTAR("DPSERIEFISCALLOAD")
   ENDIF


   DEFAULT lSay  :=.F.,;
           nLen  :=8,;
           cSerie:=oDp:cImpLetra

   nLenC:=nLen-1

   oDp:cTFHFAV:="" // numero de factura

   IF !("TFHK_DLL"$oDp:cImpFiscal)
      EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))
   ENDIF

   EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"GETFAV")

//EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"GETDATA") // Generar reporte ZETA en TXT
//"AQUI",oDp:cSql,oDp:cTkSerie,oDp:cTFHFAV,"oDp:cTFHFAV"

RETURN oDp:cTFHFAV
// EOF
