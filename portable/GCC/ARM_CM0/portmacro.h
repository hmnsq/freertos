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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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

#جے_بنا_تعریف configENABLE_MPU
    #غلطی configENABLE_MPU must be defined وچ FreeRTOSConfig.h.  سیٹ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#جے_انت /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع لما             ادھار_Type_t;
تعريفنوع بنانشانی لما    UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t        TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY   ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t        TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#تعریف_کرو پورٹ_ARCH_NAME                      "Cortex-M0+"
#تعریف_کرو پورٹ_ڈھیر_GROWTH                   ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT                 8
#تعریف_کرو پورٹ_NOP()
#تعریف_کرو پورٹ_INLINE                         __inline
#جے_بنا_تعریف پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#جے_انت
#تعریف_کرو پورٹ_DONT_DISCARD                   __attribute__( ( ورتیا ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
خارجي ادھار_Type_t x_پورٹ_Is_Inside_رکاوٹ( فراغ );

خارجي فراغ v_پورٹ_Yield( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي فراغ v_پورٹ_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;
خارجي فراغ v_پورٹ_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي uint32_t ul_سیٹ_رکاوٹ_نقاب( فراغ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
خارجي فراغ v_Clear_رکاوٹ_نقاب( uint32_t ul_نقاب ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#إذا ( configENABLE_MPU == 1 )
    خارجي ادھار_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#جے_انت /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کرو پورٹ_USING_MPU_WRAPPERS          1
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ               ( 0x80000000UL )
#وإلا
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ               ( 0x0UL )
#جے_انت /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#جے_بنا_تعریف configS_C_B_FLASH
    #تعریف_کرو configS_C_B_FLASH               ( 0x07UL )
#جے_انت

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#جے_بنا_تعریف configS_C_B_SRAM
    #تعریف_کرو configS_C_B_SRAM                ( 0x07UL )
#جے_انت

/* MPU regions. */
#تعریف_کرو پورٹ_PRIVILEGED_RAM_REGION           ( 7UL )
#تعریف_کرو پورٹ_PRIVILEGED_FLASH_REGION         ( 6UL )
#تعریف_کرو پورٹ_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#تعریف_کرو پورٹ_ڈھیر_REGION                    ( 4UL )
#تعریف_کرو پورٹ_پہلا_CONFIGURABLE_REGION       ( 0UL )
#تعریف_کرو پورٹ_آخری_CONFIGURABLE_REGION        ( 3UL )
#تعریف_کرو پورٹ_عدد_CONFIGURABLE_REGIONS        ( 4UL )
#تعریف_کرو پورٹ_کل_عدد_REGIONS               ( پورٹ_عدد_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#تعریف_کرو پورٹ_MPU_REGION_ناپ_256_B            ( 0x07UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_512_B            ( 0x08UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_1_KB             ( 0x09UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_2_KB             ( 0x0AUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_4_KB             ( 0x0BUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_8_KB             ( 0x0CUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_16_KB            ( 0x0DUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_32_KB            ( 0x0EUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_64_KB            ( 0x0FUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_128_KB           ( 0x10UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_256_KB           ( 0x11UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_512_KB           ( 0x12UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_1_MB             ( 0x13UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_2_MB             ( 0x14UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_4_MB             ( 0x15UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_8_MB             ( 0x16UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_16_MB            ( 0x17UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_32_MB            ( 0x18UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_64_MB            ( 0x19UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_128_MB           ( 0x1AUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_256_MB           ( 0x1BUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_512_MB           ( 0x1CUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_1_GB             ( 0x1DUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_2_GB             ( 0x1EUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_ناپ_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کرو پورٹ_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#تعریف_کرو پورٹ_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#تعریف_کرو پورٹ_MPU_REGION_عام_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#تعریف_کرو پورٹ_MPU_REGION_عام_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#تعریف_کرو پورٹ_MPU_REGION_عام_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#تعریف_کرو پورٹ_MPU_REGION_عام_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#تعریف_کرو پورٹ_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

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

        #جے_بنا_تعریف config_SYSTEM_CALL_ڈھیر_ناپ
            #غلطی config_SYSTEM_CALL_ڈھیر_ناپ must be defined منزل the desired ناپ دا the system call ڈھیر وچ الفاظ لكل using MPU wrappers v2.
        #جے_انت

        /**
         * @brief System call stack.
         */
        تعريفنوع بنية SYSTEM_CALL_ڈھیر_INFO
        {
            uint32_t ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_ناپ ];
            uint32_t * pul_System_Call_ڈھیر;
            uint32_t * pul_Task_ڈھیر;
            uint32_t ul_Link_رجسٹر_At_System_Call_اندراج;
        } x_SYSTEM_CALL_ڈھیر_INFO;

    #جے_انت /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #تعریف_کرو CONTEXT_ناپ    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کرو پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کرو پورٹ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کرو پورٹ_ACL_اندراج_ناپ_بٹ             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ پورٹ_کل_عدد_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_ناپ ];
        uint32_t ulTaskFlags;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ڈھیر_INFO x_System_Call_ڈھیر_Info;
            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ناپ / پورٹ_ACL_اندراج_ناپ_بٹ ) + 1 ];
            #جے_انت
        #جے_انت
    } xMPU_SETTINGS;

#جے_انت /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#تعریف_کرو پورٹ_SVC_شروع_SCHEDULER            100
#تعریف_کرو پورٹ_SVC_RAISE_PRIVILEGE            101
#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT           102
#تعریف_کرو پورٹ_SVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کرو پورٹ_YIELD()               __asm متطاير ( "svc %0" ::"i" ( پورٹ_SVC_YIELD ) : "memory" )
    #تعریف_کرو پورٹ_YIELD_WITHIN_API()    v_پورٹ_Yield()
#وإلا
    #تعریف_کرو پورٹ_YIELD()               v_پورٹ_Yield()
    #تعریف_کرو پورٹ_YIELD_WITHIN_API()    v_پورٹ_Yield()
#جے_انت

#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()       ul_سیٹ_رکاوٹ_نقاب()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )  v_Clear_رکاوٹ_نقاب( x )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                __asm متطاير ( " cpsid i " ::: "memory" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                 __asm متطاير ( " cpsie i " ::: "memory" )
#تعریف_کرو پورٹ_ENTER_CRITICAL()                    v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                     v_پورٹ_Exit_Critical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#جے_بنا_تعریف پورٹ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا );
    #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ویلا )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ویلا )
#جے_انت
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #تعریف_کرو پورٹ_IS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #تعریف_کرو پورٹ_RAISE_PRIVILEGE()    __asm متطاير ( "svc %0 \n" ::"i" ( پورٹ_SVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #تعریف_کرو پورٹ_RESET_PRIVILEGE()    vResetPrivilege()

#وإلا

    #تعریف_کرو پورٹ_IS_PRIVILEGED()
    #تعریف_کرو پورٹ_RAISE_PRIVILEGE()
    #تعریف_کرو پورٹ_RESET_PRIVILEGE()

#جے_انت /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    خارجي ادھار_Type_t x_پورٹ_Is_Task_Privileged( فراغ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #تعریف_کرو پورٹ_IS_TASK_PRIVILEGED()    x_پورٹ_Is_Task_Privileged()

#جے_انت /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
