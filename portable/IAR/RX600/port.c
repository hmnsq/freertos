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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Library includes. */
#شامل "string.h"

/* Hardware specifics. */
#شامل <iorx62n.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#تعریف_کرو پورٹ_INITIAL_PSW     ( ( ڈھیر_Type_t ) 0x00030000 )
#تعریف_کرو پورٹ_INITIAL_FPSW    ( ( ڈھیر_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
خارجی خالی prv_آغاز_پہلا_Task( خالی );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt خالی vTickISR( خالی );

/*-----------------------------------------------------------*/

خارجی خالی * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_چوٹی_کا_ڈھیر = 0x00;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_PSW;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #اگر_تعریف_شدہ USE_بھرا_رجسٹر_INITIALISATION
    {
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xffffffff; /* r15. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xeeeeeeee;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xdddddddd;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xcccccccc;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xbbbbbbbb;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0xaaaaaaaa;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x99999999;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x88888888;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x77777777;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x66666666;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x55555555;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x44444444;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x33333333;
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = 0x22222222;
        px_چوٹی_کا_ڈھیر--;
    }
    #ورنہ /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_چوٹی_کا_ڈھیر -= 15;
    }
    #اگر_ختم /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_FPSW;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x12345678; /* Accumulator. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x87654321; /* Accumulator. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    خارجی خالی v_Application_تیاری_Timer_مداخلت( خالی );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    اگر( pxCurrentTCB != تہی )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_تیاری_Timer_مداخلت();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_مداخلت_ترجیح;

        /* Start the first task. */
        prv_آغاز_پہلا_Task();
    }

    /* Should not get here. */
    واپس pdFAIL;
}
/*-----------------------------------------------------------*/

#ہدایت سمتیہ = config_TICK_سمتیہ
__interrupt خالی vTickISR( خالی )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( config_MAX_SYSCALL_مداخلت_ترجیح );
    {
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_مداخلت_ترجیح );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == تہی );
}
/*-----------------------------------------------------------*/
