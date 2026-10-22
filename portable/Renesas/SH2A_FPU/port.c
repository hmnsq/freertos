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
#include "FreeRTOS.h"
#include "task.h"

/* Library includes. */
#include "string.h"

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

#if ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error configSUPPORT_DYNAMIC_ALLOCATION must be 1 to use this port.
#endif

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
void vPortYield( void );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
extern void vPortStartFirstTask( void );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
extern uint32_t ulPortGetGBR( void );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
सालानसान_Type_t * px_Port_Initialise_सालानसान( सालानसान_Type_t * px_इताअस_Of_सालानसान,
                                     TaskFunction_t pxCode,
                                     void * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_इताअस_Of_सालानसान = 0x11111111UL;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = 0x22222222UL;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = 0x33333333UL;
    px_इताअस_Of_सालानसान--;

    /* SR. */
    *px_इताअस_Of_सालानसान = portINITIAL_SR;
    px_इताअस_Of_सालानसान--;

    /* PC. */
    *px_इताअस_Of_सालानसान = ( uint32_t ) pxCode;
    px_इताअस_Of_सालानसान--;

    /* PR. */
    *px_इताअस_Of_सालानसान = 15;
    px_इताअस_Of_सालानसान--;

    /* 14. */
    *px_इताअस_Of_सालानसान = 14;
    px_इताअस_Of_सालानसान--;

    /* R13. */
    *px_इताअस_Of_सालानसान = 13;
    px_इताअस_Of_सालानसान--;

    /* R12. */
    *px_इताअस_Of_सालानसान = 12;
    px_इताअस_Of_सालानसान--;

    /* R11. */
    *px_इताअस_Of_सालानसान = 11;
    px_इताअस_Of_सालानसान--;

    /* R10. */
    *px_इताअस_Of_सालानसान = 10;
    px_इताअस_Of_सालानसान--;

    /* R9. */
    *px_इताअस_Of_सालानसान = 9;
    px_इताअस_Of_सालानसान--;

    /* R8. */
    *px_इताअस_Of_सालानसान = 8;
    px_इताअस_Of_सालानसान--;

    /* R7. */
    *px_इताअस_Of_सालानसान = 7;
    px_इताअस_Of_सालानसान--;

    /* R6. */
    *px_इताअस_Of_सालानसान = 6;
    px_इताअस_Of_सालानसान--;

    /* R5. */
    *px_इताअस_Of_सालानसान = 5;
    px_इताअस_Of_सालानसान--;

    /* R4. */
    *px_इताअस_Of_सालानसान = ( uint32_t ) pvParameters;
    px_इताअस_Of_सालानसान--;

    /* R3. */
    *px_इताअस_Of_सालानसान = 3;
    px_इताअस_Of_सालानसान--;

    /* R2. */
    *px_इताअस_Of_सालानसान = 2;
    px_इताअस_Of_सालानसान--;

    /* R1. */
    *px_इताअस_Of_सालानसान = 1;
    px_इताअस_Of_सालानसान--;

    /* R0 */
    *px_इताअस_Of_सालानसान = 0;
    px_इताअस_Of_सालानसान--;

    /* MACL. */
    *px_इताअस_Of_सालानसान = 16;
    px_इताअस_Of_सालानसान--;

    /* MACH. */
    *px_इताअस_Of_सालानसान = 17;
    px_इताअस_Of_सालानसान--;

    /* GBR. */
    *px_इताअस_Of_सालानसान = ulPortGetGBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    return px_इताअस_Of_सालानसान;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
    extern void vApplicationSetupTimerInterrupt( void );

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
    return pdFAIL;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

void vPortYield( void )
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
    set_imask( ( int ) lInterruptMask );
}
/*-----------------------------------------------------------*/

BaseType_t xPortUsesFloatingPoint( TaskHandle_t xTask )
{
    uint32_t * pulFlopBuffer;
    BaseType_t xReturn;
    extern void * volatile pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    if( xTask == NULL )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pulFlopBuffer = ( uint32_t * ) pvPortMalloc( portFLOP_STORAGE_SIZE );

    if( pulFlopBuffer != NULL )
    {
        /* Start with the registers in a benign state. */
        memset( ( void * ) pulFlopBuffer, 0x00, portFLOP_STORAGE_SIZE );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pulFlopBuffer = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        vTaskSetApplicationTaskTag( xTask, ( void * ) ( pulFlopBuffer + portFLOP_REGISTERS_TO_STORE ) );
        xReturn = pdPASS;
    }
    else
    {
        xReturn = pdFAIL;
    }

    return xReturn;
}
/*-----------------------------------------------------------*/
