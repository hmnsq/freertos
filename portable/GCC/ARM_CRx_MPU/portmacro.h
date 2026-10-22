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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

/* Include stdint for integer types of specific bit widths. */
#ضمن <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#که_نه_تعریف_شوی config_SYSTEM_CALL_ډېری_اندازه
    #تېروتنه "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#د_که_پای /* configSYSTEM_CALL_STACK_SIZE */

#إذا( configUSE_MPU_WRAPPERS_V1 == 1 )
    #تېروتنه This پورټ is usable with MPU wrappers V2 only.
#د_که_پای /* configUSE_MPU_WRAPPERS_V1 */

#که_نه_تعریف_شوی config_تیاری_TICK_مداخله
    #تېروتنه "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#د_که_پای /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#إذا( config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #تېروتنه "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #د_که_پای /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, ux_سر_Ready_لومړیتوب ) \
        ( ux_سر_Ready_لومړیتوب ) |= ( 1UL << ( ux_لومړیتوب ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, ux_سر_Ready_لومړیتوب ) \
        ( ux_سر_Ready_لومړیتوب ) &= ~( 1UL << ( ux_لومړیتوب ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, ux_سر_Ready_لومړیتوب ) \
        ( ux_سر_لومړیتوب ) = ( 31UL - ul_پورټ_شمېر_Leading_Zeros( ( ux_سر_Ready_لومړیتوب ) ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#ضمن "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#تعریف_کړه پورټ_THUMB_ډېرپېښ_بټ      ( ( ډېری_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#تعریف_کړه پورټ_THUMB_ډېرپېښ_پته  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
تعريفنوع uint32_t ډېری_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
تعريفنوع int32_t بنسټ_Type_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
تعريفنوع uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
تعريفنوع uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کړه پورټ_ډېری_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کړه پورټ_BYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    فراغ vFunction( فراغ * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) \
    فراغ vFunction( فراغ * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کړه پورټ_NOP()                                    __asm متطاير( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کړه پورټ_INLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کړه پورټ_حافظه_BARRIER()                         __asm متطاير( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کړه پورټ_DONT_DISCARD                             __attribute__( ( کارول_شوی ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#تعریف_کړه پورټ_TICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / config_TICK_شرح_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#تعریف_کړه پورټ_MAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
فراغ FreeRTOS_SVC_Handler( فراغ );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
فراغ FreeRTOS_IRQ_Handler( فراغ );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
فراغ v_پورټ_Yield( فراغ );

#تعریف_کړه پورټ_YIELD() v_پورټ_Yield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
فراغ v_پورټ_Enable_Interrupts( فراغ );

#تعریف_کړه پورټ_ENABLE_INTERRUPTS() v_پورټ_Enable_Interrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
فراغ v_پورټ_Disable_Interrupts( فراغ );

#تعریف_کړه پورټ_DISABLE_INTERRUPTS() v_پورټ_Disable_Interrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
فراغ v_پورټ_System_Call_Exit( فراغ );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
فراغ vMPUEnable( فراغ );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
فراغ vMPUDisable( فراغ );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
فراغ vMPUEnableBackgroundRegion( فراغ );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
فراغ vMPUDisableBackgroundRegion( فراغ );

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
فراغ vMPUSetRegion( uint32_t ul_Region_شمېره,
                    uint32_t ul_بنسټ_پته,
                    uint32_t ul_Region_اندازه,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
فراغ v_پورټ_Enter_Critical( فراغ );

#تعریف_کړه پورټ_ENTER_CRITICAL() v_پورټ_Enter_Critical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
فراغ v_پورټ_Exit_Critical( فراغ );

#تعریف_کړه پورټ_EXIT_CRITICAL() v_پورټ_Exit_Critical()

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
بنسټ_Type_t x_پورټ_Is_Privileged( فراغ );

#تعریف_کړه پورټ_IS_PRIVILEGED() x_پورټ_Is_Privileged()

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
بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ );

#تعریف_کړه پورټ_IS_TASK_PRIVILEGED() x_پورټ_Is_Task_Privileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
فراغ prvTaskExitError( فراغ );

#که_تعریف_شوی config_TASK_RETURN_پته
    #تعریف_کړه پورټ_TASK_RETURN_پته config_TASK_RETURN_پته
#وإلا
    #تعریف_کړه پورټ_TASK_RETURN_پته prvTaskExitError
#د_که_پای /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_پورټ_شمېر_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
فراغ v_پورټ_پای_ټکی_Scheduler( فراغ );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#تعریف_کړه پورټ_USING_MPU_WRAPPERS     1

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
#تعریف_کړه پورټ_PRIVILEGE_بټ          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#تعریف_کړه پورټ_ACL_ثبت_اندازه_بټونه    ( 32UL )

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
تعريفنوع بنية MPU_REGION_REGISTERS
{
    uint32_t ul_Region_اندازه;        /* Information for MPU Region Size and Enable Register. */
    uint32_t ulRegionAttribute;   /* Information for MPU Region Access Control Register. */
    uint32_t ul_Region_بنسټ_پته; /* Information for MPU Region Base Address Register. */
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
تعريفنوع بنية SYSTEM_CALL_ډېری_INFO
{
    uint32_t * pul_Task_ډېری_اشاره_ګر; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_Link_ثبتوونکی_At_System_Call_ثبت; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_ډېری_اشاره_ګر; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pul_System_Call_Exit_پته; /**< System call exit address. */
    uint32_t ul_System_Call_ډېری_بفر[ config_SYSTEM_CALL_ډېری_اندازه ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_ډېری_INFO;

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
تعريفنوع بنية MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورټ_ټول_عدد_REGIONS_دننه_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_ډېری_INFO x_System_Call_ډېری_Info;
    uint32_t ulContext[ CONTEXT_اندازه ]; /**< Buffer used to store task context. */

    #إذا( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه
                                        / پورټ_ACL_ثبت_اندازه_بټونه )
                                      + 1UL ];
    #د_که_پای
} xMPU_SETTINGS;

#که_تعریف_شوی __cplusplus
} /* extern C */
#د_که_پای

#د_که_پای /* PORTMACRO_H */
