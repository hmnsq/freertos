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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

#ضمن <stdlib.h>
#ضمن <stdint.h>
#ضمن <csi_core.h>

خارجي فراغ v_پورټ_Yield( فراغ );

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    class v_پورټ_Yield;
    خارجي "C" {
#د_که_پای
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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;
تعريفنوع فراغ (* portvectorfunc)( فراغ );

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای


/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT    8
#تعریف_کړه پورټ_ډېری_GROWTH      -1
#تعریف_کړه پورټ_MS_PERIOD_TICK    10
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )


ساكن مضمن فراغ v_پورټ_Enable_مداخله( فراغ )
{
    __enable_irq();
}

ساكن مضمن فراغ v_پورټ_Disable_مداخله( فراغ )
{
    __disable_irq();
}

ساكن مضمن پورټ_LONG GetCurrentPSR( فراغ )
{
    أرجع __get_PSR();
}

ساكن مضمن پورټ_LONG SaveLocalPSR( فراغ )
{
    پورټ_LONG flags = __get_PSR();

    __disable_irq();
    أرجع flags;
}

ساكن مضمن فراغ RestoreLocalPSR( پورټ_LONG new_ماسک )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_ماسک )
        : "memory"
        );
}

خارجي فراغ v_پورټ_Enter_Critical( فراغ );
خارجي فراغ v_پورټ_Exit_Critical( فراغ );
خارجي __attribute__( ( naked ) ) فراغ cpu_yeild( فراغ );

#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                  v_پورټ_Disable_مداخله()
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                   v_پورټ_Enable_مداخله()
#تعریف_کړه پورټ_ENTER_CRITICAL()                      v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()                       v_پورټ_Exit_Critical()
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         SaveLocalPSR()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( a )    RestoreLocalPSR( a )

#تعریف_کړه پورټ_NOP()                                 asm ( "nop" )

خارجي پورټ_LONG ulCriticalNesting;
خارجي پورټ_LONG pendsvflag;

#تعریف_کړه پورټ_YIELD()              \
    إذا( ulCriticalNesting == 0 ) \
    {                            \
        v_پورټ_Yield();            \
    }                            \
    وإلا                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    پورټ_NOP(); پورټ_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
    افعل {                                         \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            پورټ_YIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

#تعریف_کړه پورټ_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
