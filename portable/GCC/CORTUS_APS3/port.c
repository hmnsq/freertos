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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/* Kernel includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Machine includes */
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/counter.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );
/*-----------------------------------------------------------*/

ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 16 ] = 0;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 15 ] = ਪੋਰਟ_INITIAL_PSR;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 14 ] = ( uint32_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 13 ] = 0x00000000UL; /* R15. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 12 ] = 0x00000000UL; /* R14. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 11 ] = 0x0d0d0d0dUL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 10 ] = 0x0c0c0c0cUL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 9 ] = 0x0b0b0b0bUL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 8 ] = 0x0a0a0a0aUL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 7 ] = 0x09090909UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 6 ] = 0x08080808UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 5 ] = 0x07070707UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 4 ] = 0x06060606UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 3 ] = 0x05050505UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 2 ] = 0x04040404UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 1 ] = 0x03030303UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ[ 0 ] = ( uint32_t ) pvParameters;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Set-up the timer interrupt. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    ਪੋਰਟ_RESTORE_CONTEXT();

    /* Should not get here. */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1;
    counter1->ਮੁੱਲ = counter1->reload;
    counter1->ਨਕਾਬ = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
ਖਾਲੀ interrupt31_handler( ਖਾਲੀ ) __attribute__( ( naked ) );
ਖਾਲੀ interrupt31_handler( ਖਾਲੀ )
{
    ਪੋਰਟ_SAVE_CONTEXT();
    __asm ਅਸਥਿਰ ( "call vTaskSwitchContext" );
    ਪੋਰਟ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvProcessTick( ਖਾਲੀ ) __attribute__( ( noinline ) );
ਸਥਿਰ ਖਾਲੀ prvProcessTick( ਖਾਲੀ )
{
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
ਖਾਲੀ interrupt7_handler( ਖਾਲੀ ) __attribute__( ( naked ) );
ਖਾਲੀ interrupt7_handler( ਖਾਲੀ )
{
    ਪੋਰਟ_SAVE_CONTEXT();
    prvProcessTick();
    ਪੋਰਟ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
