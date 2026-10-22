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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Port includes */
#అన్తర్భావ <sys/ports_def.h>

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the HCS12 port.
*----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/* NOTE: Interrupt service routines must be in non-banked memory - as does the
 * scheduler startup function. */
#నిర్వచించు ATTR_NEAR    __attribute__( ( near ) )

/* Manual context switch function.  This is the SWI ISR. */
/* __attribute__((interrupt)) */
శూన్య ATTR_NEAR v_పోర్టు_Yield( శూన్య );

/* Tick context switch function.  This is the timer ISR. */
/* __attribute__((interrupt)) */
శూన్య ATTR_NEAR v_పోర్టు_Tick_అంతరాయం( శూన్య );

/* Function in non-banked memory which actually switches to first task. */
పునాది_Type_t ATTR_NEAR x_ప్రారంభం_Scheduler_Near( శూన్య );

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
 * critical section should not be left (i.e. interrupts should not be re-enabled)
 * until the nesting depth reaches 0.  This variable simply tracks the nesting
 * depth.  Each task maintains its own critical nesting depth variable so
 * uxCriticalNesting is saved and restored from the task stack during a context
 * switch. */
అస్థిర UBaseType_t uxCriticalNesting = 0x80; /* un-initialized */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
     * expected by the HCS12 RTI instruction. */


    /* The address of the task function is placed in the stack byte at a time. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) *( ( ( దొంతర_Type_t * ) ( &px_సంకేతం ) ) + 1 );
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) *( ( ( దొంతర_Type_t * ) ( &px_సంకేతం ) ) + 0 );

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xff;
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xee;

    /* X register */
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xdd;
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xcc;

    /* A register contains parameter high byte. */
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) *( ( ( దొంతర_Type_t * ) ( &pvParameters ) ) + 0 );

    /* B register contains parameter low byte. */
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) *( ( ( దొంతర_Type_t * ) ( &pvParameters ) ) + 1 );

    /* CCR: Note that when the task starts interrupts will be enabled since
     * "I" bit of CCR is cleared */
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x80; /* keeps Stop disabled (MCU default) */

    /* tmp softregs used by GCC. Values right now don't matter. */
    __asm( "\n\
        movw _.చట్రం_2, 2,-%0                         \n\
        movw _.tmp, 2,-%0                           \n\
        movw _.z, 2,-%0                             \n\
        movw _.xy, 2,-%0                            \n\
        ;movw _.d2, 2,-%0                           \n\
        ;movw _.d1, 2,-%0                           \n\
    " : "=A" ( pxTopOfStack ) : "0" ( px_శిఖరం_యొక్క_దొంతర ) );

    #నిర్వచితమైతే BANKED_MODEL
        /* The page of the task. */
        *--px_శిఖరం_యొక్క_దొంతర = 0x30; /* can only directly start in PPAGE 0x30 */
    #అయితే_ముగింపు

    /* The critical nesting depth is initialised with 0 (meaning not in
     * a critical section). */
    *--px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00;


    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Enable hardware RTI timer */
    /* Ignores configTICK_RATE_HZ */
    RTICTL = 0x50;  /* 16 MHz xtal: 976.56 Hz, 1024mS */
    CRGINT |= 0x80; /* RTIE */
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* xPortStartScheduler() does not start the scheduler directly because
     * the header file containing the xPortStartScheduler() prototype is part
     * of the common kernel code, and therefore cannot use the CODE_SEG pragma.
     * Instead it simply calls the locally defined xNearStartScheduler() -
     * which does use the CODE_SEG pragma. */

    int16_t నమోదు d;

    __asm( "jmp  xStartSchedulerNear        ; will never return" : "=d" ( d ) );
    తిరిగి d;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_ప్రారంభం_Scheduler_Near( శూన్య )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
     * disabled when this function is called. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Restore the context of the first task. */
    పోర్టు_RESTORE_CONTEXT();

    పోర్టు_ISR_తోక();

    /* Should not get here! */
    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
శూన్య v_పోర్టు_Yield( శూన్య )
{
    పోర్టు_ISR_తల();

    /* NOTE: This is the trap routine (swi) although not defined as a trap.
     * It will fill the stack the same way as an ISR in order to mix preemtion
     * and cooperative yield. */

    పోర్టు_SAVE_CONTEXT();
    vTaskSwitchContext();
    పోర్టు_RESTORE_CONTEXT();

    పోర్టు_ISR_తోక();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
శూన్య v_పోర్టు_Tick_అంతరాయం( శూన్య )
{
    పోర్టు_ISR_తల();

    /* Clear tick timer flag */
    CRGFLG = 0x80;

    #ఒకవేళ configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        పోర్టు_SAVE_CONTEXT();

        /* Increment the tick ... */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* A context switch is necessary. */
            vTaskSwitchContext();
        }

        /* Restore the context of a task - which may be a different task
         * to that interrupted. */
        పోర్టు_RESTORE_CONTEXT();
    }
    #లేకపోతే /* if configUSE_PREEMPTION == 1 */
    {
        xTaskIncrementTick();
    }
    #అయితే_ముగింపు /* if configUSE_PREEMPTION == 1 */

    పోర్టు_ISR_తోక();
}
