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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACROCOMMON_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACROCOMMON_H

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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_FPU
    #ದೋಷ configENABLE_FPU must be defined ಒಳ FreeRTOSConfig.h.  ಗಣ_2 configENABLE_FPU ಗಮ್ಯ 1 ಗಮ್ಯ enable the FPU or 0 ಗಮ್ಯ disable the FPU.
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_FPU */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_MPU
    #ದೋಷ configENABLE_MPU must be defined ಒಳ FreeRTOSConfig.h.  ಗಣ_2 configENABLE_MPU ಗಮ್ಯ 1 ಗಮ್ಯ enable the MPU or 0 ಗಮ್ಯ disable the MPU.
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_TRUSTZONE
    #ದೋಷ configENABLE_TRUSTZONE must be defined ಒಳ FreeRTOSConfig.h.  ಗಣ_2 configENABLE_TRUSTZONE ಗಮ್ಯ 1 ಗಮ್ಯ enable TrustZone or 0 ಗಮ್ಯ disable TrustZone.
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
    #ಆದರೆ ( ಪೋರ್ಟ್_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #ದೋಷ "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #ಆದರೆ_ಅಂತ್ಯ /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_CORE_ID_ರಿಜಿಸ್ಟರ್
        #ದೋಷ "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #ಆದರೆ_ಅಂತ್ಯ /* ifndef configCORE_ID_REGISTER */

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configWAKE_SECONDARY_CORES
        #ದೋಷ "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #ಆದರೆ_ಅಂತ್ಯ /* ifndef configWAKE_SECONDARY_CORES */
#ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES > 1 ) */
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
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffffffffUL

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH                   ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT                 8
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE                         __inline
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_FORCE_INLINE
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FORCE_INLINE               ಸಾಲೊಳಗೆ __attribute__( ( always_inline ) )
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_HAS_ರಾಶಿ_ಅತಿಪ್ರವಾಹ_CHECKING    1
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

#ಆದರೆ ( configENABLE_TRUSTZONE == 1 )
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Allocate_Secure_Context( uint32_t ul_Secure_ರಾಶಿ_ಗಾತ್ರ ); /* __attribute__ (( naked )) */
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */

#ಆದರೆ ( configENABLE_MPU == 1 )
    ಬಾಹ್ಯ ತಳ_Type_t xIsPrivileged( ಶೂನ್ಯ ) /* __attribute__ (( naked )) */;
    ಬಾಹ್ಯ ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ ) /* __attribute__ (( naked )) */;
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

#ಆದರೆ ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    ಶೂನ್ಯ v_Application_Generate_Task_Random_Pac_ಕೀಲಿ( uint32_t * pul_Task_Pac_ಕೀಲಿ );

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#ಆದರೆ ( configENABLE_MPU == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USING_MPU_WRAPPERS    1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್         ( 0x80000000UL )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್         ( 0x0UL )
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಒಟ್ಟು_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_ಒಟ್ಟು_MPU_REGIONS    ( 8UL )
#ಆದರೆ_ಅಂತ್ಯ

/* MPU regions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION                   ( 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION                     ( 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_REGION                              ( 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION                 ( 5UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION                  ( config_ಒಟ್ಟು_MPU_REGIONS - 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS                  ( ( ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION - ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION ) + 1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS                         ( ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_GRE                    ( 0x08 )       /* 0000 1000 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
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
            uint32_t * pul_System_Call_ರಾಶಿ_ಎಲ್ಲೆ;
            uint32_t * pul_Task_ರಾಶಿ;
            uint32_t ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
            uint32_t ul_ರಾಶಿ_ಎಲ್ಲೆ_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
        } x_SYSTEM_CALL_ರಾಶಿ_INFO;

    #ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #ಆದರೆ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #ಆದರೆ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    59

        #ಅಥವಾಆದರೆ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    55

        #ಅಥವಾಆದರೆ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    58

        #ಇಲ್ಲದಿದ್ದರೆ /* if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

            /*
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |     |
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><---->
             *      16             17            8               8                  4              1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    54

        #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #ಆದರೆ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    26

        #ಅಥವಾಆದರೆ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    22

        #ಅಥವಾಆದರೆ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    25

        #ಇಲ್ಲದಿದ್ದರೆ /* #if( configENABLE_TRUSTZONE == 1 ) */

            /*
             * +----------+-----------------+----------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |          | PC, xPSR        | EXC_RETURN           |     |
             * +----------+-----------------+----------------------+-----+
             *
             * <---------><----------------><----------------------><---->
             *     8               8                  4              1
             */
            #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    21

        #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು             ( 32U )

    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_ಗಾತ್ರ ];
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
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#ಆದರೆ ( configASSERT_DEFINED == 1 )
    #ಆದರೆ ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ );
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಅಡಚಣೆ_ಆದ್ಯತೆ_INVALID()    v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ()
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief SVC numbers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ALLOCATE_SECURE_CONTEXT    100
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_FREE_SECURE_CONTEXT        101
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER            102
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE            103
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT           104
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_YIELD                      105
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

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()                  ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ( x )             v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( x )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( x )

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                      v_ಪೋರ್ಟ್_Enter_Critical()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                       v_ಪೋರ್ಟ್_Exit_Critical()
#ಇಲ್ಲದಿದ್ದರೆ /* ( configNUMBER_OF_CORES == 1 ) */
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskEnterCritical( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCritical( ಶೂನ್ಯ );
    ಬಾಹ್ಯ UBaseType_t vTaskEnterCriticalFromISR( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                      vTaskEnterCritical()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                       vTaskExitCritical()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES != 1 ) */
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
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ALLOCATE_SECURE_CONTEXT( ul_Secure_ರಾಶಿ_ಗಾತ್ರ )    v_ಪೋರ್ಟ್_Allocate_Secure_Context( ul_Secure_ರಾಶಿ_ಗಾತ್ರ )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAN_ಮೇಲೆ_TCB( pxTCB )                           v_ಪೋರ್ಟ್_Free_Secure_Context( ( uint32_t * ) pxTCB )
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_TRUSTZONE */
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

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ಆದರೆ ( ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 ) )
        #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    0
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#ಆದರೆ ( config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    ಸ್ಥಿರ ಪೋರ್ಟ್_FORCE_INLINE uint32_t ul_ಪೋರ್ಟ್_ಎಣಿಕೆ_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm ಅಸ್ಥಿರ ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        ಹಿಂತಿರುಗಿ ulReturn;
    }

/* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 different priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
    #ಆದರೆ_ಅಂತ್ಯ

    #ಆದರೆ ( ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #ದೋಷ ARMv8-M baseline implementations (such as Cortex-M23) ಮಾಡು not support ಪೋರ್ಟ್-optimised task selection.  Please ಗಣ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION ಗಮ್ಯ 0 or leave it undefined.
    #ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - ul_ಪೋರ್ಟ್_ಎಣಿಕೆ_Leading_Zeros( ( uxReadyPriorities ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
    {
        e_Isr_ಬೀಗ = 0,
        e_Task_ಬೀಗ,
        e_ಬೀಗ_ಎಣಿಕೆ
    } e_ಪೋರ್ಟ್_RTOSLock;

    ಬಾಹ್ಯ ಅಸ್ಥಿರ uint32_t ulCriticalNestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ];
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( uint8_t ucCoreID,
                                    e_ಪೋರ್ಟ್_RTOSLock e_ಬೀಗ_ಅಂಕೆ,
                                    ತಳ_Type_t uxAcquire );
    ಬಾಹ್ಯ uint8_t uc_ಪೋರ್ಟ್_Get_Core_ID( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಅಡಚಣೆ_Core( uint8_t ucCoreID );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()                                  uc_ಪೋರ್ಟ್_Get_Core_ID()

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INCREMENT_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DECREMENT_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ                                 ( config_ಸಂಖ್ಯೆ_ದ_CORES )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE( xCoreID )                          v_ಅಡಚಣೆ_Core( xCoreID )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )                    v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Isr_ಬೀಗ, pdFALSE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )                        v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Isr_ಬೀಗ, pdTRUE )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )                   v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Task_ಬೀಗ, pdFALSE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )                       v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Task_ಬೀಗ, pdTRUE )

    #ಆದರೆ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( ತಳ_Type_t x_Write_Control_ರಿಜಿಸ್ಟರ್ );
    #ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#ಆದರೆ_ಅಂತ್ಯ

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACROCOMMON_H */
