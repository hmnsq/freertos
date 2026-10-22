/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2024, 2026 Arm Limited and/or its affiliates <open-source-office@arm.com>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACROCOMMON_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACROCOMMON_H

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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_FPU
    #ਗਲਤੀ configENABLE_FPU must be defined ਵਿੱਚ_2 FreeRTOSConfig.h.  ਸੈੱਟ_2 configENABLE_FPU ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ enable the FPU or 0 ਮੰਜ਼ਿਲ disable the FPU.
#ਜੇ_ਅੰਤ /* configENABLE_FPU */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_MPU
    #ਗਲਤੀ configENABLE_MPU must be defined ਵਿੱਚ_2 FreeRTOSConfig.h.  ਸੈੱਟ_2 configENABLE_MPU ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ enable the MPU or 0 ਮੰਜ਼ਿਲ disable the MPU.
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_TRUSTZONE
    #ਗਲਤੀ configENABLE_TRUSTZONE must be defined ਵਿੱਚ_2 FreeRTOSConfig.h.  ਸੈੱਟ_2 configENABLE_TRUSTZONE ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ enable TrustZone or 0 ਮੰਜ਼ਿਲ disable TrustZone.
#ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
    #ਜੇ ( ਪੋਰਟ_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #ਗਲਤੀ "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #ਜੇ_ਅੰਤ /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CORE_ID_ਰਜਿਸਟਰ
        #ਗਲਤੀ "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #ਜੇ_ਅੰਤ /* ifndef configCORE_ID_REGISTER */

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configWAKE_SECONDARY_CORES
        #ਗਲਤੀ "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #ਜੇ_ਅੰਤ /* ifndef configWAKE_SECONDARY_CORES */
#ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES > 1 ) */
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
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH                   ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT                 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE                         __inline
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_FORCE_INLINE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FORCE_INLINE               ਸਤਰਅੰਦਰ __attribute__( ( always_inline ) )
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_HAS_ਢੇਰ_ਉਛਾਲ_CHECKING    1
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

#ਜੇ ( configENABLE_TRUSTZONE == 1 )
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Allocate_Secure_Context( uint32_t ul_Secure_ਢੇਰ_ਮਾਪ ); /* __attribute__ (( naked )) */
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */

#ਜੇ ( configENABLE_MPU == 1 )
    ਬਾਹਰੀ ਅਧਾਰ_Type_t xIsPrivileged( ਖਾਲੀ ) /* __attribute__ (( naked )) */;
    ਬਾਹਰੀ ਖਾਲੀ vResetPrivilege( ਖਾਲੀ ) /* __attribute__ (( naked )) */;
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

#ਜੇ ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    ਖਾਲੀ v_Application_Generate_Task_Random_Pac_ਕੁੰਜੀ( uint32_t * pul_Task_Pac_ਕੁੰਜੀ );

#ਜੇ_ਅੰਤ /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#ਜੇ ( configENABLE_MPU == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS    1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ         ( 0x80000000UL )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ         ( 0x0UL )
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਕੁੱਲ_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਕੁੱਲ_MPU_REGIONS    ( 8UL )
#ਜੇ_ਅੰਤ

/* MPU regions. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_FLASH_REGION                   ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_RAM_REGION                     ( 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_REGION                              ( 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION                 ( 5UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION                  ( config_ਕੁੱਲ_MPU_REGIONS - 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS                  ( ( ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION - ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION ) + 1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS                         ( ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

/* Device memory attributes used in MPU_MAIR registers.
 *
 * 8-bit values encoded as follows:
 *  Bit[7:4] - 0000 - Device Memory
 *  Bit[3:2] - 00 --> Device-nGnRnE
 *              01 --> Device-nGnRE
 *              10 --> Device-nGRE
 *              11 --> Device-GRE
 *  Bit[1:0] - 00, Reserved.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_GRE                    ( 0x08 )       /* 0000 1000 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
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
            uint32_t * pul_System_Call_ਢੇਰ_ਹੱਦਬੰਦੀ;
            uint32_t * pul_Task_ਢੇਰ;
            uint32_t ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
            uint32_t ul_ਢੇਰ_ਹੱਦਬੰਦੀ_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
        } x_SYSTEM_CALL_ਢੇਰ_INFO;

    #ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #ਜੇ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #ਜੇ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    59

        #ਜਾਂਜੇ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    55

        #ਜਾਂਜੇ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    58

        #ਨਹੀਂਤਾਂ /* if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

            /*
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |     |
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><---->
             *      16             17            8               8                  4              1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    54

        #ਜੇ_ਅੰਤ /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #ਨਹੀਂਤਾਂ /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #ਜੇ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    26

        #ਜਾਂਜੇ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    22

        #ਜਾਂਜੇ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    25

        #ਨਹੀਂਤਾਂ /* #if( configENABLE_TRUSTZONE == 1 ) */

            /*
             * +----------+-----------------+----------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |          | PC, xPSR        | EXC_RETURN           |     |
             * +----------+-----------------+----------------------+-----+
             *
             * <---------><----------------><----------------------><---->
             *     8               8                  4              1
             */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    21

        #ਜੇ_ਅੰਤ /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #ਜੇ_ਅੰਤ /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ             ( 32U )

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_ਮਾਪ ];
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
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#ਜੇ ( configASSERT_DEFINED == 1 )
    #ਜੇ ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਰੁਕਾਵਟ_ਤਰਜੀਹ_INVALID()    v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ()
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/**
 * @brief SVC numbers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ALLOCATE_SECURE_CONTEXT    100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_FREE_SECURE_CONTEXT        101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER            102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_RAISE_PRIVILEGE            103
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT           104
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_YIELD                      105
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()                  ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ( x )             v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( x )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( x )

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                      v_ਪੋਰਟ_Enter_Critical()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                       v_ਪੋਰਟ_Exit_Critical()
#ਨਹੀਂਤਾਂ /* ( configNUMBER_OF_CORES == 1 ) */
    ਬਾਹਰੀ ਖਾਲੀ vTaskEnterCritical( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ vTaskExitCritical( ਖਾਲੀ );
    ਬਾਹਰੀ UBaseType_t vTaskEnterCriticalFromISR( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                      vTaskEnterCritical()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                       vTaskExitCritical()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES != 1 ) */
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
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ALLOCATE_SECURE_CONTEXT( ul_Secure_ਢੇਰ_ਮਾਪ )    v_ਪੋਰਟ_Allocate_Secure_Context( ul_Secure_ਢੇਰ_ਮਾਪ )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAN_ਉੱਪਰ_TCB( pxTCB )                           v_ਪੋਰਟ_Free_Secure_Context( ( uint32_t * ) pxTCB )
#ਜੇ_ਅੰਤ /* configENABLE_TRUSTZONE */
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

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਜੇ ( ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 ) )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    0
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#ਜੇ ( config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    ਸਥਿਰ ਪੋਰਟ_FORCE_INLINE uint32_t ul_ਪੋਰਟ_ਗਿਣਤੀ_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm ਅਸਥਿਰ ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        ਵਾਪਸ ulReturn;
    }

/* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 different priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ

    #ਜੇ ( ਪੋਰਟ_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #ਗਲਤੀ ARMv8-M baseline implementations (such as Cortex-M23) ਕਰੋ not support ਪੋਰਟ-optimised task selection.  Please ਸੈੱਟ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION ਮੰਜ਼ਿਲ 0 or leave it undefined.
    #ਜੇ_ਅੰਤ

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31UL - ul_ਪੋਰਟ_ਗਿਣਤੀ_Leading_Zeros( ( uxReadyPriorities ) ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
    {
        e_Isr_ਤਾਲਾ = 0,
        e_Task_ਤਾਲਾ,
        e_ਤਾਲਾ_ਗਿਣਤੀ
    } e_ਪੋਰਟ_RTOSLock;

    ਬਾਹਰੀ ਅਸਥਿਰ uint32_t ulCriticalNestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ];
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ( uint8_t ucCoreID,
                                    e_ਪੋਰਟ_RTOSLock e_ਤਾਲਾ_ਅੰਕ,
                                    ਅਧਾਰ_Type_t uxAcquire );
    ਬਾਹਰੀ uint8_t uc_ਪੋਰਟ_Get_Core_ID( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ v_ਰੁਕਾਵਟ_Core( uint8_t ucCoreID );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID()                                  uc_ਪੋਰਟ_Get_Core_ID()

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INCREMENT_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DECREMENT_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ                                 ( config_ਸੰਖਿਆ_ਦਾ_CORES )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_CORE( xCoreID )                          v_ਰੁਕਾਵਟ_Core( xCoreID )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )                    v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Isr_ਤਾਲਾ, pdFALSE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )                        v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Isr_ਤਾਲਾ, pdTRUE )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )                   v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Task_ਤਾਲਾ, pdFALSE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )                       v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Task_ਤਾਲਾ, pdTRUE )

    #ਜੇ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( ਅਧਾਰ_Type_t x_Write_Control_ਰਜਿਸਟਰ );
    #ਜੇ_ਅੰਤ /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#ਜੇ_ਅੰਤ

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACROCOMMON_H */
