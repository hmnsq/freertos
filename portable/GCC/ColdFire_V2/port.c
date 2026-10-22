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

#define portINITIAL_FORMAT_VECTOR      ( ( StackType_t ) 0x4000 )

/* Supervisor mode set. */
#define portINITIAL_STATUS_REGISTER    ( ( StackType_t ) 0x2000 )

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
ساكن uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    *pxTopOfStack = ( StackType_t ) pvParameters;
    pxTopOfStack--;

    *pxTopOfStack = ( StackType_t ) 0xDEADBEEF;
    pxTopOfStack--;

    /* Exception stack frame starts with the return address. */
    *pxTopOfStack = ( StackType_t ) pxCode;
    pxTopOfStack--;

    *pxTopOfStack = ( portINITIAL_FORMAT_VECTOR << 16UL ) | ( portINITIAL_STATUS_REGISTER );
    pxTopOfStack--;

    *pxTopOfStack = ( StackType_t ) 0x0; /*FP*/
    pxTopOfStack -= 14;                  /* A5 to D0. */

    أرجع pxTopOfStack;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    خارجي فراغ vPortStartFirstTask( فراغ );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    vApplicationSetupInterrupts();

    /* Start the first task executing. */
    vPortStartFirstTask();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

فراغ vPortEnterCritical( فراغ )
{
    𐤀𐤌( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
         * critical section being entered. */
        𐤐𐤏𐤋
        {
            portDISABLE_INTERRUPTS();

            𐤀𐤌( MCF_INTC0_INTFRCL == 0UL )
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

    𐤀𐤌( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ vPortYieldHandler( فراغ )
{
    uint32_t ulSavedInterruptMask;

    ulSavedInterruptMask = portSET_INTERRUPT_MASK_FROM_ISR();
    /* Note this will clear all forced interrupts - this is done for speed. */
    MCF_INTC0_INTFRCL = 0;
    vTaskSwitchContext();
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulSavedInterruptMask );
}
