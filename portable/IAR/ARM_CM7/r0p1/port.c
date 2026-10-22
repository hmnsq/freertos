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
* Implementation of functions defined in portable.h for the ARM CM7 port.
*----------------------------------------------------------*/

/* IAR includes. */
#ضمن <intrinsics.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#اگر_تعریف_نشده __ARMVFP__
    #خطا This پورت can only be استفاده_شده when the project options are configured مقصد enable hardware floating نقطه_2 support.
#پایان_اگر

#إذا ( config_MAX_SYSCALL_وقفه_اولویت == 0 )
    #خطا config_MAX_SYSCALL_وقفه_اولویت must not be مجموعه مقصد 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#پایان_اگر

/* Prototype of all Interrupt Service Routines (ISRs). */
تعريفنوع فراغ ( * پورت_ISR_t )( فراغ );

/* Constants required to manipulate the core.  Registers first... */
#تعریف_کن پورت_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کن پورت_NVIC_SYSTICK_بارگیری_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کن پورت_NVIC_SYSTICK_CURRENT_مقدار_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کن پورت_NVIC_SHPR2_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#تعریف_کن پورت_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت              ( 1UL << 2UL )
#تعریف_کن پورت_NVIC_SYSTICK_INT_بیت              ( 1UL << 1UL )
#تعریف_کن پورت_NVIC_SYSTICK_ENABLE_بیت           ( 1UL << 0UL )
#تعریف_کن پورت_NVIC_SYSTICK_شمار_FLAG_بیت       ( 1UL << 16UL )
#تعریف_کن پورت_NVIC_PENDSVCLEAR_بیت              ( 1UL << 27UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_مجموعه_بیت         ( 1UL << 26UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_CLEAR_بیت       ( 1UL << 25UL )

#تعریف_کن پورت_MIN_وقفه_اولویت            ( 255UL )
#تعریف_کن پورت_NVIC_PENDSV_PRI                   ( ( ( uint32_t ) پورت_MIN_وقفه_اولویت ) << 16UL )
#تعریف_کن پورت_NVIC_SYSTICK_PRI                  ( ( ( uint32_t ) پورت_MIN_وقفه_اولویت ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#تعریف_کن پورت_SCB_VTOR_REG                      ( *( ( پورت_ISR_t ** ) 0xE000ED08 ) )
#تعریف_کن پورت_وکتور_شاخص_SVC                  ( 11 )
#تعریف_کن پورت_وکتور_شاخص_PENDSV               ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#تعریف_کن پورت_اولی_USER_وقفه_عدد       ( 16 )
#تعریف_کن پورت_NVIC_IP_REGISTERS_جابه_جایی_16       ( 0xE000E3F0 )
#تعریف_کن پورت_AIRCR_REG                         ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کن پورت_MAX_8_بیت_مقدار                   ( ( uint8_t ) 0xff )
#تعریف_کن پورت_بالاترین_بیت_از_BYTE                   ( ( uint8_t ) 0x80 )
#تعریف_کن پورت_MAX_PRIGROUP_بیتها                 ( ( uint8_t ) 7 )
#تعریف_کن پورت_اولویت_گروه_ماسک               ( 0x07UL << 8UL )
#تعریف_کن پورت_PRIGROUP_لغزش                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کن پورت_VECTACTIVE_ماسک                   ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#تعریف_کن پورت_FPCCR                             ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#تعریف_کن پورت_ASPEN_AND_LSPEN_بیتها              ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کن پورت_INITIAL_XPSR                      ( 0x01000000 )
#تعریف_کن پورت_INITIAL_EXC_RETURN                ( 0xfffffffd )

/* The systick is a 24-bit counter. */
#تعریف_کن پورت_MAX_24_بیت_عدد                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#تعریف_کن پورت_MISSED_COUNTS_ضریب              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کن پورت_شروع_آدرس_ماسک                ( ( پشته_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#اگر_تعریف_نشده configSYSTICK_CLOCK_HZ
    #تعریف_کن configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( پورت_NVIC_SYSTICK_CLK_بیت )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( 0 )
#پایان_اگر

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورت_Sys_Tick_Handler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );

/*
 * Turn the VFP on.
 */
خارجي فراغ v_پورت_Enable_VFP( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * FreeRTOS handlers implemented in assembly.
 */
خارجي فراغ v_پورت_SVCHandler( فراغ );
خارجي فراغ x_پورت_Pend_SVHandler( فراغ );
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_بیشینه_Possible_Suppressed_Ticks = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( configASSERT_DEFINED == 1 )
    ساكن uint8_t uc_Max_Sys_Call_اولویت = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_وقفه_اولویت_Registers = ( ثابت متطاير uint8_t * ثابت ) پورت_NVIC_IP_REGISTERS_جابه_جایی_16;
#پایان_اگر /* configASSERT_DEFINED */

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
    *px_بالاترین_از_پشته = ( پشته_Type_t ) prvTaskExitError;                    /* LR */

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
    configASSERT( uxCriticalNesting == ~0UL );
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
    #إذا ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ثابت پورت_ISR_t * ثابت px_وکتور_جدول = پورت_SCB_VTOR_REG;

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
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_SVC ] == v_پورت_SVCHandler );
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_PENDSV ] == x_پورت_Pend_SVHandler );
    }
    #پایان_اگر /* configCHECK_HANDLER_INSTALLATION */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_اولویت;
        متطاير uint32_t ul_Implemented_Prio_بیتها = 0;
        متطاير uint8_t * ثابت puc_اولی_User_اولویت_ثبات = ( متطاير uint8_t * ثابت ) ( پورت_NVIC_IP_REGISTERS_جابه_جایی_16 + پورت_اولی_USER_وقفه_عدد );
        متطاير uint8_t uc_Max_اولویت_مقدار;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_اولویت = *puc_اولی_User_اولویت_ثبات;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_اولی_User_اولویت_ثبات = پورت_MAX_8_بیت_مقدار;

        /* Read the value back to see how many bits stuck. */
        uc_Max_اولویت_مقدار = *puc_اولی_User_اولویت_ثبات;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_اولویت = config_MAX_SYSCALL_وقفه_اولویت & uc_Max_اولویت_مقدار;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_اولویت );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت & ( uint8_t ) ( ~( uint32_t ) uc_Max_اولویت_مقدار ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        طالما( ( uc_Max_اولویت_مقدار & پورت_بالاترین_بیت_از_BYTE ) == پورت_بالاترین_بیت_از_BYTE )
        {
            ul_Implemented_Prio_بیتها++;
            uc_Max_اولویت_مقدار <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بیتها == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_وقفه_اولویت & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورت_MAX_PRIGROUP_بیتها - ul_Implemented_Prio_بیتها;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورت_PRIGROUP_لغزش;
        ulMaxPRIGROUPValue &= پورت_اولویت_گروه_ماسک;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_اولی_User_اولویت_ثبات = uc_Original_اولویت;
    }
    #پایان_اگر /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_PENDSV_PRI;
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_SYSTICK_PRI;
    پورت_NVIC_SHPR2_REG = 0;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورت_راهاندازی_Timer_وقفه();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

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
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    پورت_DISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    إذا( uxCriticalNesting == 1 )
    {
        configASSERT( ( پورت_NVIC_INT_CTRL_REG & پورت_VECTACTIVE_ماسک ) == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    إذا( uxCriticalNesting == 0 )
    {
        پورت_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ x_پورت_Sys_Tick_Handler( فراغ )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    پورت_DISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورت_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __weak فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان )
    {
        uint32_t ul_Reload_مقدار, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_چپ;
        TickType_t x_Modifiable_Idle_زمان;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_زمان > x_بیشینه_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_زمان = x_بیشینه_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_interrupt();
        __DSB();
        __ISB();

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_نما_وضعیت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_interrupt()
             * call above. */
            __enable_interrupt();
        }
        وإلا
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_چپ = پورت_NVIC_SYSTICK_CURRENT_مقدار_REG;

            إذا( ul_Sys_Tick_Decrements_چپ == 0 )
            {
                ul_Sys_Tick_Decrements_چپ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_مقدار = ul_Sys_Tick_Decrements_چپ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_زمان - 1UL ) );

            إذا( ( پورت_NVIC_INT_CTRL_REG & پورت_NVIC_PEND_SYSTICK_مجموعه_بیت ) != 0 )
            {
                پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PEND_SYSTICK_CLEAR_بیت;
                ul_Reload_مقدار -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_مقدار > ulStoppedTimerCompensation )
            {
                ul_Reload_مقدار -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورت_NVIC_SYSTICK_بارگیری_REG = ul_Reload_مقدار;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

            /* Restart SysTick. */
            پورت_NVIC_SYSTICK_CTRL_REG |= پورت_NVIC_SYSTICK_ENABLE_بیت;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_زمان = x_Expected_Idle_زمان;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_زمان );

            إذا( x_Modifiable_Idle_زمان > 0 )
            {
                __DSB();
                __WFI();
                __ISB();
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_زمان );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_interrupt() call above. */
            __enable_interrupt();
            __DSB();
            __ISB();

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_interrupt();
            __DSB();
            __ISB();

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورت_NVIC_SYSTICK_CTRL_REG & پورت_NVIC_SYSTICK_شمار_FLAG_بیت ) != 0 )
            {
                uint32_t ul_Calculated_بارگیری_مقدار;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_بارگیری_مقدار = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_مقدار - پورت_NVIC_SYSTICK_CURRENT_مقدار_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_بارگیری_مقدار <= ulStoppedTimerCompensation ) || ( ul_Calculated_بارگیری_مقدار > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_بارگیری_مقدار = ( ulTimerCountsForOneTick - 1UL );
                }

                پورت_NVIC_SYSTICK_بارگیری_REG = ul_Calculated_بارگیری_مقدار;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_زمان - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_چپ = پورت_NVIC_SYSTICK_CURRENT_مقدار_REG;
                #إذا ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG != پورت_NVIC_SYSTICK_CLK_بیت )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_چپ == 0 )
                    {
                        ul_Sys_Tick_Decrements_چپ = ul_Reload_مقدار;
                    }
                }
                #پایان_اگر /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_زمان * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_چپ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورت_NVIC_SYSTICK_بارگیری_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;
            پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
            #إذا ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG == پورت_NVIC_SYSTICK_CLK_بیت )
            {
                پورت_NVIC_SYSTICK_بارگیری_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت;

                إذا( ( پورت_NVIC_SYSTICK_CTRL_REG & پورت_NVIC_SYSTICK_شمار_FLAG_بیت ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0;
                }

                پورت_NVIC_SYSTICK_بارگیری_REG = ulTimerCountsForOneTick - 1UL;
                پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
            }
            #پایان_اگر /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_گام_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_interrupt();
        }
    }

#پایان_اگر /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ );
        x_بیشینه_Possible_Suppressed_Ticks = پورت_MAX_24_بیت_عدد / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورت_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #پایان_اگر /* configUSE_TICKLESS_IDLE */

    /* Stop and clear the SysTick. */
    پورت_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورت_NVIC_SYSTICK_بارگیری_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL;
    پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت );
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورت_Validate_وقفه_اولویت( فراغ )
    {
        uint32_t ul_Current_وقفه;
        uint8_t uc_Current_اولویت;

        /* Obtain the number of the currently executing interrupt. */
        __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_وقفه )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_وقفه >= پورت_اولی_USER_وقفه_عدد )
        {
            /* Look up the interrupt's priority. */
            uc_Current_اولویت = pc_وقفه_اولویت_Registers[ ul_Current_وقفه ];

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
            configASSERT( uc_Current_اولویت >= uc_Max_Sys_Call_اولویت );
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
        configASSERT( ( پورت_AIRCR_REG & پورت_اولویت_گروه_ماسک ) <= ulMaxPRIGROUPValue );
    }

#پایان_اگر /* configASSERT_DEFINED */
