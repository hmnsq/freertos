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

/* Type definitions. */
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      اوږد
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       صحيح
#تعریف_کړه پورټ_ډېری_TYPE  uint16_t
#تعریف_کړه پورټ_بنسټ_TYPE   لنډ

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع لنډ بنسټ_Type_t;
تعريفنوع بینښه لنډ UBaseType_t;


#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه  == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Critical section handling. */
#تعریف_کړه پورټ_ENTER_CRITICAL()            __asm{ pushf }  \
                                        __asm{ cli   }  \

#تعریف_کړه پورټ_EXIT_CRITICAL()             __asm{ popf }

#تعریف_کړه پورټ_DISABLE_INTERRUPTS()        __asm{ cli }

#تعریف_کړه پورټ_ENABLE_INTERRUPTS()         __asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_NOP()                       __asm{ nop }
#تعریف_کړه پورټ_ډېری_GROWTH                ( -1 )
#تعریف_کړه پورټ_SWITCH_INT_شمېره           0x80
#تعریف_کړه پورټ_YIELD()                     __asm{ صحيح پورټ_SWITCH_INT_شمېره }
#تعریف_کړه پورټ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT              2
#تعریف_کړه پورټ_INITIAL_SW                  ( ( پورټ_ډېری_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#تعریف_کړه پورټ_ننوت_BYTE( xAddr )             inp( xAddr )
#تعریف_کړه پورټ_OUTPUT_BYTE( xAddr, uc_ارزښت )   outp( xAddr, uc_ارزښت )
#تعریف_کړه پورټ_ننوت_کلمه( xAddr )             inpw( xAddr )
#تعریف_کړه پورټ_OUTPUT_کلمه( xAddr, us_ارزښت )   outpw( xAddr, us_ارزښت )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vTaskFunction, vParameters ) فراغ vTaskFunction( فراغ *pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vTaskFunction, vParameters ) فراغ vTaskFunction( فراغ *pvParameters )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */


#د_که_پای /* PORTMACRO_H */
