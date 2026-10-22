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
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Library includes. */
#অন্তর্ভাব "xtime_l.h"
#অন্তর্ভাব "xintc.h"
#অন্তর্ভাব "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#define portCRITICAL_INTERRUPT_ENABLE    ( 1UL << 17UL )
#define portEXTERNAL_INTERRUPT_ENABLE    ( 1UL << 15UL )
#define portMACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#যদি configUSE_FPU == 1
    #define portAPU_PRESENT              ( 1UL << 25UL )
    #define portFCM_FPU_PRESENT          ( 1UL << 13UL )
#অন্যথা
    #define portAPU_PRESENT              ( 0UL )
    #define portFCM_FPU_PRESENT          ( 0UL )
#endif

#define portINITIAL_MSR                  ( portCRITICAL_INTERRUPT_ENABLE | portEXTERNAL_INTERRUPT_ENABLE | portMACHINE_CHECK_ENABLE | portAPU_PRESENT | portFCM_FPU_PRESENT )


বাহ্যিক ধ্রুবক unsigned _SDA_BASE_;
বাহ্যিক ধ্রুবক unsigned _SDA2_BASE_;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
স্থির শূন্য prvSetupTimerInterrupt( শূন্য );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
বাহ্যিক শূন্য vPortTickISR( শূন্য );

/*
 * The handler for the yield function - defined in portasm.s.
 */
বাহ্যিক শূন্য vPortYield( শূন্য );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
বাহ্যিক শূন্য vPortStartFirstTask( শূন্য );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
স্থির XIntc xInterruptController;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_শীর্ষ_Of_স্তূপ = 0xDEADBEEF;
    px_শীর্ষ_Of_স্তূপ--;

    /* EABI stack frame. */
    px_শীর্ষ_Of_স্তূপ -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) &_SDA_BASE_; /* address of the first small data area */
    px_শীর্ষ_Of_স্তূপ -= 10;

    /* Parameters in R3. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters;
    px_শীর্ষ_Of_স্তূপ--;

    /* Parameters in R2. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) &_SDA2_BASE_; /* address of the second small data area */
    px_শীর্ষ_Of_স্তূপ--;

    /* R1 is the stack pointer so is omitted. */

    *px_শীর্ষ_Of_স্তূপ = 0x10000001UL;                      /* R0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x00000000UL;                      /* USPRG0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x00000000UL;                      /* CR. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x00000000UL;                      /* XER. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x00000000UL;                      /* CTR. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) vPortEndScheduler; /* LR. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxCode;            /* SRR0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_MSR;                   /* SRR1. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) vPortEndScheduler; /* Next LR. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x00000000UL;                      /* Backchain. */

    ফেরত px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    prvSetupTimerInterrupt();
    XExc_RegisterHandler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) vPortYield, ( শূন্য * ) 0 );
    vPortStartFirstTask();

    /* Should not get here as the tasks are now running! */
    ফেরত pdFALSE;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented. */
    জন্য( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
স্থির শূন্য prvSetupTimerInterrupt( শূন্য )
{
    ধ্রুবক uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL );

    XTime_DECClearInterrupt();
    XTime_FITClearInterrupt();
    XTime_WDTClearInterrupt();
    XTime_WDTDisableInterrupt();
    XTime_FITDisableInterrupt();

    XExc_RegisterHandler( XEXC_ID_DEC_INT, ( XExceptionHandler ) vPortTickISR, ( শূন্য * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnableInterrupt();
}
/*-----------------------------------------------------------*/

শূন্য vPortISRHandler( শূন্য * pvNullDoNotUse )
{
    uint32_t ulInterruptStatus, ulInterruptMask = 1UL;
    BaseType_t x_Interrupt_সংখ্যা;
    XIntc_Config * pxInterruptController;
    XIntc_VectorTableEntry * pxTable;

    /* Just to remove compiler warning. */
    ( শূন্য ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    pxInterruptController = &XIntc_ConfigTable[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ulInterruptStatus = XIntc_mGetIntrStatus( pxInterruptController->BaseAddress );

    জন্য( x_Interrupt_সংখ্যা = 0; x_Interrupt_সংখ্যা < XPAR_INTC_MAX_অঙ্ক_INTR_INPUTS; x_Interrupt_সংখ্যা++ )
    {
        যদি( ulInterruptStatus & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( pxInterruptController->BaseAddress, ulInterruptMask );

            /* Call the registered handler. */
            pxTable = &( pxInterruptController->HandlerTable[ x_Interrupt_সংখ্যা ] );
            pxTable->Handler( pxTable->CallBackRef );
        }

        /* Check the next interrupt. */
        ulInterruptMask <<= 0x01UL;
        ulInterruptStatus >>= 0x01UL;

        /* Have we serviced all interrupts? */
        যদি( ulInterruptStatus == 0UL )
        {
            বিরতি;
        }
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortSetupInterruptController( শূন্য )
{
    বাহ্যিক শূন্য vPortISRWrapper( শূন্য );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_RegisterHandler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) vPortISRWrapper, ফাঁকা );
    XIntc_Initialize( &xInterruptController, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_Start( &xInterruptController, XIN_REAL_MODE );
}
/*-----------------------------------------------------------*/

BaseType_t xPortInstallInterruptHandler( uint8_t ucInterruptID,
                                         XInterruptHandler pxHandler,
                                         শূন্য * pvCallBackRef )
{
    BaseType_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    যদি( XST_SUCCESS == XIntc_Connect( &xInterruptController, ucInterruptID, pxHandler, pvCallBackRef ) )
    {
        XIntc_Enable( &xInterruptController, ucInterruptID );
        xReturn = pdPASS;
    }

    ফেরত xReturn;
}
