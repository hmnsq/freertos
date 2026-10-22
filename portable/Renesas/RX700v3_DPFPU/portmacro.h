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
    বাহ্য "C" {
#endif
/* *INDENT-ON* */

/* Hardware specifics. */
    #অন্তর্ভাব <machine.h>

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
    #ifndef configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H
        #define configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H 0
    #endif

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or undefined) then each task will
 * be created without a DPFPU context, and a task must call vTaskUsesDPFPU() before
 * making use of any DPFPU registers.  If configUSE_TASK_DPFPU_SUPPORT is set to 2 then
 * tasks are created with a DPFPU context by default, and calling vTaskUsesDPFPU() has
 * no effect.  If configUSE_TASK_DPFPU_SUPPORT is set to 0 then tasks never take care
 * of any DPFPU context (even if DPFPU registers are used). */
    #ifndef configUSE_TASK_DPFPU_SUPPORT
        #define configUSE_TASK_DPFPU_SUPPORT 1
    #endif

/*-----------------------------------------------------------*/

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
    #define portCHAR          বর্ণ
    #define portFLOAT         ভিন্ন
    #define portDOUBLE        দ্বিগুণ
    #define portLONG          long
    #define portSHORT         short
    #define port_স্তূপ_TYPE    uint32_t
    #define portBASE_TYPE     long

    প্রকারনির্দেশ port_স্তূপ_TYPE   স্তূপ_Type_t;
    প্রকারনির্দেশ long             BaseType_t;
    প্রকারনির্দেশ unsigned long    UBaseType_t;

    #যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        প্রকারনির্দেশ uint16_t     TickType_t;
        #define portMAX_DELAY              ( TickType_t ) 0xffff
    #নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        প্রকারনির্দেশ uint32_t     TickType_t;
        #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #define portTICK_TYPE_IS_ATOMIC    1
    #অন্যথা
        #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #endif

/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #define portBYTE_ALIGNMENT    8     /* Could make four, according to manual. */
    #define port_স্তূপ_GROWTH      -1
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #define portNOP()    nop()

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) *portITU_SWINTR;"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0).  Don't rely on the assembler to select a register, so instead
 * save and restore clobbered registers manually. */
    #pragma inline_asm vPortYield
    স্থির শূন্য vPortYield( শূন্য )
    {
    #ifndef __CDT_PARSER__
        /* Save clobbered register - may not actually be necessary if inline asm
         * functions are considered to use the same rules as function calls by the
         * compiler. */
        ঠেলো_2.L R5
        /* Set ITU SWINTR. */
        MOV.L # 000872E0H, R5
        MOV.B # 1, [ R5 ]
        /* Read back to ensure the value is taken before proceeding. */
        CMP [ R5 ].UB, R5
        /* Restore clobbered register to its previous value. */
        বের_করো_2 R5
    #endif
    }

    #define portYIELD()                                       vPortYield()
    #define portYIELD_FROM_ISR( x )                           কুরু { যদি( ( x ) != pdFALSE ) portYIELD(); } যাবত্( 0 )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above  configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
    #define portENABLE_INTERRUPTS()                           set_ipl( ( long ) 0 )
    #যদি ( configASSERT_DEFINED == 1 )
        #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    configASSERT( ( get_ipl() <= configMAX_SYSCALL_INTERRUPT_PRIORITY ) )
        #define portDISABLE_INTERRUPTS()                      যদি( get_ipl() < configMAX_SYSCALL_INTERRUPT_PRIORITY ) set_ipl( ( long ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
    #অন্যথা
        #define portDISABLE_INTERRUPTS()                      set_ipl( ( long ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
    #endif

/* Critical nesting counts are stored in the TCB. */
    #define portCRITICAL_NESTING_IN_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
    বাহ্য শূন্য vTaskEnterCritical( শূন্য );
    বাহ্য শূন্য vTaskExitCritical( শূন্য );
    #define portENTER_CRITICAL()    vTaskEnterCritical()
    #define portEXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
    #define portSET_INTERRUPT_MASK_FROM_ISR()                              ( UBaseType_t ) get_ipl(); set_ipl( ( long ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
    #define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus )    set_ipl( ( long ) uxSavedInterruptStatus )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )

/*-----------------------------------------------------------*/

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without a DPFPU context and must call vPortTaskUsesDPFPU() to give
 * themselves a DPFPU context before using any DPFPU instructions.  If
 * configUSE_TASK_DPFPU_SUPPORT is set to 2 then all tasks will have a DPFPU context
 * by default. */
    #যদি( configUSE_TASK_DPFPU_SUPPORT == 1 )
        শূন্য vPortTaskUsesDPFPU( শূন্য );
    #অন্যথা
/* Each task has a DPFPU context already, so define this function away to
 * nothing to prevent it being called accidentally. */
        #define vPortTaskUsesDPFPU()
    #endif
    #define portTASK_USES_DPFPU() vPortTaskUsesDPFPU()

/* Definition to allow compatibility with existing FreeRTOS Demo using flop.c. */
    #define portTASK_USES_FLOATING_POINT() vPortTaskUsesDPFPU()

#pragma inline_asm vPortMemoryBarrier
স্থির শূন্য vPortMemoryBarrier( শূন্য )
{
}

#define portMEMORY_BARRIER()    vPortMemoryBarrier()

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
