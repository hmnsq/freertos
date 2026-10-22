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
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <intrinsics.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Constants required to setup the tick ISR. */
#నిర్వచించు పోర్టు_ENABLE_TIMER             ( ( uint8_t ) 0x01 )
#నిర్వచించు పోర్టు_PRESCALE_విలువ           0x00
#నిర్వచించు పోర్టు_అంతరాయం_ON_సరిపోలిక       ( ( uint32_t ) 0x01 )
#నిర్వచించు పోర్టు_RESET_లెక్క_ON_సరిపోలిక     ( ( uint32_t ) 0x02 )

/* Constants required to setup the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_SPSR             ( ( దొంతర_Type_t ) 0x1f )    /* System mode, ARM mode, interrupts enabled. */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు           ( ( దొంతర_Type_t ) 0x20 )
#నిర్వచించు పోర్టు_INSTRUCTION_కొలత         ( ( దొంతర_Type_t ) 4 )

/* Constants required to setup the PIT. */
#నిర్వచించు పోర్టు_PIT_CLOCK_భాజకం        ( ( uint32_t ) 16 )
#నిర్వచించు పోర్టు_PIT_COUNTER_విలువ        ( ( ( configCPU_CLOCK_HZ / పోర్టు_PIT_CLOCK_భాజకం ) / 1000UL ) * పోర్టు_TICK_PERIOD_MS )

/* Constants required to handle interrupts. */
#నిర్వచించు పోర్టు_TIMER_సరిపోలిక_ISR_బిట్టు      ( ( uint8_t ) 0x01 )
#నిర్వచించు పోర్టు_CLEAR_VIC_అంతరాయం      ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING      ( ( uint32_t ) 0 )


#నిర్వచించు పోర్టు_INT_LEVEL_SENSITIVE      0
#నిర్వచించు పోర్టు_PIT_ENABLE               ( ( uint16_t ) 0x1 << 24 )
#నిర్వచించు పోర్టు_PIT_INT_ENABLE           ( ( uint16_t ) 0x1 << 25 )

/* Constants required to setup the VIC for the tick ISR. */
#నిర్వచించు పోర్టు_TIMER_VIC_CHANNEL        ( ( uint32_t ) 0x0004 )
#నిర్వచించు పోర్టు_TIMER_VIC_CHANNEL_బిట్టు    ( ( uint32_t ) 0x0010 )
#నిర్వచించు పోర్టు_TIMER_VIC_ENABLE         ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

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
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    దొంతర_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_శిఖరం_యొక్క_దొంతర;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం + పోర్టు_INSTRUCTION_కొలత;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212;    /* R12 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111;    /* R11 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010;    /* R10 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909;    /* R9 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808;    /* R8 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707;    /* R7 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606;    /* R6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505;    /* R5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404;    /* R4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303;    /* R3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202;    /* R2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101;    /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_INITIAL_SPSR;

    ఒకవేళ( ( ( uint32_t ) px_సంకేతం & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_శిఖరం_యొక్క_దొంతర |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }

    px_శిఖరం_యొక్క_దొంతర--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    స్థిర __arm __irq శూన్య v_పోర్టు_Non_Preemptive_Tick( శూన్య );
    స్థిర __arm __irq శూన్య v_పోర్టు_Non_Preemptive_Tick( శూన్య )
    {
        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Ready for the next interrupt. */
        T0IR = పోర్టు_TIMER_సరిపోలిక_ISR_బిట్టు;
        VICVectAddr = పోర్టు_CLEAR_VIC_అంతరాయం;
    }

#లేకపోతే /* if configUSE_PREEMPTION == 0 */

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
    శూన్య v_పోర్టు_Preemptive_Tick( శూన్య );
    శూన్య v_పోర్టు_Preemptive_Tick( శూన్య )
    {
        /* Increment the tick counter. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* The new tick value might unblock a task.  Ensure the highest task that
             * is ready to execute is the task that will execute when the tick ISR
             * exits. */
            vTaskSwitchContext();
        }

        /* Ready for the next interrupt. */
        T0IR = పోర్టు_TIMER_సరిపోలిక_ISR_బిట్టు;
        VICVectAddr = పోర్టు_CLEAR_VIC_అంతరాయం;
    }

#అయితే_ముగింపు /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    uint32_t ul_Compare_సరిపోలిక;

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = పోర్టు_PRESCALE_విలువ;

    /* Calculate the match value required for our wanted tick rate. */
    ul_Compare_సరిపోలిక = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #ఒకవేళ పోర్టు_PRESCALE_విలువ != 0
    {
        ul_Compare_సరిపోలిక /= ( పోర్టు_PRESCALE_విలువ + 1 );
    }
    #అయితే_ముగింపు

    T0MR0 = ul_Compare_సరిపోలిక;

    /* Generate tick with timer 0 compare match. */
    T0MCR = పోర్టు_RESET_లెక్క_ON_సరిపోలిక | పోర్టు_అంతరాయం_ON_సరిపోలిక;

    /* Setup the VIC for the timer. */
    VICIntSelect &= ~( పోర్టు_TIMER_VIC_CHANNEL_బిట్టు );
    VICIntEnable |= పోర్టు_TIMER_VIC_CHANNEL_బిట్టు;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #ఒకవేళ configUSE_PREEMPTION == 1
    {
        బాహ్య శూన్య( v_పోర్టు_Preemptive_Tick_నమోదు )( శూన్య );

        VICVectAddr0 = ( uint32_t ) v_పోర్టు_Preemptive_Tick_నమోదు;
    }
    #లేకపోతే
    {
        బాహ్య శూన్య( vNonPreemptiveTick )( శూన్య );

        VICVectAddr0 = ( int32_t ) v_పోర్టు_Non_Preemptive_Tick;
    }
    #అయితే_ముగింపు /* if configUSE_PREEMPTION == 1 */

    VICVectCntl0 = పోర్టు_TIMER_VIC_CHANNEL | పోర్టు_TIMER_VIC_ENABLE;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = పోర్టు_ENABLE_TIMER;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
