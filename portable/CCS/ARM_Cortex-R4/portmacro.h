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

#اگر_غیر_تعریف_شدہ __PORTMACRO_H__
#تعریف_کرو __PORTMACRO_H__

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
#تعریف_کرو پورٹ_DOUBLE      دوہرا
#تعریف_کرو پورٹ_LONG        طویل
#تعریف_کرو پورٹ_SHORT       مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE   طویل

قسمتعریف پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
قسمتعریف طویل بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل UBaseType_t;

#اگر (config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ)
    قسمتعریف uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY (TickType_t) 0xFFFF
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY (TickType_t) 0xFFFFFFFFF

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC 1
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم


/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH    (-1)
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ((TickType_t) 1000 / config_TICK_شرح_HZ)
#تعریف_کرو پورٹ_BYTE_ALIGNMENT  8

/* Critical section handling. */
خارجی خالی v_پورٹ_Enter_Critical(خالی);
خارجی خالی v_پورٹ_Exit_Critical(خالی);
#تعریف_کرو پورٹ_ENTER_CRITICAL()        v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()         v_پورٹ_Exit_Critical()
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    asm( " CPSID I" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     asm( " CPSIE I" )

/* Scheduler utilities. */
#ہدایت SWI_ALIAS( v_پورٹ_Yield, 0 )
خارجی خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_YIELD()                 v_پورٹ_Yield()
#تعریف_کرو پورٹ_SYS_SSIR1_REG           ( * ( ( متلون uint32_t * ) 0xFFFFFFB0 ) )
#تعریف_کرو پورٹ_SYS_SSIR1_SSKEY         ( 0x7500UL )
#تعریف_کرو پورٹ_YIELD_WITHIN_API()      { پورٹ_SYS_SSIR1_REG = پورٹ_SYS_SSIR1_SSKEY;  asm( " DSB " ); asm( " ISB " ); }
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )     کرو { اگر( x != pdFALSE ) { پورٹ_SYS_SSIR1_REG = پورٹ_SYS_SSIR1_SSKEY;  ( خالی ) پورٹ_SYS_SSIR1_REG; } } جب( 0 )

#اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION 1
#اگر_ختم

/* Architecture specific optimisations. */
#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #اگر( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires مزید than 10 مقصد 15 difference priorities as tasks that share a ترجیح will time قاش.
    #اگر_ختم

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

    /*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities ) ux_چوٹی_ترجیح = ( 31 - __clz( ( uxReadyPriorities ) ) )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION(vFunction, pvParameters)       خالی vFunction(خالی *pvParameters)
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO(vFunction, pvParameters) خالی vFunction(خالی *pvParameters)

#اگر_ختم /* __PORTMACRO_H__ */
