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
#अन्तर्भाव <limits.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#यदि ( config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः
#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#यदि ( config_ISR_राशिः_आकार < ( config_अल्पिष्ठम्_राशिः_आकार * 2 ) )
    #warning config_ISR_राशिः_आकार is probably too small!
#यदि_अन्तः /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#यदि ( ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता > पत्तनम्_MAX_प्राथमिकता ) || ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता < 2 ) )
    #दोषः config_MAX_API_CALL_व्यवधानम्_प्राथमिकता must be between 2 and 15
#यदि_अन्तः

#यदि ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 0 ) )
    #दोषः config_SUPPORT_DYNAMIC_आवण्टनम् must be समुच्चयः गन्तव्यम् 1 गन्तव्यम् use this पत्तनम् with an FPU
#यदि_अन्तः

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#परिभाषय पत्तनम्_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#परिभाषय पत्तनम्_NO_FLOATING_POINT_CONTEXT    ( ( राशिः_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#परिभाषय पत्तनम्_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#परिभाषय पत्तनम्_APIC_LVT_ERROR_सदिशम्        ( 0xfe )
#परिभाषय पत्तनम्_APIC_SPURIOUS_INT_सदिशम्     ( 0xff )

/* EFLAGS bits. */
#परिभाषय पत्तनम्_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#परिभाषय पत्तनम्_FPU_CONTEXT_आकार_अष्टकानि       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#परिभाषय पत्तनम्_EXPECTED_IDT_प्रविष्टिः_आकार      8

/* Default flags setting for entries in the IDT. */
#परिभाषय पत्तनम्_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#परिभाषय पत्तनम्_APIC_MIN_ALLOWABLE_सदिशम्    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#परिभाषय पत्तनम्_राशिः_WORD                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*
 * Complete one descriptor in the IDT.
 */
स्थिर शून्य prv_समुच्चयः_व्यवधानम्_Gate( uint8_t uc_सङ्ख्या,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
बाह्य शून्य v_पत्तनम्_Central_व्यवधानम्_Wrapper( शून्य );

/*
 * Handler for portYIELD().
 */
बाह्य शून्य v_पत्तनम्_Yield_Call( शून्य );

/*
 * Configure the APIC to generate the RTOS tick.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * Tick interrupt handler.
 */
बाह्य शून्य v_पत्तनम्_Timer_Handler( शून्य );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
स्थिर आधारः_Type_t prv_Check_Validity_सम्बन्धि_सदिशम्_सङ्ख्या( uint32_t ul_सदिशम्_सङ्ख्या );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable must be initialised to a non zero value to ensure interrupts don't
 * inadvertently become unmasked before the scheduler starts. It is set to zero
 * before the first task starts executing. */
चञ्चल uint32_t ulCriticalNesting = 9999UL;

/* A structure used to map the various fields of an IDT entry into separate
 * structure members. */
संरचना IDTEntry
{
    uint16_t usISRLow;          /* Low 16 bits of handler address. */
    uint16_t usSegmentSelector; /* Flat model means this is not changed. */
    uint8_t ucZero;             /* Must be set to zero. */
    uint8_t ucFlags;            /* Flags for this entry. */
    uint16_t usISRHigh;         /* High 16 bits of handler address. */
}
__attribute__( ( packed ) );
प्रकारनिर्देश संरचना IDTEntry IDTEntry_t;


/* Use to pass the location of the IDT to the CPU. */
संरचना IDTPointer
{
    uint16_t us_सारणी_सीमा;
    uint32_t ul_सारणी_आधारः; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
प्रकारनिर्देश संरचना IDTPointer IDTPointer_t;

/* The IDT itself. */
स्थिर __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_व्यवधानम्_Descriptor_सारणी[ पत्तनम्_अङ्कः_VECTORS ];

#यदि ( config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
स्थिर ISR_Handler_t x_व्यवधानम्_Handler_सारणी[ पत्तनम्_अङ्कः_VECTORS ] = { रिक्त };

#यदि_अन्तः /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#यदि ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_पत्तनम्_Task_FPUContext_बफर __attribute__( ( प्रयुक्तम् ) ) = pdFALSE;

#यदि_अन्तः /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
स्थिर uint32_t ul_System_राशिः[ config_ISR_राशिः_आकार ] __attribute__( ( प्रयुक्तम् ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
चञ्चल uint32_t ul_शिखरम्_सम्बन्धि_System_राशिः __attribute__( ( प्रयुक्तम् ) ) = ( uint32_t ) &( ul_System_राशिः[ config_ISR_राशिः_आकार - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
चञ्चल uint32_t ul_पत्तनम्_Yield_Pending __attribute__( ( प्रयुक्तम् ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
चञ्चल uint32_t ul_व्यवधानम्_Nesting __attribute__( ( प्रयुक्तम् ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    uint32_t ul_संहिता_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_शिखरम्_सम्बन्धि_राशिः = 0x00;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Parameters first. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) prvTaskExitError;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* iret used to start the task pops up to here. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EFLAGS;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* CS */
    __asm चञ्चल ( "movl %%cs, %0" : "=r" ( ul_संहिता_Segment ) );
    *px_शिखरम्_सम्बन्धि_राशिः = ul_संहिता_Segment;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* First instruction in the task. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_शिखरम्_सम्बन्धि_राशिः = 0xEA;
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = 0xEC;
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = 0xED1; /* EDX */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = 0xEB1; /* EBX */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Hole for ESP. */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = 0x00; /* EBP */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = 0xE5; /* ESI */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = 0xeeeeeeee; /* EDI */

    #यदि ( configSUPPORT_FPU == 1 )
    {
        px_शिखरम्_सम्बन्धि_राशिः--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_FLOATING_POINT_CONTEXT;
    }
    #यदि_अन्तः /* configSUPPORT_FPU */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_समुच्चयः_व्यवधानम्_Gate( uint8_t uc_सङ्ख्या,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_संहिता_Segment;
    uint32_t ul_आधारः = ( uint32_t ) pxHandlerFunction;

    x_व्यवधानम्_Descriptor_सारणी[ uc_सङ्ख्या ].usISRLow = ( uint16_t ) ( ul_आधारः & USHRT_MAX );
    x_व्यवधानम्_Descriptor_सारणी[ uc_सङ्ख्या ].usISRHigh = ( uint16_t ) ( ( ul_आधारः >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm चञ्चल ( "mov %%cs, %0" : "=r" ( us_संहिता_Segment ) );
    x_व्यवधानम्_Descriptor_सारणी[ uc_सङ्ख्या ].usSegmentSelector = us_संहिता_Segment;
    x_व्यवधानम्_Descriptor_सारणी[ uc_सङ्ख्या ].ucZero = 0;
    x_व्यवधानम्_Descriptor_सारणी[ uc_सङ्ख्या ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_सज्जता_IDT( शून्य )
{
    uint32_t ul_अङ्कः;
    IDTPointer_t xIDT;

    #यदि ( config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT == 1 )
    {
        प्रति( ul_अङ्कः = 0; ul_अङ्कः < पत्तनम्_अङ्कः_VECTORS; ul_अङ्कः++ )
        {
            /* If a handler has not already been installed on this vector. */
            यदि( ( x_व्यवधानम्_Descriptor_सारणी[ ul_अङ्कः ].usISRLow == 0x00 ) && ( x_व्यवधानम्_Descriptor_सारणी[ ul_अङ्कः ].usISRHigh == 0x00 ) )
            {
                prv_समुच्चयः_व्यवधानम्_Gate( ( uint8_t ) ul_अङ्कः, v_पत्तनम्_Central_व्यवधानम्_Wrapper, पत्तनम्_IDT_FLAGS );
            }
        }
    }
    #यदि_अन्तः /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_सारणी_आधारः = ( uint32_t ) x_व्यवधानम्_Descriptor_सारणी;
    xIDT.us_सारणी_सीमा = परिमाण( x_व्यवधानम्_Descriptor_सारणी ) - 1;

    /* Set IDT in CPU. */
    __asm चञ्चल ( "lidt %0" ::"m" ( xIDT ) );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    पत्तनम्_DISABLE_INTERRUPTS();

    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    बाह्य शून्य v_पत्तनम्_APICError_Handler_Wrapper( शून्य );
    बाह्य शून्य v_पत्तनम्_APICSpurious_Handler( शून्य );

    /* Initialise LAPIC to a well known state. */
    पत्तनम्_APIC_LDR = 0xFFFFFFFF;
    पत्तनम्_APIC_LDR = ( ( पत्तनम्_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    पत्तनम्_APIC_LVT_TIMER = पत्तनम्_APIC_DISABLE;
    पत्तनम्_APIC_LVT_PERF = पत्तनम्_APIC_NMI;
    पत्तनम्_APIC_LVT_LINT0 = पत्तनम्_APIC_DISABLE;
    पत्तनम्_APIC_LVT_LINT1 = पत्तनम्_APIC_DISABLE;
    पत्तनम्_APIC_TASK_प्राथमिकता = 0;

    /* Install APIC timer ISR vector. */
    prv_समुच्चयः_व्यवधानम्_Gate( ( uint8_t ) पत्तनम्_APIC_TIMER_INT_सदिशम्, v_पत्तनम्_Timer_Handler, पत्तनम्_IDT_FLAGS );

    /* Install API error handler. */
    prv_समुच्चयः_व्यवधानम्_Gate( ( uint8_t ) पत्तनम्_APIC_LVT_ERROR_सदिशम्, v_पत्तनम्_APICError_Handler_Wrapper, पत्तनम्_IDT_FLAGS );

    /* Install Yield handler. */
    prv_समुच्चयः_व्यवधानम्_Gate( ( uint8_t ) पत्तनम्_APIC_YIELD_INT_सदिशम्, v_पत्तनम्_Yield_Call, पत्तनम्_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_समुच्चयः_व्यवधानम्_Gate( ( uint8_t ) पत्तनम्_APIC_SPURIOUS_INT_सदिशम्, v_पत्तनम्_APICSpurious_Handler, पत्तनम्_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    पत्तनम्_APIC_SPURIOUS_INT = पत्तनम्_APIC_SPURIOUS_INT_सदिशम् | पत्तनम्_APIC_ENABLE_BIT;

    /* Set timer error vector. */
    पत्तनम्_APIC_LVT_ERROR = पत्तनम्_APIC_LVT_ERROR_सदिशम्;

    /* Set the interrupt frequency. */
    पत्तनम्_APIC_TMRDIV = पत्तनम्_APIC_DIV_16;
    पत्तनम्_APIC_TIMER_INITIAL_गणनम् = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_दरः_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    आधारः_Type_t xWord;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( परिमाण( संरचना IDTEntry ) == पत्तनम्_EXPECTED_IDT_प्रविष्टिः_आकार );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    प्रति( xWord = 0; xWord < config_ISR_राशिः_आकार - 20; xWord++ )
    {
        ul_System_राशिः[ xWord ] = पत्तनम्_राशिः_WORD;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_पत्तनम्_सज्जता_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Make sure the stack used by interrupts is aligned. */
    ul_शिखरम्_सम्बन्धि_System_राशिः &= ~पत्तनम्_BYTE_ALIGNMENT_आवरणम्;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    पत्तनम्_APIC_LVT_TIMER = पत्तनम्_APIC_TIMER_PERIODIC | पत्तनम्_APIC_TIMER_INT_सदिशम्;

    /* Sometimes needed. */
    पत्तनम्_APIC_TMRDIV = पत्तनम्_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_पत्तनम्_Start_First_Task();

    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    यदि( ulCriticalNesting == 0 )
    {
        #यदि ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता == पत्तनम्_MAX_प्राथमिकता )
        {
            __asm चञ्चल ( "cli" );
        }
        #अन्यथा
        {
            पत्तनम्_APIC_TASK_प्राथमिकता = पत्तनम्_MAX_API_CALL_प्राथमिकता;
            configASSERT( पत्तनम्_APIC_TASK_प्राथमिकता == पत्तनम्_MAX_API_CALL_प्राथमिकता );
        }
        #यदि_अन्तः
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    यदि( ulCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #यदि ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता == पत्तनम्_MAX_प्राथमिकता )
            {
                __asm चञ्चल ( "sti" );
            }
            #अन्यथा
            {
                पत्तनम्_APIC_TASK_प्राथमिकता = 0;
            }
            #यदि_अन्तः

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            यदि( ul_पत्तनम्_Yield_Pending != pdFALSE )
            {
                ul_पत्तनम्_Yield_Pending = pdFALSE;
                __asm चञ्चल ( पत्तनम्_YIELD_व्यवधानम् );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य )
{
    चञ्चल uint32_t ul_Original_आवरणम्;

    /* Set mask to max syscall priority. */
    #यदि ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता == पत्तनम्_MAX_प्राथमिकता )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm चञ्चल ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_आवरणम् )::"memory" );

        ul_Original_आवरणम् &= पत्तनम्_EFLAGS_IF;
    }
    #अन्यथा
    {
        /* Return original mask. */
        ul_Original_आवरणम् = पत्तनम्_APIC_TASK_प्राथमिकता;
        पत्तनम्_APIC_TASK_प्राथमिकता = पत्तनम्_MAX_API_CALL_प्राथमिकता;
        configASSERT( पत्तनम्_APIC_TASK_प्राथमिकता == पत्तनम्_MAX_API_CALL_प्राथमिकता );
    }
    #यदि_अन्तः /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    प्रत्यागम ul_Original_आवरणम्;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( uint32_t ul_New_आवरणम्_मानम् )
{
    #यदि ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता == पत्तनम्_MAX_प्राथमिकता )
    {
        यदि( ul_New_आवरणम्_मानम् != pdFALSE )
        {
            __asm चञ्चल ( "sti" );
        }
    }
    #अन्यथा
    {
        पत्तनम्_APIC_TASK_प्राथमिकता = ul_New_आवरणम्_मानम्;
        configASSERT( पत्तनम्_APIC_TASK_प्राथमिकता == ul_New_आवरणम्_मानम् );
    }
    #यदि_अन्तः /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#यदि ( configSUPPORT_FPU == 1 )

    शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_पत्तनम्_Task_FPUContext_बफर = ( uint8_t * ) pv_पत्तनम्_Malloc( पत्तनम्_FPU_CONTEXT_आकार_अष्टकानि );
        configASSERT( puc_पत्तनम्_Task_FPUContext_बफर );

        /* Initialise the floating point registers. */
        __asm चञ्चल ( "fninit" );
    }

#यदि_अन्तः /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_APICError_Handler( शून्य )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    चञ्चल uint32_t ul_Error_स्थितिः = 0;

    पत्तनम्_APIC_ERROR_स्थितिः = 0;
    ul_Error_स्थितिः = पत्तनम्_APIC_ERROR_स्थितिः;
    ( शून्य ) ul_Error_स्थितिः;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#यदि ( config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT == 1 )

    शून्य v_पत्तनम्_Central_व्यवधानम्_Handler( uint32_t ul_सदिशम् )
    {
        यदि( ul_सदिशम् < पत्तनम्_अङ्कः_VECTORS )
        {
            यदि( x_व्यवधानम्_Handler_सारणी[ ul_सदिशम् ] != रिक्त )
            {
                ( x_व्यवधानम्_Handler_सारणी[ ul_सदिशम् ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_राशिः[ 10 ] == पत्तनम्_राशिः_WORD );
        configASSERT( ul_System_राशिः[ 12 ] == पत्तनम्_राशिः_WORD );
        configASSERT( ul_System_राशिः[ 14 ] == पत्तनम्_राशिः_WORD );
    }

#यदि_अन्तः /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#यदि ( config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT == 1 )

    आधारः_Type_t x_पत्तनम्_पञ्जिकाकोशः_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_सदिशम्_सङ्ख्या )
    {
        आधारः_Type_t xReturn;

        xReturn = prv_Check_Validity_सम्बन्धि_सदिशम्_सङ्ख्या( ul_सदिशम्_सङ्ख्या );

        यदि( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_व्यवधानम्_Handler_सारणी[ ul_सदिशम्_सङ्ख्या ] = pxHandler;
        }

        प्रत्यागम xReturn;
    }

#यदि_अन्तः /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Install_व्यवधानम्_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_सदिशम्_सङ्ख्या )
{
    आधारः_Type_t xReturn;

    xReturn = prv_Check_Validity_सम्बन्धि_सदिशम्_सङ्ख्या( ul_सदिशम्_सङ्ख्या );

    यदि( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_समुच्चयः_व्यवधानम्_Gate( ( uint8_t ) ul_सदिशम्_सङ्ख्या, ( ISR_Handler_t ) pxHandler, पत्तनम्_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    प्रत्यागम xReturn;
}
/*-----------------------------------------------------------*/

स्थिर आधारः_Type_t prv_Check_Validity_सम्बन्धि_सदिशम्_सङ्ख्या( uint32_t ul_सदिशम्_सङ्ख्या )
{
    आधारः_Type_t xReturn;

    /* Check validity of vector number. */
    यदि( ul_सदिशम्_सङ्ख्या >= पत्तनम्_अङ्कः_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    अन्यथा यदि( ul_सदिशम्_सङ्ख्या < पत्तनम्_APIC_MIN_ALLOWABLE_सदिशम् )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    अन्यथा यदि( ul_सदिशम्_सङ्ख्या == पत्तनम्_APIC_TIMER_INT_सदिशम् )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    अन्यथा यदि( ul_सदिशम्_सङ्ख्या == पत्तनम्_APIC_YIELD_INT_सदिशम् )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    अन्यथा यदि( ul_सदिशम्_सङ्ख्या == पत्तनम्_APIC_LVT_ERROR_सदिशम् )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    अन्यथा यदि( ul_सदिशम्_सङ्ख्या == पत्तनम्_APIC_SPURIOUS_INT_सदिशम् )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#यदि ( config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT == 1 )
    अन्यथा यदि( x_व्यवधानम्_Handler_सारणी[ ul_सदिशम्_सङ्ख्या ] != रिक्त )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#यदि_अन्तः  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    अन्यथा
    {
        xReturn = pdPASS;
    }

    प्रत्यागम xReturn;
}
/*-----------------------------------------------------------*/

शून्य v_Generate_Yield_व्यवधानम्( शून्य )
{
    __asm चञ्चल ( पत्तनम्_YIELD_व्यवधानम् );
}
