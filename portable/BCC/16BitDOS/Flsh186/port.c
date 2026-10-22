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

/*
Changes from V1.00:

    + Call to taskYIELD() from within tick ISR has been replaced by the more
      efficient portSWITCH_CONTEXT().
    + ISR function definitions renamed to include the prv prefix.

Changes from V2.6.1

    + Replaced the sUsingPreemption variable with the configUSE_PREEMPTION
      macro to be consistent with the later ports.
*/

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the Flashlite 186
 * port.
 *----------------------------------------------------------*/

#అన్తర్భావ <dos.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <setjmp.h>

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "portasm.h"

/*lint -e950 Non ANSI reserved words okay in this file only. */

#నిర్వచించు పోర్టు_TIMER_EOI_TYPE      ( 8 )
#నిర్వచించు పోర్టు_RESET_PIC()         పోర్టు_OUTPUT_మాట( ( uint16_t ) 0xff22, పోర్టు_TIMER_EOI_TYPE )
#నిర్వచించు పోర్టు_TIMER_INT_సంఖ్య    0x12

#నిర్వచించు పోర్టు_TIMER_1_CONTROL_రిజిస్టరు    ( ( uint16_t ) 0xff5e )
#నిర్వచించు పోర్టు_TIMER_0_CONTROL_రిజిస్టరు    ( ( uint16_t ) 0xff56 )
#నిర్వచించు పోర్టు_TIMER_అంతరాయం_ENABLE      ( ( uint16_t ) 0x2000 )

/* Setup the hardware to generate the required tick frequency. */
స్థిర శూన్య prv_సమితి_Tick_Frequency( uint32_t ul_Tick_రేటు_Hz );

/* Set the hardware back to the state as per before the scheduler started. */
స్థిర శూన్య prvExitFunction( శూన్య );

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

/*lint -e956 File scopes necessary here. */

/* Set true when the vectors are set so the scheduler will service the tick. */
స్థిర పునాది_Type_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual
context switches.  This is then used to restore the original routine during
prvExitFunction(). */
స్థిర శూన్య ( __interrupt __far *pxOldSwitchISR )();

/* Used to restore the original DOS context when the scheduler is ended. */
స్థిర jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( పోర్టు_SWITCH_INT_సంఖ్య );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( పోర్టు_SWITCH_INT_సంఖ్య, prvYieldProcessor );

    #ఒకవేళ( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( పోర్టు_TIMER_INT_సంఖ్య, prvPreemptiveTick );
    }
    #లేకపోతే
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( పోర్టు_TIMER_INT_సంఖ్య, prvNonPreemptiveTick );
    }
    #అయితే_ముగింపు

    prv_సమితి_Tick_Frequency( config_TICK_రేటు_HZ );

    /* Clean up function if we want to return to DOS. */
    ఒకవేళ( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    లేకపోతే
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        పోర్టు_మొదటి_CONTEXT();
    }

    తిరిగి xSchedulerRunning;
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
            పోర్టు_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        పోర్టు_RESET_PIC();
    }
#లేకపోతే
    స్థిర శూన్య __interrupt __far prvNonPreemptiveTick( శూన్య )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        పోర్టు_RESET_PIC();
    }
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

స్థిర శూన్య __interrupt __far prvYieldProcessor( శూన్య )
{
    /* Switch in the context of the next task to be run. */
    పోర్టు_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvExitFunction( శూన్య )
{
స్థిరరాశి uint16_t usTimerDisable = 0x0000;
uint16_t usTimer0Control;

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    పోర్టు_DISABLE_INTERRUPTS();
    ఒకవేళ( xSchedulerRunning == pdTRUE )
    {
        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( పోర్టు_SWITCH_INT_సంఖ్య, pxOldSwitchISR );
    }

    /* Disable the timer used for the tick to ensure the scheduler is
    not called before restoring interrupts.  There was previously nothing
    on this timer so there is no old ISR to restore. */
    పోర్టు_OUTPUT_మాట( పోర్టు_TIMER_1_CONTROL_రిజిస్టరు, usTimerDisable );

    /* Restart the DOS tick. */
    usTimer0Control = పోర్టు_ఆదానం_మాట( పోర్టు_TIMER_0_CONTROL_రిజిస్టరు );
    usTimer0Control |= పోర్టు_TIMER_అంతరాయం_ENABLE;
    పోర్టు_OUTPUT_మాట( పోర్టు_TIMER_0_CONTROL_రిజిస్టరు, usTimer0Control );


    పోర్టు_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_సమితి_Tick_Frequency( uint32_t ul_Tick_రేటు_Hz )
{
స్థిరరాశి uint16_t us_Max_లెక్క_రిజిస్టరు = 0xff5a;
స్థిరరాశి uint16_t us_Timer_ప్రాధాన్యత_రిజిస్టరు = 0xff32;
స్థిరరాశి uint16_t usTimerEnable = 0xC000;
స్థిరరాశి uint16_t usRetrigger = 0x0001;
స్థిరరాశి uint16_t us_Timer_ఎగువ_ప్రాధాన్యత = 0x0000;
uint16_t usTimer0Control;

/* ( CPU frequency / 4 ) / clock 2 max count [inpw( 0xff62 ) = 7] */

స్థిరరాశి uint32_t ulClockFrequency = ( uint32_t ) 0x7f31a0UL;

uint32_t ul_Timer_లెక్క = ulClockFrequency / ul_Tick_రేటు_Hz;

    పోర్టు_OUTPUT_మాట( పోర్టు_TIMER_1_CONTROL_రిజిస్టరు, usTimerEnable | పోర్టు_TIMER_అంతరాయం_ENABLE | usRetrigger );
    పోర్టు_OUTPUT_మాట( us_Max_లెక్క_రిజిస్టరు, ( uint16_t ) ul_Timer_లెక్క );
    పోర్టు_OUTPUT_మాట( us_Timer_ప్రాధాన్యత_రిజిస్టరు, us_Timer_ఎగువ_ప్రాధాన్యత );

    /* Stop the DOS tick - don't do this if you want to maintain a TOD clock. */
    usTimer0Control = పోర్టు_ఆదానం_మాట( పోర్టు_TIMER_0_CONTROL_రిజిస్టరు );
    usTimer0Control &= ~పోర్టు_TIMER_అంతరాయం_ENABLE;
    పోర్టు_OUTPUT_మాట( పోర్టు_TIMER_0_CONTROL_రిజిస్టరు, usTimer0Control );
}


/*lint +e950 */
