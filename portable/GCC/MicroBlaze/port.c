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
* Implementation of functions defined in portable.h for the MicroBlaze port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Standard includes. */
#ضمن <string.h>

/* Hardware includes. */
#ضمن <xintc.h>
#ضمن <xintc_i.h>
#ضمن <xtmrctr.h>

#إذا ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #خطا config_SUPPORT_DYNAMIC_تخصیص must be مجموعه مقصد 1 مقصد use this پورت.
#پایان_اگر

/* Tasks are started with interrupts enabled. */
#تعریف_کن پورت_INITIAL_MSR_STATE        ( ( پشته_Type_t ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 * to the scheduler being commenced we don't want the critical nesting level
 * to reach zero, so it is initialised to a high value. */
#تعریف_کن پورت_INITIAL_NESTING_مقدار    ( 0xff )

/* Our hardware setup only uses one counter. */
#تعریف_کن پورت_COUNTER_0                0

/* The stack used by the ISR is filled with a known value to assist in
 * debugging. */
#تعریف_کن پورت_ISR_پشته_FILL_مقدار     0x55555555

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متطاير UBaseType_t uxCriticalNesting = پورت_INITIAL_NESTING_مقدار;

/* To limit the amount of stack required by each task, this port uses a
 * separate stack for interrupts. */
uint32_t * pulISRStack;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the header file portable.h.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    خارجي فراغ * SDA2_پایه;
    خارجي فراغ * SDA_پایه;
    ثابت uint32_t ulR2 = ( uint32_t ) &SDA2_پایه;
    ثابت uint32_t ulR13 = ( uint32_t ) &SDA_پایه;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted.  The parameter value will overwrite the
     * 0x22222222 value during the function prologue. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11111111;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x22222222;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x33333333;
    px_بالاترین_از_پشته--;

    /* First stack an initial value for the critical section nesting.  This
     *  is initialised to zero as tasks are started with interrupts enabled. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00; /* R0. */

    /* Place an initial value for all the general purpose registers. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ulR2;         /* R2 - small data area. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03;         /* R3. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04;         /* R4. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R5 contains the function call parameters. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06;         /* R6. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07;         /* R7. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08;         /* R8. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09;         /* R9. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0a;         /* R10. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0b;         /* R11. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0c;         /* R12. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ulR13;        /* R13 - small data read write area. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;       /* R14. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0f;         /* R15. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10;         /* R16. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11;         /* R17. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12;         /* R18. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x13;         /* R19. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x14;         /* R20. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x15;         /* R21. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x16;         /* R22. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x17;         /* R23. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x18;         /* R24. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x19;         /* R25. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1a;         /* R26. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1b;         /* R27. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1c;         /* R28. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1d;         /* R29. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1e;         /* R30. */
    px_بالاترین_از_پشته--;

    /* The MSR is stacked between R30 and R31. */
    *px_بالاترین_از_پشته = پورت_INITIAL_MSR_STATE;
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1f; /* R31. */
    px_بالاترین_از_پشته--;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    خارجي فراغ( __FreeRTOS_interrupt_Handler )( فراغ );
    خارجي فراغ( v_شروع_اولی_Task )( فراغ );


    /* Setup the FreeRTOS interrupt handler.  Code copied from crt0.s. */
    asm متطاير ( "la r6, r0, __FreeRTOS_interrupt_handler        \n\t" \
                   "sw r6, r1, r0                                  \n\t" \
                   "lhu r7, r1, r0                                 \n\t" \
                   "shi r7, r0, 0x12                               \n\t" \
                   "shi r6, r0, 0x16 " );

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_راهاندازی_Timer_وقفه();

    /* Allocate the stack to be used by the interrupt handler. */
    pulISRStack = ( uint32_t * ) pv_پورت_Malloc( config_کمینه_پشته_اندازه * حجم( پشته_Type_t ) );

    /* Restore the context of the first task that is going to run. */
    إذا( pulISRStack != عدم )
    {
        /* Fill the ISR stack with a known value to facilitate debugging. */
        memset( pulISRStack, پورت_ISR_پشته_FILL_مقدار, config_کمینه_پشته_اندازه * حجم( پشته_Type_t ) );
        pulISRStack += ( config_کمینه_پشته_اندازه - 1 );

        /* Kick off the first task. */
        v_شروع_اولی_Task();
    }

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
فراغ v_پورت_Yield( فراغ )
{
    خارجي فراغ VPortYieldASM( فراغ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورت_ENTER_CRITICAL();

    /* Jump directly to the yield function to ensure there is no
     * compiler generated prologue code. */
    asm متطاير ( "bralid r14, VPortYieldASM      \n\t" \
                   "or r0, r0, r0                  \n\t" );
    پورت_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    XTmrCtr xTimer;
    ثابت uint32_t ul_Counter_مقدار = configCPU_CLOCK_HZ / config_TICK_نرخ_HZ;
    UBaseType_t ux_ماسک;

    /* The OPB timer1 is used to generate the tick.  Use the provided library
     * functions to enable the timer and set the tick frequency. */
    XTmrCtr_mDisable( XPAR_OPB_TIMER_1_BASEADDR, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_Initialize( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_مجموعه_بارگیری_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورت_COUNTER_0, ul_Counter_مقدار );
    XTmr_Ctr_m_مجموعه_Control_وضعیت_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورت_COUNTER_0, XTC_CSR_بارگیری_ماسک | XTC_CSR_INT_occurred_ماسک );

    /* Set the timer interrupt enable bit while maintaining the other bit
     * states. */
    ux_ماسک = XIntc_In32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_جابه_جایی ) );
    ux_ماسک |= XPAR_OPB_TIMER_1_وقفه_ماسک;
    XIntc_Out32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_جابه_جایی ), ( ux_ماسک ) );

    XTmr_Ctr_شروع( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_مجموعه_Control_وضعیت_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورت_COUNTER_0, XTC_CSR_ENABLE_TMR_ماسک | XTC_CSR_ENABLE_INT_ماسک | XTC_CSR_AUTO_RELOAD_ماسک | XTC_CSR_پایین_شمار_ماسک | XTC_CSR_INT_occurred_ماسک );
    XIntc_mAckIntr( XPAR_INTC_SINGLE_BASEADDR, 1 );
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
فراغ vTaskISRHandler( فراغ )
{
    ساكن uint32_t ulPending;

    /* Which interrupts are pending? */
    ulPending = XIntc_In32( ( XPAR_INTC_SINGLE_BASEADDR + XIN_IVR_جابه_جایی ) );

    إذا( ulPending < XPAR_INTC_MAX_رقم_INTR_INPUTS )
    {
        ساكن XIntc_وکتور_جدول_مدخل * px_جدول_Ptr;
        ساكن XIntc_Config * pxConfig;
        ساكن uint32_t ul_وقفه_ماسک;

        ul_وقفه_ماسک = ( uint32_t ) 1 << ulPending;

        /* Get the configuration data using the device ID */
        pxConfig = &XIntc_Config_جدول[ ( uint32_t ) XPAR_INTC_SINGLE_DEVICE_ID ];

        px_جدول_Ptr = &( pxConfig->Handler_جدول[ ulPending ] );

        إذا( pxConfig->AckBeforeService & ( ul_وقفه_ماسک ) )
        {
            XIntc_mAckIntr( pxConfig->پایه_آدرس, ul_وقفه_ماسک );
            px_جدول_Ptr->Handler( px_جدول_Ptr->Call_پشت_Ref );
        }
        وإلا
        {
            px_جدول_Ptr->Handler( px_جدول_Ptr->Call_پشت_Ref );
            XIntc_mAckIntr( pxConfig->پایه_آدرس, ul_وقفه_ماسک );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.
 */
فراغ vTickISR( فراغ * pv_پایه_آدرس )
{
    uint32_t ulCSR;

    /* Increment the RTOS tick - this might cause a task to unblock. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the timer interrupt */
    ulCSR = XTmr_Ctr_m_Get_Control_وضعیت_Reg( XPAR_OPB_TIMER_1_BASEADDR, 0 );
    XTmr_Ctr_m_مجموعه_Control_وضعیت_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورت_COUNTER_0, ulCSR );
}
/*-----------------------------------------------------------*/
