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
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CTRL       ( ( متطاير uint32_t * ) 0xe000e010 )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ڀريو       ( ( متطاير uint32_t * ) 0xe000e014 )
#وصف_ڪريو پورٽ_NVIC_SHPR3_REG          ( ( متطاير uint32_t * ) 0xe000ed20 )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CLK        0x00000004
#وصف_ڪريو پورٽ_NVIC_SYSTICK_INT        0x00000002
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ENABLE     0x00000001
#وصف_ڪريو پورٽ_MIN_مداخلت_ترجيح  ( 255UL )
#وصف_ڪريو پورٽ_NVIC_PENDSV_PRI         ( ( ( uint32_t ) پورٽ_MIN_مداخلت_ترجيح ) << 16UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) پورٽ_MIN_مداخلت_ترجيح ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#وصف_ڪريو پورٽ_VECTACTIVE_نقاب         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#وصف_ڪريو پورٽ_FPCCR                   ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#وصف_ڪريو پورٽ_ASPEN_AND_LSPEN_بٽ    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#وصف_ڪريو پورٽ_INITIAL_XPSR            ( 0x01000000 )
#وصف_ڪريو پورٽ_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#جيڪڏهن_وصف_ٿيل config_TASK_RETURN_پتو
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    config_TASK_RETURN_پتو
#وإلا
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    prvTaskExitError
#جيڪڏهن_پورو

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#وصف_ڪريو پورٽ_شروعات_پتو_نقاب    ( ( ڍير_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ثابت uint32_t ul_Kernel_ترجيح = پورٽ_MIN_مداخلت_ترجيح;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*
 * Exception handlers.
 */
فراغ SysTick_Handler( فراغ );

/*
 * Functions defined in port_asm.asm.
 */
خارجي فراغ v_پورٽ_Enable_VFP( فراغ );
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ثابت uint32_t ul_Max_Syscall_مداخلت_ترجيح_Const = config_MAX_SYSCALL_مداخلت_ترجيح;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_XPSR;                                    /* xPSR */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ( ڍير_Type_t ) px_ڪوڊ ) & پورٽ_شروعات_پتو_نقاب; /* PC */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_TASK_RETURN_پتو;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_چوٽي_جو_ڍير -= 5;                            /* R12, R3, R2 and R1. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_EXC_RETURN;

    px_چوٽي_جو_ڍير -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    أرجع px_چوٽي_جو_ڍير;
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
    پورٽ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_مداخلت_ترجيح ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( پورٽ_NVIC_SHPR3_REG ) |= پورٽ_NVIC_PENDSV_PRI;
    *( پورٽ_NVIC_SHPR3_REG ) |= پورٽ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تياري_Timer_مداخلت();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورٽ_Enable_VFP();

    /* Lazy save always. */
    *( پورٽ_FPCCR ) |= پورٽ_ASPEN_AND_LSPEN_بٽ;

    /* Start the first task. */
    v_پورٽ_شروعات_پهريون_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    *( پورٽ_NVIC_INT_CTRL ) = پورٽ_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();
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
        configASSERT( ( ( *( پورٽ_NVIC_INT_CTRL ) ) & پورٽ_VECTACTIVE_نقاب ) == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورٽ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ )
{
    uint32_t ulDummy;

    ulDummy = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
    traceISR_ENTER();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            *( پورٽ_NVIC_INT_CTRL ) = پورٽ_NVIC_PENDSVSET;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( پورٽ_NVIC_SYSTICK_ڀريو ) = ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    *( پورٽ_NVIC_SYSTICK_CTRL ) = پورٽ_NVIC_SYSTICK_CLK | پورٽ_NVIC_SYSTICK_INT | پورٽ_NVIC_SYSTICK_ENABLE;
}