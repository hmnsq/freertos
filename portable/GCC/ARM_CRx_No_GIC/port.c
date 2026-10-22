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
#شامل <stdlib.h>
#شامل <string.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires مزید than 10 مقصد 15 difference priorities as tasks that share a ترجیح will time قاش.
    #اگر_ختم
#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#اگر_غیر_تعریف_شدہ config_تیاری_TICK_مداخلت
    #غلطی config_تیاری_TICK_مداخلت() must be defined اندر FreeRTOSConfig.h مقصد call the function that sets اوپر the tick مداخلت.
#اگر_ختم

#اگر_غیر_تعریف_شدہ config_CLEAR_TICK_مداخلت
    #غلطی config_CLEAR_TICK_مداخلت must be defined اندر FreeRTOSConfig.h مقصد clear which ever مداخلت was مستعمل مقصد generate the tick مداخلت.
#اگر_ختم

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
#اگر_تعریف_شدہ __ARMEB__
    #تعریف_کرو پورٹ_INITIAL_SPSR             ( ( ڈھیر_Type_t ) 0x21f ) /* System mode, ARM mode, IRQ enabled FIQ enabled, Big-endian. */
#ورنہ
    #تعریف_کرو پورٹ_INITIAL_SPSR             ( ( ڈھیر_Type_t ) 0x01f ) /* System mode, ARM mode, IRQ enabled FIQ enabled, Little-endian. */
#اگر_ختم
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
#اگر_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#ورنہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#اگر_ختم

/* The space on the stack required to hold the FPU registers. */
#اگر ( configFPU_D32 == 1 )
    #تعریف_کرو پورٹ_FPU_رجسٹر_الفاظ     ( ( 32 * 2 ) + 1 ) /* D0-D31 and FPSCR. */
#ورنہ
    #تعریف_کرو پورٹ_FPU_رجسٹر_الفاظ     ( ( 16 * 2 ) + 1 ) /* D0-D15 and FPSCR. */
#اگر_ختم /* configFPU_D32 */

/*-----------------------------------------------------------*/

/*
 * These functions are necessarily written in assembly code, so are implemented
 * in portASM.S.
 */
خارجی خالی v_پورٹ_Restore_Task_Context( خالی );
خارجی خالی v_پورٹ_Initialise_FPSCR( خالی );
خارجی uint32_t ulReadAPSR( خالی );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
متلون uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
متلون uint32_t ul_پورٹ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
متلون uint32_t ul_پورٹ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
متلون uint32_t ul_پورٹ_مداخلت_Nesting = 0UL;

/* Used in the asm file to clear an interrupt. */
__attribute__( ( مستعمل ) ) ثابت uint32_t ulICCEOIR = config_EOI_پتہ;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) تہی;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) تہی;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) تہی;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_INITIAL_SPSR;

    اگر( ( ( uint32_t ) px_رمز & پورٹ_THUMB_منوال_پتہ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_چوٹی_کا_ڈھیر |= پورٹ_THUMB_منوال_ثنائی_ہندسہ;
    }

    px_چوٹی_کا_ڈھیر--;

    /* Next the return address, which in this case is the start of the task. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;
    px_چوٹی_کا_ڈھیر--;

    /* Next all the registers other than the stack pointer. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* R14 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;              /* R12 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;              /* R11 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;              /* R10 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;              /* R9 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;              /* R8 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;              /* R7 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;              /* R6 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;              /* R5 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;              /* R4 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;              /* R3 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;              /* R2 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;              /* R1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;            /* R0 */
    px_چوٹی_کا_ڈھیر--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_چوٹی_کا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;

    #اگر ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start without a floating point context.  A task that uses
         * the floating point hardware must call vPortTaskUsesFPU() before executing
         * any floating point instructions. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = پورٹ_NO_FLOATING_نقطہ_CONTEXT;
    }
    #وگرنہ_اگر ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_چوٹی_کا_ڈھیر -= پورٹ_FPU_رجسٹر_الفاظ;
        memset( px_چوٹی_کا_ڈھیر, 0x00, پورٹ_FPU_رجسٹر_الفاظ * حجم( ڈھیر_Type_t ) );

        /* Initialise the slot containing ulPortTaskHasFPUContext to true as
         * the task starts with a floating point context. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = pdTRUE;
        ul_پورٹ_Task_Has_FPUContext = pdTRUE;
    }
    #ورنہ
    {
        #غلطی "Invalid configUSE_TASK_FPU_SUPPORT value - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #اگر_ختم /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساکن خالی prvTaskExitError( خالی )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_پورٹ_مداخلت_Nesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    برائے( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    ulAPSR = ulReadAPSR();

    ulAPSR &= پورٹ_APSR_منوال_بٹ_نقاب;
    configASSERT( ulAPSR != پورٹ_APSR_USER_منوال );

    اگر( ulAPSR != پورٹ_APSR_USER_منوال )
    {
        /* Start the timer that generates the tick ISR. */
        پورٹ_DISABLE_INTERRUPTS();
        config_تیاری_TICK_مداخلت();

        /* Start the first task executing. */
        v_پورٹ_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( خالی ) prvTaskExitError;
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
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
    اگر( ulCriticalNesting == 1 )
    {
        configASSERT( ul_پورٹ_مداخلت_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    اگر( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورٹ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

خالی FreeRTOS_Tick_Handler( خالی )
{
    uint32_t ul_مداخلت_حالت;

    ul_مداخلت_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

    /* Increment the RTOS tick. */
    اگر( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٹ_Yield_Required = pdTRUE;
    }

    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_مداخلت_حالت );

    config_CLEAR_TICK_مداخلت();
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_TASK_FPU_SUPPORT != 2 )

    خالی v_پورٹ_Task_استعمال_کرتا_FPU( خالی )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ul_پورٹ_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_پورٹ_Initialise_FPSCR();
    }

#اگر_ختم /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/
