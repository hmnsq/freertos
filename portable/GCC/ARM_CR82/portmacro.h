/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025-2026 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
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

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    माप_प्रकार
#घोषणा portBASE_TYPE     दीर्घ

#अगर !defined(__ASSEMBLER__)
    प्रकार port_ढेर_TYPE   ढेर_Type_t;
    प्रकार portBASE_TYPE    BaseType_t;
    प्रकार uint64_t         UBaseType_t;

    प्रकार uint64_t         TickType_t;
    #घोषणा portMAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#घोषणा portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#घोषणा port_ढेर_GROWTH         ( -1 )
#घोषणा portTICK_PERIOD_MS       ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT       16
#घोषणा port_POINTER_आकार_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#अगर !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #अगर ( config_संख्या_OF_CORES == 1 )
        #घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            बाह्य uint64_t ullPortYieldRequired;        \
                                                        \
            अगर( xSwitchRequired != pdFALSE )             \
            {                                            \
                ullPortYieldRequired = pdTRUE;           \
            }                                            \
        }
    #अन्यथा
        #घोषणा portEND_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            बाह्य uint64_t ullPortYieldRequired[ config_संख्या_OF_CORES ]; \
                                                                        \
            अगर( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ullPortYieldRequired[ portGET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #पूर्ण_अगर /* if ( configNUMBER_OF_CORES == 1 ) */
#पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#घोषणा portSVC_SYSTEM_CALL_EXIT                    104
#घोषणा portSVC_YIELD                               105
#घोषणा portSVC_START_FIRST_TASK                    106
#घोषणा portSVC_DISABLE_INTERRUPTS                  107
#घोषणा portSVC_ENABLE_INTERRUPTS                   108
#घोषणा portSVC_GET_CORE_ID                         109
#घोषणा portSVC_MASK_ALL_INTERRUPTS                 110
#घोषणा portSVC_UNMASK_ALL_INTERRUPTS               111
#घोषणा portSVC_UNMASK_INTERRUPTS                   112
#घोषणा portSVC_CHECK_PRIVILEGE                     113
#घोषणा portSVC_SAVE_TASK_CONTEXT                   114
#घोषणा portSVC_RESTORE_CONTEXT                     115
#घोषणा portSVC_DELETE_CURRENT_TASK                 116
#घोषणा portSVC_INTERRUPT_CORE                      117

#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
#घोषणा portYIELD()                __asm अस्थिर ( "SVC %0" : : "i" ( portSVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#अगर !defined(__ASSEMBLER__)
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( व्योम );
    बाह्य व्योम vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
    बाह्य UBaseType_t uxPortSetInterruptMask( व्योम );
    बाह्य UBaseType_t uxPortSetInterruptMaskFromISR( व्योम );
    बाह्य व्योम vPortClearInterruptMask( UBaseType_t ux_New_Mask_मूल्य );
    बाह्य व्योम vPortClearInterruptMaskFromISR( UBaseType_t ux_New_Mask_मूल्य );
    बाह्य व्योम vInterruptCore( uint32_t ulInterruptID, uint8_t ucCoreID );
#पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#घोषणा portDISABLE_INTERRUPTS() __asm अस्थिर ( "SVC %0" : : "i" ( portSVC_DISABLE_INTERRUPTS ) : "memory" )

#घोषणा portENABLE_INTERRUPTS()  __asm अस्थिर ( "SVC %0" : : "i" ( portSVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#घोषणा port_UNMASK_मूल्य           ( 0xFFUL )

#अगर !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #अगर  ( config_संख्या_OF_CORES == 1 )
        बाह्य व्योम vPortEnterCritical( व्योम );
        बाह्य व्योम vPortExitCritical( व्योम );
        #घोषणा portENTER_CRITICAL()                  vPortEnterCritical()
        #घोषणा portEXIT_CRITICAL()                   vPortExitCritical()
    #अन्यथा
        #घोषणा portENTER_CRITICAL()                  vTaskEnterCritical()
        #घोषणा portEXIT_CRITICAL()                   vTaskExitCritical()
    #पूर्ण_अगर
    #घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         uxPortSetInterruptMaskFromISR()
    #घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMaskFromISR( x )
    #घोषणा portENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #घोषणा portEXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

#अगर !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    व्योम FreeRTOS_Tick_Handler( व्योम );
#पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

#घोषणा portTASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#घोषणा portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#अगर ( configUSE_TASK_FPU_SUPPORT == portTASK_NO_FPU_CONTEXT_BY_DEFAULT )
    व्योम vPortTaskUsesFPU( व्योम );
#अन्यथा
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #घोषणा vPortTaskUsesFPU()
#पूर्ण_अगर

#घोषणा portTASK_USES_FLOATING_POINT()          vPortTaskUsesFPU()

#घोषणा portLOWEST_INTERRUPT_PRIORITY           ( ( ( uint32_t ) configUNIQUE_INTERRUPT_PRIORITIES ) - 1UL )
#घोषणा portLOWEST_USABLE_INTERRUPT_PRIORITY    ( portLOWEST_INTERRUPT_PRIORITY - 1UL )

/* Architecture specific optimisations. */
#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31 - __builtin_clz( uxReadyPriorities ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#अगर ( configASSERT_DEFINED == 1 )
    व्योम vPortValidateInterruptPriority( व्योम );
    #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#पूर्ण_अगर /* configASSERT */

#घोषणा portNOP()     __asm अस्थिर ( "NOP" )
#घोषणा portINLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#अगर configUNIQUE_INTERRUPT_PRIORITIES == 16
    #घोषणा portPRIORITY_SHIFT            4
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    3
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 32
    #घोषणा portPRIORITY_SHIFT            3
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    2
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 64
    #घोषणा portPRIORITY_SHIFT            2
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    1
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 128
    #घोषणा portPRIORITY_SHIFT            1
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    0
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 256
    #घोषणा portPRIORITY_SHIFT            0
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    0
#अन्यथा /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #त्रुटि Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the संख्या of unique priorities implemented by the target hardware
#पूर्ण_अगर /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#घोषणा portINTERRUPT_PRIORITY_REGISTER_OFFSET    ( 0x400U )
#घोषणा portYIELD_CORE_INT_ID                     ( 0x0U )
#घोषणा portMAX_API_PRIORITY_MASK                 ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT )

#अगर ( config_संख्या_OF_CORES > 1 )

    #अगर !defined(__ASSEMBLER__)
        प्रकार क्रमागत
        {
            eIsrLock = 0,
            eTaskLock,
            e_Lock_गिनती
        } ePortRTOSLock;

        बाह्य अस्थिर uint64_t ullCriticalNestings[ config_संख्या_OF_CORES ];
        बाह्य व्योम vPortRecursiveLock( uint8_t ucCoreID,
                                        ePortRTOSLock e_Lock_अंक,
                                        BaseType_t uxAcquire );
        बाह्य uint8_t ucPortGetCoreID( व्योम );
        बाह्य uint8_t ucPortGetCoreIDFromIsr( व्योम );
    #पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

    #घोषणा portSET_INTERRUPT_MASK()         uxPortSetInterruptMask()
    #घोषणा portCLEAR_INTERRUPT_MASK( x )    vPortClearInterruptMask( x )

    #घोषणा port_MAX_CORE_गिनती               config_संख्या_OF_CORES
    #घोषणा portGET_CORE_ID()                ucPortGetCoreID()
    #घोषणा portGET_CORE_ID_FROM_ISR()       ucPortGetCoreIDFromIsr()

    /* Use SGI 0 as the yield core interrupt. */
    #घोषणा portYIELD_CORE( xCoreID )                          vInterruptCore( portYIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #घोषणा portRELEASE_ISR_LOCK( xCoreID )                    vPortRecursiveLock( ( uint8_t ) xCoreID, eIsrLock, pdFALSE )
    #घोषणा portGET_ISR_LOCK( xCoreID )                        vPortRecursiveLock( ( uint8_t ) xCoreID, eIsrLock, pdTRUE )

    #घोषणा portRELEASE_TASK_LOCK( xCoreID )                   vPortRecursiveLock( ( uint8_t ) xCoreID, eTaskLock, pdFALSE )
    #घोषणा portGET_TASK_LOCK( xCoreID )                       vPortRecursiveLock( ( uint8_t ) xCoreID, eTaskLock, pdTRUE )
    #घोषणा port_GET_CRITICAL_NESTING_गिनती( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #घोषणा port_SET_CRITICAL_NESTING_गिनती( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #घोषणा port_INCREMENT_CRITICAL_NESTING_गिनती( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #घोषणा port_DECREMENT_CRITICAL_NESTING_गिनती( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#पूर्ण_अगर /* configNUMBER_OF_CORES > 1 */

#घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#अगर ( configENABLE_MPU == 1 )

    #अगर !defined(__ASSEMBLER__)
        बाह्य BaseType_t xPortIsTaskPrivileged( व्योम );
    #पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

    /* Device memory attributes used in MAIR_EL1 registers.
     *
     * 8-bit values encoded as follows:
     *  Bit[7:4] - 0000 - Device Memory
     *  Bit[3:2] - 00 --> Device-nGnRnE
     *             01 --> Device-nGnRE
     *             10 --> Device-nGRE
     *             11 --> Device-GRE
     *  Bit[1:0] - 00.
     */
    #घोषणा portMPU_DEVICE_MEMORY_nGnRnE                 ( 0x00 )
    #घोषणा portMPU_DEVICE_MEMORY_nGnRE                  ( 0x04 )
    #घोषणा portMPU_DEVICE_MEMORY_nGRE                   ( 0x08 )
    #घोषणा portMPU_DEVICE_MEMORY_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #अगर_अघोषित config_योग_MPU_REGIONS
        #घोषणा config_योग_MPU_REGIONS                  ( 16UL )
    #पूर्ण_अगर

    #घोषणा portPRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #घोषणा portUNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #घोषणा portUNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #घोषणा portPRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #घोषणा port_ढेर_REGION                             ( 4ULL )                                /* Stack region number. */
    #घोषणा port_ढेर_REGION_सूचकांक                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #घोषणा portFIRST_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #घोषणा portLAST_CONFIGURABLE_REGION                 ( config_योग_MPU_REGIONS - 1UL )
    #घोषणा port_अंक_CONFIGURABLE_REGIONS                 ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
    #घोषणा port_योग_अंक_REGIONS                        ( port_अंक_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #घोषणा port_ACL_ENTRY_आकार_BITS ( 32UL )
    #पूर्ण_अगर /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #अगर !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        प्रकार काष्ठा MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #अगर_अघोषित config_SYSTEM_CALL_ढेर_आकार
            #घोषणा config_SYSTEM_CALL_ढेर_आकार 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #पूर्ण_अगर

        /**
         * @brief System call info.
         */
        प्रकार काष्ठा SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ullLinkRegisterAtSystemCallEntry;
            uint64_t ullUserSPAtSystemCallEntry;
        } xSYSTEM_CALL_INFO;
    #पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #अगर ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #घोषणा MAX_CONTEXT_आकार    102

    #अन्यथा /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #घोषणा MAX_CONTEXT_आकार    36
    #पूर्ण_अगर /* #if ( configENABLE_FPU == 1 ) */

    #अगर !defined(__ASSEMBLER__)
        प्रकार काष्ठा MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ port_योग_अंक_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_आकार + config_SYSTEM_CALL_ढेर_आकार ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार / port_ACL_ENTRY_आकार_BITS ) + 1 ];
            #पूर्ण_अगर /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #पूर्ण_अगर /* if !defined(__ASSEMBLER__) */

    #घोषणा portUSING_MPU_WRAPPERS                        ( 1 )
    #घोषणा portPRIVILEGE_BIT                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #घोषणा portMPU_NORMAL_MEMORY_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #घोषणा portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #घोषणा portMPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #घोषणा portMPU_MAIR_EL1_ATTR0_MASK                   ( 0x00000000000000ffULL )

    #घोषणा portMPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #घोषणा portMPU_MAIR_EL1_ATTR1_MASK                   ( 0x000000000000ff00ULL )

    #घोषणा portMPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #घोषणा portMPU_MAIR_EL1_ATTR2_MASK                   ( 0x0000000000ff0000ULL )

    #घोषणा portMPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #घोषणा portMPU_MAIR_EL1_ATTR3_MASK                   ( 0x00000000ff000000ULL )

    #घोषणा portMPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #घोषणा portMPU_MAIR_EL1_ATTR4_MASK                   ( 0x000000ff00000000ULL )

    #घोषणा portMPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #घोषणा portMPU_MAIR_EL1_ATTR5_MASK                   ( 0x0000ff0000000000ULL )

    #घोषणा portMPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #घोषणा portMPU_MAIR_EL1_ATTR6_MASK                   ( 0x00ff000000000000ULL )

    #घोषणा portMPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #घोषणा portMPU_MAIR_EL1_ATTR7_MASK                   ( 0xff00000000000000ULL )

    #घोषणा portMPU_PRBAR_EL1_ADDRESS_MASK                ( 0x0000FFFFFFFFFFC0ULL )
    #घोषणा portMPU_PRLAR_EL1_ADDRESS_MASK                ( 0x0000FFFFFFFFFFC0ULL )
    #घोषणा portMPU_PRLAR_EL1_ADDRESS_IMPLIED_BITS        ( 0x000000000000003FULL )
    #घोषणा portMPU_PRBAR_EL1_ACCESS_PERMISSIONS_MASK     ( 3ULL<< 2ULL )

    #घोषणा portMPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #घोषणा portMPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #घोषणा portMPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #घोषणा portMPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #घोषणा portMPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #घोषणा portMPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #घोषणा portMPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #घोषणा portMPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #घोषणा portMPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #घोषणा portMPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #घोषणा portMPU_ENABLE_BIT                            ( 1ULL << 0ULL )
    #घोषणा portMPU_PRIV_BACKGROUND_ENABLE_BIT            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #घोषणा portUINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #घोषणा portADD_UINT64_WILL_OVERFLOW( a, b )          ( ( a ) > ( portUINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #घोषणा portEXTRACT_FIRST_ADDRESS_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & portMPU_PRBAR_EL1_ADDRESS_MASK )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #घोषणा portEXTRACT_LAST_ADDRESS_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & portMPU_PRLAR_EL1_ADDRESS_MASK ) | portMPU_PRLAR_EL1_ADDRESS_IMPLIED_BITS )

    /* Does addr lies within [start, end] address range? */
    #घोषणा portIS_ADDRESS_WITHIN_RANGE( addr, start, end ) \
        ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( end ) ) )

    /* Is the access request satisfied by the available permissions? */
    #घोषणा portIS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #अगर ( configUSE_TASK_FPU_SUPPORT == portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #घोषणा portOFFSET_TO_PC     ( 68 )
        #घोषणा portOFFSET_TO_LR     ( 70 )
        #घोषणा portOFFSET_TO_X0     ( 100 )
        #घोषणा portOFFSET_TO_X1     ( 101 )
        #घोषणा portOFFSET_TO_X2     ( 98 )
        #घोषणा portOFFSET_TO_X3     ( 99 )
    #अन्यथा
        #घोषणा portOFFSET_TO_PC     ( 2 )
        #घोषणा portOFFSET_TO_LR     ( 4 )
        #घोषणा portOFFSET_TO_X0     ( 34 )
        #घोषणा portOFFSET_TO_X1     ( 35 )
        #घोषणा portOFFSET_TO_X2     ( 32 )
        #घोषणा portOFFSET_TO_X3     ( 33 )
    #पूर्ण_अगर

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #घोषणा portTASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #घोषणा portIS_TASK_PRIVILEGED() xPortIsTaskPrivileged()

#अन्यथा

    #घोषणा portPRIVILEGE_BIT        ( 0x0UL )

#पूर्ण_अगर /* #if ( configENABLE_MPU == 1 ) */

#घोषणा portPSTATE_I_BIT             ( 0x7 )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
