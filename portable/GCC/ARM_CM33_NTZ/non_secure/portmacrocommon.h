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

#ifndef PORTMACROCOMMON_H
#define PORTMACROCOMMON_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    ബാഹ്യ "C" {
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

#ifndef configENABLE_FPU
    #error configENABLE_FPU must be defined in FreeRTOSConfig.h.  Set configENABLE_FPU to 1 to enable the FPU or 0 to disable the FPU.
#endif /* configENABLE_FPU */

#ifndef configENABLE_MPU
    #error configENABLE_MPU must be defined in FreeRTOSConfig.h.  Set configENABLE_MPU to 1 to enable the MPU or 0 to disable the MPU.
#endif /* configENABLE_MPU */

#ifndef configENABLE_TRUSTZONE
    #error configENABLE_TRUSTZONE must be defined in FreeRTOSConfig.h.  Set configENABLE_TRUSTZONE to 1 to enable TrustZone or 0 to disable TrustZone.
#endif /* configENABLE_TRUSTZONE */

#എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )
    #എങ്കിൽ ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 )
        #error "Multi-core SMP is currently only validated for Cortex-M33 non-TrustZone non-MPU port."
    #endif /* if ( portVALIDATED_FOR_SMP != 1 ) || ( configENABLE_MPU == 1 ) || ( configENABLE_TRUSTZONE == 1 ) ) */

    #ifndef configCORE_ID_REGISTER
        #error "configCORE_ID_REGISTER must be defined to the address of the register used to identify the core executing the code."
    #endif /* ifndef configCORE_ID_REGISTER */

    #ifndef configWAKE_SECONDARY_CORES
        #error "configWAKE_SECONDARY_CORES must be defined to a function that wakes the secondary cores."
    #endif /* ifndef configWAKE_SECONDARY_CORES */
#endif /* #if ( configNUMBER_OF_CORES > 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Type definitions.
 */
#define portCHAR          അക്ഷരം
#define portFLOAT         ദശാംശം
#define portDOUBLE        ഇരട്ട
#define portLONG          long
#define portSHORT         short
#define port_അട്ടി_TYPE    uint32_t
#define portBASE_TYPE     long

തരനിർവചനം port_അട്ടി_TYPE   അട്ടി_Type_t;
തരനിർവചനം long             BaseType_t;
തരനിർവചനം unsigned long    UBaseType_t;

#എങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#define port_അട്ടി_GROWTH                   ( -1 )
#define portTICK_PERIOD_MS                 ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT                 8
#define portNOP()
#define portINLINE                         __inline
#ifndef portFORCE_INLINE
    #define portFORCE_INLINE               വരിയിൽ __attribute__( ( always_inline ) )
#endif
#define port_HAS_അട്ടി_OVERFLOW_CHECKING    1
/*-----------------------------------------------------------*/

/**
 * @brief Extern declarations.
 */
ബാഹ്യ BaseType_t xPortIsInsideInterrupt( ശൂന്യം );

ബാഹ്യ ശൂന്യം vPortYield( ശൂന്യം ) /* PRIVILEGED_FUNCTION */;

ബാഹ്യ ശൂന്യം vPortEnterCritical( ശൂന്യം ) /* PRIVILEGED_FUNCTION */;
ബാഹ്യ ശൂന്യം vPortExitCritical( ശൂന്യം ) /* PRIVILEGED_FUNCTION */;

ബാഹ്യ uint32_t ulSetInterruptMask( ശൂന്യം ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;
ബാഹ്യ ശൂന്യം vClearInterruptMask( uint32_t ulMask ) /* __attribute__(( naked )) PRIVILEGED_FUNCTION */;

#എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )
    ബാഹ്യ ശൂന്യം vPortAllocateSecureContext( uint32_t ul_Secure_അട്ടി_Size ); /* __attribute__ (( naked )) */
    ബാഹ്യ ശൂന്യം vPortFreeSecureContext( uint32_t * pulTCB ) /* __attribute__ (( naked )) PRIVILEGED_FUNCTION */;
#endif /* configENABLE_TRUSTZONE */

#എങ്കിൽ ( configENABLE_MPU == 1 )
    ബാഹ്യ BaseType_t xIsPrivileged( ശൂന്യം ) /* __attribute__ (( naked )) */;
    ബാഹ്യ ശൂന്യം vResetPrivilege( ശൂന്യം ) /* __attribute__ (( naked )) */;
#endif /* configENABLE_MPU */

#എങ്കിൽ ( configENABLE_PAC == 1 )

    /**
     * @brief Generates 128-bit task's random PAC key.
     *
     * @param[out] pulTaskPacKey Pointer to a 4-word (128-bits) array to be
     *             filled with a 128-bit random number.
     */
    ശൂന്യം v_Application_Generate_Task_Random_Pac_താക്കോൽ( uint32_t * pul_Task_Pac_താക്കോൽ );

#endif /* configENABLE_PAC */
/*-----------------------------------------------------------*/

/**
 * @brief MPU specific constants.
 */
#എങ്കിൽ ( configENABLE_MPU == 1 )
    #define portUSING_MPU_WRAPPERS    1
    #define portPRIVILEGE_BIT         ( 0x80000000UL )
#അല്ലെങ്കിൽ
    #define portPRIVILEGE_BIT         ( 0x0UL )
#endif /* configENABLE_MPU */

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#ifndef configTOTAL_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #define configTOTAL_MPU_REGIONS    ( 8UL )
#endif

/* MPU regions. */
#define portPRIVILEGED_FLASH_REGION                   ( 0UL )
#define portUNPRIVILEGED_FLASH_REGION                 ( 1UL )
#define portUNPRIVILEGED_SYSCALLS_REGION              ( 2UL )
#define portPRIVILEGED_RAM_REGION                     ( 3UL )
#define port_അട്ടി_REGION                              ( 4UL )
#define portFIRST_CONFIGURABLE_REGION                 ( 5UL )
#define portLAST_CONFIGURABLE_REGION                  ( configTOTAL_MPU_REGIONS - 1UL )
#define port_അക്കം_CONFIGURABLE_REGIONS                  ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#define port_TOTAL_അക്കം_REGIONS                         ( port_അക്കം_CONFIGURABLE_REGIONS + 1 )       /* Plus one to make space for the stack region. */

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
#define portMPU_DEVICE_MEMORY_nGnRnE                  ( 0x00 )       /* 0000 0000 */
#define portMPU_DEVICE_MEMORY_nGnRE                   ( 0x04 )       /* 0000 0100 */
#define portMPU_DEVICE_MEMORY_nGRE                    ( 0x08 )       /* 0000 1000 */
#define portMPU_DEVICE_MEMORY_GRE                     ( 0x0C )       /* 0000 1100 */

/* Normal memory attributes used in MPU_MAIR registers. */
#define portMPU_NORMAL_MEMORY_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
#define portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

/* Attributes used in MPU_RBAR registers. */
#define portMPU_REGION_NON_SHAREABLE                  ( 0UL << 3UL )
#define portMPU_REGION_INNER_SHAREABLE                ( 1UL << 3UL )
#define portMPU_REGION_OUTER_SHAREABLE                ( 2UL << 3UL )

#define portMPU_REGION_PRIVILEGED_READ_WRITE          ( 0UL << 1UL )
#define portMPU_REGION_READ_WRITE                     ( 1UL << 1UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY           ( 2UL << 1UL )
#define portMPU_REGION_READ_ONLY                      ( 3UL << 1UL )

#define portMPU_REGION_EXECUTE_NEVER                  ( 1UL )
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

    /**
     * @brief Settings to define an MPU region.
     */
    തരനിർവചനം ഘടന MPURegionSettings
    {
        uint32_t ulRBAR; /**< RBAR for the region. */
        uint32_t ulRLAR; /**< RLAR for the region. */
    } MPURegionSettings_t;

    #എങ്കിൽ ( configUSE_MPU_WRAPPERS_V1 == 0 )

        #ifndef config_SYSTEM_CALL_അട്ടി_SIZE
            #error config_SYSTEM_CALL_അട്ടി_SIZE must be defined to the desired size of the system call അട്ടി in വാക്കുകൾ വേണ്ടി using MPU wrappers v2.
        #endif

        /**
         * @brief System call stack.
         */
        തരനിർവചനം ഘടന SYSTEM_CALL_അട്ടി_INFO
        {
            uint32_t ul_System_Call_അട്ടി_Buffer[ config_SYSTEM_CALL_അട്ടി_SIZE ];
            uint32_t * pul_System_Call_അട്ടി;
            uint32_t * pul_System_Call_അട്ടി_Limit;
            uint32_t * pul_Task_അട്ടി;
            uint32_t ulLinkRegisterAtSystemCallEntry;
            uint32_t ul_അട്ടി_Limit_Register_At_System_Call_Entry;
        } x_SYSTEM_CALL_അട്ടി_INFO;

    #endif /* configUSE_MPU_WRAPPERS_V1 == 0 */

    /**
     * @brief MPU settings as stored in the TCB.
     */
    #എങ്കിൽ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )

        #എങ്കിൽ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +-----------+---------------+----------+-----------------+------------------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><-----------><---->
             *      16             17            8               8                     5                      4         1
             */
            #define MAX_CONTEXT_SIZE    59

        #അല്ലെങ്കിലെങ്കിൽ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |           |               |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +-----------+---------------+----------+-----------------+------------------------------+-----+
             *
             * <-----------><--------------><---------><----------------><-----------------------------><---->
             *      16             17            8               8                     5                   1
             */
            #define MAX_CONTEXT_SIZE    55

        #അല്ലെങ്കിലെങ്കിൽ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +-----------+---------------+----------+-----------------+----------------------+------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><-----------><---->
             *      16             17            8               8                  4                 4         1
             */
            #define MAX_CONTEXT_SIZE    58

        #അല്ലെങ്കിൽ /* if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

            /*
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             * |  s16-s31  | s0-s15, FPSCR |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |           |               |          | PC, xPSR        | EXC_RETURN           |     |
             * +-----------+---------------+----------+-----------------+----------------------+-----+
             *
             * <-----------><--------------><---------><----------------><---------------------><---->
             *      16             17            8               8                  4              1
             */
            #define MAX_CONTEXT_SIZE    54

        #endif /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #അല്ലെങ്കിൽ /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

        #എങ്കിൽ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+------------------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, | TaskPacKey |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |            |     |
             * +----------+-----------------+------------------------------+------------+-----+
             *
             * <---------><----------------><------------------------------><-----------><---->
             *     8               8                      5                       4         1
             */
            #define MAX_CONTEXT_SIZE    26

        #അല്ലെങ്കിലെങ്കിൽ ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 0 ) )

            /*
             * +----------+-----------------+------------------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | xSecureContext, PSP, PSPLIM, |     |
             * |          | PC, xPSR        | CONTROL, EXC_RETURN          |     |
             * +----------+-----------------+------------------------------+-----+
             *
             * <---------><----------------><------------------------------><---->
             *     8               8                      5                   1
             */
            #define MAX_CONTEXT_SIZE    22

        #അല്ലെങ്കിലെങ്കിൽ ( ( configENABLE_TRUSTZONE == 0 ) && ( configENABLE_PAC == 1 ) )

            /*
             * +----------+-----------------+----------------------+------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL | TaskPacKey |     |
             * |          | PC, xPSR        | EXC_RETURN           |            |     |
             * +----------+-----------------+----------------------+------------+-----+
             *
             * <---------><----------------><----------------------><-----------><---->
             *     8               8                  4                   4         1
             */
            #define MAX_CONTEXT_SIZE    25

        #അല്ലെങ്കിൽ /* #if( configENABLE_TRUSTZONE == 1 ) */

            /*
             * +----------+-----------------+----------------------+-----+
             * |  r4-r11  | r0-r3, r12, LR, | PSP, PSPLIM, CONTROL |     |
             * |          | PC, xPSR        | EXC_RETURN           |     |
             * +----------+-----------------+----------------------+-----+
             *
             * <---------><----------------><----------------------><---->
             *     8               8                  4              1
             */
            #define MAX_CONTEXT_SIZE    21

        #endif /* #if ( ( configENABLE_TRUSTZONE == 1 ) && ( configENABLE_PAC == 1 ) ) */

    #endif /* #if ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) ) */

    /* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
    #define port_അട്ടി_FRAME_HAS_PADDING_FLAG    ( 1UL << 0UL )
    #define portTASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

    /* Size of an Access Control List (ACL) entry in bits. */
    #define portACL_ENTRY_SIZE_BITS             ( 32U )

    തരനിർവചനം ഘടന MPU_SETTINGS
    {
        uint32_t ulMAIR0;                                              /**< MAIR0 for the task containing attributes for all the 4 per task regions. */
        MPURegionSettings_t xRegionsSettings[ port_TOTAL_അക്കം_REGIONS ]; /**< Settings for 4 per task regions. */
        uint32_t ulContext[ MAX_CONTEXT_SIZE ];
        uint32_t ulTaskFlags;

        #എങ്കിൽ ( configUSE_MPU_WRAPPERS_V1 == 0 )
            x_SYSTEM_CALL_അട്ടി_INFO x_System_Call_അട്ടി_Info;
            #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( configPROTECTED_KERNEL_OBJECT_POOL_SIZE / portACL_ENTRY_SIZE_BITS ) + 1 ];
            #endif
        #endif
    } xMPU_SETTINGS;

#endif /* configENABLE_MPU == 1 */
/*-----------------------------------------------------------*/

/**
 * @brief Validate priority of ISRs that are allowed to call FreeRTOS
 * system calls.
 */
#എങ്കിൽ ( configASSERT_DEFINED == 1 )
    #എങ്കിൽ ( portHAS_ARMV8M_MAIN_EXTENSION == 1 )
        ശൂന്യം vPortValidateInterruptPriority( ശൂന്യം );
        #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
    #endif
#endif

/**
 * @brief SVC numbers.
 */
#define portSVC_ALLOCATE_SECURE_CONTEXT    100
#define portSVC_FREE_SECURE_CONTEXT        101
#define portSVC_START_SCHEDULER            102
#define portSVC_RAISE_PRIVILEGE            103
#define portSVC_SYSTEM_CALL_EXIT           104
#define portSVC_YIELD                      105
/*-----------------------------------------------------------*/

/**
 * @brief Scheduler utilities.
 */
#എങ്കിൽ ( configENABLE_MPU == 1 )
    #define portYIELD()               __asm അസ്ഥിര ( "svc %0" ::"i" ( portSVC_YIELD ) : "memory" )
    #define portYIELD_WITHIN_API()    vPortYield()
#അല്ലെങ്കിൽ
    #define portYIELD()               vPortYield()
    #define portYIELD_WITHIN_API()    vPortYield()
#endif

#define portNVIC_INT_CTRL_REG     ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    ചെയ്യുക                                                      \
    {                                                       \
        എങ്കിൽ( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        അല്ലെങ്കിൽ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ആകുമ്പോൾ( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */

#define portSET_INTERRUPT_MASK()                  ulSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK( x )             vClearInterruptMask( x )
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMask( x )

#എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
    #define portENTER_CRITICAL()                      vPortEnterCritical()
    #define portEXIT_CRITICAL()                       vPortExitCritical()
#അല്ലെങ്കിൽ /* ( configNUMBER_OF_CORES == 1 ) */
    ബാഹ്യ ശൂന്യം vTaskEnterCritical( ശൂന്യം );
    ബാഹ്യ ശൂന്യം vTaskExitCritical( ശൂന്യം );
    ബാഹ്യ UBaseType_t vTaskEnterCriticalFromISR( ശൂന്യം );
    ബാഹ്യ ശൂന്യം vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );

    #define portENTER_CRITICAL()                      vTaskEnterCritical()
    #define portEXIT_CRITICAL()                       vTaskExitCritical()
    #define portENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #define portEXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#endif /* if ( configNUMBER_OF_CORES != 1 ) */
/*-----------------------------------------------------------*/

/**
 * @brief Tickless idle/low power functionality.
 */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    ബാഹ്യ ശൂന്യം vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/**
 * @brief Task function macros as described on the FreeRTOS.org WEB site.
 */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_TRUSTZONE == 1 )

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
    #define portALLOCATE_SECURE_CONTEXT( ul_Secure_അട്ടി_Size )    vPortAllocateSecureContext( ul_Secure_അട്ടി_Size )

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
    #define portCLEAN_UP_TCB( pxTCB )                           vPortFreeSecureContext( ( uint32_t * ) pxTCB )
#endif /* configENABLE_TRUSTZONE */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

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
    #define portRAISE_PRIVILEGE()    __asm അസ്ഥിര ( "svc %0 \n" ::"i" ( portSVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
    #define portRESET_PRIVILEGE()    vResetPrivilege()
#അല്ലെങ്കിൽ
    #define portIS_PRIVILEGED()
    #define portRAISE_PRIVILEGE()
    #define portRESET_PRIVILEGE()
#endif /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configENABLE_MPU == 1 )

    ബാഹ്യ BaseType_t xPortIsTaskPrivileged( ശൂന്യം );

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
#define portMEMORY_BARRIER()    __asm അസ്ഥിര ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Select correct value of configUSE_PORT_OPTIMISED_TASK_SELECTION
 * based on whether or not Mainline extension is implemented. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #എങ്കിൽ ( ( portHAS_ARMV8M_MAIN_EXTENSION == 1 ) && ( config_സംഖ്യ_OF_CORES == 1 ) )
        #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
    #അല്ലെങ്കിൽ
        #define configUSE_PORT_OPTIMISED_TASK_SELECTION    0
    #endif
#endif /* #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION */

/**
 * @brief Port-optimised task selection.
 */
#എങ്കിൽ ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

/**
 * @brief Count the number of leading zeros in a 32-bit value.
 */
    സ്ഥിതം portFORCE_INLINE uint32_t ul_Port_എണ്ണം_Leading_Zeros( uint32_t ulBitmap )
    {
        uint32_t ulReturn;

        __asm അസ്ഥിര ( "clz %0, %1" : "=r" ( ulReturn ) : "r" ( ulBitmap ) : "memory" );

        തിരികെ ulReturn;
    }

/* Check the configuration. */
    #എങ്കിൽ ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice.
    #endif

    #എങ്കിൽ ( portHAS_ARMV8M_MAIN_EXTENSION == 0 )
        #error ARMv8-M baseline implementations (such as Cortex-M23) ചെയ്യുക not support port-optimised task selection.  Please set configUSE_PORT_OPTIMISED_TASK_SELECTION to 0 or leave it undefined.
    #endif

/**
 * @brief Store/clear the ready priorities in a bit map.
 */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )      ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )       ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/**
 * @brief Get the priority of the highest-priority task that is ready to execute.
 */
    #define portGET_HIGHEST_PRIORITY( ux_മുകൾ_Priority, uxReadyPriorities )    ux_മുകൾ_Priority = ( 31UL - ul_Port_എണ്ണം_Leading_Zeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/


#എങ്കിൽ ( config_സംഖ്യ_OF_CORES > 1 )
    തരനിർവചനം എണ്ണൽ
    {
        eIsrLock = 0,
        eTaskLock,
        e_Lock_എണ്ണം
    } ePortRTOSLock;

    ബാഹ്യ അസ്ഥിര uint32_t ulCriticalNestings[ config_സംഖ്യ_OF_CORES ];
    ബാഹ്യ ശൂന്യം vPortRecursiveLock( uint8_t ucCoreID,
                                    ePortRTOSLock e_Lock_അക്കം,
                                    BaseType_t uxAcquire );
    ബാഹ്യ uint8_t ucPortGetCoreID( ശൂന്യം );
    ബാഹ്യ ശൂന്യം vInterruptCore( uint8_t ucCoreID );

    #define portGET_CORE_ID()                                  ucPortGetCoreID()

    #define port_GET_CRITICAL_NESTING_എണ്ണം( xCoreID )          ( ulCriticalNestings[ ( uint8_t ) xCoreID ] )
    #define port_SET_CRITICAL_NESTING_എണ്ണം( xCoreID, x )       ( ulCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #define port_INCREMENT_CRITICAL_NESTING_എണ്ണം( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #define port_DECREMENT_CRITICAL_NESTING_എണ്ണം( xCoreID )    ( ulCriticalNestings[ ( uint8_t ) xCoreID ]-- )

    #define port_MAX_CORE_എണ്ണം                                 ( config_സംഖ്യ_OF_CORES )

    #define portYIELD_CORE( xCoreID )                          vInterruptCore( xCoreID )

    #define portRELEASE_ISR_LOCK( xCoreID )                    vPortRecursiveLock( ( uint8_t ) xCoreID, eIsrLock, pdFALSE )
    #define portGET_ISR_LOCK( xCoreID )                        vPortRecursiveLock( ( uint8_t ) xCoreID, eIsrLock, pdTRUE )

    #define portRELEASE_TASK_LOCK( xCoreID )                   vPortRecursiveLock( ( uint8_t ) xCoreID, eTaskLock, pdFALSE )
    #define portGET_TASK_LOCK( xCoreID )                       vPortRecursiveLock( ( uint8_t ) xCoreID, eTaskLock, pdTRUE )

    #എങ്കിൽ ( ( configENABLE_PAC == 1 ) || ( configENABLE_BTI == 1 ) )
        uint32_t vConfigurePACBTI( BaseType_t xWriteControlRegister );
    #endif /* ( configENABLE_PAC == 1 || configENABLE_BTI == 1 ) */
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACROCOMMON_H */
