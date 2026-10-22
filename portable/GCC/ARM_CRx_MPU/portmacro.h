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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

/* Include stdint for integer types of specific bit widths. */
#అన్తర్భావ <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#నిర్వచితం_కాకపోతే config_SYSTEM_CALL_దొంతర_కొలత
    #దోషం "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#అయితే_ముగింపు /* configSYSTEM_CALL_STACK_SIZE */

#ఒకవేళ( configUSE_MPU_WRAPPERS_V1 == 1 )
    #దోషం This పోర్టు is usable with MPU wrappers V2 only.
#అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 */

#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం
    #దోషం "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#ఒకవేళ( config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #ఒకవేళ( configMAX_PRIORITIES > 32 )
        #దోషం "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #అయితే_ముగింపు /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, ux_శిఖరం_Ready_ప్రాధాన్యత ) \
        ( ux_శిఖరం_Ready_ప్రాధాన్యత ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, ux_శిఖరం_Ready_ప్రాధాన్యత ) \
        ( ux_శిఖరం_Ready_ప్రాధాన్యత ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, ux_శిఖరం_Ready_ప్రాధాన్యత ) \
        ( ux_శిఖరం_ప్రాధాన్యత ) = ( 31UL - ul_పోర్టు_లెక్క_Leading_Zeros( ( ux_శిఖరం_Ready_ప్రాధాన్యత ) ) )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#అన్తర్భావ "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు      ( ( దొంతర_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_చిరునామా  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
రకనిర్వచనం uint32_t దొంతర_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
రకనిర్వచనం int32_t పునాది_Type_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
రకనిర్వచనం uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
రకనిర్వచనం uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#నిర్వచించు పోర్టు_దొంతర_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    శూన్య vFunction( శూన్య * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters ) \
    శూన్య vFunction( శూన్య * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#నిర్వచించు పోర్టు_NOP()                                    __asm అస్థిర( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#నిర్వచించు పోర్టు_INLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()                         __asm అస్థిర( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#నిర్వచించు పోర్టు_DONT_DISCARD                             __attribute__( ( వాడిన ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#నిర్వచించు పోర్టు_TICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / config_TICK_రేటు_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#నిర్వచించు పోర్టు_MAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
శూన్య FreeRTOS_SVC_Handler( శూన్య );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
శూన్య FreeRTOS_IRQ_Handler( శూన్య );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
శూన్య v_పోర్టు_Yield( శూన్య );

#నిర్వచించు పోర్టు_YIELD() v_పోర్టు_Yield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
శూన్య v_పోర్టు_Enable_Interrupts( శూన్య );

#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS() v_పోర్టు_Enable_Interrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
శూన్య v_పోర్టు_Disable_Interrupts( శూన్య );

#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS() v_పోర్టు_Disable_Interrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
శూన్య v_పోర్టు_System_Call_Exit( శూన్య );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
శూన్య vMPUEnable( శూన్య );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
శూన్య vMPUDisable( శూన్య );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
శూన్య vMPUEnableBackgroundRegion( శూన్య );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
శూన్య vMPUDisableBackgroundRegion( శూన్య );

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
శూన్య vMPUSetRegion( uint32_t ul_Region_సంఖ్య,
                    uint32_t ul_పునాది_చిరునామా,
                    uint32_t ul_Region_కొలత,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
శూన్య v_పోర్టు_Enter_Critical( శూన్య );

#నిర్వచించు పోర్టు_ENTER_CRITICAL() v_పోర్టు_Enter_Critical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
శూన్య v_పోర్టు_Exit_Critical( శూన్య );

#నిర్వచించు పోర్టు_EXIT_CRITICAL() v_పోర్టు_Exit_Critical()

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
పునాది_Type_t x_పోర్టు_Is_Privileged( శూన్య );

#నిర్వచించు పోర్టు_IS_PRIVILEGED() x_పోర్టు_Is_Privileged()

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
పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య );

#నిర్వచించు పోర్టు_IS_TASK_PRIVILEGED() x_పోర్టు_Is_Task_Privileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
శూన్య prvTaskExitError( శూన్య );

#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా prvTaskExitError
#అయితే_ముగింపు /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_పోర్టు_లెక్క_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
శూన్య v_పోర్టు_చివర_Scheduler( శూన్య );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#నిర్వచించు పోర్టు_USING_MPU_WRAPPERS     1

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
#నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#నిర్వచించు పోర్టు_ACL_నమోదు_కొలత_బిట్లు    ( 32UL )

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
రకనిర్వచనం నిర్మాణం MPU_REGION_REGISTERS
{
    uint32_t ul_Region_కొలత;        /* Information for MPU Region Size and Enable Register. */
    uint32_t ulRegionAttribute;   /* Information for MPU Region Access Control Register. */
    uint32_t ul_Region_పునాది_చిరునామా; /* Information for MPU Region Base Address Register. */
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
రకనిర్వచనం నిర్మాణం SYSTEM_CALL_దొంతర_INFO
{
    uint32_t * pul_Task_దొంతర_సూచిక; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_Link_రిజిస్టరు_At_System_Call_నమోదు; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_దొంతర_సూచిక; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pul_System_Call_Exit_చిరునామా; /**< System call exit address. */
    uint32_t ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_దొంతర_INFO;

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
రకనిర్వచనం నిర్మాణం MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ పోర్టు_మొత్తం_అంకె_REGIONS_లోపల_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_దొంతర_INFO x_System_Call_దొంతర_Info;
    uint32_t ulContext[ CONTEXT_కొలత ]; /**< Buffer used to store task context. */

    #ఒకవేళ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_కొలత
                                        / పోర్టు_ACL_నమోదు_కొలత_బిట్లు )
                                      + 1UL ];
    #అయితే_ముగింపు
} xMPU_SETTINGS;

#నిర్వచితమైతే __cplusplus
} /* extern C */
#అయితే_ముగింపు

#అయితే_ముగింపు /* PORTMACRO_H */
