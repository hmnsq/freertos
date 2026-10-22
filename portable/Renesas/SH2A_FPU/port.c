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
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"

/* Library includes. */
#અન્તર્ભાવ "string.h"

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

#જો ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error configSUPPORT_DYNAMIC_ALLOCATION must be 1 to use this port.
#endif

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
શૂન્ય vPortYield( શૂન્ય );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
બાહ્ય શૂન્ય vPortStartFirstTask( શૂન્ય );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
બાહ્ય uint32_t ulPortGetGBR( શૂન્ય );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                     TaskFunction_t pxCode,
                                     શૂન્ય * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_ટોચ_Of_ઢગલો = 0x11111111UL;
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = 0x22222222UL;
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = 0x33333333UL;
    px_ટોચ_Of_ઢગલો--;

    /* SR. */
    *px_ટોચ_Of_ઢગલો = portINITIAL_SR;
    px_ટોચ_Of_ઢગલો--;

    /* PC. */
    *px_ટોચ_Of_ઢગલો = ( uint32_t ) pxCode;
    px_ટોચ_Of_ઢગલો--;

    /* PR. */
    *px_ટોચ_Of_ઢગલો = 15;
    px_ટોચ_Of_ઢગલો--;

    /* 14. */
    *px_ટોચ_Of_ઢગલો = 14;
    px_ટોચ_Of_ઢગલો--;

    /* R13. */
    *px_ટોચ_Of_ઢગલો = 13;
    px_ટોચ_Of_ઢગલો--;

    /* R12. */
    *px_ટોચ_Of_ઢગલો = 12;
    px_ટોચ_Of_ઢગલો--;

    /* R11. */
    *px_ટોચ_Of_ઢગલો = 11;
    px_ટોચ_Of_ઢગલો--;

    /* R10. */
    *px_ટોચ_Of_ઢગલો = 10;
    px_ટોચ_Of_ઢગલો--;

    /* R9. */
    *px_ટોચ_Of_ઢગલો = 9;
    px_ટોચ_Of_ઢગલો--;

    /* R8. */
    *px_ટોચ_Of_ઢગલો = 8;
    px_ટોચ_Of_ઢગલો--;

    /* R7. */
    *px_ટોચ_Of_ઢગલો = 7;
    px_ટોચ_Of_ઢગલો--;

    /* R6. */
    *px_ટોચ_Of_ઢગલો = 6;
    px_ટોચ_Of_ઢગલો--;

    /* R5. */
    *px_ટોચ_Of_ઢગલો = 5;
    px_ટોચ_Of_ઢગલો--;

    /* R4. */
    *px_ટોચ_Of_ઢગલો = ( uint32_t ) pvParameters;
    px_ટોચ_Of_ઢગલો--;

    /* R3. */
    *px_ટોચ_Of_ઢગલો = 3;
    px_ટોચ_Of_ઢગલો--;

    /* R2. */
    *px_ટોચ_Of_ઢગલો = 2;
    px_ટોચ_Of_ઢગલો--;

    /* R1. */
    *px_ટોચ_Of_ઢગલો = 1;
    px_ટોચ_Of_ઢગલો--;

    /* R0 */
    *px_ટોચ_Of_ઢગલો = 0;
    px_ટોચ_Of_ઢગલો--;

    /* MACL. */
    *px_ટોચ_Of_ઢગલો = 16;
    px_ટોચ_Of_ઢગલો--;

    /* MACH. */
    *px_ટોચ_Of_ઢગલો = 17;
    px_ટોચ_Of_ઢગલો--;

    /* GBR. */
    *px_ટોચ_Of_ઢગલો = ulPortGetGBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    પાછા px_ટોચ_Of_ઢગલો;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( શૂન્ય )
{
    બાહ્ય શૂન્ય vApplicationSetupTimerInterrupt( શૂન્ય );

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
    પાછા pdFAIL;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEndScheduler( શૂન્ય )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

શૂન્ય vPortYield( શૂન્ય )
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
    set_imask( ( પૂર્ણાંક ) lInterruptMask );
}
/*-----------------------------------------------------------*/

BaseType_t xPortUsesFloatingPoint( TaskHandle_t xTask )
{
    uint32_t * pulFlopBuffer;
    BaseType_t xReturn;
    બાહ્ય શૂન્ય * અસ્થિર pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    જો( xTask == ખાલી )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pulFlopBuffer = ( uint32_t * ) pvPortMalloc( portFLOP_STORAGE_SIZE );

    જો( pulFlopBuffer != ખાલી )
    {
        /* Start with the registers in a benign state. */
        memset( ( શૂન્ય * ) pulFlopBuffer, 0x00, portFLOP_STORAGE_SIZE );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pulFlopBuffer = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        vTaskSetApplicationTaskTag( xTask, ( શૂન્ય * ) ( pulFlopBuffer + portFLOP_REGISTERS_TO_STORE ) );
        xReturn = pdPASS;
    }
    નહીંતર
    {
        xReturn = pdFAIL;
    }

    પાછા xReturn;
}
/*-----------------------------------------------------------*/
