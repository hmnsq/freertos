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
* Implementation of functions defined in portable.h for the NIOS2 port.
*----------------------------------------------------------*/

/* Standard Includes. */
#అన్తర్భావ <string.h>
#అన్తర్భావ <errno.h>

/* Altera includes. */
#అన్తర్భావ "sys/alt_irq.h"
#అన్తర్భావ "sys/alt_exceptions.h"
#అన్తర్భావ "altera_avalon_timer_regs.h"
#అన్తర్భావ "priv/alt_irq_table.h"

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Interrupts are enabled. */
#నిర్వచించు పోర్టు_INITIAL_ESTATUS    ( దొంతర_Type_t ) 0x01

పూర్ణాంకం alt_ic_isr_రిజిస్టరు( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          శూన్య * isr_context,
                          శూన్య * flags );
/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Call back for the alarm function.
 */
శూన్య v_పోర్టు_Sys_Tick_Handler( శూన్య * context );

/*-----------------------------------------------------------*/

స్థిర శూన్య prvReadGp( uint32_t * ul_విలువ )
{
    asm ( "stw gp, (%0)" ::"r" ( ul_విలువ ) );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    దొంతర_Type_t * px_చట్రం_సూచిక = px_శిఖరం_యొక్క_దొంతర - 1;
    దొంతర_Type_t x_Global_సూచిక;

    prvReadGp( &x_Global_సూచిక );

    /* End of stack marker. */
    *px_శిఖరం_యొక్క_దొంతర = 0xdeadbeef;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_చట్రం_సూచిక;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = x_Global_సూచిక;

    /* Space for R23 to R16. */
    px_శిఖరం_యొక్క_దొంతర -= 9;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_ESTATUS;

    /* Space for R15 to R5. */
    px_శిఖరం_యొక్క_దొంతర -= 12;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;

    /* Space for R3 to R1, muldiv and RA. */
    px_శిఖరం_యొక్క_దొంతర -= 5;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task. */
    asm అస్థిర ( " movia r2, restore_sp_from_pxCurrentTCB        \n"
                   " jmp r2                                          " );

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the NIOS2 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Try to register the interrupt handler. */
    ఒకవేళ( -EINVAL == alt_ic_isr_రిజిస్టరు( SYS_CLK_IRQ_అంతరాయం_CONTROLLER_ID, SYS_CLK_IRQ, v_పోర్టు_Sys_Tick_Handler, 0x0, 0x0 ) )
    {
        /* Failed to install the Interrupt Handler. */
        asm ( "break" );
    }
    లేకపోతే
    {
        /* Configure SysTick to interrupt at the requested rate. */
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_పునాది, ALTERA_AVALON_TIMER_CONTROL_STOP_MSK );
        IOWR_ALTERA_AVALON_TIMER_PERIODL( SYS_CLK_పునాది, ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ ) & 0xFFFF );
        IOWR_ALTERA_AVALON_TIMER_PERIODH( SYS_CLK_పునాది, ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ ) >> 16 );
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_పునాది, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_ప్రారంభం_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK );
    }

    /* Clear any already pending interrupts generated by the Timer. */
    IOWR_ALTERA_AVALON_TIMER_స్థితి( SYS_CLK_పునాది, ~ALTERA_AVALON_TIMER_స్థితి_గమ్యం_MSK );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Sys_Tick_Handler( శూన్య * context )
{
    /* Increment the kernel tick. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the interrupt. */
    IOWR_ALTERA_AVALON_TIMER_స్థితి( SYS_CLK_పునాది, ~ALTERA_AVALON_TIMER_స్థితి_గమ్యం_MSK );
}
/*-----------------------------------------------------------*/

/** This function is a re-implementation of the Altera provided function.
 * The function is re-implemented to prevent it from enabling an interrupt
 * when it is registered. Interrupts should only be enabled after the FreeRTOS.org
 * kernel has its scheduler started so that contexts are saved and switched
 * correctly.
 */
పూర్ణాంకం alt_ic_isr_రిజిస్టరు( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          శూన్య * isr_context,
                          శూన్య * flags )
{
    పూర్ణాంకం rc = -EINVAL;
    alt_irq_context status;
    పూర్ణాంకం id = irq; /* IRQ interpreted as the interrupt ID. */

    ఒకవేళ( id < ALT_NIRQ )
    {
        /*
         * interrupts are disabled while the handler tables are updated to ensure
         * that an interrupt doesn't occur while the tables are in an inconsistent
         * state.
         */

        status = alt_irq_disable_all();

        alt_irq[ id ].handler = isr;
        alt_irq[ id ].context = isr_context;

        rc = ( isr ) ? alt_ic_irq_enable( ic_id, id ) : alt_ic_irq_disable( ic_id, id );

        /* alt_irq_enable_all(status); This line is removed to prevent the interrupt from being immediately enabled. */
    }

    తిరిగి rc;
}
/*-----------------------------------------------------------*/
