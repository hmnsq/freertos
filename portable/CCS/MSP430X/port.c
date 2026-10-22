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
#ਅਨ੍ਤਰ੍ਭਾਵ "msp430.h"

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the MSP430X port.
 *----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
not the MCLK. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLAGS_INT_ENABLED           ( ( ਢੇਰ_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ TCB_t;
ਬਾਹਰੀ ਅਸਥਿਰ TCB_t * ਅਸਥਿਰ pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
time a critical section is entered the count is incremented.  Each time a
critical section is exited the count is decremented - with interrupts only
being re-enabled if the count is zero.

usCriticalNesting will get set to zero when the scheduler starts, but must
not be initialised to zero as this will cause problems during the startup
sequence. */
ਅਸਥਿਰ uint16_t usCriticalNesting = ਪੋਰਟ_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
uint16_t *pus_ਸਿਖਰ_ਦਾ_ਢੇਰ;
uint32_t *pul_ਸਿਖਰ_ਦਾ_ਢੇਰ, ul_ਆਰਜ਼ੀ;

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
    ਜੇ( ਆਕਾਰ( px_ਕੋਡ ) == ਆਕਾਰ( uint16_t ) )
    {
        pus_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint16_t * ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
        ul_ਆਰਜ਼ੀ = ( uint32_t ) px_ਕੋਡ;
        *pus_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint16_t ) ul_ਆਰਜ਼ੀ;
    }
    ਨਹੀਂਤਾਂ
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint16_t * ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
        pus_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        pul_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint32_t * ) pus_ਸਿਖਰ_ਦਾ_ਢੇਰ;
        *pul_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint32_t ) px_ਕੋਡ;
    }

    pus_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *pus_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_FLAGS_INT_ENABLED;
    pus_ਸਿਖਰ_ਦਾ_ਢੇਰ -= ( ਆਕਾਰ( ਢੇਰ_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t * ) pus_ਸਿਖਰ_ਦਾ_ਢੇਰ;

    /* Next the general purpose registers. */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PRELOAD_ਰਜਿਸਟਰ_ਮੁੱਲਾਂ
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xffff;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xeeee;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xdddd;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xbbbb;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xaaaa;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x9999;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x8888;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x5555;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x6666;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x5555;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x4444;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਨਹੀਂਤਾਂ
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 3;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 9;
    #ਜੇ_ਅੰਤ

    /* A variable is used to keep track of the critical section nesting.
    This variable has to be stored as part of the task context and is
    initially set to zero. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
    be stored in the task control block for the task. */
    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
    disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();
}
/*-----------------------------------------------------------*/

#ਹਦਾਇਤ ਸਦਿਸ਼=config_TICK_ਸਦਿਸ਼
ਰੁਕਾਵਟ ਖਾਲੀ vTickISREntry( ਖਾਲੀ )
{
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Tick_ISR( ਖਾਲੀ );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    #ਜੇ configUSE_PREEMPTION == 1
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Preemptive_Tick_ISR( ਖਾਲੀ );
        v_ਪੋਰਟ_Preemptive_Tick_ISR();
    #ਨਹੀਂਤਾਂ
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Cooperative_Tick_ISR( ਖਾਲੀ );
        v_ਪੋਰਟ_Cooperative_Tick_ISR();
    #ਜੇ_ਅੰਤ
}


