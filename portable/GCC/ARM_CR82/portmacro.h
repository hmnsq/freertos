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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    size_t
#परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

#यदि !defined(__ASSEMBLER__)
    प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
    प्रकारनिर्देश पत्तनम्_आधारः_TYPE    आधारः_Type_t;
    प्रकारनिर्देश uint64_t         UBaseType_t;

    प्रकारनिर्देश uint64_t         TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#यदि_अन्तः /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH         ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT       16
#परिभाषय पत्तनम्_POINTER_आकार_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#यदि !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        #परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            बाह्य uint64_t ull_पत्तनम्_Yield_Required;        \
                                                        \
            यदि( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_पत्तनम्_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #अन्यथा
        #परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            बाह्य uint64_t ull_पत्तनम्_Yield_Required[ config_सङ्ख्या_सम्बन्धि_CORES ]; \
                                                                        \
            यदि( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_पत्तनम्_Yield_Required[ पत्तनम्_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */
#यदि_अन्तः /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#परिभाषय पत्तनम्_SVC_SYSTEM_CALL_EXIT                    104
#परिभाषय पत्तनम्_SVC_YIELD                               105
#परिभाषय पत्तनम्_SVC_START_FIRST_TASK                    106
#परिभाषय पत्तनम्_SVC_DISABLE_INTERRUPTS                  107
#परिभाषय पत्तनम्_SVC_ENABLE_INTERRUPTS                   108
#परिभाषय पत्तनम्_SVC_GET_CORE_ID                         109
#परिभाषय पत्तनम्_SVC_आवरणम्_ALL_INTERRUPTS                 110
#परिभाषय पत्तनम्_SVC_UNMASK_ALL_INTERRUPTS               111
#परिभाषय पत्तनम्_SVC_UNMASK_INTERRUPTS                   112
#परिभाषय पत्तनम्_SVC_CHECK_PRIVILEGE                     113
#परिभाषय पत्तनम्_SVC_SAVE_TASK_CONTEXT                   114
#परिभाषय पत्तनम्_SVC_RESTORE_CONTEXT                     115
#परिभाषय पत्तनम्_SVC_DELETE_CURRENT_TASK                 116
#परिभाषय पत्तनम्_SVC_व्यवधानम्_CORE                      117

#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
#परिभाषय पत्तनम्_YIELD()                __asm चञ्चल ( "SVC %0" : : "i" ( पत्तनम्_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#यदि !defined(__ASSEMBLER__)
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( शून्य );
    बाह्य शून्य vTaskExitCriticalFromISR( UBaseType_t ux_Saved_व्यवधानम्_स्थितिः );
    बाह्य UBaseType_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य );
    बाह्य UBaseType_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य );
    बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( UBaseType_t ux_New_आवरणम्_मानम् );
    बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( UBaseType_t ux_New_आवरणम्_मानम् );
    बाह्य शून्य v_व्यवधानम्_Core( uint32_t ul_व्यवधानम्_ID, uint8_t ucCoreID );
#यदि_अन्तः /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS() __asm चञ्चल ( "SVC %0" : : "i" ( पत्तनम्_SVC_DISABLE_INTERRUPTS ) : "memory" )

#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()  __asm चञ्चल ( "SVC %0" : : "i" ( पत्तनम्_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#परिभाषय पत्तनम्_UNMASK_मानम्           ( 0xFFUL )

#यदि !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #यदि  ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
        बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
        #परिभाषय पत्तनम्_ENTER_CRITICAL()                  v_पत्तनम्_Enter_Critical()
        #परिभाषय पत्तनम्_EXIT_CRITICAL()                   v_पत्तनम्_Exit_Critical()
    #अन्यथा
        #परिभाषय पत्तनम्_ENTER_CRITICAL()                  vTaskEnterCritical()
        #परिभाषय पत्तनम्_EXIT_CRITICAL()                   vTaskExitCritical()
    #यदि_अन्तः
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( x )
    #परिभाषय पत्तनम्_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #परिभाषय पत्तनम्_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#यदि_अन्तः /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#यदि !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    शून्य FreeRTOS_Tick_Handler( शून्य );
#यदि_अन्तः /* if !defined(__ASSEMBLER__) */

#परिभाषय पत्तनम्_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#परिभाषय पत्तनम्_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य );
#अन्यथा
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #परिभाषय v_पत्तनम्_Task_उपयुङ्क्ते_FPU()
#यदि_अन्तः

#परिभाषय पत्तनम्_TASK_उपयुङ्क्ते_FLOATING_POINT()          v_पत्तनम्_Task_उपयुङ्क्ते_FPU()

#परिभाषय पत्तनम्_निम्नतमम्_व्यवधानम्_प्राथमिकता           ( ( ( uint32_t ) config_UNIQUE_व्यवधानम्_PRIORITIES ) - 1UL )
#परिभाषय पत्तनम्_निम्नतमम्_USABLE_व्यवधानम्_प्राथमिकता    ( पत्तनम्_निम्नतमम्_व्यवधानम्_प्राथमिकता - 1UL )

/* Architecture specific optimisations. */
#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
#यदि_अन्तः

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31 - __builtin_clz( uxReadyPriorities ) )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#यदि ( configASSERT_DEFINED == 1 )
    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य );
    #परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता()
#यदि_अन्तः /* configASSERT */

#परिभाषय पत्तनम्_NOP()     __asm चञ्चल ( "NOP" )
#परिभाषय पत्तनम्_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 16
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            4
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    3
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 32
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            3
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    2
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 64
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            2
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    1
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 128
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            1
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    0
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 256
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            0
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    0
#अन्यथा /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #दोषः Invalid config_UNIQUE_व्यवधानम्_PRIORITIES setting.  config_UNIQUE_व्यवधानम्_PRIORITIES must be समुच्चयः गन्तव्यम् the सङ्ख्या सम्बन्धि unique priorities implemented by the target hardware
#यदि_अन्तः /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#परिभाषय पत्तनम्_व्यवधानम्_प्राथमिकता_पञ्जिकाकोशः_विस्थापनम्    ( 0x400U )
#परिभाषय पत्तनम्_YIELD_CORE_INT_ID                     ( 0x0U )
#परिभाषय पत्तनम्_MAX_API_प्राथमिकता_आवरणम्                 ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् )

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

    #यदि !defined(__ASSEMBLER__)
        प्रकारनिर्देश गणना
        {
            e_Isr_तालकम् = 0,
            e_Task_तालकम्,
            e_तालकम्_गणनम्
        } e_पत्तनम्_RTOSLock;

        बाह्य चञ्चल uint64_t ullCriticalNestings[ config_सङ्ख्या_सम्बन्धि_CORES ];
        बाह्य शून्य v_पत्तनम्_Recursive_तालकम्( uint8_t ucCoreID,
                                        e_पत्तनम्_RTOSLock e_तालकम्_अङ्कः,
                                        आधारः_Type_t uxAcquire );
        बाह्य uint8_t uc_पत्तनम्_Get_Core_ID( शून्य );
        बाह्य uint8_t uc_पत्तनम्_Get_Core_IDFrom_Isr( शून्य );
    #यदि_अन्तः /* if !defined(__ASSEMBLER__) */

    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()         ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्( x )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( x )

    #परिभाषय पत्तनम्_MAX_CORE_गणनम्               config_सङ्ख्या_सम्बन्धि_CORES
    #परिभाषय पत्तनम्_GET_CORE_ID()                uc_पत्तनम्_Get_Core_ID()
    #परिभाषय पत्तनम्_GET_CORE_ID_FROM_ISR()       uc_पत्तनम्_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #परिभाषय पत्तनम्_YIELD_CORE( xCoreID )                          v_व्यवधानम्_Core( पत्तनम्_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )                    v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Isr_तालकम्, pdFALSE )
    #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )                        v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Isr_तालकम्, pdTRUE )

    #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )                   v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Task_तालकम्, pdFALSE )
    #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )                       v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Task_तालकम्, pdTRUE )
    #परिभाषय पत्तनम्_GET_CRITICAL_NESTING_गणनम्( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #परिभाषय पत्तनम्_समुच्चयः_CRITICAL_NESTING_गणनम्( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #परिभाषय पत्तनम्_INCREMENT_CRITICAL_NESTING_गणनम्( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #परिभाषय पत्तनम्_DECREMENT_CRITICAL_NESTING_गणनम्( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#यदि_अन्तः /* configNUMBER_OF_CORES > 1 */

#परिभाषय पत्तनम्_स्मृतिः_BARRIER()    __asm चञ्चल ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#यदि ( configENABLE_MPU == 1 )

    #यदि !defined(__ASSEMBLER__)
        बाह्य आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य );
    #यदि_अन्तः /* if !defined(__ASSEMBLER__) */

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
    #परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_Rn_E                 ( 0x00 )
    #परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_RE                  ( 0x04 )
    #परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_n_GRE                   ( 0x08 )
    #परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #यदि_अपरिभाषितम् config_योग_MPU_REGIONS
        #परिभाषय config_योग_MPU_REGIONS                  ( 16UL )
    #यदि_अन्तः

    #परिभाषय पत्तनम्_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #परिभाषय पत्तनम्_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #परिभाषय पत्तनम्_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #परिभाषय पत्तनम्_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #परिभाषय पत्तनम्_राशिः_REGION                             ( 4ULL )                                /* Stack region number. */
    #परिभाषय पत्तनम्_राशिः_REGION_सूचकांक                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #परिभाषय पत्तनम्_FIRST_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #परिभाषय पत्तनम्_चरमः_CONFIGURABLE_REGION                 ( config_योग_MPU_REGIONS - 1UL )
    #परिभाषय पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS                 ( ( पत्तनम्_चरमः_CONFIGURABLE_REGION - पत्तनम्_FIRST_CONFIGURABLE_REGION ) + 1 )
    #परिभाषय पत्तनम्_योग_अङ्कः_REGIONS                        ( पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #परिभाषय पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः ( 32UL )
    #यदि_अन्तः /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #यदि !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        प्रकारनिर्देश संरचना MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #यदि_अपरिभाषितम् config_SYSTEM_CALL_राशिः_आकार
            #परिभाषय config_SYSTEM_CALL_राशिः_आकार 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #यदि_अन्तः

        /**
         * @brief System call info.
         */
        प्रकारनिर्देश संरचना SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
            uint64_t ull_User_SPAt_System_Call_प्रविष्टिः;
        } xSYSTEM_CALL_INFO;
    #यदि_अन्तः /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #यदि ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #परिभाषय MAX_CONTEXT_आकार    102

    #अन्यथा /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #परिभाषय MAX_CONTEXT_आकार    36
    #यदि_अन्तः /* #if ( configENABLE_FPU == 1 ) */

    #यदि !defined(__ASSEMBLER__)
        प्रकारनिर्देश संरचना MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ पत्तनम्_योग_अङ्कः_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_आकार + config_SYSTEM_CALL_राशिः_आकार ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः ) + 1 ];
            #यदि_अन्तः /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #यदि_अन्तः /* if !defined(__ASSEMBLER__) */

    #परिभाषय पत्तनम्_USING_MPU_WRAPPERS                        ( 1 )
    #परिभाषय पत्तनम्_PRIVILEGE_BIT                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #परिभाषय पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #परिभाषय पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR0_आवरणम्                   ( 0x00000000000000ffULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR1_आवरणम्                   ( 0x000000000000ff00ULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR2_आवरणम्                   ( 0x0000000000ff0000ULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR3_आवरणम्                   ( 0x00000000ff000000ULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR4_आवरणम्                   ( 0x000000ff00000000ULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR5_आवरणम्                   ( 0x0000ff0000000000ULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR6_आवरणम्                   ( 0x00ff000000000000ULL )

    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #परिभाषय पत्तनम्_MPU_MAIR_EL1_ATTR7_आवरणम्                   ( 0xff00000000000000ULL )

    #परिभाषय पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम्                ( 0x0000FFFFFFFFFFC0ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम्                ( 0x0000FFFFFFFFFFC0ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_IMPLIED_द्वयङ्काः        ( 0x000000000000003FULL )
    #परिभाषय पत्तनम्_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_आवरणम्     ( 3ULL<< 2ULL )

    #परिभाषय पत्तनम्_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #परिभाषय पत्तनम्_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #परिभाषय पत्तनम्_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #परिभाषय पत्तनम्_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #परिभाषय पत्तनम्_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #परिभाषय पत्तनम्_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #परिभाषय पत्तनम्_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #परिभाषय पत्तनम्_MPU_ENABLE_BIT                            ( 1ULL << 0ULL )
    #परिभाषय पत्तनम्_MPU_PRIV_BACKGROUND_ENABLE_BIT            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #परिभाषय पत्तनम्_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #परिभाषय पत्तनम्_सङ्कलय_UINT64_WILL_अतिप्रवाहः( a, b )          ( ( a ) > ( पत्तनम्_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #परिभाषय पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & पत्तनम्_MPU_PRBAR_EL1_स्थानाङ्कः_आवरणम् )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #परिभाषय पत्तनम्_EXTRACT_चरमः_स्थानाङ्कः_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_आवरणम् ) | पत्तनम्_MPU_PRLAR_EL1_स्थानाङ्कः_IMPLIED_द्वयङ्काः )

    /* Does addr lies within [start, end] address range? */
    #परिभाषय पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( addr, start, अन्तः_2 ) \
        ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( अन्तः_2 ) ) )

    /* Is the access request satisfied by the available permissions? */
    #परिभाषय पत्तनम्_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #यदि ( configUSE_TASK_FPU_SUPPORT == पत्तनम्_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PC     ( 68 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_LR     ( 70 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X0     ( 100 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X1     ( 101 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X2     ( 98 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X3     ( 99 )
    #अन्यथा
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PC     ( 2 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_LR     ( 4 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X0     ( 34 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X1     ( 35 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X2     ( 32 )
        #परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_X3     ( 33 )
    #यदि_अन्तः

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #परिभाषय पत्तनम्_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #परिभाषय पत्तनम्_IS_TASK_PRIVILEGED() x_पत्तनम्_Is_Task_Privileged()

#अन्यथा

    #परिभाषय पत्तनम्_PRIVILEGE_BIT        ( 0x0UL )

#यदि_अन्तः /* #if ( configENABLE_MPU == 1 ) */

#परिभाषय पत्तनम्_PSTATE_I_BIT             ( 0x7 )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
