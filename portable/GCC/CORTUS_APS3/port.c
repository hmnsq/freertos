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
#ضمن <stdlib.h>

/* Kernel includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Machine includes */
#ضمن <machine/counter.h>
#ضمن <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ساكن فراغ prvSetupTimerInterrupt( فراغ );
/*-----------------------------------------------------------*/

مكدس_Type_t * px_Port_Initialise_مكدس( مكدس_Type_t * px_قمة_Of_مكدس,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_قمة_Of_مكدس -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_قمة_Of_مكدس[ 16 ] = 0;
    px_قمة_Of_مكدس[ 15 ] = portINITIAL_PSR;
    px_قمة_Of_مكدس[ 14 ] = ( uint32_t ) pxCode;
    px_قمة_Of_مكدس[ 13 ] = 0x00000000UL; /* R15. */
    px_قمة_Of_مكدس[ 12 ] = 0x00000000UL; /* R14. */
    px_قمة_Of_مكدس[ 11 ] = 0x0d0d0d0dUL;
    px_قمة_Of_مكدس[ 10 ] = 0x0c0c0c0cUL;
    px_قمة_Of_مكدس[ 9 ] = 0x0b0b0b0bUL;
    px_قمة_Of_مكدس[ 8 ] = 0x0a0a0a0aUL;
    px_قمة_Of_مكدس[ 7 ] = 0x09090909UL;
    px_قمة_Of_مكدس[ 6 ] = 0x08080808UL;
    px_قمة_Of_مكدس[ 5 ] = 0x07070707UL;
    px_قمة_Of_مكدس[ 4 ] = 0x06060606UL;
    px_قمة_Of_مكدس[ 3 ] = 0x05050505UL;
    px_قمة_Of_مكدس[ 2 ] = 0x04040404UL;
    px_قمة_Of_مكدس[ 1 ] = 0x03030303UL;
    px_قمة_Of_مكدس[ 0 ] = ( uint32_t ) pvParameters;

    إرجاع px_قمة_Of_مكدس;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    إرجاع 0;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSetupTimerInterrupt( فراغ )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->قيمة = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
فراغ interrupt31_handler( فراغ ) __attribute__( ( naked ) );
فراغ interrupt31_handler( فراغ )
{
    portSAVE_CONTEXT();
    __asm متطاير ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ساكن فراغ prvProcessTick( فراغ ) __attribute__( ( noinline ) );
ساكن فراغ prvProcessTick( فراغ )
{
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
فراغ interrupt7_handler( فراغ ) __attribute__( ( naked ) );
فراغ interrupt7_handler( فراغ )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
