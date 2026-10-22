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
#تعریف_کړه پورټ_CHAR         حرف
#تعریف_کړه پورټ_FLOAT        عائم
#تعریف_کړه پورټ_DOUBLE       مزدوج
#تعریف_کړه پورټ_LONG         اوږد
#تعریف_کړه پورټ_SHORT        صحيح
#تعریف_کړه پورټ_بنسټ_TYPE    لنډ

/* The stack type changes depending on the data model. */
#إذا ( __DATA_MODEL__ == __DATA_MODEL_SMALL__ )
    #تعریف_کړه پورټ_ډېری_TYPE           uint16_t
    #تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    uint16_t
#وإلا
    #تعریف_کړه پورټ_ډېری_TYPE           uint32_t
#د_که_پای

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع لنډ            بنسټ_Type_t;
تعريفنوع بینښه لنډ   UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای

/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    __asm متطاير ( "DINT\n" "NOP" )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     __asm متطاير ( "NOP\n" "EINT\n" "NOP" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#تعریف_کړه پورټ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

#تعریف_کړه پورټ_ENTER_CRITICAL()                                                     \
    {                                                                            \
        خارجي متطاير uint16_t usCriticalNesting;                              \
                                                                                 \
        پورټ_DISABLE_INTERRUPTS();                                                \
                                                                                 \
        /* Now interrupts are disabled usCriticalNesting can be accessed */      \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */ \
        /* times portENTER_CRITICAL() has been called. */                        \
        usCriticalNesting++;                                                     \
    }

#تعریف_کړه پورټ_EXIT_CRITICAL()                                                         \
    {                                                                               \
        خارجي متطاير uint16_t usCriticalNesting;                                 \
                                                                                    \
        إذا( usCriticalNesting > پورټ_NO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            إذا( usCriticalNesting == پورټ_NO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                پورټ_ENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
خارجي فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()    v_پورټ_Yield()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT    2
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_NOP()             __asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کړه پورټ_YIELD_FROM_ISR( x )                               افعل { إذا( x ) v_پورټ_Yield( ); } طالما( 0 )

فراغ v_Application_تیاری_Timer_مداخله( فراغ );

/* sizeof( int ) != sizeof( long ) so a full printf() library is required if
 * run time stats information is to be displayed. */
#تعریف_کړه پورټ_LU_PRINTF_SPECIFIER_REQUIRED

#د_که_پای /* PORTMACRO_H */
