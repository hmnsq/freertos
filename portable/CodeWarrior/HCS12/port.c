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

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"


/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the HCS12 port.
 *----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ );

/* Interrupt service routines have to be in non-banked memory - as does the
scheduler startup function. */
#pragma CODE_SEG __NEAR_SEG NON_BANKED

    /* Manual context switch function.  This is the SWI ISR. */
    ಶೂನ್ಯ interrupt vPortYield( ಶೂನ್ಯ );

    /* Tick context switch function.  This is the timer ISR. */
    ಶೂನ್ಯ interrupt vPortTickInterrupt( ಶೂನ್ಯ );

    /* Simply called by xPortStartScheduler().  xPortStartScheduler() does not
    start the scheduler directly because the header file containing the
    xPortStartScheduler() prototype is part of the common kernel code, and
    therefore cannot use the CODE_SEG pragma. */
    ಸ್ಥಿರ BaseType_t xBankedStartScheduler( ಶೂನ್ಯ );

#pragma CODE_SEG DEFAULT

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
critical section should not be left (i.e. interrupts should not be re-enabled)
until the nesting depth reaches 0.  This variable simply tracks the nesting
depth.  Each task maintains its own critical nesting depth variable so
uxCriticalNesting is saved and restored from the task stack during a context
switch. */
ಚಞ್ಚಲ UBaseType_t uxCriticalNesting = 0xff;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_Of_ರಾಶಿ, TaskFunction_t pxCode, ಶೂನ್ಯ *pvParameters )
{
    /*
        Place a few bytes of known values on the bottom of the stack.
        This can be uncommented to provide useful stack markers when debugging.

        *pxTopOfStack = ( StackType_t ) 0x11;
        pxTopOfStack--;
        *pxTopOfStack = ( StackType_t ) 0x22;
        pxTopOfStack--;
        *pxTopOfStack = ( StackType_t ) 0x33;
        pxTopOfStack--;
    */



    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
    expected by the HCS12 RTI instruction. */


    /* The address of the task function is placed in the stack byte at a time. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&pxCode) ) + 1 );
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&pxCode) ) + 0 );
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xff;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xee;
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* X register */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xdd;
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xcc;
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* A register contains parameter high byte. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&pvParameters) ) + 0 );
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* B register contains parameter low byte. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&pvParameters) ) + 1 );
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* CCR: Note that when the task starts interrupts will be enabled since
    "I" bit of CCR is cleared */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;
    px_ತುದಿ_Of_ರಾಶಿ--;

    #ifdef BANKED_MODEL
        /* The page of the task. */
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ( ಪೂರ್ಣಾಙ್ಕ ) pxCode );
        px_ತುದಿ_Of_ರಾಶಿ--;
    #endif

    /* Finally the critical nesting depth is initialised with 0 (not within
    a critical section). */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    TickTimer_SetFreqHz( configTICK_RATE_HZ );
    TickTimer_Enable();
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    /* xPortStartScheduler() does not start the scheduler directly because
    the header file containing the xPortStartScheduler() prototype is part
    of the common kernel code, and therefore cannot use the CODE_SEG pragma.
    Instead it simply calls the locally defined xBankedStartScheduler() -
    which does use the CODE_SEG pragma. */

    ಪ್ರತ್ಯಾಗಮ xBankedStartScheduler();
}
/*-----------------------------------------------------------*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED

ಸ್ಥಿರ BaseType_t xBankedStartScheduler( ಶೂನ್ಯ )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
    disabled when this function is called. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task. */
    portRESTORE_CONTEXT();

    /* Simulate the end of an interrupt to start the scheduler off. */
    __asm( "rti" );

    /* Should not get here! */
    ಪ್ರತ್ಯಾಗಮ pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are both interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
ಶೂನ್ಯ interrupt vPortYield( ಶೂನ್ಯ )
{
    portSAVE_CONTEXT();
    vTaskSwitchContext();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
ಶೂನ್ಯ interrupt vPortTickInterrupt( ಶೂನ್ಯ )
{
    #ಯದಿ configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        portSAVE_CONTEXT();

        /* Increment the tick ... */
        ಯದಿ( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        TFLG1 = 1;

        /* Restore the context of a task - which may be a different task
        to that interrupted. */
        portRESTORE_CONTEXT();
    }
    #ಅನ್ಯಥಾ
    {
        xTaskIncrementTick();
        TFLG1 = 1;
    }
    #endif
}

#pragma CODE_SEG DEFAULT
