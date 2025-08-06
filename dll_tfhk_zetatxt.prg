// Programa   : DLL_TFHK_ZETATXT
// Fecha/Hora : 08/07/2025 14:09:24
// Propósito  : Generar ZETA en TXT
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
// Tabla      :
// Para el caso de 18 el flag 63 en 19 y le pase como me comento en 13 que es para el caso que el flag 63 esta en 00


#INCLUDE "DPXBASE.CH"

PROCE MAIN(cFileZeta,lEstatus,lView)
  LOCAL cMemo   :="",aData:={},aResult:={},I,nPos:=1,I,cLine,cFile:="",cZeta:="",nAt,cTitle:=""
  LOCAL aS3     :={},aS1  :={}
  LOCAL aTasas  :={}
  LOCAL nLenPar :=18 // Depende del valor del FLAG 63=19 será 18, caso contrario será 13, programarlo con PJ6300
  LOCAL nIzq    :=60
  LOCAL nDer    :=30
  LOCAL aEstatus:={}

  DEFAULT cFileZeta:="ZETA.TXT",;
          lEstatus :=.F.,;
          lView    :=.T.

  aS3:=EJECUTAR("DLL_TFHK_S3",NIL,NIL,.F.)
  aS1:=EJECUTAR("DLL_TFHK_S1",NIL,NIL,.F.)

  EJECUTAR("DLL_TFHK_REPORT")

  cMemo  :=MemoRead(oDp:cFileZeta)

  aResult:=_VECTOR(cMemo,CHR(124))
  cMemo  :=STRTRAN(cMemo,CHR(124),"")

  AADD(aData,{"Número del Reporte Z: "                              ,  0,  4,""})
  AADD(aData,{"Fecha del último Reporte Z emitido: "                ,  4,  6,""})
  AADD(aData,{"Hora de último Reporte Z emitido: "                  , 10,  4,""})
  AADD(aData,{"Número de última factura: "                          , 14,  8,""})
  AADD(aData,{"Fecha de emision de la última factura: "             , 22,  6,""})
  AADD(aData,{"Hora de emision de la última factura: "              , 28,  4,""})
  AADD(aData,{"Número de última nota de credito: "                  , 32,  8,""})
  AADD(aData,{"Número de última nota de dedito : "                  , 40,  8,""})
  AADD(aData,{"Número de último Documento no fiscal: "              , 48,  8,""})
  AADD(aData,{"Acumulado de exento: "                               , 56, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa{1}: "                  , 69, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {1}: "                       , 82, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa{2}: "                  , 95, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {2}: "                       ,108, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {3}: "                 ,121, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {3}: "                       ,134, 18,""})
  AADD(aData,{"Acumulado exento Nota de Debito: "                   ,147, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {1} Nota de debito: "  ,160, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {1} Nota de debito: "        ,173, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {2} Nota de debito: "  ,186, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {2} Nota de debito: "        ,199, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {3} Nota de debito: "  ,212, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {3} Nota de debito: "        ,225, 18,""})
  AADD(aData,{"Acumulado exento Nota de credito: "                  ,238, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {1} Nota de credito: " ,251, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {1} Nota de credito: "       ,264, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {2} Nota de credito: " ,277, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {2} Nota de credito: "       ,290, 18,""})
  AADD(aData,{"Acumulado Base Imponible Tasa {3} Nota de credito: " ,303, 18,""})
  AADD(aData,{"Acumulado Impuesto Tasa {3} Nota de credito: "       ,316, 18,""})


  AEVAL(aData,{|a,n| aData[n,4]:=SUBS(cMemo,nPos,a[3]),;
                     nPos      :=nPos+a[3]})


  
  cMemo:=""

  IF lEstatus

    AADD(aEstatus,{"Modelo: ",oTFH:cModelo})

    AADD(aEstatus,{REPLI("-",15)+" S3 "+REPLI("-",15),""})

    FOR I=1 TO LEN(aEstatus)
      cLine:=PADL(aEstatus[I,1],nIzq)+PADR(aEstatus[I,2],10)
      cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)+cLine
    NEXT I

    FOR I=1 TO LEN(aS3)
      cLine:=PADL(aS3[I,1],nIzq)+PADR(aS3[I,2],10)
      cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)+cLine
    NEXT I

  ENDIF

  FOR I=1 TO LEN(aS1)
    cLine:=PADL(aS1[I,1],nIzq)+PADR(aS1[I,2],10)
    cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)+cLine
  NEXT I

  IF !lEstatus

    nAt:=ASCAN(aS3,{|a,n|"Flag"$a[1]})

    IF nAt>0

       FOR I=1 TO nAt-1
         cLine:=PADL(aS3[I,1],nIzq)+PADR(aS3[I,2],10)
         cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)+cLine
       NEXT I

    ENDIF

  ENDIF

/*
  cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)
  cMemo:=cMemo+PADL(" Tasa {1}: ",nIzq)+PADR(LEFT(aS3[4,2],2)+"."+RIGHT(aS3[4,2],2),10)+CRLF
  cMemo:=cMemo+PADL(" Tasa {2}: ",nIzq)+PADR(LEFT(aS3[5,2],2)+"."+RIGHT(aS3[5,2],2),10)+CRLF
  cMemo:=cMemo+PADL(" Tasa {3}: ",nIzq)+PADR(LEFT(aS3[6,2],2)+"."+RIGHT(aS3[6,2],2),10)
*/

ViewArray(aData)

  FOR I=1 TO LEN(aData)

    IF aData[I,3]>14
       aData[I,4]:=LEFT(aData[I,4],16)+"."+RIGHT(aData[I,4],2)
       aData[I,4]:=FDP(VAL(aData[I,4]),"999,999,999,999,999.99")
       cLine:=PADL(aData[I,1],nIzq)+PADR(aData[I,4],25)
    ELSE
       cLine:=PADL(aData[I,1],nIzq)+PADR(aData[I,4],10)
    ENDIF
   
    cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)+cLine

  NEXT I

  oDp:aZeta:=ACLONE(aData)

  lMkdir("thefactory")

  cZeta:=aData[1,4]

  IF lEstatus
     cTitle:="Estatus "+oTFH:cModelo
     cFile :="thefactory\estatus_"+dtos(oDp:dFecha)+".txt"
  ELSE
     cTitle:="REPORTE ZETA "+cZeta
     cFile :="thefactory\zeta"+cZeta+".txt"
  ENDIF

  DPWRITE(cFile,cMemo)

  IF lView

    VIEWRTF(cFile,cTitle)

  ENDIF

RETURN cMemo
// EOF
