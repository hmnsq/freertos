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
 *   1100011000000000
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

/* The address of the pxCurrentTCB variable, but don't know or need to know its
 * type. */
തരനിർവചനം ശൂന്യം TCB_t;
ബാഹ്യ അസ്ഥിര TCB_t * അസ്ഥിര pxCurrentTCB;

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
ബാഹ്യ ശൂന്യം vApplicationSetupTimerInterrupt( ശൂന്യം );

/*
 * Starts the scheduler by loading the context of the first Task to run.
 * (implemented in portasm.s).
 */
ബാഹ്യ ശൂന്യം vPortStartFirstTask( ശൂന്യം );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
സ്ഥിതം ശൂന്യം prvTaskExitError( ശൂന്യം );

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
    /* With large data sizeof( StackType_t ) == 2, and
     * sizeof( StackType_t * ) == 4.  With small data
     * sizeof( StackType_t ) == 2 and sizeof( StackType_t * ) == 2. */
#എങ്കിൽ __DATA_MODEL__ == __DATA_MODEL_FAR__
    {
        /* Far pointer parameters are passed using the A:DE registers (24-bit).
         * Although they are stored in memory as a 32-bit value.  Hence decrement
         * the stack pointer, so 2 bytes are left for the contents of A, before
         * storing the pvParameters value. */
        px_മുകൾ_Of_അട്ടി--;
        pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
        #എങ്കിൽ  __CALLING_CONVENTION__ == __CC_V2__
            /* V2: parameter via A:DE, do not push pvParameters on stack */
        #അല്ലെങ്കിൽ
            /* V1 or unknown: keep stack write */
            *pulLocal = ( uint32_t ) pvParameters;
            px_മുകൾ_Of_അട്ടി--;
        #endif
        /* The return address is a 32-bit value. So decrement the stack pointer
         * in order to make extra room needed to store the correct value.  See the
         * comments above the prvTaskExitError() prototype at the top of this file. */
        px_മുകൾ_Of_അട്ടി--;
        pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_മുകൾ_Of_അട്ടി--;
        /* The task function start address combined with the PSW is also stored
         * as a 32-bit value. So leave a space for the second two bytes. */
        px_മുകൾ_Of_അട്ടി--;
        pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
        *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
        px_മുകൾ_Of_അട്ടി--;
        /* Register image on task entry. */
        #എങ്കിൽ  __CALLING_CONVENTION__ == __CC_V2__
        {
            uint32_t p = ( uint32_t ) pvParameters;
            uint16_t de_init = (uint16_t)( p & 0xFFFFU );
            uint16_t ax_init = (uint16_t)( ((p >> 16) & 0xFFU) << 8 );
            /* AX register image */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) ax_init;
            px_മുകൾ_Of_അട്ടി--;
            /* HL register image (dummy) */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x2222;
            px_മുകൾ_Of_അട്ടി--;
            /* CS:ES register image */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x0F00;
            px_മുകൾ_Of_അട്ടി--;
            /* DE register image */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) de_init;
            px_മുകൾ_Of_അട്ടി--;
        }
        #അല്ലെങ്കിൽ
            /* An initial value for the AX register. */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x1111;
            px_മുകൾ_Of_അട്ടി--;
            /* HL register image (dummy) */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x2222;
            px_മുകൾ_Of_അട്ടി--;
            /* CS:ES register image */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x0F00;
            px_മുകൾ_Of_അട്ടി--;
            /* DE register image (dummy) */
            *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xDEDE;
            px_മുകൾ_Of_അട്ടി--;
        #endif
        /* BC remains a dummy value (not used for parameter passing). */
        *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xBCBC;
        px_മുകൾ_Of_അട്ടി--;
    }
#അല്ലെങ്കിൽ /* if __DATA_MODEL__ == __DATA_MODEL_FAR__ */
    {
       /* The return address, leaving space for the first two bytes of the
         * 32-bit value.  See the comments above the prvTaskExitError() prototype
         * at the top of this file. */
        px_മുകൾ_Of_അട്ടി--;
        pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_മുകൾ_Of_അട്ടി--;
        /* Task function.  Again as it is written as a 32-bit value a space is
         * left on the stack for the second two bytes. */
        px_മുകൾ_Of_അട്ടി--;
        /* Task function start address combined with the PSW. */
        pulLocal = ( uint32_t * ) px_മുകൾ_Of_അട്ടി;
        *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
        px_മുകൾ_Of_അട്ടി--;
        /* The parameter is passed in AX. */
        *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters;
        px_മുകൾ_Of_അട്ടി--;
        /* An initial value for the HL register. */
        *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x2222;
        px_മുകൾ_Of_അട്ടി--;
        /* CS and ES registers. */
        *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0x0F00;
        px_മുകൾ_Of_അട്ടി--;
        /* The remaining general purpose registers DE and BC */
        *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xDEDE;
        px_മുകൾ_Of_അട്ടി--;
        *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) 0xBCBC;
        px_മുകൾ_Of_അട്ടി--;
    }
#endif /* __DATA_MODEL__ */
    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portNO_CRITICAL_SECTION_NESTING;
    /* Return a pointer to the top of the stack that has been generated so
     * it can be stored in the task control block for the task. */
    തിരികെ px_മുകൾ_Of_അട്ടി;
}

/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvTaskExitError( ശൂന്യം )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( usCriticalNesting == ~0U );
    portDISABLE_INTERRUPTS();

    വേണ്ടി( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    /* Setup the hardware to generate the tick. Interrupts are disabled when
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
