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

/* Standard includes. */
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 difference priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
    #అయితే_ముగింపు
#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం
    #దోషం config_అమరిక_TICK_అంతరాయం() must be defined లోపల FreeRTOSConfig.h గమ్యం call the function that sets పైకి the tick అంతరాయం.
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_CLEAR_TICK_అంతరాయం
    #దోషం config_CLEAR_TICK_అంతరాయం must be defined లోపల FreeRTOSConfig.h గమ్యం clear which ever అంతరాయం was వాడిన గమ్యం generate the tick అంతరాయం.
#అయితే_ముగింపు

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#నిర్వచించు పోర్టు_NO_FLOATING_బిందువు_CONTEXT    ( ( దొంతర_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#నిర్వచితమైతే __ARMEB__
    #నిర్వచించు పోర్టు_INITIAL_SPSR             ( ( దొంతర_Type_t ) 0x21f ) /* System mode, ARM mode, IRQ enabled FIQ enabled, Big-endian. */
#లేకపోతే
    #నిర్వచించు పోర్టు_INITIAL_SPSR             ( ( దొంతర_Type_t ) 0x01f ) /* System mode, ARM mode, IRQ enabled FIQ enabled, Little-endian. */
#అయితే_ముగింపు
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు               ( ( దొంతర_Type_t ) 0x20 )
#నిర్వచించు పోర్టు_THUMB_బహుళకం_చిరునామా           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#నిర్వచించు పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#నిర్వచించు పోర్టు_APSR_USER_బహుళకం               ( 0x10 )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/* The space on the stack required to hold the FPU registers. */
#ఒకవేళ ( configFPU_D32 == 1 )
    #నిర్వచించు పోర్టు_FPU_రిజిస్టరు_పదాలు     ( ( 32 * 2 ) + 1 ) /* D0-D31 and FPSCR. */
#లేకపోతే
    #నిర్వచించు పోర్టు_FPU_రిజిస్టరు_పదాలు     ( ( 16 * 2 ) + 1 ) /* D0-D15 and FPSCR. */
#అయితే_ముగింపు /* configFPU_D32 */

/*-----------------------------------------------------------*/

/*
 * These functions are necessarily written in assembly code, so are implemented
 * in portASM.S.
 */
బాహ్య శూన్య v_పోర్టు_Restore_Task_Context( శూన్య );
బాహ్య శూన్య v_పోర్టు_Initialise_FPSCR( శూన్య );
బాహ్య uint32_t ulReadAPSR( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
అస్థిర uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
అస్థిర uint32_t ul_పోర్టు_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
అస్థిర uint32_t ul_పోర్టు_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
అస్థిర uint32_t ul_పోర్టు_అంతరాయం_Nesting = 0UL;

/* Used in the asm file to clear an interrupt. */
__attribute__( ( వాడిన ) ) స్థిరరాశి uint32_t ulICCEOIR = config_EOI_చిరునామా;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ఖాళీ;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ఖాళీ;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ఖాళీ;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_INITIAL_SPSR;

    ఒకవేళ( ( ( uint32_t ) px_సంకేతం & పోర్టు_THUMB_బహుళకం_చిరునామా ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_శిఖరం_యొక్క_దొంతర |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }

    px_శిఖరం_యొక్క_దొంతర--;

    /* Next the return address, which in this case is the start of the task. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Next all the registers other than the stack pointer. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212;              /* R12 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111;              /* R11 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010;              /* R10 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909;              /* R9 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808;              /* R8 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707;              /* R7 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606;              /* R6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505;              /* R5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404;              /* R4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303;              /* R3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202;              /* R2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101;              /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;            /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

    #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start without a floating point context.  A task that uses
         * the floating point hardware must call vPortTaskUsesFPU() before executing
         * any floating point instructions. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_FLOATING_బిందువు_CONTEXT;
    }
    #లేదావేళ ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_శిఖరం_యొక్క_దొంతర -= పోర్టు_FPU_రిజిస్టరు_పదాలు;
        memset( px_శిఖరం_యొక్క_దొంతర, 0x00, పోర్టు_FPU_రిజిస్టరు_పదాలు * పరిమాణం( దొంతర_Type_t ) );

        /* Initialise the slot containing ulPortTaskHasFPUContext to true as
         * the task starts with a floating point context. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = pdTRUE;
        ul_పోర్టు_Task_Has_FPUContext = pdTRUE;
    }
    #లేకపోతే
    {
        #దోషం "Invalid configUSE_TASK_FPU_SUPPORT value - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #అయితే_ముగింపు /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

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
    configASSERT( ul_పోర్టు_అంతరాయం_Nesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    ulAPSR = ulReadAPSR();

    ulAPSR &= పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు;
    configASSERT( ulAPSR != పోర్టు_APSR_USER_బహుళకం );

    ఒకవేళ( ulAPSR != పోర్టు_APSR_USER_బహుళకం )
    {
        /* Start the timer that generates the tick ISR. */
        పోర్టు_DISABLE_INTERRUPTS();
        config_అమరిక_TICK_అంతరాయం();

        /* Start the first task executing. */
        v_పోర్టు_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( శూన్య ) prvTaskExitError;
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ఒకవేళ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_పోర్టు_అంతరాయం_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

శూన్య FreeRTOS_Tick_Handler( శూన్య )
{
    uint32_t ul_అంతరాయం_స్థితి;

    ul_అంతరాయం_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

    /* Increment the RTOS tick. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        ul_పోర్టు_Yield_Required = pdTRUE;
    }

    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_అంతరాయం_స్థితి );

    config_CLEAR_TICK_అంతరాయం();
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_FPU_SUPPORT != 2 )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ul_పోర్టు_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        v_పోర్టు_Initialise_FPSCR();
    }

#అయితే_ముగింపు /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/
