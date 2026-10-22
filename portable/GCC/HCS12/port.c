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

/* GCC/HCS12 port by Jefferson L Smith, 2005 */

/* Scheduler includes. */
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

/* Port includes */
#ଅନ୍ତର୍ଭାଵ <sys/ports_def.h>

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the HCS12 port.
*----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );

/* NOTE: Interrupt service routines must be in non-banked memory - as does the
 * scheduler startup function. */
#define ATTR_NEAR    __attribute__( ( near ) )

/* Manual context switch function.  This is the SWI ISR. */
/* __attribute__((interrupt)) */
ଶୂନ୍ୟ ATTR_NEAR vPortYield( ଶୂନ୍ୟ );

/* Tick context switch function.  This is the timer ISR. */
/* __attribute__((interrupt)) */
ଶୂନ୍ୟ ATTR_NEAR vPortTickInterrupt( ଶୂନ୍ୟ );

/* Function in non-banked memory which actually switches to first task. */
BaseType_t ATTR_NEAR xStartSchedulerNear( ଶୂନ୍ୟ );

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
 * critical section should not be left (i.e. interrupts should not be re-enabled)
 * until the nesting depth reaches 0.  This variable simply tracks the nesting
 * depth.  Each task maintains its own critical nesting depth variable so
 * uxCriticalNesting is saved and restored from the task stack during a context
 * switch. */
ଅସ୍ଥିର UBaseType_t uxCriticalNesting = 0x80; /* un-initialized */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
     * expected by the HCS12 RTI instruction. */


    /* The address of the task function is placed in the stack byte at a time. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) *( ( ( ଗଦା_Type_t * ) ( &pxCode ) ) + 1 );
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) *( ( ( ଗଦା_Type_t * ) ( &pxCode ) ) + 0 );

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xff;
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xee;

    /* X register */
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xdd;
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xcc;

    /* A register contains parameter high byte. */
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) *( ( ( ଗଦା_Type_t * ) ( &pvParameters ) ) + 0 );

    /* B register contains parameter low byte. */
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) *( ( ( ଗଦା_Type_t * ) ( &pvParameters ) ) + 1 );

    /* CCR: Note that when the task starts interrupts will be enabled since
     * "I" bit of CCR is cleared */
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x80; /* keeps Stop disabled (MCU default) */

    /* tmp softregs used by GCC. Values right now don't matter. */
    __asm( "\n\
        movw _.frame, 2,-%0                         \n\
        movw _.tmp, 2,-%0                           \n\
        movw _.z, 2,-%0                             \n\
        movw _.xy, 2,-%0                            \n\
        ;movw _.d2, 2,-%0                           \n\
        ;movw _.d1, 2,-%0                           \n\
    " : "=A" ( pxTopOfStack ) : "0" ( px_ଶୀର୍ଷ_Of_ଗଦା ) );

    #ifdef BANKED_MODEL
        /* The page of the task. */
        *--px_ଶୀର୍ଷ_Of_ଗଦା = 0x30; /* can only directly start in PPAGE 0x30 */
    #endif

    /* The critical nesting depth is initialised with 0 (meaning not in
     * a critical section). */
    *--px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x00;


    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
    /* Enable hardware RTI timer */
    /* Ignores configTICK_RATE_HZ */
    RTICTL = 0x50;  /* 16 MHz xtal: 976.56 Hz, 1024mS */
    CRGINT |= 0x80; /* RTIE */
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    /* xPortStartScheduler() does not start the scheduler directly because
     * the header file containing the xPortStartScheduler() prototype is part
     * of the common kernel code, and therefore cannot use the CODE_SEG pragma.
     * Instead it simply calls the locally defined xNearStartScheduler() -
     * which does use the CODE_SEG pragma. */

    int16_t ପଞ୍ଜିକରଣ d;

    __asm( "jmp  xStartSchedulerNear        ; will never return" : "=d" ( d ) );
    ଫେରନ୍ତୁ d;
}
/*-----------------------------------------------------------*/

BaseType_t xStartSchedulerNear( ଶୂନ୍ୟ )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
     * disabled when this function is called. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task. */
    portRESTORE_CONTEXT();

    portISR_TAIL();

    /* Should not get here! */
    ଫେରନ୍ତୁ pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ )
{
    portISR_HEAD();

    /* NOTE: This is the trap routine (swi) although not defined as a trap.
     * It will fill the stack the same way as an ISR in order to mix preemtion
     * and cooperative yield. */

    portSAVE_CONTEXT();
    vTaskSwitchContext();
    portRESTORE_CONTEXT();

    portISR_TAIL();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
ଶୂନ୍ୟ vPortTickInterrupt( ଶୂନ୍ୟ )
{
    portISR_HEAD();

    /* Clear tick timer flag */
    CRGFLG = 0x80;

    #ଯଦି configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        portSAVE_CONTEXT();

        /* Increment the tick ... */
        ଯଦି( xTaskIncrementTick() != pdFALSE )
        {
            /* A context switch is necessary. */
            vTaskSwitchContext();
        }

        /* Restore the context of a task - which may be a different task
         * to that interrupted. */
        portRESTORE_CONTEXT();
    }
    #ଅନ୍ୟଥା /* if configUSE_PREEMPTION == 1 */
    {
        xTaskIncrementTick();
    }
    #endif /* if configUSE_PREEMPTION == 1 */

    portISR_TAIL();
}
