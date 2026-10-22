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
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint8_t
#تعریف_کرو پورٹ_ادھار_TYPE     حرف

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع نشانیوالا حرف      ادھار_Type_t;
تعريفنوع بنانشانی حرف    UBaseType_t;

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
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    2
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_YIELD()    asm متطاير ( "TRAPA #0" )
#تعریف_کرو پورٹ_NOP()      asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     asm متطاير ( "ANDC #0x7F, CCR" );
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    asm متطاير ( "ORC  #0x80, CCR" );

/* Push the CCR then disable interrupts. */
#تعریف_کرو پورٹ_ENTER_CRITICAL()            \
    asm متطاير ( "STC  CCR, @-ER7" ); \
    پورٹ_DISABLE_INTERRUPTS();

/* Pop the CCR to set the interrupt masking back to its previous state. */
#تعریف_کرو  پورٹ_EXIT_CRITICAL()    asm متطاير ( "LDC  @ER7+, CCR" );
/*-----------------------------------------------------------*/

/* Task utilities. */

/* Context switch macros.  These macros are very simple as the context
 * is saved simply by selecting the saveall attribute of the context switch
 * interrupt service routines.  These macros save and restore the stack
 * pointer to the TCB. */

#تعریف_کرو پورٹ_SAVE_ڈھیر_اشارہ_گر()                  \
    خارجي فراغ * pxCurrentTCB;                   \
                                                  \
    asm متطاير (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  ER7, @ER5                   \n\t" \
        );                                        \
    ( فراغ ) pxCurrentTCB;


#تعریف_کرو پورٹ_RESTORE_ڈھیر_اشارہ_گر()               \
    خارجي فراغ * pxCurrentTCB;                   \
                                                  \
    asm متطاير (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  @ER5, ER7                   \n\t" \
        );                                        \
    ( فراغ ) pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Macros to allow a context switch from within an application ISR. */

#تعریف_کرو پورٹ_ENTER_SWITCHING_ISR()    پورٹ_SAVE_ڈھیر_اشارہ_گر(); {
#تعریف_کرو پورٹ_EXIT_SWITCHING_ISR( x )             \
    إذا( x )                                     \
    {                                           \
        خارجي فراغ vTaskSwitchContext( فراغ ); \
        vTaskSwitchContext();                   \
    }                                           \
}                                               \
    پورٹ_RESTORE_ڈھیر_اشارہ_گر();
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
