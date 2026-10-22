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

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_సంఖ్య_యొక్క_CORES == 1 ) )
    #దోషం INCLUDE_xTaskGetCurrentTaskHandle must be సమితి గమ్యం 1 లోపల single core.
#అయితే_ముగింపు

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#నిర్వచించు పోర్టు_PSW_రిజిస్టరు_ID          ( 5 )
#నిర్వచించు పోర్టు_FPSR_రిజిస్టరు_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#నిర్వచించు పోర్టు_INITIAL_PSW_ముసుగు         ( 0x000f8000 )
#నిర్వచించు పోర్టు_CURRENT_PSW_విలువ        ( పోర్టు_STSR( పోర్టు_PSW_రిజిస్టరు_ID ) )
#నిర్వచించు పోర్టు_CURRENT_SR_ZERO_విలువ    ( ( దొంతర_Type_t ) 0x00000000 )
#నిర్వచించు పోర్టు_CURRENT_FPSR_విలువ       ( పోర్టు_STSR( పోర్టు_FPSR_రిజిస్టరు_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#నిర్వచించు పోర్టు_INITIAL_FPSR_ముసుగు        ( 0x00ae0000 )
#నిర్వచించు పోర్టు_PSW_ID_ముసుగు              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#నిర్వచించు పోర్టు_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#నిర్వచించు పోర్టు_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#నిర్వచించు పోర్టు_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#నిర్వచించు పోర్టు_OSTM0_TS_ADDR             ( 0xFFD70014 )

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #నిర్వచితమైతే configIPIR_CHANNEL
        #నిర్వచించు పోర్టు_IPIR_పునాది_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #లేకపోతే
        #నిర్వచించు పోర్టు_IPIR_పునాది_ADDR    ( 0xFFFEEC80 )
    #అయితే_ముగింపు

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #నిర్వచితమైతే config_EXCLUSIVE_చిరునామా
        #నిర్వచించు పోర్టు_MEV_పునాది_ADDR    config_EXCLUSIVE_చిరునామా
    #లేకపోతే
        #నిర్వచించు పోర్టు_MEV_పునాది_ADDR    ( 0xFFFEEC00 )
    #అయితే_ముగింపు
#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R1     ( ( దొంతర_Type_t ) 0x01010101 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R2     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x02 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R3     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x03 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R4     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x04 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R5     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x05 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R6     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x06 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R7     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x07 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R8     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x08 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R9     ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x09 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R10    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x10 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R11    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x11 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R12    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x12 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R13    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x13 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R14    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x14 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R15    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x15 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R16    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x16 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R17    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x17 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R18    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x18 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R19    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x19 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R20    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x20 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R21    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x21 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R22    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x22 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R23    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x23 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R24    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x24 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R25    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x25 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R26    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x26 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R27    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x27 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R28    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x28 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R29    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x29 )
#నిర్వచించు పోర్టు_దొంతర_INITIAL_విలువ_R30    ( ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#నిర్వచించు పోర్టు_OSTM_COUNTER_ప్రారంభం              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#నిర్వచించు పోర్టు_OSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#నిర్వచించు పోర్టు_OSTM_బహుళకం_INTERVAL_TIMER        ( 0x00U )
#నిర్వచించు పోర్టు_OSTM_బహుళకం_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#నిర్వచించు పోర్టు_OSTM_ప్రారంభం_అంతరాయం_DISABLE    ( 0x00U )
#నిర్వచించు పోర్టు_OSTM_ప్రారంభం_అంతరాయం_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#నిర్వచించు పోర్టు_INT_ప్రత్యక్ష_సదిశ               ( 0x0U )
#నిర్వచించు పోర్టు_INT_పట్టిక_సదిశ                ( 0x1U )

/* Interrupt mask (MKxxx) */
#నిర్వచించు పోర్టు_INT_PROCESSING_ENABLED          ( 0x0U )
#నిర్వచించు పోర్టు_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL1             ( 0x0001U ) /* Level 1 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL2             ( 0x0002U ) /* Level 2 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL3             ( 0x0003U ) /* Level 3 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL4             ( 0x0004U ) /* Level 4 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL5             ( 0x0005U ) /* Level 5 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL6             ( 0x0006U ) /* Level 6 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL7             ( 0x0007U ) /* Level 7 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL8             ( 0x0008U ) /* Level 8 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL9             ( 0x0009U ) /* Level 9 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL10            ( 0x000AU ) /* Level 10 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL11            ( 0x000BU ) /* Level 11 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL12            ( 0x000CU ) /* Level 12 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL13            ( 0x000DU ) /* Level 13 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_LEVEL14            ( 0x000EU ) /* Level 14 */
#నిర్వచించు పోర్టు_INT_ప్రాధాన్యత_అత్యల్ప             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#నిర్వచించు పోర్టు_SCHEDULER_NOREQUEST            0UL
#నిర్వచించు పోర్టు_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#నిర్వచించు పోర్టు_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #నిర్వచించు config_అమరిక_TICK_అంతరాయం()    prv_అమరిక_Timer_అంతరాయం()
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

#ఒకవేళ ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #నిర్వచించు configMAX_INT_NESTING    2UL
#అయితే_ముగింపు

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    స్థిర శూన్య prv_Exclusive_తాళం( పునాది_Type_t xFromIsr );
    స్థిర శూన్య prvExclusiveRelease( పునాది_Type_t xFromIsr );

#అయితే_ముగింపు

/*
 * Function to start the first task executing
 */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/* Scheduler request on each cores which are starting first task and switching
 * context */
అస్థిర పునాది_Type_t x_పోర్టు_కాలపట్టిక_స్థితి[ config_సంఖ్య_యొక్క_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
అస్థిర UBaseType_t ux_అంతరాయం_Nesting[ config_సంఖ్య_యొక్క_CORES ] = { 0 };
అస్థిర స్థిరరాశి UBaseType_t ux_పోర్టు_Max_అంతరాయం_లోతు = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_తాళం_Nesting[ config_సంఖ్య_యొక్క_CORES ][ 2 ] = { 0 };

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/* Pointer to exclusive access memory */
    అస్థిర పునాది_Type_t * px_పోర్టు_Exclusive_Reg = ( అస్థిర పునాది_Type_t * ) ( పోర్టు_MEV_పునాది_ADDR );
#అయితే_ముగింపు

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
శూన్య v_పోర్టు_Tick_ISR( శూన్య );

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    శూన్య v_పోర్టు_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    శూన్య v_పోర్టు_IPIHander( శూన్య );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    శూన్య v_పోర్టు_Recursive_తాళం_Acquire( పునాది_Type_t xCoreID, పునాది_Type_t xFromIsr );
    శూన్య v_పోర్టు_Recursive_తాళం_Release( పునాది_Type_t xCoreID, పునాది_Type_t xFromIsr );

#అయితే_ముగింపు /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
పోర్టు_LONG x_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య )
{
    పోర్టు_LONG ulPSWValue = పోర్టు_STSR( పోర్టు_PSW_రిజిస్టరు_ID );

    పోర్టు_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    తిరిగి ulPSWValue;
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( పోర్టు_LONG ux_Saved_అంతరాయం_స్థితి )
{
    పోర్టు_LONG ulPSWValue = పోర్టు_STSR( పోర్టు_PSW_రిజిస్టరు_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( పోర్టు_PSW_ID_ముసుగు ) );
    ulPSWValue |= ( పోర్టు_PSW_ID_ముసుగు & ux_Saved_అంతరాయం_స్థితి );
    పోర్టు_LDSR( పోర్టు_PSW_రిజిస్టరు_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
పునాది_Type_t x_పోర్టు_GET_CORE_ID( శూన్య )
{
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        తిరిగి ( పోర్టు_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #లేకపోతే

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        తిరిగి 0;
    #అయితే_ముగింపు
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
శూన్య * pv_పోర్టు_Get_Current_TCB( శూన్య )
{
    శూన్య * pvCurrentTCB = ( శూన్య * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != ఖాళీ );

    తిరిగి pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
శూన్య v_పోర్టు_సమితి_Switch( పునాది_Type_t xSwitchRequired )
{
    ఒకవేళ( xSwitchRequired != pdFALSE )
    {
        x_పోర్టు_కాలపట్టిక_స్థితి[ x_పోర్టు_GET_CORE_ID() ] = పోర్టు_SCHEDULER_TASKSWITCH;
    }
}

/*-----------------------------------------------------------*/

/*
 * Setup the stack of a new task so it is ready to be placed under the
 * scheduler control. The registers have to be placed on the stack in the
 * order that the port expects to find them.
 *
 * @param[in]  pxTopOfStack  Pointer to top of this task's stack
 * @param[in]  pxCode        Task function, stored as initial PC for the task
 * @param[in]  pvParameters  Parameters for task
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R5;  /* R5 (TP)  */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;                /* R6       */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R7;  /* R7       */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R8;  /* R8       */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R9;  /* R9       */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R10; /* R10      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R11; /* R11      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R12; /* R12      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R13; /* R13      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R14; /* R14      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R15; /* R15      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R16; /* R16      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R17; /* R17      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R18; /* R18      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R19; /* R19      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R20; /* R20      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R21; /* R21      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R22; /* R22      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R23; /* R23      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R24; /* R24      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R25; /* R25      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R26; /* R26      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R27; /* R27      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R28; /* R28      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R29; /* R29      */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R30; /* R30 (EP) */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R1;  /* R1        */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_దొంతర_INITIAL_విలువ_R2;  /* R2        */

    px_శిఖరం_యొక్క_దొంతర--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( పోర్టు_CURRENT_PSW_విలువ & పోర్టు_INITIAL_PSW_ముసుగు ); /* EIPSW */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;                                           /* EIPC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_CURRENT_SR_ZERO_విలువ;                        /* EIIC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( పోర్టు_CURRENT_PSW_విలువ & పోర్టు_INITIAL_PSW_ముసుగు ); /* CTPSW */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_CURRENT_SR_ZERO_విలువ;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #ఒకవేళ ( configENABLE_FPU == 1 )
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( పోర్టు_CURRENT_FPSR_విలువ & పోర్టు_INITIAL_FPSR_ముసుగు ); /* FPSR */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_CURRENT_SR_ZERO_విలువ;                          /* FPEPC */
    #అయితే_ముగింపు /* (configENABLE_FPU == 1) */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        పునాది_Type_t xCurrentCore = x_పోర్టు_GET_CORE_ID();
    #అయితే_ముగింపు

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    పోర్టు_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_అమరిక_TICK_అంతరాయం();

    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        /* Start scheduler on other cores */
        కొరకు( uint16_t xCoreID = 0; xCoreID < config_సంఖ్య_యొక్క_CORES; xCoreID++ )
        {
            ఒకవేళ( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_పోర్టు_కాలపట్టిక_స్థితి[ xCoreID ] = పోర్టు_SCHEDULER_STARTFIRSTTASK;
                v_పోర్టు_Yield_Core( xCoreID );
            }
            లేకపోతే
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_పోర్టు_కాలపట్టిక_స్థితి[ xCoreID ] = పోర్టు_SCHEDULER_NOREQUEST;
            }
        }
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
            xCurrentCore
        #అయితే_ముగింపు
        );

    తిరిగి pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */

    /* This statement will always fail, triggering the assert */
    configASSERT( pdFALSE );

    /*
     * The following statement may be unreachable because configASSERT(pdFALSE)
     * always triggers an assertion failure, which typically halts program
     * execution.
     * The warning may be reported to indicate to indicate that the compiler
     * detects the subsequent code will not be executed.
     * The warning is acceptable to ensure program is halt regardless of
     * configASSERT(pdFALSE) implementation
     */
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

    శూన్య v_పోర్టు_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        ఒకవేళ( xCoreID != x_పోర్టు_GET_CORE_ID() )
        {
            అస్థిర uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( అస్థిర uint32_t * ) ( పోర్టు_IPIR_పునాది_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        లేకపోతే
        {
            /* Yielding current core */
            v_పోర్టు_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    శూన్య v_పోర్టు_IPIHander( శూన్య )
    {
        పునాది_Type_t xCurrentCore = x_పోర్టు_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        ఒకవేళ( పోర్టు_SCHEDULER_STARTFIRSTTASK != x_పోర్టు_కాలపట్టిక_స్థితి[ xCurrentCore ] )
        {
            x_పోర్టు_కాలపట్టిక_స్థితి[ xCurrentCore ] = పోర్టు_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* (configNUMBER_OF_CORES > 1) */

శూన్య v_పోర్టు_Tick_ISR( శూన్య )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        పునాది_Type_t x_Saved_అంతరాయం_స్థితి;

        x_Saved_అంతరాయం_స్థితి = పోర్టు_ENTER_CRITICAL_FROM_ISR();
    #అయితే_ముగింపు
    {
        /* Increment the RTOS tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_పోర్టు_కాలపట్టిక_స్థితి[ x_పోర్టు_GET_CORE_ID() ] = పోర్టు_SCHEDULER_TASKSWITCH;
        }
    }
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
        పోర్టు_EXIT_CRITICAL_FROM_ISR( x_Saved_అంతరాయం_స్థితి );
    #అయితే_ముగింపు
}

/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    అస్థిర uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( అస్థిర uint32_t * ) పోర్టు_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( పోర్టు_INT_PROCESSING_ENABLED | పోర్టు_INT_ప్రత్యక్ష_సదిశ | పోర్టు_INT_ప్రాధాన్యత_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( అస్థిర uint32_t * ) పోర్టు_OSTM0_CTL_ADDR ) =
        ( పోర్టు_OSTM_బహుళకం_INTERVAL_TIMER | పోర్టు_OSTM_ప్రారంభం_అంతరాయం_DISABLE );
    *( ( అస్థిర uint32_t * ) పోర్టు_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_రేటు_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( అస్థిర uint32_t * ) పోర్టు_OSTM0_TS_ADDR ) = పోర్టు_OSTM_COUNTER_ప్రారంభం;
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #సూచన inline_asm prv_Exclusive_తాళం
    స్థిర శూన్య prv_Exclusive_తాళం( పునాది_Type_t x_బిట్టు_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_పోర్టు_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_తాళం_తాళం:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_తాళం_తాళం_success
        snooze
        br prv_Exclusive_తాళం_తాళం

prv_Exclusive_తాళం_తాళం_success:
    }

/*-----------------------------------------------------------*/

    #సూచన inline_asm prvExclusiveRelease
    స్థిర శూన్య prvExclusiveRelease( పునాది_Type_t x_బిట్టు_Position )
    {
        mov     # px_పోర్టు_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    శూన్య v_పోర్టు_Recursive_తాళం_Acquire( పునాది_Type_t xCoreID, పునాది_Type_t xFromIsr )
    {
        పునాది_Type_t x_Saved_అంతరాయం_స్థితి;
        పునాది_Type_t x_బిట్టు_Position = ( xFromIsr == pdTRUE );

        x_Saved_అంతరాయం_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        ఒకవేళ( ux_తాళం_Nesting[ xCoreID ][ x_బిట్టు_Position ] == 0 )
        {
            prv_Exclusive_తాళం( x_బిట్టు_Position );
        }

        ux_తాళం_Nesting[ xCoreID ][ x_బిట్టు_Position ]++;
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x_Saved_అంతరాయం_స్థితి );
    }

    శూన్య v_పోర్టు_Recursive_తాళం_Release( పునాది_Type_t xCoreID, పునాది_Type_t xFromIsr )
    {
        పునాది_Type_t x_Saved_అంతరాయం_స్థితి;
        పునాది_Type_t x_బిట్టు_Position = ( xFromIsr == pdTRUE );

        x_Saved_అంతరాయం_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        /* Sync memory */
        పోర్టు_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_తాళం_Nesting[ xCoreID ][ x_బిట్టు_Position ] > 0 ) );
        ux_తాళం_Nesting[ xCoreID ][ x_బిట్టు_Position ]--;

        ఒకవేళ( ux_తాళం_Nesting[ xCoreID ][ x_బిట్టు_Position ] == 0 )
        {
            prvExclusiveRelease( x_బిట్టు_Position );
        }

        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x_Saved_అంతరాయం_స్థితి );
    }

/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* (configNUMBER_OF_CORES > 1) */
