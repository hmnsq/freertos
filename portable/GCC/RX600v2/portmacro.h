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

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
#جيڪڏهن_وصف_نه_ٿيل config_INCLUDE_PLATFORM_H_INSTEAD_جو_IODEFINE_H
    #وصف_ڪريو config_INCLUDE_PLATFORM_H_INSTEAD_جو_IODEFINE_H    0
#جيڪڏهن_پورو

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    8         /* Could make four, according to manual. */
#وصف_ڪريو پورٽ_ڍير_GROWTH      -1
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_NOP()    __asm متطاير ( "NOP" )

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) *portITU_SWINTR;"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0).  Don't rely on the assembler to select a register, so instead
 * save and restore clobbered registers manually. */
#وصف_ڪريو پورٽ_YIELD()                     \
    __asm متطاير                      \
    (                                   \
        "PUSH.L R10                 \n" \
        "MOV.L  #0x872E0, R10       \n" \
        "MOV.B  #0x1, [R10]         \n" \
        "MOV.L  [R10], R10          \n" \
        "POP    R10                 \n" \
    )

#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )                           افعل { إذا( x != pdFALSE ) پورٽ_YIELD( ); } طالما( 0 )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                           __asm متطاير ( "MVTIPL    #0" )
#إذا ( configASSERT_DEFINED == 1 )
    #وصف_ڪريو پورٽ_ASSERT_IF_مداخلت_ترجيح_INVALID()    configASSERT( ( ul_پورٽ_Get_IPL() <= config_MAX_SYSCALL_مداخلت_ترجيح ) )
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                      إذا( ul_پورٽ_Get_IPL() < config_MAX_SYSCALL_مداخلت_ترجيح ) __asm متطاير( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_مداخلت_ترجيح ) )
#وإلا
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                      __asm متطاير ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_مداخلت_ترجيح ) )
#جيڪڏهن_پورو

/* Critical nesting counts are stored in the TCB. */
#وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#وصف_ڪريو پورٽ_ENTER_CRITICAL()    vTaskEnterCritical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
uint32_t ul_پورٽ_Get_IPL( فراغ ) __attribute__( ( naked ) );
فراغ v_پورٽ_سيٽ_IPL( uint32_t ulNewIPL ) __attribute__( ( naked ) );
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()                              ul_پورٽ_Get_IPL(); پورٽ_DISABLE_INTERRUPTS()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ux_Saved_مداخلت_حالت )    v_پورٽ_سيٽ_IPL( ux_Saved_مداخلت_حالت )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#وصف_ڪريو پورٽ_يادگيري_BARRIER()                                  __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
