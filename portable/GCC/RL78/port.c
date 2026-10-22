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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* The critical nesting value is initialised to a non zero value to ensure
 * interrupts don't accidentally become enabled before the scheduler is started. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSW                         ( 0xc6UL )

/* Each task maintains a count of the critical section nesting depth.  Each time
 * a critical section is entered the count is incremented.  Each time a critical
 * section is exited the count is decremented - with interrupts only being
 * re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as that could cause problems during the startup
 * sequence. */
ਅਸਥਿਰ uint16_t usCriticalNesting = ਪੋਰਟ_INITIAL_CRITICAL_NESTING;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
__attribute__( ( weak ) ) ਖਾਲੀ v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Starts the scheduler by loading the context of the first task to run.
 * (defined in portasm.S).
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    uint32_t * pulLocal;

    /* Stack type and pointers to the stack type are both 2 bytes. */

    /* Parameters are passed in on the stack, and written using a 32bit value
     * hence a space is left for the second two bytes. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Write in the parameter value. */
    pulLocal = ( uint32_t * ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    *pulLocal = ( ਢੇਰ_Type_t ) pvParameters;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The return address, leaving space for the first two bytes of the
     * 32-bit value. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    pulLocal = ( uint32_t * ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    *pulLocal = ( uint32_t ) 0;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The start address / PSW value is also written in as a 32bit value,
     * so leave a space for the second two bytes. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Task function start address combined with the PSW. */
    pulLocal = ( uint32_t * ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    *pulLocal = ( ( ( uint32_t ) px_ਕੋਡ ) | ( ਪੋਰਟ_PSW << 24UL ) );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* An initial value for the AX register. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x1111;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* An initial value for the HL register. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x2222;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* CS and ES registers. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0F00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The remaining general purpose registers bank 0 (DE and BC) and the other
     * two register banks...register bank 3 is dedicated for use by interrupts so
     * is not saved as part of the task context. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 10;

    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack that has been generated so it
     * can be stored in the task control block for the task. */
    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Restore the context of the first task that is going to run. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Execution should not reach here as the tasks are now running! */
    ਵਾਪਸ pdTRUE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the RL78 port will get stopped. */
}
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ਖਾਲੀ v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    ਅਚਲ uint16_t usClockHz = 15000UL; /* Internal clock. */
    ਅਚਲ uint16_t us_Compare_ਮੇਲ = ( usClockHz / config_TICK_ਦਰ_HZ ) + 1UL;

    /* Use the internal 15K clock. */
    OSMC = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0x16;

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ RTCEN
    {
        /* Supply the interval timer clock. */
        RTCEN = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 1U;

        /* Disable INTIT interrupt. */
        ITMK = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 1;

        /* Disable ITMC operation. */
        ITMC = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0x0000;

        /* Clear INIT interrupt. */
        ITIF = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0;

        /* Set interval and enable interrupt operation. */
        ITMC = us_Compare_ਮੇਲ | 0x8000U;

        /* Enable INTIT interrupt. */
        ITMK = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0;
    }
    #ਜੇ_ਅੰਤ /* ifdef RTCEN */

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TMKAEN
    {
        /* Supply the interval timer clock. */
        TMKAEN = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 1U;

        /* Disable INTIT interrupt. */
        TMKAMK = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 1;

        /* Disable ITMC operation. */
        ITMC = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0x0000;

        /* Clear INIT interrupt. */
        TMKAIF = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0;

        /* Set interval and enable interrupt operation. */
        ITMC = us_Compare_ਮੇਲ | 0x8000U;

        /* Enable INTIT interrupt. */
        TMKAMK = ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ) 0;
    }
    #ਜੇ_ਅੰਤ /* ifdef TMKAEN */
}
/*-----------------------------------------------------------*/
