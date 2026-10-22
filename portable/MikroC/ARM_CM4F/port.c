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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

/* Constants required to manipulate the core.  Registers first... */
#define portNVIC_SYSTICK_CTRL_REG             ( *( ( അസ്ഥിര uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG             ( *( ( അസ്ഥിര uint32_t * ) 0xe000e014 ) )
#define port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG    ( *( ( അസ്ഥിര uint32_t * ) 0xe000e018 ) )
#define portNVIC_SHPR3_REG                    ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#define portNVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#define portNVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#define portNVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#define port_NVIC_SYSTICK_എണ്ണം_FLAG_BIT       ( 1UL << 16UL )
#define portNVIC_PENDSVCLEAR_BIT              ( 1UL << 27UL )
#define portNVIC_PEND_SYSTICK_SET_BIT         ( 1UL << 26UL )
#define portNVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )

#define portMIN_INTERRUPT_PRIORITY            ( 255UL )
#define portNVIC_PENDSV_PRI                   ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI                  ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#define port_FIRST_USER_INTERRUPT_സംഖ്യ       ( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16       ( 0xE000E3F0 )
#define portAIRCR_REG                         ( *( ( അസ്ഥിര uint32_t * ) 0xE000ED0C ) )
#define port_MAX_8_BIT_മൂല്യം                   ( ( uint8_t ) 0xff )
#define port_മുകൾ_BIT_OF_BYTE                   ( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS                 ( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK               ( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#define portVECTACTIVE_MASK                   ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#define portFPCCR                             ( ( അസ്ഥിര uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#define portASPEN_AND_LSPEN_BITS              ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR                      ( 0x01000000 )
#define portINITIAL_EXC_RETURN                ( 0xfffffffd )

/* The systick is a 24-bit counter. */
#define port_MAX_24_BIT_സംഖ്യ                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#define portMISSED_COUNTS_FACTOR              ( 94UL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT_CONFIG    ( portNVIC_SYSTICK_CLK_BIT )
#അല്ലെങ്കിൽ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#endif

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#അല്ലെങ്കിൽ
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

/* Cannot find a weak linkage attribute, so the
 * configOVERRIDE_DEFAULT_TICK_CONFIGURATION constant must be set to 1 if the
 * application writer wants to provide their own implementation of
 * vPortSetupTimerInterrupt().  Ensure configOVERRIDE_DEFAULT_TICK_CONFIGURATION
 * is defined. */
#ifndef configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #define configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#endif

/* Manual definition of missing asm names. */
#define psp        9
#define basepri    17
#define msp        8
#define ipsr       5
#define control    20

/* From port.c. */
ബാഹ്യ ശൂന്യം * pxCurrentTCB;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
സ്ഥിതം UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ശൂന്യം vPortSetupTimerInterrupt( ശൂന്യം );

/*
 * Exception handlers.
 */
ശൂന്യം xPortPendSVHandler( ശൂന്യം );
ശൂന്യം xPortSysTickHandler( ശൂന്യം );
ശൂന്യം vPortSVCHandler( ശൂന്യം );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
സ്ഥിതം ശൂന്യം prvPortStartFirstTask( ശൂന്യം );

/*
 * Function to enable the VFP.
 */
സ്ഥിതം ശൂന്യം vPortEnableVFP( ശൂന്യം );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
സ്ഥിതം ശൂന്യം prvTaskExitError( ശൂന്യം );

/*-----------------------------------------------------------*/

/*
 * The number of SysTick increments that make up one tick period.
 */
#എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )
    സ്ഥിതം uint32_t ulTimerCountsForOneTick = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )
    സ്ഥിതം uint32_t xMaximumPossibleSuppressedTicks = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )
    സ്ഥിതം uint32_t ulStoppedTimerCompensation = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#എങ്കിൽ ( configASSERT_DEFINED == 1 )
    സ്ഥിതം uint8_t ucMaxSysCallPriority = 0;
    സ്ഥിതം uint32_t ulMaxPRIGROUPValue = 0;
#endif /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_മുകൾ_Of_അട്ടി--;

    /* Sometimes the parameters are loaded from the stack. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters;
    px_മുകൾ_Of_അട്ടി--;

    *px_മുകൾ_Of_അട്ടി = portINITIAL_XPSR;                        /* xPSR */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pxCode;                  /* PC */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) portTASK_RETURN_ADDRESS; /* LR */

    /* Save code space by skipping register initialisation. */
    px_മുകൾ_Of_അട്ടി -= 5;                            /* R12, R3, R2 and R1. */
    *px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_മുകൾ_Of_അട്ടി--;
    *px_മുകൾ_Of_അട്ടി = portINITIAL_EXC_RETURN;

    px_മുകൾ_Of_അട്ടി -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvTaskExitError( ശൂന്യം )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    വേണ്ടി( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortSVCHandler( ശൂന്യം ) iv IVT_INT_SVCall ics ICS_OFF
{
    __asm {
/* *INDENT-OFF* */
        ldr r3, =_pxCurrentTCB     /* Restore the context. */
        ldr r1, [ r3 ]    /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
        ldr r0, [ r1 ]              /* The first item in pxCurrentTCB is the task top of stack. */
        ldm r0 !, ( r4 - r11, r14 ) /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
        msr psp, r0                 /* Restore the task stack pointer. */
        isb
        mov r0, #0
        msr basepri, r0
        bx r14
/* *INDENT-ON* */
    };
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvPortStartFirstTask( ശൂന്യം )
{
    __asm {
/* *INDENT-OFF* */
        ldr r0, =0xE000ED08 /* Use the NVIC offset register to locate the stack. */
        ldr r0, [ r0 ]
        ldr r0, [ r0 ]
        msr msp, r0 /* Set the msp back to the start of the stack. */

        /* Clear the bit that indicates the FPU is in use in case the FPU was used
         * before the scheduler was started - which would otherwise result in the
         * unnecessary leaving of space in the SVC stack for lazy saving of FPU
         * registers. */
        mov r0, #0
        msr control, r0
        cpsie i /* Globally enable interrupts. */
        cpsie f
        dsb
        isb
        svc #0 /* System call to start first task. */
        nop
/* *INDENT-ON* */
    };
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ശൂന്യം )
{
    #എങ്കിൽ ( configASSERT_DEFINED == 1 )
    {
        അസ്ഥിര uint8_t ucOriginalPriority;
        അസ്ഥിര uint32_t ulImplementedPrioBits = 0;
        അസ്ഥിര uint8_t * സ്ഥിരം pucFirstUserPriorityRegister = ( അസ്ഥിര uint8_t * സ്ഥിരം ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_സംഖ്യ );
        അസ്ഥിര uint8_t uc_Max_Priority_മൂല്യം;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_മൂല്യം;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_മൂല്യം = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_മൂല്യം;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( ~uc_Max_Priority_മൂല്യം ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        ആകുമ്പോൾ( ( uc_Max_Priority_മൂല്യം & port_മുകൾ_BIT_OF_BYTE ) == port_മുകൾ_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_മൂല്യം <<= ( uint8_t ) 0x01;
        }

        എങ്കിൽ( ulImplementedPrioBits == 8 )
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
        അല്ലെങ്കിൽ
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

    /* Make PendSV and SysTick the lowest priority interrupts. */
    portNVIC_SHPR3_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG |= portNVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    vPortEnableVFP();

    /* Lazy save always. */
    *( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

    /* Start the first task. */
    prvPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. */
    prvTaskExitError();

    /* Should not get here! */
    തിരികെ 0;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEnterCritical( ശൂന്യം )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    എങ്കിൽ( uxCriticalNesting == 1 )
    {
        configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortExitCritical( ശൂന്യം )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    എങ്കിൽ( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

സ്ഥിരം uint8_t ucMaxSyscallInterruptPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY;
ശൂന്യം xPortPendSVHandler( ശൂന്യം ) iv IVT_INT_PendSV ics ICS_OFF
{
    __asm {
        #ifdef HW_DEBUG
/* *INDENT-OFF* */

            /* The function is not truly naked, so add back the 4 bytes subtracted
            * from the stack pointer by the function prologue. */
            add sp, sp, # 4
        #endif
        mrs r0, psp
        isb

        ldr r3, =_pxCurrentTCB /* Get the location of the current TCB. */
        ldr r2, [ r3 ]

        tst r14, #0x10 /* Is the task using the FPU context?  If so, push high vfp registers. */
        it eq
        vstmdbeq r0 !, ( s16 - s31 )

        stmdb r0 !, ( r4 - r11, r14 ) /* Save the core registers. */

        str r0, [ r2 ]                /* Save the new top of stack into the first member of the TCB. */

        stmdb sp !, ( r0, r3 )
        ldr r0, = _ucMaxSyscallInterruptPriority
        ldr r1, [ r0 ]
        msr basepri, r1
        dsb
        isb
        bl _vTaskSwitchContext
        mov r0, #0
        msr basepri, r0
        ldm sp !, ( r0, r3 )

        ldr r1, [ r3 ] /* The first item in pxCurrentTCB is the task top of stack. */
        ldr r0, [ r1 ]

        ldm r0 !, ( r4 - r11, r14 ) /* Pop the core registers. */

        tst r14, #0x10             /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
        it eq
        vldmiaeq r0 !, ( s16 - s31 )

        msr psp, r0
        isb
        bx r14
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം xPortSysTickHandler( ശൂന്യം ) iv IVT_INT_SysTick ics ICS_AUTO
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known - therefore the slightly faster portDISABLE_INTERRUPTS() function is
     * used in place of portSET_INTERRUPT_MASK_FROM_ISR(). */
    portDISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        അല്ലെങ്കിൽ
        {
            traceISR_EXIT();
        }
    }
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_TICKLESS_IDLE == 1 ) && ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 ) )

    ശൂന്യം vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_മൂല്യം, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ഇടത്;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        എങ്കിൽ( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm {
            "cpsid i"
        };
        __asm {
            "dsb"
        };
        __asm {
            "isb"
        };

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        എങ്കിൽ( eTaskConfirmSleepModeStatus() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm {
                "cpsie i"
            };
        }
        അല്ലെങ്കിൽ
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
            ul_Sys_Tick_Decrements_ഇടത് = port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG;

            എങ്കിൽ( ul_Sys_Tick_Decrements_ഇടത് == 0 )
            {
                ul_Sys_Tick_Decrements_ഇടത് = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_മൂല്യം = ul_Sys_Tick_Decrements_ഇടത് + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            എങ്കിൽ( ( portNVIC_INT_CTRL_REG & portNVIC_PEND_SYSTICK_SET_BIT ) != 0 )
            {
                portNVIC_INT_CTRL_REG = portNVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_മൂല്യം -= ulTimerCountsForOneTick;
            }

            എങ്കിൽ( ul_Reload_മൂല്യം > ulStoppedTimerCompensation )
            {
                ul_Reload_മൂല്യം -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            portNVIC_SYSTICK_LOAD_REG = ul_Reload_മൂല്യം;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0UL;

            /* Restart SysTick. */
            portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            എങ്കിൽ( xModifiableIdleTime > 0 )
            {
                __asm {
                    "dsb"
                };
                __asm {
                    "wfi"
                };
                __asm {
                    "isb"
                };
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm {
                "cpsie i"
            };
            __asm {
                "dsb"
            };
            __asm {
                "isb"
            };

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm {
                "cpsid i"
            };
            __asm {
                "dsb"
            };
            __asm {
                "isb"
            };

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            എങ്കിൽ( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_എണ്ണം_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_Load_മൂല്യം;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_Load_മൂല്യം = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_മൂല്യം - port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                എങ്കിൽ( ( ul_Calculated_Load_മൂല്യം <= ulStoppedTimerCompensation ) || ( ul_Calculated_Load_മൂല്യം > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_Load_മൂല്യം = ( ulTimerCountsForOneTick - 1UL );
                }

                portNVIC_SYSTICK_LOAD_REG = ul_Calculated_Load_മൂല്യം;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            അല്ലെങ്കിൽ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ഇടത് = port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG;
                #എങ്കിൽ ( portNVIC_SYSTICK_CLK_BIT_CONFIG != portNVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    എങ്കിൽ( ul_Sys_Tick_Decrements_ഇടത് == 0 )
                    {
                        ul_Sys_Tick_Decrements_ഇടത് = ul_Reload_മൂല്യം;
                    }
                }
                #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ഇടത്;

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
            port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0UL;
            portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            #എങ്കിൽ ( portNVIC_SYSTICK_CLK_BIT_CONFIG == portNVIC_SYSTICK_CLK_BIT )
            {
                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
            }
            #അല്ലെങ്കിൽ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;

                എങ്കിൽ( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_എണ്ണം_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0;
                }

                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            }
            #endif /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            vTaskStepTick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm {
                "cpsie i"
            };
        }
    }

    #endif /* #if configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
    #എങ്കിൽ ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    ശൂന്യം vPortSetupTimerInterrupt( ശൂന്യം )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #എങ്കിൽ ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
            xMaximumPossibleSuppressedTicks = port_MAX_24_BIT_സംഖ്യ / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #endif /* configUSE_TICKLESS_IDLE */

        /* Reset SysTick. */
        portNVIC_SYSTICK_CTRL_REG = 0UL;
        port_NVIC_SYSTICK_CURRENT_മൂല്യം_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
        portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT );
    }

    #endif /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

/* This is a naked function. */
സ്ഥിതം ശൂന്യം vPortEnableVFP( ശൂന്യം )
{
    __asm {
/* *INDENT-OFF* */
        ldr r0, =0xE000ED88 /* The FPU enable bits are in the CPACR. */
        ldr r1, [ r0 ]

        orr r1, r1, #0xF00000 /* Enable CP10 and CP11 coprocessors, then save back. */
        str r1, [ r0 ]
        bx r14
/* *INDENT-ON* */
    };
}
/*-----------------------------------------------------------*/

BaseType_t xPortIsInsideInterrupt( ശൂന്യം )
{
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    എങ്കിൽ( CPU_REG_GET( CPU_IPSR ) == 0 )
    {
        xReturn = pdFALSE;
    }
    അല്ലെങ്കിൽ
    {
        xReturn = pdTRUE;
    }

    തിരികെ xReturn;
}
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configASSERT_DEFINED == 1 )

/* Limitations in the MikroC inline asm means ulCurrentInterrupt has to be
 * global - which makes vPortValidateInterruptPriority() non re-entrant.
 * However that should not matter as an interrupt can only itself be
 * interrupted by a higher priority interrupt.  That means if
 * ulCurrentInterrupt, so ulCurrentInterrupt getting corrupted cannot lead to
 * an invalid interrupt priority being missed. */
    uint32_t ulCurrentInterrupt;
    uint8_t ucCurrentPriority;
    ശൂന്യം vPortValidateInterruptPriority( ശൂന്യം )
    {
        /* Obtain the number of the currently executing interrupt. */
        __asm {
/* *INDENT-OFF* */
            തള്ളുക( r0, r1 )
            mrs r0, ipsr
            ldr r1, =_ulCurrentInterrupt
            str r0, [ r1 ]
            എടുക്കുക( r0, r1 )
/* *INDENT-ON* */
        };

        /* Is the interrupt number a user defined interrupt? */
        എങ്കിൽ( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_സംഖ്യ )
        {
            /* Look up the interrupt's priority. */
            ucCurrentPriority = *( ( uint8_t * ) ( portNVIC_IP_REGISTERS_OFFSET_16 + ulCurrentInterrupt ) );

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
