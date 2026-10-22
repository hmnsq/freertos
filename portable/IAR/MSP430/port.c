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

/* Scheduler includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the MSP430 port.
*----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
 * not the MCLK. */
#define portACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#define portINITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#define portFLAGS_INT_ENABLED           ( ( അട്ടി_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
തരനിർവചനം ശൂന്യം TCB_t;
ബാഹ്യ അസ്ഥിര TCB_t * അസ്ഥിര pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
 * time a critical section is entered the count is incremented.  Each time a
 * critical section is exited the count is decremented - with interrupts only
 * being re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as this will cause problems during the startup
 * sequence. */
അസ്ഥിര uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ശൂന്യം vPortSetupTimerInterrupt( ശൂന്യം );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    /*
     *  Place a few bytes of known values on the bottom of the stack.
     *  This is just useful for debugging and can be included if required.
     *
     * pxTopOfStack = ( StackType_t ) 0x1111;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x2222;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x3333;
     *  pxTopOfStack--;
     */

    /* The msp430 automatically pushes the PC then SR onto the stack before
     * executing an ISR.  We want the stack to look just as if this has happened
     * so place a pointer to the start of the task on the stack first - followed
     * by the flags we want the task to use when it starts up. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = portFLAGS_INT_ENABLED;
    px_മുകൾ_Of_അട്ടി--;

    /* Next the general purpose registers. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x4444;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x5555;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x6666;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x7777;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x8888;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x9999;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xaaaa;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xbbbb;
    px_മുകൾ_Of_അട്ടി--;

    /* When the task starts is will expect to find the function parameter in
     * R15. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters;
    px_മുകൾ_Of_അട്ടി--;

    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xdddd;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xeeee;
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xffff;
    px_മുകൾ_Of_അട്ടി--;

    /* A variable is used to keep track of the critical section nesting.
     * This variable has to be stored as part of the task context and is
     * initially set to zero. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portNO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.  This uses timer 0
 * but could alternatively use the watchdog timer or timer 1.
 */
ശൂന്യം vPortSetupTimerInterrupt( ശൂന്യം )
{
    /* Ensure the timer is stopped. */
    TACTL = 0;

    /* Run the timer of the ACLK. */
    TACTL = TASSEL_1;

    /* Clear everything to start with. */
    TACTL |= TACLR;

    /* Set the compare match value according to the tick rate we want. */
    TACCR0 = portACLK_FREQUENCY_HZ / configTICK_RATE_HZ;

    /* Enable the interrupts. */
    TACCTL0 = CCIE;

    /* Start up clean. */
    TACTL |= TACLR;

    /* Up mode. */
    TACTL |= MC_1;
}
/*-----------------------------------------------------------*/
