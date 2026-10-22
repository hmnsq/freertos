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
* Implementation of functions defined in portable.h for the Atmel AT91R40008
* port.
*
* Components that can be compiled to either ARM or THUMB mode are
* contained in this file.  The ISR routines, which can only be compiled
* to ARM mode are contained in portISR.c.
*----------------------------------------------------------*/

/* Standard includes. */
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Hardware specific definitions. */
#ضمن "AT91R40008.h"
#ضمن "pio.h"
#ضمن "aic.h"
#ضمن "tc.h"

/* Constants required to setup the task context. */
#define portINITIAL_SPSR                   ( ( تيندنن_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT                 ( ( تيندنن_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE               ( ( تيندنن_Type_t ) 4 )
#define portNO_CRITICAL_SECTION_NESTING    ( ( تيندنن_Type_t ) 0 )
#define portTICK_PRIORITY_6                ( 6 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prvSetupTimerInterrupt( فراغ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
خارجي فراغ vPortISRStartFirstTask( فراغ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
تيندنن_Type_t * px_Port_Initialise_تيندنن( تيندنن_Type_t * px_اتس_Of_تيندنن,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    تيندنن_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_اتس_Of_تيندنن;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_اتس_Of_تيندنن--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_اتس_Of_تيندنن--;

    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x12121212;    /* R12 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x11111111;    /* R11 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x10101010;    /* R10 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x09090909;    /* R9 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x08080808;    /* R8 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x07070707;    /* R7 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x06060606;    /* R6 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x05050505;    /* R5 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x04040404;    /* R4 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x03030303;    /* R3 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x02020202;    /* R2 */
    px_اتس_Of_تيندنن--;
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) 0x01010101;    /* R1 */
    px_اتس_Of_تيندنن--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) pvParameters; /* R0 */
    px_اتس_Of_تيندنن--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_اتس_Of_تيندنن = ( تيندنن_Type_t ) portINITIAL_SPSR;

    #ifdef THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_اتس_Of_تيندنن |= portTHUMB_MODE_BIT;
    }
    #endif

    px_اتس_Of_تيندنن--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_اتس_Of_تيندنن = portNO_CRITICAL_SECTION_NESTING;

    أرجع px_اتس_Of_تيندنن;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortISRStartFirstTask();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the tick timer to generate the tick interrupts at the required frequency.
 */
ساكن فراغ prvSetupTimerInterrupt( فراغ )
{
    متطاير uint32_t ulDummy;

    /* Enable clock to the tick timer... */
    AT91C_BASE_PS->PS_PCER = portTIMER_CLK_ENABLE_BIT;

    /* Stop the tick timer... */
    portTIMER_REG_BASE_PTR->TC_CCR = TC_CLKDIS;

    /* Start with tick timer interrupts disabled... */
    portTIMER_REG_BASE_PTR->TC_IDR = 0xFFFFFFFF;

    /* Clear any pending tick timer interrupts... */
    ulDummy = portTIMER_REG_BASE_PTR->TC_SR;

    /* Store interrupt handler function address in tick timer vector register...
     * The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #إذا configUSE_PREEMPTION == 1
    {
        خارجي فراغ( vPreemptiveTick )( فراغ );
        AT91C_BASE_AIC->AIC_SVR[ portTIMER_AIC_CHANNEL ] = ( uint32_t ) vPreemptiveTick;
    }
    #وإلا // else use cooperative scheduler
    {
        خارجي فراغ( vNonPreemptiveTick )( فراغ );
        AT91C_BASE_AIC->AIC_SVR[ portTIMER_AIC_CHANNEL ] = ( uint32_t ) vNonPreemptiveTick;
    }
    #endif

    /* Tick timer interrupt level-sensitive, priority 6... */
    AT91C_BASE_AIC->AIC_SMR[ portTIMER_AIC_CHANNEL ] = AIC_SRCTYPE_INT_LEVEL_SENSITIVE | portTICK_PRIORITY_6;

    /* Enable the tick timer interrupt...
     *
     * First at timer level */
    portTIMER_REG_BASE_PTR->TC_IER = TC_CPCS;

    /* Then at the AIC level. */
    AT91C_BASE_AIC->AIC_IECR = ( 1 << portTIMER_AIC_CHANNEL );

    /* Calculate timer compare value to achieve the desired tick rate... */
    إذا( ( configCPU_CLOCK_HZ / ( configTICK_RATE_HZ * 2 ) ) <= 0xFFFF )
    {
        /* The tick rate is fast enough for us to use the faster timer input
         * clock (main clock / 2). */
        portTIMER_REG_BASE_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK2 | TC_BURST_NONE | TC_CPCTRG;
        portTIMER_REG_BASE_PTR->TC_RC = configCPU_CLOCK_HZ / ( configTICK_RATE_HZ * 2 );
    }
    وإلا
    {
        /* We must use a slower timer input clock (main clock / 8) because the
         * tick rate is too slow for the faster input clock. */
        portTIMER_REG_BASE_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK8 | TC_BURST_NONE | TC_CPCTRG;
        portTIMER_REG_BASE_PTR->TC_RC = configCPU_CLOCK_HZ / ( configTICK_RATE_HZ * 8 );
    }

    /* Start tick timer... */
    portTIMER_REG_BASE_PTR->TC_CCR = TC_SWTRG | TC_CLKEN;
}
/*-----------------------------------------------------------*/
