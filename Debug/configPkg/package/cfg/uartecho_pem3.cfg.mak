# invoke SourceDir generated makefile for uartecho.pem3
uartecho.pem3: .libraries,uartecho.pem3
.libraries,uartecho.pem3: package/cfg/uartecho_pem3.xdl
	$(MAKE) -f C:\Users\embedded\ti\Tx_460/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\embedded\ti\Tx_460/src/makefile.libs clean

