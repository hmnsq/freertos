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
    #تعریف_کرو پورٹ_CHAR          حرف
    #تعریف_کرو پورٹ_FLOAT         اعشاری
    #تعریف_کرو پورٹ_DOUBLE        دوہرا
    #تعریف_کرو پورٹ_LONG          طویل
    #تعریف_کرو پورٹ_SHORT         مختصر
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
    #تعریف_کرو پورٹ_بنیاد_TYPE     طویل

    قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    قسمتعریف طویل             بنیاد_Type_t;
    قسمتعریف غیرعلامتی طویل    UBaseType_t;


    #اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
        قسمتعریف uint16_t     TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
    #وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
        قسمتعریف uint32_t     TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
    #ورنہ
        #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
    #اگر_ختم
/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجی خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_NVIC_INT_CTRL     ( ( متلون uint32_t * ) 0xe000ed04 )
#تعریف_کرو پورٹ_NVIC_PENDSVSET    0x10000000
#تعریف_کرو پورٹ_YIELD()                v_پورٹ_Yield()

#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired )         \
    کرو                                                   \
    {                                                    \
        اگر( xSwitchRequired != pdFALSE )                 \
        {                                                \
            trace_ISR_EXIT_مقصد_SCHEDULER();                \
            *( پورٹ_NVIC_INT_CTRL ) = پورٹ_NVIC_PENDSVSET; \
        }                                                \
        ورنہ                                             \
        {                                                \
            traceISR_EXIT();                             \
        }                                                \
    } جب( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/


/* Critical section management. */

/*
 * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without effecting other
 * registers.  r0 is clobbered.
 */
    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب()      __set_BASEPRI( config_MAX_SYSCALL_مداخلت_ترجیح )

/*
 * Set basepri back to 0 without effective other registers.
 * r0 is clobbered.  FAQ:  Setting BASEPRI to 0 is not a bug.  Please see
 * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html before disagreeing.
 */
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب()    __set_BASEPRI( 0 )

    خارجی uint32_t ul_پورٹ_سیٹ_مداخلت_نقاب( خالی );
    خارجی خالی v_پورٹ_Clear_مداخلت_نقاب( uint32_t ul_New_نقاب );
    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         ul_پورٹ_سیٹ_مداخلت_نقاب()
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٹ_Clear_مداخلت_نقاب( x )


    خارجی خالی v_پورٹ_Enter_Critical( خالی );
    خارجی خالی v_پورٹ_Exit_Critical( خالی );

    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    پورٹ_سیٹ_مداخلت_نقاب()
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     پورٹ_CLEAR_مداخلت_نقاب()
    #تعریف_کرو پورٹ_ENTER_CRITICAL()        v_پورٹ_Enter_Critical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()         v_پورٹ_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

    #تعریف_کرو پورٹ_NOP()

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
