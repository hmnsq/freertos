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

/*
 * Changes from V1.2.3
 *
 + portCPU_CLOCK_HZ definition changed to 8MHz base 10, previously it
 +    base 16.
 */

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR                 حرف
#تعریف_کن پورت_FLOAT                عائم
#تعریف_کن پورت_DOUBLE               مزدوج
#تعریف_کن پورت_LONG                 دراز
#تعریف_کن پورت_SHORT                صحيح
#تعریف_کن پورت_پشته_TYPE           uint8_t
#تعریف_کن پورت_پایه_TYPE            حرف
#تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint16_t

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع علامتدار حرف      پایه_Type_t;
تعريفنوع بیعلامت حرف    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر

/*-----------------------------------------------------------*/

/* Critical section management. */
خارجي فراغ v_پورت_Enter_Critical( فراغ );
خارجي فراغ v_پورت_Exit_Critical( فراغ );
#تعریف_کن پورت_ENTER_CRITICAL()        v_پورت_Enter_Critical()
#تعریف_کن پورت_EXIT_CRITICAL()         v_پورت_Exit_Critical()

#تعریف_کن پورت_DISABLE_INTERRUPTS()    asm ( "cli" )
#تعریف_کن پورت_ENABLE_INTERRUPTS()     asm ( "sei" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH      ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT    1
#تعریف_کن پورت_NOP()    asm ( "nop" )
/*-----------------------------------------------------------*/

/* Kernel utilities. */
فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_YIELD()                v_پورت_Yield()

#اگر_تعریف_شده IAR_MEGA_AVR
    #تعریف_کن outb( پورت_3, مقدار_3 )    پورت_3 = مقدار_3
#پایان_اگر
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
