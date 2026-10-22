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

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر
#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#اگر_تعریف_نشده config_راهاندازی_TICK_وقفه
    #خطا config_راهاندازی_TICK_وقفه() must be defined درون FreeRTOSConfig.h مقصد call the function that sets به_بالا the tick وقفه.  A افتراضي that استفاده_میکند the PIT is provided درون the official demo application.
#پایان_اگر

#اگر_تعریف_نشده config_CLEAR_TICK_وقفه
    #خطا config_CLEAR_TICK_وقفه must be defined درون FreeRTOSConfig.h مقصد clear which ever وقفه was استفاده_شده مقصد generate the tick وقفه.  A افتراضي that استفاده_میکند the PIT is provided درون the official demo application.
#پایان_اگر

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کن پورت_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کن پورت_NO_FLOATING_نقطه_CONTEXT    ( ( پشته_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کن پورت_INITIAL_SPSR                 ( ( پشته_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کن پورت_THUMB_نما_بیت               ( ( پشته_Type_t ) 0x20 )
#تعریف_کن پورت_THUMB_نما_آدرس           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کن پورت_APSR_نما_بیتها_ماسک          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#تعریف_کن پورت_APSR_USER_نما               ( 0x10 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورت_Restore_Task_Context( فراغ );

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
uint32_t ul_پورت_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_پورت_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_پورت_وقفه_Nesting = 0UL;


/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_بالاترین_از_پشته = عدم;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = عدم;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = عدم;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_کد & پورت_THUMB_نما_آدرس ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_بالاترین_از_پشته |= پورت_THUMB_نما_بیت;
    }

    px_بالاترین_از_پشته--;

    /* Next the return address, which in this case is the start of the task. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;
    px_بالاترین_از_پشته--;

    /* Next all the registers other than the stack pointer. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) prvTaskExitError; /* R14 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12121212;       /* R12 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11111111;       /* R11 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10101010;       /* R10 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09090909;       /* R9 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08080808;       /* R8 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07070707;       /* R7 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06060606;       /* R6 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x05050505;       /* R5 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04040404;       /* R4 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03030303;       /* R3 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x02020202;       /* R2 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x01010101;       /* R1 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;     /* R0 */
    px_بالاترین_از_پشته--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_بالاترین_از_پشته = پورت_NO_CRITICAL_NESTING;
    px_بالاترین_از_پشته--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_بالاترین_از_پشته = پورت_NO_FLOATING_نقطه_CONTEXT;

    أرجع px_بالاترین_از_پشته;
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
    configASSERT( ul_پورت_وقفه_Nesting == ~0UL );
    پورت_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm متطاير ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= پورت_APSR_نما_بیتها_ماسک;
    configASSERT( ulAPSR != پورت_APSR_USER_نما );

    إذا( ulAPSR != پورت_APSR_USER_نما )
    {
        /* Start the timer that generates the tick ISR. */
        config_راهاندازی_TICK_وقفه();
        v_پورت_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    پورت_DISABLE_INTERRUPTS();

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
        configASSERT( ul_پورت_وقفه_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورت_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورت_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورت_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    پورت_DISABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورت_Yield_Required = pdTRUE;
    }

    پورت_ENABLE_INTERRUPTS();
    config_CLEAR_TICK_وقفه();
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_پورت_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/
