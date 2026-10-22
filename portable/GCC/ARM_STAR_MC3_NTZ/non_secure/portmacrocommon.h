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

#جيڪڏهن_وصف_نه_ٿيل PORTMACROCOMMON_H
#وصف_ڪريو PORTMACROCOMMON_H

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

#جيڪڏهن_وصف_نه_ٿيل configENABLE_FPU
    #غلطي configENABLE_FPU must be defined اندريون FreeRTOSConfig.h.  سيٽ_2 configENABLE_FPU منزل 1 منزل enable the FPU or 0 منزل disable the FPU.
#جيڪڏهن_پورو /* configENABLE_FPU */

#جيڪڏهن_وصف_نه_ٿيل configENABLE_MPU
    #غلطي configENABLE_MPU must be defined اندريون FreeRTOSConfig.h.  سيٽ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#جيڪڏهن_پورو /* configENABLE_MPU */

#جيڪڏهن_وصف_نه_ٿيل configENABLE_TRUSTZONE
    #غلطي configENABLE_TRUSTZONE must be defined اندريون FreeRTOSConfig.h.  سيٽ_2 configENABLE_TRUSTZONE منزل 1 منزل enable TrustZone or 0 منزل disable TrustZone.
#جيڪڏهن_پورو /* configENABLE_TRUSTZONE */

#إذا ( config_عدد_جو_CORES > 1 )
    #إذا ( پورٽ_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #غلطي "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #جيڪڏهن_پورو /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #جيڪڏهن_وصف_نه_ٿيل config_CORE_ID_رجسٽر
        #غلطي "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #جيڪڏهن_پورو /* ifndef configCORE_ID_REGISTER */

    #جيڪڏهن_وصف_نه_ٿيل configWAKE_SECONDARY_CORES
        #غلطي "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #جيڪڏهن_پورو /* ifndef configWAKE_SECONDARY_CORES */
#جيڪڏهن_پورو /* #if ( configNUMBER_OF_CORES > 1 ) */
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
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

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
#وصف_ڪريو پورٽ_ڍير_GROWTH                   ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT                 8
#وصف_ڪريو پورٽ_NOP()
#وصف_ڪريو پورٽ_INLINE                         __inline
#جيڪڏهن_وصف_نه_ٿيل پورٽ_FORCE_INLINE
    #وصف_ڪريو پورٽ_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#جيڪڏهن_پورو
#وصف_ڪريو پورٽ_HAS_ڍير_حد_کان_مٿي_CHECKING    1
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

#إذا ( configENABLE_TRUSTZONE == 1 )
    خارجي فراغ v_پورٽ_Allocate_Secure_Context( uint32_t ul_Secure_ڍير_سائيز ); /* __attribute__ (( naked )) */
    خارجي فراغ v_پورٽ_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#جيڪڏهن_پورو /* configENABLE_TRUSTZONE */

#إذا ( configENABLE_MPU == 1 )
    خارجي بنياد_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#جيڪڏهن_پورو /* configENABLE_MPU */

#إذا ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    فراغ v_Application_Generate_Task_Random_Pac_ڪنجي( uint32_t * pul_Task_Pac_ڪنجي );

#جيڪڏهن_پورو /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #وصف_ڪريو پورٽ_USING_MPU_WRAPPERS    1
    #وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ         ( 0x80000000UL )
#وإلا
    #وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ         ( 0x0UL )
#جيڪڏهن_پورو /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#جيڪڏهن_وصف_نه_ٿيل config_ڪل_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #وصف_ڪريو config_ڪل_MPU_REGIONS    ( 8UL )
#جيڪڏهن_پورو

/* MPU regions. */
#وصف_ڪريو پورٽ_PRIVILEGED_FLASH_REGION                   ( 0UL )
#وصف_ڪريو پورٽ_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#وصف_ڪريو پورٽ_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#وصف_ڪريو پورٽ_PRIVILEGED_RAM_REGION                     ( 3UL )
#وصف_ڪريو پورٽ_ڍير_REGION                              ( 4UL )
#وصف_ڪريو پورٽ_پهريون_CONFIGURABLE_REGION                 ( 5UL )
#وصف_ڪريو پورٽ_آخري_CONFIGURABLE_REGION                  ( config_ڪل_MPU_REGIONS - 1UL )
#وصف_ڪريو پورٽ_انگ_CONFIGURABLE_REGIONS                  ( ( پورٽ_آخري_CONFIGURABLE_REGION - پورٽ_پهريون_CONFIGURABLE_REGION ) + 1 )
#وصف_ڪريو پورٽ_ڪل_انگ_REGIONS                         ( پورٽ_انگ_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_n_GRE                    ( 0x08 )       /* 0000 1000 */
#وصف_ڪريو پورٽ_MPU_DEVICE_يادگيري_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#وصف_ڪريو پورٽ_MPU_عام_يادگيري_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#وصف_ڪريو پورٽ_MPU_عام_يادگيري_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#وصف_ڪريو پورٽ_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#وصف_ڪريو پورٽ_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#وصف_ڪريو پورٽ_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#وصف_ڪريو پورٽ_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#وصف_ڪريو پورٽ_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
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
            uint32_t * pul_System_Call_ڍير_حد_بندي;
            uint32_t * pul_Task_ڍير;
            uint32_t ul_Link_رجسٽر_At_System_Call_داخلا;
            uint32_t ul_ڍير_حد_بندي_رجسٽر_At_System_Call_داخلا;
        } x_SYSTEM_CALL_ڍير_INFO;

    #جيڪڏهن_پورو /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    59

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    55

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    58

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    54

        #جيڪڏهن_پورو /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    26

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    22

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    25

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
            #وصف_ڪريو MAX_CONTEXT_سائيز    21

        #جيڪڏهن_پورو /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #جيڪڏهن_پورو /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #وصف_ڪريو پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #وصف_ڪريو پورٽ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #وصف_ڪريو پورٽ_ACL_داخلا_سائيز_بٽ             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ پورٽ_ڪل_انگ_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_سائيز ];
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
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#إذا ( configASSERT_DEFINED == 1 )
    #إذا ( پورٽ_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ );
        #وصف_ڪريو پورٽ_ASSERT_IF_مداخلت_ترجيح_INVALID()    v_پورٽ_Validate_مداخلت_ترجيح()
    #جيڪڏهن_پورو
#جيڪڏهن_پورو

/**
 * @brief SVC numbers.
 */
#وصف_ڪريو پورٽ_SVC_ALLOCATE_SECURE_CONTEXT    100
#وصف_ڪريو پورٽ_SVC_FREE_SECURE_CONTEXT        101
#وصف_ڪريو پورٽ_SVC_شروعات_SCHEDULER            102
#وصف_ڪريو پورٽ_SVC_RAISE_PRIVILEGE            103
#وصف_ڪريو پورٽ_SVC_SYSTEM_CALL_EXIT           104
#وصف_ڪريو پورٽ_SVC_YIELD                      105
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

#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()                  ul_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب( x )             v_Clear_مداخلت_نقاب( x )
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         ul_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_Clear_مداخلت_نقاب( x )

#إذا ( config_عدد_جو_CORES == 1 )
    #وصف_ڪريو پورٽ_ENTER_CRITICAL()                      v_پورٽ_Enter_Critical()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL()                       v_پورٽ_Exit_Critical()
#وإلا /* ( configNUMBER_OF_CORES == 1 ) */
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );

    #وصف_ڪريو پورٽ_ENTER_CRITICAL()                      vTaskEnterCritical()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL()                       vTaskExitCritical()
    #وصف_ڪريو پورٽ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES != 1 ) */
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
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
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
    #وصف_ڪريو پورٽ_ALLOCATE_SECURE_CONTEXT( ul_Secure_ڍير_سائيز )    v_پورٽ_Allocate_Secure_Context( ul_Secure_ڍير_سائيز )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #وصف_ڪريو پورٽ_CLEAN_مٿي_TCB( pxTCB )                           v_پورٽ_Free_Secure_Context( ( uint32_t * ) pxTCB )
#جيڪڏهن_پورو /* configENABLE_TRUSTZONE */
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

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #إذا ( ( پورٽ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_عدد_جو_CORES == 1 ) )
        #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
    #وإلا
        #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    0
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#إذا ( config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    ساكن پورٽ_FORCE_INLINE uint32_t ul_پورٽ_ڳڻپ_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        أرجع ulReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 different priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو

    #إذا ( پورٽ_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #غلطي ARMv8-M baseline implementations (such as Cortex-M23) افعل not support پورٽ-optimised task selection.  Please سيٽ config_USE_پورٽ_OPTIMISED_TASK_SELECTION منزل 0 or leave it undefined.
    #جيڪڏهن_پورو

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31UL - ul_پورٽ_ڳڻپ_Leading_Zeros( ( uxReadyPriorities ) ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#إذا ( config_عدد_جو_CORES > 1 )
    تعريفنوع تعداد
    {
        e_Isr_تالو = 0,
        e_Task_تالو,
        e_تالو_ڳڻپ
    } e_پورٽ_RTOSLock;

    خارجي متطاير uint32_t ulCriticalNestings[ config_عدد_جو_CORES ];
    خارجي فراغ v_پورٽ_Recursive_تالو( uint8_t ucCoreID,
                                    e_پورٽ_RTOSLock e_تالو_انگ,
                                    بنياد_Type_t uxAcquire );
    خارجي uint8_t uc_پورٽ_Get_Core_ID( فراغ );
    خارجي فراغ v_مداخلت_Core( uint8_t ucCoreID );

    #وصف_ڪريو پورٽ_GET_CORE_ID()                                  uc_پورٽ_Get_Core_ID()

    #وصف_ڪريو پورٽ_GET_CRITICAL_NESTING_ڳڻپ( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #وصف_ڪريو پورٽ_سيٽ_CRITICAL_NESTING_ڳڻپ( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #وصف_ڪريو پورٽ_INCREMENT_CRITICAL_NESTING_ڳڻپ( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #وصف_ڪريو پورٽ_DECREMENT_CRITICAL_NESTING_ڳڻپ( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #وصف_ڪريو پورٽ_MAX_CORE_ڳڻپ                                 ( config_عدد_جو_CORES )

    #وصف_ڪريو پورٽ_YIELD_CORE( xCoreID )                          v_مداخلت_Core( xCoreID )

    #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )                    v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Isr_تالو, pdFALSE )
    #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )                        v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Isr_تالو, pdTRUE )

    #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )                   v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Task_تالو, pdFALSE )
    #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )                       v_پورٽ_Recursive_تالو( ( uint8_t ) xCoreID, e_Task_تالو, pdTRUE )

    #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( بنياد_Type_t x_Write_Control_رجسٽر );
    #جيڪڏهن_پورو /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#جيڪڏهن_پورو

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACROCOMMON_H */
