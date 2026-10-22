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

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <dos.h>
#অন্তর্ভাব <setjmp.h>

#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "portasm.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the industrial
 * PC port.
 *----------------------------------------------------------*/

/*lint -e950 Non ANSI reserved words okay in this file only. */

#define port_TIMER_INT_সংখ্যা    0x08

/* Setup hardware for required tick interrupt rate. */
স্থির শূন্য prvSetTickFrequency( uint32_t ulTickRateHz );

/* Restore hardware to as it was prior to starting the scheduler. */
স্থির শূন্য prvExitFunction( শূন্য );

/* Either chain to the DOS tick (which itself clears the PIC) or clear the PIC
directly.  We chain to the DOS tick as close as possible to the standard DOS
tick rate. */
স্থির শূন্য prvPortResetPIC( শূন্য );

/* The ISR used depends on whether the preemptive or cooperative
scheduler is being used. */
#যদি( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    স্থির শূন্য __interrupt __far prvPreemptiveTick( শূন্য );
#অন্যথা
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    স্থির শূন্য __interrupt __far prvNonPreemptiveTick( শূন্য );
#endif

/* Trap routine used by taskYIELD() to manually cause a context switch. */
স্থির শূন্য __interrupt __far prvYieldProcessor( শূন্য );

/* Set the tick frequency back so the floppy drive works correctly when the
scheduler exits. */
স্থির শূন্য prvSetTickFrequencyDefault( শূন্য );

/*lint -e956 File scopes necessary here. */

/* Used to signal when to chain to the DOS tick, and when to just clear the PIC ourselves. */
স্থির int16_t sDOSTickCounter;

/* Set true when the vectors are set so the scheduler will service the tick. */
স্থির BaseType_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
স্থির শূন্য ( __interrupt __far *pxOldSwitchISR )();

/* Points to the original routine installed on the vector we use to chain to the DOS tick.  This is then used to restore the original routine during prvExitFunction(). */
স্থির শূন্য ( __interrupt __far *pxOldSwitchISRPlus1 )();

/* Used to restore the original DOS context when the scheduler is ended. */
স্থির jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
BaseType_t xPortStartScheduler( শূন্য )
{
pxISR pxOriginalTickISR;

    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( port_SWITCH_INT_সংখ্যা );
    pxOriginalTickISR = _dos_getvect( port_TIMER_INT_সংখ্যা );
    pxOldSwitchISRPlus1 = _dos_getvect( port_SWITCH_INT_সংখ্যা + 1 );

    prvSetTickFrequency( configTICK_RATE_HZ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( port_SWITCH_INT_সংখ্যা, prvYieldProcessor );

    /* Put the old tick on a different interrupt number so we can
    call it when we want. */
    _dos_setvect( port_SWITCH_INT_সংখ্যা + 1, pxOriginalTickISR );

    /* The ISR used depends on whether the preemptive or cooperative
    scheduler is being used. */
    #যদি( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( port_TIMER_INT_সংখ্যা, prvPreemptiveTick );
    }
    #অন্যথা
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( port_TIMER_INT_সংখ্যা, prvNonPreemptiveTick );
    }
    #endif

    /* Setup a counter that is used to call the DOS interrupt as close
    to it's original frequency as can be achieved given our chosen tick
    frequency. */
    sDOSTickCounter = portTICKS_PER_DOS_TICK;

    /* Clean up function if we want to return to DOS. */
    যদি( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    অন্যথা
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        portFIRST_CONTEXT();
    }

    প্রত্যাগম xSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative
scheduler is being used. */
#যদি( configUSE_PREEMPTION == 1 )
    স্থির শূন্য __interrupt __far prvPreemptiveTick( শূন্য )
    {
        /* Get the scheduler to update the task states following the tick. */
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portSWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        prvPortResetPIC();
    }
#অন্যথা
    স্থির শূন্য __interrupt __far prvNonPreemptiveTick( শূন্য )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        prvPortResetPIC();
    }
#endif
/*-----------------------------------------------------------*/

স্থির শূন্য __interrupt __far prvYieldProcessor( শূন্য )
{
    /* Switch in the context of the next task to be run. */
    portSWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvPortResetPIC( শূন্য )
{
    /* We are going to call the DOS tick interrupt at as close a
    frequency to the normal DOS tick as possible. */

    /* WE SHOULD NOT DO THIS IF YIELD WAS CALLED. */
    --sDOSTickCounter;
    যদি( sDOSTickCounter <= 0 )
    {
        sDOSTickCounter = ( int16_t ) portTICKS_PER_DOS_TICK;
        __asm{ পূর্ণাঙ্ক  port_SWITCH_INT_সংখ্যা + 1 };
    }
    অন্যথা
    {
        /* Reset the PIC as the DOS tick is not being called to
        do it. */
        __asm
        {
            mov al, 20H
            out 20H, al
        };
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvExitFunction( শূন্য )
{
শূন্য ( __interrupt __far *pxOriginalTickISR )();

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    portDISABLE_INTERRUPTS();
    যদি( xSchedulerRunning == pdTRUE )
    {
        /* Set the DOS tick back onto the timer ticker. */
        pxOriginalTickISR = _dos_getvect( port_SWITCH_INT_সংখ্যা + 1 );
        _dos_setvect( port_TIMER_INT_সংখ্যা, pxOriginalTickISR );
        prvSetTickFrequencyDefault();

        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( port_SWITCH_INT_সংখ্যা, pxOldSwitchISR );
        _dos_setvect( port_SWITCH_INT_সংখ্যা + 1, pxOldSwitchISRPlus1 );
    }
    /* The tick timer is back how DOS wants it.  We can re-enable
    interrupts without the scheduler being called. */
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSetTickFrequency( uint32_t ulTickRateHz )
{
ধ্রুব uint16_t usPIT_MODE = ( uint16_t ) 0x43;
ধ্রুব uint16_t usPIT0 = ( uint16_t ) 0x40;
ধ্রুব uint32_t ulPIT_CONST = ( uint32_t ) 1193180UL;
ধ্রুব uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;
uint32_t ulOutput;

    /* Setup the 8245 to tick at the wanted frequency. */
    portOUTPUT_BYTE( usPIT_MODE, us8254_CTR0_MODE3 );
    ulOutput = ulPIT_CONST / ulTickRateHz;
    portOUTPUT_BYTE( usPIT0, ( uint16_t )( ulOutput & ( uint32_t ) 0xff ) );
    ulOutput >>= 8;
    portOUTPUT_BYTE( usPIT0, ( uint16_t ) ( ulOutput & ( uint32_t ) 0xff ) );
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSetTickFrequencyDefault( শূন্য )
{
ধ্রুব uint16_t usPIT_MODE = ( uint16_t ) 0x43;
ধ্রুব uint16_t usPIT0 = ( uint16_t ) 0x40;
ধ্রুব uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;

    portOUTPUT_BYTE( usPIT_MODE, us8254_CTR0_MODE3 );
    portOUTPUT_BYTE( usPIT0,0 );
    portOUTPUT_BYTE( usPIT0,0 );
}


/*lint +e950 */
