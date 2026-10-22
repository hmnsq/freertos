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
#ضمن "FreeRTOS.h"
#ضمن "task.h"


#define portINITIAL_FORMAT_VECTOR       ( ( تر_Type_t ) 0x4000 )

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER     ( ( تر_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#define port_PRESCALE_درج              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#define portRTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm فراغ interrupt Vector_لمب_VL1swi vPortYieldISR( فراغ );
ساكن فراغ prvSetupTimerInterrupt( فراغ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ساكن uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

تر_Type_t *px_Port_Initialise_تر( تر_Type_t * px_كولي_Of_تر, TaskFunction_t pxCode, فراغ *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_كولي_Of_تر = (تر_Type_t) 0xDEADBEEF;
    px_كولي_Of_تر--;

    /* Exception stack frame starts with the return address. */
    *px_كولي_Of_تر = ( تر_Type_t ) pxCode;
    px_كولي_Of_تر--;

    *px_كولي_Of_تر = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    px_كولي_Of_تر--;

    *px_كولي_Of_تر = ( تر_Type_t ) 0x0; /*FP*/
    px_كولي_Of_تر -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_كولي_Of_تر + 8 ) = ( تر_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_كولي_Of_تر + 13 ) = ulOriginalA5;

    أرجع px_كولي_Of_تر;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
خارجي فراغ vPortStartFirstTask( فراغ );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prvSetupTimerInterrupt();

    /* Start the first task executing. */
    vPortStartFirstTask();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSetupTimerInterrupt( فراغ )
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

فراغ vPortEndScheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

فراغ vPortEnterCritical( فراغ )
{
    إذا( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        افعل
        {
            portDISABLE_INTERRUPTS();
            إذا( INTC_FRC == 0UL )
            {
                اكسر;
            }

            portENABLE_INTERRUPTS();

        } طالما( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ vPortExitCritical( فراغ )
{
    ulCriticalNesting--;
    إذا( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ vPortYieldHandler( فراغ )
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

فراغ interrupt Vector_لمب_Vrtc vPortTickISR( فراغ )
{
uint32_t ulSavedInterruptMask;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_MASK;

    /* Increment the RTOS tick. */
    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
