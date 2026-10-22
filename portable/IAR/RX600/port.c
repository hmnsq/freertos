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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Library includes. */
#అన్తర్భావ "string.h"

/* Hardware specifics. */
#అన్తర్భావ <iorx62n.h>

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#నిర్వచించు పోర్టు_INITIAL_PSW     ( ( దొంతర_Type_t ) 0x00030000 )
#నిర్వచించు పోర్టు_INITIAL_FPSW    ( ( దొంతర_Type_t ) 0x00000100 )

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
బాహ్య శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt శూన్య vTickISR( శూన్య );

/*-----------------------------------------------------------*/

బాహ్య శూన్య * pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* R0 is not included as it is the stack pointer. */

    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_PSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #నిర్వచితమైతే USE_నిండిన_రిజిస్టరు_INITIALISATION
    {
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xffffffff; /* r15. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xeeeeeeee;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xdddddddd;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xcccccccc;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xbbbbbbbb;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xaaaaaaaa;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x99999999;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x88888888;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x77777777;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x66666666;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x55555555;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x44444444;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x33333333;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x22222222;
        px_శిఖరం_యొక్క_దొంతర--;
    }
    #లేకపోతే /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        px_శిఖరం_యొక్క_దొంతర -= 15;
    }
    #అయితే_ముగింపు /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_FPSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x12345678; /* Accumulator. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x87654321; /* Accumulator. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_Application_అమరిక_Timer_అంతరాయం( శూన్య );

    /* Use pxCurrentTCB just so it does not get optimised away. */
    ఒకవేళ( pxCurrentTCB != ఖాళీ )
    {
        /* Call an application function to set up the timer that will generate the
         * tick interrupt.  This way the application can decide which peripheral to
         * use.  A demo application is provided to show a suitable example. */
        v_Application_అమరిక_Timer_అంతరాయం();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

        /* Start the first task. */
        prv_ప్రారంభం_మొదటి_Task();
    }

    /* Should not get here. */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

#సూచన సదిశ = config_TICK_సదిశ
__interrupt శూన్య vTickISR( శూన్య )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత );
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_అంతరాయం_ప్రాధాన్యత );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ఖాళీ );
}
/*-----------------------------------------------------------*/
