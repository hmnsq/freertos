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

/* Standard includes. */
#అన్తర్భావ <stdlib.h>

/* Kernel includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Machine includes */
#అన్తర్భావ <machine/counter.h>
#అన్తర్భావ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#నిర్వచించు పోర్టు_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );
/*-----------------------------------------------------------*/

దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_శిఖరం_యొక్క_దొంతర -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_శిఖరం_యొక్క_దొంతర[ 16 ] = 0;
    px_శిఖరం_యొక్క_దొంతర[ 15 ] = పోర్టు_INITIAL_PSR;
    px_శిఖరం_యొక్క_దొంతర[ 14 ] = ( uint32_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర[ 13 ] = 0x00000000UL; /* R15. */
    px_శిఖరం_యొక్క_దొంతర[ 12 ] = 0x00000000UL; /* R14. */
    px_శిఖరం_యొక్క_దొంతర[ 11 ] = 0x0d0d0d0dUL;
    px_శిఖరం_యొక్క_దొంతర[ 10 ] = 0x0c0c0c0cUL;
    px_శిఖరం_యొక్క_దొంతర[ 9 ] = 0x0b0b0b0bUL;
    px_శిఖరం_యొక్క_దొంతర[ 8 ] = 0x0a0a0a0aUL;
    px_శిఖరం_యొక్క_దొంతర[ 7 ] = 0x09090909UL;
    px_శిఖరం_యొక్క_దొంతర[ 6 ] = 0x08080808UL;
    px_శిఖరం_యొక్క_దొంతర[ 5 ] = 0x07070707UL;
    px_శిఖరం_యొక్క_దొంతర[ 4 ] = 0x06060606UL;
    px_శిఖరం_యొక్క_దొంతర[ 3 ] = 0x05050505UL;
    px_శిఖరం_యొక్క_దొంతర[ 2 ] = 0x04040404UL;
    px_శిఖరం_యొక్క_దొంతర[ 1 ] = 0x03030303UL;
    px_శిఖరం_యొక్క_దొంతర[ 0 ] = ( uint32_t ) pvParameters;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Set-up the timer interrupt. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    పోర్టు_RESTORE_CONTEXT();

    /* Should not get here. */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1;
    counter1->విలువ = counter1->reload;
    counter1->ముసుగు = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
శూన్య interrupt31_handler( శూన్య ) __attribute__( ( naked ) );
శూన్య interrupt31_handler( శూన్య )
{
    పోర్టు_SAVE_CONTEXT();
    __asm అస్థిర ( "call vTaskSwitchContext" );
    పోర్టు_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvProcessTick( శూన్య ) __attribute__( ( noinline ) );
స్థిర శూన్య prvProcessTick( శూన్య )
{
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
శూన్య interrupt7_handler( శూన్య ) __attribute__( ( naked ) );
శూన్య interrupt7_handler( శూన్య )
{
    పోర్టు_SAVE_CONTEXT();
    prvProcessTick();
    పోర్టు_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
