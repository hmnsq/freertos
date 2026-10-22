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

#ਅਨ੍ਤਰ੍ਭਾਵ <dos.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <setjmp.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portasm.h"

/*lint -e950 Non ANSI reserved words okay in this file only. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_EOI_TYPE      ( 8 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_PIC()         ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( ( uint16_t ) 0xff22, ਪੋਰਟ_TIMER_EOI_TYPE )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_INT_ਸੰਖਿਆ    0x12

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_1_CONTROL_ਰਜਿਸਟਰ    ( ( uint16_t ) 0xff5e )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_0_CONTROL_ਰਜਿਸਟਰ    ( ( uint16_t ) 0xff56 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_ਰੁਕਾਵਟ_ENABLE      ( ( uint16_t ) 0x2000 )

/* Setup the hardware to generate the required tick frequency. */
ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_Tick_Frequency( uint32_t ul_Tick_ਦਰ_Hz );

/* Set the hardware back to the state as per before the scheduler started. */
ਸਥਿਰ ਖਾਲੀ prvExitFunction( ਖਾਲੀ );

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

/*lint -e956 File scopes necessary here. */

/* Set true when the vectors are set so the scheduler will service the tick. */
ਸਥਿਰ ਅਧਾਰ_Type_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual
context switches.  This is then used to restore the original routine during
prvExitFunction(). */
ਸਥਿਰ ਖਾਲੀ ( __interrupt __far *pxOldSwitchISR )();

/* Used to restore the original DOS context when the scheduler is ended. */
ਸਥਿਰ jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ, prvYieldProcessor );

    #ਜੇ( configUSE_PREEMPTION == 1 )
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

    prv_ਸੈੱਟ_Tick_Frequency( config_TICK_ਦਰ_HZ );

    /* Clean up function if we want to return to DOS. */
    ਜੇ( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    ਨਹੀਂਤਾਂ
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        ਪੋਰਟ_ਪਹਿਲਾ_CONTEXT();
    }

    ਵਾਪਸ xSchedulerRunning;
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

        /* Reset the PIC ready for the next time. */
        ਪੋਰਟ_RESET_PIC();
    }
#ਨਹੀਂਤਾਂ
    ਸਥਿਰ ਖਾਲੀ __interrupt __far prvNonPreemptiveTick( ਖਾਲੀ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        ਪੋਰਟ_RESET_PIC();
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
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvExitFunction( ਖਾਲੀ )
{
ਅਚਲ uint16_t usTimerDisable = 0x0000;
uint16_t usTimer0Control;

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    ਜੇ( xSchedulerRunning == pdTRUE )
    {
        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ, pxOldSwitchISR );
    }

    /* Disable the timer used for the tick to ensure the scheduler is
    not called before restoring interrupts.  There was previously nothing
    on this timer so there is no old ISR to restore. */
    ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( ਪੋਰਟ_TIMER_1_CONTROL_ਰਜਿਸਟਰ, usTimerDisable );

    /* Restart the DOS tick. */
    usTimer0Control = ਪੋਰਟ_ਨਿਵੇਸ਼_ਸ਼ਬਦ( ਪੋਰਟ_TIMER_0_CONTROL_ਰਜਿਸਟਰ );
    usTimer0Control |= ਪੋਰਟ_TIMER_ਰੁਕਾਵਟ_ENABLE;
    ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( ਪੋਰਟ_TIMER_0_CONTROL_ਰਜਿਸਟਰ, usTimer0Control );


    ਪੋਰਟ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_Tick_Frequency( uint32_t ul_Tick_ਦਰ_Hz )
{
ਅਚਲ uint16_t us_Max_ਗਿਣਤੀ_ਰਜਿਸਟਰ = 0xff5a;
ਅਚਲ uint16_t us_Timer_ਤਰਜੀਹ_ਰਜਿਸਟਰ = 0xff32;
ਅਚਲ uint16_t usTimerEnable = 0xC000;
ਅਚਲ uint16_t usRetrigger = 0x0001;
ਅਚਲ uint16_t us_Timer_ਉੱਚਾ_ਤਰਜੀਹ = 0x0000;
uint16_t usTimer0Control;

/* ( CPU frequency / 4 ) / clock 2 max count [inpw( 0xff62 ) = 7] */

ਅਚਲ uint32_t ulClockFrequency = ( uint32_t ) 0x7f31a0UL;

uint32_t ul_Timer_ਗਿਣਤੀ = ulClockFrequency / ul_Tick_ਦਰ_Hz;

    ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( ਪੋਰਟ_TIMER_1_CONTROL_ਰਜਿਸਟਰ, usTimerEnable | ਪੋਰਟ_TIMER_ਰੁਕਾਵਟ_ENABLE | usRetrigger );
    ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( us_Max_ਗਿਣਤੀ_ਰਜਿਸਟਰ, ( uint16_t ) ul_Timer_ਗਿਣਤੀ );
    ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( us_Timer_ਤਰਜੀਹ_ਰਜਿਸਟਰ, us_Timer_ਉੱਚਾ_ਤਰਜੀਹ );

    /* Stop the DOS tick - don't do this if you want to maintain a TOD clock. */
    usTimer0Control = ਪੋਰਟ_ਨਿਵੇਸ਼_ਸ਼ਬਦ( ਪੋਰਟ_TIMER_0_CONTROL_ਰਜਿਸਟਰ );
    usTimer0Control &= ~ਪੋਰਟ_TIMER_ਰੁਕਾਵਟ_ENABLE;
    ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( ਪੋਰਟ_TIMER_0_CONTROL_ਰਜਿਸਟਰ, usTimer0Control );
}


/*lint +e950 */
