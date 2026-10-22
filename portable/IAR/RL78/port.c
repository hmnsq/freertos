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
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

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
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ TCB_t;
ବାହ୍ୟ ଅସ୍ଥିର TCB_t * ଅସ୍ଥିର pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each time
 * a critical section is entered the count is incremented.  Each time a critical
 * section is exited the count is decremented - with interrupts only being
 * re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as that could cause problems during the startup
 * sequence. */
ଅସ୍ଥିର uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
ବାହ୍ୟ ଶୂନ୍ୟ vApplicationSetupTimerInterrupt( ଶୂନ୍ୟ );

/*
 * Starts the scheduler by loading the context of the first Task to run.
 * (implemented in portasm.s).
 */
ବାହ୍ୟ ଶୂନ୍ୟ vPortStartFirstTask( ଶୂନ୍ୟ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvTaskExitError( ଶୂନ୍ୟ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    uint32_t * pulLocal;
    /* With large data sizeof( StackType_t ) == 2, and
     * sizeof( StackType_t * ) == 4.  With small data
     * sizeof( StackType_t ) == 2 and sizeof( StackType_t * ) == 2. */
#ଯଦି __DATA_MODEL__ == __DATA_MODEL_FAR__
    {
        /* Far pointer parameters are passed using the A:DE registers (24-bit).
         * Although they are stored in memory as a 32-bit value.  Hence decrement
         * the stack pointer, so 2 bytes are left for the contents of A, before
         * storing the pvParameters value. */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        pulLocal = ( uint32_t * ) px_ଶୀର୍ଷ_Of_ଗଦା;
        #ଯଦି  __CALLING_CONVENTION__ == __CC_V2__
            /* V2: parameter via A:DE, do not push pvParameters on stack */
        #ଅନ୍ୟଥା
            /* V1 or unknown: keep stack write */
            *pulLocal = ( uint32_t ) pvParameters;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
        #endif
        /* The return address is a 32-bit value. So decrement the stack pointer
         * in order to make extra room needed to store the correct value.  See the
         * comments above the prvTaskExitError() prototype at the top of this file. */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        pulLocal = ( uint32_t * ) px_ଶୀର୍ଷ_Of_ଗଦା;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* The task function start address combined with the PSW is also stored
         * as a 32-bit value. So leave a space for the second two bytes. */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        pulLocal = ( uint32_t * ) px_ଶୀର୍ଷ_Of_ଗଦା;
        *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* Register image on task entry. */
        #ଯଦି  __CALLING_CONVENTION__ == __CC_V2__
        {
            uint32_t p = ( uint32_t ) pvParameters;
            uint16_t de_init = (uint16_t)( p & 0xFFFFU );
            uint16_t ax_init = (uint16_t)( ((p >> 16) & 0xFFU) << 8 );
            /* AX register image */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) ax_init;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
            /* HL register image (dummy) */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x2222;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
            /* CS:ES register image */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x0F00;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
            /* DE register image */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) de_init;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
        }
        #ଅନ୍ୟଥା
            /* An initial value for the AX register. */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x1111;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
            /* HL register image (dummy) */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x2222;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
            /* CS:ES register image */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x0F00;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
            /* DE register image (dummy) */
            *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xDEDE;
            px_ଶୀର୍ଷ_Of_ଗଦା--;
        #endif
        /* BC remains a dummy value (not used for parameter passing). */
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xBCBC;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
    }
#ଅନ୍ୟଥା /* if __DATA_MODEL__ == __DATA_MODEL_FAR__ */
    {
       /* The return address, leaving space for the first two bytes of the
         * 32-bit value.  See the comments above the prvTaskExitError() prototype
         * at the top of this file. */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        pulLocal = ( uint32_t * ) px_ଶୀର୍ଷ_Of_ଗଦା;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* Task function.  Again as it is written as a 32-bit value a space is
         * left on the stack for the second two bytes. */
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* Task function start address combined with the PSW. */
        pulLocal = ( uint32_t * ) px_ଶୀର୍ଷ_Of_ଗଦା;
        *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* The parameter is passed in AX. */
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pvParameters;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* An initial value for the HL register. */
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x2222;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* CS and ES registers. */
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0x0F00;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        /* The remaining general purpose registers DE and BC */
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xDEDE;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
        *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) 0xBCBC;
        px_ଶୀର୍ଷ_Of_ଗଦା--;
    }
#endif /* __DATA_MODEL__ */
    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) portNO_CRITICAL_SECTION_NESTING;
    /* Return a pointer to the top of the stack that has been generated so
     * it can be stored in the task control block for the task. */
    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}

/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvTaskExitError( ଶୂନ୍ୟ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( usCriticalNesting == ~0U );
    portDISABLE_INTERRUPTS();

    ପାଇଁ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    /* Setup the hardware to generate the tick. Interrupts are disabled when
     * this function is called. */
    vApplicationSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run. */
    vPortStartFirstTask();

    /* Execution should not reach here as the tasks are now running! */
    ଫେରନ୍ତୁ pdTRUE;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    /* It is unlikely that the RL78 port will get stopped. */
}
/*-----------------------------------------------------------*/
