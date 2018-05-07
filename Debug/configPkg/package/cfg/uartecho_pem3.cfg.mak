# invoke SourceDir generated makefile for uartecho.pem3
uartecho.pem3: .libraries,uartecho.pem3
.libraries,uartecho.pem3: package/cfg/uartecho_pem3.xdl
	$(MAKE) -f C:\Users\Zhenge\workspace_v7\wisp5\CCS\uartecho_CC2650_LAUNCHXL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Zhenge\workspace_v7\wisp5\CCS\uartecho_CC2650_LAUNCHXL_TI/src/makefile.libs clean

