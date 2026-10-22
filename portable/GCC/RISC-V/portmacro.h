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
#اگر __riscv_xlen == 64
    #تعریف_کرو پورٹ_ڈھیر_TYPE           uint64_t
    #تعریف_کرو پورٹ_بنیاد_TYPE            int64_t
    #تعریف_کرو پورٹ_UBASE_TYPE           uint64_t
    #تعریف_کرو پورٹ_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    uint64_t
#وگرنہ_اگر __riscv_xlen == 32
    #تعریف_کرو پورٹ_ڈھیر_TYPE           uint32_t
    #تعریف_کرو پورٹ_بنیاد_TYPE            int32_t
    #تعریف_کرو پورٹ_UBASE_TYPE           uint32_t
    #تعریف_کرو پورٹ_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#ورنہ /* if __riscv_xlen == 64 */
    #غلطی "Assembler did not define __riscv_xlen"
#اگر_ختم /* if __riscv_xlen == 64 */

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف پورٹ_بنیاد_TYPE    بنیاد_Type_t;
قسمتعریف پورٹ_UBASE_TYPE   UBaseType_t;
قسمتعریف پورٹ_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#تعریف_کرو پورٹ_CHAR                   حرف
#تعریف_کرو پورٹ_FLOAT                  اعشاری
#تعریف_کرو پورٹ_DOUBLE                 دوہرا
#تعریف_کرو پورٹ_LONG                   طویل
#تعریف_کرو پورٹ_SHORT                  مختصر

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH          ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#اگر_تعریف_شدہ __riscv_32e
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8     /* RV32E uses RISC-V EABI with reduced stack alignment requirements */
#ورنہ
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    16
#اگر_ختم
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجی خالی vTaskSwitchContext( خالی );
#تعریف_کرو پورٹ_YIELD()                __asm متلون ( "ecall" );
#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired ) \
    کرو                                           \
    {                                            \
        اگر( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        ورنہ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } جب( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB    0

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                   __asm متلون ( "csrc mstatus, 8" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                    __asm متلون ( "csrs mstatus, 8" )

خارجی size_t xCriticalNesting;
#تعریف_کرو پورٹ_ENTER_CRITICAL()      \
    {                             \
        پورٹ_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#تعریف_کرو پورٹ_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        اگر( xCriticalNesting == 0 )  \
        {                            \
            پورٹ_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#اگر_ختم

#اگر ( config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #اگر_ختم

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - __builtin_clz( uxReadyPriorities ) )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_NOP()    __asm متلون ( " nop " )
#تعریف_کرو پورٹ_INLINE              __inline

#اگر_غیر_تعریف_شدہ پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE    اندرونی __attribute__( ( always_inline ) )
#اگر_ختم

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متلون ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#اگر defined( config_CLINT_بنیاد_پتہ ) && !defined( config_MTIME_بنیاد_پتہ ) && ( config_CLINT_بنیاد_پتہ == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #تعریف_کرو config_MTIME_بنیاد_پتہ       ( 0 )
    #تعریف_کرو config_MTIMECMP_بنیاد_پتہ    ( 0 )
#وگرنہ_اگر defined( config_CLINT_بنیاد_پتہ ) && !defined( config_MTIME_بنیاد_پتہ )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #تعریف_کرو config_MTIME_بنیاد_پتہ       ( ( config_CLINT_بنیاد_پتہ ) + 0xBFF8UL )
    #تعریف_کرو config_MTIMECMP_بنیاد_پتہ    ( ( config_CLINT_بنیاد_پتہ ) + 0x4000UL )
#وگرنہ_اگر !defined( config_MTIME_بنیاد_پتہ ) || !defined( config_MTIMECMP_بنیاد_پتہ )
    #غلطی "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#اگر_ختم /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
