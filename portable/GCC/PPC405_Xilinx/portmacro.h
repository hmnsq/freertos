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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

#అన్తర్భావ "xexception_l.h"

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
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
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* This port uses the critical nesting count from the TCB rather than
 * maintaining a separate value and then saving this value in the task stack. */
#నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    1

/* Interrupt control macros. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     XExc_mEnableExceptions( XEXC_NON_CRITICAL );

/*-----------------------------------------------------------*/

/* Critical section macros. */
శూన్య vTaskEnterCritical( శూన్య );
శూన్య vTaskExitCritical( శూన్య );
#నిర్వచించు పోర్టు_ENTER_CRITICAL()    vTaskEnterCritical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/

/* Task utilities. */
శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_YIELD()             asm అస్థిర ( "SC \n\t NOP" )
#నిర్వచించు పోర్టు_YIELD_FROM_ISR()    vTaskSwitchContext()

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_NOP()    asm అస్థిర ( "NOP" )

/* There are 32 * 32bit floating point registers, plus the FPSCR to save. */
#నిర్వచించు పోర్టు_NO_FLOP_REGISTERS_గమ్యం_SAVE    ( 32 + 1 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* Port specific interrupt handling functions. */
శూన్య v_పోర్టు_అమరిక_అంతరాయం_Controller( శూన్య );
పునాది_Type_t x_పోర్టు_Install_అంతరాయం_Handler( uint8_t uc_అంతరాయం_ID,
                                         XInterruptHandler pxHandler,
                                         శూన్య * pv_Call_వెనుక_Ref );

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
