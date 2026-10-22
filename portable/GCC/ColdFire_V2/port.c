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

/* Kernel includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచించు పోర్టు_INITIAL_FORMAT_సదిశ      ( ( దొంతర_Type_t ) 0x4000 )

/* Supervisor mode set. */
#నిర్వచించు పోర్టు_INITIAL_స్థితి_రిజిస్టరు    ( ( దొంతర_Type_t ) 0x2000 )

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
స్థిర uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDEADBEEF;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Exception stack frame starts with the return address. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( పోర్టు_INITIAL_FORMAT_సదిశ << 16UL ) | ( పోర్టు_INITIAL_స్థితి_రిజిస్టరు );
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0; /*FP*/
    px_శిఖరం_యొక్క_దొంతర -= 14;                  /* A5 to D0. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    v_Application_అమరిక_Interrupts();

    /* Start the first task executing. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
         * critical section being entered. */
        చేయి
        {
            పోర్టు_DISABLE_INTERRUPTS();

            ఒకవేళ( MCF_INTC0_INTFRCL == 0UL )
            {
                ఆపు;
            }

            పోర్టు_ENABLE_INTERRUPTS();
        } అయితే( 1 );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ulCriticalNesting--;

    ఒకవేళ( ulCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield_Handler( శూన్య )
{
    uint32_t ul_Saved_అంతరాయం_ముసుగు;

    ul_Saved_అంతరాయం_ముసుగు = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    /* Note this will clear all forced interrupts - this is done for speed. */
    MCF_INTC0_INTFRCL = 0;
    vTaskSwitchContext();
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_Saved_అంతరాయం_ముసుగు );
}
