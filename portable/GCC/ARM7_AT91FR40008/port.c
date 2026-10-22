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
* Implementation of functions defined in portable.h for the Atmel AT91R40008
* port.
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

/* Hardware specific definitions. */
#అన్తర్భావ "AT91R40008.h"
#అన్తర్భావ "pio.h"
#అన్తర్భావ "aic.h"
#అన్తర్భావ "tc.h"

/* Constants required to setup the task context. */
#నిర్వచించు పోర్టు_INITIAL_SPSR                   ( ( దొంతర_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు                 ( ( దొంతర_Type_t ) 0x20 )
#నిర్వచించు పోర్టు_INSTRUCTION_కొలత               ( ( దొంతర_Type_t ) 4 )
#నిర్వచించు పోర్టు_NO_CRITICAL_SECTION_NESTING    ( ( దొంతర_Type_t ) 0 )
#నిర్వచించు పోర్టు_TICK_ప్రాధాన్యత_6                ( 6 )
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
 * Setup the tick timer to generate the tick interrupts at the required frequency.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    అస్థిర uint32_t ulDummy;

    /* Enable clock to the tick timer... */
    AT91_C_పునాది_PS->PS_PCER = పోర్టు_TIMER_CLK_ENABLE_బిట్టు;

    /* Stop the tick timer... */
    పోర్టు_TIMER_REG_పునాది_PTR->TC_CCR = TC_CLKDIS;

    /* Start with tick timer interrupts disabled... */
    పోర్టు_TIMER_REG_పునాది_PTR->TC_IDR = 0xFFFFFFFF;

    /* Clear any pending tick timer interrupts... */
    ulDummy = పోర్టు_TIMER_REG_పునాది_PTR->TC_SR;

    /* Store interrupt handler function address in tick timer vector register...
     * The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #ఒకవేళ configUSE_PREEMPTION == 1
    {
        బాహ్య శూన్య( vPreemptiveTick )( శూన్య );
        AT91_C_పునాది_AIC->AIC_SVR[ పోర్టు_TIMER_AIC_CHANNEL ] = ( uint32_t ) vPreemptiveTick;
    }
    #లేకపోతే // else use cooperative scheduler
    {
        బాహ్య శూన్య( vNonPreemptiveTick )( శూన్య );
        AT91_C_పునాది_AIC->AIC_SVR[ పోర్టు_TIMER_AIC_CHANNEL ] = ( uint32_t ) vNonPreemptiveTick;
    }
    #అయితే_ముగింపు

    /* Tick timer interrupt level-sensitive, priority 6... */
    AT91_C_పునాది_AIC->AIC_SMR[ పోర్టు_TIMER_AIC_CHANNEL ] = AIC_SRCTYPE_INT_LEVEL_SENSITIVE | పోర్టు_TICK_ప్రాధాన్యత_6;

    /* Enable the tick timer interrupt...
     *
     * First at timer level */
    పోర్టు_TIMER_REG_పునాది_PTR->TC_IER = TC_CPCS;

    /* Then at the AIC level. */
    AT91_C_పునాది_AIC->AIC_IECR = ( 1 << పోర్టు_TIMER_AIC_CHANNEL );

    /* Calculate timer compare value to achieve the desired tick rate... */
    ఒకవేళ( ( configCPU_CLOCK_HZ / ( config_TICK_రేటు_HZ * 2 ) ) <= 0xFFFF )
    {
        /* The tick rate is fast enough for us to use the faster timer input
         * clock (main clock / 2). */
        పోర్టు_TIMER_REG_పునాది_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK2 | TC_వ్యవధి_NONE | TC_CPCTRG;
        పోర్టు_TIMER_REG_పునాది_PTR->TC_RC = configCPU_CLOCK_HZ / ( config_TICK_రేటు_HZ * 2 );
    }
    లేకపోతే
    {
        /* We must use a slower timer input clock (main clock / 8) because the
         * tick rate is too slow for the faster input clock. */
        పోర్టు_TIMER_REG_పునాది_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK8 | TC_వ్యవధి_NONE | TC_CPCTRG;
        పోర్టు_TIMER_REG_పునాది_PTR->TC_RC = configCPU_CLOCK_HZ / ( config_TICK_రేటు_HZ * 8 );
    }

    /* Start tick timer... */
    పోర్టు_TIMER_REG_పునాది_PTR->TC_CCR = TC_SWTRG | TC_CLKEN;
}
/*-----------------------------------------------------------*/
