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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_Task( ਖਾਲੀ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
ਪੋਰਟ_LONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
ਪੋਰਟ_LONG pendsvflag = 0;

ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ਢੇਰ_Type_t * stk = ਨਿਰਾ;

    stk = px_ਸਿਖਰ_ਦਾ_ਢੇਰ;

    *( --stk ) = ( uint32_t ) px_ਕੋਡ;       /* Entry Point                                         */
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

    ਵਾਪਸ stk;
}

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ulCriticalNesting = 0UL;

    v_ਪੋਰਟ_ਸ਼ੁਰੂ_Task();

    ਵਾਪਸ pdFALSE;
}


ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented as there is nothing to return to. */
}

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting == 0 )
    {
        ਜਦੋਂ( 1 )
        {
        }
    }

    ulCriticalNesting--;

    ਜੇ( ulCriticalNesting == 0 )
    {
        ਪੋਰਟ_ENABLE_INTERRUPTS();

        ਜੇ( pendsvflag )
        {
            pendsvflag = 0;
            ਪੋਰਟ_YIELD();
        }
    }
}

#ਜੇ configUSE_PREEMPTION == 0
    ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ )
    {
        ਪੋਰਟ_LONG ulDummy;

        ulDummy = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
        xTaskIncrementTick();
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ulDummy );
    }

#ਨਹੀਂਤਾਂ
    ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ )
    {
        ਪੋਰਟ_LONG ulDummy;

        ulDummy = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
        traceISR_ENTER();
        {
            ਜੇ( xTaskIncrementTick() != pdFALSE )
            {
                trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
                ਪੋਰਟ_YIELD_FROM_ISR( pdTRUE );
            }
            ਨਹੀਂਤਾਂ
            {
                traceISR_EXIT();
            }
        }
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ulDummy );
    }
#ਜੇ_ਅੰਤ /* if configUSE_PREEMPTION == 0 */

ਖਾਲੀ v_ਪੋਰਟ_Yield_Handler( ਖਾਲੀ )
{
    uint32_t ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ;

    ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

    vTaskSwitchContext();

    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ );
}

__attribute__( ( weak ) ) ਖਾਲੀ v_Application_ਢੇਰ_ਉਛਾਲ_Hook( xTaskHandle * pxTask,
                                                              ਨਿਸ਼ਾਨੀਵਾਲਾ ਪੋਰਟ_CHAR * pcTaskName )
{
    ਲਈ( ; ; )
    {
    }
}

__attribute__( ( weak ) ) ਖਾਲੀ vApplicationMallocFailedHook( ਖਾਲੀ )
{
    ਲਈ( ; ; )
    {
    }
}
