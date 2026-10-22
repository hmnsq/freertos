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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Hardware includes. */
#ضمن "msp430.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the MSP430X port.
*----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
 * not the MCLK. */
#وصف_ڪريو پورٽ_ACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#وصف_ڪريو پورٽ_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#وصف_ڪريو پورٽ_FLAGS_INT_ENABLED           ( ( ڍير_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
 * time a critical section is entered the count is incremented.  Each time a
 * critical section is exited the count is decremented - with interrupts only
 * being re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as this will cause problems during the startup
 * sequence. */
متطاير uint16_t usCriticalNesting = پورٽ_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    uint16_t * pus_چوٽي_جو_ڍير;
    uint32_t * pul_چوٽي_جو_ڍير;

    /*
     *  Place a few bytes of known values on the bottom of the stack.
     *  This is just useful for debugging and can be included if required.
     *
     * pxTopOfStack = ( StackType_t ) 0x1111;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x2222;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x3333;
     */

    /* StackType_t is either 16 bits or 32 bits depending on the data model.
     * Some stacked items do not change size depending on the data model so have
     * to be explicitly cast to the correct size so this function will work
     * whichever data model is being used. */
    إذا( حجم( ڍير_Type_t ) == حجم( uint16_t ) )
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_چوٽي_جو_ڍير = ( uint16_t * ) px_چوٽي_جو_ڍير;
        pus_چوٽي_جو_ڍير--;
        pul_چوٽي_جو_ڍير = ( uint32_t * ) pus_چوٽي_جو_ڍير;
    }
    وإلا
    {
        pul_چوٽي_جو_ڍير = ( uint32_t * ) px_چوٽي_جو_ڍير;
    }

    *pul_چوٽي_جو_ڍير = ( uint32_t ) px_ڪوڊ;

    pus_چوٽي_جو_ڍير = ( uint16_t * ) pul_چوٽي_جو_ڍير;
    pus_چوٽي_جو_ڍير--;
    *pus_چوٽي_جو_ڍير = پورٽ_FLAGS_INT_ENABLED;
    pus_چوٽي_جو_ڍير -= ( حجم( ڍير_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_چوٽي_جو_ڍير = ( ڍير_Type_t * ) pus_چوٽي_جو_ڍير;

    /* Next the general purpose registers. */
    #جيڪڏهن_وصف_ٿيل PRELOAD_رجسٽر_قدرون
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xffff;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xeeee;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xdddd;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xbbbb;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xaaaa;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x9999;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x8888;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x5555;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x6666;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x5555;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x4444;
        px_چوٽي_جو_ڍير--;
    #وإلا /* ifdef PRELOAD_REGISTER_VALUES */
        px_چوٽي_جو_ڍير -= 3;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;
        px_چوٽي_جو_ڍير -= 9;
    #جيڪڏهن_پورو /* ifdef PRELOAD_REGISTER_VALUES */


    /* A variable is used to keep track of the critical section nesting.
     * This variable has to be stored as part of the task context and is
     * initially set to zero. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ )
{
    v_Application_تياري_Timer_مداخلت();
}
/*-----------------------------------------------------------*/

#هدايت ويڪٽر=config_TICK_ويڪٽر
__interrupt __raw فراغ vTickISREntry( فراغ )
{
    خارجي فراغ v_پورٽ_Tick_ISR( فراغ );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    v_پورٽ_Tick_ISR();
}
