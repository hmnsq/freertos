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
#अन्तर्भाव <stdlib.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#यदि_अपरिभाषितम् config_व्यवधानम्_CONTROLLER_आधारः_स्थानाङ्कः
    #दोषः "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#यदि_अन्तः

#यदि_अपरिभाषितम् config_व्यवधानम्_CONTROLLER_CPU_INTERFACE_विस्थापनम्
    #दोषः "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#यदि_अन्तः

#यदि_अपरिभाषितम् config_UNIQUE_व्यवधानम्_PRIORITIES
    #दोषः "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#यदि_अन्तः

#यदि_अपरिभाषितम् config_सज्जता_TICK_व्यवधानम्
    #दोषः "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#यदि_अन्तः /* configSETUP_TICK_INTERRUPT */

#यदि_अपरिभाषितम् config_MAX_API_CALL_व्यवधानम्_प्राथमिकता
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#यदि_अन्तः

#यदि config_MAX_API_CALL_व्यवधानम्_प्राथमिकता == 0
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#यदि_अन्तः

#यदि config_MAX_API_CALL_व्यवधानम्_प्राथमिकता > config_UNIQUE_व्यवधानम्_PRIORITIES
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#यदि_अन्तः

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #यदि_अन्तः
#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#यदि config_MAX_API_CALL_व्यवधानम्_प्राथमिकता <= ( config_UNIQUE_व्यवधानम्_PRIORITIES / 2 )
    #दोषः "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#यदि_अन्तः

#यदि_अपरिभाषितम् config_CLEAR_TICK_व्यवधानम्
    #परिभाषय config_CLEAR_TICK_व्यवधानम्()
#यदि_अन्तः

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 16
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            4
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    3
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 32
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            3
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    2
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 64
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            2
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    1
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 128
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            1
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    0
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 256
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            0
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    0
#अन्यथा /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #दोषः "Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the number of unique priorities implemented by the target hardware"
#यदि_अन्तः /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#परिभाषय पत्तनम्_NO_CRITICAL_NESTING                              ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#परिभाषय पत्तनम्_UNMASK_मानम्                                     ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#परिभाषय पत्तनम्_NO_FLOATING_POINT_CONTEXT                        ( ( राशिः_Type_t ) 0 )

/* Interrupt controller access addresses. */
#परिभाषय पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_विस्थापनम्                      ( 0x04 )
#परिभाषय पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_विस्थापनम्              ( 0x0C )
#परिभाषय पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_विस्थापनम्                  ( 0x10 )
#परिभाषय पत्तनम्_ICCBPR_द्विमान_POINT_विस्थापनम्                       ( 0x08 )
#परिभाषय पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_विस्थापनम्                   ( 0x14 )
#परिभाषय पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः       ( config_व्यवधानम्_CONTROLLER_आधारः_स्थानाङ्कः + config_व्यवधानम्_CONTROLLER_CPU_INTERFACE_विस्थापनम् )
#परिभाषय पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः                    ( *( ( चञ्चल uint32_t * ) ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_विस्थापनम् ) ) )
#परिभाषय पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_पञ्जिकाकोशः_स्थानाङ्कः    ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_विस्थापनम् )
#परिभाषय पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_पञ्जिकाकोशः_स्थानाङ्कः        ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_विस्थापनम् )
#परिभाषय पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः_स्थानाङ्कः            ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_विस्थापनम् )
#परिभाषय पत्तनम्_ICCBPR_द्विमान_POINT_पञ्जिकाकोशः                     ( *( ( ध्रुव चञ्चल uint32_t * ) ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCBPR_द्विमान_POINT_विस्थापनम् ) ) )
#परिभाषय पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_पञ्जिकाकोशः                 ( *( ( ध्रुव चञ्चल uint32_t * ) ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_विस्थापनम् ) ) )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#परिभाषय पत्तनम्_द्विमान_POINT_द्वयङ्काः                                ( ( uint8_t ) 0x03 )

/* Constants required to setup the initial task context. */
#परिभाषय पत्तनम्_INITIAL_SPSR                                     ( ( राशिः_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#परिभाषय पत्तनम्_THUMB_बहुलकम्_BIT                                   ( ( राशिः_Type_t ) 0x20 )
#परिभाषय पत्तनम्_THUMB_बहुलकम्_स्थानाङ्कः                               ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#परिभाषय पत्तनम्_APSR_बहुलकम्_द्वयङ्काः_आवरणम्                              ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#परिभाषय पत्तनम्_APSR_USER_बहुलकम्                                   ( 0x10 )

/* Macro to unmask all interrupt priorities. */
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्()                            \
    {                                                         \
        __disable_irq();                                      \
        पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः = पत्तनम्_UNMASK_मानम्; \
        __asm( "DSB        \n"                                \
               "ISB        \n" );                             \
        __enable_irq();                                       \
    }

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
बाह्य शून्य v_पत्तनम्_Restore_Task_Context( शून्य );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
चञ्चल uint32_t ulCriticalNesting = 9999UL;

/* Used to pass constants into the ASM code.  The address at which variables are
 * placed is the constant value so indirect loads in the asm code are not
 * required. */
uint32_t ulICCIAR __attribute__( ( at( पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_पञ्जिकाकोशः_स्थानाङ्कः ) ) );
uint32_t ulICCEOIR __attribute__( ( at( पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_पञ्जिकाकोशः_स्थानाङ्कः ) ) );
uint32_t ulICCPMR __attribute__( ( at( पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः_स्थानाङ्कः ) ) );
uint32_t ul_Asm_APIPriority_आवरणम् __attribute__( ( at( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) ) );

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
uint32_t ul_पत्तनम्_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_पत्तनम्_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_पत्तनम्_व्यवधानम्_Nesting = 0UL;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_शिखरम्_सम्बन्धि_राशिः = रिक्त;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = रिक्त;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = रिक्त;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_INITIAL_SPSR;

    यदि( ( ( uint32_t ) px_संहिता & पत्तनम्_THUMB_बहुलकम्_स्थानाङ्कः ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_शिखरम्_सम्बन्धि_राशिः |= पत्तनम्_THUMB_बहुलकम्_BIT;
    }

    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next the return address, which in this case is the start of the task. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next all the registers other than the stack pointer. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) prvTaskExitError; /* R14 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12121212;       /* R12 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11111111;       /* R11 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10101010;       /* R10 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09090909;       /* R9 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x08080808;       /* R8 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07070707;       /* R7 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06060606;       /* R6 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x05050505;       /* R5 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04040404;       /* R4 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03030303;       /* R3 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x02020202;       /* R2 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x01010101;       /* R1 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;     /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_CRITICAL_NESTING;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_FLOATING_POINT_CONTEXT;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_पत्तनम्_व्यवधानम्_Nesting == ~0UL );
    पत्तनम्_DISABLE_INTERRUPTS();

    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm( "MRS ulAPSR, APSR" );
    ulAPSR &= पत्तनम्_APSR_बहुलकम्_द्वयङ्काः_आवरणम्;
    configASSERT( ulAPSR != पत्तनम्_APSR_USER_बहुलकम् );

    यदि( ulAPSR != पत्तनम्_APSR_USER_बहुलकम् )
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( पत्तनम्_ICCBPR_द्विमान_POINT_पञ्जिकाकोशः & पत्तनम्_द्विमान_POINT_द्वयङ्काः ) <= पत्तनम्_MAX_द्विमान_POINT_मानम् );

        यदि( ( पत्तनम्_ICCBPR_द्विमान_POINT_पञ्जिकाकोशः & पत्तनम्_द्विमान_POINT_द्वयङ्काः ) <= पत्तनम्_MAX_द्विमान_POINT_मानम् )
        {
            /* Start the timer that generates the tick ISR. */
            config_सज्जता_TICK_व्यवधानम्();

            __enable_irq();
            v_पत्तनम्_Restore_Task_Context();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();  */
    ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    यदि( ulCriticalNesting == 1 )
    {
        configASSERT( ul_पत्तनम्_व्यवधानम्_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    यदि( ulCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            पत्तनम्_CLEAR_व्यवधानम्_आवरणम्();
        }
    }
}
/*-----------------------------------------------------------*/

शून्य FreeRTOS_Tick_Handler( शून्य )
{
    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value. */
    __disable_irq();
    पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः = ( uint32_t ) ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् );
    __asm( "DSB        \n"
           "ISB        \n" );
    __enable_irq();

    /* Increment the RTOS tick. */
    यदि( xTaskIncrementTick() != pdFALSE )
    {
        ul_पत्तनम्_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्();
    config_CLEAR_TICK_व्यवधानम्();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_पत्तनम्_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, ulInitialFPSCR" );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( uint32_t ul_New_आवरणम्_मानम् )
{
    यदि( ul_New_आवरणम्_मानम् == pdFALSE )
    {
        पत्तनम्_CLEAR_व्यवधानम्_आवरणम्();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य )
{
    uint32_t ulReturn;

    __disable_irq();

    यदि( पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः == ( uint32_t ) ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    अन्यथा
    {
        ulReturn = pdFALSE;
        पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः = ( uint32_t ) ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् );
        __asm( "DSB        \n"
               "ISB        \n" );
    }

    __enable_irq();

    प्रत्यागम ulReturn;
}
/*-----------------------------------------------------------*/

#यदि ( configASSERT_DEFINED == 1 )

    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य )
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
        configASSERT( पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_पञ्जिकाकोशः >= ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् ) );

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
        configASSERT( पत्तनम्_ICCBPR_द्विमान_POINT_पञ्जिकाकोशः <= पत्तनम्_MAX_द्विमान_POINT_मानम् );
    }

#यदि_अन्तः /* configASSERT_DEFINED */
