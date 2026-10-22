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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#define portINITIAL_FORMAT_VECTOR      ( ( राशिः_Type_t ) 0x4000 )

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER    ( ( राशिः_Type_t ) 0x2000 )

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
स्थिर uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

राशिः_Type_t * px_Port_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_Of_राशिः,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pvParameters;
    px_शिखरम्_Of_राशिः--;

    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0xDEADBEEF;
    px_शिखरम्_Of_राशिः--;

    /* Exception stack frame starts with the return address. */
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pxCode;
    px_शिखरम्_Of_राशिः--;

    *px_शिखरम्_Of_राशिः = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    px_शिखरम्_Of_राशिः--;

    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x0; /*FP*/
    px_शिखरम्_Of_राशिः -= 14;                  /* A5 to D0. */

    प्रत्यागम px_शिखरम्_Of_राशिः;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    बाह्य शून्य vPortStartFirstTask( शून्य );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    vApplicationSetupInterrupts();

    /* Start the first task executing. */
    vPortStartFirstTask();

    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

शून्य vPortEnterCritical( शून्य )
{
    जइ( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
         * critical section being entered. */
        करेहि
        {
            portDISABLE_INTERRUPTS();

            जइ( MCF_INTC0_INTFRCL == 0UL )
            {
                भङ्ग;
            }

            portENABLE_INTERRUPTS();
        } जाव( 1 );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य vPortExitCritical( शून्य )
{
    ulCriticalNesting--;

    जइ( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

शून्य vPortYieldHandler( शून्य )
{
    uint32_t ulSavedInterruptMask;

    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    /* Note this will clear all forced interrupts - this is done for speed. */
    MCF_INTC0_INTFRCL = 0;
    vTaskSwitchContext();
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
