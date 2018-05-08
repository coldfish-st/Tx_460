################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CC2650_LAUNCHXL.obj: ../CC2650_LAUNCHXL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/embedded/ti/Tx_460" --include_path="C:/Users/embedded/ti/Tx_460" --include_path="C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272" --include_path="D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="CC2650_LAUNCHXL.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ccfg.obj: ../ccfg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/embedded/ti/Tx_460" --include_path="C:/Users/embedded/ti/Tx_460" --include_path="C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272" --include_path="D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="ccfg.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uartecho.obj: ../uartecho.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/embedded/ti/Tx_460" --include_path="C:/Users/embedded/ti/Tx_460" --include_path="C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272" --include_path="D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="uartecho.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1751515407:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1751515407-inproc

build-1751515407-inproc: ../uartecho.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/packages;C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;D:/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC2650F128 -r release -c "D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS" --compileOptions "-mv7M3 --code_state=16 --float_support=vfplib -me --include_path=\"C:/Users/embedded/ti/Tx_460\" --include_path=\"C:/Users/embedded/ti/Tx_460\" --include_path=\"C:/TI/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272\" --include_path=\"D:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include\" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1751515407 ../uartecho.cfg
configPkg/compiler.opt: build-1751515407
configPkg/: build-1751515407


