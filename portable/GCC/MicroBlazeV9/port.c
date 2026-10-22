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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Standard includes. */
#अन्तर्भाव <string.h>

/* Hardware includes. */
#अन्तर्भाव <xintc_i.h>
#अन्तर्भाव <xil_exception.h>
#अन्तर्भाव <microblaze_exceptions_g.h>
#अन्तर्भाव <microblaze_instructions.h>

/* Tasks are started with a critical section nesting of 0 - however, prior to
 * the scheduler being commenced interrupts should not be enabled, so the critical
 * nesting variable is initialised to a non-zero value. */
#परिभाषय पत्तनम्_INITIAL_NESTING_मानम्    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#परिभाषय पत्तनम्_MSR_IE                   ( 0x02U )
#परिभाषय पत्तनम्_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#परिभाषय पत्तनम्_INITIAL_FSR              ( 0U )
/*
 * Global counter used for calculation of run time statistics of tasks.
 * Defined only when the relevant option is turned on
 */
#यदि (config_GENERATE_सततम्_TIME_STATS==1)
    चञ्चल uint32_t ul_उच्चः_Frequency_Timer_Ticks;
#यदि_अन्तः

/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
स्थिर int32_t prv_Initialise_व्यवधानम्_Controller( शून्य );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
स्थिर int32_t prv_Ensure_व्यवधानम्_Controller_Is_Initialised( शून्य );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
चञ्चल UBaseType_t uxCriticalNesting = पत्तनम्_INITIAL_NESTING_मानम्;

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
चञ्चल uint32_t ulTaskSwitchRequested = 0UL;

/* The instance of the interrupt controller used by this port.  This is required
 * by the Xilinx library API functions. */
स्थिर XIntc x_व्यवधानम्_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
#यदि ( पत्तनम्_HAS_राशिः_अतिप्रवाहः_CHECKING == 1 )
    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         राशिः_Type_t * px_अन्तः_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters )
#अन्यथा
    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters )
#यदि_अन्तः
{
    बाह्य शून्य *SDA2_आधारः;
    बाह्य शून्य *SDA_आधारः;
    ध्रुव UINTPTR ulR2 = ( UINTPTR ) &SDA2_आधारः;
    ध्रुव UINTPTR ulR13 = ( UINTPTR ) &SDA_आधारः;

    बाह्य शून्य _start1( शून्य );

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00000000;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00000000;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00000000;
    px_शिखरम्_सम्बन्धि_राशिः--;

    #यदि ( पत्तनम्_HAS_राशिः_अतिप्रवाहः_CHECKING == 1 )
        /* Store the stack limits. */
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( px_शिखरम्_सम्बन्धि_राशिः + 3 );
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_अन्तः_सम्बन्धि_राशिः;
        px_शिखरम्_सम्बन्धि_राशिः--;
    #यदि_अन्तः

    #यदि ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_FSR;
        px_शिखरम्_सम्बन्धि_राशिः--;
    #यदि_अन्तः

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_शिखरम्_सम्बन्धि_राशिः = mfmsr() & ~पत्तनम्_MSR_IE;

    #यदि ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_शिखरम्_सम्बन्धि_राशिः |= पत्तनम्_MSR_EE;
    }
    #यदि_अन्तः

    px_शिखरम्_सम्बन्धि_राशिः--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #यदि_परिभाषितम् पत्तनम्_PRE_आरोपय_राशिः_FOR_DEBUGGING
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06;   /* R6 - other parameters and temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07;   /* R7 - other parameters and temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) रिक्त;   /* R8 - other parameters and temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09;   /* R9 - other parameters and temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x0a;   /* R10 - other parameters and temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x0b;   /* R11 - temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x0c;   /* R12 - temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
    #अन्यथा /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_शिखरम्_सम्बन्धि_राशिः -= 8;
    #यदि_अन्तः /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ulR13;   /* R13 - read/write small data area. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;  /* R14 - return address for interrupt. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) _start1; /* R15 - return address for subroutine. */

    #यदि_परिभाषितम् पत्तनम्_PRE_आरोपय_राशिः_FOR_DEBUGGING
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10;   /* R16 - return address for trap (debugger). */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11;   /* R17 - return address for exceptions, if configured. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12;   /* R18 - reserved for assembler and compiler temporaries. */
        px_शिखरम्_सम्बन्धि_राशिः--;
    #अन्यथा
        px_शिखरम्_सम्बन्धि_राशिः -= 4;
    #यदि_अन्तः

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00;   /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #यदि_परिभाषितम् पत्तनम्_PRE_आरोपय_राशिः_FOR_DEBUGGING
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x14;   /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x15;   /* R21 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x16;   /* R22 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x17;   /* R23 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x18;   /* R24 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x19;   /* R25 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x1a;   /* R26 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x1b;   /* R27 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x1c;   /* R28 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x1d;   /* R29 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x1e;   /* R30 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x1f;   /* R31 - must be saved across function calls. Callee-save. */
        px_शिखरम्_सम्बन्धि_राशिः--;
    #अन्यथा /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_शिखरम्_सम्बन्धि_राशिः -= 13;
    #यदि_अन्तः /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    बाह्य शून्य ( v_पत्तनम्_Start_First_Task )( शून्य );
    बाह्य UINTPTR राशिः_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_सज्जता_Timer_व्यवधानम्();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( UINTPTR * ) राशिः_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_पत्तनम्_Start_First_Task();

    /* Should not get here as the tasks are now running! */
    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
शून्य v_पत्तनम्_Yield( शून्य )
{
    बाह्य शून्य VPortYieldASM( शून्य );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    पत्तनम्_ENTER_CRITICAL();
	  {
		    /* Jump directly to the yield function to ensure there is no
		    * compiler generated prologue code. */
        #यदि_परिभाषितम् __arch64__
            asm चञ्चल (	"brealid r14, VPortYieldASM		\n\t" \
        		         				"or r0, r0, r0					      \n\t" );
        #अन्यथा
         		asm चञ्चल (	"bralid r14, VPortYieldASM		\n\t" \
				                 		"or r0, r0, r0					      \n\t" );
        #यदि_अन्तः
  	}
	  पत्तनम्_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enable_व्यवधानम्( uint8_t uc_व्यवधानम्_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_व्यवधानम्_Controller_Is_Initialised();

    यदि( lReturn == pdPASS )
    {
        /* Critical section protects read/modify/writer operation inside
         * XIntc_Enable(). */
        पत्तनम्_ENTER_CRITICAL();
        {
            XIntc_Enable( &x_व्यवधानम्_Controller_Instance, uc_व्यवधानम्_ID );
        }
        पत्तनम्_EXIT_CRITICAL();
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Disable_व्यवधानम्( uint8_t uc_व्यवधानम्_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_व्यवधानम्_Controller_Is_Initialised();

    यदि( lReturn == pdPASS )
    {
        XIntc_Disable( &x_व्यवधानम्_Controller_Instance, uc_व्यवधानम्_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Install_व्यवधानम्_Handler( uint8_t uc_व्यवधानम्_ID,
                                         XInterruptHandler pxHandler,
                                         शून्य * pv_Call_पृष्ठभागः_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_व्यवधानम्_Controller_Is_Initialised();

    यदि( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_व्यवधानम्_Controller_Instance, uc_व्यवधानम्_ID, pxHandler, pv_Call_पृष्ठभागः_Ref );
    }

    यदि( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    प्रत्यागम lReturn;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Remove_व्यवधानम्_Handler( uint8_t uc_व्यवधानम्_ID )
{
    int32_t lReturn;

    /* An API function is provided to remove an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_व्यवधानम्_Controller_Is_Initialised();

    यदि( lReturn == pdPASS )
    {
        XIntc_Disconnect( &x_व्यवधानम्_Controller_Instance, uc_व्यवधानम्_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

स्थिर int32_t prv_Ensure_व्यवधानम्_Controller_Is_Initialised( शून्य )
{
    स्थिर int32_t l_व्यवधानम्_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    यदि( l_व्यवधानम्_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_व्यवधानम्_Controller();

        यदि( lReturn == pdPASS )
        {
            l_व्यवधानम्_Controller_Initialised = pdTRUE;
        }
    }
    अन्यथा
    {
        lReturn = pdPASS;
    }

    प्रत्यागम lReturn;
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.  This is the handler that the application
 * defined callback function vApplicationSetupTimerInterrupt() should install.
 */
शून्य v_पत्तनम्_Tick_ISR( शून्य * pv_अप्रयुक्तम् )
{
    बाह्य शून्य v_Application_Clear_Timer_व्यवधानम्( शून्य );

	/* Ensure the unused parameter does not generate a compiler warning. */
	( शून्य ) pv_अप्रयुक्तम्;

    /* The Xilinx implementation of generating run time task stats uses the same timer used for generating
	   * FreeRTOS ticks. In case user decides to generate run time stats the tick handler is called more
	   * frequently (10 times faster). The timer    ick handler uses logic to handle the same. It handles
	   * the FreeRTOS tick once per 10 interrupts.
	   * For handling generation of run time stats, it increments a pre-defined counter every time the
	   * interrupt handler executes. */
#यदि (config_GENERATE_सततम्_TIME_STATS == 1)
    ul_उच्चः_Frequency_Timer_Ticks++;
    यदि (!(ul_उच्चः_Frequency_Timer_Ticks % 10))
#यदि_अन्तः
    {
        /* This port uses an application defined callback function to clear the tick
         * interrupt because the kernel will run on lots of different MicroBlaze and
         * FPGA configurations - not all of which will have the same timer peripherals
         * defined or available.  An example definition of
         * vApplicationClearTimerInterrupt() is provided in the official demo
         * application that accompanies this port. */
        v_Application_Clear_Timer_व्यवधानम्();

        /* Increment the RTOS tick - this might cause a task to unblock. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Force vTaskSwitchContext() to be called as the interrupt exits. */
            ulTaskSwitchRequested = 1;
        }
    }
}
/*-----------------------------------------------------------*/

स्थिर int32_t prv_Initialise_व्यवधानम्_Controller( शून्य )
{
    int32_t l_स्थितिः;

    l_स्थितिः = XIntc_Initialize( &x_व्यवधानम्_Controller_Instance, config_व्यवधानम्_CONTROLLER_गन्तव्यम्_USE );

    यदि( l_स्थितिः == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_समुच्चयः_Intr_Svc_Option( x_व्यवधानम्_Controller_Instance.आधारः_स्थानाङ्कः, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #यदि ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_पत्तनम्_Exceptions_Install_Handlers();
        }
        #यदि_अन्तः /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_स्थितिः = XIntc_Start( &x_व्यवधानम्_Controller_Instance, XIN_REAL_बहुलकम् );

        यदि( l_स्थितिः == XST_SUCCESS )
        {
            l_स्थितिः = pdPASS;
        }
        अन्यथा
        {
            l_स्थितिः = pdFAIL;
        }
    }

    configASSERT( l_स्थितिः == pdPASS );

    प्रत्यागम l_स्थितिः;
}

#यदि( config_GENERATE_सततम्_TIME_STATS == 1 )
/*
 * For Xilinx implementation this is a dummy function that does a redundant operation
 * of zeroing out the global counter.
 * It is called by FreeRTOS kernel.
 */
शून्य x_CONFIGURE_TIMER_FOR_सततम्_TIME_STATS (शून्य)
{
	ul_उच्चः_Frequency_Timer_Ticks = 0;
}
/*
 * For Xilinx implementation this function returns the global counter used for
 * run time task stats calculation.
 * It is called by FreeRTOS kernel task handling logic.
 */
uint32_t x_GET_सततम्_TIME_गणक_मानम् (शून्य)
{
	प्रत्यागम ul_उच्चः_Frequency_Timer_Ticks;
}
#यदि_अन्तः
/*-----------------------------------------------------------*/
