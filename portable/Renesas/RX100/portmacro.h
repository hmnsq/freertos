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


#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
/* *INDENT-ON* */

/* Hardware specifics. */
#समावेश "machine.h"

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions - these are a bit legacy and not really used now, other
than portSTACK_TYPE and portBASE_TYPE. */
#घोषणा portCHAR        अक्षर
#घोषणा portFLOAT       भग्न
#घोषणा portDOUBLE      द्विगुन
#घोषणा portLONG        दीर्घ
#घोषणा portSHORT       लघु
#घोषणा port_ढेर_TYPE  uint32_t
#घोषणा portBASE_TYPE   दीर्घ

प्रकार port_ढेर_TYPE ढेर_Type_t;
प्रकार दीर्घ BaseType_t;
प्रकार अचिन्हित दीर्घ UBaseType_t;

#अगर( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t TickType_t;
    #घोषणा portMAX_DELAY ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t TickType_t;
    #घोषणा portMAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC 1
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#घोषणा portBYTE_ALIGNMENT              8   /* Could make four, according to manual. */
#घोषणा port_ढेर_GROWTH                -1
#घोषणा portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portNOP()                       nop()

#आशय inline_asm vPortYield
अटल व्योम vPortYield( व्योम )
{
    /* Save clobbered register - may not actually be necessary if inline asm
    functions are considered to use the same rules as function calls by the
    compiler. */
    धकेलो_2.L R5
    /* Set ITU SWINTR. */
    MOV.L #872E0H, R5
    MOV.B #1, [R5]
    /* Read back to ensure the value is taken before proceeding. */
    MOV.L [R5], R5
    /* Restore clobbered register to its previous value. */
    निकालो_2 R5
}
#घोषणा portYIELD() vPortYield()
#घोषणा portYIELD_FROM_ISR( x ) करो { अगर( x != pdFALSE ) { portYIELD(); } } जबतक( 0 )

/* These macros should not be called directly, but through the
taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
performed if configASSERT() is defined to ensure an assertion handler does not
inadvertently attempt to lower the IPL when the call to assert was triggered
because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
functions are those that end in FromISR.  FreeRTOS maintains a separate
interrupt API to ensure API function and interrupt entry is as fast and as
simple as possible. */
#घोषणा portENABLE_INTERRUPTS()     set_ipl( ( दीर्घ ) 0 )
#अगर ( configASSERT_DEFINED == 1 )
    #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID() configASSERT( ( get_ipl() <= configMAX_SYSCALL_INTERRUPT_PRIORITY ) )
    #घोषणा portDISABLE_INTERRUPTS()    अगर( get_ipl() < configMAX_SYSCALL_INTERRUPT_PRIORITY ) set_ipl( ( दीर्घ ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#अन्यथा
    #घोषणा portDISABLE_INTERRUPTS()    set_ipl( ( दीर्घ ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#पूर्ण_अगर

/* Critical nesting counts are stored in the TCB. */
#घोषणा portCRITICAL_NESTING_IN_TCB ( 1 )

/* The critical nesting functions defined within tasks.c. */
बाह्य व्योम vTaskEnterCritical( व्योम );
बाह्य व्योम vTaskExitCritical( व्योम );
#घोषणा portENTER_CRITICAL()    vTaskEnterCritical()
#घोषणा portEXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR() ( UBaseType_t ) get_ipl(); set_ipl( ( चिन्हित दीर्घ ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus ) set_ipl( ( चिन्हित दीर्घ ) uxSavedInterruptStatus )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#अगर configUSE_TICKLESS_IDLE == 1
    #अगर_अघोषित portSUPPRESS_TICKS_AND_SLEEP
        बाह्य व्योम vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
        #घोषणा portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime ) vPortSuppressTicksAndSleep( xExpectedIdleTime )
    #पूर्ण_अगर
#पूर्ण_अगर

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )

#आशय inline_asm vPortMemoryBarrier
अटल व्योम vPortMemoryBarrier( व्योम )
{
}

#घोषणा portMEMORY_BARRIER()    vPortMemoryBarrier()

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
