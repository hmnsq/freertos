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
#ಅನ್ತರ್ಭಾವ "limits.h"

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Library includes. */
#ಅನ್ತರ್ಭಾವ "string.h"

/* Hardware specifics. */
#ಅನ್ತರ್ಭಾವ "machine.h"

/*-----------------------------------------------------------*/

/* Tasks should start with interrupts enabled and in Supervisor mode, therefore
 * PSW is set with U and I set, and PM and IPL clear. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSW    ( ( ರಾಶಿ_Type_t ) 0x00030000 )

/* The peripheral clock is divided by this value before being supplying the
 * CMT. */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 0 )
    /* If tickless idle is not used then the divisor can be fixed. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ    8UL
#ಅಥವಾಆದರೆ ( configPERIPHERAL_CLOCK_HZ >= 12000000 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ    512UL
#ಅಥವಾಆದರೆ ( configPERIPHERAL_CLOCK_HZ >= 6000000 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ    128UL
#ಅಥವಾಆದರೆ ( configPERIPHERAL_CLOCK_HZ >= 1000000 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ    32UL
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ    8UL
#ಆದರೆ_ಅಂತ್ಯ


/* Keys required to lock and unlock access to certain system registers
 * respectively. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNLOCK_ಕೀಲಿ    0xA50B
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬೀಗ_ಕೀಲಿ      0xA500

/*-----------------------------------------------------------*/

/*
 * Function to start the first task executing - written in asm code as direct
 * access to registers is required.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ prv_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * The tick ISR handler.  The peripheral used is configured by the application
 * via a hook/callback function.
 */
__interrupt ಸ್ಥಿರ ಶೂನ್ಯ prvTickISR( ಶೂನ್ಯ );

/*
 * Sets up the periodic ISR used for the RTOS tick using the CMT.
 * The application writer can define configSETUP_TICK_INTERRUPT() (in
 * FreeRTOSConfig.h) such that their own tick interrupt configuration is used
 * in place of prvSetupTimerInterrupt().
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ

/* The user has not provided their own tick interrupt configuration so use
 * the definition in this file (which uses the interval timer). */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ()    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ()
#ಆದರೆ_ಅಂತ್ಯ /* configSETUP_TICK_INTERRUPT */

/*
 * Called after the sleep mode registers have been configured, prvSleep()
 * executes the pre and post sleep macros, and actually calls the wait
 * instruction.
 */
#ಆದರೆ configUSE_TICKLESS_IDLE == 1
    ಸ್ಥಿರ ಶೂನ್ಯ prvSleep( TickType_t x_Expected_Idle_ಸಮಯ );
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ಶೂನ್ಯ * pxCurrentTCB;

/*-----------------------------------------------------------*/

/* Calculate how many clock increments make up a single tick period. */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint32_t ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick = ( ( configPERIPHERAL_CLOCK_HZ / ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ ) / config_TICK_ದರ_HZ );

#ಆದರೆ configUSE_TICKLESS_IDLE == 1

/* Holds the maximum number of ticks that can be suppressed - which is
 * basically how far into the future an interrupt can be generated. Set
 * during initialisation.  This is the maximum possible value that the
 * compare match register can hold divided by ulMatchValueForOneTick. */
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ TickType_t x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = USHRT_MAX / ( ( configPERIPHERAL_CLOCK_HZ / ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ ) / config_TICK_ದರ_HZ );

/* Flag set from the tick interrupt to allow the sleep processing to know if
 * sleep mode was exited because of a tick interrupt, or an interrupt
 * generated by something else. */
    ಸ್ಥಿರ ಅಸ್ಥಿರ uint32_t ulTickFlag = pdFALSE;

/* The CMT counter is stopped temporarily each time it is re-programmed.
 * The following constant offsets the CMT counter match value by the number of
 * CMT counts that would typically be missed while the counter was stopped to
 * compensate for the lost time.  The large difference between the divided CMT
 * clock and the CPU clock means it is likely ulStoppedTimerCompensation will
 * equal zero - and be optimised away. */
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint32_t ulStoppedTimerCompensation = 100UL / ( configCPU_CLOCK_HZ / ( configPERIPHERAL_CLOCK_HZ / ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ ) );

#ಆದರೆ_ಅಂತ್ಯ /* if configUSE_TICKLESS_IDLE == 1 */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Offset to end up on 8 byte boundary. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R0 is not included as it is the stack pointer. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_PSW;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;

    /* When debugging it can be useful if every register is set to a known
     * value.  Otherwise code space can be saved by just setting the registers
     * that need to be set. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ತುಂಬಿದ_ರಿಜಿಸ್ಟರ್_INITIALISATION
    {
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x12345678; /* r15. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xaaaabbbb;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xdddddddd;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xcccccccc;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xbbbbbbbb;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0xaaaaaaaa;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x99999999;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x88888888;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x77777777;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x66666666;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x55555555;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x44444444;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x33333333;
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = 0x22222222;
        px_ತುದಿ_ದ_ರಾಶಿ--;
    }
    #ಇಲ್ಲದಿದ್ದರೆ /* ifdef USE_FULL_REGISTER_INITIALISATION */
    {
        /* Leave space for the registers that will get popped from the stack
         * when the task first starts executing. */
        px_ತುದಿ_ದ_ರಾಶಿ -= 15;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef USE_FULL_REGISTER_INITIALISATION */

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x12345678;                   /* Accumulator. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x87654321;                   /* Accumulator. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Use pxCurrentTCB just so it does not get optimised away. */
    ಆದರೆ( pxCurrentTCB != ಖಾಲಿ )
    {
        /* Call an application function to set up the timer that will generate
         * the tick interrupt.  This way the application can decide which
         * peripheral to use.  If tickless mode is used then the default
         * implementation defined in this file (which uses CMT0) should not be
         * overridden. */
        config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();

        /* Enable the software interrupt. */
        _IEN( _ICU_SWINT ) = 1;

        /* Ensure the software interrupt is clear. */
        _IR( _ICU_SWINT ) = 0;

        /* Ensure the software interrupt is set to the kernel priority. */
        _IPR( _ICU_SWINT ) = config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

        /* Start the first task. */
        prv_ಆರಂಭ_ಮೊದಲ_Task();
    }

    /* Execution should not reach here as the tasks are now running!
     * prvSetupTimerInterrupt() is called here to prevent the compiler outputting
     * a warning about a statically declared function not being referenced in the
     * case that the application writer has provided their own tick interrupt
     * configuration routine (and defined configSETUP_TICK_INTERRUPT() such that
     * their own routine will be called in place of prvSetupTimerInterrupt()). */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

#ಸೂಚನೆ ಸದಿಶ = config_TICK_ಸದಿಶ
__interrupt ಸ್ಥಿರ ಶೂನ್ಯ prvTickISR( ಶೂನ್ಯ )
{
    /* Re-enable interrupts. */
    __enable_interrupt();

    /* Increment the tick, and perform any processing the new tick value
     * necessitates. */
    __set_interrupt_level( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ );
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    __set_interrupt_level( config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ );

    #ಆದರೆ configUSE_TICKLESS_IDLE == 1
    {
        /* The CPU woke because of a tick. */
        ulTickFlag = pdTRUE;

        /* If this is the first tick since exiting tickless mode then the CMT
         * compare match value needs resetting. */
        CMT0.CMCOR = ( uint16_t ) ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick;
    }
    #ಆದರೆ_ಅಂತ್ಯ
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( pxCurrentTCB == ಖಾಲಿ );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Unlock. */
    SYSTEM.PRCR.ಶಬ್ದ_3 = ಪೋರ್ಟ್_UNLOCK_ಕೀಲಿ;

    /* Enable CMT0. */
    MSTP( CMT0 ) = 0;

    /* Lock again. */
    SYSTEM.PRCR.ಶಬ್ದ_3 = ಪೋರ್ಟ್_ಬೀಗ_ಕೀಲಿ;

    /* Interrupt on compare match. */
    CMT0.CMCR.ಬಿಟ್_3.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( uint16_t ) ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick;

    /* Divide the PCLK. */
    #ಆದರೆ ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ == 512
    {
        CMT0.CMCR.ಬಿಟ್_3.CKS = 3;
    }
    #ಅಥವಾಆದರೆ ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ == 128
    {
        CMT0.CMCR.ಬಿಟ್_3.CKS = 2;
    }
    #ಅಥವಾಆದರೆ ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ == 32
    {
        CMT0.CMCR.ಬಿಟ್_3.CKS = 1;
    }
    #ಅಥವಾಆದರೆ ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ == 8
    {
        CMT0.CMCR.ಬಿಟ್_3.CKS = 0;
    }
    #ಇಲ್ಲದಿದ್ದರೆ /* if portCLOCK_DIVISOR == 512 */
    {
        #ದೋಷ Invalid ಪೋರ್ಟ್_CLOCK_ಭಾಜಕ setting
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if portCLOCK_DIVISOR == 512 */


    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

    /* Start the timer. */
    CMT.CMSTR0.ಬಿಟ್_3.STR0 = 1;
}
/*-----------------------------------------------------------*/

#ಆದರೆ configUSE_TICKLESS_IDLE == 1

    ಸ್ಥಿರ ಶೂನ್ಯ prvSleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        /* Allow the application to define some pre-sleep processing. */
        configPRE_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );

        /* xExpectedIdleTime being set to 0 by configPRE_SLEEP_PROCESSING()
         * means the application defined code has already executed the WAIT
         * instruction. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > 0 )
        {
            __wait_for_interrupt();
        }

        /* Allow the application to define some post sleep processing. */
        configPOST_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

#ಆದರೆ configUSE_TICKLESS_IDLE == 1

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        uint32_t ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ, ulCompleteTickPeriods, ul_Current_ಎಣಿಕೆ;
        e_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ eSleepAction;

        /* THIS FUNCTION IS CALLED WITH THE SCHEDULER SUSPENDED. */

        /* Make sure the CMT reload value does not overflow the counter. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ಸಮಯ = x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks;
        }

        /* Calculate the reload value required to wait xExpectedIdleTime tick
         * periods. */
        ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ = ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick * x_Expected_Idle_ಸಮಯ;

        ಆದರೆ( ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ > ulStoppedTimerCompensation )
        {
            /* Compensate for the fact that the CMT is going to be stopped
             * momentarily. */
            ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ -= ulStoppedTimerCompensation;
        }

        /* Stop the CMT momentarily.  The time the CMT is stopped for is
         * accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        CMT.CMSTR0.ಬಿಟ್_3.STR0 = 0;

        ಆಗ( CMT.CMSTR0.ಬಿಟ್_3.STR0 == 1 )
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
        eSleepAction = e_Task_Confirm_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ();

        ಆದರೆ( eSleepAction == eAbortSleep )
        {
            /* Restart tick. */
            CMT.CMSTR0.ಬಿಟ್_3.STR0 = 1;
            __enable_interrupt();
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( eSleepAction == e_No_Tasks_ಕಾಯುವಿಕೆ_Timeout )
        {
            /* Protection off. */
            SYSTEM.PRCR.ಶಬ್ದ_3 = ಪೋರ್ಟ್_UNLOCK_ಕೀಲಿ;

            /* Ready for software standby with all clocks stopped. */
            SYSTEM.SBYCR.ಬಿಟ್_3.SSBY = 1;

            /* Protection on. */
            SYSTEM.PRCR.ಶಬ್ದ_3 = ಪೋರ್ಟ್_ಬೀಗ_ಕೀಲಿ;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_ಸಮಯ );

            /* Restart the CMT. */
            CMT.CMSTR0.ಬಿಟ್_3.STR0 = 1;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Protection off. */
            SYSTEM.PRCR.ಶಬ್ದ_3 = ಪೋರ್ಟ್_UNLOCK_ಕೀಲಿ;

            /* Ready for deep sleep mode. */
            SYSTEM.MSTPCRC.ಬಿಟ್_3.DSLPE = 1;
            SYSTEM.MSTPCRA.ಬಿಟ್_3.MSTPA28 = 1;
            SYSTEM.SBYCR.ಬಿಟ್_3.SSBY = 0;

            /* Protection on. */
            SYSTEM.PRCR.ಶಬ್ದ_3 = ಪೋರ್ಟ್_ಬೀಗ_ಕೀಲಿ;

            /* Adjust the match value to take into account that the current
             * time slice is already partially complete. */
            ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ -= ( uint32_t ) CMT0.CMCNT;
            CMT0.CMCOR = ( uint16_t ) ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ;

            /* Restart the CMT to count up to the new match value. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ಬಿಟ್_3.STR0 = 1;

            /* Sleep until something happens.  Calling prvSleep() will
             * automatically reset the i bit in the PSW. */
            prvSleep( x_Expected_Idle_ಸಮಯ );

            /* Stop CMT.  Again, the time the SysTick is stopped for is
             * accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            CMT.CMSTR0.ಬಿಟ್_3.STR0 = 0;

            ಆಗ( CMT.CMSTR0.ಬಿಟ್_3.STR0 == 1 )
            {
                /* Nothing to do here. */
            }

            ul_Current_ಎಣಿಕೆ = ( uint32_t ) CMT0.CMCNT;

            ಆದರೆ( ulTickFlag != pdFALSE )
            {
                /* The tick interrupt has already executed, although because
                 * this function is called with the scheduler suspended the actual
                 * tick processing will not occur until after this function has
                 * exited.  Reset the match value with whatever remains of this
                 * tick period. */
                ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ = ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick - ul_Current_ಎಣಿಕೆ;
                CMT0.CMCOR = ( uint16_t ) ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ;

                /* The tick interrupt handler will already have pended the tick
                 * processing in the kernel.  As the pending tick will be
                 * processed as soon as this function exits, the tick value
                 * maintained by the tick is stepped forward by one less than the
                 * time spent sleeping.  The actual stepping of the tick appears
                 * later in this function. */
                ulCompleteTickPeriods = x_Expected_Idle_ಸಮಯ - 1UL;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Something other than the tick interrupt ended the sleep.
                 * How many complete tick periods passed while the processor was
                 * sleeping? */
                ulCompleteTickPeriods = ul_Current_ಎಣಿಕೆ / ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick;

                /* The match value is set to whatever fraction of a single tick
                 * period remains. */
                ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ = ul_Current_ಎಣಿಕೆ - ( ulCompleteTickPeriods * ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ_For_One_Tick );
                CMT0.CMCOR = ( uint16_t ) ul_ಹೊಂದಿಕೆ_ಮೌಲ್ಯ;
            }

            /* Restart the CMT so it runs up to the match value.  The match value
             * will get set to the value required to generate exactly one tick period
             * the next time the CMT interrupt executes. */
            CMT0.CMCNT = 0;
            CMT.CMSTR0.ಬಿಟ್_3.STR0 = 1;

            /* Wind the tick forward by the number of tick periods that the CPU
             * remained in a low power state. */
            v_Task_ಹೆಜ್ಜೆ_Tick( ulCompleteTickPeriods );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */
