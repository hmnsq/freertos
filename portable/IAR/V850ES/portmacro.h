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
    ಬಾಹ್ಯ "C" {
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
#define portCHAR          ವರ್ಣ
#define portFLOAT         ಭಿನ್ನ
#define portDOUBLE        ದ್ವಿಗುಣ
#define portLONG          long
#define portSHORT         short
#define port_ರಾಶಿ_TYPE    unsigned ಪೂರ್ಣಾಙ್ಕ
#define portBASE_TYPE     ಪೂರ್ಣಾಙ್ಕ

ಪ್ರಕಾರನಿರ್ದೇಶ port_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರನಿರ್ದೇಶ long             BaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned long    UBaseType_t;


#ಯದಿ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#ನೋಚೇದ್ಯದಿ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#ಅನ್ಯಥಾ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS()    __asm( "DI" )
#define portENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#define portNO_CRITICAL_SECTION_NESTING    ( ( UBaseType_t ) 0 )

#define portENTER_CRITICAL()                                                      \
    {                                                                             \
        ಬಾಹ್ಯ ಚಞ್ಚಲ /*uint16_t*/ port_ರಾಶಿ_TYPE usCriticalNesting;            \
                                                                                  \
        portDISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

#define portEXIT_CRITICAL()                                                         \
    {                                                                               \
        ಬಾಹ್ಯ ಚಞ್ಚಲ /*uint16_t*/ port_ರಾಶಿ_TYPE usCriticalNesting;              \
                                                                                    \
        ಯದಿ( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            ಯದಿ( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                portENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
ಬಾಹ್ಯ ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortStart( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ portSAVE_CONTEXT( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ portRESTORE_CONTEXT( ಶೂನ್ಯ );
#define portYIELD()                                       __asm( "trap 0" )
#define portNOP()                                         __asm( "NOP" )
ಬಾಹ್ಯ ಶೂನ್ಯ vTaskSwitchContext( ಶೂನ್ಯ );
#define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    ಕುರು { ಯದಿ( xHigherPriorityTaskWoken ) vTaskSwitchContext( ); } ಯಾವತ್( 0 )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    4
#define port_ರಾಶಿ_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )


/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
