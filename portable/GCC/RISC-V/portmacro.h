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


#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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
    #وصف_ڪريو پورٽ_ڍير_TYPE           uint64_t
    #وصف_ڪريو پورٽ_بنياد_TYPE            int64_t
    #وصف_ڪريو پورٽ_UBASE_TYPE           uint64_t
    #وصف_ڪريو پورٽ_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint64_t
#وإلاإذا __riscv_xlen == 32
    #وصف_ڪريو پورٽ_ڍير_TYPE           uint32_t
    #وصف_ڪريو پورٽ_بنياد_TYPE            int32_t
    #وصف_ڪريو پورٽ_UBASE_TYPE           uint32_t
    #وصف_ڪريو پورٽ_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#وإلا /* if __riscv_xlen == 64 */
    #غلطي "Assembler did not define __riscv_xlen"
#جيڪڏهن_پورو /* if __riscv_xlen == 64 */

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع پورٽ_بنياد_TYPE    بنياد_Type_t;
تعريفنوع پورٽ_UBASE_TYPE   UBaseType_t;
تعريفنوع پورٽ_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#وصف_ڪريو پورٽ_CHAR                   حرف
#وصف_ڪريو پورٽ_FLOAT                  عائم
#وصف_ڪريو پورٽ_DOUBLE                 مزدوج
#وصف_ڪريو پورٽ_LONG                   ڊگهو
#وصف_ڪريو پورٽ_SHORT                  ننڍو

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH          ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#جيڪڏهن_وصف_ٿيل __riscv_32e
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    8     /* RV32E uses RISC-V EABI with reduced stack alignment requirements */
#وإلا
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    16
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجي فراغ vTaskSwitchContext( فراغ );
#وصف_ڪريو پورٽ_YIELD()                __asm متطاير ( "ecall" );
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired ) \
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
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB    0

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                                   __asm متطاير ( "csrc mstatus, 8" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                                    __asm متطاير ( "csrs mstatus, 8" )

خارجي size_t xCriticalNesting;
#وصف_ڪريو پورٽ_ENTER_CRITICAL()      \
    {                             \
        پورٽ_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#وصف_ڪريو پورٽ_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        إذا( xCriticalNesting == 0 )  \
        {                            \
            پورٽ_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#إذا ( config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #جيڪڏهن_پورو

/* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/*-----------------------------------------------------------*/

    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31UL - __builtin_clz( uxReadyPriorities ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_NOP()    __asm متطاير ( " nop " )
#وصف_ڪريو پورٽ_INLINE              __inline

#جيڪڏهن_وصف_نه_ٿيل پورٽ_FORCE_INLINE
    #وصف_ڪريو پورٽ_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#إذا defined( config_CLINT_بنياد_پتو ) && !defined( config_MTIME_بنياد_پتو ) && ( config_CLINT_بنياد_پتو == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #وصف_ڪريو config_MTIME_بنياد_پتو       ( 0 )
    #وصف_ڪريو config_MTIMECMP_بنياد_پتو    ( 0 )
#وإلاإذا defined( config_CLINT_بنياد_پتو ) && !defined( config_MTIME_بنياد_پتو )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #وصف_ڪريو config_MTIME_بنياد_پتو       ( ( config_CLINT_بنياد_پتو ) + 0xBFF8UL )
    #وصف_ڪريو config_MTIMECMP_بنياد_پتو    ( ( config_CLINT_بنياد_پتو ) + 0x4000UL )
#وإلاإذا !defined( config_MTIME_بنياد_پتو ) || !defined( config_MTIMECMP_بنياد_پتو )
    #غلطي "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جيڪڏهن_پورو /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
