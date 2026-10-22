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

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

#اگر_غیر_تعریف_شدہ config_مداخلت_CONTROLLER_بنیاد_پتہ
    #غلطی "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#اگر_ختم

#اگر_غیر_تعریف_شدہ config_مداخلت_CONTROLLER_CPU_INTERFACE_انحراف
    #غلطی "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#اگر_ختم

#اگر_غیر_تعریف_شدہ config_UNIQUE_مداخلت_PRIORITIES
    #غلطی "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#اگر_ختم

#اگر_غیر_تعریف_شدہ config_تیاری_TICK_مداخلت
    #غلطی "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#اگر_ختم /* configSETUP_TICK_INTERRUPT */

#اگر_غیر_تعریف_شدہ config_MAX_API_CALL_مداخلت_ترجیح
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#اگر_ختم

#اگر config_MAX_API_CALL_مداخلت_ترجیح == 0
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#اگر_ختم

#اگر config_MAX_API_CALL_مداخلت_ترجیح > config_UNIQUE_مداخلت_PRIORITIES
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#اگر_ختم

#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #اگر_ختم
#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#اگر config_MAX_API_CALL_مداخلت_ترجیح <= ( config_UNIQUE_مداخلت_PRIORITIES / 2 )
    #غلطی "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#اگر_ختم

#اگر_غیر_تعریف_شدہ config_CLEAR_TICK_مداخلت
    #تعریف_کرو config_CLEAR_TICK_مداخلت()
#اگر_ختم

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#اگر config_UNIQUE_مداخلت_PRIORITIES == 16
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            4
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    3
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 32
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            3
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    2
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 64
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            2
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    1
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 128
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            1
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 256
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            0
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#ورنہ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #غلطی "Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the number of unique priorities implemented by the target hardware"
#اگر_ختم /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING                              ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کرو پورٹ_UNMASK_قدر                                     ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کرو پورٹ_NO_FLOATING_نقطہ_CONTEXT                        ( ( ڈھیر_Type_t ) 0 )

/* Interrupt controller access addresses. */
#تعریف_کرو پورٹ_ICCPMR_ترجیح_نقاب_انحراف                      ( 0x04 )
#تعریف_کرو پورٹ_ICCIAR_مداخلت_ACKNOWLEDGE_انحراف              ( 0x0C )
#تعریف_کرو پورٹ_ICCEOIR_انتہا_کا_مداخلت_انحراف                  ( 0x10 )
#تعریف_کرو پورٹ_ICCBPR_ثنائی_نقطہ_انحراف                       ( 0x08 )
#تعریف_کرو پورٹ_ICCRPR_RUNNING_ترجیح_انحراف                   ( 0x14 )
#تعریف_کرو پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ       ( config_مداخلت_CONTROLLER_بنیاد_پتہ + config_مداخلت_CONTROLLER_CPU_INTERFACE_انحراف )
#تعریف_کرو پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر                    ( *( ( متلون uint32_t * ) ( پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCPMR_ترجیح_نقاب_انحراف ) ) )
#تعریف_کرو پورٹ_ICCIAR_مداخلت_ACKNOWLEDGE_رجسٹر_پتہ    ( پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCIAR_مداخلت_ACKNOWLEDGE_انحراف )
#تعریف_کرو پورٹ_ICCEOIR_انتہا_کا_مداخلت_رجسٹر_پتہ        ( پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCEOIR_انتہا_کا_مداخلت_انحراف )
#تعریف_کرو پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر_پتہ            ( پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCPMR_ترجیح_نقاب_انحراف )
#تعریف_کرو پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر                     ( *( ( ثابت متلون uint32_t * ) ( پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCBPR_ثنائی_نقطہ_انحراف ) ) )
#تعریف_کرو پورٹ_ICCRPR_RUNNING_ترجیح_رجسٹر                 ( *( ( ثابت متلون uint32_t * ) ( پورٹ_مداخلت_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCRPR_RUNNING_ترجیح_انحراف ) ) )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#تعریف_کرو پورٹ_ثنائی_نقطہ_بٹ                                ( ( uint8_t ) 0x03 )

/* Constants required to setup the initial task context. */
#تعریف_کرو پورٹ_INITIAL_SPSR                                     ( ( ڈھیر_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کرو پورٹ_THUMB_منوال_ثنائی_ہندسہ                                   ( ( ڈھیر_Type_t ) 0x20 )
#تعریف_کرو پورٹ_THUMB_منوال_پتہ                               ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#تعریف_کرو پورٹ_APSR_منوال_بٹ_نقاب                              ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#تعریف_کرو پورٹ_APSR_USER_منوال                                   ( 0x10 )

/* Macro to unmask all interrupt priorities. */
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب()                            \
    {                                                         \
        __disable_irq();                                      \
        پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = پورٹ_UNMASK_قدر; \
        __asm( "DSB        \n"                                \
               "ISB        \n" );                             \
        __enable_irq();                                       \
    }

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجی خالی v_پورٹ_Restore_Task_Context( خالی );

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

/* Used to pass constants into the ASM code.  The address at which variables are
 * placed is the constant value so indirect loads in the asm code are not
 * required. */
uint32_t ulICCIAR __attribute__( ( at( پورٹ_ICCIAR_مداخلت_ACKNOWLEDGE_رجسٹر_پتہ ) ) );
uint32_t ulICCEOIR __attribute__( ( at( پورٹ_ICCEOIR_انتہا_کا_مداخلت_رجسٹر_پتہ ) ) );
uint32_t ulICCPMR __attribute__( ( at( پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر_پتہ ) ) );
uint32_t ul_Asm_APIPriority_نقاب __attribute__( ( at( config_MAX_API_CALL_مداخلت_ترجیح << پورٹ_ترجیح_سرکاؤ ) ) );

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
uint32_t ul_پورٹ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_پورٹ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_پورٹ_مداخلت_Nesting = 0UL;

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
    *px_چوٹی_کا_ڈھیر = تہی;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = تہی;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = تہی;
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
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) prvTaskExitError; /* R14 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;       /* R12 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;       /* R11 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;       /* R10 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;       /* R9 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;       /* R8 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;       /* R7 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;       /* R6 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;       /* R5 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;       /* R4 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;       /* R3 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;       /* R2 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;       /* R1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;     /* R0 */
    px_چوٹی_کا_ڈھیر--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_چوٹی_کا_ڈھیر = پورٹ_NO_CRITICAL_NESTING;
    px_چوٹی_کا_ڈھیر--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_چوٹی_کا_ڈھیر = پورٹ_NO_FLOATING_نقطہ_CONTEXT;

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
    __asm( "MRS ulAPSR, APSR" );
    ulAPSR &= پورٹ_APSR_منوال_بٹ_نقاب;
    configASSERT( ulAPSR != پورٹ_APSR_USER_منوال );

    اگر( ulAPSR != پورٹ_APSR_USER_منوال )
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر );

        اگر( ( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر & پورٹ_ثنائی_نقطہ_بٹ ) <= پورٹ_MAX_ثنائی_نقطہ_قدر )
        {
            /* Start the timer that generates the tick ISR. */
            config_تیاری_TICK_مداخلت();

            __enable_irq();
            v_پورٹ_Restore_Task_Context();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
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
    /* Disable interrupts as per portDISABLE_INTERRUPTS();  */
    ul_پورٹ_سیٹ_مداخلت_نقاب();

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
            پورٹ_CLEAR_مداخلت_نقاب();
        }
    }
}
/*-----------------------------------------------------------*/

خالی FreeRTOS_Tick_Handler( خالی )
{
    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value. */
    __disable_irq();
    پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجیح << پورٹ_ترجیح_سرکاؤ );
    __asm( "DSB        \n"
           "ISB        \n" );
    __enable_irq();

    /* Increment the RTOS tick. */
    اگر( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٹ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورٹ_CLEAR_مداخلت_نقاب();
    config_CLEAR_TICK_مداخلت();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Task_استعمال_کرتا_FPU( خالی )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_پورٹ_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, ulInitialFPSCR" );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Clear_مداخلت_نقاب( uint32_t ul_New_نقاب_قدر )
{
    اگر( ul_New_نقاب_قدر == pdFALSE )
    {
        پورٹ_CLEAR_مداخلت_نقاب();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٹ_سیٹ_مداخلت_نقاب( خالی )
{
    uint32_t ulReturn;

    __disable_irq();

    اگر( پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر == ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجیح << پورٹ_ترجیح_سرکاؤ ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    ورنہ
    {
        ulReturn = pdFALSE;
        پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر = ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجیح << پورٹ_ترجیح_سرکاؤ );
        __asm( "DSB        \n"
               "ISB        \n" );
    }

    __enable_irq();

    واپس ulReturn;
}
/*-----------------------------------------------------------*/

#اگر ( configASSERT_DEFINED == 1 )

    خالی v_پورٹ_Validate_مداخلت_ترجیح( خالی )
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
        configASSERT( پورٹ_ICCRPR_RUNNING_ترجیح_رجسٹر >= ( config_MAX_API_CALL_مداخلت_ترجیح << پورٹ_ترجیح_سرکاؤ ) );

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
        configASSERT( پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر <= پورٹ_MAX_ثنائی_نقطہ_قدر );
    }

#اگر_ختم /* configASSERT_DEFINED */
