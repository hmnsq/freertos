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
#تعریف_کرو پورٹ_CRITICAL_مداخلت_ENABLE    ( 1UL << 17UL )
#تعریف_کرو پورٹ_EXTERNAL_مداخلت_ENABLE    ( 1UL << 15UL )
#تعریف_کرو پورٹ_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#اگر configUSE_FPU == 1
    #تعریف_کرو پورٹ_APU_PRESENT              ( 1UL << 25UL )
    #تعریف_کرو پورٹ_FCM_FPU_PRESENT          ( 1UL << 13UL )
#ورنہ
    #تعریف_کرو پورٹ_APU_PRESENT              ( 0UL )
    #تعریف_کرو پورٹ_FCM_FPU_PRESENT          ( 0UL )
#اگر_ختم

#تعریف_کرو پورٹ_INITIAL_MSR                  ( پورٹ_CRITICAL_مداخلت_ENABLE | پورٹ_EXTERNAL_مداخلت_ENABLE | پورٹ_MACHINE_CHECK_ENABLE | پورٹ_APU_PRESENT | پورٹ_FCM_FPU_PRESENT )


خارجی ثابت غیرعلامتی SDA_بنیاد;
خارجی ثابت غیرعلامتی SDA2_بنیاد;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
خارجی خالی v_پورٹ_Tick_ISR( خالی );

/*
 * The handler for the yield function - defined in portasm.s.
 */
خارجی خالی v_پورٹ_Yield( خالی );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
خارجی خالی v_پورٹ_آغاز_پہلا_Task( خالی );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
ساکن XIntc x_مداخلت_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_چوٹی_کا_ڈھیر = 0xDEADBEEF;
    px_چوٹی_کا_ڈھیر--;

    /* EABI stack frame. */
    px_چوٹی_کا_ڈھیر -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) &SDA_بنیاد; /* address of the first small data area */
    px_چوٹی_کا_ڈھیر -= 10;

    /* Parameters in R3. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
    px_چوٹی_کا_ڈھیر--;

    /* Parameters in R2. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) &SDA2_بنیاد; /* address of the second small data area */
    px_چوٹی_کا_ڈھیر--;

    /* R1 is the stack pointer so is omitted. */

    *px_چوٹی_کا_ڈھیر = 0x10000001UL;                      /* R0. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00000000UL;                      /* USPRG0. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00000000UL;                      /* CR. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00000000UL;                      /* XER. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00000000UL;                      /* CTR. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) v_پورٹ_انتہا_Scheduler; /* LR. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;            /* SRR0. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_MSR;                   /* SRR1. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) v_پورٹ_انتہا_Scheduler; /* Next LR. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x00000000UL;                      /* Backchain. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    prv_تیاری_Timer_مداخلت();
    XExc_رجسٹر_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_پورٹ_Yield, ( خالی * ) 0 );
    v_پورٹ_آغاز_پہلا_Task();

    /* Should not get here as the tasks are now running! */
    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented. */
    برائے( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    ثابت uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL );

    XTime_PITClear_مداخلت();
    XTime_FITClear_مداخلت();
    XTime_WDTClear_مداخلت();
    XTime_WDTDisable_مداخلت();
    XTime_FITDisable_مداخلت();

    XExc_رجسٹر_Handler( XEXC_ID_PIT_INT, ( XExceptionHandler ) v_پورٹ_Tick_ISR, ( خالی * ) 0 );

    XTime_PITEnableAutoReload();
    XTime_PITSetInterval( ulInterval );
    XTime_PITEnable_مداخلت();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_ISRHandler( خالی * pvNullDoNotUse )
{
    uint32_t ul_مداخلت_حالت, ul_مداخلت_نقاب = 1UL;
    بنیاد_Type_t x_مداخلت_نمبر;
    XIntc_Config * px_مداخلت_Controller;
    XIntc_سمتیہ_جدول_اندراج * px_جدول;

    /* Just to remove compiler warning. */
    ( خالی ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_مداخلت_Controller = &XIntc_Config_جدول[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_مداخلت_حالت = XIntc_m_Get_Intr_حالت( px_مداخلت_Controller->بنیاد_پتہ );

    برائے( x_مداخلت_نمبر = 0; x_مداخلت_نمبر < XPAR_INTC_MAX_عدد_INTR_INPUTS; x_مداخلت_نمبر++ )
    {
        اگر( ul_مداخلت_حالت & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_مداخلت_Controller->بنیاد_پتہ, ul_مداخلت_نقاب );

            /* Call the registered handler. */
            px_جدول = &( px_مداخلت_Controller->Handler_جدول[ x_مداخلت_نمبر ] );
            px_جدول->Handler( px_جدول->Call_عقب_Ref );
        }

        /* Check the next interrupt. */
        ul_مداخلت_نقاب <<= 0x01UL;
        ul_مداخلت_حالت >>= 0x01UL;

        /* Have we serviced all interrupts? */
        اگر( ul_مداخلت_حالت == 0UL )
        {
            توڑو;
        }
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_تیاری_مداخلت_Controller( خالی )
{
    خارجی خالی v_پورٹ_ISRWrapper( خالی );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_رجسٹر_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_پورٹ_ISRWrapper, تہی );
    XIntc_Initialize( &x_مداخلت_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_آغاز( &x_مداخلت_Controller, XIN_REAL_منوال );
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_Install_مداخلت_Handler( uint8_t uc_مداخلت_ID,
                                         XInterruptHandler pxHandler,
                                         خالی * pv_Call_عقب_Ref )
{
    بنیاد_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    اگر( XST_SUCCESS == XIntc_Connect( &x_مداخلت_Controller, uc_مداخلت_ID, pxHandler, pv_Call_عقب_Ref ) )
    {
        XIntc_Enable( &x_مداخلت_Controller, uc_مداخلت_ID );
        xReturn = pdPASS;
    }

    واپس xReturn;
}
