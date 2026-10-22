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

/* IAR includes. */
#अन्तर्भाव <intrinsics.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः
#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#यदि_अपरिभाषितम् config_सज्जता_TICK_व्यवधानम्
    #दोषः config_सज्जता_TICK_व्यवधानम्() must be defined अन्तर् FreeRTOSConfig.h गन्तव्यम् call the function that sets ऊर्ध्वम् the tick व्यवधानम्.  A स्वभाव that उपयुङ्क्ते the PIT is provided अन्तर् the official demo application.
#यदि_अन्तः

#यदि_अपरिभाषितम् config_CLEAR_TICK_व्यवधानम्
    #दोषः config_CLEAR_TICK_व्यवधानम् must be defined अन्तर् FreeRTOSConfig.h गन्तव्यम् clear which ever व्यवधानम् was प्रयुक्तम् गन्तव्यम् generate the tick व्यवधानम्.  A स्वभाव that उपयुङ्क्ते the PIT is provided अन्तर् the official demo application.
#यदि_अन्तः

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#परिभाषय पत्तनम्_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#परिभाषय पत्तनम्_NO_FLOATING_POINT_CONTEXT    ( ( राशिः_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#परिभाषय पत्तनम्_INITIAL_SPSR                 ( ( राशिः_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#परिभाषय पत्तनम्_THUMB_बहुलकम्_BIT               ( ( राशिः_Type_t ) 0x20 )
#परिभाषय पत्तनम्_THUMB_बहुलकम्_स्थानाङ्कः           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#परिभाषय पत्तनम्_APSR_बहुलकम्_द्वयङ्काः_आवरणम्          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#परिभाषय पत्तनम्_APSR_USER_बहुलकम्               ( 0x10 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
बाह्य शून्य v_पत्तनम्_Restore_Task_Context( शून्य );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
चञ्चल uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero
 * then a floating point context must be saved and restored for the task. */
uint32_t ul_पत्तनम्_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_पत्तनम्_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_पत्तनम्_व्यवधानम्_Nesting = 0UL;


/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_शिखरम्_सम्बन्धि_राशिः = रिक्त;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = रिक्त;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = रिक्त;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_INITIAL_SPSR;

    यदि( ( ( uint32_t ) px_संहिता & पत्तनम्_THUMB_बहुलकम्_स्थानाङ्कः ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_शिखरम्_सम्बन्धि_राशिः |= पत्तनम्_THUMB_बहुलकम्_BIT;
    }

    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next the return address, which in this case is the start of the task. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next all the registers other than the stack pointer. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) prvTaskExitError; /* R14 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12121212;       /* R12 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11111111;       /* R11 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10101010;       /* R10 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09090909;       /* R9 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x08080808;       /* R8 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07070707;       /* R7 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06060606;       /* R6 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x05050505;       /* R5 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04040404;       /* R4 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03030303;       /* R3 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x02020202;       /* R2 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x01010101;       /* R1 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;     /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_CRITICAL_NESTING;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_FLOATING_POINT_CONTEXT;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_पत्तनम्_व्यवधानम्_Nesting == ~0UL );
    पत्तनम्_DISABLE_INTERRUPTS();

    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm चञ्चल ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= पत्तनम्_APSR_बहुलकम्_द्वयङ्काः_आवरणम्;
    configASSERT( ulAPSR != पत्तनम्_APSR_USER_बहुलकम् );

    यदि( ulAPSR != पत्तनम्_APSR_USER_बहुलकम् )
    {
        /* Start the timer that generates the tick ISR. */
        config_सज्जता_TICK_व्यवधानम्();
        v_पत्तनम्_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    यदि( ulCriticalNesting == 1 )
    {
        configASSERT( ul_पत्तनम्_व्यवधानम्_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    यदि( ulCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            पत्तनम्_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

शून्य FreeRTOS_Tick_Handler( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    यदि( xTaskIncrementTick() != pdFALSE )
    {
        ul_पत्तनम्_Yield_Required = pdTRUE;
    }

    पत्तनम्_ENABLE_INTERRUPTS();
    config_CLEAR_TICK_व्यवधानम्();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_पत्तनम्_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/
