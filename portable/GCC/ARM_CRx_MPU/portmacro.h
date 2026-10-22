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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

/* Include stdint for integer types of specific bit widths. */
#समावेश <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#अगर_अघोषित config_SYSTEM_CALL_ढेर_आकार
    #त्रुटि "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#पूर्ण_अगर /* configSYSTEM_CALL_STACK_SIZE */

#अगर( configUSE_MPU_WRAPPERS_V1 == 1 )
    #त्रुटि This port is usable with MPU wrappers V2 only.
#पूर्ण_अगर /* configUSE_MPU_WRAPPERS_V1 */

#अगर_अघोषित configSETUP_TICK_INTERRUPT
    #त्रुटि "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#पूर्ण_अगर /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#अगर( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #अगर( configMAX_PRIORITIES > 32 )
        #त्रुटि "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #पूर्ण_अगर /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, ux_शीर्ष_Ready_Priority ) \
        ( ux_शीर्ष_Ready_Priority ) |= ( 1UL << ( uxPriority ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #घोषणा portRESET_READY_PRIORITY( uxPriority, ux_शीर्ष_Ready_Priority ) \
        ( ux_शीर्ष_Ready_Priority ) &= ~( 1UL << ( uxPriority ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, ux_शीर्ष_Ready_Priority ) \
        ( ux_शीर्ष_Priority ) = ( 31UL - ul_Port_गिनती_Leading_Zeros( ( ux_शीर्ष_Ready_Priority ) ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#समावेश "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#घोषणा portNO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#घोषणा portTHUMB_MODE_BIT      ( ( ढेर_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#घोषणा portTHUMB_MODE_ADDRESS  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
प्रकार uint32_t ढेर_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
प्रकार int32_t BaseType_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
प्रकार uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
प्रकार uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#घोषणा port_ढेर_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#घोषणा portBYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    व्योम vFunction( व्योम * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#घोषणा portTASK_FUNCTION( vFunction, pvParameters ) \
    व्योम vFunction( व्योम * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#घोषणा portNOP()                                    __asm अस्थिर( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#घोषणा portINLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#घोषणा portMEMORY_BARRIER()                         __asm अस्थिर( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#घोषणा portDONT_DISCARD                             __attribute__( ( used ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#घोषणा portTICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#घोषणा portTICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / configTICK_RATE_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#घोषणा portMAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
व्योम FreeRTOS_SVC_Handler( व्योम );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
व्योम FreeRTOS_IRQ_Handler( व्योम );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
व्योम vPortYield( व्योम );

#घोषणा portYIELD() vPortYield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
व्योम vPortEnableInterrupts( व्योम );

#घोषणा portENABLE_INTERRUPTS() vPortEnableInterrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
व्योम vPortDisableInterrupts( व्योम );

#घोषणा portDISABLE_INTERRUPTS() vPortDisableInterrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
व्योम vPortSystemCallExit( व्योम );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
व्योम vPortStartFirstTask( व्योम );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
व्योम vMPUEnable( व्योम );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
व्योम vMPUDisable( व्योम );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
व्योम vMPUEnableBackgroundRegion( व्योम );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
व्योम vMPUDisableBackgroundRegion( व्योम );

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
व्योम vMPUSetRegion( uint32_t ul_Region_संख्या,
                    uint32_t ulBaseAddress,
                    uint32_t ul_Region_आकार,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
व्योम vPortEnterCritical( व्योम );

#घोषणा portENTER_CRITICAL() vPortEnterCritical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
व्योम vPortExitCritical( व्योम );

#घोषणा portEXIT_CRITICAL() vPortExitCritical()

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
BaseType_t xPortIsPrivileged( व्योम );

#घोषणा portIS_PRIVILEGED() xPortIsPrivileged()

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
BaseType_t xPortIsTaskPrivileged( व्योम );

#घोषणा portIS_TASK_PRIVILEGED() xPortIsTaskPrivileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
व्योम prvTaskExitError( व्योम );

#अगर_घोषित configTASK_RETURN_ADDRESS
    #घोषणा portTASK_RETURN_ADDRESS configTASK_RETURN_ADDRESS
#अन्यथा
    #घोषणा portTASK_RETURN_ADDRESS prvTaskExitError
#पूर्ण_अगर /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_Port_गिनती_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
व्योम vPortEndScheduler( व्योम );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#घोषणा portUSING_MPU_WRAPPERS     1

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
#घोषणा portPRIVILEGE_BIT          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#घोषणा port_ACL_ENTRY_आकार_BITS    ( 32UL )

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
प्रकार काष्ठा MPU_REGION_REGISTERS
{
    uint32_t ul_Region_आकार;        /* Information for MPU Region Size and Enable Register. */
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
प्रकार काष्ठा SYSTEM_CALL_ढेर_INFO
{
    uint32_t * pul_Task_ढेर_Pointer; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pulLinkRegisterAtSystemCallEntry; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_ढेर_Pointer; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pulSystemCallExitAddress; /**< System call exit address. */
    uint32_t ul_System_Call_ढेर_बफर[ config_SYSTEM_CALL_ढेर_आकार ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_ढेर_INFO;

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
प्रकार काष्ठा MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ port_योग_अंक_REGIONS_IN_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_ढेर_INFO x_System_Call_ढेर_Info;
    uint32_t ulContext[ CONTEXT_आकार ]; /**< Buffer used to store task context. */

    #अगर( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार
                                        / port_ACL_ENTRY_आकार_BITS )
                                      + 1UL ];
    #पूर्ण_अगर
} xMPU_SETTINGS;

#अगर_घोषित __cplusplus
} /* extern C */
#पूर्ण_अगर

#पूर्ण_अगर /* PORTMACRO_H */
