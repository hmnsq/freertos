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
#నిర్వచించు పోర్టు_DOUBLE      దీర్ఘ
#నిర్వచించు పోర్టు_LONG        దీర్ఘ
#నిర్వచించు పోర్టు_SHORT       పూర్ణాంకం
#నిర్వచించు పోర్టు_దొంతర_TYPE  uint16_t
#నిర్వచించు పోర్టు_పునాది_TYPE   పొట్టి

రకనిర్వచనం పోర్టు_దొంతర_TYPE దొంతర_Type_t;
రకనిర్వచనం పొట్టి పునాది_Type_t;
రకనిర్వచనం గుర్తులేని పొట్టి UBaseType_t;


రకనిర్వచనం శూన్య ( __interrupt __far *pxISR )();

#ఒకవేళ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు  == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t             TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Critical section handling. */
#నిర్వచించు పోర్టు_ENTER_CRITICAL()            __asm{ pushf }  \
                                        __asm{ cli   }  \

#నిర్వచించు పోర్టు_EXIT_CRITICAL()             __asm{ popf }

#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()        __asm{ cli }

#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()         __asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_NOP()                       __asm{ nop }
#నిర్వచించు పోర్టు_దొంతర_GROWTH                ( -1 )
#నిర్వచించు పోర్టు_SWITCH_INT_సంఖ్య           0x80
#నిర్వచించు పోర్టు_YIELD()                     __asm{ పూర్ణాంకం పోర్టు_SWITCH_INT_సంఖ్య }
#నిర్వచించు పోర్టు_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT              2
#నిర్వచించు పోర్టు_INITIAL_SW                  ( ( పోర్టు_దొంతర_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#నిర్వచించు పోర్టు_ఆదానం_BYTE( xAddr )             inp( xAddr )
#నిర్వచించు పోర్టు_OUTPUT_BYTE( xAddr, uc_విలువ )   outp( xAddr, uc_విలువ )
#నిర్వచించు పోర్టు_ఆదానం_మాట( xAddr )             inpw( xAddr )
#నిర్వచించు పోర్టు_OUTPUT_మాట( xAddr, us_విలువ )   outpw( xAddr, us_విలువ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vTaskFunction, vParameters ) శూన్య vTaskFunction( శూన్య *pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vTaskFunction, vParameters ) శూన్య vTaskFunction( శూన్య *pvParameters )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
