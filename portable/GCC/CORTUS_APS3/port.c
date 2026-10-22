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
#অন্তর্ভাব <stdlib.h>

/* Kernel includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Machine includes */
#অন্তর্ভাব <machine/counter.h>
#অন্তর্ভাব <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
স্থির শূন্য prvSetupTimerInterrupt( শূন্য );
/*-----------------------------------------------------------*/

স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_শীর্ষ_Of_স্তূপ -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_শীর্ষ_Of_স্তূপ[ 16 ] = 0;
    px_শীর্ষ_Of_স্তূপ[ 15 ] = portINITIAL_PSR;
    px_শীর্ষ_Of_স্তূপ[ 14 ] = ( uint32_t ) pxCode;
    px_শীর্ষ_Of_স্তূপ[ 13 ] = 0x00000000UL; /* R15. */
    px_শীর্ষ_Of_স্তূপ[ 12 ] = 0x00000000UL; /* R14. */
    px_শীর্ষ_Of_স্তূপ[ 11 ] = 0x0d0d0d0dUL;
    px_শীর্ষ_Of_স্তূপ[ 10 ] = 0x0c0c0c0cUL;
    px_শীর্ষ_Of_স্তূপ[ 9 ] = 0x0b0b0b0bUL;
    px_শীর্ষ_Of_স্তূপ[ 8 ] = 0x0a0a0a0aUL;
    px_শীর্ষ_Of_স্তূপ[ 7 ] = 0x09090909UL;
    px_শীর্ষ_Of_স্তূপ[ 6 ] = 0x08080808UL;
    px_শীর্ষ_Of_স্তূপ[ 5 ] = 0x07070707UL;
    px_শীর্ষ_Of_স্তূপ[ 4 ] = 0x06060606UL;
    px_শীর্ষ_Of_স্তূপ[ 3 ] = 0x05050505UL;
    px_শীর্ষ_Of_স্তূপ[ 2 ] = 0x04040404UL;
    px_শীর্ষ_Of_স্তূপ[ 1 ] = 0x03030303UL;
    px_শীর্ষ_Of_স্তূপ[ 0 ] = ( uint32_t ) pvParameters;

    প্রত্যাগম px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    প্রত্যাগম 0;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSetupTimerInterrupt( শূন্য )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->মান = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
শূন্য interrupt31_handler( শূন্য ) __attribute__( ( naked ) );
শূন্য interrupt31_handler( শূন্য )
{
    portSAVE_CONTEXT();
    __asm চঞ্চল ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvProcessTick( শূন্য ) __attribute__( ( noinline ) );
স্থির শূন্য prvProcessTick( শূন্য )
{
    যদি( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
শূন্য interrupt7_handler( শূন্য ) __attribute__( ( naked ) );
শূন্য interrupt7_handler( শূন্য )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
