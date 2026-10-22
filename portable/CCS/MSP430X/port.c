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
#ಅನ್ತರ್ಭಾವ "msp430.h"

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the MSP430X port.
 *----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
not the MCLK. */
#define portACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#define portINITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#define portFLAGS_INT_ENABLED           ( ( ರಾಶಿ_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ TCB_t;
ಬಾಹ್ಯ ಚಞ್ಚಲ TCB_t * ಚಞ್ಚಲ pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
time a critical section is entered the count is incremented.  Each time a
critical section is exited the count is decremented - with interrupts only
being re-enabled if the count is zero.

usCriticalNesting will get set to zero when the scheduler starts, but must
not be initialised to zero as this will cause problems during the startup
sequence. */
ಚಞ್ಚಲ uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ಶೂನ್ಯ vPortSetupTimerInterrupt( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ರಾಶಿ_Type_t *px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_Of_ರಾಶಿ, TaskFunction_t pxCode, ಶೂನ್ಯ *pvParameters )
{
uint16_t *pus_ತುದಿ_Of_ರಾಶಿ;
uint32_t *pul_ತುದಿ_Of_ರಾಶಿ, ulTemp;

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
    ಯದಿ( ಪರಿಮಾಣ( pxCode ) == ಪರಿಮಾಣ( uint16_t ) )
    {
        pus_ತುದಿ_Of_ರಾಶಿ = ( uint16_t * ) px_ತುದಿ_Of_ರಾಶಿ;
        ulTemp = ( uint32_t ) pxCode;
        *pus_ತುದಿ_Of_ರಾಶಿ = ( uint16_t ) ulTemp;
    }
    ಅನ್ಯಥಾ
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_ತುದಿ_Of_ರಾಶಿ = ( uint16_t * ) px_ತುದಿ_Of_ರಾಶಿ;
        pus_ತುದಿ_Of_ರಾಶಿ--;
        pul_ತುದಿ_Of_ರಾಶಿ = ( uint32_t * ) pus_ತುದಿ_Of_ರಾಶಿ;
        *pul_ತುದಿ_Of_ರಾಶಿ = ( uint32_t ) pxCode;
    }

    pus_ತುದಿ_Of_ರಾಶಿ--;
    *pus_ತುದಿ_Of_ರಾಶಿ = portFLAGS_INT_ENABLED;
    pus_ತುದಿ_Of_ರಾಶಿ -= ( ಪರಿಮಾಣ( ರಾಶಿ_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t * ) pus_ತುದಿ_Of_ರಾಶಿ;

    /* Next the general purpose registers. */
    #ifdef PRELOAD_REGISTER_ಮೌಲ್ಯಗಳು
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xffff;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xeeee;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xdddd;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xbbbb;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xaaaa;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x9999;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x8888;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x5555;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x6666;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x5555;
        px_ತುದಿ_Of_ರಾಶಿ--;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x4444;
        px_ತುದಿ_Of_ರಾಶಿ--;
    #ಅನ್ಯಥಾ
        px_ತುದಿ_Of_ರಾಶಿ -= 3;
        *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
        px_ತುದಿ_Of_ರಾಶಿ -= 9;
    #endif

    /* A variable is used to keep track of the critical section nesting.
    This variable has to be stored as part of the task context and is
    initially set to zero. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) portNO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
    be stored in the task control block for the task. */
    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
    disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ಶೂನ್ಯ vPortSetupTimerInterrupt( ಶೂನ್ಯ )
{
    vApplicationSetupTimerInterrupt();
}
/*-----------------------------------------------------------*/

#pragma vector=configTICK_VECTOR
interrupt ಶೂನ್ಯ vTickISREntry( ಶೂನ್ಯ )
{
ಬಾಹ್ಯ ಶೂನ್ಯ vPortTickISR( ಶೂನ್ಯ );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    #ಯದಿ configUSE_PREEMPTION == 1
        ಬಾಹ್ಯ ಶೂನ್ಯ vPortPreemptiveTickISR( ಶೂನ್ಯ );
        vPortPreemptiveTickISR();
    #ಅನ್ಯಥಾ
        ಬಾಹ್ಯ ಶೂನ್ಯ vPortCooperativeTickISR( ಶೂನ್ಯ );
        vPortCooperativeTickISR();
    #endif
}


