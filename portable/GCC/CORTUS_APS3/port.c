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
#تعریف_کړه پورټ_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );
/*-----------------------------------------------------------*/

ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_سر_د_ډېری -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_سر_د_ډېری[ 16 ] = 0;
    px_سر_د_ډېری[ 15 ] = پورټ_INITIAL_PSR;
    px_سر_د_ډېری[ 14 ] = ( uint32_t ) px_کوډ;
    px_سر_د_ډېری[ 13 ] = 0x00000000UL; /* R15. */
    px_سر_د_ډېری[ 12 ] = 0x00000000UL; /* R14. */
    px_سر_د_ډېری[ 11 ] = 0x0d0d0d0dUL;
    px_سر_د_ډېری[ 10 ] = 0x0c0c0c0cUL;
    px_سر_د_ډېری[ 9 ] = 0x0b0b0b0bUL;
    px_سر_د_ډېری[ 8 ] = 0x0a0a0a0aUL;
    px_سر_د_ډېری[ 7 ] = 0x09090909UL;
    px_سر_د_ډېری[ 6 ] = 0x08080808UL;
    px_سر_د_ډېری[ 5 ] = 0x07070707UL;
    px_سر_د_ډېری[ 4 ] = 0x06060606UL;
    px_سر_د_ډېری[ 3 ] = 0x05050505UL;
    px_سر_د_ډېری[ 2 ] = 0x04040404UL;
    px_سر_د_ډېری[ 1 ] = 0x03030303UL;
    px_سر_د_ډېری[ 0 ] = ( uint32_t ) pvParameters;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    /* Set-up the timer interrupt. */
    prv_تیاری_Timer_مداخله();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    پورټ_RESTORE_CONTEXT();

    /* Should not get here. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1;
    counter1->ارزښت = counter1->reload;
    counter1->ماسک = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
فراغ interrupt31_handler( فراغ ) __attribute__( ( naked ) );
فراغ interrupt31_handler( فراغ )
{
    پورټ_SAVE_CONTEXT();
    __asm متطاير ( "call vTaskSwitchContext" );
    پورټ_RESTORE_CONTEXT();
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
    پورټ_SAVE_CONTEXT();
    prvProcessTick();
    پورټ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
