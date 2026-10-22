/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright 2020 Cambridge Consultants Ltd.
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

#شامل <limits.h>
#شامل <stdint.h>

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
#تعریف_کرو پورٹ_ڈھیر_TYPE           غیرعلامتی طویل
#تعریف_کرو پورٹ_بنیاد_TYPE            طویل
#تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    intptr_t

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

قسمتعریف غیرعلامتی طویل    TickType_t;
#تعریف_کرو پورٹ_MAX_DELAY              ( ( TickType_t ) ULONG_MAX )

#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH                   ( -1 )
#تعریف_کرو پورٹ_HAS_ڈھیر_حد_سے_تجاوز_CHECKING    ( 1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_TICK_شرح_MICROSECONDS         ( ( TickType_t ) 1000000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT                 8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
خارجی خالی v_پورٹ_Yield( خالی );

#تعریف_کرو پورٹ_YIELD()                v_پورٹ_Yield()

#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired ) \
    کرو                                           \
    {                                            \
        اگر( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            v_پورٹ_Yield();                        \
        }                                        \
        ورنہ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } جب( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
خارجی خالی v_پورٹ_Disable_Interrupts( خالی );
خارجی خالی v_پورٹ_Enable_Interrupts( خالی );
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب()      ( v_پورٹ_Disable_Interrupts() )
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب()    ( v_پورٹ_Enable_Interrupts() )

خارجی UBaseType_t x_پورٹ_سیٹ_مداخلت_نقاب( خالی );
خارجی خالی v_پورٹ_Clear_مداخلت_نقاب( UBaseType_t x_نقاب );

خارجی خالی v_پورٹ_Enter_Critical( خالی );
خارجی خالی v_پورٹ_Exit_Critical( خالی );
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         x_پورٹ_سیٹ_مداخلت_نقاب()
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٹ_Clear_مداخلت_نقاب( x )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  پورٹ_سیٹ_مداخلت_نقاب()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   پورٹ_CLEAR_مداخلت_نقاب()
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()

/*-----------------------------------------------------------*/

خارجی خالی v_پورٹ_Thread_Dying( خالی * px_Task_مقصد_Delete,
                              متلون بنیاد_Type_t * pxPendYield );
خارجی خالی v_پورٹ_Cancel_Thread( خالی * px_Task_مقصد_Delete );
#تعریف_کرو پورٹ_PRE_TASK_DELETE_HOOK( pv_Task_مقصد_Delete, pxPendYield )    v_پورٹ_Thread_Dying( ( pv_Task_مقصد_Delete ), ( pxPendYield ) )
#تعریف_کرو پورٹ_CLEAN_اوپر_TCB( pxTCB )                                  v_پورٹ_Cancel_Thread( pxTCB )
/*-----------------------------------------------------------*/

#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )         خالی vFunction( خالی * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )               خالی vFunction( خالی * pvParameters )
/*-----------------------------------------------------------*/

/*
 * Tasks run in their own pthreads and context switches between them
 * are always a full memory barrier. ISRs are emulated as signals
 * which also imply a full memory barrier.
 *
 * Thus, only a compiler barrier is needed to prevent the compiler
 * reordering.
 */
#تعریف_کرو پورٹ_حافظہ_BARRIER()                        __asm متلون ( "" ::: "memory" )

خارجی uint32_t ul_پورٹ_Get_تسلسل_وقت( خالی );
#تعریف_کرو پورٹ_CONFIGURE_TIMER_FOR_تسلسل_وقت_STATS()    /* no-op */
#تعریف_کرو پورٹ_GET_تسلسل_وقت_شمار_قدر()            ul_پورٹ_Get_تسلسل_وقت()

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
