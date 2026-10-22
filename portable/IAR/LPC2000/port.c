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
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <intrinsics.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to setup the tick ISR. */
#define portENABLE_TIMER             ( ( uint8_t ) 0x01 )
#define port_PRESCALE_ಮೌಲ್ಯ           0x00
#define portINTERRUPT_ON_MATCH       ( ( uint32_t ) 0x01 )
#define port_RESET_ಎಣಿಕೆ_ON_MATCH     ( ( uint32_t ) 0x02 )

/* Constants required to setup the initial stack. */
#define portINITIAL_SPSR             ( ( ರಾಶಿ_Type_t ) 0x1f )    /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT           ( ( ರಾಶಿ_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE         ( ( ರಾಶಿ_Type_t ) 4 )

/* Constants required to setup the PIT. */
#define port_PIT_CLOCK_ಭಾಜಕ        ( ( uint32_t ) 16 )
#define port_PIT_COUNTER_ಮೌಲ್ಯ        ( ( ( configCPU_CLOCK_HZ / port_PIT_CLOCK_ಭಾಜಕ ) / 1000UL ) * portTICK_PERIOD_MS )

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
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ );

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
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    ರಾಶಿ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_ತುದಿ_Of_ರಾಶಿ;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212;    /* R12 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;    /* R11 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010;    /* R10 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909;    /* R9 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808;    /* R8 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707;    /* R7 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606;    /* R6 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505;    /* R5 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404;    /* R4 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303;    /* R3 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202;    /* R2 */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101;    /* R1 */
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) portINITIAL_SPSR;

    ಯದಿ( ( ( uint32_t ) pxCode & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_ತುದಿ_Of_ರಾಶಿ |= portTHUMB_MODE_BIT;
    }

    px_ತುದಿ_Of_ರಾಶಿ--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ತುದಿ_Of_ರಾಶಿ = portNO_CRITICAL_NESTING;

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ vPortStartFirstTask( ಶೂನ್ಯ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    ಪ್ರತ್ಯಾಗಮ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#ಯದಿ configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    ಸ್ಥಿರ __arm __irq ಶೂನ್ಯ vPortNonPreemptiveTick( ಶೂನ್ಯ );
    ಸ್ಥಿರ __arm __irq ಶೂನ್ಯ vPortNonPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Ready for the next interrupt. */
        T0IR = portTIMER_MATCH_ISR_BIT;
        VICVectAddr = portCLEAR_VIC_INTERRUPT;
    }

#ಅನ್ಯಥಾ /* if configUSE_PREEMPTION == 0 */

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
    ಶೂನ್ಯ vPortPreemptiveTick( ಶೂನ್ಯ );
    ಶೂನ್ಯ vPortPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Increment the tick counter. */
        ಯದಿ( xTaskIncrementTick() != pdFALSE )
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

ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    uint32_t ulCompareMatch;

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = port_PRESCALE_ಮೌಲ್ಯ;

    /* Calculate the match value required for our wanted tick rate. */
    ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #ಯದಿ port_PRESCALE_ಮೌಲ್ಯ != 0
    {
        ulCompareMatch /= ( port_PRESCALE_ಮೌಲ್ಯ + 1 );
    }
    #endif

    T0MR0 = ulCompareMatch;

    /* Generate tick with timer 0 compare match. */
    T0MCR = port_RESET_ಎಣಿಕೆ_ON_MATCH | portINTERRUPT_ON_MATCH;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( portTIMER_VIC_CHANNEL_BIT );
    VICIntEnable |= portTIMER_VIC_CHANNEL_BIT;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #ಯದಿ configUSE_PREEMPTION == 1
    {
        ಬಾಹ್ಯ ಶೂನ್ಯ( vPortPreemptiveTickEntry )( ಶೂನ್ಯ );

        VICVectAddr0 = ( uint32_t ) vPortPreemptiveTickEntry;
    }
    #ಅನ್ಯಥಾ
    {
        ಬಾಹ್ಯ ಶೂನ್ಯ( vNonPreemptiveTick )( ಶೂನ್ಯ );

        VICVectAddr0 = ( int32_t ) vPortNonPreemptiveTick;
    }
    #endif /* if configUSE_PREEMPTION == 1 */

    VICVectCntl0 = portTIMER_VIC_CHANNEL | portTIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = portENABLE_TIMER;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ )
{
    ಯದಿ( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ಯದಿ( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
