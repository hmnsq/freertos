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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    size_t
#تعریف_کرو پورٹ_بنیاد_TYPE     طویل

#اگر !defined(__ASSEMBLER__)
    قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    قسمتعریف پورٹ_بنیاد_TYPE    بنیاد_Type_t;
    قسمتعریف uint64_t         UBaseType_t;

    قسمتعریف uint64_t         TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#اگر_ختم /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH         ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT       16
#تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#اگر !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #اگر ( config_نمبر_کا_CORES == 1 )
        #تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            خارجی uint64_t ull_پورٹ_Yield_Required;        \
                                                        \
            اگر( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_پورٹ_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #ورنہ
        #تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            خارجی uint64_t ull_پورٹ_Yield_Required[ config_نمبر_کا_CORES ]; \
                                                                        \
            اگر( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_پورٹ_Yield_Required[ پورٹ_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #اگر_ختم /* if ( configNUMBER_OF_CORES == 1 ) */
#اگر_ختم /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT                    104
#تعریف_کرو پورٹ_SVC_YIELD                               105
#تعریف_کرو پورٹ_SVC_آغاز_پہلا_TASK                    106
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
#تعریف_کرو پورٹ_SVC_مداخلت_CORE                      117

#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
#تعریف_کرو پورٹ_YIELD()                __asm متلون ( "SVC %0" : : "i" ( پورٹ_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#اگر !defined(__ASSEMBLER__)
    خارجی UBaseType_t vTaskEnterCriticalFromISR( خالی );
    خارجی خالی vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );
    خارجی UBaseType_t ux_پورٹ_سیٹ_مداخلت_نقاب( خالی );
    خارجی UBaseType_t ux_پورٹ_سیٹ_مداخلت_نقاب_From_ISR( خالی );
    خارجی خالی v_پورٹ_Clear_مداخلت_نقاب( UBaseType_t ux_New_نقاب_قدر );
    خارجی خالی v_پورٹ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t ux_New_نقاب_قدر );
    خارجی خالی v_مداخلت_Core( uint32_t ul_مداخلت_ID, uint8_t ucCoreID );
#اگر_ختم /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS() __asm متلون ( "SVC %0" : : "i" ( پورٹ_SVC_DISABLE_INTERRUPTS ) : "memory" )

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()  __asm متلون ( "SVC %0" : : "i" ( پورٹ_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کرو پورٹ_UNMASK_قدر           ( 0xFFUL )

#اگر !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #اگر  ( config_نمبر_کا_CORES == 1 )
        خارجی خالی v_پورٹ_Enter_Critical( خالی );
        خارجی خالی v_پورٹ_Exit_Critical( خالی );
        #تعریف_کرو پورٹ_ENTER_CRITICAL()                  v_پورٹ_Enter_Critical()
        #تعریف_کرو پورٹ_EXIT_CRITICAL()                   v_پورٹ_Exit_Critical()
    #ورنہ
        #تعریف_کرو پورٹ_ENTER_CRITICAL()                  vTaskEnterCritical()
        #تعریف_کرو پورٹ_EXIT_CRITICAL()                   vTaskExitCritical()
    #اگر_ختم
    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         ux_پورٹ_سیٹ_مداخلت_نقاب_From_ISR()
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٹ_Clear_مداخلت_نقاب_From_ISR( x )
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#اگر_ختم /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#اگر !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    خالی FreeRTOS_Tick_Handler( خالی );
#اگر_ختم /* if !defined(__ASSEMBLER__) */

#تعریف_کرو پورٹ_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#تعریف_کرو پورٹ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#اگر ( configUSE_TASK_FPU_SUPPORT == پورٹ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    خالی v_پورٹ_Task_استعمال_کرتا_FPU( خالی );
#ورنہ
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #تعریف_کرو v_پورٹ_Task_استعمال_کرتا_FPU()
#اگر_ختم

#تعریف_کرو پورٹ_TASK_استعمال_کرتا_FLOATING_نقطہ()          v_پورٹ_Task_استعمال_کرتا_FPU()

#تعریف_کرو پورٹ_سب_سے_نیچا_مداخلت_ترجیح           ( ( ( uint32_t ) config_UNIQUE_مداخلت_PRIORITIES ) - 1UL )
#تعریف_کرو پورٹ_سب_سے_نیچا_USABLE_مداخلت_ترجیح    ( پورٹ_سب_سے_نیچا_مداخلت_ترجیح - 1UL )

/* Architecture specific optimisations. */
#اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#اگر_ختم

#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31 - __builtin_clz( uxReadyPriorities ) )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#اگر ( configASSERT_DEFINED == 1 )
    خالی v_پورٹ_Validate_مداخلت_ترجیح( خالی );
    #تعریف_کرو پورٹ_ASSERT_IF_مداخلت_ترجیح_INVALID()    v_پورٹ_Validate_مداخلت_ترجیح()
#اگر_ختم /* configASSERT */

#تعریف_کرو پورٹ_NOP()     __asm متلون ( "NOP" )
#تعریف_کرو پورٹ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#اگر config_UNIQUE_مداخلت_PRIORITIES == 16
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            4
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    3
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 32
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            3
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    2
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 64
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            2
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    1
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 128
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            1
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#وگرنہ_اگر config_UNIQUE_مداخلت_PRIORITIES == 256
    #تعریف_کرو پورٹ_ترجیح_سرکاؤ            0
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#ورنہ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #غلطی Invalid config_UNIQUE_مداخلت_PRIORITIES setting.  config_UNIQUE_مداخلت_PRIORITIES must be سیٹ مقصد the نمبر کا unique priorities implemented by the ہدف hardware
#اگر_ختم /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#تعریف_کرو پورٹ_مداخلت_ترجیح_رجسٹر_انحراف    ( 0x400U )
#تعریف_کرو پورٹ_YIELD_CORE_INT_ID                     ( 0x0U )
#تعریف_کرو پورٹ_MAX_API_ترجیح_نقاب                 ( config_MAX_API_CALL_مداخلت_ترجیح << پورٹ_ترجیح_سرکاؤ )

#اگر ( config_نمبر_کا_CORES > 1 )

    #اگر !defined(__ASSEMBLER__)
        قسمتعریف شمار
        {
            e_Isr_تالا = 0,
            e_Task_تالا,
            e_تالا_گنتی
        } e_پورٹ_RTOSLock;

        خارجی متلون uint64_t ullCriticalNestings[ config_نمبر_کا_CORES ];
        خارجی خالی v_پورٹ_Recursive_تالا( uint8_t ucCoreID,
                                        e_پورٹ_RTOSLock e_تالا_عدد,
                                        بنیاد_Type_t uxAcquire );
        خارجی uint8_t uc_پورٹ_Get_Core_ID( خالی );
        خارجی uint8_t uc_پورٹ_Get_Core_IDFrom_Isr( خالی );
    #اگر_ختم /* if !defined(__ASSEMBLER__) */

    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب()         ux_پورٹ_سیٹ_مداخلت_نقاب()
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب( x )    v_پورٹ_Clear_مداخلت_نقاب( x )

    #تعریف_کرو پورٹ_MAX_CORE_گنتی               config_نمبر_کا_CORES
    #تعریف_کرو پورٹ_GET_CORE_ID()                uc_پورٹ_Get_Core_ID()
    #تعریف_کرو پورٹ_GET_CORE_ID_FROM_ISR()       uc_پورٹ_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #تعریف_کرو پورٹ_YIELD_CORE( xCoreID )                          v_مداخلت_Core( پورٹ_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #تعریف_کرو پورٹ_RELEASE_ISR_تالا( xCoreID )                    v_پورٹ_Recursive_تالا( ( uint8_t ) xCoreID, e_Isr_تالا, pdFALSE )
    #تعریف_کرو پورٹ_GET_ISR_تالا( xCoreID )                        v_پورٹ_Recursive_تالا( ( uint8_t ) xCoreID, e_Isr_تالا, pdTRUE )

    #تعریف_کرو پورٹ_RELEASE_TASK_تالا( xCoreID )                   v_پورٹ_Recursive_تالا( ( uint8_t ) xCoreID, e_Task_تالا, pdFALSE )
    #تعریف_کرو پورٹ_GET_TASK_تالا( xCoreID )                       v_پورٹ_Recursive_تالا( ( uint8_t ) xCoreID, e_Task_تالا, pdTRUE )
    #تعریف_کرو پورٹ_GET_CRITICAL_NESTING_گنتی( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کرو پورٹ_سیٹ_CRITICAL_NESTING_گنتی( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کرو پورٹ_INCREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کرو پورٹ_DECREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#اگر_ختم /* configNUMBER_OF_CORES > 1 */

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متلون ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#اگر ( configENABLE_MPU == 1 )

    #اگر !defined(__ASSEMBLER__)
        خارجی بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی );
    #اگر_ختم /* if !defined(__ASSEMBLER__) */

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
    #اگر_غیر_تعریف_شدہ config_کل_MPU_REGIONS
        #تعریف_کرو config_کل_MPU_REGIONS                  ( 16UL )
    #اگر_ختم

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

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #تعریف_کرو پورٹ_ACL_اندراج_سائز_بٹ ( 32UL )
    #اگر_ختم /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #اگر !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        قسمتعریف ساخت MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #اگر_غیر_تعریف_شدہ config_SYSTEM_CALL_ڈھیر_سائز
            #تعریف_کرو config_SYSTEM_CALL_ڈھیر_سائز 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #اگر_ختم

        /**
         * @brief System call info.
         */
        قسمتعریف ساخت SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_رجسٹر_At_System_Call_اندراج;
            uint64_t ull_User_SPAt_System_Call_اندراج;
        } xSYSTEM_CALL_INFO;
    #اگر_ختم /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #اگر ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #تعریف_کرو MAX_CONTEXT_سائز    102

    #ورنہ /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #تعریف_کرو MAX_CONTEXT_سائز    36
    #اگر_ختم /* #if ( configENABLE_FPU == 1 ) */

    #اگر !defined(__ASSEMBLER__)
        قسمتعریف ساخت MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ پورٹ_کل_عدد_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_سائز + config_SYSTEM_CALL_ڈھیر_سائز ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائز / پورٹ_ACL_اندراج_سائز_بٹ ) + 1 ];
            #اگر_ختم /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #اگر_ختم /* if !defined(__ASSEMBLER__) */

    #تعریف_کرو پورٹ_USING_MPU_WRAPPERS                        ( 1 )
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #تعریف_کرو پورٹ_MPU_معمول_حافظہ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #تعریف_کرو پورٹ_MPU_معمول_حافظہ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

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
    #تعریف_کرو پورٹ_جوڑو_UINT64_WILL_حد_سے_تجاوز( a, b )          ( ( a ) > ( پورٹ_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #تعریف_کرو پورٹ_نکالو_پہلا_پتہ_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & پورٹ_MPU_PRBAR_EL1_پتہ_نقاب )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #تعریف_کرو پورٹ_نکالو_آخری_پتہ_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & پورٹ_MPU_PRLAR_EL1_پتہ_نقاب ) | پورٹ_MPU_PRLAR_EL1_پتہ_IMPLIED_بٹ )

    /* Does addr lies within [start, end] address range? */
    #تعریف_کرو پورٹ_IS_پتہ_WITHIN_RANGE( addr, آغاز, انتہا ) \
        ( ( ( addr ) >= ( آغاز ) ) && ( ( addr ) <= ( انتہا ) ) )

    /* Is the access request satisfied by the available permissions? */
    #تعریف_کرو پورٹ_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #اگر ( configUSE_TASK_FPU_SUPPORT == پورٹ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #تعریف_کرو پورٹ_انحراف_مقصد_PC     ( 68 )
        #تعریف_کرو پورٹ_انحراف_مقصد_LR     ( 70 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X0     ( 100 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X1     ( 101 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X2     ( 98 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X3     ( 99 )
    #ورنہ
        #تعریف_کرو پورٹ_انحراف_مقصد_PC     ( 2 )
        #تعریف_کرو پورٹ_انحراف_مقصد_LR     ( 4 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X0     ( 34 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X1     ( 35 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X2     ( 32 )
        #تعریف_کرو پورٹ_انحراف_مقصد_X3     ( 33 )
    #اگر_ختم

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

#ورنہ

    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ        ( 0x0UL )

#اگر_ختم /* #if ( configENABLE_MPU == 1 ) */

#تعریف_کرو پورٹ_PSTATE_I_ثنائی_ہندسہ             ( 0x7 )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
