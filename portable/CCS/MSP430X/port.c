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
#ضمن "msp430.h"

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the MSP430X port.
 *----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
not the MCLK. */
#تعریف_کړه پورټ_ACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#تعریف_کړه پورټ_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#تعریف_کړه پورټ_FLAGS_INT_ENABLED           ( ( ډېری_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
time a critical section is entered the count is incremented.  Each time a
critical section is exited the count is decremented - with interrupts only
being re-enabled if the count is zero.

usCriticalNesting will get set to zero when the scheduler starts, but must
not be initialised to zero as this will cause problems during the startup
sequence. */
متطاير uint16_t usCriticalNesting = پورټ_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ډېری_Type_t *px_پورټ_Initialise_ډېری( ډېری_Type_t *px_سر_د_ډېری, TaskFunction_t px_کوډ, فراغ *pvParameters )
{
uint16_t *pus_سر_د_ډېری;
uint32_t *pul_سر_د_ډېری, ul_لنډمهاله;

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
    إذا( حجم( px_کوډ ) == حجم( uint16_t ) )
    {
        pus_سر_د_ډېری = ( uint16_t * ) px_سر_د_ډېری;
        ul_لنډمهاله = ( uint32_t ) px_کوډ;
        *pus_سر_د_ډېری = ( uint16_t ) ul_لنډمهاله;
    }
    وإلا
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_سر_د_ډېری = ( uint16_t * ) px_سر_د_ډېری;
        pus_سر_د_ډېری--;
        pul_سر_د_ډېری = ( uint32_t * ) pus_سر_د_ډېری;
        *pul_سر_د_ډېری = ( uint32_t ) px_کوډ;
    }

    pus_سر_د_ډېری--;
    *pus_سر_د_ډېری = پورټ_FLAGS_INT_ENABLED;
    pus_سر_د_ډېری -= ( حجم( ډېری_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_سر_د_ډېری = ( ډېری_Type_t * ) pus_سر_د_ډېری;

    /* Next the general purpose registers. */
    #که_تعریف_شوی PRELOAD_ثبتوونکی_ارزښتونه
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0xffff;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0xeeee;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0xdddd;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0xbbbb;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0xaaaa;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x9999;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x8888;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x5555;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x6666;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x5555;
        px_سر_د_ډېری--;
        *px_سر_د_ډېری = ( ډېری_Type_t ) 0x4444;
        px_سر_د_ډېری--;
    #وإلا
        px_سر_د_ډېری -= 3;
        *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;
        px_سر_د_ډېری -= 9;
    #د_که_پای

    /* A variable is used to keep track of the critical section nesting.
    This variable has to be stored as part of the task context and is
    initially set to zero. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
    be stored in the task control block for the task. */
    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
    disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ )
{
    v_Application_تیاری_Timer_مداخله();
}
/*-----------------------------------------------------------*/

#لارښوونه ویکټور=config_TICK_ویکټور
مداخله فراغ vTickISREntry( فراغ )
{
خارجي فراغ v_پورټ_Tick_ISR( فراغ );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    #إذا configUSE_PREEMPTION == 1
        خارجي فراغ v_پورټ_Preemptive_Tick_ISR( فراغ );
        v_پورټ_Preemptive_Tick_ISR();
    #وإلا
        خارجي فراغ v_پورټ_Cooperative_Tick_ISR( فراغ );
        v_پورټ_Cooperative_Tick_ISR();
    #د_که_پای
}


