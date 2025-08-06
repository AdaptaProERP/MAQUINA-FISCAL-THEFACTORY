// Programa   : DLL_TFHK_S3
// Fecha/Hora : 24/06/2024 12:54:03
// Propósito  : Genera Arreglo con Valor S2, Alícuotas
//              https://github.com/AdaptaProERP/MAQUINA-FISCAL-THEFACTORY/blob/main/Ejemplo_Informacion_de_Impresora_Fiscal.cpp
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cS3,lMemo,lView)
   LOCAL aData:={},cMemo:="",nPos:=1,I,nAdd:=0

   DEFAULT lMemo:=.T.,;
           lView:=.T.

   IF Empty(cS3)

     IF Empty(oDp:cImpLetra)
       EJECUTAR("DPSERIEFISCALLOAD")
     ENDIF

     EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))

     EJECUTAR("DLL_TFH","",NIL,NIL,NIL,"GETDATA") // Generar reporte ZETA en TXT
     cS3:=oTFH:S3

  ENDIF

  cS3:=ALLTRIM(cS3)

  IF LEN(cS3)>142
     // Para las impresoras: SRP812, DT230,  HKA80, P3100DL, PP9, ACLAS, PP9-PLUS, TD1140.
     // 19.3. STATUS S3
     // Este comando permiteconsultar información referentea la
     // configuraciónde las tasasde
     // impuesto y flags
     nAdd:=6
  ENDIF

  IF nAdd=0

    AADD(aData,{"Tipo de Tasa 1: "   , 2, 1,""})
    AADD(aData,{"Tipo de Tasa 2: "   , 7, 1,""})
    AADD(aData,{"Tipo de Tasa 3: "   ,12, 1,""})
    AADD(aData,{"Valor de tasa 1: "  , 3, 4,""})
    AADD(aData,{"Valor de tasa 2: "  , 8, 4,""})
    AADD(aData,{"Valor de tasa 3: "  ,13, 4,""})

  ELSE

    AADD(aData,{"Tipo de Tasa 1: "   , 2, 1,""})
    AADD(aData,{"Tipo de Tasa 2: "   , 7, 1,""})
    AADD(aData,{"Tipo de Tasa 3: "   ,12, 1,""})
    AADD(aData,{"Tipo de IGTF  : "   ,17, 1,""})

    AADD(aData,{"Valor de tasa 1: "  , 3, 4,""})
    AADD(aData,{"Valor de tasa 2: "  , 8, 4,""})
    AADD(aData,{"Valor de tasa 3: "  ,13, 4,""})
    AADD(aData,{"Valor tasa IGTF: "  ,18, 4,""})

  ENDIF

  AADD(aData,{"Flag 00: " ,17+nAdd, 2,""})
  AADD(aData,{"Flag 01: " ,19+nAdd, 2,""})
  AADD(aData,{"Flag 02: " ,21+nAdd, 2,""})
  AADD(aData,{"Flag 03: " ,23+nAdd, 2,""})
  AADD(aData,{"Flag 04: " ,25+nAdd, 2,""})
  AADD(aData,{"Flag 05: " ,27+nAdd, 2,""})
  AADD(aData,{"Flag 06: " ,29+nAdd, 2,""})
  AADD(aData,{"Flag 07: " ,31+nAdd, 2,""})
  AADD(aData,{"Flag 08: " ,33+nAdd, 2,""})
  AADD(aData,{"Flag 09: " ,35+nAdd, 2,""})
  AADD(aData,{"Flag 10: " ,37+nAdd, 2,""})
  AADD(aData,{"Flag 11: " ,39+nAdd, 2,""})
  AADD(aData,{"Flag 12: " ,41+nAdd, 2,""})
  AADD(aData,{"Flag 13: " ,43+nAdd, 2,""})
  AADD(aData,{"Flag 14: " ,45+nAdd, 2,""})
  AADD(aData,{"Flag 15: " ,47+nAdd, 2,""})
  AADD(aData,{"Flag 16: " ,49+nAdd, 2,""})
  AADD(aData,{"Flag 17: " ,51+nAdd, 2,""})
  AADD(aData,{"Flag 18: " ,53+nAdd, 2,""})
  AADD(aData,{"Flag 19: " ,55+nAdd, 2,""})
  AADD(aData,{"Flag 20: " ,57+nAdd, 2,""})
  AADD(aData,{"Flag 21: " ,59+nAdd, 2,""})
  AADD(aData,{"Flag 22: " ,61+nAdd, 2,""})
  AADD(aData,{"Flag 23: " ,63+nAdd, 2,""})
  AADD(aData,{"Flag 24: " ,65+nAdd, 2,""})
  AADD(aData,{"Flag 25: " ,67+nAdd, 2,""})
  AADD(aData,{"Flag 26: " ,69+nAdd, 2,""})
  AADD(aData,{"Flag 27: " ,71+nAdd, 2,""})
  AADD(aData,{"Flag 28: " ,73+nAdd, 2,""})
  AADD(aData,{"Flag 29: " ,75+nAdd, 2,""})
  AADD(aData,{"Flag 30: " ,77+nAdd, 2,""})
  AADD(aData,{"Flag 31: " ,79+nAdd, 2,""})
  AADD(aData,{"Flag 32: " ,81+nAdd, 2,""})
  AADD(aData,{"Flag 33: " ,83+nAdd, 2,""})
  AADD(aData,{"Flag 34: " ,85+nAdd, 2,""})
  AADD(aData,{"Flag 35: " ,87+nAdd, 2,""})
  AADD(aData,{"Flag 36: " ,89+nAdd, 2,""})
  AADD(aData,{"Flag 37: " ,91+nAdd, 2,""})
  AADD(aData,{"Flag 38: " ,93+nAdd, 2,""})
  AADD(aData,{"Flag 39: " ,95+nAdd, 2,""})
  AADD(aData,{"Flag 40: " ,97+nAdd, 2,""})
  AADD(aData,{"Flag 41: " ,99+nAdd, 2,""})
  AADD(aData,{"Flag 42: " ,101+nAdd, 2,""})
  AADD(aData,{"Flag 43: " ,103+nAdd, 2,""})
  AADD(aData,{"Flag 44: " ,105+nAdd, 2,""})
  AADD(aData,{"Flag 45: " ,107+nAdd, 2,""})
  AADD(aData,{"Flag 46: " ,109+nAdd, 2,""})
  AADD(aData,{"Flag 47: " ,111+nAdd, 2,""})
  AADD(aData,{"Flag 48: " ,113+nAdd, 2,""})
  AADD(aData,{"Flag 49: " ,115+nAdd, 2,""})
  AADD(aData,{"Flag 50: " ,117+nAdd, 2,""})
  AADD(aData,{"Flag 51: " ,119+nAdd, 2,""})
  AADD(aData,{"Flag 52: " ,121+nAdd, 2,""})
  AADD(aData,{"Flag 53: " ,123+nAdd, 2,""})
  AADD(aData,{"Flag 54: " ,125+nAdd, 2,""})
  AADD(aData,{"Flag 55: " ,127+nAdd, 2,""})
  AADD(aData,{"Flag 56: " ,129+nAdd, 2,""})
  AADD(aData,{"Flag 57: " ,131+nAdd, 2,""})
  AADD(aData,{"Flag 58: " ,133+nAdd, 2,""})
  AADD(aData,{"Flag 59: " ,135+nAdd, 2,""})
  AADD(aData,{"Flag 60: " ,137+nAdd, 2,""})
  AADD(aData,{"Flag 61: " ,139+nAdd, 2,""})
  AADD(aData,{"Flag 62: " ,141+nAdd, 2,""})
  AADD(aData,{"Flag 63: " ,142+nAdd, 2,""})

  cS3:=ALLTRIM(cS3)

  AEVAL(aData,{|a,n| aData[n,4]:=SUBS(cS3,a[2]+1,a[3])})
  AEVAL(aData,{|a,n| aData[n]  :={a[1],a[4],"S3"}})

  IF lMemo
     AEVAL(aData,{|a,n| cMemo:=cMemo+IF(Empty(cMemo),"",CRLF)+a[1]+a[2]})
  ENDIF

  IF lView
    ViewArray(aData)
  ENDIF

RETURN aData
// EOF



