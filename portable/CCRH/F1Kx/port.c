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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_نمبر_کا_CORES == 1 ) )
    #غلطی INCLUDE_xTaskGetCurrentTaskHandle must be سیٹ مقصد 1 اندر single core.
#اگر_ختم

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#تعریف_کرو پورٹ_PSW_رجسٹر_ID          ( 5 )
#تعریف_کرو پورٹ_FPSR_رجسٹر_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#تعریف_کرو پورٹ_INITIAL_PSW_نقاب         ( 0x000f8000 )
#تعریف_کرو پورٹ_CURRENT_PSW_قدر        ( پورٹ_STSR( پورٹ_PSW_رجسٹر_ID ) )
#تعریف_کرو پورٹ_CURRENT_SR_ZERO_قدر    ( ( ڈھیر_Type_t ) 0x00000000 )
#تعریف_کرو پورٹ_CURRENT_FPSR_قدر       ( پورٹ_STSR( پورٹ_FPSR_رجسٹر_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#تعریف_کرو پورٹ_INITIAL_FPSR_نقاب        ( 0x00ae0000 )
#تعریف_کرو پورٹ_PSW_ID_نقاب              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#تعریف_کرو پورٹ_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#تعریف_کرو پورٹ_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#تعریف_کرو پورٹ_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#تعریف_کرو پورٹ_OSTM0_TS_ADDR             ( 0xFFD70014 )

#اگر ( config_نمبر_کا_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #اگر_تعریف_شدہ configIPIR_CHANNEL
        #تعریف_کرو پورٹ_IPIR_بنیاد_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #ورنہ
        #تعریف_کرو پورٹ_IPIR_بنیاد_ADDR    ( 0xFFFEEC80 )
    #اگر_ختم

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #اگر_تعریف_شدہ config_EXCLUSIVE_پتہ
        #تعریف_کرو پورٹ_MEV_بنیاد_ADDR    config_EXCLUSIVE_پتہ
    #ورنہ
        #تعریف_کرو پورٹ_MEV_بنیاد_ADDR    ( 0xFFFEEC00 )
    #اگر_ختم
#اگر_ختم /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R1     ( ( ڈھیر_Type_t ) 0x01010101 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R2     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x02 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R3     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x03 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R4     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x04 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R5     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x05 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R6     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x06 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R7     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x07 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R8     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x08 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R9     ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x09 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R10    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x10 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R11    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x11 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R12    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x12 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R13    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x13 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R14    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x14 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R15    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x15 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R16    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x16 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R17    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x17 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R18    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x18 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R19    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x19 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R20    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x20 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R21    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x21 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R22    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x22 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R23    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x23 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R24    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x24 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R25    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x25 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R26    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x26 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R27    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x27 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R28    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x28 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R29    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x29 )
#تعریف_کرو پورٹ_ڈھیر_INITIAL_قدر_R30    ( ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#تعریف_کرو پورٹ_OSTM_شمار_آغاز              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#تعریف_کرو پورٹ_OSTM_شمار_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#تعریف_کرو پورٹ_OSTM_منوال_INTERVAL_TIMER        ( 0x00U )
#تعریف_کرو پورٹ_OSTM_منوال_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#تعریف_کرو پورٹ_OSTM_آغاز_مداخلت_DISABLE    ( 0x00U )
#تعریف_کرو پورٹ_OSTM_آغاز_مداخلت_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#تعریف_کرو پورٹ_INT_براہ_راست_سمتیہ               ( 0x0U )
#تعریف_کرو پورٹ_INT_جدول_سمتیہ                ( 0x1U )

/* Interrupt mask (MKxxx) */
#تعریف_کرو پورٹ_INT_PROCESSING_ENABLED          ( 0x0U )
#تعریف_کرو پورٹ_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#تعریف_کرو پورٹ_INT_ترجیح_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL1             ( 0x0001U ) /* Level 1 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL2             ( 0x0002U ) /* Level 2 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL3             ( 0x0003U ) /* Level 3 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL4             ( 0x0004U ) /* Level 4 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL5             ( 0x0005U ) /* Level 5 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL6             ( 0x0006U ) /* Level 6 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL7             ( 0x0007U ) /* Level 7 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL8             ( 0x0008U ) /* Level 8 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL9             ( 0x0009U ) /* Level 9 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL10            ( 0x000AU ) /* Level 10 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL11            ( 0x000BU ) /* Level 11 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL12            ( 0x000CU ) /* Level 12 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL13            ( 0x000DU ) /* Level 13 */
#تعریف_کرو پورٹ_INT_ترجیح_LEVEL14            ( 0x000EU ) /* Level 14 */
#تعریف_کرو پورٹ_INT_ترجیح_سب_سے_نیچا             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#تعریف_کرو پورٹ_SCHEDULER_NOREQUEST            0UL
#تعریف_کرو پورٹ_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#تعریف_کرو پورٹ_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#اگر_غیر_تعریف_شدہ config_تیاری_TICK_مداخلت

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #تعریف_کرو config_تیاری_TICK_مداخلت()    prv_تیاری_Timer_مداخلت()
#اگر_ختم /* configSETUP_TICK_INTERRUPT */

#اگر ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #تعریف_کرو configMAX_INT_NESTING    2UL
#اگر_ختم

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

#اگر ( config_نمبر_کا_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ساکن خالی prv_Exclusive_تالا( بنیاد_Type_t xFromIsr );
    ساکن خالی prvExclusiveRelease( بنیاد_Type_t xFromIsr );

#اگر_ختم

/*
 * Function to start the first task executing
 */
خارجی خالی v_پورٹ_آغاز_پہلا_Task( خالی );

/* Scheduler request on each cores which are starting first task and switching
 * context */
متلون بنیاد_Type_t x_پورٹ_جدول_وقت_حالت[ config_نمبر_کا_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
متلون UBaseType_t ux_مداخلت_Nesting[ config_نمبر_کا_CORES ] = { 0 };
متلون ثابت UBaseType_t ux_پورٹ_Max_مداخلت_گہرائی = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_تالا_Nesting[ config_نمبر_کا_CORES ][ 2 ] = { 0 };

#اگر ( config_نمبر_کا_CORES > 1 )

/* Pointer to exclusive access memory */
    متلون بنیاد_Type_t * px_پورٹ_Exclusive_Reg = ( متلون بنیاد_Type_t * ) ( پورٹ_MEV_بنیاد_ADDR );
#اگر_ختم

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
خالی v_پورٹ_Tick_ISR( خالی );

#اگر ( config_نمبر_کا_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    خالی v_پورٹ_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    خالی v_پورٹ_IPIHander( خالی );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    خالی v_پورٹ_Recursive_تالا_Acquire( بنیاد_Type_t xCoreID, بنیاد_Type_t xFromIsr );
    خالی v_پورٹ_Recursive_تالا_Release( بنیاد_Type_t xCoreID, بنیاد_Type_t xFromIsr );

#اگر_ختم /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
پورٹ_LONG x_پورٹ_سیٹ_مداخلت_نقاب( خالی )
{
    پورٹ_LONG ulPSWValue = پورٹ_STSR( پورٹ_PSW_رجسٹر_ID );

    پورٹ_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    واپس ulPSWValue;
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_Clear_مداخلت_نقاب( پورٹ_LONG ux_Saved_مداخلت_حالت )
{
    پورٹ_LONG ulPSWValue = پورٹ_STSR( پورٹ_PSW_رجسٹر_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( پورٹ_PSW_ID_نقاب ) );
    ulPSWValue |= ( پورٹ_PSW_ID_نقاب & ux_Saved_مداخلت_حالت );
    پورٹ_LDSR( پورٹ_PSW_رجسٹر_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
بنیاد_Type_t x_پورٹ_GET_CORE_ID( خالی )
{
    #اگر ( config_نمبر_کا_CORES > 1 )
        واپس ( پورٹ_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #ورنہ

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        واپس 0;
    #اگر_ختم
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
خالی * pv_پورٹ_Get_Current_TCB( خالی )
{
    خالی * pvCurrentTCB = ( خالی * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != تہی );

    واپس pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
خالی v_پورٹ_سیٹ_Switch( بنیاد_Type_t xSwitchRequired )
{
    اگر( xSwitchRequired != pdFALSE )
    {
        x_پورٹ_جدول_وقت_حالت[ x_پورٹ_GET_CORE_ID() ] = پورٹ_SCHEDULER_TASKSWITCH;
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
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R5;  /* R5 (TP)  */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;                /* R6       */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R7;  /* R7       */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R8;  /* R8       */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R9;  /* R9       */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R10; /* R10      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R11; /* R11      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R12; /* R12      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R13; /* R13      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R14; /* R14      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R15; /* R15      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R16; /* R16      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R17; /* R17      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R18; /* R18      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R19; /* R19      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R20; /* R20      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R21; /* R21      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R22; /* R22      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R23; /* R23      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R24; /* R24      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R25; /* R25      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R26; /* R26      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R27; /* R27      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R28; /* R28      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R29; /* R29      */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R30; /* R30 (EP) */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R1;  /* R1        */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_ڈھیر_INITIAL_قدر_R2;  /* R2        */

    px_چوٹی_کا_ڈھیر--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( پورٹ_CURRENT_PSW_قدر & پورٹ_INITIAL_PSW_نقاب ); /* EIPSW */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;                                           /* EIPC */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_CURRENT_SR_ZERO_قدر;                        /* EIIC */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( پورٹ_CURRENT_PSW_قدر & پورٹ_INITIAL_PSW_نقاب ); /* CTPSW */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_CURRENT_SR_ZERO_قدر;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #اگر ( configENABLE_FPU == 1 )
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( پورٹ_CURRENT_FPSR_قدر & پورٹ_INITIAL_FPSR_نقاب ); /* FPSR */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_CURRENT_SR_ZERO_قدر;                          /* FPEPC */
    #اگر_ختم /* (configENABLE_FPU == 1) */

    واپس px_چوٹی_کا_ڈھیر;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    #اگر ( config_نمبر_کا_CORES > 1 )
        بنیاد_Type_t xCurrentCore = x_پورٹ_GET_CORE_ID();
    #اگر_ختم

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    پورٹ_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_تیاری_TICK_مداخلت();

    #اگر ( config_نمبر_کا_CORES > 1 )
        /* Start scheduler on other cores */
        برائے( uint16_t xCoreID = 0; xCoreID < config_نمبر_کا_CORES; xCoreID++ )
        {
            اگر( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_پورٹ_جدول_وقت_حالت[ xCoreID ] = پورٹ_SCHEDULER_STARTFIRSTTASK;
                v_پورٹ_Yield_Core( xCoreID );
            }
            ورنہ
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_پورٹ_جدول_وقت_حالت[ xCoreID ] = پورٹ_SCHEDULER_NOREQUEST;
            }
        }
    #اگر_ختم /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_پورٹ_آغاز_پہلا_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #اگر ( config_نمبر_کا_CORES > 1 )
            xCurrentCore
        #اگر_ختم
        );

    واپس pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی )
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
    پورٹ_DISABLE_INTERRUPTS();

    برائے( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#اگر ( config_نمبر_کا_CORES > 1 )

    خالی v_پورٹ_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        اگر( xCoreID != x_پورٹ_GET_CORE_ID() )
        {
            متلون uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( متلون uint32_t * ) ( پورٹ_IPIR_بنیاد_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        ورنہ
        {
            /* Yielding current core */
            v_پورٹ_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    خالی v_پورٹ_IPIHander( خالی )
    {
        بنیاد_Type_t xCurrentCore = x_پورٹ_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        اگر( پورٹ_SCHEDULER_STARTFIRSTTASK != x_پورٹ_جدول_وقت_حالت[ xCurrentCore ] )
        {
            x_پورٹ_جدول_وقت_حالت[ xCurrentCore ] = پورٹ_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#اگر_ختم /* (configNUMBER_OF_CORES > 1) */

خالی v_پورٹ_Tick_ISR( خالی )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #اگر ( config_نمبر_کا_CORES > 1 )
        بنیاد_Type_t x_Saved_مداخلت_حالت;

        x_Saved_مداخلت_حالت = پورٹ_ENTER_CRITICAL_FROM_ISR();
    #اگر_ختم
    {
        /* Increment the RTOS tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_پورٹ_جدول_وقت_حالت[ x_پورٹ_GET_CORE_ID() ] = پورٹ_SCHEDULER_TASKSWITCH;
        }
    }
    #اگر ( config_نمبر_کا_CORES > 1 )
        پورٹ_EXIT_CRITICAL_FROM_ISR( x_Saved_مداخلت_حالت );
    #اگر_ختم
}

/*-----------------------------------------------------------*/

ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    متلون uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( متلون uint32_t * ) پورٹ_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( پورٹ_INT_PROCESSING_ENABLED | پورٹ_INT_براہ_راست_سمتیہ | پورٹ_INT_ترجیح_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( متلون uint32_t * ) پورٹ_OSTM0_CTL_ADDR ) =
        ( پورٹ_OSTM_منوال_INTERVAL_TIMER | پورٹ_OSTM_آغاز_مداخلت_DISABLE );
    *( ( متلون uint32_t * ) پورٹ_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_شرح_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( متلون uint32_t * ) پورٹ_OSTM0_TS_ADDR ) = پورٹ_OSTM_شمار_آغاز;
}

/*-----------------------------------------------------------*/

#اگر ( config_نمبر_کا_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #ہدایت inline_asm prv_Exclusive_تالا
    ساکن خالی prv_Exclusive_تالا( بنیاد_Type_t x_ثنائی_ہندسہ_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_پورٹ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_تالا_تالا:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_تالا_تالا_success
        snooze
        br prv_Exclusive_تالا_تالا

prv_Exclusive_تالا_تالا_success:
    }

/*-----------------------------------------------------------*/

    #ہدایت inline_asm prvExclusiveRelease
    ساکن خالی prvExclusiveRelease( بنیاد_Type_t x_ثنائی_ہندسہ_Position )
    {
        mov     # px_پورٹ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    خالی v_پورٹ_Recursive_تالا_Acquire( بنیاد_Type_t xCoreID, بنیاد_Type_t xFromIsr )
    {
        بنیاد_Type_t x_Saved_مداخلت_حالت;
        بنیاد_Type_t x_ثنائی_ہندسہ_Position = ( xFromIsr == pdTRUE );

        x_Saved_مداخلت_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

        اگر( ux_تالا_Nesting[ xCoreID ][ x_ثنائی_ہندسہ_Position ] == 0 )
        {
            prv_Exclusive_تالا( x_ثنائی_ہندسہ_Position );
        }

        ux_تالا_Nesting[ xCoreID ][ x_ثنائی_ہندسہ_Position ]++;
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x_Saved_مداخلت_حالت );
    }

    خالی v_پورٹ_Recursive_تالا_Release( بنیاد_Type_t xCoreID, بنیاد_Type_t xFromIsr )
    {
        بنیاد_Type_t x_Saved_مداخلت_حالت;
        بنیاد_Type_t x_ثنائی_ہندسہ_Position = ( xFromIsr == pdTRUE );

        x_Saved_مداخلت_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

        /* Sync memory */
        پورٹ_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_تالا_Nesting[ xCoreID ][ x_ثنائی_ہندسہ_Position ] > 0 ) );
        ux_تالا_Nesting[ xCoreID ][ x_ثنائی_ہندسہ_Position ]--;

        اگر( ux_تالا_Nesting[ xCoreID ][ x_ثنائی_ہندسہ_Position ] == 0 )
        {
            prvExclusiveRelease( x_ثنائی_ہندسہ_Position );
        }

        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x_Saved_مداخلت_حالت );
    }

/*-----------------------------------------------------------*/

#اگر_ختم /* (configNUMBER_OF_CORES > 1) */
