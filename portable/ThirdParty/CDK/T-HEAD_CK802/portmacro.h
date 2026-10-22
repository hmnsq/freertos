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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#ضمن <stdlib.h>
#ضمن <stdint.h>
#ضمن <csi_core.h>

خارجي فراغ v_پورٹ_Yield( فراغ );

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    class v_پورٹ_Yield;
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
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع لما             ادھار_Type_t;
تعريفنوع بنانشانی لما    UBaseType_t;
تعريفنوع فراغ (* portvectorfunc)( فراغ );

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت


/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#تعریف_کرو پورٹ_ڈھیر_GROWTH      -1
#تعریف_کرو پورٹ_MS_PERIOD_TICK    10
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )


ساكن مضمن فراغ v_پورٹ_Enable_رکاوٹ( فراغ )
{
    __enable_irq();
}

ساكن مضمن فراغ v_پورٹ_Disable_رکاوٹ( فراغ )
{
    __disable_irq();
}

ساكن مضمن پورٹ_LONG GetCurrentPSR( فراغ )
{
    أرجع __get_PSR();
}

ساكن مضمن پورٹ_LONG SaveLocalPSR( فراغ )
{
    پورٹ_LONG flags = __get_PSR();

    __disable_irq();
    أرجع flags;
}

ساكن مضمن فراغ RestoreLocalPSR( پورٹ_LONG new_نقاب )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_نقاب )
        : "memory"
        );
}

خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
خارجي __attribute__( ( naked ) ) فراغ cpu_yeild( فراغ );

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  v_پورٹ_Disable_رکاوٹ()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   v_پورٹ_Enable_رکاوٹ()
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         SaveLocalPSR()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( a )    RestoreLocalPSR( a )

#تعریف_کرو پورٹ_NOP()                                 asm ( "nop" )

خارجي پورٹ_LONG ulCriticalNesting;
خارجي پورٹ_LONG pendsvflag;

#تعریف_کرو پورٹ_YIELD()              \
    إذا( ulCriticalNesting == 0 ) \
    {                            \
        v_پورٹ_Yield();            \
    }                            \
    وإلا                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    پورٹ_NOP(); پورٹ_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired ) \
    افعل {                                         \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورٹ_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

#تعریف_کرو پورٹ_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
