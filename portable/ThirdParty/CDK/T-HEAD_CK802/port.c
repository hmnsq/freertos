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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

ബാഹ്യ ശൂന്യം vPortStartTask( ശൂന്യം );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
portLONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
portLONG pendsvflag = 0;

അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    അട്ടി_Type_t * stk = ശൂന്യ;

    stk = px_മുകൾ_Of_അട്ടി;

    *( --stk ) = ( uint32_t ) pxCode;       /* Entry Point                                         */
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

    തിരികെ stk;
}

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    ulCriticalNesting = 0UL;

    vPortStartTask();

    തിരികെ pdFALSE;
}


ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* Not implemented as there is nothing to return to. */
}

ശൂന്യം vPortEnterCritical( ശൂന്യം )
{
    portDISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

ശൂന്യം vPortExitCritical( ശൂന്യം )
{
    എങ്കിൽ( ulCriticalNesting == 0 )
    {
        ആകുമ്പോൾ( 1 )
        {
        }
    }

    ulCriticalNesting--;

    എങ്കിൽ( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();

        എങ്കിൽ( pendsvflag )
        {
            pendsvflag = 0;
            portYIELD();
        }
    }
}

#എങ്കിൽ configUSE_PREEMPTION == 0
    ശൂന്യം xPortSysTickHandler( ശൂന്യം )
    {
        portLONG ulDummy;

        ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
        xTaskIncrementTick();
        portCLEAR_INTERRUPT_MASK_FROM_ISR( ulDummy );
    }

#അല്ലെങ്കിൽ
    ശൂന്യം xPortSysTickHandler( ശൂന്യം )
    {
        portLONG ulDummy;

        ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
        traceISR_ENTER();
        {
            എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
            {
                traceISR_EXIT_TO_SCHEDULER();
                portYIELD_FROM_ISR( pdTRUE );
            }
            അല്ലെങ്കിൽ
            {
                traceISR_EXIT();
            }
        }
        portCLEAR_INTERRUPT_MASK_FROM_ISR( ulDummy );
    }
#endif /* if configUSE_PREEMPTION == 0 */

ശൂന്യം vPortYieldHandler( ശൂന്യം )
{
    uint32_t ulSavedInterruptMask;

    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();

    vTaskSwitchContext();

    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}

__attribute__( ( weak ) ) ശൂന്യം v_Application_അട്ടി_Overflow_Hook( xTaskHandle * pxTask,
                                                              signed portCHAR * pcTaskName )
{
    വേണ്ടി( ; ; )
    {
    }
}

__attribute__( ( weak ) ) ശൂന്യം vApplicationMallocFailedHook( ശൂന്യം )
{
    വേണ്ടി( ; ; )
    {
    }
}
