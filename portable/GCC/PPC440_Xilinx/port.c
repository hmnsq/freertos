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
#تعریف_کن پورت_CRITICAL_وقفه_ENABLE    ( 1UL << 17UL )
#تعریف_کن پورت_EXTERNAL_وقفه_ENABLE    ( 1UL << 15UL )
#تعریف_کن پورت_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#إذا configUSE_FPU == 1
    #تعریف_کن پورت_APU_PRESENT              ( 1UL << 25UL )
    #تعریف_کن پورت_FCM_FPU_PRESENT          ( 1UL << 13UL )
#وإلا
    #تعریف_کن پورت_APU_PRESENT              ( 0UL )
    #تعریف_کن پورت_FCM_FPU_PRESENT          ( 0UL )
#پایان_اگر

#تعریف_کن پورت_INITIAL_MSR                  ( پورت_CRITICAL_وقفه_ENABLE | پورت_EXTERNAL_وقفه_ENABLE | پورت_MACHINE_CHECK_ENABLE | پورت_APU_PRESENT | پورت_FCM_FPU_PRESENT )


خارجي ثابت بیعلامت SDA_پایه;
خارجي ثابت بیعلامت SDA2_پایه;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
خارجي فراغ v_پورت_Tick_ISR( فراغ );

/*
 * The handler for the yield function - defined in portasm.s.
 */
خارجي فراغ v_پورت_Yield( فراغ );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ساكن XIntc x_وقفه_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_بالاترین_از_پشته = 0xDEADBEEF;
    px_بالاترین_از_پشته--;

    /* EABI stack frame. */
    px_بالاترین_از_پشته -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) &SDA_پایه; /* address of the first small data area */
    px_بالاترین_از_پشته -= 10;

    /* Parameters in R3. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;
    px_بالاترین_از_پشته--;

    /* Parameters in R2. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) &SDA2_پایه; /* address of the second small data area */
    px_بالاترین_از_پشته--;

    /* R1 is the stack pointer so is omitted. */

    *px_بالاترین_از_پشته = 0x10000001UL;                      /* R0. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x00000000UL;                      /* USPRG0. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x00000000UL;                      /* CR. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x00000000UL;                      /* XER. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x00000000UL;                      /* CTR. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) v_پورت_انتها_Scheduler; /* LR. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;            /* SRR0. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_INITIAL_MSR;                   /* SRR1. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) v_پورت_انتها_Scheduler; /* Next LR. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x00000000UL;                      /* Backchain. */

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    prv_راهاندازی_Timer_وقفه();
    XExc_ثبات_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_پورت_Yield, ( فراغ * ) 0 );
    v_پورت_شروع_اولی_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
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
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    ثابت uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL );

    XTime_DECClear_وقفه();
    XTime_FITClear_وقفه();
    XTime_WDTClear_وقفه();
    XTime_WDTDisable_وقفه();
    XTime_FITDisable_وقفه();

    XExc_ثبات_Handler( XEXC_ID_DEC_INT, ( XExceptionHandler ) v_پورت_Tick_ISR, ( فراغ * ) 0 );

    XTime_DECEnableAutoReload();
    XTime_DECSetInterval( ulInterval );
    XTime_DECEnable_وقفه();
}
/*-----------------------------------------------------------*/

فراغ v_پورت_ISRHandler( فراغ * pvNullDoNotUse )
{
    uint32_t ul_وقفه_وضعیت, ul_وقفه_ماسک = 1UL;
    پایه_Type_t x_وقفه_عدد;
    XIntc_Config * px_وقفه_Controller;
    XIntc_وکتور_جدول_مدخل * px_جدول;

    /* Just to remove compiler warning. */
    ( فراغ ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_وقفه_Controller = &XIntc_Config_جدول[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_وقفه_وضعیت = XIntc_m_Get_Intr_وضعیت( px_وقفه_Controller->پایه_آدرس );

    لكل( x_وقفه_عدد = 0; x_وقفه_عدد < XPAR_INTC_MAX_رقم_INTR_INPUTS; x_وقفه_عدد++ )
    {
        إذا( ul_وقفه_وضعیت & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_وقفه_Controller->پایه_آدرس, ul_وقفه_ماسک );

            /* Call the registered handler. */
            px_جدول = &( px_وقفه_Controller->Handler_جدول[ x_وقفه_عدد ] );
            px_جدول->Handler( px_جدول->Call_پشت_Ref );
        }

        /* Check the next interrupt. */
        ul_وقفه_ماسک <<= 0x01UL;
        ul_وقفه_وضعیت >>= 0x01UL;

        /* Have we serviced all interrupts? */
        إذا( ul_وقفه_وضعیت == 0UL )
        {
            اكسر;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_راهاندازی_وقفه_Controller( فراغ )
{
    خارجي فراغ v_پورت_ISRWrapper( فراغ );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_ثبات_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_پورت_ISRWrapper, عدم );
    XIntc_Initialize( &x_وقفه_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_شروع( &x_وقفه_Controller, XIN_REAL_نما );
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_Install_وقفه_Handler( uint8_t uc_وقفه_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پشت_Ref )
{
    پایه_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    إذا( XST_SUCCESS == XIntc_Connect( &x_وقفه_Controller, uc_وقفه_ID, pxHandler, pv_Call_پشت_Ref ) )
    {
        XIntc_Enable( &x_وقفه_Controller, uc_وقفه_ID );
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
