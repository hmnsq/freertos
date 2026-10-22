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

#جے_بنا_تعریف PORTMACROCOMMON_H
#تعریف_کرو PORTMACROCOMMON_H

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

#جے_بنا_تعریف configENABLE_FPU
    #غلطی configENABLE_FPU must be defined وچ FreeRTOSConfig.h.  سیٹ_2 configENABLE_FPU منزل 1 منزل enable the FPU or 0 منزل disable the FPU.
#جے_انت /* configENABLE_FPU */

#جے_بنا_تعریف configENABLE_MPU
    #غلطی configENABLE_MPU must be defined وچ FreeRTOSConfig.h.  سیٹ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#جے_انت /* configENABLE_MPU */

#جے_بنا_تعریف configENABLE_TRUSTZONE
    #غلطی configENABLE_TRUSTZONE must be defined وچ FreeRTOSConfig.h.  سیٹ_2 configENABLE_TRUSTZONE منزل 1 منزل enable TrustZone or 0 منزل disable TrustZone.
#جے_انت /* configENABLE_TRUSTZONE */

#إذا ( config_نمبر_دا_CORES > 1 )
    #إذا ( پورٹ_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #غلطی "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #جے_انت /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #جے_بنا_تعریف config_CORE_ID_رجسٹر
        #غلطی "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #جے_انت /* ifndef configCORE_ID_REGISTER */

    #جے_بنا_تعریف configWAKE_SECONDARY_CORES
        #غلطی "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #جے_انت /* ifndef configWAKE_SECONDARY_CORES */
#جے_انت /* #if ( configNUMBER_OF_CORES > 1 ) */
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
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

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
#تعریف_کرو پورٹ_ڈھیر_GROWTH                   ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT                 8
#تعریف_کرو پورٹ_NOP()
#تعریف_کرو پورٹ_INLINE                         __inline
#جے_بنا_تعریف پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#جے_انت
#تعریف_کرو پورٹ_HAS_ڈھیر_حد_توں_ودھ_CHECKING    1
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

#إذا ( configENABLE_TRUSTZONE == 1 )
    خارجي فراغ v_پورٹ_Allocate_Secure_Context( uint32_t ul_Secure_ڈھیر_ناپ ); /* __attribute__ (( naked )) */
    خارجي فراغ v_پورٹ_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#جے_انت /* configENABLE_TRUSTZONE */

#إذا ( configENABLE_MPU == 1 )
    خارجي ادھار_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#جے_انت /* configENABLE_MPU */

#إذا ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    فراغ v_Application_Generate_Task_Random_Pac_کلید( uint32_t * pul_Task_Pac_کلید );

#جے_انت /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کرو پورٹ_USING_MPU_WRAPPERS    1
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ         ( 0x80000000UL )
#وإلا
    #تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ         ( 0x0UL )
#جے_انت /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#جے_بنا_تعریف config_کل_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #تعریف_کرو config_کل_MPU_REGIONS    ( 8UL )
#جے_انت

/* MPU regions. */
#تعریف_کرو پورٹ_PRIVILEGED_FLASH_REGION                   ( 0UL )
#تعریف_کرو پورٹ_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#تعریف_کرو پورٹ_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#تعریف_کرو پورٹ_PRIVILEGED_RAM_REGION                     ( 3UL )
#تعریف_کرو پورٹ_ڈھیر_REGION                              ( 4UL )
#تعریف_کرو پورٹ_پہلا_CONFIGURABLE_REGION                 ( 5UL )
#تعریف_کرو پورٹ_آخری_CONFIGURABLE_REGION                  ( config_کل_MPU_REGIONS - 1UL )
#تعریف_کرو پورٹ_عدد_CONFIGURABLE_REGIONS                  ( ( پورٹ_آخری_CONFIGURABLE_REGION - پورٹ_پہلا_CONFIGURABLE_REGION ) + 1 )
#تعریف_کرو پورٹ_کل_عدد_REGIONS                         ( پورٹ_عدد_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_n_GRE                    ( 0x08 )       /* 0000 1000 */
#تعریف_کرو پورٹ_MPU_DEVICE_حافظہ_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#تعریف_کرو پورٹ_MPU_عام_حافظہ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#تعریف_کرو پورٹ_MPU_عام_حافظہ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#تعریف_کرو پورٹ_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#تعریف_کرو پورٹ_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#تعریف_کرو پورٹ_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#تعریف_کرو پورٹ_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#تعریف_کرو پورٹ_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    تعريفنوع بنية MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
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
            uint32_t * pul_System_Call_ڈھیر_حد_بندی;
            uint32_t * pul_Task_ڈھیر;
            uint32_t ul_Link_رجسٹر_At_System_Call_اندراج;
            uint32_t ul_ڈھیر_حد_بندی_رجسٹر_At_System_Call_اندراج;
        } x_SYSTEM_CALL_ڈھیر_INFO;

    #جے_انت /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #إذا ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #إذا ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    59

        #وإلاإذا ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    55

        #وإلاإذا ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    58

        #وإلا /* if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

            /*
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |     |
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><---->
             *      16             17            8               8                  4              1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    54

        #جے_انت /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #وإلا /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #إذا ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    26

        #وإلاإذا ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    22

        #وإلاإذا ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    25

        #وإلا /* #if( configENABLE_TRUSTZONE == 1 ) */

            /*
             * +----------+-----------------+----------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |          | PC, xPSR        | EXC_RETURN           |     |
             * +----------+-----------------+----------------------+-----+
             *
             * <---------><----------------><----------------------><---->
             *     8               8                  4              1
             */
            #تعریف_کرو MAX_CONTEXT_ناپ    21

        #جے_انت /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #جے_انت /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کرو پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کرو پورٹ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کرو پورٹ_ACL_اندراج_ناپ_بٹ             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ پورٹ_کل_عدد_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_ناپ ];
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
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#إذا ( configASSERT_DEFINED == 1 )
    #إذا ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ );
        #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    v_پورٹ_Validate_رکاوٹ_ترجیح()
    #جے_انت
#جے_انت

/**
 * @brief SVC numbers.
 */
#تعریف_کرو پورٹ_SVC_ALLOCATE_SECURE_CONTEXT    100
#تعریف_کرو پورٹ_SVC_FREE_SECURE_CONTEXT        101
#تعریف_کرو پورٹ_SVC_شروع_SCHEDULER            102
#تعریف_کرو پورٹ_SVC_RAISE_PRIVILEGE            103
#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT           104
#تعریف_کرو پورٹ_SVC_YIELD                      105
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

#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب()                  ul_سیٹ_رکاوٹ_نقاب()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب( x )             v_Clear_رکاوٹ_نقاب( x )
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ul_سیٹ_رکاوٹ_نقاب()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_Clear_رکاوٹ_نقاب( x )

#إذا ( config_نمبر_دا_CORES == 1 )
    #تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()
#وإلا /* ( configNUMBER_OF_CORES == 1 ) */
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_رکاوٹ_حالت );

    #تعریف_کرو پورٹ_ENTER_CRITICAL()                      vTaskEnterCritical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()                       vTaskExitCritical()
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#جے_انت /* if ( configNUMBER_OF_CORES != 1 ) */
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
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #تعریف_کرو پورٹ_ALLOCATE_SECURE_CONTEXT( ul_Secure_ڈھیر_ناپ )    v_پورٹ_Allocate_Secure_Context( ul_Secure_ڈھیر_ناپ )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #تعریف_کرو پورٹ_CLEAN_اتے_TCB( pxTCB )                           v_پورٹ_Free_Secure_Context( ( uint32_t * ) pxTCB )
#جے_انت /* configENABLE_TRUSTZONE */
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

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #إذا ( ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_نمبر_دا_CORES == 1 ) )
        #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
    #وإلا
        #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    0
    #جے_انت
#جے_انت /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#إذا ( config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    ساكن پورٹ_FORCE_INLINE uint32_t ul_پورٹ_گنتی_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        أرجع ulReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 different priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت

    #إذا ( پورٹ_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #غلطی ARMv8-M baseline implementations (such as Cortex-M23) افعل not support پورٹ-optimised task selection.  Please سیٹ config_USE_پورٹ_OPTIMISED_TASK_SELECTION منزل 0 or leave it undefined.
    #جے_انت

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ul_پورٹ_گنتی_Leading_Zeros( ( uxReadyPriorities ) ) )

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#إذا ( config_نمبر_دا_CORES > 1 )
    تعريفنوع تعداد
    {
        e_Isr_جندرا = 0,
        e_Task_جندرا,
        e_جندرا_گنتی
    } e_پورٹ_RTOSLock;

    خارجي متطاير uint32_t ulCriticalNestings[ config_نمبر_دا_CORES ];
    خارجي فراغ v_پورٹ_Recursive_جندرا( uint8_t ucCoreID,
                                    e_پورٹ_RTOSLock e_جندرا_عدد,
                                    ادھار_Type_t uxAcquire );
    خارجي uint8_t uc_پورٹ_Get_Core_ID( فراغ );
    خارجي فراغ v_رکاوٹ_Core( uint8_t ucCoreID );

    #تعریف_کرو پورٹ_GET_CORE_ID()                                  uc_پورٹ_Get_Core_ID()

    #تعریف_کرو پورٹ_GET_CRITICAL_NESTING_گنتی( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کرو پورٹ_سیٹ_CRITICAL_NESTING_گنتی( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کرو پورٹ_INCREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کرو پورٹ_DECREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #تعریف_کرو پورٹ_MAX_CORE_گنتی                                 ( config_نمبر_دا_CORES )

    #تعریف_کرو پورٹ_YIELD_CORE( xCoreID )                          v_رکاوٹ_Core( xCoreID )

    #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )                    v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Isr_جندرا, pdFALSE )
    #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )                        v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Isr_جندرا, pdTRUE )

    #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )                   v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Task_جندرا, pdFALSE )
    #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )                       v_پورٹ_Recursive_جندرا( ( uint8_t ) xCoreID, e_Task_جندرا, pdTRUE )

    #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( ادھار_Type_t x_Write_Control_رجسٹر );
    #جے_انت /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#جے_انت

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACROCOMMON_H */
