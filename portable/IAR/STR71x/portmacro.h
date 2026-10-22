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

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

#அந்தர்பாவ <intrinsics.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    வெளி "C" {
#endif
/* *INDENT-ON* */


/* Type definitions. */
#define portCHAR          எழுத்து
#define portFLOAT         தசம
#define portDOUBLE        இரட்டை
#define portLONG          long
#define portSHORT         short
#define port_அடுக்கு_TYPE    uint32_t
#define portBASE_TYPE     long

வகைவரை port_அடுக்கு_TYPE   அடுக்கு_Type_t;
வகைவரை long             BaseType_t;
வகைவரை unsigned long    UBaseType_t;


#எனில் ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    வகைவரை uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#அல்லதெனில் ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    வகைவரை uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#இல்லையெனில்
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define port_அடுக்கு_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8
#define portYIELD()    asm ( "SWI 0" )
#define portNOP()      asm ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */
__arm __interwork வெறுமை vPortDisableInterruptsFromThumb( வெறுமை );
__arm __interwork வெறுமை vPortEnableInterruptsFromThumb( வெறுமை );
__arm __interwork வெறுமை vPortEnterCritical( வெறுமை );
__arm __interwork வெறுமை vPortExitCritical( வெறுமை );

#define portDISABLE_INTERRUPTS()    __disable_interrupt()
#define portENABLE_INTERRUPTS()     __enable_interrupt()
#define portENTER_CRITICAL()        vPortEnterCritical()
#define portEXIT_CRITICAL()         vPortExitCritical()
/*-----------------------------------------------------------*/

/* Task utilities. */
#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        வெளி வெறுமை vTaskSwitchContext( வெறுமை );  \
                                                 \
        எனில்( xSwitchRequired )                    \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        இல்லையெனில்                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    }
/*-----------------------------------------------------------*/

/* EIC utilities. */
#define portEIC_CICR_ADDR    *( ( uint32_t * ) 0xFFFFF804 )
#define portEIC_IPR_ADDR     *( ( uint32_t * ) 0xFFFFF840 )
#define portCLEAR_EIC()    portEIC_IPR_ADDR = 0x01 << portEIC_CICR_ADDR

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    வெறுமை vFunction( வெறுமை * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          வெறுமை vFunction( வெறுமை * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
