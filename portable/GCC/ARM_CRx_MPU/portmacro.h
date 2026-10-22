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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/* Include stdint for integer types of specific bit widths. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ
    #ਗਲਤੀ "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#ਜੇ_ਅੰਤ /* configSYSTEM_CALL_STACK_SIZE */

#ਜੇ( configUSE_MPU_WRAPPERS_V1 == 1 )
    #ਗਲਤੀ This ਪੋਰਟ is usable with MPU wrappers V2 only.
#ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#ਜੇ_ਅੰਤ /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#ਜੇ( config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #ਜੇ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #ਜੇ_ਅੰਤ /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, ux_ਸਿਖਰ_Ready_ਤਰਜੀਹ ) \
        ( ux_ਸਿਖਰ_Ready_ਤਰਜੀਹ ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, ux_ਸਿਖਰ_Ready_ਤਰਜੀਹ ) \
        ( ux_ਸਿਖਰ_Ready_ਤਰਜੀਹ ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, ux_ਸਿਖਰ_Ready_ਤਰਜੀਹ ) \
        ( ux_ਸਿਖਰ_ਤਰਜੀਹ ) = ( 31UL - ul_ਪੋਰਟ_ਗਿਣਤੀ_Leading_Zeros( ( ux_ਸਿਖਰ_Ready_ਤਰਜੀਹ ) ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#ਅਨ੍ਤਰ੍ਭਾਵ "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ      ( ( ਢੇਰ_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਪਤਾ  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t ਢੇਰ_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t ਅਧਾਰ_Type_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters ) \
    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()                                    __asm ਅਸਥਿਰ( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()                         __asm ਅਸਥਿਰ( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DONT_DISCARD                             __attribute__( ( ਵਰਤਿਆ ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / config_TICK_ਦਰ_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
ਖਾਲੀ FreeRTOS_SVC_Handler( ਖਾਲੀ );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
ਖਾਲੀ FreeRTOS_IRQ_Handler( ਖਾਲੀ );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD() v_ਪੋਰਟ_Yield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
ਖਾਲੀ v_ਪੋਰਟ_Enable_Interrupts( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS() v_ਪੋਰਟ_Enable_Interrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
ਖਾਲੀ v_ਪੋਰਟ_Disable_Interrupts( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS() v_ਪੋਰਟ_Disable_Interrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
ਖਾਲੀ v_ਪੋਰਟ_System_Call_Exit( ਖਾਲੀ );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
ਖਾਲੀ vMPUEnable( ਖਾਲੀ );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
ਖਾਲੀ vMPUDisable( ਖਾਲੀ );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
ਖਾਲੀ vMPUEnableBackgroundRegion( ਖਾਲੀ );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
ਖਾਲੀ vMPUDisableBackgroundRegion( ਖਾਲੀ );

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
ਖਾਲੀ vMPUSetRegion( uint32_t ul_Region_ਸੰਖਿਆ,
                    uint32_t ul_ਅਧਾਰ_ਪਤਾ,
                    uint32_t ul_Region_ਮਾਪ,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL() v_ਪੋਰਟ_Enter_Critical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL() v_ਪੋਰਟ_Exit_Critical()

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
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Privileged( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_PRIVILEGED() x_ਪੋਰਟ_Is_Privileged()

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
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_TASK_PRIVILEGED() x_ਪੋਰਟ_Is_Task_Privileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ prvTaskExitError
#ਜੇ_ਅੰਤ /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_ਪੋਰਟ_ਗਿਣਤੀ_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS     1

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ    ( 32UL )

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
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_REGION_REGISTERS
{
    uint32_t ul_Region_ਮਾਪ;        /* Information for MPU Region Size and Enable Register. */
    uint32_t ulRegionAttribute;   /* Information for MPU Region Access Control Register. */
    uint32_t ul_Region_ਅਧਾਰ_ਪਤਾ; /* Information for MPU Region Base Address Register. */
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
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SYSTEM_CALL_ਢੇਰ_INFO
{
    uint32_t * pul_Task_ਢੇਰ_ਸੂਚਕ; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_ਢੇਰ_ਸੂਚਕ; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pul_System_Call_Exit_ਪਤਾ; /**< System call exit address. */
    uint32_t ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_ਢੇਰ_INFO;

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
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_ਢੇਰ_INFO x_System_Call_ਢੇਰ_Info;
    uint32_t ulContext[ CONTEXT_ਮਾਪ ]; /**< Buffer used to store task context. */

    #ਜੇ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ
                                        / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ )
                                      + 1UL ];
    #ਜੇ_ਅੰਤ
} xMPU_SETTINGS;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
} /* extern C */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
