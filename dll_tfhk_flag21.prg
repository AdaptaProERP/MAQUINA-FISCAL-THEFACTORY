// Programa   : DLL_TFHK_FLAG21
// Fecha/Hora : 07/07/2025 07:14:39
// Propósito  : Obiente la cantidad enteros y decimales del campo precio
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cS1,lMemo)
   LOCAL aData:={},cMemo:=""
   LOCAL aS3,lMemo,aData:={},aF21:={},nAt:=0,cFlag:=""

   IF Empty(oDp:cImpLetra)
     EJECUTAR("DPSERIEFISCALLOAD")
   ENDIF

   EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))

   aS3:=EJECUTAR("DLL_TFHK_S3")

   AADD(aF21,{"00","8,2"})
   AADD(aF21,{"01","7,3"})
   AADD(aF21,{"02","6,4"})
   AADD(aF21,{"11","9,1"})
   AADD(aF21,{"12","10,0"})
   AADD(aF21,{"30","14,2"})

   nAt:=ASCAN(aS3,{|a,n|a[1]="Flag 21:"})

   oDp:aFHK_FLAG21:={}
   oDp:nFHK_LENENT:=0 // definidas por el usuario en formulario
   oDp:nFHK_LENDEC:=0 // 

   IF nAt>0

      cFlag          :=aS3[nAt,2]
      nAt            :=ASCAN(aF21,{|a,n|a[1]=cFlag})

      IF nAt=0 
        MsgMemo("FLAG 21, no encontrado en S3")
      ELSE
        oDp:aFHK_FLAG21:=_VECTOR(aF21[nAt,2])
        oDp:nFHK_LENENT:=CTOO(oDp:aFHK_FLAG21[1],"N")
        oDp:nFHK_LENDEC:=CTOO(oDp:aFHK_FLAG21[2],"N")
      ENDIF

   ENDIF

// ViewArray(aS3)
  
RETURN oDp:aFHK_FLAG21
// EOF
