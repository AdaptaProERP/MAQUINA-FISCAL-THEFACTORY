// Programa   : DLL_TFHK_GENTXT
// Fecha/Hora : 24/06/2024 12:54:03
// Propósito  : Devuelve Ultimo Número de Factura, impresora THEFACTORY
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
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

  AADD(aData,{"Número de Cajero asignado: "                           , 2,  2,""})
  AADD(aData,{"Total de ventas diarias: "                             , 4, 17,""})
  AADD(aData,{"Número de la última factura: "                         , 21, 8,""})
  AADD(aData,{"Cantidad de facturas emitidas en el día: "             , 29, 5,""})
  AADD(aData,{"Número de la última nota de débito: "                  , 34, 8,""})
  AADD(aData,{"Cantidad de notas de débito emitidas en el día:"       , 42, 5,""})
  AADD(aData,{"Número de la última nota de crédito: "                 , 47, 8,""})
  AADD(aData,{"Cantidad de notas de crédito emitidas en el día:"      , 55, 5,""})
  AADD(aData,{"Número del último documento no fiscal: "               , 60, 8,""})
  AADD(aData,{"Cantidad de documentos no fiscales emitidos en el día:", 68, 5,""})
  AADD(aData,{"Contador de reportes de Memoria Fiscal: "              , 73, 4,""})
  AADD(aData,{"Contador de cierres diarios Z: "                       , 77, 4,""})
  AADD(aData,{"RIF: "                                                 , 81, 11,""})
  AADD(aData,{"Número de Registro de la Máquina:  "                   , 92, 10,""})
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
