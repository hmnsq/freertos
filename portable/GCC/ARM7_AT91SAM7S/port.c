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
#અન્તર્ભાવ <stdlib.h>

/* Scheduler includes. */
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"

/* Processor constants. */
#અન્તર્ભાવ "AT91SAM7X256.h"

/* Constants required to setup the task context. */
#define portINITIAL_SPSR                   ( ( ઢગલો_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT                 ( ( ઢગલો_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE               ( ( ઢગલો_Type_t ) 4 )
#define portNO_CRITICAL_SECTION_NESTING    ( ( ઢગલો_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#define portENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#define port_PRESCALE_કિંમત                 0x00
#define portINTERRUPT_ON_MATCH             ( ( uint32_t ) 0x01 )
#define port_RESET_ગણતરી_ON_MATCH           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#define port_PIT_CLOCK_ભાજક              ( ( uint32_t ) 16 )
#define port_PIT_COUNTER_કિંમત              ( ( ( configCPU_CLOCK_HZ / port_PIT_CLOCK_ભાજક ) / 1000UL ) * portTICK_PERIOD_MS )

#define portINT_LEVEL_SENSITIVE            0
#define portPIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#define portPIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
સ્થિર શૂન્ય prvSetupTimerInterrupt( શૂન્ય );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
બાહ્ય શૂન્ય vPortISRStartFirstTask( શૂન્ય );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                     TaskFunction_t pxCode,
                                     શૂન્ય * pvParameters )
{
    ઢગલો_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_ટોચ_Of_ઢગલો;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_ટોચ_Of_ઢગલો--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_ટોચ_Of_ઢગલો--;

    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x00000000;    /* R14 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x12121212;    /* R12 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x11111111;    /* R11 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x10101010;    /* R10 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x09090909;    /* R9 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x08080808;    /* R8 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x07070707;    /* R7 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x06060606;    /* R6 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x05050505;    /* R5 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x04040404;    /* R4 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x03030303;    /* R3 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x02020202;    /* R2 */
    px_ટોચ_Of_ઢગલો--;
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) 0x01010101;    /* R1 */
    px_ટોચ_Of_ઢગલો--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) pvParameters; /* R0 */
    px_ટોચ_Of_ઢગલો--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t ) portINITIAL_SPSR;

    #ifdef THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_ટોચ_Of_ઢગલો |= portTHUMB_MODE_BIT;
    }
    #endif

    px_ટોચ_Of_ઢગલો--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ટોચ_Of_ઢગલો = portNO_CRITICAL_SECTION_NESTING;

    પાછા px_ટોચ_Of_ઢગલો;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( શૂન્ય )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortISRStartFirstTask();

    /* Should not get here! */
    પાછા 0;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEndScheduler( શૂન્ય )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
સ્થિર શૂન્ય prvSetupTimerInterrupt( શૂન્ય )
{
    AT91PS_PITC pxPIT = AT91C_BASE_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #જો configUSE_PREEMPTION == 0
        બાહ્ય શૂન્ય( vNonPreemptiveTick ) ( શૂન્ય );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91C_AIC_PRIOR_HIGHEST, portINT_LEVEL_SENSITIVE, ( શૂન્ય ( * )( શૂન્ય ) )vNonPreemptiveTick );
    #નહીંતર
        બાહ્ય શૂન્ય( vPreemptiveTick )( શૂન્ય );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91C_AIC_PRIOR_HIGHEST, portINT_LEVEL_SENSITIVE, ( શૂન્ય ( * )( શૂન્ય ) )vPreemptiveTick );
    #endif

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = portPIT_ENABLE | portPIT_INT_ENABLE | port_PIT_COUNTER_કિંમત;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91C_BASE_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
