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

/* Standard includes. */
#అన్తర్భావ <limits.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#ఒకవేళ ( config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 difference priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
    #అయితే_ముగింపు
#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ఒకవేళ ( config_ISR_దొంతర_కొలత < ( config_కనీస_దొంతర_కొలత * 2 ) )
    #warning config_ISR_దొంతర_కొలత is probably too small!
#అయితే_ముగింపు /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#ఒకవేళ ( ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత > పోర్టు_MAX_ప్రాధాన్యత ) || ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత < 2 ) )
    #దోషం config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత must be between 2 and 15
#అయితే_ముగింపు

#ఒకవేళ ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 0 ) )
    #దోషం config_SUPPORT_DYNAMIC_కేటాయింపు must be సమితి గమ్యం 1 గమ్యం use this పోర్టు with an FPU
#అయితే_ముగింపు

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#నిర్వచించు పోర్టు_NO_FLOATING_బిందువు_CONTEXT    ( ( దొంతర_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#నిర్వచించు పోర్టు_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#నిర్వచించు పోర్టు_APIC_LVT_ERROR_సదిశ        ( 0xfe )
#నిర్వచించు పోర్టు_APIC_SPURIOUS_INT_సదిశ     ( 0xff )

/* EFLAGS bits. */
#నిర్వచించు పోర్టు_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#నిర్వచించు పోర్టు_FPU_CONTEXT_కొలత_బైట్లు       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#నిర్వచించు పోర్టు_EXPECTED_IDT_నమోదు_కొలత      8

/* Default flags setting for entries in the IDT. */
#నిర్వచించు పోర్టు_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#నిర్వచించు పోర్టు_APIC_MIN_ALLOWABLE_సదిశ    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#నిర్వచించు పోర్టు_దొంతర_మాట                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*
 * Complete one descriptor in the IDT.
 */
స్థిర శూన్య prv_సమితి_అంతరాయం_Gate( uint8_t uc_సంఖ్య,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
బాహ్య శూన్య v_పోర్టు_Central_అంతరాయం_Wrapper( శూన్య );

/*
 * Handler for portYIELD().
 */
బాహ్య శూన్య v_పోర్టు_Yield_Call( శూన్య );

/*
 * Configure the APIC to generate the RTOS tick.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Tick interrupt handler.
 */
బాహ్య శూన్య v_పోర్టు_Timer_Handler( శూన్య );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
స్థిర పునాది_Type_t prv_Check_Validity_యొక్క_సదిశ_సంఖ్య( uint32_t ul_సదిశ_సంఖ్య );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable must be initialised to a non zero value to ensure interrupts don't
 * inadvertently become unmasked before the scheduler starts. It is set to zero
 * before the first task starts executing. */
అస్థిర uint32_t ulCriticalNesting = 9999UL;

/* A structure used to map the various fields of an IDT entry into separate
 * structure members. */
నిర్మాణం IDTEntry
{
    uint16_t usISRLow;          /* Low 16 bits of handler address. */
    uint16_t usSegmentSelector; /* Flat model means this is not changed. */
    uint8_t ucZero;             /* Must be set to zero. */
    uint8_t ucFlags;            /* Flags for this entry. */
    uint16_t usISRHigh;         /* High 16 bits of handler address. */
}
__attribute__( ( packed ) );
రకనిర్వచనం నిర్మాణం IDTEntry IDTEntry_t;


/* Use to pass the location of the IDT to the CPU. */
నిర్మాణం IDTPointer
{
    uint16_t us_పట్టిక_హద్దు;
    uint32_t ul_పట్టిక_పునాది; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
రకనిర్వచనం నిర్మాణం IDTPointer IDTPointer_t;

/* The IDT itself. */
స్థిర __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_అంతరాయం_Descriptor_పట్టిక[ పోర్టు_అంకె_VECTORS ];

#ఒకవేళ ( config_USE_COMMON_అంతరాయం_నమోదు_బిందువు == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
స్థిర ISR_Handler_t x_అంతరాయం_Handler_పట్టిక[ పోర్టు_అంకె_VECTORS ] = { ఖాళీ };

#అయితే_ముగింపు /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#ఒకవేళ ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_పోర్టు_Task_FPUContext_బఫరు __attribute__( ( వాడిన ) ) = pdFALSE;

#అయితే_ముగింపు /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
స్థిర uint32_t ul_System_దొంతర[ config_ISR_దొంతర_కొలత ] __attribute__( ( వాడిన ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
అస్థిర uint32_t ul_శిఖరం_యొక్క_System_దొంతర __attribute__( ( వాడిన ) ) = ( uint32_t ) &( ul_System_దొంతర[ config_ISR_దొంతర_కొలత - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
అస్థిర uint32_t ul_పోర్టు_Yield_Pending __attribute__( ( వాడిన ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
అస్థిర uint32_t ul_అంతరాయం_Nesting __attribute__( ( వాడిన ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    uint32_t ul_సంకేతం_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Parameters first. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
    px_శిఖరం_యొక్క_దొంతర--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) prvTaskExitError;
    px_శిఖరం_యొక్క_దొంతర--;

    /* iret used to start the task pops up to here. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_EFLAGS;
    px_శిఖరం_యొక్క_దొంతర--;

    /* CS */
    __asm అస్థిర ( "movl %%cs, %0" : "=r" ( ul_సంకేతం_Segment ) );
    *px_శిఖరం_యొక్క_దొంతర = ul_సంకేతం_Segment;
    px_శిఖరం_యొక్క_దొంతర--;

    /* First instruction in the task. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_శిఖరం_యొక్క_దొంతర = 0xEA;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = 0xEC;
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = 0xED1; /* EDX */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = 0xEB1; /* EBX */
    px_శిఖరం_యొక్క_దొంతర--;

    /* Hole for ESP. */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = 0x00; /* EBP */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = 0xE5; /* ESI */
    px_శిఖరం_యొక్క_దొంతర--;

    *px_శిఖరం_యొక్క_దొంతర = 0xeeeeeeee; /* EDI */

    #ఒకవేళ ( configSUPPORT_FPU == 1 )
    {
        px_శిఖరం_యొక్క_దొంతర--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_FLOATING_బిందువు_CONTEXT;
    }
    #అయితే_ముగింపు /* configSUPPORT_FPU */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_సమితి_అంతరాయం_Gate( uint8_t uc_సంఖ్య,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_సంకేతం_Segment;
    uint32_t ul_పునాది = ( uint32_t ) pxHandlerFunction;

    x_అంతరాయం_Descriptor_పట్టిక[ uc_సంఖ్య ].usISRLow = ( uint16_t ) ( ul_పునాది & USHRT_MAX );
    x_అంతరాయం_Descriptor_పట్టిక[ uc_సంఖ్య ].usISRHigh = ( uint16_t ) ( ( ul_పునాది >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm అస్థిర ( "mov %%cs, %0" : "=r" ( us_సంకేతం_Segment ) );
    x_అంతరాయం_Descriptor_పట్టిక[ uc_సంఖ్య ].usSegmentSelector = us_సంకేతం_Segment;
    x_అంతరాయం_Descriptor_పట్టిక[ uc_సంఖ్య ].ucZero = 0;
    x_అంతరాయం_Descriptor_పట్టిక[ uc_సంఖ్య ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_అమరిక_IDT( శూన్య )
{
    uint32_t ul_అంకె;
    IDTPointer_t xIDT;

    #ఒకవేళ ( config_USE_COMMON_అంతరాయం_నమోదు_బిందువు == 1 )
    {
        కొరకు( ul_అంకె = 0; ul_అంకె < పోర్టు_అంకె_VECTORS; ul_అంకె++ )
        {
            /* If a handler has not already been installed on this vector. */
            ఒకవేళ( ( x_అంతరాయం_Descriptor_పట్టిక[ ul_అంకె ].usISRLow == 0x00 ) && ( x_అంతరాయం_Descriptor_పట్టిక[ ul_అంకె ].usISRHigh == 0x00 ) )
            {
                prv_సమితి_అంతరాయం_Gate( ( uint8_t ) ul_అంకె, v_పోర్టు_Central_అంతరాయం_Wrapper, పోర్టు_IDT_FLAGS );
            }
        }
    }
    #అయితే_ముగింపు /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_పట్టిక_పునాది = ( uint32_t ) x_అంతరాయం_Descriptor_పట్టిక;
    xIDT.us_పట్టిక_హద్దు = పరిమాణం( x_అంతరాయం_Descriptor_పట్టిక ) - 1;

    /* Set IDT in CPU. */
    __asm అస్థిర ( "lidt %0" ::"m" ( xIDT ) );
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

స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    బాహ్య శూన్య v_పోర్టు_APICError_Handler_Wrapper( శూన్య );
    బాహ్య శూన్య v_పోర్టు_APICSpurious_Handler( శూన్య );

    /* Initialise LAPIC to a well known state. */
    పోర్టు_APIC_LDR = 0xFFFFFFFF;
    పోర్టు_APIC_LDR = ( ( పోర్టు_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    పోర్టు_APIC_LVT_TIMER = పోర్టు_APIC_DISABLE;
    పోర్టు_APIC_LVT_PERF = పోర్టు_APIC_NMI;
    పోర్టు_APIC_LVT_LINT0 = పోర్టు_APIC_DISABLE;
    పోర్టు_APIC_LVT_LINT1 = పోర్టు_APIC_DISABLE;
    పోర్టు_APIC_TASK_ప్రాధాన్యత = 0;

    /* Install APIC timer ISR vector. */
    prv_సమితి_అంతరాయం_Gate( ( uint8_t ) పోర్టు_APIC_TIMER_INT_సదిశ, v_పోర్టు_Timer_Handler, పోర్టు_IDT_FLAGS );

    /* Install API error handler. */
    prv_సమితి_అంతరాయం_Gate( ( uint8_t ) పోర్టు_APIC_LVT_ERROR_సదిశ, v_పోర్టు_APICError_Handler_Wrapper, పోర్టు_IDT_FLAGS );

    /* Install Yield handler. */
    prv_సమితి_అంతరాయం_Gate( ( uint8_t ) పోర్టు_APIC_YIELD_INT_సదిశ, v_పోర్టు_Yield_Call, పోర్టు_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_సమితి_అంతరాయం_Gate( ( uint8_t ) పోర్టు_APIC_SPURIOUS_INT_సదిశ, v_పోర్టు_APICSpurious_Handler, పోర్టు_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    పోర్టు_APIC_SPURIOUS_INT = పోర్టు_APIC_SPURIOUS_INT_సదిశ | పోర్టు_APIC_ENABLE_బిట్టు;

    /* Set timer error vector. */
    పోర్టు_APIC_LVT_ERROR = పోర్టు_APIC_LVT_ERROR_సదిశ;

    /* Set the interrupt frequency. */
    పోర్టు_APIC_TMRDIV = పోర్టు_APIC_DIV_16;
    పోర్టు_APIC_TIMER_INITIAL_లెక్క = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_రేటు_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    పునాది_Type_t x_మాట;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( పరిమాణం( నిర్మాణం IDTEntry ) == పోర్టు_EXPECTED_IDT_నమోదు_కొలత );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    కొరకు( x_మాట = 0; x_మాట < config_ISR_దొంతర_కొలత - 20; x_మాట++ )
    {
        ul_System_దొంతర[ x_మాట ] = పోర్టు_దొంతర_మాట;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_పోర్టు_అమరిక_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Make sure the stack used by interrupts is aligned. */
    ul_శిఖరం_యొక్క_System_దొంతర &= ~పోర్టు_BYTE_ALIGNMENT_ముసుగు;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    పోర్టు_APIC_LVT_TIMER = పోర్టు_APIC_TIMER_PERIODIC | పోర్టు_APIC_TIMER_INT_సదిశ;

    /* Sometimes needed. */
    పోర్టు_APIC_TMRDIV = పోర్టు_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

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

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting == 0 )
    {
        #ఒకవేళ ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == పోర్టు_MAX_ప్రాధాన్యత )
        {
            __asm అస్థిర ( "cli" );
        }
        #లేకపోతే
        {
            పోర్టు_APIC_TASK_ప్రాధాన్యత = పోర్టు_MAX_API_CALL_ప్రాధాన్యత;
            configASSERT( పోర్టు_APIC_TASK_ప్రాధాన్యత == పోర్టు_MAX_API_CALL_ప్రాధాన్యత );
        }
        #అయితే_ముగింపు
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #ఒకవేళ ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == పోర్టు_MAX_ప్రాధాన్యత )
            {
                __asm అస్థిర ( "sti" );
            }
            #లేకపోతే
            {
                పోర్టు_APIC_TASK_ప్రాధాన్యత = 0;
            }
            #అయితే_ముగింపు

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            ఒకవేళ( ul_పోర్టు_Yield_Pending != pdFALSE )
            {
                ul_పోర్టు_Yield_Pending = pdFALSE;
                __asm అస్థిర ( పోర్టు_YIELD_అంతరాయం );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య )
{
    అస్థిర uint32_t ul_Original_ముసుగు;

    /* Set mask to max syscall priority. */
    #ఒకవేళ ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == పోర్టు_MAX_ప్రాధాన్యత )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm అస్థిర ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_ముసుగు )::"memory" );

        ul_Original_ముసుగు &= పోర్టు_EFLAGS_IF;
    }
    #లేకపోతే
    {
        /* Return original mask. */
        ul_Original_ముసుగు = పోర్టు_APIC_TASK_ప్రాధాన్యత;
        పోర్టు_APIC_TASK_ప్రాధాన్యత = పోర్టు_MAX_API_CALL_ప్రాధాన్యత;
        configASSERT( పోర్టు_APIC_TASK_ప్రాధాన్యత == పోర్టు_MAX_API_CALL_ప్రాధాన్యత );
    }
    #అయితే_ముగింపు /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    తిరిగి ul_Original_ముసుగు;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( uint32_t ul_New_ముసుగు_విలువ )
{
    #ఒకవేళ ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == పోర్టు_MAX_ప్రాధాన్యత )
    {
        ఒకవేళ( ul_New_ముసుగు_విలువ != pdFALSE )
        {
            __asm అస్థిర ( "sti" );
        }
    }
    #లేకపోతే
    {
        పోర్టు_APIC_TASK_ప్రాధాన్యత = ul_New_ముసుగు_విలువ;
        configASSERT( పోర్టు_APIC_TASK_ప్రాధాన్యత == ul_New_ముసుగు_విలువ );
    }
    #అయితే_ముగింపు /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configSUPPORT_FPU == 1 )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_పోర్టు_Task_FPUContext_బఫరు = ( uint8_t * ) pv_పోర్టు_Malloc( పోర్టు_FPU_CONTEXT_కొలత_బైట్లు );
        configASSERT( puc_పోర్టు_Task_FPUContext_బఫరు );

        /* Initialise the floating point registers. */
        __asm అస్థిర ( "fninit" );
    }

#అయితే_ముగింపు /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_APICError_Handler( శూన్య )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    అస్థిర uint32_t ul_Error_స్థితి = 0;

    పోర్టు_APIC_ERROR_స్థితి = 0;
    ul_Error_స్థితి = పోర్టు_APIC_ERROR_స్థితి;
    ( శూన్య ) ul_Error_స్థితి;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_COMMON_అంతరాయం_నమోదు_బిందువు == 1 )

    శూన్య v_పోర్టు_Central_అంతరాయం_Handler( uint32_t ul_సదిశ )
    {
        ఒకవేళ( ul_సదిశ < పోర్టు_అంకె_VECTORS )
        {
            ఒకవేళ( x_అంతరాయం_Handler_పట్టిక[ ul_సదిశ ] != ఖాళీ )
            {
                ( x_అంతరాయం_Handler_పట్టిక[ ul_సదిశ ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_దొంతర[ 10 ] == పోర్టు_దొంతర_మాట );
        configASSERT( ul_System_దొంతర[ 12 ] == పోర్టు_దొంతర_మాట );
        configASSERT( ul_System_దొంతర[ 14 ] == పోర్టు_దొంతర_మాట );
    }

#అయితే_ముగింపు /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_COMMON_అంతరాయం_నమోదు_బిందువు == 1 )

    పునాది_Type_t x_పోర్టు_రిజిస్టరు_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_సదిశ_సంఖ్య )
    {
        పునాది_Type_t xReturn;

        xReturn = prv_Check_Validity_యొక్క_సదిశ_సంఖ్య( ul_సదిశ_సంఖ్య );

        ఒకవేళ( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_అంతరాయం_Handler_పట్టిక[ ul_సదిశ_సంఖ్య ] = pxHandler;
        }

        తిరిగి xReturn;
    }

#అయితే_ముగింపు /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_Install_అంతరాయం_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_సదిశ_సంఖ్య )
{
    పునాది_Type_t xReturn;

    xReturn = prv_Check_Validity_యొక్క_సదిశ_సంఖ్య( ul_సదిశ_సంఖ్య );

    ఒకవేళ( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_సమితి_అంతరాయం_Gate( ( uint8_t ) ul_సదిశ_సంఖ్య, ( ISR_Handler_t ) pxHandler, పోర్టు_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    తిరిగి xReturn;
}
/*-----------------------------------------------------------*/

స్థిర పునాది_Type_t prv_Check_Validity_యొక్క_సదిశ_సంఖ్య( uint32_t ul_సదిశ_సంఖ్య )
{
    పునాది_Type_t xReturn;

    /* Check validity of vector number. */
    ఒకవేళ( ul_సదిశ_సంఖ్య >= పోర్టు_అంకె_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    లేకపోతే ఒకవేళ( ul_సదిశ_సంఖ్య < పోర్టు_APIC_MIN_ALLOWABLE_సదిశ )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    లేకపోతే ఒకవేళ( ul_సదిశ_సంఖ్య == పోర్టు_APIC_TIMER_INT_సదిశ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    లేకపోతే ఒకవేళ( ul_సదిశ_సంఖ్య == పోర్టు_APIC_YIELD_INT_సదిశ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    లేకపోతే ఒకవేళ( ul_సదిశ_సంఖ్య == పోర్టు_APIC_LVT_ERROR_సదిశ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    లేకపోతే ఒకవేళ( ul_సదిశ_సంఖ్య == పోర్టు_APIC_SPURIOUS_INT_సదిశ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#ఒకవేళ ( config_USE_COMMON_అంతరాయం_నమోదు_బిందువు == 1 )
    లేకపోతే ఒకవేళ( x_అంతరాయం_Handler_పట్టిక[ ul_సదిశ_సంఖ్య ] != ఖాళీ )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#అయితే_ముగింపు  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    లేకపోతే
    {
        xReturn = pdPASS;
    }

    తిరిగి xReturn;
}
/*-----------------------------------------------------------*/

శూన్య v_Generate_Yield_అంతరాయం( శూన్య )
{
    __asm అస్థిర ( పోర్టు_YIELD_అంతరాయం );
}
