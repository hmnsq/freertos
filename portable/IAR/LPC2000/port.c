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
#وصف_ڪريو پورٽ_ENABLE_TIMER             ( ( uint8_t ) 0x01 )
#وصف_ڪريو پورٽ_PRESCALE_قدر           0x00
#وصف_ڪريو پورٽ_مداخلت_ON_ميلاپ       ( ( uint32_t ) 0x01 )
#وصف_ڪريو پورٽ_RESET_ڳڻپ_ON_ميلاپ     ( ( uint32_t ) 0x02 )

/* Constants required to setup the initial stack. */
#وصف_ڪريو پورٽ_INITIAL_SPSR             ( ( ڍير_Type_t ) 0x1f )    /* System mode, ARM mode, interrupts enabled. */
#وصف_ڪريو پورٽ_THUMB_گهڻائي_ٻٽو_انگ           ( ( ڍير_Type_t ) 0x20 )
#وصف_ڪريو پورٽ_INSTRUCTION_سائيز         ( ( ڍير_Type_t ) 4 )

/* Constants required to setup the PIT. */
#وصف_ڪريو پورٽ_PIT_CLOCK_ورهائيندڙ        ( ( uint32_t ) 16 )
#وصف_ڪريو پورٽ_PIT_COUNTER_قدر        ( ( ( configCPU_CLOCK_HZ / پورٽ_PIT_CLOCK_ورهائيندڙ ) / 1000UL ) * پورٽ_TICK_PERIOD_MS )

/* Constants required to handle interrupts. */
#وصف_ڪريو پورٽ_TIMER_ميلاپ_ISR_ٻٽو_انگ      ( ( uint8_t ) 0x01 )
#وصف_ڪريو پورٽ_CLEAR_VIC_مداخلت      ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING      ( ( uint32_t ) 0 )


#وصف_ڪريو پورٽ_INT_LEVEL_SENSITIVE      0
#وصف_ڪريو پورٽ_PIT_ENABLE               ( ( uint16_t ) 0x1 << 24 )
#وصف_ڪريو پورٽ_PIT_INT_ENABLE           ( ( uint16_t ) 0x1 << 25 )

/* Constants required to setup the VIC for the tick ISR. */
#وصف_ڪريو پورٽ_TIMER_VIC_CHANNEL        ( ( uint32_t ) 0x0004 )
#وصف_ڪريو پورٽ_TIMER_VIC_CHANNEL_ٻٽو_انگ    ( ( uint32_t ) 0x0010 )
#وصف_ڪريو پورٽ_TIMER_VIC_ENABLE         ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

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
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    ڍير_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_چوٽي_جو_ڍير;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ + پورٽ_INSTRUCTION_سائيز;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12121212;    /* R12 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11111111;    /* R11 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10101010;    /* R10 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09090909;    /* R9 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08080808;    /* R8 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07070707;    /* R7 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06060606;    /* R6 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x05050505;    /* R5 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04040404;    /* R4 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03030303;    /* R3 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x02020202;    /* R2 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x01010101;    /* R1 */
    px_چوٽي_جو_ڍير--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R0 */
    px_چوٽي_جو_ڍير--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_ڪوڊ & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_چوٽي_جو_ڍير |= پورٽ_THUMB_گهڻائي_ٻٽو_انگ;
    }

    px_چوٽي_جو_ڍير--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_NESTING;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تياري_Timer_مداخلت();

    /* Start the first task. */
    v_پورٽ_شروعات_پهريون_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    ساكن __arm __irq فراغ v_پورٽ_Non_Preemptive_Tick( فراغ );
    ساكن __arm __irq فراغ v_پورٽ_Non_Preemptive_Tick( فراغ )
    {
        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Ready for the next interrupt. */
        T0IR = پورٽ_TIMER_ميلاپ_ISR_ٻٽو_انگ;
        VICVectAddr = پورٽ_CLEAR_VIC_مداخلت;
    }

#وإلا /* if configUSE_PREEMPTION == 0 */

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
    فراغ v_پورٽ_Preemptive_Tick( فراغ );
    فراغ v_پورٽ_Preemptive_Tick( فراغ )
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
        T0IR = پورٽ_TIMER_ميلاپ_ISR_ٻٽو_انگ;
        VICVectAddr = پورٽ_CLEAR_VIC_مداخلت;
    }

#جيڪڏهن_پورو /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    uint32_t ul_Compare_ميلاپ;

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = پورٽ_PRESCALE_قدر;

    /* Calculate the match value required for our wanted tick rate. */
    ul_Compare_ميلاپ = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #إذا پورٽ_PRESCALE_قدر != 0
    {
        ul_Compare_ميلاپ /= ( پورٽ_PRESCALE_قدر + 1 );
    }
    #جيڪڏهن_پورو

    T0MR0 = ul_Compare_ميلاپ;

    /* Generate tick with timer 0 compare match. */
    T0MCR = پورٽ_RESET_ڳڻپ_ON_ميلاپ | پورٽ_مداخلت_ON_ميلاپ;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( پورٽ_TIMER_VIC_CHANNEL_ٻٽو_انگ );
    VICIntEnable |= پورٽ_TIMER_VIC_CHANNEL_ٻٽو_انگ;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #إذا configUSE_PREEMPTION == 1
    {
        خارجي فراغ( v_پورٽ_Preemptive_Tick_داخلا )( فراغ );

        VICVectAddr0 = ( uint32_t ) v_پورٽ_Preemptive_Tick_داخلا;
    }
    #وإلا
    {
        خارجي فراغ( vNonPreemptiveTick )( فراغ );

        VICVectAddr0 = ( int32_t ) v_پورٽ_Non_Preemptive_Tick;
    }
    #جيڪڏهن_پورو /* if configUSE_PREEMPTION == 1 */

    VICVectCntl0 = پورٽ_TIMER_VIC_CHANNEL | پورٽ_TIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = پورٽ_ENABLE_TIMER;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
