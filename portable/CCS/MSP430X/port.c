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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLAGS_INT_ENABLED           ( ( ರಾಶಿ_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ TCB_t;
ಬಾಹ್ಯ ಅಸ್ಥಿರ TCB_t * ಅಸ್ಥಿರ pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
time a critical section is entered the count is incremented.  Each time a
critical section is exited the count is decremented - with interrupts only
being re-enabled if the count is zero.

usCriticalNesting will get set to zero when the scheduler starts, but must
not be initialised to zero as this will cause problems during the startup
sequence. */
ಅಸ್ಥಿರ uint16_t usCriticalNesting = ಪೋರ್ಟ್_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t *px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{
uint16_t *pus_ತುದಿ_ದ_ರಾಶಿ;
uint32_t *pul_ತುದಿ_ದ_ರಾಶಿ, ul_ತಾತ್ಕಾಲಿಕ;

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
    ಆದರೆ( ಗಾತ್ರ( px_ಸಂಕೇತ ) == ಗಾತ್ರ( uint16_t ) )
    {
        pus_ತುದಿ_ದ_ರಾಶಿ = ( uint16_t * ) px_ತುದಿ_ದ_ರಾಶಿ;
        ul_ತಾತ್ಕಾಲಿಕ = ( uint32_t ) px_ಸಂಕೇತ;
        *pus_ತುದಿ_ದ_ರಾಶಿ = ( uint16_t ) ul_ತಾತ್ಕಾಲಿಕ;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_ತುದಿ_ದ_ರಾಶಿ = ( uint16_t * ) px_ತುದಿ_ದ_ರಾಶಿ;
        pus_ತುದಿ_ದ_ರಾಶಿ--;
        pul_ತುದಿ_ದ_ರಾಶಿ = ( uint32_t * ) pus_ತುದಿ_ದ_ರಾಶಿ;
        *pul_ತುದಿ_ದ_ರಾಶಿ = ( uint32_t ) px_ಸಂಕೇತ;
    }

    pus_ತುದಿ_ದ_ರಾಶಿ--;
    *pus_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_FLAGS_INT_ENABLED;
    pus_ತುದಿ_ದ_ರಾಶಿ -= ( ಗಾತ್ರ( ರಾಶಿ_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t * ) pus_ತುದಿ_ದ_ರಾಶಿ;

    /* Next the general purpose registers. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PRELOAD_ರಿಜಿಸ್ಟರ್_ಮೌಲ್ಯಗಳು
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xffff;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xeeee;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xdddd;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xbbbb;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xaaaa;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x9999;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x8888;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x5555;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x6666;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x5555;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x4444;
        px_ತುದಿ_ದ_ರಾಶಿ--;
    #ಇಲ್ಲದಿದ್ದರೆ
        px_ತುದಿ_ದ_ರಾಶಿ -= 3;
        *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
        px_ತುದಿ_ದ_ರಾಶಿ -= 9;
    #ಆದರೆ_ಅಂತ್ಯ

    /* A variable is used to keep track of the critical section nesting.
    This variable has to be stored as part of the task context and is
    initially set to zero. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
    be stored in the task control block for the task. */
    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
    disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ ಸದಿಶ=config_TICK_ಸದಿಶ
ಅಡಚಣೆ ಶೂನ್ಯ vTickISREntry( ಶೂನ್ಯ )
{
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    #ಆದರೆ configUSE_PREEMPTION == 1
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Preemptive_Tick_ISR( ಶೂನ್ಯ );
        v_ಪೋರ್ಟ್_Preemptive_Tick_ISR();
    #ಇಲ್ಲದಿದ್ದರೆ
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Cooperative_Tick_ISR( ಶೂನ್ಯ );
        v_ಪೋರ್ಟ್_Cooperative_Tick_ISR();
    #ಆದರೆ_ಅಂತ್ಯ
}


