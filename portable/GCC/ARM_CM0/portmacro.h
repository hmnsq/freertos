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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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

#اگر_تعریف_نشده configENABLE_MPU
    #خطا configENABLE_MPU must be defined درون FreeRTOSConfig.h.  مجموعه_2 configENABLE_MPU مقصد 1 مقصد enable the MPU or 0 مقصد disable the MPU.
#پایان_اگر /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t        TickType_t;
    #تعریف_کن پورت_MAX_DELAY   ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t        TickType_t;
    #تعریف_کن پورت_MAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#تعریف_کن پورت_ARCH_NAME                      "Cortex-M0+"
#تعریف_کن پورت_پشته_GROWTH                   ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT                 8
#تعریف_کن پورت_NOP()
#تعریف_کن پورت_INLINE                         __inline
#اگر_تعریف_نشده پورت_FORCE_INLINE
    #تعریف_کن پورت_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#پایان_اگر
#تعریف_کن پورت_DONT_DISCARD                   __attribute__( ( استفاده_شده ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
خارجي پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ );

خارجي فراغ v_پورت_Yield( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي فراغ v_پورت_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;
خارجي فراغ v_پورت_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي uint32_t ul_مجموعه_وقفه_ماسک( فراغ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
خارجي فراغ v_Clear_وقفه_ماسک( uint32_t ul_ماسک ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#إذا ( configENABLE_MPU == 1 )
    خارجي پایه_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#پایان_اگر /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کن پورت_USING_MPU_WRAPPERS          1
    #تعریف_کن پورت_PRIVILEGE_بیت               ( 0x80000000UL )
#وإلا
    #تعریف_کن پورت_PRIVILEGE_بیت               ( 0x0UL )
#پایان_اگر /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#اگر_تعریف_نشده configS_C_B_FLASH
    #تعریف_کن configS_C_B_FLASH               ( 0x07UL )
#پایان_اگر

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#اگر_تعریف_نشده configS_C_B_SRAM
    #تعریف_کن configS_C_B_SRAM                ( 0x07UL )
#پایان_اگر

/* MPU regions. */
#تعریف_کن پورت_PRIVILEGED_RAM_REGION           ( 7UL )
#تعریف_کن پورت_PRIVILEGED_FLASH_REGION         ( 6UL )
#تعریف_کن پورت_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#تعریف_کن پورت_پشته_REGION                    ( 4UL )
#تعریف_کن پورت_اولی_CONFIGURABLE_REGION       ( 0UL )
#تعریف_کن پورت_آخرین_CONFIGURABLE_REGION        ( 3UL )
#تعریف_کن پورت_رقم_CONFIGURABLE_REGIONS        ( 4UL )
#تعریف_کن پورت_مجموع_رقم_REGIONS               ( پورت_رقم_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#تعریف_کن پورت_MPU_REGION_اندازه_256_B            ( 0x07UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_512_B            ( 0x08UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_1_KB             ( 0x09UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_2_KB             ( 0x0AUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_4_KB             ( 0x0BUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_8_KB             ( 0x0CUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_16_KB            ( 0x0DUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_32_KB            ( 0x0EUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_64_KB            ( 0x0FUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_128_KB           ( 0x10UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_256_KB           ( 0x11UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_512_KB           ( 0x12UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_1_MB             ( 0x13UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_2_MB             ( 0x14UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_4_MB             ( 0x15UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_8_MB             ( 0x16UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_16_MB            ( 0x17UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_32_MB            ( 0x18UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_64_MB            ( 0x19UL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_128_MB           ( 0x1AUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_256_MB           ( 0x1BUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_512_MB           ( 0x1CUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_1_GB             ( 0x1DUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_2_GB             ( 0x1EUL << 1UL )
#تعریف_کن پورت_MPU_REGION_اندازه_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کن پورت_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#تعریف_کن پورت_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#تعریف_کن پورت_MPU_REGION_نرمال_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#تعریف_کن پورت_MPU_REGION_نرمال_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#تعریف_کن پورت_MPU_REGION_نرمال_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#تعریف_کن پورت_MPU_REGION_نرمال_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#تعریف_کن پورت_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#تعریف_کن پورت_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

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

        #اگر_تعریف_نشده config_SYSTEM_CALL_پشته_اندازه
            #خطا config_SYSTEM_CALL_پشته_اندازه must be defined مقصد the desired اندازه از the system call پشته درون واژگان لكل using MPU wrappers v2.
        #پایان_اگر

        /**
         * @brief System call stack.
         */
        تعريفنوع بنية SYSTEM_CALL_پشته_INFO
        {
            uint32_t ul_System_Call_پشته_میانگیر[ config_SYSTEM_CALL_پشته_اندازه ];
            uint32_t * pul_System_Call_پشته;
            uint32_t * pul_Task_پشته;
            uint32_t ul_Link_ثبات_At_System_Call_مدخل;
        } x_SYSTEM_CALL_پشته_INFO;

    #پایان_اگر /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #تعریف_کن CONTEXT_اندازه    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کن پورت_پشته_قاب_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کن پورت_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کن پورت_ACL_مدخل_اندازه_بیتها             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ پورت_مجموع_رقم_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_اندازه ];
        uint32_t ulTaskFlags;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_پشته_INFO x_System_Call_پشته_Info;
            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورت_ACL_مدخل_اندازه_بیتها ) + 1 ];
            #پایان_اگر
        #پایان_اگر
    } xMPU_SETTINGS;

#پایان_اگر /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#تعریف_کن پورت_SVC_شروع_SCHEDULER            100
#تعریف_کن پورت_SVC_RAISE_PRIVILEGE            101
#تعریف_کن پورت_SVC_SYSTEM_CALL_EXIT           102
#تعریف_کن پورت_SVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کن پورت_YIELD()               __asm متطاير ( "svc %0" ::"i" ( پورت_SVC_YIELD ) : "memory" )
    #تعریف_کن پورت_YIELD_WITHIN_API()    v_پورت_Yield()
#وإلا
    #تعریف_کن پورت_YIELD()               v_پورت_Yield()
    #تعریف_کن پورت_YIELD_WITHIN_API()    v_پورت_Yield()
#پایان_اگر

#تعریف_کن پورت_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کن پورت_NVIC_PENDSVSET_بیت    ( 1UL << 28UL )
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()       ul_مجموعه_وقفه_ماسک()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )  v_Clear_وقفه_ماسک( x )
#تعریف_کن پورت_DISABLE_INTERRUPTS()                __asm متطاير ( " cpsid i " ::: "memory" )
#تعریف_کن پورت_ENABLE_INTERRUPTS()                 __asm متطاير ( " cpsie i " ::: "memory" )
#تعریف_کن پورت_ENTER_CRITICAL()                    v_پورت_Enter_Critical()
#تعریف_کن پورت_EXIT_CRITICAL()                     v_پورت_Exit_Critical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#اگر_تعریف_نشده پورت_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان );
    #تعریف_کن پورت_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_زمان )    v_پورت_Suppress_Ticks_And_Sleep( x_Expected_Idle_زمان )
#پایان_اگر
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #تعریف_کن پورت_IS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #تعریف_کن پورت_RAISE_PRIVILEGE()    __asm متطاير ( "svc %0 \n" ::"i" ( پورت_SVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #تعریف_کن پورت_RESET_PRIVILEGE()    vResetPrivilege()

#وإلا

    #تعریف_کن پورت_IS_PRIVILEGED()
    #تعریف_کن پورت_RAISE_PRIVILEGE()
    #تعریف_کن پورت_RESET_PRIVILEGE()

#پایان_اگر /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    خارجي پایه_Type_t x_پورت_Is_Task_Privileged( فراغ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #تعریف_کن پورت_IS_TASK_PRIVILEGED()    x_پورت_Is_Task_Privileged()

#پایان_اگر /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
