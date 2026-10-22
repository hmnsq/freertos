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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
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
#ಅನ್ತರ್ಭಾವ <intrinsics.h>

/* Type definitions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ             ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ    UBaseType_t;

#ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ "configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width."
#ಆದರೆ_ಅಂತ್ಯ

/* Errata 837070 workaround must be enabled on Cortex-M7 r0p0
 * and r0p1 cores. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_ERRATA_837070_WORKAROUND
    #ವ್ಯಾಖ್ಯಾನಿಸು configENABLE_ERRATA_837070_WORKAROUND    0
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USING_MPU_WRAPPERS                                   1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್                                        ( 0x80000000UL )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_READ_WRITE                                ( 0x03UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_ONLY                      ( 0x05UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_READ_ONLY                                 ( 0x06UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE                     ( 0x01UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE_UNPRIV_READ_ONLY    ( 0x02UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_CACHEABLE_BUFFERABLE                      ( 0x07UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER                             ( 0x01UL << 28UL )

/* Location of the TEX,S,C,B bits in the MPU Region Attribute and Size
 * Register (RASR). */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_LOCATION                          ( 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_TEX_S_C_B_ಮುಖವಾಡ                              ( 0x3FUL )

/* MPU settings that can be overridden in FreeRTOSConfig.h. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಒಟ್ಟು_MPU_REGIONS
    /* Define to 8 for backward compatibility. */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_ಒಟ್ಟು_MPU_REGIONS    ( 8UL )
#ಆದರೆ_ಅಂತ್ಯ

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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configTEX_S_C_B_FLASH
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #ವ್ಯಾಖ್ಯಾನಿಸು configTEX_S_C_B_FLASH    ( 0x07UL )
#ಆದರೆ_ಅಂತ್ಯ

/* TEX, Shareable (S), Cacheable (C) and Bufferable (B) bits for RAM
 * region. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configTEX_S_C_B_SRAM
    /* Default to TEX=000, S=1, C=1, B=1 for backward compatibility. */
    #ವ್ಯಾಖ್ಯಾನಿಸು configTEX_S_C_B_SRAM          ( 0x07UL )
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_REGION                  ( config_ಒಟ್ಟು_MPU_REGIONS - 5UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GENERAL_PERIPHERALS_REGION    ( config_ಒಟ್ಟು_MPU_REGIONS - 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION     ( config_ಒಟ್ಟು_MPU_REGIONS - 3UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION       ( config_ಒಟ್ಟು_MPU_REGIONS - 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION         ( config_ಒಟ್ಟು_MPU_REGIONS - 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION     ( 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION      ( config_ಒಟ್ಟು_MPU_REGIONS - 6UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS      ( config_ಒಟ್ಟು_MPU_REGIONS - 5UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB      ( ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS + 1 ) /* Plus 1 to create space for the stack region. */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_REGION_REGISTERS
{
    uint32_t ul_Region_ತಳ_ವಿಳಾಸ;
    uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_REGION_SETTINGS
{
    uint32_t ul_Region_ಆರಂಭ_ವಿಳಾಸ;
    uint32_t ul_Region_ಕೊನೆ_ವಿಳಾಸ;
    uint32_t ulRegionPermissions;
} xMPU_REGION_SETTINGS;

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ
        #ದೋಷ "configSYSTEM_CALL_STACK_SIZE must be defined to the desired size of the system call stack in words for using MPU wrappers v2."
    #ಆದರೆ_ಅಂತ್ಯ

    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SYSTEM_CALL_ರಾಶಿ_INFO
    {
        uint32_t ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ ];
        uint32_t * pul_System_Call_ರಾಶಿ;
        uint32_t * pul_Task_ರಾಶಿ;
        uint32_t ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
    } x_SYSTEM_CALL_ರಾಶಿ_INFO;

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 == 0 */

/*
 * +---------+---------------+-----------------+-----------------+-----+
 * | s16-s31 | s0-s15, FPSCR | CONTROL, r4-r11 | PSP, r0-r3, r12 |     |
 * |         |               | EXC_RETURN      | LR, PC, xPSR    |     |
 * +---------+---------------+-----------------+-----------------+-----+
 *
 * <--------><---------------><----------------><----------------><---->
 *     16           17               10                 9           1
 */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ                    ( 53 )

/* Size of an Access Control List (ACL) entry in bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು             ( 32U )

/* Flags used for xMPU_SETTINGS.ulTaskFlags member. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG    ( 1UL << 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG         ( 1UL << 1UL )

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_SETTINGS
{
    xMPU_REGION_REGISTERS xRegion[ ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB ];
    xMPU_REGION_SETTINGS xRegionSettings[ ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS_ಒಳ_TCB ];
    uint32_t ulContext[ MAX_CONTEXT_ಗಾತ್ರ ];
    uint32_t ulTaskFlags;

    #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        x_SYSTEM_CALL_ರಾಶಿ_INFO x_System_Call_ರಾಶಿ_Info;
        #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
            uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು ) + 1 ];
        #ಆದರೆ_ಅಂತ್ಯ
    #ಆದರೆ_ಅಂತ್ಯ
} xMPU_SETTINGS;

/* Architecture specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH      ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER        100
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_YIELD                  101
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE        102
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT       103

/* Scheduler utilities. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()    __asm ಅಸ್ಥಿರ ( "   SVC %0  \n" ::"i" ( ಪೋರ್ಟ್_SVC_YIELD ) : "memory" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_WITHIN_API()                          \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್; \
        __DSB();                                        \
        __ISB();                                        \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_INT_CTRL_REG     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed04 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್    ( 1UL << 28UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired ) \
    ಮಾಡು                                           \
    {                                            \
        ಆದರೆ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();        \
            ಪೋರ್ಟ್_YIELD_WITHIN_API();              \
        }                                        \
        ಇಲ್ಲದಿದ್ದರೆ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ಆಗ( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #ಆದರೆ_ಅಂತ್ಯ

/* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - ( ( uint32_t ) __CLZ( ( uxReadyPriorities ) ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );

#ಆದರೆ ( configENABLE_ERRATA_837070_WORKAROUND == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                           \
    {                                                          \
        __disable_interrupt();                                 \
        __set_BASEPRI( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ ); \
        __DSB();                                               \
        __ISB();                                               \
        __enable_interrupt();                                  \
    }
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                           \
    {                                                          \
        __set_BASEPRI( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ ); \
        __DSB();                                               \
        __ISB();                                               \
    }
#ಆದರೆ_ಅಂತ್ಯ /* if ( configENABLE_ERRATA_837070_WORKAROUND == 1 ) */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                   __set_BASEPRI( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                      v_ಪೋರ್ಟ್_Enter_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                       v_ಪೋರ್ಟ್_Exit_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         __get_BASEPRI(); ಪೋರ್ಟ್_DISABLE_INTERRUPTS()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    __set_BASEPRI( x )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/

#ಆದರೆ ( configASSERT_DEFINED == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಅಡಚಣೆ_ಆದ್ಯತೆ_INVALID()    v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ()
#ಆದರೆ_ಅಂತ್ಯ

/* portNOP() is not required by this port. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE              __inline

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_FORCE_INLINE
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FORCE_INLINE    ಸಾಲೊಳಗೆ __attribute__( ( always_inline ) )
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/

ಪೋರ್ಟ್_FORCE_INLINE ಸ್ಥಿರ ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    uint32_t ul_Current_ಅಡಚಣೆ;
    ತಳ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm ಅಸ್ಥಿರ ( "mrs %0, ipsr" : "=r" ( ul_Current_ಅಡಚಣೆ )::"memory" );

    ಆದರೆ( ul_Current_ಅಡಚಣೆ == 0 )
    {
        xReturn = pdFALSE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}


/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ತಳ_Type_t xIsPrivileged( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vResetPrivilege( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Switch_ಗಮ್ಯ_User_ಬಹುಲಕ( ಶೂನ್ಯ );

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_PRIVILEGED()          xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RAISE_PRIVILEGE()        __asm ಅಸ್ಥಿರ ( "svc %0 \n" ::"i" ( ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE ) : "memory" );

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_PRIVILEGE()        vResetPrivilege()

/**
 * @brief Make a task unprivileged.
 *
 * It must be called from privileged tasks only. Calling it from unprivileged
 * task will result in a memory protection fault.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SWITCH_ಗಮ್ಯ_USER_ಬಹುಲಕ()    v_ಪೋರ್ಟ್_Switch_ಗಮ್ಯ_User_ಬಹುಲಕ()
/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ );

/**
 * @brief Checks whether or not the calling task is privileged.
 *
 * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_TASK_PRIVILEGED()    x_ಪೋರ್ಟ್_Is_Task_Privileged()
/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY
    #warning "configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY is not defined. We recommend defining it to 1 in FreeRTOSConfig.h for better security. www.FreeRTOS.org/FreeRTOS-V10.3.x.html"
    #ವ್ಯಾಖ್ಯಾನಿಸು configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY    0
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#ಸೂಚನೆ diag_suppress=Pe191
#ಸೂಚನೆ diag_suppress=Pa082
#ಸೂಚನೆ diag_suppress=Be006
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
