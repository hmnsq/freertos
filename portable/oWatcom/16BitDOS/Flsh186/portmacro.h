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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR        ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT       ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE      ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG        ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT       ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE  uint16_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE   ਛੋਟਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਛੋਟਾ ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ UBaseType_t;


#ਜੇ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ  == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t             TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Critical section management. */
ਖਾਲੀ ਪੋਰਟ_ENTER_CRITICAL( ਖਾਲੀ );
#ਹਦਾਇਤ aux ਪੋਰਟ_ENTER_CRITICAL = "pushf" \
                                 "cli";

ਖਾਲੀ ਪੋਰਟ_EXIT_CRITICAL( ਖਾਲੀ );
#ਹਦਾਇਤ aux ਪੋਰਟ_EXIT_CRITICAL   = "popf";

ਖਾਲੀ ਪੋਰਟ_DISABLE_INTERRUPTS( ਖਾਲੀ );
#ਹਦਾਇਤ aux ਪੋਰਟ_DISABLE_INTERRUPTS = "cli";

ਖਾਲੀ ਪੋਰਟ_ENABLE_INTERRUPTS( ਖਾਲੀ );
#ਹਦਾਇਤ aux ਪੋਰਟ_ENABLE_INTERRUPTS = "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH        ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ   0x80
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()             __asm{ ਪੂਰਨ ਪੋਰਟ_SWITCH_INT_ਸੰਖਿਆ }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT      2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SW          ( ( ਪੋਰਟ_ਢੇਰ_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()               __asm{ nop }
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਨਿਵੇਸ਼_BYTE( xAddr )                 inp( xAddr )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OUTPUT_BYTE( xAddr, uc_ਮੁੱਲ )       outp( xAddr, uc_ਮੁੱਲ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਨਿਵੇਸ਼_ਸ਼ਬਦ( xAddr )                 inpw( xAddr )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_OUTPUT_ਸ਼ਬਦ( xAddr, us_ਮੁੱਲ )       outpw( xAddr, us_ਮੁੱਲ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) ਖਾਲੀ vFunction( ਖਾਲੀ *pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters ) ਖਾਲੀ vFunction( ਖਾਲੀ *pvParameters )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
