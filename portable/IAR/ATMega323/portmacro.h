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

/*
 * Changes from V1.2.3
 *
 + portCPU_CLOCK_HZ definition changed to 8MHz base 10, previously it
 +    base 16.
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
#నిర్వచించు పోర్టు_CHAR                 అక్షరం
#నిర్వచించు పోర్టు_FLOAT                దశాంశం
#నిర్వచించు పోర్టు_DOUBLE               ద్విగుణ
#నిర్వచించు పోర్టు_LONG                 దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                పూర్ణాంకం
#నిర్వచించు పోర్టు_దొంతర_TYPE           uint8_t
#నిర్వచించు పోర్టు_పునాది_TYPE            అక్షరం
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint16_t

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం గుర్తుగల అక్షరం      పునాది_Type_t;
రకనిర్వచనం గుర్తులేని అక్షరం    UBaseType_t;

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

/* Critical section management. */
బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
#నిర్వచించు పోర్టు_ENTER_CRITICAL()        v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()         v_పోర్టు_Exit_Critical()

#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    asm ( "cli" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     asm ( "sei" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    1
#నిర్వచించు పోర్టు_NOP()    asm ( "nop" )
/*-----------------------------------------------------------*/

/* Kernel utilities. */
శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_YIELD()                v_పోర్టు_Yield()

#నిర్వచితమైతే IAR_MEGA_AVR
    #నిర్వచించు outb( పోర్టు_3, విలువ_3 )    పోర్టు_3 = విలువ_3
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
