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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    size_t
#تعریف_کن پورت_پایه_TYPE     دراز

#إذا !defined(__ASSEMBLER__)
    تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
    تعريفنوع پورت_پایه_TYPE    پایه_Type_t;
    تعريفنوع uint64_t         UBaseType_t;

    تعريفنوع uint64_t         TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#پایان_اگر /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_پشته_GROWTH         ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT       16
#تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#إذا !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #إذا ( config_عدد_از_CORES == 1 )
        #تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            خارجي uint64_t ull_پورت_Yield_Required;        \
                                                        \
            إذا( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_پورت_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #وإلا
        #تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            خارجي uint64_t ull_پورت_Yield_Required[ config_عدد_از_CORES ]; \
                                                                        \
            إذا( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_پورت_Yield_Required[ پورت_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #پایان_اگر /* if ( configNUMBER_OF_CORES == 1 ) */
#پایان_اگر /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#تعریف_کن پورت_SVC_SYSTEM_CALL_EXIT                    104
#تعریف_کن پورت_SVC_YIELD                               105
#تعریف_کن پورت_SVC_شروع_اولی_TASK                    106
#تعریف_کن پورت_SVC_DISABLE_INTERRUPTS                  107
#تعریف_کن پورت_SVC_ENABLE_INTERRUPTS                   108
#تعریف_کن پورت_SVC_GET_CORE_ID                         109
#تعریف_کن پورت_SVC_ماسک_ALL_INTERRUPTS                 110
#تعریف_کن پورت_SVC_UNMASK_ALL_INTERRUPTS               111
#تعریف_کن پورت_SVC_UNMASK_INTERRUPTS                   112
#تعریف_کن پورت_SVC_CHECK_PRIVILEGE                     113
#تعریف_کن پورت_SVC_SAVE_TASK_CONTEXT                   114
#تعریف_کن پورت_SVC_RESTORE_CONTEXT                     115
#تعریف_کن پورت_SVC_DELETE_CURRENT_TASK                 116
#تعریف_کن پورت_SVC_وقفه_CORE                      117

#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
#تعریف_کن پورت_YIELD()                __asm متطاير ( "SVC %0" : : "i" ( پورت_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#إذا !defined(__ASSEMBLER__)
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_وقفه_وضعیت );
    خارجي UBaseType_t ux_پورت_مجموعه_وقفه_ماسک( فراغ );
    خارجي UBaseType_t ux_پورت_مجموعه_وقفه_ماسک_From_ISR( فراغ );
    خارجي فراغ v_پورت_Clear_وقفه_ماسک( UBaseType_t ux_New_ماسک_مقدار );
    خارجي فراغ v_پورت_Clear_وقفه_ماسک_From_ISR( UBaseType_t ux_New_ماسک_مقدار );
    خارجي فراغ v_وقفه_Core( uint32_t ul_وقفه_ID, uint8_t ucCoreID );
#پایان_اگر /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#تعریف_کن پورت_DISABLE_INTERRUPTS() __asm متطاير ( "SVC %0" : : "i" ( پورت_SVC_DISABLE_INTERRUPTS ) : "memory" )

#تعریف_کن پورت_ENABLE_INTERRUPTS()  __asm متطاير ( "SVC %0" : : "i" ( پورت_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#تعریف_کن پورت_UNMASK_مقدار           ( 0xFFUL )

#إذا !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #إذا  ( config_عدد_از_CORES == 1 )
        خارجي فراغ v_پورت_Enter_Critical( فراغ );
        خارجي فراغ v_پورت_Exit_Critical( فراغ );
        #تعریف_کن پورت_ENTER_CRITICAL()                  v_پورت_Enter_Critical()
        #تعریف_کن پورت_EXIT_CRITICAL()                   v_پورت_Exit_Critical()
    #وإلا
        #تعریف_کن پورت_ENTER_CRITICAL()                  vTaskEnterCritical()
        #تعریف_کن پورت_EXIT_CRITICAL()                   vTaskExitCritical()
    #پایان_اگر
    #تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ux_پورت_مجموعه_وقفه_ماسک_From_ISR()
    #تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_پورت_Clear_وقفه_ماسک_From_ISR( x )
    #تعریف_کن پورت_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کن پورت_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#پایان_اگر /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    فراغ FreeRTOS_Tick_Handler( فراغ );
#پایان_اگر /* if !defined(__ASSEMBLER__) */

#تعریف_کن پورت_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#تعریف_کن پورت_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT == پورت_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ );
#وإلا
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #تعریف_کن v_پورت_Task_استفاده_میکند_FPU()
#پایان_اگر

#تعریف_کن پورت_TASK_استفاده_میکند_FLOATING_نقطه()          v_پورت_Task_استفاده_میکند_FPU()

#تعریف_کن پورت_پایینترین_وقفه_اولویت           ( ( ( uint32_t ) config_UNIQUE_وقفه_PRIORITIES ) - 1UL )
#تعریف_کن پورت_پایینترین_USABLE_وقفه_اولویت    ( پورت_پایینترین_وقفه_اولویت - 1UL )

/* Architecture specific optimisations. */
#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
#پایان_اگر

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31 - __builtin_clz( uxReadyPriorities ) )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورت_Validate_وقفه_اولویت( فراغ );
    #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    v_پورت_Validate_وقفه_اولویت()
#پایان_اگر /* configASSERT */

#تعریف_کن پورت_NOP()     __asm متطاير ( "NOP" )
#تعریف_کن پورت_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_وقفه_PRIORITIES == 16
    #تعریف_کن پورت_اولویت_لغزش            4
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    3
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 32
    #تعریف_کن پورت_اولویت_لغزش            3
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    2
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 64
    #تعریف_کن پورت_اولویت_لغزش            2
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    1
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 128
    #تعریف_کن پورت_اولویت_لغزش            1
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    0
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 256
    #تعریف_کن پورت_اولویت_لغزش            0
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #خطا Invalid config_UNIQUE_وقفه_PRIORITIES setting.  config_UNIQUE_وقفه_PRIORITIES must be مجموعه مقصد the عدد از unique priorities implemented by the هدف hardware
#پایان_اگر /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#تعریف_کن پورت_وقفه_اولویت_ثبات_جابه_جایی    ( 0x400U )
#تعریف_کن پورت_YIELD_CORE_INT_ID                     ( 0x0U )
#تعریف_کن پورت_MAX_API_اولویت_ماسک                 ( config_MAX_API_CALL_وقفه_اولویت << پورت_اولویت_لغزش )

#إذا ( config_عدد_از_CORES > 1 )

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع تعداد
        {
            e_Isr_قفل = 0,
            e_Task_قفل,
            e_قفل_شمار
        } e_پورت_RTOSLock;

        خارجي متطاير uint64_t ullCriticalNestings[ config_عدد_از_CORES ];
        خارجي فراغ v_پورت_Recursive_قفل( uint8_t ucCoreID,
                                        e_پورت_RTOSLock e_قفل_رقم,
                                        پایه_Type_t uxAcquire );
        خارجي uint8_t uc_پورت_Get_Core_ID( فراغ );
        خارجي uint8_t uc_پورت_Get_Core_IDFrom_Isr( فراغ );
    #پایان_اگر /* if !defined(__ASSEMBLER__) */

    #تعریف_کن پورت_مجموعه_وقفه_ماسک()         ux_پورت_مجموعه_وقفه_ماسک()
    #تعریف_کن پورت_CLEAR_وقفه_ماسک( x )    v_پورت_Clear_وقفه_ماسک( x )

    #تعریف_کن پورت_MAX_CORE_شمار               config_عدد_از_CORES
    #تعریف_کن پورت_GET_CORE_ID()                uc_پورت_Get_Core_ID()
    #تعریف_کن پورت_GET_CORE_ID_FROM_ISR()       uc_پورت_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #تعریف_کن پورت_YIELD_CORE( xCoreID )                          v_وقفه_Core( پورت_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )                    v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Isr_قفل, pdFALSE )
    #تعریف_کن پورت_GET_ISR_قفل( xCoreID )                        v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Isr_قفل, pdTRUE )

    #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )                   v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Task_قفل, pdFALSE )
    #تعریف_کن پورت_GET_TASK_قفل( xCoreID )                       v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Task_قفل, pdTRUE )
    #تعریف_کن پورت_GET_CRITICAL_NESTING_شمار( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کن پورت_مجموعه_CRITICAL_NESTING_شمار( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کن پورت_INCREMENT_CRITICAL_NESTING_شمار( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کن پورت_DECREMENT_CRITICAL_NESTING_شمار( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#پایان_اگر /* configNUMBER_OF_CORES > 1 */

#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )

    #إذا !defined(__ASSEMBLER__)
        خارجي پایه_Type_t x_پورت_Is_Task_Privileged( فراغ );
    #پایان_اگر /* if !defined(__ASSEMBLER__) */

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
    #تعریف_کن پورت_MPU_DEVICE_حافظه_n_Gn_Rn_E                 ( 0x00 )
    #تعریف_کن پورت_MPU_DEVICE_حافظه_n_Gn_RE                  ( 0x04 )
    #تعریف_کن پورت_MPU_DEVICE_حافظه_n_GRE                   ( 0x08 )
    #تعریف_کن پورت_MPU_DEVICE_حافظه_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #اگر_تعریف_نشده config_مجموع_MPU_REGIONS
        #تعریف_کن config_مجموع_MPU_REGIONS                  ( 16UL )
    #پایان_اگر

    #تعریف_کن پورت_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #تعریف_کن پورت_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #تعریف_کن پورت_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #تعریف_کن پورت_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #تعریف_کن پورت_پشته_REGION                             ( 4ULL )                                /* Stack region number. */
    #تعریف_کن پورت_پشته_REGION_شاخص                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #تعریف_کن پورت_اولی_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #تعریف_کن پورت_آخرین_CONFIGURABLE_REGION                 ( config_مجموع_MPU_REGIONS - 1UL )
    #تعریف_کن پورت_رقم_CONFIGURABLE_REGIONS                 ( ( پورت_آخرین_CONFIGURABLE_REGION - پورت_اولی_CONFIGURABLE_REGION ) + 1 )
    #تعریف_کن پورت_مجموع_رقم_REGIONS                        ( پورت_رقم_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #تعریف_کن پورت_ACL_مدخل_اندازه_بیتها ( 32UL )
    #پایان_اگر /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #إذا !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        تعريفنوع بنية MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #اگر_تعریف_نشده config_SYSTEM_CALL_پشته_اندازه
            #تعریف_کن config_SYSTEM_CALL_پشته_اندازه 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #پایان_اگر

        /**
         * @brief System call info.
         */
        تعريفنوع بنية SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_ثبات_At_System_Call_مدخل;
            uint64_t ull_User_SPAt_System_Call_مدخل;
        } xSYSTEM_CALL_INFO;
    #پایان_اگر /* if !defined(__ASSEMBLER__) */

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
        #تعریف_کن MAX_CONTEXT_اندازه    102

    #وإلا /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #تعریف_کن MAX_CONTEXT_اندازه    36
    #پایان_اگر /* #if ( configENABLE_FPU == 1 ) */

    #إذا !defined(__ASSEMBLER__)
        تعريفنوع بنية MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ پورت_مجموع_رقم_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_اندازه + config_SYSTEM_CALL_پشته_اندازه ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورت_ACL_مدخل_اندازه_بیتها ) + 1 ];
            #پایان_اگر /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #پایان_اگر /* if !defined(__ASSEMBLER__) */

    #تعریف_کن پورت_USING_MPU_WRAPPERS                        ( 1 )
    #تعریف_کن پورت_PRIVILEGE_بیت                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #تعریف_کن پورت_MPU_نرمال_حافظه_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #تعریف_کن پورت_MPU_نرمال_حافظه_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR0_ماسک                   ( 0x00000000000000ffULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR1_ماسک                   ( 0x000000000000ff00ULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR2_ماسک                   ( 0x0000000000ff0000ULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR3_ماسک                   ( 0x00000000ff000000ULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR4_ماسک                   ( 0x000000ff00000000ULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR5_ماسک                   ( 0x0000ff0000000000ULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR6_ماسک                   ( 0x00ff000000000000ULL )

    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #تعریف_کن پورت_MPU_MAIR_EL1_ATTR7_ماسک                   ( 0xff00000000000000ULL )

    #تعریف_کن پورت_MPU_PRBAR_EL1_آدرس_ماسک                ( 0x0000FFFFFFFFFFC0ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_آدرس_ماسک                ( 0x0000FFFFFFFFFFC0ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_آدرس_IMPLIED_بیتها        ( 0x000000000000003FULL )
    #تعریف_کن پورت_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ماسک     ( 3ULL<< 2ULL )

    #تعریف_کن پورت_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #تعریف_کن پورت_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #تعریف_کن پورت_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #تعریف_کن پورت_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #تعریف_کن پورت_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #تعریف_کن پورت_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #تعریف_کن پورت_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #تعریف_کن پورت_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #تعریف_کن پورت_MPU_ENABLE_بیت                            ( 1ULL << 0ULL )
    #تعریف_کن پورت_MPU_PRIV_BACKGROUND_ENABLE_بیت            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #تعریف_کن پورت_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #تعریف_کن پورت_جمع_کن_UINT64_WILL_سرریز( a, b )          ( ( a ) > ( پورت_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #تعریف_کن پورت_استخراج_اولی_آدرس_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & پورت_MPU_PRBAR_EL1_آدرس_ماسک )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #تعریف_کن پورت_استخراج_آخرین_آدرس_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & پورت_MPU_PRLAR_EL1_آدرس_ماسک ) | پورت_MPU_PRLAR_EL1_آدرس_IMPLIED_بیتها )

    /* Does addr lies within [start, end] address range? */
    #تعریف_کن پورت_IS_آدرس_WITHIN_RANGE( addr, شروع, انتها ) \
        ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( انتها ) ) )

    /* Is the access request satisfied by the available permissions? */
    #تعریف_کن پورت_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #إذا ( configUSE_TASK_FPU_SUPPORT == پورت_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #تعریف_کن پورت_جابه_جایی_مقصد_PC     ( 68 )
        #تعریف_کن پورت_جابه_جایی_مقصد_LR     ( 70 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X0     ( 100 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X1     ( 101 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X2     ( 98 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X3     ( 99 )
    #وإلا
        #تعریف_کن پورت_جابه_جایی_مقصد_PC     ( 2 )
        #تعریف_کن پورت_جابه_جایی_مقصد_LR     ( 4 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X0     ( 34 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X1     ( 35 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X2     ( 32 )
        #تعریف_کن پورت_جابه_جایی_مقصد_X3     ( 33 )
    #پایان_اگر

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #تعریف_کن پورت_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #تعریف_کن پورت_IS_TASK_PRIVILEGED() x_پورت_Is_Task_Privileged()

#وإلا

    #تعریف_کن پورت_PRIVILEGE_بیت        ( 0x0UL )

#پایان_اگر /* #if ( configENABLE_MPU == 1 ) */

#تعریف_کن پورت_PSTATE_I_بیت             ( 0x7 )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
