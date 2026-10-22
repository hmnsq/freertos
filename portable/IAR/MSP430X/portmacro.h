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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

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
#وصف_ڪريو پورٽ_CHAR         حرف
#وصف_ڪريو پورٽ_FLOAT        عائم
#وصف_ڪريو پورٽ_DOUBLE       مزدوج
#وصف_ڪريو پورٽ_LONG         ڊگهو
#وصف_ڪريو پورٽ_SHORT        صحيح
#وصف_ڪريو پورٽ_بنياد_TYPE    ننڍو

/* The stack type changes depending on the data model. */
#إذا ( __DATA_MODEL__ == __DATA_MODEL_SMALL__ )
    #وصف_ڪريو پورٽ_ڍير_TYPE           uint16_t
    #وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint16_t
#وإلا
    #وصف_ڪريو پورٽ_ڍير_TYPE           uint32_t
#جيڪڏهن_پورو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ننڍو            بنياد_Type_t;
تعريفنوع بنانشان ننڍو   UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو

/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    __asm متطاير ( "DINT\n" "NOP" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     __asm متطاير ( "NOP\n" "EINT\n" "NOP" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#وصف_ڪريو پورٽ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

#وصف_ڪريو پورٽ_ENTER_CRITICAL()                                                     \
    {                                                                            \
        خارجي متطاير uint16_t usCriticalNesting;                              \
                                                                                 \
        پورٽ_DISABLE_INTERRUPTS();                                                \
                                                                                 \
        /* Now interrupts are disabled usCriticalNesting can be accessed */      \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */ \
        /* times portENTER_CRITICAL() has been called. */                        \
        usCriticalNesting++;                                                     \
    }

#وصف_ڪريو پورٽ_EXIT_CRITICAL()                                                         \
    {                                                                               \
        خارجي متطاير uint16_t usCriticalNesting;                                 \
                                                                                    \
        إذا( usCriticalNesting > پورٽ_NO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            إذا( usCriticalNesting == پورٽ_NO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                پورٽ_ENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
خارجي فراغ v_پورٽ_Yield( فراغ );
#وصف_ڪريو پورٽ_YIELD()    v_پورٽ_Yield()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    2
#وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_NOP()             __asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )                               افعل { إذا( x ) v_پورٽ_Yield( ); } طالما( 0 )

فراغ v_Application_تياري_Timer_مداخلت( فراغ );

/* sizeof( int ) != sizeof( long ) so a full printf() library is required if
 * run time stats information is to be displayed. */
#وصف_ڪريو پورٽ_LU_PRINTF_SPECIFIER_REQUIRED

#جيڪڏهن_پورو /* PORTMACRO_H */
