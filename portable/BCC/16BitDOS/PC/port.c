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

#समावेश <stdlib.h>
#समावेश <dos.h>
#समावेश <setjmp.h>

#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "portasm.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the industrial
 * PC port.
 *----------------------------------------------------------*/

/*lint -e950 Non ANSI reserved words okay in this file only. */

#घोषणा port_TIMER_INT_संख्या    0x08

/* Setup hardware for required tick interrupt rate. */
अटल व्योम prvSetTickFrequency( uint32_t ulTickRateHz );

/* Restore hardware to as it was prior to starting the scheduler. */
अटल व्योम prvExitFunction( व्योम );

/* Either chain to the DOS tick (which itself clears the PIC) or clear the PIC
directly.  We chain to the DOS tick as close as possible to the standard DOS
tick rate. */
अटल व्योम prvPortResetPIC( व्योम );

/* The ISR used depends on whether the preemptive or cooperative
scheduler is being used. */
#अगर( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    अटल व्योम __interrupt __far prvPreemptiveTick( व्योम );
#अन्यथा
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    अटल व्योम __interrupt __far prvNonPreemptiveTick( व्योम );
#पूर्ण_अगर

/* Trap routine used by taskYIELD() to manually cause a context switch. */
अटल व्योम __interrupt __far prvYieldProcessor( व्योम );

/* Set the tick frequency back so the floppy drive works correctly when the
scheduler exits. */
अटल व्योम prvSetTickFrequencyDefault( व्योम );

/*lint -e956 File scopes necessary here. */

/* Used to signal when to chain to the DOS tick, and when to just clear the PIC ourselves. */
अटल int16_t s_DOSTick_गणक;

/* Set true when the vectors are set so the scheduler will service the tick. */
अटल BaseType_t xSchedulerRunning = pdFALSE;

/* Points to the original routine installed on the vector we use for manual context switches.  This is then used to restore the original routine during prvExitFunction(). */
अटल व्योम ( __interrupt __far *pxOldSwitchISR )();

/* Points to the original routine installed on the vector we use to chain to the DOS tick.  This is then used to restore the original routine during prvExitFunction(). */
अटल व्योम ( __interrupt __far *pxOldSwitchISRPlus1 )();

/* Used to restore the original DOS context when the scheduler is ended. */
अटल लाँघ_बफ xJumpBuf;

/*lint +e956 */

/*-----------------------------------------------------------*/
BaseType_t xPortStartScheduler( व्योम )
{
pxISR pxOriginalTickISR;

    /* This is called with interrupts already disabled. */

    /* Remember what was on the interrupts we are going to use
    so we can put them back later if required. */
    pxOldSwitchISR = _dos_getvect( port_SWITCH_INT_संख्या );
    pxOriginalTickISR = _dos_getvect( port_TIMER_INT_संख्या );
    pxOldSwitchISRPlus1 = _dos_getvect( port_SWITCH_INT_संख्या + 1 );

    prvSetTickFrequency( configTICK_RATE_HZ );

    /* Put our manual switch (yield) function on a known
    vector. */
    _dos_setvect( port_SWITCH_INT_संख्या, prvYieldProcessor );

    /* Put the old tick on a different interrupt number so we can
    call it when we want. */
    _dos_setvect( port_SWITCH_INT_संख्या + 1, pxOriginalTickISR );

    /* The ISR used depends on whether the preemptive or cooperative
    scheduler is being used. */
    #अगर( configUSE_PREEMPTION == 1 )
    {
        /* Put our tick switch function on the timer interrupt. */
        _dos_setvect( port_TIMER_INT_संख्या, prvPreemptiveTick );
    }
    #अन्यथा
    {
        /* We want the timer interrupt to just increment the tick count. */
        _dos_setvect( port_TIMER_INT_संख्या, prvNonPreemptiveTick );
    }
    #पूर्ण_अगर

    /* Setup a counter that is used to call the DOS interrupt as close
    to it's original frequency as can be achieved given our chosen tick
    frequency. */
    s_DOSTick_गणक = portTICKS_PER_DOS_TICK;

    /* Clean up function if we want to return to DOS. */
    अगर( बनाओ_लाँघ( xJumpBuf ) != 0 )
    {
        prvExitFunction();
        xSchedulerRunning = pdFALSE;
    }
    अन्यथा
    {
        xSchedulerRunning = pdTRUE;

        /* Kick off the scheduler by setting up the context of the first task. */
        portFIRST_CONTEXT();
    }

    वापस xSchedulerRunning;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative
scheduler is being used. */
#अगर( configUSE_PREEMPTION == 1 )
    अटल व्योम __interrupt __far prvPreemptiveTick( व्योम )
    {
        /* Get the scheduler to update the task states following the tick. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portSWITCH_CONTEXT();
        }

        /* Reset the PIC ready for the next time. */
        prvPortResetPIC();
    }
#अन्यथा
    अटल व्योम __interrupt __far prvNonPreemptiveTick( व्योम )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();
        prvPortResetPIC();
    }
#पूर्ण_अगर
/*-----------------------------------------------------------*/

अटल व्योम __interrupt __far prvYieldProcessor( व्योम )
{
    /* Switch in the context of the next task to be run. */
    portSWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

अटल व्योम prvPortResetPIC( व्योम )
{
    /* We are going to call the DOS tick interrupt at as close a
    frequency to the normal DOS tick as possible. */

    /* WE SHOULD NOT DO THIS IF YIELD WAS CALLED. */
    --s_DOSTick_गणक;
    अगर( s_DOSTick_गणक <= 0 )
    {
        s_DOSTick_गणक = ( int16_t ) portTICKS_PER_DOS_TICK;
        __asm{ पूर्णांक  port_SWITCH_INT_संख्या + 1 };
    }
    अन्यथा
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

व्योम vPortEndScheduler( व्योम )
{
    /* Jump back to the processor state prior to starting the
    scheduler.  This means we are not going to be using a
    task stack frame so the task can be deleted. */
    दीर्घ_लाँघ( xJumpBuf, 1 );
}
/*-----------------------------------------------------------*/

अटल व्योम prvExitFunction( व्योम )
{
व्योम ( __interrupt __far *pxOriginalTickISR )();

    /* Interrupts should be disabled here anyway - but no
    harm in making sure. */
    portDISABLE_INTERRUPTS();
    अगर( xSchedulerRunning == pdTRUE )
    {
        /* Set the DOS tick back onto the timer ticker. */
        pxOriginalTickISR = _dos_getvect( port_SWITCH_INT_संख्या + 1 );
        _dos_setvect( port_TIMER_INT_संख्या, pxOriginalTickISR );
        prvSetTickFrequencyDefault();

        /* Put back the switch interrupt routines that was in place
        before the scheduler started. */
        _dos_setvect( port_SWITCH_INT_संख्या, pxOldSwitchISR );
        _dos_setvect( port_SWITCH_INT_संख्या + 1, pxOldSwitchISRPlus1 );
    }
    /* The tick timer is back how DOS wants it.  We can re-enable
    interrupts without the scheduler being called. */
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetTickFrequency( uint32_t ulTickRateHz )
{
स्थिर uint16_t usPIT_MODE = ( uint16_t ) 0x43;
स्थिर uint16_t usPIT0 = ( uint16_t ) 0x40;
स्थिर uint32_t ulPIT_CONST = ( uint32_t ) 1193180UL;
स्थिर uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;
uint32_t ulOutput;

    /* Setup the 8245 to tick at the wanted frequency. */
    portOUTPUT_BYTE( usPIT_MODE, us8254_CTR0_MODE3 );
    ulOutput = ulPIT_CONST / ulTickRateHz;
    portOUTPUT_BYTE( usPIT0, ( uint16_t )( ulOutput & ( uint32_t ) 0xff ) );
    ulOutput >>= 8;
    portOUTPUT_BYTE( usPIT0, ( uint16_t ) ( ulOutput & ( uint32_t ) 0xff ) );
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetTickFrequencyDefault( व्योम )
{
स्थिर uint16_t usPIT_MODE = ( uint16_t ) 0x43;
स्थिर uint16_t usPIT0 = ( uint16_t ) 0x40;
स्थिर uint16_t us8254_CTR0_MODE3 = ( uint16_t ) 0x36;

    portOUTPUT_BYTE( usPIT_MODE, us8254_CTR0_MODE3 );
    portOUTPUT_BYTE( usPIT0,0 );
    portOUTPUT_BYTE( usPIT0,0 );
}


/*lint +e950 */
