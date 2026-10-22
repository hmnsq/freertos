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

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the SH2A port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Library includes. */
#অন্তর্ভাব "string.h"

/* Hardware specifics. */
#অন্তর্ভাব <machine.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( স্তূপ_Type_t ) 0x00030000 )
#define portINITIAL_FPSW    ( ( স্তূপ_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
বাহ্যিক শূন্য prvStartFirstTask( শূন্য );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt শূন্য vTickISR( শূন্য );

/*-----------------------------------------------------------*/

বাহ্যিক শূন্য * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_শীর্ষ_Of_স্তূপ = 0x00;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_PSW;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
    {
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0xffffffff; /* r15. */
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0xeeeeeeee;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0xdddddddd;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0xcccccccc;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0xbbbbbbbb;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0xaaaaaaaa;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x99999999;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x88888888;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x77777777;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x66666666;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x55555555;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x44444444;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x33333333;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = 0x22222222;
        px_শীর্ষ_Of_স্তূপ--;
    }
    #অন্যথা /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_শীর্ষ_Of_স্তূপ -= 15;
    }
    #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters; /* R1 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_FPSW;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x11111111; /* Accumulator 0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x22222222; /* Accumulator 0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x33333333; /* Accumulator 0. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x44444444; /* Accumulator 1. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x55555555; /* Accumulator 1. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x66666666; /* Accumulator 1. */

    ফেরত px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    বাহ্যিক শূন্য vApplicationSetupTimerInterrupt( শূন্য );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    যদি( pxCurrentTCB != ফাঁকা )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        vApplicationSetupTimerInterrupt();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = configKERNEL_INTERRUPT_PRIORITY;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Should not get here. */
    ফেরত pdFAIL;
}
/*-----------------------------------------------------------*/

#pragma vector = configTICK_VECTOR
__interrupt শূন্য vTickISR( শূন্য )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( configKERNEL_INTERRUPT_PRIORITY );
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ফাঁকা );
}
/*-----------------------------------------------------------*/
