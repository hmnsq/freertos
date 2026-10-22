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
#ଅନ୍ତର୍ଭାଵ <stdlib.h>

/* Kernel includes. */
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

/* Machine includes */
#ଅନ୍ତର୍ଭାଵ <machine/counter.h>
#ଅନ୍ତର୍ଭାଵ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#define portINITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );
/*-----------------------------------------------------------*/

ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_ଶୀର୍ଷ_Of_ଗଦା -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_ଶୀର୍ଷ_Of_ଗଦା[ 16 ] = 0;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 15 ] = portINITIAL_PSR;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 14 ] = ( uint32_t ) pxCode;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 13 ] = 0x00000000UL; /* R15. */
    px_ଶୀର୍ଷ_Of_ଗଦା[ 12 ] = 0x00000000UL; /* R14. */
    px_ଶୀର୍ଷ_Of_ଗଦା[ 11 ] = 0x0d0d0d0dUL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 10 ] = 0x0c0c0c0cUL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 9 ] = 0x0b0b0b0bUL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 8 ] = 0x0a0a0a0aUL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 7 ] = 0x09090909UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 6 ] = 0x08080808UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 5 ] = 0x07070707UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 4 ] = 0x06060606UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 3 ] = 0x05050505UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 2 ] = 0x04040404UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 1 ] = 0x03030303UL;
    px_ଶୀର୍ଷ_Of_ଗଦା[ 0 ] = ( uint32_t ) pvParameters;

    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    /* Set-up the timer interrupt. */
    prvSetupTimerInterrupt();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    portRESTORE_CONTEXT();

    /* Should not get here. */
    ଫେରନ୍ତୁ 0;
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1;
    counter1->ମୂଲ୍ୟ = counter1->reload;
    counter1->mask = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
ଶୂନ୍ୟ interrupt31_handler( ଶୂନ୍ୟ ) __attribute__( ( naked ) );
ଶୂନ୍ୟ interrupt31_handler( ଶୂନ୍ୟ )
{
    portSAVE_CONTEXT();
    __asm ଅସ୍ଥିର ( "call vTaskSwitchContext" );
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvProcessTick( ଶୂନ୍ୟ ) __attribute__( ( noinline ) );
ସ୍ଥିର ଶୂନ୍ୟ prvProcessTick( ଶୂନ୍ୟ )
{
    ଯଦି( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
ଶୂନ୍ୟ interrupt7_handler( ଶୂନ୍ୟ ) __attribute__( ( naked ) );
ଶୂନ୍ୟ interrupt7_handler( ଶୂନ୍ୟ )
{
    portSAVE_CONTEXT();
    prvProcessTick();
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
