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
#ضمن <microblaze_instructions.h>

/* Tasks are started with a critical section nesting of 0 - however, prior to
 * the scheduler being commenced interrupts should not be enabled, so the critical
 * nesting variable is initialised to a non-zero value. */
#تعریف_کرو پورٹ_INITIAL_NESTING_قدر    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#تعریف_کرو پورٹ_MSR_IE                   ( 0x02U )
#تعریف_کرو پورٹ_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#تعریف_کرو پورٹ_INITIAL_FSR              ( 0U )
/*
 * Global counter used for calculation of run time statistics of tasks.
 * Defined only when the relevant option is turned on
 */
#إذا (config_GENERATE_لگاتار_ویلا_STATS==1)
    متطاير uint32_t ul_بلند_Frequency_Timer_Ticks;
#جے_انت

/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ساكن int32_t prv_Initialise_رکاوٹ_Controller( فراغ );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ساكن int32_t prv_Ensure_رکاوٹ_Controller_Is_Initialised( فراغ );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متطاير UBaseType_t uxCriticalNesting = پورٹ_INITIAL_NESTING_قدر;

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
ساكن XIntc x_رکاوٹ_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
#إذا ( پورٹ_HAS_ڈھیر_حد_توں_ودھ_CHECKING == 1 )
    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                         ڈھیر_Type_t * px_سرا_دا_ڈھیر,
                                         TaskFunction_t px_کوڈ,
                                         فراغ * pvParameters )
#وإلا
    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                         TaskFunction_t px_کوڈ,
                                         فراغ * pvParameters )
#جے_انت
{
    خارجي فراغ *SDA2_ادھار;
    خارجي فراغ *SDA_ادھار;
    ثابت UINTPTR ulR2 = ( UINTPTR ) &SDA2_ادھار;
    ثابت UINTPTR ulR13 = ( UINTPTR ) &SDA_ادھار;

    خارجي فراغ _start1( فراغ );

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;
    px_چوٹی_دا_ڈھیر--;

    #إذا ( پورٹ_HAS_ڈھیر_حد_توں_ودھ_CHECKING == 1 )
        /* Store the stack limits. */
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( px_چوٹی_دا_ڈھیر + 3 );
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_سرا_دا_ڈھیر;
        px_چوٹی_دا_ڈھیر--;
    #جے_انت

    #إذا ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_FSR;
        px_چوٹی_دا_ڈھیر--;
    #جے_انت

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_چوٹی_دا_ڈھیر = mfmsr() & ~پورٹ_MSR_IE;

    #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_چوٹی_دا_ڈھیر |= پورٹ_MSR_EE;
    }
    #جے_انت

    px_چوٹی_دا_ڈھیر--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #جے_تعریف_شدہ پورٹ_PRE_لدو_ڈھیر_FOR_DEBUGGING
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x06;   /* R6 - other parameters and temporaries. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x07;   /* R7 - other parameters and temporaries. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) عدم;   /* R8 - other parameters and temporaries. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x09;   /* R9 - other parameters and temporaries. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x0a;   /* R10 - other parameters and temporaries. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x0b;   /* R11 - temporaries. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x0c;   /* R12 - temporaries. */
        px_چوٹی_دا_ڈھیر--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_چوٹی_دا_ڈھیر -= 8;
    #جے_انت /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ulR13;   /* R13 - read/write small data area. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;  /* R14 - return address for interrupt. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) _start1; /* R15 - return address for subroutine. */

    #جے_تعریف_شدہ پورٹ_PRE_لدو_ڈھیر_FOR_DEBUGGING
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x10;   /* R16 - return address for trap (debugger). */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x11;   /* R17 - return address for exceptions, if configured. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x12;   /* R18 - reserved for assembler and compiler temporaries. */
        px_چوٹی_دا_ڈھیر--;
    #وإلا
        px_چوٹی_دا_ڈھیر -= 4;
    #جے_انت

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00;   /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #جے_تعریف_شدہ پورٹ_PRE_لدو_ڈھیر_FOR_DEBUGGING
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x14;   /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x15;   /* R21 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x16;   /* R22 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x17;   /* R23 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x18;   /* R24 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x19;   /* R25 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1a;   /* R26 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1b;   /* R27 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1c;   /* R28 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1d;   /* R29 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1e;   /* R30 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1f;   /* R31 - must be saved across function calls. Callee-save. */
        px_چوٹی_دا_ڈھیر--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_چوٹی_دا_ڈھیر -= 13;
    #جے_انت /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    خارجي فراغ ( v_پورٹ_شروع_پہلا_Task )( فراغ );
    خارجي UINTPTR ڈھیر_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_تیاری_Timer_رکاوٹ();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( UINTPTR * ) ڈھیر_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_پورٹ_شروع_پہلا_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
فراغ v_پورٹ_Yield( فراغ )
{
    خارجي فراغ VPortYieldASM( فراغ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورٹ_ENTER_CRITICAL();
	  {
		    /* Jump directly to the yield function to ensure there is no
		    * compiler generated prologue code. */
        #جے_تعریف_شدہ __arch64__
            asm متطاير (	"brealid r14, VPortYieldASM		\n\t" \
        		         				"or r0, r0, r0					      \n\t" );
        #وإلا
         		asm متطاير (	"bralid r14, VPortYieldASM		\n\t" \
				                 		"or r0, r0, r0					      \n\t" );
        #جے_انت
  	}
	  پورٹ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enable_رکاوٹ( uint8_t uc_رکاوٹ_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_رکاوٹ_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        /* Critical section protects read/modify/writer operation inside
         * XIntc_Enable(). */
        پورٹ_ENTER_CRITICAL();
        {
            XIntc_Enable( &x_رکاوٹ_Controller_Instance, uc_رکاوٹ_ID );
        }
        پورٹ_EXIT_CRITICAL();
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Disable_رکاوٹ( uint8_t uc_رکاوٹ_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_رکاوٹ_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Disable( &x_رکاوٹ_Controller_Instance, uc_رکاوٹ_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_Install_رکاوٹ_Handler( uint8_t uc_رکاوٹ_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پٹھ_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_رکاوٹ_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_رکاوٹ_Controller_Instance, uc_رکاوٹ_ID, pxHandler, pv_Call_پٹھ_Ref );
    }

    إذا( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    أرجع lReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Remove_رکاوٹ_Handler( uint8_t uc_رکاوٹ_ID )
{
    int32_t lReturn;

    /* An API function is provided to remove an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_رکاوٹ_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Disconnect( &x_رکاوٹ_Controller_Instance, uc_رکاوٹ_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Ensure_رکاوٹ_Controller_Is_Initialised( فراغ )
{
    ساكن int32_t l_رکاوٹ_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    إذا( l_رکاوٹ_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_رکاوٹ_Controller();

        إذا( lReturn == pdPASS )
        {
            l_رکاوٹ_Controller_Initialised = pdTRUE;
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
فراغ v_پورٹ_Tick_ISR( فراغ * pv_بن_ورتیا )
{
    خارجي فراغ v_Application_Clear_Timer_رکاوٹ( فراغ );

	/* Ensure the unused parameter does not generate a compiler warning. */
	( فراغ ) pv_بن_ورتیا;

    /* The Xilinx implementation of generating run time task stats uses the same timer used for generating
	   * FreeRTOS ticks. In case user decides to generate run time stats the tick handler is called more
	   * frequently (10 times faster). The timer    ick handler uses logic to handle the same. It handles
	   * the FreeRTOS tick once per 10 interrupts.
	   * For handling generation of run time stats, it increments a pre-defined counter every time the
	   * interrupt handler executes. */
#إذا (config_GENERATE_لگاتار_ویلا_STATS == 1)
    ul_بلند_Frequency_Timer_Ticks++;
    إذا (!(ul_بلند_Frequency_Timer_Ticks % 10))
#جے_انت
    {
        /* This port uses an application defined callback function to clear the tick
         * interrupt because the kernel will run on lots of different MicroBlaze and
         * FPGA configurations - not all of which will have the same timer peripherals
         * defined or available.  An example definition of
         * vApplicationClearTimerInterrupt() is provided in the official demo
         * application that accompanies this port. */
        v_Application_Clear_Timer_رکاوٹ();

        /* Increment the RTOS tick - this might cause a task to unblock. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Force vTaskSwitchContext() to be called as the interrupt exits. */
            ulTaskSwitchRequested = 1;
        }
    }
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Initialise_رکاوٹ_Controller( فراغ )
{
    int32_t l_حالت;

    l_حالت = XIntc_Initialize( &x_رکاوٹ_Controller_Instance, config_رکاوٹ_CONTROLLER_منزل_USE );

    إذا( l_حالت == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_سیٹ_Intr_Svc_Option( x_رکاوٹ_Controller_Instance.ادھار_پتہ, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_پورٹ_Exceptions_Install_Handlers();
        }
        #جے_انت /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_حالت = XIntc_شروع( &x_رکاوٹ_Controller_Instance, XIN_REAL_منوال );

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

#إذا( config_GENERATE_لگاتار_ویلا_STATS == 1 )
/*
 * For Xilinx implementation this is a dummy function that does a redundant operation
 * of zeroing out the global counter.
 * It is called by FreeRTOS kernel.
 */
فراغ x_CONFIGURE_TIMER_FOR_لگاتار_ویلا_STATS (فراغ)
{
	ul_بلند_Frequency_Timer_Ticks = 0;
}
/*
 * For Xilinx implementation this function returns the global counter used for
 * run time task stats calculation.
 * It is called by FreeRTOS kernel task handling logic.
 */
uint32_t x_GET_لگاتار_ویلا_COUNTER_قدر (فراغ)
{
	أرجع ul_بلند_Frequency_Timer_Ticks;
}
#جے_انت
/*-----------------------------------------------------------*/
