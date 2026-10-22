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


#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

#अन्तर्भाव "intrinsics.h"

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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
#यदि __riscv_xlen == 64
    #परिभाषय पत्तनम्_राशिः_TYPE           uint64_t
    #परिभाषय पत्तनम्_आधारः_TYPE            int64_t
    #परिभाषय पत्तनम्_UBASE_TYPE           uint64_t
    #परिभाषय पत्तनम्_MAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #परिभाषय पत्तनम्_POINTER_आकार_TYPE    uint64_t
#नोचेद्यदि __riscv_xlen == 32
    #परिभाषय पत्तनम्_राशिः_TYPE           uint32_t
    #परिभाषय पत्तनम्_आधारः_TYPE            int32_t
    #परिभाषय पत्तनम्_UBASE_TYPE           uint32_t
    #परिभाषय पत्तनम्_MAX_DELAY            ( TickType_t ) 0xffffffffUL
#अन्यथा /* if __riscv_xlen == 64 */
    #दोषः "Assembler did not define __riscv_xlen"
#यदि_अन्तः /* if __riscv_xlen == 64 */

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश पत्तनम्_आधारः_TYPE    आधारः_Type_t;
प्रकारनिर्देश पत्तनम्_UBASE_TYPE   UBaseType_t;
प्रकारनिर्देश पत्तनम्_UBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#परिभाषय पत्तनम्_CHAR                   वर्ण
#परिभाषय पत्तनम्_FLOAT                  भिन्न
#परिभाषय पत्तनम्_DOUBLE                 द्विगुण
#परिभाषय पत्तनम्_LONG                   दीर्घ
#परिभाषय पत्तनम्_SHORT                  ह्रस्व

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH          ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#यदि_परिभाषितम् __riscv_32e
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    8         /* RV32E uses RISC-V EABI with reduced stack alignment requirements. */
#अन्यथा
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    16
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
बाह्य शून्य vTaskSwitchContext( शून्य );
#परिभाषय पत्तनम्_YIELD()                __asm चञ्चल ( "ecall" );
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired ) \
    कुरु                                           \
    {                                            \
        यदि( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } यावत्( 0 )
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB    0

#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                                   __disable_interrupt()
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                                    __enable_interrupt()

बाह्य size_t xCriticalNesting;
#परिभाषय पत्तनम्_ENTER_CRITICAL()      \
    {                             \
        पत्तनम्_DISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#परिभाषय पत्तनम्_EXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        यदि( xCriticalNesting == 0 )  \
        {                            \
            पत्तनम्_ENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#यदि ( config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1 )

    #दोषः "configUSE_PORT_OPTIMISED_TASK_SELECTION cannot yet be used in the IAR RISC-V port, the CLZ instruction needs to be emulated."

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/*-----------------------------------------------------------*/

#परिभाषय पत्तनम्_NOP()    __asm चञ्चल ( " nop " )
#परिभाषय पत्तनम्_INLINE              __inline

#यदि_अपरिभाषितम् पत्तनम्_FORCE_INLINE
    #परिभाषय पत्तनम्_FORCE_INLINE    अन्तःस्थ __attribute__( ( always_inline ) )
#यदि_अन्तः

#परिभाषय पत्तनम्_स्मृतिः_BARRIER()    __asm चञ्चल ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#निर्देशः diag_suppress=Pa082

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#यदि defined( config_CLINT_आधारः_स्थानाङ्कः ) && !defined( config_MTIME_आधारः_स्थानाङ्कः ) && ( config_CLINT_आधारः_स्थानाङ्कः == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #परिभाषय config_MTIME_आधारः_स्थानाङ्कः       ( 0 )
    #परिभाषय config_MTIMECMP_आधारः_स्थानाङ्कः    ( 0 )
#नोचेद्यदि defined( config_CLINT_आधारः_स्थानाङ्कः ) && !defined( config_MTIME_आधारः_स्थानाङ्कः )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #परिभाषय config_MTIME_आधारः_स्थानाङ्कः       ( ( config_CLINT_आधारः_स्थानाङ्कः ) + 0xBFF8UL )
    #परिभाषय config_MTIMECMP_आधारः_स्थानाङ्कः    ( ( config_CLINT_आधारः_स्थानाङ्कः ) + 0x4000UL )
#नोचेद्यदि !defined( config_MTIME_आधारः_स्थानाङ्कः ) || !defined( config_MTIMECMP_आधारः_स्थानाङ्कः )
    #दोषः "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#यदि_अन्तः /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
