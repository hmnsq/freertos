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
#تعریف_کړه پورټ_CRITICAL_مداخله_ENABLE    ( 1UL << 17UL )
#تعریف_کړه پورټ_EXTERNAL_مداخله_ENABLE    ( 1UL << 15UL )
#تعریف_کړه پورټ_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#إذا configUSE_FPU == 1
    #تعریف_کړه پورټ_APU_PRESENT              ( 1UL << 25UL )
    #تعریف_کړه پورټ_FCM_FPU_PRESENT          ( 1UL << 13UL )
#وإلا
    #تعریف_کړه پورټ_APU_PRESENT              ( 0UL )
    #تعریف_کړه پورټ_FCM_FPU_PRESENT          ( 0UL )
#د_که_پای

#تعریف_کړه پورټ_INITIAL_MSR                  ( پورټ_CRITICAL_مداخله_ENABLE | پورټ_EXTERNAL_مداخله_ENABLE | پورټ_MACHINE_CHECK_ENABLE | پورټ_APU_PRESENT | پورټ_FCM_FPU_PRESENT )


خارجي ثابت بینښه SDA_بنسټ;
خارجي ثابت بینښه SDA2_بنسټ;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
خارجي فراغ v_پورټ_Tick_ISR( فراغ );

/*
 * The handler for the yield function - defined in portasm.s.
 */
خارجي فراغ v_پورټ_Yield( فراغ );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ساكن XIntc x_مداخله_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_سر_د_ډېری = 0xDEADBEEF;
    px_سر_د_ډېری--;

    /* EABI stack frame. */
    px_سر_د_ډېری -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) &SDA_بنسټ; /* address of the first small data area */
    px_سر_د_ډېری -= 10;

    /* Parameters in R3. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;
    px_سر_د_ډېری--;

    /* Parameters in R2. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) &SDA2_بنسټ; /* address of the second small data area */
    px_سر_د_ډېری--;

    /* R1 is the stack pointer so is omitted. */

    *px_سر_د_ډېری = 0x10000001UL;                      /* R0. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x00000000UL;                      /* USPRG0. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x00000000UL;                      /* CR. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x00000000UL;                      /* XER. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x00000000UL;                      /* CTR. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) v_پورټ_پای_ټکی_Scheduler; /* LR. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;            /* SRR0. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = پورټ_INITIAL_MSR;                   /* SRR1. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) v_پورټ_پای_ټکی_Scheduler; /* Next LR. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x00000000UL;                      /* Backchain. */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    prv_تیاری_Timer_مداخله();
    XExc_ثبتوونکی_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_پورټ_Yield, ( فراغ * ) 0 );
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
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
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    ثابت uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL );

    XTime_DECClear_مداخله();
    XTime_FITClear_مداخله();
    XTime_WDTClear_مداخله();
    XTime_WDTDisable_مداخله();
    XTime_FITDisable_مداخله();

    XExc_ثبتوونکی_Handler( XEXC_ID_DEC_INT, ( XExceptionHandler ) v_پورټ_Tick_ISR, ( فراغ * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnable_مداخله();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_ISRHandler( فراغ * pvNullDoNotUse )
{
    uint32_t ul_مداخله_حالت, ul_مداخله_ماسک = 1UL;
    بنسټ_Type_t x_مداخله_شمېره;
    XIntc_Config * px_مداخله_Controller;
    XIntc_ویکټور_جدول_ثبت * px_جدول;

    /* Just to remove compiler warning. */
    ( فراغ ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_مداخله_Controller = &XIntc_Config_جدول[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_مداخله_حالت = XIntc_m_Get_Intr_حالت( px_مداخله_Controller->بنسټ_پته );

    لكل( x_مداخله_شمېره = 0; x_مداخله_شمېره < XPAR_INTC_MAX_عدد_INTR_INPUTS; x_مداخله_شمېره++ )
    {
        إذا( ul_مداخله_حالت & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_مداخله_Controller->بنسټ_پته, ul_مداخله_ماسک );

            /* Call the registered handler. */
            px_جدول = &( px_مداخله_Controller->Handler_جدول[ x_مداخله_شمېره ] );
            px_جدول->Handler( px_جدول->Call_شا_Ref );
        }

        /* Check the next interrupt. */
        ul_مداخله_ماسک <<= 0x01UL;
        ul_مداخله_حالت >>= 0x01UL;

        /* Have we serviced all interrupts? */
        إذا( ul_مداخله_حالت == 0UL )
        {
            اكسر;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_تیاری_مداخله_Controller( فراغ )
{
    خارجي فراغ v_پورټ_ISRWrapper( فراغ );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_ثبتوونکی_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_پورټ_ISRWrapper, عدم );
    XIntc_Initialize( &x_مداخله_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_پیل( &x_مداخله_Controller, XIN_REAL_ډېرپېښ );
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_Install_مداخله_Handler( uint8_t uc_مداخله_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_شا_Ref )
{
    بنسټ_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    إذا( XST_SUCCESS == XIntc_Connect( &x_مداخله_Controller, uc_مداخله_ID, pxHandler, pv_Call_شا_Ref ) )
    {
        XIntc_Enable( &x_مداخله_Controller, uc_مداخله_ID );
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
