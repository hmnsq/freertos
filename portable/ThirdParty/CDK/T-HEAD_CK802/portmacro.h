/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
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
 */

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <csi_core.h>

బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    class v_పోర్టు_Yield;
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
రకనిర్వచనం శూన్య (* portvectorfunc)( శూన్య );

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు


/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8
#నిర్వచించు పోర్టు_దొంతర_GROWTH      -1
#నిర్వచించు పోర్టు_MS_PERIOD_TICK    10
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )


స్థిర అంతఃవరుస శూన్య v_పోర్టు_Enable_అంతరాయం( శూన్య )
{
    __enable_irq();
}

స్థిర అంతఃవరుస శూన్య v_పోర్టు_Disable_అంతరాయం( శూన్య )
{
    __disable_irq();
}

స్థిర అంతఃవరుస పోర్టు_LONG GetCurrentPSR( శూన్య )
{
    తిరిగి __get_PSR();
}

స్థిర అంతఃవరుస పోర్టు_LONG SaveLocalPSR( శూన్య )
{
    పోర్టు_LONG flags = __get_PSR();

    __disable_irq();
    తిరిగి flags;
}

స్థిర అంతఃవరుస శూన్య RestoreLocalPSR( పోర్టు_LONG new_ముసుగు )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_ముసుగు )
        : "memory"
        );
}

బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
బాహ్య __attribute__( ( naked ) ) శూన్య cpu_yeild( శూన్య );

#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  v_పోర్టు_Disable_అంతరాయం()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   v_పోర్టు_Enable_అంతరాయం()
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                      v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()                       v_పోర్టు_Exit_Critical()
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         SaveLocalPSR()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( a )    RestoreLocalPSR( a )

#నిర్వచించు పోర్టు_NOP()                                 asm ( "nop" )

బాహ్య పోర్టు_LONG ulCriticalNesting;
బాహ్య పోర్టు_LONG pendsvflag;

#నిర్వచించు పోర్టు_YIELD()              \
    ఒకవేళ( ulCriticalNesting == 0 ) \
    {                            \
        v_పోర్టు_Yield();            \
    }                            \
    లేకపోతే                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    పోర్టు_NOP(); పోర్టు_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters ) __attribute__( ( noreturn ) )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )
/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired ) \
    చేయి {                                         \
        ఒకవేళ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();        \
            పోర్టు_YIELD();                         \
        }                                        \
        లేకపోతే                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } అయితే( 0 )

#నిర్వచించు పోర్టు_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
