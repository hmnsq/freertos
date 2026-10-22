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
#ಅನ್ತರ್ಭಾವ <stdlib.h>

/* Kernel includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Machine includes */
#ಅನ್ತರ್ಭಾವ <machine/counter.h>
#ಅನ್ತರ್ಭಾವ <machine/ic.h>
/*-----------------------------------------------------------*/

/* The initial PSR has the Previous Interrupt Enabled (PIEN) flag set. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_ತುದಿ_ದ_ರಾಶಿ -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_ತುದಿ_ದ_ರಾಶಿ[ 16 ] = 0;
    px_ತುದಿ_ದ_ರಾಶಿ[ 15 ] = ಪೋರ್ಟ್_INITIAL_PSR;
    px_ತುದಿ_ದ_ರಾಶಿ[ 14 ] = ( uint32_t ) px_ಸಂಕೇತ;
    px_ತುದಿ_ದ_ರಾಶಿ[ 13 ] = 0x00000000UL; /* R15. */
    px_ತುದಿ_ದ_ರಾಶಿ[ 12 ] = 0x00000000UL; /* R14. */
    px_ತುದಿ_ದ_ರಾಶಿ[ 11 ] = 0x0d0d0d0dUL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 10 ] = 0x0c0c0c0cUL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 9 ] = 0x0b0b0b0bUL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 8 ] = 0x0a0a0a0aUL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 7 ] = 0x09090909UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 6 ] = 0x08080808UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 5 ] = 0x07070707UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 4 ] = 0x06060606UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 3 ] = 0x05050505UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 2 ] = 0x04040404UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 1 ] = 0x03030303UL;
    px_ತುದಿ_ದ_ರಾಶಿ[ 0 ] = ( uint32_t ) pvParameters;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Set-up the timer interrupt. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1;
    counter1->ಮೌಲ್ಯ = counter1->reload;
    counter1->ಮುಖವಾಡ = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
ಶೂನ್ಯ interrupt31_handler( ಶೂನ್ಯ ) __attribute__( ( naked ) );
ಶೂನ್ಯ interrupt31_handler( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_SAVE_CONTEXT();
    __asm ಅಸ್ಥಿರ ( "call vTaskSwitchContext" );
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvProcessTick( ಶೂನ್ಯ ) __attribute__( ( noinline ) );
ಸ್ಥಿರ ಶೂನ್ಯ prvProcessTick( ಶೂನ್ಯ )
{
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the Tick Interrupt. */
    counter1->expired = 0;
}
/*-----------------------------------------------------------*/

/* Timer 1 interrupt handler, used for tick interrupt. */
ಶೂನ್ಯ interrupt7_handler( ಶೂನ್ಯ ) __attribute__( ( naked ) );
ಶೂನ್ಯ interrupt7_handler( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_SAVE_CONTEXT();
    prvProcessTick();
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
