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


#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint8_t
#परिभाषय पत्तनम्_आधारः_TYPE     वर्ण

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश चिह्नित वर्ण      आधारः_Type_t;
प्रकारनिर्देश अचिह्नित वर्ण    UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    2
#परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_YIELD()    asm चञ्चल ( "TRAPA #0" )
#परिभाषय पत्तनम्_NOP()      asm चञ्चल ( "NOP" )
/*-----------------------------------------------------------*/

/* Critical section handling. */
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     asm चञ्चल ( "ANDC #0x7F, CCR" );
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    asm चञ्चल ( "ORC  #0x80, CCR" );

/* Push the CCR then disable interrupts. */
#परिभाषय पत्तनम्_ENTER_CRITICAL()            \
    asm चञ्चल ( "STC  CCR, @-ER7" ); \
    पत्तनम्_DISABLE_INTERRUPTS();

/* Pop the CCR to set the interrupt masking back to its previous state. */
#परिभाषय  पत्तनम्_EXIT_CRITICAL()    asm चञ्चल ( "LDC  @ER7+, CCR" );
/*-----------------------------------------------------------*/

/* Task utilities. */

/* Context switch macros.  These macros are very simple as the context
 * is saved simply by selecting the saveall attribute of the context switch
 * interrupt service routines.  These macros save and restore the stack
 * pointer to the TCB. */

#परिभाषय पत्तनम्_SAVE_राशिः_POINTER()                  \
    बाह्य शून्य * pxCurrentTCB;                   \
                                                  \
    asm चञ्चल (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  ER7, @ER5                   \n\t" \
        );                                        \
    ( शून्य ) pxCurrentTCB;


#परिभाषय पत्तनम्_RESTORE_राशिः_POINTER()               \
    बाह्य शून्य * pxCurrentTCB;                   \
                                                  \
    asm चञ्चल (                                \
        "MOV.L  @_pxCurrentTCB, ER5         \n\t" \
        "MOV.L  @ER5, ER7                   \n\t" \
        );                                        \
    ( शून्य ) pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Macros to allow a context switch from within an application ISR. */

#परिभाषय पत्तनम्_ENTER_SWITCHING_ISR()    पत्तनम्_SAVE_राशिः_POINTER(); {
#परिभाषय पत्तनम्_EXIT_SWITCHING_ISR( x )             \
    यदि( x )                                     \
    {                                           \
        बाह्य शून्य vTaskSwitchContext( शून्य ); \
        vTaskSwitchContext();                   \
    }                                           \
}                                               \
    पत्तनम्_RESTORE_राशिः_POINTER();
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
