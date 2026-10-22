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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    size_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

#إذا !defined(__ASSEMBLER__)
    تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
    تعريفنوع پورٽ_بنياد_TYPE    بنياد_Type_t;
    تعريفنوع uint64_t         UBaseType_t;

    تعريفنوع uint64_t         TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH         ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT       16
#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#إذا !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #إذا ( config_عدد_جو_CORES == 1 )
        #وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            خارجي uint64_t ull_پورٽ_Yield_Required;        \
                                                        \
            إذا( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_پورٽ_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #وإلا
        #وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            خارجي uint64_t ull_پورٽ_Yield_Required[ config_عدد_جو_CORES ]; \
                                                                        \
            إذا( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_پورٽ_Yield_Required[ پورٽ_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */
#جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#وصف_ڪريو پورٽ_SVC_SYSTEM_CALL_EXIT                    104
#وصف_ڪريو پورٽ_SVC_YIELD                               105
#وصف_ڪريو پورٽ_SVC_شروعات_پهريون_TASK                    106
#وصف_ڪريو پورٽ_SVC_DISABLE_INTERRUPTS                  107
#وصف_ڪريو پورٽ_SVC_ENABLE_INTERRUPTS                   108
#وصف_ڪريو پورٽ_SVC_GET_CORE_ID                         109
#وصف_ڪريو پورٽ_SVC_نقاب_ALL_INTERRUPTS                 110
#وصف_ڪريو پورٽ_SVC_UNMASK_ALL_INTERRUPTS               111
#وصف_ڪريو پورٽ_SVC_UNMASK_INTERRUPTS                   112
#وصف_ڪريو پورٽ_SVC_CHECK_PRIVILEGE                     113
#وصف_ڪريو پورٽ_SVC_SAVE_TASK_CONTEXT                   114
#وصف_ڪريو پورٽ_SVC_RESTORE_CONTEXT                     115
#وصف_ڪريو پورٽ_SVC_DELETE_CURRENT_TASK                 116
#وصف_ڪريو پورٽ_SVC_مداخلت_CORE                      117

#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
#وصف_ڪريو پورٽ_YIELD()                __asm متطاير ( "SVC %0" : : "i" ( پورٽ_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#إذا !defined(__ASSEMBLER__)
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );
    خارجي UBaseType_t ux_پورٽ_سيٽ_مداخلت_نقاب( فراغ );
    خارجي UBaseType_t ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR( فراغ );
    خارجي فراغ v_پورٽ_Clear_مداخلت_نقاب( UBaseType_t ux_New_نقاب_قدر );
    خارجي فراغ v_پورٽ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t ux_New_نقاب_قدر );
    خارجي فراغ v_مداخلت_Core( uint32_t ul_مداخلت_ID, uint8_t ucCoreID );
#جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS() __asm متطاير ( "SVC %0" : : "i" ( پورٽ_SVC_DISABLE_INTERRUPTS ) : "memory" )

#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()  __asm متطاير ( "SVC %0" : : "i" ( پورٽ_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#وصف_ڪريو پورٽ_UNMASK_قدر           ( 0xFFUL )

#إذا !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #إذا  ( config_عدد_جو_CORES == 1 )
        خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
        خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
        #وصف_ڪريو پورٽ_ENTER_CRITICAL()                  v_پورٽ_Enter_Critical()
        #وصف_ڪريو پورٽ_EXIT_CRITICAL()                   v_پورٽ_Exit_Critical()
    #وإلا
        #وصف_ڪريو پورٽ_ENTER_CRITICAL()                  vTaskEnterCritical()
        #وصف_ڪريو پورٽ_EXIT_CRITICAL()                   vTaskExitCritical()
    #جيڪڏهن_پورو
    #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         ux_پورٽ_سيٽ_مداخلت_نقاب_From_ISR()
    #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٽ_Clear_مداخلت_نقاب_From_ISR( x )
    #وصف_ڪريو پورٽ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    فراغ FreeRTOS_Tick_Handler( فراغ );
#جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

#وصف_ڪريو پورٽ_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#وصف_ڪريو پورٽ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT == پورٽ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ );
#وإلا
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #وصف_ڪريو v_پورٽ_Task_استعمال_ڪري_FPU()
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_TASK_استعمال_ڪري_FLOATING_نقطو()          v_پورٽ_Task_استعمال_ڪري_FPU()

#وصف_ڪريو پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح           ( ( ( uint32_t ) config_UNIQUE_مداخلت_PRIORITIES ) - 1UL )
#وصف_ڪريو پورٽ_سڀ_کان_هيٺ_USABLE_مداخلت_ترجيح    ( پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح - 1UL )

/* Architecture specific optimisations. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31 - __builtin_clz( uxReadyPriorities ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ );
    #وصف_ڪريو پورٽ_ASSERT_IF_مداخلت_ترجيح_INVALID()    v_پورٽ_Validate_مداخلت_ترجيح()
#جيڪڏهن_پورو /* configASSERT */

#وصف_ڪريو پورٽ_NOP()     __asm متطاير ( "NOP" )
#وصف_ڪريو پورٽ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_مداخلت_PRIORITIES == 16
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            4
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    3
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 32
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            3
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    2
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 64
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            2
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    1
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 128
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            1
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    0
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 256
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            0
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #غلطي Invalid config_UNIQUE_مداخلت_PRIORITIES setting.  config_UNIQUE_مداخلت_PRIORITIES must be سيٽ منزل the عدد جو unique priorities implemented by the هدف hardware
#جيڪڏهن_پورو /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#وصف_ڪريو پورٽ_مداخلت_ترجيح_رجسٽر_وٿي    ( 0x400U )
#وصف_ڪريو پورٽ_YIELD_CORE_INT_ID                     ( 0x0U )
#وصف_ڪريو پورٽ_MAX_API_ترجيح_نقاب                 ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو )

#إذا ( config_عدد_جو_CORES > 1 )

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع تعداد
        {
            e_Isr_تالو = 0,
            e_Task_تالو,
            e_تالو_ڳڻپ
        } e_پورٽ_RTOSLock;

        خارجي متطاير uint64_t ullCriticalNestings[ config_عدد_جو_CORES ];
        خارجي فراغ v_پورٽ_Recursive_تالو( uint8_t ucCoreID,
                                        e_پورٽ_RTOSLock e_تالو_انگ,
                                        بنياد_Type_t uxAcquire );
        خارجي uint8_t uc_پورٽ_Get_Core_ID( فراغ );
        خارجي uint8_t uc_پورٽ_Get_Core_IDFrom_Isr( فراغ );
    #جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

    #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()         ux_پورٽ_سيٽ_مداخلت_نقاب()
    #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب( x )    v_پورٽ_Clear_مداخلت_نقاب( x )

    #وصف_ڪريو پورٽ_MAX_CORE_ڳڻپ               config_عدد_جو_CORES
    #وصف_ڪريو پورٽ_GET_CORE_ID()                uc_پورٽ_Get_Core_ID()
    #وصف_ڪريو پورٽ_GET_CORE_ID_FROM_ISR()       uc_پورٽ_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #وصف_ڪريو پورٽ_YIELD_CORE( xCoreID )                          v_مداخلت_Core( پورٽ_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )                    v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Isr_تالو, pdFALSE )
    #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )                        v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Isr_تالو, pdTRUE )

    #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )                   v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Task_تالو, pdFALSE )
    #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )                       v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Task_تالو, pdTRUE )
    #وصف_ڪريو پورٽ_GET_CRITICAL_NESTING_ڳڻپ( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #وصف_ڪريو پورٽ_سيٽ_CRITICAL_NESTING_ڳڻپ( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #وصف_ڪريو پورٽ_INCREMENT_CRITICAL_NESTING_ڳڻپ( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #وصف_ڪريو پورٽ_DECREMENT_CRITICAL_NESTING_ڳڻپ( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#جيڪڏهن_پورو /* configNUMBER_OF_CORES > 1 */

#وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )

    #إذا !defined(__ASSEMBLER__)
        خارجي بنياد_Type_t x_پورٽ_Is_Task_Privileged( فراغ );
    #جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

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
    #وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_n_Gn_Rn_E                 ( 0x00 )
    #وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_n_Gn_RE                  ( 0x04 )
    #وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_n_GRE                   ( 0x08 )
    #وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #جيڪڏهن_وصف_نه_ٿيل config_ڪل_MPU_REGIONS
        #وصف_ڪريو config_ڪل_MPU_REGIONS                  ( 16UL )
    #جيڪڏهن_پورو

    #وصف_ڪريو پورٽ_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #وصف_ڪريو پورٽ_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #وصف_ڪريو پورٽ_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #وصف_ڪريو پورٽ_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #وصف_ڪريو پورٽ_ڍير_REGION                             ( 4ULL )                                /* Stack region number. */
    #وصف_ڪريو پورٽ_ڍير_REGION_اشاريو                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #وصف_ڪريو پورٽ_پهريون_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #وصف_ڪريو پورٽ_آخري_CONFIGURABLE_REGION                 ( config_ڪل_MPU_REGIONS - 1UL )
    #وصف_ڪريو پورٽ_انگ_CONFIGURABLE_REGIONS                 ( ( پورٽ_آخري_CONFIGURABLE_REGION - پورٽ_پهريون_CONFIGURABLE_REGION ) + 1 )
    #وصف_ڪريو پورٽ_ڪل_انگ_REGIONS                        ( پورٽ_انگ_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #وصف_ڪريو پورٽ_ACL_داخلا_سائيز_بٽ ( 32UL )
    #جيڪڏهن_پورو /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #إذا !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        تعريفنوع بنية MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #جيڪڏهن_وصف_نه_ٿيل config_SYSTEM_CALL_ڍير_سائيز
            #وصف_ڪريو config_SYSTEM_CALL_ڍير_سائيز 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #جيڪڏهن_پورو

        /**
         * @brief System call info.
         */
        تعريفنوع بنية SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_رجسٽر_At_System_Call_داخلا;
            uint64_t ull_User_SPAt_System_Call_داخلا;
        } xSYSTEM_CALL_INFO;
    #جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

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
        #وصف_ڪريو MAX_CONTEXT_سائيز    102

    #وإلا /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #وصف_ڪريو MAX_CONTEXT_سائيز    36
    #جيڪڏهن_پورو /* #if ( configENABLE_FPU == 1 ) */

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع بنية MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ پورٽ_ڪل_انگ_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_سائيز + config_SYSTEM_CALL_ڍير_سائيز ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائيز / پورٽ_ACL_داخلا_سائيز_بٽ ) + 1 ];
            #جيڪڏهن_پورو /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #جيڪڏهن_پورو /* if !defined(__ASSEMBLER__) */

    #وصف_ڪريو پورٽ_USING_MPU_WRAPPERS                        ( 1 )
    #وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #وصف_ڪريو پورٽ_MPU_عام_يادگيري_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #وصف_ڪريو پورٽ_MPU_عام_يادگيري_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR0_نقاب                   ( 0x00000000000000ffULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR1_نقاب                   ( 0x000000000000ff00ULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR2_نقاب                   ( 0x0000000000ff0000ULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR3_نقاب                   ( 0x00000000ff000000ULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR4_نقاب                   ( 0x000000ff00000000ULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR5_نقاب                   ( 0x0000ff0000000000ULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR6_نقاب                   ( 0x00ff000000000000ULL )

    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #وصف_ڪريو پورٽ_MPU_MAIR_EL1_ATTR7_نقاب                   ( 0xff00000000000000ULL )

    #وصف_ڪريو پورٽ_MPU_PRBAR_EL1_پتو_نقاب                ( 0x0000FFFFFFFFFFC0ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_پتو_نقاب                ( 0x0000FFFFFFFFFFC0ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_پتو_IMPLIED_بٽ        ( 0x000000000000003FULL )
    #وصف_ڪريو پورٽ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_نقاب     ( 3ULL<< 2ULL )

    #وصف_ڪريو پورٽ_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #وصف_ڪريو پورٽ_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #وصف_ڪريو پورٽ_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #وصف_ڪريو پورٽ_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #وصف_ڪريو پورٽ_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #وصف_ڪريو پورٽ_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #وصف_ڪريو پورٽ_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #وصف_ڪريو پورٽ_MPU_ENABLE_ٻٽو_انگ                            ( 1ULL << 0ULL )
    #وصف_ڪريو پورٽ_MPU_PRIV_BACKGROUND_ENABLE_ٻٽو_انگ            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #وصف_ڪريو پورٽ_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #وصف_ڪريو پورٽ_جوڙيو_UINT64_WILL_حد_کان_مٿي( a, b )          ( ( a ) > ( پورٽ_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #وصف_ڪريو پورٽ_ڪڍو_پهريون_پتو_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & پورٽ_MPU_PRBAR_EL1_پتو_نقاب )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #وصف_ڪريو پورٽ_ڪڍو_آخري_پتو_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & پورٽ_MPU_PRLAR_EL1_پتو_نقاب ) | پورٽ_MPU_PRLAR_EL1_پتو_IMPLIED_بٽ )

    /* Does addr lies within [start, end] address range? */
    #وصف_ڪريو پورٽ_IS_پتو_WITHIN_RANGE( addr, شروعات, پڇاڙي ) \
        ( ( ( addr ) >= ( شروعات ) ) && ( ( addr ) <= ( پڇاڙي ) ) )

    /* Is the access request satisfied by the available permissions? */
    #وصف_ڪريو پورٽ_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #إذا ( configUSE_TASK_FPU_SUPPORT == پورٽ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #وصف_ڪريو پورٽ_وٿي_منزل_PC     ( 68 )
        #وصف_ڪريو پورٽ_وٿي_منزل_LR     ( 70 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X0     ( 100 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X1     ( 101 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X2     ( 98 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X3     ( 99 )
    #وإلا
        #وصف_ڪريو پورٽ_وٿي_منزل_PC     ( 2 )
        #وصف_ڪريو پورٽ_وٿي_منزل_LR     ( 4 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X0     ( 34 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X1     ( 35 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X2     ( 32 )
        #وصف_ڪريو پورٽ_وٿي_منزل_X3     ( 33 )
    #جيڪڏهن_پورو

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #وصف_ڪريو پورٽ_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #وصف_ڪريو پورٽ_IS_TASK_PRIVILEGED() x_پورٽ_Is_Task_Privileged()

#وإلا

    #وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ        ( 0x0UL )

#جيڪڏهن_پورو /* #if ( configENABLE_MPU == 1 ) */

#وصف_ڪريو پورٽ_PSTATE_I_ٻٽو_انگ             ( 0x7 )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
