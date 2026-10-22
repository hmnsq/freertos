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

#تعریف_کرو پورٹ_CHAR                 حرف
#تعریف_کرو پورٹ_FLOAT                اعشاری
#تعریف_کرو پورٹ_DOUBLE               دوہرا
#تعریف_کرو پورٹ_LONG                 طویل
#تعریف_کرو پورٹ_SHORT                مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE           uint16_t
#تعریف_کرو پورٹ_بنیاد_TYPE            مختصر
#تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    uint16_t

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
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm متلون ( "DI" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm متلون ( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( غیرعلامتی مختصر ) 0 )

#تعریف_کرو پورٹ_ENTER_CRITICAL()                                                      \
    {                                                                             \
        خارجی متلون uint16_t usCriticalNesting;                               \
                                                                                  \
        پورٹ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
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
#تعریف_کرو پورٹ_YIELD()                                       __asm متلون ( "BRK" )
#اگر_غیر_تعریف_شدہ configREQUIRE_ASM_ISR_WRAPPER
    #تعریف_کرو configREQUIRE_ASM_ISR_WRAPPER    1
#اگر_ختم
#اگر( configREQUIRE_ASM_ISR_WRAPPER == 1 )
    /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
     * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
    #تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    کرو { اگر( x_Higher_ترجیح_Task_Woken != pdFALSE ) vTaskSwitchContext(); } جب( 0 )
#ورنہ
    /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
     * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
    #تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    کرو { اگر( x_Higher_ترجیح_Task_Woken != pdFALSE ) پورٹ_YIELD(); } جب( 0 )
#اگر_ختم
#تعریف_کرو پورٹ_NOP()                                         __asm متلون ( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    2
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#اگر_ختم /* PORTMACRO_H */
