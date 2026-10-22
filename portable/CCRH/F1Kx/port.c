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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_सङ्ख्या_सम्बन्धि_CORES == 1 ) )
    #दोषः INCLUDE_xTaskGetCurrentTaskHandle must be समुच्चयः गन्तव्यम् 1 अन्तर् single core.
#यदि_अन्तः

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#परिभाषय पत्तनम्_PSW_पञ्जिकाकोशः_ID          ( 5 )
#परिभाषय पत्तनम्_FPSR_पञ्जिकाकोशः_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#परिभाषय पत्तनम्_INITIAL_PSW_आवरणम्         ( 0x000f8000 )
#परिभाषय पत्तनम्_CURRENT_PSW_मानम्        ( पत्तनम्_STSR( पत्तनम्_PSW_पञ्जिकाकोशः_ID ) )
#परिभाषय पत्तनम्_CURRENT_SR_ZERO_मानम्    ( ( राशिः_Type_t ) 0x00000000 )
#परिभाषय पत्तनम्_CURRENT_FPSR_मानम्       ( पत्तनम्_STSR( पत्तनम्_FPSR_पञ्जिकाकोशः_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#परिभाषय पत्तनम्_INITIAL_FPSR_आवरणम्        ( 0x00ae0000 )
#परिभाषय पत्तनम्_PSW_ID_आवरणम्              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#परिभाषय पत्तनम्_OSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#परिभाषय पत्तनम्_OSTM0_CMP_ADDR            ( 0xFFD70000 )
#परिभाषय पत्तनम्_OSTM0_CTL_ADDR            ( 0xFFD70020 )
#परिभाषय पत्तनम्_OSTM0_TS_ADDR             ( 0xFFD70014 )

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #यदि_परिभाषितम् configIPIR_CHANNEL
        #परिभाषय पत्तनम्_IPIR_आधारः_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #अन्यथा
        #परिभाषय पत्तनम्_IPIR_आधारः_ADDR    ( 0xFFFEEC80 )
    #यदि_अन्तः

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #यदि_परिभाषितम् config_EXCLUSIVE_स्थानाङ्कः
        #परिभाषय पत्तनम्_MEV_आधारः_ADDR    config_EXCLUSIVE_स्थानाङ्कः
    #अन्यथा
        #परिभाषय पत्तनम्_MEV_आधारः_ADDR    ( 0xFFFEEC00 )
    #यदि_अन्तः
#यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R1     ( ( राशिः_Type_t ) 0x01010101 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R2     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x02 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R3     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x03 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R4     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x04 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R5     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x05 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R6     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x06 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R7     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x07 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R8     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x08 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R9     ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x09 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R10    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x10 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R11    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x11 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R12    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x12 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R13    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x13 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R14    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x14 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R15    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x15 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R16    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x16 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R17    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x17 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R18    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x18 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R19    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x19 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R20    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x20 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R21    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x21 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R22    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x22 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R23    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x23 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R24    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x24 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R25    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x25 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R26    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x26 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R27    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x27 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R28    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x28 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R29    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x29 )
#परिभाषय पत्तनम्_राशिः_INITIAL_मानम्_R30    ( ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#परिभाषय पत्तनम्_OSTM_गणक_START              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#परिभाषय पत्तनम्_OSTM_गणक_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#परिभाषय पत्तनम्_OSTM_बहुलकम्_INTERVAL_TIMER        ( 0x00U )
#परिभाषय पत्तनम्_OSTM_बहुलकम्_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#परिभाषय पत्तनम्_OSTM_START_व्यवधानम्_DISABLE    ( 0x00U )
#परिभाषय पत्तनम्_OSTM_START_व्यवधानम्_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#परिभाषय पत्तनम्_INT_प्रत्यक्षम्_सदिशम्               ( 0x0U )
#परिभाषय पत्तनम्_INT_सारणी_सदिशम्                ( 0x1U )

/* Interrupt mask (MKxxx) */
#परिभाषय पत्तनम्_INT_PROCESSING_ENABLED          ( 0x0U )
#परिभाषय पत्तनम्_INT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#परिभाषय पत्तनम्_INT_प्राथमिकता_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL1             ( 0x0001U ) /* Level 1 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL2             ( 0x0002U ) /* Level 2 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL3             ( 0x0003U ) /* Level 3 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL4             ( 0x0004U ) /* Level 4 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL5             ( 0x0005U ) /* Level 5 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL6             ( 0x0006U ) /* Level 6 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL7             ( 0x0007U ) /* Level 7 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL8             ( 0x0008U ) /* Level 8 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL9             ( 0x0009U ) /* Level 9 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL10            ( 0x000AU ) /* Level 10 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL11            ( 0x000BU ) /* Level 11 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL12            ( 0x000CU ) /* Level 12 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL13            ( 0x000DU ) /* Level 13 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_LEVEL14            ( 0x000EU ) /* Level 14 */
#परिभाषय पत्तनम्_INT_प्राथमिकता_निम्नतमम्             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#परिभाषय पत्तनम्_SCHEDULER_NOREQUEST            0UL
#परिभाषय पत्तनम्_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#परिभाषय पत्तनम्_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#यदि_अपरिभाषितम् config_सज्जता_TICK_व्यवधानम्

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #परिभाषय config_सज्जता_TICK_व्यवधानम्()    prv_सज्जता_Timer_व्यवधानम्()
#यदि_अन्तः /* configSETUP_TICK_INTERRUPT */

#यदि ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #परिभाषय configMAX_INT_NESTING    2UL
#यदि_अन्तः

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    स्थिर शून्य prv_Exclusive_तालकम्( आधारः_Type_t xFromIsr );
    स्थिर शून्य prvExclusiveRelease( आधारः_Type_t xFromIsr );

#यदि_अन्तः

/*
 * Function to start the first task executing
 */
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

/* Scheduler request on each cores which are starting first task and switching
 * context */
चञ्चल आधारः_Type_t x_पत्तनम्_कालसारणी_स्थितिः[ config_सङ्ख्या_सम्बन्धि_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
चञ्चल UBaseType_t ux_व्यवधानम्_Nesting[ config_सङ्ख्या_सम्बन्धि_CORES ] = { 0 };
चञ्चल ध्रुव UBaseType_t ux_पत्तनम्_Max_व्यवधानम्_गभीरता = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t ux_तालकम्_Nesting[ config_सङ्ख्या_सम्बन्धि_CORES ][ 2 ] = { 0 };

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/* Pointer to exclusive access memory */
    चञ्चल आधारः_Type_t * px_पत्तनम्_Exclusive_Reg = ( चञ्चल आधारः_Type_t * ) ( पत्तनम्_MEV_आधारः_ADDR );
#यदि_अन्तः

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
शून्य v_पत्तनम्_Tick_ISR( शून्य );

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    शून्य v_पत्तनम्_Yield_Core( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    शून्य v_पत्तनम्_IPIHander( शून्य );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    शून्य v_पत्तनम्_Recursive_तालकम्_Acquire( आधारः_Type_t xCoreID, आधारः_Type_t xFromIsr );
    शून्य v_पत्तनम्_Recursive_तालकम्_Release( आधारः_Type_t xCoreID, आधारः_Type_t xFromIsr );

#यदि_अन्तः /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
पत्तनम्_LONG x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य )
{
    पत्तनम्_LONG ulPSWValue = पत्तनम्_STSR( पत्तनम्_PSW_पञ्जिकाकोशः_ID );

    पत्तनम्_DISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    प्रत्यागम ulPSWValue;
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( पत्तनम्_LONG ux_Saved_व्यवधानम्_स्थितिः )
{
    पत्तनम्_LONG ulPSWValue = पत्तनम्_STSR( पत्तनम्_PSW_पञ्जिकाकोशः_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( पत्तनम्_PSW_ID_आवरणम् ) );
    ulPSWValue |= ( पत्तनम्_PSW_ID_आवरणम् & ux_Saved_व्यवधानम्_स्थितिः );
    पत्तनम्_LDSR( पत्तनम्_PSW_पञ्जिकाकोशः_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
आधारः_Type_t x_पत्तनम्_GET_CORE_ID( शून्य )
{
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        प्रत्यागम ( पत्तनम्_STSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #अन्यथा

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        प्रत्यागम 0;
    #यदि_अन्तः
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
शून्य * pv_पत्तनम्_Get_Current_TCB( शून्य )
{
    शून्य * pvCurrentTCB = ( शून्य * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != रिक्त );

    प्रत्यागम pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
शून्य v_पत्तनम्_समुच्चयः_Switch( आधारः_Type_t xSwitchRequired )
{
    यदि( xSwitchRequired != pdFALSE )
    {
        x_पत्तनम्_कालसारणी_स्थितिः[ x_पत्तनम्_GET_CORE_ID() ] = पत्तनम्_SCHEDULER_TASKSWITCH;
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
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R5;  /* R5 (TP)  */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;                /* R6       */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R7;  /* R7       */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R8;  /* R8       */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R9;  /* R9       */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R10; /* R10      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R11; /* R11      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R12; /* R12      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R13; /* R13      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R14; /* R14      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R15; /* R15      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R16; /* R16      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R17; /* R17      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R18; /* R18      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R19; /* R19      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R20; /* R20      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R21; /* R21      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R22; /* R22      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R23; /* R23      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R24; /* R24      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R25; /* R25      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R26; /* R26      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R27; /* R27      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R28; /* R28      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R29; /* R29      */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R30; /* R30 (EP) */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R1;  /* R1        */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_राशिः_INITIAL_मानम्_R2;  /* R2        */

    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( पत्तनम्_CURRENT_PSW_मानम् & पत्तनम्_INITIAL_PSW_आवरणम् ); /* EIPSW */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;                                           /* EIPC */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_CURRENT_SR_ZERO_मानम्;                        /* EIIC */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( पत्तनम्_CURRENT_PSW_मानम् & पत्तनम्_INITIAL_PSW_आवरणम् ); /* CTPSW */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_CURRENT_SR_ZERO_मानम्;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #यदि ( configENABLE_FPU == 1 )
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( पत्तनम्_CURRENT_FPSR_मानम् & पत्तनम्_INITIAL_FPSR_आवरणम् ); /* FPSR */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_CURRENT_SR_ZERO_मानम्;                          /* FPEPC */
    #यदि_अन्तः /* (configENABLE_FPU == 1) */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        आधारः_Type_t xCurrentCore = x_पत्तनम्_GET_CORE_ID();
    #यदि_अन्तः

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    पत्तनम्_DISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    config_सज्जता_TICK_व्यवधानम्();

    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        /* Start scheduler on other cores */
        प्रति( uint16_t xCoreID = 0; xCoreID < config_सङ्ख्या_सम्बन्धि_CORES; xCoreID++ )
        {
            यदि( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                x_पत्तनम्_कालसारणी_स्थितिः[ xCoreID ] = पत्तनम्_SCHEDULER_STARTFIRSTTASK;
                v_पत्तनम्_Yield_Core( xCoreID );
            }
            अन्यथा
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                x_पत्तनम्_कालसारणी_स्थितिः[ xCoreID ] = पत्तनम्_SCHEDULER_NOREQUEST;
            }
        }
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    v_पत्तनम्_Start_First_Task();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
            xCurrentCore
        #यदि_अन्तः
        );

    प्रत्यागम pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य )
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
    पत्तनम्_DISABLE_INTERRUPTS();

    प्रति( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

    शून्य v_पत्तनम्_Yield_Core( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        यदि( xCoreID != x_पत्तनम्_GET_CORE_ID() )
        {
            चञ्चल uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( चञ्चल uint32_t * ) ( पत्तनम्_IPIR_आधारः_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        अन्यथा
        {
            /* Yielding current core */
            v_पत्तनम्_Yield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    शून्य v_पत्तनम्_IPIHander( शून्य )
    {
        आधारः_Type_t xCurrentCore = x_पत्तनम्_GET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        यदि( पत्तनम्_SCHEDULER_STARTFIRSTTASK != x_पत्तनम्_कालसारणी_स्थितिः[ xCurrentCore ] )
        {
            x_पत्तनम्_कालसारणी_स्थितिः[ xCurrentCore ] = पत्तनम्_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#यदि_अन्तः /* (configNUMBER_OF_CORES > 1) */

शून्य v_पत्तनम्_Tick_ISR( शून्य )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        आधारः_Type_t x_Saved_व्यवधानम्_स्थितिः;

        x_Saved_व्यवधानम्_स्थितिः = पत्तनम्_ENTER_CRITICAL_FROM_ISR();
    #यदि_अन्तः
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            x_पत्तनम्_कालसारणी_स्थितिः[ x_पत्तनम्_GET_CORE_ID() ] = पत्तनम्_SCHEDULER_TASKSWITCH;
        }
    }
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
        पत्तनम्_EXIT_CRITICAL_FROM_ISR( x_Saved_व्यवधानम्_स्थितिः );
    #यदि_अन्तः
}

/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    चञ्चल uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( चञ्चल uint32_t * ) पत्तनम्_OSTM_EIC_ADDR;
    *pulOSTMIntReg = ( पत्तनम्_INT_PROCESSING_ENABLED | पत्तनम्_INT_प्रत्यक्षम्_सदिशम् | पत्तनम्_INT_प्राथमिकता_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( चञ्चल uint32_t * ) पत्तनम्_OSTM0_CTL_ADDR ) =
        ( पत्तनम्_OSTM_बहुलकम्_INTERVAL_TIMER | पत्तनम्_OSTM_START_व्यवधानम्_DISABLE );
    *( ( चञ्चल uint32_t * ) पत्तनम्_OSTM0_CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / config_TICK_दरः_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( चञ्चल uint32_t * ) पत्तनम्_OSTM0_TS_ADDR ) = पत्तनम्_OSTM_गणक_START;
}

/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #निर्देशः inline_asm prv_Exclusive_तालकम्
    स्थिर शून्य prv_Exclusive_तालकम्( आधारः_Type_t xBitPosition )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # px_पत्तनम्_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

prv_Exclusive_तालकम्_तालकम्:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prv_Exclusive_तालकम्_तालकम्_success
        snooze
        br prv_Exclusive_तालकम्_तालकम्

prv_Exclusive_तालकम्_तालकम्_success:
    }

/*-----------------------------------------------------------*/

    #निर्देशः inline_asm prvExclusiveRelease
    स्थिर शून्य prvExclusiveRelease( आधारः_Type_t xBitPosition )
    {
        mov     # px_पत्तनम्_Exclusive_Reg_2, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    शून्य v_पत्तनम्_Recursive_तालकम्_Acquire( आधारः_Type_t xCoreID, आधारः_Type_t xFromIsr )
    {
        आधारः_Type_t x_Saved_व्यवधानम्_स्थितिः;
        आधारः_Type_t xBitPosition = ( xFromIsr == pdTRUE );

        x_Saved_व्यवधानम्_स्थितिः = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();

        यदि( ux_तालकम्_Nesting[ xCoreID ][ xBitPosition ] == 0 )
        {
            prv_Exclusive_तालकम्( xBitPosition );
        }

        ux_तालकम्_Nesting[ xCoreID ][ xBitPosition ]++;
        पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x_Saved_व्यवधानम्_स्थितिः );
    }

    शून्य v_पत्तनम्_Recursive_तालकम्_Release( आधारः_Type_t xCoreID, आधारः_Type_t xFromIsr )
    {
        आधारः_Type_t x_Saved_व्यवधानम्_स्थितिः;
        आधारः_Type_t xBitPosition = ( xFromIsr == pdTRUE );

        x_Saved_व्यवधानम्_स्थितिः = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();

        /* Sync memory */
        पत्तनम्_SYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( ux_तालकम्_Nesting[ xCoreID ][ xBitPosition ] > 0 ) );
        ux_तालकम्_Nesting[ xCoreID ][ xBitPosition ]--;

        यदि( ux_तालकम्_Nesting[ xCoreID ][ xBitPosition ] == 0 )
        {
            prvExclusiveRelease( xBitPosition );
        }

        पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x_Saved_व्यवधानम्_स्थितिः );
    }

/*-----------------------------------------------------------*/

#यदि_अन्तः /* (configNUMBER_OF_CORES > 1) */
