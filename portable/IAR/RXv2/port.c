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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Library includes. */
#अन्तर्भाव "string.h"

/* Hardware specifics. */
#अन्तर्भाव <machine.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW     ( ( चळत_Type_t ) 0x00030000 )
#define portINITIAL_FPSW    ( ( चळत_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
बाह्य शून्य prvStartFirstTask( शून्य );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt शून्य vTickISR( शून्य );

/*-----------------------------------------------------------*/

बाह्य शून्य * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
चळत_Type_t * px_Port_Initialise_चळत( चळत_Type_t * px_शीर्ष_Of_चळत,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_शीर्ष_Of_चळत = 0x00;
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = portINITIAL_PSW;
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = ( चळत_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
    {
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xffffffff; /* r15. */
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xeeeeeeee;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xdddddddd;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xcccccccc;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xbbbbbbbb;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0xaaaaaaaa;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x99999999;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x88888888;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x77777777;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x66666666;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x55555555;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x44444444;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x33333333;
        px_शीर्ष_Of_चळत--;
        *px_शीर्ष_Of_चळत = 0x22222222;
        px_शीर्ष_Of_चळत--;
    }
    #अन्यथा /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_शीर्ष_Of_चळत -= 15;
    }
    #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_शीर्ष_Of_चळत = ( चळत_Type_t ) pvParameters; /* R1 */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = portINITIAL_FPSW;
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x11111111; /* Accumulator 0. */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x22222222; /* Accumulator 0. */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x33333333; /* Accumulator 0. */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x44444444; /* Accumulator 1. */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x55555555; /* Accumulator 1. */
    px_शीर्ष_Of_चळत--;
    *px_शीर्ष_Of_चळत = 0x66666666; /* Accumulator 1. */

    परत px_शीर्ष_Of_चळत;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    बाह्य शून्य vApplicationSetupTimerInterrupt( शून्य );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    जर( pxCurrentTCB != रिक्त )
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
    परत pdFAIL;
}
/*-----------------------------------------------------------*/

#pragma vector = configTICK_VECTOR
__interrupt शून्य vTickISR( शून्य )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        जर( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( configKERNEL_INTERRUPT_PRIORITY );
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == रिक्त );
}
/*-----------------------------------------------------------*/
