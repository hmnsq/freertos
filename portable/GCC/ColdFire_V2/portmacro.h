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
    বাহ্যিক "C" {
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
#define portCHAR          অক্ষর
#define portFLOAT         দশমিক
#define portDOUBLE        দ্বিগুণ
#define portLONG          long
#define portSHORT         short
#define port_স্তূপ_TYPE    uint32_t
#define portBASE_TYPE     long

প্রকারলেখ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারলেখ long             BaseType_t;
প্রকারলেখ unsigned long    UBaseType_t;

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারলেখ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#নতুবা_যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারলেখ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    4
#define port_স্তূপ_GROWTH      -1
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/
uint32_t ulPortSetIPL( uint32_t );
#define portDISABLE_INTERRUPTS()    ulPortSetIPL( configMAX_SYSCALL_INTERRUPT_PRIORITY )
#define portENABLE_INTERRUPTS()     ulPortSetIPL( 0 )


বাহ্যিক শূন্য vPortEnterCritical( শূন্য );
বাহ্যিক শূন্য vPortExitCritical( শূন্য );
#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()

বাহ্যিক UBaseType_t uxPortSetInterruptMaskFromISR( শূন্য );
বাহ্যিক শূন্য vPortClearInterruptMaskFromISR( UBaseType_t );
#define portSET_INTERRUPT_MASK_FROM_ISR()                             ulPortSetIPL( configMAX_SYSCALL_INTERRUPT_PRIORITY )
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedStatusRegister )    ulPortSetIPL( uxSavedStatusRegister )

/*-----------------------------------------------------------*/

/* Task utilities. */

#define portNOP()      asm অস্থির ( "nop" )

/* Note this will overwrite all other bits in the force register, it is done this way for speed. */
#define portYIELD()    MCF_INTC0_INTFRCL = ( 1UL << configYIELD_INTERRUPT_VECTOR ); portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    করো                                           \
    {                                            \
        যদি( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        অন্যথা                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } যখন( 0 )


/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
