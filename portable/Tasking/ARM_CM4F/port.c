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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to manipulate the NVIC. */
#define portNVIC_SYSTICK_CTRL       ( ( ಚಞ್ಚಲ uint32_t * ) 0xe000e010 )
#define portNVIC_SYSTICK_LOAD       ( ( ಚಞ್ಚಲ uint32_t * ) 0xe000e014 )
#define portNVIC_SHPR3_REG          ( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ed20 )
#define portNVIC_SYSTICK_CLK        0x00000004
#define portNVIC_SYSTICK_INT        0x00000002
#define portNVIC_SYSTICK_ENABLE     0x00000001
#define portMIN_INTERRUPT_PRIORITY  ( 255UL )
#define portNVIC_PENDSV_PRI         ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI        ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#define portVECTACTIVE_MASK         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#define portFPCCR                   ( ( ಚಞ್ಚಲ uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#define portASPEN_AND_LSPEN_BITS    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR            ( 0x01000000 )
#define portINITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#ಅನ್ಯಥಾ
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK    ( ( ರಾಶಿ_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ಧ್ರುವ uint32_t ulKernelPriority = portMIN_INTERRUPT_PRIORITY;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ಸ್ಥಿರ uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ );

/*
 * Exception handlers.
 */
ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ );

/*
 * Functions defined in port_asm.asm.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ vPortEnableVFP( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortStartFirstTask( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ಧ್ರುವ uint32_t ulMaxSyscallInterruptPriorityConst = configMAX_SYSCALL_INTERRUPT_PRIORITY;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = portINITIAL_XPSR;                                    /* xPSR */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ( ರಾಶಿ_Type_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) portTASK_RETURN_ADDRESS;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_ತುದಿ_Of_ರಾಶಿ -= 5;                            /* R12, R3, R2 and R1. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = portINITIAL_EXC_RETURN;

    px_ತುದಿ_Of_ರಾಶಿ -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    ಪ್ರತಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( portNVIC_SHPR3_REG ) |= portNVIC_PENDSV_PRI;
    *( portNVIC_SHPR3_REG ) |= portNVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    vPortEnableVFP();

    /* Lazy save always. */
    *( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    ಪ್ರತ್ಯಾಗಮ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ )
{
    /* Set a PendSV to request a context switch. */
    *( portNVIC_INT_CTRL ) = portNVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ )
{
    portDISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ಯದಿ( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( portNVIC_INT_CTRL ) ) & portVECTACTIVE_MASK ) == 0 );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ಯದಿ( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ )
{
    uint32_t ulDummy;

    ulDummy = portSET_INTERRUPT_MASK_FROM_ISR();
    traceISR_ENTER();
    {
        ಯದಿ( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();
            /* Pend a context switch. */
            *( portNVIC_INT_CTRL ) = portNVIC_PENDSVSET;
        }
        ಅನ್ಯಥಾ
        {
            traceISR_EXIT();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( portNVIC_SYSTICK_LOAD ) = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    *( portNVIC_SYSTICK_CTRL ) = portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE;
}