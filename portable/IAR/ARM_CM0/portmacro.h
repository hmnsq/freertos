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


#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
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


#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجي فراغ v_پورٹ_Yield( فراغ );
#تعریف_کرو پورٹ_NVIC_INT_CTRL     ( ( متطاير uint32_t * ) 0xe000ed04 )
#تعریف_کرو پورٹ_NVIC_PENDSVSET    0x10000000
#تعریف_کرو پورٹ_YIELD()                v_پورٹ_Yield()
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )         \
    افعل                                                   \
    {                                                    \
        إذا( xSwitchRequired != pdFALSE )                 \
        {                                                \
            trace_ISR_EXIT_منزل_SCHEDULER();                \
            *( پورٹ_NVIC_INT_CTRL ) = پورٹ_NVIC_PENDSVSET; \
        }                                                \
        وإلا                                             \
        {                                                \
            traceISR_EXIT();                             \
        }                                                \
    } طالما( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/


/* Critical section management. */

خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
خارجي uint32_t ul_سیٹ_رکاوٹ_نقاب_From_ISR( فراغ );
خارجي فراغ v_Clear_رکاوٹ_نقاب_From_ISR( uint32_t ul_نقاب );

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  __asm متطاير ( "cpsid i" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   __asm متطاير ( "cpsie i" )
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical()
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ul_سیٹ_رکاوٹ_نقاب_From_ISR()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_Clear_رکاوٹ_نقاب_From_ISR( x )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#جے_بنا_تعریف پورٹ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا );
    #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ویلا )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ویلا )
#جے_انت
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کرو پورٹ_NOP()

#تعریف_کرو پورٹ_INLINE              __inline

#جے_بنا_تعریف پورٹ_FORCE_INLINE
    #تعریف_کرو پورٹ_FORCE_INLINE    مضمن __attribute__( ( always_inline ) )
#جے_انت

/*-----------------------------------------------------------*/

پورٹ_FORCE_INLINE ساكن ادھار_Type_t x_پورٹ_Is_Inside_رکاوٹ( فراغ )
{
    uint32_t ul_Current_رکاوٹ;
    ادھار_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_رکاوٹ )::"memory" );

    إذا( ul_Current_رکاوٹ == 0 )
    {
        xReturn = pdFALSE;
    }
    وإلا
    {
        xReturn = pdTRUE;
    }

    أرجع xReturn;
}

/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#ہدایت diag_suppress=Pa082

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
