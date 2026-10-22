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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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
#تعریف_کرو پورٹ_CHAR        حرف
#تعریف_کرو پورٹ_FLOAT       اعشاری
#تعریف_کرو پورٹ_DOUBLE      طویل
#تعریف_کرو پورٹ_LONG        طویل
#تعریف_کرو پورٹ_SHORT       صحیح
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint16_t
#تعریف_کرو پورٹ_بنیاد_TYPE   مختصر

قسمتعریف پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
قسمتعریف مختصر بنیاد_Type_t;
قسمتعریف غیرعلامتی مختصر UBaseType_t;


#اگر( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ  == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*-----------------------------------------------------------*/

/* Critical section handling. */
#تعریف_کرو پورٹ_ENTER_CRITICAL()            __asm{ pushf }  \
                                        __asm{ cli   }  \

#تعریف_کرو پورٹ_EXIT_CRITICAL()             __asm{ popf }

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()        __asm{ cli }

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()         __asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_NOP()                       __asm{ nop }
#تعریف_کرو پورٹ_ڈھیر_GROWTH                ( -1 )
#تعریف_کرو پورٹ_SWITCH_INT_نمبر           0x80
#تعریف_کرو پورٹ_YIELD()                     __asm{ صحیح پورٹ_SWITCH_INT_نمبر }
#تعریف_کرو پورٹ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT              2
#تعریف_کرو پورٹ_INITIAL_SW                  ( ( پورٹ_ڈھیر_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#تعریف_کرو پورٹ_داخلہ_BYTE( xAddr )             inp( xAddr )
#تعریف_کرو پورٹ_OUTPUT_BYTE( xAddr, uc_قدر )   outp( xAddr, uc_قدر )
#تعریف_کرو پورٹ_داخلہ_لفظ( xAddr )             inpw( xAddr )
#تعریف_کرو پورٹ_OUTPUT_لفظ( xAddr, us_قدر )   outpw( xAddr, us_قدر )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vTaskFunction, vParameters ) خالی vTaskFunction( خالی *pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vTaskFunction, vParameters ) خالی vTaskFunction( خالی *pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */


#اگر_ختم /* PORTMACRO_H */
