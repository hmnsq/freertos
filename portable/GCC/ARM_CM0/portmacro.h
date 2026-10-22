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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    বাহ্যিক "C" {
#endif
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

#ifndef configENABLE_MPU
    #error configENABLE_MPU must be defined in FreeRTOSConfig.h.  Set configENABLE_MPU to 1 to enable the MPU or 0 to disable the MPU.
#endif /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#define portCHAR          অক্ষর
#define portFLOAT         দশমিক
#define portDOUBLE        দ্বিগুণ
#define portLONG          long
#define portSHORT         short
#define port_স্তূপ_TYPE    uint32_t
#define portBASE_TYPE     long

প্রকারলেখ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারলেখ long             BaseType_t;
প্রকারলেখ unsigned long    UBaseType_t;

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারলেখ uint16_t        TickType_t;
    #define portMAX_DELAY   ( TickType_t ) 0xffff
#নতুবা_যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারলেখ uint32_t        TickType_t;
    #define portMAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#define portARCH_NAME                      "Cortex-M0+"
#define port_স্তূপ_GROWTH                   ( -1 )
#define portTICK_PERIOD_MS                 ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT                 8
#define portNOP()
#define portINLINE                         __inline
#ifndef portFORCE_INLINE
    #define portFORCE_INLINE               অন্তঃরেখ __attribute__( ( always_inline ) )
#endif
#define portDONT_DISCARD                   __attribute__( ( used ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
বাহ্যিক BaseType_t xPortIsInsideInterrupt( শূন্য );

বাহ্যিক শূন্য vPortYield( শূন্য ) /* PRIVILEGED_FUNCTION */;

বাহ্যিক শূন্য vPortEnterCritical( শূন্য ) /* PRIVILEGED_FUNCTION */;
বাহ্যিক শূন্য vPortExitCritical( শূন্য ) /* PRIVILEGED_FUNCTION */;

বাহ্যিক uint32_t ulSetInterruptMask( শূন্য ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
বাহ্যিক শূন্য vClearInterruptMask( uint32_t ulMask ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#যদি ( configENABLE_MPU == 1 )
    বাহ্যিক BaseType_t xIsPrivileged( শূন্য ) /* __attribute__ (( naked )) */;
    বাহ্যিক শূন্য vResetPrivilege( শূন্য ) /* __attribute__ (( naked )) */;
#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#যদি ( configENABLE_MPU == 1 )
    #define portUSING_MPU_WRAPPERS          1
    #define portPRIVILEGE_BIT               ( 0x80000000UL )
#অন্যথা
    #define portPRIVILEGE_BIT               ( 0x0UL )
#endif /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#ifndef configS_C_B_FLASH
    #define configS_C_B_FLASH               ( 0x07UL )
#endif

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#ifndef configS_C_B_SRAM
    #define configS_C_B_SRAM                ( 0x07UL )
#endif

/* MPU regions. */
#define portPRIVILEGED_RAM_REGION           ( 7UL )
#define portPRIVILEGED_FLASH_REGION         ( 6UL )
#define portUNPRIVILEGED_FLASH_REGION       ( 5UL )
#define port_স্তূপ_REGION                    ( 4UL )
#define portFIRST_CONFIGURABLE_REGION       ( 0UL )
#define portLAST_CONFIGURABLE_REGION        ( 3UL )
#define port_অঙ্ক_CONFIGURABLE_REGIONS        ( 4UL )
#define port_যোগ_অঙ্ক_REGIONS               ( port_অঙ্ক_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#define port_MPU_REGION_আকার_256_B            ( 0x07UL << 1UL )
#define port_MPU_REGION_আকার_512_B            ( 0x08UL << 1UL )
#define port_MPU_REGION_আকার_1_KB             ( 0x09UL << 1UL )
#define port_MPU_REGION_আকার_2_KB             ( 0x0AUL << 1UL )
#define port_MPU_REGION_আকার_4_KB             ( 0x0BUL << 1UL )
#define port_MPU_REGION_আকার_8_KB             ( 0x0CUL << 1UL )
#define port_MPU_REGION_আকার_16_KB            ( 0x0DUL << 1UL )
#define port_MPU_REGION_আকার_32_KB            ( 0x0EUL << 1UL )
#define port_MPU_REGION_আকার_64_KB            ( 0x0FUL << 1UL )
#define port_MPU_REGION_আকার_128_KB           ( 0x10UL << 1UL )
#define port_MPU_REGION_আকার_256_KB           ( 0x11UL << 1UL )
#define port_MPU_REGION_আকার_512_KB           ( 0x12UL << 1UL )
#define port_MPU_REGION_আকার_1_MB             ( 0x13UL << 1UL )
#define port_MPU_REGION_আকার_2_MB             ( 0x14UL << 1UL )
#define port_MPU_REGION_আকার_4_MB             ( 0x15UL << 1UL )
#define port_MPU_REGION_আকার_8_MB             ( 0x16UL << 1UL )
#define port_MPU_REGION_আকার_16_MB            ( 0x17UL << 1UL )
#define port_MPU_REGION_আকার_32_MB            ( 0x18UL << 1UL )
#define port_MPU_REGION_আকার_64_MB            ( 0x19UL << 1UL )
#define port_MPU_REGION_আকার_128_MB           ( 0x1AUL << 1UL )
#define port_MPU_REGION_আকার_256_MB           ( 0x1BUL << 1UL )
#define port_MPU_REGION_আকার_512_MB           ( 0x1CUL << 1UL )
#define port_MPU_REGION_আকার_1_GB             ( 0x1DUL << 1UL )
#define port_MPU_REGION_আকার_2_GB             ( 0x1EUL << 1UL )
#define port_MPU_REGION_আকার_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#define portMPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#define portMPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#define portMPU_REGION_NORMAL_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#define portMPU_REGION_NORMAL_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#define portMPU_REGION_NORMAL_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#define portMPU_REGION_NORMAL_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#define portMPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#define portMPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#define portMPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#define portMPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#define portMPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#define portMPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#define portMPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#যদি ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    প্রকারলেখ কাঠামো MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
    } MPURegionSettings_t;

    #যদি ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #ifndef config_SYSTEM_CALL_স্তূপ_আকার
            #error config_SYSTEM_CALL_স্তূপ_আকার must be defined to the desired আকার_2 of the system call স্তূপ in শব্দগুলি জন্য using MPU wrappers v2.
        #endif

        /**
         * @brief System call stack.
         */
        প্রকারলেখ কাঠামো SYSTEM_CALL_স্তূপ_INFO
        {
            uint32_t ul_System_Call_স্তূপ_বাফার[ config_SYSTEM_CALL_স্তূপ_আকার ];
            uint32_t * pul_System_Call_স্তূপ;
            uint32_t * pul_Task_স্তূপ;
            uint32_t ulLinkRegisterAtSystemCallEntry;
        } x_SYSTEM_CALL_স্তূপ_INFO;

    #endif /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #define CONTEXT_আকার    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #define port_স্তূপ_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #define portTASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #define port_ACL_ENTRY_আকার_BITS             ( 32U )

    প্রকারলেখ কাঠামো MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ port_যোগ_অঙ্ক_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_আকার ];
        uint32_t ulTaskFlags;

        #যদি ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_স্তূপ_INFO x_System_Call_স্তূপ_Info;
            #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_আকার / port_ACL_ENTRY_আকার_BITS ) + 1 ];
            #endif
        #endif
    } xMPU_SETTINGS;

#endif /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#define portSVC_START_SCHEDULER            100
#define portSVC_RAISE_PRIVILEGE            101
#define portSVC_SYSTEM_CALL_EXIT           102
#define portSVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#যদি ( configENABLE_MPU == 1 )
    #define portYIELD()               __asm অস্থির ( "svc %0" ::"i" ( portSVC_YIELD ) : "memory" )
    #define portYIELD_WITHIN_API()    vPortYield()
#অন্যথা
    #define portYIELD()               vPortYield()
    #define portYIELD_WITHIN_API()    vPortYield()
#endif

#define portNVIC_INT_CTRL_REG     ( *( ( অস্থির uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    করো                                                      \
    {                                                       \
        যদি( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        অন্যথা                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } যখন( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#define portSET_INTERRUPT_MASK_FROM_ISR()       ulSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )  vClearInterruptMask( x )
#define portDISABLE_INTERRUPTS()                __asm অস্থির ( " cpsid i " ::: "memory" )
#define portENABLE_INTERRUPTS()                 __asm অস্থির ( " cpsie i " ::: "memory" )
#define portENTER_CRITICAL()                    vPortEnterCritical()
#define portEXIT_CRITICAL()                     vPortExitCritical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    বাহ্যিক শূন্য vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )
/*-----------------------------------------------------------*/

#যদি ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #define portIS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #define portRAISE_PRIVILEGE()    __asm অস্থির ( "svc %0 \n" ::"i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #define portRESET_PRIVILEGE()    vResetPrivilege()

#অন্যথা

    #define portIS_PRIVILEGED()
    #define portRAISE_PRIVILEGE()
    #define portRESET_PRIVILEGE()

#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#যদি ( configENABLE_MPU == 1 )

    বাহ্যিক BaseType_t xPortIsTaskPrivileged( শূন্য );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #define portIS_TASK_PRIVILEGED()    xPortIsTaskPrivileged()

#endif /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#define portMEMORY_BARRIER()    __asm অস্থির ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
