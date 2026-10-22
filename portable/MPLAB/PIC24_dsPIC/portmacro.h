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
#నిర్వచించు పోర్టు_CHAR        అక్షరం
#నిర్వచించు పోర్టు_FLOAT       దశాంశం
#నిర్వచించు పోర్టు_DOUBLE      ద్విగుణ
#నిర్వచించు పోర్టు_LONG        దీర్ఘ
#నిర్వచించు పోర్టు_SHORT       పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE  uint16_t
#నిర్వచించు పోర్టు_పునాది_TYPE   పొట్టి
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE size_t
#నిర్వచించు SIZE_MAX    ( ( size_t ) -1 )

రకనిర్వచనం పోర్టు_దొంతర_TYPE దొంతర_Type_t;
రకనిర్వచనం పొట్టి పునాది_Type_t;
రకనిర్వచనం గుర్తులేని పొట్టి UBaseType_t;

#ఒకవేళ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t ) 0xffff
/* 16-bit tick type on a 16-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC 1
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు  == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t             TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT          2
#నిర్వచించు పోర్టు_దొంతర_GROWTH            1
#నిర్వచించు పోర్టు_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    సమితి_CPU_IPL( config_KERNEL_అంతరాయం_ప్రాధాన్యత ); __asm అస్థిర ( "NOP" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     సమితి_CPU_IPL( 0 )

/* Note that exiting a critical sectino will set the IPL bits to 0, no matter
what their value was prior to entering the critical section. */
బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
#నిర్వచించు పోర్టు_ENTER_CRITICAL()        v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()         v_పోర్టు_Exit_Critical()
/*-----------------------------------------------------------*/

/* Task utilities. */
బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_YIELD()             asm అస్థిర ( "CALL _vPortYield            \n"     \
                                                "NOP                      " );
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters ) శూన్య vFunction( శూన్య *pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters ) శూన్య vFunction( శూన్య *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#నిర్వచితమైతే __DEBUG
    #నిర్వచించు పోర్టు_REMOVE_STATIC_QUALIFIER
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_NOP()               asm అస్థిర ( "NOP" )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
