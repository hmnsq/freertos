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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "xtime_l.h"
#ضمن "xintc.h"
#ضمن "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#وصف_ڪريو پورٽ_CRITICAL_مداخلت_ENABLE    ( 1UL << 17UL )
#وصف_ڪريو پورٽ_EXTERNAL_مداخلت_ENABLE    ( 1UL << 15UL )
#وصف_ڪريو پورٽ_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#إذا configUSE_FPU == 1
    #وصف_ڪريو پورٽ_APU_PRESENT              ( 1UL << 25UL )
    #وصف_ڪريو پورٽ_FCM_FPU_PRESENT          ( 1UL << 13UL )
#وإلا
    #وصف_ڪريو پورٽ_APU_PRESENT              ( 0UL )
    #وصف_ڪريو پورٽ_FCM_FPU_PRESENT          ( 0UL )
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_INITIAL_MSR                  ( پورٽ_CRITICAL_مداخلت_ENABLE | پورٽ_EXTERNAL_مداخلت_ENABLE | پورٽ_MACHINE_CHECK_ENABLE | پورٽ_APU_PRESENT | پورٽ_FCM_FPU_PRESENT )


خارجي ثابت بنانشان SDA_بنياد;
خارجي ثابت بنانشان SDA2_بنياد;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
خارجي فراغ v_پورٽ_Tick_ISR( فراغ );

/*
 * The handler for the yield function - defined in portasm.s.
 */
خارجي فراغ v_پورٽ_Yield( فراغ );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ساكن XIntc x_مداخلت_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_چوٽي_جو_ڍير = 0xDEADBEEF;
    px_چوٽي_جو_ڍير--;

    /* EABI stack frame. */
    px_چوٽي_جو_ڍير -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) &SDA_بنياد; /* address of the first small data area */
    px_چوٽي_جو_ڍير -= 10;

    /* Parameters in R3. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;
    px_چوٽي_جو_ڍير--;

    /* Parameters in R2. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) &SDA2_بنياد; /* address of the second small data area */
    px_چوٽي_جو_ڍير--;

    /* R1 is the stack pointer so is omitted. */

    *px_چوٽي_جو_ڍير = 0x10000001UL;                      /* R0. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x00000000UL;                      /* USPRG0. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x00000000UL;                      /* CR. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x00000000UL;                      /* XER. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x00000000UL;                      /* CTR. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) v_پورٽ_پڇاڙي_Scheduler; /* LR. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;            /* SRR0. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_MSR;                   /* SRR1. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) v_پورٽ_پڇاڙي_Scheduler; /* Next LR. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x00000000UL;                      /* Backchain. */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    prv_تياري_Timer_مداخلت();
    XExc_رجسٽر_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_پورٽ_Yield, ( فراغ * ) 0 );
    v_پورٽ_شروعات_پهريون_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented. */
    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    ثابت uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL );

    XTime_DECClear_مداخلت();
    XTime_FITClear_مداخلت();
    XTime_WDTClear_مداخلت();
    XTime_WDTDisable_مداخلت();
    XTime_FITDisable_مداخلت();

    XExc_رجسٽر_Handler( XEXC_ID_DEC_INT, ( XExceptionHandler ) v_پورٽ_Tick_ISR, ( فراغ * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnable_مداخلت();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_ISRHandler( فراغ * pvNullDoNotUse )
{
    uint32_t ul_مداخلت_حالت, ul_مداخلت_نقاب = 1UL;
    بنياد_Type_t x_مداخلت_عدد;
    XIntc_Config * px_مداخلت_Controller;
    XIntc_ويڪٽر_جدول_داخلا * px_جدول;

    /* Just to remove compiler warning. */
    ( فراغ ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_مداخلت_Controller = &XIntc_Config_جدول[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_مداخلت_حالت = XIntc_m_Get_Intr_حالت( px_مداخلت_Controller->بنياد_پتو );

    لكل( x_مداخلت_عدد = 0; x_مداخلت_عدد < XPAR_INTC_MAX_انگ_INTR_INPUTS; x_مداخلت_عدد++ )
    {
        إذا( ul_مداخلت_حالت & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_مداخلت_Controller->بنياد_پتو, ul_مداخلت_نقاب );

            /* Call the registered handler. */
            px_جدول = &( px_مداخلت_Controller->Handler_جدول[ x_مداخلت_عدد ] );
            px_جدول->Handler( px_جدول->Call_پٺ_Ref );
        }

        /* Check the next interrupt. */
        ul_مداخلت_نقاب <<= 0x01UL;
        ul_مداخلت_حالت >>= 0x01UL;

        /* Have we serviced all interrupts? */
        إذا( ul_مداخلت_حالت == 0UL )
        {
            اكسر;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_تياري_مداخلت_Controller( فراغ )
{
    خارجي فراغ v_پورٽ_ISRWrapper( فراغ );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_رجسٽر_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_پورٽ_ISRWrapper, عدم );
    XIntc_Initialize( &x_مداخلت_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_شروعات( &x_مداخلت_Controller, XIN_REAL_گهڻائي );
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_Install_مداخلت_Handler( uint8_t uc_مداخلت_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پٺ_Ref )
{
    بنياد_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    إذا( XST_SUCCESS == XIntc_Connect( &x_مداخلت_Controller, uc_مداخلت_ID, pxHandler, pv_Call_پٺ_Ref ) )
    {
        XIntc_Enable( &x_مداخلت_Controller, uc_مداخلت_ID );
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
