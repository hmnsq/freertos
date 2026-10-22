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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Constants required to manipulate the NVIC. */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CTRL       ( ( అస్థిర uint32_t * ) 0xe000e010 )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ఎక్కించు       ( ( అస్థిర uint32_t * ) 0xe000e014 )
#నిర్వచించు పోర్టు_NVIC_SHPR3_REG          ( ( అస్థిర uint32_t * ) 0xe000ed20 )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK        0x00000004
#నిర్వచించు పోర్టు_NVIC_SYSTICK_INT        0x00000002
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ENABLE     0x00000001
#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత  ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI         ( ( ( uint32_t ) పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత ) << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#నిర్వచించు పోర్టు_VECTACTIVE_ముసుగు         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#నిర్వచించు పోర్టు_FPCCR                   ( ( అస్థిర uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#నిర్వచించు పోర్టు_ASPEN_AND_LSPEN_బిట్లు    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_XPSR            ( 0x01000000 )
#నిర్వచించు పోర్టు_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#నిర్వచించు పోర్టు_ప్రారంభం_చిరునామా_ముసుగు    ( ( దొంతర_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
స్థిరరాశి uint32_t ul_Kernel_ప్రాధాన్యత = పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
స్థిర uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Exception handlers.
 */
శూన్య SysTick_Handler( శూన్య );

/*
 * Functions defined in port_asm.asm.
 */
బాహ్య శూన్య v_పోర్టు_Enable_VFP( శూన్య );
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
స్థిరరాశి uint32_t ul_Max_Syscall_అంతరాయం_ప్రాధాన్యత_Const = config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత;

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

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR;                                    /* xPSR */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( ( దొంతర_Type_t ) px_సంకేతం ) & పోర్టు_ప్రారంభం_చిరునామా_ముసుగు; /* PC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_శిఖరం_యొక్క_దొంతర -= 5;                            /* R12, R3, R2 and R1. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_EXC_RETURN;

    px_శిఖరం_యొక్క_దొంతర -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

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
    configASSERT( ulCriticalNesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( పోర్టు_NVIC_SHPR3_REG ) |= పోర్టు_NVIC_PENDSV_PRI;
    *( పోర్టు_NVIC_SHPR3_REG ) |= పోర్టు_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_పోర్టు_Enable_VFP();

    /* Lazy save always. */
    *( పోర్టు_FPCCR ) |= పోర్టు_ASPEN_AND_LSPEN_బిట్లు;

    /* Start the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య )
{
    /* Set a PendSV to request a context switch. */
    *( పోర్టు_NVIC_INT_CTRL ) = పోర్టు_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ఒకవేళ( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( పోర్టు_NVIC_INT_CTRL ) ) & పోర్టు_VECTACTIVE_ముసుగు ) == 0 );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ఒకవేళ( ulCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

శూన్య SysTick_Handler( శూన్య )
{
    uint32_t ulDummy;

    ulDummy = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    traceISR_ENTER();
    {
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_గమ్యం_SCHEDULER();
            /* Pend a context switch. */
            *( పోర్టు_NVIC_INT_CTRL ) = పోర్టు_NVIC_PENDSVSET;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( పోర్టు_NVIC_SYSTICK_ఎక్కించు ) = ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL;
    *( పోర్టు_NVIC_SYSTICK_CTRL ) = పోర్టు_NVIC_SYSTICK_CLK | పోర్టు_NVIC_SYSTICK_INT | పోర్టు_NVIC_SYSTICK_ENABLE;
}