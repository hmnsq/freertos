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
#અન્તર્ભાવ <stdlib.h>

/* Kernel includes. */
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"

/* Machine includes */
#અન્તર્ભાવ <machine/counter.h>
#અન્તર્ભાવ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
સ્થિર શૂન્ય prvSetupTimerInterrupt( શૂન્ય );
/*-----------------------------------------------------------*/

ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                     TaskFunction_t pxCode,
                                     શૂન્ય * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_ટોચ_Of_ઢગલો -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_ટોચ_Of_ઢગલો[ 16 ] = 0;
    px_ટોચ_Of_ઢગલો[ 15 ] = portINITIAL_PSR;
    px_ટોચ_Of_ઢગલો[ 14 ] = ( uint32_t ) pxCode;
    px_ટોચ_Of_ઢગલો[ 13 ] = 0x00000000UL; /* R15. */
    px_ટોચ_Of_ઢગલો[ 12 ] = 0x00000000UL; /* R14. */
    px_ટોચ_Of_ઢગલો[ 11 ] = 0x0d0d0d0dUL;
    px_ટોચ_Of_ઢગલો[ 10 ] = 0x0c0c0c0cUL;
    px_ટોચ_Of_ઢગલો[ 9 ] = 0x0b0b0b0bUL;
    px_ટોચ_Of_ઢગલો[ 8 ] = 0x0a0a0a0aUL;
    px_ટોચ_Of_ઢગલો[ 7 ] = 0x09090909UL;
    px_ટોચ_Of_ઢગલો[ 6 ] = 0x08080808UL;
    px_ટોચ_Of_ઢગલો[ 5 ] = 0x07070707UL;
    px_ટોચ_Of_ઢગલો[ 4 ] = 0x06060606UL;
    px_ટોચ_Of_ઢગલો[ 3 ] = 0x05050505UL;
    px_ટોચ_Of_ઢગલો[ 2 ] = 0x04040404UL;
    px_ટોચ_Of_ઢગલો[ 1 ] = 0x03030303UL;
    px_ટોચ_Of_ઢગલો[ 0 ] = ( uint32_t ) pvParameters;

    પાછા px_ટોચ_Of_ઢગલો;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( શૂન્ય )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    પાછા 0;
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvSetupTimerInterrupt( શૂન્ય )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->કિંમત = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
શૂન્ય interrupt31_handler( શૂન્ય ) __attribute__( ( naked ) );
શૂન્ય interrupt31_handler( શૂન્ય )
{
    portSAVE_CONTEXT();
    __asm અસ્થિર ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvProcessTick( શૂન્ય ) __attribute__( ( noinline ) );
સ્થિર શૂન્ય prvProcessTick( શૂન્ય )
{
    જો( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
શૂન્ય interrupt7_handler( શૂન્ય ) __attribute__( ( naked ) );
શૂન્ય interrupt7_handler( શૂન્ય )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEndScheduler( શૂન્ય )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
