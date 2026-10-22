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

#నిర్వచితం_కాకపోతే PORTMACROCOMMON_H
#నిర్వచించు PORTMACROCOMMON_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
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

#నిర్వచితం_కాకపోతే configENABLE_FPU
    #దోషం configENABLE_FPU must be defined లోపల FreeRTOSConfig.h.  సమితి_2 configENABLE_FPU గమ్యం 1 గమ్యం enable the FPU or 0 గమ్యం disable the FPU.
#అయితే_ముగింపు /* configENABLE_FPU */

#నిర్వచితం_కాకపోతే configENABLE_MPU
    #దోషం configENABLE_MPU must be defined లోపల FreeRTOSConfig.h.  సమితి_2 configENABLE_MPU గమ్యం 1 గమ్యం enable the MPU or 0 గమ్యం disable the MPU.
#అయితే_ముగింపు /* configENABLE_MPU */

#నిర్వచితం_కాకపోతే configENABLE_TRUSTZONE
    #దోషం configENABLE_TRUSTZONE must be defined లోపల FreeRTOSConfig.h.  సమితి_2 configENABLE_TRUSTZONE గమ్యం 1 గమ్యం enable TrustZone or 0 గమ్యం disable TrustZone.
#అయితే_ముగింపు /* configENABLE_TRUSTZONE */

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
    #ఒకవేళ ( పోర్టు_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #దోషం "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #అయితే_ముగింపు /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #నిర్వచితం_కాకపోతే config_CORE_ID_రిజిస్టరు
        #దోషం "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #అయితే_ముగింపు /* ifndef configCORE_ID_REGISTER */

    #నిర్వచితం_కాకపోతే configWAKE_SECONDARY_CORES
        #దోషం "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #అయితే_ముగింపు /* ifndef configWAKE_SECONDARY_CORES */
#అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES > 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#నిర్వచించు పోర్టు_దొంతర_GROWTH                   ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT                 8
#నిర్వచించు పోర్టు_NOP()
#నిర్వచించు పోర్టు_INLINE                         __inline
#నిర్వచితం_కాకపోతే పోర్టు_FORCE_INLINE
    #నిర్వచించు పోర్టు_FORCE_INLINE               అంతఃవరుస __attribute__( ( always_inline ) )
#అయితే_ముగింపు
#నిర్వచించు పోర్టు_HAS_దొంతర_అధికప్రవాహం_CHECKING    1
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
బాహ్య పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య );

బాహ్య శూన్య v_పోర్టు_Yield( శూన్య ) /* PRIVILEGED_FUNCTION */;

బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య ) /* PRIVILEGED_FUNCTION */;
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య ) /* PRIVILEGED_FUNCTION */;

బాహ్య uint32_t ul_సమితి_అంతరాయం_ముసుగు( శూన్య ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
బాహ్య శూన్య v_Clear_అంతరాయం_ముసుగు( uint32_t ul_ముసుగు ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#ఒకవేళ ( configENABLE_TRUSTZONE == 1 )
    బాహ్య శూన్య v_పోర్టు_Allocate_Secure_Context( uint32_t ul_Secure_దొంతర_కొలత ); /* __attribute__ (( naked )) */
    బాహ్య శూన్య v_పోర్టు_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#అయితే_ముగింపు /* configENABLE_TRUSTZONE */

#ఒకవేళ ( configENABLE_MPU == 1 )
    బాహ్య పునాది_Type_t xIsPrivileged( శూన్య ) /* __attribute__ (( naked )) */;
    బాహ్య శూన్య vResetPrivilege( శూన్య ) /* __attribute__ (( naked )) */;
#అయితే_ముగింపు /* configENABLE_MPU */

#ఒకవేళ ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    శూన్య v_Application_Generate_Task_Random_Pac_కీలకం( uint32_t * pul_Task_Pac_కీలకం );

#అయితే_ముగింపు /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#ఒకవేళ ( configENABLE_MPU == 1 )
    #నిర్వచించు పోర్టు_USING_MPU_WRAPPERS    1
    #నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు         ( 0x80000000UL )
#లేకపోతే
    #నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు         ( 0x0UL )
#అయితే_ముగింపు /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#నిర్వచితం_కాకపోతే config_మొత్తం_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #నిర్వచించు config_మొత్తం_MPU_REGIONS    ( 8UL )
#అయితే_ముగింపు

/* MPU regions. */
#నిర్వచించు పోర్టు_PRIVILEGED_FLASH_REGION                   ( 0UL )
#నిర్వచించు పోర్టు_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#నిర్వచించు పోర్టు_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#నిర్వచించు పోర్టు_PRIVILEGED_RAM_REGION                     ( 3UL )
#నిర్వచించు పోర్టు_దొంతర_REGION                              ( 4UL )
#నిర్వచించు పోర్టు_మొదటి_CONFIGURABLE_REGION                 ( 5UL )
#నిర్వచించు పోర్టు_చివరి_CONFIGURABLE_REGION                  ( config_మొత్తం_MPU_REGIONS - 1UL )
#నిర్వచించు పోర్టు_అంకె_CONFIGURABLE_REGIONS                  ( ( పోర్టు_చివరి_CONFIGURABLE_REGION - పోర్టు_మొదటి_CONFIGURABLE_REGION ) + 1 )
#నిర్వచించు పోర్టు_మొత్తం_అంకె_REGIONS                         ( పోర్టు_అంకె_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_n_GRE                    ( 0x08 )       /* 0000 1000 */
#నిర్వచించు పోర్టు_MPU_DEVICE_జ్ఞాపకం_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#నిర్వచించు పోర్టు_MPU_సాధారణ_జ్ఞాపకం_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#నిర్వచించు పోర్టు_MPU_సాధారణ_జ్ఞాపకం_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#నిర్వచించు పోర్టు_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#నిర్వచించు పోర్టు_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#నిర్వచించు పోర్టు_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#నిర్వచించు పోర్టు_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    రకనిర్వచనం నిర్మాణం MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
    } MPURegionSettings_t;

    #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #నిర్వచితం_కాకపోతే config_SYSTEM_CALL_దొంతర_కొలత
            #దోషం config_SYSTEM_CALL_దొంతర_కొలత must be defined గమ్యం the desired కొలత యొక్క the system call దొంతర లోపల పదాలు కొరకు using MPU wrappers v2.
        #అయితే_ముగింపు

        /**
         * @brief System call stack.
         */
        రకనిర్వచనం నిర్మాణం SYSTEM_CALL_దొంతర_INFO
        {
            uint32_t ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత ];
            uint32_t * pul_System_Call_దొంతర;
            uint32_t * pul_System_Call_దొంతర_హద్దు;
            uint32_t * pul_Task_దొంతర;
            uint32_t ul_Link_రిజిస్టరు_At_System_Call_నమోదు;
            uint32_t ul_దొంతర_హద్దు_రిజిస్టరు_At_System_Call_నమోదు;
        } x_SYSTEM_CALL_దొంతర_INFO;

    #అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #ఒకవేళ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #ఒకవేళ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    59

        #లేదావేళ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    55

        #లేదావేళ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    58

        #లేకపోతే /* if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

            /*
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |     |
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><---->
             *      16             17            8               8                  4              1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    54

        #అయితే_ముగింపు /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #లేకపోతే /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #ఒకవేళ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    26

        #లేదావేళ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    22

        #లేదావేళ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    25

        #లేకపోతే /* #if( configENABLE_TRUSTZONE == 1 ) */

            /*
             * +----------+-----------------+----------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |          | PC, xPSR        | EXC_RETURN           |     |
             * +----------+-----------------+----------------------+-----+
             *
             * <---------><----------------><----------------------><---->
             *     8               8                  4              1
             */
            #నిర్వచించు MAX_CONTEXT_కొలత    21

        #అయితే_ముగింపు /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #అయితే_ముగింపు /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #నిర్వచించు పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #నిర్వచించు పోర్టు_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #నిర్వచించు పోర్టు_ACL_నమోదు_కొలత_బిట్లు             ( 32U )

    రకనిర్వచనం నిర్మాణం MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ పోర్టు_మొత్తం_అంకె_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_కొలత ];
        uint32_t ulTaskFlags;

        #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_దొంతర_INFO x_System_Call_దొంతర_Info;
            #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_కొలత / పోర్టు_ACL_నమోదు_కొలత_బిట్లు ) + 1 ];
            #అయితే_ముగింపు
        #అయితే_ముగింపు
    } xMPU_SETTINGS;

#అయితే_ముగింపు /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#ఒకవేళ ( configASSERT_DEFINED == 1 )
    #ఒకవేళ ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య );
        #నిర్వచించు పోర్టు_ASSERT_IF_అంతరాయం_ప్రాధాన్యత_INVALID()    v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత()
    #అయితే_ముగింపు
#అయితే_ముగింపు

/**
 * @brief SVC numbers.
 */
#నిర్వచించు పోర్టు_SVC_ALLOCATE_SECURE_CONTEXT    100
#నిర్వచించు పోర్టు_SVC_FREE_SECURE_CONTEXT        101
#నిర్వచించు పోర్టు_SVC_ప్రారంభం_SCHEDULER            102
#నిర్వచించు పోర్టు_SVC_RAISE_PRIVILEGE            103
#నిర్వచించు పోర్టు_SVC_SYSTEM_CALL_EXIT           104
#నిర్వచించు పోర్టు_SVC_YIELD                      105
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#ఒకవేళ ( configENABLE_MPU == 1 )
    #నిర్వచించు పోర్టు_YIELD()               __asm అస్థిర ( "svc %0" ::"i" ( పోర్టు_SVC_YIELD ) : "memory" )
    #నిర్వచించు పోర్టు_YIELD_WITHIN_API()    v_పోర్టు_Yield()
#లేకపోతే
    #నిర్వచించు పోర్టు_YIELD()               v_పోర్టు_Yield()
    #నిర్వచించు పోర్టు_YIELD_WITHIN_API()    v_పోర్టు_Yield()
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_NVIC_INT_CTRL_REG     ( *( ( అస్థిర uint32_t * ) 0xe000ed04 ) )
#నిర్వచించు పోర్టు_NVIC_PENDSVSET_బిట్టు    ( 1UL << 28UL )
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )            \
    చేయి                                                      \
    {                                                       \
        ఒకవేళ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();                   \
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు; \
        }                                                   \
        లేకపోతే                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } అయితే( 0 )
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */

#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()                  ul_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు( x )             v_Clear_అంతరాయం_ముసుగు( x )
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ul_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_Clear_అంతరాయం_ముసుగు( x )

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    #నిర్వచించు పోర్టు_ENTER_CRITICAL()                      v_పోర్టు_Enter_Critical()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()                       v_పోర్టు_Exit_Critical()
#లేకపోతే /* ( configNUMBER_OF_CORES == 1 ) */
    బాహ్య శూన్య vTaskEnterCritical( శూన్య );
    బాహ్య శూన్య vTaskExitCritical( శూన్య );
    బాహ్య UBaseType_t vTaskEnterCriticalFromISR( శూన్య );
    బాహ్య శూన్య vTaskExitCriticalFromISR( UBaseType_t ux_Saved_అంతరాయం_స్థితి );

    #నిర్వచించు పోర్టు_ENTER_CRITICAL()                      vTaskEnterCritical()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()                       vTaskExitCritical()
    #నిర్వచించు పోర్టు_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES != 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#నిర్వచితం_కాకపోతే పోర్టు_SUPPRESS_TICKS_AND_SLEEP
    బాహ్య శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం );
    #నిర్వచించు పోర్టు_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_సమయం )    v_పోర్టు_Suppress_Ticks_And_Sleep( x_Expected_Idle_సమయం )
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #నిర్వచించు పోర్టు_ALLOCATE_SECURE_CONTEXT( ul_Secure_దొంతర_కొలత )    v_పోర్టు_Allocate_Secure_Context( ul_Secure_దొంతర_కొలత )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #నిర్వచించు పోర్టు_CLEAN_పైకి_TCB( pxTCB )                           v_పోర్టు_Free_Secure_Context( ( uint32_t * ) pxTCB )
#అయితే_ముగింపు /* configENABLE_TRUSTZONE */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
    #నిర్వచించు పోర్టు_IS_PRIVILEGED()      xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 *
 * The SVC handler checks that the SVC was raised from a system call and only
 * then it raises the privilege. If this is called from any other place,
 * the privilege is not raised.
 */
    #నిర్వచించు పోర్టు_RAISE_PRIVILEGE()    __asm అస్థిర ( "svc %0 \n" ::"i" ( పోర్టు_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
    #నిర్వచించు పోర్టు_RESET_PRIVILEGE()    vResetPrivilege()
#లేకపోతే
    #నిర్వచించు పోర్టు_IS_PRIVILEGED()
    #నిర్వచించు పోర్టు_RAISE_PRIVILEGE()
    #నిర్వచించు పోర్టు_RESET_PRIVILEGE()
#అయితే_ముగింపు /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    బాహ్య పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
    #నిర్వచించు పోర్టు_IS_TASK_PRIVILEGED()    x_పోర్టు_Is_Task_Privileged()

#అయితే_ముగింపు /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #ఒకవేళ ( ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_సంఖ్య_యొక్క_CORES == 1 ) )
        #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
    #లేకపోతే
        #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    0
    #అయితే_ముగింపు
#అయితే_ముగింపు /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#ఒకవేళ ( config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    స్థిర పోర్టు_FORCE_INLINE uint32_t ul_పోర్టు_లెక్క_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm అస్థిర ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        తిరిగి ulReturn;
    }

/* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 different priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
    #అయితే_ముగింపు

    #ఒకవేళ ( పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #దోషం ARMv8-M baseline implementations (such as Cortex-M23) చేయి not support పోర్టు-optimised task selection.  Please సమితి config_USE_పోర్టు_OPTIMISED_TASK_SELECTION గమ్యం 0 or leave it undefined.
    #అయితే_ముగింపు

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    ux_శిఖరం_ప్రాధాన్యత = ( 31UL - ul_పోర్టు_లెక్క_Leading_Zeros( ( uxReadyPriorities ) ) )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
    రకనిర్వచనం గణన
    {
        e_Isr_తాళం = 0,
        e_Task_తాళం,
        e_తాళం_లెక్క
    } e_పోర్టు_RTOSLock;

    బాహ్య అస్థిర uint32_t ulCriticalNestings[ config_సంఖ్య_యొక్క_CORES ];
    బాహ్య శూన్య v_పోర్టు_Recursive_తాళం( uint8_t ucCoreID,
                                    e_పోర్టు_RTOSLock e_తాళం_అంకె,
                                    పునాది_Type_t uxAcquire );
    బాహ్య uint8_t uc_పోర్టు_Get_Core_ID( శూన్య );
    బాహ్య శూన్య v_అంతరాయం_Core( uint8_t ucCoreID );

    #నిర్వచించు పోర్టు_GET_CORE_ID()                                  uc_పోర్టు_Get_Core_ID()

    #నిర్వచించు పోర్టు_GET_CRITICAL_NESTING_లెక్క( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #నిర్వచించు పోర్టు_సమితి_CRITICAL_NESTING_లెక్క( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #నిర్వచించు పోర్టు_INCREMENT_CRITICAL_NESTING_లెక్క( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #నిర్వచించు పోర్టు_DECREMENT_CRITICAL_NESTING_లెక్క( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #నిర్వచించు పోర్టు_MAX_CORE_లెక్క                                 ( config_సంఖ్య_యొక్క_CORES )

    #నిర్వచించు పోర్టు_YIELD_CORE( xCoreID )                          v_అంతరాయం_Core( xCoreID )

    #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )                    v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Isr_తాళం, pdFALSE )
    #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )                        v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Isr_తాళం, pdTRUE )

    #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )                   v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Task_తాళం, pdFALSE )
    #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )                       v_పోర్టు_Recursive_తాళం( ( uint8_t ) xCoreID, e_Task_తాళం, pdTRUE )

    #ఒకవేళ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( పునాది_Type_t x_Write_Control_రిజిస్టరు );
    #అయితే_ముగింపు /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#అయితే_ముగింపు

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACROCOMMON_H */
