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
#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_عدد_از_CORES == 1 ) )
    #خطا INCLUDE_xTaskGetCurrentTaskHandle must be مجموعه مقصد 1 درون single core.
#پایان_اگر

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#تعریف_کن پورت_PSW_ثبات_ID          ( 5 )
#تعریف_کن پورت_FPSR_ثبات_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#تعریف_کن پورت_INITIAL_PSW_ماسک         ( 0x000f8000 )
#تعریف_کن پورت_CURRENT_PSW_مقدار        ( پورت_STSR( پورت_PSW_ثبات_ID ) )
#تعریف_کن پورت_CURRENT_SR_ZERO_مقدار    ( ( پشته_Type_t ) 0x00000000 )
#تعریف_کن پورت_CURRENT_FPSR_مقدار       ( پورت_STSR( پورت_FPSR_ثبات_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#تعریف_کن پورت_INITIAL_FPSR_ماسک        ( 0x00ae0000 )
#تعریف_کن پورت_PSW_ID_ماسک              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#تعریف_کن پورت_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#تعریف_کن پورت_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#تعریف_کن پورت_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#تعریف_کن پورت_OSTM0_TS_ADDR             ( 0xFFD70014 )

#إذا ( config_عدد_از_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #اگر_تعریف_شده configIPIR_CHANNEL
        #تعریف_کن پورت_IPIR_پایه_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #وإلا
        #تعریف_کن پورت_IPIR_پایه_ADDR    ( 0xFFFEEC80 )
    #پایان_اگر

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #اگر_تعریف_شده config_EXCLUSIVE_آدرس
        #تعریف_کن پورت_MEV_پایه_ADDR    config_EXCLUSIVE_آدرس
    #وإلا
        #تعریف_کن پورت_MEV_پایه_ADDR    ( 0xFFFEEC00 )
    #پایان_اگر
#پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#تعریف_کن پورت_پشته_INITIAL_مقدار_R1     ( ( پشته_Type_t ) 0x01010101 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R2     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x02 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R3     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x03 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R4     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x04 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R5     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x05 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R6     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x06 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R7     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x07 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R8     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x08 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R9     ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x09 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R10    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x10 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R11    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x11 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R12    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x12 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R13    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x13 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R14    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x14 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R15    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x15 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R16    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x16 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R17    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x17 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R18    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x18 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R19    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x19 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R20    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x20 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R21    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x21 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R22    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x22 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R23    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x23 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R24    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x24 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R25    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x25 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R26    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x26 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R27    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x27 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R28    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x28 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R29    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x29 )
#تعریف_کن پورت_پشته_INITIAL_مقدار_R30    ( ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#تعریف_کن پورت_OSTM_COUNTER_شروع              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#تعریف_کن پورت_OSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#تعریف_کن پورت_OSTM_نما_INTERVAL_TIMER        ( 0x00U )
#تعریف_کن پورت_OSTM_نما_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#تعریف_کن پورت_OSTM_شروع_وقفه_DISABLE    ( 0x00U )
#تعریف_کن پورت_OSTM_شروع_وقفه_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#تعریف_کن پورت_INT_مستقیم_وکتور               ( 0x0U )
#تعریف_کن پورت_INT_جدول_وکتور                ( 0x1U )

/* Interrupt mask (MKxxx) */
#تعریف_کن پورت_INT_PROCESSING_ENABLED          ( 0x0U )
#تعریف_کن پورت_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#تعریف_کن پورت_INT_اولویت_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#تعریف_کن پورت_INT_اولویت_LEVEL1             ( 0x0001U ) /* Level 1 */
#تعریف_کن پورت_INT_اولویت_LEVEL2             ( 0x0002U ) /* Level 2 */
#تعریف_کن پورت_INT_اولویت_LEVEL3             ( 0x0003U ) /* Level 3 */
#تعریف_کن پورت_INT_اولویت_LEVEL4             ( 0x0004U ) /* Level 4 */
#تعریف_کن پورت_INT_اولویت_LEVEL5             ( 0x0005U ) /* Level 5 */
#تعریف_کن پورت_INT_اولویت_LEVEL6             ( 0x0006U ) /* Level 6 */
#تعریف_کن پورت_INT_اولویت_LEVEL7             ( 0x0007U ) /* Level 7 */
#تعریف_کن پورت_INT_اولویت_LEVEL8             ( 0x0008U ) /* Level 8 */
#تعریف_کن پورت_INT_اولویت_LEVEL9             ( 0x0009U ) /* Level 9 */
#تعریف_کن پورت_INT_اولویت_LEVEL10            ( 0x000AU ) /* Level 10 */
#تعریف_کن پورت_INT_اولویت_LEVEL11            ( 0x000BU ) /* Level 11 */
#تعریف_کن پورت_INT_اولویت_LEVEL12            ( 0x000CU ) /* Level 12 */
#تعریف_کن پورت_INT_اولویت_LEVEL13            ( 0x000DU ) /* Level 13 */
#تعریف_کن پورت_INT_اولویت_LEVEL14            ( 0x000EU ) /* Level 14 */
#تعریف_کن پورت_INT_اولویت_پایینترین             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#تعریف_کن پورت_SCHEDULER_NOREQUEST            0UL
#تعریف_کن پورت_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#تعریف_کن پورت_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#اگر_تعریف_نشده config_راهاندازی_TICK_وقفه

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #تعریف_کن config_راهاندازی_TICK_وقفه()    prv_راهاندازی_Timer_وقفه()
#پایان_اگر /* configSETUP_TICK_INTERRUPT */

#إذا ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #تعریف_کن configMAX_INT_NESTING    2UL
#پایان_اگر

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
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

#إذا ( config_عدد_از_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ساكن فراغ prv_Exclusive_قفل( پایه_Type_t xFromIsr );
    ساكن فراغ prvExclusiveRelease( پایه_Type_t xFromIsr );

#پایان_اگر

/*
 * Function to start the first task executing
 */
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );

/* Scheduler request on each cores which are starting first task and switching
 * context */
متطاير پایه_Type_t x_پورت_زمانبندی_وضعیت[ config_عدد_از_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
متطاير UBaseType_t ux_وقفه_Nesting[ config_عدد_از_CORES ] = { 0 };
متطاير ثابت UBaseType_t ux_پورت_Max_وقفه_عمق = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_قفل_Nesting[ config_عدد_از_CORES ][ 2 ] = { 0 };

#إذا ( config_عدد_از_CORES > 1 )

/* Pointer to exclusive access memory */
    متطاير پایه_Type_t * px_پورت_Exclusive_Reg = ( متطاير پایه_Type_t * ) ( پورت_MEV_پایه_ADDR );
#پایان_اگر

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
فراغ v_پورت_Tick_ISR( فراغ );

#إذا ( config_عدد_از_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    فراغ v_پورت_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    فراغ v_پورت_IPIHander( فراغ );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    فراغ v_پورت_Recursive_قفل_Acquire( پایه_Type_t xCoreID, پایه_Type_t xFromIsr );
    فراغ v_پورت_Recursive_قفل_Release( پایه_Type_t xCoreID, پایه_Type_t xFromIsr );

#پایان_اگر /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
پورت_LONG x_پورت_مجموعه_وقفه_ماسک( فراغ )
{
    پورت_LONG ulPSWValue = پورت_STSR( پورت_PSW_ثبات_ID );

    پورت_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    أرجع ulPSWValue;
}

/*-----------------------------------------------------------*/

فراغ v_پورت_Clear_وقفه_ماسک( پورت_LONG ux_Saved_وقفه_وضعیت )
{
    پورت_LONG ulPSWValue = پورت_STSR( پورت_PSW_ثبات_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( پورت_PSW_ID_ماسک ) );
    ulPSWValue |= ( پورت_PSW_ID_ماسک & ux_Saved_وقفه_وضعیت );
    پورت_LDSR( پورت_PSW_ثبات_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
پایه_Type_t x_پورت_GET_CORE_ID( فراغ )
{
    #إذا ( config_عدد_از_CORES > 1 )
        أرجع ( پورت_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #وإلا

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        أرجع 0;
    #پایان_اگر
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
فراغ * pv_پورت_Get_Current_TCB( فراغ )
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
فراغ v_پورت_مجموعه_Switch( پایه_Type_t xSwitchRequired )
{
    إذا( xSwitchRequired != pdFALSE )
    {
        x_پورت_زمانبندی_وضعیت[ x_پورت_GET_CORE_ID() ] = پورت_SCHEDULER_TASKSWITCH;
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
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R5;  /* R5 (TP)  */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;                /* R6       */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R7;  /* R7       */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R8;  /* R8       */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R9;  /* R9       */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R10; /* R10      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R11; /* R11      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R12; /* R12      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R13; /* R13      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R14; /* R14      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R15; /* R15      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R16; /* R16      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R17; /* R17      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R18; /* R18      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R19; /* R19      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R20; /* R20      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R21; /* R21      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R22; /* R22      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R23; /* R23      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R24; /* R24      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R25; /* R25      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R26; /* R26      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R27; /* R27      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R28; /* R28      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R29; /* R29      */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R30; /* R30 (EP) */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R1;  /* R1        */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_پشته_INITIAL_مقدار_R2;  /* R2        */

    px_بالاترین_از_پشته--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( پورت_CURRENT_PSW_مقدار & پورت_INITIAL_PSW_ماسک ); /* EIPSW */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;                                           /* EIPC */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_CURRENT_SR_ZERO_مقدار;                        /* EIIC */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( پورت_CURRENT_PSW_مقدار & پورت_INITIAL_PSW_ماسک ); /* CTPSW */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_CURRENT_SR_ZERO_مقدار;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #إذا ( configENABLE_FPU == 1 )
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) ( پورت_CURRENT_FPSR_مقدار & پورت_INITIAL_FPSR_ماسک ); /* FPSR */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_CURRENT_SR_ZERO_مقدار;                          /* FPEPC */
    #پایان_اگر /* (configENABLE_FPU == 1) */

    أرجع px_بالاترین_از_پشته;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    #إذا ( config_عدد_از_CORES > 1 )
        پایه_Type_t xCurrentCore = x_پورت_GET_CORE_ID();
    #پایان_اگر

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    پورت_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_راهاندازی_TICK_وقفه();

    #إذا ( config_عدد_از_CORES > 1 )
        /* Start scheduler on other cores */
        لكل( uint16_t xCoreID = 0; xCoreID < config_عدد_از_CORES; xCoreID++ )
        {
            إذا( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_پورت_زمانبندی_وضعیت[ xCoreID ] = پورت_SCHEDULER_STARTFIRSTTASK;
                v_پورت_Yield_Core( xCoreID );
            }
            وإلا
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_پورت_زمانبندی_وضعیت[ xCoreID ] = پورت_SCHEDULER_NOREQUEST;
            }
        }
    #پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_پورت_شروع_اولی_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #إذا ( config_عدد_از_CORES > 1 )
            xCurrentCore
        #پایان_اگر
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
    پورت_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#إذا ( config_عدد_از_CORES > 1 )

    فراغ v_پورت_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        إذا( xCoreID != x_پورت_GET_CORE_ID() )
        {
            متطاير uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( متطاير uint32_t * ) ( پورت_IPIR_پایه_ADDR );

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
            v_پورت_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    فراغ v_پورت_IPIHander( فراغ )
    {
        پایه_Type_t xCurrentCore = x_پورت_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        إذا( پورت_SCHEDULER_STARTFIRSTTASK != x_پورت_زمانبندی_وضعیت[ xCurrentCore ] )
        {
            x_پورت_زمانبندی_وضعیت[ xCurrentCore ] = پورت_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#پایان_اگر /* (configNUMBER_OF_CORES > 1) */

فراغ v_پورت_Tick_ISR( فراغ )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #إذا ( config_عدد_از_CORES > 1 )
        پایه_Type_t x_Saved_وقفه_وضعیت;

        x_Saved_وقفه_وضعیت = پورت_ENTER_CRITICAL_FROM_ISR();
    #پایان_اگر
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_پورت_زمانبندی_وضعیت[ x_پورت_GET_CORE_ID() ] = پورت_SCHEDULER_TASKSWITCH;
        }
    }
    #إذا ( config_عدد_از_CORES > 1 )
        پورت_EXIT_CRITICAL_FROM_ISR( x_Saved_وقفه_وضعیت );
    #پایان_اگر
}

/*-----------------------------------------------------------*/

ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    متطاير uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( متطاير uint32_t * ) پورت_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( پورت_INT_PROCESSING_ENABLED | پورت_INT_مستقیم_وکتور | پورت_INT_اولویت_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( متطاير uint32_t * ) پورت_OSTM0_CTL_ADDR ) =
        ( پورت_OSTM_نما_INTERVAL_TIMER | پورت_OSTM_شروع_وقفه_DISABLE );
    *( ( متطاير uint32_t * ) پورت_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_نرخ_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( متطاير uint32_t * ) پورت_OSTM0_TS_ADDR ) = پورت_OSTM_COUNTER_شروع;
}

/*-----------------------------------------------------------*/

#إذا ( config_عدد_از_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #رهنمود inline_asm prv_Exclusive_قفل
    ساكن فراغ prv_Exclusive_قفل( پایه_Type_t x_بیت_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_پورت_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_قفل_قفل:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_قفل_قفل_success
        snooze
        br prv_Exclusive_قفل_قفل

prv_Exclusive_قفل_قفل_success:
    }

/*-----------------------------------------------------------*/

    #رهنمود inline_asm prvExclusiveRelease
    ساكن فراغ prvExclusiveRelease( پایه_Type_t x_بیت_Position )
    {
        mov     # px_پورت_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    فراغ v_پورت_Recursive_قفل_Acquire( پایه_Type_t xCoreID, پایه_Type_t xFromIsr )
    {
        پایه_Type_t x_Saved_وقفه_وضعیت;
        پایه_Type_t x_بیت_Position = ( xFromIsr == pdTRUE );

        x_Saved_وقفه_وضعیت = پورت_مجموعه_وقفه_ماسک_FROM_ISR();

        إذا( ux_قفل_Nesting[ xCoreID ][ x_بیت_Position ] == 0 )
        {
            prv_Exclusive_قفل( x_بیت_Position );
        }

        ux_قفل_Nesting[ xCoreID ][ x_بیت_Position ]++;
        پورت_CLEAR_وقفه_ماسک_FROM_ISR( x_Saved_وقفه_وضعیت );
    }

    فراغ v_پورت_Recursive_قفل_Release( پایه_Type_t xCoreID, پایه_Type_t xFromIsr )
    {
        پایه_Type_t x_Saved_وقفه_وضعیت;
        پایه_Type_t x_بیت_Position = ( xFromIsr == pdTRUE );

        x_Saved_وقفه_وضعیت = پورت_مجموعه_وقفه_ماسک_FROM_ISR();

        /* Sync memory */
        پورت_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_قفل_Nesting[ xCoreID ][ x_بیت_Position ] > 0 ) );
        ux_قفل_Nesting[ xCoreID ][ x_بیت_Position ]--;

        إذا( ux_قفل_Nesting[ xCoreID ][ x_بیت_Position ] == 0 )
        {
            prvExclusiveRelease( x_بیت_Position );
        }

        پورت_CLEAR_وقفه_ماسک_FROM_ISR( x_Saved_وقفه_وضعیت );
    }

/*-----------------------------------------------------------*/

#پایان_اگر /* (configNUMBER_OF_CORES > 1) */
