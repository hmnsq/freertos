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
#وصف_ڪريو پورٽ_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );
/*-----------------------------------------------------------*/

ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_چوٽي_جو_ڍير -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_چوٽي_جو_ڍير[ 16 ] = 0;
    px_چوٽي_جو_ڍير[ 15 ] = پورٽ_INITIAL_PSR;
    px_چوٽي_جو_ڍير[ 14 ] = ( uint32_t ) px_ڪوڊ;
    px_چوٽي_جو_ڍير[ 13 ] = 0x00000000UL; /* R15. */
    px_چوٽي_جو_ڍير[ 12 ] = 0x00000000UL; /* R14. */
    px_چوٽي_جو_ڍير[ 11 ] = 0x0d0d0d0dUL;
    px_چوٽي_جو_ڍير[ 10 ] = 0x0c0c0c0cUL;
    px_چوٽي_جو_ڍير[ 9 ] = 0x0b0b0b0bUL;
    px_چوٽي_جو_ڍير[ 8 ] = 0x0a0a0a0aUL;
    px_چوٽي_جو_ڍير[ 7 ] = 0x09090909UL;
    px_چوٽي_جو_ڍير[ 6 ] = 0x08080808UL;
    px_چوٽي_جو_ڍير[ 5 ] = 0x07070707UL;
    px_چوٽي_جو_ڍير[ 4 ] = 0x06060606UL;
    px_چوٽي_جو_ڍير[ 3 ] = 0x05050505UL;
    px_چوٽي_جو_ڍير[ 2 ] = 0x04040404UL;
    px_چوٽي_جو_ڍير[ 1 ] = 0x03030303UL;
    px_چوٽي_جو_ڍير[ 0 ] = ( uint32_t ) pvParameters;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Set-up the timer interrupt. */
    prv_تياري_Timer_مداخلت();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    پورٽ_RESTORE_CONTEXT();

    /* Should not get here. */
    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
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
    پورٽ_SAVE_CONTEXT();
    __asm متطاير ( "call vTaskSwitchContext" );
    پورٽ_RESTORE_CONTEXT();
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
    پورٽ_SAVE_CONTEXT();
    prvProcessTick();
    پورٽ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
