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


#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE     طویل

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#ورنہ
    #غلطی "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#اگر_ختم

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#اگر_غیر_تعریف_شدہ configENABLE_ERRATA_837070_WORKAROUND
    #تعریف_کرو configENABLE_ERRATA_837070_WORKAROUND    0
#اگر_ختم
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#تعریف_کرو پورٹ_USING_MPU_WRAPPERS                                   1
#تعریف_کرو پورٹ_PRIVILEGE_ثنائی_ہندسہ                                        ( 0x80000000UL )

#تعریف_کرو پورٹ_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#تعریف_کرو پورٹ_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#تعریف_کرو پورٹ_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کرو پورٹ_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#تعریف_کرو پورٹ_MPU_RASR_TEX_S_C_B_نقاب                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#اگر_غیر_تعریف_شدہ config_کل_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #تعریف_کرو config_کل_MPU_REGIONS    ( 8UL )
#اگر_ختم

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
#اگر_غیر_تعریف_شدہ configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #تعریف_کرو configTEX_S_C_B_FLASH    ( 0x07UL )
#اگر_ختم

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for SRAM
 * region. */
#اگر_غیر_تعریف_شدہ configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #تعریف_کرو configTEX_S_C_B_SRAM          ( 0x07UL )
#اگر_ختم

#تعریف_کرو پورٹ_ڈھیر_REGION                  ( config_کل_MPU_REGIONS - 5UL )
#تعریف_کرو پورٹ_GENERAL_PERIPHERALS_REGION    ( config_کل_MPU_REGIONS - 4UL )
#تعریف_کرو پورٹ_UNPRIVILEGED_FLASH_REGION     ( config_کل_MPU_REGIONS - 3UL )
#تعریف_کرو پورٹ_PRIVILEGED_FLASH_REGION       ( config_کل_MPU_REGIONS - 2UL )
#تعریف_کرو پورٹ_PRIVILEGED_RAM_REGION         ( config_کل_MPU_REGIONS - 1UL )
#تعریف_کرو پورٹ_پہلا_CONFIGURABLE_REGION     ( 0UL )
#تعریف_کرو پورٹ_آخری_CONFIGURABLE_REGION      ( config_کل_MPU_REGIONS - 6UL )
#تعریف_کرو پورٹ_عدد_CONFIGURABLE_REGIONS      ( config_کل_MPU_REGIONS - 5UL )
#تعریف_کرو پورٹ_کل_عدد_REGIONS_اندر_TCB      ( پورٹ_عدد_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

قسمتعریف ساخت MPU_REGION_REGISTERS
{
    uint32_t ul_Region_بنیاد_پتہ;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

قسمتعریف ساخت MPU_REGION_SETTINGS
{
    uint32_t ul_Region_آغاز_پتہ;
    uint32_t ul_Region_انتہا_پتہ;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #اگر_غیر_تعریف_شدہ config_SYSTEM_CALL_ڈھیر_سائز
        #غلطی "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #اگر_ختم

    قسمتعریف ساخت SYSTEM_CALL_ڈھیر_INFO
    {
        uint32_t ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_سائز ];
        uint32_t * pul_System_Call_ڈھیر;
        uint32_t * pul_Task_ڈھیر;
        uint32_t ul_Link_رجسٹر_At_System_Call_اندراج;
    } x_SYSTEM_CALL_ڈھیر_INFO;

#اگر_ختم /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#تعریف_کرو MAX_CONTEXT_سائز                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#تعریف_کرو پورٹ_ACL_اندراج_سائز_بٹ             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#تعریف_کرو پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG    ( 1UL << 0UL )
#تعریف_کرو پورٹ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

قسمتعریف ساخت MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورٹ_کل_عدد_REGIONS_اندر_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ پورٹ_کل_عدد_REGIONS_اندر_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_سائز ];
    uint32_t ulTaskFlags;

    #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ڈھیر_INFO x_System_Call_ڈھیر_Info;
        #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_سائز / پورٹ_ACL_اندراج_سائز_بٹ ) + 1 ];
        #اگر_ختم
    #اگر_ختم
} xMPU_SETTINGS;

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH          ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT        8

/* Constants used with memory barrier intrinsics. */
#تعریف_کرو پورٹ_SY_بھرا_READ_WRITE    ( 15 )

/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#تعریف_کرو پورٹ_SVC_آغاز_SCHEDULER        100
#تعریف_کرو پورٹ_SVC_YIELD                  101
#تعریف_کرو پورٹ_SVC_RAISE_PRIVILEGE        102
#تعریف_کرو پورٹ_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#تعریف_کرو پورٹ_YIELD()    __asm { SVC پورٹ_SVC_YIELD }
#تعریف_کرو پورٹ_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __dsb( پورٹ_SY_بھرا_READ_WRITE );                           \
        __isb( پورٹ_SY_بھرا_READ_WRITE );                           \
    }
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متلون uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired )            \
    کرو                                                      \
    {                                                       \
        اگر( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
        }                                                   \
        ورنہ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } جب( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجی خالی v_پورٹ_Enter_Critical( خالی );
خارجی خالی v_پورٹ_Exit_Critical( خالی );

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  v_پورٹ_Raise_BASEPRI()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   v_پورٹ_سیٹ_BASEPRI( 0 )
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         ul_پورٹ_Raise_BASEPRI()
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٹ_سیٹ_BASEPRI( x )

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#اگر_ختم

#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #اگر_ختم

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )
/*-----------------------------------------------------------*/

#اگر ( configASSERT_DEFINED == 1 )
    خالی v_پورٹ_Validate_مداخلت_ترجیح( خالی );
    #تعریف_کرو پورٹ_ASSERT_IF_مداخلت_ترجیح_INVALID()    v_پورٹ_Validate_مداخلت_ترجیح()
#اگر_ختم

/* portNOP() is not required by this port. */
#تعریف_کرو پورٹ_NOP()

#تعریف_کرو پورٹ_INLINE              __inline

#اگر_غیر_تعریف_شدہ پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE    __forceinline
#اگر_ختم
/*-----------------------------------------------------------*/

خارجی بنیاد_Type_t xIsPrivileged( خالی );
خارجی خالی vResetPrivilege( خالی );
خارجی خالی v_پورٹ_Switch_مقصد_User_منوال( خالی );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#تعریف_کرو پورٹ_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#تعریف_کرو پورٹ_RAISE_PRIVILEGE()        __asm { svc پورٹ_SVC_RAISE_PRIVILEGE }

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#تعریف_کرو پورٹ_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#تعریف_کرو پورٹ_SWITCH_مقصد_USER_منوال()    v_پورٹ_Switch_مقصد_User_منوال()
/*-----------------------------------------------------------*/

خارجی بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#تعریف_کرو پورٹ_IS_TASK_PRIVILEGED()    x_پورٹ_Is_Task_Privileged()
/*-----------------------------------------------------------*/

ساکن پورٹ_FORCE_INLINE خالی v_پورٹ_سیٹ_BASEPRI( uint32_t ulBASEPRI )
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

ساکن پورٹ_FORCE_INLINE خالی v_پورٹ_Raise_BASEPRI( خالی )
{
    uint32_t ulNewBASEPRI = config_MAX_SYSCALL_مداخلت_ترجیح;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
    #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsid i
    #اگر_ختم
        msr basepri, ulNewBASEPRI
        dsb
        isb
    #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsie i
    #اگر_ختم
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ساکن پورٹ_FORCE_INLINE خالی v_پورٹ_Clear_BASEPRIFrom_ISR( خالی )
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

ساکن پورٹ_FORCE_INLINE uint32_t ul_پورٹ_Raise_BASEPRI( خالی )
{
    uint32_t ulReturn, ulNewBASEPRI = config_MAX_SYSCALL_مداخلت_ترجیح;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
        mrs ulReturn, basepri
    #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsid i
    #اگر_ختم
        msr basepri, ulNewBASEPRI
        dsb
        isb
    #اگر ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsie i
    #اگر_ختم
/* *INDENT-ON* */
    }

    واپس ulReturn;
}
/*-----------------------------------------------------------*/

ساکن پورٹ_FORCE_INLINE بنیاد_Type_t x_پورٹ_Is_Inside_مداخلت( خالی )
{
    uint32_t ul_Current_مداخلت;
    بنیاد_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
        mrs ul_Current_مداخلت, ipsr
    }

    اگر( ul_Current_مداخلت == 0 )
    {
        xReturn = pdFALSE;
    }
    ورنہ
    {
        xReturn = pdTRUE;
    }

    واپس xReturn;
}
/*-----------------------------------------------------------*/

#اگر_غیر_تعریف_شدہ configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #تعریف_کرو configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#اگر_ختم
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
