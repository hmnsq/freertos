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

/* IAR includes. */
#ضمن <intrinsics.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#که_نه_تعریف_شوی config_مداخله_CONTROLLER_بنسټ_پته
    #تېروتنه "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#که_نه_تعریف_شوی config_مداخله_CONTROLLER_CPU_INTERFACE_دننه_واټن
    #تېروتنه "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#که_نه_تعریف_شوی config_UNIQUE_مداخله_PRIORITIES
    #تېروتنه "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#که_نه_تعریف_شوی config_تیاری_TICK_مداخله
    #تېروتنه "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای /* configSETUP_TICK_INTERRUPT */

#که_نه_تعریف_شوی config_MAX_API_CALL_مداخله_لومړیتوب
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#د_که_پای

#إذا config_MAX_API_CALL_مداخله_لومړیتوب == 0
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#د_که_پای

#إذا config_MAX_API_CALL_مداخله_لومړیتوب > config_UNIQUE_مداخله_PRIORITIES
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #د_که_پای
#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_مداخله_لومړیتوب <= ( config_UNIQUE_مداخله_PRIORITIES / 2 )
    #تېروتنه "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#د_که_پای

#که_نه_تعریف_شوی config_CLEAR_TICK_مداخله
    #تعریف_کړه config_CLEAR_TICK_مداخله()
#د_که_پای

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کړه پورټ_UNMASK_ارزښت                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کړه پورټ_NO_FLOATING_ټکی_CONTEXT    ( ( ډېری_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#تعریف_کړه پورټ_INITIAL_SPSR                 ( ( ډېری_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کړه پورټ_THUMB_ډېرپېښ_بټ               ( ( ډېری_Type_t ) 0x20 )
#تعریف_کړه پورټ_THUMB_ډېرپېښ_پته           ( 0x01UL )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#تعریف_کړه پورټ_دوګونی_ټکی_بټونه            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کړه پورټ_APSR_ډېرپېښ_بټونه_ماسک          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#تعریف_کړه پورټ_APSR_USER_ډېرپېښ               ( 0x10 )

/* Macro to unmask all interrupt priorities. */
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک()                            \
    {                                                         \
        __disable_irq();                                      \
        پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی = پورټ_UNMASK_ارزښت; \
        __asm( "DSB        \n"                                \
               "ISB        \n" );                             \
        __enable_irq();                                       \
    }

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورټ_Restore_Task_Context( فراغ );

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
uint32_t ul_پورټ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_پورټ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_پورټ_مداخله_Nesting = 0UL;


/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_سر_د_ډېری = عدم;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = عدم;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = عدم;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_کوډ & پورټ_THUMB_ډېرپېښ_پته ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_سر_د_ډېری |= پورټ_THUMB_ډېرپېښ_بټ;
    }

    px_سر_د_ډېری--;

    /* Next the return address, which in this case is the start of the task. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;
    px_سر_د_ډېری--;

    /* Next all the registers other than the stack pointer. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) prvTaskExitError; /* R14 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12121212;       /* R12 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11111111;       /* R11 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10101010;       /* R10 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09090909;       /* R9 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x08080808;       /* R8 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07070707;       /* R7 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06060606;       /* R6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x05050505;       /* R5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04040404;       /* R4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03030303;       /* R3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x02020202;       /* R2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x01010101;       /* R1 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;     /* R0 */
    px_سر_د_ډېری--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;
    px_سر_د_ډېری--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_سر_د_ډېری = پورټ_NO_FLOATING_ټکی_CONTEXT;

    أرجع px_سر_د_ډېری;
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
    configASSERT( ul_پورټ_مداخله_Nesting == ~0UL );
    پورټ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm متطاير ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= پورټ_APSR_ډېرپېښ_بټونه_ماسک;
    configASSERT( ulAPSR != پورټ_APSR_USER_ډېرپېښ );

    إذا( ulAPSR != پورټ_APSR_USER_ډېرپېښ )
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی & پورټ_دوګونی_ټکی_بټونه ) <= پورټ_MAX_دوګونی_ټکی_ارزښت );

        إذا( ( پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی & پورټ_دوګونی_ټکی_بټونه ) <= پورټ_MAX_دوګونی_ټکی_ارزښت )
        {
            /* Start the timer that generates the tick ISR. */
            config_تیاری_TICK_مداخله();

            __enable_irq();
            v_پورټ_Restore_Task_Context();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();  */
    ul_پورټ_سېټ_مداخله_ماسک();

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
        configASSERT( ul_پورټ_مداخله_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورټ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورټ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            پورټ_CLEAR_مداخله_ماسک();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value. */
    __disable_irq();
    پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی = ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه );
    __asm( "DSB        \n"
           "ISB        \n" );
    __enable_irq();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورټ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورټ_CLEAR_مداخله_ماسک();
    config_CLEAR_TICK_مداخله();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Task_کاروي_FPU( فراغ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_پورټ_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک( uint32_t ul_New_ماسک_ارزښت )
{
    إذا( ul_New_ماسک_ارزښت == pdFALSE )
    {
        پورټ_CLEAR_مداخله_ماسک();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورټ_سېټ_مداخله_ماسک( فراغ )
{
    uint32_t ulReturn;

    __disable_irq();

    إذا( پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی == ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    وإلا
    {
        ulReturn = pdFALSE;
        پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی = ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه );
        __asm( "DSB        \n"
               "ISB        \n" );
    }

    __enable_irq();

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ )
    {
        /* The following assertion will fail if a service routine (ISR) for
         * an interrupt that has been assigned a priority above
         * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
         * function.  ISR safe FreeRTOS API functions must *only* be called
         * from interrupts that have been assigned a priority at or below
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * Numerically low interrupt priority numbers represent logically high
         * interrupt priorities, therefore the priority of the interrupt must
         * be set to a value equal to or numerically *higher* than
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * FreeRTOS maintains separate thread and ISR API functions to ensure
         * interrupt entry is as fast and simple as possible.
         *
         * The following links provide detailed information:
         * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
         * https://www.freertos.org/Why-FreeRTOS/FAQs */
        configASSERT( پورټ_ICCRPR_RUNNING_لومړیتوب_ثبتوونکی >= ( uint32_t ) ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه ) );

        /* Priority grouping:  The interrupt controller (GIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * The priority grouping is configured by the GIC's binary point register
         * (ICCBPR).  Writing 0 to ICCBPR will ensure it is set to its lowest
         * possible value (which may be above 0). */
        configASSERT( ( پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی & پورټ_دوګونی_ټکی_بټونه ) <= پورټ_MAX_دوګونی_ټکی_ارزښت );
    }

#د_که_پای /* configASSERT_DEFINED */
