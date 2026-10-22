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
#وصف_ڪريو پورٽ_PRESCALE_قدر ( 16 )
#وصف_ڪريو پورٽ_TIMER_COMPARE ( configCPU_CLOCK_HZ  / ( config_TICK_شرح_HZ * 4UL ) )

/* From the RDC data sheet. */
#وصف_ڪريو پورٽ_ENABLE_TIMER_AND_مداخلت  ( uint16_t ) 0xe00b
#وصف_ڪريو پورٽ_ENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#وصف_ڪريو پورٽ_EIO_رجسٽر 0xff22
#وصف_ڪريو پورٽ_CLEAR_مداخلت 0x0008

/* Setup the hardware to generate the required tick frequency. */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

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
#جيڪڏهن_پورو

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساكن فراغ __interrupt __far prvYieldProcessor( فراغ );

/*-----------------------------------------------------------*/
/* See header file for description. */
ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t *px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{
ڍير_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_چوٽي_جو_ڍير = 0x1111;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x2222;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x3333;
    px_چوٽي_جو_ڍير--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_چوٽي_جو_ڍير = FP_OFF( pvParameters );
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = FP_OFF( px_ڪوڊ );
    px_چوٽي_جو_ڍير--;

    /* Next the status register and interrupt return address. */
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_SW;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = FP_SEG( px_ڪوڊ );
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = FP_OFF( px_ڪوڊ );
    px_چوٽي_جو_ڍير--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xAAAA; /* AX */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xBBBB; /* BX */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xCCCC; /* CX */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xDDDD; /* DX */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xEEEE; /* ES */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = DS_Reg;                     /* DS */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x0123; /* SI */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xDDDD; /* DI */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xBBBB; /* BP */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( پورٽ_SWITCH_INT_عدد, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_تياري_Timer_مداخلت();

    /* Kick off the scheduler by setting up the context of the first task. */
    پورٽ_پهريون_CONTEXT();

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
            پورٽ_پڇاڙي_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( پورٽ_EIO_رجسٽر, پورٽ_CLEAR_مداخلت );
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( پورٽ_EIO_رجسٽر, پورٽ_CLEAR_مداخلت );
    }
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    پورٽ_پڇاڙي_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
ثابت uint32_t ul_Compare_قدر = پورٽ_TIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_قدر >> 4 );
    t2_init( پورٽ_ENABLE_TIMER, پورٽ_PRESCALE_قدر, عدم );

    #إذا( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( پورٽ_ENABLE_TIMER_AND_مداخلت, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #وإلا
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( پورٽ_ENABLE_TIMER_AND_مداخلت, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #جيڪڏهن_پورو
}
