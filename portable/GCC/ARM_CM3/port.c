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
* Implementation of functions defined in portable.h for the ARM CM3 port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

/* Prototype of all Interrupt Service Routines (ISRs). */
প্রকারলেখ শূন্য ( * portISR_t )( শূন্য );

/* Constants required to manipulate the core.  Registers first... */
#define portNVIC_SYSTICK_CTRL_REG             ( *( ( অস্থির uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG             ( *( ( অস্থির uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_মান_REG    ( *( ( অস্থির uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR2_REG                    ( *( ( অস্থির uint32_t * ) 0xe000ed1c ) )
#define portNVIC_SHPR3_REG                    ( *( ( অস্থির uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#define portNVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#define portNVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#define portNVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#define port_NVIC_SYSTICK_গুনতি_FLAG_BIT       ( 1UL << 16UL )
#define portNVIC_PENDSVCLEAR_BIT              ( 1UL << 27UL )
#define portNVIC_PEND_SYSTICK_SET_BIT         ( 1UL << 26UL )
#define portNVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )

#define portMIN_INTERRUPT_PRIORITY            ( 255UL )
#define portNVIC_PENDSV_PRI                   ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI                  ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#define portSCB_VTOR_REG                      ( *( ( portISR_t ** ) 0xE000ED08 ) )
#define port_VECTOR_সূচক_SVC                  ( 11 )
#define port_VECTOR_সূচক_PENDSV               ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#define port_FIRST_USER_INTERRUPT_সংখ্যা       ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16       ( 0xE000E3F0 )
#define portAIRCR_REG                         ( *( ( অস্থির uint32_t * ) 0xE000ED0C ) )
#define port_MAX_8_BIT_মান                   ( ( uint8_t ) 0xff )
#define port_শীর্ষ_BIT_OF_BYTE                   ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS                 ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK               ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#define portVECTACTIVE_MASK                   ( 0xFFUL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR                      ( 0x01000000UL )

/* The systick is a 24-bit counter. */
#define port_MAX_24_BIT_সংখ্যা                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#define portMISSED_COUNTS_FACTOR              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK                ( ( স্তূপ_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT_CONFIG    ( portNVIC_SYSTICK_CLK_BIT )
#অন্যথা
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#endif

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#অন্যথা
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
শূন্য vPortSetupTimerInterrupt( শূন্য );

/*
 * Exception handlers.
 */
শূন্য xPortPendSVHandler( শূন্য ) __attribute__( ( naked ) );
শূন্য xPortSysTickHandler( শূন্য );
শূন্য vPortSVCHandler( শূন্য ) __attribute__( ( naked ) );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
স্থির শূন্য prvPortStartFirstTask( শূন্য ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
স্থির শূন্য prvTaskExitError( শূন্য );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
স্থির UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#যদি ( configUSE_TICKLESS_IDLE == 1 )
    স্থির uint32_t ulTimerCountsForOneTick = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#যদি ( configUSE_TICKLESS_IDLE == 1 )
    স্থির uint32_t xMaximumPossibleSuppressedTicks = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#যদি ( configUSE_TICKLESS_IDLE == 1 )
    স্থির uint32_t ulStoppedTimerCompensation = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#যদি ( configASSERT_DEFINED == 1 )
    স্থির uint8_t ucMaxSysCallPriority = 0;
    স্থির uint32_t ulMaxPRIGROUPValue = 0;
    স্থির ধ্রুবক অস্থির uint8_t * ধ্রুবক pcInterruptPriorityRegisters = ( ধ্রুবক অস্থির uint8_t * ধ্রুবক ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_শীর্ষ_Of_স্তূপ--;                                                      /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_শীর্ষ_Of_স্তূপ = portINITIAL_XPSR;                                    /* xPSR */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( ( স্তূপ_Type_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) portTASK_RETURN_ADDRESS;             /* LR */
    px_শীর্ষ_Of_স্তূপ -= 5;                                                   /* R12, R3, R2 and R1. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters;                        /* R0 */
    px_শীর্ষ_Of_স্তূপ -= 8;                                                   /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    ফেরত px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvTaskExitError( শূন্য )
{
    অস্থির uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    যখন( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being defined
         * but never called.  ulDummy is used purely to quieten other warnings
         * about code appearing after this function is called - making ulDummy
         * volatile makes the compiler think the function could return and
         * therefore not output an 'unreachable code' warning for code that appears
         * after it. */
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortSVCHandler( শূন্য )
{
    __asm অস্থির (
        "   ldr r3, =pxCurrentTCB           \n" /* Restore the context. */
        "   ldr r1, [r3]                    \n" /* Get the pxCurrentTCB address. */
        "   ldr r0, [r1]                    \n" /* The first item in pxCurrentTCB is the task top of stack. */
        "   ldmia r0!, {r4-r11}             \n" /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
        "   msr psp, r0                     \n" /* Restore the task stack pointer. */
        "   isb                             \n"
        "   mov r0, #0                      \n"
        "   msr basepri, r0                 \n"
        "   orr r14, #0xd                   \n"
        "   bx r14                          \n"
        "                                   \n"
        "   .ltorg                          \n"
        );
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvPortStartFirstTask( শূন্য )
{
    __asm অস্থির (
        " ldr r0, =0xE000ED08   \n" /* Use the NVIC offset register to locate the stack. */
        " ldr r0, [r0]          \n"
        " ldr r0, [r0]          \n"
        " msr msp, r0           \n" /* Set the msp back to the start of the stack. */
        " cpsie i               \n" /* Globally enable interrupts. */
        " cpsie f               \n"
        " dsb                   \n"
        " isb                   \n"
        " svc 0                 \n" /* System call to start first task. */
        " nop                   \n"
        " .ltorg                \n"
        );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( শূন্য )
{
    /* An application can install FreeRTOS interrupt handlers in one of the
     * following ways:
     * 1. Direct Routing - Install the functions vPortSVCHandler and
     *    xPortPendSVHandler for SVCall and PendSV interrupts respectively.
     * 2. Indirect Routing - Install separate handlers for SVCall and PendSV
     *    interrupts and route program control from those handlers to
     *    vPortSVCHandler and xPortPendSVHandler functions.
     *
     * Applications that use Indirect Routing must set
     * configCHECK_HANDLER_INSTALLATION to 0 in their FreeRTOSConfig.h. Direct
     * routing, which is validated here when configCHECK_HANDLER_INSTALLATION
     * is 1, should be preferred when possible. */
    #যদি ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ধ্রুবক portISR_t * ধ্রুবক pxVectorTable = portSCB_VTOR_REG;

        /* Validate that the application has correctly installed the FreeRTOS
         * handlers for SVCall and PendSV interrupts. We do not check the
         * installation of the SysTick handler because the application may
         * choose to drive the RTOS tick using a timer other than the SysTick
         * timer by overriding the weak function vPortSetupTimerInterrupt().
         *
         * Assertion failures here indicate incorrect installation of the
         * FreeRTOS handlers. For help installing the FreeRTOS handlers, see
         * https://www.freertos.org/Why-FreeRTOS/FAQs.
         *
         * Systems with a configurable address for the interrupt vector table
         * can also encounter assertion failures or even system faults here if
         * VTOR is not set correctly to point to the application's vector table. */
        configASSERT( pxVectorTable[ port_VECTOR_সূচক_SVC ] == vPortSVCHandler );
        configASSERT( pxVectorTable[ port_VECTOR_সূচক_PENDSV ] == xPortPendSVHandler );
    }
    #endif /* configCHECK_HANDLER_INSTALLATION */

    #যদি ( configASSERT_DEFINED == 1 )
    {
        অস্থির uint8_t ucOriginalPriority;
        অস্থির uint32_t ulImplementedPrioBits = 0;
        অস্থির uint8_t * ধ্রুবক pucFirstUserPriorityRegister = ( অস্থির uint8_t * ধ্রুবক ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_সংখ্যা );
        অস্থির uint8_t uc_Max_Priority_মান;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_মান;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_মান = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_মান;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( ~uc_Max_Priority_মান ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        যখন( ( uc_Max_Priority_মান & port_শীর্ষ_BIT_OF_BYTE ) == port_শীর্ষ_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_মান <<= ( uint8_t ) 0x01;
        }

        যদি( ulImplementedPrioBits == 8 )
        {
            /* When the hardware implements 8 priority bits, there is no way for
             * the software to configure PRIGROUP to not have sub-priorities. As
             * a result, the least significant bit is always used for sub-priority
             * and there are 128 preemption priorities and 2 sub-priorities.
             *
             * This may cause some confusion in some cases - for example, if
             * configMAX_SYSCALL_INTERRUPT_PRIORITY is set to 5, both 5 and 4
             * priority interrupts will be masked in Critical Sections as those
             * are at the same preemption priority. This may appear confusing as
             * 4 is higher (numerically lower) priority than
             * configMAX_SYSCALL_INTERRUPT_PRIORITY and therefore, should not
             * have been masked. Instead, if we set configMAX_SYSCALL_INTERRUPT_PRIORITY
             * to 4, this confusion does not happen and the behaviour remains the same.
             *
             * The following assert ensures that the sub-priority bit in the
             * configMAX_SYSCALL_INTERRUPT_PRIORITY is clear to avoid the above mentioned
             * confusion. */
            configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        অন্যথা
        {
            ulMaxPRIGROUPValue = portMAX_PRIGROUP_BITS - ulImplementedPrioBits;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= portPRIGROUP_SHIFT;
        ulMaxPRIGROUPValue &= portPRIORITY_GROUP_MASK;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *pucFirstUserPriorityRegister = ucOriginalPriority;
    }
    #endif /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    portNVIC_SHPR3_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG |= portNVIC_SYSTICK_PRI;
    portNVIC_SHPR2_REG = 0;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prvPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS.  Call
     * vTaskSwitchContext() so link time optimisation does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here! */
    ফেরত 0;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

শূন্য vPortEnterCritical( শূন্য )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    যদি( uxCriticalNesting == 1 )
    {
        configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortExitCritical( শূন্য )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    যদি( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

শূন্য xPortPendSVHandler( শূন্য )
{
    /* This is a naked function. */

    __asm অস্থির
    (
        "   mrs r0, psp                         \n"
        "   isb                                 \n"
        "                                       \n"
        "   ldr r3, =pxCurrentTCB               \n" /* Get the location of the current TCB. */
        "   ldr r2, [r3]                        \n"
        "                                       \n"
        "   stmdb r0!, {r4-r11}                 \n" /* Save the remaining registers. */
        "   str r0, [r2]                        \n" /* Save the new top of stack into the first member of the TCB. */
        "                                       \n"
        "   stmdb sp!, {r3, r14}                \n"
        "   mov r0, %0                          \n"
        "   msr basepri, r0                     \n"
        "   bl vTaskSwitchContext               \n"
        "   mov r0, #0                          \n"
        "   msr basepri, r0                     \n"
        "   ldmia sp!, {r3, r14}                \n"
        "                                       \n" /* Restore the context, including the critical nesting count. */
        "   ldr r1, [r3]                        \n"
        "   ldr r0, [r1]                        \n" /* The first item in pxCurrentTCB is the task top of stack. */
        "   ldmia r0!, {r4-r11}                 \n" /* Pop the registers. */
        "   msr psp, r0                         \n"
        "   isb                                 \n"
        "   bx r14                              \n"
        "                                       \n"
        "   .ltorg                              \n"
        ::"i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY )
    );
}
/*-----------------------------------------------------------*/

শূন্য xPortSysTickHandler( শূন্য )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    portDISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        অন্যথা
        {
            traceISR_EXIT();
        }
    }
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

#যদি ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) শূন্য vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_মান, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_বাম;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        যদি( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm অস্থির ( "cpsid i" ::: "memory" );
        __asm অস্থির ( "dsb" );
        __asm অস্থির ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        যদি( eTaskConfirmSleepModeStatus() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm অস্থির ( "cpsie i" ::: "memory" );
        }
        অন্যথা
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_বাম = port_NVIC_SYSTICK_CURRENT_মান_REG;

            যদি( ul_Sys_Tick_Decrements_বাম == 0 )
            {
                ul_Sys_Tick_Decrements_বাম = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_মান = ul_Sys_Tick_Decrements_বাম + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            যদি( ( portNVIC_INT_CTRL_REG & portNVIC_PEND_SYSTICK_SET_BIT ) != 0 )
            {
                portNVIC_INT_CTRL_REG = portNVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_মান -= ulTimerCountsForOneTick;
            }

            যদি( ul_Reload_মান > ulStoppedTimerCompensation )
            {
                ul_Reload_মান -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            portNVIC_SYSTICK_LOAD_REG = ul_Reload_মান;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            port_NVIC_SYSTICK_CURRENT_মান_REG = 0UL;

            /* Restart SysTick. */
            portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            যদি( xModifiableIdleTime > 0 )
            {
                __asm অস্থির ( "dsb" ::: "memory" );
                __asm অস্থির ( "wfi" );
                __asm অস্থির ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm অস্থির ( "cpsie i" ::: "memory" );
            __asm অস্থির ( "dsb" );
            __asm অস্থির ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm অস্থির ( "cpsid i" ::: "memory" );
            __asm অস্থির ( "dsb" );
            __asm অস্থির ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            যদি( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_গুনতি_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_Load_মান;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_Load_মান = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_মান - port_NVIC_SYSTICK_CURRENT_মান_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                যদি( ( ul_Calculated_Load_মান <= ulStoppedTimerCompensation ) || ( ul_Calculated_Load_মান > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_Load_মান = ( ulTimerCountsForOneTick - 1UL );
                }

                portNVIC_SYSTICK_LOAD_REG = ul_Calculated_Load_মান;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            অন্যথা
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_বাম = port_NVIC_SYSTICK_CURRENT_মান_REG;
                #যদি ( portNVIC_SYSTICK_CLK_BIT_CONFIG != portNVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    যদি( ul_Sys_Tick_Decrements_বাম == 0 )
                    {
                        ul_Sys_Tick_Decrements_বাম = ul_Reload_মান;
                    }
                }
                #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_বাম;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                portNVIC_SYSTICK_LOAD_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            port_NVIC_SYSTICK_CURRENT_মান_REG = 0UL;
            portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            #যদি ( portNVIC_SYSTICK_CLK_BIT_CONFIG == portNVIC_SYSTICK_CLK_BIT )
            {
                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
            }
            #অন্যথা
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;

                যদি( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_গুনতি_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    port_NVIC_SYSTICK_CURRENT_মান_REG = 0;
                }

                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            }
            #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            vTaskStepTick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm অস্থির ( "cpsie i" ::: "memory" );
        }
    }

#endif /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) শূন্য vPortSetupTimerInterrupt( শূন্য )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #যদি ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
        xMaximumPossibleSuppressedTicks = port_MAX_24_BIT_সংখ্যা / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #endif /* configUSE_TICKLESS_IDLE */

    /* Stop and clear the SysTick. */
    portNVIC_SYSTICK_CTRL_REG = 0UL;
    port_NVIC_SYSTICK_CURRENT_মান_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

#যদি ( configASSERT_DEFINED == 1 )

    শূন্য vPortValidateInterruptPriority( শূন্য )
    {
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        /* Obtain the number of the currently executing interrupt. */
        __asm অস্থির ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        যদি( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_সংখ্যা )
        {
            /* Look up the interrupt's priority. */
            ucCurrentPriority = pcInterruptPriorityRegisters[ ulCurrentInterrupt ];

            /* The following assertion will fail if a service routine (ISR) for
             * an interrupt that has been assigned a priority above
             * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
             * function.  ISR safe FreeRTOS API functions must *only* be called
             * from interrupts that have been assigned a priority at or below
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Numerically low interrupt priority numbers represent logically high
             * interrupt priorities, therefore the priority of the interrupt must
             * be set to a value equal to or numerically *higher* than
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Interrupts that  use the FreeRTOS API must not be left at their
             * default priority of  zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and  therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( ucCurrentPriority >= ucMaxSysCallPriority );
        }

        /* Priority grouping:  The interrupt controller (NVIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * If the application only uses CMSIS libraries for interrupt
         * configuration then the correct setting can be achieved on all Cortex-M
         * devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
         * scheduler.  Note however that some vendor specific peripheral libraries
         * assume a non-zero priority group setting, in which cases using a value
         * of zero will result in unpredictable behaviour. */
        configASSERT( ( portAIRCR_REG & portPRIORITY_GROUP_MASK ) <= ulMaxPRIGROUPValue );
    }

#endif /* configASSERT_DEFINED */
