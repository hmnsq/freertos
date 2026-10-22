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

/* Standard includes. */
#ضمن <stddef.h>

/* Constants denoting the available memory models.  These are used within
FreeRTOSConfig.h to set the configMEMMODEL value. */
#تعریف_کن پورت_SMALL     0
#تعریف_کن پورت_MEDIUM    1
#تعریف_کن پورت_COMPACT   2
#تعریف_کن پورت_LARGE     3


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
#تعریف_کن پورت_FLOAT       عائم
#تعریف_کن پورت_DOUBLE      مزدوج
#تعریف_کن پورت_LONG        دراز
#تعریف_کن پورت_SHORT       کوتاه
#تعریف_کن پورت_پشته_TYPE  uint16_t
#تعریف_کن پورت_پایه_TYPE   کوتاه

تعريفنوع پورت_پشته_TYPE پشته_Type_t;
تعريفنوع کوتاه پایه_Type_t;
تعريفنوع بیعلامت کوتاه UBaseType_t;


#إذا( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها  == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Critical section handling. */
#إذا config_KERNEL_وقفه_اولویت != 6
    #خطا config_KERNEL_وقفه_اولویت (مجموعه درون FreeRTOSConfig.h) must تطابق the ILM مقدار مجموعه درون the following سطر - #06H being the افتراضي.
#پایان_اگر
#تعریف_کن پورت_DISABLE_INTERRUPTS()    __asm(" MOV ILM, #06h ")
#تعریف_کن پورت_ENABLE_INTERRUPTS()     __asm(" MOV ILM, #07h ")

#تعریف_کن پورت_ENTER_CRITICAL()                                \
        {   __asm(" PUSHW PS ");                            \
            پورت_DISABLE_INTERRUPTS();                       \
        }

#تعریف_کن پورت_EXIT_CRITICAL()                                 \
        {   __asm(" POPW PS ");                             \
        }

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH            ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT          2
#تعریف_کن پورت_NOP()                   __asm( " NOP " );
/*-----------------------------------------------------------*/

/* portYIELD() uses SW interrupt */
#تعریف_کن پورت_YIELD()                 __asm( " INT #122 " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#تعریف_کن پورت_YIELD_FROM_ISR()         __asm( " SETB  03A4H:0 " );
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#تعریف_کن پورت_کمینه_پشته_اندازه config_کمینه_پشته_اندازه


#پایان_اگر /* PORTMACRO_H */
