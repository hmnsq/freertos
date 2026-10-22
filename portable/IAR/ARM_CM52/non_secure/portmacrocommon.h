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

#अगर_अघोषित PORTMACROCOMMON_H
#घोषणा PORTMACROCOMMON_H

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

#अगर_अघोषित configENABLE_FPU
    #त्रुटि configENABLE_FPU must be defined in FreeRTOSConfig.h.  Set configENABLE_FPU to 1 to enable the FPU or 0 to disable the FPU.
#पूर्ण_अगर /* configENABLE_FPU */

#अगर_अघोषित configENABLE_MPU
    #त्रुटि configENABLE_MPU must be defined in FreeRTOSConfig.h.  Set configENABLE_MPU to 1 to enable the MPU or 0 to disable the MPU.
#पूर्ण_अगर /* configENABLE_MPU */

#अगर_अघोषित configENABLE_TRUSTZONE
    #त्रुटि configENABLE_TRUSTZONE must be defined in FreeRTOSConfig.h.  Set configENABLE_TRUSTZONE to 1 to enable TrustZone or 0 to disable TrustZone.
#पूर्ण_अगर /* configENABLE_TRUSTZONE */

#अगर ( config_संख्या_OF_CORES > 1 )
    #अगर ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #त्रुटि "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #पूर्ण_अगर /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #अगर_अघोषित configCORE_ID_REGISTER
        #त्रुटि "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #पूर्ण_अगर /* ifndef configCORE_ID_REGISTER */

    #अगर_अघोषित configWAKE_SECONDARY_CORES
        #त्रुटि "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #पूर्ण_अगर /* ifndef configWAKE_SECONDARY_CORES */
#पूर्ण_अगर /* #if ( configNUMBER_OF_CORES > 1 ) */
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
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

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
#घोषणा port_ढेर_GROWTH                   ( -1 )
#घोषणा portTICK_PERIOD_MS                 ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT                 8
#घोषणा portNOP()
#घोषणा portINLINE                         __inline
#अगर_अघोषित portFORCE_INLINE
    #घोषणा portFORCE_INLINE               अंतरभूत __attribute__( ( always_inline ) )
#पूर्ण_अगर
#घोषणा port_HAS_ढेर_OVERFLOW_CHECKING    1
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

#अगर ( configENABLE_TRUSTZONE == 1 )
    बाह्य व्योम vPortAllocateSecureContext( uint32_t ul_Secure_ढेर_आकार ); /* __attribute__ (( naked )) */
    बाह्य व्योम vPortFreeSecureContext( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#पूर्ण_अगर /* configENABLE_TRUSTZONE */

#अगर ( configENABLE_MPU == 1 )
    बाह्य BaseType_t xIsPrivileged( व्योम ) /* __attribute__ (( naked )) */;
    बाह्य व्योम vResetPrivilege( व्योम ) /* __attribute__ (( naked )) */;
#पूर्ण_अगर /* configENABLE_MPU */

#अगर ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    व्योम v_Application_Generate_Task_Random_Pac_कुंजी( uint32_t * pul_Task_Pac_कुंजी );

#पूर्ण_अगर /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#अगर ( configENABLE_MPU == 1 )
    #घोषणा portUSING_MPU_WRAPPERS    1
    #घोषणा portPRIVILEGE_BIT         ( 0x80000000UL )
#अन्यथा
    #घोषणा portPRIVILEGE_BIT         ( 0x0UL )
#पूर्ण_अगर /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#अगर_अघोषित config_योग_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #घोषणा config_योग_MPU_REGIONS    ( 8UL )
#पूर्ण_अगर

/* MPU regions. */
#घोषणा portPRIVILEGED_FLASH_REGION                   ( 0UL )
#घोषणा portUNPRIVILEGED_FLASH_REGION                 ( 1UL )
#घोषणा portUNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#घोषणा portPRIVILEGED_RAM_REGION                     ( 3UL )
#घोषणा port_ढेर_REGION                              ( 4UL )
#घोषणा portFIRST_CONFIGURABLE_REGION                 ( 5UL )
#घोषणा portLAST_CONFIGURABLE_REGION                  ( config_योग_MPU_REGIONS - 1UL )
#घोषणा port_अंक_CONFIGURABLE_REGIONS                  ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#घोषणा port_योग_अंक_REGIONS                         ( port_अंक_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#घोषणा portMPU_DEVICE_MEMORY_nGnRnE                  ( 0x00 )       /* 0000 0000 */
#घोषणा portMPU_DEVICE_MEMORY_nGnRE                   ( 0x04 )       /* 0000 0100 */
#घोषणा portMPU_DEVICE_MEMORY_nGRE                    ( 0x08 )       /* 0000 1000 */
#घोषणा portMPU_DEVICE_MEMORY_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#घोषणा portMPU_NORMAL_MEMORY_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#घोषणा portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#घोषणा portMPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#घोषणा portMPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#घोषणा portMPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#घोषणा portMPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#घोषणा portMPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#घोषणा portMPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#घोषणा portMPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#घोषणा portMPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    प्रकार काष्ठा MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
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
            uint32_t * pul_System_Call_ढेर_Limit;
            uint32_t * pul_Task_ढेर;
            uint32_t ulLinkRegisterAtSystemCallEntry;
            uint32_t ul_ढेर_Limit_Register_At_System_Call_Entry;
        } x_SYSTEM_CALL_ढेर_INFO;

    #पूर्ण_अगर /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #अगर ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #अगर ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #घोषणा MAX_CONTEXT_आकार    59

        #या_अगर ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #घोषणा MAX_CONTEXT_आकार    55

        #या_अगर ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #घोषणा MAX_CONTEXT_आकार    58

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
            #घोषणा MAX_CONTEXT_आकार    54

        #पूर्ण_अगर /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #अन्यथा /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #अगर ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #घोषणा MAX_CONTEXT_आकार    26

        #या_अगर ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #घोषणा MAX_CONTEXT_आकार    22

        #या_अगर ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #घोषणा MAX_CONTEXT_आकार    25

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
            #घोषणा MAX_CONTEXT_आकार    21

        #पूर्ण_अगर /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #पूर्ण_अगर /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #घोषणा port_ढेर_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #घोषणा portTASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #घोषणा port_ACL_ENTRY_आकार_BITS             ( 32U )

    प्रकार काष्ठा MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ port_योग_अंक_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_आकार ];
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
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#अगर ( configASSERT_DEFINED == 1 )
    #अगर ( portHAS_ARMV8M_MAIN_EXTENSION == 1 )
        व्योम vPortValidateInterruptPriority( व्योम );
        #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
    #पूर्ण_अगर
#पूर्ण_अगर

/**
 * @brief SVC numbers.
 */
#घोषणा portSVC_ALLOCATE_SECURE_CONTEXT    100
#घोषणा portSVC_FREE_SECURE_CONTEXT        101
#घोषणा portSVC_START_SCHEDULER            102
#घोषणा portSVC_RAISE_PRIVILEGE            103
#घोषणा portSVC_SYSTEM_CALL_EXIT           104
#घोषणा portSVC_YIELD                      105
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

#घोषणा portSET_INTERRUPT_MASK()                  ulSetInterruptMask()
#घोषणा portCLEAR_INTERRUPT_MASK( x )             vClearInterruptMask( x )
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMask()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMask( x )

#अगर ( config_संख्या_OF_CORES == 1 )
    #घोषणा portENTER_CRITICAL()                      vPortEnterCritical()
    #घोषणा portEXIT_CRITICAL()                       vPortExitCritical()
#अन्यथा /* ( configNUMBER_OF_CORES == 1 ) */
    बाह्य व्योम vTaskEnterCritical( व्योम );
    बाह्य व्योम vTaskExitCritical( व्योम );
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( व्योम );
    बाह्य व्योम vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );

    #घोषणा portENTER_CRITICAL()                      vTaskEnterCritical()
    #घोषणा portEXIT_CRITICAL()                       vTaskExitCritical()
    #घोषणा portENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #घोषणा portEXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#पूर्ण_अगर /* if ( configNUMBER_OF_CORES != 1 ) */
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
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/

#अगर ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #घोषणा portALLOCATE_SECURE_CONTEXT( ul_Secure_ढेर_आकार )    vPortAllocateSecureContext( ul_Secure_ढेर_आकार )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #घोषणा portCLEAN_UP_TCB( pxTCB )                           vPortFreeSecureContext( ( uint32_t * ) pxTCB )
#पूर्ण_अगर /* configENABLE_TRUSTZONE */
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

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #अगर ( ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) && ( config_संख्या_OF_CORES == 1 ) )
        #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
    #अन्यथा
        #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    0
    #पूर्ण_अगर
#पूर्ण_अगर /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#अगर ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    अटल portFORCE_INLINE uint32_t ul_Port_गिनती_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm अस्थिर ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        वापस ulReturn;
    }

/* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 different priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

    #अगर ( portHAS_ARMV8M_MAIN_EXTENSION == 0 )
        #त्रुटि ARMv8-M baseline implementations (such as Cortex-M23) करो not support port-optimised task selection.  Please set configUSE_PORT_OPTIMISED_TASK_SELECTION to 0 or leave it undefined.
    #पूर्ण_अगर

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31UL - ul_Port_गिनती_Leading_Zeros( ( uxReadyPriorities ) ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#अगर ( config_संख्या_OF_CORES > 1 )
    प्रकार क्रमागत
    {
        eIsrLock = 0,
        eTaskLock,
        e_Lock_गिनती
    } ePortRTOSLock;

    बाह्य अस्थिर uint32_t ulCriticalNestings[ config_संख्या_OF_CORES ];
    बाह्य व्योम vPortRecursiveLock( uint8_t ucCoreID,
                                    ePortRTOSLock e_Lock_अंक,
                                    BaseType_t uxAcquire );
    बाह्य uint8_t ucPortGetCoreID( व्योम );
    बाह्य व्योम vInterruptCore( uint8_t ucCoreID );

    #घोषणा portGET_CORE_ID()                                  ucPortGetCoreID()

    #घोषणा port_GET_CRITICAL_NESTING_गिनती( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #घोषणा port_SET_CRITICAL_NESTING_गिनती( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #घोषणा port_INCREMENT_CRITICAL_NESTING_गिनती( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #घोषणा port_DECREMENT_CRITICAL_NESTING_गिनती( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #घोषणा port_MAX_CORE_गिनती                                 ( config_संख्या_OF_CORES )

    #घोषणा portYIELD_CORE( xCoreID )                          vInterruptCore( xCoreID )

    #घोषणा portRELEASE_ISR_LOCK( xCoreID )                    vPortRecursiveLock( ( uint8_t ) xCoreID, eIsrLock, pdFALSE )
    #घोषणा portGET_ISR_LOCK( xCoreID )                        vPortRecursiveLock( ( uint8_t ) xCoreID, eIsrLock, pdTRUE )

    #घोषणा portRELEASE_TASK_LOCK( xCoreID )                   vPortRecursiveLock( ( uint8_t ) xCoreID, eTaskLock, pdFALSE )
    #घोषणा portGET_TASK_LOCK( xCoreID )                       vPortRecursiveLock( ( uint8_t ) xCoreID, eTaskLock, pdTRUE )

    #अगर ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( BaseType_t xWriteControlRegister );
    #पूर्ण_अगर /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#पूर्ण_अगर

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACROCOMMON_H */
