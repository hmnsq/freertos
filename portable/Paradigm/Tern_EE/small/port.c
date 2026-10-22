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
#تعریف_کن پورت_PRESCALE_مقدار ( 16 )
#تعریف_کن پورت_TIMER_COMPARE ( configCPU_CLOCK_HZ  / ( config_TICK_نرخ_HZ * 4UL ) )

/* From the RDC data sheet. */
#تعریف_کن پورت_ENABLE_TIMER_AND_وقفه  ( uint16_t ) 0xe00b
#تعریف_کن پورت_ENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#تعریف_کن پورت_EIO_ثبات 0xff22
#تعریف_کن پورت_CLEAR_وقفه 0x0008

/* Setup the hardware to generate the required tick frequency. */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

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
#پایان_اگر

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساكن فراغ __interrupt __far prvYieldProcessor( فراغ );

/*-----------------------------------------------------------*/
/* See header file for description. */
پشته_Type_t *px_پورت_Initialise_پشته( پشته_Type_t *px_بالاترین_از_پشته, TaskFunction_t px_کد, فراغ *pvParameters )
{
پشته_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_بالاترین_از_پشته = 0x1111;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x2222;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x3333;
    px_بالاترین_از_پشته--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_بالاترین_از_پشته = FP_OFF( pvParameters );
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = FP_OFF( px_کد );
    px_بالاترین_از_پشته--;

    /* Next the status register and interrupt return address. */
    *px_بالاترین_از_پشته = پورت_INITIAL_SW;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = FP_SEG( px_کد );
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = FP_OFF( px_کد );
    px_بالاترین_از_پشته--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xAAAA; /* AX */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xBBBB; /* BX */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xCCCC; /* CX */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xDDDD; /* DX */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xEEEE; /* ES */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = DS_Reg;                     /* DS */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0123; /* SI */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xDDDD; /* DI */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0xBBBB; /* BP */

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( پورت_SWITCH_INT_عدد, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_راهاندازی_Timer_وقفه();

    /* Kick off the scheduler by setting up the context of the first task. */
    پورت_اولی_CONTEXT();

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
            پورت_انتها_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( پورت_EIO_ثبات, پورت_CLEAR_وقفه );
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( پورت_EIO_ثبات, پورت_CLEAR_وقفه );
    }
#پایان_اگر
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    پورت_انتها_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
ثابت uint32_t ul_Compare_مقدار = پورت_TIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_مقدار >> 4 );
    t2_init( پورت_ENABLE_TIMER, پورت_PRESCALE_مقدار, عدم );

    #إذا( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( پورت_ENABLE_TIMER_AND_وقفه, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #وإلا
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( پورت_ENABLE_TIMER_AND_وقفه, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #پایان_اگر
}
