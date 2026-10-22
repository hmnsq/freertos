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
* Implementation of functions defined in portable.h for the ARM CM4 MPU port.
*----------------------------------------------------------*/

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __TARGET_FPU_VFP
    #ದೋಷ This ಪೋರ್ಟ್ can only be ಬಳಸಿದ when the project options are configured ಗಮ್ಯ enable hardware floating ಬಿಂದು_2 support.
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Unprivileged critical sections are not supported when using MPU wrappers
 * version 2. Default the option to 0 and reject an explicit value of 1. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS
    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        #ವ್ಯಾಖ್ಯಾನಿಸು configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    0
    #ಇಲ್ಲದಿದ್ದರೆ
        #warning "configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not defined. We recommend defining it to 0 in FreeRTOSConfig.h for better security."
        #ವ್ಯಾಖ್ಯಾನಿಸು configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS    1
    #ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
    #ಆದರೆ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) )
        #ದೋಷ configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS is not supported with MPU wrappers ಆವೃತ್ತಿ 2 ( configUSE_MPU_WRAPPERS_V1 == 0 ).
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* Prototype of all Interrupt Service Routines (ISRs). */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ ( * ಪೋರ್ಟ್_ISR_t )( ಶೂನ್ಯ );

/* Constants required to access and manipulate the NVIC. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG                 ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e010 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG                 ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e014 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e018 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR3_REG                        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed20 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR2_REG                        ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed1c ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYS_CTRL_STATE_REG               ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed24 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_MEM_FAULT_ENABLE                 ( 1UL << 16UL )

/* Constants used to detect Cortex-M7 r0p0 and r0p1 cores, and ensure
 * that a work around is active for errata 837070. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPUID                                 ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xE000ed00 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CORTEX_M7_r0p1_ID                     ( 0x410FC271UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CORTEX_M7_r0p0_ID                     ( 0x410FC270UL )

/* Constants required to access and manipulate the MPU. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_TYPE_REG                          ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed90 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ತಳ_ವಿಳಾಸ_REG           ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed9C ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ATTRIBUTE_REG              ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000edA0 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_CTRL_REG                          ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed94 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ               ( config_ಒಟ್ಟು_MPU_REGIONS << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ENABLE                            ( 0x01UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_BACKGROUND_ENABLE                 ( 1UL << 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_EXECUTION_ಆರಂಭ_ವಿಳಾಸ    ( 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_VALID                      ( 0x10UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ENABLE                     ( 0x01UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PERIPHERALS_ಆರಂಭ_ವಿಳಾಸ             0x40000000UL
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PERIPHERALS_ಕೊನೆ_ವಿಳಾಸ               0x5FFFFFFFUL

/* Constants required to access and manipulate the SysTick and other FreeRTOS
 * interrupts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK                      ( 0x00000004UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_INT                      ( 0x00000002UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE                   ( 0x00000001UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ                ( 255UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSV_PRI                       ( ( ( uint32_t ) ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_PRI                      ( ( ( uint32_t ) ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SVC_PRI                          ( ( ( uint32_t ) config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ - 1UL ) << 24UL )

/* Constants required to manipulate the VFP. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR                                 ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ef34UL ) /* Floating point context control register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASPEN_AND_LSPEN_ಬಿಟ್ಟುಗಳು                  ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_XPSR                          ( 0x01000000UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EXC_RETURN                    ( 0xfffffffdUL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CONTROL_IF_UNPRIVILEGED       ( 0x03 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CONTROL_IF_PRIVILEGED         ( 0x02 )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_VTOR_REG                          ( *( ( ಪೋರ್ಟ್_ISR_t ** ) 0xE000ED08 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_SVC                      ( 11 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_PENDSV                   ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ           ( 16 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16           ( 0xE000E3F0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_AIRCR_REG                             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xE000ED0C ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ                       ( ( uint8_t ) 0xff )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE                       ( ( uint8_t ) 0x80 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_PRIGROUP_ಬಿಟ್ಟುಗಳು                     ( ( uint8_t ) 7 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ                   ( 0x07UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIGROUP_ಸರಿಸು                        ( 8UL )

/* Constants used during system call enter and exit. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ                ( 1UL << 9UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ      ( 1UL << 4UL )

/* Offsets in the stack to the parameters when inside the SVC handler. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR                          ( 5 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC                          ( 6 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR                         ( 7 )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆರಂಭ_ವಿಳಾಸ_ಮುಖವಾಡ                    ( ( ರಾಶಿ_Type_t ) 0xfffffffeUL )

/* Does addr lie within [start, end] address range? */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( addr, ಆರಂಭ, ಕೊನೆ ) \
    ( ( ( addr ) >= ( ಆರಂಭ ) ) && ( ( addr ) <= ( ಕೊನೆ ) ) )

/* Is the access request satisfied by the available permissions? */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( a ) > ( ಪೋರ್ಟ್_UINT32_MAX - ( b ) ) )
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable.  Note this is not saved as part of the task context as context
 * switches can only occur when uxCriticalNesting is zero. */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/*
 * This variable is set to pdTRUE when the scheduler is started.
 */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ತಳ_Type_t xSchedulerRunning = pdFALSE;

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * Setup the timer to generate the tick interrupts.
 */
ಶೂನ್ಯ v_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*
 * Configure a number of standard MPU regions that are used by all tasks.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*
 * Return the smallest MPU region size that a given number of bytes will fit
 * into.  The region size is returned as the value that should be programmed
 * into the region attribute register for that region.
 */
ಸ್ಥಿರ uint32_t prv_Get_MPURegion_ಗಾತ್ರ_Setting( uint32_t ul_Actual_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು ) PRIVILEGED_FUNCTION;

/*
 * Standard FreeRTOS exception handlers.
 */
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*
 * Starts the scheduler by restoring the context of the first task to run.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_Restore_Context_ದ_ಮೊದಲ_Task( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*
 * C portion of the SVC handler.  The SVC handler is split between an asm entry
 * and a C wrapper for simplicity of coding and maintenance.
 */
ಶೂನ್ಯ vSVCHandler_C( uint32_t * pulRegisters ) __attribute__( ( ಬಳಸಿದ ) ) PRIVILEGED_FUNCTION;

/*
 * Function to enable the VFP.
 */
ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_VFP( ಶೂನ್ಯ );

/*
 * Utility function.
 */
ಸ್ಥಿರ uint32_t prv_ಪೋರ್ಟ್_Get_IPSR( ಶೂನ್ಯ );

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ಆದರೆ ( configASSERT_DEFINED == 1 )
    ಸ್ಥಿರ uint8_t uc_Max_Sys_Call_ಆದ್ಯತೆ = 0;
    ಸ್ಥಿರ uint32_t ulMaxPRIGROUPValue = 0;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ pc_ಅಡಚಣೆ_ಆದ್ಯತೆ_Registers = ( ಸ್ಥಿರಾಂಕ uint8_t * ) ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16;
#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
ತಳ_Type_t xIsPrivileged( ಶೂನ್ಯ );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ );

/**
 * @brief Make a task unprivileged.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Switch_ಗಮ್ಯ_User_ಬಹುಲಕ( ಶೂನ್ಯ );

/**
 * @brief Enter critical section.
 */
#ಆದರೆ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;
#ಇಲ್ಲದಿದ್ದರೆ
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Exit from critical section.
 */
#ಆದರೆ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;
#ಇಲ್ಲದಿದ್ದರೆ
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Triggers lazy stacking of FPU registers.
 */
    ಸ್ಥಿರ ಶೂನ್ಯ prvTriggerLazyStacking( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the system call stack so that upon returning from
 * SVC, the system call stack is used.
 *
 * @param pulTaskStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 * @param ucSystemCallNumber The system call number of the system call.
 */
    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Raise SVC for exiting from a system call.
 */
    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

/**
 * @brief Sets up the task stack so that upon returning from
 * SVC, the task stack is used again.
 *
 * @param pulSystemCallStack The current SP when the SVC was raised.
 * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
 */
    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters,
                                     ತಳ_Type_t x_ಸತತ_Privileged,
                                     xMPU_SETTINGS * xMPUSettings )
{
    ಆದರೆ( x_ಸತತ_Privileged == pdTRUE )
    {
        xMPUSettings->ulTaskFlags |= ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG;
        xMPUSettings->ulContext[ 0 ] = ಪೋರ್ಟ್_INITIAL_CONTROL_IF_PRIVILEGED;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xMPUSettings->ulTaskFlags &= ( ~( ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) );
        xMPUSettings->ulContext[ 0 ] = ಪೋರ್ಟ್_INITIAL_CONTROL_IF_UNPRIVILEGED;
    }

    xMPUSettings->ulContext[ 1 ] = 0x04040404;                                        /* r4. */
    xMPUSettings->ulContext[ 2 ] = 0x05050505;                                        /* r5. */
    xMPUSettings->ulContext[ 3 ] = 0x06060606;                                        /* r6. */
    xMPUSettings->ulContext[ 4 ] = 0x07070707;                                        /* r7. */
    xMPUSettings->ulContext[ 5 ] = 0x08080808;                                        /* r8. */
    xMPUSettings->ulContext[ 6 ] = 0x09090909;                                        /* r9. */
    xMPUSettings->ulContext[ 7 ] = 0x10101010;                                        /* r10. */
    xMPUSettings->ulContext[ 8 ] = 0x11111111;                                        /* r11. */
    xMPUSettings->ulContext[ 9 ] = ಪೋರ್ಟ್_INITIAL_EXC_RETURN;                            /* EXC_RETURN. */

    xMPUSettings->ulContext[ 10 ] = ( uint32_t ) ( px_ತುದಿ_ದ_ರಾಶಿ - 8 );                /* PSP with the hardware saved stack. */
    xMPUSettings->ulContext[ 11 ] = ( uint32_t ) pvParameters;                        /* r0. */
    xMPUSettings->ulContext[ 12 ] = 0x01010101;                                       /* r1. */
    xMPUSettings->ulContext[ 13 ] = 0x02020202;                                       /* r2. */
    xMPUSettings->ulContext[ 14 ] = 0x03030303;                                       /* r3. */
    xMPUSettings->ulContext[ 15 ] = 0x12121212;                                       /* r12. */
    xMPUSettings->ulContext[ 16 ] = 0;                                                /* LR. */
    xMPUSettings->ulContext[ 17 ] = ( ( uint32_t ) px_ಸಂಕೇತ ) & ಪೋರ್ಟ್_ಆರಂಭ_ವಿಳಾಸ_ಮುಖವಾಡ; /* PC. */
    xMPUSettings->ulContext[ 18 ] = ಪೋರ್ಟ್_INITIAL_XPSR;                                 /* xPSR. */

    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        /* Ensure that the system call stack is double word aligned. */
        xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = &( xMPUSettings->x_System_Call_ರಾಶಿ_Info.ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ - 1 ] );
        xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ ) &
                                                                                 ( uint32_t ) ( ~( ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );

        /* This is not NULL only for the duration of a system call. */
        xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ಖಾಲಿ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    ಹಿಂತಿರುಗಿ &( xMPUSettings->ulContext[ 19 ] );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vSVCHandler_C( uint32_t * pulParam )
{
    uint8_t ucSVCNumber;
    uint32_t ulPC;

    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 1 )
        uint32_t ulReg;
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ಆದರೆ ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) )
        ಬಾಹ್ಯ uint32_t __syscalls_flash_start__;
        ಬಾಹ್ಯ uint32_t __syscalls_flash_end__;
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 1 ) && ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) ) */

    /* The stack contains: r0, r1, r2, r3, r12, LR, PC and xPSR. The first
     * argument (r0) is pulParam[ 0 ]. */
    ulPC = pulParam[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ಆಯ್ಕೆ( ucSVCNumber )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER:
            prv_Restore_Context_ದ_ಮೊದಲ_Task();
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_YIELD:
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;

            /* Barriers are normally not required
             * but do ensure the code is completely
             * within the specified behaviour for the
             * architecture. */
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            ನಿಲ್ಲಿಸು;

    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 1 )
        #ಆದರೆ ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 )
            ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE: /* Only raise the privilege, if the
                                           * svc was raised from any of the
                                           * system calls. */

                ಆದರೆ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                    ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
                {
                    __asm
                    {
                        /* *INDENT-OFF* */
                        mrs ulReg, control /* Obtain current control value. */
                        bic ulReg, # 1     /* Set privilege bit. */
                        msr control, ulReg /* Write back new control value. */
                        /* *INDENT-ON* */
                    }
                }

                ನಿಲ್ಲಿಸು;
        #ಇಲ್ಲದಿದ್ದರೆ /* if ( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
            ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE:
                __asm
                {
                    /* *INDENT-OFF* */
                    mrs ulReg, control /* Obtain current control value. */
                    bic ulReg, # 1     /* Set privilege bit. */
                    msr control, ulReg /* Write back new control value. */
                    /* *INDENT-ON* */
                }
                ನಿಲ್ಲಿಸು;
        #ಆದರೆ_ಅಂತ್ಯ /* #if( configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY == 1 ) */
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

        ಪೂರ್ವನಿಯೋಜಿತ: /* Unknown SVC call. */
            ನಿಲ್ಲಿಸು;
    }
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm ಶೂನ್ಯ prvTriggerLazyStacking( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
    /* *INDENT-OFF* */
        PRESERVE8

        vpush {s0} /* Trigger lazy stacking. */
        vpop  {s0} /* Nullify the affect of the above instruction. */

    /* *INDENT-ON* */
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        ಬಾಹ್ಯ UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ರಾಶಿ;
        uint32_t ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ, ulSystemCallLocation, i, r1;
        ಬಾಹ್ಯ uint32_t __syscalls_flash_start__;
        ಬಾಹ್ಯ uint32_t __syscalls_flash_end__;

        ulSystemCallLocation = pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
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
        ಆದರೆ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ == ಖಾಲಿ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ಆದರೆ( ( ulLR & ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 26;
                prvTriggerLazyStacking();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;
            }

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ರಾಶಿ = pul_System_Call_ರಾಶಿ - ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Copy the stack frame. */
            ಗಾಗಿ( i = 0; i < ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ; i++ )
            {
                pul_System_Call_ರಾಶಿ[ i ] = pul_Task_ರಾಶಿ[ i ];
            }

            /* Use the pulSystemCallStack in thread mode. */
            __asm
            {
                msr psp, pul_System_Call_ರಾಶಿ
            };

            /* Raise the privilege for the duration of the system call. */
            __asm
            {
                mrs r1, control /* Obtain current control value. */
                bic r1, # 1     /* Clear nPRIV bit. */
                msr control, r1 /* Write back new control value. */
            };

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ + ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು = pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ];

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ] = uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ];
            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ಆದರೆ( ( pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] & ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ )
            {
                pxMpuSettings->ulTaskFlags |= ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pxMpuSettings->ulTaskFlags &= ( ~ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] &= ( ~ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        PRESERVE8

        svc #portSVC_SYSTEM_CALL_EXIT
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ರಾಶಿ;
        uint32_t ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ, ulSystemCallLocation, i, r1;
        ಬಾಹ್ಯ uint32_t __privileged_functions_start__;
        ಬಾಹ್ಯ uint32_t __privileged_functions_end__;

        ulSystemCallLocation = pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
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
        ಆದರೆ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ != ಖಾಲಿ ) )
        {
            pul_Task_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ;

            /* Hardware Saved Stack Frame Size upon Exception entry:
             * - No FPU: basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
             * - With FPU (lazy stacking): basic frame + S0–S15 + FPSCR + reserved word = 26 words.
             */
            ಆದರೆ( ( ulLR & ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ ) == 0UL )
            {
                /* Extended frame i.e. FPU in use. */
                ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 26;
                prvTriggerLazyStacking();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Standard frame i.e. FPU not in use. */
                ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;
            }

            /* Make space on the task stack for the stack frame. */
            pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ - ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Copy the stack frame. */
            ಗಾಗಿ( i = 0; i < ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ; i++ )
            {
                pul_Task_ರಾಶಿ[ i ] = pul_System_Call_ರಾಶಿ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm
            {
                msr psp, pul_Task_ರಾಶಿ
            };

            /* Drop the privilege before returning to the thread mode. */
            __asm
            {
                mrs r1, control /* Obtain current control value. */
                orr r1, # 1     /* Set nPRIV bit. */
                msr control, r1 /* Write back new control value. */
            };

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
            /* Ensure that LR has a valid value.*/
            pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ಆದರೆ( ( pxMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG ) == ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG )
            {
                pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] |= ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] &= ( ~ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ಖಾಲಿ;
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    ತಳ_Type_t xTaskIsPrivileged = pdFALSE;
    ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

    ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
    {
        xTaskIsPrivileged = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xTaskIsPrivileged;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    __asm ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ )
    {
        ಬಾಹ್ಯ vSVCHandler_C
        ಬಾಹ್ಯ vSystemCallEnter
        ಬಾಹ್ಯ vSystemCallExit

/* *INDENT-OFF* */
    PRESERVE8

    tst lr, #4
    ite eq
    mrseq r0, msp
    mrsne r0, psp

    ldr r1, [r0, #24]
    ldrb r2, [r1, #-2]
    cmp r2, #NUM_SYSTEM_CALLS
    blt syscall_enter
    cmp r2, #portSVC_SYSTEM_CALL_EXIT
    beq syscall_exit
    b vSVCHandler_C

syscall_enter
        mov r1, lr
        b vSystemCallEnter

syscall_exit
        mov r1, lr
        b vSystemCallExit
/* *INDENT-ON* */
    }

#ಇಲ್ಲದಿದ್ದರೆ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    __asm ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ )
    {
        ಬಾಹ್ಯ vSVCHandler_C

/* *INDENT-OFF* */
        PRESERVE8

    /* Assumes psp was in use. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_PROCESS_ರಾಶಿ   /* Code should not be required if a main() is using the process stack. */
        tst lr, # 4
        ite eq
        mrseq r0, msp
        mrsne r0, psp
    #ಇಲ್ಲದಿದ್ದರೆ
        mrs r0, psp
    #ಆದರೆ_ಅಂತ್ಯ

    b vSVCHandler_C
/* *INDENT-ON* */
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ prv_Restore_Context_ದ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    PRESERVE8

    ldr r0, =0xE000ED08         /* Use the NVIC offset register to locate the stack. */
    ldr r0, [r0]
    ldr r0, [r0]
    msr msp, r0                 /* Set the msp back to the start of the stack. */

    /*------------ Program MPU. ------------ */
    ldr r3, =pxCurrentTCB       /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                /* r2 = pxCurrentTCB. */
    ಕೂಡಿಸು r2, r2, #4              /* r2 = Second item in the TCB which is xMPUSettings. */

    dmb                         /* Complete outstanding transfers before disabling MPU. */
    ldr r0, =0xe000ed94         /* MPU_CTRL register. */
    ldr r3, [r0]                /* Read the value of MPU_CTRL. */
    bic r3, r3, # 1             /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
    str r3, [r0]                /* Disable MPU. */

    ldr r0, =0xe000ed9c         /* Region Base Address register. */
    ldmia r2!, {r4-r11}         /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
    stmia r0, {r4-r11}          /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */

    #ಆದರೆ ( config_ಒಟ್ಟು_MPU_REGIONS == 16 )
        ldmia r2!, {r4-r11}     /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
        stmia r0, {r4-r11}      /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
        ldmia r2!, {r4-r11}     /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
        stmia r0, {r4-r11}      /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
    #ಆದರೆ_ಅಂತ್ಯ /* configTOTAL_MPU_REGIONS == 16. */

    ldr r0, =0xe000ed94         /* MPU_CTRL register. */
    ldr r3, [r0]                /* Read the value of MPU_CTRL. */
    orr r3, r3, #1              /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
    str r3, [r0]                /* Enable MPU. */
    dsb                         /* Force memory writes before continuing. */

    /*---------- Restore Context. ---------- */
    ldr r3, =pxCurrentTCB       /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                /* r1 = Location of saved context in TCB. */

    ldmdb r1!, {r0, r4-r11}     /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
    msr psp, r0
    stmia r0, {r4-r11}          /* Copy the hardware saved context on the task stack. */
    ldmdb r1!, {r3-r11, lr}     /* r3 contains CONTROL register. r4-r11 and LR restored. */
    msr control, r3
    str r1, [r2]                /* Save the location where the context should be saved next as the first member of TCB. */

    mov r0, #0
    msr basepri, r0
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ );

    /* Errata 837070 workaround must only be enabled on Cortex-M7 r0p0
     * and r0p1 cores. */
    #ಆದರೆ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        configASSERT( ( ಪೋರ್ಟ್_CPUID == ಪೋರ್ಟ್_CORTEX_M7_r0p1_ID ) || ( ಪೋರ್ಟ್_CPUID == ಪೋರ್ಟ್_CORTEX_M7_r0p0_ID ) );
    #ಇಲ್ಲದಿದ್ದರೆ

        /* When using this port on a Cortex-M7 r0p0 or r0p1 core, define
         * configENABLE_ERRATA_837070_WORKAROUND to 1 in your
         * FreeRTOSConfig.h. */
        configASSERT( ಪೋರ್ಟ್_CPUID != ಪೋರ್ಟ್_CORTEX_M7_r0p1_ID );
        configASSERT( ಪೋರ್ಟ್_CPUID != ಪೋರ್ಟ್_CORTEX_M7_r0p0_ID );
    #ಆದರೆ_ಅಂತ್ಯ

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
    #ಆದರೆ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ಸ್ಥಿರಾಂಕ ಪೋರ್ಟ್_ISR_t * ಸ್ಥಿರಾಂಕ px_ಸದಿಶ_ಕೋಷ್ಟಕ = ಪೋರ್ಟ್_SCB_VTOR_REG;

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
        configASSERT( px_ಸದಿಶ_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_SVC ] == v_ಪೋರ್ಟ್_SVCHandler );
        configASSERT( px_ಸದಿಶ_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_PENDSV ] == x_ಪೋರ್ಟ್_Pend_SVHandler );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configCHECK_HANDLER_INSTALLATION */

    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        ಅಸ್ಥಿರ uint8_t uc_Original_ಆದ್ಯತೆ;
        ಅಸ್ಥಿರ uint32_t ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು = 0;
        ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ( uint8_t * ) ( ಪೋರ್ಟ್_NVIC_IP_REGISTERS_ಸ್ಥಾನಾಂತರ_16 + ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ );
        ಅಸ್ಥಿರ uint8_t uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ಆದ್ಯತೆ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ಆದ್ಯತೆ = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ಆದ್ಯತೆ );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & ( ~uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        ಆಗ( ( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ & ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE ) == ಪೋರ್ಟ್_ತುದಿ_ಬಿಟ್_ದ_BYTE )
        {
            ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು++;
            uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ <<= ( uint8_t ) 0x01;
        }

        ಆದರೆ( ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ulMaxPRIGROUPValue = ಪೋರ್ಟ್_MAX_PRIGROUP_ಬಿಟ್ಟುಗಳು - ul_Implemented_Prio_ಬಿಟ್ಟುಗಳು;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= ಪೋರ್ಟ್_PRIGROUP_ಸರಿಸು;
        ulMaxPRIGROUPValue &= ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = uc_Original_ಆದ್ಯತೆ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and configure
     * SVCall for sufficient preemption priority. */
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR2_REG = ಪೋರ್ಟ್_NVIC_SVC_PRI;

    /* Configure the regions in the MPU that are common to all tasks. */
    prv_ಸಿದ್ಧತೆ_MPU();

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
    {
        xSchedulerRunning = pdTRUE;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    /* Ensure the VFP is enabled - it should be anyway. */
    v_ಪೋರ್ಟ್_Enable_VFP();

    /* Lazy save always. */
    *( ಪೋರ್ಟ್_FPCCR ) |= ಪೋರ್ಟ್_ASPEN_AND_LSPEN_ಬಿಟ್ಟುಗಳು;

    /* Start the first task. */
    prv_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    PRESERVE8

    /* Use the NVIC offset register to locate the stack. */
    ldr r0, =0xE000ED08
    ldr r0, [ r0 ]
    ldr r0, [ r0 ]
    /* Set the msp back to the start of the stack. */
    msr msp, r0

    /* Clear the bit that indicates the FPU is in use in case the FPU was used
     * before the scheduler was started - which would otherwise result in the
     * unnecessary leaving of space in the SVC stack for lazy saving of FPU
     * registers. */
    mov r0, #0
    msr control, r0
    /* Globally enable interrupts. */
    cpsie i
    cpsie f
    dsb
    isb
    svc ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER /* System call to start first task. */
    nop
    nop
/* *INDENT-ON* */
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    #ಆದರೆ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
            uxCriticalNesting++;
        }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    #ಆದರೆ ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 )
        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ಆದರೆ( uxCriticalNesting == 0 )
            {
                ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
            }

            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            configASSERT( uxCriticalNesting );
            uxCriticalNesting--;

            ಆದರೆ( uxCriticalNesting == 0 )
            {
                ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
            }
        }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ಆದರೆ( uxCriticalNesting == 0 )
        {
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS == 1 ) */
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ uxCriticalNesting;
    ಬಾಹ್ಯ pxCurrentTCB;
    ಬಾಹ್ಯ vTaskSwitchContext;

/* *INDENT-OFF* */
    PRESERVE8

    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                        /* r1 = Location where the context should be saved. */

    /*------------ Save Context. ----------- */
    mrs r3, control
    mrs r0, psp
    isb

    ಕೂಡಿಸು r0, r0, #0x20                   /* Move r0 to location where s0 is saved. */
    tst lr, #0x10
    ittt eq
    vstmiaeq r1!, {s16-s31}             /* Store s16-s31. */
    vldmiaeq r0, {s0-s16}               /* Copy hardware saved FP context into s0-s16. */
    vstmiaeq r1!, {s0-s16}              /* Store hardware saved FP context. */
    sub r0, r0, #0x20                   /* Set r0 back to the location of hardware saved context. */

    stmia r1!, {r3-r11, lr}             /* Store CONTROL register, r4-r11 and LR. */
    ldmia r0, {r4-r11}                  /* Copy hardware saved context into r4-r11. */
    stmia r1!, {r0, r4-r11}             /* Store original PSP (after hardware has saved context) and the hardware saved context. */
    str r1, [r2]                        /* Save the location from where the context should be restored as the first member of TCB. */

    /*---------- Select next task. --------- */
    mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
#ಆದರೆ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    cpsid i                             /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
#ಆದರೆ_ಅಂತ್ಯ
    msr basepri, r0
    dsb
    isb
#ಆದರೆ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    cpsie i                             /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
#ಆದರೆ_ಅಂತ್ಯ
    bl vTaskSwitchContext
    mov r0, #0
    msr basepri, r0

    /*------------ Program MPU. ------------ */
    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    ಕೂಡಿಸು r2, r2, #4                      /* r2 = Second item in the TCB which is xMPUSettings. */

    dmb                                 /* Complete outstanding transfers before disabling MPU. */
    ldr r0, =0xe000ed94                 /* MPU_CTRL register. */
    ldr r3, [r0]                        /* Read the value of MPU_CTRL. */
    bic r3, #1                          /* r3 = r3 & ~1 i.e. Clear the bit 0 in r3. */
    str r3, [r0]                        /* Disable MPU. */

    ldr r0, =0xe000ed9c                 /* Region Base Address register. */
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 0 - 3]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers [MPU Region # 0 - 3]. */

#ಆದರೆ ( config_ಒಟ್ಟು_MPU_REGIONS == 16 )
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 4 - 7]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers. [MPU Region # 4 - 7]. */
    ldmia r2!, {r4-r11}                 /* Read 4 sets of MPU registers [MPU Region # 8 - 11]. */
    stmia r0, {r4-r11}                  /* Write 4 sets of MPU registers. [MPU Region # 8 - 11]. */
#ಆದರೆ_ಅಂತ್ಯ /* configTOTAL_MPU_REGIONS == 16. */

    ldr r0, =0xe000ed94                 /* MPU_CTRL register. */
    ldr r3, [r0]                        /* Read the value of MPU_CTRL. */
    orr r3, #1                          /* r3 = r3 | 1 i.e. Set the bit 0 in r3. */
    str r3, [r0]                        /* Enable MPU. */
    dsb                                 /* Force memory writes before continuing. */

    /*---------- Restore Context. ---------- */
    ldr r3, =pxCurrentTCB               /* r3 = &( pxCurrentTCB ). */
    ldr r2, [r3]                        /* r2 = pxCurrentTCB. */
    ldr r1, [r2]                        /* r1 = Location of saved context in TCB. */

    ldmdb r1!, {r0, r4-r11}             /* r0 contains PSP after the hardware had saved context. r4-r11 contain hardware saved context. */
    msr psp, r0
    stmia r0!, {r4-r11}                 /* Copy the hardware saved context on the task stack. */
    ldmdb r1!, {r3-r11, lr}             /* r3 contains CONTROL register. r4-r11 and LR restored. */
    msr control, r3

    tst lr, #0x10
    ittt eq
    vldmdbeq r1!, {s0-s16}              /* s0-s16 contain hardware saved FP context. */
    vstmiaeq r0!, {s0-s16}              /* Copy hardware saved FP context on the task stack. */
    vldmdbeq r1!, {s16-s31}             /* Restore s16-s31. */

    str r1, [r2]                        /* Save the location where the context should be saved next as the first member of TCB. */
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ )
{
    uint32_t ulDummy;

    ulDummy = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
            /* Pend a context switch. */
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            traceISR_EXIT();
        }
    }
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak ಶೂನ್ಯ v_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Reset the SysTick. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = 0UL;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( configCPU_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK | ಪೋರ್ಟ್_NVIC_SYSTICK_INT | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE;
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_VFP( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    PRESERVE8

    ldr.w r0, =0xE000ED88 /* The FPU enable bits are in the CPACR. */
    ldr r1, [ r0 ]

    orr r1, r1, #( 0xf << 20 ) /* Enable CP10 and CP11 coprocessors, then save back. */
    str r1, [ r0 ]
    bx r14
    nop
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ uint32_t __privileged_functions_start__;
    ಬಾಹ್ಯ uint32_t __privileged_functions_end__;
    ಬಾಹ್ಯ uint32_t __FLASH_segment_start__;
    ಬಾಹ್ಯ uint32_t __FLASH_segment_end__;
    ಬಾಹ್ಯ uint32_t __privileged_data_start__;
    ಬಾಹ್ಯ uint32_t __privileged_data_end__;

    /* The only permitted number of regions are 8 or 16. */
    configASSERT( ( config_ಒಟ್ಟು_MPU_REGIONS == 8 ) || ( config_ಒಟ್ಟು_MPU_REGIONS == 16 ) );

    /* Ensure that the configTOTAL_MPU_REGIONS is configured correctly. */
    configASSERT( ಪೋರ್ಟ್_MPU_TYPE_REG == ಪೋರ್ಟ್_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ );

    /* Check the expected MPU is present. */
    ಆದರೆ( ಪೋರ್ಟ್_MPU_TYPE_REG == ಪೋರ್ಟ್_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ )
    {
        /* First setup the unprivileged flash for unprivileged read only access. */
        ಪೋರ್ಟ್_MPU_REGION_ತಳ_ವಿಳಾಸ_REG = ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                          ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
                                          ( ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION );

        ಪೋರ್ಟ್_MPU_REGION_ATTRIBUTE_REG = ( ಪೋರ್ಟ್_MPU_REGION_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_ಮುಖವಾಡ ) << ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

        /* Setup the privileged flash for privileged only access.  This is where
         * the kernel code is placed. */
        ಪೋರ್ಟ್_MPU_REGION_ತಳ_ವಿಳಾಸ_REG = ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                          ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
                                          ( ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION );

        ಪೋರ್ಟ್_MPU_REGION_ATTRIBUTE_REG = ( ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_ONLY ) |
                                       ( ( configTEX_S_C_B_FLASH & ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_ಮುಖವಾಡ ) << ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

        /* Setup the privileged data RAM region.  This is where the kernel data
         * is placed. */
        ಪೋರ್ಟ್_MPU_REGION_ತಳ_ವಿಳಾಸ_REG = ( ( uint32_t ) __privileged_data_start__ ) | /* Base address. */
                                          ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
                                          ( ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION );

        ಪೋರ್ಟ್_MPU_REGION_ATTRIBUTE_REG = ( ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
                                       ( ( configTEX_S_C_B_SRAM & ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_ಮುಖವಾಡ ) << ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_LOCATION ) |
                                       prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __privileged_data_end__ - ( uint32_t ) __privileged_data_start__ ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

        /* By default allow everything to access the general peripherals.  The
         * system peripherals and registers are protected. */
        ಪೋರ್ಟ್_MPU_REGION_ತಳ_ವಿಳಾಸ_REG = ( ಪೋರ್ಟ್_PERIPHERALS_ಆರಂಭ_ವಿಳಾಸ ) |
                                          ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
                                          ( ಪೋರ್ಟ್_GENERAL_PERIPHERALS_REGION );

        ಪೋರ್ಟ್_MPU_REGION_ATTRIBUTE_REG = ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE | ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
                                       ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ಪೋರ್ಟ್_PERIPHERALS_ಕೊನೆ_ವಿಳಾಸ - ಪೋರ್ಟ್_PERIPHERALS_ಆರಂಭ_ವಿಳಾಸ ) ) |
                                       ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

        /* Enable the memory fault exception. */
        ಪೋರ್ಟ್_NVIC_SYS_CTRL_STATE_REG |= ಪೋರ್ಟ್_NVIC_MEM_FAULT_ENABLE;

        /* Enable the MPU with the background region configured. */
        ಪೋರ್ಟ್_MPU_CTRL_REG |= ( ಪೋರ್ಟ್_MPU_ENABLE | ಪೋರ್ಟ್_MPU_BACKGROUND_ENABLE );
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint32_t prv_Get_MPURegion_ಗಾತ್ರ_Setting( uint32_t ul_Actual_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು )
{
    uint32_t ul_Region_ಗಾತ್ರ, ul_Return_ಮೌಲ್ಯ = 4;

    /* 32 is the smallest region size, 31 is the largest valid value for
     * ulReturnValue. */
    ಗಾಗಿ( ul_Region_ಗಾತ್ರ = 32UL; ul_Return_ಮೌಲ್ಯ < 31UL; ( ul_Region_ಗಾತ್ರ <<= 1UL ) )
    {
        ಆದರೆ( ul_Actual_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು <= ul_Region_ಗಾತ್ರ )
        {
            ನಿಲ್ಲಿಸು;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ul_Return_ಮೌಲ್ಯ++;
        }
    }

    /* Shift the code by one before returning so it can be written directly
     * into the correct bit position of the attribute register. */
    ಹಿಂತಿರುಗಿ( ul_Return_ಮೌಲ್ಯ << 1UL );
}
/*-----------------------------------------------------------*/

__asm ತಳ_Type_t xIsPrivileged( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, control /* r0 = CONTROL. */
    tst r0, #1      /* Perform r0 & 1 (bitwise AND) and update the conditions flag. */
    ite ne
    movne r0, #0    /* CONTROL[0]!=0. Return false to indicate that the processor is not privileged. */
    moveq r0, #1    /* CONTROL[0]==0. Return true to indicate that the processor is privileged. */
    bx lr           /* Return. */
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, control     /* r0 = CONTROL. */
    orrs r0, #1         /* r0 = r0 | 1. */
    msr control, r0     /* CONTROL = r0. */
    bx lr               /* Return. */
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Switch_ಗಮ್ಯ_User_ಬಹುಲಕ( ಶೂನ್ಯ )
{
    /* Load the current task's MPU settings from its TCB. */
    xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ );

    /* Mark the task as unprivileged. */
    xTaskMpuSettings->ulTaskFlags &= ( ~( ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) );

    /* Lower the processor's privilege level. */
    vResetPrivilege();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ )
{
    ಬಾಹ್ಯ uint32_t __SRAM_segment_start__;
    ಬಾಹ್ಯ uint32_t __SRAM_segment_end__;
    ಬಾಹ್ಯ uint32_t __privileged_data_start__;
    ಬಾಹ್ಯ uint32_t __privileged_data_end__;


    int32_t l_ಸೂಚ್ಯಂಕ;
    uint32_t ul;

    ಆದರೆ( xRegions == ಖಾಲಿ )
    {
        /* No MPU regions are specified so allow access to all RAM. */
        xMPUSettings->xRegion[ 0 ].ul_Region_ತಳ_ವಿಳಾಸ =
            ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
            ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
            ( ಪೋರ್ಟ್_ರಾಶಿ_REGION );                     /* Region number. */

        xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
            ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE ) |
            ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
            ( ( configTEX_S_C_B_SRAM & ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_ಮುಖವಾಡ ) << ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_LOCATION ) |
            ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
            ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

        xMPUSettings->xRegionSettings[ 0 ].ul_Region_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) __SRAM_segment_start__;
        xMPUSettings->xRegionSettings[ 0 ].ul_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint32_t ) __SRAM_segment_end__;
        xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                   tskMPU_WRITE_PERMISSION );

        /* Invalidate user configurable regions. */
        ಗಾಗಿ( ul = 1UL; ul <= ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul++ )
        {
            xMPUSettings->xRegion[ ul ].ul_Region_ತಳ_ವಿಳಾಸ = ( ( ul - 1UL ) | ಪೋರ್ಟ್_MPU_REGION_VALID );
            xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_ಆರಂಭ_ವಿಳಾಸ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ul_Region_ಕೊನೆ_ವಿಳಾಸ = 0UL;
            xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
        }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        /* This function is called automatically when the task is created - in
         * which case the stack region parameters will be valid.  At all other
         * times the stack parameters will not be valid and it is assumed that the
         * stack region has already been configured. */
        ಆದರೆ( ux_ರಾಶಿ_ಆಳ > 0 )
        {
            /* Define the region that allows access to the stack. */
            xMPUSettings->xRegion[ 0 ].ul_Region_ತಳ_ವಿಳಾಸ =
                ( ( uint32_t ) px_Bottom_ದ_ರಾಶಿ ) |
                ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
                ( ಪೋರ್ಟ್_ರಾಶಿ_REGION ); /* Region number. */

            xMPUSettings->xRegion[ 0 ].ulRegionAttribute =
                ( ಪೋರ್ಟ್_MPU_REGION_READ_WRITE ) |
                ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
                ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ux_ರಾಶಿ_ಆಳ * ( config_ರಾಶಿ_ಆಳ_TYPE ) ಗಾತ್ರ( ರಾಶಿ_Type_t ) ) ) |
                ( ( configTEX_S_C_B_SRAM & ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_ಮುಖವಾಡ ) << ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_LOCATION ) |
                ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

            xMPUSettings->xRegionSettings[ 0 ].ul_Region_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) px_Bottom_ದ_ರಾಶಿ;
            xMPUSettings->xRegionSettings[ 0 ].ul_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint32_t ) ( ( uint32_t ) ( px_Bottom_ದ_ರಾಶಿ ) +
                                                                                   ( ux_ರಾಶಿ_ಆಳ * ( config_ರಾಶಿ_ಆಳ_TYPE ) ಗಾತ್ರ( ರಾಶಿ_Type_t ) ) - 1UL );
            xMPUSettings->xRegionSettings[ 0 ].ulRegionPermissions = ( tskMPU_READ_PERMISSION |
                                                                       tskMPU_WRITE_PERMISSION );
        }

        l_ಸೂಚ್ಯಂಕ = 0;

        ಗಾಗಿ( ul = 1UL; ul <= ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul++ )
        {
            ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ] ).ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು > 0UL )
            {
                /* Translate the generic region definition contained in
                 * xRegions into the CM4 specific MPU settings that are then
                 * stored in xMPUSettings. */
                xMPUSettings->xRegion[ ul ].ul_Region_ತಳ_ವಿಳಾಸ =
                    ( ( uint32_t ) xRegions[ l_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ ) |
                    ( ಪೋರ್ಟ್_MPU_REGION_VALID ) |
                    ( ul - 1UL ); /* Region number. */

                xMPUSettings->xRegion[ ul ].ulRegionAttribute =
                    ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( xRegions[ l_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು ) ) |
                    ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters ) |
                    ( ಪೋರ್ಟ್_MPU_REGION_ENABLE );

                xMPUSettings->xRegionSettings[ ul ].ul_Region_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) xRegions[ l_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ಕೊನೆ_ವಿಳಾಸ = ( uint32_t ) ( ( uint32_t ) xRegions[ l_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ + xRegions[ l_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು - 1UL );
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;

                ಆದರೆ( ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & ಪೋರ್ಟ್_MPU_REGION_READ_ONLY ) == ಪೋರ್ಟ್_MPU_REGION_READ_ONLY ) ||
                    ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) == ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY ) )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = tskMPU_READ_PERMISSION;
                }

                ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters & ಪೋರ್ಟ್_MPU_REGION_READ_WRITE ) == ಪೋರ್ಟ್_MPU_REGION_READ_WRITE )
                {
                    xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = ( tskMPU_READ_PERMISSION | tskMPU_WRITE_PERMISSION );
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Invalidate the region. */
                xMPUSettings->xRegion[ ul ].ul_Region_ತಳ_ವಿಳಾಸ = ( ( ul - 1UL ) | ಪೋರ್ಟ್_MPU_REGION_VALID );
                xMPUSettings->xRegion[ ul ].ulRegionAttribute = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ಆರಂಭ_ವಿಳಾಸ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ul_Region_ಕೊನೆ_ವಿಳಾಸ = 0UL;
                xMPUSettings->xRegionSettings[ ul ].ulRegionPermissions = 0UL;
            }

            l_ಸೂಚ್ಯಂಕ++;
        }
    }
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_ಬಫರ್,
                                                size_t x_ಬಫರ್_ಉದ್ದಳತೆ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ, ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ;
        ತಳ_Type_t xAccessGranted = pdFALSE;
        ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */


        ಆದರೆ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಆದರೆ( ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( ( ( uint32_t ) pv_ಬಫರ್ ), ( ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1UL ) ) == pdFALSE )
            {
                ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) pv_ಬಫರ್;
                ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ = ( ( ( uint32_t ) pv_ಬಫರ್ ) + ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1UL );

                ಗಾಗಿ( i = 0; i < ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB; i++ )
                {
                    ಆದರೆ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ಆರಂಭ_ವಿಳಾಸ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ಕೊನೆ_ವಿಳಾಸ ) &&
                        ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ಆರಂಭ_ವಿಳಾಸ,
                                                     xTaskMpuSettings->xRegionSettings[ i ].ul_Region_ಕೊನೆ_ವಿಳಾಸ ) &&
                        ಪೋರ್ಟ್_IS_AUTHORIZED( ulAccessRequested, xTaskMpuSettings->xRegionSettings[ i ].ulRegionPermissions ) )
                    {
                        xAccessGranted = pdTRUE;
                        ನಿಲ್ಲಿಸು;
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xAccessGranted;
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/

__asm uint32_t prv_ಪೋರ್ಟ್_Get_IPSR( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, ipsr
    bx r14
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configASSERT_DEFINED == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ )
    {
        uint32_t ul_Current_ಅಡಚಣೆ;
        uint8_t uc_Current_ಆದ್ಯತೆ;

        /* Obtain the number of the currently executing interrupt. */
        ul_Current_ಅಡಚಣೆ = prv_ಪೋರ್ಟ್_Get_IPSR();

        /* Is the interrupt number a user defined interrupt? */
        ಆದರೆ( ul_Current_ಅಡಚಣೆ >= ಪೋರ್ಟ್_ಮೊದಲ_USER_ಅಡಚಣೆ_ಸಂಖ್ಯೆ )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ಆದ್ಯತೆ = pc_ಅಡಚಣೆ_ಆದ್ಯತೆ_Registers[ ul_Current_ಅಡಚಣೆ ];

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
             * Interrupts that use the FreeRTOS API must not be left at their
             * default priority of zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( uc_Current_ಆದ್ಯತೆ >= uc_Max_Sys_Call_ಆದ್ಯತೆ );
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
        configASSERT( ( ಪೋರ್ಟ್_AIRCR_REG & ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಗುಂಪು_ಮುಖವಾಡ ) <= ulMaxPRIGROUPValue );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                         int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] |= ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                          int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] &= ~( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
            ತಳ_Type_t xAccessGranted = pdFALSE;
            ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings;

            ಆದರೆ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
                ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

                ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ಆದರೆ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] & ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xAccessGranted;
        }

    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ಶೂನ್ಯ ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ಹಿಂತಿರುಗಿ pdTRUE;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
/*-----------------------------------------------------------*/
