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


#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطي "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#جيڪڏهن_پورو

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#جيڪڏهن_وصف_نه_ٿيل configENABLE_ERRATA_837070_WORKAROUND
    #وصف_ڪريو configENABLE_ERRATA_837070_WORKAROUND    0
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#وصف_ڪريو پورٽ_USING_MPU_WRAPPERS                                   1
#وصف_ڪريو پورٽ_PRIVILEGE_ٻٽو_انگ                                        ( 0x80000000UL )

#وصف_ڪريو پورٽ_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#وصف_ڪريو پورٽ_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#وصف_ڪريو پورٽ_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#وصف_ڪريو پورٽ_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#وصف_ڪريو پورٽ_MPU_RASR_TEX_S_C_B_نقاب                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#جيڪڏهن_وصف_نه_ٿيل config_ڪل_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #وصف_ڪريو config_ڪل_MPU_REGIONS    ( 8UL )
#جيڪڏهن_پورو

/*
 * The TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits define the
 * memory type, and where necessary the cacheable and shareable properties
 * of the memory region.
 *
 * The TEX, C, and B bits together indicate the memory type of the region,
 * and:
 * - For Normal memory, the cacheable properties of the region.
 * - For Device memory, whether the region is shareable.
 *
 * For Normal memory regions, the S bit indicates whether the region is
 * shareable. For Strongly-ordered and Device memory, the S bit is ignored.
 *
 * See the following two tables for setting TEX, S, C and B bits for
 * unprivileged flash, privileged flash and privileged RAM regions.
 *
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | TEX | C | B | Memory type            |  Description or Normal region cacheability             |  Shareable?             |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 0 | 0 | Strongly-ordered       |  Strongly ordered                                      |  Shareable              |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 0 | 1 | Device                 |  Shared device                                         |  Shareable              |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 1 | 0 | Normal                 |  Outer and inner   write-through; no write allocate    |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 000 | 1 | 1 | Normal                 |  Outer and inner   write-back; no write allocate       |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 0 | 0 | Normal                 |  Outer and inner   Non-cacheable                       |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 0 | 1 | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 1 | 0 | IMPLEMENTATION DEFINED |  IMPLEMENTATION DEFINED                                |  IMPLEMENTATION DEFINED |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 001 | 1 | 1 | Normal                 |  Outer and inner   write-back; write and read allocate |  S bit                  |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 010 | 0 | 0 | Device                 |  Non-shared device                                     |  Not shareable          |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 010 | 0 | 1 | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 010 | 1 | X | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 011 | X | X | Reserved               |  Reserved                                              |  Reserved               |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 | 1BB | A | A | Normal                 | Cached memory, with AA and BB indicating the inner and |  Reserved               |
 |     |   |   |                        | outer cacheability rules that must be exported on the  |                         |
 |     |   |   |                        | bus. See the table below for the cacheability policy   |                         |
 |     |   |   |                        | encoding. memory, BB=Outer policy, AA=Inner policy.    |                         |
 +-----+---+---+------------------------+--------------------------------------------------------+-------------------------+
 |
 +-----------------------------------------+----------------------------------------+
 | AA or BB subfield of {TEX,C,B} encoding |  Cacheability policy                   |
 +-----------------------------------------+----------------------------------------+
 | 00                                      |  Non-cacheable                         |
 +-----------------------------------------+----------------------------------------+
 | 01                                      |  Write-back, write and   read allocate |
 +-----------------------------------------+----------------------------------------+
 | 10                                      |  Write-through, no write   allocate    |
 +-----------------------------------------+----------------------------------------+
 | 11                                      |  Write-back, no write   allocate       |
 +-----------------------------------------+----------------------------------------+
 */

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for Flash
 * region. */
#جيڪڏهن_وصف_نه_ٿيل configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #وصف_ڪريو configTEX_S_C_B_FLASH    ( 0x07UL )
#جيڪڏهن_پورو

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for SRAM
 * region. */
#جيڪڏهن_وصف_نه_ٿيل configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #وصف_ڪريو configTEX_S_C_B_SRAM          ( 0x07UL )
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_ڍير_REGION                  ( config_ڪل_MPU_REGIONS - 5UL )
#وصف_ڪريو پورٽ_GENERAL_PERIPHERALS_REGION    ( config_ڪل_MPU_REGIONS - 4UL )
#وصف_ڪريو پورٽ_UNPRIVILEGED_FLASH_REGION     ( config_ڪل_MPU_REGIONS - 3UL )
#وصف_ڪريو پورٽ_PRIVILEGED_FLASH_REGION       ( config_ڪل_MPU_REGIONS - 2UL )
#وصف_ڪريو پورٽ_PRIVILEGED_RAM_REGION         ( config_ڪل_MPU_REGIONS - 1UL )
#وصف_ڪريو پورٽ_پهريون_CONFIGURABLE_REGION     ( 0UL )
#وصف_ڪريو پورٽ_آخري_CONFIGURABLE_REGION      ( config_ڪل_MPU_REGIONS - 6UL )
#وصف_ڪريو پورٽ_انگ_CONFIGURABLE_REGIONS      ( config_ڪل_MPU_REGIONS - 5UL )
#وصف_ڪريو پورٽ_ڪل_انگ_REGIONS_اندريون_TCB      ( پورٽ_انگ_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

تعريفنوع بنية MPU_REGION_REGISTERS
{
    uint32_t ul_Region_بنياد_پتو;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

تعريفنوع بنية MPU_REGION_SETTINGS
{
    uint32_t ul_Region_شروعات_پتو;
    uint32_t ul_Region_پڇاڙي_پتو;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #جيڪڏهن_وصف_نه_ٿيل config_SYSTEM_CALL_ڍير_سائيز
        #غلطي "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #جيڪڏهن_پورو

    تعريفنوع بنية SYSTEM_CALL_ڍير_INFO
    {
        uint32_t ul_System_Call_ڍير_بفر[ config_SYSTEM_CALL_ڍير_سائيز ];
        uint32_t * pul_System_Call_ڍير;
        uint32_t * pul_Task_ڍير;
        uint32_t ul_Link_رجسٽر_At_System_Call_داخلا;
    } x_SYSTEM_CALL_ڍير_INFO;

#جيڪڏهن_پورو /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#وصف_ڪريو MAX_CONTEXT_سائيز                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#وصف_ڪريو پورٽ_ACL_داخلا_سائيز_بٽ             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#وصف_ڪريو پورٽ_ڍير_چوکٺو_HAS_PADDING_FLAG    ( 1UL << 0UL )
#وصف_ڪريو پورٽ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

تعريفنوع بنية MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورٽ_ڪل_انگ_REGIONS_اندريون_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ پورٽ_ڪل_انگ_REGIONS_اندريون_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_سائيز ];
    uint32_t ulTaskFlags;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ڍير_INFO x_System_Call_ڍير_Info;
        #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائيز / پورٽ_ACL_داخلا_سائيز_بٽ ) + 1 ];
        #جيڪڏهن_پورو
    #جيڪڏهن_پورو
} xMPU_SETTINGS;

/* Architecture specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH          ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT        8

/* Constants used with memory barrier intrinsics. */
#وصف_ڪريو پورٽ_SY_ڀريل_READ_WRITE    ( 15 )

/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#وصف_ڪريو پورٽ_SVC_شروعات_SCHEDULER        100
#وصف_ڪريو پورٽ_SVC_YIELD                  101
#وصف_ڪريو پورٽ_SVC_RAISE_PRIVILEGE        102
#وصف_ڪريو پورٽ_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#وصف_ڪريو پورٽ_YIELD()    __asm { SVC پورٽ_SVC_YIELD }
#وصف_ڪريو پورٽ_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __dsb( پورٽ_SY_ڀريل_READ_WRITE );                           \
        __isb( پورٽ_SY_ڀريل_READ_WRITE );                           \
    }
/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#وصف_ڪريو پورٽ_NVIC_PENDSVSET_ٻٽو_انگ    ( 1UL << 28UL )
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                  v_پورٽ_Raise_BASEPRI()
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                   v_پورٽ_سيٽ_BASEPRI( 0 )
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                      v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()                       v_پورٽ_Exit_Critical()
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         ul_پورٽ_Raise_BASEPRI()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٽ_سيٽ_BASEPRI( x )

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #جيڪڏهن_پورو

/* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/*-----------------------------------------------------------*/

    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ );
    #وصف_ڪريو پورٽ_ASSERT_IF_مداخلت_ترجيح_INVALID()    v_پورٽ_Validate_مداخلت_ترجيح()
#جيڪڏهن_پورو

/* portNOP() is not required by this port. */
#وصف_ڪريو پورٽ_NOP()

#وصف_ڪريو پورٽ_INLINE              __inline

#جيڪڏهن_وصف_نه_ٿيل پورٽ_FORCE_INLINE
    #وصف_ڪريو پورٽ_FORCE_INLINE    __forceinline
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

خارجي بنياد_Type_t xIsPrivileged( فراغ );
خارجي فراغ vResetPrivilege( فراغ );
خارجي فراغ v_پورٽ_Switch_منزل_User_گهڻائي( فراغ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#وصف_ڪريو پورٽ_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#وصف_ڪريو پورٽ_RAISE_PRIVILEGE()        __asm { svc پورٽ_SVC_RAISE_PRIVILEGE }

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#وصف_ڪريو پورٽ_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#وصف_ڪريو پورٽ_SWITCH_منزل_USER_گهڻائي()    v_پورٽ_Switch_منزل_User_گهڻائي()
/*-----------------------------------------------------------*/

خارجي بنياد_Type_t x_پورٽ_Is_Task_Privileged( فراغ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#وصف_ڪريو پورٽ_IS_TASK_PRIVILEGED()    x_پورٽ_Is_Task_Privileged()
/*-----------------------------------------------------------*/

ساكن پورٽ_FORCE_INLINE فراغ v_پورٽ_سيٽ_BASEPRI( uint32_t ulBASEPRI )
{
    __asm
    {
        /* Barrier instructions are not used as this function is only used to
         * lower the BASEPRI value. */
/* *INDENT-OFF* */
        msr basepri, ulBASEPRI
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ساكن پورٽ_FORCE_INLINE فراغ v_پورٽ_Raise_BASEPRI( فراغ )
{
    uint32_t ulNewBASEPRI = config_MAX_SYSCALL_مداخلت_ترجيح;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsid i
    #جيڪڏهن_پورو
        msr basepri, ulNewBASEPRI
        dsb
        isb
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsie i
    #جيڪڏهن_پورو
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ساكن پورٽ_FORCE_INLINE فراغ v_پورٽ_Clear_BASEPRIFrom_ISR( فراغ )
{
    __asm
    {
        /* Set BASEPRI to 0 so no interrupts are masked.  This function is only
         * used to lower the mask in an interrupt, so memory barriers are not
         * used. */
/* *INDENT-OFF* */
        msr basepri, # 0
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ساكن پورٽ_FORCE_INLINE uint32_t ul_پورٽ_Raise_BASEPRI( فراغ )
{
    uint32_t ulReturn, ulNewBASEPRI = config_MAX_SYSCALL_مداخلت_ترجيح;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
        mrs ulReturn, basepri
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsid i
    #جيڪڏهن_پورو
        msr basepri, ulNewBASEPRI
        dsb
        isb
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsie i
    #جيڪڏهن_پورو
/* *INDENT-ON* */
    }

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

ساكن پورٽ_FORCE_INLINE بنياد_Type_t x_پورٽ_Is_Inside_مداخلت( فراغ )
{
    uint32_t ul_Current_مداخلت;
    بنياد_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
        mrs ul_Current_مداخلت, ipsr
    }

    إذا( ul_Current_مداخلت == 0 )
    {
        xReturn = pdFALSE;
    }
    وإلا
    {
        xReturn = pdTRUE;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

#جيڪڏهن_وصف_نه_ٿيل configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #وصف_ڪريو configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
