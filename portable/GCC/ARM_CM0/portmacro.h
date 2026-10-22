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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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

#اگر_غیر_تعریف_شدہ configENABLE_MPU
    #غلطی configENABLE_MPU must be defined اندر FreeRTOSConfig.h.  سیٹ_2 configENABLE_MPU مقصد 1 مقصد enable the MPU or 0 مقصد disable the MPU.
#اگر_ختم /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE     طویل

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t        TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY   ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t        TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
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
#اگر_غیر_تعریف_شدہ پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE               اندرونی __attribute__( ( always_inline ) )
#اگر_ختم
#تعریف_کرو پورٹ_DONT_DISCARD                   __attribute__( ( مستعمل ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
خارجی بنیاد_Type_t x_پورٹ_Is_Inside_مداخلت( خالی );

خارجی خالی v_پورٹ_Yield( خالی ) /* PRIVILEGED_FUNCTION */;

خارجی خالی v_پورٹ_Enter_Critical( خالی ) /* PRIVILEGED_FUNCTION */;
خارجی خالی v_پورٹ_Exit_Critical( خالی ) /* PRIVILEGED_FUNCTION */;

خارجی uint32_t ul_سیٹ_مداخلت_نقاب( خالی ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
خارجی خالی v_Clear_مداخلت_نقاب( uint32_t ul_نقاب ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#اگر ( configENABLE_MPU == 1 )
    خارجی بنیاد_Type_t xIsPrivileged( خالی ) /* __attribute__ (( naked )) */;
    خارجی خالی vResetPrivilege( خالی ) /* __attribute__ (( naked )) */;
#اگر_ختم /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#اگر ( configENABLE_MPU == 1 )
    #تعریف_کرو پورٹ_USING_MPU_WRAPPERS          1
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ               ( 0x80000000UL )
#ورنہ
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ               ( 0x0UL )
#اگر_ختم /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#اگر_غیر_تعریف_شدہ configS_C_B_FLASH
    #تعریف_کرو configS_C_B_FLASH               ( 0x07UL )
#اگر_ختم

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#اگر_غیر_تعریف_شدہ configS_C_B_SRAM
    #تعریف_کرو configS_C_B_SRAM                ( 0x07UL )
#اگر_ختم

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
#تعریف_کرو پورٹ_MPU_REGION_سائز_256_B            ( 0x07UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_512_B            ( 0x08UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_1_KB             ( 0x09UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_2_KB             ( 0x0AUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_4_KB             ( 0x0BUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_8_KB             ( 0x0CUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_16_KB            ( 0x0DUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_32_KB            ( 0x0EUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_64_KB            ( 0x0FUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_128_KB           ( 0x10UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_256_KB           ( 0x11UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_512_KB           ( 0x12UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_1_MB             ( 0x13UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_2_MB             ( 0x14UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_4_MB             ( 0x15UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_8_MB             ( 0x16UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_16_MB            ( 0x17UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_32_MB            ( 0x18UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_64_MB            ( 0x19UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_128_MB           ( 0x1AUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_256_MB           ( 0x1BUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_512_MB           ( 0x1CUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_1_GB             ( 0x1DUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_2_GB             ( 0x1EUL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_سائز_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کرو پورٹ_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#تعریف_کرو پورٹ_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#تعریف_کرو پورٹ_MPU_REGION_معمول_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#تعریف_کرو پورٹ_MPU_REGION_معمول_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#تعریف_کرو پورٹ_MPU_REGION_معمول_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#تعریف_کرو پورٹ_MPU_REGION_معمول_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#تعریف_کرو پورٹ_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#اگر ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    قسمتعریف ساخت MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
    } MPURegionSettings_t;

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #اگر_غیر_تعریف_شدہ config_SYSTEM_CALL_ڈھیر_سائز
            #غلطی config_SYSTEM_CALL_ڈھیر_سائز must be defined مقصد the desired سائز کا the system call ڈھیر اندر الفاظ برائے using MPU wrappers v2.
        #اگر_ختم

        /**
         * @brief System call stack.
         */
        قسمتعریف ساخت SYSTEM_CALL_ڈھیر_INFO
        {
            uint32_t ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_سائز ];
            uint32_t * pul_System_Call_ڈھیر;
            uint32_t * pul_Task_ڈھیر;
            uint32_t ul_Link_رجسٹر_At_System_Call_اندراج;
        } x_SYSTEM_CALL_ڈھیر_INFO;

    #اگر_ختم /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #تعریف_کرو CONTEXT_سائز    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کرو پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کرو پورٹ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کرو پورٹ_ACL_اندراج_سائز_بٹ             ( 32U )

    قسمتعریف ساخت MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ پورٹ_کل_عدد_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_سائز ];
        uint32_t ulTaskFlags;

        #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ڈھیر_INFO x_System_Call_ڈھیر_Info;
            #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائز / پورٹ_ACL_اندراج_سائز_بٹ ) + 1 ];
            #اگر_ختم
        #اگر_ختم
    } xMPU_SETTINGS;

#اگر_ختم /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#تعریف_کرو پورٹ_SVC_آغاز_SCHEDULER            100
#تعریف_کرو پورٹ_SVC_RAISE_PRIVILEGE            101
#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT           102
#تعریف_کرو پورٹ_SVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#اگر ( configENABLE_MPU == 1 )
    #تعریف_کرو پورٹ_YIELD()               __asm متلون ( "svc %0" ::"i" ( پورٹ_SVC_YIELD ) : "memory" )
    #تعریف_کرو پورٹ_YIELD_WITHIN_API()    v_پورٹ_Yield()
#ورنہ
    #تعریف_کرو پورٹ_YIELD()               v_پورٹ_Yield()
    #تعریف_کرو پورٹ_YIELD_WITHIN_API()    v_پورٹ_Yield()
#اگر_ختم

#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متلون uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired )            \
    کرو                                                      \
    {                                                       \
        اگر( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
        }                                                   \
        ورنہ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } جب( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()       ul_سیٹ_مداخلت_نقاب()
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )  v_Clear_مداخلت_نقاب( x )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                __asm متلون ( " cpsid i " ::: "memory" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                 __asm متلون ( " cpsie i " ::: "memory" )
#تعریف_کرو پورٹ_ENTER_CRITICAL()                    v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                     v_پورٹ_Exit_Critical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#اگر_غیر_تعریف_شدہ پورٹ_SUPPRESS_TICKS_AND_SLEEP
    خارجی خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت );
    #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وقت )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وقت )
#اگر_ختم
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )
/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

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
    #تعریف_کرو پورٹ_RAISE_PRIVILEGE()    __asm متلون ( "svc %0 \n" ::"i" ( پورٹ_SVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #تعریف_کرو پورٹ_RESET_PRIVILEGE()    vResetPrivilege()

#ورنہ

    #تعریف_کرو پورٹ_IS_PRIVILEGED()
    #تعریف_کرو پورٹ_RAISE_PRIVILEGE()
    #تعریف_کرو پورٹ_RESET_PRIVILEGE()

#اگر_ختم /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

    خارجی بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #تعریف_کرو پورٹ_IS_TASK_PRIVILEGED()    x_پورٹ_Is_Task_Privileged()

#اگر_ختم /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متلون ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
