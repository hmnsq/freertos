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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint16_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਛੋਟਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE     ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਛੋਟਾ              ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ     UBaseType_t;

#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t       TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    __asm( "DI" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                                                      \
    {                                                                             \
        ਬਾਹਰੀ ਅਸਥਿਰ uint16_t usCriticalNesting;                               \
                                                                                  \
        ਪੋਰਟ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                                                         \
    {                                                                               \
        ਬਾਹਰੀ ਅਸਥਿਰ uint16_t usCriticalNesting;                                 \
                                                                                    \
        ਜੇ( usCriticalNesting > ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            ਜੇ( usCriticalNesting == ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                ਪੋਰਟ_ENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ( ਖਾਲੀ );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                                       __asm( "BRK" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x_Higher_ਤਰਜੀਹ_Task_Woken )    ਕਰੋ { ਜੇ( x_Higher_ਤਰਜੀਹ_Task_Woken ) vTaskSwitchContext( ); } ਜਦੋਂ( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()                                         __asm( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )


ਸਥਿਰ __interrupt ਖਾਲੀ P0_isr( ਖਾਲੀ );

/* --------------------------------------------------------------------------*/
/* Option-bytes and security ID                                              */
/* --------------------------------------------------------------------------*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPT_ਬਾਈਟਾਂ_ਮਾਪ       4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SECU_ID_ਮਾਪ         10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WATCHDOG_DISABLED    0x00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LVI_ENABLED          0xFE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LVI_DISABLED         0xFF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_FF          0xFF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OCD_DISABLED         0x04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OCD_ENABLED          0x81
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OCD_ENABLED_ERASE    0x80

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
