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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Hardware includes. */
#अन्तर्भाव "msp430.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the MSP430X port.
*----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
 * not the MCLK. */
#define portACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#define portINITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#define portFLAGS_INT_ENABLED           ( ( ढेर_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
प्रकारनिर्देश शून्य TCB_t;
बाह्य चञ्चल TCB_t * चञ्चल pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each
 * time a critical section is entered the count is incremented.  Each time a
 * critical section is exited the count is decremented - with interrupts only
 * being re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as this will cause problems during the startup
 * sequence. */
चञ्चल uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/


/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
शून्य vPortSetupTimerInterrupt( शून्य );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    uint16_t * pus_शीर्ष_Of_ढेर;
    uint32_t * pul_शीर्ष_Of_ढेर;

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
    यदि( परिमाण( ढेर_Type_t ) == परिमाण( uint16_t ) )
    {
        /* Make room for a 20 bit value stored as a 32 bit value. */
        pus_शीर्ष_Of_ढेर = ( uint16_t * ) px_शीर्ष_Of_ढेर;
        pus_शीर्ष_Of_ढेर--;
        pul_शीर्ष_Of_ढेर = ( uint32_t * ) pus_शीर्ष_Of_ढेर;
    }
    अन्यथा
    {
        pul_शीर्ष_Of_ढेर = ( uint32_t * ) px_शीर्ष_Of_ढेर;
    }

    *pul_शीर्ष_Of_ढेर = ( uint32_t ) pxCode;

    pus_शीर्ष_Of_ढेर = ( uint16_t * ) pul_शीर्ष_Of_ढेर;
    pus_शीर्ष_Of_ढेर--;
    *pus_शीर्ष_Of_ढेर = portFLAGS_INT_ENABLED;
    pus_शीर्ष_Of_ढेर -= ( परिमाण( ढेर_Type_t ) / 2 );

    /* From here on the size of stacked items depends on the memory model. */
    px_शीर्ष_Of_ढेर = ( ढेर_Type_t * ) pus_शीर्ष_Of_ढेर;

    /* Next the general purpose registers. */
    #ifdef PRELOAD_REGISTER_मूल्यावली
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xffff;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xeeee;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xdddd;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xbbbb;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xaaaa;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x9999;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x8888;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x5555;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x6666;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x5555;
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x4444;
        px_शीर्ष_Of_ढेर--;
    #अन्यथा /* ifdef PRELOAD_REGISTER_VALUES */
        px_शीर्ष_Of_ढेर -= 3;
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters;
        px_शीर्ष_Of_ढेर -= 9;
    #endif /* ifdef PRELOAD_REGISTER_VALUES */


    /* A variable is used to keep track of the critical section nesting.
     * This variable has to be stored as part of the task context and is
     * initially set to zero. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portNO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    प्रत्यागम px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.
 */
शून्य vPortSetupTimerInterrupt( शून्य )
{
    vApplicationSetupTimerInterrupt();
}
/*-----------------------------------------------------------*/

#pragma vector=configTICK_VECTOR
__interrupt __raw शून्य vTickISREntry( शून्य )
{
    बाह्य शून्य vPortTickISR( शून्य );

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
    vPortTickISR();
}
