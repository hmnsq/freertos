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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Library includes. */
#شامل "string.h"

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

#اگر ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error configSUPPORT_DYNAMIC_ALLOCATION must be 1 to use this port.
#endif

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
تهی vPortYield( تهی );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
بیرونی تهی vPortStartFirstTask( تهی );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
بیرونی uint32_t ulPortGetGBR( تهی );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_Port_Initialise_پشته( پشته_Type_t * px_بالاترین_Of_پشته,
                                     TaskFunction_t pxCode,
                                     تهی * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_بالاترین_Of_پشته = 0x11111111UL;
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x22222222UL;
    px_بالاترین_Of_پشته--;
    *px_بالاترین_Of_پشته = 0x33333333UL;
    px_بالاترین_Of_پشته--;

    /* SR. */
    *px_بالاترین_Of_پشته = portINITIAL_SR;
    px_بالاترین_Of_پشته--;

    /* PC. */
    *px_بالاترین_Of_پشته = ( uint32_t ) pxCode;
    px_بالاترین_Of_پشته--;

    /* PR. */
    *px_بالاترین_Of_پشته = 15;
    px_بالاترین_Of_پشته--;

    /* 14. */
    *px_بالاترین_Of_پشته = 14;
    px_بالاترین_Of_پشته--;

    /* R13. */
    *px_بالاترین_Of_پشته = 13;
    px_بالاترین_Of_پشته--;

    /* R12. */
    *px_بالاترین_Of_پشته = 12;
    px_بالاترین_Of_پشته--;

    /* R11. */
    *px_بالاترین_Of_پشته = 11;
    px_بالاترین_Of_پشته--;

    /* R10. */
    *px_بالاترین_Of_پشته = 10;
    px_بالاترین_Of_پشته--;

    /* R9. */
    *px_بالاترین_Of_پشته = 9;
    px_بالاترین_Of_پشته--;

    /* R8. */
    *px_بالاترین_Of_پشته = 8;
    px_بالاترین_Of_پشته--;

    /* R7. */
    *px_بالاترین_Of_پشته = 7;
    px_بالاترین_Of_پشته--;

    /* R6. */
    *px_بالاترین_Of_پشته = 6;
    px_بالاترین_Of_پشته--;

    /* R5. */
    *px_بالاترین_Of_پشته = 5;
    px_بالاترین_Of_پشته--;

    /* R4. */
    *px_بالاترین_Of_پشته = ( uint32_t ) pvParameters;
    px_بالاترین_Of_پشته--;

    /* R3. */
    *px_بالاترین_Of_پشته = 3;
    px_بالاترین_Of_پشته--;

    /* R2. */
    *px_بالاترین_Of_پشته = 2;
    px_بالاترین_Of_پشته--;

    /* R1. */
    *px_بالاترین_Of_پشته = 1;
    px_بالاترین_Of_پشته--;

    /* R0 */
    *px_بالاترین_Of_پشته = 0;
    px_بالاترین_Of_پشته--;

    /* MACL. */
    *px_بالاترین_Of_پشته = 16;
    px_بالاترین_Of_پشته--;

    /* MACH. */
    *px_بالاترین_Of_پشته = 17;
    px_بالاترین_Of_پشته--;

    /* GBR. */
    *px_بالاترین_Of_پشته = ulPortGetGBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    بازگشت px_بالاترین_Of_پشته;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( تهی )
{
    بیرونی تهی vApplicationSetupTimerInterrupt( تهی );

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
    بازگشت pdFAIL;
}
/*-----------------------------------------------------------*/

تهی vPortEndScheduler( تهی )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

تهی vPortYield( تهی )
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
    set_imask( ( صحیح ) lInterruptMask );
}
/*-----------------------------------------------------------*/

BaseType_t xPortUsesFloatingPoint( TaskHandle_t xTask )
{
    uint32_t * pulFlopBuffer;
    BaseType_t xReturn;
    بیرونی تهی * فرار pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    اگر( xTask == پوچ )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pulFlopBuffer = ( uint32_t * ) pvPortMalloc( portFLOP_STORAGE_SIZE );

    اگر( pulFlopBuffer != پوچ )
    {
        /* Start with the registers in a benign state. */
        memset( ( تهی * ) pulFlopBuffer, 0x00, portFLOP_STORAGE_SIZE );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pulFlopBuffer = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        vTaskSetApplicationTaskTag( xTask, ( تهی * ) ( pulFlopBuffer + portFLOP_REGISTERS_TO_STORE ) );
        xReturn = pdPASS;
    }
    وگرنه
    {
        xReturn = pdFAIL;
    }

    بازگشت xReturn;
}
/*-----------------------------------------------------------*/
