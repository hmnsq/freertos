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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"


#define portINITIAL_FORMAT_VECTOR       ( ( അട്ടി_Type_t ) 0x4000 )

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER     ( ( അട്ടി_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#define port_PRESCALE_മൂല്യം              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#define portRTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm ശൂന്യം interrupt Vector_സംഖ്യ_VL1swi vPortYieldISR( ശൂന്യം );
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
സ്ഥിതം uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

അട്ടി_Type_t *px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി, TaskFunction_t pxCode, ശൂന്യം *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_മുകൾ_Of_അട്ടി = (അട്ടി_Type_t) 0xDEADBEEF;
    px_മുകൾ_Of_അട്ടി--;

    /* Exception stack frame starts with the return address. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode;
    px_മുകൾ_Of_അട്ടി--;

    *px_മുകൾ_Of_അട്ടി = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    px_മുകൾ_Of_അട്ടി--;

    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x0; /*FP*/
    px_മുകൾ_Of_അട്ടി -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_മുകൾ_Of_അട്ടി + 8 ) = ( അട്ടി_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_മുകൾ_Of_അട്ടി + 13 ) = ulOriginalA5;

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
ബാഹ്യ ശൂന്യം vPortStartFirstTask( ശൂന്യം );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Start the first task executing. */
    vPortStartFirstTask();

    തിരികെ pdFALSE;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം )
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

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEnterCritical( ശൂന്യം )
{
    എങ്കിൽ( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        ചെയ്യുക
        {
            portDISABLE_INTERRUPTS();
            എങ്കിൽ( INTC_FRC == 0UL )
            {
                നിർത്തുക;
            }

            portENABLE_INTERRUPTS();

        } ആകുമ്പോൾ( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortExitCritical( ശൂന്യം )
{
    ulCriticalNesting--;
    എങ്കിൽ( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortYieldHandler( ശൂന്യം )
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

ശൂന്യം interrupt Vector_സംഖ്യ_Vrtc vPortTickISR( ശൂന്യം )
{
uint32_t ulSavedInterruptMask;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_MASK;

    /* Increment the RTOS tick. */
    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
