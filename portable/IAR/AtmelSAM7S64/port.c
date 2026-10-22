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
* Implementation of functions defined in portable.h for the Atmel ARM7 port.
*----------------------------------------------------------*/


/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Constants required to setup the initial stack. */
#define portINITIAL_SPSR           ( ( सालानसान_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT         ( ( सालानसान_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE       ( ( सालानसान_Type_t ) 4 )

/* Constants required to setup the PIT. */
#define port_PIT_CLOCK_पांगहाति      ( ( uint32_t ) 16 )
#define port_PIT_COUNTER_हालागा      ( ( ( configCPU_CLOCK_HZ / port_PIT_CLOCK_पांगहाति ) / 1000UL ) * portTICK_PERIOD_MS )

/* Constants required to handle critical sections. */
#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )


#define portINT_LEVEL_SENSITIVE    0
#define portPIT_ENABLE             ( ( uint16_t ) 0x1 << 24 )
#define portPIT_INT_ENABLE         ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
static void prvSetupTimerInterrupt( void );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
सालानसान_Type_t * px_Port_Initialise_सालानसान( सालानसान_Type_t * px_इताअस_Of_सालानसान,
                                     TaskFunction_t pxCode,
                                     void * pvParameters )
{
    सालानसान_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_इताअस_Of_सालानसान;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_इताअस_Of_सालानसान--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_इताअस_Of_सालानसान--;

    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x12121212;    /* R12 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x11111111;    /* R11 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x10101010;    /* R10 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x09090909;    /* R9 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x08080808;    /* R8 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x07070707;    /* R7 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x06060606;    /* R6 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x05050505;    /* R5 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x04040404;    /* R4 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x03030303;    /* R3 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x02020202;    /* R2 */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x01010101;    /* R1 */
    px_इताअस_Of_सालानसान--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) pvParameters; /* R0 */
    px_इताअस_Of_सालानसान--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) portINITIAL_SPSR;

    if( ( ( uint32_t ) pxCode & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_इताअस_Of_सालानसान |= portTHUMB_MODE_BIT;
    }

    px_इताअस_Of_सालानसान--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_इताअस_Of_सालानसान = portNO_CRITICAL_NESTING;

    return px_इताअस_Of_सालानसान;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
    extern void vPortStartFirstTask( void );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    return 0;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#if configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    static __arm __irq void vPortNonPreemptiveTick( void );
    static __arm __irq void vPortNonPreemptiveTick( void )
    {
        uint32_t ulDummy;

        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Clear the PIT interrupt. */
        ulDummy = AT91C_BASE_PITC->PITC_PIVR;

        /* End the interrupt in the AIC. */
        AT91C_BASE_AIC->AIC_EOICR = ulDummy;
    }

#else /* if configUSE_PREEMPTION == 0 */

/* Currently the IAR port requires the preemptive tick function to be
 * defined in an asm file. */

#endif /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

static void prvSetupTimerInterrupt( void )
{
    AT91PS_PITC pxPIT = AT91C_BASE_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #if configUSE_PREEMPTION == 0
        AT91F_AIC_ConfigureIt( AT91C_BASE_AIC, AT91C_ID_SYS, AT91C_AIC_PRIOR_HIGHEST, portINT_LEVEL_SENSITIVE, ( void ( * )( void ) )vPortNonPreemptiveTick );
    #else
        extern void( vPortPreemptiveTick )( void );
        AT91F_AIC_ConfigureIt( AT91C_BASE_AIC, AT91C_ID_SYS, AT91C_AIC_PRIOR_HIGHEST, portINT_LEVEL_SENSITIVE, ( void ( * )( void ) )vPortPreemptiveTick );
    #endif

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = portPIT_ENABLE | portPIT_INT_ENABLE | port_PIT_COUNTER_हालागा;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91F_AIC_EnableIt( AT91C_BASE_AIC, AT91C_ID_SYS );
}
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
    if( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        if( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
