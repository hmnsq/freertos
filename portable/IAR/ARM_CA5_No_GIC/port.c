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
#ضمن <intrinsics.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 difference priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#جيڪڏهن_وصف_نه_ٿيل config_تياري_TICK_مداخلت
    #غلطي config_تياري_TICK_مداخلت() must be defined اندريون FreeRTOSConfig.h منزل call the function that sets مٿي the tick مداخلت.  A افتراضي that استعمال_ڪري the PIT is provided اندريون the official demo application.
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_CLEAR_TICK_مداخلت
    #غلطي config_CLEAR_TICK_مداخلت must be defined اندريون FreeRTOSConfig.h منزل clear which ever مداخلت was استعمال_ٿيل منزل generate the tick مداخلت.  A افتراضي that استعمال_ڪري the PIT is provided اندريون the official demo application.
#جيڪڏهن_پورو

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#وصف_ڪريو پورٽ_NO_FLOATING_نقطو_CONTEXT    ( ( ڍير_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#وصف_ڪريو پورٽ_INITIAL_SPSR                 ( ( ڍير_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#وصف_ڪريو پورٽ_THUMB_گهڻائي_ٻٽو_انگ               ( ( ڍير_Type_t ) 0x20 )
#وصف_ڪريو پورٽ_THUMB_گهڻائي_پتو           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#وصف_ڪريو پورٽ_APSR_گهڻائي_بٽ_نقاب          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#وصف_ڪريو پورٽ_APSR_USER_گهڻائي               ( 0x10 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورٽ_Restore_Task_Context( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
متطاير uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero
 * then a floating point context must be saved and restored for the task. */
uint32_t ul_پورٽ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_پورٽ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_پورٽ_مداخلت_Nesting = 0UL;


/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_چوٽي_جو_ڍير = عدم;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = عدم;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = عدم;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_ڪوڊ & پورٽ_THUMB_گهڻائي_پتو ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_چوٽي_جو_ڍير |= پورٽ_THUMB_گهڻائي_ٻٽو_انگ;
    }

    px_چوٽي_جو_ڍير--;

    /* Next the return address, which in this case is the start of the task. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;
    px_چوٽي_جو_ڍير--;

    /* Next all the registers other than the stack pointer. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) prvTaskExitError; /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12121212;       /* R12 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11111111;       /* R11 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10101010;       /* R10 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09090909;       /* R9 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08080808;       /* R8 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07070707;       /* R7 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06060606;       /* R6 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x05050505;       /* R5 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04040404;       /* R4 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03030303;       /* R3 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x02020202;       /* R2 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x01010101;       /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;     /* R0 */
    px_چوٽي_جو_ڍير--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_NESTING;
    px_چوٽي_جو_ڍير--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_چوٽي_جو_ڍير = پورٽ_NO_FLOATING_نقطو_CONTEXT;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_پورٽ_مداخلت_Nesting == ~0UL );
    پورٽ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm متطاير ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= پورٽ_APSR_گهڻائي_بٽ_نقاب;
    configASSERT( ulAPSR != پورٽ_APSR_USER_گهڻائي );

    إذا( ulAPSR != پورٽ_APSR_USER_گهڻائي )
    {
        /* Start the timer that generates the tick ISR. */
        config_تياري_TICK_مداخلت();
        v_پورٽ_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    إذا( ulCriticalNesting == 1 )
    {
        configASSERT( ul_پورٽ_مداخلت_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٽ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٽ_Yield_Required = pdTRUE;
    }

    پورٽ_ENABLE_INTERRUPTS();
    config_CLEAR_TICK_مداخلت();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_پورٽ_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/
