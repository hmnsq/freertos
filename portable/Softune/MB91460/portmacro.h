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

/* Hardware specific includes. */
#ضمن "mb91467d.h"

/* Standard includes. */
#ضمن <stddef.h>

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
#تعریف_کرو پورٹ_FLOAT       عائم
#تعریف_کرو پورٹ_DOUBLE      مزدوج
#تعریف_کرو پورٹ_LONG        لما
#تعریف_کرو پورٹ_SHORT       چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE   لما

تعريفنوع پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
تعريفنوع لما ادھار_Type_t;
تعريفنوع بنانشانی لما UBaseType_t;


#إذا( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ  == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Critical section management. */
#إذا config_KERNEL_رکاوٹ_ترجیح != 30
    #غلطی config_KERNEL_رکاوٹ_ترجیح (سیٹ وچ FreeRTOSConfig.h) must میل the ILM قدر سیٹ وچ the following سطر - 30 (1Eh) being the افتراضي.
#جے_انت
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS() __asm(" STILM #1Eh ")
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS() __asm(" STILM #1Fh ")

#تعریف_کرو پورٹ_ENTER_CRITICAL()    \
    __asm(" ST PS,@-R15 ");     \
    __asm(" ANDCCR #0xef ");    \


#تعریف_کرو پورٹ_EXIT_CRITICAL()     \
    __asm(" LD @R15+,PS ");     \

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH            ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT          4
#تعریف_کرو پورٹ_NOP()                   __asm( " nop " );
/*-----------------------------------------------------------*/

/* portYIELD() uses a SW interrupt */
#تعریف_کرو پورٹ_YIELD()                 __asm( " INT #40H " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#تعریف_کرو پورٹ_YIELD_FROM_ISR()            DICR_DLYI = 1
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#تعریف_کرو پورٹ_اقل_ڈھیر_ناپ config_اقل_ڈھیر_ناپ


#جے_انت /* PORTMACRO_H */
