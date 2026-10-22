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
#അന്തര്ഭാവ <stdlib.h>

/* Kernel includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/* Machine includes */
#അന്തര്ഭാവ <machine/counter.h>
#അന്തര്ഭാവ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം );
/*-----------------------------------------------------------*/

അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_മുകൾ_Of_അട്ടി -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_മുകൾ_Of_അട്ടി[ 16 ] = 0;
    px_മുകൾ_Of_അട്ടി[ 15 ] = portINITIAL_PSR;
    px_മുകൾ_Of_അട്ടി[ 14 ] = ( uint32_t ) pxCode;
    px_മുകൾ_Of_അട്ടി[ 13 ] = 0x00000000UL; /* R15. */
    px_മുകൾ_Of_അട്ടി[ 12 ] = 0x00000000UL; /* R14. */
    px_മുകൾ_Of_അട്ടി[ 11 ] = 0x0d0d0d0dUL;
    px_മുകൾ_Of_അട്ടി[ 10 ] = 0x0c0c0c0cUL;
    px_മുകൾ_Of_അട്ടി[ 9 ] = 0x0b0b0b0bUL;
    px_മുകൾ_Of_അട്ടി[ 8 ] = 0x0a0a0a0aUL;
    px_മുകൾ_Of_അട്ടി[ 7 ] = 0x09090909UL;
    px_മുകൾ_Of_അട്ടി[ 6 ] = 0x08080808UL;
    px_മുകൾ_Of_അട്ടി[ 5 ] = 0x07070707UL;
    px_മുകൾ_Of_അട്ടി[ 4 ] = 0x06060606UL;
    px_മുകൾ_Of_അട്ടി[ 3 ] = 0x05050505UL;
    px_മുകൾ_Of_അട്ടി[ 2 ] = 0x04040404UL;
    px_മുകൾ_Of_അട്ടി[ 1 ] = 0x03030303UL;
    px_മുകൾ_Of_അട്ടി[ 0 ] = ( uint32_t ) pvParameters;

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    തിരികെ 0;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->മൂല്യം = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
ശൂന്യം interrupt31_handler( ശൂന്യം ) __attribute__( ( naked ) );
ശൂന്യം interrupt31_handler( ശൂന്യം )
{
    portSAVE_CONTEXT();
    __asm അസ്ഥിര ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvProcessTick( ശൂന്യം ) __attribute__( ( noinline ) );
സ്ഥിതം ശൂന്യം prvProcessTick( ശൂന്യം )
{
    എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
ശൂന്യം interrupt7_handler( ശൂന്യം ) __attribute__( ( naked ) );
ശൂന്യം interrupt7_handler( ശൂന്യം )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
