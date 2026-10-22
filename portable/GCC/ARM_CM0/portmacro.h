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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_MPU
    #ದೋಷ configENABLE_MPU must be defined ಒಳ FreeRTOSConfig.h.  ಗಣ_2 configENABLE_MPU ಗಮ್ಯ 1 ಗಮ್ಯ enable the MPU or 0 ಗಮ್ಯ disable the MPU.
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ             ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ    UBaseType_t;

#ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t        TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY   ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t        TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ARCH_NAME                      "Cortex-M0+"
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH                   ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT                 8
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE                         __inline
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_FORCE_INLINE
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FORCE_INLINE               ಸಾಲೊಳಗೆ __attribute__( ( always_inline ) )
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DONT_DISCARD                   __attribute__( ( ಬಳಸಿದ ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
ಬಾಹ್ಯ ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ );

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */;

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */;
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */;

ಬಾಹ್ಯ uint32_t ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
ಬಾಹ್ಯ ಶೂನ್ಯ v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( uint32_t ul_ಮುಖವಾಡ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#ಆದರೆ ( configENABLE_MPU == 1 )
    ಬಾಹ್ಯ ತಳ_Type_t xIsPrivileged( ಶೂನ್ಯ ) /* __attribute__ (( naked )) */;
    ಬಾಹ್ಯ ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ ) /* __attribute__ (( naked )) */;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#ಆದರೆ ( configENABLE_MPU == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USING_MPU_WRAPPERS          1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್               ( 0x80000000UL )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್               ( 0x0UL )
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configS_C_B_FLASH
    #ವ್ಯಾಖ್ಯಾನಿಸು configS_C_B_FLASH               ( 0x07UL )
#ಆದರೆ_ಅಂತ್ಯ

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configS_C_B_SRAM
    #ವ್ಯಾಖ್ಯಾನಿಸು configS_C_B_SRAM                ( 0x07UL )
#ಆದರೆ_ಅಂತ್ಯ

/* MPU regions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION           ( 7UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION         ( 6UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_REGION                    ( 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION       ( 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION        ( 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS        ( 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS               ( ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_256_B            ( 0x07UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_512_B            ( 0x08UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_1_KB             ( 0x09UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_2_KB             ( 0x0AUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_4_KB             ( 0x0BUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_8_KB             ( 0x0CUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_16_KB            ( 0x0DUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_32_KB            ( 0x0EUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_64_KB            ( 0x0FUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_128_KB           ( 0x10UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_256_KB           ( 0x11UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_512_KB           ( 0x12UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_1_MB             ( 0x13UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_2_MB             ( 0x14UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_4_MB             ( 0x15UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_8_MB             ( 0x16UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_16_MB            ( 0x17UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_32_MB            ( 0x18UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_64_MB            ( 0x19UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_128_MB           ( 0x1AUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_256_MB           ( 0x1BUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_512_MB           ( 0x1CUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_1_GB             ( 0x1DUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_2_GB             ( 0x1EUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಗಾತ್ರ_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_ಸಾಮಾನ್ಯ_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
    } MPURegionSettings_t;

    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ
            #ದೋಷ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ must be defined ಗಮ್ಯ the desired ಗಾತ್ರ_2 ದ the system call ರಾಶಿ ಒಳ ಪದಗಳು ಗಾಗಿ using MPU wrappers v2.
        #ಆದರೆ_ಅಂತ್ಯ

        /**
         * @brief System call stack.
         */
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SYSTEM_CALL_ರಾಶಿ_INFO
        {
            uint32_t ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ ];
            uint32_t * pul_System_Call_ರಾಶಿ;
            uint32_t * pul_Task_ರಾಶಿ;
            uint32_t ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
        } x_SYSTEM_CALL_ರಾಶಿ_INFO;

    #ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #ವ್ಯಾಖ್ಯಾನಿಸು CONTEXT_ಗಾತ್ರ    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು             ( 32U )

    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_ಗಾತ್ರ ];
        uint32_t ulTaskFlags;

        #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ರಾಶಿ_INFO x_System_Call_ರಾಶಿ_Info;
            #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು ) + 1 ];
            #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ_ಅಂತ್ಯ
    } xMPU_SETTINGS;

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER            100
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE            101
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT           102
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#ಆದರೆ ( configENABLE_MPU == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()               __asm ಅಸ್ಥಿರ ( "svc %0" ::"i" ( ಪೋರ್ಟ್_SVC_YIELD ) : "memory" )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_WITHIN_API()    v_ಪೋರ್ಟ್_Yield()
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()               v_ಪೋರ್ಟ್_Yield()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_WITHIN_API()    v_ಪೋರ್ಟ್_Yield()
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_INT_CTRL_REG     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed04 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್    ( 1UL << 28UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired )            \
    ಮಾಡು                                                      \
    {                                                       \
        ಆದರೆ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();                   \
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್; \
        }                                                   \
        ಇಲ್ಲದಿದ್ದರೆ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ಆಗ( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()       ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )  v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( x )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                __asm ಅಸ್ಥಿರ ( " cpsid i " ::: "memory" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                 __asm ಅಸ್ಥಿರ ( " cpsie i " ::: "memory" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                    v_ಪೋರ್ಟ್_Enter_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                     v_ಪೋರ್ಟ್_Exit_Critical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ಸಮಯ )    v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( x_Expected_Idle_ಸಮಯ )
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RAISE_PRIVILEGE()    __asm ಅಸ್ಥಿರ ( "svc %0 \n" ::"i" ( ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_PRIVILEGE()    vResetPrivilege()

#ಇಲ್ಲದಿದ್ದರೆ

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_PRIVILEGED()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RAISE_PRIVILEGE()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_PRIVILEGE()

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ಬಾಹ್ಯ ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_TASK_PRIVILEGED()    x_ಪೋರ್ಟ್_Is_Task_Privileged()

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
