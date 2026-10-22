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

Changes from V1.2.0:

    + prvPortResetPIC() is now called last thing before the end of the
      preemptive tick routine.

Changes from V2.6.1

    + Replaced the sUsingPreemption variable with the configUSE_PREEMPTION
      macro to be consistent with the later ports.

Changes from V4.0.1

    + Add function prvSetTickFrequencyDefault() to set the DOS tick back to
      its proper value when the scheduler exits.
*/

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <i86.h>
#అన్తర్భావ <dos.h>
#అన్తర్భావ <setjmp.h>

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "portasm.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the industrial
 * PC port.
 *----------------------------------------------------------*/

/*lint -e950 Non ANSI reserved words okay in this file only. */

#నిర్వచించు పోర్టు_TIMER_INT_సంఖ్య    0x08

/* Setup hardware for required tick interrupt rate. */
స్థిర శూన్య prv_సమితి_Tick_Frequency( uint32_t ul_Tick_రేటు_Hz );

/* Restore hardware to as it was prior to starting the scheduler. */
స్థిర శూన్య prvExitFunction( శూన్య );

/* Either chain to the DOS tick (which itself clears the PIC) or clear the PIC
directly.  We chain to the DOS tick as close as possible to the standard DOS
tick rate. */
స్థిర శూన్య prv_పోర్టు_Reset_PIC( శూన్య );

/* The tick ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ఒకవేళ configUSE_PREEMPTION == 1
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

/* Set the tick frequency back so the floppy drive works correctly when the
scheduler exits. */
స్థిర శూన్య prv_సమితి_Tick_Frequency_Default( శూన్య );

/*lint -e956 File scopes necessary here. */

/* Used to signal when to chain to the DOS tick, and when to just clear the PIC ourselves. */
స్థిర int16_t sDOSTickCounter;

/* Set true when the vectors are set so the scheduler will service the tick. */
స్థిర int16_t sSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
స్థిర శూన్య ( __interrupt __far *pxOldSwitchISR )();

/* Points to the original routine installed on the vector we use to chain to the DOS tick.  This is then used to restore the original routine during prvExitFunction(). */
స్థిర శూన్య ( __interrupt __far *pxOldSwitchISRPlus1 )();

/* Used to restore the original DOS context when the scheduler is ended. */
స్థిర jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
pxISR pxOriginalTickISR;

    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( పోర్టు_SWITCH_INT_సంఖ్య );
    pxOriginalTickISR = _dos_getvect( పోర్టు_TIMER_INT_సంఖ్య );
    pxOldSwitchISRPlus1 = _dos_getvect( పోర్టు_SWITCH_INT_సంఖ్య + 1 );

    prv_సమితి_Tick_Frequency( config_TICK_రేటు_HZ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( పోర్టు_SWITCH_INT_సంఖ్య, prvYieldProcessor );

    /* Put the old tick on a different interrupt number so we can
    call it when we want. */
    _dos_setvect( పోర్టు_SWITCH_INT_సంఖ్య + 1, pxOriginalTickISR );

    #ఒకవేళ configUSE_PREEMPTION == 1
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

    /* Setup a counter that is used to call the DOS interrupt as close
    to it's original frequency as can be achieved given our chosen tick
    frequency. */
    sDOSTickCounter = పోర్టు_TICKS_చొప్పున_DOS_TICK;

    /* Clean up function if we want to return to DOS. */
    ఒకవేళ( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        sSchedulerRunning = pdFALSE;
    }
    లేకపోతే
    {
        sSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        పోర్టు_మొదటి_CONTEXT();
    }

    తిరిగి sSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The tick ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ఒకవేళ configUSE_PREEMPTION == 1
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    స్థిర శూన్య __interrupt __far prvPreemptiveTick( శూన్య )
    {
        /* Get the scheduler to update the task states following the tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            పోర్టు_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        prv_పోర్టు_Reset_PIC();
    }
#లేకపోతే
    స్థిర శూన్య __interrupt __far prvNonPreemptiveTick( శూన్య )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        prv_పోర్టు_Reset_PIC();
    }
#అయితే_ముగింపు
/*-----------------------------------------------------------*/


స్థిర శూన్య __interrupt __far prvYieldProcessor( శూన్య )
{
    /* Switch in the context of the next task to be run. */
    పోర్టు_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_పోర్టు_Reset_PIC( శూన్య )
{
    /* We are going to call the DOS tick interrupt at as close a
    frequency to the normal DOS tick as possible. */

    /* WE SHOULD NOT DO THIS IF YIELD WAS CALLED. */
    --sDOSTickCounter;
    ఒకవేళ( sDOSTickCounter <= 0 )
    {
        sDOSTickCounter = ( int16_t ) పోర్టు_TICKS_చొప్పున_DOS_TICK;
        __asm{ పూర్ణాంకం  పోర్టు_SWITCH_INT_సంఖ్య + 1 };
    }
    లేకపోతే
    {
        /* Reset the PIC as the DOS tick is not being called to
        do it. */
        __asm
        {
            mov al, 20H
            బహిర్గతం 20H, al
        };
    }
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
శూన్య ( __interrupt __far *pxOriginalTickISR )();

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    పోర్టు_DISABLE_INTERRUPTS();
    ఒకవేళ( sSchedulerRunning == pdTRUE )
    {
        /* Set the DOS tick back onto the timer ticker. */
        pxOriginalTickISR = _dos_getvect( పోర్టు_SWITCH_INT_సంఖ్య + 1 );
        _dos_setvect( పోర్టు_TIMER_INT_సంఖ్య, pxOriginalTickISR );
        prv_సమితి_Tick_Frequency_Default();

        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( పోర్టు_SWITCH_INT_సంఖ్య, pxOldSwitchISR );
        _dos_setvect( పోర్టు_SWITCH_INT_సంఖ్య + 1, pxOldSwitchISRPlus1 );
    }
    /* The tick timer is back how DOS wants it.  We can re-enable
    interrupts without the scheduler being called. */
    పోర్టు_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_సమితి_Tick_Frequency( uint32_t ul_Tick_రేటు_Hz )
{
స్థిరరాశి uint16_t us_PIT_బహుళకం = ( uint16_t ) 0x43;
స్థిరరాశి uint16_t usPIT0 = ( uint16_t ) 0x40;
స్థిరరాశి uint32_t ulPIT_CONST = ( uint32_t ) 1193180;
స్థిరరాశి uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;
uint32_t ulOutput;

    /* Setup the 8245 to tick at the wanted frequency. */
    పోర్టు_OUTPUT_BYTE( us_PIT_బహుళకం, us8254_CTR0_MODE3 );
    ulOutput = ulPIT_CONST / ul_Tick_రేటు_Hz;

    పోర్టు_OUTPUT_BYTE( usPIT0, ( uint16_t )( ulOutput & ( uint32_t ) 0xff ) );
    ulOutput >>= 8;
    పోర్టు_OUTPUT_BYTE( usPIT0, ( uint16_t ) ( ulOutput & ( uint32_t ) 0xff ) );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_సమితి_Tick_Frequency_Default( శూన్య )
{
స్థిరరాశి uint16_t us_PIT_బహుళకం = ( uint16_t ) 0x43;
స్థిరరాశి uint16_t usPIT0 = ( uint16_t ) 0x40;
స్థిరరాశి uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;

    పోర్టు_OUTPUT_BYTE( us_PIT_బహుళకం, us8254_CTR0_MODE3 );
    పోర్టు_OUTPUT_BYTE( usPIT0,0 );
    పోర్టు_OUTPUT_BYTE( usPIT0,0 );
}


/*lint +e950 */
