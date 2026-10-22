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

#அந்தர்பாவ <dos.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <setjmp.h>

#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"
#அந்தர்பாவ "portasm.h"

/*lint -e950 Non ANSI reserved words okay in this file only. */

#define portTIMER_EOI_TYPE      ( 8 )
#define portRESET_PIC()         portOUTPUT_WORD( ( uint16_t ) 0xff22, portTIMER_EOI_TYPE )
#define port_TIMER_INT_எண்    0x12

#define portTIMER_1_CONTROL_REGISTER    ( ( uint16_t ) 0xff5e )
#define portTIMER_0_CONTROL_REGISTER    ( ( uint16_t ) 0xff56 )
#define portTIMER_INTERRUPT_ENABLE      ( ( uint16_t ) 0x2000 )

/* Setup the hardware to generate the required tick frequency. */
நிலையான வெறுமை prvSetTickFrequency( uint32_t ulTickRateHz );

/* Set the hardware back to the state as per before the scheduler started. */
நிலையான வெறுமை prvExitFunction( வெறுமை );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#எனில்( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    நிலையான வெறுமை __interrupt __far prvPreemptiveTick( வெறுமை );
#இல்லையெனில்
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    நிலையான வெறுமை __interrupt __far prvNonPreemptiveTick( வெறுமை );
#endif

/* Trap routine used by taskYIELD() to manually cause a context switch. */
நிலையான வெறுமை __interrupt __far prvYieldProcessor( வெறுமை );

/*lint -e956 File scopes necessary here. */

/* Set true when the vectors are set so the scheduler will service the tick. */
நிலையான BaseType_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual
context switches.  This is then used to restore the original routine during
prvExitFunction(). */
நிலையான வெறுமை ( __interrupt __far *pxOldSwitchISR )();

/* Used to restore the original DOS context when the scheduler is ended. */
நிலையான jmp_buf xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
BaseType_t xPortStartScheduler( வெறுமை )
{
    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( port_SWITCH_INT_எண் );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( port_SWITCH_INT_எண், prvYieldProcessor );

    #எனில்( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( port_TIMER_INT_எண், prvPreemptiveTick );
    }
    #இல்லையெனில்
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( port_TIMER_INT_எண், prvNonPreemptiveTick );
    }
    #endif

    prvSetTickFrequency( configTICK_RATE_HZ );

    /* Clean up function if we want to return to DOS. */
    எனில்( setjmp( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    இல்லையெனில்
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        portFIRST_CONTEXT();
    }

    திரும்பு xSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#எனில்( configUSE_PREEMPTION == 1 )
    நிலையான வெறுமை __interrupt __far prvPreemptiveTick( வெறுமை )
    {
        /* Get the scheduler to update the task states following the tick. */
        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portSWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        portRESET_PIC();
    }
#இல்லையெனில்
    நிலையான வெறுமை __interrupt __far prvNonPreemptiveTick( வெறுமை )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        portRESET_PIC();
    }
#endif
/*-----------------------------------------------------------*/

நிலையான வெறுமை __interrupt __far prvYieldProcessor( வெறுமை )
{
    /* Switch in the context of the next task to be run. */
    portSWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    longjmp( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvExitFunction( வெறுமை )
{
மாறிலி uint16_t usTimerDisable = 0x0000;
uint16_t usTimer0Control;

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    portDISABLE_INTERRUPTS();
    எனில்( xSchedulerRunning == pdTRUE )
    {
        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( port_SWITCH_INT_எண், pxOldSwitchISR );
    }

    /* Disable the timer used for the tick to ensure the scheduler is
    not called before restoring interrupts.  There was previously nothing
    on this timer so there is no old ISR to restore. */
    portOUTPUT_WORD( portTIMER_1_CONTROL_REGISTER, usTimerDisable );

    /* Restart the DOS tick. */
    usTimer0Control = port_உள்ளீடு_WORD( portTIMER_0_CONTROL_REGISTER );
    usTimer0Control |= portTIMER_INTERRUPT_ENABLE;
    portOUTPUT_WORD( portTIMER_0_CONTROL_REGISTER, usTimer0Control );


    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetTickFrequency( uint32_t ulTickRateHz )
{
மாறிலி uint16_t us_Max_மொத்தம்_Register = 0xff5a;
மாறிலி uint16_t usTimerPriorityRegister = 0xff32;
மாறிலி uint16_t usTimerEnable = 0xC000;
மாறிலி uint16_t usRetrigger = 0x0001;
மாறிலி uint16_t us_Timer_உயர்வு_Priority = 0x0000;
uint16_t usTimer0Control;

/* ( CPU frequency / 4 ) / clock 2 max count [inpw( 0xff62 ) = 7] */

மாறிலி uint32_t ulClockFrequency = ( uint32_t ) 0x7f31a0UL;

uint32_t ul_Timer_மொத்தம் = ulClockFrequency / ulTickRateHz;

    portOUTPUT_WORD( portTIMER_1_CONTROL_REGISTER, usTimerEnable | portTIMER_INTERRUPT_ENABLE | usRetrigger );
    portOUTPUT_WORD( us_Max_மொத்தம்_Register, ( uint16_t ) ul_Timer_மொத்தம் );
    portOUTPUT_WORD( usTimerPriorityRegister, us_Timer_உயர்வு_Priority );

    /* Stop the DOS tick - don't do this if you want to maintain a TOD clock. */
    usTimer0Control = port_உள்ளீடு_WORD( portTIMER_0_CONTROL_REGISTER );
    usTimer0Control &= ~portTIMER_INTERRUPT_ENABLE;
    portOUTPUT_WORD( portTIMER_0_CONTROL_REGISTER, usTimer0Control );
}


/*lint +e950 */
