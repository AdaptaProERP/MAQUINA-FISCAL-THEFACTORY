// Programa   : TFHKA_DATA
// Fecha/Hora : 09/11/2022
// Propósito  : Genera la data para la Impresora Fiscal
// Creado Por : Juan Navas/ Kelvis Escalante	
// Llamado por: RUNEXE_TFHKA             
// Aplicación : FACTURACION CONVENCIONAL Y PUNTO DE VENTA
// Tabla      : DPDOCCLI

#INCLUDE "DPXBASE.CH"

PROCE MAIN(cCodSuc,cTipDoc,cNumero,cOption)
   LOCAL oTable
   LOCAL cWhere:="",cFile,cSql,cText:="",cSerie:=""
   LOCAL cUS,cNombre,cRIF,cDireccion,cTelefono,nIva:=0,cIva:="",cPrecio:="",nPrecio:=0,cCant:="",cDescri:=""
   LOCAL aPagos  :={},nLenP:=0,nLenC:=0,cLine,nPorEnt
   LOCAL aTipIva :={},nAt,oFacAfe,cWhereA

   DEFAULT cCodSuc:=oDp:cSucursal,;
           cTipDoc:="TIK",;
           cNumero:=SQLGETMAX("DPDOCCLI","DOC_NUMERO","DOC_TIPDOC"+GetWhere("=",cTipDoc)),;
           cOption:="3"

   oDp:cImpFiscalSqlPagos:=cSql

   nLenP:=oDp:nImpFisEntPre     // Antes 23/11/2023 oDp:nImpFisEnt        // Definible Ancho Numérico
   nLenP:=IF(nLenP=0,10,nLenP)  // Longitud del precio

   nLenP:=oDp:nFHK_LENENT+oDp:nFHK_LENDEC

//  https://github.com/AdaptaProERP/MAQUINA-FISCAL-THEFACTORY/blob/main/Ejemplo_Envio_Factura_Simple.cpp
//	LPCSTR PLU1 = " 000000001000001000Producto1";              //Información  de PLU: Tasa Exento  , cantidad 1, monto 0.10 bs, nombre del PLU
//	LPCSTR PLU2 = "!000000001000001000Producto2";              //Información  de PLU: Tasa General , cantidad 1, monto 0.10 bs, nombre del PLU
//	LPCSTR PLU3 = "\"000000001000001000Producto3";             //Información  de PLU: Tasa Reducida, cantidad 1, monto 0.10 bs, nombre del PLU
//	LPCSTR PLU4 = "#000000001000001000Producto4";              //Información  de PLU: Tasa Ampliada, cantidad 1, monto 0.10 bs, nombre del PLU
//	LPCSTR PLU5 = "$000000001000001000Producto5";              //Información  de PLU: Tasa Percibida, cantidad 1, monto 0.10 bs, nombre del PLU
	
   IF cTipDoc = "DEV" .OR. cTipDoc="CRE"

          // 14.3.	COMANDOS PARA GENERAR UNA NOTA DE CRÉDITO (DEVOLUCIÓN)
     AADD(aTipIva,{"EX","0"})
     AADD(aTipIva,{"GN","1"})
     AADD(aTipIva,{"RD","2"})
     AADD(aTipIva,{"S1","3"})

   ELSE

     // 14.1.	COMANDOS PARA EL REGISTRO DE UN ÍTEM EN UNA FACTURA

     AADD(aTipIva,{"EX",CHR(32)})
     AADD(aTipIva,{"GN","!"    })
     AADD(aTipIva,{"RD",["]    })
     AADD(aTipIva,{"S1","#"    })

   ENDIF

// ? nLenP,"longitud del campo"

   nLenC:=oDp:nImpFisEntCan
   nLenC:=IF(nLenC=0,8,nLenC)

// ? nLenP,"nLenP",nLenC,"nLenC"

   cWhere:="DOC_CODSUC"+GetWhere("=",cCodSuc)+" AND "+;
           "DOC_TIPDOC"+GetWhere("=",cTipDoc)+" AND "+;
           "DOC_NUMERO"+GetWhere("=",cNumero)+" AND "+;
           "DOC_ACT"   +GetWhere("=",1      )

   IF cOption="3"
      cWhere:=cWhere+" AND DOC_TIPTRA"+GetWhere("=","D"    )
   ENDIF

   IF Empty(cSerie)
      cSerie        :=SQLGET("DPDOCCLI","DOC_SERFIS",cWhere)
   ENDIF

   IF Empty(oDp:cImpFisCom)
      oDp:cImpFisCom:=SQLGET("DPSERIEFISCAL","SFI_PUERTO","SFI_LETRA"+GetWhere("=",cSerie))
   ENDIF

   FERASE("FACTURA.TXT") // ,cText)

   cSql:=" SELECT  MOV_CODIGO,INV_DESCRI,MOV_TOTAL,DOC_OTROS,DOC_DCTO,MOV_PRECIO,MOV_DESCUE,MOV_CANTID,MOV_IVA,MOV_TIPIVA,"+;
         " IF(CCG_NOMBRE IS NULL,CLI_NOMBRE,CCG_NOMBRE) AS CCG_NOMBRE,"+;
         " IF(CCG_DIR1   IS NULL,CLI_DIR1  ,CCG_DIR1  ) AS CCG_DIR1,"+;
         " IF(CCG_TEL1   IS NULL,CLI_TEL1  ,CCG_TEL1  ) AS CCG_TEL1,"+;
         " IF(CCG_RIF    IS NULL,CLI_RIF   ,CCG_RIF   ) AS CCG_RIF ,"+;
         " DOC_DCTO,DOC_DESCCO,DOC_SERFIS,DOC_ASODOC,MOV_LISTA,TPP_INCIVA,DOC_TIPAFE "+;
         " FROM DPDOCCLI "+;
         " INNER  JOIN DPMOVINV       ON MOV_CODSUC=DOC_CODSUC AND MOV_TIPDOC=DOC_TIPDOC AND DOC_NUMERO=MOV_DOCUME AND MOV_APLORG"+GetWhere("=","V")+;
         " INNER  JOIN DPINV          ON MOV_CODIGO=INV_CODIGO "+;
         " LEFT   JOIN DPCLIENTESCERO ON CCG_CODSUC=DOC_CODSUC AND CCG_TIPDOC=DOC_TIPDOC AND CCG_NUMDOC=DOC_NUMERO "+;
         " INNER  JOIN DPCLIENTES     ON DOC_CODIGO=CLI_CODIGO "+;
         " INNER  JOIN DPPRECIOTIP       ON MOV_LISTA=TPP_CODIGO "+;
         " WHERE DOC_CODSUC"+GetWhere("=",cCodSuc)+;
         "   AND DOC_TIPDOC"+GetWhere("=",cTipDoc)+;
         "   AND DOC_NUMERO"+GetWhere("=",cNumero)+;
         "   AND DOC_TIPTRA"+GetWhere("=","D"    )

// 13/07/2025
//   IF cOption="3"
//      cSql:=cSql+" AND DOC_TIPTRA"+GetWhere("=","D"    )
//   ENDIF

   IF Empty(cSql)
      RETURN ""
   ENDIF

   oTable:=OpenTable(cSql,.T.)

   oDp:aData:=ACLONE(oTable:aDataFill)

   IF oTable:RecCount()=0
      oTable:End()
      cText:=""
      RETURN 
   ENDIF

   oTable:GoTop()

   cUS        :=oDp:cUsuario
   cNombre    :=PADR(oTable:CCG_NOMBRE,20)
   cRIF       :=PADR(oTable:CCG_RIF   ,20)
   cDireccion :=PADR(oTable:CCG_DIR1  ,20)
   cTelefono  :=PADR(oTable:CCG_TEL1  ,20)

   IF cTipDoc = "DEV" .OR. cTipDoc="CRE" .OR. cTipDoc="DEB"

      // Factura Afectada
      // cWhereA:=" INNER JOIN dptipdocclinum ON TDN_CODSUC=DOC_CODSUC AND TDN_TIPDOC"+GetWhere("=",oTable:DOC_TIPAFE)+" AND TDN_SERFIS=DOC_SERFIS "+;

      cWhereA:=" INNER JOIN DPSERIEFISCAL  ON SFI_LETRA=DOC_SERFIS "+;
               " WHERE "+;
               " DOC_CODSUC"+GetWhere("=",cCodSuc          )+" AND "+;
               " DOC_TIPDOC"+GetWhere("=",oTable:DOC_TIPAFE)+" AND "+;
               " DOC_NUMERO"+GetWhere("=",oTable:DOC_ASODOC)+" AND "+;
               " DOC_TIPTRA"+GetWhere("=","D")           

      oFacAfe:=OpenTable("SELECT DOC_FECHA,SFI_SERIMP FROM DPDOCCLI "+cWhereA,.T.)
      oFacAfe:End()

      cText:=cText+CHR(105)+CHR(82)+CHR(42)+cRIF+CRLF
      cText:=cText+CHR(105)+CHR(83)+CHR(42)+cNombre+CRLF
//    cText:=cText+CHR(105)+CHR(70)+CHR(42)+cNumero+CRLF
      cText:=cText+CHR(105)+"F"    +CHR(42)+""+oTable:DOC_ASODOC+CRLF                    // FACTURA AFECTADA
      cText:=cText+CHR(105)+CHR(68)+CHR(42)+""+DTOC(oFacAfe:DOC_FECHA)+CRLF     // FECHA DE LA FACTURA
      cText:=cText+CHR(105)+CHR(73)+CHR(42)+""+oFacAfe:SFI_SERIMP+CRLF        // IMPRESORA FISCAL DONDE FUE REALIZADA LA FACTURA

      // "Z6C3000509"+CRLF
      // cText:=cText+CHR(105)+CHR(73)+CHR(42)+"Factura Origen:"+oTable:DOC_FACAFE+CRLF
      // cText:=cText+"<TEXTO_CF,"+REPL("-",40)+",0>"+CRLF

   ELSE

      cText:=cText+CHR(105)+CHR(83)+CHR(42)+cNombre+CRLF
      cText:=cText+CHR(105)+CHR(82)+CHR(42)+cRIF+CRLF

/*
      IF !Empty(oTable:DOC_DESCCO) .OR. !Empty(oTable:DOC_DCTO)

        IF !Empty(oTable:DOC_DESCCO)
          cDireccion:="%Bono: " + ALLTRIM(oTable:DOC_DESCCO)
        ELSE
          cDireccion:="%Bono: " + LSTR(oTable:DOC_DCTO)
        ENDIF

        cDireccion:=PADR(oTable:CCG_DIR1,20)

      ENDIF
*/

      cText:=cText+CHR(105)+CHR(48)+CHR(51)+"Dir. :"+cDireccion+CRLF
      cText:=cText+CHR(105)+CHR(48)+CHR(52)+"Tlf. :"+cTelefono+" Cajero: "+cUS+CRLF
      cText:=cText+CHR(105)+CHR(48)+CHR(53)+"Ref. :"+cNumero+CRLF

   ENDIF

   oTable:Gotop()

   WHILE !oTable:Eof()

     nIva     :=1+(oTable:MOV_IVA/100)
/*
     IF oDp:nImpFisEntCan=0
       cCant    :=STRZERO(oTable:MOV_CANTID*1000,8,0)
     ELSE
       cCant    :=STRZERO(oTable:MOV_CANTID*1000,nLenC,0)
     ENDIF
*/
     // Cantidad 8 con 3 decimales
     cCant    :=STRZERO(oTable:MOV_CANTID*1000,8,0)

     // Precio Incluye IVA, Debe separarlo

     // 28/11/2023 en todos los casos la impresora calcula el IVA y la cuenta viene directamente el formulario de facturacion
     IF oTable:TPP_INCIVA .AND. .F.
        nPrecio  :=(oTable:MOV_TOTAL/oTable:MOV_CANTID)/nIva 
     ELSE
        nPrecio  :=(oTable:MOV_TOTAL/oTable:MOV_CANTID)
     ENDIF

     nPorEnt  :=MAX(1,VAL("1"+REPLI("0",oDp:nFHK_LENDEC)))
     cPrecio  :=STRZERO(nPrecio*nPorEnt,oDp:nFHK_LENENT+oDp:nFHK_LENDEC)
//     cIva     :=IIF(oTable:MOV_IVA<>0,CHR(33),CHR(32))


     nAt      :=ASCAN(aTipIva,{|a,n|a[1]=oTable:MOV_TIPIVA})
     cIva     :=aTipIva[nAt,2]

//    ? nAt,oTable:MOV_TIPIVA,"oTable:MOV_TIPIVA",aTipIva[nAt,2],cIva

     cDescri  :=PADR(oTable:INV_DESCRI,40)

     IF cTipDoc = "DEV" .OR. cTipDoc="CRE" .OR. cTipDoc="DEB"

        IF cTipDoc="DEB"
          // ‘ = CHR(145)
          cText    :=cText+CHR(145)+cIva+cPrecio+cCant+cDescri+CRLF
        ELSE
          cText    :=cText+"d"+cIva+cPrecio+cCant+cDescri+CRLF
        ENDIF

     ELSE

        cText    :=cText+cIva+cPrecio+cCant+cDescri+CRLF

     ENDIF

     oTable:DbSkip()

  ENDDO

  oTable:Gotop()

  // Cierre de los Items
  // Antes era "3" ahora es cOption
  // cOption con valor "7" es Anular Ticket
  cText:=cText+cOption+CRLF

  // Pagos
  IF cOption="3"

    aPagos:=EJECUTAR("TFHKA_PAGOS",cCodSuc,cTipDoc,cNumero)

ViewArray(aPagos)

    AEVAL(aPagos,{|cLine| cText:=cText+cLine+CRLF })

    // Cerrar el Documento, solo para impresoras con IGTF
    // IF cOption="3"
    // 02/07/2024, 199 sólo aplica a contribuyente especial, depende del flag 
    // Estos se habilitan siempre y cuando tenga el flag 50 en 01, adicional al tenerlo configurado 
    // de esta manera para el cierre de cualquier documento es necesario enviar el comando 199

    IF oDp:lConEsp 
       // LEFT(oDp:cTipCon,1)="E"
       cText:=cText+"199"+CRLF
    ENDIF

  ENDIF

  DPWRITE("thefactory\FACTURA.TXT",cText)

RETURN cText
// EOF

