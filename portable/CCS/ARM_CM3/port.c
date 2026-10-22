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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#إذا ( config_MAX_SYSCALL_مداخله_لومړیتوب == 0 )
    #تېروتنه config_MAX_SYSCALL_مداخله_لومړیتوب must not be سېټ منزل 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#د_که_پای

/* Constants required to manipulate the core.  Registers first... */
#تعریف_کړه پورټ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_بارول_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کړه پورټ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ              ( 1UL << 2UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_INT_بټ              ( 1UL << 1UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_ENABLE_بټ           ( 1UL << 0UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ       ( 1UL << 16UL )
#تعریف_کړه پورټ_NVIC_PENDSVCLEAR_بټ              ( 1UL << 27UL )
#تعریف_کړه پورټ_NVIC_PEND_SYSTICK_سېټ_بټ         ( 1UL << 26UL )
#تعریف_کړه پورټ_NVIC_PEND_SYSTICK_CLEAR_بټ       ( 1UL << 25UL )

#تعریف_کړه پورټ_MIN_مداخله_لومړیتوب            ( 255UL )
#تعریف_کړه پورټ_NVIC_PENDSV_PRI                   ( ( ( uint32_t ) پورټ_MIN_مداخله_لومړیتوب ) << 16UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_PRI                  ( ( ( uint32_t ) پورټ_MIN_مداخله_لومړیتوب ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#تعریف_کړه پورټ_لومړی_USER_مداخله_شمېره       ( 16 )
#تعریف_کړه پورټ_NVIC_IP_REGISTERS_دننه_واټن_16       ( 0xE000E3F0 )
#تعریف_کړه پورټ_AIRCR_REG                         ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کړه پورټ_MAX_8_بټ_ارزښت                   ( ( uint8_t ) 0xff )
#تعریف_کړه پورټ_سر_بټ_د_BYTE                   ( ( uint8_t ) 0x80 )
#تعریف_کړه پورټ_MAX_PRIGROUP_بټونه                 ( ( uint8_t ) 7 )
#تعریف_کړه پورټ_لومړیتوب_ډله_ماسک               ( 0x07UL << 8UL )
#تعریف_کړه پورټ_PRIGROUP_ښويدنه                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کړه پورټ_VECTACTIVE_ماسک                   ( 0xFFUL )

/* Constants required to set up the initial stack. */
#تعریف_کړه پورټ_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#تعریف_کړه پورټ_MAX_24_بټ_شمېره                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#تعریف_کړه پورټ_MISSED_COUNTS_ضریب              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کړه پورټ_پیل_پته_ماسک                ( ( ډېری_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#که_نه_تعریف_شوی configSYSTICK_CLOCK_HZ
    #تعریف_کړه configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG    ( پورټ_NVIC_SYSTICK_CLK_بټ )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG    ( 0 )
#د_که_پای

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورټ_Sys_Tick_Handler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* Required to allow portasm.asm access the configMAX_SYSCALL_INTERRUPT_PRIORITY
 * setting. */
ثابت uint32_t ul_Max_Syscall_مداخله_لومړیتوب = config_MAX_SYSCALL_مداخله_لومړیتوب;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_اعظمي_Possible_Suppressed_Ticks = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( configASSERT_DEFINED == 1 )
    ساكن uint8_t uc_Max_Sys_Call_لومړیتوب = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_مداخله_لومړیتوب_Registers = ( uint8_t * ) پورټ_NVIC_IP_REGISTERS_دننه_واټن_16;
#د_که_پای /* configASSERT_DEFINED */

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
    *px_سر_د_ډېری = ( ډېری_Type_t ) prvTaskExitError;                    /* LR */

    /* Save code space by skipping register initialisation. */
    px_سر_د_ډېری -= 5;                            /* R12, R3, R2 and R1. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */

    px_سر_د_ډېری -= 8;                            /* R11, R10, R9, R8, R7, R6, R5 and R4. */

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
    configASSERT( uxCriticalNesting == ~0UL );
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
    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_لومړیتوب;
        متطاير uint32_t ul_Implemented_Prio_بټونه = 0;
        متطاير uint8_t * ثابت puc_لومړی_User_لومړیتوب_ثبتوونکی = ( uint8_t * ) ( پورټ_NVIC_IP_REGISTERS_دننه_واټن_16 + پورټ_لومړی_USER_مداخله_شمېره );
        متطاير uint8_t uc_Max_لومړیتوب_ارزښت;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_لومړیتوب = *puc_لومړی_User_لومړیتوب_ثبتوونکی;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_لومړی_User_لومړیتوب_ثبتوونکی = پورټ_MAX_8_بټ_ارزښت;

        /* Read the value back to see how many bits stuck. */
        uc_Max_لومړیتوب_ارزښت = *puc_لومړی_User_لومړیتوب_ثبتوونکی;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_لومړیتوب = config_MAX_SYSCALL_مداخله_لومړیتوب & uc_Max_لومړیتوب_ارزښت;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_لومړیتوب );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_مداخله_لومړیتوب & ( ~uc_Max_لومړیتوب_ارزښت ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        طالما( ( uc_Max_لومړیتوب_ارزښت & پورټ_سر_بټ_د_BYTE ) == پورټ_سر_بټ_د_BYTE )
        {
            ul_Implemented_Prio_بټونه++;
            uc_Max_لومړیتوب_ارزښت <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بټونه == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_مداخله_لومړیتوب & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورټ_MAX_PRIGROUP_بټونه - ul_Implemented_Prio_بټونه;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورټ_PRIGROUP_ښويدنه;
        ulMaxPRIGROUPValue &= پورټ_لومړیتوب_ډله_ماسک;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_لومړی_User_لومړیتوب_ثبتوونکی = uc_Original_لومړیتوب;
    }
    #د_که_پای /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_PENDSV_PRI;
    پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورټ_تیاری_Timer_مداخله();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

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
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    پورټ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    إذا( uxCriticalNesting == 1 )
    {
        configASSERT( ( پورټ_NVIC_INT_CTRL_REG & پورټ_VECTACTIVE_ماسک ) == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    إذا( uxCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ x_پورټ_Sys_Tick_Handler( فراغ )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    ( فراغ ) پورټ_سېټ_مداخله_ماسک_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( 0 );
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    #لارښوونه WEAK( v_پورټ_Suppress_Ticks_And_Sleep )
    فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت )
    {
        uint32_t ul_Reload_ارزښت, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_کیڼ;
        TickType_t x_Modifiable_Idle_وخت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_وخت > x_اعظمي_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وخت = x_اعظمي_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm( "    cpsid i" );
        __asm( "    dsb" );
        __asm( "    isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_ډېرپېښ_حالت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm( "    cpsie i" );
        }
        وإلا
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_کیڼ = پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG;

            إذا( ul_Sys_Tick_Decrements_کیڼ == 0 )
            {
                ul_Sys_Tick_Decrements_کیڼ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ارزښت = ul_Sys_Tick_Decrements_کیڼ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وخت - 1UL ) );

            إذا( ( پورټ_NVIC_INT_CTRL_REG & پورټ_NVIC_PEND_SYSTICK_سېټ_بټ ) != 0 )
            {
                پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PEND_SYSTICK_CLEAR_بټ;
                ul_Reload_ارزښت -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_ارزښت > ulStoppedTimerCompensation )
            {
                ul_Reload_ارزښت -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورټ_NVIC_SYSTICK_بارول_REG = ul_Reload_ارزښت;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;

            /* Restart SysTick. */
            پورټ_NVIC_SYSTICK_CTRL_REG |= پورټ_NVIC_SYSTICK_ENABLE_بټ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_وخت = x_Expected_Idle_وخت;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_وخت );

            إذا( x_Modifiable_Idle_وخت > 0 )
            {
                __asm( "    dsb" );
                __asm( "    wfi" );
                __asm( "    isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وخت );

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
            پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورټ_NVIC_SYSTICK_CTRL_REG & پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ ) != 0 )
            {
                uint32_t ul_Calculated_بارول_ارزښت;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_بارول_ارزښت = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ارزښت - پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_بارول_ارزښت <= ulStoppedTimerCompensation ) || ( ul_Calculated_بارول_ارزښت > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_بارول_ارزښت = ( ulTimerCountsForOneTick - 1UL );
                }

                پورټ_NVIC_SYSTICK_بارول_REG = ul_Calculated_بارول_ارزښت;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_وخت - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_کیڼ = پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG;
                #إذا ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG != پورټ_NVIC_SYSTICK_CLK_بټ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_کیڼ == 0 )
                    {
                        ul_Sys_Tick_Decrements_کیڼ = ul_Reload_ارزښت;
                    }
                }
                #د_که_پای /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وخت * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_کیڼ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورټ_NVIC_SYSTICK_بارول_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;
            پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ;
            #إذا ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG == پورټ_NVIC_SYSTICK_CLK_بټ )
            {
                پورټ_NVIC_SYSTICK_بارول_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ | پورټ_NVIC_SYSTICK_INT_بټ;

                إذا( ( پورټ_NVIC_SYSTICK_CTRL_REG & پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0;
                }

                پورټ_NVIC_SYSTICK_بارول_REG = ulTimerCountsForOneTick - 1UL;
                پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ;
            }
            #د_که_پای /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ګام_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm( "    cpsie i" );
        }
    }

#د_که_پای /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#لارښوونه WEAK( v_پورټ_تیاری_Timer_مداخله )
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
        x_اعظمي_Possible_Suppressed_Ticks = پورټ_MAX_24_بټ_شمېره / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورټ_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #د_که_پای /* configUSE_TICKLESS_IDLE */

    /* Stop and clear the SysTick. */
    پورټ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورټ_NVIC_SYSTICK_بارول_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ );
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ )
    {
        خارجي uint32_t ul_پورټ_Get_IPSR( فراغ );
        uint32_t ul_Current_مداخله;
        uint8_t uc_Current_لومړیتوب;

        ul_Current_مداخله = ul_پورټ_Get_IPSR();

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_مداخله >= پورټ_لومړی_USER_مداخله_شمېره )
        {
            /* Look up the interrupt's priority. */
            uc_Current_لومړیتوب = pc_مداخله_لومړیتوب_Registers[ ul_Current_مداخله ];

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
            configASSERT( uc_Current_لومړیتوب >= uc_Max_Sys_Call_لومړیتوب );
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
        configASSERT( ( پورټ_AIRCR_REG & پورټ_لومړیتوب_ډله_ماسک ) <= ulMaxPRIGROUPValue );
    }

#د_که_پای /* configASSERT_DEFINED */
