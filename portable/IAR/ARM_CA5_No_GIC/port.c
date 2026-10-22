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

/* IAR includes. */
#ಅನ್ತರ್ಭಾವ <intrinsics.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 difference priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ
    #ದೋಷ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ() must be defined ಒಳ FreeRTOSConfig.h ಗಮ್ಯ call the function that sets ಮೇಲೆ the tick ಅಡಚಣೆ.  A ಪೂರ್ವನಿಯೋಜಿತ that ಬಳಸುತ್ತದೆ the PIT is provided ಒಳ the official demo application.
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_CLEAR_TICK_ಅಡಚಣೆ
    #ದೋಷ config_CLEAR_TICK_ಅಡಚಣೆ must be defined ಒಳ FreeRTOSConfig.h ಗಮ್ಯ clear which ever ಅಡಚಣೆ was ಬಳಸಿದ ಗಮ್ಯ generate the tick ಅಡಚಣೆ.  A ಪೂರ್ವನಿಯೋಜಿತ that ಬಳಸುತ್ತದೆ the PIT is provided ಒಳ the official demo application.
#ಆದರೆ_ಅಂತ್ಯ

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT    ( ( ರಾಶಿ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR                 ( ( ರಾಶಿ_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್               ( ( ರಾಶಿ_Type_t ) 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ               ( 0x10 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Restore_Task_Context( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero
 * then a floating point context must be saved and restored for the task. */
uint32_t ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_ಪೋರ್ಟ್_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting = 0UL;


/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_INITIAL_SPSR;

    ಆದರೆ( ( ( uint32_t ) px_ಸಂಕೇತ & ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Next the return address, which in this case is the start of the task. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Next all the registers other than the stack pointer. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) prvTaskExitError; /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212;       /* R12 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;       /* R11 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010;       /* R10 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909;       /* R9 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808;       /* R8 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707;       /* R7 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606;       /* R6 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505;       /* R5 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404;       /* R4 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303;       /* R3 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202;       /* R2 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101;       /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;     /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm ಅಸ್ಥಿರ ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ;
    configASSERT( ulAPSR != ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ );

    ಆದರೆ( ulAPSR != ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ )
    {
        /* Start the timer that generates the tick ISR. */
        config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();
        v_ಪೋರ್ಟ್_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ಆದರೆ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        ul_ಪೋರ್ಟ್_Yield_Required = pdTRUE;
    }

    ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
    config_CLEAR_TICK_ಅಡಚಣೆ();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/
