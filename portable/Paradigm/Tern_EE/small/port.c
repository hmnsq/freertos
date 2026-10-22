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
#समावेश <embedded.h>
#समावेश <ae.h>

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#घोषणा port_PRESCALE_मूल्य ( 16 )
#घोषणा portTIMER_COMPARE ( configCPU_CLOCK_HZ  / ( configTICK_RATE_HZ * 4UL ) )

/* From the RDC data sheet. */
#घोषणा portENABLE_TIMER_AND_INTERRUPT  ( uint16_t ) 0xe00b
#घोषणा portENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#घोषणा portEIO_REGISTER 0xff22
#घोषणा portCLEAR_INTERRUPT 0x0008

/* Setup the hardware to generate the required tick frequency. */
अटल व्योम prvSetupTimerInterrupt( व्योम );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
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

/*-----------------------------------------------------------*/
/* See header file for description. */
ढेर_Type_t *px_Port_Initialise_ढेर( ढेर_Type_t *px_शीर्ष_Of_ढेर, TaskFunction_t pxCode, व्योम *pvParameters )
{
ढेर_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_शीर्ष_Of_ढेर = 0x1111;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2222;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x3333;
    px_शीर्ष_Of_ढेर--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_शीर्ष_Of_ढेर = FP_OFF( pvParameters );
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = FP_OFF( pxCode );
    px_शीर्ष_Of_ढेर--;

    /* Next the status register and interrupt return address. */
    *px_शीर्ष_Of_ढेर = portINITIAL_SW;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = FP_SEG( pxCode );
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = FP_OFF( pxCode );
    px_शीर्ष_Of_ढेर--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xAAAA; /* AX */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xBBBB; /* BX */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xCCCC; /* CX */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xDDDD; /* DX */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xEEEE; /* ES */
    px_शीर्ष_Of_ढेर--;

    *px_शीर्ष_Of_ढेर = DS_Reg;                     /* DS */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x0123; /* SI */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xDDDD; /* DI */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xBBBB; /* BP */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( port_SWITCH_INT_संख्या, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Kick off the scheduler by setting up the context of the first task. */
    portFIRST_CONTEXT();

    /* Should not get here! */
    वापस pdFALSE;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#अगर( configUSE_PREEMPTION == 1 )
    अटल व्योम __interrupt __far prvPreemptiveTick( व्योम )
    {
        /* Get the scheduler to update the task states following the tick. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portEND_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#अन्यथा
    अटल व्योम __interrupt __far prvNonPreemptiveTick( व्योम )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#पूर्ण_अगर
/*-----------------------------------------------------------*/

अटल व्योम __interrupt __far prvYieldProcessor( व्योम )
{
    /* Switch in the context of the next task to be run. */
    portEND_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetupTimerInterrupt( व्योम )
{
स्थिर uint32_t ul_Compare_मूल्य = portTIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_मूल्य >> 4 );
    t2_init( portENABLE_TIMER, port_PRESCALE_मूल्य, शून्य );

    #अगर( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( portENABLE_TIMER_AND_INTERRUPT, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #अन्यथा
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( portENABLE_TIMER_AND_INTERRUPT, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #पूर्ण_अगर
}
