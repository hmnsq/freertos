/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

/* Include stdint for integer types of specific bit widths. */
#ಅನ್ತರ್ಭಾವ <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ
    #ದೋಷ "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#ಆದರೆ_ಅಂತ್ಯ /* configSYSTEM_CALL_STACK_SIZE */

#ಆದರೆ( configUSE_MPU_WRAPPERS_V1 == 1 )
    #ದೋಷ This ಪೋರ್ಟ್ is usable with MPU wrappers V2 only.
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ
    #ದೋಷ "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#ಆದರೆ_ಅಂತ್ಯ /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#ಆದರೆ( config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #ಆದರೆ( configMAX_PRIORITIES > 32 )
        #ದೋಷ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #ಆದರೆ_ಅಂತ್ಯ /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) \
        ( ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) \
        ( ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) \
        ( ux_ತುದಿ_ಆದ್ಯತೆ ) = ( 31UL - ul_ಪೋರ್ಟ್_ಎಣಿಕೆ_Leading_Zeros( ( ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#ಅನ್ತರ್ಭಾವ "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್      ( ( ರಾಶಿ_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t ರಾಶಿ_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t ತಳ_Type_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters ) \
    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()                                    __asm ಅಸ್ಥಿರ( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()                         __asm ಅಸ್ಥಿರ( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DONT_DISCARD                             __attribute__( ( ಬಳಸಿದ ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / config_TICK_ದರ_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
ಶೂನ್ಯ FreeRTOS_SVC_Handler( ಶೂನ್ಯ );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
ಶೂನ್ಯ FreeRTOS_IRQ_Handler( ಶೂನ್ಯ );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD() v_ಪೋರ್ಟ್_Yield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_Interrupts( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS() v_ಪೋರ್ಟ್_Enable_Interrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Disable_Interrupts( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS() v_ಪೋರ್ಟ್_Disable_Interrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_System_Call_Exit( ಶೂನ್ಯ );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
ಶೂನ್ಯ vMPUEnable( ಶೂನ್ಯ );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
ಶೂನ್ಯ vMPUDisable( ಶೂನ್ಯ );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
ಶೂನ್ಯ vMPUEnableBackgroundRegion( ಶೂನ್ಯ );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
ಶೂನ್ಯ vMPUDisableBackgroundRegion( ಶೂನ್ಯ );

/**
 * @brief Set permissions for an MPU Region.
 *
 * @ingroup MPU Control
 *
 * @param[in] ulRegionNumber The MPU Region Number to set permissions for.
 * @param[in] ulBaseAddress The base address of the MPU Region.
 * @param[in] ulRegionSize The size of the MPU Region in bytes.
 * @param[in] ulRegionPermissions The permissions associated with the MPU Region.
 *
 * @note This is an internal function and assumes that the inputs to this
 * function are checked before calling this function.
 */
ಶೂನ್ಯ vMPUSetRegion( uint32_t ul_Region_ಸಂಖ್ಯೆ,
                    uint32_t ul_ತಳ_ವಿಳಾಸ,
                    uint32_t ul_Region_ಗಾತ್ರ,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL() v_ಪೋರ್ಟ್_Enter_Critical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL() v_ಪೋರ್ಟ್_Exit_Critical()

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @ingroup Port Privilege
 *
 * @note The processor privilege level is determined by checking the
 * mode bits [4:0] of the Current Program Status Register (CPSR).
 *
 * @return pdTRUE, if the processor is privileged, pdFALSE otherwise.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Privileged( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_PRIVILEGED() x_ಪೋರ್ಟ್_Is_Privileged()

/**
 * @brief Checks whether or not a task is privileged.
 *
 * @ingroup Port Privilege
 *
 * @note A task's privilege level is associated with the task and is different from
 * the processor's privilege level returned by xPortIsPrivileged. For example,
 * the processor is privileged when an unprivileged task executes a system call.
 *
 * @return pdTRUE if the task is privileged, pdFALSE otherwise.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_TASK_PRIVILEGED() x_ಪೋರ್ಟ್_Is_Task_Privileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_ಪೋರ್ಟ್_ಎಣಿಕೆ_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USING_MPU_WRAPPERS     1

/**
 * @brief Used to mark if a task should be created as a privileged task.
 *
 * @ingroup Task Context
 * @ingroup MPU Control
 *
 * @note A privileged task is created by performing a bitwise OR of this value and
 * the task priority. For example, to create a privileged task at priority 2, the
 * uxPriority parameter should be set to ( 2 | portPRIVILEGE_BIT ).
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು    ( 32UL )

/**
 * @brief Structure to hold the MPU Register Values.
 *
 * @struct xMPU_REGION_REGISTERS
 *
 * @ingroup MPU Control
 *
 * @note The ordering of this struct MUST be in sync with the ordering in
 * portRESTORE_CONTEXT.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_REGION_REGISTERS
{
    uint32_t ul_Region_ಗಾತ್ರ;        /* Information for MPU Region Size and Enable Register. */
    uint32_t ulRegionAttribute;   /* Information for MPU Region Access Control Register. */
    uint32_t ul_Region_ತಳ_ವಿಳಾಸ; /* Information for MPU Region Base Address Register. */
} xMPU_REGION_REGISTERS;

/**
 * @brief Structure to hold per-task System Call Stack information.
 *
 * @struct xSYSTEM_CALL_STACK_INFO
 *
 * @ingroup Port Privilege
 *
 * @note The ordering of this structure MUST be in sync with the assembly code
 * of the port.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SYSTEM_CALL_ರಾಶಿ_INFO
{
    uint32_t * pul_Task_ರಾಶಿ_ಸೂಚಕ; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_ರಾಶಿ_ಸೂಚಕ; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pul_System_Call_Exit_ವಿಳಾಸ; /**< System call exit address. */
    uint32_t ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_ರಾಶಿ_INFO;

/**
 * @brief Per-Task MPU settings structure stored in the TCB.
 * @struct xMPU_SETTINGS
 *
 * @ingroup MPU Control
 * @ingroup Task Context
 * @ingroup Port Privilege
 *
 * @note The ordering of this structure MUST be in sync with the assembly code
 * of the port.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_ರಾಶಿ_INFO x_System_Call_ರಾಶಿ_Info;
    uint32_t ulContext[ CONTEXT_ಗಾತ್ರ ]; /**< Buffer used to store task context. */

    #ಆದರೆ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ
                                        / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು )
                                      + 1UL ];
    #ಆದರೆ_ಅಂತ್ಯ
} xMPU_SETTINGS;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
} /* extern C */
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
