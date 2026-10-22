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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Standard includes. */
#شامل <string.h>

/* Hardware includes. */
#شامل <xintc_i.h>
#شامل <xil_exception.h>
#شامل <microblaze_exceptions_g.h>

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
/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ساکن int32_t prv_Initialise_مداخلت_Controller( خالی );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ساکن int32_t prv_Ensure_مداخلت_Controller_Is_Initialised( خالی );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متلون UBaseType_t uxCriticalNesting = پورٹ_INITIAL_NESTING_قدر;

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
متلون uint32_t ulTaskSwitchRequested = 0UL;

/* The instance of the interrupt controller used by this port.  This is required
 * by the Xilinx library API functions. */
ساکن XIntc x_مداخلت_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    خارجی خالی * SDA2_بنیاد;
    خارجی خالی * SDA_بنیاد;
    ثابت uint32_t ulR2 = ( uint32_t ) &SDA2_بنیاد;
    ثابت uint32_t ulR13 = ( uint32_t ) &SDA_بنیاد;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;
    px_چوٹی_کا_ڈھیر--;

    #اگر ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_FSR;
        px_چوٹی_کا_ڈھیر--;
    #اگر_ختم

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_چوٹی_کا_ڈھیر = mfmsr() & ~پورٹ_MSR_IE;

    #اگر ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_چوٹی_کا_ڈھیر |= پورٹ_MSR_EE;
    }
    #اگر_ختم

    px_چوٹی_کا_ڈھیر--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #اگر_تعریف_شدہ پورٹ_PRE_بھرو_ڈھیر_FOR_DEBUGGING
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06; /* R6 - other parameters and temporaries.  Used as the return address from vPortTaskEntryPoint. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07; /* R7 - other parameters and temporaries. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08; /* R8 - other parameters and temporaries. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09; /* R9 - other parameters and temporaries. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0a; /* R10 - other parameters and temporaries. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0b; /* R11 - temporaries. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0c; /* R12 - temporaries. */
        px_چوٹی_کا_ڈھیر--;
    #ورنہ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_چوٹی_کا_ڈھیر -= 8;
    #اگر_ختم /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ulR13;  /* R13 - read/write small data area. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز; /* R14 - return address for interrupt. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) تہی;   /* R15 - return address for subroutine. */

    #اگر_تعریف_شدہ پورٹ_PRE_بھرو_ڈھیر_FOR_DEBUGGING
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10; /* R16 - return address for trap (debugger). */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11; /* R17 - return address for exceptions, if configured. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12; /* R18 - reserved for assembler and compiler temporaries. */
        px_چوٹی_کا_ڈھیر--;
    #ورنہ
        px_چوٹی_کا_ڈھیر -= 4;
    #اگر_ختم

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00; /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #اگر_تعریف_شدہ پورٹ_PRE_بھرو_ڈھیر_FOR_DEBUGGING
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x14; /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x15; /* R21 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x16; /* R22 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x17; /* R23 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x18; /* R24 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x19; /* R25 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1a; /* R26 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1b; /* R27 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1c; /* R28 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1d; /* R29 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1e; /* R30 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
        *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x1f; /* R31 - must be saved across function calls. Callee-save. */
        px_چوٹی_کا_ڈھیر--;
    #ورنہ /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_چوٹی_کا_ڈھیر -= 13;
    #اگر_ختم /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    خارجی خالی( v_پورٹ_آغاز_پہلا_Task )( خالی );
    خارجی uint32_t ڈھیر_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_تیاری_Timer_مداخلت();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( uint32_t * ) ڈھیر_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_پورٹ_آغاز_پہلا_Task();

    /* Should not get here as the tasks are now running! */
    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
خالی v_پورٹ_Yield( خالی )
{
    خارجی خالی VPortYieldASM( خالی );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورٹ_ENTER_CRITICAL();
    {
        /* Jump directly to the yield function to ensure there is no
         * compiler generated prologue code. */
        asm متلون ( "bralid r14, VPortYieldASM      \n\t" \
                       "or r0, r0, r0                  \n\t" );
    }
    پورٹ_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enable_مداخلت( uint8_t uc_مداخلت_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_مداخلت_Controller_Is_Initialised();

    اگر( lReturn == pdPASS )
    {
        XIntc_Enable( &x_مداخلت_Controller_Instance, uc_مداخلت_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Disable_مداخلت( uint8_t uc_مداخلت_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_مداخلت_Controller_Is_Initialised();

    اگر( lReturn == pdPASS )
    {
        XIntc_Disable( &x_مداخلت_Controller_Instance, uc_مداخلت_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_Install_مداخلت_Handler( uint8_t uc_مداخلت_ID,
                                         XInterruptHandler pxHandler,
                                         خالی * pv_Call_عقب_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_مداخلت_Controller_Is_Initialised();

    اگر( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_مداخلت_Controller_Instance, uc_مداخلت_ID, pxHandler, pv_Call_عقب_Ref );
    }

    اگر( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    واپس lReturn;
}
/*-----------------------------------------------------------*/

ساکن int32_t prv_Ensure_مداخلت_Controller_Is_Initialised( خالی )
{
    ساکن int32_t l_مداخلت_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    اگر( l_مداخلت_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_مداخلت_Controller();

        اگر( lReturn == pdPASS )
        {
            l_مداخلت_Controller_Initialised = pdTRUE;
        }
    }
    ورنہ
    {
        lReturn = pdPASS;
    }

    واپس lReturn;
}
/*-----------------------------------------------------------*/

/*
 * Handler for the timer interrupt.  This is the handler that the application
 * defined callback function vApplicationSetupTimerInterrupt() should install.
 */
خالی v_پورٹ_Tick_ISR( خالی * pv_غیر_مستعمل )
{
    خارجی خالی v_Application_Clear_Timer_مداخلت( خالی );

    /* Ensure the unused parameter does not generate a compiler warning. */
    ( خالی ) pv_غیر_مستعمل;

    /* This port uses an application defined callback function to clear the tick
     * interrupt because the kernel will run on lots of different MicroBlaze and
     * FPGA configurations - not all of which will have the same timer peripherals
     * defined or available.  An example definition of
     * vApplicationClearTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_Clear_Timer_مداخلت();

    /* Increment the RTOS tick - this might cause a task to unblock. */
    اگر( xTaskIncrementTick() != pdFALSE )
    {
        /* Force vTaskSwitchContext() to be called as the interrupt exits. */
        ulTaskSwitchRequested = 1;
    }
}
/*-----------------------------------------------------------*/

ساکن int32_t prv_Initialise_مداخلت_Controller( خالی )
{
    int32_t l_حالت;

    l_حالت = XIntc_Initialize( &x_مداخلت_Controller_Instance, config_مداخلت_CONTROLLER_مقصد_USE );

    اگر( l_حالت == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_سیٹ_Intr_Svc_Option( x_مداخلت_Controller_Instance.بنیاد_پتہ, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #اگر ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_پورٹ_Exceptions_Install_Handlers();
        }
        #اگر_ختم /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_حالت = XIntc_آغاز( &x_مداخلت_Controller_Instance, XIN_REAL_منوال );

        اگر( l_حالت == XST_SUCCESS )
        {
            l_حالت = pdPASS;
        }
        ورنہ
        {
            l_حالت = pdFAIL;
        }
    }

    configASSERT( l_حالت == pdPASS );

    واپس l_حالت;
}
/*-----------------------------------------------------------*/
