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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    size_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

#إذا !defined(__ASSEMBLER__)
    تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    تعريفنوع پورٹ_ادھار_TYPE    ادھار_Type_t;
    تعريفنوع uint64_t         UBaseType_t;

    تعريفنوع uint64_t         TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#جے_انت /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH         ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT       16
#تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#إذا !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #إذا ( config_نمبر_دا_CORES == 1 )
        #تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            خارجي uint64_t ull_پورٹ_Yield_Required;        \
                                                        \
            إذا( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_پورٹ_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #وإلا
        #تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            خارجي uint64_t ull_پورٹ_Yield_Required[ config_نمبر_دا_CORES ]; \
                                                                        \
            إذا( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_پورٹ_Yield_Required[ پورٹ_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #جے_انت /* if ( configNUMBER_OF_CORES == 1 ) */
#جے_انت /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT                    104
#تعریف_کرو پورٹ_SVC_YIELD                               105
#تعریف_کرو پورٹ_SVC_شروع_پہلا_TASK                    106
#تعریف_کرو پورٹ_SVC_DISABLE_INTERRUPTS                  107
#تعریف_کرو پورٹ_SVC_ENABLE_INTERRUPTS                   108
#تعریف_کرو پورٹ_SVC_GET_CORE_ID                         109
#تعریف_کرو پورٹ_SVC_نقاب_ALL_INTERRUPTS                 110
#تعریف_کرو پورٹ_SVC_UNMASK_ALL_INTERRUPTS               111
#تعریف_کرو پورٹ_SVC_UNMASK_INTERRUPTS                   112
#تعریف_کرو پورٹ_SVC_CHECK_PRIVILEGE                     113
#تعریف_کرو پورٹ_SVC_SAVE_TASK_CONTEXT                   114
#تعریف_کرو پورٹ_SVC_RESTORE_CONTEXT                     115
#تعریف_کرو پورٹ_SVC_DELETE_CURRENT_TASK                 116
#تعریف_کرو پورٹ_SVC_رکاوٹ_CORE                      117

#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
#تعریف_کرو پورٹ_YIELD()                __asm متطاير ( "SVC %0" : : "i" ( پورٹ_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#إذا !defined(__ASSEMBLER__)
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_رکاوٹ_حالت );
    خارجي UBaseType_t ux_پورٹ_سیٹ_رکاوٹ_نقاب( فراغ );
    خارجي UBaseType_t ux_پورٹ_سیٹ_رکاوٹ_نقاب_From_ISR( فراغ );
    خارجي فراغ v_پورٹ_Clear_رکاوٹ_نقاب( UBaseType_t ux_New_نقاب_قدر );
    خارجي فراغ v_پورٹ_Clear_رکاوٹ_نقاب_From_ISR( UBaseType_t ux_New_نقاب_قدر );
    خارجي فراغ v_رکاوٹ_Core( uint32_t ul_رکاوٹ_ID, uint8_t ucCoreID );
#جے_انت /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS() __asm متطاير ( "SVC %0" : : "i" ( پورٹ_SVC_DISABLE_INTERRUPTS ) : "memory" )

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()  __asm متطاير ( "SVC %0" : : "i" ( پورٹ_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کرو پورٹ_UNMASK_قدر           ( 0xFFUL )

#إذا !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #إذا  ( config_نمبر_دا_CORES == 1 )
        خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
        خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
        #تعریف_کرو پورٹ_ENTER_CRITICAL()                  v_پورٹ_Enter_Critical()
        #تعریف_کرو پورٹ_EXIT_CRITICAL()                   v_پورٹ_Exit_Critical()
    #وإلا
        #تعریف_کرو پورٹ_ENTER_CRITICAL()                  vTaskEnterCritical()
        #تعریف_کرو پورٹ_EXIT_CRITICAL()                   vTaskExitCritical()
    #جے_انت
    #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ux_پورٹ_سیٹ_رکاوٹ_نقاب_From_ISR()
    #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_پورٹ_Clear_رکاوٹ_نقاب_From_ISR( x )
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#جے_انت /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    فراغ FreeRTOS_Tick_Handler( فراغ );
#جے_انت /* if !defined(__ASSEMBLER__) */

#تعریف_کرو پورٹ_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#تعریف_کرو پورٹ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT == پورٹ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ );
#وإلا
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #تعریف_کرو v_پورٹ_Task_ورتدا_FPU()
#جے_انت

#تعریف_کرو پورٹ_TASK_ورتدا_FLOATING_نقطہ()          v_پورٹ_Task_ورتدا_FPU()

#تعریف_کرو پورٹ_سبھ_توں_نیواں_رکاوٹ_ترجیح           ( ( ( uint32_t ) config_UNIQUE_رکاوٹ_PRIORITIES ) - 1UL )
#تعریف_کرو پورٹ_سبھ_توں_نیواں_USABLE_رکاوٹ_ترجیح    ( پورٹ_سبھ_توں_نیواں_رکاوٹ_ترجیح - 1UL )

/* Architecture specific optimisations. */
#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31 - __builtin_clz( uxReadyPriorities ) )

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ );
    #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    v_پورٹ_Validate_رکاوٹ_ترجیح()
#جے_انت /* configASSERT */

#تعریف_کرو پورٹ_NOP()     __asm متطاير ( "NOP" )
#تعریف_کرو پورٹ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_رکاوٹ_PRIORITIES == 16
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            4
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    3
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 32
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            3
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    2
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 64
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            2
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    1
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 128
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            1
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 256
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            0
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #غلطی Invalid config_UNIQUE_رکاوٹ_PRIORITIES setting.  config_UNIQUE_رکاوٹ_PRIORITIES must be سیٹ منزل the نمبر دا unique priorities implemented by the نشانہ hardware
#جے_انت /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#تعریف_کرو پورٹ_رکاوٹ_ترجیح_رجسٹر_وتھ    ( 0x400U )
#تعریف_کرو پورٹ_YIELD_CORE_INT_ID                     ( 0x0U )
#تعریف_کرو پورٹ_MAX_API_ترجیح_نقاب                 ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_ترجیح_کھسکاؤ )

#إذا ( config_نمبر_دا_CORES > 1 )

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع تعداد
        {
            e_Isr_جندرا = 0,
            e_Task_جندرا,
            e_جندرا_گنتی
        } e_پورٹ_RTOSLock;

        خارجي متطاير uint64_t ullCriticalNestings[ config_نمبر_دا_CORES ];
        خارجي فراغ v_پورٹ_Recursive_جندرا( uint8_t ucCoreID,
                                        e_پورٹ_RTOSLock e_جندرا_عدد,
                                        ادھار_Type_t uxAcquire );
        خارجي uint8_t uc_پورٹ_Get_Core_ID( فراغ );
        خارجي uint8_t uc_پورٹ_Get_Core_IDFrom_Isr( فراغ );
    #جے_انت /* if !defined(__ASSEMBLER__) */

    #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب()         ux_پورٹ_سیٹ_رکاوٹ_نقاب()
    #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب( x )    v_پورٹ_Clear_رکاوٹ_نقاب( x )

    #تعریف_کرو پورٹ_MAX_CORE_گنتی               config_نمبر_دا_CORES
    #تعریف_کرو پورٹ_GET_CORE_ID()                uc_پورٹ_Get_Core_ID()
    #تعریف_کرو پورٹ_GET_CORE_ID_FROM_ISR()       uc_پورٹ_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #تعریف_کرو پورٹ_YIELD_CORE( xCoreID )                          v_رکاوٹ_Core( پورٹ_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )                    v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Isr_جندرا, pdFALSE )
    #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )                        v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Isr_جندرا, pdTRUE )

    #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )                   v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Task_جندرا, pdFALSE )
    #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )                       v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Task_جندرا, pdTRUE )
    #تعریف_کرو پورٹ_GET_CRITICAL_NESTING_گنتی( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کرو پورٹ_سیٹ_CRITICAL_NESTING_گنتی( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کرو پورٹ_INCREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کرو پورٹ_DECREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#جے_انت /* configNUMBER_OF_CORES > 1 */

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متطاير ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )

    #إذا !defined(__ASSEMBLER__)
        خارجي ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ );
    #جے_انت /* if !defined(__ASSEMBLER__) */

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
    #تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_n_Gn_Rn_E                 ( 0x00 )
    #تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_n_Gn_RE                  ( 0x04 )
    #تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_n_GRE                   ( 0x08 )
    #تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #جے_بنا_تعریف config_کل_MPU_REGIONS
        #تعریف_کرو config_کل_MPU_REGIONS                  ( 16UL )
    #جے_انت

    #تعریف_کرو پورٹ_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #تعریف_کرو پورٹ_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #تعریف_کرو پورٹ_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #تعریف_کرو پورٹ_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #تعریف_کرو پورٹ_ڈھیر_REGION                             ( 4ULL )                                /* Stack region number. */
    #تعریف_کرو پورٹ_ڈھیر_REGION_اشاریہ                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #تعریف_کرو پورٹ_پہلا_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #تعریف_کرو پورٹ_آخری_CONFIGURABLE_REGION                 ( config_کل_MPU_REGIONS - 1UL )
    #تعریف_کرو پورٹ_عدد_CONFIGURABLE_REGIONS                 ( ( پورٹ_آخری_CONFIGURABLE_REGION - پورٹ_پہلا_CONFIGURABLE_REGION ) + 1 )
    #تعریف_کرو پورٹ_کل_عدد_REGIONS                        ( پورٹ_عدد_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #تعریف_کرو پورٹ_ACL_اندراج_ناپ_بٹ ( 32UL )
    #جے_انت /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #إذا !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        تعريفنوع بنية MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #جے_بنا_تعریف config_SYSTEM_CALL_ڈھیر_ناپ
            #تعریف_کرو config_SYSTEM_CALL_ڈھیر_ناپ 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #جے_انت

        /**
         * @brief System call info.
         */
        تعريفنوع بنية SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_رجسٹر_At_System_Call_اندراج;
            uint64_t ull_User_SPAt_System_Call_اندراج;
        } xSYSTEM_CALL_INFO;
    #جے_انت /* if !defined(__ASSEMBLER__) */

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
        #تعریف_کرو MAX_CONTEXT_ناپ    102

    #وإلا /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #تعریف_کرو MAX_CONTEXT_ناپ    36
    #جے_انت /* #if ( configENABLE_FPU == 1 ) */

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع بنية MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ پورٹ_کل_عدد_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_ناپ + config_SYSTEM_CALL_ڈھیر_ناپ ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ناپ / پورٹ_ACL_اندراج_ناپ_بٹ ) + 1 ];
            #جے_انت /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #جے_انت /* if !defined(__ASSEMBLER__) */

    #تعریف_کرو پورٹ_USING_MPU_WRAPPERS                        ( 1 )
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #تعریف_کرو پورٹ_MPU_عام_حافظہ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #تعریف_کرو پورٹ_MPU_عام_حافظہ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR0_نقاب                   ( 0x00000000000000ffULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR1_نقاب                   ( 0x000000000000ff00ULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR2_نقاب                   ( 0x0000000000ff0000ULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR3_نقاب                   ( 0x00000000ff000000ULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR4_نقاب                   ( 0x000000ff00000000ULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR5_نقاب                   ( 0x0000ff0000000000ULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR6_نقاب                   ( 0x00ff000000000000ULL )

    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #تعریف_کرو پورٹ_MPU_MAIR_EL1_ATTR7_نقاب                   ( 0xff00000000000000ULL )

    #تعریف_کرو پورٹ_MPU_PRBAR_EL1_پتہ_نقاب                ( 0x0000FFFFFFFFFFC0ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_پتہ_نقاب                ( 0x0000FFFFFFFFFFC0ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_پتہ_IMPLIED_بٹ        ( 0x000000000000003FULL )
    #تعریف_کرو پورٹ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_نقاب     ( 3ULL<< 2ULL )

    #تعریف_کرو پورٹ_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #تعریف_کرو پورٹ_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #تعریف_کرو پورٹ_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #تعریف_کرو پورٹ_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #تعریف_کرو پورٹ_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #تعریف_کرو پورٹ_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #تعریف_کرو پورٹ_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #تعریف_کرو پورٹ_MPU_ENABLE_ثنائی_ہندسہ                            ( 1ULL << 0ULL )
    #تعریف_کرو پورٹ_MPU_PRIV_BACKGROUND_ENABLE_ثنائی_ہندسہ            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #تعریف_کرو پورٹ_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #تعریف_کرو پورٹ_جوڑو_UINT64_WILL_حد_توں_ودھ( a, b )          ( ( a ) > ( پورٹ_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #تعریف_کرو پورٹ_کڈھو_پہلا_پتہ_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & پورٹ_MPU_PRBAR_EL1_پتہ_نقاب )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #تعریف_کرو پورٹ_کڈھو_آخری_پتہ_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & پورٹ_MPU_PRLAR_EL1_پتہ_نقاب ) | پورٹ_MPU_PRLAR_EL1_پتہ_IMPLIED_بٹ )

    /* Does addr lies within [start, end] address range? */
    #تعریف_کرو پورٹ_IS_پتہ_WITHIN_RANGE( addr, شروع, سرا ) \
        ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( سرا ) ) )

    /* Is the access request satisfied by the available permissions? */
    #تعریف_کرو پورٹ_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #إذا ( configUSE_TASK_FPU_SUPPORT == پورٹ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #تعریف_کرو پورٹ_وتھ_منزل_PC     ( 68 )
        #تعریف_کرو پورٹ_وتھ_منزل_LR     ( 70 )
        #تعریف_کرو پورٹ_وتھ_منزل_X0     ( 100 )
        #تعریف_کرو پورٹ_وتھ_منزل_X1     ( 101 )
        #تعریف_کرو پورٹ_وتھ_منزل_X2     ( 98 )
        #تعریف_کرو پورٹ_وتھ_منزل_X3     ( 99 )
    #وإلا
        #تعریف_کرو پورٹ_وتھ_منزل_PC     ( 2 )
        #تعریف_کرو پورٹ_وتھ_منزل_LR     ( 4 )
        #تعریف_کرو پورٹ_وتھ_منزل_X0     ( 34 )
        #تعریف_کرو پورٹ_وتھ_منزل_X1     ( 35 )
        #تعریف_کرو پورٹ_وتھ_منزل_X2     ( 32 )
        #تعریف_کرو پورٹ_وتھ_منزل_X3     ( 33 )
    #جے_انت

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #تعریف_کرو پورٹ_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #تعریف_کرو پورٹ_IS_TASK_PRIVILEGED() x_پورٹ_Is_Task_Privileged()

#وإلا

    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ        ( 0x0UL )

#جے_انت /* #if ( configENABLE_MPU == 1 ) */

#تعریف_کرو پورٹ_PSTATE_I_ثنائی_ہندسہ             ( 0x7 )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
