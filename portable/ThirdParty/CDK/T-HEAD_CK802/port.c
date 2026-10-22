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
#شامل "FreeRTOS.h"
#شامل "task.h"

خارجی خالی v_پورٹ_آغاز_Task( خالی );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
پورٹ_LONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
پورٹ_LONG pendsvflag = 0;

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    ڈھیر_Type_t * stk = تہی;

    stk = px_چوٹی_کا_ڈھیر;

    *( --stk ) = ( uint32_t ) px_رمز;       /* Entry Point                                         */
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

    واپس stk;
}

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    ulCriticalNesting = 0UL;

    v_پورٹ_آغاز_Task();

    واپس pdFALSE;
}


خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented as there is nothing to return to. */
}

خالی v_پورٹ_Enter_Critical( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

خالی v_پورٹ_Exit_Critical( خالی )
{
    اگر( ulCriticalNesting == 0 )
    {
        جب( 1 )
        {
        }
    }

    ulCriticalNesting--;

    اگر( ulCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();

        اگر( pendsvflag )
        {
            pendsvflag = 0;
            پورٹ_YIELD();
        }
    }
}

#اگر configUSE_PREEMPTION == 0
    خالی x_پورٹ_Sys_Tick_Handler( خالی )
    {
        پورٹ_LONG ulDummy;

        ulDummy = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
        xTaskIncrementTick();
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ulDummy );
    }

#ورنہ
    خالی x_پورٹ_Sys_Tick_Handler( خالی )
    {
        پورٹ_LONG ulDummy;

        ulDummy = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
        traceISR_ENTER();
        {
            اگر( xTaskIncrementTick() != pdFALSE )
            {
                trace_ISR_EXIT_مقصد_SCHEDULER();
                پورٹ_YIELD_FROM_ISR( pdTRUE );
            }
            ورنہ
            {
                traceISR_EXIT();
            }
        }
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ulDummy );
    }
#اگر_ختم /* if configUSE_PREEMPTION == 0 */

خالی v_پورٹ_Yield_Handler( خالی )
{
    uint32_t ul_Saved_مداخلت_نقاب;

    ul_Saved_مداخلت_نقاب = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

    vTaskSwitchContext();

    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_Saved_مداخلت_نقاب );
}

__attribute__( ( weak ) ) خالی v_Application_ڈھیر_حد_سے_تجاوز_Hook( xTaskHandle * pxTask,
                                                              علامتی پورٹ_CHAR * pcTaskName )
{
    برائے( ; ; )
    {
    }
}

__attribute__( ( weak ) ) خالی vApplicationMallocFailedHook( خالی )
{
    برائے( ; ; )
    {
    }
}
