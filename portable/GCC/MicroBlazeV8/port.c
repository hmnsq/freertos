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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Standard includes. */
#ಅನ್ತರ್ಭಾವ <string.h>

/* Hardware includes. */
#ಅನ್ತರ್ಭಾವ <xintc_i.h>
#ಅನ್ತರ್ಭಾವ <xil_exception.h>
#ಅನ್ತರ್ಭಾವ <microblaze_exceptions_g.h>

/* Tasks are started with a critical section nesting of 0 - however, prior to
 * the scheduler being commenced interrupts should not be enabled, so the critical
 * nesting variable is initialised to a non-zero value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_NESTING_ಮೌಲ್ಯ    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MSR_IE                   ( 0x02U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FSR              ( 0U )
/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ಸ್ಥಿರ int32_t prv_Initialise_ಅಡಚಣೆ_Controller( ಶೂನ್ಯ );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ಸ್ಥಿರ int32_t prv_Ensure_ಅಡಚಣೆ_Controller_Is_Initialised( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting = ಪೋರ್ಟ್_INITIAL_NESTING_ಮೌಲ್ಯ;

/* This port uses a separate stack for interrupts.  This prevents the stack of
 * every task needing to be large enough to hold an entire interrupt stack on top
 * of the task stack. */
uint32_t * pulISRStack;

/* If an interrupt requests a context switch, then ulTaskSwitchRequested will
 * get set to 1.  ulTaskSwitchRequested is inspected just before the main interrupt
 * handler exits.  If, at that time, ulTaskSwitchRequested is set to 1, the kernel
 * will call vTaskSwitchContext() to ensure the task that runs immediately after
 * the interrupt exists is the highest priority task that is able to run.  This is
 * an unusual mechanism, but is used for this port because a single interrupt can
 * cause the servicing of multiple peripherals - and it is inefficient to call
 * vTaskSwitchContext() multiple times as each peripheral is serviced. */
ಅಸ್ಥಿರ uint32_t ulTaskSwitchRequested = 0UL;

/* The instance of the interrupt controller used by this port.  This is required
 * by the Xilinx library API functions. */
ಸ್ಥಿರ XIntc x_ಅಡಚಣೆ_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ * SDA2_ತಳ;
    ಬಾಹ್ಯ ಶೂನ್ಯ * SDA_ತಳ;
    ಸ್ಥಿರಾಂಕ uint32_t ulR2 = ( uint32_t ) &SDA2_ತಳ;
    ಸ್ಥಿರಾಂಕ uint32_t ulR13 = ( uint32_t ) &SDA_ತಳ;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00000000;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00000000;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00000000;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    #ಆದರೆ ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_FSR;
        px_ತುದಿ_ದ_ರಾಶಿ--;
    #ಆದರೆ_ಅಂತ್ಯ

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_ತುದಿ_ದ_ರಾಶಿ = mfmsr() & ~ಪೋರ್ಟ್_MSR_IE;

    #ಆದರೆ ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_MSR_EE;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ಪೋರ್ಟ್_PRE_ತುಂಬು_ರಾಶಿ_FOR_DEBUGGING
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06; /* R6 - other parameters and temporaries.  Used as the return address from vPortTaskEntryPoint. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07; /* R7 - other parameters and temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08; /* R8 - other parameters and temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09; /* R9 - other parameters and temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0a; /* R10 - other parameters and temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0b; /* R11 - temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0c; /* R12 - temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
    #ಇಲ್ಲದಿದ್ದರೆ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_ತುದಿ_ದ_ರಾಶಿ -= 8;
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ulR13;  /* R13 - read/write small data area. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* R14 - return address for interrupt. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಖಾಲಿ;   /* R15 - return address for subroutine. */

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ಪೋರ್ಟ್_PRE_ತುಂಬು_ರಾಶಿ_FOR_DEBUGGING
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10; /* R16 - return address for trap (debugger). */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11; /* R17 - return address for exceptions, if configured. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12; /* R18 - reserved for assembler and compiler temporaries. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
    #ಇಲ್ಲದಿದ್ದರೆ
        px_ತುದಿ_ದ_ರಾಶಿ -= 4;
    #ಆದರೆ_ಅಂತ್ಯ

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00; /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ಪೋರ್ಟ್_PRE_ತುಂಬು_ರಾಶಿ_FOR_DEBUGGING
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x14; /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x15; /* R21 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x16; /* R22 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x17; /* R23 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x18; /* R24 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x19; /* R25 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1a; /* R26 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1b; /* R27 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1c; /* R28 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1d; /* R29 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1e; /* R30 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1f; /* R31 - must be saved across function calls. Callee-save. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
    #ಇಲ್ಲದಿದ್ದರೆ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_ತುದಿ_ದ_ರಾಶಿ -= 13;
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ( v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task )( ಶೂನ್ಯ );
    ಬಾಹ್ಯ uint32_t ರಾಶಿ_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( uint32_t * ) ರಾಶಿ_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here as the tasks are now running! */
    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ VPortYieldASM( ಶೂನ್ಯ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    ಪೋರ್ಟ್_ENTER_CRITICAL();
    {
        /* Jump directly to the yield function to ensure there is no
         * compiler generated prologue code. */
        asm ಅಸ್ಥಿರ ( "bralid r14, VPortYieldASM      \n\t" \
                       "or r0, r0, r0                  \n\t" );
    }
    ಪೋರ್ಟ್_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_ಅಡಚಣೆ( uint8_t uc_ಅಡಚಣೆ_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_ಅಡಚಣೆ_Controller_Is_Initialised();

    ಆದರೆ( lReturn == pdPASS )
    {
        XIntc_Enable( &x_ಅಡಚಣೆ_Controller_Instance, uc_ಅಡಚಣೆ_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Disable_ಅಡಚಣೆ( uint8_t uc_ಅಡಚಣೆ_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_ಅಡಚಣೆ_Controller_Is_Initialised();

    ಆದರೆ( lReturn == pdPASS )
    {
        XIntc_Disable( &x_ಅಡಚಣೆ_Controller_Instance, uc_ಅಡಚಣೆ_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Install_ಅಡಚಣೆ_Handler( uint8_t uc_ಅಡಚಣೆ_ID,
                                         XInterruptHandler pxHandler,
                                         ಶೂನ್ಯ * pv_Call_ಹಿಂಭಾಗ_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_ಅಡಚಣೆ_Controller_Is_Initialised();

    ಆದರೆ( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_ಅಡಚಣೆ_Controller_Instance, uc_ಅಡಚಣೆ_ID, pxHandler, pv_Call_ಹಿಂಭಾಗ_Ref );
    }

    ಆದರೆ( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    ಹಿಂತಿರುಗಿ lReturn;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ int32_t prv_Ensure_ಅಡಚಣೆ_Controller_Is_Initialised( ಶೂನ್ಯ )
{
    ಸ್ಥಿರ int32_t l_ಅಡಚಣೆ_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    ಆದರೆ( l_ಅಡಚಣೆ_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_ಅಡಚಣೆ_Controller();

        ಆದರೆ( lReturn == pdPASS )
        {
            l_ಅಡಚಣೆ_Controller_Initialised = pdTRUE;
        }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        lReturn = pdPASS;
    }

    ಹಿಂತಿರುಗಿ lReturn;
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.  This is the handler that the application
 * defined callback function vApplicationSetupTimerInterrupt() should install.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ * pv_ಬಳಸದ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_Application_Clear_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

    /* Ensure the unused parameter does not generate a compiler warning. */
    ( ಶೂನ್ಯ ) pv_ಬಳಸದ;

    /* This port uses an application defined callback function to clear the tick
     * interrupt because the kernel will run on lots of different MicroBlaze and
     * FPGA configurations - not all of which will have the same timer peripherals
     * defined or available.  An example definition of
     * vApplicationClearTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_Clear_Timer_ಅಡಚಣೆ();

    /* Increment the RTOS tick - this might cause a task to unblock. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        /* Force vTaskSwitchContext() to be called as the interrupt exits. */
        ulTaskSwitchRequested = 1;
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ int32_t prv_Initialise_ಅಡಚಣೆ_Controller( ಶೂನ್ಯ )
{
    int32_t l_ಸ್ಥಿತಿ;

    l_ಸ್ಥಿತಿ = XIntc_Initialize( &x_ಅಡಚಣೆ_Controller_Instance, config_ಅಡಚಣೆ_CONTROLLER_ಗಮ್ಯ_USE );

    ಆದರೆ( l_ಸ್ಥಿತಿ == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_ಗಣ_Intr_Svc_Option( x_ಅಡಚಣೆ_Controller_Instance.ತಳ_ವಿಳಾಸ, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #ಆದರೆ ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_ಪೋರ್ಟ್_Exceptions_Install_Handlers();
        }
        #ಆದರೆ_ಅಂತ್ಯ /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_ಸ್ಥಿತಿ = XIntc_ಆರಂಭ( &x_ಅಡಚಣೆ_Controller_Instance, XIN_REAL_ಬಹುಲಕ );

        ಆದರೆ( l_ಸ್ಥಿತಿ == XST_SUCCESS )
        {
            l_ಸ್ಥಿತಿ = pdPASS;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            l_ಸ್ಥಿತಿ = pdFAIL;
        }
    }

    configASSERT( l_ಸ್ಥಿತಿ == pdPASS );

    ಹಿಂತಿರುಗಿ l_ಸ್ಥಿತಿ;
}
/*-----------------------------------------------------------*/
