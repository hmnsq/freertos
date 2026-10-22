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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Port includes */
#شامل <sys/ports_def.h>

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the HCS12 port.
*----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/* NOTE: Interrupt service routines must be in non-banked memory - as does the
 * scheduler startup function. */
#تعریف_کرو ATTR_NEAR    __attribute__( ( near ) )

/* Manual context switch function.  This is the SWI ISR. */
/* __attribute__((interrupt)) */
خالی ATTR_NEAR v_پورٹ_Yield( خالی );

/* Tick context switch function.  This is the timer ISR. */
/* __attribute__((interrupt)) */
خالی ATTR_NEAR v_پورٹ_Tick_مداخلت( خالی );

/* Function in non-banked memory which actually switches to first task. */
بنیاد_Type_t ATTR_NEAR x_آغاز_Scheduler_Near( خالی );

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
 * critical section should not be left (i.e. interrupts should not be re-enabled)
 * until the nesting depth reaches 0.  This variable simply tracks the nesting
 * depth.  Each task maintains its own critical nesting depth variable so
 * uxCriticalNesting is saved and restored from the task stack during a context
 * switch. */
متلون UBaseType_t uxCriticalNesting = 0x80; /* un-initialized */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
     * expected by the HCS12 RTI instruction. */


    /* The address of the task function is placed in the stack byte at a time. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) *( ( ( ڈھیر_Type_t * ) ( &px_رمز ) ) + 1 );
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) *( ( ( ڈھیر_Type_t * ) ( &px_رمز ) ) + 0 );

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xff;
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xee;

    /* X register */
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xdd;
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xcc;

    /* A register contains parameter high byte. */
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) *( ( ( ڈھیر_Type_t * ) ( &pvParameters ) ) + 0 );

    /* B register contains parameter low byte. */
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) *( ( ( ڈھیر_Type_t * ) ( &pvParameters ) ) + 1 );

    /* CCR: Note that when the task starts interrupts will be enabled since
     * "I" bit of CCR is cleared */
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x80; /* keeps Stop disabled (MCU default) */

    /* tmp softregs used by GCC. Values right now don't matter. */
    __asm( "\n\
        movw _.چوکھٹا_2, 2,-%0                         \n\
        movw _.tmp, 2,-%0                           \n\
        movw _.z, 2,-%0                             \n\
        movw _.xy, 2,-%0                            \n\
        ;movw _.d2, 2,-%0                           \n\
        ;movw _.d1, 2,-%0                           \n\
    " : "=A" ( pxTopOfStack ) : "0" ( px_چوٹی_کا_ڈھیر ) );

    #اگر_تعریف_شدہ BANKED_MODEL
        /* The page of the task. */
        *--px_چوٹی_کا_ڈھیر = 0x30; /* can only directly start in PPAGE 0x30 */
    #اگر_ختم

    /* The critical nesting depth is initialised with 0 (meaning not in
     * a critical section). */
    *--px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00;


    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    /* Enable hardware RTI timer */
    /* Ignores configTICK_RATE_HZ */
    RTICTL = 0x50;  /* 16 MHz xtal: 976.56 Hz, 1024mS */
    CRGINT |= 0x80; /* RTIE */
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* xPortStartScheduler() does not start the scheduler directly because
     * the header file containing the xPortStartScheduler() prototype is part
     * of the common kernel code, and therefore cannot use the CODE_SEG pragma.
     * Instead it simply calls the locally defined xNearStartScheduler() -
     * which does use the CODE_SEG pragma. */

    int16_t اندراج d;

    __asm( "jmp  xStartSchedulerNear        ; will never return" : "=d" ( d ) );
    واپس d;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_آغاز_Scheduler_Near( خالی )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
     * disabled when this function is called. */
    prv_تیاری_Timer_مداخلت();

    /* Restore the context of the first task. */
    پورٹ_RESTORE_CONTEXT();

    پورٹ_ISR_دم();

    /* Should not get here! */
    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
خالی v_پورٹ_Yield( خالی )
{
    پورٹ_ISR_سر();

    /* NOTE: This is the trap routine (swi) although not defined as a trap.
     * It will fill the stack the same way as an ISR in order to mix preemtion
     * and cooperative yield. */

    پورٹ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٹ_RESTORE_CONTEXT();

    پورٹ_ISR_دم();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
خالی v_پورٹ_Tick_مداخلت( خالی )
{
    پورٹ_ISR_سر();

    /* Clear tick timer flag */
    CRGFLG = 0x80;

    #اگر configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        پورٹ_SAVE_CONTEXT();

        /* Increment the tick ... */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* A context switch is necessary. */
            vTaskSwitchContext();
        }

        /* Restore the context of a task - which may be a different task
         * to that interrupted. */
        پورٹ_RESTORE_CONTEXT();
    }
    #ورنہ /* if configUSE_PREEMPTION == 1 */
    {
        xTaskIncrementTick();
    }
    #اگر_ختم /* if configUSE_PREEMPTION == 1 */

    پورٹ_ISR_دم();
}
