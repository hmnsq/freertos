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
#تعریف_کرو پورٹ_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );
/*-----------------------------------------------------------*/

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_چوٹی_دا_ڈھیر -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_چوٹی_دا_ڈھیر[ 16 ] = 0;
    px_چوٹی_دا_ڈھیر[ 15 ] = پورٹ_INITIAL_PSR;
    px_چوٹی_دا_ڈھیر[ 14 ] = ( uint32_t ) px_کوڈ;
    px_چوٹی_دا_ڈھیر[ 13 ] = 0x00000000UL; /* R15. */
    px_چوٹی_دا_ڈھیر[ 12 ] = 0x00000000UL; /* R14. */
    px_چوٹی_دا_ڈھیر[ 11 ] = 0x0d0d0d0dUL;
    px_چوٹی_دا_ڈھیر[ 10 ] = 0x0c0c0c0cUL;
    px_چوٹی_دا_ڈھیر[ 9 ] = 0x0b0b0b0bUL;
    px_چوٹی_دا_ڈھیر[ 8 ] = 0x0a0a0a0aUL;
    px_چوٹی_دا_ڈھیر[ 7 ] = 0x09090909UL;
    px_چوٹی_دا_ڈھیر[ 6 ] = 0x08080808UL;
    px_چوٹی_دا_ڈھیر[ 5 ] = 0x07070707UL;
    px_چوٹی_دا_ڈھیر[ 4 ] = 0x06060606UL;
    px_چوٹی_دا_ڈھیر[ 3 ] = 0x05050505UL;
    px_چوٹی_دا_ڈھیر[ 2 ] = 0x04040404UL;
    px_چوٹی_دا_ڈھیر[ 1 ] = 0x03030303UL;
    px_چوٹی_دا_ڈھیر[ 0 ] = ( uint32_t ) pvParameters;

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* Set-up the timer interrupt. */
    prv_تیاری_Timer_رکاوٹ();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    پورٹ_RESTORE_CONTEXT();

    /* Should not get here. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1;
    counter1->قدر = counter1->reload;
    counter1->نقاب = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
فراغ interrupt31_handler( فراغ ) __attribute__( ( naked ) );
فراغ interrupt31_handler( فراغ )
{
    پورٹ_SAVE_CONTEXT();
    __asm متطاير ( "call vTaskSwitchContext" );
    پورٹ_RESTORE_CONTEXT();
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
    پورٹ_SAVE_CONTEXT();
    prvProcessTick();
    پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
