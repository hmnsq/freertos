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
#அந்தர்பாவ <embedded.h>
#அந்தர்பாவ <ae.h>

/* Scheduler includes. */
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"
#அந்தர்பாவ "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#define port_PRESCALE_மதிப்பு ( 16 )
#define portTIMER_COMPARE ( configCPU_CLOCK_HZ  / ( configTICK_RATE_HZ * 4UL ) )

/* From the RDC data sheet. */
#define portENABLE_TIMER_AND_INTERRUPT  ( uint16_t ) 0xe00b
#define portENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#define portEIO_REGISTER 0xff22
#define portCLEAR_INTERRUPT 0x0008

/* Setup the hardware to generate the required tick frequency. */
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை );

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

/*-----------------------------------------------------------*/
/* See header file for description. */
அடுக்கு_Type_t *px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t *px_உச்சி_Of_அடுக்கு, TaskFunction_t pxCode, வெறுமை *pvParameters )
{
அடுக்கு_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_உச்சி_Of_அடுக்கு = 0x1111;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x2222;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x3333;
    px_உச்சி_Of_அடுக்கு--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_உச்சி_Of_அடுக்கு = FP_OFF( pvParameters );
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = FP_OFF( pxCode );
    px_உச்சி_Of_அடுக்கு--;

    /* Next the status register and interrupt return address. */
    *px_உச்சி_Of_அடுக்கு = portINITIAL_SW;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = FP_SEG( pxCode );
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = FP_OFF( pxCode );
    px_உச்சி_Of_அடுக்கு--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xAAAA; /* AX */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xBBBB; /* BX */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xCCCC; /* CX */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xDDDD; /* DX */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xEEEE; /* ES */
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = DS_Reg;                     /* DS */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0x0123; /* SI */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xDDDD; /* DI */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0xBBBB; /* BP */

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( port_SWITCH_INT_எண், prvYieldProcessor );

    /* Setup the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Kick off the scheduler by setting up the context of the first task. */
    portFIRST_CONTEXT();

    /* Should not get here! */
    திரும்பு pdFALSE;
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
            portEND_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#இல்லையெனில்
    நிலையான வெறுமை __interrupt __far prvNonPreemptiveTick( வெறுமை )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#endif
/*-----------------------------------------------------------*/

நிலையான வெறுமை __interrupt __far prvYieldProcessor( வெறுமை )
{
    /* Switch in the context of the next task to be run. */
    portEND_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை )
{
மாறிலி uint32_t ul_Compare_மதிப்பு = portTIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_மதிப்பு >> 4 );
    t2_init( portENABLE_TIMER, port_PRESCALE_மதிப்பு, வெற்று );

    #எனில்( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( portENABLE_TIMER_AND_INTERRUPT, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #இல்லையெனில்
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( portENABLE_TIMER_AND_INTERRUPT, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #endif
}
