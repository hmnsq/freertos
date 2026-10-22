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
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"


#define portINITIAL_FORMAT_VECTOR       ( ( அடுக்கு_Type_t ) 0x4000 )

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER     ( ( அடுக்கு_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#define port_PRESCALE_மதிப்பு              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#define portRTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm வெறுமை interrupt Vector_எண்_VL1swi vPortYieldISR( வெறுமை );
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
நிலையான uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

அடுக்கு_Type_t *px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு, TaskFunction_t pxCode, வெறுமை *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_உச்சி_Of_அடுக்கு = (அடுக்கு_Type_t) 0xDEADBEEF;
    px_உச்சி_Of_அடுக்கு--;

    /* Exception stack frame starts with the return address. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pxCode;
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0x0; /*FP*/
    px_உச்சி_Of_அடுக்கு -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_உச்சி_Of_அடுக்கு + 8 ) = ( அடுக்கு_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_உச்சி_Of_அடுக்கு + 13 ) = ulOriginalA5;

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
வெளி வெறுமை vPortStartFirstTask( வெறுமை );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Start the first task executing. */
    vPortStartFirstTask();

    திரும்பு pdFALSE;
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை )
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

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

வெறுமை vPortEnterCritical( வெறுமை )
{
    எனில்( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        செய்
        {
            portDISABLE_INTERRUPTS();
            எனில்( INTC_FRC == 0UL )
            {
                நிறுத்து;
            }

            portENABLE_INTERRUPTS();

        } போது( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

வெறுமை vPortExitCritical( வெறுமை )
{
    ulCriticalNesting--;
    எனில்( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

வெறுமை vPortYieldHandler( வெறுமை )
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

வெறுமை interrupt Vector_எண்_Vrtc vPortTickISR( வெறுமை )
{
uint32_t ulSavedInterruptMask;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_MASK;

    /* Increment the RTOS tick. */
    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
