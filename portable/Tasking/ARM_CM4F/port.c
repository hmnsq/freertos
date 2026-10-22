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
* Implementation of functions defined in portable.h for the ARM CM4F port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Constants required to manipulate the NVIC. */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CTRL       ( ( चञ्चल uint32_t * ) 0xe000e010 )
#परिभाषय पत्तनम्_NVIC_SYSTICK_आरोपय       ( ( चञ्चल uint32_t * ) 0xe000e014 )
#परिभाषय पत्तनम्_NVIC_SHPR3_REG          ( ( चञ्चल uint32_t * ) 0xe000ed20 )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CLK        0x00000004
#परिभाषय पत्तनम्_NVIC_SYSTICK_INT        0x00000002
#परिभाषय पत्तनम्_NVIC_SYSTICK_ENABLE     0x00000001
#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता  ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI         ( ( ( uint32_t ) पत्तनम्_MIN_व्यवधानम्_प्राथमिकता ) << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) पत्तनम्_MIN_व्यवधानम्_प्राथमिकता ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#परिभाषय पत्तनम्_VECTACTIVE_आवरणम्         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#परिभाषय पत्तनम्_FPCCR                   ( ( चञ्चल uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#परिभाषय पत्तनम्_ASPEN_AND_LSPEN_द्वयङ्काः    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#परिभाषय पत्तनम्_INITIAL_XPSR            ( 0x01000000 )
#परिभाषय पत्तनम्_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#यदि_परिभाषितम् config_TASK_RETURN_स्थानाङ्कः
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    config_TASK_RETURN_स्थानाङ्कः
#अन्यथा
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    prvTaskExitError
#यदि_अन्तः

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#परिभाषय पत्तनम्_START_स्थानाङ्कः_आवरणम्    ( ( राशिः_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ध्रुव uint32_t ul_Kernel_प्राथमिकता = पत्तनम्_MIN_व्यवधानम्_प्राथमिकता;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
स्थिर uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * Exception handlers.
 */
शून्य SysTick_Handler( शून्य );

/*
 * Functions defined in port_asm.asm.
 */
बाह्य शून्य v_पत्तनम्_Enable_VFP( शून्य );
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ध्रुव uint32_t ul_Max_Syscall_व्यवधानम्_प्राथमिकता_Const = config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR;                                    /* xPSR */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( ( राशिः_Type_t ) px_संहिता ) & पत्तनम्_START_स्थानाङ्कः_आवरणम्; /* PC */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_शिखरम्_सम्बन्धि_राशिः -= 5;                            /* R12, R3, R2 and R1. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EXC_RETURN;

    px_शिखरम्_सम्बन्धि_राशिः -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

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
    configASSERT( ulCriticalNesting == ~0UL );
    पत्तनम्_DISABLE_INTERRUPTS();

    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( पत्तनम्_NVIC_SHPR3_REG ) |= पत्तनम्_NVIC_PENDSV_PRI;
    *( पत्तनम्_NVIC_SHPR3_REG ) |= पत्तनम्_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_पत्तनम्_Enable_VFP();

    /* Lazy save always. */
    *( पत्तनम्_FPCCR ) |= पत्तनम्_ASPEN_AND_LSPEN_द्वयङ्काः;

    /* Start the first task. */
    v_पत्तनम्_Start_First_Task();

    /* Should not get here! */
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

शून्य v_पत्तनम्_Yield( शून्य )
{
    /* Set a PendSV to request a context switch. */
    *( पत्तनम्_NVIC_INT_CTRL ) = पत्तनम्_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    यदि( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( पत्तनम्_NVIC_INT_CTRL ) ) & पत्तनम्_VECTACTIVE_आवरणम् ) == 0 );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    यदि( ulCriticalNesting == 0 )
    {
        पत्तनम्_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

शून्य SysTick_Handler( शून्य )
{
    uint32_t ulDummy;

    ulDummy = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    traceISR_ENTER();
    {
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
            /* Pend a context switch. */
            *( पत्तनम्_NVIC_INT_CTRL ) = पत्तनम्_NVIC_PENDSVSET;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( पत्तनम्_NVIC_SYSTICK_आरोपय ) = ( configCPU_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL;
    *( पत्तनम्_NVIC_SYSTICK_CTRL ) = पत्तनम्_NVIC_SYSTICK_CLK | पत्तनम्_NVIC_SYSTICK_INT | पत्तनम्_NVIC_SYSTICK_ENABLE;
}