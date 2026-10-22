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
#अन्तर्भाव <stdlib.h>

/* Kernel includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Machine includes */
#अन्तर्भाव <machine/counter.h>
#अन्तर्भाव <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
स्थिर शून्य prvSetupTimerInterrupt( शून्य );
/*-----------------------------------------------------------*/

ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_शीर्ष_Of_ढेर -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_शीर्ष_Of_ढेर[ 16 ] = 0;
    px_शीर्ष_Of_ढेर[ 15 ] = portINITIAL_PSR;
    px_शीर्ष_Of_ढेर[ 14 ] = ( uint32_t ) pxCode;
    px_शीर्ष_Of_ढेर[ 13 ] = 0x00000000UL; /* R15. */
    px_शीर्ष_Of_ढेर[ 12 ] = 0x00000000UL; /* R14. */
    px_शीर्ष_Of_ढेर[ 11 ] = 0x0d0d0d0dUL;
    px_शीर्ष_Of_ढेर[ 10 ] = 0x0c0c0c0cUL;
    px_शीर्ष_Of_ढेर[ 9 ] = 0x0b0b0b0bUL;
    px_शीर्ष_Of_ढेर[ 8 ] = 0x0a0a0a0aUL;
    px_शीर्ष_Of_ढेर[ 7 ] = 0x09090909UL;
    px_शीर्ष_Of_ढेर[ 6 ] = 0x08080808UL;
    px_शीर्ष_Of_ढेर[ 5 ] = 0x07070707UL;
    px_शीर्ष_Of_ढेर[ 4 ] = 0x06060606UL;
    px_शीर्ष_Of_ढेर[ 3 ] = 0x05050505UL;
    px_शीर्ष_Of_ढेर[ 2 ] = 0x04040404UL;
    px_शीर्ष_Of_ढेर[ 1 ] = 0x03030303UL;
    px_शीर्ष_Of_ढेर[ 0 ] = ( uint32_t ) pvParameters;

    प्रत्यागम px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSetupTimerInterrupt( शून्य )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->मूल्य = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
शून्य interrupt31_handler( शून्य ) __attribute__( ( naked ) );
शून्य interrupt31_handler( शून्य )
{
    portSAVE_CONTEXT();
    __asm चञ्चल ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvProcessTick( शून्य ) __attribute__( ( noinline ) );
स्थिर शून्य prvProcessTick( शून्य )
{
    यदि( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
शून्य interrupt7_handler( शून्य ) __attribute__( ( naked ) );
शून्य interrupt7_handler( शून्य )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
