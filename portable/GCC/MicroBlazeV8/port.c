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
#تعریف_کن پورت_INITIAL_NESTING_مقدار    ( 0xff )

/* The bit within the MSR register that enabled/disables interrupts and
 * exceptions respectively. */
#تعریف_کن پورت_MSR_IE                   ( 0x02U )
#تعریف_کن پورت_MSR_EE                   ( 0x100U )

/* If the floating point unit is included in the MicroBlaze build, then the
 * FSR register is saved as part of the task context.  portINITIAL_FSR is the value
 * given to the FSR register when the initial context is set up for a task being
 * created. */
#تعریف_کن پورت_INITIAL_FSR              ( 0U )
/*-----------------------------------------------------------*/

/*
 * Initialise the interrupt controller instance.
 */
ساكن int32_t prv_Initialise_وقفه_Controller( فراغ );

/* Ensure the interrupt controller instance variable is initialised before it is
 * used, and that the initialisation only happens once.
 */
ساكن int32_t prv_Ensure_وقفه_Controller_Is_Initialised( فراغ );

/*-----------------------------------------------------------*/

/* Counts the nesting depth of calls to portENTER_CRITICAL().  Each task
 * maintains its own count, so this variable is saved as part of the task
 * context. */
متطاير UBaseType_t uxCriticalNesting = پورت_INITIAL_NESTING_مقدار;

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
ساكن XIntc x_وقفه_Controller_Instance;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been made.
 *
 * See the portable.h header file.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    خارجي فراغ * SDA2_پایه;
    خارجي فراغ * SDA_پایه;
    ثابت uint32_t ulR2 = ( uint32_t ) &SDA2_پایه;
    ثابت uint32_t ulR13 = ( uint32_t ) &SDA_پایه;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is essential for the Microblaze port and these lines must
     * not be omitted. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00000000;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00000000;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00000000;
    px_بالاترین_از_پشته--;

    #إذا ( XPAR_MICROBLAZE_USE_FPU != 0 )
        /* The FSR value placed in the initial task context is just 0. */
        *px_بالاترین_از_پشته = پورت_INITIAL_FSR;
        px_بالاترین_از_پشته--;
    #پایان_اگر

    /* The MSR value placed in the initial task context should have interrupts
     * disabled.  Each task will enable interrupts automatically when it enters
     * the running state for the first time. */
    *px_بالاترین_از_پشته = mfmsr() & ~پورت_MSR_IE;

    #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 )
    {
        /* Ensure exceptions are enabled for the task. */
        *px_بالاترین_از_پشته |= پورت_MSR_EE;
    }
    #پایان_اگر

    px_بالاترین_از_پشته--;

    /* First stack an initial value for the critical section nesting.  This
     * is initialised to zero. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00;

    /* R0 is always zero. */
    /* R1 is the SP. */

    /* Place an initial value for all the general purpose registers. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ulR2;         /* R2 - read only small data area. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03;         /* R3 - return values and temporaries. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04;         /* R4 - return values and temporaries. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R5 contains the function call parameters. */

    #اگر_تعریف_شده پورت_PRE_بارگیری_پشته_FOR_DEBUGGING
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06; /* R6 - other parameters and temporaries.  Used as the return address from vPortTaskEntryPoint. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07; /* R7 - other parameters and temporaries. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08; /* R8 - other parameters and temporaries. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09; /* R9 - other parameters and temporaries. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0a; /* R10 - other parameters and temporaries. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0b; /* R11 - temporaries. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x0c; /* R12 - temporaries. */
        px_بالاترین_از_پشته--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_بالاترین_از_پشته -= 8;
    #پایان_اگر /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    *px_بالاترین_از_پشته = ( پشته_Type_t ) ulR13;  /* R13 - read/write small data area. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد; /* R14 - return address for interrupt. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) عدم;   /* R15 - return address for subroutine. */

    #اگر_تعریف_شده پورت_PRE_بارگیری_پشته_FOR_DEBUGGING
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10; /* R16 - return address for trap (debugger). */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11; /* R17 - return address for exceptions, if configured. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12; /* R18 - reserved for assembler and compiler temporaries. */
        px_بالاترین_از_پشته--;
    #وإلا
        px_بالاترین_از_پشته -= 4;
    #پایان_اگر

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00; /* R19 - must be saved across function calls. Callee-save.  Seems to be interpreted as the frame pointer. */

    #اگر_تعریف_شده پورت_PRE_بارگیری_پشته_FOR_DEBUGGING
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x14; /* R20 - reserved for storing a pointer to the Global Offset Table (GOT) in Position Independent Code (PIC). Non-volatile in non-PIC code. Must be saved across function calls. Callee-save.  Not used by FreeRTOS. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x15; /* R21 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x16; /* R22 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x17; /* R23 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x18; /* R24 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x19; /* R25 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1a; /* R26 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1b; /* R27 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1c; /* R28 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1d; /* R29 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1e; /* R30 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
        *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x1f; /* R31 - must be saved across function calls. Callee-save. */
        px_بالاترین_از_پشته--;
    #وإلا /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */
        px_بالاترین_از_پشته -= 13;
    #پایان_اگر /* ifdef portPRE_LOAD_STACK_FOR_DEBUGGING */

    /* Return a pointer to the top of the stack that has been generated so this
     * can be stored in the task control block for the task. */
    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    خارجي فراغ( v_پورت_شروع_اولی_Task )( فراغ );
    خارجي uint32_t پشته_3[];

    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called.
     *
     * This port uses an application defined callback function to install the tick
     * interrupt handler because the kernel will run on lots of different
     * MicroBlaze and FPGA configurations - not all of which will have the same
     * timer peripherals defined or available.  An example definition of
     * vApplicationSetupTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_راهاندازی_Timer_وقفه();

    /* Reuse the stack from main() as the stack for the interrupts/exceptions. */
    pulISRStack = ( uint32_t * ) پشته_3;

    /* Ensure there is enough space for the functions called from the interrupt
     * service routines to write back into the stack frame of the caller. */
    pulISRStack -= 2;

    /* Restore the context of the first task that is going to run.  From here
     * on, the created tasks will be executing. */
    v_پورت_شروع_اولی_Task();

    /* Should not get here as the tasks are now running! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
فراغ v_پورت_Yield( فراغ )
{
    خارجي فراغ VPortYieldASM( فراغ );

    /* Perform the context switch in a critical section to assure it is
     * not interrupted by the tick ISR.  It is not a problem to do this as
     * each task maintains its own interrupt status. */
    پورت_ENTER_CRITICAL();
    {
        /* Jump directly to the yield function to ensure there is no
         * compiler generated prologue code. */
        asm متطاير ( "bralid r14, VPortYieldASM      \n\t" \
                       "or r0, r0, r0                  \n\t" );
    }
    پورت_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enable_وقفه( uint8_t uc_وقفه_ID )
{
    int32_t lReturn;

    /* An API function is provided to enable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_وقفه_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Enable( &x_وقفه_Controller_Instance, uc_وقفه_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Disable_وقفه( uint8_t uc_وقفه_ID )
{
    int32_t lReturn;

    /* An API function is provided to disable an interrupt in the interrupt
     * controller because the interrupt controller instance variable is private
     * to this file. */
    lReturn = prv_Ensure_وقفه_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        XIntc_Disable( &x_وقفه_Controller_Instance, uc_وقفه_ID );
    }

    configASSERT( lReturn );
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_Install_وقفه_Handler( uint8_t uc_وقفه_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_پشت_Ref )
{
    int32_t lReturn;

    /* An API function is provided to install an interrupt handler because the
     * interrupt controller instance variable is private to this file. */

    lReturn = prv_Ensure_وقفه_Controller_Is_Initialised();

    إذا( lReturn == pdPASS )
    {
        lReturn = XIntc_Connect( &x_وقفه_Controller_Instance, uc_وقفه_ID, pxHandler, pv_Call_پشت_Ref );
    }

    إذا( lReturn == XST_SUCCESS )
    {
        lReturn = pdPASS;
    }

    configASSERT( lReturn == pdPASS );

    أرجع lReturn;
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Ensure_وقفه_Controller_Is_Initialised( فراغ )
{
    ساكن int32_t l_وقفه_Controller_Initialised = pdFALSE;
    int32_t lReturn;

    /* Ensure the interrupt controller instance variable is initialised before
     * it is used, and that the initialisation only happens once. */
    إذا( l_وقفه_Controller_Initialised != pdTRUE )
    {
        lReturn = prv_Initialise_وقفه_Controller();

        إذا( lReturn == pdPASS )
        {
            l_وقفه_Controller_Initialised = pdTRUE;
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
فراغ v_پورت_Tick_ISR( فراغ * pv_استفادهنشده )
{
    خارجي فراغ v_Application_Clear_Timer_وقفه( فراغ );

    /* Ensure the unused parameter does not generate a compiler warning. */
    ( فراغ ) pv_استفادهنشده;

    /* This port uses an application defined callback function to clear the tick
     * interrupt because the kernel will run on lots of different MicroBlaze and
     * FPGA configurations - not all of which will have the same timer peripherals
     * defined or available.  An example definition of
     * vApplicationClearTimerInterrupt() is provided in the official demo
     * application that accompanies this port. */
    v_Application_Clear_Timer_وقفه();

    /* Increment the RTOS tick - this might cause a task to unblock. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        /* Force vTaskSwitchContext() to be called as the interrupt exits. */
        ulTaskSwitchRequested = 1;
    }
}
/*-----------------------------------------------------------*/

ساكن int32_t prv_Initialise_وقفه_Controller( فراغ )
{
    int32_t l_وضعیت;

    l_وضعیت = XIntc_Initialize( &x_وقفه_Controller_Instance, config_وقفه_CONTROLLER_مقصد_USE );

    إذا( l_وضعیت == XST_SUCCESS )
    {
        /* Initialise the exception table. */
        Xil_ExceptionInit();

        /* Service all pending interrupts each time the handler is entered. */
        XIntc_مجموعه_Intr_Svc_Option( x_وقفه_Controller_Instance.پایه_آدرس, XIN_SVC_ALL_ISRS_OPTION );

        /* Install exception handlers if the MicroBlaze is configured to handle
         * exceptions, and the application defined constant
         * configINSTALL_EXCEPTION_HANDLERS is set to 1. */
        #إذا ( MICROBLAZE_EXCEPTIONS_ENABLED == 1 ) && ( configINSTALL_EXCEPTION_HANDLERS == 1 )
        {
            v_پورت_Exceptions_Install_Handlers();
        }
        #پایان_اگر /* MICROBLAZE_EXCEPTIONS_ENABLED */

        /* Start the interrupt controller.  Interrupts are enabled when the
         * scheduler starts. */
        l_وضعیت = XIntc_شروع( &x_وقفه_Controller_Instance, XIN_REAL_نما );

        إذا( l_وضعیت == XST_SUCCESS )
        {
            l_وضعیت = pdPASS;
        }
        وإلا
        {
            l_وضعیت = pdFAIL;
        }
    }

    configASSERT( l_وضعیت == pdPASS );

    أرجع l_وضعیت;
}
/*-----------------------------------------------------------*/
