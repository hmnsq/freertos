/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025-2026 Arm Limited and/or its affiliates
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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    size_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

#إذا !defined(__ASSEMBLER__)
    تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
    تعريفنوع پورټ_بنسټ_TYPE    بنسټ_Type_t;
    تعريفنوع uint64_t         UBaseType_t;

    تعريفنوع uint64_t         TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#د_که_پای /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH         ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT       16
#تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#إذا !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #إذا ( config_شمېره_د_CORES == 1 )
        #تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            خارجي uint64_t ull_پورټ_Yield_Required;        \
                                                        \
            إذا( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_پورټ_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #وإلا
        #تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            خارجي uint64_t ull_پورټ_Yield_Required[ config_شمېره_د_CORES ]; \
                                                                        \
            إذا( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_پورټ_Yield_Required[ پورټ_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */
#د_که_پای /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#تعریف_کړه پورټ_SVC_SYSTEM_CALL_EXIT                    104
#تعریف_کړه پورټ_SVC_YIELD                               105
#تعریف_کړه پورټ_SVC_پیل_لومړی_TASK                    106
#تعریف_کړه پورټ_SVC_DISABLE_INTERRUPTS                  107
#تعریف_کړه پورټ_SVC_ENABLE_INTERRUPTS                   108
#تعریف_کړه پورټ_SVC_GET_CORE_ID                         109
#تعریف_کړه پورټ_SVC_ماسک_ALL_INTERRUPTS                 110
#تعریف_کړه پورټ_SVC_UNMASK_ALL_INTERRUPTS               111
#تعریف_کړه پورټ_SVC_UNMASK_INTERRUPTS                   112
#تعریف_کړه پورټ_SVC_CHECK_PRIVILEGE                     113
#تعریف_کړه پورټ_SVC_SAVE_TASK_CONTEXT                   114
#تعریف_کړه پورټ_SVC_RESTORE_CONTEXT                     115
#تعریف_کړه پورټ_SVC_DELETE_CURRENT_TASK                 116
#تعریف_کړه پورټ_SVC_مداخله_CORE                      117

#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
#تعریف_کړه پورټ_YIELD()                __asm متطاير ( "SVC %0" : : "i" ( پورټ_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#إذا !defined(__ASSEMBLER__)
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخله_حالت );
    خارجي UBaseType_t ux_پورټ_سېټ_مداخله_ماسک( فراغ );
    خارجي UBaseType_t ux_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ );
    خارجي فراغ v_پورټ_Clear_مداخله_ماسک( UBaseType_t ux_New_ماسک_ارزښت );
    خارجي فراغ v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t ux_New_ماسک_ارزښت );
    خارجي فراغ v_مداخله_Core( uint32_t ul_مداخله_ID, uint8_t ucCoreID );
#د_که_پای /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS() __asm متطاير ( "SVC %0" : : "i" ( پورټ_SVC_DISABLE_INTERRUPTS ) : "memory" )

#تعریف_کړه پورټ_ENABLE_INTERRUPTS()  __asm متطاير ( "SVC %0" : : "i" ( پورټ_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کړه پورټ_UNMASK_ارزښت           ( 0xFFUL )

#إذا !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #إذا  ( config_شمېره_د_CORES == 1 )
        خارجي فراغ v_پورټ_Enter_Critical( فراغ );
        خارجي فراغ v_پورټ_Exit_Critical( فراغ );
        #تعریف_کړه پورټ_ENTER_CRITICAL()                  v_پورټ_Enter_Critical()
        #تعریف_کړه پورټ_EXIT_CRITICAL()                   v_پورټ_Exit_Critical()
    #وإلا
        #تعریف_کړه پورټ_ENTER_CRITICAL()                  vTaskEnterCritical()
        #تعریف_کړه پورټ_EXIT_CRITICAL()                   vTaskExitCritical()
    #د_که_پای
    #تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         ux_پورټ_سېټ_مداخله_ماسک_From_ISR()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    v_پورټ_Clear_مداخله_ماسک_From_ISR( x )
    #تعریف_کړه پورټ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کړه پورټ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#د_که_پای /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    فراغ FreeRTOS_Tick_Handler( فراغ );
#د_که_پای /* if !defined(__ASSEMBLER__) */

#تعریف_کړه پورټ_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#تعریف_کړه پورټ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    فراغ v_پورټ_Task_کاروي_FPU( فراغ );
#وإلا
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #تعریف_کړه v_پورټ_Task_کاروي_FPU()
#د_که_پای

#تعریف_کړه پورټ_TASK_کاروي_FLOATING_ټکی()          v_پورټ_Task_کاروي_FPU()

#تعریف_کړه پورټ_ټیټ_ترین_مداخله_لومړیتوب           ( ( ( uint32_t ) config_UNIQUE_مداخله_PRIORITIES ) - 1UL )
#تعریف_کړه پورټ_ټیټ_ترین_USABLE_مداخله_لومړیتوب    ( پورټ_ټیټ_ترین_مداخله_لومړیتوب - 1UL )

/* Architecture specific optimisations. */
#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31 - __builtin_clz( uxReadyPriorities ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ );
    #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    v_پورټ_Validate_مداخله_لومړیتوب()
#د_که_پای /* configASSERT */

#تعریف_کړه پورټ_NOP()     __asm متطاير ( "NOP" )
#تعریف_کړه پورټ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_مداخله_PRIORITIES == 16
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            4
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    3
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 32
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            3
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    2
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 64
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            2
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    1
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 128
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            1
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    0
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 256
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            0
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #تېروتنه Invalid config_UNIQUE_مداخله_PRIORITIES setting.  config_UNIQUE_مداخله_PRIORITIES must be سېټ منزل the شمېره د unique priorities implemented by the موخه hardware
#د_که_پای /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#تعریف_کړه پورټ_مداخله_لومړیتوب_ثبتوونکی_دننه_واټن    ( 0x400U )
#تعریف_کړه پورټ_YIELD_CORE_INT_ID                     ( 0x0U )
#تعریف_کړه پورټ_MAX_API_لومړیتوب_ماسک                 ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه )

#إذا ( config_شمېره_د_CORES > 1 )

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع تعداد
        {
            e_Isr_قلف = 0,
            e_Task_قلف,
            e_قلف_شمېر
        } e_پورټ_RTOSLock;

        خارجي متطاير uint64_t ullCriticalNestings[ config_شمېره_د_CORES ];
        خارجي فراغ v_پورټ_Recursive_قلف( uint8_t ucCoreID,
                                        e_پورټ_RTOSLock e_قلف_عدد,
                                        بنسټ_Type_t uxAcquire );
        خارجي uint8_t uc_پورټ_Get_Core_ID( فراغ );
        خارجي uint8_t uc_پورټ_Get_Core_IDFrom_Isr( فراغ );
    #د_که_پای /* if !defined(__ASSEMBLER__) */

    #تعریف_کړه پورټ_سېټ_مداخله_ماسک()         ux_پورټ_سېټ_مداخله_ماسک()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک( x )    v_پورټ_Clear_مداخله_ماسک( x )

    #تعریف_کړه پورټ_MAX_CORE_شمېر               config_شمېره_د_CORES
    #تعریف_کړه پورټ_GET_CORE_ID()                uc_پورټ_Get_Core_ID()
    #تعریف_کړه پورټ_GET_CORE_ID_FROM_ISR()       uc_پورټ_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #تعریف_کړه پورټ_YIELD_CORE( xCoreID )                          v_مداخله_Core( پورټ_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )                    v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Isr_قلف, pdFALSE )
    #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )                        v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Isr_قلف, pdTRUE )

    #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )                   v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Task_قلف, pdFALSE )
    #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )                       v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Task_قلف, pdTRUE )
    #تعریف_کړه پورټ_GET_CRITICAL_NESTING_شمېر( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کړه پورټ_سېټ_CRITICAL_NESTING_شمېر( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کړه پورټ_INCREMENT_CRITICAL_NESTING_شمېر( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کړه پورټ_DECREMENT_CRITICAL_NESTING_شمېر( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#د_که_پای /* configNUMBER_OF_CORES > 1 */

#تعریف_کړه پورټ_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )

    #إذا !defined(__ASSEMBLER__)
        خارجي بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ );
    #د_که_پای /* if !defined(__ASSEMBLER__) */

    /* Device memory attributes used in MAIR_EL1 registers.
     *
     * 8-bit values encoded as follows:
     *  Bit[7:4] - 0000 - Device Memory
     *  Bit[3:2] - 00 --> Device-nGnRnE
     *             01 --> Device-nGnRE
     *             10 --> Device-nGRE
     *             11 --> Device-GRE
     *  Bit[1:0] - 00.
     */
    #تعریف_کړه پورټ_MPU_DEVICE_حافظه_n_Gn_Rn_E                 ( 0x00 )
    #تعریف_کړه پورټ_MPU_DEVICE_حافظه_n_Gn_RE                  ( 0x04 )
    #تعریف_کړه پورټ_MPU_DEVICE_حافظه_n_GRE                   ( 0x08 )
    #تعریف_کړه پورټ_MPU_DEVICE_حافظه_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #که_نه_تعریف_شوی config_ټول_MPU_REGIONS
        #تعریف_کړه config_ټول_MPU_REGIONS                  ( 16UL )
    #د_که_پای

    #تعریف_کړه پورټ_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #تعریف_کړه پورټ_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #تعریف_کړه پورټ_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #تعریف_کړه پورټ_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #تعریف_کړه پورټ_ډېری_REGION                             ( 4ULL )                                /* Stack region number. */
    #تعریف_کړه پورټ_ډېری_REGION_شاخص                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #تعریف_کړه پورټ_لومړی_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #تعریف_کړه پورټ_وروستی_CONFIGURABLE_REGION                 ( config_ټول_MPU_REGIONS - 1UL )
    #تعریف_کړه پورټ_عدد_CONFIGURABLE_REGIONS                 ( ( پورټ_وروستی_CONFIGURABLE_REGION - پورټ_لومړی_CONFIGURABLE_REGION ) + 1 )
    #تعریف_کړه پورټ_ټول_عدد_REGIONS                        ( پورټ_عدد_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #تعریف_کړه پورټ_ACL_ثبت_اندازه_بټونه ( 32UL )
    #د_که_پای /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #إذا !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        تعريفنوع بنية MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #که_نه_تعریف_شوی config_SYSTEM_CALL_ډېری_اندازه
            #تعریف_کړه config_SYSTEM_CALL_ډېری_اندازه 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #د_که_پای

        /**
         * @brief System call info.
         */
        تعريفنوع بنية SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_ثبتوونکی_At_System_Call_ثبت;
            uint64_t ull_User_SPAt_System_Call_ثبت;
        } xSYSTEM_CALL_INFO;
    #د_که_پای /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #إذا ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #تعریف_کړه MAX_CONTEXT_اندازه    102

    #وإلا /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #تعریف_کړه MAX_CONTEXT_اندازه    36
    #د_که_پای /* #if ( configENABLE_FPU == 1 ) */

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع بنية MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ پورټ_ټول_عدد_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_اندازه + config_SYSTEM_CALL_ډېری_اندازه ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورټ_ACL_ثبت_اندازه_بټونه ) + 1 ];
            #د_که_پای /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #د_که_پای /* if !defined(__ASSEMBLER__) */

    #تعریف_کړه پورټ_USING_MPU_WRAPPERS                        ( 1 )
    #تعریف_کړه پورټ_PRIVILEGE_بټ                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #تعریف_کړه پورټ_MPU_نورمال_حافظه_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #تعریف_کړه پورټ_MPU_نورمال_حافظه_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR0_ماسک                   ( 0x00000000000000ffULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR1_ماسک                   ( 0x000000000000ff00ULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR2_ماسک                   ( 0x0000000000ff0000ULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR3_ماسک                   ( 0x00000000ff000000ULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR4_ماسک                   ( 0x000000ff00000000ULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR5_ماسک                   ( 0x0000ff0000000000ULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR6_ماسک                   ( 0x00ff000000000000ULL )

    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #تعریف_کړه پورټ_MPU_MAIR_EL1_ATTR7_ماسک                   ( 0xff00000000000000ULL )

    #تعریف_کړه پورټ_MPU_PRBAR_EL1_پته_ماسک                ( 0x0000FFFFFFFFFFC0ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_پته_ماسک                ( 0x0000FFFFFFFFFFC0ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_پته_IMPLIED_بټونه        ( 0x000000000000003FULL )
    #تعریف_کړه پورټ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ماسک     ( 3ULL<< 2ULL )

    #تعریف_کړه پورټ_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #تعریف_کړه پورټ_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #تعریف_کړه پورټ_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #تعریف_کړه پورټ_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #تعریف_کړه پورټ_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #تعریف_کړه پورټ_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #تعریف_کړه پورټ_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #تعریف_کړه پورټ_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #تعریف_کړه پورټ_MPU_ENABLE_بټ                            ( 1ULL << 0ULL )
    #تعریف_کړه پورټ_MPU_PRIV_BACKGROUND_ENABLE_بټ            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #تعریف_کړه پورټ_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #تعریف_کړه پورټ_جمع_کړه_UINT64_WILL_ډکېدنه( a, b )          ( ( a ) > ( پورټ_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #تعریف_کړه پورټ_ایستل_لومړی_پته_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & پورټ_MPU_PRBAR_EL1_پته_ماسک )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #تعریف_کړه پورټ_ایستل_وروستی_پته_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & پورټ_MPU_PRLAR_EL1_پته_ماسک ) | پورټ_MPU_PRLAR_EL1_پته_IMPLIED_بټونه )

    /* Does addr lies within [start, end] address range? */
    #تعریف_کړه پورټ_IS_پته_WITHIN_RANGE( addr, پیل, پای_ټکی ) \
        ( ( ( addr ) >= ( پیل ) ) && ( ( addr ) <= ( پای_ټکی ) ) )

    /* Is the access request satisfied by the available permissions? */
    #تعریف_کړه پورټ_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #إذا ( configUSE_TASK_FPU_SUPPORT == پورټ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #تعریف_کړه پورټ_دننه_واټن_منزل_PC     ( 68 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_LR     ( 70 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X0     ( 100 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X1     ( 101 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X2     ( 98 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X3     ( 99 )
    #وإلا
        #تعریف_کړه پورټ_دننه_واټن_منزل_PC     ( 2 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_LR     ( 4 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X0     ( 34 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X1     ( 35 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X2     ( 32 )
        #تعریف_کړه پورټ_دننه_واټن_منزل_X3     ( 33 )
    #د_که_پای

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #تعریف_کړه پورټ_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #تعریف_کړه پورټ_IS_TASK_PRIVILEGED() x_پورټ_Is_Task_Privileged()

#وإلا

    #تعریف_کړه پورټ_PRIVILEGE_بټ        ( 0x0UL )

#د_که_پای /* #if ( configENABLE_MPU == 1 ) */

#تعریف_کړه پورټ_PSTATE_I_بټ             ( 0x7 )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
