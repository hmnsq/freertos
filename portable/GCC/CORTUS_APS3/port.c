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
#परिभाषय पत्तनम्_INITIAL_PSR    ( 0x00020000 )

/*-----------------------------------------------------------*/

/*
 * Perform any hardware configuration necessary to generate the tick interrupt.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );
/*-----------------------------------------------------------*/

राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Make space on the stack for the context - this leaves a couple of spaces
     * empty.  */
    px_शिखरम्_सम्बन्धि_राशिः -= 20;

    /* Fill the registers with known values to assist debugging. */
    px_शिखरम्_सम्बन्धि_राशिः[ 16 ] = 0;
    px_शिखरम्_सम्बन्धि_राशिः[ 15 ] = पत्तनम्_INITIAL_PSR;
    px_शिखरम्_सम्बन्धि_राशिः[ 14 ] = ( uint32_t ) px_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः[ 13 ] = 0x00000000UL; /* R15. */
    px_शिखरम्_सम्बन्धि_राशिः[ 12 ] = 0x00000000UL; /* R14. */
    px_शिखरम्_सम्बन्धि_राशिः[ 11 ] = 0x0d0d0d0dUL;
    px_शिखरम्_सम्बन्धि_राशिः[ 10 ] = 0x0c0c0c0cUL;
    px_शिखरम्_सम्बन्धि_राशिः[ 9 ] = 0x0b0b0b0bUL;
    px_शिखरम्_सम्बन्धि_राशिः[ 8 ] = 0x0a0a0a0aUL;
    px_शिखरम्_सम्बन्धि_राशिः[ 7 ] = 0x09090909UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 6 ] = 0x08080808UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 5 ] = 0x07070707UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 4 ] = 0x06060606UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 3 ] = 0x05050505UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 2 ] = 0x04040404UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 1 ] = 0x03030303UL;
    px_शिखरम्_सम्बन्धि_राशिः[ 0 ] = ( uint32_t ) pvParameters;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Set-up the timer interrupt. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Integrated Interrupt Controller: Enable all interrupts. */
    ic->ien = 1;

    /* Restore callee saved registers. */
    पत्तनम्_RESTORE_CONTEXT();

    /* Should not get here. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Enable timer interrupts */
    counter1->reload = ( configCPU_CLOCK_HZ / config_TICK_दरः_HZ ) - 1;
    counter1->मानम् = counter1->reload;
    counter1->आवरणम् = 1;

    /* Set the IRQ Handler priority and enable it. */
    irq[ IRQ_COUNTER1 ].ien = 1;
}
/*-----------------------------------------------------------*/

/* Trap 31 handler. */
शून्य interrupt31_handler( शून्य ) __attribute__( ( naked ) );
शून्य interrupt31_handler( शून्य )
{
    पत्तनम्_SAVE_CONTEXT();
    __asm चञ्चल ( "call vTaskSwitchContext" );
    पत्तनम्_RESTORE_CONTEXT();
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
    पत्तनम्_SAVE_CONTEXT();
    prvProcessTick();
    पत्तनम्_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Nothing to do. Unlikely to want to end. */
}
/*-----------------------------------------------------------*/
