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


/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the Tern EE 186
 * port.
 *----------------------------------------------------------*/

/* Library includes. */
#شامل <embedded.h>
#شامل <ae.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#define portTIMER_COMPARE ( uint16_t ) ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) / ( uint32_t ) 4 )

/* From the RDC data sheet. */
#define portENABLE_TIMER_AND_INTERRUPT ( uint16_t ) 0xe001

/* Interrupt control. */
#define portEIO_REGISTER 0xff22
#define portCLEAR_INTERRUPT 0x0008

/* Setup the hardware to generate the required tick frequency. */
ایستا تهی prvSetupTimerInterrupt( تهی );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#اگر( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ایستا تهی __interrupt __far prvPreemptiveTick( تهی );
#وگرنه
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ایستا تهی __interrupt __far prvNonPreemptiveTick( تهی );
#endif

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ایستا تهی __interrupt __far prvYieldProcessor( تهی );

/* The timer initialisation functions leave interrupts enabled,
which is not what we want.  This ISR is installed temporarily in case
the timer fires before we get a change to disable interrupts again. */
ایستا تهی __interrupt __far prvDummyISR( تهی );

/*-----------------------------------------------------------*/
/* See header file for description. */
پشته_Type_t *px_Port_Initialise_پشته( پشته_Type_t *px_بالاترین_Of_پشته, TaskFunction_t pxCode, تهی *pvParameters )
{
پشته_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_بالاترین_Of_پشته = 0x1111;
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x2222;
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x3333;
    px_بالاترین_Of_پشته--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_بالاترین_Of_پشته = FP_SEG( pvParameters );
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = FP_OFF( pvParameters );
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = FP_SEG( pxCode );
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = FP_OFF( pxCode );
    px_بالاترین_Of_پشته--;

    /* Next the status register and interrupt return address. */
    *px_بالاترین_Of_پشته = portINITIAL_SW;
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = FP_SEG( pxCode );
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = FP_OFF( pxCode );
    px_بالاترین_Of_پشته--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xAAAA; /* AX */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xBBBB; /* BX */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xCCCC; /* CX */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xDDDD; /* DX */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xEEEE; /* ES */
    px_بالاترین_Of_پشته--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_بالاترین_Of_پشته = DS_Reg;                     /* DS */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0x0123; /* SI */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xDDDD; /* DI */
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = ( پشته_Type_t ) 0xBBBB; /* BP */

    بازگشت px_بالاترین_Of_پشته;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( تهی )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( port_SWITCH_INT_عدد, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Kick off the scheduler by setting up the context of the first task. */
    portFIRST_CONTEXT();

    /* Should not get here! */
    بازگشت pdFALSE;
}
/*-----------------------------------------------------------*/

ایستا تهی __interrupt __far prvDummyISR( تهی )
{
    /* The timer initialisation functions leave interrupts enabled,
    which is not what we want.  This ISR is installed temporarily in case
    the timer fires before we get a change to disable interrupts again. */
    outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#اگر( configUSE_PREEMPTION == 1 )
    ایستا تهی __interrupt __far prvPreemptiveTick( تهی )
    {
        /* Get the scheduler to update the task states following the tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portSWITCH_CONTEXT();
        }

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#وگرنه
    ایستا تهی __interrupt __far prvNonPreemptiveTick( تهی )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#endif
/*-----------------------------------------------------------*/

ایستا تهی __interrupt __far prvYieldProcessor( تهی )
{
    /* Switch in the context of the next task to be run. */
    portSWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

تهی vPortEndScheduler( تهی )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ایستا تهی prvSetupTimerInterrupt( تهی )
{
ثابت uint16_t usTimerACompare = portTIMER_COMPARE, usTimerAMode = portENABLE_TIMER_AND_INTERRUPT;
ثابت uint16_t usT2_IRQ = 0x13;

    /* Configure the timer, the dummy handler is used here as the init
    function leaves interrupts enabled. */
    t2_init( usTimerAMode, usTimerACompare, prvDummyISR );

    /* Disable interrupts again before installing the real handlers. */
    portDISABLE_INTERRUPTS();

    #اگر( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        setvect( usT2_IRQ, prvPreemptiveTick );
    #وگرنه
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        setvect( usT2_IRQ, prvNonPreemptiveTick );
    #endif
}
