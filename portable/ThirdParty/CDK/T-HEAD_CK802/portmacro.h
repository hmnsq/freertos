/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
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
 */

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#شامل <stdlib.h>
#شامل <stdint.h>
#شامل <csi_core.h>

خارجی خالی v_پورٹ_Yield( خالی );

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    class v_پورٹ_Yield;
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
قسمتعریف خالی (* portvectorfunc)( خالی );

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم


/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#تعریف_کرو پورٹ_ڈھیر_GROWTH      -1
#تعریف_کرو پورٹ_MS_PERIOD_TICK    10
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )


ساکن اندرونی خالی v_پورٹ_Enable_مداخلت( خالی )
{
    __enable_irq();
}

ساکن اندرونی خالی v_پورٹ_Disable_مداخلت( خالی )
{
    __disable_irq();
}

ساکن اندرونی پورٹ_LONG GetCurrentPSR( خالی )
{
    واپس __get_PSR();
}

ساکن اندرونی پورٹ_LONG SaveLocalPSR( خالی )
{
    پورٹ_LONG flags = __get_PSR();

    __disable_irq();
    واپس flags;
}

ساکن اندرونی خالی RestoreLocalPSR( پورٹ_LONG new_نقاب )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_نقاب )
        : "memory"
        );
}

خارجی خالی v_پورٹ_Enter_Critical( خالی );
خارجی خالی v_پورٹ_Exit_Critical( خالی );
خارجی __attribute__( ( naked ) ) خالی cpu_yeild( خالی );

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  v_پورٹ_Disable_مداخلت()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   v_پورٹ_Enable_مداخلت()
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         SaveLocalPSR()
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( a )    RestoreLocalPSR( a )

#تعریف_کرو پورٹ_NOP()                                 asm ( "nop" )

خارجی پورٹ_LONG ulCriticalNesting;
خارجی پورٹ_LONG pendsvflag;

#تعریف_کرو پورٹ_YIELD()              \
    اگر( ulCriticalNesting == 0 ) \
    {                            \
        v_پورٹ_Yield();            \
    }                            \
    ورنہ                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    پورٹ_NOP(); پورٹ_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired ) \
    کرو {                                         \
        اگر( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            پورٹ_YIELD();                         \
        }                                        \
        ورنہ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } جب( 0 )

#تعریف_کرو پورٹ_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
