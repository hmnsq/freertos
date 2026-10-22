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

#که_نه_تعریف_شوی PORTMACROCOMMON_H
#تعریف_کړه PORTMACROCOMMON_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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

#که_نه_تعریف_شوی configENABLE_FPU
    #تېروتنه configENABLE_FPU must be defined دننه FreeRTOSConfig.h.  سېټ_2 configENABLE_FPU منزل 1 منزل enable the FPU or 0 منزل disable the FPU.
#د_که_پای /* configENABLE_FPU */

#که_نه_تعریف_شوی configENABLE_MPU
    #تېروتنه configENABLE_MPU must be defined دننه FreeRTOSConfig.h.  سېټ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#د_که_پای /* configENABLE_MPU */

#که_نه_تعریف_شوی configENABLE_TRUSTZONE
    #تېروتنه configENABLE_TRUSTZONE must be defined دننه FreeRTOSConfig.h.  سېټ_2 configENABLE_TRUSTZONE منزل 1 منزل enable TrustZone or 0 منزل disable TrustZone.
#د_که_پای /* configENABLE_TRUSTZONE */

#إذا ( config_شمېره_د_CORES > 1 )
    #إذا ( پورټ_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #تېروتنه "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #د_که_پای /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #که_نه_تعریف_شوی config_CORE_ID_ثبتوونکی
        #تېروتنه "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #د_که_پای /* ifndef configCORE_ID_REGISTER */

    #که_نه_تعریف_شوی configWAKE_SECONDARY_CORES
        #تېروتنه "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #د_که_پای /* ifndef configWAKE_SECONDARY_CORES */
#د_که_پای /* #if ( configNUMBER_OF_CORES > 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#تعریف_کړه پورټ_ډېری_GROWTH                   ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT                 8
#تعریف_کړه پورټ_NOP()
#تعریف_کړه پورټ_INLINE                         __inline
#که_نه_تعریف_شوی پورټ_FORCE_INLINE
    #تعریف_کړه پورټ_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#د_که_پای
#تعریف_کړه پورټ_HAS_ډېری_ډکېدنه_CHECKING    1
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
خارجي بنسټ_Type_t x_پورټ_Is_Inside_مداخله( فراغ );

خارجي فراغ v_پورټ_Yield( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي فراغ v_پورټ_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;
خارجي فراغ v_پورټ_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي uint32_t ul_سېټ_مداخله_ماسک( فراغ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
خارجي فراغ v_Clear_مداخله_ماسک( uint32_t ul_ماسک ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#إذا ( configENABLE_TRUSTZONE == 1 )
    خارجي فراغ v_پورټ_Allocate_Secure_Context( uint32_t ul_Secure_ډېری_اندازه ); /* __attribute__ (( naked )) */
    خارجي فراغ v_پورټ_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#د_که_پای /* configENABLE_TRUSTZONE */

#إذا ( configENABLE_MPU == 1 )
    خارجي بنسټ_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#د_که_پای /* configENABLE_MPU */

#إذا ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    فراغ v_Application_Generate_Task_Random_Pac_کلی( uint32_t * pul_Task_Pac_کلی );

#د_که_پای /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کړه پورټ_USING_MPU_WRAPPERS    1
    #تعریف_کړه پورټ_PRIVILEGE_بټ         ( 0x80000000UL )
#وإلا
    #تعریف_کړه پورټ_PRIVILEGE_بټ         ( 0x0UL )
#د_که_پای /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#که_نه_تعریف_شوی config_ټول_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #تعریف_کړه config_ټول_MPU_REGIONS    ( 8UL )
#د_که_پای

/* MPU regions. */
#تعریف_کړه پورټ_PRIVILEGED_FLASH_REGION                   ( 0UL )
#تعریف_کړه پورټ_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#تعریف_کړه پورټ_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#تعریف_کړه پورټ_PRIVILEGED_RAM_REGION                     ( 3UL )
#تعریف_کړه پورټ_ډېری_REGION                              ( 4UL )
#تعریف_کړه پورټ_لومړی_CONFIGURABLE_REGION                 ( 5UL )
#تعریف_کړه پورټ_وروستی_CONFIGURABLE_REGION                  ( config_ټول_MPU_REGIONS - 1UL )
#تعریف_کړه پورټ_عدد_CONFIGURABLE_REGIONS                  ( ( پورټ_وروستی_CONFIGURABLE_REGION - پورټ_لومړی_CONFIGURABLE_REGION ) + 1 )
#تعریف_کړه پورټ_ټول_عدد_REGIONS                         ( پورټ_عدد_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#تعریف_کړه پورټ_MPU_DEVICE_حافظه_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#تعریف_کړه پورټ_MPU_DEVICE_حافظه_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#تعریف_کړه پورټ_MPU_DEVICE_حافظه_n_GRE                    ( 0x08 )       /* 0000 1000 */
#تعریف_کړه پورټ_MPU_DEVICE_حافظه_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#تعریف_کړه پورټ_MPU_نورمال_حافظه_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#تعریف_کړه پورټ_MPU_نورمال_حافظه_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#تعریف_کړه پورټ_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#تعریف_کړه پورټ_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#تعریف_کړه پورټ_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#تعریف_کړه پورټ_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
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

        #که_نه_تعریف_شوی config_SYSTEM_CALL_ډېری_اندازه
            #تېروتنه config_SYSTEM_CALL_ډېری_اندازه must be defined منزل the desired اندازه د the system call ډېری دننه ټکي لكل using MPU wrappers v2.
        #د_که_پای

        /**
         * @brief System call stack.
         */
        تعريفنوع بنية SYSTEM_CALL_ډېری_INFO
        {
            uint32_t ul_System_Call_ډېری_بفر[ config_SYSTEM_CALL_ډېری_اندازه ];
            uint32_t * pul_System_Call_ډېری;
            uint32_t * pul_System_Call_ډېری_حد;
            uint32_t * pul_Task_ډېری;
            uint32_t ul_Link_ثبتوونکی_At_System_Call_ثبت;
            uint32_t ul_ډېری_حد_ثبتوونکی_At_System_Call_ثبت;
        } x_SYSTEM_CALL_ډېری_INFO;

    #د_که_پای /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
            #تعریف_کړه MAX_CONTEXT_اندازه    59

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
            #تعریف_کړه MAX_CONTEXT_اندازه    55

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
            #تعریف_کړه MAX_CONTEXT_اندازه    58

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
            #تعریف_کړه MAX_CONTEXT_اندازه    54

        #د_که_پای /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

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
            #تعریف_کړه MAX_CONTEXT_اندازه    26

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
            #تعریف_کړه MAX_CONTEXT_اندازه    22

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
            #تعریف_کړه MAX_CONTEXT_اندازه    25

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
            #تعریف_کړه MAX_CONTEXT_اندازه    21

        #د_که_پای /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #د_که_پای /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کړه پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کړه پورټ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کړه پورټ_ACL_ثبت_اندازه_بټونه             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ پورټ_ټول_عدد_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_اندازه ];
        uint32_t ulTaskFlags;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ډېری_INFO x_System_Call_ډېری_Info;
            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورټ_ACL_ثبت_اندازه_بټونه ) + 1 ];
            #د_که_پای
        #د_که_پای
    } xMPU_SETTINGS;

#د_که_پای /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#إذا ( configASSERT_DEFINED == 1 )
    #إذا ( پورټ_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ );
        #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    v_پورټ_Validate_مداخله_لومړیتوب()
    #د_که_پای
#د_که_پای

/**
 * @brief SVC numbers.
 */
#تعریف_کړه پورټ_SVC_ALLOCATE_SECURE_CONTEXT    100
#تعریف_کړه پورټ_SVC_FREE_SECURE_CONTEXT        101
#تعریف_کړه پورټ_SVC_پیل_SCHEDULER            102
#تعریف_کړه پورټ_SVC_RAISE_PRIVILEGE            103
#تعریف_کړه پورټ_SVC_SYSTEM_CALL_EXIT           104
#تعریف_کړه پورټ_SVC_YIELD                      105
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کړه پورټ_YIELD()               __asm متطاير ( "svc %0" ::"i" ( پورټ_SVC_YIELD ) : "memory" )
    #تعریف_کړه پورټ_YIELD_WITHIN_API()    v_پورټ_Yield()
#وإلا
    #تعریف_کړه پورټ_YIELD()               v_پورټ_Yield()
    #تعریف_کړه پورټ_YIELD_WITHIN_API()    v_پورټ_Yield()
#د_که_پای

#تعریف_کړه پورټ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کړه پورټ_NVIC_PENDSVSET_بټ    ( 1UL << 28UL )
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */

#تعریف_کړه پورټ_سېټ_مداخله_ماسک()                  ul_سېټ_مداخله_ماسک()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک( x )             v_Clear_مداخله_ماسک( x )
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         ul_سېټ_مداخله_ماسک()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    v_Clear_مداخله_ماسک( x )

#إذا ( config_شمېره_د_CORES == 1 )
    #تعریف_کړه پورټ_ENTER_CRITICAL()                      v_پورټ_Enter_Critical()
    #تعریف_کړه پورټ_EXIT_CRITICAL()                       v_پورټ_Exit_Critical()
#وإلا /* ( configNUMBER_OF_CORES == 1 ) */
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخله_حالت );

    #تعریف_کړه پورټ_ENTER_CRITICAL()                      vTaskEnterCritical()
    #تعریف_کړه پورټ_EXIT_CRITICAL()                       vTaskExitCritical()
    #تعریف_کړه پورټ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کړه پورټ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#د_که_پای /* if ( configNUMBER_OF_CORES != 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#که_نه_تعریف_شوی پورټ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت );
    #تعریف_کړه پورټ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وخت )    v_پورټ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وخت )
#د_که_پای
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
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
    #تعریف_کړه پورټ_ALLOCATE_SECURE_CONTEXT( ul_Secure_ډېری_اندازه )    v_پورټ_Allocate_Secure_Context( ul_Secure_ډېری_اندازه )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #تعریف_کړه پورټ_CLEAN_پورته_TCB( pxTCB )                           v_پورټ_Free_Secure_Context( ( uint32_t * ) pxTCB )
#د_که_پای /* configENABLE_TRUSTZONE */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
    #تعریف_کړه پورټ_IS_PRIVILEGED()      xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 *
 * The SVC handler checks that the SVC was raised from a system call and only
 * then it raises the privilege. If this is called from any other place,
 * the privilege is not raised.
 */
    #تعریف_کړه پورټ_RAISE_PRIVILEGE()    __asm متطاير ( "svc %0 \n" ::"i" ( پورټ_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
    #تعریف_کړه پورټ_RESET_PRIVILEGE()    vResetPrivilege()
#وإلا
    #تعریف_کړه پورټ_IS_PRIVILEGED()
    #تعریف_کړه پورټ_RAISE_PRIVILEGE()
    #تعریف_کړه پورټ_RESET_PRIVILEGE()
#د_که_پای /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    خارجي بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
    #تعریف_کړه پورټ_IS_TASK_PRIVILEGED()    x_پورټ_Is_Task_Privileged()

#د_که_پای /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#تعریف_کړه پورټ_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #إذا ( ( پورټ_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_شمېره_د_CORES == 1 ) )
        #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
    #وإلا
        #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    0
    #د_که_پای
#د_که_پای /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#إذا ( config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    ساكن پورټ_FORCE_INLINE uint32_t ul_پورټ_شمېر_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        أرجع ulReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 different priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای

    #إذا ( پورټ_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #تېروتنه ARMv8-M baseline implementations (such as Cortex-M23) افعل not support پورټ-optimised task selection.  Please سېټ config_USE_پورټ_OPTIMISED_TASK_SELECTION منزل 0 or leave it undefined.
    #د_که_پای

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31UL - ul_پورټ_شمېر_Leading_Zeros( ( uxReadyPriorities ) ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#إذا ( config_شمېره_د_CORES > 1 )
    تعريفنوع تعداد
    {
        e_Isr_قلف = 0,
        e_Task_قلف,
        e_قلف_شمېر
    } e_پورټ_RTOSLock;

    خارجي متطاير uint32_t ulCriticalNestings[ config_شمېره_د_CORES ];
    خارجي فراغ v_پورټ_Recursive_قلف( uint8_t ucCoreID,
                                    e_پورټ_RTOSLock e_قلف_عدد,
                                    بنسټ_Type_t uxAcquire );
    خارجي uint8_t uc_پورټ_Get_Core_ID( فراغ );
    خارجي فراغ v_مداخله_Core( uint8_t ucCoreID );

    #تعریف_کړه پورټ_GET_CORE_ID()                                  uc_پورټ_Get_Core_ID()

    #تعریف_کړه پورټ_GET_CRITICAL_NESTING_شمېر( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کړه پورټ_سېټ_CRITICAL_NESTING_شمېر( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کړه پورټ_INCREMENT_CRITICAL_NESTING_شمېر( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کړه پورټ_DECREMENT_CRITICAL_NESTING_شمېر( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #تعریف_کړه پورټ_MAX_CORE_شمېر                                 ( config_شمېره_د_CORES )

    #تعریف_کړه پورټ_YIELD_CORE( xCoreID )                          v_مداخله_Core( xCoreID )

    #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )                    v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Isr_قلف, pdFALSE )
    #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )                        v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Isr_قلف, pdTRUE )

    #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )                   v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Task_قلف, pdFALSE )
    #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )                       v_پورټ_Recursive_قلف( ( uint8_t ) xCoreID, e_Task_قلف, pdTRUE )

    #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( بنسټ_Type_t x_Write_Control_ثبتوونکی );
    #د_که_پای /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#د_که_پای

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACROCOMMON_H */
