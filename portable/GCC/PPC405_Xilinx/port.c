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
* Implementation of functions defined in portable.h for the PPC405 port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Library includes. */
#شامل "xtime_l.h"
#شامل "xintc.h"
#شامل "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#define portCRITICAL_INTERRUPT_ENABLE    ( 1UL << 17UL )
#define portEXTERNAL_INTERRUPT_ENABLE    ( 1UL << 15UL )
#define portMACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#اگر configUSE_FPU == 1
    #define portAPU_PRESENT              ( 1UL << 25UL )
    #define portFCM_FPU_PRESENT          ( 1UL << 13UL )
#وگرنه
    #define portAPU_PRESENT              ( 0UL )
    #define portFCM_FPU_PRESENT          ( 0UL )
#endif

#define portINITIAL_MSR                  ( portCRITICAL_INTERRUPT_ENABLE | portEXTERNAL_INTERRUPT_ENABLE | portMACHINE_CHECK_ENABLE | portAPU_PRESENT | portFCM_FPU_PRESENT )


بیرونی ثابت unsigned _SDA_BASE_;
بیرونی ثابت unsigned _SDA2_BASE_;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ایستا تهی prvSetupTimerInterrupt( تهی );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
بیرونی تهی vPortTickISR( تهی );

/*
 * The handler for the yield function - defined in portasm.s.
 */
بیرونی تهی vPortYield( تهی );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
بیرونی تهی vPortStartFirstTask( تهی );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ایستا XIntc xInterruptController;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
پشته_Type_t * px_Port_Initialise_پشته( پشته_Type_t * px_بالاترین_Of_پشته,
                                     TaskFunction_t pxCode,
                                     تهی * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_بالاترین_Of_پشته = 0xDEADBEEF;
    px_بالاترین_Of_پشته--;

    /* EABI stack frame. */
    px_بالاترین_Of_پشته -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) &_SDA_BASE_; /* address of the first small data area */
    px_بالاترین_Of_پشته -= 10;

    /* Parameters in R3. */
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) pvParameters;
    px_بالاترین_Of_پشته--;

    /* Parameters in R2. */
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) &_SDA2_BASE_; /* address of the second small data area */
    px_بالاترین_Of_پشته--;

    /* R1 is the stack pointer so is omitted. */

    *px_بالاترین_Of_پشته = 0x10000001UL;                      /* R0. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x00000000UL;                      /* USPRG0. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x00000000UL;                      /* CR. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x00000000UL;                      /* XER. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x00000000UL;                      /* CTR. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) vPortEndScheduler; /* LR. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) pxCode;            /* SRR0. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = portINITIAL_MSR;                   /* SRR1. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) vPortEndScheduler; /* Next LR. */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x00000000UL;                      /* Backchain. */

    بازگشت px_بالاترین_Of_پشته;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( تهی )
{
    prvSetupTimerInterrupt();
    XExc_RegisterHandler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) vPortYield, ( تهی * ) 0 );
    vPortStartFirstTask();

    /* Should not get here as the tasks are now running! */
    بازگشت pdFALSE;
}
/*-----------------------------------------------------------*/

تهی vPortEndScheduler( تهی )
{
    /* Not implemented. */
    برای( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ایستا تهی prvSetupTimerInterrupt( تهی )
{
    ثابت uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL );

    XTime_PITClearInterrupt();
    XTime_FITClearInterrupt();
    XTime_WDTClearInterrupt();
    XTime_WDTDisableInterrupt();
    XTime_FITDisableInterrupt();

    XExc_RegisterHandler( XEXC_ID_PIT_INT, ( XExceptionHandler ) vPortTickISR, ( تهی * ) 0 );

    XTime_PITEnableAutoReload();
    XTime_PITSetInterval( ulInterval );
    XTime_PITEnableInterrupt();
}
/*-----------------------------------------------------------*/

تهی vPortISRHandler( تهی * pvNullDoNotUse )
{
    uint32_t ulInterruptStatus, ulInterruptMask = 1UL;
    BaseType_t x_Interrupt_عدد;
    XIntc_Config * pxInterruptController;
    XIntc_VectorTableEntry * pxTable;

    /* Just to remove compiler warning. */
    ( تهی ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    pxInterruptController = &XIntc_ConfigTable[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ulInterruptStatus = XIntc_mGetIntrStatus( pxInterruptController->BaseAddress );

    برای( x_Interrupt_عدد = 0; x_Interrupt_عدد < XPAR_INTC_MAX_رقم_INTR_INPUTS; x_Interrupt_عدد++ )
    {
        اگر( ulInterruptStatus & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( pxInterruptController->BaseAddress, ulInterruptMask );

            /* Call the registered handler. */
            pxTable = &( pxInterruptController->HandlerTable[ x_Interrupt_عدد ] );
            pxTable->Handler( pxTable->CallBackRef );
        }

        /* Check the next interrupt. */
        ulInterruptMask <<= 0x01UL;
        ulInterruptStatus >>= 0x01UL;

        /* Have we serviced all interrupts? */
        اگر( ulInterruptStatus == 0UL )
        {
            بشکن;
        }
    }
}
/*-----------------------------------------------------------*/

تهی vPortSetupInterruptController( تهی )
{
    بیرونی تهی vPortISRWrapper( تهی );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_RegisterHandler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) vPortISRWrapper, پوچ );
    XIntc_Initialize( &xInterruptController, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_Start( &xInterruptController, XIN_REAL_MODE );
}
/*-----------------------------------------------------------*/

BaseType_t xPortInstallInterruptHandler( uint8_t ucInterruptID,
                                         XInterruptHandler pxHandler,
                                         تهی * pvCallBackRef )
{
    BaseType_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    اگر( XST_SUCCESS == XIntc_Connect( &xInterruptController, ucInterruptID, pxHandler, pvCallBackRef ) )
    {
        XIntc_Enable( &xInterruptController, ucInterruptID );
        xReturn = pdPASS;
    }

    بازگشت xReturn;
}
