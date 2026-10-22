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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* The critical nesting value is initialised to a non zero value to ensure
 * interrupts don't accidentally become enabled before the scheduler is started. */
#నిర్వచించు పోర్టు_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )

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
#నిర్వచించు పోర్టు_PSW                         ( 0xc6UL )

/* The address of the pxCurrentTCB variable, but don't know or need to know its
 * type. */
రకనిర్వచనం శూన్య TCB_t;
బాహ్య అస్థిర TCB_t * అస్థిర pxCurrentTCB;

/* Each task maintains a count of the critical section nesting depth.  Each time
 * a critical section is entered the count is incremented.  Each time a critical
 * section is exited the count is decremented - with interrupts only being
 * re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as that could cause problems during the startup
 * sequence. */
అస్థిర uint16_t usCriticalNesting = పోర్టు_INITIAL_CRITICAL_NESTING;

/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
బాహ్య శూన్య v_Application_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Starts the scheduler by loading the context of the first Task to run.
 * (implemented in portasm.s).
 */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    uint32_t * pulLocal;
    /* With large data sizeof( StackType_t ) == 2, and
     * sizeof( StackType_t * ) == 4.  With small data
     * sizeof( StackType_t ) == 2 and sizeof( StackType_t * ) == 2. */
#ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_FAR__
    {
        /* Far pointer parameters are passed using the A:DE registers (24-bit).
         * Although they are stored in memory as a 32-bit value.  Hence decrement
         * the stack pointer, so 2 bytes are left for the contents of A, before
         * storing the pvParameters value. */
        px_శిఖరం_యొక్క_దొంతర--;
        pulLocal = ( uint32_t * ) px_శిఖరం_యొక్క_దొంతర;
        #ఒకవేళ  __CALLING_CONVENTION__ == __CC_V2__
            /* V2: parameter via A:DE, do not push pvParameters on stack */
        #లేకపోతే
            /* V1 or unknown: keep stack write */
            *pulLocal = ( uint32_t ) pvParameters;
            px_శిఖరం_యొక్క_దొంతర--;
        #అయితే_ముగింపు
        /* The return address is a 32-bit value. So decrement the stack pointer
         * in order to make extra room needed to store the correct value.  See the
         * comments above the prvTaskExitError() prototype at the top of this file. */
        px_శిఖరం_యొక్క_దొంతర--;
        pulLocal = ( uint32_t * ) px_శిఖరం_యొక్క_దొంతర;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_శిఖరం_యొక్క_దొంతర--;
        /* The task function start address combined with the PSW is also stored
         * as a 32-bit value. So leave a space for the second two bytes. */
        px_శిఖరం_యొక్క_దొంతర--;
        pulLocal = ( uint32_t * ) px_శిఖరం_యొక్క_దొంతర;
        *pulLocal = ( ( ( uint32_t ) px_సంకేతం ) | ( పోర్టు_PSW << 24UL ) );
        px_శిఖరం_యొక్క_దొంతర--;
        /* Register image on task entry. */
        #ఒకవేళ  __CALLING_CONVENTION__ == __CC_V2__
        {
            uint32_t p = ( uint32_t ) pvParameters;
            uint16_t de_init = (uint16_t)( p & 0xFFFFU );
            uint16_t ax_init = (uint16_t)( ((p >> 16) & 0xFFU) << 8 );
            /* AX register image */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ax_init;
            px_శిఖరం_యొక్క_దొంతర--;
            /* HL register image (dummy) */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x2222;
            px_శిఖరం_యొక్క_దొంతర--;
            /* CS:ES register image */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0F00;
            px_శిఖరం_యొక్క_దొంతర--;
            /* DE register image */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) de_init;
            px_శిఖరం_యొక్క_దొంతర--;
        }
        #లేకపోతే
            /* An initial value for the AX register. */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x1111;
            px_శిఖరం_యొక్క_దొంతర--;
            /* HL register image (dummy) */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x2222;
            px_శిఖరం_యొక్క_దొంతర--;
            /* CS:ES register image */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0F00;
            px_శిఖరం_యొక్క_దొంతర--;
            /* DE register image (dummy) */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDEDE;
            px_శిఖరం_యొక్క_దొంతర--;
        #అయితే_ముగింపు
        /* BC remains a dummy value (not used for parameter passing). */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xBCBC;
        px_శిఖరం_యొక్క_దొంతర--;
    }
#లేకపోతే /* if __DATA_MODEL__ == __DATA_MODEL_FAR__ */
    {
       /* The return address, leaving space for the first two bytes of the
         * 32-bit value.  See the comments above the prvTaskExitError() prototype
         * at the top of this file. */
        px_శిఖరం_యొక్క_దొంతర--;
        pulLocal = ( uint32_t * ) px_శిఖరం_యొక్క_దొంతర;
        *pulLocal = ( uint32_t ) prvTaskExitError;
        px_శిఖరం_యొక్క_దొంతర--;
        /* Task function.  Again as it is written as a 32-bit value a space is
         * left on the stack for the second two bytes. */
        px_శిఖరం_యొక్క_దొంతర--;
        /* Task function start address combined with the PSW. */
        pulLocal = ( uint32_t * ) px_శిఖరం_యొక్క_దొంతర;
        *pulLocal = ( ( ( uint32_t ) px_సంకేతం ) | ( పోర్టు_PSW << 24UL ) );
        px_శిఖరం_యొక్క_దొంతర--;
        /* The parameter is passed in AX. */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
        px_శిఖరం_యొక్క_దొంతర--;
        /* An initial value for the HL register. */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x2222;
        px_శిఖరం_యొక్క_దొంతర--;
        /* CS and ES registers. */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0F00;
        px_శిఖరం_యొక్క_దొంతర--;
        /* The remaining general purpose registers DE and BC */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDEDE;
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xBCBC;
        px_శిఖరం_యొక్క_దొంతర--;
    }
#అయితే_ముగింపు /* __DATA_MODEL__ */
    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_NO_CRITICAL_SECTION_NESTING;
    /* Return a pointer to the top of the stack that has been generated so
     * it can be stored in the task control block for the task. */
    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}

/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( usCriticalNesting == ~0U );
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Setup the hardware to generate the tick. Interrupts are disabled when
     * this function is called. */
    v_Application_అమరిక_Timer_అంతరాయం();

    /* Restore the context of the first task that is going to run. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Execution should not reach here as the tasks are now running! */
    తిరిగి pdTRUE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the RL78 port will get stopped. */
}
/*-----------------------------------------------------------*/
