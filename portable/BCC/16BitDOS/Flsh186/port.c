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

#ضمن <dos.h>
#ضمن <stdlib.h>
#ضمن <setjmp.h>

#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portasm.h"

/*lint -e950 Non ANSI reserved words okay in this file only. */

#تعریف_کرو پورٹ_TIMER_EOI_TYPE      ( 8 )
#تعریف_کرو پورٹ_RESET_PIC()         پورٹ_OUTPUT_لفظ( ( uint16_t ) 0xff22, پورٹ_TIMER_EOI_TYPE )
#تعریف_کرو پورٹ_TIMER_INT_نمبر    0x12

#تعریف_کرو پورٹ_TIMER_1_CONTROL_رجسٹر    ( ( uint16_t ) 0xff5e )
#تعریف_کرو پورٹ_TIMER_0_CONTROL_رجسٹر    ( ( uint16_t ) 0xff56 )
#تعریف_کرو پورٹ_TIMER_رکاوٹ_ENABLE      ( ( uint16_t ) 0x2000 )

/* Setup the hardware to generate the required tick frequency. */
ساكن فراغ prv_سیٹ_Tick_Frequency( uint32_t ul_Tick_شرح_Hz );

/* Set the hardware back to the state as per before the scheduler started. */
ساكن فراغ prvExitFunction( فراغ );

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
#جے_انت

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساكن فراغ __interrupt __far prvYieldProcessor( فراغ );

/*lint -e956 File scopes necessary here. */

/* Set true when the vectors are set so the scheduler will service the tick. */
ساكن ادھار_Type_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual
context switches.  This is then used to restore the original routine during
prvExitFunction(). */
ساكن فراغ ( __interrupt __far *pxOldSwitchISR )();

/* Used to restore the original DOS context when the scheduler is ended. */
ساكن jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( پورٹ_SWITCH_INT_نمبر );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( پورٹ_SWITCH_INT_نمبر, prvYieldProcessor );

    #إذا( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( پورٹ_TIMER_INT_نمبر, prvPreemptiveTick );
    }
    #وإلا
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( پورٹ_TIMER_INT_نمبر, prvNonPreemptiveTick );
    }
    #جے_انت

    prv_سیٹ_Tick_Frequency( config_TICK_شرح_HZ );

    /* Clean up function if we want to return to DOS. */
    إذا( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    وإلا
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        پورٹ_پہلا_CONTEXT();
    }

    أرجع xSchedulerRunning;
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
            پورٹ_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        پورٹ_RESET_PIC();
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        پورٹ_RESET_PIC();
    }
#جے_انت
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    پورٹ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvExitFunction( فراغ )
{
ثابت uint16_t usTimerDisable = 0x0000;
uint16_t usTimer0Control;

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    پورٹ_DISABLE_INTERRUPTS();
    إذا( xSchedulerRunning == pdTRUE )
    {
        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( پورٹ_SWITCH_INT_نمبر, pxOldSwitchISR );
    }

    /* Disable the timer used for the tick to ensure the scheduler is
    not called before restoring interrupts.  There was previously nothing
    on this timer so there is no old ISR to restore. */
    پورٹ_OUTPUT_لفظ( پورٹ_TIMER_1_CONTROL_رجسٹر, usTimerDisable );

    /* Restart the DOS tick. */
    usTimer0Control = پورٹ_داخلہ_لفظ( پورٹ_TIMER_0_CONTROL_رجسٹر );
    usTimer0Control |= پورٹ_TIMER_رکاوٹ_ENABLE;
    پورٹ_OUTPUT_لفظ( پورٹ_TIMER_0_CONTROL_رجسٹر, usTimer0Control );


    پورٹ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سیٹ_Tick_Frequency( uint32_t ul_Tick_شرح_Hz )
{
ثابت uint16_t us_Max_گنتی_رجسٹر = 0xff5a;
ثابت uint16_t us_Timer_ترجیح_رجسٹر = 0xff32;
ثابت uint16_t usTimerEnable = 0xC000;
ثابت uint16_t usRetrigger = 0x0001;
ثابت uint16_t us_Timer_بلند_ترجیح = 0x0000;
uint16_t usTimer0Control;

/* ( CPU frequency / 4 ) / clock 2 max count [inpw( 0xff62 ) = 7] */

ثابت uint32_t ulClockFrequency = ( uint32_t ) 0x7f31a0UL;

uint32_t ul_Timer_گنتی = ulClockFrequency / ul_Tick_شرح_Hz;

    پورٹ_OUTPUT_لفظ( پورٹ_TIMER_1_CONTROL_رجسٹر, usTimerEnable | پورٹ_TIMER_رکاوٹ_ENABLE | usRetrigger );
    پورٹ_OUTPUT_لفظ( us_Max_گنتی_رجسٹر, ( uint16_t ) ul_Timer_گنتی );
    پورٹ_OUTPUT_لفظ( us_Timer_ترجیح_رجسٹر, us_Timer_بلند_ترجیح );

    /* Stop the DOS tick - don't do this if you want to maintain a TOD clock. */
    usTimer0Control = پورٹ_داخلہ_لفظ( پورٹ_TIMER_0_CONTROL_رجسٹر );
    usTimer0Control &= ~پورٹ_TIMER_رکاوٹ_ENABLE;
    پورٹ_OUTPUT_لفظ( پورٹ_TIMER_0_CONTROL_رجسٹر, usTimer0Control );
}


/*lint +e950 */
