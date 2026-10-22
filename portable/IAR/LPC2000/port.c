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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_TIMER             ( ( uint8_t ) 0x01 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRESCALE_ಮೌಲ್ಯ           0x00
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಡಚಣೆ_ON_ಹೊಂದಿಕೆ       ( ( uint32_t ) 0x01 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_ಎಣಿಕೆ_ON_ಹೊಂದಿಕೆ     ( ( uint32_t ) 0x02 )

/* Constants required to setup the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR             ( ( ರಾಶಿ_Type_t ) 0x1f )    /* System mode, ARM mode, interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್           ( ( ರಾಶಿ_Type_t ) 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ         ( ( ರಾಶಿ_Type_t ) 4 )

/* Constants required to setup the PIT. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_CLOCK_ಭಾಜಕ        ( ( uint32_t ) 16 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_COUNTER_ಮೌಲ್ಯ        ( ( ( configCPU_CLOCK_HZ / ಪೋರ್ಟ್_PIT_CLOCK_ಭಾಜಕ ) / 1000UL ) * ಪೋರ್ಟ್_TICK_PERIOD_MS )

/* Constants required to handle interrupts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_ಹೊಂದಿಕೆ_ISR_ಬಿಟ್      ( ( uint8_t ) 0x01 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_VIC_ಅಡಚಣೆ      ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING      ( ( uint32_t ) 0 )


#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_LEVEL_SENSITIVE      0
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_ENABLE               ( ( uint16_t ) 0x1 << 24 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_INT_ENABLE           ( ( uint16_t ) 0x1 << 25 )

/* Constants required to setup the VIC for the tick ISR. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_VIC_CHANNEL        ( ( uint32_t ) 0x0004 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_VIC_CHANNEL_ಬಿಟ್    ( ( uint32_t ) 0x0010 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_VIC_ENABLE         ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

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
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ರಾಶಿ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_ತುದಿ_ದ_ರಾಶಿ;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ + ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212;    /* R12 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;    /* R11 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010;    /* R10 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909;    /* R9 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808;    /* R8 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707;    /* R7 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606;    /* R6 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505;    /* R5 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404;    /* R4 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303;    /* R3 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202;    /* R2 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101;    /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_INITIAL_SPSR;

    ಆದರೆ( ( ( uint32_t ) px_ಸಂಕೇತ & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Start the first task. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#ಆದರೆ configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    ಸ್ಥಿರ __arm __irq ಶೂನ್ಯ v_ಪೋರ್ಟ್_Non_Preemptive_Tick( ಶೂನ್ಯ );
    ಸ್ಥಿರ __arm __irq ಶೂನ್ಯ v_ಪೋರ್ಟ್_Non_Preemptive_Tick( ಶೂನ್ಯ )
    {
        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Ready for the next interrupt. */
        T0IR = ಪೋರ್ಟ್_TIMER_ಹೊಂದಿಕೆ_ISR_ಬಿಟ್;
        VICVectAddr = ಪೋರ್ಟ್_CLEAR_VIC_ಅಡಚಣೆ;
    }

#ಇಲ್ಲದಿದ್ದರೆ /* if configUSE_PREEMPTION == 0 */

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Preemptive_Tick( ಶೂನ್ಯ );
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Preemptive_Tick( ಶೂನ್ಯ )
    {
        /* Increment the tick counter. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* The new tick value might unblock a task.  Ensure the highest task that
             * is ready to execute is the task that will execute when the tick ISR
             * exits. */
            vTaskSwitchContext();
        }

        /* Ready for the next interrupt. */
        T0IR = ಪೋರ್ಟ್_TIMER_ಹೊಂದಿಕೆ_ISR_ಬಿಟ್;
        VICVectAddr = ಪೋರ್ಟ್_CLEAR_VIC_ಅಡಚಣೆ;
    }

#ಆದರೆ_ಅಂತ್ಯ /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    uint32_t ul_Compare_ಹೊಂದಿಕೆ;

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = ಪೋರ್ಟ್_PRESCALE_ಮೌಲ್ಯ;

    /* Calculate the match value required for our wanted tick rate. */
    ul_Compare_ಹೊಂದಿಕೆ = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #ಆದರೆ ಪೋರ್ಟ್_PRESCALE_ಮೌಲ್ಯ != 0
    {
        ul_Compare_ಹೊಂದಿಕೆ /= ( ಪೋರ್ಟ್_PRESCALE_ಮೌಲ್ಯ + 1 );
    }
    #ಆದರೆ_ಅಂತ್ಯ

    T0MR0 = ul_Compare_ಹೊಂದಿಕೆ;

    /* Generate tick with timer 0 compare match. */
    T0MCR = ಪೋರ್ಟ್_RESET_ಎಣಿಕೆ_ON_ಹೊಂದಿಕೆ | ಪೋರ್ಟ್_ಅಡಚಣೆ_ON_ಹೊಂದಿಕೆ;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( ಪೋರ್ಟ್_TIMER_VIC_CHANNEL_ಬಿಟ್ );
    VICIntEnable |= ಪೋರ್ಟ್_TIMER_VIC_CHANNEL_ಬಿಟ್;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #ಆದರೆ configUSE_PREEMPTION == 1
    {
        ಬಾಹ್ಯ ಶೂನ್ಯ( v_ಪೋರ್ಟ್_Preemptive_Tick_ನಮೂದು )( ಶೂನ್ಯ );

        VICVectAddr0 = ( uint32_t ) v_ಪೋರ್ಟ್_Preemptive_Tick_ನಮೂದು;
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        ಬಾಹ್ಯ ಶೂನ್ಯ( vNonPreemptiveTick )( ಶೂನ್ಯ );

        VICVectAddr0 = ( int32_t ) v_ಪೋರ್ಟ್_Non_Preemptive_Tick;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if configUSE_PREEMPTION == 1 */

    VICVectCntl0 = ಪೋರ್ಟ್_TIMER_VIC_CHANNEL | ಪೋರ್ಟ್_TIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = ಪೋರ್ಟ್_ENABLE_TIMER;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
