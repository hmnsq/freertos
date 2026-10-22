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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

बाह्य शून्य v_पत्तनम्_Start_Task( शून्य );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
पत्तनम्_LONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
पत्तनम्_LONG pendsvflag = 0;

राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    राशिः_Type_t * stk = रिक्त;

    stk = px_शिखरम्_सम्बन्धि_राशिः;

    *( --stk ) = ( uint32_t ) px_संहिता;       /* Entry Point                                         */
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

    प्रत्यागम stk;
}

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    ulCriticalNesting = 0UL;

    v_पत्तनम्_Start_Task();

    प्रत्यागम pdFALSE;
}


शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented as there is nothing to return to. */
}

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    यदि( ulCriticalNesting == 0 )
    {
        यावत्( 1 )
        {
        }
    }

    ulCriticalNesting--;

    यदि( ulCriticalNesting == 0 )
    {
        पत्तनम्_ENABLE_INTERRUPTS();

        यदि( pendsvflag )
        {
            pendsvflag = 0;
            पत्तनम्_YIELD();
        }
    }
}

#यदि configUSE_PREEMPTION == 0
    शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य )
    {
        पत्तनम्_LONG ulDummy;

        ulDummy = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
        xTaskIncrementTick();
        पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ulDummy );
    }

#अन्यथा
    शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य )
    {
        पत्तनम्_LONG ulDummy;

        ulDummy = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
        traceISR_ENTER();
        {
            यदि( xTaskIncrementTick() != pdFALSE )
            {
                trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
                पत्तनम्_YIELD_FROM_ISR( pdTRUE );
            }
            अन्यथा
            {
                traceISR_EXIT();
            }
        }
        पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ulDummy );
    }
#यदि_अन्तः /* if configUSE_PREEMPTION == 0 */

शून्य v_पत्तनम्_Yield_Handler( शून्य )
{
    uint32_t ul_Saved_व्यवधानम्_आवरणम्;

    ul_Saved_व्यवधानम्_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();

    vTaskSwitchContext();

    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Saved_व्यवधानम्_आवरणम् );
}

__attribute__( ( weak ) ) शून्य v_Application_राशिः_अतिप्रवाहः_Hook( xTaskHandle * pxTask,
                                                              चिह्नित पत्तनम्_CHAR * pcTaskName )
{
    प्रति( ; ; )
    {
    }
}

__attribute__( ( weak ) ) शून्य vApplicationMallocFailedHook( शून्य )
{
    प्रति( ; ; )
    {
    }
}
