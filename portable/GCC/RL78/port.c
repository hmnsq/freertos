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

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* The critical nesting value is initialised to a non zero value to ensure
 * interrupts don't accidentally become enabled before the scheduler is started. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )

/* Initial PSW value allocated to a newly created task.
 *   11000110
 *   ||||||||-------------- Fill byte
 *   |||||||--------------- Carry Flag cleared
 *   |||||----------------- In-service priority Flags set to low level
 *   ||||------------------ Register bank Select 0 Flag cleared
 *   |||------------------- Auxiliary Carry Flag cleared
 *   ||-------------------- Register bank Select 1 Flag cleared
 *   |--------------------- Zero Flag set
 *   ---------------------- Global Interrupt Flag set (enabled)
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSW                         ( 0xc6UL )

/* Each task maintains a count of the critical section nesting depth.  Each time
 * a critical section is entered the count is incremented.  Each time a critical
 * section is exited the count is decremented - with interrupts only being
 * re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as that could cause problems during the startup
 * sequence. */
ಅಸ್ಥಿರ uint16_t usCriticalNesting = ಪೋರ್ಟ್_INITIAL_CRITICAL_NESTING;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
__attribute__( ( weak ) ) ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Starts the scheduler by loading the context of the first task to run.
 * (defined in portasm.S).
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    uint32_t * pulLocal;

    /* Stack type and pointers to the stack type are both 2 bytes. */

    /* Parameters are passed in on the stack, and written using a 32bit value
     * hence a space is left for the second two bytes. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Write in the parameter value. */
    pulLocal = ( uint32_t * ) px_ತುದಿ_ದ_ರಾಶಿ;
    *pulLocal = ( ರಾಶಿ_Type_t ) pvParameters;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The return address, leaving space for the first two bytes of the
     * 32-bit value. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    pulLocal = ( uint32_t * ) px_ತುದಿ_ದ_ರಾಶಿ;
    *pulLocal = ( uint32_t ) 0;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The start address / PSW value is also written in as a 32bit value,
     * so leave a space for the second two bytes. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Task function start address combined with the PSW. */
    pulLocal = ( uint32_t * ) px_ತುದಿ_ದ_ರಾಶಿ;
    *pulLocal = ( ( ( uint32_t ) px_ಸಂಕೇತ ) | ( ಪೋರ್ಟ್_PSW << 24UL ) );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* An initial value for the AX register. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x1111;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* An initial value for the HL register. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x2222;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* CS and ES registers. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0F00;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The remaining general purpose registers bank 0 (DE and BC) and the other
     * two register banks...register bank 3 is dedicated for use by interrupts so
     * is not saved as part of the task context. */
    px_ತುದಿ_ದ_ರಾಶಿ -= 10;

    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack that has been generated so it
     * can be stored in the task control block for the task. */
    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Restore the context of the first task that is going to run. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Execution should not reach here as the tasks are now running! */
    ಹಿಂತಿರುಗಿ pdTRUE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the RL78 port will get stopped. */
}
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    ಸ್ಥಿರಾಂಕ uint16_t usClockHz = 15000UL; /* Internal clock. */
    ಸ್ಥಿರಾಂಕ uint16_t us_Compare_ಹೊಂದಿಕೆ = ( usClockHz / config_TICK_ದರ_HZ ) + 1UL;

    /* Use the internal 15K clock. */
    OSMC = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0x16;

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ RTCEN
    {
        /* Supply the interval timer clock. */
        RTCEN = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 1U;

        /* Disable INTIT interrupt. */
        ITMK = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 1;

        /* Disable ITMC operation. */
        ITMC = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0x0000;

        /* Clear INIT interrupt. */
        ITIF = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0;

        /* Set interval and enable interrupt operation. */
        ITMC = us_Compare_ಹೊಂದಿಕೆ | 0x8000U;

        /* Enable INTIT interrupt. */
        ITMK = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef RTCEN */

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TMKAEN
    {
        /* Supply the interval timer clock. */
        TMKAEN = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 1U;

        /* Disable INTIT interrupt. */
        TMKAMK = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 1;

        /* Disable ITMC operation. */
        ITMC = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0x0000;

        /* Clear INIT interrupt. */
        TMKAIF = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0;

        /* Set interval and enable interrupt operation. */
        ITMC = us_Compare_ಹೊಂದಿಕೆ | 0x8000U;

        /* Enable INTIT interrupt. */
        TMKAMK = ( ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ) 0;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef TMKAEN */
}
/*-----------------------------------------------------------*/
