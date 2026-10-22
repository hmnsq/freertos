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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Standard includes. */
#ضمن <string.h>

/* Hardware includes. */
#ضمن <xintc_i.h>
#ضمن <xil_exception.h>
#ضمن <microblaze_exceptions_g.h>

/* Tasks are started with a critical section nesting of 0 - however, prior to
 * the scheduler being commenced interrupts should not be enabled, so the critical
 * nesting variable is initialised to a non-zero value. */
#وصف_ڪريو پورٽ_INITIAL_NESTING_قدر    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#وصف_ڪريو پورٽ_MSR_IE                   ( 0x02U )
#وصف_ڪريو پورٽ_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#وصف_ڪريو پورٽ_INITIAL_FSR              ( 0U )
/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ساكن int32_t prv_Initialise_مداخلت_Controller( فراغ );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ساكن int32_t prv_Ensure_مداخلت_Controller_Is_Initialised( فراغ );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متطاير UBaseType_t uxCriticalNesting = پورٽ_INITIAL_NESTING_قدر;

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
متطاير uint32_t ulTaskSwitchRequested = 0UL;

/* The instance of the interrupt controller used by this port.  This is required
 * by the Xilinx library API functions. */
ساكن XIntc x_مداخلت_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    خارجي فراغ * SDA2_بنياد;
    خارجي فراغ * SDA_بنياد;
    ثابت uint32_t ulR2 = ( uint32_t ) &SDA2_بنياد;
    ثابت uint32_t ulR13 = ( uint32_t ) &SDA_بنياد;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00000000;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00000000;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00000000;
    px_چوٽي_جو_ڍير--;

    #إذا ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_چوٽي_جو_ڍير = پورٽ_INITIAL_FSR;
        px_چوٽي_جو_ڍير--;
    #جيڪڏهن_پورو

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_چوٽي_جو_ڍير = mfmsr() & ~پورٽ_MSR_IE;

    #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_چوٽي_جو_ڍير |= پورٽ_MSR_EE;
    }
    #جيڪڏهن_پورو

    px_چوٽي_جو_ڍير--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #جيڪڏهن_وصف_ٿيل پورٽ_PRE_ڀريو_ڍير_FOR_DEBUGGING
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06; /* R6 - other parameters and temporaries.  Used as the return address from vPortTaskEntryPoint. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07; /* R7 - other parameters and temporaries. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08; /* R8 - other parameters and temporaries. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09; /* R9 - other parameters and temporaries. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x0a; /* R10 - other parameters and temporaries. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x0b; /* R11 - temporaries. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x0c; /* R12 - temporaries. */
        px_چوٽي_جو_ڍير--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_چوٽي_جو_ڍير -= 8;
    #جيڪڏهن_پورو /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ulR13;  /* R13 - read/write small data area. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ; /* R14 - return address for interrupt. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) عدم;   /* R15 - return address for subroutine. */

    #جيڪڏهن_وصف_ٿيل پورٽ_PRE_ڀريو_ڍير_FOR_DEBUGGING
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10; /* R16 - return address for trap (debugger). */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11; /* R17 - return address for exceptions, if configured. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12; /* R18 - reserved for assembler and compiler temporaries. */
        px_چوٽي_جو_ڍير--;
    #وإلا
        px_چوٽي_جو_ڍير -= 4;
    #جيڪڏهن_پورو

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #جيڪڏهن_وصف_ٿيل پورٽ_PRE_ڀريو_ڍير_FOR_DEBUGGING
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x14; /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x15; /* R21 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x16; /* R22 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x17; /* R23 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x18; /* R24 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x19; /* R25 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1a; /* R26 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1b; /* R27 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1c; /* R28 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1d; /* R29 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1e; /* R30 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1f; /* R31 - must be saved across function calls. Callee-save. */
        px_چوٽي_جو_ڍير--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_چوٽي_جو_ڍير -= 13;
    #جيڪڏهن_پورو /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    خارجي فراغ( v_پورٽ_شروعات_پهريون_Task )( فراغ );
    خارجي uint32_t ڍير_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_تياري_Timer_مداخلت();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( uint32_t * ) ڍير_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_پورٽ_شروعات_پهريون_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
فراغ v_پورٽ_Yield( فراغ )
{
    خارجي فراغ VPortYieldASM( فراغ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورٽ_ENTER_CRITICAL();
    {
        /* Jump directly to the yield function to ensure there is no
         * compiler generated prologue code. */
        asm متطاير ( "bralid r14, VPortYieldASM      \n\t" \
                       "or r0, r0, r0                  \n\t" );
    }
    پورٽ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enable_مداخلت( uint8_t uc_مداخلت_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_مداخلت_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Enable( &x_مداخلت_Controller_Instance, uc_مداخلت_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Disable_مداخلت( uint8_t uc_مداخلت_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_مداخلت_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Disable( &x_مداخلت_Controller_Instance, uc_مداخلت_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_Install_مداخلت_Handler( uint8_t uc_مداخلت_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پٺ_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_مداخلت_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_مداخلت_Controller_Instance, uc_مداخلت_ID, pxHandler, pv_Call_پٺ_Ref );
    }

    إذا( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    أرجع lReturn;
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Ensure_مداخلت_Controller_Is_Initialised( فراغ )
{
    ساكن int32_t l_مداخلت_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    إذا( l_مداخلت_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_مداخلت_Controller();

        إذا( lReturn == pdPASS )
        {
            l_مداخلت_Controller_Initialised = pdTRUE;
        }
    }
    وإلا
    {
        lReturn = pdPASS;
    }

    أرجع lReturn;
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.  This is the handler that the application
 * defined callback function vApplicationSetupTimerInterrupt() should install.
 */
فراغ v_پورٽ_Tick_ISR( فراغ * pv_اڻ_استعمال_ٿيل )
{
    خارجي فراغ v_Application_Clear_Timer_مداخلت( فراغ );

    /* Ensure the unused parameter does not generate a compiler warning. */
    ( فراغ ) pv_اڻ_استعمال_ٿيل;

    /* This port uses an application defined callback function to clear the tick
     * interrupt because the kernel will run on lots of different MicroBlaze and
     * FPGA configurations - not all of which will have the same timer peripherals
     * defined or available.  An example definition of
     * vApplicationClearTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_Clear_Timer_مداخلت();

    /* Increment the RTOS tick - this might cause a task to unblock. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        /* Force vTaskSwitchContext() to be called as the interrupt exits. */
        ulTaskSwitchRequested = 1;
    }
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Initialise_مداخلت_Controller( فراغ )
{
    int32_t l_حالت;

    l_حالت = XIntc_Initialize( &x_مداخلت_Controller_Instance, config_مداخلت_CONTROLLER_منزل_USE );

    إذا( l_حالت == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_سيٽ_Intr_Svc_Option( x_مداخلت_Controller_Instance.بنياد_پتو, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_پورٽ_Exceptions_Install_Handlers();
        }
        #جيڪڏهن_پورو /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_حالت = XIntc_شروعات( &x_مداخلت_Controller_Instance, XIN_REAL_گهڻائي );

        إذا( l_حالت == XST_SUCCESS )
        {
            l_حالت = pdPASS;
        }
        وإلا
        {
            l_حالت = pdFAIL;
        }
    }

    configASSERT( l_حالت == pdPASS );

    أرجع l_حالت;
}
/*-----------------------------------------------------------*/
