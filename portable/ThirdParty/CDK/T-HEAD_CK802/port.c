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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

خارجي فراغ v_پورټ_پیل_Task( فراغ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
پورټ_LONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
پورټ_LONG pendsvflag = 0;

ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    ډېری_Type_t * stk = عدم;

    stk = px_سر_د_ډېری;

    *( --stk ) = ( uint32_t ) px_کوډ;       /* Entry Point                                         */
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

    أرجع stk;
}

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    ulCriticalNesting = 0UL;

    v_پورټ_پیل_Task();

    أرجع pdFALSE;
}


فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}

فراغ v_پورټ_Enter_Critical( فراغ )
{
    پورټ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0 )
    {
        طالما( 1 )
        {
        }
    }

    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();

        إذا( pendsvflag )
        {
            pendsvflag = 0;
            پورټ_YIELD();
        }
    }
}

#إذا configUSE_PREEMPTION == 0
    فراغ x_پورټ_Sys_Tick_Handler( فراغ )
    {
        پورټ_LONG ulDummy;

        ulDummy = پورټ_سېټ_مداخله_ماسک_FROM_ISR();
        xTaskIncrementTick();
        پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ulDummy );
    }

#وإلا
    فراغ x_پورټ_Sys_Tick_Handler( فراغ )
    {
        پورټ_LONG ulDummy;

        ulDummy = پورټ_سېټ_مداخله_ماسک_FROM_ISR();
        traceISR_ENTER();
        {
            إذا( xTaskIncrementTick() != pdFALSE )
            {
                trace_ISR_EXIT_منزل_SCHEDULER();
                پورټ_YIELD_FROM_ISR( pdTRUE );
            }
            وإلا
            {
                traceISR_EXIT();
            }
        }
        پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ulDummy );
    }
#د_که_پای /* if configUSE_PREEMPTION == 0 */

فراغ v_پورټ_Yield_Handler( فراغ )
{
    uint32_t ul_Saved_مداخله_ماسک;

    ul_Saved_مداخله_ماسک = پورټ_سېټ_مداخله_ماسک_FROM_ISR();

    vTaskSwitchContext();

    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ul_Saved_مداخله_ماسک );
}

__attribute__( ( weak ) ) فراغ v_Application_ډېری_ډکېدنه_Hook( xTaskHandle * pxTask,
                                                              نښهدار پورټ_CHAR * pcTaskName )
{
    لكل( ; ; )
    {
    }
}

__attribute__( ( weak ) ) فراغ vApplicationMallocFailedHook( فراغ )
{
    لكل( ; ; )
    {
    }
}
