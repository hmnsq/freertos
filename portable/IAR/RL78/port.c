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
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

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
প্রকারলেখ শূন্য TCB_t;
বাহ্যিক অস্থির TCB_t * অস্থির pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each time
 * a critical section is entered the count is incremented.  Each time a critical
 * section is exited the count is decremented - with interrupts only being
 * re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as that could cause problems during the startup
 * sequence. */
অস্থির uint16_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
বাহ্যিক শূন্য vApplicationSetupTimerInterrupt( শূন্য );

/*
 * Starts the scheduler by loading the context of the first Task to run.
 * (implemented in portasm.s).
 */
বাহ্যিক শূন্য vPortStartFirstTask( শূন্য );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
স্থির শূন্য prvTaskExitError( শূন্য );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    uint32_t * pulLocal;
    /* With large data sizeof( StackType_t ) == 2, and
     * sizeof( StackType_t * ) == 4.  With small data
     * sizeof( StackType_t ) == 2 and sizeof( StackType_t * ) == 2. */
#যদি __DATA_MODEL__ == __DATA_MODEL_FAR__
    {
        /* Far pointer parameters are passed using the A:DE registers (24-bit).
         * Although they are stored in memory as a 32-bit value.  Hence decrement
         * the stack pointer, so 2 bytes are left for the contents of A, before
         * storing the pvParameters value. */
        px_শীর্ষ_Of_স্তূপ--;
        pulLocal = ( uint32_t * ) px_শীর্ষ_Of_স্তূপ;
        #যদি  __CALLING_CONVENTION__ == __CC_V2__
            /* V2: parameter via A:DE, do not push pvParameters on stack */
        #অন্যথা
            /* V1 or unknown: keep stack write */
            *pulLocal = ( uint32_t ) pvParameters;
            px_শীর্ষ_Of_স্তূপ--;
        #endif
        /* The return address is a 32-bit value. So decrement the stack pointer
         * in order to make extra room needed to store the correct value.  See the
         * comments above the prvTaskExitError() prototype at the top of this file. */
        px_শীর্ষ_Of_স্তূপ--;
        pulLocal = ( uint32_t * ) px_শীর্ষ_Of_স্তূপ;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_শীর্ষ_Of_স্তূপ--;
        /* The task function start address combined with the PSW is also stored
         * as a 32-bit value. So leave a space for the second two bytes. */
        px_শীর্ষ_Of_স্তূপ--;
        pulLocal = ( uint32_t * ) px_শীর্ষ_Of_স্তূপ;
        *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
        px_শীর্ষ_Of_স্তূপ--;
        /* Register image on task entry. */
        #যদি  __CALLING_CONVENTION__ == __CC_V2__
        {
            uint32_t p = ( uint32_t ) pvParameters;
            uint16_t de_init = (uint16_t)( p & 0xFFFFU );
            uint16_t ax_init = (uint16_t)( ((p >> 16) & 0xFFU) << 8 );
            /* AX register image */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) ax_init;
            px_শীর্ষ_Of_স্তূপ--;
            /* HL register image (dummy) */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x2222;
            px_শীর্ষ_Of_স্তূপ--;
            /* CS:ES register image */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x0F00;
            px_শীর্ষ_Of_স্তূপ--;
            /* DE register image */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) de_init;
            px_শীর্ষ_Of_স্তূপ--;
        }
        #অন্যথা
            /* An initial value for the AX register. */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x1111;
            px_শীর্ষ_Of_স্তূপ--;
            /* HL register image (dummy) */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x2222;
            px_শীর্ষ_Of_স্তূপ--;
            /* CS:ES register image */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x0F00;
            px_শীর্ষ_Of_স্তূপ--;
            /* DE register image (dummy) */
            *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xDEDE;
            px_শীর্ষ_Of_স্তূপ--;
        #endif
        /* BC remains a dummy value (not used for parameter passing). */
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xBCBC;
        px_শীর্ষ_Of_স্তূপ--;
    }
#অন্যথা /* if __DATA_MODEL__ == __DATA_MODEL_FAR__ */
    {
       /* The return address, leaving space for the first two bytes of the
         * 32-bit value.  See the comments above the prvTaskExitError() prototype
         * at the top of this file. */
        px_শীর্ষ_Of_স্তূপ--;
        pulLocal = ( uint32_t * ) px_শীর্ষ_Of_স্তূপ;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_শীর্ষ_Of_স্তূপ--;
        /* Task function.  Again as it is written as a 32-bit value a space is
         * left on the stack for the second two bytes. */
        px_শীর্ষ_Of_স্তূপ--;
        /* Task function start address combined with the PSW. */
        pulLocal = ( uint32_t * ) px_শীর্ষ_Of_স্তূপ;
        *pulLocal = ( ( ( uint32_t ) pxCode ) | ( portPSW << 24UL ) );
        px_শীর্ষ_Of_স্তূপ--;
        /* The parameter is passed in AX. */
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters;
        px_শীর্ষ_Of_স্তূপ--;
        /* An initial value for the HL register. */
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x2222;
        px_শীর্ষ_Of_স্তূপ--;
        /* CS and ES registers. */
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x0F00;
        px_শীর্ষ_Of_স্তূপ--;
        /* The remaining general purpose registers DE and BC */
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xDEDE;
        px_শীর্ষ_Of_স্তূপ--;
        *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xBCBC;
        px_শীর্ষ_Of_স্তূপ--;
    }
#endif /* __DATA_MODEL__ */
    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) portNO_CRITICAL_SECTION_NESTING;
    /* Return a pointer to the top of the stack that has been generated so
     * it can be stored in the task control block for the task. */
    ফেরত px_শীর্ষ_Of_স্তূপ;
}

/*-----------------------------------------------------------*/

স্থির শূন্য prvTaskExitError( শূন্য )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( usCriticalNesting == ~0U );
    portDISABLE_INTERRUPTS();

    জন্য( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    /* Setup the hardware to generate the tick. Interrupts are disabled when
     * this function is called. */
    vApplicationSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run. */
    vPortStartFirstTask();

    /* Execution should not reach here as the tasks are now running! */
    ফেরত pdTRUE;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* It is unlikely that the RL78 port will get stopped. */
}
/*-----------------------------------------------------------*/
