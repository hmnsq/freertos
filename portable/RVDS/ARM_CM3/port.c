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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#ఒకవేళ config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత == 0
    #దోషం config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత must not be సమితి గమ్యం 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#అయితే_ముగింపు

/* Legacy macro for backward compatibility only.  This macro used to be used to
 * replace the function that configures the clock used to generate the tick
 * interrupt (prvSetupTimerInterrupt()), but now the function is declared weak so
 * the application writer can override it by simply defining a function of the
 * same name (vApplicationSetupTickInterrupt()). */
#నిర్వచితం_కాకపోతే configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #నిర్వచించు configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#అయితే_ముగింపు

/* Constants required to manipulate the core.  Registers first... */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CTRL_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e010 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e014 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG    ( *( ( అస్థిర uint32_t * ) 0xe000e018 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR3_REG                    ( *( ( అస్థిర uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు              ( 1UL << 2UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_INT_బిట్టు              ( 1UL << 1UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు           ( 1UL << 0UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు       ( 1UL << 16UL )
#నిర్వచించు పోర్టు_NVIC_PENDSVCLEAR_బిట్టు              ( 1UL << 27UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు         ( 1UL << 26UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు       ( 1UL << 25UL )

#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత            ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI                   ( ( ( uint32_t ) పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత ) << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI                  ( ( ( uint32_t ) పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#నిర్వచించు పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య       ( 16 )
#నిర్వచించు పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16       ( 0xE000E3F0 )
#నిర్వచించు పోర్టు_AIRCR_REG                         ( *( ( అస్థిర uint32_t * ) 0xE000ED0C ) )
#నిర్వచించు పోర్టు_MAX_8_బిట్టు_విలువ                   ( ( uint8_t ) 0xff )
#నిర్వచించు పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE                   ( ( uint8_t ) 0x80 )
#నిర్వచించు పోర్టు_MAX_PRIGROUP_బిట్లు                 ( ( uint8_t ) 7 )
#నిర్వచించు పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు               ( 0x07UL << 8UL )
#నిర్వచించు పోర్టు_PRIGROUP_జరుపు                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#నిర్వచించు పోర్టు_VECTACTIVE_ముసుగు                   ( 0xFFUL )

/* Constants required to set up the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#నిర్వచించు పోర్టు_MAX_24_బిట్టు_సంఖ్య                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#నిర్వచించు పోర్టు_MISSED_COUNTS_గుణకం              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#నిర్వచించు పోర్టు_ప్రారంభం_చిరునామా_ముసుగు                ( ( దొంతర_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#నిర్వచితం_కాకపోతే configSYSTICK_CLOCK_HZ
    #నిర్వచించు configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
#లేకపోతే
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( 0 )
#అయితే_ముగింపు

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Exception handlers.
 */
శూన్య x_పోర్టు_Pend_SVHandler( శూన్య );
శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య );
శూన్య v_పోర్టు_SVCHandler( శూన్య );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
స్థిర శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
స్థిర UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t ulTimerCountsForOneTick = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t x_గరిష్ఠ_Possible_Suppressed_Ticks = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t ulStoppedTimerCompensation = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ఒకవేళ ( configASSERT_DEFINED == 1 )
    స్థిర uint8_t uc_Max_Sys_Call_ప్రాధాన్యత = 0;
    స్థిర uint32_t ulMaxPRIGROUPValue = 0;
    స్థిర స్థిరరాశి అస్థిర uint8_t * స్థిరరాశి pc_అంతరాయం_ప్రాధాన్యత_Registers = ( uint8_t * ) పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16;
#అయితే_ముగింపు /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_శిఖరం_యొక్క_దొంతర--;                                                      /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR;                                    /* xPSR */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( ( దొంతర_Type_t ) px_సంకేతం ) & పోర్టు_ప్రారంభం_చిరునామా_ముసుగు; /* PC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) prvTaskExitError;                    /* LR */

    px_శిఖరం_యొక్క_దొంతర -= 5;                                                   /* R12, R3, R2 and R1. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;                        /* R0 */
    px_శిఖరం_యొక్క_దొంతర -= 8;                                                   /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

__asm శూన్య v_పోర్టు_SVCHandler( శూన్య )
{
/* *INDENT-OFF* */
    PRESERVE8

    ldr r3, = pxCurrentTCB   /* Restore the context. */
    ldr r1, [ r3 ] /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
    ldr r0, [ r1 ]           /* The first item in pxCurrentTCB is the task top of stack. */
    ldmia r0 !, { r4 - r11 } /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
    msr psp, r0 /* Restore the task stack pointer. */
    isb
    mov r0, # 0
    msr basepri, r0
    orr r14, # 0xd
    bx r14
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm శూన్య prv_ప్రారంభం_మొదటి_Task( శూన్య )
{
/* *INDENT-OFF* */
    PRESERVE8

    /* Use the NVIC offset register to locate the stack. */
    ldr r0, =0xE000ED08
    ldr r0, [ r0 ]
    ldr r0, [ r0 ]

    /* Set the msp back to the start of the stack. */
    msr msp, r0
    /* Globally enable interrupts. */
    cpsie i
    cpsie f
    dsb
    isb
    /* Call SVC to start the first task. */
    svc 0
    nop
    nop
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        అస్థిర uint8_t uc_Original_ప్రాధాన్యత;
        అస్థిర uint32_t ul_Implemented_Prio_బిట్లు = 0;
        అస్థిర uint8_t * స్థిరరాశి puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = ( uint8_t * ) ( పోర్టు_NVIC_IP_REGISTERS_స్థానభ్రంశం_16 + పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య );
        అస్థిర uint8_t uc_Max_ప్రాధాన్యత_విలువ;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ప్రాధాన్యత = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = పోర్టు_MAX_8_బిట్టు_విలువ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ప్రాధాన్యత_విలువ = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_ప్రాధాన్యత = config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & uc_Max_ప్రాధాన్యత_విలువ;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_ప్రాధాన్యత );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & ( ~uc_Max_ప్రాధాన్యత_విలువ ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        అయితే( ( uc_Max_ప్రాధాన్యత_విలువ & పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE ) == పోర్టు_శిఖరం_బిట్టు_యొక్క_BYTE )
        {
            ul_Implemented_Prio_బిట్లు++;
            uc_Max_ప్రాధాన్యత_విలువ <<= ( uint8_t ) 0x01;
        }

        ఒకవేళ( ul_Implemented_Prio_బిట్లు == 8 )
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
            configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        లేకపోతే
        {
            ulMaxPRIGROUPValue = పోర్టు_MAX_PRIGROUP_బిట్లు - ul_Implemented_Prio_బిట్లు;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= పోర్టు_PRIGROUP_జరుపు;
        ulMaxPRIGROUPValue &= పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = uc_Original_ప్రాధాన్యత;
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;

    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_పోర్టు_అమరిక_Timer_అంతరాయం();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prv_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ఒకవేళ( uxCriticalNesting == 1 )
    {
        configASSERT( ( పోర్టు_NVIC_INT_CTRL_REG & పోర్టు_VECTACTIVE_ముసుగు ) == 0 );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    ఒకవేళ( uxCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

__asm శూన్య x_పోర్టు_Pend_SVHandler( శూన్య )
{
    బాహ్య uxCriticalNesting;
    బాహ్య pxCurrentTCB;
    బాహ్య vTaskSwitchContext;

/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, psp
    isb

    ldr r3, =pxCurrentTCB /* Get the location of the current TCB. */
    ldr r2, [ r3 ]

    stmdb r0 !, { r4 - r11 } /* Save the remaining registers. */
    str r0, [ r2 ] /* Save the new top of stack into the first member of the TCB. */

    stmdb sp !, { r3, r14 }
    mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
    msr basepri, r0
    dsb
    isb
    bl vTaskSwitchContext
    mov r0, #0
    msr basepri, r0
    ldmia sp !, { r3, r14 }

    ldr r1, [ r3 ]
    ldr r0, [ r1 ] /* The first item in pxCurrentTCB is the task top of stack. */
    ldmia r0 !, { r4 - r11 } /* Pop the registers and the critical nesting count. */
    msr psp, r0
    isb
    bx r14
    nop
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known - therefore the slightly faster vPortRaiseBASEPRI() function is used
     * in place of portSET_INTERRUPT_MASK_FROM_ISR(). */
    v_పోర్టు_Raise_BASEPRI();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_గమ్యం_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }

    v_పోర్టు_Clear_BASEPRIFrom_ISR();
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    __weak శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
    {
        uint32_t ul_Reload_విలువ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ఎడమ;
        TickType_t x_Modifiable_Idle_సమయం;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ఒకవేళ( x_Expected_Idle_సమయం > x_గరిష్ఠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_సమయం = x_గరిష్ఠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_irq();
        __dsb( పోర్టు_SY_నిండిన_READ_WRITE );
        __isb( పోర్టు_SY_నిండిన_READ_WRITE );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ఒకవేళ( e_Task_Confirm_Sleep_బహుళకం_స్థితి() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_irq()
             * call above. */
            __enable_irq();
        }
        లేకపోతే
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ఎడమ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;

            ఒకవేళ( ul_Sys_Tick_Decrements_ఎడమ == 0 )
            {
                ul_Sys_Tick_Decrements_ఎడమ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_విలువ = ul_Sys_Tick_Decrements_ఎడమ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_సమయం - 1UL ) );

            ఒకవేళ( ( పోర్టు_NVIC_INT_CTRL_REG & పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు ) != 0 )
            {
                పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు;
                ul_Reload_విలువ -= ulTimerCountsForOneTick;
            }

            ఒకవేళ( ul_Reload_విలువ > ulStoppedTimerCompensation )
            {
                ul_Reload_విలువ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ul_Reload_విలువ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

            /* Restart SysTick. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG |= పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_సమయం = x_Expected_Idle_సమయం;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_సమయం );

            ఒకవేళ( x_Modifiable_Idle_సమయం > 0 )
            {
                __dsb( పోర్టు_SY_నిండిన_READ_WRITE );
                __wfi();
                __isb( పోర్టు_SY_నిండిన_READ_WRITE );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_irq() call above. */
            __enable_irq();
            __dsb( పోర్టు_SY_నిండిన_READ_WRITE );
            __isb( పోర్టు_SY_నిండిన_READ_WRITE );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_irq();
            __dsb( పోర్టు_SY_నిండిన_READ_WRITE );
            __isb( పోర్టు_SY_నిండిన_READ_WRITE );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Determine whether the SysTick has already counted to zero. */
            ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
            {
                uint32_t ul_Calculated_ఎక్కించు_విలువ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_విలువ - పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ఒకవేళ( ( ul_Calculated_ఎక్కించు_విలువ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ఎక్కించు_విలువ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL );
                }

                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ul_Calculated_ఎక్కించు_విలువ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_సమయం - 1UL;
            }
            లేకపోతే
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ఎడమ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;
                #ఒకవేళ ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG != పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ఒకవేళ( ul_Sys_Tick_Decrements_ఎడమ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ఎడమ = ul_Reload_విలువ;
                    }
                }
                #అయితే_ముగింపు /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_సమయం * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ఎడమ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;
            పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            #ఒకవేళ ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG == పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
            {
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;
            }
            #లేకపోతే
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు;

                ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0;
                }

                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;
                పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            }
            #అయితే_ముగింపు /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_అడుగు_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_irq();
        }
    }

#అయితే_ముగింపు /* #if configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

/*
 * Setup the SysTick timer to generate the tick interrupts at the required
 * frequency.
 */
#ఒకవేళ ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    __weak శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ );
            x_గరిష్ఠ_Possible_Suppressed_Ticks = పోర్టు_MAX_24_బిట్టు_సంఖ్య / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = పోర్టు_MISSED_COUNTS_గుణకం / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

        /* Stop and clear the SysTick. */
        పోర్టు_NVIC_SYSTICK_CTRL_REG = 0UL;
        పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL;
        పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు );
    }

#అయితే_ముగింపు /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

__asm uint32_t v_పోర్టు_Get_IPSR( శూన్య )
{
/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, ipsr
    bx r14
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configASSERT_DEFINED == 1 )

    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య )
    {
        uint32_t ul_Current_అంతరాయం;
        uint8_t uc_Current_ప్రాధాన్యత;

        /* Obtain the number of the currently executing interrupt. */
        ul_Current_అంతరాయం = v_పోర్టు_Get_IPSR();

        /* Is the interrupt number a user defined interrupt? */
        ఒకవేళ( ul_Current_అంతరాయం >= పోర్టు_మొదటి_USER_అంతరాయం_సంఖ్య )
        {
            /* Look up the interrupt's priority. */
            uc_Current_ప్రాధాన్యత = pc_అంతరాయం_ప్రాధాన్యత_Registers[ ul_Current_అంతరాయం ];

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
            configASSERT( uc_Current_ప్రాధాన్యత >= uc_Max_Sys_Call_ప్రాధాన్యత );
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
        configASSERT( ( పోర్టు_AIRCR_REG & పోర్టు_ప్రాధాన్యత_సమూహం_ముసుగు ) <= ulMaxPRIGROUPValue );
    }

#అయితే_ముగింపు /* configASSERT_DEFINED */
