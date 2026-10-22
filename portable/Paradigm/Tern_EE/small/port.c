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
#ضمن <embedded.h>
#ضمن <ae.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#تعریف_کرو پورٹ_PRESCALE_قدر ( 16 )
#تعریف_کرو پورٹ_TIMER_COMPARE ( configCPU_CLOCK_HZ  / ( config_TICK_شرح_HZ * 4UL ) )

/* From the RDC data sheet. */
#تعریف_کرو پورٹ_ENABLE_TIMER_AND_رکاوٹ  ( uint16_t ) 0xe00b
#تعریف_کرو پورٹ_ENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#تعریف_کرو پورٹ_EIO_رجسٹر 0xff22
#تعریف_کرو پورٹ_CLEAR_رکاوٹ 0x0008

/* Setup the hardware to generate the required tick frequency. */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#إذا( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ساكن فراغ __interrupt __far prvPreemptiveTick( فراغ );
#وإلا
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ );
#جے_انت

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساكن فراغ __interrupt __far prvYieldProcessor( فراغ );

/*-----------------------------------------------------------*/
/* See header file for description. */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_دا_ڈھیر, TaskFunction_t px_کوڈ, فراغ *pvParameters )
{
ڈھیر_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_چوٹی_دا_ڈھیر = 0x1111;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2222;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x3333;
    px_چوٹی_دا_ڈھیر--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_چوٹی_دا_ڈھیر = FP_OFF( pvParameters );
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = FP_OFF( px_کوڈ );
    px_چوٹی_دا_ڈھیر--;

    /* Next the status register and interrupt return address. */
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_SW;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = FP_SEG( px_کوڈ );
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = FP_OFF( px_کوڈ );
    px_چوٹی_دا_ڈھیر--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xAAAA; /* AX */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xBBBB; /* BX */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xCCCC; /* CX */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xDDDD; /* DX */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xEEEE; /* ES */
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = DS_Reg;                     /* DS */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x0123; /* SI */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xDDDD; /* DI */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xBBBB; /* BP */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( پورٹ_SWITCH_INT_نمبر, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_تیاری_Timer_رکاوٹ();

    /* Kick off the scheduler by setting up the context of the first task. */
    پورٹ_پہلا_CONTEXT();

    /* Should not get here! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#إذا( configUSE_PREEMPTION == 1 )
    ساكن فراغ __interrupt __far prvPreemptiveTick( فراغ )
    {
        /* Get the scheduler to update the task states following the tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            پورٹ_سرا_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( پورٹ_EIO_رجسٹر, پورٹ_CLEAR_رکاوٹ );
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( پورٹ_EIO_رجسٹر, پورٹ_CLEAR_رکاوٹ );
    }
#جے_انت
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    پورٹ_سرا_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
ثابت uint32_t ul_Compare_قدر = پورٹ_TIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_قدر >> 4 );
    t2_init( پورٹ_ENABLE_TIMER, پورٹ_PRESCALE_قدر, عدم );

    #إذا( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( پورٹ_ENABLE_TIMER_AND_رکاوٹ, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #وإلا
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( پورٹ_ENABLE_TIMER_AND_رکاوٹ, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #جے_انت
}
