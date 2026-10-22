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

/* Hardware includes. */
#অন্তর্ভাব "msp430.h"

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the MSP430X port.
 *----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
not the MCLK. */
#define portACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#define portINITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#define portFLAGS_INT_ENABLED           ( ( স্তূপ_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
প্রকারলেখ শূন্য TCB_t;
বাহ্যিক অস্থির TCB_t * অস্থির pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
time a critical section is entered the count is incremented.  Each time a
critical section is exited the count is decremented - with interrupts only
being re-enabled if the count is zero.

usCriticalNesting will get set to zero when the scheduler starts, but must
not be initialised to zero as this will cause problems during the startup
sequence. */
অস্থির uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
শূন্য vPortSetupTimerInterrupt( শূন্য );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
স্তূপ_Type_t *px_Port_Initialise_স্তূপ( স্তূপ_Type_t *px_শীর্ষ_Of_স্তূপ, TaskFunction_t pxCode, শূন্য *pvParameters )
{
uint16_t *pus_শীর্ষ_Of_স্তূপ;
uint32_t *pul_শীর্ষ_Of_স্তূপ, ul_অস্থায়ী;

    /*
        Place a few bytes of known values on the bottom of the stack.
        This is just useful for debugging and can be included if required.

        *pxTopOfStack = ( StackType_t ) 0x1111;
        pxTopOfStack--;
        *pxTopOfStack = ( StackType_t ) 0x2222;
        pxTopOfStack--;
        *pxTopOfStack = ( StackType_t ) 0x3333;
        pxTopOfStack--;
    */

    /* Data types are need either 16 bits or 32 bits depending on the data
    and code model used. */
    যদি( আকার( pxCode ) == আকার( uint16_t ) )
    {
        pus_শীর্ষ_Of_স্তূপ = ( uint16_t * ) px_শীর্ষ_Of_স্তূপ;
        ul_অস্থায়ী = ( uint32_t ) pxCode;
        *pus_শীর্ষ_Of_স্তূপ = ( uint16_t ) ul_অস্থায়ী;
    }
    অন্যথা
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_শীর্ষ_Of_স্তূপ = ( uint16_t * ) px_শীর্ষ_Of_স্তূপ;
        pus_শীর্ষ_Of_স্তূপ--;
        pul_শীর্ষ_Of_স্তূপ = ( uint32_t * ) pus_শীর্ষ_Of_স্তূপ;
        *pul_শীর্ষ_Of_স্তূপ = ( uint32_t ) pxCode;
    }

    pus_শীর্ষ_Of_স্তূপ--;
    *pus_শীর্ষ_Of_স্তূপ = portFLAGS_INT_ENABLED;
    pus_শীর্ষ_Of_স্তূপ -= ( আকার( স্তূপ_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t * ) pus_শীর্ষ_Of_স্তূপ;

    /* Next the general purpose registers. */
    #ifdef PRELOAD_REGISTER_মানসমূহ
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xffff;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xeeee;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xdddd;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xbbbb;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xaaaa;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x9999;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x8888;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x5555;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x6666;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x5555;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x4444;
        px_শীর্ষ_Of_স্তূপ--;
    #অন্যথা
        px_শীর্ষ_Of_স্তূপ -= 3;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters;
        px_শীর্ষ_Of_স্তূপ -= 9;
    #endif

    /* A variable is used to keep track of the critical section nesting.
    This variable has to be stored as part of the task context and is
    initially set to zero. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) portNO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
    be stored in the task control block for the task. */
    ফেরত px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
    disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
শূন্য vPortSetupTimerInterrupt( শূন্য )
{
    vApplicationSetupTimerInterrupt();
}
/*-----------------------------------------------------------*/

#pragma vector=configTICK_VECTOR
interrupt শূন্য vTickISREntry( শূন্য )
{
বাহ্যিক শূন্য vPortTickISR( শূন্য );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    #যদি configUSE_PREEMPTION == 1
        বাহ্যিক শূন্য vPortPreemptiveTickISR( শূন্য );
        vPortPreemptiveTickISR();
    #অন্যথা
        বাহ্যিক শূন্য vPortCooperativeTickISR( শূন্য );
        vPortCooperativeTickISR();
    #endif
}


