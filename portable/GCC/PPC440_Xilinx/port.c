/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the PPC440 port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/* Library includes. */
#അന്തര്ഭാവ "xtime_l.h"
#അന്തര്ഭാവ "xintc.h"
#അന്തര്ഭാവ "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#define portCRITICAL_INTERRUPT_ENABLE    ( 1UL << 17UL )
#define portEXTERNAL_INTERRUPT_ENABLE    ( 1UL << 15UL )
#define portMACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#എങ്കിൽ configUSE_FPU == 1
    #define portAPU_PRESENT              ( 1UL << 25UL )
    #define portFCM_FPU_PRESENT          ( 1UL << 13UL )
#അല്ലെങ്കിൽ
    #define portAPU_PRESENT              ( 0UL )
    #define portFCM_FPU_PRESENT          ( 0UL )
#endif

#define portINITIAL_MSR                  ( portCRITICAL_INTERRUPT_ENABLE | portEXTERNAL_INTERRUPT_ENABLE | portMACHINE_CHECK_ENABLE | portAPU_PRESENT | portFCM_FPU_PRESENT )


ബാഹ്യ സ്ഥിരം unsigned _SDA_BASE_;
ബാഹ്യ സ്ഥിരം unsigned _SDA2_BASE_;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
ബാഹ്യ ശൂന്യം vPortTickISR( ശൂന്യം );

/*
 * The handler for the yield function - defined in portasm.s.
 */
ബാഹ്യ ശൂന്യം vPortYield( ശൂന്യം );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
ബാഹ്യ ശൂന്യം vPortStartFirstTask( ശൂന്യം );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
സ്ഥിതം XIntc xInterruptController;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_മുകൾ_Of_അട്ടി = 0xDEADBEEF;
    px_മുകൾ_Of_അട്ടി--;

    /* EABI stack frame. */
    px_മുകൾ_Of_അട്ടി -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) &_SDA_BASE_; /* address of the first small data area */
    px_മുകൾ_Of_അട്ടി -= 10;

    /* Parameters in R3. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters;
    px_മുകൾ_Of_അട്ടി--;

    /* Parameters in R2. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) &_SDA2_BASE_; /* address of the second small data area */
    px_മുകൾ_Of_അട്ടി--;

    /* R1 is the stack pointer so is omitted. */

    *px_മുകൾ_Of_അട്ടി = 0x10000001UL;                      /* R0. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x00000000UL;                      /* USPRG0. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x00000000UL;                      /* CR. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x00000000UL;                      /* XER. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x00000000UL;                      /* CTR. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) vPortEndScheduler; /* LR. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode;            /* SRR0. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = portINITIAL_MSR;                   /* SRR1. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) vPortEndScheduler; /* Next LR. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = 0x00000000UL;                      /* Backchain. */

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    prvSetupTimerInterrupt();
    XExc_RegisterHandler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) vPortYield, ( ശൂന്യം * ) 0 );
    vPortStartFirstTask();

    /* Should not get here as the tasks are now running! */
    തിരികെ pdFALSE;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* Not implemented. */
    വേണ്ടി( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം )
{
    സ്ഥിരം uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL );

    XTime_DECClearInterrupt();
    XTime_FITClearInterrupt();
    XTime_WDTClearInterrupt();
    XTime_WDTDisableInterrupt();
    XTime_FITDisableInterrupt();

    XExc_RegisterHandler( XEXC_ID_DEC_INT, ( XExceptionHandler ) vPortTickISR, ( ശൂന്യം * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnableInterrupt();
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortISRHandler( ശൂന്യം * pvNullDoNotUse )
{
    uint32_t ulInterruptStatus, ulInterruptMask = 1UL;
    BaseType_t x_Interrupt_സംഖ്യ;
    XIntc_Config * pxInterruptController;
    XIntc_VectorTableEntry * pxTable;

    /* Just to remove compiler warning. */
    ( ശൂന്യം ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    pxInterruptController = &XIntc_ConfigTable[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ulInterruptStatus = XIntc_mGetIntrStatus( pxInterruptController->BaseAddress );

    വേണ്ടി( x_Interrupt_സംഖ്യ = 0; x_Interrupt_സംഖ്യ < XPAR_INTC_MAX_അക്കം_INTR_INPUTS; x_Interrupt_സംഖ്യ++ )
    {
        എങ്കിൽ( ulInterruptStatus & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( pxInterruptController->BaseAddress, ulInterruptMask );

            /* Call the registered handler. */
            pxTable = &( pxInterruptController->HandlerTable[ x_Interrupt_സംഖ്യ ] );
            pxTable->Handler( pxTable->CallBackRef );
        }

        /* Check the next interrupt. */
        ulInterruptMask <<= 0x01UL;
        ulInterruptStatus >>= 0x01UL;

        /* Have we serviced all interrupts? */
        എങ്കിൽ( ulInterruptStatus == 0UL )
        {
            നിർത്തുക;
        }
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortSetupInterruptController( ശൂന്യം )
{
    ബാഹ്യ ശൂന്യം vPortISRWrapper( ശൂന്യം );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_RegisterHandler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) vPortISRWrapper, ശൂന്യ );
    XIntc_Initialize( &xInterruptController, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_Start( &xInterruptController, XIN_REAL_MODE );
}
/*-----------------------------------------------------------*/

BaseType_t xPortInstallInterruptHandler( uint8_t ucInterruptID,
                                         XInterruptHandler pxHandler,
                                         ശൂന്യം * pvCallBackRef )
{
    BaseType_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    എങ്കിൽ( XST_SUCCESS == XIntc_Connect( &xInterruptController, ucInterruptID, pxHandler, pvCallBackRef ) )
    {
        XIntc_Enable( &xInterruptController, ucInterruptID );
        xReturn = pdPASS;
    }

    തിരികെ xReturn;
}
