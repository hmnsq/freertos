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
Changes from V2.6.1

    + Replaced the sUsingPreemption variable with the configUSE_PREEMPTION
      macro to be consistent with the later ports.

Changes from V4.0.1

    + Add function prvSetTickFrequencyDefault() to set the DOS tick back to
      its proper value when the scheduler exits.
*/

#ضمن <stdlib.h>
#ضمن <dos.h>
#ضمن <setjmp.h>

#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portasm.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the industrial
 * PC port.
 *----------------------------------------------------------*/

/*lint -e950 Non ANSI reserved words okay in this file only. */

#وصف_ڪريو پورٽ_TIMER_INT_عدد    0x08

/* Setup hardware for required tick interrupt rate. */
ساكن فراغ prv_سيٽ_Tick_Frequency( uint32_t ul_Tick_شرح_Hz );

/* Restore hardware to as it was prior to starting the scheduler. */
ساكن فراغ prvExitFunction( فراغ );

/* Either chain to the DOS tick (which itself clears the PIC) or clear the PIC
directly.  We chain to the DOS tick as close as possible to the standard DOS
tick rate. */
ساكن فراغ prv_پورٽ_Reset_PIC( فراغ );

/* The ISR used depends on whether the preemptive or cooperative
scheduler is being used. */
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

/* Set the tick frequency back so the floppy drive works correctly when the
scheduler exits. */
ساكن فراغ prv_سيٽ_Tick_Frequency_Default( فراغ );

/*lint -e956 File scopes necessary here. */

/* Used to signal when to chain to the DOS tick, and when to just clear the PIC ourselves. */
ساكن int16_t sDOSTickCounter;

/* Set true when the vectors are set so the scheduler will service the tick. */
ساكن بنياد_Type_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
ساكن فراغ ( __interrupt __far *pxOldSwitchISR )();

/* Points to the original routine installed on the vector we use to chain to the DOS tick.  This is then used to restore the original routine during prvExitFunction(). */
ساكن فراغ ( __interrupt __far *pxOldSwitchISRPlus1 )();

/* Used to restore the original DOS context when the scheduler is ended. */
ساكن jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
pxISR pxOriginalTickISR;

    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( پورٽ_SWITCH_INT_عدد );
    pxOriginalTickISR = _dos_getvect( پورٽ_TIMER_INT_عدد );
    pxOldSwitchISRPlus1 = _dos_getvect( پورٽ_SWITCH_INT_عدد + 1 );

    prv_سيٽ_Tick_Frequency( config_TICK_شرح_HZ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( پورٽ_SWITCH_INT_عدد, prvYieldProcessor );

    /* Put the old tick on a different interrupt number so we can
    call it when we want. */
    _dos_setvect( پورٽ_SWITCH_INT_عدد + 1, pxOriginalTickISR );

    /* The ISR used depends on whether the preemptive or cooperative
    scheduler is being used. */
    #إذا( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( پورٽ_TIMER_INT_عدد, prvPreemptiveTick );
    }
    #وإلا
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( پورٽ_TIMER_INT_عدد, prvNonPreemptiveTick );
    }
    #جيڪڏهن_پورو

    /* Setup a counter that is used to call the DOS interrupt as close
    to it's original frequency as can be achieved given our chosen tick
    frequency. */
    sDOSTickCounter = پورٽ_TICKS_في_DOS_TICK;

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
        پورٽ_پهريون_CONTEXT();
    }

    أرجع xSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative
scheduler is being used. */
#إذا( configUSE_PREEMPTION == 1 )
    ساكن فراغ __interrupt __far prvPreemptiveTick( فراغ )
    {
        /* Get the scheduler to update the task states following the tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            پورٽ_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        prv_پورٽ_Reset_PIC();
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        prv_پورٽ_Reset_PIC();
    }
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    پورٽ_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_پورٽ_Reset_PIC( فراغ )
{
    /* We are going to call the DOS tick interrupt at as close a
    frequency to the normal DOS tick as possible. */

    /* WE SHOULD NOT DO THIS IF YIELD WAS CALLED. */
    --sDOSTickCounter;
    إذا( sDOSTickCounter <= 0 )
    {
        sDOSTickCounter = ( int16_t ) پورٽ_TICKS_في_DOS_TICK;
        __asm{ صحيح  پورٽ_SWITCH_INT_عدد + 1 };
    }
    وإلا
    {
        /* Reset the PIC as the DOS tick is not being called to
        do it. */
        __asm
        {
            mov al, 20H
            ٻاهريون 20H, al
        };
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvExitFunction( فراغ )
{
فراغ ( __interrupt __far *pxOriginalTickISR )();

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    پورٽ_DISABLE_INTERRUPTS();
    إذا( xSchedulerRunning == pdTRUE )
    {
        /* Set the DOS tick back onto the timer ticker. */
        pxOriginalTickISR = _dos_getvect( پورٽ_SWITCH_INT_عدد + 1 );
        _dos_setvect( پورٽ_TIMER_INT_عدد, pxOriginalTickISR );
        prv_سيٽ_Tick_Frequency_Default();

        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( پورٽ_SWITCH_INT_عدد, pxOldSwitchISR );
        _dos_setvect( پورٽ_SWITCH_INT_عدد + 1, pxOldSwitchISRPlus1 );
    }
    /* The tick timer is back how DOS wants it.  We can re-enable
    interrupts without the scheduler being called. */
    پورٽ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سيٽ_Tick_Frequency( uint32_t ul_Tick_شرح_Hz )
{
ثابت uint16_t us_PIT_گهڻائي = ( uint16_t ) 0x43;
ثابت uint16_t usPIT0 = ( uint16_t ) 0x40;
ثابت uint32_t ulPIT_CONST = ( uint32_t ) 1193180UL;
ثابت uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;
uint32_t ulOutput;

    /* Setup the 8245 to tick at the wanted frequency. */
    پورٽ_OUTPUT_BYTE( us_PIT_گهڻائي, us8254_CTR0_MODE3 );
    ulOutput = ulPIT_CONST / ul_Tick_شرح_Hz;
    پورٽ_OUTPUT_BYTE( usPIT0, ( uint16_t )( ulOutput & ( uint32_t ) 0xff ) );
    ulOutput >>= 8;
    پورٽ_OUTPUT_BYTE( usPIT0, ( uint16_t ) ( ulOutput & ( uint32_t ) 0xff ) );
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سيٽ_Tick_Frequency_Default( فراغ )
{
ثابت uint16_t us_PIT_گهڻائي = ( uint16_t ) 0x43;
ثابت uint16_t usPIT0 = ( uint16_t ) 0x40;
ثابت uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;

    پورٽ_OUTPUT_BYTE( us_PIT_گهڻائي, us8254_CTR0_MODE3 );
    پورٽ_OUTPUT_BYTE( usPIT0,0 );
    پورٽ_OUTPUT_BYTE( usPIT0,0 );
}


/*lint +e950 */
