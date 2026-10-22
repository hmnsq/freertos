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
#ضمن <stdlib.h>
#ضمن <intrinsics.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to setup the tick ISR. */
#تعریف_کړه پورټ_ENABLE_TIMER             ( ( uint8_t ) 0x01 )
#تعریف_کړه پورټ_PRESCALE_ارزښت           0x00
#تعریف_کړه پورټ_مداخله_ON_سمون       ( ( uint32_t ) 0x01 )
#تعریف_کړه پورټ_RESET_شمېر_ON_سمون     ( ( uint32_t ) 0x02 )

/* Constants required to setup the initial stack. */
#تعریف_کړه پورټ_INITIAL_SPSR             ( ( ډېری_Type_t ) 0x1f )    /* System mode, ARM mode, interrupts enabled. */
#تعریف_کړه پورټ_THUMB_ډېرپېښ_بټ           ( ( ډېری_Type_t ) 0x20 )
#تعریف_کړه پورټ_INSTRUCTION_اندازه         ( ( ډېری_Type_t ) 4 )

/* Constants required to setup the PIT. */
#تعریف_کړه پورټ_PIT_CLOCK_وېشونکی        ( ( uint32_t ) 16 )
#تعریف_کړه پورټ_PIT_COUNTER_ارزښت        ( ( ( configCPU_CLOCK_HZ / پورټ_PIT_CLOCK_وېشونکی ) / 1000UL ) * پورټ_TICK_PERIOD_MS )

/* Constants required to handle interrupts. */
#تعریف_کړه پورټ_TIMER_سمون_ISR_بټ      ( ( uint8_t ) 0x01 )
#تعریف_کړه پورټ_CLEAR_VIC_مداخله      ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING      ( ( uint32_t ) 0 )


#تعریف_کړه پورټ_INT_LEVEL_SENSITIVE      0
#تعریف_کړه پورټ_PIT_ENABLE               ( ( uint16_t ) 0x1 << 24 )
#تعریف_کړه پورټ_PIT_INT_ENABLE           ( ( uint16_t ) 0x1 << 25 )

/* Constants required to setup the VIC for the tick ISR. */
#تعریف_کړه پورټ_TIMER_VIC_CHANNEL        ( ( uint32_t ) 0x0004 )
#تعریف_کړه پورټ_TIMER_VIC_CHANNEL_بټ    ( ( uint32_t ) 0x0010 )
#تعریف_کړه پورټ_TIMER_VIC_ENABLE         ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

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
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    ډېری_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_سر_د_ډېری;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ + پورټ_INSTRUCTION_اندازه;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12121212;    /* R12 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11111111;    /* R11 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10101010;    /* R10 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09090909;    /* R9 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x08080808;    /* R8 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07070707;    /* R7 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06060606;    /* R6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x05050505;    /* R5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04040404;    /* R4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03030303;    /* R3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x02020202;    /* R2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x01010101;    /* R1 */
    px_سر_د_ډېری--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */
    px_سر_د_ډېری--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_کوډ & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_سر_د_ډېری |= پورټ_THUMB_ډېرپېښ_بټ;
    }

    px_سر_د_ډېری--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخله();

    /* Start the first task. */
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    ساكن __arm __irq فراغ v_پورټ_Non_Preemptive_Tick( فراغ );
    ساكن __arm __irq فراغ v_پورټ_Non_Preemptive_Tick( فراغ )
    {
        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Ready for the next interrupt. */
        T0IR = پورټ_TIMER_سمون_ISR_بټ;
        VICVectAddr = پورټ_CLEAR_VIC_مداخله;
    }

#وإلا /* if configUSE_PREEMPTION == 0 */

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
    فراغ v_پورټ_Preemptive_Tick( فراغ );
    فراغ v_پورټ_Preemptive_Tick( فراغ )
    {
        /* Increment the tick counter. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* The new tick value might unblock a task.  Ensure the highest task that
             * is ready to execute is the task that will execute when the tick ISR
             * exits. */
            vTaskSwitchContext();
        }

        /* Ready for the next interrupt. */
        T0IR = پورټ_TIMER_سمون_ISR_بټ;
        VICVectAddr = پورټ_CLEAR_VIC_مداخله;
    }

#د_که_پای /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    uint32_t ul_Compare_سمون;

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = پورټ_PRESCALE_ارزښت;

    /* Calculate the match value required for our wanted tick rate. */
    ul_Compare_سمون = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #إذا پورټ_PRESCALE_ارزښت != 0
    {
        ul_Compare_سمون /= ( پورټ_PRESCALE_ارزښت + 1 );
    }
    #د_که_پای

    T0MR0 = ul_Compare_سمون;

    /* Generate tick with timer 0 compare match. */
    T0MCR = پورټ_RESET_شمېر_ON_سمون | پورټ_مداخله_ON_سمون;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( پورټ_TIMER_VIC_CHANNEL_بټ );
    VICIntEnable |= پورټ_TIMER_VIC_CHANNEL_بټ;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #إذا configUSE_PREEMPTION == 1
    {
        خارجي فراغ( v_پورټ_Preemptive_Tick_ثبت )( فراغ );

        VICVectAddr0 = ( uint32_t ) v_پورټ_Preemptive_Tick_ثبت;
    }
    #وإلا
    {
        خارجي فراغ( vNonPreemptiveTick )( فراغ );

        VICVectAddr0 = ( int32_t ) v_پورټ_Non_Preemptive_Tick;
    }
    #د_که_پای /* if configUSE_PREEMPTION == 1 */

    VICVectCntl0 = پورټ_TIMER_VIC_CHANNEL | پورټ_TIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = پورټ_ENABLE_TIMER;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورټ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == پورټ_NO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
