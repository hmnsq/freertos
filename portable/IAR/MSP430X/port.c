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

/* Hardware includes. */
#అన్తర్భావ "msp430.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the MSP430X port.
*----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
 * not the MCLK. */
#నిర్వచించు పోర్టు_ACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#నిర్వచించు పోర్టు_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#నిర్వచించు పోర్టు_FLAGS_INT_ENABLED           ( ( దొంతర_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
రకనిర్వచనం శూన్య TCB_t;
బాహ్య అస్థిర TCB_t * అస్థిర pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
 * time a critical section is entered the count is incremented.  Each time a
 * critical section is exited the count is decremented - with interrupts only
 * being re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as this will cause problems during the startup
 * sequence. */
అస్థిర uint16_t usCriticalNesting = పోర్టు_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    uint16_t * pus_శిఖరం_యొక్క_దొంతర;
    uint32_t * pul_శిఖరం_యొక్క_దొంతర;

    /*
     *  Place a few bytes of known values on the bottom of the stack.
     *  This is just useful for debugging and can be included if required.
     *
     * pxTopOfStack = ( StackType_t ) 0x1111;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x2222;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x3333;
     */

    /* StackType_t is either 16 bits or 32 bits depending on the data model.
     * Some stacked items do not change size depending on the data model so have
     * to be explicitly cast to the correct size so this function will work
     * whichever data model is being used. */
    ఒకవేళ( పరిమాణం( దొంతర_Type_t ) == పరిమాణం( uint16_t ) )
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_శిఖరం_యొక్క_దొంతర = ( uint16_t * ) px_శిఖరం_యొక్క_దొంతర;
        pus_శిఖరం_యొక్క_దొంతర--;
        pul_శిఖరం_యొక్క_దొంతర = ( uint32_t * ) pus_శిఖరం_యొక్క_దొంతర;
    }
    లేకపోతే
    {
        pul_శిఖరం_యొక్క_దొంతర = ( uint32_t * ) px_శిఖరం_యొక్క_దొంతర;
    }

    *pul_శిఖరం_యొక్క_దొంతర = ( uint32_t ) px_సంకేతం;

    pus_శిఖరం_యొక్క_దొంతర = ( uint16_t * ) pul_శిఖరం_యొక్క_దొంతర;
    pus_శిఖరం_యొక్క_దొంతర--;
    *pus_శిఖరం_యొక్క_దొంతర = పోర్టు_FLAGS_INT_ENABLED;
    pus_శిఖరం_యొక్క_దొంతర -= ( పరిమాణం( దొంతర_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t * ) pus_శిఖరం_యొక్క_దొంతర;

    /* Next the general purpose registers. */
    #నిర్వచితమైతే PRELOAD_రిజిస్టరు_విలువలు
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xffff;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xeeee;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xdddd;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xbbbb;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xaaaa;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x9999;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x8888;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x5555;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x6666;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x5555;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x4444;
        px_శిఖరం_యొక్క_దొంతర--;
    #లేకపోతే /* ifdef PRELOAD_REGISTER_VALUES */
        px_శిఖరం_యొక్క_దొంతర -= 3;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
        px_శిఖరం_యొక్క_దొంతర -= 9;
    #అయితే_ముగింపు /* ifdef PRELOAD_REGISTER_VALUES */


    /* A variable is used to keep track of the critical section nesting.
     * This variable has to be stored as part of the task context and is
     * initially set to zero. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య )
{
    v_Application_అమరిక_Timer_అంతరాయం();
}
/*-----------------------------------------------------------*/

#సూచన సదిశ=config_TICK_సదిశ
__interrupt __raw శూన్య vTickISREntry( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_Tick_ISR( శూన్య );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    v_పోర్టు_Tick_ISR();
}
