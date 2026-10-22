/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

/*------------------------------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
 *
 * These settings should not be altered.
 *------------------------------------------------------------------------------
 */

#جيڪڏهن_وصف_نه_ٿيل configENABLE_MPU
    #غلطي configENABLE_MPU must be defined اندريون FreeRTOSConfig.h.  سيٽ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#جيڪڏهن_پورو /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t        TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY   ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t        TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#وصف_ڪريو پورٽ_ARCH_NAME                      "Cortex-M0+"
#وصف_ڪريو پورٽ_ڍير_GROWTH                   ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT                 8
#وصف_ڪريو پورٽ_NOP()
#وصف_ڪريو پورٽ_INLINE                         __inline
#جيڪڏهن_وصف_نه_ٿيل پورٽ_FORCE_INLINE
    #وصف_ڪريو پورٽ_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#جيڪڏهن_پورو
#وصف_ڪريو پورٽ_DONT_DISCARD                   __attribute__( ( استعمال_ٿيل ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
خارجي بنياد_Type_t x_پورٽ_Is_Inside_مداخلت( فراغ );

خارجي فراغ v_پورٽ_Yield( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي فراغ v_پورٽ_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;
خارجي فراغ v_پورٽ_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي uint32_t ul_سيٽ_مداخلت_نقاب( فراغ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
خارجي فراغ v_Clear_مداخلت_نقاب( uint32_t ul_نقاب ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#إذا ( configENABLE_MPU == 1 )
    خارجي بنياد_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#جيڪڏهن_پورو /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #وصف_ڪريو پورٽ_USING_MPU_WRAPPERS          1
    #وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ               ( 0x80000000UL )
#وإلا
    #وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ               ( 0x0UL )
#جيڪڏهن_پورو /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#جيڪڏهن_وصف_نه_ٿيل configS_C_B_FLASH
    #وصف_ڪريو configS_C_B_FLASH               ( 0x07UL )
#جيڪڏهن_پورو

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#جيڪڏهن_وصف_نه_ٿيل configS_C_B_SRAM
    #وصف_ڪريو configS_C_B_SRAM                ( 0x07UL )
#جيڪڏهن_پورو

/* MPU regions. */
#وصف_ڪريو پورٽ_PRIVILEGED_RAM_REGION           ( 7UL )
#وصف_ڪريو پورٽ_PRIVILEGED_FLASH_REGION         ( 6UL )
#وصف_ڪريو پورٽ_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#وصف_ڪريو پورٽ_ڍير_REGION                    ( 4UL )
#وصف_ڪريو پورٽ_پهريون_CONFIGURABLE_REGION       ( 0UL )
#وصف_ڪريو پورٽ_آخري_CONFIGURABLE_REGION        ( 3UL )
#وصف_ڪريو پورٽ_انگ_CONFIGURABLE_REGIONS        ( 4UL )
#وصف_ڪريو پورٽ_ڪل_انگ_REGIONS               ( پورٽ_انگ_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_256_B            ( 0x07UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_512_B            ( 0x08UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_1_KB             ( 0x09UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_2_KB             ( 0x0AUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_4_KB             ( 0x0BUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_8_KB             ( 0x0CUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_16_KB            ( 0x0DUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_32_KB            ( 0x0EUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_64_KB            ( 0x0FUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_128_KB           ( 0x10UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_256_KB           ( 0x11UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_512_KB           ( 0x12UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_1_MB             ( 0x13UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_2_MB             ( 0x14UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_4_MB             ( 0x15UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_8_MB             ( 0x16UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_16_MB            ( 0x17UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_32_MB            ( 0x18UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_64_MB            ( 0x19UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_128_MB           ( 0x1AUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_256_MB           ( 0x1BUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_512_MB           ( 0x1CUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_1_GB             ( 0x1DUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_2_GB             ( 0x1EUL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_سائيز_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#وصف_ڪريو پورٽ_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#وصف_ڪريو پورٽ_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#وصف_ڪريو پورٽ_MPU_REGION_عام_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#وصف_ڪريو پورٽ_MPU_REGION_عام_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#وصف_ڪريو پورٽ_MPU_REGION_عام_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#وصف_ڪريو پورٽ_MPU_REGION_عام_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#وصف_ڪريو پورٽ_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    تعريفنوع بنية MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
    } MPURegionSettings_t;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #جيڪڏهن_وصف_نه_ٿيل config_SYSTEM_CALL_ڍير_سائيز
            #غلطي config_SYSTEM_CALL_ڍير_سائيز must be defined منزل the desired سائيز جو the system call ڍير اندريون لفظ لكل using MPU wrappers v2.
        #جيڪڏهن_پورو

        /**
         * @brief System call stack.
         */
        تعريفنوع بنية SYSTEM_CALL_ڍير_INFO
        {
            uint32_t ul_System_Call_ڍير_بفر[ config_SYSTEM_CALL_ڍير_سائيز ];
            uint32_t * pul_System_Call_ڍير;
            uint32_t * pul_Task_ڍير;
            uint32_t ul_Link_رجسٽر_At_System_Call_داخلا;
        } x_SYSTEM_CALL_ڍير_INFO;

    #جيڪڏهن_پورو /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */

    /*
     * +----------+-----------------+---------------+-----+
     * |  r4-r11  | r0-r3, r12, LR, | PSP, CONTROL  |     |
     * |          | PC, xPSR        | EXC_RETURN    |     |
     * +----------+-----------------+---------------+-----+
     *
     * <---------><----------------><---------------><---->
     *     8               8                3          1
     */
    #وصف_ڪريو CONTEXT_سائيز    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #وصف_ڪريو پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #وصف_ڪريو پورٽ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #وصف_ڪريو پورٽ_ACL_داخلا_سائيز_بٽ             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ پورٽ_ڪل_انگ_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_سائيز ];
        uint32_t ulTaskFlags;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ڍير_INFO x_System_Call_ڍير_Info;
            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائيز / پورٽ_ACL_داخلا_سائيز_بٽ ) + 1 ];
            #جيڪڏهن_پورو
        #جيڪڏهن_پورو
    } xMPU_SETTINGS;

#جيڪڏهن_پورو /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#وصف_ڪريو پورٽ_SVC_شروعات_SCHEDULER            100
#وصف_ڪريو پورٽ_SVC_RAISE_PRIVILEGE            101
#وصف_ڪريو پورٽ_SVC_SYSTEM_CALL_EXIT           102
#وصف_ڪريو پورٽ_SVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#إذا ( configENABLE_MPU == 1 )
    #وصف_ڪريو پورٽ_YIELD()               __asm متطاير ( "svc %0" ::"i" ( پورٽ_SVC_YIELD ) : "memory" )
    #وصف_ڪريو پورٽ_YIELD_WITHIN_API()    v_پورٽ_Yield()
#وإلا
    #وصف_ڪريو پورٽ_YIELD()               v_پورٽ_Yield()
    #وصف_ڪريو پورٽ_YIELD_WITHIN_API()    v_پورٽ_Yield()
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#وصف_ڪريو پورٽ_NVIC_PENDSVSET_ٻٽو_انگ    ( 1UL << 28UL )
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()       ul_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )  v_Clear_مداخلت_نقاب( x )
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                __asm متطاير ( " cpsid i " ::: "memory" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                 __asm متطاير ( " cpsie i " ::: "memory" )
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                    v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()                     v_پورٽ_Exit_Critical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#جيڪڏهن_وصف_نه_ٿيل پورٽ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورٽ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت );
    #وصف_ڪريو پورٽ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وقت )    v_پورٽ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وقت )
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #وصف_ڪريو پورٽ_IS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #وصف_ڪريو پورٽ_RAISE_PRIVILEGE()    __asm متطاير ( "svc %0 \n" ::"i" ( پورٽ_SVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #وصف_ڪريو پورٽ_RESET_PRIVILEGE()    vResetPrivilege()

#وإلا

    #وصف_ڪريو پورٽ_IS_PRIVILEGED()
    #وصف_ڪريو پورٽ_RAISE_PRIVILEGE()
    #وصف_ڪريو پورٽ_RESET_PRIVILEGE()

#جيڪڏهن_پورو /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    خارجي بنياد_Type_t x_پورٽ_Is_Task_Privileged( فراغ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #وصف_ڪريو پورٽ_IS_TASK_PRIVILEGED()    x_پورٽ_Is_Task_Privileged()

#جيڪڏهن_پورو /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
