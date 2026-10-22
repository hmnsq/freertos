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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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

#अगर_अघोषित configENABLE_MPU
    #त्रुटि configENABLE_MPU must be defined in FreeRTOSConfig.h.  Set configENABLE_MPU to 1 to enable the MPU or 0 to disable the MPU.
#पूर्ण_अगर /* configENABLE_MPU */

/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    uint32_t
#घोषणा portBASE_TYPE     दीर्घ

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार दीर्घ             BaseType_t;
प्रकार अचिन्हित दीर्घ    UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t        TickType_t;
    #घोषणा portMAX_DELAY   ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t        TickType_t;
    #घोषणा portMAX_DELAY   ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#घोषणा portARCH_NAME                      "Cortex-M0+"
#घोषणा port_ढेर_GROWTH                   ( -1 )
#घोषणा portTICK_PERIOD_MS                 ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT                 8
#घोषणा portNOP()
#घोषणा portINLINE                         __inline
#अगर_अघोषित portFORCE_INLINE
    #घोषणा portFORCE_INLINE               अंतरभूत __attribute__( ( always_inline ) )
#पूर्ण_अगर
#घोषणा portDONT_DISCARD                   __attribute__( ( used ) )
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
बाह्य BaseType_t xPortIsInsideInterrupt( व्योम );

बाह्य व्योम vPortYield( व्योम ) /* PRIVILEGED_FUNCTION */;

बाह्य व्योम vPortEnterCritical( व्योम ) /* PRIVILEGED_FUNCTION */;
बाह्य व्योम vPortExitCritical( व्योम ) /* PRIVILEGED_FUNCTION */;

बाह्य uint32_t ulSetInterruptMask( व्योम ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
बाह्य व्योम vClearInterruptMask( uint32_t ulMask ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#अगर ( configENABLE_MPU == 1 )
    बाह्य BaseType_t xIsPrivileged( व्योम ) /* __attribute__ (( naked )) */;
    बाह्य व्योम vResetPrivilege( व्योम ) /* __attribute__ (( naked )) */;
#पूर्ण_अगर /* configENABLE_MPU */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#अगर ( configENABLE_MPU == 1 )
    #घोषणा portUSING_MPU_WRAPPERS          1
    #घोषणा portPRIVILEGE_BIT               ( 0x80000000UL )
#अन्यथा
    #घोषणा portPRIVILEGE_BIT               ( 0x0UL )
#पूर्ण_अगर /* configENABLE_MPU */

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for flash region. */
#अगर_अघोषित configS_C_B_FLASH
    #घोषणा configS_C_B_FLASH               ( 0x07UL )
#पूर्ण_अगर

/* Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM region. */
#अगर_अघोषित configS_C_B_SRAM
    #घोषणा configS_C_B_SRAM                ( 0x07UL )
#पूर्ण_अगर

/* MPU regions. */
#घोषणा portPRIVILEGED_RAM_REGION           ( 7UL )
#घोषणा portPRIVILEGED_FLASH_REGION         ( 6UL )
#घोषणा portUNPRIVILEGED_FLASH_REGION       ( 5UL )
#घोषणा port_ढेर_REGION                    ( 4UL )
#घोषणा portFIRST_CONFIGURABLE_REGION       ( 0UL )
#घोषणा portLAST_CONFIGURABLE_REGION        ( 3UL )
#घोषणा port_अंक_CONFIGURABLE_REGIONS        ( 4UL )
#घोषणा port_योग_अंक_REGIONS               ( port_अंक_CONFIGURABLE_REGIONS + 1UL ) /* Plus one to make space for the stack region. */

/* MPU region sizes. This information is encoded in the SIZE bits of the MPU
 * Region Attribute and Size Register (RASR). */
#घोषणा port_MPU_REGION_आकार_256_B            ( 0x07UL << 1UL )
#घोषणा port_MPU_REGION_आकार_512_B            ( 0x08UL << 1UL )
#घोषणा port_MPU_REGION_आकार_1_KB             ( 0x09UL << 1UL )
#घोषणा port_MPU_REGION_आकार_2_KB             ( 0x0AUL << 1UL )
#घोषणा port_MPU_REGION_आकार_4_KB             ( 0x0BUL << 1UL )
#घोषणा port_MPU_REGION_आकार_8_KB             ( 0x0CUL << 1UL )
#घोषणा port_MPU_REGION_आकार_16_KB            ( 0x0DUL << 1UL )
#घोषणा port_MPU_REGION_आकार_32_KB            ( 0x0EUL << 1UL )
#घोषणा port_MPU_REGION_आकार_64_KB            ( 0x0FUL << 1UL )
#घोषणा port_MPU_REGION_आकार_128_KB           ( 0x10UL << 1UL )
#घोषणा port_MPU_REGION_आकार_256_KB           ( 0x11UL << 1UL )
#घोषणा port_MPU_REGION_आकार_512_KB           ( 0x12UL << 1UL )
#घोषणा port_MPU_REGION_आकार_1_MB             ( 0x13UL << 1UL )
#घोषणा port_MPU_REGION_आकार_2_MB             ( 0x14UL << 1UL )
#घोषणा port_MPU_REGION_आकार_4_MB             ( 0x15UL << 1UL )
#घोषणा port_MPU_REGION_आकार_8_MB             ( 0x16UL << 1UL )
#घोषणा port_MPU_REGION_आकार_16_MB            ( 0x17UL << 1UL )
#घोषणा port_MPU_REGION_आकार_32_MB            ( 0x18UL << 1UL )
#घोषणा port_MPU_REGION_आकार_64_MB            ( 0x19UL << 1UL )
#घोषणा port_MPU_REGION_आकार_128_MB           ( 0x1AUL << 1UL )
#घोषणा port_MPU_REGION_आकार_256_MB           ( 0x1BUL << 1UL )
#घोषणा port_MPU_REGION_आकार_512_MB           ( 0x1CUL << 1UL )
#घोषणा port_MPU_REGION_आकार_1_GB             ( 0x1DUL << 1UL )
#घोषणा port_MPU_REGION_आकार_2_GB             ( 0x1EUL << 1UL )
#घोषणा port_MPU_REGION_आकार_4_GB             ( 0x1FUL << 1UL )

/* MPU memory types. This information is encoded in the S ( Shareable), C
 * (Cacheable) and B (Bufferable) bits of the MPU Region Attribute and Size
 * Register (RASR). */
#घोषणा portMPU_REGION_STRONGLY_ORDERED_SHAREABLE   ( 0x0UL << 16UL ) /* S=NA, C=0, B=0. */
#घोषणा portMPU_REGION_DEVICE_SHAREABLE             ( 0x1UL << 16UL ) /* S=NA, C=0, B=1. */
#घोषणा portMPU_REGION_NORMAL_OIWTNOWA_NONSHARED    ( 0x2UL << 16UL ) /* S=0, C=1, B=0. */
#घोषणा portMPU_REGION_NORMAL_OIWTNOWA_SHARED       ( 0x6UL << 16UL ) /* S=1, C=1, B=0. */
#घोषणा portMPU_REGION_NORMAL_OIWBNOWA_NONSHARED    ( 0x3UL << 16UL ) /* S=0, C=1, B=1.*/
#घोषणा portMPU_REGION_NORMAL_OIWBNOWA_SHARED       ( 0x7UL << 16UL ) /* S=1, C=1, B=1.*/

/* MPU access permissions. This information is encoded in the AP and XN bits of
 * the MPU Region Attribute and Size Register (RASR). */
#घोषणा portMPU_REGION_PRIV_NA_UNPRIV_NA            ( 0x0UL << 24UL )
#घोषणा portMPU_REGION_PRIV_RW_UNPRIV_NA            ( 0x1UL << 24UL )
#घोषणा portMPU_REGION_PRIV_RW_UNPRIV_RO            ( 0x2UL << 24UL )
#घोषणा portMPU_REGION_PRIV_RW_UNPRIV_RW            ( 0x3UL << 24UL )
#घोषणा portMPU_REGION_PRIV_RO_UNPRIV_NA            ( 0x5UL << 24UL )
#घोषणा portMPU_REGION_PRIV_RO_UNPRIV_RO            ( 0x6UL << 24UL )
#घोषणा portMPU_REGION_EXECUTE_NEVER                ( 0x1UL << 28UL )

#अगर ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    प्रकार काष्ठा MPURegionSettings
    {
        uint32_t ulRBAR; /**< MPU Region Base Address Register (RBAR) for the region. */
        uint32_t ulRASR; /**< MPU Region Attribute and Size Register (RASR) for the region. */
    } MPURegionSettings_t;

    #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #अगर_अघोषित config_SYSTEM_CALL_ढेर_आकार
            #त्रुटि config_SYSTEM_CALL_ढेर_आकार must be defined to the desired आकार of the प्रणाली call ढेर in शब्दगण क्रम using MPU wrappers v2.
        #पूर्ण_अगर

        /**
         * @brief System call stack.
         */
        प्रकार काष्ठा SYSTEM_CALL_ढेर_INFO
        {
            uint32_t ul_System_Call_ढेर_बफर[ config_SYSTEM_CALL_ढेर_आकार ];
            uint32_t * pul_System_Call_ढेर;
            uint32_t * pul_Task_ढेर;
            uint32_t ulLinkRegisterAtSystemCallEntry;
        } x_SYSTEM_CALL_ढेर_INFO;

    #पूर्ण_अगर /* configUSE_MPU_WRAPPERS_V1 == 0 */

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
    #घोषणा CONTEXT_आकार    20

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #घोषणा port_ढेर_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #घोषणा portTASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #घोषणा port_ACL_ENTRY_आकार_BITS             ( 32U )

    प्रकार काष्ठा MPU_SETTINGS
    {
        MPURegionSettings_t xRegionsSettings[ port_योग_अंक_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ CONTEXT_आकार ];
        uint32_t ulTaskFlags;

        #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_ढेर_INFO x_System_Call_ढेर_Info;
            #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार / port_ACL_ENTRY_आकार_BITS ) + 1 ];
            #पूर्ण_अगर
        #पूर्ण_अगर
    } xMPU_SETTINGS;

#पूर्ण_अगर /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
#घोषणा portSVC_START_SCHEDULER            100
#घोषणा portSVC_RAISE_PRIVILEGE            101
#घोषणा portSVC_SYSTEM_CALL_EXIT           102
#घोषणा portSVC_YIELD                      103
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#अगर ( configENABLE_MPU == 1 )
    #घोषणा portYIELD()               __asm अस्थिर ( "svc %0" ::"i" ( portSVC_YIELD ) : "memory" )
    #घोषणा portYIELD_WITHIN_API()    vPortYield()
#अन्यथा
    #घोषणा portYIELD()               vPortYield()
    #घोषणा portYIELD_WITHIN_API()    vPortYield()
#पूर्ण_अगर

#घोषणा portNVIC_INT_CTRL_REG     ( *( ( अस्थिर uint32_t * ) 0xe000ed04 ) )
#घोषणा portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#घोषणा portEND_SWITCHING_ISR( xSwitchRequired )            \
    करो                                                      \
    {                                                       \
        अगर( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } जबतक( 0 )
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()       ulSetInterruptMask()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )  vClearInterruptMask( x )
#घोषणा portDISABLE_INTERRUPTS()                __asm अस्थिर ( " cpsid i " ::: "memory" )
#घोषणा portENABLE_INTERRUPTS()                 __asm अस्थिर ( " cpsie i " ::: "memory" )
#घोषणा portENTER_CRITICAL()                    vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()                     vPortExitCritical()
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#अगर_अघोषित portSUPPRESS_TICKS_AND_SLEEP
    बाह्य व्योम vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #घोषणा portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org website.
 */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the processor is privileged.
     *
     * @return 1 if the processor is already privileged, 0 otherwise.
     */
    #घोषणा portIS_PRIVILEGED()      xIsPrivileged()

    /**
     * @brief Raise an SVC request to raise privilege.
     *
     * The SVC handler checks that the SVC was raised from a system call and only
     * then it raises the privilege. If this is called from any other place,
     * the privilege is not raised.
     */
    #घोषणा portRAISE_PRIVILEGE()    __asm अस्थिर ( "svc %0 \n" ::"i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );

    /**
     * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
     * register.
     */
    #घोषणा portRESET_PRIVILEGE()    vResetPrivilege()

#अन्यथा

    #घोषणा portIS_PRIVILEGED()
    #घोषणा portRAISE_PRIVILEGE()
    #घोषणा portRESET_PRIVILEGE()

#पूर्ण_अगर /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    बाह्य BaseType_t xPortIsTaskPrivileged( व्योम );

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #घोषणा portIS_TASK_PRIVILEGED()    xPortIsTaskPrivileged()

#पूर्ण_अगर /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Barriers.
 */
#घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
