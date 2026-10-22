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
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

/* This port uses xTaskGetCurrentTaskHandle to get TCB stack, it is required to
 * enable this API. */
#ଯଦି ( ( INCLUDE_xTaskGetCurrentTaskHandle != 1 ) && ( config_ସଂଖ୍ୟା_OF_CORES == 1 ) )
    #error INCLUDE_xTaskGetCurrentTaskHandle must be set to 1 in single core.
#endif

/***********************************************************
* Macro definitions
***********************************************************/

/* Hardware specific macros */
#define portPSW_REGISTER_ID          ( 5 )
#define portFPSR_REGISTER_ID         ( 6 )

/* PSW.EBV and PSW.CUx bits are kept as current status */
#define portINITIAL_PSW_MASK         ( 0x000f8000 )
#define port_CURRENT_PSW_ମୂଲ୍ୟ        ( portSTSR( portPSW_REGISTER_ID ) )
#define port_CURRENT_SR_ZERO_ମୂଲ୍ୟ    ( ( ଗଦା_Type_t ) 0x00000000 )
#define port_CURRENT_FPSR_ମୂଲ୍ୟ       ( portSTSR( portFPSR_REGISTER_ID ) )

/* Mask for FPU configuration bits (FN, PEM, RM, FS) */
#define portINITIAL_FPSR_MASK        ( 0x00ae0000 )
#define portPSW_ID_MASK              ( 0x00000020 )

/* Define necessary hardware IO for OSTM timer. OSTM0 is used by default as
 * it is common for almost device variants. If it conflicts with application,
 * the application shall implement another timer.*/
#define portOSTM_EIC_ADDR            ( 0xFFFFB0A8 )
#define portOSTM0CMP_ADDR            ( 0xFFD70000 )
#define portOSTM0CTL_ADDR            ( 0xFFD70020 )
#define portOSTM0TS_ADDR             ( 0xFFD70014 )

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )

/* IPIR  base address, the peripheral is used for Inter-Processor communication
 * Hardware supports 4 channels which is offset by 0x0, 0x4, 0x8, 0xC bytes from
 * base address. By default, channel 0 is selected. */
    #ifdef configIPIR_CHANNEL
        #define portIPIR_BASE_ADDR    ( ( 0xFFFEEC80 ) + ( configIPIR_CHANNEL << 2 ) )
    #ଅନ୍ୟଥା
        #define portIPIR_BASE_ADDR    ( 0xFFFEEC80 )
    #endif

/*  Address used for exclusive control for variable shared between PEs
 * (common resources), each CPU cores have independent access path to
 * this address. By default, G0MEV0 register is selected*/
    #ifdef configEXCLUSIVE_ADDRESS
        #define portMEV_BASE_ADDR    configEXCLUSIVE_ADDRESS
    #ଅନ୍ୟଥା
        #define portMEV_BASE_ADDR    ( 0xFFFEEC00 )
    #endif
#endif /* if ( configNUMBER_OF_CORES > 1 ) */

/* Macros required to set up the initial stack. */
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1     ( ( ଗଦା_Type_t ) 0x01010101 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R2     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x02 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R3     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x03 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R4     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x04 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R5     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x05 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R6     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x06 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R7     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x07 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R8     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x08 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R9     ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x09 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R10    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x10 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R11    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x11 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R12    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x12 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R13    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x13 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R14    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x14 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R15    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x15 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R16    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x16 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R17    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x17 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R18    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x18 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R19    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x19 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R20    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x20 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R21    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x21 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R22    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x22 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R23    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x23 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R24    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x24 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R25    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x25 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R26    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x26 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R27    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x27 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R28    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x28 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R29    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x29 )
#define port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R30    ( ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1 * 0x30 )

/***********************************************************
* Typedef definitions
***********************************************************/

/* OSTM Count Start Trigger Register (OSTMnTS) */
#define portOSTM_COUNTER_START              ( 0x01U ) /* Starts the counter */

/* OSTM Count Stop Trigger Register (OSTMnTT) */
#define portOSTM_COUNTER_STOP               ( 0x01U ) /* Stops the counter */

/* OSTM Control Register (OSTMnCTL) */
#define portOSTM_MODE_INTERVAL_TIMER        ( 0x00U )
#define portOSTM_MODE_FREE_RUNNING          ( 0x02U )

/* Disables or Enable the interrupts when counting starts */
#define portOSTM_START_INTERRUPT_DISABLE    ( 0x00U )
#define portOSTM_START_INTERRUPT_ENABLE     ( 0x01U )

/* Interrupt vector method select (TBxxx) */
#define portINT_DIRECT_VECTOR               ( 0x0U )
#define portINT_TABLE_VECTOR                ( 0x1U )

/* Interrupt mask (MKxxx) */
#define portINT_PROCESSING_ENABLED          ( 0x0U )
#define portINT_PROCESSING_DISABLED         ( 0x1U )

/* Specify 16 interrupt priority levels */
#define portINT_PRIORITY_HIGHEST            ( 0x0000U ) /* Level 0 (highest) */
#define portINT_PRIORITY_LEVEL1             ( 0x0001U ) /* Level 1 */
#define portINT_PRIORITY_LEVEL2             ( 0x0002U ) /* Level 2 */
#define portINT_PRIORITY_LEVEL3             ( 0x0003U ) /* Level 3 */
#define portINT_PRIORITY_LEVEL4             ( 0x0004U ) /* Level 4 */
#define portINT_PRIORITY_LEVEL5             ( 0x0005U ) /* Level 5 */
#define portINT_PRIORITY_LEVEL6             ( 0x0006U ) /* Level 6 */
#define portINT_PRIORITY_LEVEL7             ( 0x0007U ) /* Level 7 */
#define portINT_PRIORITY_LEVEL8             ( 0x0008U ) /* Level 8 */
#define portINT_PRIORITY_LEVEL9             ( 0x0009U ) /* Level 9 */
#define portINT_PRIORITY_LEVEL10            ( 0x000AU ) /* Level 10 */
#define portINT_PRIORITY_LEVEL11            ( 0x000BU ) /* Level 11 */
#define portINT_PRIORITY_LEVEL12            ( 0x000CU ) /* Level 12 */
#define portINT_PRIORITY_LEVEL13            ( 0x000DU ) /* Level 13 */
#define portINT_PRIORITY_LEVEL14            ( 0x000EU ) /* Level 14 */
#define portINT_PRIORITY_LOWEST             ( 0x000FU ) /* Level 15 (lowest) */

/* Macros indicating status of scheduler request */
#define PORT_SCHEDULER_NOREQUEST            0UL
#define PORT_SCHEDULER_TASKSWITCH           1UL       /* Do not modify */
#define PORT_SCHEDULER_STARTFIRSTTASK       2UL       /* Do not modify */

#ifndef configSETUP_TICK_INTERRUPT

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #define configSETUP_TICK_INTERRUPT()    prvSetupTimerInterrupt()
#endif /* configSETUP_TICK_INTERRUPT */

#ଯଦି ( !defined( configMAX_INT_NESTING ) || ( configMAX_INT_NESTING == 0 ) )

/* Set the default value for depth of nested interrupt. In theory, the
 * microcontroller have mechanism to limit number of nested level of interrupt
 * by priority (maximum 16 levels). However, the large stack memory should be
 * prepared for each task to save resource in interrupt handler. Therefore, it
 * is necessary to limit depth of nesting interrupt to optimize memory usage.
 * In addition, the execution time of interrupt handler should be very short
 * (typically not exceed 20us), this constraint does not impact to system.
 */
    #define configMAX_INT_NESTING    2UL
#endif

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvTaskExitError( ଶୂନ୍ୟ );

/*
 * Sets up the periodic ISR used for the RTOS tick using the OSTM.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )

/*
 * Functions implement spin-lock between cores by atomic accesses to Exclusive
 * Control Register (G0MEVm). There are separated access path between CPU cores,
 * but they should wait if access to same register
 */
    ସ୍ଥିର ଶୂନ୍ୟ prvExclusiveLock( BaseType_t xFromIsr );
    ସ୍ଥିର ଶୂନ୍ୟ prvExclusiveRelease( BaseType_t xFromIsr );

#endif

/*
 * Function to start the first task executing
 */
ବାହ୍ୟ ଶୂନ୍ୟ vPortStartFirstTask( ଶୂନ୍ୟ );

/* Scheduler request on each cores which are starting first task and switching
 * context */
ଅସ୍ଥିର BaseType_t xPortScheduleStatus[ config_ସଂଖ୍ୟା_OF_CORES ] = { 0 };

/* Counts the interrupt nesting depth. A context switch is only performed if
 * the nesting depth is 0. In addition, the interrupt shares same stack
 * allocated for each tasks. With supporting nesting interrupt, the stack
 * may be overflowed.
 * It is necessary to control maximum stack depth.
 */
ଅସ୍ଥିର UBaseType_t uxInterruptNesting[ config_ସଂଖ୍ୟା_OF_CORES ] = { 0 };
ଅସ୍ଥିର ଅଚଳ UBaseType_t uxPortMaxInterruptDepth = configMAX_INT_NESTING;

/* Count number of nested locks by same cores. The lock is completely released
 * only if this count is decreased to 0, the lock is separated for task
 * and isr */
UBaseType_t uxLockNesting[ config_ସଂଖ୍ୟା_OF_CORES ][ 2 ] = { 0 };

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )

/* Pointer to exclusive access memory */
    ଅସ୍ଥିର BaseType_t * pxPortExclusiveReg = ( ଅସ୍ଥିର BaseType_t * ) ( portMEV_BASE_ADDR );
#endif

/* Interrupt handler for OSTM timer which handling tick increment and resulting
 * to switch context. */
ଶୂନ୍ୟ vPortTickISR( ଶୂନ୍ୟ );

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )

/* Yield specific cores by send inter-processor interrupt */
    ଶୂନ୍ୟ vPortYieldCore( uint32_t xCoreID );

/*
 * Inter-processor interrupt handler. The interrupt is triggered by
 * portYIELD_CORE().
 */
    ଶୂନ୍ୟ vPortIPIHander( ଶୂନ୍ୟ );

/* These functions below implement recursive spinlock for exclusive access among
 * cores. The core will wait until lock will be available, whilst the core which
 * already had lock can acquire lock without waiting. This function could be
 * call from task and interrupt context, the critical section is called
 * as in ISR */
    ଶୂନ୍ୟ vPortRecursiveLockAcquire( BaseType_t xCoreID, BaseType_t xFromIsr );
    ଶୂନ୍ୟ vPortRecursiveLockRelease( BaseType_t xCoreID, BaseType_t xFromIsr );

#endif /* (configNUMBER_OF_CORES > 1) */

/*-----------------------------------------------------------*/

/*
 * These below functions implement interrupt mask from interrupt. They are not
 * called in nesting, it is protected by FreeRTOS kernel.
 */
portLONG xPortSetInterruptMask( ଶୂନ୍ୟ )
{
    portLONG ulPSWValue = portSTSR( portPSW_REGISTER_ID );

    portDISABLE_INTERRUPTS();

    /* It returns current value of Program Status Word register */
    ଫେରନ୍ତୁ ulPSWValue;
}

/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortClearInterruptMask( portLONG uxSavedInterruptStatus )
{
    portLONG ulPSWValue = portSTSR( portPSW_REGISTER_ID );

    /* Interrupt Disable status is indicates by bit#5 of PSW
    * (1: Interrupt is disabled; 0: Interrupt is enabled) */

    /* Revert to the status before interrupt mask. */
    ulPSWValue &= ( ~( portPSW_ID_MASK ) );
    ulPSWValue |= ( portPSW_ID_MASK & uxSavedInterruptStatus );
    portLDSR( portPSW_REGISTER_ID, ulPSWValue );
}

/*-----------------------------------------------------------*/

/*
 * Using CC-RH intrinsic function to get HTCFG0 (regID, selID) = (0,2)
 * Core ID is indicates by bit HTCFG0.PEID located at bit 18 to 16
 * Bit 31 to 19 are read only and always be read as 0. HTCFG0.PEID is 1 and 2
 * corresponding to core 0 (PE1) and core 1 (PE2). It is adjusted to 0 and 1.
 */
BaseType_t xPortGET_CORE_ID( ଶୂନ୍ୟ )
{
    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )
        ଫେରନ୍ତୁ ( portSTSR_CCRH( 0, 2 ) >> 16 ) - 1;
    #ଅନ୍ୟଥା

        /* In single core, xPortGET_CORE_ID is used in this port only.
         * The dummy core ID could be controlled inside this port. */
        ଫେରନ୍ତୁ 0;
    #endif
}

/*-----------------------------------------------------------*/

/*
 * This port supports both multi-cores and single-core, whilst TCB stack
 * variables are different which are respectively pxCurrentTCB (single-core)
 * and pxCurrentTCBs[] (multiple-cores). This function is defined to obtains
 * TCBs of current cores. Also, the C function could switch to corresponding
 * pointer by pre-compile conditions.
 */
ଶୂନ୍ୟ * pvPortGetCurrentTCB( ଶୂନ୍ୟ )
{
    ଶୂନ୍ୟ * pvCurrentTCB = ( ଶୂନ୍ୟ * ) xTaskGetCurrentTaskHandle();

    configASSERT( pvCurrentTCB != ଖାଲି );

    ଫେରନ୍ତୁ pvCurrentTCB;
}

/*-----------------------------------------------------------*/

/*
 * This function checks if a context switch is required and, if so, updates
 * the scheduler status for the core on which the function is called. The
 * scheduler status is set to indicate that a task switch should occur.
 */
ଶୂନ୍ୟ vPortSetSwitch( BaseType_t xSwitchRequired )
{
    ଯଦି( xSwitchRequired != pdFALSE )
    {
        xPortScheduleStatus[ xPortGET_CORE_ID() ] = PORT_SCHEDULER_TASKSWITCH;
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
ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    /* Simulate the stack frame as it would be created by
     * a context switch interrupt. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) prvTaskExitError;            /* R31 (LP) */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R5;  /* R5 (TP)  */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pvParameters;                /* R6       */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R7;  /* R7       */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R8;  /* R8       */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R9;  /* R9       */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R10; /* R10      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R11; /* R11      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R12; /* R12      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R13; /* R13      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R14; /* R14      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R15; /* R15      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R16; /* R16      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R17; /* R17      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R18; /* R18      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R19; /* R19      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R20; /* R20      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R21; /* R21      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R22; /* R22      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R23; /* R23      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R24; /* R24      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R25; /* R25      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R26; /* R26      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R27; /* R27      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R28; /* R28      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R29; /* R29      */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R30; /* R30 (EP) */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R1;  /* R1        */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_ଗଦା_INITIAL_ମୂଲ୍ୟ_R2;  /* R2        */

    px_ଶୀର୍ଷ_Of_ଗଦା--;

    /* Keep System pre-configuration (HV, CUx, EBV) as current setting in
     * PSW register */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ( port_CURRENT_PSW_ମୂଲ୍ୟ & portINITIAL_PSW_MASK ); /* EIPSW */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pxCode;                                           /* EIPC */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_CURRENT_SR_ZERO_ମୂଲ୍ୟ;                        /* EIIC */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ( port_CURRENT_PSW_ମୂଲ୍ୟ & portINITIAL_PSW_MASK ); /* CTPSW */
    px_ଶୀର୍ଷ_Of_ଗଦା--;
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_CURRENT_SR_ZERO_ମୂଲ୍ୟ;                        /* CTPC */

/* __FPU is defined by CCRH compiler if FPU is enabled */
    #ଯଦି ( configENABLE_FPU == 1 )
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ( port_CURRENT_FPSR_ମୂଲ୍ୟ & portINITIAL_FPSR_MASK ); /* FPSR */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) port_CURRENT_SR_ZERO_ମୂଲ୍ୟ;                          /* FPEPC */
    #endif /* (configENABLE_FPU == 1) */

    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}

/*-----------------------------------------------------------*/

/*
 * Configures the tick frequency and starts the first task.
 */
BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )
        BaseType_t xCurrentCore = xPortGET_CORE_ID();
    #endif

    /* Prevent interrupt by timer interrupt during starting first task.
     * The interrupt shall be enabled automatically by being restored from
     * task stack */
    portDISABLE_INTERRUPTS();

    /* Setup the tick interrupt */
    configSETUP_TICK_INTERRUPT();

    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )
        /* Start scheduler on other cores */
        ପାଇଁ( uint16_t xCoreID = 0; xCoreID < config_ସଂଖ୍ୟା_OF_CORES; xCoreID++ )
        {
            ଯଦି( xCoreID != xCurrentCore )
            {
                /* Send yielding request to other cores with flag to start
                 * first task. TaskContextSwitch is not executed */
                xPortScheduleStatus[ xCoreID ] = PORT_SCHEDULER_STARTFIRSTTASK;
                vPortYieldCore( xCoreID );
            }
            ଅନ୍ୟଥା
            {
                /* Nothing to do. The first task is started in this call by
                 * below vPortStartFirstTask() */
                xPortScheduleStatus[ xCoreID ] = PORT_SCHEDULER_NOREQUEST;
            }
        }
    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    /* Start first task in primary core */
    vPortStartFirstTask();

    /* Should never get here as the tasks will now be executing! */
    prvTaskExitError();

    /* To prevent compiler warnings in the case that the application writer
     * overrides this functionality by defining configTASK_RETURN_ADDRESS.
     * Call vTaskSwitchContext() so link time optimization does not remove
     * the symbol. */
    vTaskSwitchContext(
        #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )
            xCurrentCore
        #endif
        );

    ଫେରନ୍ତୁ pdFALSE;
}

/*-----------------------------------------------------------*/

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvTaskExitError( ଶୂନ୍ୟ )
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
    portDISABLE_INTERRUPTS();

    ପାଇଁ( ; ; )
    {
        /* Infinite loop to ensure the function does not return. */
    }
}

/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pdFALSE );
}

/*-----------------------------------------------------------*/

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )

    ଶୂନ୍ୟ vPortYieldCore( uint32_t xCoreID )
    {
        /* Check if we need to yield on a different core */
        ଯଦି( xCoreID != xPortGET_CORE_ID() )
        {
            ଅସ୍ଥିର uint32_t * pulIPIRReg;

            /* Determine the IPI register based on the target core ID */
            pulIPIRReg = ( ଅସ୍ଥିର uint32_t * ) ( portIPIR_BASE_ADDR );

            /*Inter-processor interrupt generates an interrupt request by
             * writing 1 to applicable bits of target cores. The interrupt
             * should be enabled by application in  corresponding cores
             * including PSW.ID (EI instruction) and interrupt control setting
             * for ICIPIRn channel (interrupt mask, vector method)
             */
            *pulIPIRReg = ( 1 << xCoreID );
        }
        ଅନ୍ୟଥା
        {
            /* Yielding current core */
            vPortYield();
        }
    }

/*-----------------------------------------------------------*/

/*
 * Handler for inter-processor interrupt in second cores. The interrupt is
 * triggered by portYIELD_CORE(). vTaskSwitchContext() is invoked to
 * switch tasks
 */
    ଶୂନ୍ୟ vPortIPIHander( ଶୂନ୍ୟ )
    {
        BaseType_t xCurrentCore = xPortGET_CORE_ID();

        /* 1st execution starts 1st task, TaskSwitchContext is not executed */
        ଯଦି( PORT_SCHEDULER_STARTFIRSTTASK != xPortScheduleStatus[ xCurrentCore ] )
        {
            xPortScheduleStatus[ xCurrentCore ] = PORT_SCHEDULER_TASKSWITCH;
        }
    }

/*-----------------------------------------------------------*/

#endif /* (configNUMBER_OF_CORES > 1) */

ଶୂନ୍ୟ vPortTickISR( ଶୂନ୍ୟ )
{
    /* In case of multicores with SMP,  xTaskIncrementTick is required to
     * called in critical section to avoid conflict resource as this function
     * could be called by xTaskResumeAll() from any cores. */
    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )
        BaseType_t xSavedInterruptStatus;

        xSavedInterruptStatus = portENTER_CRITICAL_FROM_ISR();
    #endif
    {
        /* Increment the RTOS tick. */
        ଯଦି( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            xPortScheduleStatus[ xPortGET_CORE_ID() ] = PORT_SCHEDULER_TASKSWITCH;
        }
    }
    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )
        portEXIT_CRITICAL_FROM_ISR( xSavedInterruptStatus );
    #endif
}

/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
    ଅସ୍ଥିର uint32_t * pulOSTMIntReg;

    /* Interrupt configuration for OSTM Timer
     * By default, the second lowest priority is set for timer interrupt to
     * avoid blocking other interrupt. Normally, user could set the lowest
     * priority for non-critical event. It try to keep timer on time.
     * In addition, direct vector table is used by default.
     */
    pulOSTMIntReg = ( ଅସ୍ଥିର uint32_t * ) portOSTM_EIC_ADDR;
    *pulOSTMIntReg = ( portINT_PROCESSING_ENABLED | portINT_DIRECT_VECTOR | portINT_PRIORITY_LEVEL14 );

    /* Set OSTM0 control setting */
    *( ( ଅସ୍ଥିର uint32_t * ) portOSTM0CTL_ADDR ) =
        ( portOSTM_MODE_INTERVAL_TIMER | portOSTM_START_INTERRUPT_DISABLE );
    *( ( ଅସ୍ଥିର uint32_t * ) portOSTM0CMP_ADDR ) =
        ( ( configCPU_CLOCK_HZ / configTIMER_PRESCALE ) / configTICK_RATE_HZ ) - 1;

    /* Enable OSTM0 operation */
    *( ( ଅସ୍ଥିର uint32_t * ) portOSTM0TS_ADDR ) = portOSTM_COUNTER_START;
}

/*-----------------------------------------------------------*/

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES > 1 )

/*
 * These functions implement spin-lock mechanism among cores using hardware
 * exclusive control with atomic access by CLR1 and SET1 instruction.
 * Nesting calls to these APIs are possible.
 */
    #pragma inline_asm prvExclusiveLock
    ସ୍ଥିର ଶୂନ୍ୟ prvExclusiveLock( BaseType_t xBitPosition )
    {
        /* No problem with r19, CCRH does not required to restore same value
         * before and after function call. */
        mov     # _pxPortExclusiveReg, r19
        ld.w    0[ r19 ], r19

prvExclusiveLock_Lock:

        /* r6 is xBitPosition */
        set1 r6, [ r19 ]
        bz prvExclusiveLock_Lock_success
        snooze
        br prvExclusiveLock_Lock

prvExclusiveLock_Lock_success:
    }

/*-----------------------------------------------------------*/

    #pragma inline_asm prvExclusiveRelease
    ସ୍ଥିର ଶୂନ୍ୟ prvExclusiveRelease( BaseType_t xBitPosition )
    {
        mov     # _pxPortExclusiveReg, r19
        ld.w    0[ r19 ], r19

        /* r6 is xBitPosition */
        clr1 r6, [ r19 ]
    }

/*-----------------------------------------------------------*/
    ଶୂନ୍ୟ vPortRecursiveLockAcquire( BaseType_t xCoreID, BaseType_t xFromIsr )
    {
        BaseType_t xSavedInterruptStatus;
        BaseType_t xBitPosition = ( xFromIsr == pdTRUE );

        xSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        ଯଦି( uxLockNesting[ xCoreID ][ xBitPosition ] == 0 )
        {
            prvExclusiveLock( xBitPosition );
        }

        uxLockNesting[ xCoreID ][ xBitPosition ]++;
        portCLEAR_INTERRUPT_MASK_FROM_ISR( xSavedInterruptStatus );
    }

    ଶୂନ୍ୟ vPortRecursiveLockRelease( BaseType_t xCoreID, BaseType_t xFromIsr )
    {
        BaseType_t xSavedInterruptStatus;
        BaseType_t xBitPosition = ( xFromIsr == pdTRUE );

        xSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        /* Sync memory */
        portSYNCM();

        /* Error check whether vPortRecursiveLockRelease() is not called in
         * pair with vPortRecursiveLockAcquire() */
        configASSERT( ( uxLockNesting[ xCoreID ][ xBitPosition ] > 0 ) );
        uxLockNesting[ xCoreID ][ xBitPosition ]--;

        ଯଦି( uxLockNesting[ xCoreID ][ xBitPosition ] == 0 )
        {
            prvExclusiveRelease( xBitPosition );
        }

        portCLEAR_INTERRUPT_MASK_FROM_ISR( xSavedInterruptStatus );
    }

/*-----------------------------------------------------------*/

#endif /* (configNUMBER_OF_CORES > 1) */
