/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/Power.h>
/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/rf/RF.h>

/* Example/Board Header files */
#include "Board.h"
#include "smartrf_settings/smartrf_settings.h"

#include <stdint.h>

#define TASKSTACKSIZE     768

/***** Defines *****/
#define CW_TASK_STACK_SIZE 1024
#define CW_TASK_PRIORITY   2

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

Task_Struct cwTask;    /* not static so you can see in ROV */
static Task_Params cwTaskParams;
static uint8_t cwTaskStack[CW_TASK_STACK_SIZE];

static RF_Object rfObject;
static RF_Handle rfHandle;

PIN_Handle ledPinHandle;
Task_Params taskParams;
UART_Handle uart;
UART_Params uartParams;

/* Global memory storage for a PIN_Config table */
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config ledPinTable[] = {
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};



void Delayms (int xms) {

    int i, j;
    for (i = xms; i>0; i--) {
        for (j = 587; j>0; j--);
    }

}

/***** Function definitions *****/

static void cwTaskFunction(UArg arg0, UArg arg1)
{
    /* Configure the radio for Proprietary mode */
    RF_Params rfParams;
    RF_Params_init(&rfParams);

    /* Explicitly configure CW (1) or Modulated (0). Default modulated mode is PRBS-15. */
    RF_cmdTxTest.config.bUseCw = 1;

    /* In order to achieve +14dBm output power, make sure .txPower = 0xa73f, and
    that the define CCFG_FORCE_VDDR_HH = 0x1 in ccfg.c */

    /* Request access to the radio */
    rfHandle = RF_open(&rfObject, &RF_prop, (RF_RadioSetup*)&RF_cmdPropRadioDivSetup, &rfParams);

    RF_postCmd(rfHandle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);

    /* Enter RX mode and stay forever in RX */

    RF_CmdHandle rx_cmd = RF_postCmd(rfHandle, (RF_Op*)&RF_cmdPropRx, RF_PriorityNormal, NULL, IRQ_RX_ENTRY_DONE);

    Delayms(100000); /* Wait for x/3 cycles*/

    RF_cancelCmd(rfHandle, rx_cmd, 0);  /* Abort the RF rx_cmd */
    /* Send CMD_FS and wait until it has completed */
//    RF_runCmd(rfHandle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);
//
//
//    /* Send CMD_TX_TEST which sends forever */
//    RF_runCmd(rfHandle, (RF_Op*)&RF_cmdTxTest, RF_PriorityNormal, NULL, 0);
//    RF_cancelCmd(rfHandle, rx_cmd, 0);

    /* Should never come here */
    PIN_setOutputValue(ledPinHandle, Board_LED1, 1);//!PIN_getOutputValue(Board_LED2));
    Task_exit();
    PIN_setOutputValue(ledPinHandle, Board_LED2, 0);
    //while (1);
}

void CwTask_init(void) {
    Task_Params_init(&cwTaskParams);
    cwTaskParams.stackSize = CW_TASK_STACK_SIZE;
    cwTaskParams.priority = CW_TASK_PRIORITY;
    cwTaskParams.stack = &cwTaskStack;

    Task_construct(&cwTask, cwTaskFunction, &cwTaskParams, NULL);
}



/*
 *  ======== echoFxn ========
 *  Task for this function is created statically. See the project's .cfg file.
 */
Void echoFxn(UArg arg0, UArg arg1)
{
    //PIN_Handle ledPinHandle;

    bool input;
    //int input;

    //const char echoPrompt[] = "\fEchoing characters:\r\n";

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uartParams.readTimeout = 10000;
    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        System_abort("Error opening the UART");
    }

    //ledPinHandle = PIN_open(&ledPinState, ledPinTable);
//    if(!ledPinHandle) {
//       System_abort("1Error initializing board LED pins\n");
//    }

    //UART_write(uart, echoPrompt, sizeof(echoPrompt));
    System_printf("Test\n");
    System_flush();

    /* Loop forever echoing */
    while (1) {

        UART_read(uart, &input, sizeof(input));
        System_printf("%d\n", input);
        System_flush();

        CwTask_init();

        Delayms(1000);

    }
}

/*
 *  ======== main ========
 */
int main(void)
{



    /* Call board init functions */
    Board_initGeneral();
    Board_initUART();

    /* Construct BIOS objects */
    Task_Params_init(&taskParams);
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)echoFxn, &taskParams, NULL);

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
//    if(!ledPinHandle) {
//        System_abort("2Error initializing board LED pins\n");
//    }

    //PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));

    /* This example has logging and many other debug capabilities enabled */
    System_printf("This example does not attempt to minimize code or data "
                  "footprint\n");
    System_flush();

    System_printf("Starting the UART Echo example\nSystem provider is set to "
                  "SysMin. Halt the target to view any SysMin contents in "
                  "ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();
    //System_printf("2s\n");
    //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
    /* Start BIOS */
    BIOS_start();

    return (0);
}
