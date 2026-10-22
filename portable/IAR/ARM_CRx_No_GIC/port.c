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

/* Standard includes. */
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت
#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#جے_بنا_تعریف config_تیاری_TICK_رکاوٹ
    #غلطی config_تیاری_TICK_رکاوٹ() must be defined وچ FreeRTOSConfig.h منزل call the function that sets اتے the tick رکاوٹ.
#جے_انت

#جے_بنا_تعریف config_CLEAR_TICK_رکاوٹ
    #غلطی config_CLEAR_TICK_رکاوٹ must be defined وچ FreeRTOSConfig.h منزل clear which ever رکاوٹ was ورتیا منزل generate the tick رکاوٹ.
#جے_انت

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کرو پورٹ_NO_FLOATING_نقطہ_CONTEXT    ( ( ڈھیر_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کرو پورٹ_INITIAL_SPSR                 ( ( ڈھیر_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#تعریف_کرو پورٹ_THUMB_منوال_ثنائی_ہندسہ               ( ( ڈھیر_Type_t ) 0x20 )
#تعریف_کرو پورٹ_THUMB_منوال_پتہ           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کرو پورٹ_APSR_منوال_بٹ_نقاب          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#تعریف_کرو پورٹ_APSR_USER_منوال               ( 0x10 )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#جے_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#وإلا
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#جے_انت

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورٹ_Restore_Task_Context( فراغ );

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

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
متطاير uint32_t ul_پورٹ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
متطاير uint32_t ul_پورٹ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
متطاير uint32_t ul_پورٹ_رکاوٹ_Nesting = 0UL;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_کوڈ & پورٹ_THUMB_منوال_پتہ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_چوٹی_دا_ڈھیر |= پورٹ_THUMB_منوال_ثنائی_ہندسہ;
    }

    px_چوٹی_دا_ڈھیر--;

    /* Next the return address, which in this case is the start of the task. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;
    px_چوٹی_دا_ڈھیر--;

    /* Next all the registers other than the stack pointer. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* R14 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;              /* R12 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;              /* R11 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;              /* R10 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;              /* R9 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;              /* R8 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;              /* R7 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;              /* R6 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;              /* R5 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;              /* R4 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;              /* R3 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;              /* R2 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;              /* R1 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;            /* R0 */
    px_چوٹی_دا_ڈھیر--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_چوٹی_دا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;
    px_چوٹی_دا_ڈھیر--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_چوٹی_دا_ڈھیر = پورٹ_NO_FLOATING_نقطہ_CONTEXT;

    أرجع px_چوٹی_دا_ڈھیر;
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
    configASSERT( ul_پورٹ_رکاوٹ_Nesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm متطاير ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= پورٹ_APSR_منوال_بٹ_نقاب;
    configASSERT( ulAPSR != پورٹ_APSR_USER_منوال );

    إذا( ulAPSR != پورٹ_APSR_USER_منوال )
    {
        /* Start the timer that generates the tick ISR. */
        پورٹ_DISABLE_INTERRUPTS();
        config_تیاری_TICK_رکاوٹ();

        /* Start the first task executing. */
        v_پورٹ_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( فراغ ) prvTaskExitError;
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    پورٹ_DISABLE_INTERRUPTS();

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
        configASSERT( ul_پورٹ_رکاوٹ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٹ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    uint32_t ul_رکاوٹ_حالت;

    ul_رکاوٹ_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٹ_Yield_Required = pdTRUE;
    }

    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ul_رکاوٹ_حالت );

    config_CLEAR_TICK_رکاوٹ();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Task_ورتدا_FPU( فراغ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_پورٹ_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm متطاير ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/
