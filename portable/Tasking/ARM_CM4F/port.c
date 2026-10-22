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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to manipulate the NVIC. */
#تعریف_کړه پورټ_NVIC_SYSTICK_CTRL       ( ( متطاير uint32_t * ) 0xe000e010 )
#تعریف_کړه پورټ_NVIC_SYSTICK_بارول       ( ( متطاير uint32_t * ) 0xe000e014 )
#تعریف_کړه پورټ_NVIC_SHPR3_REG          ( ( متطاير uint32_t * ) 0xe000ed20 )
#تعریف_کړه پورټ_NVIC_SYSTICK_CLK        0x00000004
#تعریف_کړه پورټ_NVIC_SYSTICK_INT        0x00000002
#تعریف_کړه پورټ_NVIC_SYSTICK_ENABLE     0x00000001
#تعریف_کړه پورټ_MIN_مداخله_لومړیتوب  ( 255UL )
#تعریف_کړه پورټ_NVIC_PENDSV_PRI         ( ( ( uint32_t ) پورټ_MIN_مداخله_لومړیتوب ) << 16UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) پورټ_MIN_مداخله_لومړیتوب ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کړه پورټ_VECTACTIVE_ماسک         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#تعریف_کړه پورټ_FPCCR                   ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#تعریف_کړه پورټ_ASPEN_AND_LSPEN_بټونه    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کړه پورټ_INITIAL_XPSR            ( 0x01000000 )
#تعریف_کړه پورټ_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#که_تعریف_شوی config_TASK_RETURN_پته
    #تعریف_کړه پورټ_TASK_RETURN_پته    config_TASK_RETURN_پته
#وإلا
    #تعریف_کړه پورټ_TASK_RETURN_پته    prvTaskExitError
#د_که_پای

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کړه پورټ_پیل_پته_ماسک    ( ( ډېری_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ثابت uint32_t ul_Kernel_لومړیتوب = پورټ_MIN_مداخله_لومړیتوب;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/*
 * Exception handlers.
 */
فراغ SysTick_Handler( فراغ );

/*
 * Functions defined in port_asm.asm.
 */
خارجي فراغ v_پورټ_Enable_VFP( فراغ );
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ثابت uint32_t ul_Max_Syscall_مداخله_لومړیتوب_Const = config_MAX_SYSCALL_مداخله_لومړیتوب;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = پورټ_INITIAL_XPSR;                                    /* xPSR */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ( ډېری_Type_t ) px_کوډ ) & پورټ_پیل_پته_ماسک; /* PC */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_TASK_RETURN_پته;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_سر_د_ډېری -= 5;                            /* R12, R3, R2 and R1. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = پورټ_INITIAL_EXC_RETURN;

    px_سر_د_ډېری -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    پورټ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_مداخله_لومړیتوب ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( پورټ_NVIC_SHPR3_REG ) |= پورټ_NVIC_PENDSV_PRI;
    *( پورټ_NVIC_SHPR3_REG ) |= پورټ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخله();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورټ_Enable_VFP();

    /* Lazy save always. */
    *( پورټ_FPCCR ) |= پورټ_ASPEN_AND_LSPEN_بټونه;

    /* Start the first task. */
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    *( پورټ_NVIC_INT_CTRL ) = پورټ_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    پورټ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    إذا( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( پورټ_NVIC_INT_CTRL ) ) & پورټ_VECTACTIVE_ماسک ) == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ )
{
    uint32_t ulDummy;

    ulDummy = پورټ_سېټ_مداخله_ماسک_FROM_ISR();
    traceISR_ENTER();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            *( پورټ_NVIC_INT_CTRL ) = پورټ_NVIC_PENDSVSET;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( پورټ_NVIC_SYSTICK_بارول ) = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    *( پورټ_NVIC_SYSTICK_CTRL ) = پورټ_NVIC_SYSTICK_CLK | پورټ_NVIC_SYSTICK_INT | پورټ_NVIC_SYSTICK_ENABLE;
}