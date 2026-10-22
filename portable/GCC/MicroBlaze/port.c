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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Standard includes. */
#شامل <string.h>

/* Hardware includes. */
#شامل <xintc.h>
#شامل <xintc_i.h>
#شامل <xtmrctr.h>

#اگر ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #غلطی config_SUPPORT_DYNAMIC_تخصیص must be سیٹ مقصد 1 مقصد use this پورٹ.
#اگر_ختم

/* Tasks are started with interrupts enabled. */
#تعریف_کرو پورٹ_INITIAL_MSR_STATE        ( ( ڈھیر_Type_t ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 * to the scheduler being commenced we don't want the critical nesting level
 * to reach zero, so it is initialised to a high value. */
#تعریف_کرو پورٹ_INITIAL_NESTING_قدر    ( 0xff )

/* Our hardware setup only uses one counter. */
#تعریف_کرو پورٹ_شمار_0                0

/* The stack used by the ISR is filled with a known value to assist in
 * debugging. */
#تعریف_کرو پورٹ_ISR_ڈھیر_FILL_قدر     0x55555555

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متلون UBaseType_t uxCriticalNesting = پورٹ_INITIAL_NESTING_قدر;

/* To limit the amount of stack required by each task, this port uses a
 * separate stack for interrupts. */
uint32_t * pulISRStack;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the header file portable.h.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    خارجی خالی * SDA2_بنیاد;
    خارجی خالی * SDA_بنیاد;
    ثابت uint32_t ulR2 = ( uint32_t ) &SDA2_بنیاد;
    ثابت uint32_t ulR13 = ( uint32_t ) &SDA_بنیاد;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted.  The parameter value will overwrite the
     * 0x22222222 value during the function prologue. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x22222222;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x33333333;
    px_چوٹی_کا_ڈھیر--;

    /* First stack an initial value for the critical section nesting.  This
     *  is initialised to zero as tasks are started with interrupts enabled. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00; /* R0. */

    /* Place an initial value for all the general purpose registers. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ulR2;         /* R2 - small data area. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03;         /* R3. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04;         /* R4. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R5 contains the function call parameters. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06;         /* R6. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07;         /* R7. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08;         /* R8. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09;         /* R9. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0a;         /* R10. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0b;         /* R11. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0c;         /* R12. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ulR13;        /* R13 - small data read write area. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;       /* R14. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0f;         /* R15. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10;         /* R16. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11;         /* R17. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12;         /* R18. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x13;         /* R19. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x14;         /* R20. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x15;         /* R21. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x16;         /* R22. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x17;         /* R23. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x18;         /* R24. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x19;         /* R25. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1a;         /* R26. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1b;         /* R27. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1c;         /* R28. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1d;         /* R29. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1e;         /* R30. */
    px_چوٹی_کا_ڈھیر--;

    /* The MSR is stacked between R30 and R31. */
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_MSR_STATE;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1f; /* R31. */
    px_چوٹی_کا_ڈھیر--;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    خارجی خالی( __FreeRTOS_interrupt_Handler )( خالی );
    خارجی خالی( v_آغاز_پہلا_Task )( خالی );


    /* Setup the FreeRTOS interrupt handler.  Code copied from crt0.s. */
    asm متلون ( "la r6, r0, __FreeRTOS_interrupt_handler        \n\t" \
                   "sw r6, r1, r0                                  \n\t" \
                   "lhu r7, r1, r0                                 \n\t" \
                   "shi r7, r0, 0x12                               \n\t" \
                   "shi r6, r0, 0x16 " );

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_تیاری_Timer_مداخلت();

    /* Allocate the stack to be used by the interrupt handler. */
    pulISRStack = ( uint32_t * ) pv_پورٹ_Malloc( config_اقل_ڈھیر_سائز * حجم( ڈھیر_Type_t ) );

    /* Restore the context of the first task that is going to run. */
    اگر( pulISRStack != تہی )
    {
        /* Fill the ISR stack with a known value to facilitate debugging. */
        memset( pulISRStack, پورٹ_ISR_ڈھیر_FILL_قدر, config_اقل_ڈھیر_سائز * حجم( ڈھیر_Type_t ) );
        pulISRStack += ( config_اقل_ڈھیر_سائز - 1 );

        /* Kick off the first task. */
        v_آغاز_پہلا_Task();
    }

    /* Should not get here as the tasks are now running! */
    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
خالی v_پورٹ_Yield( خالی )
{
    خارجی خالی VPortYieldASM( خالی );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورٹ_ENTER_CRITICAL();

    /* Jump directly to the yield function to ensure there is no
     * compiler generated prologue code. */
    asm متلون ( "bralid r14, VPortYieldASM      \n\t" \
                   "or r0, r0, r0                  \n\t" );
    پورٹ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    XTmrCtr xTimer;
    ثابت uint32_t ul_شمار_قدر = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;
    UBaseType_t ux_نقاب;

    /* The OPB timer1 is used to generate the tick.  Use the provided library
     * functions to enable the timer and set the tick frequency. */
    XTmrCtr_mDisable( XPAR_OPB_TIMER_1_BASEADDR, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_Initialize( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_سیٹ_بھرو_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورٹ_شمار_0, ul_شمار_قدر );
    XTmr_Ctr_m_سیٹ_Control_حالت_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورٹ_شمار_0, XTC_CSR_بھرو_نقاب | XTC_CSR_INT_occurred_نقاب );

    /* Set the timer interrupt enable bit while maintaining the other bit
     * states. */
    ux_نقاب = XIntc_In32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_انحراف ) );
    ux_نقاب |= XPAR_OPB_TIMER_1_مداخلت_نقاب;
    XIntc_Out32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_انحراف ), ( ux_نقاب ) );

    XTmr_Ctr_آغاز( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_سیٹ_Control_حالت_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورٹ_شمار_0, XTC_CSR_ENABLE_TMR_نقاب | XTC_CSR_ENABLE_INT_نقاب | XTC_CSR_AUTO_RELOAD_نقاب | XTC_CSR_نیچے_کو_گنتی_نقاب | XTC_CSR_INT_occurred_نقاب );
    XIntc_mAckIntr( XPAR_INTC_SINGLE_BASEADDR, 1 );
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
خالی vTaskISRHandler( خالی )
{
    ساکن uint32_t ulPending;

    /* Which interrupts are pending? */
    ulPending = XIntc_In32( ( XPAR_INTC_SINGLE_BASEADDR + XIN_IVR_انحراف ) );

    اگر( ulPending < XPAR_INTC_MAX_عدد_INTR_INPUTS )
    {
        ساکن XIntc_سمتیہ_جدول_اندراج * px_جدول_Ptr;
        ساکن XIntc_Config * pxConfig;
        ساکن uint32_t ul_مداخلت_نقاب;

        ul_مداخلت_نقاب = ( uint32_t ) 1 << ulPending;

        /* Get the configuration data using the device ID */
        pxConfig = &XIntc_Config_جدول[ ( uint32_t ) XPAR_INTC_SINGLE_DEVICE_ID ];

        px_جدول_Ptr = &( pxConfig->Handler_جدول[ ulPending ] );

        اگر( pxConfig->AckBeforeService & ( ul_مداخلت_نقاب ) )
        {
            XIntc_mAckIntr( pxConfig->بنیاد_پتہ, ul_مداخلت_نقاب );
            px_جدول_Ptr->Handler( px_جدول_Ptr->Call_عقب_Ref );
        }
        ورنہ
        {
            px_جدول_Ptr->Handler( px_جدول_Ptr->Call_عقب_Ref );
            XIntc_mAckIntr( pxConfig->بنیاد_پتہ, ul_مداخلت_نقاب );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.
 */
خالی vTickISR( خالی * pv_بنیاد_پتہ )
{
    uint32_t ulCSR;

    /* Increment the RTOS tick - this might cause a task to unblock. */
    اگر( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the timer interrupt */
    ulCSR = XTmr_Ctr_m_Get_Control_حالت_Reg( XPAR_OPB_TIMER_1_BASEADDR, 0 );
    XTmr_Ctr_m_سیٹ_Control_حالت_Reg( XPAR_OPB_TIMER_1_BASEADDR, پورٹ_شمار_0, ulCSR );
}
/*-----------------------------------------------------------*/
