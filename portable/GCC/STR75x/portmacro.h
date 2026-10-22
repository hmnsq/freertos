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
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_پشته_GROWTH      ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT    8
#تعریف_کن پورت_YIELD()    asm متطاير ( "SWI 0" )
#تعریف_کن پورت_NOP()      asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions in
 * portISR.c to ensure a switch to ARM mode.  When THUMB_INTERWORK is not
 * defined then the utilities are defined as macros here - as per other ports.
 */

#اگر_تعریف_شده THUMB_INTERWORK

    خارجي فراغ v_پورت_Disable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );
    خارجي فراغ v_پورت_Enable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );

    #تعریف_کن پورت_DISABLE_INTERRUPTS()    v_پورت_Disable_Interrupts_From_Thumb()
    #تعریف_کن پورت_ENABLE_INTERRUPTS()     v_پورت_Enable_Interrupts_From_Thumb()

#وإلا

    #تعریف_کن پورت_DISABLE_INTERRUPTS()                                       \
    asm متطاير (                                                         \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "ORR    R0, R0, #0xC0   \n\t"   /* Disable IRQ, FIQ.            */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

    #تعریف_کن پورت_ENABLE_INTERRUPTS()                                        \
    asm متطاير (                                                         \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "BIC    R0, R0, #0xC0   \n\t"   /* Enable IRQ, FIQ.             */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

#پایان_اگر /* THUMB_INTERWORK */

خارجي فراغ v_پورت_Enter_Critical( فراغ );
خارجي فراغ v_پورت_Exit_Critical( فراغ );

#تعریف_کن پورت_ENTER_CRITICAL()    v_پورت_Enter_Critical();
#تعریف_کن پورت_EXIT_CRITICAL()     v_پورت_Exit_Critical();
/*-----------------------------------------------------------*/

/* Task utilities. */
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        خارجي فراغ vTaskSwitchContext( فراغ );  \
                                                 \
        إذا( xSwitchRequired )                    \
        {                                        \
            trace_ISR_EXIT_مقصد_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    }
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
