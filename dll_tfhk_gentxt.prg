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
/*
   oDp:aDataTFH:={}
   EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"GETDATA") // Generar reporte ZETA en TXT
*/
// ? oTFH:S1

  AADD(aData,{"N�mero de Cajero asignado: "                           , 2,  2,""})
  AADD(aData,{"Total de ventas diarias: "                             , 4, 17,""})
  AADD(aData,{"N�mero de la �ltima factura: "                         , 21, 8,""})
  AADD(aData,{"Cantidad de facturas emitidas en el d�a: "             , 29, 5,""})
  AADD(aData,{"N�mero de la �ltima nota de d�bito: "                  , 34, 8,""})
  AADD(aData,{"Cantidad de notas de d�bito emitidas en el d�a:"       , 42, 5,""})
  AADD(aData,{"N�mero de la �ltima nota de cr�dito: "                 , 47, 8,""})
  AADD(aData,{"Cantidad de notas de cr�dito emitidas en el d�a:"      , 55, 5,""})
  AADD(aData,{"N�mero del �ltimo documento no fiscal: "               , 60, 8,""})
  AADD(aData,{"Cantidad de documentos no fiscales emitidos en el d�a:", 68, 5,""})
  AADD(aData,{"Contador de reportes de Memoria Fiscal: "              , 73, 4,""})
  AADD(aData,{"Contador de cierres diarios Z: "                       , 77, 4,""})
  AADD(aData,{"RIF: "                                                 , 81, 11,""})
  AADD(aData,{"N�mero de Registro de la M�quina:  "                   , 92, 10,""})
  AADD(aData,{"Hora actual de la impresora (HHMMSS): "                ,102,  6,""})
  AADD(aData,{"Fecha actual de la impresora (DDMMAA): "               ,108,  6,""})

  AEVAL(aData,{|a,n| aData[n,4]:=SUBS(oTFH:S1,a[2]+1,a[3])})
  AEVAL(aData,{|a,n| aData[n]  :={a[1],a[4],"S1"}})

ViewArray(aData)				

/*
? oTFH:S2
? oTFH:S3
*/
//   EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"GETTXT") // Generar reporte ZETA en TXT
//    ViewArray(oDp:aDataTFH)

RETURN .T.
// EOF
