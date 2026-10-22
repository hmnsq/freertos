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
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

/* Library includes. */
#அந்தர்பாவ "string.h"

/* Hardware specifics. */
#அந்தர்பாவ <iorx62n.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( அடுக்கு_Type_t ) 0x00030000 )
#define portINITIAL_FPSW    ( ( அடுக்கு_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
வெளி வெறுமை prvStartFirstTask( வெறுமை );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt வெறுமை vTickISR( வெறுமை );

/*-----------------------------------------------------------*/

வெளி வெறுமை * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_உச்சி_Of_அடுக்கு = 0x00;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = portINITIAL_PSW;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
    {
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xffffffff; /* r15. */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xeeeeeeee;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xdddddddd;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xcccccccc;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xbbbbbbbb;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xaaaaaaaa;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x99999999;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x88888888;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x77777777;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x66666666;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x55555555;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x44444444;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x33333333;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x22222222;
        px_உச்சி_Of_அடுக்கு--;
    }
    #இல்லையெனில் /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_உச்சி_Of_அடுக்கு -= 15;
    }
    #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pvParameters; /* R1 */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = portINITIAL_FPSW;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x12345678; /* Accumulator. */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x87654321; /* Accumulator. */

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    வெளி வெறுமை vApplicationSetupTimerInterrupt( வெறுமை );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    எனில்( pxCurrentTCB != வெற்று )
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
    திரும்பு pdFAIL;
}
/*-----------------------------------------------------------*/

#pragma vector = configTICK_VECTOR
__interrupt வெறுமை vTickISR( வெறுமை )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( configKERNEL_INTERRUPT_PRIORITY );
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == வெற்று );
}
/*-----------------------------------------------------------*/
