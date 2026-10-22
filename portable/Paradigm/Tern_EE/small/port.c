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
#अन्तर्भाव <embedded.h>
#अन्तर्भाव <ae.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#परिभाषय पत्तनम्_PRESCALE_मानम् ( 16 )
#परिभाषय पत्तनम्_TIMER_COMPARE ( configCPU_CLOCK_HZ  / ( config_TICK_दरः_HZ * 4UL ) )

/* From the RDC data sheet. */
#परिभाषय पत्तनम्_ENABLE_TIMER_AND_व्यवधानम्  ( uint16_t ) 0xe00b
#परिभाषय पत्तनम्_ENABLE_TIMER                ( uint16_t ) 0xC001

/* Interrupt control. */
#परिभाषय पत्तनम्_EIO_पञ्जिकाकोशः 0xff22
#परिभाषय पत्तनम्_CLEAR_व्यवधानम् 0x0008

/* Setup the hardware to generate the required tick frequency. */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#यदि( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    स्थिर शून्य __interrupt __far prvPreemptiveTick( शून्य );
#अन्यथा
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    स्थिर शून्य __interrupt __far prvNonPreemptiveTick( शून्य );
#यदि_अन्तः

/* Trap routine used by taskYIELD() to manually cause a context switch. */
स्थिर शून्य __interrupt __far prvYieldProcessor( शून्य );

/*-----------------------------------------------------------*/
/* See header file for description. */
राशिः_Type_t *px_पत्तनम्_Initialise_राशिः( राशिः_Type_t *px_शिखरम्_सम्बन्धि_राशिः, TaskFunction_t px_संहिता, शून्य *pvParameters )
{
राशिः_Type_t DS_Reg = 0;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_शिखरम्_सम्बन्धि_राशिः = 0x1111;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x2222;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x3333;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_शिखरम्_सम्बन्धि_राशिः = FP_OFF( pvParameters );
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = FP_OFF( px_संहिता );
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next the status register and interrupt return address. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_SW;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = FP_SEG( px_संहिता );
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = FP_OFF( px_संहिता );
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xAAAA; /* AX */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xBBBB; /* BX */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xCCCC; /* CX */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xDDDD; /* DX */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xEEEE; /* ES */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = DS_Reg;                     /* DS */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x0123; /* SI */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xDDDD; /* DI */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xBBBB; /* BP */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( पत्तनम्_SWITCH_INT_सङ्ख्या, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Kick off the scheduler by setting up the context of the first task. */
    पत्तनम्_FIRST_CONTEXT();

    /* Should not get here! */
    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#यदि( configUSE_PREEMPTION == 1 )
    स्थिर शून्य __interrupt __far prvPreemptiveTick( शून्य )
    {
        /* Get the scheduler to update the task states following the tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            पत्तनम्_अन्तः_SWITCHING_ISR();
        }

        /* Reset interrupt. */
        outport( पत्तनम्_EIO_पञ्जिकाकोशः, पत्तनम्_CLEAR_व्यवधानम् );
    }
#अन्यथा
    स्थिर शून्य __interrupt __far prvNonPreemptiveTick( शून्य )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( पत्तनम्_EIO_पञ्जिकाकोशः, पत्तनम्_CLEAR_व्यवधानम् );
    }
#यदि_अन्तः
/*-----------------------------------------------------------*/

स्थिर शून्य __interrupt __far prvYieldProcessor( शून्य )
{
    /* Switch in the context of the next task to be run. */
    पत्तनम्_अन्तः_SWITCHING_ISR();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
ध्रुव uint32_t ul_Compare_मानम् = पत्तनम्_TIMER_COMPARE;
uint16_t usTimerCompare;

    usTimerCompare = ( uint16_t ) ( ul_Compare_मानम् >> 4 );
    t2_init( पत्तनम्_ENABLE_TIMER, पत्तनम्_PRESCALE_मानम्, रिक्त );

    #यदि( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        t1_init( पत्तनम्_ENABLE_TIMER_AND_व्यवधानम्, usTimerCompare, usTimerCompare, prvPreemptiveTick );
    #अन्यथा
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        t1_init( पत्तनम्_ENABLE_TIMER_AND_व्यवधानम्, usTimerCompare, usTimerCompare, prvNonPreemptiveTick );
    #यदि_अन्तः
}
