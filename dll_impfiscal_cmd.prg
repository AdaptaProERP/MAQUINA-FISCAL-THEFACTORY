// Programa   : DLL_IMPFISCAL_CMD
// Fecha/Hora : 27/04/2022 05:41:32
// Propósito  : Ejecuta comando para Impresora Fiscal, todas los metodos incorporan las mismas funciones operaciones llamando a las funciones especificas en cada impresora
// Creado Por : Juan Navas
// Llamado por:
// Aplicación : cCmd=Cada Impresora Resuelve sus comandos
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cCmd,cOption,lAuto,cLetra,cTitle)
   LOCAL oImpFiscal:=NIL,oSerFis,cError,lRun:=.F.,cResp:=""

   DEFAULT cCmd   :="PFrepz",;
           lAuto  :=.F.     ,;
           cOption:="Reporte Z ",;
           cTitle :=cOption

// ? cCmd,cOption,lAuto,cLetra,cTitle,"cCmd,cOption,lAuto,cLetra,cTitle"
 
   IF ISSQLFIND("DPSERIEFISCAL","SFI_PCNAME"+GetWhere("=",oDp:cPcName)+"  AND SFI_AUTDET=1 AND NOT SFI_IMPFIS"+GetWhere(" LIKE ","%Ningun%"))
      // Debe Actualizar el Puerto del AutoDetec
      EJECUTAR("DPSERFISCALAUTODETEC")
   ENDIF

   IF !Empty(cLetra)

     oSerFis     :=OpenTable("SELECT * FROM DPSERIEFISCAL WHERE SFI_LETRA"+GetWhere("=",cLetra))
     oSerFis:End()

   ELSE

     oSerFis     :=OpenTable("SELECT * FROM DPSERIEFISCAL WHERE SFI_PCNAME"+GetWhere("=",oDp:cPcName))
     oSerFis:End()

     IF oSerFis:RecCount()=0
        MsgMemo("Este PC "+oDp:cPcName+" no Tiene Serie Fiscal Asignada","Asignar Serie Fiscal para este PC")
        DPLBX("DPSERIEFISCAL.LBX")
     ENDIF

     IF Empty(oSerFis:SFI_PUERTO) .AND. !("Ningu"$oSerFis:SFI_IMPFIS) 
        MsgMemo("Puerto Serial no detectado para la Impresora Fiscal "+oSerFis:SFI_IMPFIS,"Seleccione el Puerto de la Impresora Fiscal")
        EJECUTAR("DPSERIEFISCAL",3,oSerFis:SFI_LETRA)
        RETURN .F.
     ENDIF

   ENDIF

   oDp:cImpFiscal:=oSerFis:SFI_IMPFIS
   oDp:cImpFisCom:=ALLTRIM(oSerFis:SFI_PUERTO)

   IF !MsgNoYes("Desea Ejecutar: "+cTitle+" en "+oDp:cImpFiscal,oDp:cMsgNoYes)
      RETURN .T.
   ENDIF

   FERASE("TEMP\IMPFISCAL_CMD.TXT")

   EJECUTAR("DPDIRTEMPDEL") // remueve los temporales

   IF "EPSON"$oDp:cImpFiscal
      lRun :=.T.
      cResp:=EJECUTAR("DLL_EPSON_CMD",cCmd,cOption)
      cError:=MemoRead("TEMP\IMPFISCAL_CMD.TXT")
   ENDIF

   IF "TFHK_EXE"$ALLTRIM(oDp:cImpFiscal)
      lRun :=.T.
      cResp:=EJECUTAR("RUNEXE_TFHKA_CMD",cCmd,cOption)
   ENDIF

   IF "TFHK_DLL"$ALLTRIM(UPPER(oDp:cImpFiscal))
      lRun:=.T.
      EJECUTAR("DLL_TFHKA_CMD",cCmd,cOption)
   ENDIF

   IF "BEMATECH"$oDp:cImpFiscal 

      lRun:=.T.
      oDp:cSerialIF:=""

      EJECUTAR("DLL_BEMATECH_CMD",cCmd,cOption)

      IF !Empty(oDp:cSerialIF)
        oDp:cSerialIF:=ALLTRIM(oDp:cSerialIF)
        SQLUPDATE("DPSERIEFISCAL","SFI_SERIMP",oDp:cSerialIF,oSerFis:cWhere)
        SQLUPDATE("DPSERIEFISCAL","SFI_SERIMP",oDp:cSerialIF,"SFI_PCNAME"+GetWhere("=",oDp:cPcName)) // tambien las demás formas 
       ENDIF

   ENDIF

   // Resumen Diario de Deventas
   IF lRun .AND. "Z"$cCmd
      RESUMENDIARIO()
   ENDIF

   IF !lRun
     MsgMemo("Impresora no "+oDp:cImpFiscal+" no Tiene Implementado el Comando "+cCmd+" "+cOption)
   ENDIF

   IF !Empty(cError)
      MsgMemo(cError,"Incidencia en "+cOption)
   ENDIF

RETURN cResp

/*
// Realizar resumen diario de Ventas
*/
FUNCTION RESUMENDIARIO()
   LOCAL cCodSuc:=oDp:cSucursal,dDesde:=oDp:dFecha,dHasta:=oDp:dFecha,aTipDoc:={"TIK","DEV"},lReset:=.F.
   LOCAL cWhere :=NIL,nPeriodo:=1,cTitle:=NIL,lZeta:=.T.
   LOCAL cSerie :=NIL
   LOCAL aSeries:=ASQL("SELECT SFI_LETRA,SFI_CODSUC FROM DPSERIEFISCAL WHERE SFI_PCNAME"+GetWhere("=",oDp:cPcName))
   LOCAL I

   IF Empty(aSeries)
      aSeries:=ASQL("SELECT SFI_LETRA,SFI_CODSUC FROM DPSERIEFISCAL WHERE SFI_IMPFIS"+GetWhere("=",oDp:cImpFiscal))
   ENDIF

// ViewArray(aSeries)
// ? "aqui ñectura Z",oDp:cZeta,"antes del resumen"

   FOR I=1 TO LEN(aSeries)
      cSerie :=aSeries[I,1]
      cCodSuc:=aSeries[I,2]
      CursorWait()
      EJECUTAR("TIKTORDV",cCodSuc,dDesde,dHasta,aTipDoc,lReset,cSerie,oDp:cZeta)
   NEXT I
  
   EJECUTAR("BRTICKETPOS",cWhere,cCodSuc,nPeriodo,dDesde,dHasta,cTitle,lZeta)

RETURN .T.
// EOF

