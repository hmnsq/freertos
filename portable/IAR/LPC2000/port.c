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
* Implementation of functions defined in portable.h for the Philips ARM7 port.
*----------------------------------------------------------*/

/*
 *  Changes from V3.2.2
 *
 + Bug fix - The prescale value for the timer setup is now written to T0PR
 +    instead of T0PC.  This bug would have had no effect unless a prescale
 +    value was actually used.
 */

/* Standard includes. */
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <intrinsics.h>

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Constants required to setup the tick ISR. */
#define portENABLE_TIMER             ( ( uint8_t ) 0x01 )
#define port_PRESCALE_মান           0x00
#define portINTERRUPT_ON_MATCH       ( ( uint32_t ) 0x01 )
#define port_RESET_গুনতি_ON_MATCH     ( ( uint32_t ) 0x02 )

/* Constants required to setup the initial stack. */
#define portINITIAL_SPSR             ( ( স্তূপ_Type_t ) 0x1f )    /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT           ( ( স্তূপ_Type_t ) 0x20 )
#define port_INSTRUCTION_আকার         ( ( স্তূপ_Type_t ) 4 )

/* Constants required to setup the PIT. */
#define port_PIT_CLOCK_ভাজক        ( ( uint32_t ) 16 )
#define port_PIT_গণক_মান        ( ( ( configCPU_CLOCK_HZ / port_PIT_CLOCK_ভাজক ) / 1000UL ) * portTICK_PERIOD_MS )

/* Constants required to handle interrupts. */
#define portTIMER_MATCH_ISR_BIT      ( ( uint8_t ) 0x01 )
#define portCLEAR_VIC_INTERRUPT      ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#define portNO_CRITICAL_NESTING      ( ( uint32_t ) 0 )


#define portINT_LEVEL_SENSITIVE      0
#define portPIT_ENABLE               ( ( uint16_t ) 0x1 << 24 )
#define portPIT_INT_ENABLE           ( ( uint16_t ) 0x1 << 25 )

/* Constants required to setup the VIC for the tick ISR. */
#define portTIMER_VIC_CHANNEL        ( ( uint32_t ) 0x0004 )
#define portTIMER_VIC_CHANNEL_BIT    ( ( uint32_t ) 0x0010 )
#define portTIMER_VIC_ENABLE         ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
স্থির শূন্য prvSetupTimerInterrupt( শূন্য );

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
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    স্তূপ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_শীর্ষ_Of_স্তূপ;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxCode + port_INSTRUCTION_আকার;
    px_শীর্ষ_Of_স্তূপ--;

    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x12121212;    /* R12 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x11111111;    /* R11 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x10101010;    /* R10 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x09090909;    /* R9 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x08080808;    /* R8 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x07070707;    /* R7 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x06060606;    /* R6 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x05050505;    /* R5 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x04040404;    /* R4 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x03030303;    /* R3 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x02020202;    /* R2 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x01010101;    /* R1 */
    px_শীর্ষ_Of_স্তূপ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters; /* R0 */
    px_শীর্ষ_Of_স্তূপ--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) portINITIAL_SPSR;

    যদি( ( ( uint32_t ) pxCode & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_শীর্ষ_Of_স্তূপ |= portTHUMB_MODE_BIT;
    }

    px_শীর্ষ_Of_স্তূপ--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_শীর্ষ_Of_স্তূপ = portNO_CRITICAL_NESTING;

    ফেরত px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    বাহ্যিক শূন্য vPortStartFirstTask( শূন্য );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    ফেরত 0;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#যদি configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    স্থির __arm __irq শূন্য vPortNonPreemptiveTick( শূন্য );
    স্থির __arm __irq শূন্য vPortNonPreemptiveTick( শূন্য )
    {
        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Ready for the next interrupt. */
        T0IR = portTIMER_MATCH_ISR_BIT;
        VICVectAddr = portCLEAR_VIC_INTERRUPT;
    }

#অন্যথা /* if configUSE_PREEMPTION == 0 */

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
    শূন্য vPortPreemptiveTick( শূন্য );
    শূন্য vPortPreemptiveTick( শূন্য )
    {
        /* Increment the tick counter. */
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            /* The new tick value might unblock a task.  Ensure the highest task that
             * is ready to execute is the task that will execute when the tick ISR
             * exits. */
            vTaskSwitchContext();
        }

        /* Ready for the next interrupt. */
        T0IR = portTIMER_MATCH_ISR_BIT;
        VICVectAddr = portCLEAR_VIC_INTERRUPT;
    }

#endif /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

স্থির শূন্য prvSetupTimerInterrupt( শূন্য )
{
    uint32_t ulCompareMatch;

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = port_PRESCALE_মান;

    /* Calculate the match value required for our wanted tick rate. */
    ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #যদি port_PRESCALE_মান != 0
    {
        ulCompareMatch /= ( port_PRESCALE_মান + 1 );
    }
    #endif

    T0MR0 = ulCompareMatch;

    /* Generate tick with timer 0 compare match. */
    T0MCR = port_RESET_গুনতি_ON_MATCH | portINTERRUPT_ON_MATCH;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( portTIMER_VIC_CHANNEL_BIT );
    VICIntEnable |= portTIMER_VIC_CHANNEL_BIT;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #যদি configUSE_PREEMPTION == 1
    {
        বাহ্যিক শূন্য( vPortPreemptiveTickEntry )( শূন্য );

        VICVectAddr0 = ( uint32_t ) vPortPreemptiveTickEntry;
    }
    #অন্যথা
    {
        বাহ্যিক শূন্য( vNonPreemptiveTick )( শূন্য );

        VICVectAddr0 = ( int32_t ) vPortNonPreemptiveTick;
    }
    #endif /* if configUSE_PREEMPTION == 1 */

    VICVectCntl0 = portTIMER_VIC_CHANNEL | portTIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = portENABLE_TIMER;
}
/*-----------------------------------------------------------*/

শূন্য vPortEnterCritical( শূন্য )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

শূন্য vPortExitCritical( শূন্য )
{
    যদি( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        যদি( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
