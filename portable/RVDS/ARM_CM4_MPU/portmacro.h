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


#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #خطا "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#پایان_اگر

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#اگر_تعریف_نشده configENABLE_ERRATA_837070_WORKAROUND
    #تعریف_کن configENABLE_ERRATA_837070_WORKAROUND    0
#پایان_اگر
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#تعریف_کن پورت_USING_MPU_WRAPPERS                                   1
#تعریف_کن پورت_PRIVILEGE_بیت                                        ( 0x80000000UL )

#تعریف_کن پورت_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#تعریف_کن پورت_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#تعریف_کن پورت_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#تعریف_کن پورت_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#تعریف_کن پورت_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کن پورت_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#تعریف_کن پورت_MPU_RASR_TEX_S_C_B_ماسک                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#اگر_تعریف_نشده config_مجموع_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #تعریف_کن config_مجموع_MPU_REGIONS    ( 8UL )
#پایان_اگر

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
#اگر_تعریف_نشده configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #تعریف_کن configTEX_S_C_B_FLASH    ( 0x07UL )
#پایان_اگر

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for SRAM
 * region. */
#اگر_تعریف_نشده configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #تعریف_کن configTEX_S_C_B_SRAM          ( 0x07UL )
#پایان_اگر

#تعریف_کن پورت_پشته_REGION                  ( config_مجموع_MPU_REGIONS - 5UL )
#تعریف_کن پورت_GENERAL_PERIPHERALS_REGION    ( config_مجموع_MPU_REGIONS - 4UL )
#تعریف_کن پورت_UNPRIVILEGED_FLASH_REGION     ( config_مجموع_MPU_REGIONS - 3UL )
#تعریف_کن پورت_PRIVILEGED_FLASH_REGION       ( config_مجموع_MPU_REGIONS - 2UL )
#تعریف_کن پورت_PRIVILEGED_RAM_REGION         ( config_مجموع_MPU_REGIONS - 1UL )
#تعریف_کن پورت_اولی_CONFIGURABLE_REGION     ( 0UL )
#تعریف_کن پورت_آخرین_CONFIGURABLE_REGION      ( config_مجموع_MPU_REGIONS - 6UL )
#تعریف_کن پورت_رقم_CONFIGURABLE_REGIONS      ( config_مجموع_MPU_REGIONS - 5UL )
#تعریف_کن پورت_مجموع_رقم_REGIONS_درون_TCB      ( پورت_رقم_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

تعريفنوع بنية MPU_REGION_REGISTERS
{
    uint32_t ul_Region_پایه_آدرس;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

تعريفنوع بنية MPU_REGION_SETTINGS
{
    uint32_t ul_Region_شروع_آدرس;
    uint32_t ul_Region_انتها_آدرس;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #اگر_تعریف_نشده config_SYSTEM_CALL_پشته_اندازه
        #خطا "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #پایان_اگر

    تعريفنوع بنية SYSTEM_CALL_پشته_INFO
    {
        uint32_t ul_System_Call_پشته_میانگیر[ config_SYSTEM_CALL_پشته_اندازه ];
        uint32_t * pul_System_Call_پشته;
        uint32_t * pul_Task_پشته;
        uint32_t ul_Link_ثبات_At_System_Call_مدخل;
    } x_SYSTEM_CALL_پشته_INFO;

#پایان_اگر /* #if ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#تعریف_کن MAX_CONTEXT_اندازه                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#تعریف_کن پورت_ACL_مدخل_اندازه_بیتها             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#تعریف_کن پورت_پشته_قاب_HAS_PADDING_FLAG    ( 1UL << 0UL )
#تعریف_کن پورت_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

تعريفنوع بنية MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورت_مجموع_رقم_REGIONS_درون_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ پورت_مجموع_رقم_REGIONS_درون_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_اندازه ];
    uint32_t ulTaskFlags;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_پشته_INFO x_System_Call_پشته_Info;
        #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورت_ACL_مدخل_اندازه_بیتها ) + 1 ];
        #پایان_اگر
    #پایان_اگر
} xMPU_SETTINGS;

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH          ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT        8

/* Constants used with memory barrier intrinsics. */
#تعریف_کن پورت_SY_پر_READ_WRITE    ( 15 )

/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#تعریف_کن پورت_SVC_شروع_SCHEDULER        100
#تعریف_کن پورت_SVC_YIELD                  101
#تعریف_کن پورت_SVC_RAISE_PRIVILEGE        102
#تعریف_کن پورت_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#تعریف_کن پورت_YIELD()    __asm { SVC پورت_SVC_YIELD }
#تعریف_کن پورت_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __dsb( پورت_SY_پر_READ_WRITE );                           \
        __isb( پورت_SY_پر_READ_WRITE );                           \
    }
/*-----------------------------------------------------------*/

#تعریف_کن پورت_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کن پورت_NVIC_PENDSVSET_بیت    ( 1UL << 28UL )
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورت_Enter_Critical( فراغ );
خارجي فراغ v_پورت_Exit_Critical( فراغ );

#تعریف_کن پورت_DISABLE_INTERRUPTS()                  v_پورت_Raise_BASEPRI()
#تعریف_کن پورت_ENABLE_INTERRUPTS()                   v_پورت_مجموعه_BASEPRI( 0 )
#تعریف_کن پورت_ENTER_CRITICAL()                      v_پورت_Enter_Critical()
#تعریف_کن پورت_EXIT_CRITICAL()                       v_پورت_Exit_Critical()
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ul_پورت_Raise_BASEPRI()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_پورت_مجموعه_BASEPRI( x )

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
#پایان_اگر

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #پایان_اگر

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورت_Validate_وقفه_اولویت( فراغ );
    #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    v_پورت_Validate_وقفه_اولویت()
#پایان_اگر

/* portNOP() is not required by this port. */
#تعریف_کن پورت_NOP()

#تعریف_کن پورت_INLINE              __inline

#اگر_تعریف_نشده پورت_FORCE_INLINE
    #تعریف_کن پورت_FORCE_INLINE    __forceinline
#پایان_اگر
/*-----------------------------------------------------------*/

خارجي پایه_Type_t xIsPrivileged( فراغ );
خارجي فراغ vResetPrivilege( فراغ );
خارجي فراغ v_پورت_Switch_مقصد_User_نما( فراغ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#تعریف_کن پورت_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#تعریف_کن پورت_RAISE_PRIVILEGE()        __asm { svc پورت_SVC_RAISE_PRIVILEGE }

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#تعریف_کن پورت_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#تعریف_کن پورت_SWITCH_مقصد_USER_نما()    v_پورت_Switch_مقصد_User_نما()
/*-----------------------------------------------------------*/

خارجي پایه_Type_t x_پورت_Is_Task_Privileged( فراغ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#تعریف_کن پورت_IS_TASK_PRIVILEGED()    x_پورت_Is_Task_Privileged()
/*-----------------------------------------------------------*/

ساكن پورت_FORCE_INLINE فراغ v_پورت_مجموعه_BASEPRI( uint32_t ulBASEPRI )
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

ساكن پورت_FORCE_INLINE فراغ v_پورت_Raise_BASEPRI( فراغ )
{
    uint32_t ulNewBASEPRI = config_MAX_SYSCALL_وقفه_اولویت;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsid i
    #پایان_اگر
        msr basepri, ulNewBASEPRI
        dsb
        isb
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsie i
    #پایان_اگر
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ساكن پورت_FORCE_INLINE فراغ v_پورت_Clear_BASEPRIFrom_ISR( فراغ )
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

ساكن پورت_FORCE_INLINE uint32_t ul_پورت_Raise_BASEPRI( فراغ )
{
    uint32_t ulReturn, ulNewBASEPRI = config_MAX_SYSCALL_وقفه_اولویت;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
        mrs ulReturn, basepri
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsid i
    #پایان_اگر
        msr basepri, ulNewBASEPRI
        dsb
        isb
    #إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
        cpsie i
    #پایان_اگر
/* *INDENT-ON* */
    }

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

ساكن پورت_FORCE_INLINE پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ )
{
    uint32_t ul_Current_وقفه;
    پایه_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
        mrs ul_Current_وقفه, ipsr
    }

    إذا( ul_Current_وقفه == 0 )
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

#اگر_تعریف_نشده configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #تعریف_کن configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#پایان_اگر
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
