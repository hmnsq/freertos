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

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         صحيح
#وصف_ڪريو پورٽ_ڍير_TYPE    uint16_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ننڍو
#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE uint16_t

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
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    asm متطاير ( "DINT" ); asm متطاير ( "NOP" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     asm متطاير ( "EINT" ); asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#وصف_ڪريو پورٽ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

#وصف_ڪريو پورٽ_ENTER_CRITICAL()                                                      \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        پورٽ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
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
خارجي فراغ v_پورٽ_Yield( فراغ ) __attribute__( ( naked ) );
#وصف_ڪريو پورٽ_YIELD()    v_پورٽ_Yield()
#وصف_ڪريو پورٽ_NOP()      asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    2
#وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/* GCC used to define these but doesn't any more */
#وصف_ڪريو مداخلت(ويڪٽر) __attribute__((__interrupt__(ويڪٽر)))
#وصف_ڪريو wakeup __attribute__((__wakeup__))

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
