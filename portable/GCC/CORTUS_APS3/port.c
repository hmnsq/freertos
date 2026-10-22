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

/* Standard includes. */
#شامل <stdlib.h>

/* Kernel includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Machine includes */
#شامل <machine/counter.h>
#شامل <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ایستا تهی prvSetupTimerInterrupt( تهی );
/*-----------------------------------------------------------*/

پشته_Type_t * px_Port_Initialise_پشته( پشته_Type_t * px_بالاترین_Of_پشته,
                                     TaskFunction_t pxCode,
                                     تهی * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_بالاترین_Of_پشته -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_بالاترین_Of_پشته[ 16 ] = 0;
    px_بالاترین_Of_پشته[ 15 ] = portINITIAL_PSR;
    px_بالاترین_Of_پشته[ 14 ] = ( uint32_t ) pxCode;
    px_بالاترین_Of_پشته[ 13 ] = 0x00000000UL; /* R15. */
    px_بالاترین_Of_پشته[ 12 ] = 0x00000000UL; /* R14. */
    px_بالاترین_Of_پشته[ 11 ] = 0x0d0d0d0dUL;
    px_بالاترین_Of_پشته[ 10 ] = 0x0c0c0c0cUL;
    px_بالاترین_Of_پشته[ 9 ] = 0x0b0b0b0bUL;
    px_بالاترین_Of_پشته[ 8 ] = 0x0a0a0a0aUL;
    px_بالاترین_Of_پشته[ 7 ] = 0x09090909UL;
    px_بالاترین_Of_پشته[ 6 ] = 0x08080808UL;
    px_بالاترین_Of_پشته[ 5 ] = 0x07070707UL;
    px_بالاترین_Of_پشته[ 4 ] = 0x06060606UL;
    px_بالاترین_Of_پشته[ 3 ] = 0x05050505UL;
    px_بالاترین_Of_پشته[ 2 ] = 0x04040404UL;
    px_بالاترین_Of_پشته[ 1 ] = 0x03030303UL;
    px_بالاترین_Of_پشته[ 0 ] = ( uint32_t ) pvParameters;

    بازگشت px_بالاترین_Of_پشته;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( تهی )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    بازگشت 0;
}
/*-----------------------------------------------------------*/

ایستا تهی prvSetupTimerInterrupt( تهی )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->مقدار = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
تهی interrupt31_handler( تهی ) __attribute__( ( naked ) );
تهی interrupt31_handler( تهی )
{
    portSAVE_CONTEXT();
    __asm فرار ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ایستا تهی prvProcessTick( تهی ) __attribute__( ( noinline ) );
ایستا تهی prvProcessTick( تهی )
{
    اگر( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
تهی interrupt7_handler( تهی ) __attribute__( ( naked ) );
تهی interrupt7_handler( تهی )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

تهی vPortEndScheduler( تهی )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
