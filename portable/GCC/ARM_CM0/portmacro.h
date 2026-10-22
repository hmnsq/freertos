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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

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

#నిర్వచితం_కాకపోతే configENABLE_MPU
    #దోషం configENABLE_MPU must be defined లోపల FreeRTOSConfig.h.  సమితి_2 configENABLE_MPU గమ్యం 1 గమ్యం enable the MPU or 0 గమ్యం disable the MPU.
#అయితే_ముగింపు /* configENABLE_MPU */

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
    రకనిర్వచనం uint16_t        TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY   ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t        TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY   ( TickType_t ) 0xffffffffUL

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
#నిర్వచించు పోర్టు_ARCH_NAME                      "Cortex-M0+"
#నిర్వచించు పోర్టు_దొంతర_GROWTH                   ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT                 8
#నిర్వచించు పోర్టు_NOP()
#నిర్వచించు పోర్టు_INLINE                         __inline
#నిర్వచితం_కాకపోతే పోర్టు_FORCE_INLINE
    #నిర్వచించు పోర్టు_FORCE_INLINE               అంతఃవరుస __attribute__( ( always_inline ) )
#అయితే_ముగింపు
#నిర్వచించు పోర్టు_DONT_DISCARD                   __attribute__( ( వాడిన ) )
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

#ఒకవేళ ( configENABLE_MPU == 1 )
    బాహ్య పునాది_Type_t xIsPrivileged( శూన్య ) /* __attribute__ (( naked )) */;
    బాహ్య శూన్య vResetPrivilege( శూన్య ) /* __attribute__ (( naked )) */;
#అయితే_ముగింపు /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#ఒకవేళ ( configENABLE_MPU == 1 )
    #నిర్వచించు పోర్టు_USING_MPU_WRAPPERS          1
    #నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు               ( 0x80000000UL )
#లేకపోతే
    #నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు               ( 0x0UL )
#అయితే_ముగింపు /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#నిర్వచితం_కాకపోతే configS_C_B_FLASH
    #నిర్వచించు configS_C_B_FLASH               ( 0x07UL )
#అయితే_ముగింపు

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#నిర్వచితం_కాకపోతే configS_C_B_SRAM
    #నిర్వచించు configS_C_B_SRAM                ( 0x07UL )
#అయితే_ముగింపు

/* MPU regions. */
#నిర్వచించు పోర్టు_PRIVILEGED_RAM_REGION           ( 7UL )
#నిర్వచించు పోర్టు_PRIVILEGED_FLASH_REGION         ( 6UL )
#నిర్వచించు పోర్టు_UNPRIVILEGED_FLASH_REGION       ( 5UL )
#నిర్వచించు పోర్టు_దొంతర_REGION                    ( 4UL )
#నిర్వచించు పోర్టు_మొదటి_CONFIGURABLE_REGION       ( 0UL )
#నిర్వచించు పోర్టు_చివరి_CONFIGURABLE_REGION        ( 3UL )
#నిర్వచించు పోర్టు_అంకె_CONFIGURABLE_REGIONS        ( 4UL )
#నిర్వచించు పోర్టు_మొత్తం_అంకె_REGIONS               ( పోర్టు_అంకె_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_256_B            ( 0x07UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_512_B            ( 0x08UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_1_KB             ( 0x09UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_2_KB             ( 0x0AUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_4_KB             ( 0x0BUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_8_KB             ( 0x0CUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_16_KB            ( 0x0DUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_32_KB            ( 0x0EUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_64_KB            ( 0x0FUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_128_KB           ( 0x10UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_256_KB           ( 0x11UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_512_KB           ( 0x12UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_1_MB             ( 0x13UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_2_MB             ( 0x14UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_4_MB             ( 0x15UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_8_MB             ( 0x16UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_16_MB            ( 0x17UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_32_MB            ( 0x18UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_64_MB            ( 0x19UL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_128_MB           ( 0x1AUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_256_MB           ( 0x1BUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_512_MB           ( 0x1CUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_1_GB             ( 0x1DUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_2_GB             ( 0x1EUL << 1UL )
#నిర్వచించు పోర్టు_MPU_REGION_కొలత_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#నిర్వచించు పోర్టు_MPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#నిర్వచించు పోర్టు_MPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#నిర్వచించు పోర్టు_MPU_REGION_సాధారణ_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#నిర్వచించు పోర్టు_MPU_REGION_సాధారణ_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#నిర్వచించు పోర్టు_MPU_REGION_సాధారణ_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#నిర్వచించు పోర్టు_MPU_REGION_సాధారణ_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#నిర్వచించు పోర్టు_MPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    రకనిర్వచనం నిర్మాణం MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
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
            uint32_t * pul_Task_దొంతర;
            uint32_t ul_Link_రిజిస్టరు_At_System_Call_నమోదు;
        } x_SYSTEM_CALL_దొంతర_INFO;

    #అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #నిర్వచించు CONTEXT_కొలత    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #నిర్వచించు పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #నిర్వచించు పోర్టు_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #నిర్వచించు పోర్టు_ACL_నమోదు_కొలత_బిట్లు             ( 32U )

    రకనిర్వచనం నిర్మాణం MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ పోర్టు_మొత్తం_అంకె_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_కొలత ];
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
 * @brief SVC numbers.
 */
#నిర్వచించు పోర్టు_SVC_ప్రారంభం_SCHEDULER            100
#నిర్వచించు పోర్టు_SVC_RAISE_PRIVILEGE            101
#నిర్వచించు పోర్టు_SVC_SYSTEM_CALL_EXIT           102
#నిర్వచించు పోర్టు_SVC_YIELD                      103
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
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()       ul_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )  v_Clear_అంతరాయం_ముసుగు( x )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                __asm అస్థిర ( " cpsid i " ::: "memory" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                 __asm అస్థిర ( " cpsie i " ::: "memory" )
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                    v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()                     v_పోర్టు_Exit_Critical()
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
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )
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

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
