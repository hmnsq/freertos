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
#تعریف_کړه پورټ_INITIAL_NESTING_ارزښت    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#تعریف_کړه پورټ_MSR_IE                   ( 0x02U )
#تعریف_کړه پورټ_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#تعریف_کړه پورټ_INITIAL_FSR              ( 0U )
/*
 * Global counter used for calculation of run time statistics of tasks.
 * Defined only when the relevant option is turned on
 */
#إذا (config_GENERATE_پرلپسې_وخت_STATS==1)
    متطاير uint32_t ul_لوړ_Frequency_Timer_Ticks;
#د_که_پای

/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ساكن int32_t prv_Initialise_مداخله_Controller( فراغ );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ساكن int32_t prv_Ensure_مداخله_Controller_Is_Initialised( فراغ );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متطاير UBaseType_t uxCriticalNesting = پورټ_INITIAL_NESTING_ارزښت;

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
ساكن XIntc x_مداخله_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
#إذا ( پورټ_HAS_ډېری_ډکېدنه_CHECKING == 1 )
    ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                         ډېری_Type_t * px_پای_ټکی_د_ډېری,
                                         TaskFunction_t px_کوډ,
                                         فراغ * pvParameters )
#وإلا
    ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                         TaskFunction_t px_کوډ,
                                         فراغ * pvParameters )
#د_که_پای
{
    خارجي فراغ *SDA2_بنسټ;
    خارجي فراغ *SDA_بنسټ;
    ثابت UINTPTR ulR2 = ( UINTPTR ) &SDA2_بنسټ;
    ثابت UINTPTR ulR13 = ( UINTPTR ) &SDA_بنسټ;

    خارجي فراغ _start1( فراغ );

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00000000;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00000000;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00000000;
    px_سر_د_ډېری--;

    #إذا ( پورټ_HAS_ډېری_ډکېدنه_CHECKING == 1 )
        /* Store the stack limits. */
        *px_سر_د_ډېری = ( ډېری_Type_t ) ( px_سر_د_ډېری + 3 );
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) px_پای_ټکی_د_ډېری;
        px_سر_د_ډېری--;
    #د_که_پای

    #إذا ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_سر_د_ډېری = پورټ_INITIAL_FSR;
        px_سر_د_ډېری--;
    #د_که_پای

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_سر_د_ډېری = mfmsr() & ~پورټ_MSR_IE;

    #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_سر_د_ډېری |= پورټ_MSR_EE;
    }
    #د_که_پای

    px_سر_د_ډېری--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #که_تعریف_شوی پورټ_PRE_بارول_ډېری_FOR_DEBUGGING
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06;   /* R6 - other parameters and temporaries. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07;   /* R7 - other parameters and temporaries. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) عدم;   /* R8 - other parameters and temporaries. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09;   /* R9 - other parameters and temporaries. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x0a;   /* R10 - other parameters and temporaries. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x0b;   /* R11 - temporaries. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x0c;   /* R12 - temporaries. */
        px_سر_د_ډېری--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_سر_د_ډېری -= 8;
    #د_که_پای /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_سر_د_ډېری = ( ډېری_Type_t ) ulR13;   /* R13 - read/write small data area. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;  /* R14 - return address for interrupt. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) _start1; /* R15 - return address for subroutine. */

    #که_تعریف_شوی پورټ_PRE_بارول_ډېری_FOR_DEBUGGING
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10;   /* R16 - return address for trap (debugger). */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11;   /* R17 - return address for exceptions, if configured. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12;   /* R18 - reserved for assembler and compiler temporaries. */
        px_سر_د_ډېری--;
    #وإلا
        px_سر_د_ډېری -= 4;
    #د_که_پای

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00;   /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #که_تعریف_شوی پورټ_PRE_بارول_ډېری_FOR_DEBUGGING
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x14;   /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x15;   /* R21 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x16;   /* R22 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x17;   /* R23 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x18;   /* R24 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x19;   /* R25 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x1a;   /* R26 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x1b;   /* R27 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x1c;   /* R28 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x1d;   /* R29 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x1e;   /* R30 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x1f;   /* R31 - must be saved across function calls. Callee-save. */
        px_سر_د_ډېری--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_سر_د_ډېری -= 13;
    #د_که_پای /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ ( v_پورټ_پیل_لومړی_Task )( فراغ );
    خارجي UINTPTR ډېری_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_تیاری_Timer_مداخله();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( UINTPTR * ) ډېری_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
فراغ v_پورټ_Yield( فراغ )
{
    خارجي فراغ VPortYieldASM( فراغ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورټ_ENTER_CRITICAL();
	  {
		    /* Jump directly to the yield function to ensure there is no
		    * compiler generated prologue code. */
        #که_تعریف_شوی __arch64__
            asm متطاير (	"brealid r14, VPortYieldASM		\n\t" \
        		         				"or r0, r0, r0					      \n\t" );
        #وإلا
         		asm متطاير (	"bralid r14, VPortYieldASM		\n\t" \
				                 		"or r0, r0, r0					      \n\t" );
        #د_که_پای
  	}
	  پورټ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enable_مداخله( uint8_t uc_مداخله_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_مداخله_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        /* Critical section protects read/modify/writer operation inside
         * XIntc_Enable(). */
        پورټ_ENTER_CRITICAL();
        {
            XIntc_Enable( &x_مداخله_Controller_Instance, uc_مداخله_ID );
        }
        پورټ_EXIT_CRITICAL();
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Disable_مداخله( uint8_t uc_مداخله_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_مداخله_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Disable( &x_مداخله_Controller_Instance, uc_مداخله_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_Install_مداخله_Handler( uint8_t uc_مداخله_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_شا_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_مداخله_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_مداخله_Controller_Instance, uc_مداخله_ID, pxHandler, pv_Call_شا_Ref );
    }

    إذا( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    أرجع lReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Remove_مداخله_Handler( uint8_t uc_مداخله_ID )
{
    int32_t lReturn;

    /* An API function is provided to remove an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_مداخله_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Disconnect( &x_مداخله_Controller_Instance, uc_مداخله_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Ensure_مداخله_Controller_Is_Initialised( فراغ )
{
    ساكن int32_t l_مداخله_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    إذا( l_مداخله_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_مداخله_Controller();

        إذا( lReturn == pdPASS )
        {
            l_مداخله_Controller_Initialised = pdTRUE;
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
فراغ v_پورټ_Tick_ISR( فراغ * pv_ناکارول_شوی )
{
    خارجي فراغ v_Application_Clear_Timer_مداخله( فراغ );

	/* Ensure the unused parameter does not generate a compiler warning. */
	( فراغ ) pv_ناکارول_شوی;

    /* The Xilinx implementation of generating run time task stats uses the same timer used for generating
	   * FreeRTOS ticks. In case user decides to generate run time stats the tick handler is called more
	   * frequently (10 times faster). The timer    ick handler uses logic to handle the same. It handles
	   * the FreeRTOS tick once per 10 interrupts.
	   * For handling generation of run time stats, it increments a pre-defined counter every time the
	   * interrupt handler executes. */
#إذا (config_GENERATE_پرلپسې_وخت_STATS == 1)
    ul_لوړ_Frequency_Timer_Ticks++;
    إذا (!(ul_لوړ_Frequency_Timer_Ticks % 10))
#د_که_پای
    {
        /* This port uses an application defined callback function to clear the tick
         * interrupt because the kernel will run on lots of different MicroBlaze and
         * FPGA configurations - not all of which will have the same timer peripherals
         * defined or available.  An example definition of
         * vApplicationClearTimerInterrupt() is provided in the official demo
         * application that accompanies this port. */
        v_Application_Clear_Timer_مداخله();

        /* Increment the RTOS tick - this might cause a task to unblock. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Force vTaskSwitchContext() to be called as the interrupt exits. */
            ulTaskSwitchRequested = 1;
        }
    }
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Initialise_مداخله_Controller( فراغ )
{
    int32_t l_حالت;

    l_حالت = XIntc_Initialize( &x_مداخله_Controller_Instance, config_مداخله_CONTROLLER_منزل_USE );

    إذا( l_حالت == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_سېټ_Intr_Svc_Option( x_مداخله_Controller_Instance.بنسټ_پته, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_پورټ_Exceptions_Install_Handlers();
        }
        #د_که_پای /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_حالت = XIntc_پیل( &x_مداخله_Controller_Instance, XIN_REAL_ډېرپېښ );

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

#إذا( config_GENERATE_پرلپسې_وخت_STATS == 1 )
/*
 * For Xilinx implementation this is a dummy function that does a redundant operation
 * of zeroing out the global counter.
 * It is called by FreeRTOS kernel.
 */
فراغ x_CONFIGURE_TIMER_FOR_پرلپسې_وخت_STATS (فراغ)
{
	ul_لوړ_Frequency_Timer_Ticks = 0;
}
/*
 * For Xilinx implementation this function returns the global counter used for
 * run time task stats calculation.
 * It is called by FreeRTOS kernel task handling logic.
 */
uint32_t x_GET_پرلپسې_وخت_COUNTER_ارزښت (فراغ)
{
	أرجع ul_لوړ_Frequency_Timer_Ticks;
}
#د_که_پای
/*-----------------------------------------------------------*/
