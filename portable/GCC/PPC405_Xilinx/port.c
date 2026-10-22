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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Library includes. */
#ಅನ್ತರ್ಭಾವ "xtime_l.h"
#ಅನ್ತರ್ಭಾವ "xintc.h"
#ಅನ್ತರ್ಭಾವ "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_ಅಡಚಣೆ_ENABLE    ( 1UL << 17UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXTERNAL_ಅಡಚಣೆ_ENABLE    ( 1UL << 15UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#ಆದರೆ configUSE_FPU == 1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APU_PRESENT              ( 1UL << 25UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FCM_FPU_PRESENT          ( 1UL << 13UL )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APU_PRESENT              ( 0UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FCM_FPU_PRESENT          ( 0UL )
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_MSR                  ( ಪೋರ್ಟ್_CRITICAL_ಅಡಚಣೆ_ENABLE | ಪೋರ್ಟ್_EXTERNAL_ಅಡಚಣೆ_ENABLE | ಪೋರ್ಟ್_MACHINE_CHECK_ENABLE | ಪೋರ್ಟ್_APU_PRESENT | ಪೋರ್ಟ್_FCM_FPU_PRESENT )


ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ SDA_ತಳ;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ SDA2_ತಳ;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ );

/*
 * The handler for the yield function - defined in portasm.s.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ಸ್ಥಿರ XIntc x_ಅಡಚಣೆ_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 0xDEADBEEF;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* EABI stack frame. */
    px_ತುದಿ_ದ_ರಾಶಿ -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) &SDA_ತಳ; /* address of the first small data area */
    px_ತುದಿ_ದ_ರಾಶಿ -= 10;

    /* Parameters in R3. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Parameters in R2. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) &SDA2_ತಳ; /* address of the second small data area */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R1 is the stack pointer so is omitted. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x10000001UL;                      /* R0. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00000000UL;                      /* USPRG0. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00000000UL;                      /* CR. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00000000UL;                      /* XER. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00000000UL;                      /* CTR. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler; /* LR. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;            /* SRR0. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_MSR;                   /* SRR1. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler; /* Next LR. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00000000UL;                      /* Backchain. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();
    XExc_ರಿಜಿಸ್ಟರ್_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_ಪೋರ್ಟ್_Yield, ( ಶೂನ್ಯ * ) 0 );
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here as the tasks are now running! */
    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented. */
    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    ಸ್ಥಿರಾಂಕ uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL );

    XTime_PITClear_ಅಡಚಣೆ();
    XTime_FITClear_ಅಡಚಣೆ();
    XTime_WDTClear_ಅಡಚಣೆ();
    XTime_WDTDisable_ಅಡಚಣೆ();
    XTime_FITDisable_ಅಡಚಣೆ();

    XExc_ರಿಜಿಸ್ಟರ್_Handler( XEXC_ID_PIT_INT, ( XExceptionHandler ) v_ಪೋರ್ಟ್_Tick_ISR, ( ಶೂನ್ಯ * ) 0 );

    XTime_PITEnableAutoReload();
    XTime_PITSetInterval( ulInterval );
    XTime_PITEnable_ಅಡಚಣೆ();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ISRHandler( ಶೂನ್ಯ * pvNullDoNotUse )
{
    uint32_t ul_ಅಡಚಣೆ_ಸ್ಥಿತಿ, ul_ಅಡಚಣೆ_ಮುಖವಾಡ = 1UL;
    ತಳ_Type_t x_ಅಡಚಣೆ_ಸಂಖ್ಯೆ;
    XIntc_Config * px_ಅಡಚಣೆ_Controller;
    XIntc_ಸದಿಶ_ಕೋಷ್ಟಕ_ನಮೂದು * px_ಕೋಷ್ಟಕ;

    /* Just to remove compiler warning. */
    ( ಶೂನ್ಯ ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_ಅಡಚಣೆ_Controller = &XIntc_Config_ಕೋಷ್ಟಕ[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_ಅಡಚಣೆ_ಸ್ಥಿತಿ = XIntc_m_Get_Intr_ಸ್ಥಿತಿ( px_ಅಡಚಣೆ_Controller->ತಳ_ವಿಳಾಸ );

    ಗಾಗಿ( x_ಅಡಚಣೆ_ಸಂಖ್ಯೆ = 0; x_ಅಡಚಣೆ_ಸಂಖ್ಯೆ < XPAR_INTC_MAX_ಅಂಕೆ_INTR_INPUTS; x_ಅಡಚಣೆ_ಸಂಖ್ಯೆ++ )
    {
        ಆದರೆ( ul_ಅಡಚಣೆ_ಸ್ಥಿತಿ & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_ಅಡಚಣೆ_Controller->ತಳ_ವಿಳಾಸ, ul_ಅಡಚಣೆ_ಮುಖವಾಡ );

            /* Call the registered handler. */
            px_ಕೋಷ್ಟಕ = &( px_ಅಡಚಣೆ_Controller->Handler_ಕೋಷ್ಟಕ[ x_ಅಡಚಣೆ_ಸಂಖ್ಯೆ ] );
            px_ಕೋಷ್ಟಕ->Handler( px_ಕೋಷ್ಟಕ->Call_ಹಿಂಭಾಗ_Ref );
        }

        /* Check the next interrupt. */
        ul_ಅಡಚಣೆ_ಮುಖವಾಡ <<= 0x01UL;
        ul_ಅಡಚಣೆ_ಸ್ಥಿತಿ >>= 0x01UL;

        /* Have we serviced all interrupts? */
        ಆದರೆ( ul_ಅಡಚಣೆ_ಸ್ಥಿತಿ == 0UL )
        {
            ನಿಲ್ಲಿಸು;
        }
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_ಅಡಚಣೆ_Controller( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ISRWrapper( ಶೂನ್ಯ );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_ರಿಜಿಸ್ಟರ್_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_ಪೋರ್ಟ್_ISRWrapper, ಖಾಲಿ );
    XIntc_Initialize( &x_ಅಡಚಣೆ_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_ಆರಂಭ( &x_ಅಡಚಣೆ_Controller, XIN_REAL_ಬಹುಲಕ );
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Install_ಅಡಚಣೆ_Handler( uint8_t uc_ಅಡಚಣೆ_ID,
                                         XInterruptHandler pxHandler,
                                         ಶೂನ್ಯ * pv_Call_ಹಿಂಭಾಗ_Ref )
{
    ತಳ_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    ಆದರೆ( XST_SUCCESS == XIntc_Connect( &x_ಅಡಚಣೆ_Controller, uc_ಅಡಚಣೆ_ID, pxHandler, pv_Call_ಹಿಂಭಾಗ_Ref ) )
    {
        XIntc_Enable( &x_ಅಡಚಣೆ_Controller, uc_ಅಡಚಣೆ_ID );
        xReturn = pdPASS;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}
