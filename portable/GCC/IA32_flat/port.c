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
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਜੇ ( config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 difference priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ਜੇ ( config_ISR_ਢੇਰ_ਮਾਪ < ( config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ * 2 ) )
    #warning config_ISR_ਢੇਰ_ਮਾਪ is probably too small!
#ਜੇ_ਅੰਤ /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#ਜੇ ( ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ > ਪੋਰਟ_MAX_ਤਰਜੀਹ ) || ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ < 2 ) )
    #ਗਲਤੀ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must be between 2 and 15
#ਜੇ_ਅੰਤ

#ਜੇ ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 0 ) )
    #ਗਲਤੀ config_SUPPORT_DYNAMIC_ਵੰਡ must be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 ਮੰਜ਼ਿਲ use this ਪੋਰਟ with an FPU
#ਜੇ_ਅੰਤ

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT    ( ( ਢੇਰ_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LVT_ERROR_ਸਦਿਸ਼        ( 0xfe )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_SPURIOUS_INT_ਸਦਿਸ਼     ( 0xff )

/* EFLAGS bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_CONTEXT_ਮਾਪ_ਬਾਈਟਾਂ       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXPECTED_IDT_ਇੰਦਰਾਜ_ਮਾਪ      8

/* Default flags setting for entries in the IDT. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_MIN_ALLOWABLE_ਸਦਿਸ਼    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਸ਼ਬਦ                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*
 * Complete one descriptor in the IDT.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( uint8_t uc_ਸੰਖਿਆ,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Central_ਰੁਕਾਵਟ_Wrapper( ਖਾਲੀ );

/*
 * Handler for portYIELD().
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield_Call( ਖਾਲੀ );

/*
 * Configure the APIC to generate the RTOS tick.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Tick interrupt handler.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Timer_Handler( ਖਾਲੀ );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
ਸਥਿਰ ਅਧਾਰ_Type_t prv_Check_Validity_ਦਾ_ਸਦਿਸ਼_ਸੰਖਿਆ( uint32_t ul_ਸਦਿਸ਼_ਸੰਖਿਆ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable must be initialised to a non zero value to ensure interrupts don't
 * inadvertently become unmasked before the scheduler starts. It is set to zero
 * before the first task starts executing. */
ਅਸਥਿਰ uint32_t ulCriticalNesting = 9999UL;

/* A structure used to map the various fields of an IDT entry into separate
 * structure members. */
ਬਣਤਰ IDTEntry
{
    uint16_t usISRLow;          /* Low 16 bits of handler address. */
    uint16_t usSegmentSelector; /* Flat model means this is not changed. */
    uint8_t ucZero;             /* Must be set to zero. */
    uint8_t ucFlags;            /* Flags for this entry. */
    uint16_t usISRHigh;         /* High 16 bits of handler address. */
}
__attribute__( ( packed ) );
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IDTEntry IDTEntry_t;


/* Use to pass the location of the IDT to the CPU. */
ਬਣਤਰ IDTPointer
{
    uint16_t us_ਸਾਰਣੀ_ਹੱਦਬੰਦੀ;
    uint32_t ul_ਸਾਰਣੀ_ਅਧਾਰ; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IDTPointer IDTPointer_t;

/* The IDT itself. */
ਸਥਿਰ __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ ਪੋਰਟ_ਅੰਕ_VECTORS ];

#ਜੇ ( config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
ਸਥਿਰ ISR_Handler_t x_ਰੁਕਾਵਟ_Handler_ਸਾਰਣੀ[ ਪੋਰਟ_ਅੰਕ_VECTORS ] = { ਨਿਰਾ };

#ਜੇ_ਅੰਤ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#ਜੇ ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_ਪੋਰਟ_Task_FPUContext_ਬਫਰ __attribute__( ( ਵਰਤਿਆ ) ) = pdFALSE;

#ਜੇ_ਅੰਤ /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
ਸਥਿਰ uint32_t ul_System_ਢੇਰ[ config_ISR_ਢੇਰ_ਮਾਪ ] __attribute__( ( ਵਰਤਿਆ ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
ਅਸਥਿਰ uint32_t ul_ਸਿਖਰ_ਦਾ_System_ਢੇਰ __attribute__( ( ਵਰਤਿਆ ) ) = ( uint32_t ) &( ul_System_ਢੇਰ[ config_ISR_ਢੇਰ_ਮਾਪ - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
ਅਸਥਿਰ uint32_t ul_ਪੋਰਟ_Yield_Pending __attribute__( ( ਵਰਤਿਆ ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
ਅਸਥਿਰ uint32_t ul_ਰੁਕਾਵਟ_Nesting __attribute__( ( ਵਰਤਿਆ ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    uint32_t ul_ਕੋਡ_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Parameters first. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) prvTaskExitError;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* iret used to start the task pops up to here. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_EFLAGS;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* CS */
    __asm ਅਸਥਿਰ ( "movl %%cs, %0" : "=r" ( ul_ਕੋਡ_Segment ) );
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ul_ਕੋਡ_Segment;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* First instruction in the task. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xEA;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xEC;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xED1; /* EDX */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xEB1; /* EBX */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Hole for ESP. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00; /* EBP */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xE5; /* ESI */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xeeeeeeee; /* EDI */

    #ਜੇ ( configSUPPORT_FPU == 1 )
    {
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT;
    }
    #ਜੇ_ਅੰਤ /* configSUPPORT_FPU */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( uint8_t uc_ਸੰਖਿਆ,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_ਕੋਡ_Segment;
    uint32_t ul_ਅਧਾਰ = ( uint32_t ) pxHandlerFunction;

    x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ uc_ਸੰਖਿਆ ].usISRLow = ( uint16_t ) ( ul_ਅਧਾਰ & USHRT_MAX );
    x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ uc_ਸੰਖਿਆ ].usISRHigh = ( uint16_t ) ( ( ul_ਅਧਾਰ >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm ਅਸਥਿਰ ( "mov %%cs, %0" : "=r" ( us_ਕੋਡ_Segment ) );
    x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ uc_ਸੰਖਿਆ ].usSegmentSelector = us_ਕੋਡ_Segment;
    x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ uc_ਸੰਖਿਆ ].ucZero = 0;
    x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ uc_ਸੰਖਿਆ ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_IDT( ਖਾਲੀ )
{
    uint32_t ul_ਅੰਕ;
    IDTPointer_t xIDT;

    #ਜੇ ( config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ == 1 )
    {
        ਲਈ( ul_ਅੰਕ = 0; ul_ਅੰਕ < ਪੋਰਟ_ਅੰਕ_VECTORS; ul_ਅੰਕ++ )
        {
            /* If a handler has not already been installed on this vector. */
            ਜੇ( ( x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ ul_ਅੰਕ ].usISRLow == 0x00 ) && ( x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ[ ul_ਅੰਕ ].usISRHigh == 0x00 ) )
            {
                prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( ( uint8_t ) ul_ਅੰਕ, v_ਪੋਰਟ_Central_ਰੁਕਾਵਟ_Wrapper, ਪੋਰਟ_IDT_FLAGS );
            }
        }
    }
    #ਜੇ_ਅੰਤ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_ਸਾਰਣੀ_ਅਧਾਰ = ( uint32_t ) x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ;
    xIDT.us_ਸਾਰਣੀ_ਹੱਦਬੰਦੀ = ਆਕਾਰ( x_ਰੁਕਾਵਟ_Descriptor_ਸਾਰਣੀ ) - 1;

    /* Set IDT in CPU. */
    __asm ਅਸਥਿਰ ( "lidt %0" ::"m" ( xIDT ) );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_APICError_Handler_Wrapper( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_APICSpurious_Handler( ਖਾਲੀ );

    /* Initialise LAPIC to a well known state. */
    ਪੋਰਟ_APIC_LDR = 0xFFFFFFFF;
    ਪੋਰਟ_APIC_LDR = ( ( ਪੋਰਟ_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    ਪੋਰਟ_APIC_LVT_TIMER = ਪੋਰਟ_APIC_DISABLE;
    ਪੋਰਟ_APIC_LVT_PERF = ਪੋਰਟ_APIC_NMI;
    ਪੋਰਟ_APIC_LVT_LINT0 = ਪੋਰਟ_APIC_DISABLE;
    ਪੋਰਟ_APIC_LVT_LINT1 = ਪੋਰਟ_APIC_DISABLE;
    ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ = 0;

    /* Install APIC timer ISR vector. */
    prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( ( uint8_t ) ਪੋਰਟ_APIC_TIMER_INT_ਸਦਿਸ਼, v_ਪੋਰਟ_Timer_Handler, ਪੋਰਟ_IDT_FLAGS );

    /* Install API error handler. */
    prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( ( uint8_t ) ਪੋਰਟ_APIC_LVT_ERROR_ਸਦਿਸ਼, v_ਪੋਰਟ_APICError_Handler_Wrapper, ਪੋਰਟ_IDT_FLAGS );

    /* Install Yield handler. */
    prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( ( uint8_t ) ਪੋਰਟ_APIC_YIELD_INT_ਸਦਿਸ਼, v_ਪੋਰਟ_Yield_Call, ਪੋਰਟ_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( ( uint8_t ) ਪੋਰਟ_APIC_SPURIOUS_INT_ਸਦਿਸ਼, v_ਪੋਰਟ_APICSpurious_Handler, ਪੋਰਟ_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    ਪੋਰਟ_APIC_SPURIOUS_INT = ਪੋਰਟ_APIC_SPURIOUS_INT_ਸਦਿਸ਼ | ਪੋਰਟ_APIC_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

    /* Set timer error vector. */
    ਪੋਰਟ_APIC_LVT_ERROR = ਪੋਰਟ_APIC_LVT_ERROR_ਸਦਿਸ਼;

    /* Set the interrupt frequency. */
    ਪੋਰਟ_APIC_TMRDIV = ਪੋਰਟ_APIC_DIV_16;
    ਪੋਰਟ_APIC_TIMER_INITIAL_ਗਿਣਤੀ = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_ਦਰ_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਅਧਾਰ_Type_t x_ਸ਼ਬਦ;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( ਆਕਾਰ( ਬਣਤਰ IDTEntry ) == ਪੋਰਟ_EXPECTED_IDT_ਇੰਦਰਾਜ_ਮਾਪ );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    ਲਈ( x_ਸ਼ਬਦ = 0; x_ਸ਼ਬਦ < config_ISR_ਢੇਰ_ਮਾਪ - 20; x_ਸ਼ਬਦ++ )
    {
        ul_System_ਢੇਰ[ x_ਸ਼ਬਦ ] = ਪੋਰਟ_ਢੇਰ_ਸ਼ਬਦ;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_ਪੋਰਟ_ਤਿਆਰੀ_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Make sure the stack used by interrupts is aligned. */
    ul_ਸਿਖਰ_ਦਾ_System_ਢੇਰ &= ~ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    ਪੋਰਟ_APIC_LVT_TIMER = ਪੋਰਟ_APIC_TIMER_PERIODIC | ਪੋਰਟ_APIC_TIMER_INT_ਸਦਿਸ਼;

    /* Sometimes needed. */
    ਪੋਰਟ_APIC_TMRDIV = ਪੋਰਟ_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting == 0 )
    {
        #ਜੇ ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ਪੋਰਟ_MAX_ਤਰਜੀਹ )
        {
            __asm ਅਸਥਿਰ ( "cli" );
        }
        #ਨਹੀਂਤਾਂ
        {
            ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ = ਪੋਰਟ_MAX_API_CALL_ਤਰਜੀਹ;
            configASSERT( ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ == ਪੋਰਟ_MAX_API_CALL_ਤਰਜੀਹ );
        }
        #ਜੇ_ਅੰਤ
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #ਜੇ ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ਪੋਰਟ_MAX_ਤਰਜੀਹ )
            {
                __asm ਅਸਥਿਰ ( "sti" );
            }
            #ਨਹੀਂਤਾਂ
            {
                ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ = 0;
            }
            #ਜੇ_ਅੰਤ

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            ਜੇ( ul_ਪੋਰਟ_Yield_Pending != pdFALSE )
            {
                ul_ਪੋਰਟ_Yield_Pending = pdFALSE;
                __asm ਅਸਥਿਰ ( ਪੋਰਟ_YIELD_ਰੁਕਾਵਟ );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ )
{
    ਅਸਥਿਰ uint32_t ul_Original_ਨਕਾਬ;

    /* Set mask to max syscall priority. */
    #ਜੇ ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ਪੋਰਟ_MAX_ਤਰਜੀਹ )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm ਅਸਥਿਰ ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_ਨਕਾਬ )::"memory" );

        ul_Original_ਨਕਾਬ &= ਪੋਰਟ_EFLAGS_IF;
    }
    #ਨਹੀਂਤਾਂ
    {
        /* Return original mask. */
        ul_Original_ਨਕਾਬ = ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ;
        ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ = ਪੋਰਟ_MAX_API_CALL_ਤਰਜੀਹ;
        configASSERT( ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ == ਪੋਰਟ_MAX_API_CALL_ਤਰਜੀਹ );
    }
    #ਜੇ_ਅੰਤ /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    ਵਾਪਸ ul_Original_ਨਕਾਬ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( uint32_t ul_New_ਨਕਾਬ_ਮੁੱਲ )
{
    #ਜੇ ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ਪੋਰਟ_MAX_ਤਰਜੀਹ )
    {
        ਜੇ( ul_New_ਨਕਾਬ_ਮੁੱਲ != pdFALSE )
        {
            __asm ਅਸਥਿਰ ( "sti" );
        }
    }
    #ਨਹੀਂਤਾਂ
    {
        ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ = ul_New_ਨਕਾਬ_ਮੁੱਲ;
        configASSERT( ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ == ul_New_ਨਕਾਬ_ਮੁੱਲ );
    }
    #ਜੇ_ਅੰਤ /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#ਜੇ ( configSUPPORT_FPU == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_ਪੋਰਟ_Task_FPUContext_ਬਫਰ = ( uint8_t * ) pv_ਪੋਰਟ_Malloc( ਪੋਰਟ_FPU_CONTEXT_ਮਾਪ_ਬਾਈਟਾਂ );
        configASSERT( puc_ਪੋਰਟ_Task_FPUContext_ਬਫਰ );

        /* Initialise the floating point registers. */
        __asm ਅਸਥਿਰ ( "fninit" );
    }

#ਜੇ_ਅੰਤ /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_APICError_Handler( ਖਾਲੀ )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    ਅਸਥਿਰ uint32_t ul_Error_ਸਥਿਤੀ = 0;

    ਪੋਰਟ_APIC_ERROR_ਸਥਿਤੀ = 0;
    ul_Error_ਸਥਿਤੀ = ਪੋਰਟ_APIC_ERROR_ਸਥਿਤੀ;
    ( ਖਾਲੀ ) ul_Error_ਸਥਿਤੀ;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Central_ਰੁਕਾਵਟ_Handler( uint32_t ul_ਸਦਿਸ਼ )
    {
        ਜੇ( ul_ਸਦਿਸ਼ < ਪੋਰਟ_ਅੰਕ_VECTORS )
        {
            ਜੇ( x_ਰੁਕਾਵਟ_Handler_ਸਾਰਣੀ[ ul_ਸਦਿਸ਼ ] != ਨਿਰਾ )
            {
                ( x_ਰੁਕਾਵਟ_Handler_ਸਾਰਣੀ[ ul_ਸਦਿਸ਼ ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_ਢੇਰ[ 10 ] == ਪੋਰਟ_ਢੇਰ_ਸ਼ਬਦ );
        configASSERT( ul_System_ਢੇਰ[ 12 ] == ਪੋਰਟ_ਢੇਰ_ਸ਼ਬਦ );
        configASSERT( ul_System_ਢੇਰ[ 14 ] == ਪੋਰਟ_ਢੇਰ_ਸ਼ਬਦ );
    }

#ਜੇ_ਅੰਤ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ == 1 )

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਰਜਿਸਟਰ_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_ਸਦਿਸ਼_ਸੰਖਿਆ )
    {
        ਅਧਾਰ_Type_t xReturn;

        xReturn = prv_Check_Validity_ਦਾ_ਸਦਿਸ਼_ਸੰਖਿਆ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ );

        ਜੇ( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_ਰੁਕਾਵਟ_Handler_ਸਾਰਣੀ[ ul_ਸਦਿਸ਼_ਸੰਖਿਆ ] = pxHandler;
        }

        ਵਾਪਸ xReturn;
    }

#ਜੇ_ਅੰਤ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Install_ਰੁਕਾਵਟ_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ਸਦਿਸ਼_ਸੰਖਿਆ )
{
    ਅਧਾਰ_Type_t xReturn;

    xReturn = prv_Check_Validity_ਦਾ_ਸਦਿਸ਼_ਸੰਖਿਆ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ );

    ਜੇ( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_ਸੈੱਟ_ਰੁਕਾਵਟ_Gate( ( uint8_t ) ul_ਸਦਿਸ਼_ਸੰਖਿਆ, ( ISR_Handler_t ) pxHandler, ਪੋਰਟ_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    ਵਾਪਸ xReturn;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਅਧਾਰ_Type_t prv_Check_Validity_ਦਾ_ਸਦਿਸ਼_ਸੰਖਿਆ( uint32_t ul_ਸਦਿਸ਼_ਸੰਖਿਆ )
{
    ਅਧਾਰ_Type_t xReturn;

    /* Check validity of vector number. */
    ਜੇ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ >= ਪੋਰਟ_ਅੰਕ_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    ਨਹੀਂਤਾਂ ਜੇ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ < ਪੋਰਟ_APIC_MIN_ALLOWABLE_ਸਦਿਸ਼ )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    ਨਹੀਂਤਾਂ ਜੇ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ == ਪੋਰਟ_APIC_TIMER_INT_ਸਦਿਸ਼ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    ਨਹੀਂਤਾਂ ਜੇ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ == ਪੋਰਟ_APIC_YIELD_INT_ਸਦਿਸ਼ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    ਨਹੀਂਤਾਂ ਜੇ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ == ਪੋਰਟ_APIC_LVT_ERROR_ਸਦਿਸ਼ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    ਨਹੀਂਤਾਂ ਜੇ( ul_ਸਦਿਸ਼_ਸੰਖਿਆ == ਪੋਰਟ_APIC_SPURIOUS_INT_ਸਦਿਸ਼ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#ਜੇ ( config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ == 1 )
    ਨਹੀਂਤਾਂ ਜੇ( x_ਰੁਕਾਵਟ_Handler_ਸਾਰਣੀ[ ul_ਸਦਿਸ਼_ਸੰਖਿਆ ] != ਨਿਰਾ )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#ਜੇ_ਅੰਤ  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    ਨਹੀਂਤਾਂ
    {
        xReturn = pdPASS;
    }

    ਵਾਪਸ xReturn;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_Generate_Yield_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    __asm ਅਸਥਿਰ ( ਪੋਰਟ_YIELD_ਰੁਕਾਵਟ );
}
