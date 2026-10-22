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


#నిర్వచించు పోర్టు_INITIAL_FORMAT_సదిశ       ( ( దొంతర_Type_t ) 0x4000 )

/* Supervisor mode set. */
#నిర్వచించు పోర్టు_INITIAL_స్థితి_రిజిస్టరు     ( ( దొంతర_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#నిర్వచించు పోర్టు_PRESCALE_విలువ              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#నిర్వచించు పోర్టు_RTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm శూన్య అంతరాయం సదిశ_సంఖ్య_VL1swi v_పోర్టు_Yield_ISR( శూన్య );
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
స్థిర uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_శిఖరం_యొక్క_దొంతర = (దొంతర_Type_t) 0xDEADBEEF;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Exception stack frame starts with the return address. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( పోర్టు_INITIAL_FORMAT_సదిశ << 16UL ) | ( పోర్టు_INITIAL_స్థితి_రిజిస్టరు );
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0; /*FP*/
    px_శిఖరం_యొక్క_దొంతర -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_శిఖరం_యొక్క_దొంతర + 8 ) = ( దొంతర_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_శిఖరం_యొక్క_దొంతర + 13 ) = ulOriginalA5;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task executing. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = పోర్టు_RTC_CLOCK_HZ / config_TICK_రేటు_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
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
        critical section being entered. */
        చేయి
        {
            పోర్టు_DISABLE_INTERRUPTS();
            ఒకవేళ( INTC_FRC == 0UL )
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
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_Saved_అంతరాయం_ముసుగు );
}
/*-----------------------------------------------------------*/

శూన్య అంతరాయం సదిశ_సంఖ్య_Vrtc v_పోర్టు_Tick_ISR( శూన్య )
{
uint32_t ul_Saved_అంతరాయం_ముసుగు;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_ముసుగు;

    /* Increment the RTOS tick. */
    ul_Saved_అంతరాయం_ముసుగు = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_Saved_అంతరాయం_ముసుగు );
}
