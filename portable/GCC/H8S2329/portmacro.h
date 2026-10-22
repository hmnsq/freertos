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
    ബാഹ്യ "C" {
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
#define portCHAR          അക്ഷരം
#define portFLOAT         ദശാംശം
#define portDOUBLE        ഇരട്ട
#define portLONG          long
#define portSHORT         short
#define port_അട്ടി_TYPE    uint8_t
#define portBASE_TYPE     അക്ഷരം

തരനിർവചനം port_അട്ടി_TYPE   അട്ടി_Type_t;
തരനിർവചനം signed അക്ഷരം      BaseType_t;
തരനിർവചനം unsigned അക്ഷരം    UBaseType_t;

#എങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    2
#define port_അട്ടി_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portYIELD()    asm അസ്ഥിര ( "TRAPA #0" )
#define portNOP()      asm അസ്ഥിര ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */
#define portENABLE_INTERRUPTS()     asm അസ്ഥിര ( "ANDC #0x7F, CCR" );
#define portDISABLE_INTERRUPTS()    asm അസ്ഥിര ( "ORC  #0x80, CCR" );

/* Push the CCR then disable interrupts. */
#define portENTER_CRITICAL()            \
    asm അസ്ഥിര ( "STC  CCR, @-ER7" ); \
    portDISABLE_INTERRUPTS();

/* Pop the CCR to set the interrupt masking back to its previous state. */
#define  portEXIT_CRITICAL()    asm അസ്ഥിര ( "LDC  @ER7+, CCR" );
/*-----------------------------------------------------------*/

/* Task utilities. */

/* Context switch macros.  These macros are very simple as the context
 * is saved simply by selecting the saveall attribute of the context switch
 * interrupt service routines.  These macros save and restore the stack
 * pointer to the TCB. */

#define port_SAVE_അട്ടി_POINTER()                  \
    ബാഹ്യ ശൂന്യം * pxCurrentTCB;                   \
                                                  \
    asm അസ്ഥിര (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  ER7, @ER5                   \n\t" \
        );                                        \
    ( ശൂന്യം ) pxCurrentTCB;


#define port_RESTORE_അട്ടി_POINTER()               \
    ബാഹ്യ ശൂന്യം * pxCurrentTCB;                   \
                                                  \
    asm അസ്ഥിര (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  @ER5, ER7                   \n\t" \
        );                                        \
    ( ശൂന്യം ) pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Macros to allow a context switch from within an application ISR. */

#define portENTER_SWITCHING_ISR()    port_SAVE_അട്ടി_POINTER(); {
#define portEXIT_SWITCHING_ISR( x )             \
    എങ്കിൽ( x )                                     \
    {                                           \
        ബാഹ്യ ശൂന്യം vTaskSwitchContext( ശൂന്യം ); \
        vTaskSwitchContext();                   \
    }                                           \
}                                               \
    port_RESTORE_അട്ടി_POINTER();
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
