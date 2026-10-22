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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

#ضمن <stdlib.h>
#ضمن <stdint.h>
#ضمن <csi_core.h>

خارجي فراغ v_پورت_Yield( فراغ );

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    class v_پورت_Yield;
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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;
تعريفنوع فراغ (* portvectorfunc)( فراغ );

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر


/* Hardware specifics. */
#تعریف_کن پورت_BYTE_ALIGNMENT    8
#تعریف_کن پورت_پشته_GROWTH      -1
#تعریف_کن پورت_MS_PERIOD_TICK    10
#تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )


ساكن مضمن فراغ v_پورت_Enable_وقفه( فراغ )
{
    __enable_irq();
}

ساكن مضمن فراغ v_پورت_Disable_وقفه( فراغ )
{
    __disable_irq();
}

ساكن مضمن پورت_LONG GetCurrentPSR( فراغ )
{
    أرجع __get_PSR();
}

ساكن مضمن پورت_LONG SaveLocalPSR( فراغ )
{
    پورت_LONG flags = __get_PSR();

    __disable_irq();
    أرجع flags;
}

ساكن مضمن فراغ RestoreLocalPSR( پورت_LONG new_ماسک )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_ماسک )
        : "memory"
        );
}

خارجي فراغ v_پورت_Enter_Critical( فراغ );
خارجي فراغ v_پورت_Exit_Critical( فراغ );
خارجي __attribute__( ( naked ) ) فراغ cpu_yeild( فراغ );

#تعریف_کن پورت_DISABLE_INTERRUPTS()                  v_پورت_Disable_وقفه()
#تعریف_کن پورت_ENABLE_INTERRUPTS()                   v_پورت_Enable_وقفه()
#تعریف_کن پورت_ENTER_CRITICAL()                      v_پورت_Enter_Critical()
#تعریف_کن پورت_EXIT_CRITICAL()                       v_پورت_Exit_Critical()
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         SaveLocalPSR()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( a )    RestoreLocalPSR( a )

#تعریف_کن پورت_NOP()                                 asm ( "nop" )

خارجي پورت_LONG ulCriticalNesting;
خارجي پورت_LONG pendsvflag;

#تعریف_کن پورت_YIELD()              \
    إذا( ulCriticalNesting == 0 ) \
    {                            \
        v_پورت_Yield();            \
    }                            \
    وإلا                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    پورت_NOP(); پورت_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
    افعل {                                         \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            پورت_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

#تعریف_کن پورت_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
