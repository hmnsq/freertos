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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#ifdef __cplusplus
বাহ্য "C" {
#endif

/* Include stdint for integer types of specific bit widths. */
#অন্তর্ভাব <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#ifndef config_SYSTEM_CALL_স্তূপ_SIZE
    #error "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#endif /* configSYSTEM_CALL_STACK_SIZE */

#যদি( configUSE_MPU_WRAPPERS_V1 == 1 )
    #error This port is usable with MPU wrappers V2 only.
#endif /* configUSE_MPU_WRAPPERS_V1 */

#ifndef configSETUP_TICK_INTERRUPT
    #error "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#endif /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#যদি( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #যদি( configMAX_PRIORITIES > 32 )
        #error "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #endif /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #define portRECORD_READY_PRIORITY( uxPriority, ux_শীর্ষ_Ready_Priority ) \
        ( ux_শীর্ষ_Ready_Priority ) |= ( 1UL << ( uxPriority ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #define portRESET_READY_PRIORITY( uxPriority, ux_শীর্ষ_Ready_Priority ) \
        ( ux_শীর্ষ_Ready_Priority ) &= ~( 1UL << ( uxPriority ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #define portGET_HIGHEST_PRIORITY( ux_শীর্ষ_Priority, ux_শীর্ষ_Ready_Priority ) \
        ( ux_শীর্ষ_Priority ) = ( 31UL - ul_Port_গুনতি_Leading_Zeros( ( ux_শীর্ষ_Ready_Priority ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#অন্তর্ভাব "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#define portNO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#define portTHUMB_MODE_BIT      ( ( স্তূপ_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#define portTHUMB_MODE_ADDRESS  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
প্রকারনির্দেশ uint32_t স্তূপ_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
প্রকারনির্দেশ int32_t BaseType_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
প্রকারনির্দেশ uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
প্রকারনির্দেশ uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#define port_স্তূপ_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#define portBYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    শূন্য vFunction( শূন্য * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#define portTASK_FUNCTION( vFunction, pvParameters ) \
    শূন্য vFunction( শূন্য * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#define portNOP()                                    __asm চঞ্চল( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#define portINLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#define portMEMORY_BARRIER()                         __asm চঞ্চল( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#define portDONT_DISCARD                             __attribute__( ( used ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#define portTICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#define portTICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / configTICK_RATE_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#define portMAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
শূন্য FreeRTOS_SVC_Handler( শূন্য );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
শূন্য FreeRTOS_IRQ_Handler( শূন্য );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
শূন্য vPortYield( শূন্য );

#define portYIELD() vPortYield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
শূন্য vPortEnableInterrupts( শূন্য );

#define portENABLE_INTERRUPTS() vPortEnableInterrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
শূন্য vPortDisableInterrupts( শূন্য );

#define portDISABLE_INTERRUPTS() vPortDisableInterrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
শূন্য vPortSystemCallExit( শূন্য );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
শূন্য vPortStartFirstTask( শূন্য );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
শূন্য vMPUEnable( শূন্য );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
শূন্য vMPUDisable( শূন্য );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
শূন্য vMPUEnableBackgroundRegion( শূন্য );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
শূন্য vMPUDisableBackgroundRegion( শূন্য );

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
শূন্য vMPUSetRegion( uint32_t ul_Region_সংখ্যা,
                    uint32_t ulBaseAddress,
                    uint32_t ulRegionSize,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
শূন্য vPortEnterCritical( শূন্য );

#define portENTER_CRITICAL() vPortEnterCritical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
শূন্য vPortExitCritical( শূন্য );

#define portEXIT_CRITICAL() vPortExitCritical()

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
BaseType_t xPortIsPrivileged( শূন্য );

#define portIS_PRIVILEGED() xPortIsPrivileged()

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
BaseType_t xPortIsTaskPrivileged( শূন্য );

#define portIS_TASK_PRIVILEGED() xPortIsTaskPrivileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
শূন্য prvTaskExitError( শূন্য );

#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS configTASK_RETURN_ADDRESS
#অন্যথা
    #define portTASK_RETURN_ADDRESS prvTaskExitError
#endif /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_Port_গুনতি_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
শূন্য vPortEndScheduler( শূন্য );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#define portUSING_MPU_WRAPPERS     1

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
#define portPRIVILEGE_BIT          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#define portACL_ENTRY_SIZE_BITS    ( 32UL )

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
প্রকারনির্দেশ সংরচনা MPU_REGION_REGISTERS
{
    uint32_t ulRegionSize;        /* Information for MPU Region Size and Enable Register. */
    uint32_t ulRegionAttribute;   /* Information for MPU Region Access Control Register. */
    uint32_t ulRegionBaseAddress; /* Information for MPU Region Base Address Register. */
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
প্রকারনির্দেশ সংরচনা SYSTEM_CALL_স্তূপ_INFO
{
    uint32_t * pul_Task_স্তূপ_Pointer; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pulLinkRegisterAtSystemCallEntry; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_স্তূপ_Pointer; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pulSystemCallExitAddress; /**< System call exit address. */
    uint32_t ul_System_Call_স্তূপ_Buffer[ config_SYSTEM_CALL_স্তূপ_SIZE ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_স্তূপ_INFO;

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
প্রকারনির্দেশ সংরচনা MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ port_TOTAL_অঙ্ক_REGIONS_IN_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_স্তূপ_INFO x_System_Call_স্তূপ_Info;
    uint32_t ulContext[ CONTEXT_SIZE ]; /**< Buffer used to store task context. */

    #যদি( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( configPROTECTED_KERNEL_OBJECT_POOL_SIZE
                                        / portACL_ENTRY_SIZE_BITS )
                                      + 1UL ];
    #endif
} xMPU_SETTINGS;

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* PORTMACRO_H */
