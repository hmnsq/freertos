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
#تعریف_کرو پورٹ_CHAR         حرف
#تعریف_کرو پورٹ_FLOAT        اعشاری
#تعریف_کرو پورٹ_DOUBLE       دوہرا
#تعریف_کرو پورٹ_LONG         طویل
#تعریف_کرو پورٹ_SHORT        صحیح
#تعریف_کرو پورٹ_بنیاد_TYPE    مختصر

/* The stack type changes depending on the data model. */
#اگر ( __DATA_MODEL__ == __DATA_MODEL_SMALL__ )
    #تعریف_کرو پورٹ_ڈھیر_TYPE           uint16_t
    #تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    uint16_t
#ورنہ
    #تعریف_کرو پورٹ_ڈھیر_TYPE           uint32_t
#اگر_ختم

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف مختصر            بنیاد_Type_t;
قسمتعریف غیرعلامتی مختصر   UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم

/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm متلون ( "DINT\n" "NOP" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm متلون ( "NOP\n" "EINT\n" "NOP" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

#تعریف_کرو پورٹ_ENTER_CRITICAL()                                                     \
    {                                                                            \
        خارجی متلون uint16_t usCriticalNesting;                              \
                                                                                 \
        پورٹ_DISABLE_INTERRUPTS();                                                \
                                                                                 \
        /* Now interrupts are disabled usCriticalNesting can be accessed */      \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */ \
        /* times portENTER_CRITICAL() has been called. */                        \
        usCriticalNesting++;                                                     \
    }

#تعریف_کرو پورٹ_EXIT_CRITICAL()                                                         \
    {                                                                               \
        خارجی متلون uint16_t usCriticalNesting;                                 \
                                                                                    \
        اگر( usCriticalNesting > پورٹ_NO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            اگر( usCriticalNesting == پورٹ_NO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                پورٹ_ENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
خارجی خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_YIELD()    v_پورٹ_Yield()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    2
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_NOP()             __asm متلون ( "NOP" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )                               کرو { اگر( x ) v_پورٹ_Yield( ); } جب( 0 )

خالی v_Application_تیاری_Timer_مداخلت( خالی );

/* sizeof( int ) != sizeof( long ) so a full printf() library is required if
 * run time stats information is to be displayed. */
#تعریف_کرو پورٹ_LU_PRINTF_SPECIFIER_REQUIRED

#اگر_ختم /* PORTMACRO_H */
