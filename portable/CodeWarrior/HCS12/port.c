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
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/* Interrupt service routines have to be in non-banked memory - as does the
scheduler startup function. */
#ಸೂಚನೆ ಸಂಕೇತ_SEG __NEAR_SEG NON_BANKED

    /* Manual context switch function.  This is the SWI ISR. */
    ಶೂನ್ಯ ಅಡಚಣೆ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );

    /* Tick context switch function.  This is the timer ISR. */
    ಶೂನ್ಯ ಅಡಚಣೆ v_ಪೋರ್ಟ್_Tick_ಅಡಚಣೆ( ಶೂನ್ಯ );

    /* Simply called by xPortStartScheduler().  xPortStartScheduler() does not
    start the scheduler directly because the header file containing the
    xPortStartScheduler() prototype is part of the common kernel code, and
    therefore cannot use the CODE_SEG pragma. */
    ಸ್ಥಿರ ತಳ_Type_t x_Banked_ಆರಂಭ_Scheduler( ಶೂನ್ಯ );

#ಸೂಚನೆ ಸಂಕೇತ_SEG DEFAULT

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
critical section should not be left (i.e. interrupts should not be re-enabled)
until the nesting depth reaches 0.  This variable simply tracks the nesting
depth.  Each task maintains its own critical nesting depth variable so
uxCriticalNesting is saved and restored from the task stack during a context
switch. */
ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting = 0xff;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
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
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&px_ಸಂಕೇತ) ) + 1 );
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&px_ಸಂಕೇತ) ) + 0 );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xff;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xee;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* X register */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xdd;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xcc;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* A register contains parameter high byte. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&pvParameters) ) + 0 );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* B register contains parameter low byte. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) *( ((ರಾಶಿ_Type_t *) (&pvParameters) ) + 1 );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* CCR: Note that when the task starts interrupts will be enabled since
    "I" bit of CCR is cleared */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BANKED_MODEL
        /* The page of the task. */
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ( ( ಪೂರ್ಣಾಂಕ ) px_ಸಂಕೇತ );
        px_ತುದಿ_ದ_ರಾಶಿ--;
    #ಆದರೆ_ಅಂತ್ಯ

    /* Finally the critical nesting depth is initialised with 0 (not within
    a critical section). */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    Tick_Timer_ಗಣ_Freq_Hz( config_TICK_ದರ_HZ );
    TickTimer_Enable();
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* xPortStartScheduler() does not start the scheduler directly because
    the header file containing the xPortStartScheduler() prototype is part
    of the common kernel code, and therefore cannot use the CODE_SEG pragma.
    Instead it simply calls the locally defined xBankedStartScheduler() -
    which does use the CODE_SEG pragma. */

    ಹಿಂತಿರುಗಿ x_Banked_ಆರಂಭ_Scheduler();
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ ಸಂಕೇತ_SEG __NEAR_SEG NON_BANKED

ಸ್ಥಿರ ತಳ_Type_t x_Banked_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
    disabled when this function is called. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Restore the context of the first task. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();

    /* Simulate the end of an interrupt to start the scheduler off. */
    __asm( "rti" );

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are both interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
ಶೂನ್ಯ ಅಡಚಣೆ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_SAVE_CONTEXT();
    vTaskSwitchContext();
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
ಶೂನ್ಯ ಅಡಚಣೆ v_ಪೋರ್ಟ್_Tick_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    #ಆದರೆ configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        ಪೋರ್ಟ್_SAVE_CONTEXT();

        /* Increment the tick ... */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        TFLG1 = 1;

        /* Restore the context of a task - which may be a different task
        to that interrupted. */
        ಪೋರ್ಟ್_RESTORE_CONTEXT();
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        xTaskIncrementTick();
        TFLG1 = 1;
    }
    #ಆದರೆ_ಅಂತ್ಯ
}

#ಸೂಚನೆ ಸಂಕೇತ_SEG DEFAULT
