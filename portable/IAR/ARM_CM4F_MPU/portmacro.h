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


#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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

/* IAR includes. */
#ضمن <intrinsics.h>

/* Type definitions. */
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #تېروتنه "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#د_که_پای

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#که_نه_تعریف_شوی configENABLE_ERRATA_837070_WORKAROUND
    #تعریف_کړه configENABLE_ERRATA_837070_WORKAROUND    0
#د_که_پای
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#تعریف_کړه پورټ_USING_MPU_WRAPPERS                                   1
#تعریف_کړه پورټ_PRIVILEGE_بټ                                        ( 0x80000000UL )

#تعریف_کړه پورټ_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#تعریف_کړه پورټ_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#تعریف_کړه پورټ_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#تعریف_کړه پورټ_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#تعریف_کړه پورټ_MPU_RASR_TEX_S_C_B_ماسک                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#که_نه_تعریف_شوی config_ټول_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #تعریف_کړه config_ټول_MPU_REGIONS    ( 8UL )
#د_که_پای

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

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for flash
 * region. */
#که_نه_تعریف_شوی configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #تعریف_کړه configTEX_S_C_B_FLASH    ( 0x07UL )
#د_که_پای

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM
 * region. */
#که_نه_تعریف_شوی configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #تعریف_کړه configTEX_S_C_B_SRAM          ( 0x07UL )
#د_که_پای

#تعریف_کړه پورټ_ډېری_REGION                  ( config_ټول_MPU_REGIONS - 5UL )
#تعریف_کړه پورټ_GENERAL_PERIPHERALS_REGION    ( config_ټول_MPU_REGIONS - 4UL )
#تعریف_کړه پورټ_UNPRIVILEGED_FLASH_REGION     ( config_ټول_MPU_REGIONS - 3UL )
#تعریف_کړه پورټ_PRIVILEGED_FLASH_REGION       ( config_ټول_MPU_REGIONS - 2UL )
#تعریف_کړه پورټ_PRIVILEGED_RAM_REGION         ( config_ټول_MPU_REGIONS - 1UL )
#تعریف_کړه پورټ_لومړی_CONFIGURABLE_REGION     ( 0UL )
#تعریف_کړه پورټ_وروستی_CONFIGURABLE_REGION      ( config_ټول_MPU_REGIONS - 6UL )
#تعریف_کړه پورټ_عدد_CONFIGURABLE_REGIONS      ( config_ټول_MPU_REGIONS - 5UL )
#تعریف_کړه پورټ_ټول_عدد_REGIONS_دننه_TCB      ( پورټ_عدد_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

تعريفنوع بنية MPU_REGION_REGISTERS
{
    uint32_t ul_Region_بنسټ_پته;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

تعريفنوع بنية MPU_REGION_SETTINGS
{
    uint32_t ul_Region_پیل_پته;
    uint32_t ul_Region_پای_ټکی_پته;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #که_نه_تعریف_شوی config_SYSTEM_CALL_ډېری_اندازه
        #تېروتنه "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #د_که_پای

    تعريفنوع بنية SYSTEM_CALL_ډېری_INFO
    {
        uint32_t ul_System_Call_ډېری_بفر[ config_SYSTEM_CALL_ډېری_اندازه ];
        uint32_t * pul_System_Call_ډېری;
        uint32_t * pul_Task_ډېری;
        uint32_t ul_Link_ثبتوونکی_At_System_Call_ثبت;
    } x_SYSTEM_CALL_ډېری_INFO;

#د_که_پای /* configUSE_MPU_WRAPPERS_V1 == 0 */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#تعریف_کړه MAX_CONTEXT_اندازه                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#تعریف_کړه پورټ_ACL_ثبت_اندازه_بټونه             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#تعریف_کړه پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG    ( 1UL << 0UL )
#تعریف_کړه پورټ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

تعريفنوع بنية MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ پورټ_ټول_عدد_REGIONS_دننه_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ پورټ_ټول_عدد_REGIONS_دننه_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_اندازه ];
    uint32_t ulTaskFlags;

    #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ډېری_INFO x_System_Call_ډېری_Info;
        #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه / پورټ_ACL_ثبت_اندازه_بټونه ) + 1 ];
        #د_که_پای
    #د_که_پای
} xMPU_SETTINGS;

/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#تعریف_کړه پورټ_SVC_پیل_SCHEDULER        100
#تعریف_کړه پورټ_SVC_YIELD                  101
#تعریف_کړه پورټ_SVC_RAISE_PRIVILEGE        102
#تعریف_کړه پورټ_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#تعریف_کړه پورټ_YIELD()    __asm متطاير ( "   SVC %0  \n" ::"i" ( پورټ_SVC_YIELD ) : "memory" )
#تعریف_کړه پورټ_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ; \
        __DSB();                                        \
        __ISB();                                        \
    }

#تعریف_کړه پورټ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کړه پورټ_NVIC_PENDSVSET_بټ    ( 1UL << 28UL )
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورټ_YIELD_WITHIN_API();              \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
#د_که_پای

#إذا ( config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #د_که_پای

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31UL - ( ( uint32_t ) __CLZ( ( uxReadyPriorities ) ) ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورټ_Enter_Critical( فراغ );
خارجي فراغ v_پورټ_Exit_Critical( فراغ );

#إذا ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                           \
    {                                                          \
        __disable_interrupt();                                 \
        __set_BASEPRI( config_MAX_SYSCALL_مداخله_لومړیتوب ); \
        __DSB();                                               \
        __ISB();                                               \
        __enable_interrupt();                                  \
    }
#وإلا
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                           \
    {                                                          \
        __set_BASEPRI( config_MAX_SYSCALL_مداخله_لومړیتوب ); \
        __DSB();                                               \
        __ISB();                                               \
    }
#د_که_پای /* if ( configENABLE_ERRATA_837070_WORKAROUND == 1 ) */

#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                   __set_BASEPRI( 0 )
#تعریف_کړه پورټ_ENTER_CRITICAL()                      v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()                       v_پورټ_Exit_Critical()
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         __get_BASEPRI(); پورټ_DISABLE_INTERRUPTS()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    __set_BASEPRI( x )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ );
    #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    v_پورټ_Validate_مداخله_لومړیتوب()
#د_که_پای

/* portNOP() is not required by this port. */
#تعریف_کړه پورټ_NOP()

#تعریف_کړه پورټ_INLINE              __inline

#که_نه_تعریف_شوی پورټ_FORCE_INLINE
    #تعریف_کړه پورټ_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#د_که_پای

/*-----------------------------------------------------------*/

پورټ_FORCE_INLINE ساكن بنسټ_Type_t x_پورټ_Is_Inside_مداخله( فراغ )
{
    uint32_t ul_Current_مداخله;
    بنسټ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_مداخله )::"memory" );

    إذا( ul_Current_مداخله == 0 )
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

خارجي بنسټ_Type_t xIsPrivileged( فراغ );
خارجي فراغ vResetPrivilege( فراغ );
خارجي فراغ v_پورټ_Switch_منزل_User_ډېرپېښ( فراغ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#تعریف_کړه پورټ_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#تعریف_کړه پورټ_RAISE_PRIVILEGE()        __asm متطاير ( "svc %0 \n" ::"i" ( پورټ_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#تعریف_کړه پورټ_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#تعریف_کړه پورټ_SWITCH_منزل_USER_ډېرپېښ()    v_پورټ_Switch_منزل_User_ډېرپېښ()
/*-----------------------------------------------------------*/

خارجي بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#تعریف_کړه پورټ_IS_TASK_PRIVILEGED()    x_پورټ_Is_Task_Privileged()
/*-----------------------------------------------------------*/

#که_نه_تعریف_شوی configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #تعریف_کړه configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#د_که_پای
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#لارښوونه diag_suppress=Pe191
#لارښوونه diag_suppress=Pa082
#لارښوونه diag_suppress=Be006
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
