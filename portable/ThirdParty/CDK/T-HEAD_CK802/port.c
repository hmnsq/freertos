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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_Task( ಶೂನ್ಯ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
ಪೋರ್ಟ್_LONG ulCriticalNesting = 0x9999UL;

/* Used to record one tack want to switch task after enter critical area, we need know it
 * and implement task switch after exit critical area */
ಪೋರ್ಟ್_LONG pendsvflag = 0;

ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ರಾಶಿ_Type_t * stk = ಖಾಲಿ;

    stk = px_ತುದಿ_ದ_ರಾಶಿ;

    *( --stk ) = ( uint32_t ) px_ಸಂಕೇತ;       /* Entry Point                                         */
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

    ಹಿಂತಿರುಗಿ stk;
}

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ulCriticalNesting = 0UL;

    v_ಪೋರ್ಟ್_ಆರಂಭ_Task();

    ಹಿಂತಿರುಗಿ pdFALSE;
}


ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented as there is nothing to return to. */
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting == 0 )
    {
        ಆಗ( 1 )
        {
        }
    }

    ulCriticalNesting--;

    ಆದರೆ( ulCriticalNesting == 0 )
    {
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();

        ಆದರೆ( pendsvflag )
        {
            pendsvflag = 0;
            ಪೋರ್ಟ್_YIELD();
        }
    }
}

#ಆದರೆ configUSE_PREEMPTION == 0
    ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ )
    {
        ಪೋರ್ಟ್_LONG ulDummy;

        ulDummy = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
        xTaskIncrementTick();
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ulDummy );
    }

#ಇಲ್ಲದಿದ್ದರೆ
    ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ )
    {
        ಪೋರ್ಟ್_LONG ulDummy;

        ulDummy = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
        traceISR_ENTER();
        {
            ಆದರೆ( xTaskIncrementTick() != pdFALSE )
            {
                trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
                ಪೋರ್ಟ್_YIELD_FROM_ISR( pdTRUE );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                traceISR_EXIT();
            }
        }
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ulDummy );
    }
#ಆದರೆ_ಅಂತ್ಯ /* if configUSE_PREEMPTION == 0 */

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Handler( ಶೂನ್ಯ )
{
    uint32_t ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ;

    ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

    vTaskSwitchContext();

    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ );
}

__attribute__( ( weak ) ) ಶೂನ್ಯ v_Application_ರಾಶಿ_ಅತಿಪ್ರವಾಹ_Hook( xTaskHandle * pxTask,
                                                              ಚಿಹ್ನೆಯುಳ್ಳ ಪೋರ್ಟ್_CHAR * pcTaskName )
{
    ಗಾಗಿ( ; ; )
    {
    }
}

__attribute__( ( weak ) ) ಶೂನ್ಯ vApplicationMallocFailedHook( ಶೂನ್ಯ )
{
    ಗಾಗಿ( ; ; )
    {
    }
}
