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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_عدد_جو_CORES == 1 ) )
    #غلطي INCLUDE_xTaskGetCurrentTaskHandle must be سيٽ منزل 1 اندريون single core.
#جيڪڏهن_پورو

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#وصف_ڪريو پورٽ_PSW_رجسٽر_ID          ( 5 )
#وصف_ڪريو پورٽ_FPSR_رجسٽر_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#وصف_ڪريو پورٽ_INITIAL_PSW_نقاب         ( 0x000f8000 )
#وصف_ڪريو پورٽ_CURRENT_PSW_قدر        ( پورٽ_STSR( پورٽ_PSW_رجسٽر_ID ) )
#وصف_ڪريو پورٽ_CURRENT_SR_ZERO_قدر    ( ( ڍير_Type_t ) 0x00000000 )
#وصف_ڪريو پورٽ_CURRENT_FPSR_قدر       ( پورٽ_STSR( پورٽ_FPSR_رجسٽر_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#وصف_ڪريو پورٽ_INITIAL_FPSR_نقاب        ( 0x00ae0000 )
#وصف_ڪريو پورٽ_PSW_ID_نقاب              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#وصف_ڪريو پورٽ_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#وصف_ڪريو پورٽ_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#وصف_ڪريو پورٽ_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#وصف_ڪريو پورٽ_OSTM0_TS_ADDR             ( 0xFFD70014 )

#إذا ( config_عدد_جو_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #جيڪڏهن_وصف_ٿيل configIPIR_CHANNEL
        #وصف_ڪريو پورٽ_IPIR_بنياد_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #وإلا
        #وصف_ڪريو پورٽ_IPIR_بنياد_ADDR    ( 0xFFFEEC80 )
    #جيڪڏهن_پورو

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #جيڪڏهن_وصف_ٿيل config_EXCLUSIVE_پتو
        #وصف_ڪريو پورٽ_MEV_بنياد_ADDR    config_EXCLUSIVE_پتو
    #وإلا
        #وصف_ڪريو پورٽ_MEV_بنياد_ADDR    ( 0xFFFEEC00 )
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R1     ( ( ڍير_Type_t ) 0x01010101 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R2     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x02 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R3     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x03 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R4     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x04 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R5     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x05 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R6     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x06 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R7     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x07 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R8     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x08 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R9     ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x09 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R10    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x10 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R11    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x11 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R12    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x12 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R13    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x13 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R14    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x14 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R15    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x15 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R16    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x16 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R17    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x17 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R18    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x18 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R19    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x19 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R20    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x20 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R21    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x21 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R22    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x22 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R23    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x23 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R24    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x24 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R25    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x25 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R26    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x26 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R27    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x27 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R28    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x28 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R29    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x29 )
#وصف_ڪريو پورٽ_ڍير_INITIAL_قدر_R30    ( ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#وصف_ڪريو پورٽ_OSTM_COUNTER_شروعات              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#وصف_ڪريو پورٽ_OSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#وصف_ڪريو پورٽ_OSTM_گهڻائي_INTERVAL_TIMER        ( 0x00U )
#وصف_ڪريو پورٽ_OSTM_گهڻائي_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#وصف_ڪريو پورٽ_OSTM_شروعات_مداخلت_DISABLE    ( 0x00U )
#وصف_ڪريو پورٽ_OSTM_شروعات_مداخلت_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#وصف_ڪريو پورٽ_INT_سڌو_ويڪٽر               ( 0x0U )
#وصف_ڪريو پورٽ_INT_جدول_ويڪٽر                ( 0x1U )

/* Interrupt mask (MKxxx) */
#وصف_ڪريو پورٽ_INT_PROCESSING_ENABLED          ( 0x0U )
#وصف_ڪريو پورٽ_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#وصف_ڪريو پورٽ_INT_ترجيح_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL1             ( 0x0001U ) /* Level 1 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL2             ( 0x0002U ) /* Level 2 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL3             ( 0x0003U ) /* Level 3 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL4             ( 0x0004U ) /* Level 4 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL5             ( 0x0005U ) /* Level 5 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL6             ( 0x0006U ) /* Level 6 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL7             ( 0x0007U ) /* Level 7 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL8             ( 0x0008U ) /* Level 8 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL9             ( 0x0009U ) /* Level 9 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL10            ( 0x000AU ) /* Level 10 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL11            ( 0x000BU ) /* Level 11 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL12            ( 0x000CU ) /* Level 12 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL13            ( 0x000DU ) /* Level 13 */
#وصف_ڪريو پورٽ_INT_ترجيح_LEVEL14            ( 0x000EU ) /* Level 14 */
#وصف_ڪريو پورٽ_INT_ترجيح_سڀ_کان_هيٺ             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#وصف_ڪريو پورٽ_SCHEDULER_NOREQUEST            0UL
#وصف_ڪريو پورٽ_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#وصف_ڪريو پورٽ_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#جيڪڏهن_وصف_نه_ٿيل config_تياري_TICK_مداخلت

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #وصف_ڪريو config_تياري_TICK_مداخلت()    prv_تياري_Timer_مداخلت()
#جيڪڏهن_پورو /* configSETUP_TICK_INTERRUPT */

#إذا ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #وصف_ڪريو configMAX_INT_NESTING    2UL
#جيڪڏهن_پورو

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

#إذا ( config_عدد_جو_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ساكن فراغ prv_Exclusive_تالو( بنياد_Type_t xFromIsr );
    ساكن فراغ prvExclusiveRelease( بنياد_Type_t xFromIsr );

#جيڪڏهن_پورو

/*
 * Function to start the first task executing
 */
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

/* Scheduler request on each cores which are starting first task and switching
 * context */
متطاير بنياد_Type_t x_پورٽ_وقت_جدول_حالت[ config_عدد_جو_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
متطاير UBaseType_t ux_مداخلت_Nesting[ config_عدد_جو_CORES ] = { 0 };
متطاير ثابت UBaseType_t ux_پورٽ_Max_مداخلت_اونهائي = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_تالو_Nesting[ config_عدد_جو_CORES ][ 2 ] = { 0 };

#إذا ( config_عدد_جو_CORES > 1 )

/* Pointer to exclusive access memory */
    متطاير بنياد_Type_t * px_پورٽ_Exclusive_Reg = ( متطاير بنياد_Type_t * ) ( پورٽ_MEV_بنياد_ADDR );
#جيڪڏهن_پورو

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
فراغ v_پورٽ_Tick_ISR( فراغ );

#إذا ( config_عدد_جو_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    فراغ v_پورٽ_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    فراغ v_پورٽ_IPIHander( فراغ );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    فراغ v_پورٽ_Recursive_تالو_Acquire( بنياد_Type_t xCoreID, بنياد_Type_t xFromIsr );
    فراغ v_پورٽ_Recursive_تالو_Release( بنياد_Type_t xCoreID, بنياد_Type_t xFromIsr );

#جيڪڏهن_پورو /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
پورٽ_LONG x_پورٽ_سيٽ_مداخلت_نقاب( فراغ )
{
    پورٽ_LONG ulPSWValue = پورٽ_STSR( پورٽ_PSW_رجسٽر_ID );

    پورٽ_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    أرجع ulPSWValue;
}

/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب( پورٽ_LONG ux_Saved_مداخلت_حالت )
{
    پورٽ_LONG ulPSWValue = پورٽ_STSR( پورٽ_PSW_رجسٽر_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( پورٽ_PSW_ID_نقاب ) );
    ulPSWValue |= ( پورٽ_PSW_ID_نقاب & ux_Saved_مداخلت_حالت );
    پورٽ_LDSR( پورٽ_PSW_رجسٽر_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
بنياد_Type_t x_پورٽ_GET_CORE_ID( فراغ )
{
    #إذا ( config_عدد_جو_CORES > 1 )
        أرجع ( پورٽ_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #وإلا

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        أرجع 0;
    #جيڪڏهن_پورو
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
فراغ * pv_پورٽ_Get_Current_TCB( فراغ )
{
    فراغ * pvCurrentTCB = ( فراغ * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != عدم );

    أرجع pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
فراغ v_پورٽ_سيٽ_Switch( بنياد_Type_t xSwitchRequired )
{
    إذا( xSwitchRequired != pdFALSE )
    {
        x_پورٽ_وقت_جدول_حالت[ x_پورٽ_GET_CORE_ID() ] = پورٽ_SCHEDULER_TASKSWITCH;
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
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R5;  /* R5 (TP)  */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;                /* R6       */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R7;  /* R7       */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R8;  /* R8       */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R9;  /* R9       */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R10; /* R10      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R11; /* R11      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R12; /* R12      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R13; /* R13      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R14; /* R14      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R15; /* R15      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R16; /* R16      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R17; /* R17      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R18; /* R18      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R19; /* R19      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R20; /* R20      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R21; /* R21      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R22; /* R22      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R23; /* R23      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R24; /* R24      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R25; /* R25      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R26; /* R26      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R27; /* R27      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R28; /* R28      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R29; /* R29      */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R30; /* R30 (EP) */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R1;  /* R1        */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_ڍير_INITIAL_قدر_R2;  /* R2        */

    px_چوٽي_جو_ڍير--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( پورٽ_CURRENT_PSW_قدر & پورٽ_INITIAL_PSW_نقاب ); /* EIPSW */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;                                           /* EIPC */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_CURRENT_SR_ZERO_قدر;                        /* EIIC */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( پورٽ_CURRENT_PSW_قدر & پورٽ_INITIAL_PSW_نقاب ); /* CTPSW */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_CURRENT_SR_ZERO_قدر;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #إذا ( configENABLE_FPU == 1 )
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( پورٽ_CURRENT_FPSR_قدر & پورٽ_INITIAL_FPSR_نقاب ); /* FPSR */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_CURRENT_SR_ZERO_قدر;                          /* FPEPC */
    #جيڪڏهن_پورو /* (configENABLE_FPU == 1) */

    أرجع px_چوٽي_جو_ڍير;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    #إذا ( config_عدد_جو_CORES > 1 )
        بنياد_Type_t xCurrentCore = x_پورٽ_GET_CORE_ID();
    #جيڪڏهن_پورو

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    پورٽ_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_تياري_TICK_مداخلت();

    #إذا ( config_عدد_جو_CORES > 1 )
        /* Start scheduler on other cores */
        لكل( uint16_t xCoreID = 0; xCoreID < config_عدد_جو_CORES; xCoreID++ )
        {
            إذا( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_پورٽ_وقت_جدول_حالت[ xCoreID ] = پورٽ_SCHEDULER_STARTFIRSTTASK;
                v_پورٽ_Yield_Core( xCoreID );
            }
            وإلا
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_پورٽ_وقت_جدول_حالت[ xCoreID ] = پورٽ_SCHEDULER_NOREQUEST;
            }
        }
    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_پورٽ_شروعات_پهريون_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #إذا ( config_عدد_جو_CORES > 1 )
            xCurrentCore
        #جيڪڏهن_پورو
        );

    أرجع pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ )
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
    پورٽ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#إذا ( config_عدد_جو_CORES > 1 )

    فراغ v_پورٽ_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        إذا( xCoreID != x_پورٽ_GET_CORE_ID() )
        {
            متطاير uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( متطاير uint32_t * ) ( پورٽ_IPIR_بنياد_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        وإلا
        {
            /* Yielding current core */
            v_پورٽ_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    فراغ v_پورٽ_IPIHander( فراغ )
    {
        بنياد_Type_t xCurrentCore = x_پورٽ_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        إذا( پورٽ_SCHEDULER_STARTFIRSTTASK != x_پورٽ_وقت_جدول_حالت[ xCurrentCore ] )
        {
            x_پورٽ_وقت_جدول_حالت[ xCurrentCore ] = پورٽ_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* (configNUMBER_OF_CORES > 1) */

فراغ v_پورٽ_Tick_ISR( فراغ )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #إذا ( config_عدد_جو_CORES > 1 )
        بنياد_Type_t x_Saved_مداخلت_حالت;

        x_Saved_مداخلت_حالت = پورٽ_ENTER_CRITICAL_FROM_ISR();
    #جيڪڏهن_پورو
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_پورٽ_وقت_جدول_حالت[ x_پورٽ_GET_CORE_ID() ] = پورٽ_SCHEDULER_TASKSWITCH;
        }
    }
    #إذا ( config_عدد_جو_CORES > 1 )
        پورٽ_EXIT_CRITICAL_FROM_ISR( x_Saved_مداخلت_حالت );
    #جيڪڏهن_پورو
}

/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    متطاير uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( متطاير uint32_t * ) پورٽ_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( پورٽ_INT_PROCESSING_ENABLED | پورٽ_INT_سڌو_ويڪٽر | پورٽ_INT_ترجيح_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( متطاير uint32_t * ) پورٽ_OSTM0_CTL_ADDR ) =
        ( پورٽ_OSTM_گهڻائي_INTERVAL_TIMER | پورٽ_OSTM_شروعات_مداخلت_DISABLE );
    *( ( متطاير uint32_t * ) پورٽ_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_شرح_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( متطاير uint32_t * ) پورٽ_OSTM0_TS_ADDR ) = پورٽ_OSTM_COUNTER_شروعات;
}

/*-----------------------------------------------------------*/

#إذا ( config_عدد_جو_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #هدايت inline_asm prv_Exclusive_تالو
    ساكن فراغ prv_Exclusive_تالو( بنياد_Type_t x_ٻٽو_انگ_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_پورٽ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_تالو_تالو:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_تالو_تالو_success
        snooze
        br prv_Exclusive_تالو_تالو

prv_Exclusive_تالو_تالو_success:
    }

/*-----------------------------------------------------------*/

    #هدايت inline_asm prvExclusiveRelease
    ساكن فراغ prvExclusiveRelease( بنياد_Type_t x_ٻٽو_انگ_Position )
    {
        mov     # px_پورٽ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    فراغ v_پورٽ_Recursive_تالو_Acquire( بنياد_Type_t xCoreID, بنياد_Type_t xFromIsr )
    {
        بنياد_Type_t x_Saved_مداخلت_حالت;
        بنياد_Type_t x_ٻٽو_انگ_Position = ( xFromIsr == pdTRUE );

        x_Saved_مداخلت_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

        إذا( ux_تالو_Nesting[ xCoreID ][ x_ٻٽو_انگ_Position ] == 0 )
        {
            prv_Exclusive_تالو( x_ٻٽو_انگ_Position );
        }

        ux_تالو_Nesting[ xCoreID ][ x_ٻٽو_انگ_Position ]++;
        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x_Saved_مداخلت_حالت );
    }

    فراغ v_پورٽ_Recursive_تالو_Release( بنياد_Type_t xCoreID, بنياد_Type_t xFromIsr )
    {
        بنياد_Type_t x_Saved_مداخلت_حالت;
        بنياد_Type_t x_ٻٽو_انگ_Position = ( xFromIsr == pdTRUE );

        x_Saved_مداخلت_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

        /* Sync memory */
        پورٽ_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_تالو_Nesting[ xCoreID ][ x_ٻٽو_انگ_Position ] > 0 ) );
        ux_تالو_Nesting[ xCoreID ][ x_ٻٽو_انگ_Position ]--;

        إذا( ux_تالو_Nesting[ xCoreID ][ x_ٻٽو_انگ_Position ] == 0 )
        {
            prvExclusiveRelease( x_ٻٽو_انگ_Position );
        }

        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x_Saved_مداخلت_حالت );
    }

/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* (configNUMBER_OF_CORES > 1) */
