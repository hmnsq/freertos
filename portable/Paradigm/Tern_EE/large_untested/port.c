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
#تعریف_کړه پورټ_TIMER_COMPARE ( uint16_t ) ( ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) / ( uint32_t ) 4 )

/* From the RDC data sheet. */
#تعریف_کړه پورټ_ENABLE_TIMER_AND_مداخله ( uint16_t ) 0xe001

/* Interrupt control. */
#تعریف_کړه پورټ_EIO_ثبتوونکی 0xff22
#تعریف_کړه پورټ_CLEAR_مداخله 0x0008

/* Setup the hardware to generate the required tick frequency. */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

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
#د_که_پای

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساكن فراغ __interrupt __far prvYieldProcessor( فراغ );

/* The timer initialisation functions leave interrupts enabled,
which is not what we want.  This ISR is installed temporarily in case
the timer fires before we get a change to disable interrupts again. */
ساكن فراغ __interrupt __far prvDummyISR( فراغ );

/*-----------------------------------------------------------*/
/* See header file for description. */
ډېری_Type_t *px_پورټ_Initialise_ډېری( ډېری_Type_t *px_سر_د_ډېری, TaskFunction_t px_کوډ, فراغ *pvParameters )
{
ډېری_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_سر_د_ډېری = 0x1111;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x2222;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x3333;
    px_سر_د_ډېری--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_سر_د_ډېری = FP_SEG( pvParameters );
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = FP_OFF( pvParameters );
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = FP_SEG( px_کوډ );
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = FP_OFF( px_کوډ );
    px_سر_د_ډېری--;

    /* Next the status register and interrupt return address. */
    *px_سر_د_ډېری = پورټ_INITIAL_SW;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = FP_SEG( px_کوډ );
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = FP_OFF( px_کوډ );
    px_سر_د_ډېری--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xAAAA; /* AX */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xBBBB; /* BX */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xCCCC; /* CX */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xDDDD; /* DX */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xEEEE; /* ES */
    px_سر_د_ډېری--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_سر_د_ډېری = DS_Reg;                     /* DS */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x0123; /* SI */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xDDDD; /* DI */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xBBBB; /* BP */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( پورټ_SWITCH_INT_شمېره, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_تیاری_Timer_مداخله();

    /* Kick off the scheduler by setting up the context of the first task. */
    پورټ_لومړی_CONTEXT();

    /* Should not get here! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvDummyISR( فراغ )
{
    /* The timer initialisation functions leave interrupts enabled,
    which is not what we want.  This ISR is installed temporarily in case
    the timer fires before we get a change to disable interrupts again. */
    outport( پورټ_EIO_ثبتوونکی, پورټ_CLEAR_مداخله );
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
            پورټ_SWITCH_CONTEXT();
        }

        /* Reset interrupt. */
        outport( پورټ_EIO_ثبتوونکی, پورټ_CLEAR_مداخله );
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( پورټ_EIO_ثبتوونکی, پورټ_CLEAR_مداخله );
    }
#د_که_پای
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    پورټ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
ثابت uint16_t usTimerACompare = پورټ_TIMER_COMPARE, usTimerAMode = پورټ_ENABLE_TIMER_AND_مداخله;
ثابت uint16_t usT2_IRQ = 0x13;

    /* Configure the timer, the dummy handler is used here as the init
    function leaves interrupts enabled. */
    t2_init( usTimerAMode, usTimerACompare, prvDummyISR );

    /* Disable interrupts again before installing the real handlers. */
    پورټ_DISABLE_INTERRUPTS();

    #إذا( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        setvect( usT2_IRQ, prvPreemptiveTick );
    #وإلا
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        setvect( usT2_IRQ, prvNonPreemptiveTick );
    #د_که_پای
}
