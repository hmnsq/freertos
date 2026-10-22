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
#ضمن <embedded.h>
#ضمن <ae.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#define port_PRESCALE_نيلاي ( 16 )
#define portTIMER_COMPARE ( configCPU_CLOCK_HZ  / ( configTICK_RATE_HZ * 4UL ) )

/* From the RDC data sheet. */
#define portENABLE_TIMER_AND_INTERRUPT  ( uint16_t ) 0xe00b
#define portENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#define portEIO_REGISTER 0xff22
#define portCLEAR_INTERRUPT 0x0008

/* Setup the hardware to generate the required tick frequency. */
ساكن فراغ prvSetupTimerInterrupt( فراغ );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#إذا( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ساكن فراغ __interrupt __far prvPreemptiveTick( فراغ );
#وإلا
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ );
#endif

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ساكن فراغ __interrupt __far prvYieldProcessor( فراغ );

/*-----------------------------------------------------------*/
/* See header file for description. */
تيندنن_Type_t *px_Port_Initialise_تيندنن( تيندنن_Type_t *px_اتس_Of_تيندنن, TaskFunction_t pxCode, فراغ *pvParameters )
{
تيندنن_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_اتس_Of_تيندنن = 0x1111;
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x2222;
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = 0x3333;
    px_اتس_Of_تيندنن--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_اتس_Of_تيندنن = FP_OFF( pvParameters );
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = FP_OFF( pxCode );
    px_اتس_Of_تيندنن--;

    /* Next the status register and interrupt return address. */
    *px_اتس_Of_تيندنن = portINITIAL_SW;
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = FP_SEG( pxCode );
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = FP_OFF( pxCode );
    px_اتس_Of_تيندنن--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xAAAA; /* AX */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xBBBB; /* BX */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xCCCC; /* CX */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xDDDD; /* DX */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xEEEE; /* ES */
    px_اتس_Of_تيندنن--;

    *px_اتس_Of_تيندنن = DS_Reg;                     /* DS */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x0123; /* SI */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xDDDD; /* DI */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xBBBB; /* BP */

    أرجع px_اتس_Of_تيندنن;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( port_SWITCH_INT_نومبور, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Kick off the scheduler by setting up the context of the first task. */
    portFIRST_CONTEXT();

    /* Should not get here! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#إذا( configUSE_PREEMPTION == 1 )
    ساكن فراغ __interrupt __far prvPreemptiveTick( فراغ )
    {
        /* Get the scheduler to update the task states following the tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            portEND_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#وإلا
    ساكن فراغ __interrupt __far prvNonPreemptiveTick( فراغ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( portEIO_REGISTER, portCLEAR_INTERRUPT );
    }
#endif
/*-----------------------------------------------------------*/

ساكن فراغ __interrupt __far prvYieldProcessor( فراغ )
{
    /* Switch in the context of the next task to be run. */
    portEND_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSetupTimerInterrupt( فراغ )
{
ثابت uint32_t ul_Compare_نيلاي = portTIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_نيلاي >> 4 );
    t2_init( portENABLE_TIMER, port_PRESCALE_نيلاي, عدم );

    #إذا( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( portENABLE_TIMER_AND_INTERRUPT, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #وإلا
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( portENABLE_TIMER_AND_INTERRUPT, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #endif
}
