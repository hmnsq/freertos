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

#جے_بنا_تعریف __ARMVFP__
    #غلطی This پورٹ can only be ورتیا when the project options are configured منزل enable hardware floating نقطہ_2 support.
#جے_انت

#إذا ( config_MAX_SYSCALL_رکاوٹ_ترجیح == 0 )
    #غلطی config_MAX_SYSCALL_رکاوٹ_ترجیح must not be سیٹ منزل 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#جے_انت

/* Prototype of all Interrupt Service Routines (ISRs). */
تعريفنوع فراغ ( * پورٹ_ISR_t )( فراغ );

/* Constants required to manipulate the core.  Registers first... */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_لدو_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کرو پورٹ_NVIC_SHPR2_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ              ( 1UL << 2UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ              ( 1UL << 1UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ           ( 1UL << 0UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ       ( 1UL << 16UL )
#تعریف_کرو پورٹ_NVIC_PENDSVCLEAR_ثنائی_ہندسہ              ( 1UL << 27UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ         ( 1UL << 26UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ       ( 1UL << 25UL )

#تعریف_کرو پورٹ_MIN_رکاوٹ_ترجیح            ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI                   ( ( ( uint32_t ) پورٹ_MIN_رکاوٹ_ترجیح ) << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI                  ( ( ( uint32_t ) پورٹ_MIN_رکاوٹ_ترجیح ) << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#تعریف_کرو پورٹ_SCB_VTOR_REG                      ( *( ( پورٹ_ISR_t ** ) 0xE000ED08 ) )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_SVC                  ( 11 )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_PENDSV               ( 14 )

/* Constants required to check the validity of an interrupt priority. */
#تعریف_کرو پورٹ_پہلا_USER_رکاوٹ_نمبر       ( 16 )
#تعریف_کرو پورٹ_NVIC_IP_REGISTERS_وتھ_16       ( 0xE000E3F0 )
#تعریف_کرو پورٹ_AIRCR_REG                         ( *( ( متطاير uint32_t * ) 0xE000ED0C ) )
#تعریف_کرو پورٹ_MAX_8_ثنائی_ہندسہ_قدر                   ( ( uint8_t ) 0xff )
#تعریف_کرو پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE                   ( ( uint8_t ) 0x80 )
#تعریف_کرو پورٹ_MAX_PRIGROUP_بٹ                 ( ( uint8_t ) 7 )
#تعریف_کرو پورٹ_ترجیح_گروہ_نقاب               ( 0x07UL << 8UL )
#تعریف_کرو پورٹ_PRIGROUP_کھسکاؤ                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#تعریف_کرو پورٹ_VECTACTIVE_نقاب                   ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#تعریف_کرو پورٹ_FPCCR                             ( ( متطاير uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#تعریف_کرو پورٹ_ASPEN_AND_LSPEN_بٹ              ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#تعریف_کرو پورٹ_INITIAL_XPSR                      ( 0x01000000 )
#تعریف_کرو پورٹ_INITIAL_EXC_RETURN                ( 0xfffffffd )

/* The systick is a 24-bit counter. */
#تعریف_کرو پورٹ_MAX_24_ثنائی_ہندسہ_نمبر                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#تعریف_کرو پورٹ_MISSED_COUNTS_ضارب              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#تعریف_کرو پورٹ_شروع_پتہ_نقاب                ( ( ڈھیر_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#جے_بنا_تعریف configSYSTICK_CLOCK_HZ
    #تعریف_کرو configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( 0 )
#جے_انت

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورٹ_Sys_Tick_Handler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
خارجي فراغ v_پورٹ_شروع_پہلا_Task( فراغ );

/*
 * Turn the VFP on.
 */
خارجي فراغ v_پورٹ_Enable_VFP( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * FreeRTOS handlers implemented in assembly.
 */
خارجي فراغ v_پورٹ_SVCHandler( فراغ );
خارجي فراغ x_پورٹ_Pend_SVHandler( فراغ );
/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#جے_انت /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_ودھ_توں_ودھ_Possible_Suppressed_Ticks = 0;
#جے_انت /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#جے_انت /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#إذا ( configASSERT_DEFINED == 1 )
    ساكن uint8_t uc_Max_Sys_Call_ترجیح = 0;
    ساكن uint32_t ulMaxPRIGROUPValue = 0;
    ساكن ثابت متطاير uint8_t * ثابت pc_رکاوٹ_ترجیح_Registers = ( ثابت متطاير uint8_t * ثابت ) پورٹ_NVIC_IP_REGISTERS_وتھ_16;
#جے_انت /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_XPSR;                                    /* xPSR */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ( ڈھیر_Type_t ) px_کوڈ ) & پورٹ_شروع_پتہ_نقاب; /* PC */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) prvTaskExitError;                    /* LR */

    /* Save code space by skipping register initialisation. */
    px_چوٹی_دا_ڈھیر -= 5;                            /* R12, R3, R2 and R1. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_EXC_RETURN;

    px_چوٹی_دا_ڈھیر -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    أرجع px_چوٹی_دا_ڈھیر;
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
    پورٹ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
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
        ثابت پورٹ_ISR_t * ثابت px_سمتیہ_جدول = پورٹ_SCB_VTOR_REG;

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
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_SVC ] == v_پورٹ_SVCHandler );
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_PENDSV ] == x_پورٹ_Pend_SVHandler );
    }
    #جے_انت /* configCHECK_HANDLER_INSTALLATION */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجیح;
        متطاير uint32_t ul_Implemented_Prio_بٹ = 0;
        متطاير uint8_t * ثابت puc_پہلا_User_ترجیح_رجسٹر = ( متطاير uint8_t * ثابت ) ( پورٹ_NVIC_IP_REGISTERS_وتھ_16 + پورٹ_پہلا_USER_رکاوٹ_نمبر );
        متطاير uint8_t uc_Max_ترجیح_قدر;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ترجیح = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_پہلا_User_ترجیح_رجسٹر = پورٹ_MAX_8_ثنائی_ہندسہ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجیح_قدر = *puc_پہلا_User_ترجیح_رجسٹر;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ترجیح = config_MAX_SYSCALL_رکاوٹ_ترجیح & uc_Max_ترجیح_قدر;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ترجیح );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_رکاوٹ_ترجیح & ( uint8_t ) ( ~( uint32_t ) uc_Max_ترجیح_قدر ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        طالما( ( uc_Max_ترجیح_قدر & پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE ) == پورٹ_چوٹی_ثنائی_ہندسہ_دا_BYTE )
        {
            ul_Implemented_Prio_بٹ++;
            uc_Max_ترجیح_قدر <<= ( uint8_t ) 0x01;
        }

        إذا( ul_Implemented_Prio_بٹ == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_رکاوٹ_ترجیح & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        وإلا
        {
            ulMaxPRIGROUPValue = پورٹ_MAX_PRIGROUP_بٹ - ul_Implemented_Prio_بٹ;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= پورٹ_PRIGROUP_کھسکاؤ;
        ulMaxPRIGROUPValue &= پورٹ_ترجیح_گروہ_نقاب;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_پہلا_User_ترجیح_رجسٹر = uc_Original_ترجیح;
    }
    #جے_انت /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;
    پورٹ_NVIC_SHPR2_REG = 0;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورٹ_تیاری_Timer_رکاوٹ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_پورٹ_Enable_VFP();

    /* Lazy save always. */
    *( پورٹ_FPCCR ) |= پورٹ_ASPEN_AND_LSPEN_بٹ;

    /* Start the first task. */
    v_پورٹ_شروع_پہلا_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    پورٹ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    إذا( uxCriticalNesting == 1 )
    {
        configASSERT( ( پورٹ_NVIC_INT_CTRL_REG & پورٹ_VECTACTIVE_نقاب ) == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    إذا( uxCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ x_پورٹ_Sys_Tick_Handler( فراغ )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    پورٹ_DISABLE_INTERRUPTS();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورٹ_ENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __weak فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا )
    {
        uint32_t ul_Reload_قدر, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_بایاں;
        TickType_t x_Modifiable_Idle_ویلا;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_ویلا > x_ودھ_توں_ودھ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ویلا = x_ودھ_توں_ودھ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_interrupt();
        __DSB();
        __ISB();

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_منوال_حالت() == eAbortSleep )
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
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_بایاں = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;

            إذا( ul_Sys_Tick_Decrements_بایاں == 0 )
            {
                ul_Sys_Tick_Decrements_بایاں = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_قدر = ul_Sys_Tick_Decrements_بایاں + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ویلا - 1UL ) );

            إذا( ( پورٹ_NVIC_INT_CTRL_REG & پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ ) != 0 )
            {
                پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ;
                ul_Reload_قدر -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_قدر > ulStoppedTimerCompensation )
            {
                ul_Reload_قدر -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورٹ_NVIC_SYSTICK_لدو_REG = ul_Reload_قدر;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

            /* Restart SysTick. */
            پورٹ_NVIC_SYSTICK_CTRL_REG |= پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ویلا = x_Expected_Idle_ویلا;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ویلا );

            إذا( x_Modifiable_Idle_ویلا > 0 )
            {
                __DSB();
                __WFI();
                __ISB();
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ویلا );

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
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
            {
                uint32_t ul_Calculated_لدو_قدر;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_لدو_قدر = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_قدر - پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_لدو_قدر <= ulStoppedTimerCompensation ) || ( ul_Calculated_لدو_قدر > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_لدو_قدر = ( ulTimerCountsForOneTick - 1UL );
                }

                پورٹ_NVIC_SYSTICK_لدو_REG = ul_Calculated_لدو_قدر;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ویلا - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_بایاں = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;
                #إذا ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG != پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_بایاں == 0 )
                    {
                        ul_Sys_Tick_Decrements_بایاں = ul_Reload_قدر;
                    }
                }
                #جے_انت /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ویلا * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_بایاں;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورٹ_NVIC_SYSTICK_لدو_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;
            پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            #إذا ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG == پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
            {
                پورٹ_NVIC_SYSTICK_لدو_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ;

                إذا( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0;
                }

                پورٹ_NVIC_SYSTICK_لدو_REG = ulTimerCountsForOneTick - 1UL;
                پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            }
            #جے_انت /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_قدم_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_interrupt();
        }
    }

#جے_انت /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
        x_ودھ_توں_ودھ_Possible_Suppressed_Ticks = پورٹ_MAX_24_ثنائی_ہندسہ_نمبر / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورٹ_MISSED_COUNTS_ضارب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #جے_انت /* configUSE_TICKLESS_IDLE */

    /* Stop and clear the SysTick. */
    پورٹ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٹ_NVIC_SYSTICK_لدو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ );
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ )
    {
        uint32_t ul_Current_رکاوٹ;
        uint8_t uc_Current_ترجیح;

        /* Obtain the number of the currently executing interrupt. */
        __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_رکاوٹ )::"memory" );

        /* Is the interrupt number a user defined interrupt? */
        إذا( ul_Current_رکاوٹ >= پورٹ_پہلا_USER_رکاوٹ_نمبر )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ترجیح = pc_رکاوٹ_ترجیح_Registers[ ul_Current_رکاوٹ ];

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
            configASSERT( uc_Current_ترجیح >= uc_Max_Sys_Call_ترجیح );
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
        configASSERT( ( پورٹ_AIRCR_REG & پورٹ_ترجیح_گروہ_نقاب ) <= ulMaxPRIGROUPValue );
    }

#جے_انت /* configASSERT_DEFINED */
