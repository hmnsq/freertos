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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

/* Hardware includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <xintc_i.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xil_exception.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <microblaze_exceptions_g.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <microblaze_instructions.h>

/* Tasks are started with a critical section nesting of 0 - however, prior to
 * the scheduler being commenced interrupts should not be enabled, so the critical
 * nesting variable is initialised to a non-zero value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_NESTING_ਮੁੱਲ    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MSR_IE                   ( 0x02U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_FSR              ( 0U )
/*
 * Global counter used for calculation of run time statistics of tasks.
 * Defined only when the relevant option is turned on
 */
#ਜੇ (config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS==1)
    ਅਸਥਿਰ uint32_t ul_ਉੱਚਾ_Frequency_Timer_Ticks;
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ਸਥਿਰ int32_t prv_Initialise_ਰੁਕਾਵਟ_Controller( ਖਾਲੀ );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ਸਥਿਰ int32_t prv_Ensure_ਰੁਕਾਵਟ_Controller_Is_Initialised( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
ਅਸਥਿਰ UBaseType_t uxCriticalNesting = ਪੋਰਟ_INITIAL_NESTING_ਮੁੱਲ;

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
ਅਸਥਿਰ uint32_t ulTaskSwitchRequested = 0UL;

/* The instance of the interrupt controller used by this port.  This is required
 * by the Xilinx library API functions. */
ਸਥਿਰ XIntc x_ਰੁਕਾਵਟ_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
#ਜੇ ( ਪੋਰਟ_HAS_ਢੇਰ_ਉਛਾਲ_CHECKING == 1 )
    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         ਢੇਰ_Type_t * px_ਸਿਰਾ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters )
#ਨਹੀਂਤਾਂ
    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters )
#ਜੇ_ਅੰਤ
{
    ਬਾਹਰੀ ਖਾਲੀ *SDA2_ਅਧਾਰ;
    ਬਾਹਰੀ ਖਾਲੀ *SDA_ਅਧਾਰ;
    ਅਚਲ UINTPTR ulR2 = ( UINTPTR ) &SDA2_ਅਧਾਰ;
    ਅਚਲ UINTPTR ulR13 = ( UINTPTR ) &SDA_ਅਧਾਰ;

    ਬਾਹਰੀ ਖਾਲੀ _start1( ਖਾਲੀ );

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00000000;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00000000;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00000000;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    #ਜੇ ( ਪੋਰਟ_HAS_ਢੇਰ_ਉਛਾਲ_CHECKING == 1 )
        /* Store the stack limits. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ + 3 );
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਸਿਰਾ_ਦਾ_ਢੇਰ;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਜੇ_ਅੰਤ

    #ਜੇ ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_FSR;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਜੇ_ਅੰਤ

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = mfmsr() & ~ਪੋਰਟ_MSR_IE;

    #ਜੇ ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ |= ਪੋਰਟ_MSR_EE;
    }
    #ਜੇ_ਅੰਤ

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_PRE_ਲੱਦੋ_ਢੇਰ_FOR_DEBUGGING
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06;   /* R6 - other parameters and temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07;   /* R7 - other parameters and temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;   /* R8 - other parameters and temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09;   /* R9 - other parameters and temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0a;   /* R10 - other parameters and temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0b;   /* R11 - temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0c;   /* R12 - temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਨਹੀਂਤਾਂ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 8;
    #ਜੇ_ਅੰਤ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ulR13;   /* R13 - read/write small data area. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;  /* R14 - return address for interrupt. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) _start1; /* R15 - return address for subroutine. */

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_PRE_ਲੱਦੋ_ਢੇਰ_FOR_DEBUGGING
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10;   /* R16 - return address for trap (debugger). */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11;   /* R17 - return address for exceptions, if configured. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12;   /* R18 - reserved for assembler and compiler temporaries. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਨਹੀਂਤਾਂ
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 4;
    #ਜੇ_ਅੰਤ

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;   /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_PRE_ਲੱਦੋ_ਢੇਰ_FOR_DEBUGGING
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x14;   /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x15;   /* R21 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x16;   /* R22 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x17;   /* R23 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x18;   /* R24 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x19;   /* R25 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1a;   /* R26 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1b;   /* R27 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1c;   /* R28 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1d;   /* R29 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1e;   /* R30 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1f;   /* R31 - must be saved across function calls. Callee-save. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਨਹੀਂਤਾਂ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 13;
    #ਜੇ_ਅੰਤ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ ( v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task )( ਖਾਲੀ );
    ਬਾਹਰੀ UINTPTR ਢੇਰ_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( UINTPTR * ) ਢੇਰ_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here as the tasks are now running! */
    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ VPortYieldASM( ਖਾਲੀ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    ਪੋਰਟ_ENTER_CRITICAL();
	  {
		    /* Jump directly to the yield function to ensure there is no
		    * compiler generated prologue code. */
        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __arch64__
            asm ਅਸਥਿਰ (	"brealid r14, VPortYieldASM		\n\t" \
        		         				"or r0, r0, r0					      \n\t" );
        #ਨਹੀਂਤਾਂ
         		asm ਅਸਥਿਰ (	"bralid r14, VPortYieldASM		\n\t" \
				                 		"or r0, r0, r0					      \n\t" );
        #ਜੇ_ਅੰਤ
  	}
	  ਪੋਰਟ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enable_ਰੁਕਾਵਟ( uint8_t uc_ਰੁਕਾਵਟ_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_ਰੁਕਾਵਟ_Controller_Is_Initialised();

    ਜੇ( lReturn == pdPASS )
    {
        /* Critical section protects read/modify/writer operation inside
         * XIntc_Enable(). */
        ਪੋਰਟ_ENTER_CRITICAL();
        {
            XIntc_Enable( &x_ਰੁਕਾਵਟ_Controller_Instance, uc_ਰੁਕਾਵਟ_ID );
        }
        ਪੋਰਟ_EXIT_CRITICAL();
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Disable_ਰੁਕਾਵਟ( uint8_t uc_ਰੁਕਾਵਟ_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_ਰੁਕਾਵਟ_Controller_Is_Initialised();

    ਜੇ( lReturn == pdPASS )
    {
        XIntc_Disable( &x_ਰੁਕਾਵਟ_Controller_Instance, uc_ਰੁਕਾਵਟ_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Install_ਰੁਕਾਵਟ_Handler( uint8_t uc_ਰੁਕਾਵਟ_ID,
                                         XInterruptHandler pxHandler,
                                         ਖਾਲੀ * pv_Call_ਪਿੱਠ_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_ਰੁਕਾਵਟ_Controller_Is_Initialised();

    ਜੇ( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_ਰੁਕਾਵਟ_Controller_Instance, uc_ਰੁਕਾਵਟ_ID, pxHandler, pv_Call_ਪਿੱਠ_Ref );
    }

    ਜੇ( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    ਵਾਪਸ lReturn;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Remove_ਰੁਕਾਵਟ_Handler( uint8_t uc_ਰੁਕਾਵਟ_ID )
{
    int32_t lReturn;

    /* An API function is provided to remove an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_ਰੁਕਾਵਟ_Controller_Is_Initialised();

    ਜੇ( lReturn == pdPASS )
    {
        XIntc_Disconnect( &x_ਰੁਕਾਵਟ_Controller_Instance, uc_ਰੁਕਾਵਟ_ID );
    }

    configASSERT( lReturn == pdPASS );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ int32_t prv_Ensure_ਰੁਕਾਵਟ_Controller_Is_Initialised( ਖਾਲੀ )
{
    ਸਥਿਰ int32_t l_ਰੁਕਾਵਟ_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    ਜੇ( l_ਰੁਕਾਵਟ_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_ਰੁਕਾਵਟ_Controller();

        ਜੇ( lReturn == pdPASS )
        {
            l_ਰੁਕਾਵਟ_Controller_Initialised = pdTRUE;
        }
    }
    ਨਹੀਂਤਾਂ
    {
        lReturn = pdPASS;
    }

    ਵਾਪਸ lReturn;
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.  This is the handler that the application
 * defined callback function vApplicationSetupTimerInterrupt() should install.
 */
ਖਾਲੀ v_ਪੋਰਟ_Tick_ISR( ਖਾਲੀ * pv_ਅਣਵਰਤਿਆ )
{
    ਬਾਹਰੀ ਖਾਲੀ v_Application_Clear_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

	/* Ensure the unused parameter does not generate a compiler warning. */
	( ਖਾਲੀ ) pv_ਅਣਵਰਤਿਆ;

    /* The Xilinx implementation of generating run time task stats uses the same timer used for generating
	   * FreeRTOS ticks. In case user decides to generate run time stats the tick handler is called more
	   * frequently (10 times faster). The timer    ick handler uses logic to handle the same. It handles
	   * the FreeRTOS tick once per 10 interrupts.
	   * For handling generation of run time stats, it increments a pre-defined counter every time the
	   * interrupt handler executes. */
#ਜੇ (config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1)
    ul_ਉੱਚਾ_Frequency_Timer_Ticks++;
    ਜੇ (!(ul_ਉੱਚਾ_Frequency_Timer_Ticks % 10))
#ਜੇ_ਅੰਤ
    {
        /* This port uses an application defined callback function to clear the tick
         * interrupt because the kernel will run on lots of different MicroBlaze and
         * FPGA configurations - not all of which will have the same timer peripherals
         * defined or available.  An example definition of
         * vApplicationClearTimerInterrupt() is provided in the official demo
         * application that accompanies this port. */
        v_Application_Clear_Timer_ਰੁਕਾਵਟ();

        /* Increment the RTOS tick - this might cause a task to unblock. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Force vTaskSwitchContext() to be called as the interrupt exits. */
            ulTaskSwitchRequested = 1;
        }
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ int32_t prv_Initialise_ਰੁਕਾਵਟ_Controller( ਖਾਲੀ )
{
    int32_t l_ਸਥਿਤੀ;

    l_ਸਥਿਤੀ = XIntc_Initialize( &x_ਰੁਕਾਵਟ_Controller_Instance, config_ਰੁਕਾਵਟ_CONTROLLER_ਮੰਜ਼ਿਲ_USE );

    ਜੇ( l_ਸਥਿਤੀ == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_ਸੈੱਟ_Intr_Svc_Option( x_ਰੁਕਾਵਟ_Controller_Instance.ਅਧਾਰ_ਪਤਾ, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #ਜੇ ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_ਪੋਰਟ_Exceptions_Install_Handlers();
        }
        #ਜੇ_ਅੰਤ /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_ਸਥਿਤੀ = XIntc_ਸ਼ੁਰੂ( &x_ਰੁਕਾਵਟ_Controller_Instance, XIN_REAL_ਬਹੁਲਕ );

        ਜੇ( l_ਸਥਿਤੀ == XST_SUCCESS )
        {
            l_ਸਥਿਤੀ = pdPASS;
        }
        ਨਹੀਂਤਾਂ
        {
            l_ਸਥਿਤੀ = pdFAIL;
        }
    }

    configASSERT( l_ਸਥਿਤੀ == pdPASS );

    ਵਾਪਸ l_ਸਥਿਤੀ;
}

#ਜੇ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )
/*
 * For Xilinx implementation this is a dummy function that does a redundant operation
 * of zeroing out the global counter.
 * It is called by FreeRTOS kernel.
 */
ਖਾਲੀ x_CONFIGURE_TIMER_FOR_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS (ਖਾਲੀ)
{
	ul_ਉੱਚਾ_Frequency_Timer_Ticks = 0;
}
/*
 * For Xilinx implementation this function returns the global counter used for
 * run time task stats calculation.
 * It is called by FreeRTOS kernel task handling logic.
 */
uint32_t x_GET_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_ਮੁੱਲ (ਖਾਲੀ)
{
	ਵਾਪਸ ul_ਉੱਚਾ_Frequency_Timer_Ticks;
}
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/
