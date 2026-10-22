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


#اگر_تعریف_نشده PORTMACRO_H
    #تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
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


    #إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
        تعريفنوع uint16_t     TickType_t;
        #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
        تعريفنوع uint32_t     TickType_t;
        #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
    #پایان_اگر
/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کن پورت_پشته_GROWTH      ( -1 )
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
    #تعریف_کن پورت_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجي فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_NVIC_INT_CTRL     ( ( متطاير uint32_t * ) 0xe000ed04 )
#تعریف_کن پورت_NVIC_PENDSVSET    0x10000000
#تعریف_کن پورت_YIELD()                v_پورت_Yield()

#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )         \
    افعل                                                   \
    {                                                    \
        إذا( xSwitchRequired != pdFALSE )                 \
        {                                                \
            trace_ISR_EXIT_مقصد_SCHEDULER();                \
            *( پورت_NVIC_INT_CTRL ) = پورت_NVIC_PENDSVSET; \
        }                                                \
        وإلا                                             \
        {                                                \
            traceISR_EXIT();                             \
        }                                                \
    } طالما( 0 )
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/


/* Critical section management. */

/*
 * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without effecting other
 * registers.  r0 is clobbered.
 */
    #تعریف_کن پورت_مجموعه_وقفه_ماسک()      __set_BASEPRI( config_MAX_SYSCALL_وقفه_اولویت )

/*
 * Set basepri back to 0 without effective other registers.
 * r0 is clobbered.  FAQ:  Setting BASEPRI to 0 is not a bug.  Please see
 * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html before disagreeing.
 */
    #تعریف_کن پورت_CLEAR_وقفه_ماسک()    __set_BASEPRI( 0 )

    خارجي uint32_t ul_پورت_مجموعه_وقفه_ماسک( فراغ );
    خارجي فراغ v_پورت_Clear_وقفه_ماسک( uint32_t ul_New_ماسک );
    #تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ul_پورت_مجموعه_وقفه_ماسک()
    #تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_پورت_Clear_وقفه_ماسک( x )


    خارجي فراغ v_پورت_Enter_Critical( فراغ );
    خارجي فراغ v_پورت_Exit_Critical( فراغ );

    #تعریف_کن پورت_DISABLE_INTERRUPTS()    پورت_مجموعه_وقفه_ماسک()
    #تعریف_کن پورت_ENABLE_INTERRUPTS()     پورت_CLEAR_وقفه_ماسک()
    #تعریف_کن پورت_ENTER_CRITICAL()        v_پورت_Enter_Critical()
    #تعریف_کن پورت_EXIT_CRITICAL()         v_پورت_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

    #تعریف_کن پورت_NOP()

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
