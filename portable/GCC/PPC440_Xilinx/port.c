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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Library includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "xtime_l.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xintc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_ਰੁਕਾਵਟ_ENABLE    ( 1UL << 17UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXTERNAL_ਰੁਕਾਵਟ_ENABLE    ( 1UL << 15UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#ਜੇ configUSE_FPU == 1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APU_PRESENT              ( 1UL << 25UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FCM_FPU_PRESENT          ( 1UL << 13UL )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APU_PRESENT              ( 0UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FCM_FPU_PRESENT          ( 0UL )
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_MSR                  ( ਪੋਰਟ_CRITICAL_ਰੁਕਾਵਟ_ENABLE | ਪੋਰਟ_EXTERNAL_ਰੁਕਾਵਟ_ENABLE | ਪੋਰਟ_MACHINE_CHECK_ENABLE | ਪੋਰਟ_APU_PRESENT | ਪੋਰਟ_FCM_FPU_PRESENT )


ਬਾਹਰੀ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ SDA_ਅਧਾਰ;
ਬਾਹਰੀ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ SDA2_ਅਧਾਰ;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Tick_ISR( ਖਾਲੀ );

/*
 * The handler for the yield function - defined in portasm.s.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ਸਥਿਰ XIntc x_ਰੁਕਾਵਟ_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xDEADBEEF;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* EABI stack frame. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) &SDA_ਅਧਾਰ; /* address of the first small data area */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 10;

    /* Parameters in R3. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Parameters in R2. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) &SDA2_ਅਧਾਰ; /* address of the second small data area */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R1 is the stack pointer so is omitted. */

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x10000001UL;                      /* R0. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00000000UL;                      /* USPRG0. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00000000UL;                      /* CR. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00000000UL;                      /* XER. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00000000UL;                      /* CTR. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) v_ਪੋਰਟ_ਸਿਰਾ_Scheduler; /* LR. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;            /* SRR0. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_MSR;                   /* SRR1. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) v_ਪੋਰਟ_ਸਿਰਾ_Scheduler; /* Next LR. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00000000UL;                      /* Backchain. */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();
    XExc_ਰਜਿਸਟਰ_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_ਪੋਰਟ_Yield, ( ਖਾਲੀ * ) 0 );
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here as the tasks are now running! */
    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented. */
    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    ਅਚਲ uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1UL );

    XTime_DECClear_ਰੁਕਾਵਟ();
    XTime_FITClear_ਰੁਕਾਵਟ();
    XTime_WDTClear_ਰੁਕਾਵਟ();
    XTime_WDTDisable_ਰੁਕਾਵਟ();
    XTime_FITDisable_ਰੁਕਾਵਟ();

    XExc_ਰਜਿਸਟਰ_Handler( XEXC_ID_DEC_INT, ( XExceptionHandler ) v_ਪੋਰਟ_Tick_ISR, ( ਖਾਲੀ * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnable_ਰੁਕਾਵਟ();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ISRHandler( ਖਾਲੀ * pvNullDoNotUse )
{
    uint32_t ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ, ul_ਰੁਕਾਵਟ_ਨਕਾਬ = 1UL;
    ਅਧਾਰ_Type_t x_ਰੁਕਾਵਟ_ਸੰਖਿਆ;
    XIntc_Config * px_ਰੁਕਾਵਟ_Controller;
    XIntc_ਸਦਿਸ਼_ਸਾਰਣੀ_ਇੰਦਰਾਜ * px_ਸਾਰਣੀ;

    /* Just to remove compiler warning. */
    ( ਖਾਲੀ ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_ਰੁਕਾਵਟ_Controller = &XIntc_Config_ਸਾਰਣੀ[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ = XIntc_m_Get_Intr_ਸਥਿਤੀ( px_ਰੁਕਾਵਟ_Controller->ਅਧਾਰ_ਪਤਾ );

    ਲਈ( x_ਰੁਕਾਵਟ_ਸੰਖਿਆ = 0; x_ਰੁਕਾਵਟ_ਸੰਖਿਆ < XPAR_INTC_MAX_ਅੰਕ_INTR_INPUTS; x_ਰੁਕਾਵਟ_ਸੰਖਿਆ++ )
    {
        ਜੇ( ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_ਰੁਕਾਵਟ_Controller->ਅਧਾਰ_ਪਤਾ, ul_ਰੁਕਾਵਟ_ਨਕਾਬ );

            /* Call the registered handler. */
            px_ਸਾਰਣੀ = &( px_ਰੁਕਾਵਟ_Controller->Handler_ਸਾਰਣੀ[ x_ਰੁਕਾਵਟ_ਸੰਖਿਆ ] );
            px_ਸਾਰਣੀ->Handler( px_ਸਾਰਣੀ->Call_ਪਿੱਠ_Ref );
        }

        /* Check the next interrupt. */
        ul_ਰੁਕਾਵਟ_ਨਕਾਬ <<= 0x01UL;
        ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ >>= 0x01UL;

        /* Have we serviced all interrupts? */
        ਜੇ( ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ == 0UL )
        {
            ਰੋਕੋ;
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_ਰੁਕਾਵਟ_Controller( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ISRWrapper( ਖਾਲੀ );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_ਰਜਿਸਟਰ_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_ਪੋਰਟ_ISRWrapper, ਨਿਰਾ );
    XIntc_Initialize( &x_ਰੁਕਾਵਟ_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_ਸ਼ੁਰੂ( &x_ਰੁਕਾਵਟ_Controller, XIN_REAL_ਬਹੁਲਕ );
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Install_ਰੁਕਾਵਟ_Handler( uint8_t uc_ਰੁਕਾਵਟ_ID,
                                         XInterruptHandler pxHandler,
                                         ਖਾਲੀ * pv_Call_ਪਿੱਠ_Ref )
{
    ਅਧਾਰ_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    ਜੇ( XST_SUCCESS == XIntc_Connect( &x_ਰੁਕਾਵਟ_Controller, uc_ਰੁਕਾਵਟ_ID, pxHandler, pv_Call_ਪਿੱਠ_Ref ) )
    {
        XIntc_Enable( &x_ਰੁਕਾਵਟ_Controller, uc_ਰੁਕਾਵਟ_ID );
        xReturn = pdPASS;
    }

    ਵਾਪਸ xReturn;
}
