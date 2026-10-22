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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

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

#यदि_अपरिभाषितम् configENABLE_MPU
    #दोषः configENABLE_MPU must be defined अन्तर् FreeRTOSConfig.h.  समुच्चयः_2 configENABLE_MPU गन्तव्यम् 1 गन्तव्यम् enable the MPU or 0 गन्तव्यम् disable the MPU.
#यदि_अन्तः /* configENABLE_MPU */

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
    प्रकारनिर्देश uint16_t        TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY   ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t        TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY   ( TickType_t ) 0xffffffffUL

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
#परिभाषय पत्तनम्_ARCH_NAME                      "Cortex-M0+"
#परिभाषय पत्तनम्_राशिः_GROWTH                   ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT                 8
#परिभाषय पत्तनम्_NOP()
#परिभाषय पत्तनम्_INLINE                         __inline
#यदि_अपरिभाषितम् पत्तनम्_FORCE_INLINE
    #परिभाषय पत्तनम्_FORCE_INLINE               अन्तःस्थ __attribute__( ( always_inline ) )
#यदि_अन्तः
#परिभाषय पत्तनम्_DONT_DISCARD                   __attribute__( ( प्रयुक्तम् ) )
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

#यदि ( configENABLE_MPU == 1 )
    बाह्य आधारः_Type_t xIsPrivileged( शून्य ) /* __attribute__ (( naked )) */;
    बाह्य शून्य vResetPrivilege( शून्य ) /* __attribute__ (( naked )) */;
#यदि_अन्तः /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#यदि ( configENABLE_MPU == 1 )
    #परिभाषय पत्तनम्_USING_MPU_WRAPPERS          1
    #परिभाषय पत्तनम्_PRIVILEGE_BIT               ( 0x80000000UL )
#अन्यथा
    #परिभाषय पत्तनम्_PRIVILEGE_BIT               ( 0x0UL )
#यदि_अन्तः /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#यदि_अपरिभाषितम् configS_C_B_FLASH
    #परिभाषय configS_C_B_FLASH               ( 0x07UL )
#यदि_अन्तः

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#यदि_अपरिभाषितम् configS_C_B_SRAM
    #परिभाषय configS_C_B_SRAM                ( 0x07UL )
#यदि_अन्तः

/* MPU regions. */
#परिभाषय पत्तनम्_PRIVILEGED_RAM_REGION           ( 7UL )
#परिभाषय पत्तनम्_PRIVILEGED_FLASH_REGION         ( 6UL )
#परिभाषय पत्तनम्_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#परिभाषय पत्तनम्_राशिः_REGION                    ( 4UL )
#परिभाषय पत्तनम्_FIRST_CONFIGURABLE_REGION       ( 0UL )
#परिभाषय पत्तनम्_चरमः_CONFIGURABLE_REGION        ( 3UL )
#परिभाषय पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS        ( 4UL )
#परिभाषय पत्तनम्_योग_अङ्कः_REGIONS               ( पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#परिभाषय पत्तनम्_MPU_REGION_आकार_256_B            ( 0x07UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_512_B            ( 0x08UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_1_KB             ( 0x09UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_2_KB             ( 0x0AUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_4_KB             ( 0x0BUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_8_KB             ( 0x0CUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_16_KB            ( 0x0DUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_32_KB            ( 0x0EUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_64_KB            ( 0x0FUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_128_KB           ( 0x10UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_256_KB           ( 0x11UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_512_KB           ( 0x12UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_1_MB             ( 0x13UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_2_MB             ( 0x14UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_4_MB             ( 0x15UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_8_MB             ( 0x16UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_16_MB            ( 0x17UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_32_MB            ( 0x18UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_64_MB            ( 0x19UL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_128_MB           ( 0x1AUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_256_MB           ( 0x1BUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_512_MB           ( 0x1CUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_1_GB             ( 0x1DUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_2_GB             ( 0x1EUL << 1UL )
#परिभाषय पत्तनम्_MPU_REGION_आकार_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#परिभाषय पत्तनम्_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#परिभाषय पत्तनम्_MPU_REGION_प्रसामान्यम्_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#परिभाषय पत्तनम्_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#परिभाषय पत्तनम्_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    प्रकारनिर्देश संरचना MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
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
            uint32_t * pul_Task_राशिः;
            uint32_t ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;
        } x_SYSTEM_CALL_राशिः_INFO;

    #यदि_अन्तः /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #परिभाषय CONTEXT_आकार    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #परिभाषय पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #परिभाषय पत्तनम्_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #परिभाषय पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः             ( 32U )

    प्रकारनिर्देश संरचना MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ पत्तनम्_योग_अङ्कः_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_आकार ];
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
 * @brief SVC numbers.
 */
#परिभाषय पत्तनम्_SVC_START_SCHEDULER            100
#परिभाषय पत्तनम्_SVC_RAISE_PRIVILEGE            101
#परिभाषय पत्तनम्_SVC_SYSTEM_CALL_EXIT           102
#परिभाषय पत्तनम्_SVC_YIELD                      103
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
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()       ul_समुच्चयः_व्यवधानम्_आवरणम्()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )  v_Clear_व्यवधानम्_आवरणम्( x )
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                __asm चञ्चल ( " cpsid i " ::: "memory" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                 __asm चञ्चल ( " cpsie i " ::: "memory" )
#परिभाषय पत्तनम्_ENTER_CRITICAL()                    v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()                     v_पत्तनम्_Exit_Critical()
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
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
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

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
