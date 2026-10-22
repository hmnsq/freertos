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

#ضمن "intrinsics.h"

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

/* Type definitions. */
#إذا __riscv_xlen == 64
    #تعریف_کړه پورټ_ډېری_TYPE           uint64_t
    #تعریف_کړه پورټ_بنسټ_TYPE            int64_t
    #تعریف_کړه پورټ_UBASE_TYPE           uint64_t
    #تعریف_کړه پورټ_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    uint64_t
#وإلاإذا __riscv_xlen == 32
    #تعریف_کړه پورټ_ډېری_TYPE           uint32_t
    #تعریف_کړه پورټ_بنسټ_TYPE            int32_t
    #تعریف_کړه پورټ_UBASE_TYPE           uint32_t
    #تعریف_کړه پورټ_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#وإلا /* if __riscv_xlen == 64 */
    #تېروتنه "Assembler did not define __riscv_xlen"
#د_که_پای /* if __riscv_xlen == 64 */

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع پورټ_بنسټ_TYPE    بنسټ_Type_t;
تعريفنوع پورټ_UBASE_TYPE   UBaseType_t;
تعريفنوع پورټ_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#تعریف_کړه پورټ_CHAR                   حرف
#تعریف_کړه پورټ_FLOAT                  عائم
#تعریف_کړه پورټ_DOUBLE                 مزدوج
#تعریف_کړه پورټ_LONG                   اوږد
#تعریف_کړه پورټ_SHORT                  لنډ

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH          ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#که_تعریف_شوی __riscv_32e
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    8         /* RV32E uses RISC-V EABI with reduced stack alignment requirements. */
#وإلا
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    16
#د_که_پای
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجي فراغ vTaskSwitchContext( فراغ );
#تعریف_کړه پورټ_YIELD()                __asm متطاير ( "ecall" );
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    0

#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                                   __disable_interrupt()
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                                    __enable_interrupt()

خارجي size_t xCriticalNesting;
#تعریف_کړه پورټ_ENTER_CRITICAL()      \
    {                             \
        پورټ_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#تعریف_کړه پورټ_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        إذا( xCriticalNesting == 0 )  \
        {                            \
            پورټ_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#إذا ( config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1 )

    #تېروتنه "configUSE_PORT_OPTIMISED_TASK_SELECTION cannot yet be used in the IAR RISC-V port, the CLZ instruction needs to be emulated."

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

#تعریف_کړه پورټ_NOP()    __asm متطاير ( " nop " )
#تعریف_کړه پورټ_INLINE              __inline

#که_نه_تعریف_شوی پورټ_FORCE_INLINE
    #تعریف_کړه پورټ_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#د_که_پای

#تعریف_کړه پورټ_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#لارښوونه diag_suppress=Pa082

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#إذا defined( config_CLINT_بنسټ_پته ) && !defined( config_MTIME_بنسټ_پته ) && ( config_CLINT_بنسټ_پته == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #تعریف_کړه config_MTIME_بنسټ_پته       ( 0 )
    #تعریف_کړه config_MTIMECMP_بنسټ_پته    ( 0 )
#وإلاإذا defined( config_CLINT_بنسټ_پته ) && !defined( config_MTIME_بنسټ_پته )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #تعریف_کړه config_MTIME_بنسټ_پته       ( ( config_CLINT_بنسټ_پته ) + 0xBFF8UL )
    #تعریف_کړه config_MTIMECMP_بنسټ_پته    ( ( config_CLINT_بنسټ_پته ) + 0x4000UL )
#وإلاإذا !defined( config_MTIME_بنسټ_پته ) || !defined( config_MTIMECMP_بنسټ_پته )
    #تېروتنه "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#د_که_پای /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
