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
* Implementation of functions defined in portable.h for the PPC405 port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Library includes. */
#అన్తర్భావ "xtime_l.h"
#అన్తర్భావ "xintc.h"
#అన్తర్భావ "xintc_i.h"

/*-----------------------------------------------------------*/

/* Definitions to set the initial MSR of each task. */
#నిర్వచించు పోర్టు_CRITICAL_అంతరాయం_ENABLE    ( 1UL << 17UL )
#నిర్వచించు పోర్టు_EXTERNAL_అంతరాయం_ENABLE    ( 1UL << 15UL )
#నిర్వచించు పోర్టు_MACHINE_CHECK_ENABLE         ( 1UL << 12UL )

#ఒకవేళ configUSE_FPU == 1
    #నిర్వచించు పోర్టు_APU_PRESENT              ( 1UL << 25UL )
    #నిర్వచించు పోర్టు_FCM_FPU_PRESENT          ( 1UL << 13UL )
#లేకపోతే
    #నిర్వచించు పోర్టు_APU_PRESENT              ( 0UL )
    #నిర్వచించు పోర్టు_FCM_FPU_PRESENT          ( 0UL )
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_INITIAL_MSR                  ( పోర్టు_CRITICAL_అంతరాయం_ENABLE | పోర్టు_EXTERNAL_అంతరాయం_ENABLE | పోర్టు_MACHINE_CHECK_ENABLE | పోర్టు_APU_PRESENT | పోర్టు_FCM_FPU_PRESENT )


బాహ్య స్థిరరాశి గుర్తులేని SDA_పునాది;
బాహ్య స్థిరరాశి గుర్తులేని SDA2_పునాది;

/*-----------------------------------------------------------*/

/*
 * Setup the system timer to generate the tick interrupt.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * The handler for the tick interrupt - defined in portasm.s.
 */
బాహ్య శూన్య v_పోర్టు_Tick_ISR( శూన్య );

/*
 * The handler for the yield function - defined in portasm.s.
 */
బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*-----------------------------------------------------------*/

/* Structure used to hold the state of the interrupt controller. */
స్థిర XIntc x_అంతరాయం_Controller;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 *
 * See the header file portable.h.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Place a known value at the bottom of the stack for debugging. */
    *px_శిఖరం_యొక్క_దొంతర = 0xDEADBEEF;
    px_శిఖరం_యొక్క_దొంతర--;

    /* EABI stack frame. */
    px_శిఖరం_యొక్క_దొంతర -= 20; /* Previous backchain and LR, R31 to R4 inclusive. */

    /* Parameters in R13. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) &SDA_పునాది; /* address of the first small data area */
    px_శిఖరం_యొక్క_దొంతర -= 10;

    /* Parameters in R3. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Parameters in R2. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) &SDA2_పునాది; /* address of the second small data area */
    px_శిఖరం_యొక్క_దొంతర--;

    /* R1 is the stack pointer so is omitted. */

    *px_శిఖరం_యొక్క_దొంతర = 0x10000001UL;                      /* R0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00000000UL;                      /* USPRG0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00000000UL;                      /* CR. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00000000UL;                      /* XER. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00000000UL;                      /* CTR. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) v_పోర్టు_చివర_Scheduler; /* LR. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;            /* SRR0. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_MSR;                   /* SRR1. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) v_పోర్టు_చివర_Scheduler; /* Next LR. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00000000UL;                      /* Backchain. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    prv_అమరిక_Timer_అంతరాయం();
    XExc_రిజిస్టరు_Handler( XEXC_ID_SYSTEM_CALL, ( XExceptionHandler ) v_పోర్టు_Yield, ( శూన్య * ) 0 );
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here as the tasks are now running! */
    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented. */
    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    స్థిరరాశి uint32_t ulInterval = ( ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL );

    XTime_PITClear_అంతరాయం();
    XTime_FITClear_అంతరాయం();
    XTime_WDTClear_అంతరాయం();
    XTime_WDTDisable_అంతరాయం();
    XTime_FITDisable_అంతరాయం();

    XExc_రిజిస్టరు_Handler( XEXC_ID_PIT_INT, ( XExceptionHandler ) v_పోర్టు_Tick_ISR, ( శూన్య * ) 0 );

    XTime_PITEnableAutoReload();
    XTime_PITSetInterval( ulInterval );
    XTime_PITEnable_అంతరాయం();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_ISRHandler( శూన్య * pvNullDoNotUse )
{
    uint32_t ul_అంతరాయం_స్థితి, ul_అంతరాయం_ముసుగు = 1UL;
    పునాది_Type_t x_అంతరాయం_సంఖ్య;
    XIntc_Config * px_అంతరాయం_Controller;
    XIntc_సదిశ_పట్టిక_నమోదు * px_పట్టిక;

    /* Just to remove compiler warning. */
    ( శూన్య ) pvNullDoNotUse;

    /* Get the configuration by using the device ID - in this case it is
     * assumed that only one interrupt controller is being used. */
    px_అంతరాయం_Controller = &XIntc_Config_పట్టిక[ XPAR_XPS_INTC_0_DEVICE_ID ];

    /* Which interrupts are pending? */
    ul_అంతరాయం_స్థితి = XIntc_m_Get_Intr_స్థితి( px_అంతరాయం_Controller->పునాది_చిరునామా );

    కొరకు( x_అంతరాయం_సంఖ్య = 0; x_అంతరాయం_సంఖ్య < XPAR_INTC_MAX_అంకె_INTR_INPUTS; x_అంతరాయం_సంఖ్య++ )
    {
        ఒకవేళ( ul_అంతరాయం_స్థితి & 0x01UL )
        {
            /* Clear the pending interrupt. */
            XIntc_mAckIntr( px_అంతరాయం_Controller->పునాది_చిరునామా, ul_అంతరాయం_ముసుగు );

            /* Call the registered handler. */
            px_పట్టిక = &( px_అంతరాయం_Controller->Handler_పట్టిక[ x_అంతరాయం_సంఖ్య ] );
            px_పట్టిక->Handler( px_పట్టిక->Call_వెనుక_Ref );
        }

        /* Check the next interrupt. */
        ul_అంతరాయం_ముసుగు <<= 0x01UL;
        ul_అంతరాయం_స్థితి >>= 0x01UL;

        /* Have we serviced all interrupts? */
        ఒకవేళ( ul_అంతరాయం_స్థితి == 0UL )
        {
            ఆపు;
        }
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_అమరిక_అంతరాయం_Controller( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_ISRWrapper( శూన్య );

    /* Perform all library calls necessary to initialise the exception table
     * and interrupt controller.  This assumes only one interrupt controller is in
     * use. */
    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
    XExc_Init();

    /* The library functions save the context - we then jump to a wrapper to
     * save the stack into the TCB.  The wrapper then calls the handler defined
     * above. */
    XExc_రిజిస్టరు_Handler( XEXC_ID_NON_CRITICAL_INT, ( XExceptionHandler ) v_పోర్టు_ISRWrapper, ఖాళీ );
    XIntc_Initialize( &x_అంతరాయం_Controller, XPAR_XPS_INTC_0_DEVICE_ID );
    XIntc_ప్రారంభం( &x_అంతరాయం_Controller, XIN_REAL_బహుళకం );
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_Install_అంతరాయం_Handler( uint8_t uc_అంతరాయం_ID,
                                         XInterruptHandler pxHandler,
                                         శూన్య * pv_Call_వెనుక_Ref )
{
    పునాది_Type_t xReturn = pdFAIL;

    /* This function is defined here so the scope of xInterruptController can
     * remain within this file. */

    ఒకవేళ( XST_SUCCESS == XIntc_Connect( &x_అంతరాయం_Controller, uc_అంతరాయం_ID, pxHandler, pv_Call_వెనుక_Ref ) )
    {
        XIntc_Enable( &x_అంతరాయం_Controller, uc_అంతరాయం_ID );
        xReturn = pdPASS;
    }

    తిరిగి xReturn;
}
