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
#అన్తర్భావ "limits.h"

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Library includes. */
#అన్తర్భావ "string.h"

/* Hardware specifics. */
#అన్తర్భావ "machine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#నిర్వచించు పోర్టు_INITIAL_PSW    ( ( దొంతర_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
 * CMT. */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    8UL
#లేదావేళ ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    512UL
#లేదావేళ ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    128UL
#లేదావేళ ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    32UL
#లేకపోతే
    #నిర్వచించు పోర్టు_CLOCK_భాజకం    8UL
#అయితే_ముగింపు


/* Keys required to lock and unlock access to certain system registers
 * respectively. */
#నిర్వచించు పోర్టు_UNLOCK_కీలకం    0xA50B
#నిర్వచించు పోర్టు_తాళం_కీలకం      0xA500

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
బాహ్య శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt స్థిర శూన్య prvTickISR( శూన్య );

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );
#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #నిర్వచించు config_అమరిక_TICK_అంతరాయం()    prv_అమరిక_Timer_అంతరాయం()
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#ఒకవేళ configUSE_TICKLESS_IDLE == 1
    స్థిర శూన్య prvSleep( TickType_t x_Expected_Idle_సమయం );
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

బాహ్య శూన్య * pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Calculate how many clock increments make up a single tick period. */
స్థిర స్థిరరాశి uint32_t ul_సరిపోలిక_విలువ_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / పోర్టు_CLOCK_భాజకం ) / config_TICK_రేటు_HZ );

#ఒకవేళ configUSE_TICKLESS_IDLE == 1

/* Holds the maximum number of ticks that can be suppressed - which is
 * basically how far into the future an interrupt can be generated. Set
 * during initialisation.  This is the maximum possible value that the
 * compare match register can hold divided by ulMatchValueForOneTick. */
    స్థిర స్థిరరాశి TickType_t x_గరిష్ఠ_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / పోర్టు_CLOCK_భాజకం ) / config_TICK_రేటు_HZ );

/* Flag set from the tick interrupt to allow the sleep processing to know if
 * sleep mode was exited because of a tick interrupt, or an interrupt
 * generated by something else. */
    స్థిర అస్థిర uint32_t ulTickFlag = pdFALSE;

/* The CMT counter is stopped temporarily each time it is re-programmed.
 * The following constant offsets the CMT counter match value by the number of
 * CMT counts that would typically be missed while the counter was stopped to
 * compensate for the lost time.  The large difference between the divided CMT
 * clock and the CPU clock means it is likely ulStoppedTimerCompensation will
 * equal zero - and be optimised away. */
    స్థిర స్థిరరాశి uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / పోర్టు_CLOCK_భాజకం ) );

#అయితే_ముగింపు /* if configUSE_TICKLESS_IDLE == 1 */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* R0 is not included as it is the stack pointer. */
    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_PSW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #నిర్వచితమైతే USE_నిండిన_రిజిస్టరు_INITIALISATION
    {
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x12345678; /* r15. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xaaaabbbb;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xdddddddd;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xcccccccc;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xbbbbbbbb;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0xaaaaaaaa;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x99999999;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x88888888;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x77777777;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x66666666;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x55555555;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x44444444;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x33333333;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = 0x22222222;
        px_శిఖరం_యొక్క_దొంతర--;
    }
    #లేకపోతే /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        /* Leave space for the registers that will get popped from the stack
         * when the task first starts executing. */
        px_శిఖరం_యొక్క_దొంతర -= 15;
    }
    #అయితే_ముగింపు /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x12345678;                   /* Accumulator. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x87654321;                   /* Accumulator. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    ఒకవేళ( pxCurrentTCB != ఖాళీ )
    {
        /* Call an application function to set up the timer that will generate
         * the tick interrupt.  This way the application can decide which
         * peripheral to use.  If tickless mode is used then the default
         * implementation defined in this file (which uses CMT0) should not be
         * overridden. */
        config_అమరిక_TICK_అంతరాయం();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

        /* Start the first task. */
        prv_ప్రారంభం_మొదటి_Task();
    }

    /* Execution should not reach here as the tasks are now running!
     * prvSetupTimerInterrupt() is called here to prevent the compiler outputting
     * a warning about a statically declared function not being referenced in the
     * case that the application writer has provided their own tick interrupt
     * configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
     * their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_అమరిక_Timer_అంతరాయం();

    /* Should not get here. */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

#సూచన సదిశ = config_TICK_సదిశ
__interrupt స్థిర శూన్య prvTickISR( శూన్య )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత );
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_అంతరాయం_ప్రాధాన్యత );

    #ఒకవేళ configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
         * compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ_For_One_Tick;
    }
    #అయితే_ముగింపు
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ఖాళీ );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Unlock. */
    SYSTEM.PRCR.మాట_3 = పోర్టు_UNLOCK_కీలకం;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.మాట_3 = పోర్టు_తాళం_కీలకం;

    /* Interrupt on compare match. */
    CMT0.CMCR.బిట్టు_3.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ_For_One_Tick;

    /* Divide the PCLK. */
    #ఒకవేళ పోర్టు_CLOCK_భాజకం == 512
    {
        CMT0.CMCR.బిట్టు_3.CKS = 3;
    }
    #లేదావేళ పోర్టు_CLOCK_భాజకం == 128
    {
        CMT0.CMCR.బిట్టు_3.CKS = 2;
    }
    #లేదావేళ పోర్టు_CLOCK_భాజకం == 32
    {
        CMT0.CMCR.బిట్టు_3.CKS = 1;
    }
    #లేదావేళ పోర్టు_CLOCK_భాజకం == 8
    {
        CMT0.CMCR.బిట్టు_3.CKS = 0;
    }
    #లేకపోతే /* if portCLOCK_DIVISOR == 512 */
    {
        #దోషం Invalid పోర్టు_CLOCK_భాజకం setting
    }
    #అయితే_ముగింపు /* if portCLOCK_DIVISOR == 512 */


    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

    /* Start the timer. */
    CMT.CMSTR0.బిట్టు_3.STR0 = 1;
}
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_TICKLESS_IDLE == 1

    స్థిర శూన్య prvSleep( TickType_t x_Expected_Idle_సమయం )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
         * means the application defined code has already executed the WAIT
         * instruction. */
        ఒకవేళ( x_Expected_Idle_సమయం > 0 )
        {
            __wait_for_interrupt();
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_TICKLESS_IDLE == 1

    శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
    {
        uint32_t ul_సరిపోలిక_విలువ, ulCompleteTickPeriods, ul_Current_లెక్క;
        e_Sleep_బహుళకం_స్థితి eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        ఒకవేళ( x_Expected_Idle_సమయం > x_గరిష్ఠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_సమయం = x_గరిష్ఠ_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
         * periods. */
        ul_సరిపోలిక_విలువ = ul_సరిపోలిక_విలువ_For_One_Tick * x_Expected_Idle_సమయం;

        ఒకవేళ( ul_సరిపోలిక_విలువ > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
             * momentarily. */
            ul_సరిపోలిక_విలువ -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
         * accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        CMT.CMSTR0.బిట్టు_3.STR0 = 0;

        అయితే( CMT.CMSTR0.బిట్టు_3.STR0 == 1 )
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
        eSleepAction = e_Task_Confirm_Sleep_బహుళకం_స్థితి();

        ఒకవేళ( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;
            __enable_interrupt();
        }
        లేకపోతే ఒకవేళ( eSleepAction == e_No_Tasks_నిరీక్షణ_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_UNLOCK_కీలకం;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.బిట్టు_3.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_తాళం_కీలకం;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_సమయం );

            /* Restart the CMT. */
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;
        }
        లేకపోతే
        {
            /* Protection off. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_UNLOCK_కీలకం;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.బిట్టు_3.DSLPE = 1;
            SYSTEM.MSTPCRA.బిట్టు_3.MSTPA28 = 1;
            SYSTEM.SBYCR.బిట్టు_3.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.మాట_3 = పోర్టు_తాళం_కీలకం;

            /* Adjust the match value to take into account that the current
             * time slice is already partially complete. */
            ul_సరిపోలిక_విలువ -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_సమయం );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
             * accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            CMT.CMSTR0.బిట్టు_3.STR0 = 0;

            అయితే( CMT.CMSTR0.బిట్టు_3.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_లెక్క = ( uint32_t ) CMT0.CMCNT;

            ఒకవేళ( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                 * this function is called with the scheduler suspended the actual
                 * tick processing will not occur until after this function has
                 * exited.  Reset the match value with whatever remains of this
                 * tick period. */
                ul_సరిపోలిక_విలువ = ul_సరిపోలిక_విలువ_For_One_Tick - ul_Current_లెక్క;
                CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ;

                /* The tick interrupt handler will already have pended the tick
                 * processing in the kernel.  As the pending tick will be
                 * processed as soon as this function exits, the tick value
                 * maintained by the tick is stepped forward by one less than the
                 * time spent sleeping.  The actual stepping of the tick appears
                 * later in this function. */
                ulCompleteTickPeriods = x_Expected_Idle_సమయం - 1UL;
            }
            లేకపోతే
            {
                /* Something other than the tick interrupt ended the sleep.
                 * How many complete tick periods passed while the processor was
                 * sleeping? */
                ulCompleteTickPeriods = ul_Current_లెక్క / ul_సరిపోలిక_విలువ_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                 * period remains. */
                ul_సరిపోలిక_విలువ = ul_Current_లెక్క - ( ulCompleteTickPeriods * ul_సరిపోలిక_విలువ_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_సరిపోలిక_విలువ;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
             * will get set to the value required to generate exactly one tick period
             * the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.బిట్టు_3.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
             * remained in a low power state. */
            v_Task_అడుగు_Tick( ulCompleteTickPeriods );
        }
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
