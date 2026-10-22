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

#ضمن "intrinsics.h"

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
#إذا __riscv_xlen == 64
    #تعریف_کن پورت_پشته_TYPE           uint64_t
    #تعریف_کن پورت_پایه_TYPE            int64_t
    #تعریف_کن پورت_UBASE_TYPE           uint64_t
    #تعریف_کن پورت_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint64_t
#وإلاإذا __riscv_xlen == 32
    #تعریف_کن پورت_پشته_TYPE           uint32_t
    #تعریف_کن پورت_پایه_TYPE            int32_t
    #تعریف_کن پورت_UBASE_TYPE           uint32_t
    #تعریف_کن پورت_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#وإلا /* if __riscv_xlen == 64 */
    #خطا "Assembler did not define __riscv_xlen"
#پایان_اگر /* if __riscv_xlen == 64 */

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع پورت_پایه_TYPE    پایه_Type_t;
تعريفنوع پورت_UBASE_TYPE   UBaseType_t;
تعريفنوع پورت_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#تعریف_کن پورت_CHAR                   حرف
#تعریف_کن پورت_FLOAT                  عائم
#تعریف_کن پورت_DOUBLE                 مزدوج
#تعریف_کن پورت_LONG                   دراز
#تعریف_کن پورت_SHORT                  کوتاه

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH          ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#اگر_تعریف_شده __riscv_32e
    #تعریف_کن پورت_BYTE_ALIGNMENT    8         /* RV32E uses RISC-V EABI with reduced stack alignment requirements. */
#وإلا
    #تعریف_کن پورت_BYTE_ALIGNMENT    16
#پایان_اگر
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجي فراغ vTaskSwitchContext( فراغ );
#تعریف_کن پورت_YIELD()                __asm متطاير ( "ecall" );
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    0

#تعریف_کن پورت_DISABLE_INTERRUPTS()                                   __disable_interrupt()
#تعریف_کن پورت_ENABLE_INTERRUPTS()                                    __enable_interrupt()

خارجي size_t xCriticalNesting;
#تعریف_کن پورت_ENTER_CRITICAL()      \
    {                             \
        پورت_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#تعریف_کن پورت_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        إذا( xCriticalNesting == 0 )  \
        {                            \
            پورت_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#إذا ( config_USE_پورت_OPTIMISED_TASK_SELECTION == 1 )

    #خطا "configUSE_PORT_OPTIMISED_TASK_SELECTION cannot yet be used in the IAR RISC-V port, the CLZ instruction needs to be emulated."

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

#تعریف_کن پورت_NOP()    __asm متطاير ( " nop " )
#تعریف_کن پورت_INLINE              __inline

#اگر_تعریف_نشده پورت_FORCE_INLINE
    #تعریف_کن پورت_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#پایان_اگر

#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#رهنمود diag_suppress=Pa082

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#إذا defined( config_CLINT_پایه_آدرس ) && !defined( config_MTIME_پایه_آدرس ) && ( config_CLINT_پایه_آدرس == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #تعریف_کن config_MTIME_پایه_آدرس       ( 0 )
    #تعریف_کن config_MTIMECMP_پایه_آدرس    ( 0 )
#وإلاإذا defined( config_CLINT_پایه_آدرس ) && !defined( config_MTIME_پایه_آدرس )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #تعریف_کن config_MTIME_پایه_آدرس       ( ( config_CLINT_پایه_آدرس ) + 0xBFF8UL )
    #تعریف_کن config_MTIMECMP_پایه_آدرس    ( ( config_CLINT_پایه_آدرس ) + 0x4000UL )
#وإلاإذا !defined( config_MTIME_پایه_آدرس ) || !defined( config_MTIMECMP_پایه_آدرس )
    #خطا "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#پایان_اگر /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
