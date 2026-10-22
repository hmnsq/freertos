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
* Implementation of functions defined in portable.h for the MicroBlaze port.
*----------------------------------------------------------*/


/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Standard includes. */
#అన్తర్భావ <string.h>

/* Hardware includes. */
#అన్తర్భావ <xintc.h>
#అన్తర్భావ <xintc_i.h>
#అన్తర్భావ <xtmrctr.h>

#ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 0 )
    #దోషం config_SUPPORT_DYNAMIC_కేటాయింపు must be సమితి గమ్యం 1 గమ్యం use this పోర్టు.
#అయితే_ముగింపు

/* Tasks are started with interrupts enabled. */
#నిర్వచించు పోర్టు_INITIAL_MSR_STATE        ( ( దొంతర_Type_t ) 0x02 )

/* Tasks are started with a critical section nesting of 0 - however prior
 * to the scheduler being commenced we don't want the critical nesting level
 * to reach zero, so it is initialised to a high value. */
#నిర్వచించు పోర్టు_INITIAL_NESTING_విలువ    ( 0xff )

/* Our hardware setup only uses one counter. */
#నిర్వచించు పోర్టు_COUNTER_0                0

/* The stack used by the ISR is filled with a known value to assist in
 * debugging. */
#నిర్వచించు పోర్టు_ISR_దొంతర_FILL_విలువ     0x55555555

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
అస్థిర UBaseType_t uxCriticalNesting = పోర్టు_INITIAL_NESTING_విలువ;

/* To limit the amount of stack required by each task, this port uses a
 * separate stack for interrupts. */
uint32_t * pulISRStack;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the header file portable.h.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    బాహ్య శూన్య * SDA2_పునాది;
    బాహ్య శూన్య * SDA_పునాది;
    స్థిరరాశి uint32_t ulR2 = ( uint32_t ) &SDA2_పునాది;
    స్థిరరాశి uint32_t ulR13 = ( uint32_t ) &SDA_పునాది;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted.  The parameter value will overwrite the
     * 0x22222222 value during the function prologue. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x22222222;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x33333333;
    px_శిఖరం_యొక్క_దొంతర--;

    /* First stack an initial value for the critical section nesting.  This
     *  is initialised to zero as tasks are started with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00; /* R0. */

    /* Place an initial value for all the general purpose registers. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ulR2;         /* R2 - small data area. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03;         /* R3. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04;         /* R4. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R5 contains the function call parameters. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06;         /* R6. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07;         /* R7. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08;         /* R8. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09;         /* R9. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0a;         /* R10. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0b;         /* R11. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0c;         /* R12. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ulR13;        /* R13 - small data read write area. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;       /* R14. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0f;         /* R15. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10;         /* R16. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11;         /* R17. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12;         /* R18. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x13;         /* R19. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x14;         /* R20. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x15;         /* R21. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x16;         /* R22. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x17;         /* R23. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x18;         /* R24. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x19;         /* R25. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1a;         /* R26. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1b;         /* R27. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1c;         /* R28. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1d;         /* R29. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1e;         /* R30. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* The MSR is stacked between R30 and R31. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_MSR_STATE;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1f; /* R31. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య( __FreeRTOS_interrupt_Handler )( శూన్య );
    బాహ్య శూన్య( v_ప్రారంభం_మొదటి_Task )( శూన్య );


    /* Setup the FreeRTOS interrupt handler.  Code copied from crt0.s. */
    asm అస్థిర ( "la r6, r0, __FreeRTOS_interrupt_handler        \n\t" \
                   "sw r6, r1, r0                                  \n\t" \
                   "lhu r7, r1, r0                                 \n\t" \
                   "shi r7, r0, 0x12                               \n\t" \
                   "shi r6, r0, 0x16 " );

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Allocate the stack to be used by the interrupt handler. */
    pulISRStack = ( uint32_t * ) pv_పోర్టు_Malloc( config_కనీస_దొంతర_కొలత * పరిమాణం( దొంతర_Type_t ) );

    /* Restore the context of the first task that is going to run. */
    ఒకవేళ( pulISRStack != ఖాళీ )
    {
        /* Fill the ISR stack with a known value to facilitate debugging. */
        memset( pulISRStack, పోర్టు_ISR_దొంతర_FILL_విలువ, config_కనీస_దొంతర_కొలత * పరిమాణం( దొంతర_Type_t ) );
        pulISRStack += ( config_కనీస_దొంతర_కొలత - 1 );

        /* Kick off the first task. */
        v_ప్రారంభం_మొదటి_Task();
    }

    /* Should not get here as the tasks are now running! */
    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
శూన్య v_పోర్టు_Yield( శూన్య )
{
    బాహ్య శూన్య VPortYieldASM( శూన్య );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    పోర్టు_ENTER_CRITICAL();

    /* Jump directly to the yield function to ensure there is no
     * compiler generated prologue code. */
    asm అస్థిర ( "bralid r14, VPortYieldASM      \n\t" \
                   "or r0, r0, r0                  \n\t" );
    పోర్టు_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    XTmrCtr xTimer;
    స్థిరరాశి uint32_t ul_Counter_విలువ = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ;
    UBaseType_t ux_ముసుగు;

    /* The OPB timer1 is used to generate the tick.  Use the provided library
     * functions to enable the timer and set the tick frequency. */
    XTmrCtr_mDisable( XPAR_OPB_TIMER_1_BASEADDR, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmrCtr_Initialize( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_సమితి_ఎక్కించు_Reg( XPAR_OPB_TIMER_1_BASEADDR, పోర్టు_COUNTER_0, ul_Counter_విలువ );
    XTmr_Ctr_m_సమితి_Control_స్థితి_Reg( XPAR_OPB_TIMER_1_BASEADDR, పోర్టు_COUNTER_0, XTC_CSR_ఎక్కించు_ముసుగు | XTC_CSR_INT_occurred_ముసుగు );

    /* Set the timer interrupt enable bit while maintaining the other bit
     * states. */
    ux_ముసుగు = XIntc_In32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_స్థానభ్రంశం ) );
    ux_ముసుగు |= XPAR_OPB_TIMER_1_అంతరాయం_ముసుగు;
    XIntc_Out32( ( XPAR_OPB_INTC_0_BASEADDR + XIN_IER_స్థానభ్రంశం ), ( ux_ముసుగు ) );

    XTmr_Ctr_ప్రారంభం( &xTimer, XPAR_OPB_TIMER_1_DEVICE_ID );
    XTmr_Ctr_m_సమితి_Control_స్థితి_Reg( XPAR_OPB_TIMER_1_BASEADDR, పోర్టు_COUNTER_0, XTC_CSR_ENABLE_TMR_ముసుగు | XTC_CSR_ENABLE_INT_ముసుగు | XTC_CSR_AUTO_RELOAD_ముసుగు | XTC_CSR_కిందికి_లెక్క_ముసుగు | XTC_CSR_INT_occurred_ముసుగు );
    XIntc_mAckIntr( XPAR_INTC_SINGLE_BASEADDR, 1 );
}
/*-----------------------------------------------------------*/

/*
 * The interrupt handler placed in the interrupt vector when the scheduler is
 * started.  The task context has already been saved when this is called.
 * This handler determines the interrupt source and calls the relevant
 * peripheral handler.
 */
శూన్య vTaskISRHandler( శూన్య )
{
    స్థిర uint32_t ulPending;

    /* Which interrupts are pending? */
    ulPending = XIntc_In32( ( XPAR_INTC_SINGLE_BASEADDR + XIN_IVR_స్థానభ్రంశం ) );

    ఒకవేళ( ulPending < XPAR_INTC_MAX_అంకె_INTR_INPUTS )
    {
        స్థిర XIntc_సదిశ_పట్టిక_నమోదు * px_పట్టిక_Ptr;
        స్థిర XIntc_Config * pxConfig;
        స్థిర uint32_t ul_అంతరాయం_ముసుగు;

        ul_అంతరాయం_ముసుగు = ( uint32_t ) 1 << ulPending;

        /* Get the configuration data using the device ID */
        pxConfig = &XIntc_Config_పట్టిక[ ( uint32_t ) XPAR_INTC_SINGLE_DEVICE_ID ];

        px_పట్టిక_Ptr = &( pxConfig->Handler_పట్టిక[ ulPending ] );

        ఒకవేళ( pxConfig->AckBeforeService & ( ul_అంతరాయం_ముసుగు ) )
        {
            XIntc_mAckIntr( pxConfig->పునాది_చిరునామా, ul_అంతరాయం_ముసుగు );
            px_పట్టిక_Ptr->Handler( px_పట్టిక_Ptr->Call_వెనుక_Ref );
        }
        లేకపోతే
        {
            px_పట్టిక_Ptr->Handler( px_పట్టిక_Ptr->Call_వెనుక_Ref );
            XIntc_mAckIntr( pxConfig->పునాది_చిరునామా, ul_అంతరాయం_ముసుగు );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.
 */
శూన్య vTickISR( శూన్య * pv_పునాది_చిరునామా )
{
    uint32_t ulCSR;

    /* Increment the RTOS tick - this might cause a task to unblock. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the timer interrupt */
    ulCSR = XTmr_Ctr_m_Get_Control_స్థితి_Reg( XPAR_OPB_TIMER_1_BASEADDR, 0 );
    XTmr_Ctr_m_సమితి_Control_స్థితి_Reg( XPAR_OPB_TIMER_1_BASEADDR, పోర్టు_COUNTER_0, ulCSR );
}
/*-----------------------------------------------------------*/
