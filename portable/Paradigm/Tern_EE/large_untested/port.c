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
#ਅਨ੍ਤਰ੍ਭਾਵ <embedded.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <ae.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE ( uint16_t ) ( ( configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ ) / ( uint32_t ) 4 )

/* From the RDC data sheet. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_TIMER_AND_ਰੁਕਾਵਟ ( uint16_t ) 0xe001

/* Interrupt control. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EIO_ਰਜਿਸਟਰ 0xff22
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ 0x0008

/* Setup the hardware to generate the required tick frequency. */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ਜੇ( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvPreemptiveTick( ਖਾਲੀ );
#ਨਹੀਂਤਾਂ
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvNonPreemptiveTick( ਖਾਲੀ );
#ਜੇ_ਅੰਤ

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ਸਥਿਰ ਖਾਲੀ __interrupt __far prvYieldProcessor( ਖਾਲੀ );

/* The timer initialisation functions leave interrupts enabled,
which is not what we want.  This ISR is installed temporarily in case
the timer fires before we get a change to disable interrupts again. */
ਸਥਿਰ ਖਾਲੀ __interrupt __far prvDummyISR( ਖਾਲੀ );

/*-----------------------------------------------------------*/
/* See header file for description. */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
ਢੇਰ_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1111;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2222;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x3333;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = FP_SEG( pvParameters );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = FP_OFF( pvParameters );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = FP_SEG( px_ਕੋਡ );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = FP_OFF( px_ਕੋਡ );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Next the status register and interrupt return address. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_SW;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = FP_SEG( px_ਕੋਡ );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = FP_OFF( px_ਕੋਡ );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xAAAA; /* AX */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xBBBB; /* BX */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xCCCC; /* CX */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xDDDD; /* DX */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xEEEE; /* ES */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = DS_Reg;                     /* DS */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0123; /* SI */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xDDDD; /* DI */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xBBBB; /* BP */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Kick off the scheduler by setting up the context of the first task. */
    ਪੋਰਟ_ਪਹਿਲਾ_CONTEXT();

    /* Should not get here! */
    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ __interrupt __far prvDummyISR( ਖਾਲੀ )
{
    /* The timer initialisation functions leave interrupts enabled,
    which is not what we want.  This ISR is installed temporarily in case
    the timer fires before we get a change to disable interrupts again. */
    outport( ਪੋਰਟ_EIO_ਰਜਿਸਟਰ, ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ );
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ਜੇ( configUSE_PREEMPTION == 1 )
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvPreemptiveTick( ਖਾਲੀ )
    {
        /* Get the scheduler to update the task states following the tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            ਪੋਰਟ_SWITCH_CONTEXT();
        }

        /* Reset interrupt. */
        outport( ਪੋਰਟ_EIO_ਰਜਿਸਟਰ, ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ );
    }
#ਨਹੀਂਤਾਂ
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvNonPreemptiveTick( ਖਾਲੀ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( ਪੋਰਟ_EIO_ਰਜਿਸਟਰ, ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ );
    }
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ __interrupt __far prvYieldProcessor( ਖਾਲੀ )
{
    /* Switch in the context of the next task to be run. */
    ਪੋਰਟ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
ਅਚਲ uint16_t usTimerACompare = ਪੋਰਟ_TIMER_COMPARE, usTimerAMode = ਪੋਰਟ_ENABLE_TIMER_AND_ਰੁਕਾਵਟ;
ਅਚਲ uint16_t usT2_IRQ = 0x13;

    /* Configure the timer, the dummy handler is used here as the init
    function leaves interrupts enabled. */
    t2_init( usTimerAMode, usTimerACompare, prvDummyISR );

    /* Disable interrupts again before installing the real handlers. */
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    #ਜੇ( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        setvect( usT2_IRQ, prvPreemptiveTick );
    #ਨਹੀਂਤਾਂ
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        setvect( usT2_IRQ, prvNonPreemptiveTick );
    #ਜੇ_ਅੰਤ
}
