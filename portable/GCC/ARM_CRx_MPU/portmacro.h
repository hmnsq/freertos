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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/**
 * @brief Functions, Defines, and Structs for use in the ARM_CRx_MPU FreeRTOS-Port
 * @file portmacro.h
 * @note The settings in this file configure FreeRTOS correctly for the given
 *  hardware and compiler. These settings should not be altered.
 */

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

/* Include stdint for integer types of specific bit widths. */
#شامل <stdint.h>

/* ------------------------------ FreeRTOS Config Check ------------------------------ */

#اگر_غیر_تعریف_شدہ config_SYSTEM_CALL_ڈھیر_سائز
    #غلطی "Define configSYSTEM_CALL_STACK_SIZE to a length, in bytes, " \
            "to use when an unprivileged task makes a FreeRTOS Kernel call. "
#اگر_ختم /* configSYSTEM_CALL_STACK_SIZE */

#اگر( configUSE_MPU_WRAPPERS_V1 == 1 )
    #غلطی This پورٹ is usable with MPU wrappers V2 only.
#اگر_ختم /* configUSE_MPU_WRAPPERS_V1 */

#اگر_غیر_تعریف_شدہ config_تیاری_TICK_مداخلت
    #غلطی "configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h " \
           "to call the function that sets up the tick interrupt."
#اگر_ختم /* configSETUP_TICK_INTERRUPT */

/* ----------------------------------------------------------------------------------- */

#اگر( config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1 )

    /* Check the configuration. */
    #اگر( configMAX_PRIORITIES > 32 )
        #غلطی "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when " \
                "configMAX_PRIORITIES is less than or equal to 32. " \
                "It is very rare that a system requires more than 10 to 15 difference " \
                "priorities as tasks that share a priority will time slice."
    #اگر_ختم /* ( configMAX_PRIORITIES > 32 ) */

    /**
     * @brief Mark that a task of the given priority is ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, ux_چوٹی_Ready_ترجیح ) \
        ( ux_چوٹی_Ready_ترجیح ) |= ( 1UL << ( ux_ترجیح ) )

    /**
     * @brief Mark that a task of the given priority is no longer ready.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxPriority Priority of the task that is no longer ready.
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     */
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, ux_چوٹی_Ready_ترجیح ) \
        ( ux_چوٹی_Ready_ترجیح ) &= ~( 1UL << ( ux_ترجیح ) )

    /**
     * @brief Determine the highest priority ready task's priority.
     *
     * @ingroup Scheduler
     *
     * @param[in] uxTopReadyPriority Bitmap of the ready tasks priorities.
     * @param[in] uxTopPriority The highest priority ready task's priority.
     */
    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, ux_چوٹی_Ready_ترجیح ) \
        ( ux_چوٹی_ترجیح ) = ( 31UL - ul_پورٹ_گنتی_Leading_Zeros( ( ux_چوٹی_Ready_ترجیح ) ) )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* ------------------------------ Port Type Definitions ------------------------------ */

#شامل "portmacro_asm.h"

/**
 * @brief Critical section nesting value.
 *
 * @ingroup Critical Sections
 *
 * @note A task exits critical section and enables IRQs when its nesting count
 * reaches this value.
 */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING ( ( uint32_t ) 0x0 )

/**
 * @brief Bit in Current Program Status Register (CPSR) to indicate that CPU is
 * in Thumb State.
 *
 * @ingroup Task Context
 */
#تعریف_کرو پورٹ_THUMB_منوال_ثنائی_ہندسہ      ( ( ڈھیر_Type_t ) 0x20 )

/**
 * @brief Bitmask to check if an address is of Thumb Code.
 *
 * @ingroup Task Context
 */
#تعریف_کرو پورٹ_THUMB_منوال_پتہ  ( 0x01UL )

/**
 * @brief Data type used to represent a stack word.
 *
 * @ingroup Port Interface Specifications
 */
قسمتعریف uint32_t ڈھیر_Type_t;

/**
 * @brief Signed data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
قسمتعریف int32_t بنیاد_Type_t;

/**
 * @brief Unsigned data type equal to the data word operating size of the CPU.
 *
 * @ingroup Port Interface Specifications
 */
قسمتعریف uint32_t UBaseType_t;

/**
 * @brief Data type used for the FreeRTOS Tick Counter.
 *
 * @note Using 32-bit tick type on a 32-bit architecture ensures that reads of
 * the tick count do not need to be guarded with a critical section.
 */
قسمتعریف uint32_t TickType_t;

/**
 * @brief Marks the direction the stack grows on the targeted CPU.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کرو پورٹ_ڈھیر_GROWTH   ( -1 )

/**
 * @brief Specifies stack pointer alignment requirements of the target CPU.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT 8U

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) \
    خالی vFunction( خالی * pvParameters )

/**
 * @brief Task function prototype macro as described on FreeRTOS.org.
 *
 * @ingroup Port Interface Specifications
 *
 * @note This is not required for this port but included in case common demo
 * code uses it.
 */
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters ) \
    خالی vFunction( خالی * pvParameters )

/**
 * @brief The no-op ARM assembly instruction.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کرو پورٹ_NOP()                                    __asm متلون( "NOP" )

/**
 * @brief The inline GCC label.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کرو پورٹ_INLINE                                   __inline

/**
 * @brief The memory access synchronization barrier.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کرو پورٹ_حافظہ_BARRIER()                         __asm متلون( "" ::: "memory" )

/**
 * @brief Ensure a symbol isn't removed from the compilation unit.
 *
 * @ingroup Port Interface Specifications
 */
#تعریف_کرو پورٹ_DONT_DISCARD                             __attribute__( ( مستعمل ) )

/**
 * @brief Defines if the tick count can be accessed atomically.
 *
 * @ingroup System Clock
 */
#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC                      1

/**
 * @brief The number of milliseconds between system ticks.
 *
 * @ingroup System Clock
 */
#تعریف_کرو پورٹ_TICK_PERIOD_MS                           ( ( TickType_t ) 1000UL / config_TICK_شرح_HZ )

/**
 * @brief The largest possible delay value for any FreeRTOS API.
 *
 * @ingroup System Clock
 */
#تعریف_کرو پورٹ_MAX_DELAY                                ( TickType_t ) 0xFFFFFFFFUL

/* ----------------------------- Port Assembly Functions ----------------------------- */

/**
 * @brief FreeRTOS Supervisor Call (SVC) Handler.
 *
 * @ingroup Scheduler
 */
خالی FreeRTOS_SVC_Handler( خالی );

/**
 * @brief FreeRTOS Interrupt Handler.
 *
 * @ingroup Scheduler
 */
خالی FreeRTOS_IRQ_Handler( خالی );

/**
 * @brief Yield the CPU.
 *
 * @ingroup Scheduler
 */
خالی v_پورٹ_Yield( خالی );

#تعریف_کرو پورٹ_YIELD() v_پورٹ_Yield()

/**
 * @brief Enable interrupts.
 *
 * @ingroup Interrupt Management
 */
خالی v_پورٹ_Enable_Interrupts( خالی );

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS() v_پورٹ_Enable_Interrupts()

/**
 * @brief Disable interrupts.
 *
 * @ingroup Interrupt Management
 */
خالی v_پورٹ_Disable_Interrupts( خالی );

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS() v_پورٹ_Disable_Interrupts()

/**
 * @brief Exit from a FreeRTO System Call.
 *
 * @ingroup Port Privilege
 */
خالی v_پورٹ_System_Call_Exit( خالی );

/**
 * @brief Start executing first task.
 *
 * @ingroup Scheduler
 */
خالی v_پورٹ_آغاز_پہلا_Task( خالی );

/**
 * @brief Enable the onboard MPU.
 *
 * @ingroup MPU Control
 */
خالی vMPUEnable( خالی );

/**
 * @brief Disable the onboard MPU.
 *
 * @ingroup MPU Control
 */
خالی vMPUDisable( خالی );

/**
 * @brief Enable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
خالی vMPUEnableBackgroundRegion( خالی );

/**
 * @brief Disable the MPU Background Region.
 *
 * @ingroup MPU Control
 */
خالی vMPUDisableBackgroundRegion( خالی );

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
خالی vMPUSetRegion( uint32_t ul_Region_نمبر,
                    uint32_t ul_بنیاد_پتہ,
                    uint32_t ul_Region_سائز,
                    uint32_t ulRegionPermissions );

/* ------------------------------- Port.c Declarations ------------------------------- */

/**
 * @brief Enter critical section.
 *
 * @ingroup Critical Section
 */
خالی v_پورٹ_Enter_Critical( خالی );

#تعریف_کرو پورٹ_ENTER_CRITICAL() v_پورٹ_Enter_Critical()

/**
 * @brief Exit critical section.
 *
 * @ingroup Critical Section
 */
خالی v_پورٹ_Exit_Critical( خالی );

#تعریف_کرو پورٹ_EXIT_CRITICAL() v_پورٹ_Exit_Critical()

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
بنیاد_Type_t x_پورٹ_Is_Privileged( خالی );

#تعریف_کرو پورٹ_IS_PRIVILEGED() x_پورٹ_Is_Privileged()

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
بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی );

#تعریف_کرو پورٹ_IS_TASK_PRIVILEGED() x_پورٹ_Is_Task_Privileged()

/**
 * @brief Default return address for tasks.
 *
 * @ingroup Task Context
 *
 * @note This function is used as the default return address for tasks if
 * configTASK_RETURN_ADDRESS is not defined in FreeRTOSConfig.h.
 */
خالی prvTaskExitError( خالی );

#اگر_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ config_TASK_RETURN_پتہ
#ورنہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ prvTaskExitError
#اگر_ختم /* configTASK_RETURN_ADDRESS */

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_پورٹ_گنتی_Leading_Zeros( UBaseType_t ulBitmap );

/**
 * @brief End the FreeRTOS scheduler.
 *
 * Not implemented on this port.
 *
 * @ingroup Scheduler
 */
خالی v_پورٹ_انتہا_Scheduler( خالی );

/* --------------------------------- MPU Definitions --------------------------------- */

/**
 * @brief Mark that this port utilizes the onboard ARM MPU.
 *
 * @ingroup MPU Control
 */
#تعریف_کرو پورٹ_USING_MPU_WRAPPERS     1

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
#تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ          ( 0x80000000UL )

/**
 * @brief Size of an Access Control List (ACL) entry in bits.
 */
#تعریف_کرو پورٹ_ACL_اندراج_سائز_بٹ    ( 32UL )

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
قسمتعریف ساخت MPU_REGION_REGISTERS
{
    uint32_t ul_Region_سائز;        /* Information for MPU Region Size and Enable Register. */
    uint32_t ulRegionAttribute;   /* Information for MPU Region Access Control Register. */
    uint32_t ul_Region_بنیاد_پتہ; /* Information for MPU Region Base Address Register. */
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
قسمتعریف ساخت SYSTEM_CALL_ڈھیر_INFO
{
    uint32_t * pul_Task_ڈھیر_اشارہ_گر; /**< Stack Pointer of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_Link_رجسٹر_At_System_Call_اندراج; /**< Link Register of the task when it made a FreeRTOS System Call. */
    uint32_t * pul_System_Call_ڈھیر_اشارہ_گر; /**< Stack Pointer to use for executing a FreeRTOS System Call. */
    uint32_t * pul_System_Call_Exit_پتہ; /**< System call exit address. */
    uint32_t ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_سائز ]; /**< Buffer to be used as stack when performing a FreeRTOS System Call. */
} x_SYSTEM_CALL_ڈھیر_INFO;

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
قسمتعریف ساخت MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورٹ_کل_عدد_REGIONS_اندر_TCB ];
    uint32_t ulTaskFlags;
    x_SYSTEM_CALL_ڈھیر_INFO x_System_Call_ڈھیر_Info;
    uint32_t ulContext[ CONTEXT_سائز ]; /**< Buffer used to store task context. */

    #اگر( configENABLE_ACCESS_CONTROL_LIST == 1 )
        uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائز
                                        / پورٹ_ACL_اندراج_سائز_بٹ )
                                      + 1UL ];
    #اگر_ختم
} xMPU_SETTINGS;

#اگر_تعریف_شدہ __cplusplus
} /* extern C */
#اگر_ختم

#اگر_ختم /* PORTMACRO_H */
