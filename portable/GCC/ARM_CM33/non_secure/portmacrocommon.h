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

#اگر_تعریف_نشده PORTMACROCOMMON_H
#تعریف_کن PORTMACROCOMMON_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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

#اگر_تعریف_نشده configENABLE_FPU
    #خطا configENABLE_FPU must be defined درون FreeRTOSConfig.h.  مجموعه_2 configENABLE_FPU مقصد 1 مقصد enable the FPU or 0 مقصد disable the FPU.
#پایان_اگر /* configENABLE_FPU */

#اگر_تعریف_نشده configENABLE_MPU
    #خطا configENABLE_MPU must be defined درون FreeRTOSConfig.h.  مجموعه_2 configENABLE_MPU مقصد 1 مقصد enable the MPU or 0 مقصد disable the MPU.
#پایان_اگر /* configENABLE_MPU */

#اگر_تعریف_نشده configENABLE_TRUSTZONE
    #خطا configENABLE_TRUSTZONE must be defined درون FreeRTOSConfig.h.  مجموعه_2 configENABLE_TRUSTZONE مقصد 1 مقصد enable TrustZone or 0 مقصد disable TrustZone.
#پایان_اگر /* configENABLE_TRUSTZONE */

#إذا ( config_عدد_از_CORES > 1 )
    #إذا ( پورت_VALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #خطا "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #پایان_اگر /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #اگر_تعریف_نشده config_CORE_ID_ثبات
        #خطا "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #پایان_اگر /* ifndef configCORE_ID_REGISTER */

    #اگر_تعریف_نشده configWAKE_SECONDARY_CORES
        #خطا "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #پایان_اگر /* ifndef configWAKE_SECONDARY_CORES */
#پایان_اگر /* #if ( configNUMBER_OF_CORES > 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#تعریف_کن پورت_پشته_GROWTH                   ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT                 8
#تعریف_کن پورت_NOP()
#تعریف_کن پورت_INLINE                         __inline
#اگر_تعریف_نشده پورت_FORCE_INLINE
    #تعریف_کن پورت_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#پایان_اگر
#تعریف_کن پورت_HAS_پشته_سرریز_CHECKING    1
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
خارجي پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ );

خارجي فراغ v_پورت_Yield( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي فراغ v_پورت_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;
خارجي فراغ v_پورت_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */;

خارجي uint32_t ul_مجموعه_وقفه_ماسک( فراغ ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
خارجي فراغ v_Clear_وقفه_ماسک( uint32_t ul_ماسک ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#إذا ( configENABLE_TRUSTZONE == 1 )
    خارجي فراغ v_پورت_Allocate_Secure_Context( uint32_t ul_Secure_پشته_اندازه ); /* __attribute__ (( naked )) */
    خارجي فراغ v_پورت_Free_Secure_Context( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#پایان_اگر /* configENABLE_TRUSTZONE */

#إذا ( configENABLE_MPU == 1 )
    خارجي پایه_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#پایان_اگر /* configENABLE_MPU */

#إذا ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    فراغ v_Application_Generate_Task_Random_Pac_کلید( uint32_t * pul_Task_Pac_کلید );

#پایان_اگر /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کن پورت_USING_MPU_WRAPPERS    1
    #تعریف_کن پورت_PRIVILEGE_بیت         ( 0x80000000UL )
#وإلا
    #تعریف_کن پورت_PRIVILEGE_بیت         ( 0x0UL )
#پایان_اگر /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#اگر_تعریف_نشده config_مجموع_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #تعریف_کن config_مجموع_MPU_REGIONS    ( 8UL )
#پایان_اگر

/* MPU regions. */
#تعریف_کن پورت_PRIVILEGED_FLASH_REGION                   ( 0UL )
#تعریف_کن پورت_UNPRIVILEGED_FLASH_REGION                 ( 1UL )
#تعریف_کن پورت_UNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#تعریف_کن پورت_PRIVILEGED_RAM_REGION                     ( 3UL )
#تعریف_کن پورت_پشته_REGION                              ( 4UL )
#تعریف_کن پورت_اولی_CONFIGURABLE_REGION                 ( 5UL )
#تعریف_کن پورت_آخرین_CONFIGURABLE_REGION                  ( config_مجموع_MPU_REGIONS - 1UL )
#تعریف_کن پورت_رقم_CONFIGURABLE_REGIONS                  ( ( پورت_آخرین_CONFIGURABLE_REGION - پورت_اولی_CONFIGURABLE_REGION ) + 1 )
#تعریف_کن پورت_مجموع_رقم_REGIONS                         ( پورت_رقم_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#تعریف_کن پورت_MPU_DEVICE_حافظه_n_Gn_Rn_E                  ( 0x00 )       /* 0000 0000 */
#تعریف_کن پورت_MPU_DEVICE_حافظه_n_Gn_RE                   ( 0x04 )       /* 0000 0100 */
#تعریف_کن پورت_MPU_DEVICE_حافظه_n_GRE                    ( 0x08 )       /* 0000 1000 */
#تعریف_کن پورت_MPU_DEVICE_حافظه_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#تعریف_کن پورت_MPU_نرمال_حافظه_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#تعریف_کن پورت_MPU_نرمال_حافظه_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#تعریف_کن پورت_MPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#تعریف_کن پورت_MPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#تعریف_کن پورت_MPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#تعریف_کن پورت_MPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#تعریف_کن پورت_MPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#تعریف_کن پورت_MPU_REGION_EXECUTE_NEVER                  ( 1UL )
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

        #اگر_تعریف_نشده config_SYSTEM_CALL_پشته_اندازه
            #خطا config_SYSTEM_CALL_پشته_اندازه must be defined مقصد the desired اندازه از the system call پشته درون واژگان لكل using MPU wrappers v2.
        #پایان_اگر

        /**
         * @brief System call stack.
         */
        تعريفنوع بنية SYSTEM_CALL_پشته_INFO
        {
            uint32_t ul_System_Call_پشته_میانگیر[ config_SYSTEM_CALL_پشته_اندازه ];
            uint32_t * pul_System_Call_پشته;
            uint32_t * pul_System_Call_پشته_حد;
            uint32_t * pul_Task_پشته;
            uint32_t ul_Link_ثبات_At_System_Call_مدخل;
            uint32_t ul_پشته_حد_ثبات_At_System_Call_مدخل;
        } x_SYSTEM_CALL_پشته_INFO;

    #پایان_اگر /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
            #تعریف_کن MAX_CONTEXT_اندازه    59

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
            #تعریف_کن MAX_CONTEXT_اندازه    55

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
            #تعریف_کن MAX_CONTEXT_اندازه    58

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
            #تعریف_کن MAX_CONTEXT_اندازه    54

        #پایان_اگر /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

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
            #تعریف_کن MAX_CONTEXT_اندازه    26

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
            #تعریف_کن MAX_CONTEXT_اندازه    22

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
            #تعریف_کن MAX_CONTEXT_اندازه    25

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
            #تعریف_کن MAX_CONTEXT_اندازه    21

        #پایان_اگر /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #پایان_اگر /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کن پورت_پشته_قاب_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کن پورت_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کن پورت_ACL_مدخل_اندازه_بیتها             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ پورت_مجموع_رقم_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_اندازه ];
        uint32_t ulTaskFlags;

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_پشته_INFO x_System_Call_پشته_Info;
            #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورت_ACL_مدخل_اندازه_بیتها ) + 1 ];
            #پایان_اگر
        #پایان_اگر
    } xMPU_SETTINGS;

#پایان_اگر /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#إذا ( configASSERT_DEFINED == 1 )
    #إذا ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 1 )
        فراغ v_پورت_Validate_وقفه_اولویت( فراغ );
        #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    v_پورت_Validate_وقفه_اولویت()
    #پایان_اگر
#پایان_اگر

/**
 * @brief SVC numbers.
 */
#تعریف_کن پورت_SVC_ALLOCATE_SECURE_CONTEXT    100
#تعریف_کن پورت_SVC_FREE_SECURE_CONTEXT        101
#تعریف_کن پورت_SVC_شروع_SCHEDULER            102
#تعریف_کن پورت_SVC_RAISE_PRIVILEGE            103
#تعریف_کن پورت_SVC_SYSTEM_CALL_EXIT           104
#تعریف_کن پورت_SVC_YIELD                      105
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کن پورت_YIELD()               __asm متطاير ( "svc %0" ::"i" ( پورت_SVC_YIELD ) : "memory" )
    #تعریف_کن پورت_YIELD_WITHIN_API()    v_پورت_Yield()
#وإلا
    #تعریف_کن پورت_YIELD()               v_پورت_Yield()
    #تعریف_کن پورت_YIELD_WITHIN_API()    v_پورت_Yield()
#پایان_اگر

#تعریف_کن پورت_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کن پورت_NVIC_PENDSVSET_بیت    ( 1UL << 28UL )
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */

#تعریف_کن پورت_مجموعه_وقفه_ماسک()                  ul_مجموعه_وقفه_ماسک()
#تعریف_کن پورت_CLEAR_وقفه_ماسک( x )             v_Clear_وقفه_ماسک( x )
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ul_مجموعه_وقفه_ماسک()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_Clear_وقفه_ماسک( x )

#إذا ( config_عدد_از_CORES == 1 )
    #تعریف_کن پورت_ENTER_CRITICAL()                      v_پورت_Enter_Critical()
    #تعریف_کن پورت_EXIT_CRITICAL()                       v_پورت_Exit_Critical()
#وإلا /* ( configNUMBER_OF_CORES == 1 ) */
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_وقفه_وضعیت );

    #تعریف_کن پورت_ENTER_CRITICAL()                      vTaskEnterCritical()
    #تعریف_کن پورت_EXIT_CRITICAL()                       vTaskExitCritical()
    #تعریف_کن پورت_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #تعریف_کن پورت_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#پایان_اگر /* if ( configNUMBER_OF_CORES != 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#اگر_تعریف_نشده پورت_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان );
    #تعریف_کن پورت_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_زمان )    v_پورت_Suppress_Ticks_And_Sleep( x_Expected_Idle_زمان )
#پایان_اگر
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
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
    #تعریف_کن پورت_ALLOCATE_SECURE_CONTEXT( ul_Secure_پشته_اندازه )    v_پورت_Allocate_Secure_Context( ul_Secure_پشته_اندازه )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #تعریف_کن پورت_CLEAN_به_بالا_TCB( pxTCB )                           v_پورت_Free_Secure_Context( ( uint32_t * ) pxTCB )
#پایان_اگر /* configENABLE_TRUSTZONE */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
    #تعریف_کن پورت_IS_PRIVILEGED()      xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 *
 * The SVC handler checks that the SVC was raised from a system call and only
 * then it raises the privilege. If this is called from any other place,
 * the privilege is not raised.
 */
    #تعریف_کن پورت_RAISE_PRIVILEGE()    __asm متطاير ( "svc %0 \n" ::"i" ( پورت_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
    #تعریف_کن پورت_RESET_PRIVILEGE()    vResetPrivilege()
#وإلا
    #تعریف_کن پورت_IS_PRIVILEGED()
    #تعریف_کن پورت_RAISE_PRIVILEGE()
    #تعریف_کن پورت_RESET_PRIVILEGE()
#پایان_اگر /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    خارجي پایه_Type_t x_پورت_Is_Task_Privileged( فراغ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
    #تعریف_کن پورت_IS_TASK_PRIVILEGED()    x_پورت_Is_Task_Privileged()

#پایان_اگر /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #إذا ( ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 1 ) && ( config_عدد_از_CORES == 1 ) )
        #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
    #وإلا
        #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    0
    #پایان_اگر
#پایان_اگر /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#إذا ( config_USE_پورت_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    ساكن پورت_FORCE_INLINE uint32_t ul_پورت_شمار_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm متطاير ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        أرجع ulReturn;
    }

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 different priorities as tasks that share a اولویت will time برش.
    #پایان_اگر

    #إذا ( پورت_HAS_ARMV8_M_MAIN_EXTENSION == 0 )
        #خطا ARMv8-M baseline implementations (such as Cortex-M23) افعل not support پورت-optimised task selection.  Please مجموعه config_USE_پورت_OPTIMISED_TASK_SELECTION مقصد 0 or leave it undefined.
    #پایان_اگر

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31UL - ul_پورت_شمار_Leading_Zeros( ( uxReadyPriorities ) ) )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#إذا ( config_عدد_از_CORES > 1 )
    تعريفنوع تعداد
    {
        e_Isr_قفل = 0,
        e_Task_قفل,
        e_قفل_شمار
    } e_پورت_RTOSLock;

    خارجي متطاير uint32_t ulCriticalNestings[ config_عدد_از_CORES ];
    خارجي فراغ v_پورت_Recursive_قفل( uint8_t ucCoreID,
                                    e_پورت_RTOSLock e_قفل_رقم,
                                    پایه_Type_t uxAcquire );
    خارجي uint8_t uc_پورت_Get_Core_ID( فراغ );
    خارجي فراغ v_وقفه_Core( uint8_t ucCoreID );

    #تعریف_کن پورت_GET_CORE_ID()                                  uc_پورت_Get_Core_ID()

    #تعریف_کن پورت_GET_CRITICAL_NESTING_شمار( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #تعریف_کن پورت_مجموعه_CRITICAL_NESTING_شمار( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #تعریف_کن پورت_INCREMENT_CRITICAL_NESTING_شمار( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #تعریف_کن پورت_DECREMENT_CRITICAL_NESTING_شمار( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #تعریف_کن پورت_MAX_CORE_شمار                                 ( config_عدد_از_CORES )

    #تعریف_کن پورت_YIELD_CORE( xCoreID )                          v_وقفه_Core( xCoreID )

    #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )                    v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Isr_قفل, pdFALSE )
    #تعریف_کن پورت_GET_ISR_قفل( xCoreID )                        v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Isr_قفل, pdTRUE )

    #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )                   v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Task_قفل, pdFALSE )
    #تعریف_کن پورت_GET_TASK_قفل( xCoreID )                       v_پورت_Recursive_قفل( ( uint8_t ) xCoreID, e_Task_قفل, pdTRUE )

    #إذا ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( پایه_Type_t x_Write_Control_ثبات );
    #پایان_اگر /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#پایان_اگر

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACROCOMMON_H */
