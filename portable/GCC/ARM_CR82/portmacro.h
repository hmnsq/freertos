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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
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
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    size_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

#ఒకవేళ !defined(__ASSEMBLER__)
    రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
    రకనిర్వచనం పోర్టు_పునాది_TYPE    పునాది_Type_t;
    రకనిర్వచనం uint64_t         UBaseType_t;

    రకనిర్వచనం uint64_t         TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH         ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT       16
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#ఒకవేళ !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        #నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            బాహ్య uint64_t ull_పోర్టు_Yield_Required;        \
                                                        \
            ఒకవేళ( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_పోర్టు_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #లేకపోతే
        #నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            బాహ్య uint64_t ull_పోర్టు_Yield_Required[ config_సంఖ్య_యొక్క_CORES ]; \
                                                                        \
            ఒకవేళ( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_పోర్టు_Yield_Required[ పోర్టు_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */
#అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#నిర్వచించు పోర్టు_SVC_SYSTEM_CALL_EXIT                    104
#నిర్వచించు పోర్టు_SVC_YIELD                               105
#నిర్వచించు పోర్టు_SVC_ప్రారంభం_మొదటి_TASK                    106
#నిర్వచించు పోర్టు_SVC_DISABLE_INTERRUPTS                  107
#నిర్వచించు పోర్టు_SVC_ENABLE_INTERRUPTS                   108
#నిర్వచించు పోర్టు_SVC_GET_CORE_ID                         109
#నిర్వచించు పోర్టు_SVC_ముసుగు_ALL_INTERRUPTS                 110
#నిర్వచించు పోర్టు_SVC_UNMASK_ALL_INTERRUPTS               111
#నిర్వచించు పోర్టు_SVC_UNMASK_INTERRUPTS                   112
#నిర్వచించు పోర్టు_SVC_CHECK_PRIVILEGE                     113
#నిర్వచించు పోర్టు_SVC_SAVE_TASK_CONTEXT                   114
#నిర్వచించు పోర్టు_SVC_RESTORE_CONTEXT                     115
#నిర్వచించు పోర్టు_SVC_DELETE_CURRENT_TASK                 116
#నిర్వచించు పోర్టు_SVC_అంతరాయం_CORE                      117

#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
#నిర్వచించు పోర్టు_YIELD()                __asm అస్థిర ( "SVC %0" : : "i" ( పోర్టు_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#ఒకవేళ !defined(__ASSEMBLER__)
    బాహ్య UBaseType_t vTaskEnterCriticalFromISR( శూన్య );
    బాహ్య శూన్య vTaskExitCriticalFromISR( UBaseType_t ux_Saved_అంతరాయం_స్థితి );
    బాహ్య UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య );
    బాహ్య UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య );
    బాహ్య శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( UBaseType_t ux_New_ముసుగు_విలువ );
    బాహ్య శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( UBaseType_t ux_New_ముసుగు_విలువ );
    బాహ్య శూన్య v_అంతరాయం_Core( uint32_t ul_అంతరాయం_ID, uint8_t ucCoreID );
#అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS() __asm అస్థిర ( "SVC %0" : : "i" ( పోర్టు_SVC_DISABLE_INTERRUPTS ) : "memory" )

#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()  __asm అస్థిర ( "SVC %0" : : "i" ( పోర్టు_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#నిర్వచించు పోర్టు_UNMASK_విలువ           ( 0xFFUL )

#ఒకవేళ !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #ఒకవేళ  ( config_సంఖ్య_యొక్క_CORES == 1 )
        బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
        బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
        #నిర్వచించు పోర్టు_ENTER_CRITICAL()                  v_పోర్టు_Enter_Critical()
        #నిర్వచించు పోర్టు_EXIT_CRITICAL()                   v_పోర్టు_Exit_Critical()
    #లేకపోతే
        #నిర్వచించు పోర్టు_ENTER_CRITICAL()                  vTaskEnterCritical()
        #నిర్వచించు పోర్టు_EXIT_CRITICAL()                   vTaskExitCritical()
    #అయితే_ముగింపు
    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR()
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( x )
    #నిర్వచించు పోర్టు_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#ఒకవేళ !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    శూన్య FreeRTOS_Tick_Handler( శూన్య );
#అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

#నిర్వచించు పోర్టు_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#నిర్వచించు పోర్టు_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య );
#లేకపోతే
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #నిర్వచించు v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU()
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_TASK_ఉపయోగిస్తుంది_FLOATING_బిందువు()          v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU()

#నిర్వచించు పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత           ( ( ( uint32_t ) config_UNIQUE_అంతరాయం_PRIORITIES ) - 1UL )
#నిర్వచించు పోర్టు_అత్యల్ప_USABLE_అంతరాయం_ప్రాధాన్యత    ( పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత - 1UL )

/* Architecture specific optimisations. */
#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    ux_శిఖరం_ప్రాధాన్యత = ( 31 - __builtin_clz( uxReadyPriorities ) )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ఒకవేళ ( configASSERT_DEFINED == 1 )
    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య );
    #నిర్వచించు పోర్టు_ASSERT_IF_అంతరాయం_ప్రాధాన్యత_INVALID()    v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత()
#అయితే_ముగింపు /* configASSERT */

#నిర్వచించు పోర్టు_NOP()     __asm అస్థిర ( "NOP" )
#నిర్వచించు పోర్టు_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#ఒకవేళ config_UNIQUE_అంతరాయం_PRIORITIES == 16
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            4
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    3
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 32
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            3
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    2
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 64
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            2
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    1
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 128
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            1
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    0
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 256
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            0
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    0
#లేకపోతే /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #దోషం Invalid config_UNIQUE_అంతరాయం_PRIORITIES setting.  config_UNIQUE_అంతరాయం_PRIORITIES must be సమితి గమ్యం the సంఖ్య యొక్క unique priorities implemented by the లక్ష్యం hardware
#అయితే_ముగింపు /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#నిర్వచించు పోర్టు_అంతరాయం_ప్రాధాన్యత_రిజిస్టరు_స్థానభ్రంశం    ( 0x400U )
#నిర్వచించు పోర్టు_YIELD_CORE_INT_ID                     ( 0x0U )
#నిర్వచించు పోర్టు_MAX_API_ప్రాధాన్యత_ముసుగు                 ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు )

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

    #ఒకవేళ !defined(__ASSEMBLER__)
        రకనిర్వచనం గణన
        {
            e_Isr_తాళం = 0,
            e_Task_తాళం,
            e_తాళం_లెక్క
        } e_పోర్టు_RTOSLock;

        బాహ్య అస్థిర uint64_t ullCriticalNestings[ config_సంఖ్య_యొక్క_CORES ];
        బాహ్య శూన్య v_పోర్టు_Recursive_తాళం( uint8_t ucCoreID,
                                        e_పోర్టు_RTOSLock e_తాళం_అంకె,
                                        పునాది_Type_t uxAcquire );
        బాహ్య uint8_t uc_పోర్టు_Get_Core_ID( శూన్య );
        బాహ్య uint8_t uc_పోర్టు_Get_Core_IDFrom_Isr( శూన్య );
    #అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()         ux_పోర్టు_సమితి_అంతరాయం_ముసుగు()
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు( x )    v_పోర్టు_Clear_అంతరాయం_ముసుగు( x )

    #నిర్వచించు పోర్టు_MAX_CORE_లెక్క               config_సంఖ్య_యొక్క_CORES
    #నిర్వచించు పోర్టు_GET_CORE_ID()                uc_పోర్టు_Get_Core_ID()
    #నిర్వచించు పోర్టు_GET_CORE_ID_FROM_ISR()       uc_పోర్టు_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #నిర్వచించు పోర్టు_YIELD_CORE( xCoreID )                          v_అంతరాయం_Core( పోర్టు_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )                    v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Isr_తాళం, pdFALSE )
    #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )                        v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Isr_తాళం, pdTRUE )

    #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )                   v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Task_తాళం, pdFALSE )
    #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )                       v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Task_తాళం, pdTRUE )
    #నిర్వచించు పోర్టు_GET_CRITICAL_NESTING_లెక్క( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #నిర్వచించు పోర్టు_సమితి_CRITICAL_NESTING_లెక్క( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #నిర్వచించు పోర్టు_INCREMENT_CRITICAL_NESTING_లెక్క( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #నిర్వచించు పోర్టు_DECREMENT_CRITICAL_NESTING_లెక్క( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#అయితే_ముగింపు /* configNUMBER_OF_CORES > 1 */

#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#ఒకవేళ ( configENABLE_MPU == 1 )

    #ఒకవేళ !defined(__ASSEMBLER__)
        బాహ్య పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య );
    #అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

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
    #నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_Rn_E                 ( 0x00 )
    #నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_RE                  ( 0x04 )
    #నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_GRE                   ( 0x08 )
    #నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #నిర్వచితం_కాకపోతే config_మొత్తం_MPU_REGIONS
        #నిర్వచించు config_మొత్తం_MPU_REGIONS                  ( 16UL )
    #అయితే_ముగింపు

    #నిర్వచించు పోర్టు_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #నిర్వచించు పోర్టు_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #నిర్వచించు పోర్టు_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #నిర్వచించు పోర్టు_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #నిర్వచించు పోర్టు_దొంతర_REGION                             ( 4ULL )                                /* Stack region number. */
    #నిర్వచించు పోర్టు_దొంతర_REGION_సూచీ                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #నిర్వచించు పోర్టు_మొదటి_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #నిర్వచించు పోర్టు_చివరి_CONFIGURABLE_REGION                 ( config_మొత్తం_MPU_REGIONS - 1UL )
    #నిర్వచించు పోర్టు_అంకె_CONFIGURABLE_REGIONS                 ( ( పోర్టు_చివరి_CONFIGURABLE_REGION - పోర్టు_మొదటి_CONFIGURABLE_REGION ) + 1 )
    #నిర్వచించు పోర్టు_మొత్తం_అంకె_REGIONS                        ( పోర్టు_అంకె_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #నిర్వచించు పోర్టు_ACL_నమోదు_కొలత_బిట్లు ( 32UL )
    #అయితే_ముగింపు /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #ఒకవేళ !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        రకనిర్వచనం నిర్మాణం MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #నిర్వచితం_కాకపోతే config_SYSTEM_CALL_దొంతర_కొలత
            #నిర్వచించు config_SYSTEM_CALL_దొంతర_కొలత 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #అయితే_ముగింపు

        /**
         * @brief System call info.
         */
        రకనిర్వచనం నిర్మాణం SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_రిజిస్టరు_At_System_Call_నమోదు;
            uint64_t ull_User_SPAt_System_Call_నమోదు;
        } xSYSTEM_CALL_INFO;
    #అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #ఒకవేళ ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #నిర్వచించు MAX_CONTEXT_కొలత    102

    #లేకపోతే /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #నిర్వచించు MAX_CONTEXT_కొలత    36
    #అయితే_ముగింపు /* #if ( configENABLE_FPU == 1 ) */

    #ఒకవేళ !defined(__ASSEMBLER__)
        రకనిర్వచనం నిర్మాణం MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ పోర్టు_మొత్తం_అంకె_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_కొలత + config_SYSTEM_CALL_దొంతర_కొలత ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_కొలత / పోర్టు_ACL_నమోదు_కొలత_బిట్లు ) + 1 ];
            #అయితే_ముగింపు /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #అయితే_ముగింపు /* if !defined(__ASSEMBLER__) */

    #నిర్వచించు పోర్టు_USING_MPU_WRAPPERS                        ( 1 )
    #నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #నిర్వచించు పోర్టు_MPU_సాధారణ_జ్ఞాపకం_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #నిర్వచించు పోర్టు_MPU_సాధారణ_జ్ఞాపకం_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR0_ముసుగు                   ( 0x00000000000000ffULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR1_ముసుగు                   ( 0x000000000000ff00ULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR2_ముసుగు                   ( 0x0000000000ff0000ULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR3_ముసుగు                   ( 0x00000000ff000000ULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR4_ముసుగు                   ( 0x000000ff00000000ULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR5_ముసుగు                   ( 0x0000ff0000000000ULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR6_ముసుగు                   ( 0x00ff000000000000ULL )

    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #నిర్వచించు పోర్టు_MPU_MAIR_EL1_ATTR7_ముసుగు                   ( 0xff00000000000000ULL )

    #నిర్వచించు పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు                ( 0x0000FFFFFFFFFFC0ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు                ( 0x0000FFFFFFFFFFC0ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_చిరునామా_IMPLIED_బిట్లు        ( 0x000000000000003FULL )
    #నిర్వచించు పోర్టు_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ముసుగు     ( 3ULL<< 2ULL )

    #నిర్వచించు పోర్టు_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #నిర్వచించు పోర్టు_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #నిర్వచించు పోర్టు_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #నిర్వచించు పోర్టు_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #నిర్వచించు పోర్టు_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #నిర్వచించు పోర్టు_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #నిర్వచించు పోర్టు_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #నిర్వచించు పోర్టు_MPU_ENABLE_బిట్టు                            ( 1ULL << 0ULL )
    #నిర్వచించు పోర్టు_MPU_PRIV_BACKGROUND_ENABLE_బిట్టు            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #నిర్వచించు పోర్టు_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #నిర్వచించు పోర్టు_కూడు_UINT64_WILL_అధికప్రవాహం( a, b )          ( ( a ) > ( పోర్టు_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #నిర్వచించు పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & పోర్టు_MPU_PRBAR_EL1_చిరునామా_ముసుగు )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #నిర్వచించు పోర్టు_వెలికితీయి_చివరి_చిరునామా_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & పోర్టు_MPU_PRLAR_EL1_చిరునామా_ముసుగు ) | పోర్టు_MPU_PRLAR_EL1_చిరునామా_IMPLIED_బిట్లు )

    /* Does addr lies within [start, end] address range? */
    #నిర్వచించు పోర్టు_IS_చిరునామా_WITHIN_RANGE( addr, ప్రారంభం, చివర ) \
        ( ( ( addr ) >= ( ప్రారంభం ) ) && ( ( addr ) <= ( చివర ) ) )

    /* Is the access request satisfied by the available permissions? */
    #నిర్వచించు పోర్టు_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == పోర్టు_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PC     ( 68 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_LR     ( 70 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X0     ( 100 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X1     ( 101 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X2     ( 98 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X3     ( 99 )
    #లేకపోతే
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PC     ( 2 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_LR     ( 4 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X0     ( 34 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X1     ( 35 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X2     ( 32 )
        #నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_X3     ( 33 )
    #అయితే_ముగింపు

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #నిర్వచించు పోర్టు_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #నిర్వచించు పోర్టు_IS_TASK_PRIVILEGED() x_పోర్టు_Is_Task_Privileged()

#లేకపోతే

    #నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు        ( 0x0UL )

#అయితే_ముగింపు /* #if ( configENABLE_MPU == 1 ) */

#నిర్వచించు పోర్టు_PSTATE_I_బిట్టు             ( 0x7 )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
