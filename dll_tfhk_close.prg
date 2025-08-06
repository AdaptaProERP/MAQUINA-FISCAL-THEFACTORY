// Programa   : DLL_TFHK_CLOSE
// Fecha/Hora : 24/06/2024 12:54:03
// Prop�sito  : Devuelve Ultimo N�mero de Factura, impresora THEFACTORY
// Creado Por : Juan Navas
// Llamado por:
// Aplicaci�n :
// Tabla      :

#INCLUDE "DPXBASE.CH"

PROCE MAIN()
  LOCAL cFarProc

  IF !Empty(oDp:nTFHDLL)

     cFarProc:= GetProcAddress(oDp:nTFHDLL,"CloseFpctrl",.T.,7 ) 
     CallDLL(cFarProc ) 
     FreeLibrary(oDp:nTFHDLL)
     oDp:nTFHDLL:=NIL
     oTFH       :=NIL

  ENDIF

  oDp:aFHK_FLAG21:={}
  oDp:nFHK_LENENT:=0 // definidas por el usuario en formulario
  oDp:nFHK_LENDEC:=0 // 

RETURN .T.
//EOF
