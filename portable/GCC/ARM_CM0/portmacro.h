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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

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

#که_نه_تعریف_شوی configENABLE_MPU
    #تېروتنه configENABLE_MPU must be defined دننه FreeRTOSConfig.h.  سېټ_2 configENABLE_MPU منزل 1 منزل enable the MPU or 0 منزل disable the MPU.
#د_که_پای /* configENABLE_MPU */

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
    تعريفنوع uint16_t        TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY   ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t        TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY   ( TickType_t ) 0xffffffffUL

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
#تعریف_کړه پورټ_ARCH_NAME                      "Cortex-M0+"
#تعریف_کړه پورټ_ډېری_GROWTH                   ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT                 8
#تعریف_کړه پورټ_NOP()
#تعریف_کړه پورټ_INLINE                         __inline
#که_نه_تعریف_شوی پورټ_FORCE_INLINE
    #تعریف_کړه پورټ_FORCE_INLINE               مضمن __attribute__( ( always_inline ) )
#د_که_پای
#تعریف_کړه پورټ_DONT_DISCARD                   __attribute__( ( کارول_شوی ) )
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

#إذا ( configENABLE_MPU == 1 )
    خارجي بنسټ_Type_t xIsPrivileged( فراغ ) /* __attribute__ (( naked )) */;
    خارجي فراغ vResetPrivilege( فراغ ) /* __attribute__ (( naked )) */;
#د_که_پای /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#إذا ( configENABLE_MPU == 1 )
    #تعریف_کړه پورټ_USING_MPU_WRAPPERS          1
    #تعریف_کړه پورټ_PRIVILEGE_بټ               ( 0x80000000UL )
#وإلا
    #تعریف_کړه پورټ_PRIVILEGE_بټ               ( 0x0UL )
#د_که_پای /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#که_نه_تعریف_شوی configS_C_B_FLASH
    #تعریف_کړه configS_C_B_FLASH               ( 0x07UL )
#د_که_پای

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#که_نه_تعریف_شوی configS_C_B_SRAM
    #تعریف_کړه configS_C_B_SRAM                ( 0x07UL )
#د_که_پای

/* MPU regions. */
#تعریف_کړه پورټ_PRIVILEGED_RAM_REGION           ( 7UL )
#تعریف_کړه پورټ_PRIVILEGED_FLASH_REGION         ( 6UL )
#تعریف_کړه پورټ_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#تعریف_کړه پورټ_ډېری_REGION                    ( 4UL )
#تعریف_کړه پورټ_لومړی_CONFIGURABLE_REGION       ( 0UL )
#تعریف_کړه پورټ_وروستی_CONFIGURABLE_REGION        ( 3UL )
#تعریف_کړه پورټ_عدد_CONFIGURABLE_REGIONS        ( 4UL )
#تعریف_کړه پورټ_ټول_عدد_REGIONS               ( پورټ_عدد_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#تعریف_کړه پورټ_MPU_REGION_اندازه_256_B            ( 0x07UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_512_B            ( 0x08UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_1_KB             ( 0x09UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_2_KB             ( 0x0AUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_4_KB             ( 0x0BUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_8_KB             ( 0x0CUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_16_KB            ( 0x0DUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_32_KB            ( 0x0EUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_64_KB            ( 0x0FUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_128_KB           ( 0x10UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_256_KB           ( 0x11UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_512_KB           ( 0x12UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_1_MB             ( 0x13UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_2_MB             ( 0x14UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_4_MB             ( 0x15UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_8_MB             ( 0x16UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_16_MB            ( 0x17UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_32_MB            ( 0x18UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_64_MB            ( 0x19UL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_128_MB           ( 0x1AUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_256_MB           ( 0x1BUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_512_MB           ( 0x1CUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_1_GB             ( 0x1DUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_2_GB             ( 0x1EUL << 1UL )
#تعریف_کړه پورټ_MPU_REGION_اندازه_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کړه پورټ_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#تعریف_کړه پورټ_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#تعریف_کړه پورټ_MPU_REGION_نورمال_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#تعریف_کړه پورټ_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    تعريفنوع بنية MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
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
            uint32_t * pul_Task_ډېری;
            uint32_t ul_Link_ثبتوونکی_At_System_Call_ثبت;
        } x_SYSTEM_CALL_ډېری_INFO;

    #د_که_پای /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #تعریف_کړه CONTEXT_اندازه    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #تعریف_کړه پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #تعریف_کړه پورټ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #تعریف_کړه پورټ_ACL_ثبت_اندازه_بټونه             ( 32U )

    تعريفنوع بنية MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ پورټ_ټول_عدد_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_اندازه ];
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
 * @brief SVC numbers.
 */
#تعریف_کړه پورټ_SVC_پیل_SCHEDULER            100
#تعریف_کړه پورټ_SVC_RAISE_PRIVILEGE            101
#تعریف_کړه پورټ_SVC_SYSTEM_CALL_EXIT           102
#تعریف_کړه پورټ_SVC_YIELD                      103
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
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()       ul_سېټ_مداخله_ماسک()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )  v_Clear_مداخله_ماسک( x )
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                __asm متطاير ( " cpsid i " ::: "memory" )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                 __asm متطاير ( " cpsie i " ::: "memory" )
#تعریف_کړه پورټ_ENTER_CRITICAL()                    v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()                     v_پورټ_Exit_Critical()
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
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
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

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
