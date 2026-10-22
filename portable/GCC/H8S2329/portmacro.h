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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint8_t
#تعریف_کړه پورټ_بنسټ_TYPE     حرف

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع نښهدار حرف      بنسټ_Type_t;
تعريفنوع بینښه حرف    UBaseType_t;

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

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT    2
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_YIELD()    asm متطاير ( "TRAPA #0" )
#تعریف_کړه پورټ_NOP()      asm متطاير ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     asm متطاير ( "ANDC #0x7F, CCR" );
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    asm متطاير ( "ORC  #0x80, CCR" );

/* Push the CCR then disable interrupts. */
#تعریف_کړه پورټ_ENTER_CRITICAL()            \
    asm متطاير ( "STC  CCR, @-ER7" ); \
    پورټ_DISABLE_INTERRUPTS();

/* Pop the CCR to set the interrupt masking back to its previous state. */
#تعریف_کړه  پورټ_EXIT_CRITICAL()    asm متطاير ( "LDC  @ER7+, CCR" );
/*-----------------------------------------------------------*/

/* Task utilities. */

/* Context switch macros.  These macros are very simple as the context
 * is saved simply by selecting the saveall attribute of the context switch
 * interrupt service routines.  These macros save and restore the stack
 * pointer to the TCB. */

#تعریف_کړه پورټ_SAVE_ډېری_اشاره_ګر()                  \
    خارجي فراغ * pxCurrentTCB;                   \
                                                  \
    asm متطاير (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  ER7, @ER5                   \n\t" \
        );                                        \
    ( فراغ ) pxCurrentTCB;


#تعریف_کړه پورټ_RESTORE_ډېری_اشاره_ګر()               \
    خارجي فراغ * pxCurrentTCB;                   \
                                                  \
    asm متطاير (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  @ER5, ER7                   \n\t" \
        );                                        \
    ( فراغ ) pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Macros to allow a context switch from within an application ISR. */

#تعریف_کړه پورټ_ENTER_SWITCHING_ISR()    پورټ_SAVE_ډېری_اشاره_ګر(); {
#تعریف_کړه پورټ_EXIT_SWITCHING_ISR( x )             \
    إذا( x )                                     \
    {                                           \
        خارجي فراغ vTaskSwitchContext( فراغ ); \
        vTaskSwitchContext();                   \
    }                                           \
}                                               \
    پورټ_RESTORE_ډېری_اشاره_ګر();
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
