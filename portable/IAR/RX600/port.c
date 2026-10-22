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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/* Hardware specifics. */
#ضمن <iorx62n.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#تعریف_کړه پورټ_INITIAL_PSW     ( ( ډېری_Type_t ) 0x00030000 )
#تعریف_کړه پورټ_INITIAL_FPSW    ( ( ډېری_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
خارجي فراغ prv_پیل_لومړی_Task( فراغ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt فراغ vTickISR( فراغ );

/*-----------------------------------------------------------*/

خارجي فراغ * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_سر_د_ډېری = 0x00;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = پورټ_INITIAL_PSW;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #که_تعریف_شوی USE_ډک_ثبتوونکی_INITIALISATION
    {
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0xffffffff; /* r15. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0xeeeeeeee;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0xdddddddd;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0xcccccccc;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0xbbbbbbbb;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0xaaaaaaaa;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x99999999;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x88888888;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x77777777;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x66666666;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x55555555;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x44444444;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x33333333;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = 0x22222222;
        px_سر_د_ډېری--;
    }
    #وإلا /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_سر_د_ډېری -= 15;
    }
    #د_که_پای /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R1 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = پورټ_INITIAL_FPSW;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x12345678; /* Accumulator. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x87654321; /* Accumulator. */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ v_Application_تیاری_Timer_مداخله( فراغ );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    إذا( pxCurrentTCB != عدم )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_تیاری_Timer_مداخله();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_مداخله_لومړیتوب;

        /* Start the first task. */
        prv_پیل_لومړی_Task();
    }

    /* Should not get here. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

#لارښوونه ویکټور = config_TICK_ویکټور
__interrupt فراغ vTickISR( فراغ )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( config_MAX_SYSCALL_مداخله_لومړیتوب );
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_مداخله_لومړیتوب );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == عدم );
}
/*-----------------------------------------------------------*/
