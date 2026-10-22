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

#ଅନ୍ତର୍ଭାଵ "xexception_l.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    ବାହ୍ୟ "C" {
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
#define portCHAR          ଅକ୍ଷର
#define portFLOAT         ଦଶମିକ
#define portDOUBLE        ଦ୍ୱିଗୁଣ
#define portLONG          long
#define portSHORT         short
#define port_ଗଦା_TYPE    uint32_t
#define portBASE_TYPE     long

ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE   ଗଦା_Type_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା long             BaseType_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned long    UBaseType_t;

#ଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#ଅନ୍ୟଥା
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* This port uses the critical nesting count from the TCB rather than
 * maintaining a separate value and then saving this value in the task stack. */
#define portCRITICAL_NESTING_IN_TCB    1

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS()    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
#define portENABLE_INTERRUPTS()     XExc_mEnableExceptions( XEXC_NON_CRITICAL );

/*-----------------------------------------------------------*/

/* Critical section macros. */
ଶୂନ୍ୟ vTaskEnterCritical( ଶୂନ୍ୟ );
ଶୂନ୍ୟ vTaskExitCritical( ଶୂନ୍ୟ );
#define portENTER_CRITICAL()    vTaskEnterCritical()
#define portEXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/

/* Task utilities. */
ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ );
#define portYIELD()             asm ଅସ୍ଥିର ( "SC \n\t NOP" )
#define portYIELD_FROM_ISR()    vTaskSwitchContext()

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_ଗଦା_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()    asm ଅସ୍ଥିର ( "NOP" )

/* There are 32 * 32bit floating point registers, plus the FPSCR to save. */
#define portNO_FLOP_REGISTERS_TO_SAVE    ( 32 + 1 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )

/* Port specific interrupt handling functions. */
ଶୂନ୍ୟ vPortSetupInterruptController( ଶୂନ୍ୟ );
BaseType_t xPortInstallInterruptHandler( uint8_t ucInterruptID,
                                         XInterruptHandler pxHandler,
                                         ଶୂନ୍ୟ * pvCallBackRef );

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
