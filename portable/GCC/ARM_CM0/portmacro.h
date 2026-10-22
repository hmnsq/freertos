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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_MPU
    #ਗਲਤੀ configENABLE_MPU must be defined ਵਿੱਚ_2 FreeRTOSConfig.h.  ਸੈੱਟ_2 configENABLE_MPU ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ enable the MPU or 0 ਮੰਜ਼ਿਲ disable the MPU.
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ             ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ    UBaseType_t;

#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t        TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY   ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t        TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ARCH_NAME                      "Cortex-M0+"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH                   ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT                 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE                         __inline
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_FORCE_INLINE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FORCE_INLINE               ਸਤਰਅੰਦਰ __attribute__( ( always_inline ) )
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DONT_DISCARD                   __attribute__( ( ਵਰਤਿਆ ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
ਬਾਹਰੀ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ );

ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */;

ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */;
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */;

ਬਾਹਰੀ uint32_t ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
ਬਾਹਰੀ ਖਾਲੀ v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( uint32_t ul_ਨਕਾਬ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#ਜੇ ( configENABLE_MPU == 1 )
    ਬਾਹਰੀ ਅਧਾਰ_Type_t xIsPrivileged( ਖਾਲੀ ) /* __attribute__ (( naked )) */;
    ਬਾਹਰੀ ਖਾਲੀ vResetPrivilege( ਖਾਲੀ ) /* __attribute__ (( naked )) */;
#ਜੇ_ਅੰਤ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#ਜੇ ( configENABLE_MPU == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS          1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ               ( 0x80000000UL )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ               ( 0x0UL )
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configS_C_B_FLASH
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configS_C_B_FLASH               ( 0x07UL )
#ਜੇ_ਅੰਤ

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configS_C_B_SRAM
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configS_C_B_SRAM                ( 0x07UL )
#ਜੇ_ਅੰਤ

/* MPU regions. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_RAM_REGION           ( 7UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_FLASH_REGION         ( 6UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_REGION                    ( 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION       ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION        ( 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS        ( 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS               ( ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_256_B            ( 0x07UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_512_B            ( 0x08UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_1_KB             ( 0x09UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_2_KB             ( 0x0AUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_4_KB             ( 0x0BUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_8_KB             ( 0x0CUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_16_KB            ( 0x0DUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_32_KB            ( 0x0EUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_64_KB            ( 0x0FUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_128_KB           ( 0x10UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_256_KB           ( 0x11UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_512_KB           ( 0x12UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_1_MB             ( 0x13UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_2_MB             ( 0x14UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_4_MB             ( 0x15UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_8_MB             ( 0x16UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_16_MB            ( 0x17UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_32_MB            ( 0x18UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_64_MB            ( 0x19UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_128_MB           ( 0x1AUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_256_MB           ( 0x1BUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_512_MB           ( 0x1CUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_1_GB             ( 0x1DUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_2_GB             ( 0x1EUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਮਾਪ_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_ਸਾਧਾਰਨ_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
    } MPURegionSettings_t;

    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ
            #ਗਲਤੀ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ must be defined ਮੰਜ਼ਿਲ the desired ਮਾਪ ਦਾ the system call ਢੇਰ ਵਿੱਚ_2 ਸ਼ਬਦ ਲਈ using MPU wrappers v2.
        #ਜੇ_ਅੰਤ

        /**
         * @brief System call stack.
         */
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SYSTEM_CALL_ਢੇਰ_INFO
        {
            uint32_t ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ ];
            uint32_t * pul_System_Call_ਢੇਰ;
            uint32_t * pul_Task_ਢੇਰ;
            uint32_t ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
        } x_SYSTEM_CALL_ਢੇਰ_INFO;

    #ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONTEXT_ਮਾਪ    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ             ( 32U )

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_ਮਾਪ ];
        uint32_t ulTaskFlags;

        #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ਢੇਰ_INFO x_System_Call_ਢੇਰ_Info;
            #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ ) + 1 ];
            #ਜੇ_ਅੰਤ
        #ਜੇ_ਅੰਤ
    } xMPU_SETTINGS;

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER            100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_RAISE_PRIVILEGE            101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT           102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#ਜੇ ( configENABLE_MPU == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()               __asm ਅਸਥਿਰ ( "svc %0" ::"i" ( ਪੋਰਟ_SVC_YIELD ) : "memory" )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_WITHIN_API()    v_ਪੋਰਟ_Yield()
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()               v_ਪੋਰਟ_Yield()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_WITHIN_API()    v_ਪੋਰਟ_Yield()
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_INT_CTRL_REG     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed04 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 1UL << 28UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired )            \
    ਕਰੋ                                                      \
    {                                                       \
        ਜੇ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();                   \
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ; \
        }                                                   \
        ਨਹੀਂਤਾਂ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ਜਦੋਂ( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()       ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )  v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( x )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                __asm ਅਸਥਿਰ ( " cpsid i " ::: "memory" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                 __asm ਅਸਥਿਰ ( " cpsie i " ::: "memory" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                    v_ਪੋਰਟ_Enter_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                     v_ਪੋਰਟ_Exit_Critical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_SUPPRESS_TICKS_AND_SLEEP
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ਸਮਾਂ )    v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ਸਮਾਂ )
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RAISE_PRIVILEGE()    __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_PRIVILEGE()    vResetPrivilege()

#ਨਹੀਂਤਾਂ

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_PRIVILEGED()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RAISE_PRIVILEGE()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_PRIVILEGE()

#ਜੇ_ਅੰਤ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਬਾਹਰੀ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_TASK_PRIVILEGED()    x_ਪੋਰਟ_Is_Task_Privileged()

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()    __asm ਅਸਥਿਰ ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
