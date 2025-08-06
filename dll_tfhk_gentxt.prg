// Programa   : DLL_TFHK_GENTXT
// Fecha/Hora : 24/06/2024 12:54:03
// Prop�sito  : Devuelve Ultimo N�mero de Factura, impresora THEFACTORY
// Creado Por : Juan Navas
// Llamado por:
// Aplicaci�n :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cFile)
  LOCAL cNumero:=SPACE(10),nLenC,aData:={}

  IF Empty(oDp:cImpLetra)
     EJECUTAR("DPSERIEFISCALLOAD")
  ENDIF

  IF !("TFHK_DLL"$oDp:cImpFiscal)
     EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))
  ENDIF

  EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"GETTXT") // Generar reporte ZETA en TXT

/*
? oTFH:S2
? oTFH:S3
*/
  ViewArray(oDp:aDataTFH)

RETURN .T.
// EOF
