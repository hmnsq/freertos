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

#ಅನ್ತರ್ಭಾವ <dos.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <setjmp.h>

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "portasm.h"

/*lint -e950 Non ANSI reserved words okay in this file only. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_EOI_TYPE      ( 8 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_PIC()         ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( ( uint16_t ) 0xff22, ಪೋರ್ಟ್_TIMER_EOI_TYPE )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_INT_ಸಂಖ್ಯೆ    0x12

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_1_CONTROL_ರಿಜಿಸ್ಟರ್    ( ( uint16_t ) 0xff5e )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_0_CONTROL_ರಿಜಿಸ್ಟರ್    ( ( uint16_t ) 0xff56 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_ಅಡಚಣೆ_ENABLE      ( ( uint16_t ) 0x2000 )

/* Setup the hardware to generate the required tick frequency. */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಗಣ_Tick_Frequency( uint32_t ul_Tick_ದರ_Hz );

/* Set the hardware back to the state as per before the scheduler started. */
ಸ್ಥಿರ ಶೂನ್ಯ prvExitFunction( ಶೂನ್ಯ );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ಆದರೆ( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvPreemptiveTick( ಶೂನ್ಯ );
#ಇಲ್ಲದಿದ್ದರೆ
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvNonPreemptiveTick( ಶೂನ್ಯ );
#ಆದರೆ_ಅಂತ್ಯ

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvYieldProcessor( ಶೂನ್ಯ );

/*lint -e956 File scopes necessary here. */

/* Set true when the vectors are set so the scheduler will service the tick. */
ಸ್ಥಿರ ತಳ_Type_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual
context switches.  This is then used to restore the original routine during
prvExitFunction(). */
ಸ್ಥಿರ ಶೂನ್ಯ ( __interrupt __far *pxOldSwitchISR )();

/* Used to restore the original DOS context when the scheduler is ended. */
ಸ್ಥಿರ jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( ಪೋರ್ಟ್_SWITCH_INT_ಸಂಖ್ಯೆ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( ಪೋರ್ಟ್_SWITCH_INT_ಸಂಖ್ಯೆ, prvYieldProcessor );

    #ಆದರೆ( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( ಪೋರ್ಟ್_TIMER_INT_ಸಂಖ್ಯೆ, prvPreemptiveTick );
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( ಪೋರ್ಟ್_TIMER_INT_ಸಂಖ್ಯೆ, prvNonPreemptiveTick );
    }
    #ಆದರೆ_ಅಂತ್ಯ

    prv_ಗಣ_Tick_Frequency( config_TICK_ದರ_HZ );

    /* Clean up function if we want to return to DOS. */
    ಆದರೆ( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        ಪೋರ್ಟ್_ಮೊದಲ_CONTEXT();
    }

    ಹಿಂತಿರುಗಿ xSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ಆದರೆ( configUSE_PREEMPTION == 1 )
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Get the scheduler to update the task states following the tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            ಪೋರ್ಟ್_SWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        ಪೋರ್ಟ್_RESET_PIC();
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvNonPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        ಪೋರ್ಟ್_RESET_PIC();
    }
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvYieldProcessor( ಶೂನ್ಯ )
{
    /* Switch in the context of the next task to be run. */
    ಪೋರ್ಟ್_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvExitFunction( ಶೂನ್ಯ )
{
ಸ್ಥಿರಾಂಕ uint16_t usTimerDisable = 0x0000;
uint16_t usTimer0Control;

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    ಆದರೆ( xSchedulerRunning == pdTRUE )
    {
        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( ಪೋರ್ಟ್_SWITCH_INT_ಸಂಖ್ಯೆ, pxOldSwitchISR );
    }

    /* Disable the timer used for the tick to ensure the scheduler is
    not called before restoring interrupts.  There was previously nothing
    on this timer so there is no old ISR to restore. */
    ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( ಪೋರ್ಟ್_TIMER_1_CONTROL_ರಿಜಿಸ್ಟರ್, usTimerDisable );

    /* Restart the DOS tick. */
    usTimer0Control = ಪೋರ್ಟ್_ಒಳಹರಿವು_ಶಬ್ದ( ಪೋರ್ಟ್_TIMER_0_CONTROL_ರಿಜಿಸ್ಟರ್ );
    usTimer0Control |= ಪೋರ್ಟ್_TIMER_ಅಡಚಣೆ_ENABLE;
    ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( ಪೋರ್ಟ್_TIMER_0_CONTROL_ರಿಜಿಸ್ಟರ್, usTimer0Control );


    ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಗಣ_Tick_Frequency( uint32_t ul_Tick_ದರ_Hz )
{
ಸ್ಥಿರಾಂಕ uint16_t us_Max_ಎಣಿಕೆ_ರಿಜಿಸ್ಟರ್ = 0xff5a;
ಸ್ಥಿರಾಂಕ uint16_t us_Timer_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = 0xff32;
ಸ್ಥಿರಾಂಕ uint16_t usTimerEnable = 0xC000;
ಸ್ಥಿರಾಂಕ uint16_t usRetrigger = 0x0001;
ಸ್ಥಿರಾಂಕ uint16_t us_Timer_ಮೇಲಿನ_ಆದ್ಯತೆ = 0x0000;
uint16_t usTimer0Control;

/* ( CPU frequency / 4 ) / clock 2 max count [inpw( 0xff62 ) = 7] */

ಸ್ಥಿರಾಂಕ uint32_t ulClockFrequency = ( uint32_t ) 0x7f31a0UL;

uint32_t ul_Timer_ಎಣಿಕೆ = ulClockFrequency / ul_Tick_ದರ_Hz;

    ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( ಪೋರ್ಟ್_TIMER_1_CONTROL_ರಿಜಿಸ್ಟರ್, usTimerEnable | ಪೋರ್ಟ್_TIMER_ಅಡಚಣೆ_ENABLE | usRetrigger );
    ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( us_Max_ಎಣಿಕೆ_ರಿಜಿಸ್ಟರ್, ( uint16_t ) ul_Timer_ಎಣಿಕೆ );
    ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( us_Timer_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್, us_Timer_ಮೇಲಿನ_ಆದ್ಯತೆ );

    /* Stop the DOS tick - don't do this if you want to maintain a TOD clock. */
    usTimer0Control = ಪೋರ್ಟ್_ಒಳಹರಿವು_ಶಬ್ದ( ಪೋರ್ಟ್_TIMER_0_CONTROL_ರಿಜಿಸ್ಟರ್ );
    usTimer0Control &= ~ಪೋರ್ಟ್_TIMER_ಅಡಚಣೆ_ENABLE;
    ಪೋರ್ಟ್_OUTPUT_ಶಬ್ದ( ಪೋರ್ಟ್_TIMER_0_CONTROL_ರಿಜಿಸ್ಟರ್, usTimer0Control );
}


/*lint +e950 */
