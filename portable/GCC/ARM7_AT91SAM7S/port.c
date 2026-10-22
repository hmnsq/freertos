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
* Implementation of functions defined in portable.h for the ARM7 port.
*
* Components that can be compiled to either ARM or THUMB mode are
* contained in this file.  The ISR routines, which can only be compiled
* to ARM mode are contained in portISR.c.
*----------------------------------------------------------*/

/* Standard includes. */
#అన్తర్భావ <stdlib.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Processor constants. */
#అన్తర్భావ "AT91SAM7X256.h"

/* Constants required to setup the task context. */
#నిర్వచించు పోర్టు_INITIAL_SPSR                   ( ( దొంతర_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు                 ( ( దొంతర_Type_t ) 0x20 )
#నిర్వచించు పోర్టు_INSTRUCTION_కొలత               ( ( దొంతర_Type_t ) 4 )
#నిర్వచించు పోర్టు_NO_CRITICAL_SECTION_NESTING    ( ( దొంతర_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#నిర్వచించు పోర్టు_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#నిర్వచించు పోర్టు_PRESCALE_విలువ                 0x00
#నిర్వచించు పోర్టు_అంతరాయం_ON_సరిపోలిక             ( ( uint32_t ) 0x01 )
#నిర్వచించు పోర్టు_RESET_లెక్క_ON_సరిపోలిక           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#నిర్వచించు పోర్టు_PIT_CLOCK_భాజకం              ( ( uint32_t ) 16 )
#నిర్వచించు పోర్టు_PIT_COUNTER_విలువ              ( ( ( configCPU_CLOCK_HZ / పోర్టు_PIT_CLOCK_భాజకం ) / 1000UL ) * పోర్టు_TICK_PERIOD_MS )

#నిర్వచించు పోర్టు_INT_LEVEL_SENSITIVE            0
#నిర్వచించు పోర్టు_PIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#నిర్వచించు పోర్టు_PIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
బాహ్య శూన్య v_పోర్టు_ISRStart_మొదటి_Task( శూన్య );

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

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00000000;    /* R14 */
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

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_INITIAL_SPSR;

    #నిర్వచితమైతే THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_శిఖరం_యొక్క_దొంతర |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }
    #అయితే_ముగింపు

    px_శిఖరం_యొక్క_దొంతర--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_SECTION_NESTING;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task. */
    v_పోర్టు_ISRStart_మొదటి_Task();

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

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    AT91PS_PITC pxPIT = AT91_C_పునాది_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #ఒకవేళ configUSE_PREEMPTION == 0
        బాహ్య శూన్య( vNonPreemptiveTick ) ( శూన్య );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_పూర్వ_HIGHEST, పోర్టు_INT_LEVEL_SENSITIVE, ( శూన్య ( * )( శూన్య ) )vNonPreemptiveTick );
    #లేకపోతే
        బాహ్య శూన్య( vPreemptiveTick )( శూన్య );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_పూర్వ_HIGHEST, పోర్టు_INT_LEVEL_SENSITIVE, ( శూన్య ( * )( శూన్య ) )vPreemptiveTick );
    #అయితే_ముగింపు

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = పోర్టు_PIT_ENABLE | పోర్టు_PIT_INT_ENABLE | పోర్టు_PIT_COUNTER_విలువ;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91_C_పునాది_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
