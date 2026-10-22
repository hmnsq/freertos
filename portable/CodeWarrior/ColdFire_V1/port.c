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
#समावेश "FreeRTOS.h"
#समावेश "task.h"


#घोषणा portINITIAL_FORMAT_VECTOR       ( ( ढेर_Type_t ) 0x4000 )

/* Supervisor mode set. */
#घोषणा portINITIAL_STATUS_REGISTER     ( ( ढेर_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#घोषणा port_PRESCALE_मूल्य              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#घोषणा portRTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

यंत्र व्योम interrupt Vector_संख्या_VL1swi vPortYieldISR( व्योम );
अटल व्योम prvSetupTimerInterrupt( व्योम );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
अटल uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ढेर_Type_t *px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर, TaskFunction_t pxCode, व्योम *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_शीर्ष_Of_ढेर = (ढेर_Type_t) 0xDEADBEEF;
    px_शीर्ष_Of_ढेर--;

    /* Exception stack frame starts with the return address. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;
    px_शीर्ष_Of_ढेर--;

    *px_शीर्ष_Of_ढेर = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    px_शीर्ष_Of_ढेर--;

    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x0; /*FP*/
    px_शीर्ष_Of_ढेर -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_शीर्ष_Of_ढेर + 8 ) = ( ढेर_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_शीर्ष_Of_ढेर + 13 ) = ulOriginalA5;

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
बाह्य व्योम vPortStartFirstTask( व्योम );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Start the first task executing. */
    vPortStartFirstTask();

    वापस pdFALSE;
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetupTimerInterrupt( व्योम )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = portRTC_CLOCK_HZ / configTICK_RATE_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    अगर( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        करो
        {
            portDISABLE_INTERRUPTS();
            अगर( INTC_FRC == 0UL )
            {
                अवरोध;
            }

            portENABLE_INTERRUPTS();

        } जबतक( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    ulCriticalNesting--;
    अगर( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

व्योम vPortYieldHandler( व्योम )
{
uint32_t ulSavedInterruptMask;

    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
/*-----------------------------------------------------------*/

व्योम interrupt Vector_संख्या_Vrtc vPortTickISR( व्योम )
{
uint32_t ulSavedInterruptMask;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_MASK;

    /* Increment the RTOS tick. */
    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
