// Programa   : DLL_TFHK_CRE
// Fecha/Hora : 24/06/2024 12:54:03
// Propósito  : Devuelve Ultimo Número de Crédito, impresora THEFACTORY
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(lSay,nLen,cSerie)
   LOCAL cNumero:=SPACE(10),nLenC,aS1,nAt

   IF Empty(oDp:cImpLetra)
      EJECUTAR("DPSERIEFISCALLOAD")
   ENDIF

   DEFAULT lSay  :=.F.,;
           nLen  :=8,;
           cSerie:=oDp:cImpLetra

   nLenC:=nLen-1

   oDp:cTFHCRE:="" // numero de factura

   IF !("TFHK_DLL"$oDp:cImpFiscal)
      EJECUTAR("DPSERIEFISCALLOAD","SFI_LETRA"+GetWhere("=",oDp:cTkSerie))
   ENDIF

   aS1:=EJECUTAR("DLL_TFHK_S1")

   nAt:=ASCAN(aS1,{|a,n|"crédito:"$a[1]})
   
   IF nAt>0
     oDp:cTFHCRE:=aS1[nAt,2]
   ENDIF

// ? oDp:cTFHCRE

RETURN oDp:cTFHCRE
// EOF

