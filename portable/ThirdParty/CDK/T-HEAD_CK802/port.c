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

/* Kernel includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

బాహ్య శూన్య v_పోర్టు_ప్రారంభం_Task( శూన్య );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
పోర్టు_LONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
పోర్టు_LONG pendsvflag = 0;

దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    దొంతర_Type_t * stk = ఖాళీ;

    stk = px_శిఖరం_యొక్క_దొంతర;

    *( --stk ) = ( uint32_t ) px_సంకేతం;       /* Entry Point                                         */
    *( --stk ) = ( uint32_t ) 0xE0000140L;  /* PSR                                                 */
    *( --stk ) = ( uint32_t ) 0xFFFFFFFEL;  /* R15 (LR) (init value will cause fault if ever used) */
    *( --stk ) = ( uint32_t ) 0x13131313L;  /* R13                                                 */
    *( --stk ) = ( uint32_t ) 0x12121212L;  /* R12                                                 */
    *( --stk ) = ( uint32_t ) 0x11111111L;  /* R11                                                 */
    *( --stk ) = ( uint32_t ) 0x10101010L;  /* R10                                                 */
    *( --stk ) = ( uint32_t ) 0x09090909L;  /* R9                                                  */
    *( --stk ) = ( uint32_t ) 0x08080808L;  /* R8                                                  */
    *( --stk ) = ( uint32_t ) 0x07070707L;  /* R7                                                  */
    *( --stk ) = ( uint32_t ) 0x06060606L;  /* R6                                                  */
    *( --stk ) = ( uint32_t ) 0x05050505L;  /* R5                                                  */
    *( --stk ) = ( uint32_t ) 0x04040404L;  /* R4                                                  */
    *( --stk ) = ( uint32_t ) 0x03030303L;  /* R3                                                  */
    *( --stk ) = ( uint32_t ) 0x02020202L;  /* R2                                                  */
    *( --stk ) = ( uint32_t ) 0x01010101L;  /* R1                                                  */
    *( --stk ) = ( uint32_t ) pvParameters; /* R0 : argument                                       */

    తిరిగి stk;
}

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    ulCriticalNesting = 0UL;

    v_పోర్టు_ప్రారంభం_Task();

    తిరిగి pdFALSE;
}


శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented as there is nothing to return to. */
}

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting == 0 )
    {
        అయితే( 1 )
        {
        }
    }

    ulCriticalNesting--;

    ఒకవేళ( ulCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();

        ఒకవేళ( pendsvflag )
        {
            pendsvflag = 0;
            పోర్టు_YIELD();
        }
    }
}

#ఒకవేళ configUSE_PREEMPTION == 0
    శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య )
    {
        పోర్టు_LONG ulDummy;

        ulDummy = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
        xTaskIncrementTick();
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ulDummy );
    }

#లేకపోతే
    శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య )
    {
        పోర్టు_LONG ulDummy;

        ulDummy = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
        traceISR_ENTER();
        {
            ఒకవేళ( xTaskIncrementTick() != pdFALSE )
            {
                trace_ISR_EXIT_గమ్యం_SCHEDULER();
                పోర్టు_YIELD_FROM_ISR( pdTRUE );
            }
            లేకపోతే
            {
                traceISR_EXIT();
            }
        }
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ulDummy );
    }
#అయితే_ముగింపు /* if configUSE_PREEMPTION == 0 */

శూన్య v_పోర్టు_Yield_Handler( శూన్య )
{
    uint32_t ul_Saved_అంతరాయం_ముసుగు;

    ul_Saved_అంతరాయం_ముసుగు = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

    vTaskSwitchContext();

    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_Saved_అంతరాయం_ముసుగు );
}

__attribute__( ( weak ) ) శూన్య v_Application_దొంతర_అధికప్రవాహం_Hook( xTaskHandle * pxTask,
                                                              గుర్తుగల పోర్టు_CHAR * pcTaskName )
{
    కొరకు( ; ; )
    {
    }
}

__attribute__( ( weak ) ) శూన్య vApplicationMallocFailedHook( శూన్య )
{
    కొరకు( ; ; )
    {
    }
}
