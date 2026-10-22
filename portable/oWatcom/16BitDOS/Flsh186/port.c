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

    + portRESET_PIC() is now called last thing before the end of the preemptive
      tick routine.

Changes from V2.6.1

    + Replaced the sUsingPreemption variable with the configUSE_PREEMPTION
      macro to be consistent with the later ports.
*/

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the Flashlite 186
 * port.
 *----------------------------------------------------------*/

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <i86.h>
#अन्तर्भाव <dos.h>
#अन्तर्भाव <setjmp.h>

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "portasm.h"

/*lint -e950 Non ANSI reserved words okay in this file only. */

#define portTIMER_EOI_TYPE      ( 8 )
#define portRESET_PIC()         portOUTPUT_WORD( ( uint16_t ) 0xff22, portTIMER_EOI_TYPE )
#define port_TIMER_INT_सङ्ख्या    0x12

#define portTIMER_1_CONTROL_REGISTER    ( ( uint16_t ) 0xff5e )
#define portTIMER_0_CONTROL_REGISTER    ( ( uint16_t ) 0xff56 )
#define portTIMER_INTERRUPT_ENABLE      ( ( uint16_t ) 0x2000 )

/* Setup the hardware to generate the required tick frequency. */
स्थिर शून्य prvSetTickFrequency( uint32_t ulTickRateHz );

/* Set the hardware back to the state as per before the scheduler started. */
स्थिर शून्य prvExitFunction( शून्य );

#यदि configUSE_PREEMPTION == 1
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    स्थिर शून्य __interrupt __far prvPreemptiveTick( शून्य );
#अन्यथा
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    स्थिर शून्य __interrupt __far prvNonPreemptiveTick( शून्य );
#endif

/* Trap routine used by taskYIELD() to manually cause a context switch. */
स्थिर शून्य __interrupt __far prvYieldProcessor( शून्य );

/*lint -e956 File scopes necessary here. */

/* Set true when the vectors are set so the scheduler will service the tick. */
स्थिर int16_t sSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
स्थिर शून्य ( __interrupt __far *pxOldSwitchISR )();

/* Used to restore the original DOS context when the scheduler is ended. */
स्थिर लाँघ_बफ xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
BaseType_t xPortStartScheduler( शून्य )
{
    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( port_SWITCH_INT_सङ्ख्या );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( port_SWITCH_INT_सङ्ख्या, prvYieldProcessor );

    #यदि configUSE_PREEMPTION == 1
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( port_TIMER_INT_सङ्ख्या, prvPreemptiveTick );
    }
    #अन्यथा
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( port_TIMER_INT_सङ्ख्या, prvNonPreemptiveTick );
    }
    #endif

    prvSetTickFrequency( configTICK_RATE_HZ );

    /* Clean up function if we want to return to DOS. */
    यदि( बनाओ_लाँघ( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        sSchedulerRunning = pdFALSE;
    }
    अन्यथा
    {
        sSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        portFIRST_CONTEXT();
    }

    फर्काऊ sSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The tick ISR used depend on whether or not the preemptive or cooperative
kernel is being used. */
#यदि configUSE_PREEMPTION == 1
    स्थिर शून्य __interrupt __far prvPreemptiveTick( शून्य )
    {
        /* Get the scheduler to update the task states following the tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portSWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        portRESET_PIC();
    }
#अन्यथा
    स्थिर शून्य __interrupt __far prvNonPreemptiveTick( शून्य )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        portRESET_PIC();
    }
#endif
/*-----------------------------------------------------------*/

स्थिर शून्य __interrupt __far prvYieldProcessor( शून्य )
{
    /* Switch in the context of the next task to be run. */
    portSWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    दीर्घ_लाँघ( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvExitFunction( शून्य )
{
अचर uint16_t usTimerDisable = 0x0000;
uint16_t usTimer0Control;

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    portDISABLE_INTERRUPTS();
    यदि( sSchedulerRunning == pdTRUE )
    {
        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( port_SWITCH_INT_सङ्ख्या, pxOldSwitchISR );
    }

    /* Disable the timer used for the tick to ensure the scheduler is
    not called before restoring interrupts.  There was previously nothing
    on this timer so there is no old ISR to restore. */
    portOUTPUT_WORD( portTIMER_1_CONTROL_REGISTER, usTimerDisable );

    /* Restart the DOS tick. */
    usTimer0Control = port_आगत_WORD( portTIMER_0_CONTROL_REGISTER );
    usTimer0Control |= portTIMER_INTERRUPT_ENABLE;
    portOUTPUT_WORD( portTIMER_0_CONTROL_REGISTER, usTimer0Control );


    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSetTickFrequency( uint32_t ulTickRateHz )
{
अचर uint16_t us_Max_गन्ती_Register = 0xff5a;
अचर uint16_t usTimerPriorityRegister = 0xff32;
अचर uint16_t usTimerEnable = 0xC000;
अचर uint16_t usRetrigger = 0x0001;
अचर uint16_t us_Timer_माथिल्लो_Priority = 0x0000;
uint16_t usTimer0Control;

/* ( CPU frequency / 4 ) / clock 2 max count [inpw( 0xff62 ) = 7] */

अचर uint32_t ulClockFrequency = 0x7f31a0;

uint32_t ul_Timer_गन्ती = ulClockFrequency / ulTickRateHz;

    portOUTPUT_WORD( portTIMER_1_CONTROL_REGISTER, usTimerEnable | portTIMER_INTERRUPT_ENABLE | usRetrigger );
    portOUTPUT_WORD( us_Max_गन्ती_Register, ( uint16_t ) ul_Timer_गन्ती );
    portOUTPUT_WORD( usTimerPriorityRegister, us_Timer_माथिल्लो_Priority );

    /* Stop the DOS tick - don't do this if you want to maintain a TOD clock. */
    usTimer0Control = port_आगत_WORD( portTIMER_0_CONTROL_REGISTER );
    usTimer0Control &= ~portTIMER_INTERRUPT_ENABLE;
    portOUTPUT_WORD( portTIMER_0_CONTROL_REGISTER, usTimer0Control );
}


/*lint +e950 */
