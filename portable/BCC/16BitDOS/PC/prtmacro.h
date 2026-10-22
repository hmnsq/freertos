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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

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
#تعریف_کن پورت_CHAR        حرف
#تعریف_کن پورت_FLOAT       دراز
#تعریف_کن پورت_DOUBLE      دراز
#تعریف_کن پورت_LONG        دراز
#تعریف_کن پورت_SHORT       صحيح
#تعریف_کن پورت_پشته_TYPE  uint16_t
#تعریف_کن پورت_پایه_TYPE   پورت_SHORT

تعريفنوع پورت_پشته_TYPE پشته_Type_t;
تعريفنوع کوتاه پایه_Type_t;
تعريفنوع بیعلامت کوتاه UBaseType_t;

#إذا( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t ) 0xffffffffUL
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کن پورت_ENTER_CRITICAL()            __asm{ pushf }  \
                                        __asm{ cli   }  \

#تعریف_کن پورت_EXIT_CRITICAL()             __asm{ popf }

#تعریف_کن پورت_DISABLE_INTERRUPTS()        __asm{ cli }

#تعریف_کن پورت_ENABLE_INTERRUPTS()         __asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_NOP()               __asm{ nop }
#تعریف_کن پورت_پشته_GROWTH        ( -1 )
#تعریف_کن پورت_SWITCH_INT_عدد   0x80
#تعریف_کن پورت_YIELD()             __asm{ صحيح پورت_SWITCH_INT_عدد }
#تعریف_کن پورت_DOS_TICK_نرخ       ( 18.20648 )
#تعریف_کن پورت_TICK_PERIOD_MS      ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_TICKS_در_هر_DOS_TICK  ( ( uint16_t ) ( ( ( پورت_DOUBLE ) config_TICK_نرخ_HZ / پورت_DOS_TICK_نرخ ) + 0.5 ) )
#تعریف_کن پورت_INITIAL_SW          ( ( پورت_پشته_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#تعریف_کن پورت_BYTE_ALIGNMENT      ( 2 )
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#تعریف_کن پورت_درون_داد_BYTE( xAddr )             inp( xAddr )
#تعریف_کن پورت_OUTPUT_BYTE( xAddr, uc_مقدار )   outp( xAddr, uc_مقدار )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vTaskFunction, pvParameters ) فراغ vTaskFunction( فراغ *pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vTaskFunction, pvParameters ) فراغ vTaskFunction( فراغ *pvParameters )

#پایان_اگر /* PORTMACRO_H */
