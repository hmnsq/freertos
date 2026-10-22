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
* Implementation of functions defined in portable.h for the SH2A port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Library includes. */
#অন্তর্ভাব "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#define portINITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#define portFLOP_REGISTERS_TO_STORE    ( 18 )
#define portFLOP_STORAGE_SIZE          ( portFLOP_REGISTERS_TO_STORE * 4 )

#যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error configSUPPORT_DYNAMIC_ALLOCATION must be 1 to use this port.
#endif

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
শূন্য vPortYield( শূন্য );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
বাহ্য শূন্য vPortStartFirstTask( শূন্য );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
বাহ্য uint32_t ulPortGetGBR( শূন্য );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_শীর্ষ_Of_স্তূপ = 0x11111111UL;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x22222222UL;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = 0x33333333UL;
    px_শীর্ষ_Of_স্তূপ--;

    /* SR. */
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_SR;
    px_শীর্ষ_Of_স্তূপ--;

    /* PC. */
    *px_শীর্ষ_Of_স্তূপ = ( uint32_t ) pxCode;
    px_শীর্ষ_Of_স্তূপ--;

    /* PR. */
    *px_শীর্ষ_Of_স্তূপ = 15;
    px_শীর্ষ_Of_স্তূপ--;

    /* 14. */
    *px_শীর্ষ_Of_স্তূপ = 14;
    px_শীর্ষ_Of_স্তূপ--;

    /* R13. */
    *px_শীর্ষ_Of_স্তূপ = 13;
    px_শীর্ষ_Of_স্তূপ--;

    /* R12. */
    *px_শীর্ষ_Of_স্তূপ = 12;
    px_শীর্ষ_Of_স্তূপ--;

    /* R11. */
    *px_শীর্ষ_Of_স্তূপ = 11;
    px_শীর্ষ_Of_স্তূপ--;

    /* R10. */
    *px_শীর্ষ_Of_স্তূপ = 10;
    px_শীর্ষ_Of_স্তূপ--;

    /* R9. */
    *px_শীর্ষ_Of_স্তূপ = 9;
    px_শীর্ষ_Of_স্তূপ--;

    /* R8. */
    *px_শীর্ষ_Of_স্তূপ = 8;
    px_শীর্ষ_Of_স্তূপ--;

    /* R7. */
    *px_শীর্ষ_Of_স্তূপ = 7;
    px_শীর্ষ_Of_স্তূপ--;

    /* R6. */
    *px_শীর্ষ_Of_স্তূপ = 6;
    px_শীর্ষ_Of_স্তূপ--;

    /* R5. */
    *px_শীর্ষ_Of_স্তূপ = 5;
    px_শীর্ষ_Of_স্তূপ--;

    /* R4. */
    *px_শীর্ষ_Of_স্তূপ = ( uint32_t ) pvParameters;
    px_শীর্ষ_Of_স্তূপ--;

    /* R3. */
    *px_শীর্ষ_Of_স্তূপ = 3;
    px_শীর্ষ_Of_স্তূপ--;

    /* R2. */
    *px_শীর্ষ_Of_স্তূপ = 2;
    px_শীর্ষ_Of_স্তূপ--;

    /* R1. */
    *px_শীর্ষ_Of_স্তূপ = 1;
    px_শীর্ষ_Of_স্তূপ--;

    /* R0 */
    *px_শীর্ষ_Of_স্তূপ = 0;
    px_শীর্ষ_Of_স্তূপ--;

    /* MACL. */
    *px_শীর্ষ_Of_স্তূপ = 16;
    px_শীর্ষ_Of_স্তূপ--;

    /* MACH. */
    *px_শীর্ষ_Of_স্তূপ = 17;
    px_শীর্ষ_Of_স্তূপ--;

    /* GBR. */
    *px_শীর্ষ_Of_স্তূপ = ulPortGetGBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    প্রত্যাগম px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    বাহ্য শূন্য vApplicationSetupTimerInterrupt( শূন্য );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    vApplicationSetupTimerInterrupt();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( portSTART_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    প্রত্যাগম pdFAIL;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

শূন্য vPortYield( শূন্য )
{
    int32_t lInterruptMask;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    lInterruptMask = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    set_imask( portKERNEL_INTERRUPT_PRIORITY );

    trapa( portYIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    set_imask( ( পূর্ণাঙ্ক ) lInterruptMask );
}
/*-----------------------------------------------------------*/

BaseType_t xPortUsesFloatingPoint( TaskHandle_t xTask )
{
    uint32_t * pulFlopBuffer;
    BaseType_t xReturn;
    বাহ্য শূন্য * চঞ্চল pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    যদি( xTask == রিক্ত )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pulFlopBuffer = ( uint32_t * ) pvPortMalloc( portFLOP_STORAGE_SIZE );

    যদি( pulFlopBuffer != রিক্ত )
    {
        /* Start with the registers in a benign state. */
        memset( ( শূন্য * ) pulFlopBuffer, 0x00, portFLOP_STORAGE_SIZE );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pulFlopBuffer = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        vTaskSetApplicationTaskTag( xTask, ( শূন্য * ) ( pulFlopBuffer + portFLOP_REGISTERS_TO_STORE ) );
        xReturn = pdPASS;
    }
    অন্যথা
    {
        xReturn = pdFAIL;
    }

    প্রত্যাগম xReturn;
}
/*-----------------------------------------------------------*/
