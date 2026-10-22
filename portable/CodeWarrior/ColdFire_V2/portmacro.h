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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
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
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE   اوږد

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع اوږد بنسټ_Type_t;
تعريفنوع بینښه اوږد UBaseType_t;

#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT          4
#تعریف_کړه پورټ_ډېری_GROWTH            -1
#تعریف_کړه پورټ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/
uint32_t ul_پورټ_سېټ_IPL( uint32_t );
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    ul_پورټ_سېټ_IPL( config_MAX_SYSCALL_مداخله_لومړیتوب )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     ul_پورټ_سېټ_IPL( 0 )


خارجي فراغ v_پورټ_Enter_Critical( فراغ );
خارجي فراغ v_پورټ_Exit_Critical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()        v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()         v_پورټ_Exit_Critical()

خارجي UBaseType_t ux_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ );
خارجي فراغ v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t );
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()   ul_پورټ_سېټ_IPL( config_MAX_SYSCALL_مداخله_لومړیتوب )
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_Saved_حالت_ثبتوونکی ) ul_پورټ_سېټ_IPL( ux_Saved_حالت_ثبتوونکی )

/*-----------------------------------------------------------*/

/* Task utilities. */

#تعریف_کړه پورټ_NOP()   asm متطاير (  "nop" )

/* Note this will overwrite all other bits in the force register, it is done this way for speed. */
#تعریف_کړه پورټ_YIELD()         MCF_INTC0_INTFRCL = ( 1UL << config_YIELD_مداخله_ویکټور ); پورټ_NOP(); پورټ_NOP() /* -32 as we are using the high word of the 64bit mask. */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters ) __attribute__((noreturn))
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
    افعل                                           \
    {                                            \
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

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
