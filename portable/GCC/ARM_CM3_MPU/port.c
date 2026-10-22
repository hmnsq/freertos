/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
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
* Implementation of functions defined in portable.h for the ARM CM3 MPU port.
*----------------------------------------------------------*/

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#यदि_अपरिभाषितम् configSYSTICK_CLOCK_HZ
    #परिभाषय configSYSTICK_CLOCK_HZ    configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK      ( 1UL << 2UL )
#अन्यथा

/* The way the SysTick is clocked is not modified in case it is not the same
 * as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK    ( 0 )
#यदि_अन्तः

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#यदि_अपरिभाषितम् configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #परिभाषय configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #अन्यथा
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #परिभाषय configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #यदि_अन्तः
#अन्यथा
    #यदि ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #दोषः configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers संस्करणम् 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #यदि_अन्तः
#यदि_अन्तः

/* Prototype of all Interrupt Service Routines (ISRs). */
प्रकारनिर्देश शून्य ( * पत्तनम्_ISR_t )( शून्य );

/* Constants required to access and manipulate the NVIC. */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CTRL_REG                 ( *( ( चञ्चल uint32_t * ) 0xe000e010 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_आरोपय_REG                 ( *( ( चञ्चल uint32_t * ) 0xe000e014 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG        ( *( ( चञ्चल uint32_t * ) 0xe000e018 ) )
#परिभाषय पत्तनम्_NVIC_SHPR3_REG                        ( *( ( चञ्चल uint32_t * ) 0xe000ed20 ) )
#परिभाषय पत्तनम्_NVIC_SHPR2_REG                        ( *( ( चञ्चल uint32_t * ) 0xe000ed1c ) )
#परिभाषय पत्तनम्_NVIC_SYS_CTRL_STATE_REG               ( *( ( चञ्चल uint32_t * ) 0xe000ed24 ) )
#परिभाषय पत्तनम्_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants required to access and manipulate the MPU. */
#परिभाषय पत्तनम्_MPU_TYPE_REG                          ( *( ( चञ्चल uint32_t * ) 0xe000ed90 ) )
#परिभाषय पत्तनम्_MPU_REGION_आधारः_स्थानाङ्कः_REG           ( *( ( चञ्चल uint32_t * ) 0xe000ed9C ) )
#परिभाषय पत्तनम्_MPU_REGION_ATTRIBUTE_REG              ( *( ( चञ्चल uint32_t * ) 0xe000edA0 ) )
#परिभाषय पत्तनम्_MPU_CTRL_REG                          ( *( ( चञ्चल uint32_t * ) 0xe000ed94 ) )
#परिभाषय पत्तनम्_EXPECTED_MPU_TYPE_मानम्               ( 8UL << 8UL ) /* 8 regions, unified. */
#परिभाषय पत्तनम्_MPU_ENABLE                            ( 0x01UL )
#परिभाषय पत्तनम्_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#परिभाषय पत्तनम्_PRIVILEGED_EXECUTION_START_स्थानाङ्कः    ( 0UL )
#परिभाषय पत्तनम्_MPU_REGION_VALID                      ( 0x10UL )
#परिभाषय पत्तनम्_MPU_REGION_ENABLE                     ( 0x01UL )
#परिभाषय पत्तनम्_PERIPHERALS_START_स्थानाङ्कः             0x40000000UL
#परिभाषय पत्तनम्_PERIPHERALS_अन्तः_स्थानाङ्कः               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#परिभाषय पत्तनम्_NVIC_SYSTICK_INT                      ( 0x00000002UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता                ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) पत्तनम्_MIN_व्यवधानम्_प्राथमिकता ) << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) पत्तनम्_MIN_व्यवधानम्_प्राथमिकता ) << 24UL )
#परिभाषय पत्तनम्_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता - 1UL ) << 24UL )

/* Constants required to set up the initial stack. */
#परिभाषय पत्तनम्_INITIAL_XPSR                          ( 0x01000000 )
#परिभाषय पत्तनम्_INITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#परिभाषय पत्तनम्_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#परिभाषय पत्तनम्_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#परिभाषय पत्तनम्_SCB_VTOR_REG                          ( *( ( पत्तनम्_ISR_t ** ) 0xE000ED08 ) )
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_SVC                      ( 11 )
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#परिभाषय पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या           ( 16 )
#परिभाषय पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16           ( 0xE000E3F0 )
#परिभाषय पत्तनम्_AIRCR_REG                             ( *( ( चञ्चल uint32_t * ) 0xE000ED0C ) )
#परिभाषय पत्तनम्_MAX_8_BIT_मानम्                       ( ( uint8_t ) 0xff )
#परिभाषय पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE                       ( ( uint8_t ) 0x80 )
#परिभाषय पत्तनम्_MAX_PRIGROUP_द्वयङ्काः                     ( ( uint8_t ) 7 )
#परिभाषय पत्तनम्_प्राथमिकता_गणः_आवरणम्                   ( 0x07UL << 8UL )
#परिभाषय पत्तनम्_PRIGROUP_सरणम्                        ( 8UL )

/* Constants used during system call enter and exit. */
#परिभाषय पत्तनम्_PSR_राशिः_PADDING_आवरणम्                ( 1UL << 9UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_LR                          ( 5 )
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PC                          ( 6 )
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR                         ( 7 )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#परिभाषय पत्तनम्_START_स्थानाङ्कः_आवरणम्                    ( ( राशिः_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#परिभाषय पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( addr, start, अन्तः_2 ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( अन्तः_2 ) ) )

/* Is the access request satisfied by the available permissions? */
#परिभाषय पत्तनम्_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#परिभाषय पत्तनम्_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( a, b )    ( ( a ) > ( पत्तनम्_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
स्थिर शून्य prv_सज्जता_MPU( शून्य ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
स्थिर uint32_t prv_Get_MPURegion_आकार_Setting( uint32_t ul_Actual_आकार_अन्तर्_अष्टकानि ) PRIVILEGED_FUNCTION;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * Standard FreeRTOS exception handlers.
 */
शून्य x_पत्तनम्_Pend_SVHandler( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;
शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य )  __attribute__( ( optimize( "3" ) ) ) PRIVILEGED_FUNCTION;
शून्य v_पत्तनम्_SVCHandler( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
स्थिर शून्य prv_Restore_Context_सम्बन्धि_First_Task( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
शून्य vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( noinline ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
आधारः_Type_t xIsPrivileged( शून्य ) __attribute__( ( naked ) );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
शून्य vResetPrivilege( शून्य ) __attribute__( ( naked ) );

/**
 * @brief Make a task unprivileged.
 */
शून्य v_पत्तनम्_Switch_गन्तव्यम्_User_बहुलकम्( शून्य );

/**
 * @brief Enter critical section.
 */
#यदि ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    शून्य v_पत्तनम्_Enter_Critical( शून्य ) FREERTOS_SYSTEM_CALL;
#अन्यथा
    शून्य v_पत्तनम्_Enter_Critical( शून्य ) PRIVILEGED_FUNCTION;
#यदि_अन्तः

/**
 * @brief Exit from critical section.
 */
#यदि ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    शून्य v_पत्तनम्_Exit_Critical( शून्य ) FREERTOS_SYSTEM_CALL;
#अन्यथा
    शून्य v_पत्तनम्_Exit_Critical( शून्य ) PRIVILEGED_FUNCTION;
#यदि_अन्तः

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    शून्य vSystemCallEnter( uint32_t * pul_Task_राशिः,
                           uint8_t uc_System_Call_सङ्ख्या ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    शून्य vRequestSystemCallExit( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 */
    शून्य vSystemCallExit( uint32_t * pul_System_Call_राशिः ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
स्थिर UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_दत्त स्थिर आधारः_Type_t xSchedulerRunning = pdFALSE;

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#यदि ( configASSERT_DEFINED == 1 )
    स्थिर uint8_t uc_Max_Sys_Call_प्राथमिकता = 0;
    स्थिर uint32_t ulMaxPRIGROUPValue = 0;
    स्थिर ध्रुव चञ्चल uint8_t * ध्रुव pc_व्यवधानम्_प्राथमिकता_Registers = ( ध्रुव चञ्चल uint8_t * ध्रुव ) पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16;
#यदि_अन्तः /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters,
                                     आधारः_Type_t x_सततम्_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    यदि( x_सततम्_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= पत्तनम्_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = पत्तनम्_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    अन्यथा
    {
        xMPUSettings->ulTaskFlags &= ( ~( पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = पत्तनम्_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = पत्तनम्_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_शिखरम्_सम्बन्धि_राशिः - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_संहिता ) & पत्तनम्_START_स्थानाङ्कः_आवरणम्; /* PC. */
    xMPUSettings->ulContext[ 18 ] = पत्तनम्_INITIAL_XPSR;                                 /* xPSR. */

    #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः = &( xMPUSettings->x_System_Call_राशिः_Info.ul_System_Call_राशिः_बफर[ config_SYSTEM_CALL_राशिः_आकार - 1 ] );
        xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः ) &
                                                                                 ( uint32_t ) ( ~( पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = रिक्त;
    }
    #यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    प्रत्यागम &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    शून्य v_पत्तनम्_SVCHandler( शून्य ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm चञ्चल
        (
            ".syntax unified                \n"
            ".extern vSVCHandler_C          \n"
            ".extern vSystemCallEnter       \n"
            ".extern vSystemCallExit        \n"
            "                               \n"
            "tst lr, #4                     \n"
            "ite eq                         \n"
            "mrseq r0, msp                  \n"
            "mrsne r0, psp                  \n"
            "                               \n"
            "ldr r2, [r0, #24]              \n"
            "ldrb r1, [r2, #-2]             \n"
            "cmp r1, %0                     \n"
            "blt vSystemCallEnter           \n"
            "cmp r1, %1                     \n"
            "beq vSystemCallExit            \n"
            "b vSVCHandler_C                \n"
            "                               \n"
            : /* No outputs. */
            : "i" ( अङ्कः_SYSTEM_CALLS ), "i" ( पत्तनम्_SVC_SYSTEM_CALL_EXIT )
            : "r0", "r1", "r2", "memory"
        );
    }

#अन्यथा /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    शून्य v_पत्तनम्_SVCHandler( शून्य ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        /* Assumes psp was in use. */
        __asm चञ्चल
        (
            #यदि_अपरिभाषितम् USE_PROCESS_राशिः /* Code should not be required if a main() is using the process stack. */
                "   tst lr, #4                      \n"
                "   ite eq                          \n"
                "   mrseq r0, msp                   \n"
                "   mrsne r0, psp                   \n"
            #अन्यथा
                "   mrs r0, psp                     \n"
            #यदि_अन्तः
            "   b %0                            \n"
            ::"i" ( vSVCHandler_C ) : "r0", "memory"
        );
    }

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

शून्य vSVCHandler_C( uint32_t * pulParam ) /* PRIVILEGED_FUNCTION */
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #यदि ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */
    #यदि_अन्तः /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR.  The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    विकल्प( ucSVCNumber )
    {
        पक्ष पत्तनम्_SVC_START_SCHEDULER:
            prv_Restore_Context_सम्बन्धि_First_Task();
            भङ्ग;

        पक्ष पत्तनम्_SVC_YIELD:
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm चञ्चल ( "dsb" ::: "memory" );
            __asm चञ्चल ( "isb" );

            भङ्ग;

    #यदि ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #यदि ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            पक्ष पत्तनम्_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                यदि( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm चञ्चल
                    (
                        "   mrs r1, control     \n" /* Obtain current control value. */
                        "   bic r1, #1          \n" /* Set privilege bit. */
                        "   msr control, r1     \n" /* Write back new control value. */
                        ::: "r1", "memory"
                    );
                }

                भङ्ग;
        #अन्यथा /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            पक्ष पत्तनम्_SVC_RAISE_PRIVILEGE:
                __asm चञ्चल
                (
                    "   mrs r1, control     \n" /* Obtain current control value. */
                    "   bic r1, #1          \n" /* Set privilege bit. */
                    "   msr control, r1     \n" /* Write back new control value. */
                    ::: "r1", "memory"
                );
                भङ्ग;
        #यदि_अन्तः /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        स्वभाव: /* Unknown SVC call. */
            भङ्ग;
    }
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    शून्य vSystemCallEnter( uint32_t * pul_Task_राशिः,
                           uint8_t uc_System_Call_सङ्ख्या ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        बाह्य UBaseType_t uxSystemCallImplementations[ अङ्कः_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_राशिः;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ध्रुव uint32_t ul_Hardware_Saved_Exception_Frame_आकार = 8;

        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must be NULL as
         *    it is non-NULL only during the execution of a system call (i.e.
         *    between system call enter and exit).
         * 3. System call is not for a kernel API disabled by the configuration
         *    in FreeRTOSConfig.h.
         * 4. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        यदि( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः == रिक्त ) &&
            ( uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_राशिः = pxMpuSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_राशिः = pul_System_Call_राशिः - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            प्रति( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_System_Call_राशिः[ i ] = pul_Task_राशिः[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm चञ्चल ( "msr psp, %0" : : "r" ( pul_System_Call_राशिः ) );

            /* Raise the privilege for the duration of the system call. */
            __asm चञ्चल (
                " mrs r1, control     \n" /* Obtain current control value. */
                " bic r1, #1          \n" /* Clear nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = pul_Task_राशिः + ul_Hardware_Saved_Exception_Frame_आकार;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः = pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ] = uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            यदि( ( pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] & पत्तनम्_PSR_राशिः_PADDING_आवरणम् ) == पत्तनम्_PSR_राशिः_PADDING_आवरणम् )
            {
                pxMpuSettings->ulTaskFlags |= पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG;
            }
            अन्यथा
            {
                pxMpuSettings->ulTaskFlags &= ( ~पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] &= ( ~पत्तनम्_PSR_राशिः_PADDING_आवरणम् );
        }
    }

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    शून्य vRequestSystemCallExit( शून्य ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm चञ्चल ( "svc %0 \n" ::"i" ( पत्तनम्_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    शून्य vSystemCallExit( uint32_t * pul_System_Call_राशिः ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_राशिः;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ध्रुव uint32_t ul_Hardware_Saved_Exception_Frame_आकार = 8;

        #यदि defined( __ARMCC_VERSION )
            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;
        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];
        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the privileged code (i.e. application is not
         *    raising SVC directly). This SVC is only raised from
         *    vRequestSystemCallExit which is in the privileged code section.
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must not be NULL -
         *    this means that we previously entered a system call and the
         *    application is not attempting to exit without entering a system
         *    call.
         */
        यदि( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः != रिक्त ) )
        {
            pul_Task_राशिः = pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः;

            /* Make space on the task stack for the stack frame. */
            pul_Task_राशिः = pul_Task_राशिः - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            प्रति( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_Task_राशिः[ i ] = pul_System_Call_राशिः[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm चञ्चल ( "msr psp, %0" : : "r" ( pul_Task_राशिः ) );

            /* Drop the privilege before returning to the thread mode. */
            __asm चञ्चल (
                " mrs r1, control     \n" /* Obtain current control value. */
                " orr r1, #1          \n" /* Set nPRIV bit. */
                " msr control, r1     \n" /* Write back new control value. */
                ::: "r1", "memory"
                );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ] = pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
            /* Ensure that LR has a valid value.*/
            pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ] = pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            यदि( ( pxMpuSettings->ulTaskFlags & पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG ) == पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] |= पत्तनम्_PSR_राशिः_PADDING_आवरणम्;
            }
            अन्यथा
            {
                pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] &= ( ~पत्तनम्_PSR_राशिः_PADDING_आवरणम् );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = रिक्त;
        }
    }

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) /* PRIVILEGED_FUNCTION */
{
    आधारः_Type_t xTaskIsPrivileged = pdFALSE;
    ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

    यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    प्रत्यागम xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Restore_Context_सम्बन्धि_First_Task( शून्य )
{
    __asm चञ्चल
    (
        " ldr r0, =0xE000ED08                   \n" /* Use the NVIC offset register to locate the stack. */
        " ldr r0, [r0]                          \n"
        " ldr r0, [r0]                          \n"
        " msr msp, r0                           \n" /* Set the msp back to the start of the stack. */
        "                                       \n"
        /*------------ Program MPU. ------------ */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " add r2, r2, #4                        \n" /* r2 = Second item in the TCB which is xMPUSettings. */
        "                                       \n"
        " dmb                                   \n" /* Complete outstanding transfers before disabling MPU. */
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " bic r3, #1                            \n" /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Disable MPU. */
        "                                       \n"
        " ldr r0, =0xe000ed9c                   \n" /* Region Base Address register. */
        " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
        " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */
        "                                       \n"
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " orr r3, #1                            \n" /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Enable MPU. */
        " dsb                                   \n" /* Force memory writes before continuing. */
        "                                       \n"
        /*---------- Restore Context. ---------- */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " ldr r1, [r2]                          \n" /* r1 = Location of saved context in TCB. */
        "                                       \n"
        " ldmdb r1!, {r0, r4-r11}               \n" /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
        " msr psp, r0                           \n"
        " stmia r0, {r4-r11}                    \n" /* Copy the hardware saved context on the task stack. */
        " ldmdb r1!, {r3-r11, lr}               \n" /* r3 contains CONTROL register. r4-r11 and LR restored. */
        " msr control, r3                       \n"
        " str r1, [r2]                          \n" /* Save the location where the context should be saved next as the first member of TCB. */
        "                                       \n"
        " mov r0, #0                            \n"
        " msr basepri, r0                       \n"
        " bx lr                                 \n"
        "                                       \n"
        " .ltorg                                \n" /* Assemble current literal pool to avoid offset-out-of-bound errors with lto. */
    );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* An application can install FreeRTOS interrupt handlers in one of the
     * following ways:
     * 1. Direct Routing - Install the functions vPortSVCHandler and
     *    xPortPendSVHandler for SVCall and PendSV interrupts respectively.
     * 2. Indirect Routing - Install separate handlers for SVCall and PendSV
     *    interrupts and route program control from those handlers to
     *    vPortSVCHandler and xPortPendSVHandler functions.
     *
     * Applications that use Indirect Routing must set
     * configCHECK_HANDLER_INSTALLATION to 0 in their FreeRTOSConfig.h. Direct
     * routing, which is validated here when configCHECK_HANDLER_INSTALLATION
     * is 1, should be preferred when possible. */
    #यदि ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ध्रुव पत्तनम्_ISR_t * ध्रुव px_सदिशम्_सारणी = पत्तनम्_SCB_VTOR_REG;

        /* Validate that the application has correctly installed the FreeRTOS
         * handlers for SVCall and PendSV interrupts. We do not check the
         * installation of the SysTick handler because the application may
         * choose to drive the RTOS tick using a timer other than the SysTick
         * timer by overriding the weak function vPortSetupTimerInterrupt().
         *
         * Assertion failures here indicate incorrect installation of the
         * FreeRTOS handlers. For help installing the FreeRTOS handlers, see
         * https://www.freertos.org/Why-FreeRTOS/FAQs.
         *
         * Systems with a configurable address for the interrupt vector table
         * can also encounter assertion failures or even system faults here if
         * VTOR is not set correctly to point to the application's vector table. */
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_SVC ] == v_पत्तनम्_SVCHandler );
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_PENDSV ] == x_पत्तनम्_Pend_SVHandler );
    }
    #यदि_अन्तः /* configCHECK_HANDLER_INSTALLATION */

    #यदि ( configASSERT_DEFINED == 1 )
    {
        चञ्चल uint8_t uc_Original_प्राथमिकता;
        चञ्चल uint32_t ul_Implemented_Prio_द्वयङ्काः = 0;
        चञ्चल uint8_t * ध्रुव puc_First_User_प्राथमिकता_पञ्जिकाकोशः = ( चञ्चल uint8_t * ध्रुव ) ( पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16 + पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या );
        चञ्चल uint8_t uc_Max_प्राथमिकता_मानम्;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions
         * to ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_प्राथमिकता = *puc_First_User_प्राथमिकता_पञ्जिकाकोशः;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_First_User_प्राथमिकता_पञ्जिकाकोशः = पत्तनम्_MAX_8_BIT_मानम्;

        /* Read the value back to see how many bits stuck. */
        uc_Max_प्राथमिकता_मानम् = *puc_First_User_प्राथमिकता_पञ्जिकाकोशः;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_प्राथमिकता = config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & uc_Max_प्राथमिकता_मानम्;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_प्राथमिकता );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & ( ~uc_Max_प्राथमिकता_मानम् ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        यावत्( ( uc_Max_प्राथमिकता_मानम् & पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE ) == पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE )
        {
            ul_Implemented_Prio_द्वयङ्काः++;
            uc_Max_प्राथमिकता_मानम् <<= ( uint8_t ) 0x01;
        }

        यदि( ul_Implemented_Prio_द्वयङ्काः == 8 )
        {
            /* When the hardware implements 8 priority bits, there is no way for
             * the software to configure PRIGROUP to not have sub-priorities. As
             * a result, the least significant bit is always used for sub-priority
             * and there are 128 preemption priorities and 2 sub-priorities.
             *
             * This may cause some confusion in some cases - for example, if
             * configMAX_SYSCALL_INTERRUPT_PRIORITY is set to 5, both 5 and 4
             * priority interrupts will be masked in Critical Sections as those
             * are at the same preemption priority. This may appear confusing as
             * 4 is higher (numerically lower) priority than
             * configMAX_SYSCALL_INTERRUPT_PRIORITY and therefore, should not
             * have been masked. Instead, if we set configMAX_SYSCALL_INTERRUPT_PRIORITY
             * to 4, this confusion does not happen and the behaviour remains the same.
             *
             * The following assert ensures that the sub-priority bit in the
             * configMAX_SYSCALL_INTERRUPT_PRIORITY is clear to avoid the above mentioned
             * confusion. */
            configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        अन्यथा
        {
            ulMaxPRIGROUPValue = पत्तनम्_MAX_PRIGROUP_द्वयङ्काः - ul_Implemented_Prio_द्वयङ्काः;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= पत्तनम्_PRIGROUP_सरणम्;
        ulMaxPRIGROUPValue &= पत्तनम्_प्राथमिकता_गणः_आवरणम्;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_First_User_प्राथमिकता_पञ्जिकाकोशः = uc_Original_प्राथमिकता;
    }
    #यदि_अन्तः /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;
    पत्तनम्_NVIC_SHPR2_REG = पत्तनम्_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_सज्जता_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_पत्तनम्_सज्जता_Timer_व्यवधानम्();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Start the first task. */
    __asm चञ्चल (
        " ldr r0, =0xE000ED08   \n" /* Use the NVIC offset register to locate the stack. */
        " ldr r0, [r0]          \n"
        " ldr r0, [r0]          \n"
        " msr msp, r0           \n" /* Set the msp back to the start of the stack. */
        " cpsie i               \n" /* Globally enable interrupts. */
        " cpsie f               \n"
        " dsb                   \n"
        " isb                   \n"
        " svc %0                \n" /* System call to start first task. */
        " nop                   \n"
        " .ltorg                \n"
        ::"i" ( पत्तनम्_SVC_START_SCHEDULER ) : "memory" );

    /* Should not get here! */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    #यदि ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            पत्तनम्_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #अन्यथा /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        पत्तनम्_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #यदि_अन्तः /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    #यदि ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            यदि( uxCriticalNesting == 0 )
            {
                पत्तनम्_ENABLE_INTERRUPTS();
            }

            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            यदि( uxCriticalNesting == 0 )
            {
                पत्तनम्_ENABLE_INTERRUPTS();
            }
        }
    #अन्यथा /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        यदि( uxCriticalNesting == 0 )
        {
            पत्तनम्_ENABLE_INTERRUPTS();
        }
    #यदि_अन्तः /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

शून्य x_पत्तनम्_Pend_SVHandler( शून्य )
{
    /* This is a naked function. */

    __asm चञ्चल
    (
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " ldr r1, [r2]                          \n" /* r1 = Location where the context should be saved. */
        "                                       \n"
        /*------------ Save Context. ----------- */
        " mrs r3, control                       \n"
        " mrs r0, psp                           \n"
        " isb                                   \n"
        "                                       \n"
        " stmia r1!, {r3-r11, lr}               \n" /* Store CONTROL register, r4-r11 and LR. */
        " ldmia r0, {r4-r11}                    \n" /* Copy hardware saved context into r4-r11. */
        " stmia r1!, {r0, r4-r11}               \n" /* Store original PSP (after hardware has saved context) and the hardware saved context. */
        " str r1, [r2]                          \n" /* Save the location from where the context should be restored as the first member of TCB. */
        "                                       \n"
        /*---------- Select next task. --------- */
        " mov r0, %0                            \n"
        " msr basepri, r0                       \n"
        " dsb                                   \n"
        " isb                                   \n"
        " bl vTaskSwitchContext                 \n"
        " mov r0, #0                            \n"
        " msr basepri, r0                       \n"
        "                                       \n"
        /*------------ Program MPU. ------------ */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " add r2, r2, #4                        \n" /* r2 = Second item in the TCB which is xMPUSettings. */
        "                                       \n"
        " dmb                                   \n" /* Complete outstanding transfers before disabling MPU. */
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " bic r3, #1                            \n" /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Disable MPU. */
        "                                       \n"
        " ldr r0, =0xe000ed9c                   \n" /* Region Base Address register. */
        " ldmia r2!, {r4-r11}                   \n" /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
        " stmia r0, {r4-r11}                    \n" /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */
        "                                       \n"
        " ldr r0, =0xe000ed94                   \n" /* MPU_CTRL register. */
        " ldr r3, [r0]                          \n" /* Read the value of MPU_CTRL. */
        " orr r3, #1                            \n" /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
        " str r3, [r0]                          \n" /* Enable MPU. */
        " dsb                                   \n" /* Force memory writes before continuing. */
        "                                       \n"
        /*---------- Restore Context. ---------- */
        " ldr r3, =pxCurrentTCB                 \n" /* r3 = =pxCurrentTCB. */
        " ldr r2, [r3]                          \n" /* r2 = pxCurrentTCB. */
        " ldr r1, [r2]                          \n" /* r1 = Location of saved context in TCB. */
        "                                       \n"
        " ldmdb r1!, {r0, r4-r11}               \n" /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
        " msr psp, r0                           \n"
        " stmia r0, {r4-r11}                    \n" /* Copy the hardware saved context on the task stack. */
        " ldmdb r1!, {r3-r11, lr}               \n" /* r3 contains CONTROL register. r4-r11 and LR restored. */
        " msr control, r3                       \n"
        "                                       \n"
        " str r1, [r2]                          \n" /* Save the location where the context should be saved next as the first member of TCB. */
        " bx lr                                 \n"
        "                                       \n"
        " .ltorg                                \n" /* Assemble current literal pool to avoid offset-out-of-bound errors with lto. */
        ::"i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता )
    );
}
/*-----------------------------------------------------------*/

शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य )
{
    uint32_t ulDummy;

    ulDummy = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
            /* Pend a context switch. */
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Stop and clear the SysTick. */
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = 0UL;
    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL;
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK | पत्तनम्_NVIC_SYSTICK_INT | पत्तनम्_NVIC_SYSTICK_ENABLE );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_MPU( शून्य )
{
    #यदि defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        बाह्य uint32_t * __privileged_functions_start__;
        बाह्य uint32_t * __privileged_functions_end__;
        बाह्य uint32_t * __FLASH_segment_start__;
        बाह्य uint32_t * __FLASH_segment_end__;
        बाह्य uint32_t * __privileged_data_start__;
        बाह्य uint32_t * __privileged_data_end__;
    #अन्यथा
        /* Declaration when these variable are exported from linker scripts. */
        बाह्य uint32_t __privileged_functions_start__[];
        बाह्य uint32_t __privileged_functions_end__[];
        बाह्य uint32_t __FLASH_segment_start__[];
        बाह्य uint32_t __FLASH_segment_end__[];
        बाह्य uint32_t __privileged_data_start__[];
        बाह्य uint32_t __privileged_data_end__[];
    #यदि_अन्तः /* if defined( __ARMCC_VERSION ) */

    /* Ensure that the device has the expected MPU type */
    configASSERT( पत्तनम्_MPU_TYPE_REG == पत्तनम्_EXPECTED_MPU_TYPE_मानम् );

    /* Check the expected MPU is present. */
    यदि( पत्तनम्_MPU_TYPE_REG == पत्तनम्_EXPECTED_MPU_TYPE_मानम् )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        पत्तनम्_MPU_REGION_आधारः_स्थानाङ्कः_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( पत्तनम्_MPU_REGION_VALID ) |
                                          ( पत्तनम्_UNPRIVILEGED_FLASH_REGION );

        पत्तनम्_MPU_REGION_ATTRIBUTE_REG = ( पत्तनम्_MPU_REGION_READ_ONLY ) |
                                       ( पत्तनम्_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                                       ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( पत्तनम्_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is * placed. */
        पत्तनम्_MPU_REGION_आधारः_स्थानाङ्कः_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( पत्तनम्_MPU_REGION_VALID ) |
                                          ( पत्तनम्_PRIVILEGED_FLASH_REGION );

        पत्तनम्_MPU_REGION_ATTRIBUTE_REG = ( पत्तनम्_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( पत्तनम्_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                                       ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( पत्तनम्_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        पत्तनम्_MPU_REGION_आधारः_स्थानाङ्कः_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( पत्तनम्_MPU_REGION_VALID ) |
                                          ( पत्तनम्_PRIVILEGED_RAM_REGION );

        पत्तनम्_MPU_REGION_ATTRIBUTE_REG = ( पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( पत्तनम्_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                                       ( पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
                                       prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( पत्तनम्_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        पत्तनम्_MPU_REGION_आधारः_स्थानाङ्कः_REG = ( पत्तनम्_PERIPHERALS_START_स्थानाङ्कः ) |
                                          ( पत्तनम्_MPU_REGION_VALID ) |
                                          ( पत्तनम्_GENERAL_PERIPHERALS_REGION );

        पत्तनम्_MPU_REGION_ATTRIBUTE_REG = ( पत्तनम्_MPU_REGION_READ_WRITE | पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_आकार_Setting( पत्तनम्_PERIPHERALS_अन्तः_स्थानाङ्कः - पत्तनम्_PERIPHERALS_START_स्थानाङ्कः ) ) |
                                       ( पत्तनम्_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        पत्तनम्_NVIC_SYS_CTRL_STATE_REG |= पत्तनम्_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        पत्तनम्_MPU_CTRL_REG |= ( पत्तनम्_MPU_ENABLE | पत्तनम्_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

स्थिर uint32_t prv_Get_MPURegion_आकार_Setting( uint32_t ul_Actual_आकार_अन्तर्_अष्टकानि )
{
    uint32_t ul_Region_आकार, ul_Return_मानम् = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    प्रति( ul_Region_आकार = 32UL; ul_Return_मानम् < 31UL; ( ul_Region_आकार <<= 1UL ) )
    {
        यदि( ul_Actual_आकार_अन्तर्_अष्टकानि <= ul_Region_आकार )
        {
            भङ्ग;
        }
        अन्यथा
        {
            ul_Return_मानम्++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    प्रत्यागम( ul_Return_मानम् << 1UL );
}
/*-----------------------------------------------------------*/

आधारः_Type_t xIsPrivileged( शून्य ) /* __attribute__ (( naked )) */
{
    __asm चञ्चल
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   tst r0, #1                              \n" /* Perform r0 & 1 (bitwise AND) and update the conditions flag. */
        "   ite ne                                  \n"
        "   movne r0, #0                            \n" /* CONTROL[0]!=0. Return false to indicate that the processor is not privileged. */
        "   moveq r0, #1                            \n" /* CONTROL[0]==0. Return true to indicate that the processor is privileged. */
        "   bx lr                                   \n" /* Return. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

शून्य vResetPrivilege( शून्य ) /* __attribute__ (( naked )) */
{
    __asm चञ्चल
    (
        "   mrs r0, control                         \n" /* r0 = CONTROL. */
        "   orr r0, #1                              \n" /* r0 = r0 | 1. */
        "   msr control, r0                         \n" /* CONTROL = r0. */
        "   bx lr                                   \n" /* Return to the caller. */
        ::: "r0", "memory"
    );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Switch_गन्तव्यम्_User_बहुलकम्( शून्य )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ध्रुव संरचना x_स्मृतिः_REGION * ध्रुव xRegions,
                                राशिः_Type_t * px_Bottom_सम्बन्धि_राशिः,
                                config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता )
{
    #यदि defined( __ARMCC_VERSION )

        /* Declaration when these variable are defined in code instead of being
         * exported from linker scripts. */
        बाह्य uint32_t * __SRAM_segment_start__;
        बाह्य uint32_t * __SRAM_segment_end__;
        बाह्य uint32_t * __privileged_data_start__;
        बाह्य uint32_t * __privileged_data_end__;
    #अन्यथा
        /* Declaration when these variable are exported from linker scripts. */
        बाह्य uint32_t __SRAM_segment_start__[];
        बाह्य uint32_t __SRAM_segment_end__[];
        बाह्य uint32_t __privileged_data_start__[];
        बाह्य uint32_t __privileged_data_end__[];
    #यदि_अन्तः /* if defined( __ARMCC_VERSION ) */

    int32_t l_सूचकांक;
    uint32_t ul;

    यदि( xRegions == रिक्त )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_आधारः_स्थानाङ्कः =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( पत्तनम्_MPU_REGION_VALID ) |
            ( पत्तनम्_राशिः_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( पत्तनम्_MPU_REGION_READ_WRITE ) |
            ( पत्तनम्_MPU_REGION_CACHEABLE_BUFFERABLE ) |
            ( पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
            ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( पत्तनम्_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_Start_स्थानाङ्कः = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_अन्तः_स्थानाङ्कः = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        प्रति( ul = 1UL; ul <= पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_आधारः_स्थानाङ्कः = ( ( ul - 1UL ) | पत्तनम्_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_Start_स्थानाङ्कः = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_अन्तः_स्थानाङ्कः = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    अन्यथा
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        यदि( ux_राशिः_गभीरता > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_आधारः_स्थानाङ्कः =
                ( ( uint32_t ) px_Bottom_सम्बन्धि_राशिः ) |
                ( पत्तनम्_MPU_REGION_VALID ) |
                ( पत्तनम्_राशिः_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( पत्तनम्_MPU_REGION_READ_WRITE ) |
                ( पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_आकार_Setting ( ( uint32_t ) ( ux_राशिः_गभीरता * ( config_राशिः_गभीरता_TYPE ) परिमाण( राशिः_Type_t ) ) ) ) |
                ( पत्तनम्_MPU_REGION_CACHEABLE_BUFFERABLE ) |
                ( पत्तनम्_MPU_REGION_ENABLE );
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_Start_स्थानाङ्कः = ( uint32_t ) px_Bottom_सम्बन्धि_राशिः;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_अन्तः_स्थानाङ्कः = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_सम्बन्धि_राशिः ) +
                                                                                   ( ux_राशिः_गभीरता * ( config_राशिः_गभीरता_TYPE ) परिमाण( राशिः_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_सूचकांक = 0;

        प्रति( ul = 1UL; ul <= पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; ul++ )
        {
            यदि( ( xRegions[ l_सूचकांक ] ).ul_दीर्घता_अन्तर्_अष्टकानि > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM3 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_आधारः_स्थानाङ्कः =
                    ( ( uint32_t ) xRegions[ l_सूचकांक ].pv_आधारः_स्थानाङ्कः ) |
                    ( पत्तनम्_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_आकार_Setting( xRegions[ l_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि ) ) |
                    ( xRegions[ l_सूचकांक ].ulParameters ) |
                    ( पत्तनम्_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_Start_स्थानाङ्कः = ( uint32_t ) xRegions[ l_सूचकांक ].pv_आधारः_स्थानाङ्कः;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_अन्तः_स्थानाङ्कः = ( uint32_t ) ( ( uint32_t ) xRegions[ l_सूचकांक ].pv_आधारः_स्थानाङ्कः + xRegions[ l_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                यदि( ( ( xRegions[ l_सूचकांक ].ulParameters & पत्तनम्_MPU_REGION_READ_ONLY ) == पत्तनम्_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_सूचकांक ].ulParameters & पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                यदि( ( xRegions[ l_सूचकांक ].ulParameters & पत्तनम्_MPU_REGION_READ_WRITE ) == पत्तनम्_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            अन्यथा
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_आधारः_स्थानाङ्कः = ( ( ul - 1UL ) | पत्तनम्_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_Start_स्थानाङ्कः = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_अन्तः_स्थानाङ्कः = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_सूचकांक++;
        }
    }
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( ध्रुव शून्य * pv_बफर,
                                                size_t x_बफर_दीर्घता,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_बफर_Start_स्थानाङ्कः, ul_बफर_अन्तः_स्थानाङ्कः;
        आधारः_Type_t xAccessGranted = pdFALSE;
        ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

        यदि( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            यदि( पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( ( ( uint32_t ) pv_बफर ), ( ( uint32_t ) x_बफर_दीर्घता - 1UL ) ) == pdFALSE )
            {
                ul_बफर_Start_स्थानाङ्कः = ( uint32_t ) pv_बफर;
                ul_बफर_अन्तः_स्थानाङ्कः = ( ( ( uint32_t ) pv_बफर ) + ( uint32_t ) x_बफर_दीर्घता - 1UL );

                प्रति( i = 0; i < पत्तनम्_योग_अङ्कः_REGIONS_अन्तर्_TCB; i++ )
                {
                    यदि( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ul_बफर_Start_स्थानाङ्कः,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_Start_स्थानाङ्कः,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_अन्तः_स्थानाङ्कः ) &&
                        पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ul_बफर_अन्तः_स्थानाङ्कः,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_Start_स्थानाङ्कः,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_अन्तः_स्थानाङ्कः ) &&
                        पत्तनम्_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        भङ्ग;
                    }
                }
            }
        }

        प्रत्यागम xAccessGranted;
    }

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#यदि ( configASSERT_DEFINED == 1 )

    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य )
    {
        uint32_t ul_Current_व्यवधानम्;
        uint8_t uc_Current_प्राथमिकता;

        /* Obtain the number of the currently executing interrupt. */
        __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ul_Current_व्यवधानम् )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        यदि( ul_Current_व्यवधानम् >= पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या )
        {
            /* Look up the interrupt's priority. */
            uc_Current_प्राथमिकता = pc_व्यवधानम्_प्राथमिकता_Registers[ ul_Current_व्यवधानम् ];

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
             * Interrupts that  use the FreeRTOS API must not be left at their
             * default priority of  zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and  therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( uc_Current_प्राथमिकता >= uc_Max_Sys_Call_प्राथमिकता );
        }

        /* Priority grouping:  The interrupt controller (NVIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * If the application only uses CMSIS libraries for interrupt
         * configuration then the correct setting can be achieved on all Cortex-M
         * devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
         * scheduler.  Note however that some vendor specific peripheral libraries
         * assume a non-zero priority group setting, in which cases using a value
         * of zero will result in unpredictable behaviour. */
        configASSERT( ( पत्तनम्_AIRCR_REG & पत्तनम्_प्राथमिकता_गणः_आवरणम् ) <= ulMaxPRIGROUPValue );
    }

#यदि_अन्तः /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#यदि ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    शून्य v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                         int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] |= ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
    }

#यदि_अन्तः /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    शून्य v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                          int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] &= ~( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
    }

#यदि_अन्तः /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
            आधारः_Type_t xAccessGranted = pdFALSE;
            ध्रुव xMPU_SETTINGS * xTaskMpuSettings;

            यदि( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            अन्यथा
            {
                xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

                ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
                ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

                यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                अन्यथा
                {
                    यदि( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] & ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            प्रत्यागम xAccessGranted;
        }

    #अन्यथा /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( शून्य ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            प्रत्यागम pdTRUE;
        }

    #यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#यदि_अन्तः /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
