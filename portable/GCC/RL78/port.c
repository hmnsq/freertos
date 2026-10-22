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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/* The critical nesting value is initialised to a non zero value to ensure
 * interrupts don't accidentally become enabled before the scheduler is started. */
#define portINITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )

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
#define portPSW                         ( 0xc6UL )

/* Each task maintains a count of the critical section nesting depth.  Each time
 * a critical section is entered the count is incremented.  Each time a critical
 * section is exited the count is decremented - with interrupts only being
 * re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as that could cause problems during the startup
 * sequence. */
അസ്ഥിര uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
__attribute__( ( weak ) ) ശൂന്യം vApplicationSetupTimerInterrupt( ശൂന്യം );

/*
 * Starts the scheduler by loading the context of the first task to run.
 * (defined in portasm.S).
 */
ബാഹ്യ ശൂന്യം vPortStartFirstTask( ശൂന്യം );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    uint32_t * pulLocal;

    /* Stack type and pointers to the stack type are both 2 bytes. */

    /* Parameters are passed in on the stack, and written using a 32bit value
     * hence a space is left for the second two bytes. */
    px_മുകൾ_Of_അട്ടി--;

    /* Write in the parameter value. */
    pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
    *pulLocal = ( അട്ടി_Type_t ) pvParameters;
    px_മുകൾ_Of_അട്ടി--;

    /* The return address, leaving space for the first two bytes of the
     * 32-bit value. */
    px_മുകൾ_Of_അട്ടി--;
    pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
    *pulLocal = ( uint32_t ) 0;
    px_മുകൾ_Of_അട്ടി--;

    /* The start address / PSW value is also written in as a 32bit value,
     * so leave a space for the second two bytes. */
    px_മുകൾ_Of_അട്ടി--;

    /* Task function start address combined with the PSW. */
    pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
    *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
    px_മുകൾ_Of_അട്ടി--;

    /* An initial value for the AX register. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x1111;
    px_മുകൾ_Of_അട്ടി--;

    /* An initial value for the HL register. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x2222;
    px_മുകൾ_Of_അട്ടി--;

    /* CS and ES registers. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x0F00;
    px_മുകൾ_Of_അട്ടി--;

    /* The remaining general purpose registers bank 0 (DE and BC) and the other
     * two register banks...register bank 3 is dedicated for use by interrupts so
     * is not saved as part of the task context. */
    px_മുകൾ_Of_അട്ടി -= 10;

    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portNO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack that has been generated so it
     * can be stored in the task control block for the task. */
    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    vApplicationSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run. */
    vPortStartFirstTask();

    /* Execution should not reach here as the tasks are now running! */
    തിരികെ pdTRUE;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* It is unlikely that the RL78 port will get stopped. */
}
/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ശൂന്യം vApplicationSetupTimerInterrupt( ശൂന്യം )
{
    സ്ഥിരം uint16_t usClockHz = 15000UL; /* Internal clock. */
    സ്ഥിരം uint16_t usCompareMatch = ( usClockHz / configTICK_RATE_HZ ) + 1UL;

    /* Use the internal 15K clock. */
    OSMC = ( unsigned അക്ഷരം ) 0x16;

    #ifdef RTCEN
    {
        /* Supply the interval timer clock. */
        RTCEN = ( unsigned അക്ഷരം ) 1U;

        /* Disable INTIT interrupt. */
        ITMK = ( unsigned അക്ഷരം ) 1;

        /* Disable ITMC operation. */
        ITMC = ( unsigned അക്ഷരം ) 0x0000;

        /* Clear INIT interrupt. */
        ITIF = ( unsigned അക്ഷരം ) 0;

        /* Set interval and enable interrupt operation. */
        ITMC = usCompareMatch | 0x8000U;

        /* Enable INTIT interrupt. */
        ITMK = ( unsigned അക്ഷരം ) 0;
    }
    #endif /* ifdef RTCEN */

    #ifdef TMKAEN
    {
        /* Supply the interval timer clock. */
        TMKAEN = ( unsigned അക്ഷരം ) 1U;

        /* Disable INTIT interrupt. */
        TMKAMK = ( unsigned അക്ഷരം ) 1;

        /* Disable ITMC operation. */
        ITMC = ( unsigned അക്ഷരം ) 0x0000;

        /* Clear INIT interrupt. */
        TMKAIF = ( unsigned അക്ഷരം ) 0;

        /* Set interval and enable interrupt operation. */
        ITMC = usCompareMatch | 0x8000U;

        /* Enable INTIT interrupt. */
        TMKAMK = ( unsigned അക്ഷരം ) 0;
    }
    #endif /* ifdef TMKAEN */
}
/*-----------------------------------------------------------*/
