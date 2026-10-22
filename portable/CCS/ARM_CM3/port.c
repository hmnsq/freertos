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
#समावेश "FreeRTOS.h"
#समावेश "task.h"

#अगर ( configMAX_SYSCALL_INTERRUPT_PRIORITY == 0 )
    #त्रुटि configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#पूर्ण_अगर

/* Constants required to manipulate the core.  Registers first... */
#घोषणा portNVIC_SYSTICK_CTRL_REG             ( *( ( अस्थिर uint32_t * ) 0xe000e010 ) )
#घोषणा portNVIC_SYSTICK_LOAD_REG             ( *( ( अस्थिर uint32_t * ) 0xe000e014 ) )
#घोषणा port_NVIC_SYSTICK_CURRENT_मूल्य_REG    ( *( ( अस्थिर uint32_t * ) 0xe000e018 ) )
#घोषणा portNVIC_SHPR3_REG                    ( *( ( अस्थिर uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#घोषणा portNVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#घोषणा portNVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#घोषणा portNVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#घोषणा port_NVIC_SYSTICK_गिनती_FLAG_BIT       ( 1UL << 16UL )
#घोषणा portNVIC_PENDSVCLEAR_BIT              ( 1UL << 27UL )
#घोषणा portNVIC_PEND_SYSTICK_SET_BIT         ( 1UL << 26UL )
#घोषणा portNVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )

#घोषणा portMIN_INTERRUPT_PRIORITY            ( 255UL )
#घोषणा portNVIC_PENDSV_PRI                   ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 16UL )
#घोषणा portNVIC_SYSTICK_PRI                  ( ( ( uint32_t ) portMIN_INTERRUPT_PRIORITY ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#घोषणा port_FIRST_USER_INTERRUPT_संख्या       ( 16 )
#घोषणा portNVIC_IP_REGISTERS_OFFSET_16       ( 0xE000E3F0 )
#घोषणा portAIRCR_REG                         ( *( ( अस्थिर uint32_t * ) 0xE000ED0C ) )
#घोषणा port_MAX_8_BIT_मूल्य                   ( ( uint8_t ) 0xff )
#घोषणा port_शीर्ष_BIT_OF_BYTE                   ( ( uint8_t ) 0x80 )
#घोषणा portMAX_PRIGROUP_BITS                 ( ( uint8_t ) 7 )
#घोषणा portPRIORITY_GROUP_MASK               ( 0x07UL << 8UL )
#घोषणा portPRIGROUP_SHIFT                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#घोषणा portVECTACTIVE_MASK                   ( 0xFFUL )

/* Constants required to set up the initial stack. */
#घोषणा portINITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#घोषणा port_MAX_24_BIT_संख्या                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#घोषणा portMISSED_COUNTS_FACTOR              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#घोषणा portSTART_ADDRESS_MASK                ( ( ढेर_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#अगर_अघोषित configSYSTICK_CLOCK_HZ
    #घोषणा configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #घोषणा portNVIC_SYSTICK_CLK_BIT_CONFIG    ( portNVIC_SYSTICK_CLK_BIT )
#अन्यथा
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #घोषणा portNVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#पूर्ण_अगर

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
व्योम vPortSetupTimerInterrupt( व्योम );

/*
 * Exception handlers.
 */
व्योम xPortSysTickHandler( व्योम );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
बाह्य व्योम vPortStartFirstTask( व्योम );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
अटल व्योम prvTaskExitError( व्योम );

/*-----------------------------------------------------------*/

/* Required to allow portasm.asm access the configMAX_SYSCALL_INTERRUPT_PRIORITY
 * setting. */
स्थिर uint32_t ulMaxSyscallInterruptPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
अटल UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#अगर ( configUSE_TICKLESS_IDLE == 1 )
    अटल uint32_t ulTimerCountsForOneTick = 0;
#पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#अगर ( configUSE_TICKLESS_IDLE == 1 )
    अटल uint32_t xMaximumPossibleSuppressedTicks = 0;
#पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#अगर ( configUSE_TICKLESS_IDLE == 1 )
    अटल uint32_t ulStoppedTimerCompensation = 0;
#पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#अगर ( configASSERT_DEFINED == 1 )
    अटल uint8_t ucMaxSysCallPriority = 0;
    अटल uint32_t ulMaxPRIGROUPValue = 0;
    अटल स्थिर अस्थिर uint8_t * स्थिर pcInterruptPriorityRegisters = ( uint8_t * ) portNVIC_IP_REGISTERS_OFFSET_16;
#पूर्ण_अगर /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_शीर्ष_Of_ढेर--;

    *px_शीर्ष_Of_ढेर = portINITIAL_XPSR;                                    /* xPSR */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ( ढेर_Type_t ) pxCode ) & portSTART_ADDRESS_MASK; /* PC */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) prvTaskExitError;                    /* LR */

    /* Save code space by skipping register initialisation. */
    px_शीर्ष_Of_ढेर -= 5;                            /* R12, R3, R2 and R1. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters; /* R0 */

    px_शीर्ष_Of_ढेर -= 8;                            /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

अटल व्योम prvTaskExitError( व्योम )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    क्रम( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( व्योम )
{
    #अगर ( configASSERT_DEFINED == 1 )
    {
        अस्थिर uint8_t ucOriginalPriority;
        अस्थिर uint32_t ulImplementedPrioBits = 0;
        अस्थिर uint8_t * स्थिर pucFirstUserPriorityRegister = ( uint8_t * ) ( portNVIC_IP_REGISTERS_OFFSET_16 + port_FIRST_USER_INTERRUPT_संख्या );
        अस्थिर uint8_t uc_Max_Priority_मूल्य;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_मूल्य;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_मूल्य = *pucFirstUserPriorityRegister;

        /* Use the same mask on the maximum system call priority. */
        ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & uc_Max_Priority_मूल्य;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( ucMaxSysCallPriority );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( configMAX_SYSCALL_INTERRUPT_PRIORITY & ( ~uc_Max_Priority_मूल्य ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        जबतक( ( uc_Max_Priority_मूल्य & port_शीर्ष_BIT_OF_BYTE ) == port_शीर्ष_BIT_OF_BYTE )
        {
            ulImplementedPrioBits++;
            uc_Max_Priority_मूल्य <<= ( uint8_t ) 0x01;
        }

        अगर( ulImplementedPrioBits == 8 )
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
        अन्यथा
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
    #पूर्ण_अगर /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    portNVIC_SHPR3_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG |= portNVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    अगर( uxCriticalNesting == 1 )
    {
        configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
    }
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    अगर( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

व्योम xPortSysTickHandler( व्योम )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    ( व्योम ) portSET_INTERRUPT_MASK_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( 0 );
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_TICKLESS_IDLE == 1 )

    #आशय WEAK( vPortSuppressTicksAndSleep )
    व्योम vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_मूल्य, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_बायाँ;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        अगर( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm( "    cpsid i" );
        __asm( "    dsb" );
        __asm( "    isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        अगर( eTaskConfirmSleepModeStatus() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm( "    cpsie i" );
        }
        अन्यथा
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
            ul_Sys_Tick_Decrements_बायाँ = port_NVIC_SYSTICK_CURRENT_मूल्य_REG;

            अगर( ul_Sys_Tick_Decrements_बायाँ == 0 )
            {
                ul_Sys_Tick_Decrements_बायाँ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_मूल्य = ul_Sys_Tick_Decrements_बायाँ + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            अगर( ( portNVIC_INT_CTRL_REG & portNVIC_PEND_SYSTICK_SET_BIT ) != 0 )
            {
                portNVIC_INT_CTRL_REG = portNVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_मूल्य -= ulTimerCountsForOneTick;
            }

            अगर( ul_Reload_मूल्य > ulStoppedTimerCompensation )
            {
                ul_Reload_मूल्य -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            portNVIC_SYSTICK_LOAD_REG = ul_Reload_मूल्य;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;

            /* Restart SysTick. */
            portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            अगर( xModifiableIdleTime > 0 )
            {
                __asm( "    dsb" );
                __asm( "    wfi" );
                __asm( "    isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm( "    cpsie i" );
            __asm( "    dsb" );
            __asm( "    isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm( "    cpsid i" );
            __asm( "    dsb" );
            __asm( "    isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            अगर( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_गिनती_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_Load_मूल्य;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_Load_मूल्य = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_मूल्य - port_NVIC_SYSTICK_CURRENT_मूल्य_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                अगर( ( ul_Calculated_Load_मूल्य <= ulStoppedTimerCompensation ) || ( ul_Calculated_Load_मूल्य > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_Load_मूल्य = ( ulTimerCountsForOneTick - 1UL );
                }

                portNVIC_SYSTICK_LOAD_REG = ul_Calculated_Load_मूल्य;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            अन्यथा
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_बायाँ = port_NVIC_SYSTICK_CURRENT_मूल्य_REG;
                #अगर ( portNVIC_SYSTICK_CLK_BIT_CONFIG != portNVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    अगर( ul_Sys_Tick_Decrements_बायाँ == 0 )
                    {
                        ul_Sys_Tick_Decrements_बायाँ = ul_Reload_मूल्य;
                    }
                }
                #पूर्ण_अगर /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_बायाँ;

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
            port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;
            portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            #अगर ( portNVIC_SYSTICK_CLK_BIT_CONFIG == portNVIC_SYSTICK_CLK_BIT )
            {
                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
            }
            #अन्यथा
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;

                अगर( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_गिनती_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0;
                }

                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            }
            #पूर्ण_अगर /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            vTaskStepTick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm( "    cpsie i" );
        }
    }

#पूर्ण_अगर /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#आशय WEAK( vPortSetupTimerInterrupt )
व्योम vPortSetupTimerInterrupt( व्योम )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #अगर ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
        xMaximumPossibleSuppressedTicks = port_MAX_24_BIT_संख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

    /* Stop and clear the SysTick. */
    portNVIC_SYSTICK_CTRL_REG = 0UL;
    port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

#अगर ( configASSERT_DEFINED == 1 )

    व्योम vPortValidateInterruptPriority( व्योम )
    {
        बाह्य uint32_t ulPortGetIPSR( व्योम );
        uint32_t ulCurrentInterrupt;
        uint8_t ucCurrentPriority;

        ulCurrentInterrupt = ulPortGetIPSR();

        /* Is the interrupt number a user defined interrupt? */
        अगर( ulCurrentInterrupt >= port_FIRST_USER_INTERRUPT_संख्या )
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

#पूर्ण_अगर /* configASSERT_DEFINED */
