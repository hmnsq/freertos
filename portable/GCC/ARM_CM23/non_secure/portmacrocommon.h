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

#यदि_अपरिभाषितम् PORTMACROCOMMON_H
#परिभाषय PORTMACROCOMMON_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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

#यदि_अपरिभाषितम् configENABLE_FPU
    #दोषः configENABLE_FPU must be defined अन्तर् FreeRTOSConfig.h.  समुच्चयः_2 configENABLE_FPU गन्तव्यम् 1 गन्तव्यम् enable the FPU or 0 गन्तव्यम् disable the FPU.
#यदि_अन्तः /* configENABLE_FPU */

#यदि_अपरिभाषितम् configENABLE_MPU
    #दोषः configENABLE_MPU must be defined अन्तर् FreeRTOSConfig.h.  समुच्चयः_2 configENABLE_MPU गन्तव्यम् 1 गन्तव्यम् enable the MPU or 0 गन्तव्यम् disable the MPU.
#यदि_अन्तः /* configENABLE_MPU */

#यदि_अपरिभाषितम् configENABLE_TRUSTZONE
    #दोषः configENABLE_TRUSTZONE must be defined अन्तर् FreeRTOSConfig.h.  समुच्चयः_2 configENABLE_TRUSTZONE गन्तव्यम् 1 गन्तव्यम् enable TrustZone or 0 गन्तव्यम् disable TrustZone.
#यदि_अन्तः /* configENABLE_TRUSTZONE */

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
    #यदि ( पत्तनम्_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #दोषः "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #यदि_अन्तः /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #यदि_अपरिभाषितम् config_CORE_ID_पञ्जिकाकोशः
        #दोषः "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #यदि_अन्तः /* ifndef configCORE_ID_REGISTER */

    #यदि_अपरिभाषितम् configWAKE_SECONDARY_CORES
        #दोषः "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #यदि_अन्तः /* ifndef configWAKE_SECONDARY_CORES */
#यदि_अन्तः /* #if ( configNUMBER_OF_CORES > 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश दीर्घ             आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ    UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#परिभाषय पत्तनम्_राशिः_GROWTH                   ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT                 8
#परिभाषय पत्तनम्_NOP()
#परिभाषय पत्तनम्_INLINE                         __inline
#यदि_अपरिभाषितम् पत्तनम्_FORCE_INLINE
    #परिभाषय पत्तनम्_FORCE_INLINE               अन्तःस्थ __attribute__( ( always_inline ) )
#यदि_अन्तः
#परिभाषय पत्तनम्_HAS_राशिः_अतिप्रवाहः_CHECKING    1
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
बाह्य आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य );

बाह्य शून्य v_पत्तनम्_Yield( शून्य ) /* PRIVILEGED_FUNCTION */;

बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य ) /* PRIVILEGED_FUNCTION */;
बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य ) /* PRIVILEGED_FUNCTION */;

बाह्य uint32_t ul_समुच्चयः_व्यवधानम्_आवरणम्( शून्य ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
बाह्य शून्य v_Clear_व्यवधानम्_आवरणम्( uint32_t ul_आवरणम् ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#यदि ( configENABLE_TRUSTZONE == 1 )
    बाह्य शून्य v_पत्तनम्_Allocate_Secure_Context( uint32_t ul_Secure_राशिः_आकार ); /* __attribute__ (( naked )) */
    बाह्य शून्य v_पत्तनम्_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#यदि_अन्तः /* configENABLE_TRUSTZONE */

#यदि ( configENABLE_MPU == 1 )
    बाह्य आधारः_Type_t xIsPrivileged( शून्य ) /* __attribute__ (( naked )) */;
    बाह्य शून्य vResetPrivilege( शून्य ) /* __attribute__ (( naked )) */;
#यदि_अन्तः /* configENABLE_MPU */

#यदि ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    शून्य v_Application_Generate_Task_Random_Pac_कुञ्चिका( uint32_t * pul_Task_Pac_कुञ्चिका );

#यदि_अन्तः /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#यदि ( configENABLE_MPU == 1 )
    #परिभाषय पत्तनम्_USING_MPU_WRAPPERS    1
    #परिभाषय पत्तनम्_PRIVILEGE_BIT         ( 0x80000000UL )
#अन्यथा
    #परिभाषय पत्तनम्_PRIVILEGE_BIT         ( 0x0UL )
#यदि_अन्तः /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#यदि_अपरिभाषितम् config_योग_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #परिभाषय config_योग_MPU_REGIONS    ( 8UL )
#यदि_अन्तः

/* MPU regions. */
#परिभाषय पत्तनम्_PRIVILEGED_FLASH_REGION                   ( 0UL )
#परिभाषय पत्तनम्_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#परिभाषय पत्तनम्_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#परिभाषय पत्तनम्_PRIVILEGED_RAM_REGION                     ( 3UL )
#परिभाषय पत्तनम्_राशिः_REGION                              ( 4UL )
#परिभाषय पत्तनम्_FIRST_CONFIGURABLE_REGION                 ( 5UL )
#परिभाषय पत्तनम्_चरमः_CONFIGURABLE_REGION                  ( config_योग_MPU_REGIONS - 1UL )
#परिभाषय पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS                  ( ( पत्तनम्_चरमः_CONFIGURABLE_REGION - पत्तनम्_FIRST_CONFIGURABLE_REGION ) + 1 )
#परिभाषय पत्तनम्_योग_अङ्कः_REGIONS                         ( पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_n_GRE                    ( 0x08 )       /* 0000 1000 */
#परिभाषय पत्तनम्_MPU_DEVICE_स्मृतिः_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#परिभाषय पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#परिभाषय पत्तनम्_MPU_प्रसामान्यम्_स्मृतिः_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#परिभाषय पत्तनम्_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#परिभाषय पत्तनम्_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#परिभाषय पत्तनम्_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#परिभाषय पत्तनम्_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    प्रकारनिर्देश संरचना MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
    } MPURegionSettings_t;

    #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #यदि_अपरिभाषितम् config_SYSTEM_CALL_राशिः_आकार
            #दोषः config_SYSTEM_CALL_राशिः_आकार must be defined गन्तव्यम् the desired आकार सम्बन्धि the system call राशिः अन्तर् शब्दाः प्रति using MPU wrappers v2.
        #यदि_अन्तः

        /**
         * @brief System call stack.
         */
        प्रकारनिर्देश संरचना SYSTEM_CALL_राशिः_INFO
        {
            uint32_t ul_System_Call_राशिः_बफर[ config_SYSTEM_CALL_राशिः_आकार ];
            uint32_t * pul_System_Call_राशिः;
            uint32_t * pul_System_Call_राशिः_सीमा;
            uint32_t * pul_Task_राशिः;
            uint32_t ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
            uint32_t ul_राशिः_सीमा_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
        } x_SYSTEM_CALL_राशिः_INFO;

    #यदि_अन्तः /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #यदि ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #यदि ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #परिभाषय MAX_CONTEXT_आकार    59

        #नोचेद्यदि ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #परिभाषय MAX_CONTEXT_आकार    55

        #नोचेद्यदि ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #परिभाषय MAX_CONTEXT_आकार    58

        #अन्यथा /* if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

            /*
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |     |
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><---->
             *      16             17            8               8                  4              1
             */
            #परिभाषय MAX_CONTEXT_आकार    54

        #यदि_अन्तः /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #अन्यथा /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #यदि ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #परिभाषय MAX_CONTEXT_आकार    26

        #नोचेद्यदि ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #परिभाषय MAX_CONTEXT_आकार    22

        #नोचेद्यदि ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #परिभाषय MAX_CONTEXT_आकार    25

        #अन्यथा /* #if( configENABLE_TRUSTZONE == 1 ) */

            /*
             * +----------+-----------------+----------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |          | PC, xPSR        | EXC_RETURN           |     |
             * +----------+-----------------+----------------------+-----+
             *
             * <---------><----------------><----------------------><---->
             *     8               8                  4              1
             */
            #परिभाषय MAX_CONTEXT_आकार    21

        #यदि_अन्तः /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #यदि_अन्तः /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #परिभाषय पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #परिभाषय पत्तनम्_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #परिभाषय पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः             ( 32U )

    प्रकारनिर्देश संरचना MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ पत्तनम्_योग_अङ्कः_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_आकार ];
        uint32_t ulTaskFlags;

        #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_राशिः_INFO x_System_Call_राशिः_Info;
            #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः ) + 1 ];
            #यदि_अन्तः
        #यदि_अन्तः
    } xMPU_SETTINGS;

#यदि_अन्तः /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#यदि ( configASSERT_DEFINED == 1 )
    #यदि ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य );
        #परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता()
    #यदि_अन्तः
#यदि_अन्तः

/**
 * @brief SVC numbers.
 */
#परिभाषय पत्तनम्_SVC_ALLOCATE_SECURE_CONTEXT    100
#परिभाषय पत्तनम्_SVC_FREE_SECURE_CONTEXT        101
#परिभाषय पत्तनम्_SVC_START_SCHEDULER            102
#परिभाषय पत्तनम्_SVC_RAISE_PRIVILEGE            103
#परिभाषय पत्तनम्_SVC_SYSTEM_CALL_EXIT           104
#परिभाषय पत्तनम्_SVC_YIELD                      105
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#यदि ( configENABLE_MPU == 1 )
    #परिभाषय पत्तनम्_YIELD()               __asm चञ्चल ( "svc %0" ::"i" ( पत्तनम्_SVC_YIELD ) : "memory" )
    #परिभाषय पत्तनम्_YIELD_WITHIN_API()    v_पत्तनम्_Yield()
#अन्यथा
    #परिभाषय पत्तनम्_YIELD()               v_पत्तनम्_Yield()
    #परिभाषय पत्तनम्_YIELD_WITHIN_API()    v_पत्तनम्_Yield()
#यदि_अन्तः

#परिभाषय पत्तनम्_NVIC_INT_CTRL_REG     ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#परिभाषय पत्तनम्_NVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )            \
    कुरु                                                      \
    {                                                       \
        यदि( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();                   \
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } यावत्( 0 )
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */

#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()                  ul_समुच्चयः_व्यवधानम्_आवरणम्()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्( x )             v_Clear_व्यवधानम्_आवरणम्( x )
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_समुच्चयः_व्यवधानम्_आवरणम्()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_Clear_व्यवधानम्_आवरणम्( x )

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    #परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical()
    #परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical()
#अन्यथा /* ( configNUMBER_OF_CORES == 1 ) */
    बाह्य शून्य vTaskEnterCritical( शून्य );
    बाह्य शून्य vTaskExitCritical( शून्य );
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( शून्य );
    बाह्य शून्य vTaskExitCriticalFromISR( UBaseType_t ux_Saved_व्यवधानम्_स्थितिः );

    #परिभाषय पत्तनम्_ENTER_CRITICAL()                      vTaskEnterCritical()
    #परिभाषय पत्तनम्_EXIT_CRITICAL()                       vTaskExitCritical()
    #परिभाषय पत्तनम्_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #परिभाषय पत्तनम्_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#यदि_अन्तः /* if ( configNUMBER_OF_CORES != 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#यदि_अपरिभाषितम् पत्तनम्_SUPPRESS_TICKS_AND_SLEEP
    बाह्य शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime );
    #परिभाषय पत्तनम्_SUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    v_पत्तनम्_Suppress_Ticks_And_Sleep( xExpectedIdleTime )
#यदि_अन्तः
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

#यदि ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #परिभाषय पत्तनम्_ALLOCATE_SECURE_CONTEXT( ul_Secure_राशिः_आकार )    v_पत्तनम्_Allocate_Secure_Context( ul_Secure_राशिः_आकार )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #परिभाषय पत्तनम्_CLEAN_ऊर्ध्वम्_TCB( pxTCB )                           v_पत्तनम्_Free_Secure_Context( ( uint32_t * ) pxTCB )
#यदि_अन्तः /* configENABLE_TRUSTZONE */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
    #परिभाषय पत्तनम्_IS_PRIVILEGED()      xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 *
 * The SVC handler checks that the SVC was raised from a system call and only
 * then it raises the privilege. If this is called from any other place,
 * the privilege is not raised.
 */
    #परिभाषय पत्तनम्_RAISE_PRIVILEGE()    __asm चञ्चल ( "svc %0 \n" ::"i" ( पत्तनम्_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
    #परिभाषय पत्तनम्_RESET_PRIVILEGE()    vResetPrivilege()
#अन्यथा
    #परिभाषय पत्तनम्_IS_PRIVILEGED()
    #परिभाषय पत्तनम्_RAISE_PRIVILEGE()
    #परिभाषय पत्तनम्_RESET_PRIVILEGE()
#यदि_अन्तः /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    बाह्य आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
    #परिभाषय पत्तनम्_IS_TASK_PRIVILEGED()    x_पत्तनम्_Is_Task_Privileged()

#यदि_अन्तः /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#परिभाषय पत्तनम्_स्मृतिः_BARRIER()    __asm चञ्चल ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #यदि ( ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_सङ्ख्या_सम्बन्धि_CORES == 1 ) )
        #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
    #अन्यथा
        #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    0
    #यदि_अन्तः
#यदि_अन्तः /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#यदि ( config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    स्थिर पत्तनम्_FORCE_INLINE uint32_t ul_पत्तनम्_गणनम्_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm चञ्चल ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        प्रत्यागम ulReturn;
    }

/* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 different priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः

    #यदि ( पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #दोषः ARMv8-M baseline implementations (such as Cortex-M23) कुरु not support पत्तनम्-optimised task selection.  Please समुच्चयः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION गन्तव्यम् 0 or leave it undefined.
    #यदि_अन्तः

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31UL - ul_पत्तनम्_गणनम्_Leading_Zeros( ( uxReadyPriorities ) ) )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
    प्रकारनिर्देश गणना
    {
        e_Isr_तालकम् = 0,
        e_Task_तालकम्,
        e_तालकम्_गणनम्
    } e_पत्तनम्_RTOSLock;

    बाह्य चञ्चल uint32_t ulCriticalNestings[ config_सङ्ख्या_सम्बन्धि_CORES ];
    बाह्य शून्य v_पत्तनम्_Recursive_तालकम्( uint8_t ucCoreID,
                                    e_पत्तनम्_RTOSLock e_तालकम्_अङ्कः,
                                    आधारः_Type_t uxAcquire );
    बाह्य uint8_t uc_पत्तनम्_Get_Core_ID( शून्य );
    बाह्य शून्य v_व्यवधानम्_Core( uint8_t ucCoreID );

    #परिभाषय पत्तनम्_GET_CORE_ID()                                  uc_पत्तनम्_Get_Core_ID()

    #परिभाषय पत्तनम्_GET_CRITICAL_NESTING_गणनम्( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #परिभाषय पत्तनम्_समुच्चयः_CRITICAL_NESTING_गणनम्( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #परिभाषय पत्तनम्_INCREMENT_CRITICAL_NESTING_गणनम्( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #परिभाषय पत्तनम्_DECREMENT_CRITICAL_NESTING_गणनम्( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #परिभाषय पत्तनम्_MAX_CORE_गणनम्                                 ( config_सङ्ख्या_सम्बन्धि_CORES )

    #परिभाषय पत्तनम्_YIELD_CORE( xCoreID )                          v_व्यवधानम्_Core( xCoreID )

    #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )                    v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Isr_तालकम्, pdFALSE )
    #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )                        v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Isr_तालकम्, pdTRUE )

    #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )                   v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Task_तालकम्, pdFALSE )
    #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )                       v_पत्तनम्_Recursive_तालकम्( ( uint8_t ) xCoreID, e_Task_तालकम्, pdTRUE )

    #यदि ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( आधारः_Type_t x_Write_Control_पञ्जिकाकोशः );
    #यदि_अन्तः /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#यदि_अन्तः

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACROCOMMON_H */
