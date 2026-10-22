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

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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

#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint16_t
#تعریف_کرو پورٹ_ادھار_TYPE     چھوٹا

تعريفنوع پورٹ_ڈھیر_TYPE     ڈھیر_Type_t;
تعريفنوع چھوٹا              ادھار_Type_t;
تعريفنوع بنانشانی چھوٹا     UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع بنانشانی صحيح   TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t       TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm( "DI" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

#تعریف_کرو پورٹ_ENTER_CRITICAL()                                                      \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
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
        خارجي متطاير uint16_t usCriticalNesting;                                 \
                                                                                    \
        إذا( usCriticalNesting > پورٹ_NO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            إذا( usCriticalNesting == پورٹ_NO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                پورٹ_ENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
خارجي فراغ v_پورٹ_شروع( فراغ );
#تعریف_کرو پورٹ_YIELD()                                       __asm( "BRK" )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    افعل { إذا( x_Higher_ترجیح_Task_Woken ) vTaskSwitchContext( ); } طالما( 0 )
#تعریف_کرو پورٹ_NOP()                                         __asm( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    2
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )


ساكن __interrupt فراغ P0_isr( فراغ );

/* --------------------------------------------------------------------------*/
/* Option-bytes and security ID                                              */
/* --------------------------------------------------------------------------*/
#تعریف_کرو OPT_بائٹاں_ناپ       4
#تعریف_کرو SECU_ID_ناپ         10
#تعریف_کرو WATCHDOG_DISABLED    0x00
#تعریف_کرو LVI_ENABLED          0xFE
#تعریف_کرو LVI_DISABLED         0xFF
#تعریف_کرو RESERVED_FF          0xFF
#تعریف_کرو OCD_DISABLED         0x04
#تعریف_کرو OCD_ENABLED          0x81
#تعریف_کرو OCD_ENABLED_ERASE    0x80

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
