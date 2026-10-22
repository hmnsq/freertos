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

/* Hardware specifics. */
#ضمن <intrinsics.h>

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

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
#که_نه_تعریف_شوی config_INCLUDE_PLATFORM_H_INSTEAD_د_IODEFINE_H
    #تعریف_کړه config_INCLUDE_PLATFORM_H_INSTEAD_د_IODEFINE_H    0
#د_که_پای

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or undefined) then each task will
 * be created without a DPFPU context, and a task must call vTaskUsesDPFPU() before
 * making use of any DPFPU registers.  If configUSE_TASK_DPFPU_SUPPORT is set to 2 then
 * tasks are created with a DPFPU context by default, and calling vTaskUsesDPFPU() has
 * no effect.  If configUSE_TASK_DPFPU_SUPPORT is set to 0 then tasks never take care
 * of any DPFPU context (even if DPFPU registers are used). */
#که_نه_تعریف_شوی configUSE_TASK_DPFPU_SUPPORT
    #تعریف_کړه configUSE_TASK_DPFPU_SUPPORT    1
#د_که_پای

/*-----------------------------------------------------------*/

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT    8         /* Could make four, according to manual. */
#تعریف_کړه پورټ_ډېری_GROWTH      -1
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_NOP()    __no_operation()

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) *portITU_SWINTR;"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0).  Don't rely on the assembler to select a register, so instead
 * save and restore clobbered registers manually. */
#تعریف_کړه پورټ_YIELD()                     \
    __asm متطاير                      \
    (                                   \
        "PUSH.L R10                 \n" \
        "MOV.L  #0x872E0, R10       \n" \
        "MOV.B  #0x1, [R10]         \n" \
        "CMP    [R10].UB, R10       \n" \
        "POP    R10                 \n" \
        پورټ_CDT_NO_PARSE( ::: ) "cc"    \
    )

#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    افعل { إذا( ( x ) != pdFALSE ) پورټ_YIELD( ); } طالما( 0 )

/* Workaround to reduce errors/warnings caused by e2 studio CDT's INDEXER and CODAN. */
#که_تعریف_شوی __CDT_PARSER__
    #که_نه_تعریف_شوی __asm
        #تعریف_کړه __asm    asm
    #د_که_پای
    #که_نه_تعریف_شوی __attribute__
        #تعریف_کړه __attribute__( ... )
    #د_که_پای
    #تعریف_کړه پورټ_CDT_NO_PARSE( token )
#وإلا
    #تعریف_کړه پورټ_CDT_NO_PARSE( token )    token
#د_که_پای

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above  configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                           __set_interrupt_level( ( uint8_t ) 0 )
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    configASSERT( ( __get_interrupt_level() <= config_MAX_SYSCALL_مداخله_لومړیتوب ) )
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                      إذا( __get_interrupt_level() < config_MAX_SYSCALL_مداخله_لومړیتوب ) __set_interrupt_level( ( uint8_t ) config_MAX_SYSCALL_مداخله_لومړیتوب )
#وإلا
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                      __set_interrupt_level( ( uint8_t ) config_MAX_SYSCALL_مداخله_لومړیتوب )
#د_که_پای

/* Critical nesting counts are stored in the TCB. */
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()                                           vTaskEnterCritical()
#تعریف_کړه پورټ_EXIT_CRITICAL()                                            vTaskExitCritical()

/* As this port allows interrupt nesting... */
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()                              __get_interrupt_level(); پورټ_DISABLE_INTERRUPTS()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_Saved_مداخله_حالت )    __set_interrupt_level( ( uint8_t ) ( ux_Saved_مداخله_حالت ) )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without a DPFPU context and must call vPortTaskUsesDPFPU() to give
 * themselves a DPFPU context before using any DPFPU instructions.  If
 * configUSE_TASK_DPFPU_SUPPORT is set to 2 then all tasks will have a DPFPU context
 * by default. */
#إذا ( configUSE_TASK_DPFPU_SUPPORT == 1 )
    فراغ v_پورټ_Task_کاروي_DPFPU( فراغ );
#وإلا

/* Each task has a DPFPU context already, so define this function away to
 * nothing to prevent it being called accidentally. */
    #تعریف_کړه v_پورټ_Task_کاروي_DPFPU()
#د_که_پای
#تعریف_کړه پورټ_TASK_کاروي_DPFPU()             v_پورټ_Task_کاروي_DPFPU()

/* Definition to allow compatibility with existing FreeRTOS Demo using flop.c. */
#تعریف_کړه پورټ_TASK_کاروي_FLOATING_ټکی()    v_پورټ_Task_کاروي_DPFPU()

/* Prevent warnings of undefined behaviour: the order of volatile accesses is
 * undefined - all warnings have been manually checked and are not an issue, and
 * the warnings cannot be prevent by code changes without undesirable effects. */
#لارښوونه diag_suppress=Pa082

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
