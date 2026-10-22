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
#ଅନ୍ତର୍ଭାଵ <embedded.h>
#ଅନ୍ତର୍ଭାଵ <ae.h>

/* Scheduler includes. */
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"
#ଅନ୍ତର୍ଭାଵ "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#define portTIMER_COMPARE ( uint16_t ) ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) / ( uint32_t ) 4 )

/* From the RDC data sheet. */
#define portENABLE_TIMER_AND_INTERRUPT ( uint16_t ) 0xe001

/* Interrupt control. */
#define portEIO_REGISTER 0xff22
#define portCLEAR_INTERRUPT 0x0008

/* Setup the hardware to generate the required tick frequency. */
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ଯଦି( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvPreemptiveTick( ଶୂନ୍ୟ );
#ଅନ୍ୟଥା
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvNonPreemptiveTick( ଶୂନ୍ୟ );
#endif

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvYieldProcessor( ଶୂନ୍ୟ );

/* The timer initialisation functions leave interrupts enabled,
which is not what we want.  This ISR is installed temporarily in case
the timer fires before we get a change to disable interrupts again. */
ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvDummyISR( ଶୂନ୍ୟ );

/*-----------------------------------------------------------*/
/* See header file for description. */
ଗଦା_Type_t *px_Port_Initialise_ଗଦା( ଗଦା_Type_t *px_ଶୀର୍ଷ_Of_ଗଦା, TaskFunction_t pxCode, ଶୂନ୍ୟ *pvParameters )
{
ଗଦା_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_ଶୀର୍ଷ_Of_ଗଦା = 0x1111;
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = 0x2222;
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = 0x3333;
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_ଶୀର୍ଷ_Of_ଗଦା = FP_SEG( pvParameters );
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = FP_OFF( pvParameters );
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = FP_SEG( pxCode );
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = FP_OFF( pxCode );
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    /* Next the status register and interrupt return address. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = portINITIAL_SW;
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = FP_SEG( pxCode );
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = FP_OFF( pxCode );
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xAAAA; /* AX */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xBBBB; /* BX */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xCCCC; /* CX */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xDDDD; /* DX */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xEEEE; /* ES */
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_ଶୀର୍ଷ_Of_ଗଦା = DS_Reg;                     /* DS */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x0123; /* SI */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xDDDD; /* DI */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xBBBB; /* BP */

    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( port_SWITCH_INT_ସଂଖ୍ୟା, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Kick off the scheduler by setting up the context of the first task. */
    portFIRST_CONTEXT();

    /* Should not get here! */
    ଫେରନ୍ତୁ pdFALSE;
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvDummyISR( ଶୂନ୍ୟ )
{
    /* The timer initialisation functions leave interrupts enabled,
    which is not what we want.  This ISR is installed temporarily in case
    the timer fires before we get a change to disable interrupts again. */
    outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ଯଦି( configUSE_PREEMPTION == 1 )
    ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvPreemptiveTick( ଶୂନ୍ୟ )
    {
        /* Get the scheduler to update the task states following the tick. */
        ଯଦି( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portSWITCH_CONTEXT();
        }

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#ଅନ୍ୟଥା
    ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvNonPreemptiveTick( ଶୂନ୍ୟ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#endif
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ __interrupt __far prvYieldProcessor( ଶୂନ୍ୟ )
{
    /* Switch in the context of the next task to be run. */
    portSWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
ଅଚଳ uint16_t usTimerACompare = portTIMER_COMPARE, usTimerAMode = portENABLE_TIMER_AND_INTERRUPT;
ଅଚଳ uint16_t usT2_IRQ = 0x13;

    /* Configure the timer, the dummy handler is used here as the init
    function leaves interrupts enabled. */
    t2_init( usTimerAMode, usTimerACompare, prvDummyISR );

    /* Disable interrupts again before installing the real handlers. */
    portDISABLE_INTERRUPTS();

    #ଯଦି( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        setvect( usT2_IRQ, prvPreemptiveTick );
    #ଅନ୍ୟଥା
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        setvect( usT2_IRQ, prvNonPreemptiveTick );
    #endif
}
