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
#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_شمېره_د_CORES == 1 ) )
    #تېروتنه INCLUDE_xTaskGetCurrentTaskHandle must be سېټ منزل 1 دننه single core.
#د_که_پای

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#تعریف_کړه پورټ_PSW_ثبتوونکی_ID          ( 5 )
#تعریف_کړه پورټ_FPSR_ثبتوونکی_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#تعریف_کړه پورټ_INITIAL_PSW_ماسک         ( 0x000f8000 )
#تعریف_کړه پورټ_CURRENT_PSW_ارزښت        ( پورټ_STSR( پورټ_PSW_ثبتوونکی_ID ) )
#تعریف_کړه پورټ_CURRENT_SR_ZERO_ارزښت    ( ( ډېری_Type_t ) 0x00000000 )
#تعریف_کړه پورټ_CURRENT_FPSR_ارزښت       ( پورټ_STSR( پورټ_FPSR_ثبتوونکی_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#تعریف_کړه پورټ_INITIAL_FPSR_ماسک        ( 0x00ae0000 )
#تعریف_کړه پورټ_PSW_ID_ماسک              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#تعریف_کړه پورټ_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#تعریف_کړه پورټ_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#تعریف_کړه پورټ_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#تعریف_کړه پورټ_OSTM0_TS_ADDR             ( 0xFFD70014 )

#إذا ( config_شمېره_د_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #که_تعریف_شوی configIPIR_CHANNEL
        #تعریف_کړه پورټ_IPIR_بنسټ_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #وإلا
        #تعریف_کړه پورټ_IPIR_بنسټ_ADDR    ( 0xFFFEEC80 )
    #د_که_پای

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #که_تعریف_شوی config_EXCLUSIVE_پته
        #تعریف_کړه پورټ_MEV_بنسټ_ADDR    config_EXCLUSIVE_پته
    #وإلا
        #تعریف_کړه پورټ_MEV_بنسټ_ADDR    ( 0xFFFEEC00 )
    #د_که_پای
#د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R1     ( ( ډېری_Type_t ) 0x01010101 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R2     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x02 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R3     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x03 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R4     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x04 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R5     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x05 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R6     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x06 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R7     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x07 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R8     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x08 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R9     ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x09 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R10    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x10 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R11    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x11 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R12    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x12 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R13    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x13 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R14    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x14 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R15    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x15 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R16    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x16 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R17    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x17 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R18    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x18 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R19    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x19 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R20    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x20 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R21    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x21 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R22    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x22 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R23    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x23 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R24    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x24 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R25    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x25 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R26    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x26 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R27    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x27 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R28    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x28 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R29    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x29 )
#تعریف_کړه پورټ_ډېری_INITIAL_ارزښت_R30    ( ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#تعریف_کړه پورټ_OSTM_COUNTER_پیل              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#تعریف_کړه پورټ_OSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#تعریف_کړه پورټ_OSTM_ډېرپېښ_INTERVAL_TIMER        ( 0x00U )
#تعریف_کړه پورټ_OSTM_ډېرپېښ_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#تعریف_کړه پورټ_OSTM_پیل_مداخله_DISABLE    ( 0x00U )
#تعریف_کړه پورټ_OSTM_پیل_مداخله_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#تعریف_کړه پورټ_INT_مستقیم_ویکټور               ( 0x0U )
#تعریف_کړه پورټ_INT_جدول_ویکټور                ( 0x1U )

/* Interrupt mask (MKxxx) */
#تعریف_کړه پورټ_INT_PROCESSING_ENABLED          ( 0x0U )
#تعریف_کړه پورټ_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#تعریف_کړه پورټ_INT_لومړیتوب_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL1             ( 0x0001U ) /* Level 1 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL2             ( 0x0002U ) /* Level 2 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL3             ( 0x0003U ) /* Level 3 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL4             ( 0x0004U ) /* Level 4 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL5             ( 0x0005U ) /* Level 5 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL6             ( 0x0006U ) /* Level 6 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL7             ( 0x0007U ) /* Level 7 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL8             ( 0x0008U ) /* Level 8 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL9             ( 0x0009U ) /* Level 9 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL10            ( 0x000AU ) /* Level 10 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL11            ( 0x000BU ) /* Level 11 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL12            ( 0x000CU ) /* Level 12 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL13            ( 0x000DU ) /* Level 13 */
#تعریف_کړه پورټ_INT_لومړیتوب_LEVEL14            ( 0x000EU ) /* Level 14 */
#تعریف_کړه پورټ_INT_لومړیتوب_ټیټ_ترین             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#تعریف_کړه پورټ_SCHEDULER_NOREQUEST            0UL
#تعریف_کړه پورټ_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#تعریف_کړه پورټ_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#که_نه_تعریف_شوی config_تیاری_TICK_مداخله

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #تعریف_کړه config_تیاری_TICK_مداخله()    prv_تیاری_Timer_مداخله()
#د_که_پای /* configSETUP_TICK_INTERRUPT */

#إذا ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #تعریف_کړه configMAX_INT_NESTING    2UL
#د_که_پای

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
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

#إذا ( config_شمېره_د_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ساكن فراغ prv_Exclusive_قلف( بنسټ_Type_t xFromIsr );
    ساكن فراغ prvExclusiveRelease( بنسټ_Type_t xFromIsr );

#د_که_پای

/*
 * Function to start the first task executing
 */
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/* Scheduler request on each cores which are starting first task and switching
 * context */
متطاير بنسټ_Type_t x_پورټ_مهالوېش_حالت[ config_شمېره_د_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
متطاير UBaseType_t ux_مداخله_Nesting[ config_شمېره_د_CORES ] = { 0 };
متطاير ثابت UBaseType_t ux_پورټ_Max_مداخله_ژوروالی = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_قلف_Nesting[ config_شمېره_د_CORES ][ 2 ] = { 0 };

#إذا ( config_شمېره_د_CORES > 1 )

/* Pointer to exclusive access memory */
    متطاير بنسټ_Type_t * px_پورټ_Exclusive_Reg = ( متطاير بنسټ_Type_t * ) ( پورټ_MEV_بنسټ_ADDR );
#د_که_پای

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
فراغ v_پورټ_Tick_ISR( فراغ );

#إذا ( config_شمېره_د_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    فراغ v_پورټ_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    فراغ v_پورټ_IPIHander( فراغ );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    فراغ v_پورټ_Recursive_قلف_Acquire( بنسټ_Type_t xCoreID, بنسټ_Type_t xFromIsr );
    فراغ v_پورټ_Recursive_قلف_Release( بنسټ_Type_t xCoreID, بنسټ_Type_t xFromIsr );

#د_که_پای /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
پورټ_LONG x_پورټ_سېټ_مداخله_ماسک( فراغ )
{
    پورټ_LONG ulPSWValue = پورټ_STSR( پورټ_PSW_ثبتوونکی_ID );

    پورټ_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    أرجع ulPSWValue;
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک( پورټ_LONG ux_Saved_مداخله_حالت )
{
    پورټ_LONG ulPSWValue = پورټ_STSR( پورټ_PSW_ثبتوونکی_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( پورټ_PSW_ID_ماسک ) );
    ulPSWValue |= ( پورټ_PSW_ID_ماسک & ux_Saved_مداخله_حالت );
    پورټ_LDSR( پورټ_PSW_ثبتوونکی_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
بنسټ_Type_t x_پورټ_GET_CORE_ID( فراغ )
{
    #إذا ( config_شمېره_د_CORES > 1 )
        أرجع ( پورټ_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #وإلا

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        أرجع 0;
    #د_که_پای
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
فراغ * pv_پورټ_Get_Current_TCB( فراغ )
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
فراغ v_پورټ_سېټ_Switch( بنسټ_Type_t xSwitchRequired )
{
    إذا( xSwitchRequired != pdFALSE )
    {
        x_پورټ_مهالوېش_حالت[ x_پورټ_GET_CORE_ID() ] = پورټ_SCHEDULER_TASKSWITCH;
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
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R5;  /* R5 (TP)  */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;                /* R6       */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R7;  /* R7       */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R8;  /* R8       */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R9;  /* R9       */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R10; /* R10      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R11; /* R11      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R12; /* R12      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R13; /* R13      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R14; /* R14      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R15; /* R15      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R16; /* R16      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R17; /* R17      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R18; /* R18      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R19; /* R19      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R20; /* R20      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R21; /* R21      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R22; /* R22      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R23; /* R23      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R24; /* R24      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R25; /* R25      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R26; /* R26      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R27; /* R27      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R28; /* R28      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R29; /* R29      */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R30; /* R30 (EP) */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R1;  /* R1        */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_ډېری_INITIAL_ارزښت_R2;  /* R2        */

    px_سر_د_ډېری--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( پورټ_CURRENT_PSW_ارزښت & پورټ_INITIAL_PSW_ماسک ); /* EIPSW */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;                                           /* EIPC */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_CURRENT_SR_ZERO_ارزښت;                        /* EIIC */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ( پورټ_CURRENT_PSW_ارزښت & پورټ_INITIAL_PSW_ماسک ); /* CTPSW */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_CURRENT_SR_ZERO_ارزښت;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #إذا ( configENABLE_FPU == 1 )
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) ( پورټ_CURRENT_FPSR_ارزښت & پورټ_INITIAL_FPSR_ماسک ); /* FPSR */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_CURRENT_SR_ZERO_ارزښت;                          /* FPEPC */
    #د_که_پای /* (configENABLE_FPU == 1) */

    أرجع px_سر_د_ډېری;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    #إذا ( config_شمېره_د_CORES > 1 )
        بنسټ_Type_t xCurrentCore = x_پورټ_GET_CORE_ID();
    #د_که_پای

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    پورټ_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_تیاری_TICK_مداخله();

    #إذا ( config_شمېره_د_CORES > 1 )
        /* Start scheduler on other cores */
        لكل( uint16_t xCoreID = 0; xCoreID < config_شمېره_د_CORES; xCoreID++ )
        {
            إذا( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_پورټ_مهالوېش_حالت[ xCoreID ] = پورټ_SCHEDULER_STARTFIRSTTASK;
                v_پورټ_Yield_Core( xCoreID );
            }
            وإلا
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_پورټ_مهالوېش_حالت[ xCoreID ] = پورټ_SCHEDULER_NOREQUEST;
            }
        }
    #د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_پورټ_پیل_لومړی_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #إذا ( config_شمېره_د_CORES > 1 )
            xCurrentCore
        #د_که_پای
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
    پورټ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#إذا ( config_شمېره_د_CORES > 1 )

    فراغ v_پورټ_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        إذا( xCoreID != x_پورټ_GET_CORE_ID() )
        {
            متطاير uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( متطاير uint32_t * ) ( پورټ_IPIR_بنسټ_ADDR );

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
            v_پورټ_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    فراغ v_پورټ_IPIHander( فراغ )
    {
        بنسټ_Type_t xCurrentCore = x_پورټ_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        إذا( پورټ_SCHEDULER_STARTFIRSTTASK != x_پورټ_مهالوېش_حالت[ xCurrentCore ] )
        {
            x_پورټ_مهالوېش_حالت[ xCurrentCore ] = پورټ_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#د_که_پای /* (configNUMBER_OF_CORES > 1) */

فراغ v_پورټ_Tick_ISR( فراغ )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #إذا ( config_شمېره_د_CORES > 1 )
        بنسټ_Type_t x_Saved_مداخله_حالت;

        x_Saved_مداخله_حالت = پورټ_ENTER_CRITICAL_FROM_ISR();
    #د_که_پای
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_پورټ_مهالوېش_حالت[ x_پورټ_GET_CORE_ID() ] = پورټ_SCHEDULER_TASKSWITCH;
        }
    }
    #إذا ( config_شمېره_د_CORES > 1 )
        پورټ_EXIT_CRITICAL_FROM_ISR( x_Saved_مداخله_حالت );
    #د_که_پای
}

/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    متطاير uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( متطاير uint32_t * ) پورټ_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( پورټ_INT_PROCESSING_ENABLED | پورټ_INT_مستقیم_ویکټور | پورټ_INT_لومړیتوب_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( متطاير uint32_t * ) پورټ_OSTM0_CTL_ADDR ) =
        ( پورټ_OSTM_ډېرپېښ_INTERVAL_TIMER | پورټ_OSTM_پیل_مداخله_DISABLE );
    *( ( متطاير uint32_t * ) پورټ_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_شرح_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( متطاير uint32_t * ) پورټ_OSTM0_TS_ADDR ) = پورټ_OSTM_COUNTER_پیل;
}

/*-----------------------------------------------------------*/

#إذا ( config_شمېره_د_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #لارښوونه inline_asm prv_Exclusive_قلف
    ساكن فراغ prv_Exclusive_قلف( بنسټ_Type_t x_بټ_Position )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_پورټ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_قلف_قلف:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_قلف_قلف_success
        snooze
        br prv_Exclusive_قلف_قلف

prv_Exclusive_قلف_قلف_success:
    }

/*-----------------------------------------------------------*/

    #لارښوونه inline_asm prvExclusiveRelease
    ساكن فراغ prvExclusiveRelease( بنسټ_Type_t x_بټ_Position )
    {
        mov     # px_پورټ_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    فراغ v_پورټ_Recursive_قلف_Acquire( بنسټ_Type_t xCoreID, بنسټ_Type_t xFromIsr )
    {
        بنسټ_Type_t x_Saved_مداخله_حالت;
        بنسټ_Type_t x_بټ_Position = ( xFromIsr == pdTRUE );

        x_Saved_مداخله_حالت = پورټ_سېټ_مداخله_ماسک_FROM_ISR();

        إذا( ux_قلف_Nesting[ xCoreID ][ x_بټ_Position ] == 0 )
        {
            prv_Exclusive_قلف( x_بټ_Position );
        }

        ux_قلف_Nesting[ xCoreID ][ x_بټ_Position ]++;
        پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x_Saved_مداخله_حالت );
    }

    فراغ v_پورټ_Recursive_قلف_Release( بنسټ_Type_t xCoreID, بنسټ_Type_t xFromIsr )
    {
        بنسټ_Type_t x_Saved_مداخله_حالت;
        بنسټ_Type_t x_بټ_Position = ( xFromIsr == pdTRUE );

        x_Saved_مداخله_حالت = پورټ_سېټ_مداخله_ماسک_FROM_ISR();

        /* Sync memory */
        پورټ_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_قلف_Nesting[ xCoreID ][ x_بټ_Position ] > 0 ) );
        ux_قلف_Nesting[ xCoreID ][ x_بټ_Position ]--;

        إذا( ux_قلف_Nesting[ xCoreID ][ x_بټ_Position ] == 0 )
        {
            prvExclusiveRelease( x_بټ_Position );
        }

        پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x_Saved_مداخله_حالت );
    }

/*-----------------------------------------------------------*/

#د_که_پای /* (configNUMBER_OF_CORES > 1) */
