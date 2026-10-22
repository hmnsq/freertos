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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#define portINITIAL_FORMAT_VECTOR      ( ( ರಾಶಿ_Type_t ) 0x4000 )

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER    ( ( ರಾಶಿ_Type_t ) 0x2000 )

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
ಸ್ಥಿರ uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xDEADBEEF;
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* Exception stack frame starts with the return address. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxCode;
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0; /*FP*/
    px_ತುದಿ_Of_ರಾಶಿ -= 14;                  /* A5 to D0. */

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ vPortStartFirstTask( ಶೂನ್ಯ );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    vApplicationSetupInterrupts();

    /* Start the first task executing. */
    vPortStartFirstTask();

    ಪ್ರತ್ಯಾಗಮ pdFALSE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ )
{
    ಯದಿ( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
         * critical section being entered. */
        ಕುರು
        {
            portDISABLE_INTERRUPTS();

            ಯದಿ( MCF_INTC0_INTFRCL == 0UL )
            {
                ಭಙ್ಗ;
            }

            portENABLE_INTERRUPTS();
        } ಯಾವತ್( 1 );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ )
{
    ulCriticalNesting--;

    ಯದಿ( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortYieldHandler( ಶೂನ್ಯ )
{
    uint32_t ulSavedInterruptMask;

    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    /* Note this will clear all forced interrupts - this is done for speed. */
    MCF_INTC0_INTFRCL = 0;
    vTaskSwitchContext();
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
