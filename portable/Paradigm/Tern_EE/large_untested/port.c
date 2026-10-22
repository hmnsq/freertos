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
 * Implementation of functions defined in portable.h for the Tern EE 186
 * port.
 *----------------------------------------------------------*/

/* Library includes. */
#شامل <embedded.h>
#شامل <ae.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#تعریف_کرو پورٹ_TIMER_COMPARE ( uint16_t ) ( ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) / ( uint32_t ) 4 )

/* From the RDC data sheet. */
#تعریف_کرو پورٹ_ENABLE_TIMER_AND_مداخلت ( uint16_t ) 0xe001

/* Interrupt control. */
#تعریف_کرو پورٹ_EIO_رجسٹر 0xff22
#تعریف_کرو پورٹ_CLEAR_مداخلت 0x0008

/* Setup the hardware to generate the required tick frequency. */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#اگر( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ساکن خالی __interrupt __far prvPreemptiveTick( خالی );
#ورنہ
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ساکن خالی __interrupt __far prvNonPreemptiveTick( خالی );
#اگر_ختم

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساکن خالی __interrupt __far prvYieldProcessor( خالی );

/* The timer initialisation functions leave interrupts enabled,
which is not what we want.  This ISR is installed temporarily in case
the timer fires before we get a change to disable interrupts again. */
ساکن خالی __interrupt __far prvDummyISR( خالی );

/*-----------------------------------------------------------*/
/* See header file for description. */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_کا_ڈھیر, TaskFunction_t px_رمز, خالی *pvParameters )
{
ڈھیر_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_چوٹی_کا_ڈھیر = 0x1111;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x2222;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x3333;
    px_چوٹی_کا_ڈھیر--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_چوٹی_کا_ڈھیر = FP_SEG( pvParameters );
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = FP_OFF( pvParameters );
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = FP_SEG( px_رمز );
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = FP_OFF( px_رمز );
    px_چوٹی_کا_ڈھیر--;

    /* Next the status register and interrupt return address. */
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_SW;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = FP_SEG( px_رمز );
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = FP_OFF( px_رمز );
    px_چوٹی_کا_ڈھیر--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xAAAA; /* AX */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xBBBB; /* BX */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xCCCC; /* CX */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xDDDD; /* DX */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xEEEE; /* ES */
    px_چوٹی_کا_ڈھیر--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_چوٹی_کا_ڈھیر = DS_Reg;                     /* DS */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0123; /* SI */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xDDDD; /* DI */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xBBBB; /* BP */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( پورٹ_SWITCH_INT_نمبر, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_تیاری_Timer_مداخلت();

    /* Kick off the scheduler by setting up the context of the first task. */
    پورٹ_پہلا_CONTEXT();

    /* Should not get here! */
    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

ساکن خالی __interrupt __far prvDummyISR( خالی )
{
    /* The timer initialisation functions leave interrupts enabled,
    which is not what we want.  This ISR is installed temporarily in case
    the timer fires before we get a change to disable interrupts again. */
    outport( پورٹ_EIO_رجسٹر, پورٹ_CLEAR_مداخلت );
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#اگر( configUSE_PREEMPTION == 1 )
    ساکن خالی __interrupt __far prvPreemptiveTick( خالی )
    {
        /* Get the scheduler to update the task states following the tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            پورٹ_SWITCH_CONTEXT();
        }

        /* Reset interrupt. */
        outport( پورٹ_EIO_رجسٹر, پورٹ_CLEAR_مداخلت );
    }
#ورنہ
    ساکن خالی __interrupt __far prvNonPreemptiveTick( خالی )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( پورٹ_EIO_رجسٹر, پورٹ_CLEAR_مداخلت );
    }
#اگر_ختم
/*-----------------------------------------------------------*/

ساکن خالی __interrupt __far prvYieldProcessor( خالی )
{
    /* Switch in the context of the next task to be run. */
    پورٹ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
ثابت uint16_t usTimerACompare = پورٹ_TIMER_COMPARE, usTimerAMode = پورٹ_ENABLE_TIMER_AND_مداخلت;
ثابت uint16_t usT2_IRQ = 0x13;

    /* Configure the timer, the dummy handler is used here as the init
    function leaves interrupts enabled. */
    t2_init( usTimerAMode, usTimerACompare, prvDummyISR );

    /* Disable interrupts again before installing the real handlers. */
    پورٹ_DISABLE_INTERRUPTS();

    #اگر( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        setvect( usT2_IRQ, prvPreemptiveTick );
    #ورنہ
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        setvect( usT2_IRQ, prvNonPreemptiveTick );
    #اگر_ختم
}
