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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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
#ਅਨ੍ਤਰ੍ਭਾਵ <intrinsics.h>

/* Type definitions. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ             ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ    UBaseType_t;

#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#ਜੇ_ਅੰਤ

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_ERRATA_837070_WORKAROUND
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configENABLE_ERRATA_837070_WORKAROUND    0
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS                                   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ                                        ( 0x80000000UL )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_TEX_S_C_B_ਨਕਾਬ                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਕੁੱਲ_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਕੁੱਲ_MPU_REGIONS    ( 8UL )
#ਜੇ_ਅੰਤ

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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configTEX_S_C_B_FLASH    ( 0x07UL )
#ਜੇ_ਅੰਤ

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM
 * region. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configTEX_S_C_B_SRAM          ( 0x07UL )
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_REGION                  ( config_ਕੁੱਲ_MPU_REGIONS - 5UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GENERAL_PERIPHERALS_REGION    ( config_ਕੁੱਲ_MPU_REGIONS - 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION     ( config_ਕੁੱਲ_MPU_REGIONS - 3UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_FLASH_REGION       ( config_ਕੁੱਲ_MPU_REGIONS - 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_RAM_REGION         ( config_ਕੁੱਲ_MPU_REGIONS - 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION     ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION      ( config_ਕੁੱਲ_MPU_REGIONS - 6UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS      ( config_ਕੁੱਲ_MPU_REGIONS - 5UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB      ( ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_REGION_REGISTERS
{
    uint32_t ul_Region_ਅਧਾਰ_ਪਤਾ;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_REGION_SETTINGS
{
    uint32_t ul_Region_ਸ਼ੁਰੂ_ਪਤਾ;
    uint32_t ul_Region_ਸਿਰਾ_ਪਤਾ;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ
        #ਗਲਤੀ "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #ਜੇ_ਅੰਤ

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SYSTEM_CALL_ਢੇਰ_INFO
    {
        uint32_t ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ ];
        uint32_t * pul_System_Call_ਢੇਰ;
        uint32_t * pul_Task_ਢੇਰ;
        uint32_t ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
    } x_SYSTEM_CALL_ਢੇਰ_INFO;

#ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 == 0 */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG    ( 1UL << 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS_ਵਿੱਚ_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_ਮਾਪ ];
    uint32_t ulTaskFlags;

    #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ਢੇਰ_INFO x_System_Call_ਢੇਰ_Info;
        #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ ) + 1 ];
        #ਜੇ_ਅੰਤ
    #ਜੇ_ਅੰਤ
} xMPU_SETTINGS;

/* Architecture specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER        100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_YIELD                  101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_RAISE_PRIVILEGE        102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    __asm ਅਸਥਿਰ ( "   SVC %0  \n" ::"i" ( ਪੋਰਟ_SVC_YIELD ) : "memory" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ; \
        __DSB();                                        \
        __ISB();                                        \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_INT_CTRL_REG     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed04 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 1UL << 28UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired ) \
    ਕਰੋ                                           \
    {                                            \
        ਜੇ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();        \
            ਪੋਰਟ_YIELD_WITHIN_API();              \
        }                                        \
        ਨਹੀਂਤਾਂ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ਜਦੋਂ( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

#ਜੇ ( config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #ਜੇ_ਅੰਤ

/* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

/*-----------------------------------------------------------*/

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31UL - ( ( uint32_t ) __CLZ( ( uxReadyPriorities ) ) ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );

#ਜੇ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                           \
    {                                                          \
        __disable_interrupt();                                 \
        __set_BASEPRI( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ); \
        __DSB();                                               \
        __ISB();                                               \
        __enable_interrupt();                                  \
    }
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                           \
    {                                                          \
        __set_BASEPRI( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ); \
        __DSB();                                               \
        __ISB();                                               \
    }
#ਜੇ_ਅੰਤ /* if ( configENABLE_ERRATA_837070_WORKAROUND == 1 ) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                   __set_BASEPRI( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                      v_ਪੋਰਟ_Enter_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                       v_ਪੋਰਟ_Exit_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         __get_BASEPRI(); ਪੋਰਟ_DISABLE_INTERRUPTS()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    __set_BASEPRI( x )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
/*-----------------------------------------------------------*/

#ਜੇ ( configASSERT_DEFINED == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਰੁਕਾਵਟ_ਤਰਜੀਹ_INVALID()    v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ()
#ਜੇ_ਅੰਤ

/* portNOP() is not required by this port. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE              __inline

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_FORCE_INLINE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FORCE_INLINE    ਸਤਰਅੰਦਰ __attribute__( ( always_inline ) )
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

ਪੋਰਟ_FORCE_INLINE ਸਥਿਰ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    uint32_t ul_Current_ਰੁਕਾਵਟ;
    ਅਧਾਰ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm ਅਸਥਿਰ ( "mrs %0, ipsr" : "=r" ( ul_Current_ਰੁਕਾਵਟ )::"memory" );

    ਜੇ( ul_Current_ਰੁਕਾਵਟ == 0 )
    {
        xReturn = pdFALSE;
    }
    ਨਹੀਂਤਾਂ
    {
        xReturn = pdTRUE;
    }

    ਵਾਪਸ xReturn;
}


/*-----------------------------------------------------------*/

ਬਾਹਰੀ ਅਧਾਰ_Type_t xIsPrivileged( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ vResetPrivilege( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Switch_ਮੰਜ਼ਿਲ_User_ਬਹੁਲਕ( ਖਾਲੀ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RAISE_PRIVILEGE()        __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SWITCH_ਮੰਜ਼ਿਲ_USER_ਬਹੁਲਕ()    v_ਪੋਰਟ_Switch_ਮੰਜ਼ਿਲ_User_ਬਹੁਲਕ()
/*-----------------------------------------------------------*/

ਬਾਹਰੀ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_TASK_PRIVILEGED()    x_ਪੋਰਟ_Is_Task_Privileged()
/*-----------------------------------------------------------*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#ਹਦਾਇਤ diag_suppress=Pe191
#ਹਦਾਇਤ diag_suppress=Pa082
#ਹਦਾਇਤ diag_suppress=Be006
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
