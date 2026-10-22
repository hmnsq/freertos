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


#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#ضمن "intrinsics.h"

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
    #تعریف_کرو پورٹ_ڈھیر_TYPE           uint64_t
    #تعریف_کرو پورٹ_ادھار_TYPE            int64_t
    #تعریف_کرو پورٹ_UBASE_TYPE           uint64_t
    #تعریف_کرو پورٹ_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    uint64_t
#وإلاإذا __riscv_xlen == 32
    #تعریف_کرو پورٹ_ڈھیر_TYPE           uint32_t
    #تعریف_کرو پورٹ_ادھار_TYPE            int32_t
    #تعریف_کرو پورٹ_UBASE_TYPE           uint32_t
    #تعریف_کرو پورٹ_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#وإلا /* if __riscv_xlen == 64 */
    #غلطی "Assembler did not define __riscv_xlen"
#جے_انت /* if __riscv_xlen == 64 */

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع پورٹ_ادھار_TYPE    ادھار_Type_t;
تعريفنوع پورٹ_UBASE_TYPE   UBaseType_t;
تعريفنوع پورٹ_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#تعریف_کرو پورٹ_CHAR                   حرف
#تعریف_کرو پورٹ_FLOAT                  عائم
#تعریف_کرو پورٹ_DOUBLE                 مزدوج
#تعریف_کرو پورٹ_LONG                   لما
#تعریف_کرو پورٹ_SHORT                  چھوٹا

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH          ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#جے_تعریف_شدہ __riscv_32e
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8         /* RV32E uses RISC-V EABI with reduced stack alignment requirements. */
#وإلا
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    16
#جے_انت
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجي فراغ vTaskSwitchContext( فراغ );
#تعریف_کرو پورٹ_YIELD()                __asm متطاير ( "ecall" );
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired ) \
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
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB    0

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                   __disable_interrupt()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                    __enable_interrupt()

خارجي size_t xCriticalNesting;
#تعریف_کرو پورٹ_ENTER_CRITICAL()      \
    {                             \
        پورٹ_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#تعریف_کرو پورٹ_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        إذا( xCriticalNesting == 0 )  \
        {                            \
            پورٹ_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#إذا ( config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1 )

    #غلطی "configUSE_PORT_OPTIMISED_TASK_SELECTION cannot yet be used in the IAR RISC-V port, the CLZ instruction needs to be emulated."

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_NOP()    __asm متطاير ( " nop " )
#تعریف_کرو پورٹ_INLINE              __inline

#جے_بنا_تعریف پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#جے_انت

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#ہدایت diag_suppress=Pa082

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#إذا defined( config_CLINT_ادھار_پتہ ) && !defined( config_MTIME_ادھار_پتہ ) && ( config_CLINT_ادھار_پتہ == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #تعریف_کرو config_MTIME_ادھار_پتہ       ( 0 )
    #تعریف_کرو config_MTIMECMP_ادھار_پتہ    ( 0 )
#وإلاإذا defined( config_CLINT_ادھار_پتہ ) && !defined( config_MTIME_ادھار_پتہ )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #تعریف_کرو config_MTIME_ادھار_پتہ       ( ( config_CLINT_ادھار_پتہ ) + 0xBFF8UL )
    #تعریف_کرو config_MTIMECMP_ادھار_پتہ    ( ( config_CLINT_ادھار_پتہ ) + 0x4000UL )
#وإلاإذا !defined( config_MTIME_ادھار_پتہ ) || !defined( config_MTIMECMP_ادھار_پتہ )
    #غلطی "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جے_انت /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
