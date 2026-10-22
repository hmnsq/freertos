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
#تعریف_کرو پورٹ_CRITICAL_رکاوٹ_ENABLE    ( 1UL << 17UL )
#تعریف_کرو پورٹ_EXTERNAL_رکاوٹ_ENABLE    ( 1UL << 15UL )
#تعریف_کرو پورٹ_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#إذا configUSE_FPU == 1
    #تعریف_کرو پورٹ_APU_PRESENT              ( 1UL << 25UL )
    #تعریف_کرو پورٹ_FCM_FPU_PRESENT          ( 1UL << 13UL )
#وإلا
    #تعریف_کرو پورٹ_APU_PRESENT              ( 0UL )
    #تعریف_کرو پورٹ_FCM_FPU_PRESENT          ( 0UL )
#جے_انت

#تعریف_کرو پورٹ_INITIAL_MSR                  ( پورٹ_CRITICAL_رکاوٹ_ENABLE | پورٹ_EXTERNAL_رکاوٹ_ENABLE | پورٹ_MACHINE_CHECK_ENABLE | پورٹ_APU_PRESENT | پورٹ_FCM_FPU_PRESENT )


خارجي ثابت بنانشانی SDA_ادھار;
خارجي ثابت بنانشانی SDA2_ادھار;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
خارجي فراغ v_پورٹ_Tick_ISR( فراغ );

/*
 * The handler for the yield function - defined in portasm.s.
 */
خارجي فراغ v_پورٹ_Yield( فراغ );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
خارجي فراغ v_پورٹ_شروع_پہلا_Task( فراغ );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ساكن XIntc x_رکاوٹ_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_چوٹی_دا_ڈھیر = 0xDEADBEEF;
    px_چوٹی_دا_ڈھیر--;

    /* EABI stack frame. */
    px_چوٹی_دا_ڈھیر -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) &SDA_ادھار; /* address of the first small data area */
    px_چوٹی_دا_ڈھیر -= 10;

    /* Parameters in R3. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
    px_چوٹی_دا_ڈھیر--;

    /* Parameters in R2. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) &SDA2_ادھار; /* address of the second small data area */
    px_چوٹی_دا_ڈھیر--;

    /* R1 is the stack pointer so is omitted. */

    *px_چوٹی_دا_ڈھیر = 0x10000001UL;                      /* R0. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x00000000UL;                      /* USPRG0. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x00000000UL;                      /* CR. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x00000000UL;                      /* XER. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x00000000UL;                      /* CTR. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) v_پورٹ_سرا_Scheduler; /* LR. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;            /* SRR0. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_MSR;                   /* SRR1. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) v_پورٹ_سرا_Scheduler; /* Next LR. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x00000000UL;                      /* Backchain. */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    prv_تیاری_Timer_رکاوٹ();
    XExc_رجسٹر_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_پورٹ_Yield, ( فراغ * ) 0 );
    v_پورٹ_شروع_پہلا_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
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
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    ثابت uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL );

    XTime_DECClear_رکاوٹ();
    XTime_FITClear_رکاوٹ();
    XTime_WDTClear_رکاوٹ();
    XTime_WDTDisable_رکاوٹ();
    XTime_FITDisable_رکاوٹ();

    XExc_رجسٹر_Handler( XEXC_ID_DEC_INT, ( XExceptionHandler ) v_پورٹ_Tick_ISR, ( فراغ * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnable_رکاوٹ();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_ISRHandler( فراغ * pvNullDoNotUse )
{
    uint32_t ul_رکاوٹ_حالت, ul_رکاوٹ_نقاب = 1UL;
    ادھار_Type_t x_رکاوٹ_نمبر;
    XIntc_Config * px_رکاوٹ_Controller;
    XIntc_سمتیہ_جدول_اندراج * px_جدول;

    /* Just to remove compiler warning. */
    ( فراغ ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_رکاوٹ_Controller = &XIntc_Config_جدول[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_رکاوٹ_حالت = XIntc_m_Get_Intr_حالت( px_رکاوٹ_Controller->ادھار_پتہ );

    لكل( x_رکاوٹ_نمبر = 0; x_رکاوٹ_نمبر < XPAR_INTC_MAX_عدد_INTR_INPUTS; x_رکاوٹ_نمبر++ )
    {
        إذا( ul_رکاوٹ_حالت & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_رکاوٹ_Controller->ادھار_پتہ, ul_رکاوٹ_نقاب );

            /* Call the registered handler. */
            px_جدول = &( px_رکاوٹ_Controller->Handler_جدول[ x_رکاوٹ_نمبر ] );
            px_جدول->Handler( px_جدول->Call_پٹھ_Ref );
        }

        /* Check the next interrupt. */
        ul_رکاوٹ_نقاب <<= 0x01UL;
        ul_رکاوٹ_حالت >>= 0x01UL;

        /* Have we serviced all interrupts? */
        إذا( ul_رکاوٹ_حالت == 0UL )
        {
            اكسر;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_تیاری_رکاوٹ_Controller( فراغ )
{
    خارجي فراغ v_پورٹ_ISRWrapper( فراغ );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_رجسٹر_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_پورٹ_ISRWrapper, عدم );
    XIntc_Initialize( &x_رکاوٹ_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_شروع( &x_رکاوٹ_Controller, XIN_REAL_منوال );
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_Install_رکاوٹ_Handler( uint8_t uc_رکاوٹ_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پٹھ_Ref )
{
    ادھار_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    إذا( XST_SUCCESS == XIntc_Connect( &x_رکاوٹ_Controller, uc_رکاوٹ_ID, pxHandler, pv_Call_پٹھ_Ref ) )
    {
        XIntc_Enable( &x_رکاوٹ_Controller, uc_رکاوٹ_ID );
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
