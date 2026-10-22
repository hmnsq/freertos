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
#تعریف_کن پورت_NVIC_SYSTICK_CTRL       ( ( متطاير uint32_t * ) 0xe000e010 )
#تعریف_کن پورت_NVIC_SYSTICK_بارگیری       ( ( متطاير uint32_t * ) 0xe000e014 )
#تعریف_کن پورت_NVIC_SHPR3_REG          ( ( متطاير uint32_t * ) 0xe000ed20 )
#تعریف_کن پورت_NVIC_SYSTICK_CLK        0x00000004
#تعریف_کن پورت_NVIC_SYSTICK_INT        0x00000002
#تعریف_کن پورت_NVIC_SYSTICK_ENABLE     0x00000001
#تعریف_کن پورت_MIN_وقفه_اولویت  ( 255UL )
#تعریف_کن پورت_NVIC_PENDSV_PRI         ( ( ( uint32_t ) پورت_MIN_وقفه_اولویت ) << 16UL )
#تعریف_کن پورت_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) پورت_MIN_وقفه_اولویت ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کن پورت_VECTACTIVE_ماسک         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#تعریف_کن پورت_FPCCR                   ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#تعریف_کن پورت_ASPEN_AND_LSPEN_بیتها    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کن پورت_INITIAL_XPSR            ( 0x01000000 )
#تعریف_کن پورت_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#اگر_تعریف_شده config_TASK_RETURN_آدرس
    #تعریف_کن پورت_TASK_RETURN_آدرس    config_TASK_RETURN_آدرس
#وإلا
    #تعریف_کن پورت_TASK_RETURN_آدرس    prvTaskExitError
#پایان_اگر

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کن پورت_شروع_آدرس_ماسک    ( ( پشته_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ثابت uint32_t ul_Kernel_اولویت = پورت_MIN_وقفه_اولویت;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

/*
 * Exception handlers.
 */
فراغ SysTick_Handler( فراغ );

/*
 * Functions defined in port_asm.asm.
 */
خارجي فراغ v_پورت_Enable_VFP( فراغ );
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ثابت uint32_t ul_Max_Syscall_وقفه_اولویت_Const = config_MAX_SYSCALL_وقفه_اولویت;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = پورت_INITIAL_XPSR;                                    /* xPSR */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( ( پشته_Type_t ) px_کد ) & پورت_شروع_آدرس_ماسک; /* PC */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_TASK_RETURN_آدرس;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_بالاترین_از_پشته -= 5;                            /* R12, R3, R2 and R1. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_INITIAL_EXC_RETURN;

    px_بالاترین_از_پشته -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    أرجع px_بالاترین_از_پشته;
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
    پورت_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( پورت_NVIC_SHPR3_REG ) |= پورت_NVIC_PENDSV_PRI;
    *( پورت_NVIC_SHPR3_REG ) |= پورت_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_راهاندازی_Timer_وقفه();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورت_Enable_VFP();

    /* Lazy save always. */
    *( پورت_FPCCR ) |= پورت_ASPEN_AND_LSPEN_بیتها;

    /* Start the first task. */
    v_پورت_شروع_اولی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    *( پورت_NVIC_INT_CTRL ) = پورت_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    پورت_DISABLE_INTERRUPTS();
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
        configASSERT( ( ( *( پورت_NVIC_INT_CTRL ) ) & پورت_VECTACTIVE_ماسک ) == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورت_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ )
{
    uint32_t ulDummy;

    ulDummy = پورت_مجموعه_وقفه_ماسک_FROM_ISR();
    traceISR_ENTER();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();
            /* Pend a context switch. */
            *( پورت_NVIC_INT_CTRL ) = پورت_NVIC_PENDSVSET;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورت_CLEAR_وقفه_ماسک_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( پورت_NVIC_SYSTICK_بارگیری ) = ( configCPU_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL;
    *( پورت_NVIC_SYSTICK_CTRL ) = پورت_NVIC_SYSTICK_CLK | پورت_NVIC_SYSTICK_INT | پورت_NVIC_SYSTICK_ENABLE;
}