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

#అన్తర్భావ "intrinsics.h"

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
#ఒకవేళ __riscv_xlen == 64
    #నిర్వచించు పోర్టు_దొంతర_TYPE           uint64_t
    #నిర్వచించు పోర్టు_పునాది_TYPE            int64_t
    #నిర్వచించు పోర్టు_UBASE_TYPE           uint64_t
    #నిర్వచించు పోర్టు_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint64_t
#లేదావేళ __riscv_xlen == 32
    #నిర్వచించు పోర్టు_దొంతర_TYPE           uint32_t
    #నిర్వచించు పోర్టు_పునాది_TYPE            int32_t
    #నిర్వచించు పోర్టు_UBASE_TYPE           uint32_t
    #నిర్వచించు పోర్టు_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#లేకపోతే /* if __riscv_xlen == 64 */
    #దోషం "Assembler did not define __riscv_xlen"
#అయితే_ముగింపు /* if __riscv_xlen == 64 */

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం పోర్టు_పునాది_TYPE    పునాది_Type_t;
రకనిర్వచనం పోర్టు_UBASE_TYPE   UBaseType_t;
రకనిర్వచనం పోర్టు_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#నిర్వచించు పోర్టు_CHAR                   అక్షరం
#నిర్వచించు పోర్టు_FLOAT                  దశాంశం
#నిర్వచించు పోర్టు_DOUBLE                 ద్విగుణ
#నిర్వచించు పోర్టు_LONG                   దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                  పొట్టి

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH          ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచితమైతే __riscv_32e
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8         /* RV32E uses RISC-V EABI with reduced stack alignment requirements. */
#లేకపోతే
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    16
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
బాహ్య శూన్య vTaskSwitchContext( శూన్య );
#నిర్వచించు పోర్టు_YIELD()                __asm అస్థిర ( "ecall" );
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired ) \
    చేయి                                           \
    {                                            \
        ఒకవేళ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        లేకపోతే                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } అయితే( 0 )
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    0

#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                                   __disable_interrupt()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                                    __enable_interrupt()

బాహ్య size_t xCriticalNesting;
#నిర్వచించు పోర్టు_ENTER_CRITICAL()      \
    {                             \
        పోర్టు_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#నిర్వచించు పోర్టు_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        ఒకవేళ( xCriticalNesting == 0 )  \
        {                            \
            పోర్టు_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ఒకవేళ ( config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1 )

    #దోషం "configUSE_PORT_OPTIMISED_TASK_SELECTION cannot yet be used in the IAR RISC-V port, the CLZ instruction needs to be emulated."

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_NOP()    __asm అస్థిర ( " nop " )
#నిర్వచించు పోర్టు_INLINE              __inline

#నిర్వచితం_కాకపోతే పోర్టు_FORCE_INLINE
    #నిర్వచించు పోర్టు_FORCE_INLINE    అంతఃవరుస __attribute__( ( always_inline ) )
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#సూచన diag_suppress=Pa082

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#ఒకవేళ defined( config_CLINT_పునాది_చిరునామా ) && !defined( config_MTIME_పునాది_చిరునామా ) && ( config_CLINT_పునాది_చిరునామా == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #నిర్వచించు config_MTIME_పునాది_చిరునామా       ( 0 )
    #నిర్వచించు config_MTIMECMP_పునాది_చిరునామా    ( 0 )
#లేదావేళ defined( config_CLINT_పునాది_చిరునామా ) && !defined( config_MTIME_పునాది_చిరునామా )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #నిర్వచించు config_MTIME_పునాది_చిరునామా       ( ( config_CLINT_పునాది_చిరునామా ) + 0xBFF8UL )
    #నిర్వచించు config_MTIMECMP_పునాది_చిరునామా    ( ( config_CLINT_పునాది_చిరునామా ) + 0x4000UL )
#లేదావేళ !defined( config_MTIME_పునాది_చిరునామా ) || !defined( config_MTIMECMP_పునాది_చిరునామా )
    #దోషం "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#అయితే_ముగింపు /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
