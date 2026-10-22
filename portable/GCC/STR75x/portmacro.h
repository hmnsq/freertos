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
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#تعریف_کرو پورٹ_YIELD()    asm متطاير ( "SWI 0" )
#تعریف_کرو پورٹ_NOP()      asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions in
 * portISR.c to ensure a switch to ARM mode.  When THUMB_INTERWORK is not
 * defined then the utilities are defined as macros here - as per other ports.
 */

#جے_تعریف_شدہ THUMB_INTERWORK

    خارجي فراغ v_پورٹ_Disable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );
    خارجي فراغ v_پورٹ_Enable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );

    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    v_پورٹ_Disable_Interrupts_From_Thumb()
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     v_پورٹ_Enable_Interrupts_From_Thumb()

#وإلا

    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                       \
    asm متطاير (                                                         \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "ORR    R0, R0, #0xC0   \n\t"   /* Disable IRQ, FIQ.            */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                        \
    asm متطاير (                                                         \
        "STMDB  SP!, {R0}       \n\t"   /* Push R0.                     */ \
        "MRS    R0, CPSR        \n\t"   /* Get CPSR.                    */ \
        "BIC    R0, R0, #0xC0   \n\t"   /* Enable IRQ, FIQ.             */ \
        "MSR    CPSR, R0        \n\t"   /* Write back modified value.   */ \
        "LDMIA  SP!, {R0}           " ) /* Pop R0.                      */

#جے_انت /* THUMB_INTERWORK */

خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
خارجي فراغ v_پورٹ_Exit_Critical( فراغ );

#تعریف_کرو پورٹ_ENTER_CRITICAL()    v_پورٹ_Enter_Critical();
#تعریف_کرو پورٹ_EXIT_CRITICAL()     v_پورٹ_Exit_Critical();
/*-----------------------------------------------------------*/

/* Task utilities. */
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        خارجي فراغ vTaskSwitchContext( فراغ );  \
                                                 \
        إذا( xSwitchRequired )                    \
        {                                        \
            trace_ISR_EXIT_منزل_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    }
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
