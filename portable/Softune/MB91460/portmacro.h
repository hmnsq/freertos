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
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE   اوږد

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع اوږد بنسټ_Type_t;
تعريفنوع بینښه اوږد UBaseType_t;


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

/* Critical section management. */
#إذا config_KERNEL_مداخله_لومړیتوب != 30
    #تېروتنه config_KERNEL_مداخله_لومړیتوب (سېټ دننه FreeRTOSConfig.h) must سمون the ILM ارزښت سېټ دننه the following کرښه - 30 (1Eh) being the افتراضي.
#د_که_پای
#تعریف_کړه پورټ_DISABLE_INTERRUPTS() __asm(" STILM #1Eh ")
#تعریف_کړه پورټ_ENABLE_INTERRUPTS() __asm(" STILM #1Fh ")

#تعریف_کړه پورټ_ENTER_CRITICAL()    \
    __asm(" ST PS,@-R15 ");     \
    __asm(" ANDCCR #0xef ");    \


#تعریف_کړه پورټ_EXIT_CRITICAL()     \
    __asm(" LD @R15+,PS ");     \

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH            ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT          4
#تعریف_کړه پورټ_NOP()                   __asm( " nop " );
/*-----------------------------------------------------------*/

/* portYIELD() uses a SW interrupt */
#تعریف_کړه پورټ_YIELD()                 __asm( " INT #40H " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#تعریف_کړه پورټ_YIELD_FROM_ISR()            DICR_DLYI = 1
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#تعریف_کړه پورټ_اصغري_ډېری_اندازه config_اصغري_ډېری_اندازه


#د_که_پای /* PORTMACRO_H */
