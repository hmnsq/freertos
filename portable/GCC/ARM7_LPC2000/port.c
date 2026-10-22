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
* Implementation of functions defined in portable.h for the ARM7 port.
*
* Components that can be compiled to either ARM or THUMB mode are
* contained in this file.  The ISR routines, which can only be compiled
* to ARM mode are contained in portISR.c.
*----------------------------------------------------------*/


/* Standard includes. */
#അന്തര്ഭാവ <stdlib.h>

/* Scheduler includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/* Constants required to setup the task context. */
#define portINITIAL_SPSR                   ( ( അട്ടി_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT                 ( ( അട്ടി_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE               ( ( അട്ടി_Type_t ) 4 )
#define portNO_CRITICAL_SECTION_NESTING    ( ( അട്ടി_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#define portENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#define port_PRESCALE_മൂല്യം                 0x00
#define portINTERRUPT_ON_MATCH             ( ( uint32_t ) 0x01 )
#define port_RESET_എണ്ണം_ON_MATCH           ( ( uint32_t ) 0x02 )

/* Constants required to setup the VIC for the tick ISR. */
#define portTIMER_VIC_CHANNEL              ( ( uint32_t ) 0x0004 )
#define portTIMER_VIC_CHANNEL_BIT          ( ( uint32_t ) 0x0010 )
#define portTIMER_VIC_ENABLE               ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
ബാഹ്യ ശൂന്യം vPortISRStartFirstTask( ശൂന്യം );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    അട്ടി_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_മുകൾ_Of_അട്ടി;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_മുകൾ_Of_അട്ടി--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_മുകൾ_Of_അട്ടി--;

    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x12121212;    /* R12 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x11111111;    /* R11 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x10101010;    /* R10 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x09090909;    /* R9 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x08080808;    /* R8 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x07070707;    /* R7 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x06060606;    /* R6 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x05050505;    /* R5 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x04040404;    /* R4 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x03030303;    /* R3 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x02020202;    /* R2 */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x01010101;    /* R1 */
    px_മുകൾ_Of_അട്ടി--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters; /* R0 */
    px_മുകൾ_Of_അട്ടി--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portINITIAL_SPSR;

    എങ്കിൽ( ( ( uint32_t ) pxCode & 0x01UL ) != 0x00 )
    {
        /* We want the task to start in thumb mode. */
        *px_മുകൾ_Of_അട്ടി |= portTHUMB_MODE_BIT;
    }

    px_മുകൾ_Of_അട്ടി--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_മുകൾ_Of_അട്ടി = portNO_CRITICAL_SECTION_NESTING;

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortISRStartFirstTask();

    /* Should not get here! */
    തിരികെ 0;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം )
{
    uint32_t ulCompareMatch;

    ബാഹ്യ ശൂന്യം( vTickISR )( ശൂന്യം );

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0_PR = port_PRESCALE_മൂല്യം;

    /* Calculate the match value required for our wanted tick rate. */
    ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #എങ്കിൽ port_PRESCALE_മൂല്യം != 0
    {
        ulCompareMatch /= ( port_PRESCALE_മൂല്യം + 1 );
    }
    #endif
    T0_MR0 = ulCompareMatch;

    /* Generate tick with timer 0 compare match. */
    T0_MCR = port_RESET_എണ്ണം_ON_MATCH | portINTERRUPT_ON_MATCH;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( portTIMER_VIC_CHANNEL_BIT );
    VICIntEnable |= portTIMER_VIC_CHANNEL_BIT;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */

    VICVectAddr0 = ( int32_t ) vTickISR;
    VICVectCntl0 = portTIMER_VIC_CHANNEL | portTIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0_TCR = portENABLE_TIMER;
}
/*-----------------------------------------------------------*/
