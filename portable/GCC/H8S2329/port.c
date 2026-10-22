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

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"


/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the H8S port.
*----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* When the task starts interrupts should be enabled. */
#నిర్వచించు పోర్టు_INITIAL_CCR                    ( ( దొంతర_Type_t ) 0x00 )

/* Hardware specific constants used to generate the RTOS tick from the TPU. */
#నిర్వచించు పోర్టు_CLEAR_ON_TGRA_COMPARE_సరిపోలిక    ( ( uint8_t ) 0x20 )
#నిర్వచించు పోర్టు_CLOCK_DIV_64                   ( ( uint8_t ) 0x03 )
#నిర్వచించు పోర్టు_CLOCK_DIV                      ( ( uint32_t ) 64 )
#నిర్వచించు పోర్టు_TGRA_అంతరాయం_ENABLE          ( ( uint8_t ) 0x01 )
#నిర్వచించు పోర్టు_TIMER_CHANNEL                  ( ( uint8_t ) 0x02 )
#నిర్వచించు పోర్టు_MSTP13                         ( ( uint16_t ) 0x2000 )

/*
 * Setup TPU channel one for the RTOS tick at the requested frequency.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * The ISR used by portYIELD(). This is installed as a trap handler.
 */
శూన్య v_పోర్టు_Yield( శూన్య ) __attribute__( ( saveall, అంతరాయం_handler ) );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    uint32_t ul_విలువ;

    /* This requires an even address. */
    ul_విలువ = ( uint32_t ) px_శిఖరం_యొక్క_దొంతర;

    ఒకవేళ( ul_విలువ & 1UL )
    {
        px_శిఖరం_యొక్క_దొంతర = px_శిఖరం_యొక్క_దొంతర - 1;
    }

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0xaa;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0xbb;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0xcc;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0xdd;

    /* The initial stack mimics an interrupt stack.  First there is the program
     * counter (24 bits). */
    ul_విలువ = ( uint32_t ) px_సంకేతం;

    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );
    px_శిఖరం_యొక్క_దొంతర--;
    ul_విలువ >>= 8UL;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );
    px_శిఖరం_యొక్క_దొంతర--;
    ul_విలువ >>= 8UL;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );

    /* Followed by the CCR. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_CCR;

    /* Next all the general purpose registers - with the parameters being passed
     * in ER0.  The parameter order must match that used by the compiler when the
     * "saveall" function attribute is used. */

    /* ER6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x66;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x66;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x66;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x66;

    /* ER0 */
    ul_విలువ = ( uint32_t ) pvParameters;

    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );
    px_శిఖరం_యొక్క_దొంతర--;
    ul_విలువ >>= 8UL;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );
    px_శిఖరం_యొక్క_దొంతర--;
    ul_విలువ >>= 8UL;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );
    px_శిఖరం_యొక్క_దొంతర--;
    ul_విలువ >>= 8UL;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( ul_విలువ & 0xff );

    /* ER1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x11;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x11;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x11;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x11;

    /* ER2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22;

    /* ER3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33;

    /* ER4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x44;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x44;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x44;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x44;

    /* ER5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x55;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x55;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x55;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x55;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య * pxCurrentTCB;

    /* Setup the hardware to generate the tick. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Restore the context of the first task that is going to run.  This
     * mirrors the function epilogue code generated by the compiler when the
     * "saveall" function attribute is used. */
    asm అస్థిర (
        "MOV.L      @_pxCurrentTCB, ER6         \n\t"
        "MOV.L      @ER6, ER7                   \n\t"
        "LDM.L      @SP+, (ER4-ER5)             \n\t"
        "LDM.L      @SP+, (ER0-ER3)             \n\t"
        "MOV.L      @ER7+, ER6                  \n\t"
        "RTE                                    \n\t"
        );

    ( శూన్య ) pxCurrentTCB;

    /* Should not get here. */
    తిరిగి pdTRUE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the h8 port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is a trap handler.  The "saveall" function
 * attribute is used so the context is saved by the compiler prologue.  All
 * we have to do is save the stack pointer.
 */
శూన్య v_పోర్టు_Yield( శూన్య )
{
    పోర్టు_SAVE_దొంతర_సూచిక();
    vTaskSwitchContext();
    పోర్టు_RESTORE_దొంతర_సూచిక();
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler installed for the RTOS tick depends on whether the
 * preemptive or cooperative scheduler is being used.
 */
#ఒకవేళ ( configUSE_PREEMPTION == 1 )

/*
 * The preemptive scheduler is used so the ISR calls vTaskSwitchContext().
 * The function prologue saves the context so all we have to do is save
 * the stack pointer.
 */
    శూన్య vTickISR( శూన్య ) __attribute__( ( saveall, అంతరాయం_handler ) );
    శూన్య vTickISR( శూన్య )
    {
        పోర్టు_SAVE_దొంతర_సూచిక();

        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Clear the interrupt. */
        TSR1 &= ~0x01;

        పోర్టు_RESTORE_దొంతర_సూచిక();
    }

#లేకపోతే /* if ( configUSE_PREEMPTION == 1 ) */

/*
 * The cooperative scheduler is being used so all we have to do is
 * periodically increment the tick.  This can just be a normal ISR and
 * the "saveall" attribute is not required.
 */
    శూన్య vTickISR( శూన్య ) __attribute__( ( అంతరాయం_handler ) );
    శూన్య vTickISR( శూన్య )
    {
        xTaskIncrementTick();

        /* Clear the interrupt. */
        TSR1 &= ~0x01;
    }

#అయితే_ముగింపు /* if ( configUSE_PREEMPTION == 1 ) */
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match to generate a tick interrupt.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    స్థిరరాశి uint32_t ul_Compare_సరిపోలిక = ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ ) / పోర్టు_CLOCK_DIV;

    /* Turn the module on. */
    MSTPCR &= ~పోర్టు_MSTP13;

    /* Configure timer 1. */
    TCR1 = పోర్టు_CLEAR_ON_TGRA_COMPARE_సరిపోలిక | పోర్టు_CLOCK_DIV_64;

    /* Configure the compare match value for a tick of configTICK_RATE_HZ. */
    TGR1A = ul_Compare_సరిపోలిక;

    /* Start the timer and enable the interrupt - we can do this here as
     * interrupts are globally disabled when this function is called. */
    TIER1 |= పోర్టు_TGRA_అంతరాయం_ENABLE;
    TSTR |= పోర్టు_TIMER_CHANNEL;
}
/*-----------------------------------------------------------*/
