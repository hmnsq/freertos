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

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
#جے_بنا_تعریف config_INCLUDE_PLATFORM_H_INSTEAD_دا_IODEFINE_H
    #تعریف_کرو config_INCLUDE_PLATFORM_H_INSTEAD_دا_IODEFINE_H    0
#جے_انت

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع لما             ادھار_Type_t;
تعريفنوع بنانشانی لما    UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8         /* Could make four, according to manual. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      -1
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_NOP()    __asm متطاير ( "NOP" )

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) *portITU_SWINTR;"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0).  Don't rely on the assembler to select a register, so instead
 * save and restore clobbered registers manually. */
#تعریف_کرو پورٹ_YIELD()                     \
    __asm متطاير                      \
    (                                   \
        "PUSH.L R10                 \n" \
        "MOV.L  #0x872E0, R10       \n" \
        "MOV.B  #0x1, [R10]         \n" \
        "MOV.L  [R10], R10          \n" \
        "POP    R10                 \n" \
    )

#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )                           إذا( x != pdFALSE ) پورٹ_YIELD( )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                           __asm متطاير ( "MVTIPL    #0" )
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    configASSERT( ( ul_پورٹ_Get_IPL() <= config_MAX_SYSCALL_رکاوٹ_ترجیح ) )
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                      إذا( ul_پورٹ_Get_IPL() < config_MAX_SYSCALL_رکاوٹ_ترجیح ) __asm متطاير( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_رکاوٹ_ترجیح ) )
#وإلا
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                      __asm متطاير ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_رکاوٹ_ترجیح ) )
#جے_انت

/* Critical nesting counts are stored in the TCB. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
uint32_t ul_پورٹ_Get_IPL( فراغ ) __attribute__( ( naked ) );
فراغ v_پورٹ_سیٹ_IPL( uint32_t ulNewIPL ) __attribute__( ( naked ) );
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()                              ul_پورٹ_Get_IPL(); پورٹ_DISABLE_INTERRUPTS()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ux_Saved_رکاوٹ_حالت )    v_پورٹ_سیٹ_IPL( ux_Saved_رکاوٹ_حالت )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کرو پورٹ_حافظہ_BARRIER()                                  __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
