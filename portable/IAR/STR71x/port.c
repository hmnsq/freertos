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
* Implementation of functions defined in portable.h for the ST STR71x ARM7
* port.
*----------------------------------------------------------*/

/* Library includes. */
#అన్తర్భావ "wdg.h"
#అన్తర్భావ "eic.h"

/* Standard includes. */
#అన్తర్భావ <stdlib.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Constants required to setup the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_SPSR           ( ( దొంతర_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు         ( ( దొంతర_Type_t ) 0x20 )
#నిర్వచించు పోర్టు_INSTRUCTION_కొలత       ( ( దొంతర_Type_t ) 4 )

/* Constants required to handle critical sections. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#నిర్వచించు పోర్టు_MICROS_చొప్పున_రెండవ      1000000

/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/* Tick interrupt routines for cooperative and preemptive operation
 * respectively.  The preemptive version is not defined as __irq as it is called
 * from an asm wrapper function. */
__arm __irq శూన్య v_పోర్టు_Non_Preemptive_Tick( శూన్య );
శూన్య v_పోర్టు_Preemptive_Tick( శూన్య );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    దొంతర_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_శిఖరం_యొక్క_దొంతర;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం + పోర్టు_INSTRUCTION_కొలత;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212;    /* R12 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111;    /* R11 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010;    /* R10 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909;    /* R9 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808;    /* R8 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707;    /* R7 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606;    /* R6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505;    /* R5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404;    /* R4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303;    /* R3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202;    /* R2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101;    /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_INITIAL_SPSR;

    ఒకవేళ( ( ( uint32_t ) px_సంకేతం & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_శిఖరం_యొక్క_దొంతర |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }

    px_శిఖరం_యొక్క_దొంతర--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
__arm __irq శూన్య v_పోర్టు_Non_Preemptive_Tick( శూన్య )
{
    /* Increment the tick count - which may wake some tasks but as the
     * preemptive scheduler is not being used any woken task is not given
     * processor time no matter what its priority. */
    xTaskIncrementTick();

    /* Clear the interrupt in the watchdog and EIC. */
    WDG->SR = 0x0000;
    పోర్టు_CLEAR_EIC();
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
శూన్య v_పోర్టు_Preemptive_Tick( శూన్య )
{
    /* Increment the tick counter. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        /* Select a new task to execute. */
        vTaskSwitchContext();
    }

    /* Clear the interrupt in the watchdog and EIC. */
    WDG->SR = 0x0000;
    పోర్టు_CLEAR_EIC();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Set the watchdog up to generate a periodic tick. */
    WDG_ECITConfig( DISABLE );
    WDG_CntOnOffConfig( DISABLE );
    WDG_Period_విలువ_Config( పోర్టు_MICROS_చొప్పున_రెండవ / config_TICK_రేటు_HZ );

    /* Setup the tick interrupt in the EIC. */
    EIC_IRQChannel_ప్రాధాన్యత_Config( WDG_IRQChannel, 1 );
    EIC_IRQChannelConfig( WDG_IRQChannel, ENABLE );
    EIC_IRQConfig( ENABLE );
    WDG_ECITConfig( ENABLE );

    /* Start the timer - interrupts are actually disabled at this point so
     * it is safe to do this here. */
    WDG_CntOnOffConfig( ENABLE );
}
/*-----------------------------------------------------------*/

__arm __interwork శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
