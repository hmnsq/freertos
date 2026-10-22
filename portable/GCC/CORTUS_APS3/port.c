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
#அந்தர்பாவ <stdlib.h>

/* Kernel includes. */
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

/* Machine includes */
#அந்தர்பாவ <machine/counter.h>
#அந்தர்பாவ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை );
/*-----------------------------------------------------------*/

அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_உச்சி_Of_அடுக்கு -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_உச்சி_Of_அடுக்கு[ 16 ] = 0;
    px_உச்சி_Of_அடுக்கு[ 15 ] = portINITIAL_PSR;
    px_உச்சி_Of_அடுக்கு[ 14 ] = ( uint32_t ) pxCode;
    px_உச்சி_Of_அடுக்கு[ 13 ] = 0x00000000UL; /* R15. */
    px_உச்சி_Of_அடுக்கு[ 12 ] = 0x00000000UL; /* R14. */
    px_உச்சி_Of_அடுக்கு[ 11 ] = 0x0d0d0d0dUL;
    px_உச்சி_Of_அடுக்கு[ 10 ] = 0x0c0c0c0cUL;
    px_உச்சி_Of_அடுக்கு[ 9 ] = 0x0b0b0b0bUL;
    px_உச்சி_Of_அடுக்கு[ 8 ] = 0x0a0a0a0aUL;
    px_உச்சி_Of_அடுக்கு[ 7 ] = 0x09090909UL;
    px_உச்சி_Of_அடுக்கு[ 6 ] = 0x08080808UL;
    px_உச்சி_Of_அடுக்கு[ 5 ] = 0x07070707UL;
    px_உச்சி_Of_அடுக்கு[ 4 ] = 0x06060606UL;
    px_உச்சி_Of_அடுக்கு[ 3 ] = 0x05050505UL;
    px_உச்சி_Of_அடுக்கு[ 2 ] = 0x04040404UL;
    px_உச்சி_Of_அடுக்கு[ 1 ] = 0x03030303UL;
    px_உச்சி_Of_அடுக்கு[ 0 ] = ( uint32_t ) pvParameters;

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    திரும்பு 0;
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->மதிப்பு = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
வெறுமை interrupt31_handler( வெறுமை ) __attribute__( ( naked ) );
வெறுமை interrupt31_handler( வெறுமை )
{
    portSAVE_CONTEXT();
    __asm நிலையற்ற ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvProcessTick( வெறுமை ) __attribute__( ( noinline ) );
நிலையான வெறுமை prvProcessTick( வெறுமை )
{
    எனில்( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
வெறுமை interrupt7_handler( வெறுமை ) __attribute__( ( naked ) );
வெறுமை interrupt7_handler( வெறுமை )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
