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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <i86.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dos.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <setjmp.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portasm.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the industrial
 * PC port.
 *----------------------------------------------------------*/

/*lint -e950 Non ANSI reserved words okay in this file only. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_INT_ਸੰਖਿਆ    0x08

/* Setup hardware for required tick interrupt rate. */
ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_Tick_Frequency( uint32_t ul_Tick_ਦਰ_Hz );

/* Restore hardware to as it was prior to starting the scheduler. */
ਸਥਿਰ ਖਾਲੀ prvExitFunction( ਖਾਲੀ );

/* Either chain to the DOS tick (which itself clears the PIC) or clear the PIC
directly.  We chain to the DOS tick as close as possible to the standard DOS
tick rate. */
ਸਥਿਰ ਖਾਲੀ prv_ਪੋਰਟ_Reset_PIC( ਖਾਲੀ );

/* The tick ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ਜੇ configUSE_PREEMPTION == 1
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

/* Set the tick frequency back so the floppy drive works correctly when the
scheduler exits. */
ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_Tick_Frequency_Default( ਖਾਲੀ );

/*lint -e956 File scopes necessary here. */

/* Used to signal when to chain to the DOS tick, and when to just clear the PIC ourselves. */
ਸਥਿਰ int16_t sDOSTickCounter;

/* Set true when the vectors are set so the scheduler will service the tick. */
ਸਥਿਰ int16_t sSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
ਸਥਿਰ ਖਾਲੀ ( __interrupt __far *pxOldSwitchISR )();

/* Points to the original routine installed on the vector we use to chain to the DOS tick.  This is then used to restore the original routine during prvExitFunction(). */
ਸਥਿਰ ਖਾਲੀ ( __interrupt __far *pxOldSwitchISRPlus1 )();

/* Used to restore the original DOS context when the scheduler is ended. */
ਸਥਿਰ jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
pxISR pxOriginalTickISR;

    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ );
    pxOriginalTickISR = _dos_getvect( ਪੋਰਟ_TIMER_INT_ਸੰਖਿਆ );
    pxOldSwitchISRPlus1 = _dos_getvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ + 1 );

    prv_ਸੈੱਟ_Tick_Frequency( config_TICK_ਦਰ_HZ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ, prvYieldProcessor );

    /* Put the old tick on a different interrupt number so we can
    call it when we want. */
    _dos_setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ + 1, pxOriginalTickISR );

    #ਜੇ configUSE_PREEMPTION == 1
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( ਪੋਰਟ_TIMER_INT_ਸੰਖਿਆ, prvPreemptiveTick );
    }
    #ਨਹੀਂਤਾਂ
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( ਪੋਰਟ_TIMER_INT_ਸੰਖਿਆ, prvNonPreemptiveTick );
    }
    #ਜੇ_ਅੰਤ

    /* Setup a counter that is used to call the DOS interrupt as close
    to it's original frequency as can be achieved given our chosen tick
    frequency. */
    sDOSTickCounter = ਪੋਰਟ_TICKS_ਪ੍ਰਤੀ_DOS_TICK;

    /* Clean up function if we want to return to DOS. */
    ਜੇ( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        sSchedulerRunning = pdFALSE;
    }
    ਨਹੀਂਤਾਂ
    {
        sSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        ਪੋਰਟ_ਪਹਿਲਾ_CONTEXT();
    }

    ਵਾਪਸ sSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The tick ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ਜੇ configUSE_PREEMPTION == 1
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvPreemptiveTick( ਖਾਲੀ )
    {
        /* Get the scheduler to update the task states following the tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            ਪੋਰਟ_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        prv_ਪੋਰਟ_Reset_PIC();
    }
#ਨਹੀਂਤਾਂ
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvNonPreemptiveTick( ਖਾਲੀ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        prv_ਪੋਰਟ_Reset_PIC();
    }
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/


ਸਥਿਰ ਖਾਲੀ __interrupt __far prvYieldProcessor( ਖਾਲੀ )
{
    /* Switch in the context of the next task to be run. */
    ਪੋਰਟ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਪੋਰਟ_Reset_PIC( ਖਾਲੀ )
{
    /* We are going to call the DOS tick interrupt at as close a
    frequency to the normal DOS tick as possible. */

    /* WE SHOULD NOT DO THIS IF YIELD WAS CALLED. */
    --sDOSTickCounter;
    ਜੇ( sDOSTickCounter <= 0 )
    {
        sDOSTickCounter = ( int16_t ) ਪੋਰਟ_TICKS_ਪ੍ਰਤੀ_DOS_TICK;
        __asm{ ਪੂਰਨ  ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ + 1 };
    }
    ਨਹੀਂਤਾਂ
    {
        /* Reset the PIC as the DOS tick is not being called to
        do it. */
        __asm
        {
            mov al, 20H
            ਬਾਹਰਲਾ 20H, al
        };
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvExitFunction( ਖਾਲੀ )
{
ਖਾਲੀ ( __interrupt __far *pxOriginalTickISR )();

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    ਜੇ( sSchedulerRunning == pdTRUE )
    {
        /* Set the DOS tick back onto the timer ticker. */
        pxOriginalTickISR = _dos_getvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ + 1 );
        _dos_setvect( ਪੋਰਟ_TIMER_INT_ਸੰਖਿਆ, pxOriginalTickISR );
        prv_ਸੈੱਟ_Tick_Frequency_Default();

        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ, pxOldSwitchISR );
        _dos_setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ + 1, pxOldSwitchISRPlus1 );
    }
    /* The tick timer is back how DOS wants it.  We can re-enable
    interrupts without the scheduler being called. */
    ਪੋਰਟ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_Tick_Frequency( uint32_t ul_Tick_ਦਰ_Hz )
{
ਅਚਲ uint16_t us_PIT_ਬਹੁਲਕ = ( uint16_t ) 0x43;
ਅਚਲ uint16_t usPIT0 = ( uint16_t ) 0x40;
ਅਚਲ uint32_t ulPIT_CONST = ( uint32_t ) 1193180;
ਅਚਲ uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;
uint32_t ulOutput;

    /* Setup the 8245 to tick at the wanted frequency. */
    ਪੋਰਟ_OUTPUT_BYTE( us_PIT_ਬਹੁਲਕ, us8254_CTR0_MODE3 );
    ulOutput = ulPIT_CONST / ul_Tick_ਦਰ_Hz;

    ਪੋਰਟ_OUTPUT_BYTE( usPIT0, ( uint16_t )( ulOutput & ( uint32_t ) 0xff ) );
    ulOutput >>= 8;
    ਪੋਰਟ_OUTPUT_BYTE( usPIT0, ( uint16_t ) ( ulOutput & ( uint32_t ) 0xff ) );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_Tick_Frequency_Default( ਖਾਲੀ )
{
ਅਚਲ uint16_t us_PIT_ਬਹੁਲਕ = ( uint16_t ) 0x43;
ਅਚਲ uint16_t usPIT0 = ( uint16_t ) 0x40;
ਅਚਲ uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;

    ਪੋਰਟ_OUTPUT_BYTE( us_PIT_ਬਹੁਲਕ, us8254_CTR0_MODE3 );
    ਪੋਰਟ_OUTPUT_BYTE( usPIT0,0 );
    ਪੋਰਟ_OUTPUT_BYTE( usPIT0,0 );
}


/*lint +e950 */
