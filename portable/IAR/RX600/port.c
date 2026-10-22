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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Library includes. */
#ಅನ್ತರ್ಭಾವ "string.h"

/* Hardware specifics. */
#ಅನ್ತರ್ಭಾವ <iorx62n.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSW     ( ( ರಾಶಿ_Type_t ) 0x00030000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FPSW    ( ( ರಾಶಿ_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ಶೂನ್ಯ * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_PSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ತುಂಬಿದ_ರಿಜಿಸ್ಟರ್_INITIALISATION
    {
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xffffffff; /* r15. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xeeeeeeee;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xdddddddd;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xcccccccc;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xbbbbbbbb;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xaaaaaaaa;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x99999999;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x88888888;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x77777777;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x66666666;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x55555555;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x44444444;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x33333333;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x22222222;
        px_ತುದಿ_ದ_ರಾಶಿ--;
    }
    #ಇಲ್ಲದಿದ್ದರೆ /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_ತುದಿ_ದ_ರಾಶಿ -= 15;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_FPSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x12345678; /* Accumulator. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x87654321; /* Accumulator. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    ಆದರೆ( pxCurrentTCB != ಖಾಲಿ )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

        /* Start the first task. */
        prv_ಆರಂಭ_ಮೊದಲ_Task();
    }

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ ಸದಿಶ = config_TICK_ಸದಿಶ
__interrupt ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ಖಾಲಿ );
}
/*-----------------------------------------------------------*/
