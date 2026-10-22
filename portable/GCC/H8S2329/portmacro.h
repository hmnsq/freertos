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


#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    বাহ্য "C" {
#endif
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
#define portCHAR          বর্ণ
#define portFLOAT         ভিন্ন
#define portDOUBLE        দ্বিগুণ
#define portLONG          long
#define portSHORT         short
#define port_স্তূপ_TYPE    uint8_t
#define portBASE_TYPE     বর্ণ

প্রকারনির্দেশ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারনির্দেশ signed বর্ণ      BaseType_t;
প্রকারনির্দেশ unsigned বর্ণ    UBaseType_t;

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারনির্দেশ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারনির্দেশ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    2
#define port_স্তূপ_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portYIELD()    asm চঞ্চল ( "TRAPA #0" )
#define portNOP()      asm চঞ্চল ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */
#define portENABLE_INTERRUPTS()     asm চঞ্চল ( "ANDC #0x7F, CCR" );
#define portDISABLE_INTERRUPTS()    asm চঞ্চল ( "ORC  #0x80, CCR" );

/* Push the CCR then disable interrupts. */
#define portENTER_CRITICAL()            \
    asm চঞ্চল ( "STC  CCR, @-ER7" ); \
    portDISABLE_INTERRUPTS();

/* Pop the CCR to set the interrupt masking back to its previous state. */
#define  portEXIT_CRITICAL()    asm চঞ্চল ( "LDC  @ER7+, CCR" );
/*-----------------------------------------------------------*/

/* Task utilities. */

/* Context switch macros.  These macros are very simple as the context
 * is saved simply by selecting the saveall attribute of the context switch
 * interrupt service routines.  These macros save and restore the stack
 * pointer to the TCB. */

#define port_SAVE_স্তূপ_POINTER()                  \
    বাহ্য শূন্য * pxCurrentTCB;                   \
                                                  \
    asm চঞ্চল (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  ER7, @ER5                   \n\t" \
        );                                        \
    ( শূন্য ) pxCurrentTCB;


#define port_RESTORE_স্তূপ_POINTER()               \
    বাহ্য শূন্য * pxCurrentTCB;                   \
                                                  \
    asm চঞ্চল (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  @ER5, ER7                   \n\t" \
        );                                        \
    ( শূন্য ) pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Macros to allow a context switch from within an application ISR. */

#define portENTER_SWITCHING_ISR()    port_SAVE_স্তূপ_POINTER(); {
#define portEXIT_SWITCHING_ISR( x )             \
    যদি( x )                                     \
    {                                           \
        বাহ্য শূন্য vTaskSwitchContext( শূন্য ); \
        vTaskSwitchContext();                   \
    }                                           \
}                                               \
    port_RESTORE_স্তূপ_POINTER();
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
