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
#ಅನ್ತರ್ಭಾವ <embedded.h>
#ಅನ್ತರ್ಭಾವ <ae.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "portasm.h"

/* The timer increments every four clocks, hence the divide by 4. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE ( uint16_t ) ( ( configCPU_CLOCK_HZ / config_TICK_ದರ_HZ ) / ( uint32_t ) 4 )

/* From the RDC data sheet. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_TIMER_AND_ಅಡಚಣೆ ( uint16_t ) 0xe001

/* Interrupt control. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EIO_ರಿಜಿಸ್ಟರ್ 0xff22
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ 0x0008

/* Setup the hardware to generate the required tick frequency. */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ಆದರೆ( configUSE_PREEMPTION == 1 )
    /* Tick service routine used by the scheduler when preemptive scheduling is
    being used. */
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvPreemptiveTick( ಶೂನ್ಯ );
#ಇಲ್ಲದಿದ್ದರೆ
    /* Tick service routine used by the scheduler when cooperative scheduling is
    being used. */
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvNonPreemptiveTick( ಶೂನ್ಯ );
#ಆದರೆ_ಅಂತ್ಯ

/* Trap routine used by taskYIELD() to manually cause a context switch. */
ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvYieldProcessor( ಶೂನ್ಯ );

/* The timer initialisation functions leave interrupts enabled,
which is not what we want.  This ISR is installed temporarily in case
the timer fires before we get a change to disable interrupts again. */
ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvDummyISR( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/
/* See header file for description. */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
ರಾಶಿ_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1111;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2222;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x3333;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_ತುದಿ_ದ_ರಾಶಿ = FP_SEG( pvParameters );
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = FP_OFF( pvParameters );
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = FP_SEG( px_ಸಂಕೇತ );
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = FP_OFF( px_ಸಂಕೇತ );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Next the status register and interrupt return address. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_SW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = FP_SEG( px_ಸಂಕೇತ );
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = FP_OFF( px_ಸಂಕೇತ );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xAAAA; /* AX */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xBBBB; /* BX */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xCCCC; /* CX */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xDDDD; /* DX */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xEEEE; /* ES */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_ತುದಿ_ದ_ರಾಶಿ = DS_Reg;                     /* DS */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0123; /* SI */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xDDDD; /* DI */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xBBBB; /* BP */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* This is called with interrupts already disabled. */

    /* Put our manual switch (yield) function on a known
    vector. */
    setvect( ಪೋರ್ಟ್_SWITCH_INT_ಸಂಖ್ಯೆ, prvYieldProcessor );

    /* Setup the tick interrupt. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Kick off the scheduler by setting up the context of the first task. */
    ಪೋರ್ಟ್_ಮೊದಲ_CONTEXT();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvDummyISR( ಶೂನ್ಯ )
{
    /* The timer initialisation functions leave interrupts enabled,
    which is not what we want.  This ISR is installed temporarily in case
    the timer fires before we get a change to disable interrupts again. */
    outport( ಪೋರ್ಟ್_EIO_ರಿಜಿಸ್ಟರ್, ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ );
}
/*-----------------------------------------------------------*/

/* The ISR used depends on whether the preemptive or cooperative scheduler
is being used. */
#ಆದರೆ( configUSE_PREEMPTION == 1 )
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Get the scheduler to update the task states following the tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch in the context of the next task to be run. */
            ಪೋರ್ಟ್_SWITCH_CONTEXT();
        }

        /* Reset interrupt. */
        outport( ಪೋರ್ಟ್_EIO_ರಿಜಿಸ್ಟರ್, ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ );
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvNonPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Same as preemptive tick, but the cooperative scheduler is being used
        so we don't have to switch in the context of the next task. */
        xTaskIncrementTick();

        /* Reset interrupt. */
        outport( ಪೋರ್ಟ್_EIO_ರಿಜಿಸ್ಟರ್, ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ );
    }
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ __interrupt __far prvYieldProcessor( ಶೂನ್ಯ )
{
    /* Switch in the context of the next task to be run. */
    ಪೋರ್ಟ್_SWITCH_CONTEXT();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
ಸ್ಥಿರಾಂಕ uint16_t usTimerACompare = ಪೋರ್ಟ್_TIMER_COMPARE, usTimerAMode = ಪೋರ್ಟ್_ENABLE_TIMER_AND_ಅಡಚಣೆ;
ಸ್ಥಿರಾಂಕ uint16_t usT2_IRQ = 0x13;

    /* Configure the timer, the dummy handler is used here as the init
    function leaves interrupts enabled. */
    t2_init( usTimerAMode, usTimerACompare, prvDummyISR );

    /* Disable interrupts again before installing the real handlers. */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    #ಆದರೆ( configUSE_PREEMPTION == 1 )
        /* Tick service routine used by the scheduler when preemptive scheduling is
        being used. */
        setvect( usT2_IRQ, prvPreemptiveTick );
    #ಇಲ್ಲದಿದ್ದರೆ
        /* Tick service routine used by the scheduler when cooperative scheduling is
        being used. */
        setvect( usT2_IRQ, prvNonPreemptiveTick );
    #ಆದರೆ_ಅಂತ್ಯ
}
