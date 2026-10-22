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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Constants required to manipulate the NVIC. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL       ( ( متلون uint32_t * ) 0xe000e010 )
#تعریف_کرو پورٹ_NVIC_SYSTICK_بھرو       ( ( متلون uint32_t * ) 0xe000e014 )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG          ( ( متلون uint32_t * ) 0xe000ed20 )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CLK        0x00000004
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT        0x00000002
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE     0x00000001
#تعریف_کرو پورٹ_MIN_مداخلت_ترجیح  ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI         ( ( ( uint32_t ) پورٹ_MIN_مداخلت_ترجیح ) << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) پورٹ_MIN_مداخلت_ترجیح ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کرو پورٹ_VECTACTIVE_نقاب         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#تعریف_کرو پورٹ_FPCCR                   ( ( متلون uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#تعریف_کرو پورٹ_ASPEN_AND_LSPEN_بٹ    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کرو پورٹ_INITIAL_XPSR            ( 0x01000000 )
#تعریف_کرو پورٹ_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#اگر_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#ورنہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#اگر_ختم

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کرو پورٹ_آغاز_پتہ_نقاب    ( ( ڈھیر_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ثابت uint32_t ul_Kernel_ترجیح = پورٹ_MIN_مداخلت_ترجیح;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساکن uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*
 * Exception handlers.
 */
خالی SysTick_Handler( خالی );

/*
 * Functions defined in port_asm.asm.
 */
خارجی خالی v_پورٹ_Enable_VFP( خالی );
خارجی خالی v_پورٹ_آغاز_پہلا_Task( خالی );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ثابت uint32_t ul_Max_Syscall_مداخلت_ترجیح_Const = config_MAX_SYSCALL_مداخلت_ترجیح;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_XPSR;                                    /* xPSR */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ( ڈھیر_Type_t ) px_رمز ) & پورٹ_آغاز_پتہ_نقاب; /* PC */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_چوٹی_کا_ڈھیر -= 5;                            /* R12, R3, R2 and R1. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_EXC_RETURN;

    px_چوٹی_کا_ڈھیر -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساکن خالی prvTaskExitError( خالی )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    برائے( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_مداخلت_ترجیح ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( پورٹ_NVIC_SHPR3_REG ) |= پورٹ_NVIC_PENDSV_PRI;
    *( پورٹ_NVIC_SHPR3_REG ) |= پورٹ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخلت();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورٹ_Enable_VFP();

    /* Lazy save always. */
    *( پورٹ_FPCCR ) |= پورٹ_ASPEN_AND_LSPEN_بٹ;

    /* Start the first task. */
    v_پورٹ_آغاز_پہلا_Task();

    /* Should not get here! */
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield( خالی )
{
    /* Set a PendSV to request a context switch. */
    *( پورٹ_NVIC_INT_CTRL ) = پورٹ_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    اگر( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( پورٹ_NVIC_INT_CTRL ) ) & پورٹ_VECTACTIVE_نقاب ) == 0 );
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    اگر( ulCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

خالی SysTick_Handler( خالی )
{
    uint32_t ulDummy;

    ulDummy = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
    traceISR_ENTER();
    {
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();
            /* Pend a context switch. */
            *( پورٹ_NVIC_INT_CTRL ) = پورٹ_NVIC_PENDSVSET;
        }
        ورنہ
        {
            traceISR_EXIT();
        }
    }
    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
خالی prv_تیاری_Timer_مداخلت( خالی )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( پورٹ_NVIC_SYSTICK_بھرو ) = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    *( پورٹ_NVIC_SYSTICK_CTRL ) = پورٹ_NVIC_SYSTICK_CLK | پورٹ_NVIC_SYSTICK_INT | پورٹ_NVIC_SYSTICK_ENABLE;
}