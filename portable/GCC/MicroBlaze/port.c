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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

/* Hardware includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <xintc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xintc_i.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xtmrctr.h>

#ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 0 )
    #ਗਲਤੀ config_SUPPORT_DYNAMIC_ਵੰਡ must be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ use this ਪੋਰਟ.
#ਜੇ_ਅੰਤ

/* Tasks are started with interrupts enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_MSR_STATE        ( ( ਢੇਰ_Type_t ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 * to the scheduler being commenced we don't want the critical nesting level
 * to reach zero, so it is initialised to a high value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_NESTING_ਮੁੱਲ    ( 0xff )

/* Our hardware setup only uses one counter. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_COUNTER_0                0

/* The stack used by the ISR is filled with a known value to assist in
 * debugging. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ISR_ਢੇਰ_FILL_ਮੁੱਲ     0x55555555

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
ਅਸਥਿਰ UBaseType_t uxCriticalNesting = ਪੋਰਟ_INITIAL_NESTING_ਮੁੱਲ;

/* To limit the amount of stack required by each task, this port uses a
 * separate stack for interrupts. */
uint32_t * pulISRStack;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the header file portable.h.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ਬਾਹਰੀ ਖਾਲੀ * SDA2_ਅਧਾਰ;
    ਬਾਹਰੀ ਖਾਲੀ * SDA_ਅਧਾਰ;
    ਅਚਲ uint32_t ulR2 = ( uint32_t ) &SDA2_ਅਧਾਰ;
    ਅਚਲ uint32_t ulR13 = ( uint32_t ) &SDA_ਅਧਾਰ;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted.  The parameter value will overwrite the
     * 0x22222222 value during the function prologue. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x22222222;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x33333333;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* First stack an initial value for the critical section nesting.  This
     *  is initialised to zero as tasks are started with interrupts enabled. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00; /* R0. */

    /* Place an initial value for all the general purpose registers. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ulR2;         /* R2 - small data area. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03;         /* R3. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04;         /* R4. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R5 contains the function call parameters. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06;         /* R6. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07;         /* R7. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08;         /* R8. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09;         /* R9. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0a;         /* R10. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0b;         /* R11. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0c;         /* R12. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ulR13;        /* R13 - small data read write area. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;       /* R14. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0f;         /* R15. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10;         /* R16. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11;         /* R17. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12;         /* R18. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x13;         /* R19. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x14;         /* R20. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x15;         /* R21. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x16;         /* R22. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x17;         /* R23. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x18;         /* R24. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x19;         /* R25. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1a;         /* R26. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1b;         /* R27. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1c;         /* R28. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1d;         /* R29. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1e;         /* R30. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The MSR is stacked between R30 and R31. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_MSR_STATE;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1f; /* R31. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ( __FreeRTOS_interrupt_Handler )( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ( v_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task )( ਖਾਲੀ );


    /* Setup the FreeRTOS interrupt handler.  Code copied from crt0.s. */
    asm ਅਸਥਿਰ ( "la r6, r0, __FreeRTOS_interrupt_handler        \n\t" \
                   "sw r6, r1, r0                                  \n\t" \
                   "lhu r7, r1, r0                                 \n\t" \
                   "shi r7, r0, 0x12                               \n\t" \
                   "shi r6, r0, 0x16 " );

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Allocate the stack to be used by the interrupt handler. */
    pulISRStack = ( uint32_t * ) pv_ਪੋਰਟ_Malloc( config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ * ਆਕਾਰ( ਢੇਰ_Type_t ) );

    /* Restore the context of the first task that is going to run. */
    ਜੇ( pulISRStack != ਨਿਰਾ )
    {
        /* Fill the ISR stack with a known value to facilitate debugging. */
        memset( pulISRStack, ਪੋਰਟ_ISR_ਢੇਰ_FILL_ਮੁੱਲ, config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ * ਆਕਾਰ( ਢੇਰ_Type_t ) );
        pulISRStack += ( config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ - 1 );

        /* Kick off the first task. */
        v_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();
    }

    /* Should not get here as the tasks are now running! */
    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ VPortYieldASM( ਖਾਲੀ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    ਪੋਰਟ_ENTER_CRITICAL();

    /* Jump directly to the yield function to ensure there is no
     * compiler generated prologue code. */
    asm ਅਸਥਿਰ ( "bralid r14, VPortYieldASM      \n\t" \
                   "or r0, r0, r0                  \n\t" );
    ਪੋਰਟ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    XTmrCtr xTimer;
    ਅਚਲ uint32_t ul_Counter_ਮੁੱਲ = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ;
    UBaseType_t ux_ਨਕਾਬ;

    /* The OPB timer1 is used to generate the tick.  Use the provided library
     * functions to enable the timer and set the tick frequency. */
    XTmrCtr_mDisable( XPAR_OPB_TIMER_1_BASEADDR, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_Initialize( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_ਸੈੱਟ_ਲੱਦੋ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ਪੋਰਟ_COUNTER_0, ul_Counter_ਮੁੱਲ );
    XTmr_Ctr_m_ਸੈੱਟ_Control_ਸਥਿਤੀ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ਪੋਰਟ_COUNTER_0, XTC_CSR_ਲੱਦੋ_ਨਕਾਬ | XTC_CSR_INT_occurred_ਨਕਾਬ );

    /* Set the timer interrupt enable bit while maintaining the other bit
     * states. */
    ux_ਨਕਾਬ = XIntc_In32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_ਵਿੱਥ ) );
    ux_ਨਕਾਬ |= XPAR_OPB_TIMER_1_ਰੁਕਾਵਟ_ਨਕਾਬ;
    XIntc_Out32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_ਵਿੱਥ ), ( ux_ਨਕਾਬ ) );

    XTmr_Ctr_ਸ਼ੁਰੂ( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_ਸੈੱਟ_Control_ਸਥਿਤੀ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ਪੋਰਟ_COUNTER_0, XTC_CSR_ENABLE_TMR_ਨਕਾਬ | XTC_CSR_ENABLE_INT_ਨਕਾਬ | XTC_CSR_AUTO_RELOAD_ਨਕਾਬ | XTC_CSR_ਥੱਲੇ_ਗਿਣਤੀ_ਨਕਾਬ | XTC_CSR_INT_occurred_ਨਕਾਬ );
    XIntc_mAckIntr( XPAR_INTC_SINGLE_BASEADDR, 1 );
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
ਖਾਲੀ vTaskISRHandler( ਖਾਲੀ )
{
    ਸਥਿਰ uint32_t ulPending;

    /* Which interrupts are pending? */
    ulPending = XIntc_In32( ( XPAR_INTC_SINGLE_BASEADDR + XIN_IVR_ਵਿੱਥ ) );

    ਜੇ( ulPending < XPAR_INTC_MAX_ਅੰਕ_INTR_INPUTS )
    {
        ਸਥਿਰ XIntc_ਸਦਿਸ਼_ਸਾਰਣੀ_ਇੰਦਰਾਜ * px_ਸਾਰਣੀ_Ptr;
        ਸਥਿਰ XIntc_Config * pxConfig;
        ਸਥਿਰ uint32_t ul_ਰੁਕਾਵਟ_ਨਕਾਬ;

        ul_ਰੁਕਾਵਟ_ਨਕਾਬ = ( uint32_t ) 1 << ulPending;

        /* Get the configuration data using the device ID */
        pxConfig = &XIntc_Config_ਸਾਰਣੀ[ ( uint32_t ) XPAR_INTC_SINGLE_DEVICE_ID ];

        px_ਸਾਰਣੀ_Ptr = &( pxConfig->Handler_ਸਾਰਣੀ[ ulPending ] );

        ਜੇ( pxConfig->AckBeforeService & ( ul_ਰੁਕਾਵਟ_ਨਕਾਬ ) )
        {
            XIntc_mAckIntr( pxConfig->ਅਧਾਰ_ਪਤਾ, ul_ਰੁਕਾਵਟ_ਨਕਾਬ );
            px_ਸਾਰਣੀ_Ptr->Handler( px_ਸਾਰਣੀ_Ptr->Call_ਪਿੱਠ_Ref );
        }
        ਨਹੀਂਤਾਂ
        {
            px_ਸਾਰਣੀ_Ptr->Handler( px_ਸਾਰਣੀ_Ptr->Call_ਪਿੱਠ_Ref );
            XIntc_mAckIntr( pxConfig->ਅਧਾਰ_ਪਤਾ, ul_ਰੁਕਾਵਟ_ਨਕਾਬ );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.
 */
ਖਾਲੀ vTickISR( ਖਾਲੀ * pv_ਅਧਾਰ_ਪਤਾ )
{
    uint32_t ulCSR;

    /* Increment the RTOS tick - this might cause a task to unblock. */
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the timer interrupt */
    ulCSR = XTmr_Ctr_m_Get_Control_ਸਥਿਤੀ_Reg( XPAR_OPB_TIMER_1_BASEADDR, 0 );
    XTmr_Ctr_m_ਸੈੱਟ_Control_ਸਥਿਤੀ_Reg( XPAR_OPB_TIMER_1_BASEADDR, ਪੋਰਟ_COUNTER_0, ulCSR );
}
/*-----------------------------------------------------------*/
