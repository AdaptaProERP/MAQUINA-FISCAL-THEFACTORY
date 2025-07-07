// Programa   : DLL_TFHK_CLOSE
// Fecha/Hora : 24/06/2024 12:54:03
// Propósito  : Devuelve Ultimo Número de Factura, impresora THEFACTORY
// Creado Por : Juan Navas
// Llamado por:
// Aplicación :
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

RETURN .T.
//EOF
