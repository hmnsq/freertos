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
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
#లేకపోతే
    #దోషం "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#అయితే_ముగింపు

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#నిర్వచితం_కాకపోతే configENABLE_ERRATA_837070_WORKAROUND
    #నిర్వచించు configENABLE_ERRATA_837070_WORKAROUND    0
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#నిర్వచించు పోర్టు_USING_MPU_WRAPPERS                                   1
#నిర్వచించు పోర్టు_PRIVILEGE_బిట్టు                                        ( 0x80000000UL )

#నిర్వచించు పోర్టు_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#నిర్వచించు పోర్టు_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#నిర్వచించు పోర్టు_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#నిర్వచించు పోర్టు_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#నిర్వచించు పోర్టు_MPU_RASR_TEX_S_C_B_ముసుగు                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#నిర్వచితం_కాకపోతే config_మొత్తం_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #నిర్వచించు config_మొత్తం_MPU_REGIONS    ( 8UL )
#అయితే_ముగింపు

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
#నిర్వచితం_కాకపోతే configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #నిర్వచించు configTEX_S_C_B_FLASH    ( 0x07UL )
#అయితే_ముగింపు

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM
 * region. */
#నిర్వచితం_కాకపోతే configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #నిర్వచించు configTEX_S_C_B_SRAM          ( 0x07UL )
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_దొంతర_REGION                  ( config_మొత్తం_MPU_REGIONS - 5UL )
#నిర్వచించు పోర్టు_GENERAL_PERIPHERALS_REGION    ( config_మొత్తం_MPU_REGIONS - 4UL )
#నిర్వచించు పోర్టు_UNPRIVILEGED_FLASH_REGION     ( config_మొత్తం_MPU_REGIONS - 3UL )
#నిర్వచించు పోర్టు_PRIVILEGED_FLASH_REGION       ( config_మొత్తం_MPU_REGIONS - 2UL )
#నిర్వచించు పోర్టు_PRIVILEGED_RAM_REGION         ( config_మొత్తం_MPU_REGIONS - 1UL )
#నిర్వచించు పోర్టు_మొదటి_CONFIGURABLE_REGION     ( 0UL )
#నిర్వచించు పోర్టు_చివరి_CONFIGURABLE_REGION      ( config_మొత్తం_MPU_REGIONS - 6UL )
#నిర్వచించు పోర్టు_అంకె_CONFIGURABLE_REGIONS      ( config_మొత్తం_MPU_REGIONS - 5UL )
#నిర్వచించు పోర్టు_మొత్తం_అంకె_REGIONS_లోపల_TCB      ( పోర్టు_అంకె_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

రకనిర్వచనం నిర్మాణం MPU_REGION_REGISTERS
{
    uint32_t ul_Region_పునాది_చిరునామా;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

రకనిర్వచనం నిర్మాణం MPU_REGION_SETTINGS
{
    uint32_t ul_Region_ప్రారంభం_చిరునామా;
    uint32_t ul_Region_చివర_చిరునామా;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #నిర్వచితం_కాకపోతే config_SYSTEM_CALL_దొంతర_కొలత
        #దోషం "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #అయితే_ముగింపు

    రకనిర్వచనం నిర్మాణం SYSTEM_CALL_దొంతర_INFO
    {
        uint32_t ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత ];
        uint32_t * pul_System_Call_దొంతర;
        uint32_t * pul_Task_దొంతర;
        uint32_t ul_Link_రిజిస్టరు_At_System_Call_నమోదు;
    } x_SYSTEM_CALL_దొంతర_INFO;

#అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 == 0 */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#నిర్వచించు MAX_CONTEXT_కొలత                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#నిర్వచించు పోర్టు_ACL_నమోదు_కొలత_బిట్లు             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#నిర్వచించు పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG    ( 1UL << 0UL )
#నిర్వచించు పోర్టు_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

రకనిర్వచనం నిర్మాణం MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ పోర్టు_మొత్తం_అంకె_REGIONS_లోపల_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ పోర్టు_మొత్తం_అంకె_REGIONS_లోపల_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_కొలత ];
    uint32_t ulTaskFlags;

    #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_దొంతర_INFO x_System_Call_దొంతర_Info;
        #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_కొలత / పోర్టు_ACL_నమోదు_కొలత_బిట్లు ) + 1 ];
        #అయితే_ముగింపు
    #అయితే_ముగింపు
} xMPU_SETTINGS;

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8
#నిర్వచించు పోర్టు_DONT_DISCARD      __attribute__( ( వాడిన ) )
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#నిర్వచించు పోర్టు_SVC_ప్రారంభం_SCHEDULER        100
#నిర్వచించు పోర్టు_SVC_YIELD                  101
#నిర్వచించు పోర్టు_SVC_RAISE_PRIVILEGE        102
#నిర్వచించు పోర్టు_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#నిర్వచించు పోర్టు_YIELD()    __asm అస్థిర ( "   SVC %0  \n" ::"i" ( పోర్టు_SVC_YIELD ) : "memory" )
#నిర్వచించు పోర్టు_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm అస్థిర ( "dsb" ::: "memory" );                     \
        __asm అస్థిర ( "isb" );                                  \
    }

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

/* Critical section management. */
బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ul_పోర్టు_Raise_BASEPRI()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_పోర్టు_సమితి_BASEPRI( x )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  v_పోర్టు_Raise_BASEPRI()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   v_పోర్టు_సమితి_BASEPRI( 0 )
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                      v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()                       v_పోర్టు_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) స్థిర అంతఃవరుస uint8_t uc_పోర్టు_లెక్క_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm అస్థిర ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        తిరిగి ucReturn;
    }

/* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #అయితే_ముగింపు

/* Store/clear the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

/*-----------------------------------------------------------*/

    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    ux_శిఖరం_ప్రాధాన్యత = ( 31UL - ( uint32_t ) uc_పోర్టు_లెక్క_Leading_Zeros( ( uxReadyPriorities ) ) )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#ఒకవేళ ( configASSERT_DEFINED == 1 )
    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య );
    #నిర్వచించు పోర్టు_ASSERT_IF_అంతరాయం_ప్రాధాన్యత_INVALID()    v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత()
#అయితే_ముగింపు

/* portNOP() is not required by this port. */
#నిర్వచించు పోర్టు_NOP()

#నిర్వచించు పోర్టు_INLINE              __inline

#నిర్వచితం_కాకపోతే పోర్టు_FORCE_INLINE
    #నిర్వచించు పోర్టు_FORCE_INLINE    అంతఃవరుస __attribute__( ( always_inline ) )
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

బాహ్య పునాది_Type_t xIsPrivileged( శూన్య );
బాహ్య శూన్య vResetPrivilege( శూన్య );
బాహ్య శూన్య v_పోర్టు_Switch_గమ్యం_User_బహుళకం( శూన్య );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#నిర్వచించు పోర్టు_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#నిర్వచించు పోర్టు_RAISE_PRIVILEGE()        __asm అస్థిర ( "svc %0 \n" ::"i" ( పోర్టు_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#నిర్వచించు పోర్టు_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#నిర్వచించు పోర్టు_SWITCH_గమ్యం_USER_బహుళకం()    v_పోర్టు_Switch_గమ్యం_User_బహుళకం()
/*-----------------------------------------------------------*/

బాహ్య పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#నిర్వచించు పోర్టు_IS_TASK_PRIVILEGED()    x_పోర్టు_Is_Task_Privileged()
/*-----------------------------------------------------------*/

పోర్టు_FORCE_INLINE స్థిర పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య )
{
    uint32_t ul_Current_అంతరాయం;
    పునాది_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm అస్థిర ( "mrs %0, ipsr" : "=r" ( ul_Current_అంతరాయం )::"memory" );

    ఒకవేళ( ul_Current_అంతరాయం == 0 )
    {
        xReturn = pdFALSE;
    }
    లేకపోతే
    {
        xReturn = pdTRUE;
    }

    తిరిగి xReturn;
}

/*-----------------------------------------------------------*/

పోర్టు_FORCE_INLINE స్థిర శూన్య v_పోర్టు_Raise_BASEPRI( శూన్య )
{
    uint32_t ulNewBASEPRI;

    __asm అస్థిర
    (
        "   mov %0, %1                                              \n"
        #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsid i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #అయితే_ముగింపు
        "   msr basepri, %0                                         \n"
        "   isb                                                     \n"
        "   dsb                                                     \n"
        #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsie i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #అయితే_ముగింపు
        : "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత ) : "memory"
    );
}

/*-----------------------------------------------------------*/

పోర్టు_FORCE_INLINE స్థిర uint32_t ul_పోర్టు_Raise_BASEPRI( శూన్య )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm అస్థిర
    (
        "   mrs %0, basepri                                         \n"
        "   mov %1, %2                                              \n"
        #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsid i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #అయితే_ముగింపు
        "   msr basepri, %1                                         \n"
        "   isb                                                     \n"
        "   dsb                                                     \n"
        #ఒకవేళ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
            "   cpsie i                                             \n" /* ARM Cortex-M7 r0p1 Errata 837070 workaround. */
        #అయితే_ముగింపు
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    తిరిగి ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

పోర్టు_FORCE_INLINE స్థిర శూన్య v_పోర్టు_సమితి_BASEPRI( uint32_t ul_New_ముసుగు_విలువ )
{
    __asm అస్థిర
    (
        "   msr basepri, %0 " ::"r" ( ul_New_ముసుగు_విలువ ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )

#నిర్వచితం_కాకపోతే configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #నిర్వచించు configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
    #నిర్వచితమైతే __cplusplus
        }
    #అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
