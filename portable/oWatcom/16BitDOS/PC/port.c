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

#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <i86.h>
#شامل <dos.h>
#شامل <setjmp.h>

#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "portasm.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the industrial
 * PC port.
 *----------------------------------------------------------*/

/*lint -e950 Non ANSI reserved words okay in this file only. */

#تعریف_کرو پورٹ_TIMER_INT_نمبر    0x08

/* Setup hardware for required tick interrupt rate. */
ساکن خالی prv_سیٹ_Tick_Frequency( uint32_t ul_Tick_شرح_Hz );

/* Restore hardware to as it was prior to starting the scheduler. */
ساکن خالی prvExitFunction( خالی );

/* Either chain to the DOS tick (which itself clears the PIC) or clear the PIC
directly.  We chain to the DOS tick as close as possible to the standard DOS
tick rate. */
ساکن خالی prv_پورٹ_Reset_PIC( خالی );

/* The tick ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#اگر configUSE_PREEMPTION == 1
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ساکن خالی __interrupt __far prvPreemptiveTick( خالی );
#ورنہ
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ساکن خالی __interrupt __far prvNonPreemptiveTick( خالی );
#اگر_ختم
/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساکن خالی __interrupt __far prvYieldProcessor( خالی );

/* Set the tick frequency back so the floppy drive works correctly when the
scheduler exits. */
ساکن خالی prv_سیٹ_Tick_Frequency_Default( خالی );

/*lint -e956 File scopes necessary here. */

/* Used to signal when to chain to the DOS tick, and when to just clear the PIC ourselves. */
ساکن int16_t s_DOSTick_شمار;

/* Set true when the vectors are set so the scheduler will service the tick. */
ساکن int16_t sSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
ساکن خالی ( __interrupt __far *pxOldSwitchISR )();

/* Points to the original routine installed on the vector we use to chain to the DOS tick.  This is then used to restore the original routine during prvExitFunction(). */
ساکن خالی ( __interrupt __far *pxOldSwitchISRPlus1 )();

/* Used to restore the original DOS context when the scheduler is ended. */
ساکن jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
pxISR pxOriginalTickISR;

    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( پورٹ_SWITCH_INT_نمبر );
    pxOriginalTickISR = _dos_getvect( پورٹ_TIMER_INT_نمبر );
    pxOldSwitchISRPlus1 = _dos_getvect( پورٹ_SWITCH_INT_نمبر + 1 );

    prv_سیٹ_Tick_Frequency( config_TICK_شرح_HZ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( پورٹ_SWITCH_INT_نمبر, prvYieldProcessor );

    /* Put the old tick on a different interrupt number so we can
    call it when we want. */
    _dos_setvect( پورٹ_SWITCH_INT_نمبر + 1, pxOriginalTickISR );

    #اگر configUSE_PREEMPTION == 1
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( پورٹ_TIMER_INT_نمبر, prvPreemptiveTick );
    }
    #ورنہ
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( پورٹ_TIMER_INT_نمبر, prvNonPreemptiveTick );
    }
    #اگر_ختم

    /* Setup a counter that is used to call the DOS interrupt as close
    to it's original frequency as can be achieved given our chosen tick
    frequency. */
    s_DOSTick_شمار = پورٹ_TICKS_فی_DOS_TICK;

    /* Clean up function if we want to return to DOS. */
    اگر( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        sSchedulerRunning = pdFALSE;
    }
    ورنہ
    {
        sSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        پورٹ_پہلا_CONTEXT();
    }

    واپس sSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The tick ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#اگر configUSE_PREEMPTION == 1
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ساکن خالی __interrupt __far prvPreemptiveTick( خالی )
    {
        /* Get the scheduler to update the task states following the tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            پورٹ_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        prv_پورٹ_Reset_PIC();
    }
#ورنہ
    ساکن خالی __interrupt __far prvNonPreemptiveTick( خالی )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        prv_پورٹ_Reset_PIC();
    }
#اگر_ختم
/*-----------------------------------------------------------*/


ساکن خالی __interrupt __far prvYieldProcessor( خالی )
{
    /* Switch in the context of the next task to be run. */
    پورٹ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ساکن خالی prv_پورٹ_Reset_PIC( خالی )
{
    /* We are going to call the DOS tick interrupt at as close a
    frequency to the normal DOS tick as possible. */

    /* WE SHOULD NOT DO THIS IF YIELD WAS CALLED. */
    --s_DOSTick_شمار;
    اگر( s_DOSTick_شمار <= 0 )
    {
        s_DOSTick_شمار = ( int16_t ) پورٹ_TICKS_فی_DOS_TICK;
        __asm{ صحیح  پورٹ_SWITCH_INT_نمبر + 1 };
    }
    ورنہ
    {
        /* Reset the PIC as the DOS tick is not being called to
        do it. */
        __asm
        {
            mov al, 20H
            برآمد 20H, al
        };
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

ساکن خالی prvExitFunction( خالی )
{
خالی ( __interrupt __far *pxOriginalTickISR )();

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    پورٹ_DISABLE_INTERRUPTS();
    اگر( sSchedulerRunning == pdTRUE )
    {
        /* Set the DOS tick back onto the timer ticker. */
        pxOriginalTickISR = _dos_getvect( پورٹ_SWITCH_INT_نمبر + 1 );
        _dos_setvect( پورٹ_TIMER_INT_نمبر, pxOriginalTickISR );
        prv_سیٹ_Tick_Frequency_Default();

        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( پورٹ_SWITCH_INT_نمبر, pxOldSwitchISR );
        _dos_setvect( پورٹ_SWITCH_INT_نمبر + 1, pxOldSwitchISRPlus1 );
    }
    /* The tick timer is back how DOS wants it.  We can re-enable
    interrupts without the scheduler being called. */
    پورٹ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

ساکن خالی prv_سیٹ_Tick_Frequency( uint32_t ul_Tick_شرح_Hz )
{
ثابت uint16_t us_PIT_منوال = ( uint16_t ) 0x43;
ثابت uint16_t usPIT0 = ( uint16_t ) 0x40;
ثابت uint32_t ulPIT_CONST = ( uint32_t ) 1193180;
ثابت uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;
uint32_t ulOutput;

    /* Setup the 8245 to tick at the wanted frequency. */
    پورٹ_OUTPUT_BYTE( us_PIT_منوال, us8254_CTR0_MODE3 );
    ulOutput = ulPIT_CONST / ul_Tick_شرح_Hz;

    پورٹ_OUTPUT_BYTE( usPIT0, ( uint16_t )( ulOutput & ( uint32_t ) 0xff ) );
    ulOutput >>= 8;
    پورٹ_OUTPUT_BYTE( usPIT0, ( uint16_t ) ( ulOutput & ( uint32_t ) 0xff ) );
}
/*-----------------------------------------------------------*/

ساکن خالی prv_سیٹ_Tick_Frequency_Default( خالی )
{
ثابت uint16_t us_PIT_منوال = ( uint16_t ) 0x43;
ثابت uint16_t usPIT0 = ( uint16_t ) 0x40;
ثابت uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;

    پورٹ_OUTPUT_BYTE( us_PIT_منوال, us8254_CTR0_MODE3 );
    پورٹ_OUTPUT_BYTE( usPIT0,0 );
    پورٹ_OUTPUT_BYTE( usPIT0,0 );
}


/*lint +e950 */
