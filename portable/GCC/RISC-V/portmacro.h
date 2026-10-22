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


#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    ബാഹ്യ "C" {
#endif
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
#എങ്കിൽ __riscv_xlen == 64
    #define port_അട്ടി_TYPE           uint64_t
    #define portBASE_TYPE            int64_t
    #define portUBASE_TYPE           uint64_t
    #define portMAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #define portPOINTER_SIZE_TYPE    uint64_t
#അല്ലെങ്കിലെങ്കിൽ __riscv_xlen == 32
    #define port_അട്ടി_TYPE           uint32_t
    #define portBASE_TYPE            int32_t
    #define portUBASE_TYPE           uint32_t
    #define portMAX_DELAY            ( TickType_t ) 0xffffffffUL
#അല്ലെങ്കിൽ /* if __riscv_xlen == 64 */
    #error "Assembler did not define __riscv_xlen"
#endif /* if __riscv_xlen == 64 */

തരനിർവചനം port_അട്ടി_TYPE   അട്ടി_Type_t;
തരനിർവചനം portBASE_TYPE    BaseType_t;
തരനിർവചനം portUBASE_TYPE   UBaseType_t;
തരനിർവചനം portUBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#define portCHAR                   അക്ഷരം
#define portFLOAT                  ദശാംശം
#define portDOUBLE                 ഇരട്ട
#define portLONG                   long
#define portSHORT                  short

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#define portTICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_അട്ടി_GROWTH          ( -1 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#ifdef __riscv_32e
    #define portBYTE_ALIGNMENT    8     /* RV32E uses RISC-V EABI with reduced stack alignment requirements */
#അല്ലെങ്കിൽ
    #define portBYTE_ALIGNMENT    16
#endif
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
ബാഹ്യ ശൂന്യം vTaskSwitchContext( ശൂന്യം );
#define portYIELD()                __asm അസ്ഥിര ( "ecall" );
#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    ചെയ്യുക                                           \
    {                                            \
        എങ്കിൽ( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        അല്ലെങ്കിൽ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ആകുമ്പോൾ( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portCRITICAL_NESTING_IN_TCB    0

#define portDISABLE_INTERRUPTS()                                   __asm അസ്ഥിര ( "csrc mstatus, 8" )
#define portENABLE_INTERRUPTS()                                    __asm അസ്ഥിര ( "csrs mstatus, 8" )

ബാഹ്യ size_t xCriticalNesting;
#define portENTER_CRITICAL()      \
    {                             \
        portDISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#define portEXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        എങ്കിൽ( xCriticalNesting == 0 )  \
        {                            \
            portENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#എങ്കിൽ ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

/* Check the configuration. */
    #എങ്കിൽ ( configMAX_PRIORITIES > 32 )
        #error "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #endif

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_മുകൾ_Priority, uxReadyPriorities )    ux_മുകൾ_Priority = ( 31UL - __builtin_clz( uxReadyPriorities ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )

/*-----------------------------------------------------------*/

#define portNOP()    __asm അസ്ഥിര ( " nop " )
#define portINLINE              __inline

#ifndef portFORCE_INLINE
    #define portFORCE_INLINE    വരിയിൽ __attribute__( ( always_inline ) )
#endif

#define portMEMORY_BARRIER()    __asm അസ്ഥിര ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#എങ്കിൽ defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #define configMTIME_BASE_ADDRESS       ( 0 )
    #define configMTIMECMP_BASE_ADDRESS    ( 0 )
#അല്ലെങ്കിലെങ്കിൽ defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #define configMTIME_BASE_ADDRESS       ( ( configCLINT_BASE_ADDRESS ) + 0xBFF8UL )
    #define configMTIMECMP_BASE_ADDRESS    ( ( configCLINT_BASE_ADDRESS ) + 0x4000UL )
#അല്ലെങ്കിലെങ്കിൽ !defined( configMTIME_BASE_ADDRESS ) || !defined( configMTIMECMP_BASE_ADDRESS )
    #error "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#endif /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
