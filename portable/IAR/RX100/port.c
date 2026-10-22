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
* Implementation of functions defined in portable.h for the SH2A port.
*----------------------------------------------------------*/

/* Standard C includes. */
#அந்தர்பாவ "limits.h"

/* Scheduler includes. */
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

/* Library includes. */
#அந்தர்பாவ "string.h"

/* Hardware specifics. */
#அந்தர்பாவ "machine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#define portINITIAL_PSW    ( ( அடுக்கு_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
 * CMT. */
#எனில் ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #define port_CLOCK_வகுஎண்    8UL
#அல்லதெனில் ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #define port_CLOCK_வகுஎண்    512UL
#அல்லதெனில் ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #define port_CLOCK_வகுஎண்    128UL
#அல்லதெனில் ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #define port_CLOCK_வகுஎண்    32UL
#இல்லையெனில்
    #define port_CLOCK_வகுஎண்    8UL
#endif


/* Keys required to lock and unlock access to certain system registers
 * respectively. */
#define port_UNLOCK_சாவி    0xA50B
#define port_LOCK_சாவி      0xA500

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
வெளி வெறுமை prvStartFirstTask( வெறுமை );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt நிலையான வெறுமை prvTickISR( வெறுமை );

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை );
#ifndef configSETUP_TICK_INTERRUPT

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #define configSETUP_TICK_INTERRUPT()    prvSetupTimerInterrupt()
#endif /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#எனில் configUSE_TICKLESS_IDLE == 1
    நிலையான வெறுமை prvSleep( TickType_t xExpectedIdleTime );
#endif /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

வெளி வெறுமை * pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Calculate how many clock increments make up a single tick period. */
நிலையான மாறிலி uint32_t ul_Match_மதிப்பு_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / port_CLOCK_வகுஎண் ) / configTICK_RATE_HZ );

#எனில் configUSE_TICKLESS_IDLE == 1

/* Holds the maximum number of ticks that can be suppressed - which is
 * basically how far into the future an interrupt can be generated. Set
 * during initialisation.  This is the maximum possible value that the
 * compare match register can hold divided by ulMatchValueForOneTick. */
    நிலையான மாறிலி TickType_t xMaximumPossibleSuppressedTicks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / port_CLOCK_வகுஎண் ) / configTICK_RATE_HZ );

/* Flag set from the tick interrupt to allow the sleep processing to know if
 * sleep mode was exited because of a tick interrupt, or an interrupt
 * generated by something else. */
    நிலையான நிலையற்ற uint32_t ulTickFlag = pdFALSE;

/* The CMT counter is stopped temporarily each time it is re-programmed.
 * The following constant offsets the CMT counter match value by the number of
 * CMT counts that would typically be missed while the counter was stopped to
 * compensate for the lost time.  The large difference between the divided CMT
 * clock and the CPU clock means it is likely ulStoppedTimerCompensation will
 * equal zero - and be optimised away. */
    நிலையான மாறிலி uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / port_CLOCK_வகுஎண் ) );

#endif /* if configUSE_TICKLESS_IDLE == 1 */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_உச்சி_Of_அடுக்கு--;

    /* R0 is not included as it is the stack pointer. */
    *px_உச்சி_Of_அடுக்கு = 0x00;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x00;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = portINITIAL_PSW;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pxCode;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ifdef USE_FULL_REGISTER_INITIALISATION
    {
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x12345678; /* r15. */
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xaaaabbbb;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xdddddddd;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xcccccccc;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xbbbbbbbb;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0xaaaaaaaa;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x99999999;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x88888888;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x77777777;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x66666666;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x55555555;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x44444444;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x33333333;
        px_உச்சி_Of_அடுக்கு--;
        *px_உச்சி_Of_அடுக்கு = 0x22222222;
        px_உச்சி_Of_அடுக்கு--;
    }
    #இல்லையெனில் /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        /* Leave space for the registers that will get popped from the stack
         * when the task first starts executing. */
        px_உச்சி_Of_அடுக்கு -= 15;
    }
    #endif /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pvParameters; /* R1 */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x12345678;                   /* Accumulator. */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x87654321;                   /* Accumulator. */

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    எனில்( pxCurrentTCB != வெற்று )
    {
        /* Call an application function to set up the timer that will generate
         * the tick interrupt.  This way the application can decide which
         * peripheral to use.  If tickless mode is used then the default
         * implementation defined in this file (which uses CMT0) should not be
         * overridden. */
        configSETUP_TICK_INTERRUPT();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = configKERNEL_INTERRUPT_PRIORITY;

        /* Start the first task. */
        prvStartFirstTask();
    }

    /* Execution should not reach here as the tasks are now running!
     * prvSetupTimerInterrupt() is called here to prevent the compiler outputting
     * a warning about a statically declared function not being referenced in the
     * case that the application writer has provided their own tick interrupt
     * configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
     * their own routine will be called in place of prvSetupTimerInterrupt()). */
    prvSetupTimerInterrupt();

    /* Should not get here. */
    திரும்பு pdFAIL;
}
/*-----------------------------------------------------------*/

#pragma vector = configTICK_VECTOR
__interrupt நிலையான வெறுமை prvTickISR( வெறுமை )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( configMAX_SYSCALL_INTERRUPT_PRIORITY );
    {
        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( configKERNEL_INTERRUPT_PRIORITY );

    #எனில் configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
         * compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_Match_மதிப்பு_For_One_Tick;
    }
    #endif
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == வெற்று );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை )
{
    /* Unlock. */
    SYSTEM.PRCR.WORD = port_UNLOCK_சாவி;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.WORD = port_LOCK_சாவி;

    /* Interrupt on compare match. */
    CMT0.CMCR.BIT.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_Match_மதிப்பு_For_One_Tick;

    /* Divide the PCLK. */
    #எனில் port_CLOCK_வகுஎண் == 512
    {
        CMT0.CMCR.BIT.CKS = 3;
    }
    #அல்லதெனில் port_CLOCK_வகுஎண் == 128
    {
        CMT0.CMCR.BIT.CKS = 2;
    }
    #அல்லதெனில் port_CLOCK_வகுஎண் == 32
    {
        CMT0.CMCR.BIT.CKS = 1;
    }
    #அல்லதெனில் port_CLOCK_வகுஎண் == 8
    {
        CMT0.CMCR.BIT.CKS = 0;
    }
    #இல்லையெனில் /* if portCLOCK_DIVISOR == 512 */
    {
        #error Invalid port_CLOCK_வகுஎண் setting
    }
    #endif /* if portCLOCK_DIVISOR == 512 */


    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = configKERNEL_INTERRUPT_PRIORITY;

    /* Start the timer. */
    CMT.CMSTR0.BIT.STR0 = 1;
}
/*-----------------------------------------------------------*/

#எனில் configUSE_TICKLESS_IDLE == 1

    நிலையான வெறுமை prvSleep( TickType_t xExpectedIdleTime )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( xExpectedIdleTime );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
         * means the application defined code has already executed the WAIT
         * instruction. */
        எனில்( xExpectedIdleTime > 0 )
        {
            __wait_for_interrupt();
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( xExpectedIdleTime );
    }

#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#எனில் configUSE_TICKLESS_IDLE == 1

    வெறுமை vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Match_மதிப்பு, ulCompleteTickPeriods, ul_Current_மொத்தம்;
        eSleepModeStatus eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        எனில்( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
         * periods. */
        ul_Match_மதிப்பு = ul_Match_மதிப்பு_For_One_Tick * xExpectedIdleTime;

        எனில்( ul_Match_மதிப்பு > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
             * momentarily. */
            ul_Match_மதிப்பு -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
         * accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        CMT.CMSTR0.BIT.STR0 = 0;

        போது( CMT.CMSTR0.BIT.STR0 == 1 )
        {
            /* Nothing to do here. */
        }

        /* Critical section using the global interrupt bit as the i bit is
         * automatically reset by the WAIT instruction. */
        __disable_interrupt();

        /* The tick flag is set to false before sleeping.  If it is true when
         * sleep mode is exited then sleep mode was probably exited because the
         * tick was suppressed for the entire xExpectedIdleTime period. */
        ulTickFlag = pdFALSE;

        /* If a context switch is pending then abandon the low power entry as
         * the context switch might have been pended by an external interrupt that
         * requires processing. */
        eSleepAction = eTaskConfirmSleepModeStatus();

        எனில்( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.BIT.STR0 = 1;
            __enable_interrupt();
        }
        இல்லையெனில் எனில்( eSleepAction == eNoTasksWaitingTimeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.WORD = port_UNLOCK_சாவி;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.BIT.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.WORD = port_LOCK_சாவி;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( xExpectedIdleTime );

            /* Restart the CMT. */
            CMT.CMSTR0.BIT.STR0 = 1;
        }
        இல்லையெனில்
        {
            /* Protection off. */
            SYSTEM.PRCR.WORD = port_UNLOCK_சாவி;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.BIT.DSLPE = 1;
            SYSTEM.MSTPCRA.BIT.MSTPA28 = 1;
            SYSTEM.SBYCR.BIT.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.WORD = port_LOCK_சாவி;

            /* Adjust the match value to take into account that the current
             * time slice is already partially complete. */
            ul_Match_மதிப்பு -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_Match_மதிப்பு;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.BIT.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( xExpectedIdleTime );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
             * accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            CMT.CMSTR0.BIT.STR0 = 0;

            போது( CMT.CMSTR0.BIT.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_மொத்தம் = ( uint32_t ) CMT0.CMCNT;

            எனில்( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                 * this function is called with the scheduler suspended the actual
                 * tick processing will not occur until after this function has
                 * exited.  Reset the match value with whatever remains of this
                 * tick period. */
                ul_Match_மதிப்பு = ul_Match_மதிப்பு_For_One_Tick - ul_Current_மொத்தம்;
                CMT0.CMCOR = ( uint16_t ) ul_Match_மதிப்பு;

                /* The tick interrupt handler will already have pended the tick
                 * processing in the kernel.  As the pending tick will be
                 * processed as soon as this function exits, the tick value
                 * maintained by the tick is stepped forward by one less than the
                 * time spent sleeping.  The actual stepping of the tick appears
                 * later in this function. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            இல்லையெனில்
            {
                /* Something other than the tick interrupt ended the sleep.
                 * How many complete tick periods passed while the processor was
                 * sleeping? */
                ulCompleteTickPeriods = ul_Current_மொத்தம் / ul_Match_மதிப்பு_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                 * period remains. */
                ul_Match_மதிப்பு = ul_Current_மொத்தம் - ( ulCompleteTickPeriods * ul_Match_மதிப்பு_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_Match_மதிப்பு;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
             * will get set to the value required to generate exactly one tick period
             * the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.BIT.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
             * remained in a low power state. */
            vTaskStepTick( ulCompleteTickPeriods );
        }
    }

#endif /* configUSE_TICKLESS_IDLE */
