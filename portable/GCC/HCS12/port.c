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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Port includes */
#ضمن <sys/ports_def.h>

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the HCS12 port.
*----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/* NOTE: Interrupt service routines must be in non-banked memory - as does the
 * scheduler startup function. */
#وصف_ڪريو ATTR_NEAR    __attribute__( ( near ) )

/* Manual context switch function.  This is the SWI ISR. */
/* __attribute__((interrupt)) */
فراغ ATTR_NEAR v_پورٽ_Yield( فراغ );

/* Tick context switch function.  This is the timer ISR. */
/* __attribute__((interrupt)) */
فراغ ATTR_NEAR v_پورٽ_Tick_مداخلت( فراغ );

/* Function in non-banked memory which actually switches to first task. */
بنياد_Type_t ATTR_NEAR x_شروعات_Scheduler_Near( فراغ );

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
 * critical section should not be left (i.e. interrupts should not be re-enabled)
 * until the nesting depth reaches 0.  This variable simply tracks the nesting
 * depth.  Each task maintains its own critical nesting depth variable so
 * uxCriticalNesting is saved and restored from the task stack during a context
 * switch. */
متطاير UBaseType_t uxCriticalNesting = 0x80; /* un-initialized */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
     * expected by the HCS12 RTI instruction. */


    /* The address of the task function is placed in the stack byte at a time. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) *( ( ( ڍير_Type_t * ) ( &px_ڪوڊ ) ) + 1 );
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) *( ( ( ڍير_Type_t * ) ( &px_ڪوڊ ) ) + 0 );

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xff;
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xee;

    /* X register */
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xdd;
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xcc;

    /* A register contains parameter high byte. */
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) *( ( ( ڍير_Type_t * ) ( &pvParameters ) ) + 0 );

    /* B register contains parameter low byte. */
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) *( ( ( ڍير_Type_t * ) ( &pvParameters ) ) + 1 );

    /* CCR: Note that when the task starts interrupts will be enabled since
     * "I" bit of CCR is cleared */
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x80; /* keeps Stop disabled (MCU default) */

    /* tmp softregs used by GCC. Values right now don't matter. */
    __asm( "\n\
        movw _.چوکٺو_2, 2,-%0                         \n\
        movw _.tmp, 2,-%0                           \n\
        movw _.z, 2,-%0                             \n\
        movw _.xy, 2,-%0                            \n\
        ;movw _.d2, 2,-%0                           \n\
        ;movw _.d1, 2,-%0                           \n\
    " : "=A" ( pxTopOfStack ) : "0" ( px_چوٽي_جو_ڍير ) );

    #جيڪڏهن_وصف_ٿيل BANKED_MODEL
        /* The page of the task. */
        *--px_چوٽي_جو_ڍير = 0x30; /* can only directly start in PPAGE 0x30 */
    #جيڪڏهن_پورو

    /* The critical nesting depth is initialised with 0 (meaning not in
     * a critical section). */
    *--px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00;


    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    /* Enable hardware RTI timer */
    /* Ignores configTICK_RATE_HZ */
    RTICTL = 0x50;  /* 16 MHz xtal: 976.56 Hz, 1024mS */
    CRGINT |= 0x80; /* RTIE */
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* xPortStartScheduler() does not start the scheduler directly because
     * the header file containing the xPortStartScheduler() prototype is part
     * of the common kernel code, and therefore cannot use the CODE_SEG pragma.
     * Instead it simply calls the locally defined xNearStartScheduler() -
     * which does use the CODE_SEG pragma. */

    int16_t سجل d;

    __asm( "jmp  xStartSchedulerNear        ; will never return" : "=d" ( d ) );
    أرجع d;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_شروعات_Scheduler_Near( فراغ )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
     * disabled when this function is called. */
    prv_تياري_Timer_مداخلت();

    /* Restore the context of the first task. */
    پورٽ_RESTORE_CONTEXT();

    پورٽ_ISR_پڇ();

    /* Should not get here! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
فراغ v_پورٽ_Yield( فراغ )
{
    پورٽ_ISR_سر();

    /* NOTE: This is the trap routine (swi) although not defined as a trap.
     * It will fill the stack the same way as an ISR in order to mix preemtion
     * and cooperative yield. */

    پورٽ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٽ_RESTORE_CONTEXT();

    پورٽ_ISR_پڇ();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
فراغ v_پورٽ_Tick_مداخلت( فراغ )
{
    پورٽ_ISR_سر();

    /* Clear tick timer flag */
    CRGFLG = 0x80;

    #إذا configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        پورٽ_SAVE_CONTEXT();

        /* Increment the tick ... */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* A context switch is necessary. */
            vTaskSwitchContext();
        }

        /* Restore the context of a task - which may be a different task
         * to that interrupted. */
        پورٽ_RESTORE_CONTEXT();
    }
    #وإلا /* if configUSE_PREEMPTION == 1 */
    {
        xTaskIncrementTick();
    }
    #جيڪڏهن_پورو /* if configUSE_PREEMPTION == 1 */

    پورٽ_ISR_پڇ();
}
