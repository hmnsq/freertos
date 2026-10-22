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
#అన్తర్భావ <embedded.h>
#అన్తర్భావ <ae.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#నిర్వచించు పోర్టు_PRESCALE_విలువ ( 16 )
#నిర్వచించు పోర్టు_TIMER_COMPARE ( configCPU_CLOCK_HZ  / ( config_TICK_రేటు_HZ * 4UL ) )

/* From the RDC data sheet. */
#నిర్వచించు పోర్టు_ENABLE_TIMER_AND_అంతరాయం  ( uint16_t ) 0xe00b
#నిర్వచించు పోర్టు_ENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#నిర్వచించు పోర్టు_EIO_రిజిస్టరు 0xff22
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం 0x0008

/* Setup the hardware to generate the required tick frequency. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ఒకవేళ( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    స్థిర శూన్య __interrupt __far prvPreemptiveTick( శూన్య );
#లేకపోతే
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    స్థిర శూన్య __interrupt __far prvNonPreemptiveTick( శూన్య );
#అయితే_ముగింపు

/* Trap routine used by taskYIELD() to manually cause a context switch. */
స్థిర శూన్య __interrupt __far prvYieldProcessor( శూన్య );

/*-----------------------------------------------------------*/
/* See header file for description. */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
దొంతర_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_శిఖరం_యొక్క_దొంతర = 0x1111;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2222;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x3333;
    px_శిఖరం_యొక్క_దొంతర--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_శిఖరం_యొక్క_దొంతర = FP_OFF( pvParameters );
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_OFF( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;

    /* Next the status register and interrupt return address. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_SW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_SEG( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_OFF( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xAAAA; /* AX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xBBBB; /* BX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xCCCC; /* CX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDDDD; /* DX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xEEEE; /* ES */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = DS_Reg;                     /* DS */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0123; /* SI */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDDDD; /* DI */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xBBBB; /* BP */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( పోర్టు_SWITCH_INT_సంఖ్య, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Kick off the scheduler by setting up the context of the first task. */
    పోర్టు_మొదటి_CONTEXT();

    /* Should not get here! */
    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ఒకవేళ( configUSE_PREEMPTION == 1 )
    స్థిర శూన్య __interrupt __far prvPreemptiveTick( శూన్య )
    {
        /* Get the scheduler to update the task states following the tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            పోర్టు_చివర_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( పోర్టు_EIO_రిజిస్టరు, పోర్టు_CLEAR_అంతరాయం );
    }
#లేకపోతే
    స్థిర శూన్య __interrupt __far prvNonPreemptiveTick( శూన్య )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( పోర్టు_EIO_రిజిస్టరు, పోర్టు_CLEAR_అంతరాయం );
    }
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

స్థిర శూన్య __interrupt __far prvYieldProcessor( శూన్య )
{
    /* Switch in the context of the next task to be run. */
    పోర్టు_చివర_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
స్థిరరాశి uint32_t ul_Compare_విలువ = పోర్టు_TIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_విలువ >> 4 );
    t2_init( పోర్టు_ENABLE_TIMER, పోర్టు_PRESCALE_విలువ, ఖాళీ );

    #ఒకవేళ( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( పోర్టు_ENABLE_TIMER_AND_అంతరాయం, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #లేకపోతే
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( పోర్టు_ENABLE_TIMER_AND_అంతరాయం, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #అయితే_ముగింపు
}
