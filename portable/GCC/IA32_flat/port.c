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
#ಅನ್ತರ್ಭಾವ <limits.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ಆದರೆ ( config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 difference priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ಆದರೆ ( config_ISR_ರಾಶಿ_ಗಾತ್ರ < ( config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ * 2 ) )
    #warning config_ISR_ರಾಶಿ_ಗಾತ್ರ is probably too small!
#ಆದರೆ_ಅಂತ್ಯ /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#ಆದರೆ ( ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ > ಪೋರ್ಟ್_MAX_ಆದ್ಯತೆ ) || ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ < 2 ) )
    #ದೋಷ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ must be between 2 and 15
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 0 ) )
    #ದೋಷ config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ must be ಗಣ ಗಮ್ಯ 1 ಗಮ್ಯ use this ಪೋರ್ಟ್ with an FPU
#ಆದರೆ_ಅಂತ್ಯ

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT    ( ( ರಾಶಿ_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LVT_ERROR_ಸದಿಶ        ( 0xfe )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_SPURIOUS_INT_ಸದಿಶ     ( 0xff )

/* EFLAGS bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_CONTEXT_ಗಾತ್ರ_ಬೈಟುಗಳು       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXPECTED_IDT_ನಮೂದು_ಗಾತ್ರ      8

/* Default flags setting for entries in the IDT. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_MIN_ALLOWABLE_ಸದಿಶ    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_ಶಬ್ದ                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*
 * Complete one descriptor in the IDT.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಗಣ_ಅಡಚಣೆ_Gate( uint8_t uc_ಸಂಖ್ಯೆ,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Central_ಅಡಚಣೆ_Wrapper( ಶೂನ್ಯ );

/*
 * Handler for portYIELD().
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Call( ಶೂನ್ಯ );

/*
 * Configure the APIC to generate the RTOS tick.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Tick interrupt handler.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Timer_Handler( ಶೂನ್ಯ );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
ಸ್ಥಿರ ತಳ_Type_t prv_Check_Validity_ದ_ಸದಿಶ_ಸಂಖ್ಯೆ( uint32_t ul_ಸದಿಶ_ಸಂಖ್ಯೆ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable must be initialised to a non zero value to ensure interrupts don't
 * inadvertently become unmasked before the scheduler starts. It is set to zero
 * before the first task starts executing. */
ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/* A structure used to map the various fields of an IDT entry into separate
 * structure members. */
ರಚನೆ IDTEntry
{
    uint16_t usISRLow;          /* Low 16 bits of handler address. */
    uint16_t usSegmentSelector; /* Flat model means this is not changed. */
    uint8_t ucZero;             /* Must be set to zero. */
    uint8_t ucFlags;            /* Flags for this entry. */
    uint16_t usISRHigh;         /* High 16 bits of handler address. */
}
__attribute__( ( packed ) );
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IDTEntry IDTEntry_t;


/* Use to pass the location of the IDT to the CPU. */
ರಚನೆ IDTPointer
{
    uint16_t us_ಕೋಷ್ಟಕ_ಎಲ್ಲೆ;
    uint32_t ul_ಕೋಷ್ಟಕ_ತಳ; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IDTPointer IDTPointer_t;

/* The IDT itself. */
ಸ್ಥಿರ __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಅಂಕೆ_VECTORS ];

#ಆದರೆ ( config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
ಸ್ಥಿರ ISR_Handler_t x_ಅಡಚಣೆ_Handler_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಅಂಕೆ_VECTORS ] = { ಖಾಲಿ };

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#ಆದರೆ ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_ಪೋರ್ಟ್_Task_FPUContext_ಬಫರ್ __attribute__( ( ಬಳಸಿದ ) ) = pdFALSE;

#ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
ಸ್ಥಿರ uint32_t ul_System_ರಾಶಿ[ config_ISR_ರಾಶಿ_ಗಾತ್ರ ] __attribute__( ( ಬಳಸಿದ ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
ಅಸ್ಥಿರ uint32_t ul_ತುದಿ_ದ_System_ರಾಶಿ __attribute__( ( ಬಳಸಿದ ) ) = ( uint32_t ) &( ul_System_ರಾಶಿ[ config_ISR_ರಾಶಿ_ಗಾತ್ರ - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_Yield_Pending __attribute__( ( ಬಳಸಿದ ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
ಅಸ್ಥಿರ uint32_t ul_ಅಡಚಣೆ_Nesting __attribute__( ( ಬಳಸಿದ ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    uint32_t ul_ಸಂಕೇತ_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Parameters first. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) prvTaskExitError;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* iret used to start the task pops up to here. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EFLAGS;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* CS */
    __asm ಅಸ್ಥಿರ ( "movl %%cs, %0" : "=r" ( ul_ಸಂಕೇತ_Segment ) );
    *px_ತುದಿ_ದ_ರಾಶಿ = ul_ಸಂಕೇತ_Segment;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* First instruction in the task. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 0xEA;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = 0xEC;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = 0xED1; /* EDX */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = 0xEB1; /* EBX */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Hole for ESP. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = 0x00; /* EBP */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = 0xE5; /* ESI */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = 0xeeeeeeee; /* EDI */

    #ಆದರೆ ( configSUPPORT_FPU == 1 )
    {
        px_ತುದಿ_ದ_ರಾಶಿ--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_FPU */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಗಣ_ಅಡಚಣೆ_Gate( uint8_t uc_ಸಂಖ್ಯೆ,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_ಸಂಕೇತ_Segment;
    uint32_t ul_ತಳ = ( uint32_t ) pxHandlerFunction;

    x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ uc_ಸಂಖ್ಯೆ ].usISRLow = ( uint16_t ) ( ul_ತಳ & USHRT_MAX );
    x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ uc_ಸಂಖ್ಯೆ ].usISRHigh = ( uint16_t ) ( ( ul_ತಳ >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm ಅಸ್ಥಿರ ( "mov %%cs, %0" : "=r" ( us_ಸಂಕೇತ_Segment ) );
    x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ uc_ಸಂಖ್ಯೆ ].usSegmentSelector = us_ಸಂಕೇತ_Segment;
    x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ uc_ಸಂಖ್ಯೆ ].ucZero = 0;
    x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ uc_ಸಂಖ್ಯೆ ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_IDT( ಶೂನ್ಯ )
{
    uint32_t ul_ಅಂಕೆ;
    IDTPointer_t xIDT;

    #ಆದರೆ ( config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು == 1 )
    {
        ಗಾಗಿ( ul_ಅಂಕೆ = 0; ul_ಅಂಕೆ < ಪೋರ್ಟ್_ಅಂಕೆ_VECTORS; ul_ಅಂಕೆ++ )
        {
            /* If a handler has not already been installed on this vector. */
            ಆದರೆ( ( x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ ul_ಅಂಕೆ ].usISRLow == 0x00 ) && ( x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ[ ul_ಅಂಕೆ ].usISRHigh == 0x00 ) )
            {
                prv_ಗಣ_ಅಡಚಣೆ_Gate( ( uint8_t ) ul_ಅಂಕೆ, v_ಪೋರ್ಟ್_Central_ಅಡಚಣೆ_Wrapper, ಪೋರ್ಟ್_IDT_FLAGS );
            }
        }
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_ಕೋಷ್ಟಕ_ತಳ = ( uint32_t ) x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ;
    xIDT.us_ಕೋಷ್ಟಕ_ಎಲ್ಲೆ = ಗಾತ್ರ( x_ಅಡಚಣೆ_Descriptor_ಕೋಷ್ಟಕ ) - 1;

    /* Set IDT in CPU. */
    __asm ಅಸ್ಥಿರ ( "lidt %0" ::"m" ( xIDT ) );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_APICError_Handler_Wrapper( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_APICSpurious_Handler( ಶೂನ್ಯ );

    /* Initialise LAPIC to a well known state. */
    ಪೋರ್ಟ್_APIC_LDR = 0xFFFFFFFF;
    ಪೋರ್ಟ್_APIC_LDR = ( ( ಪೋರ್ಟ್_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    ಪೋರ್ಟ್_APIC_LVT_TIMER = ಪೋರ್ಟ್_APIC_DISABLE;
    ಪೋರ್ಟ್_APIC_LVT_PERF = ಪೋರ್ಟ್_APIC_NMI;
    ಪೋರ್ಟ್_APIC_LVT_LINT0 = ಪೋರ್ಟ್_APIC_DISABLE;
    ಪೋರ್ಟ್_APIC_LVT_LINT1 = ಪೋರ್ಟ್_APIC_DISABLE;
    ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ = 0;

    /* Install APIC timer ISR vector. */
    prv_ಗಣ_ಅಡಚಣೆ_Gate( ( uint8_t ) ಪೋರ್ಟ್_APIC_TIMER_INT_ಸದಿಶ, v_ಪೋರ್ಟ್_Timer_Handler, ಪೋರ್ಟ್_IDT_FLAGS );

    /* Install API error handler. */
    prv_ಗಣ_ಅಡಚಣೆ_Gate( ( uint8_t ) ಪೋರ್ಟ್_APIC_LVT_ERROR_ಸದಿಶ, v_ಪೋರ್ಟ್_APICError_Handler_Wrapper, ಪೋರ್ಟ್_IDT_FLAGS );

    /* Install Yield handler. */
    prv_ಗಣ_ಅಡಚಣೆ_Gate( ( uint8_t ) ಪೋರ್ಟ್_APIC_YIELD_INT_ಸದಿಶ, v_ಪೋರ್ಟ್_Yield_Call, ಪೋರ್ಟ್_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_ಗಣ_ಅಡಚಣೆ_Gate( ( uint8_t ) ಪೋರ್ಟ್_APIC_SPURIOUS_INT_ಸದಿಶ, v_ಪೋರ್ಟ್_APICSpurious_Handler, ಪೋರ್ಟ್_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    ಪೋರ್ಟ್_APIC_SPURIOUS_INT = ಪೋರ್ಟ್_APIC_SPURIOUS_INT_ಸದಿಶ | ಪೋರ್ಟ್_APIC_ENABLE_ಬಿಟ್;

    /* Set timer error vector. */
    ಪೋರ್ಟ್_APIC_LVT_ERROR = ಪೋರ್ಟ್_APIC_LVT_ERROR_ಸದಿಶ;

    /* Set the interrupt frequency. */
    ಪೋರ್ಟ್_APIC_TMRDIV = ಪೋರ್ಟ್_APIC_DIV_16;
    ಪೋರ್ಟ್_APIC_TIMER_INITIAL_ಎಣಿಕೆ = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_ದರ_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ತಳ_Type_t x_ಶಬ್ದ;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( ಗಾತ್ರ( ರಚನೆ IDTEntry ) == ಪೋರ್ಟ್_EXPECTED_IDT_ನಮೂದು_ಗಾತ್ರ );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    ಗಾಗಿ( x_ಶಬ್ದ = 0; x_ಶಬ್ದ < config_ISR_ರಾಶಿ_ಗಾತ್ರ - 20; x_ಶಬ್ದ++ )
    {
        ul_System_ರಾಶಿ[ x_ಶಬ್ದ ] = ಪೋರ್ಟ್_ರಾಶಿ_ಶಬ್ದ;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Make sure the stack used by interrupts is aligned. */
    ul_ತುದಿ_ದ_System_ರಾಶಿ &= ~ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    ಪೋರ್ಟ್_APIC_LVT_TIMER = ಪೋರ್ಟ್_APIC_TIMER_PERIODIC | ಪೋರ್ಟ್_APIC_TIMER_INT_ಸದಿಶ;

    /* Sometimes needed. */
    ಪೋರ್ಟ್_APIC_TMRDIV = ಪೋರ್ಟ್_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting == 0 )
    {
        #ಆದರೆ ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == ಪೋರ್ಟ್_MAX_ಆದ್ಯತೆ )
        {
            __asm ಅಸ್ಥಿರ ( "cli" );
        }
        #ಇಲ್ಲದಿದ್ದರೆ
        {
            ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ = ಪೋರ್ಟ್_MAX_API_CALL_ಆದ್ಯತೆ;
            configASSERT( ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ == ಪೋರ್ಟ್_MAX_API_CALL_ಆದ್ಯತೆ );
        }
        #ಆದರೆ_ಅಂತ್ಯ
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #ಆದರೆ ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == ಪೋರ್ಟ್_MAX_ಆದ್ಯತೆ )
            {
                __asm ಅಸ್ಥಿರ ( "sti" );
            }
            #ಇಲ್ಲದಿದ್ದರೆ
            {
                ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ = 0;
            }
            #ಆದರೆ_ಅಂತ್ಯ

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            ಆದರೆ( ul_ಪೋರ್ಟ್_Yield_Pending != pdFALSE )
            {
                ul_ಪೋರ್ಟ್_Yield_Pending = pdFALSE;
                __asm ಅಸ್ಥಿರ ( ಪೋರ್ಟ್_YIELD_ಅಡಚಣೆ );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ )
{
    ಅಸ್ಥಿರ uint32_t ul_Original_ಮುಖವಾಡ;

    /* Set mask to max syscall priority. */
    #ಆದರೆ ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == ಪೋರ್ಟ್_MAX_ಆದ್ಯತೆ )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm ಅಸ್ಥಿರ ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_ಮುಖವಾಡ )::"memory" );

        ul_Original_ಮುಖವಾಡ &= ಪೋರ್ಟ್_EFLAGS_IF;
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        /* Return original mask. */
        ul_Original_ಮುಖವಾಡ = ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ;
        ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ = ಪೋರ್ಟ್_MAX_API_CALL_ಆದ್ಯತೆ;
        configASSERT( ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ == ಪೋರ್ಟ್_MAX_API_CALL_ಆದ್ಯತೆ );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    ಹಿಂತಿರುಗಿ ul_Original_ಮುಖವಾಡ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( uint32_t ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ )
{
    #ಆದರೆ ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == ಪೋರ್ಟ್_MAX_ಆದ್ಯತೆ )
    {
        ಆದರೆ( ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ != pdFALSE )
        {
            __asm ಅಸ್ಥಿರ ( "sti" );
        }
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ = ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ;
        configASSERT( ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ == ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configSUPPORT_FPU == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_ಪೋರ್ಟ್_Task_FPUContext_ಬಫರ್ = ( uint8_t * ) pv_ಪೋರ್ಟ್_Malloc( ಪೋರ್ಟ್_FPU_CONTEXT_ಗಾತ್ರ_ಬೈಟುಗಳು );
        configASSERT( puc_ಪೋರ್ಟ್_Task_FPUContext_ಬಫರ್ );

        /* Initialise the floating point registers. */
        __asm ಅಸ್ಥಿರ ( "fninit" );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_APICError_Handler( ಶೂನ್ಯ )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    ಅಸ್ಥಿರ uint32_t ul_Error_ಸ್ಥಿತಿ = 0;

    ಪೋರ್ಟ್_APIC_ERROR_ಸ್ಥಿತಿ = 0;
    ul_Error_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_APIC_ERROR_ಸ್ಥಿತಿ;
    ( ಶೂನ್ಯ ) ul_Error_ಸ್ಥಿತಿ;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Central_ಅಡಚಣೆ_Handler( uint32_t ul_ಸದಿಶ )
    {
        ಆದರೆ( ul_ಸದಿಶ < ಪೋರ್ಟ್_ಅಂಕೆ_VECTORS )
        {
            ಆದರೆ( x_ಅಡಚಣೆ_Handler_ಕೋಷ್ಟಕ[ ul_ಸದಿಶ ] != ಖಾಲಿ )
            {
                ( x_ಅಡಚಣೆ_Handler_ಕೋಷ್ಟಕ[ ul_ಸದಿಶ ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_ರಾಶಿ[ 10 ] == ಪೋರ್ಟ್_ರಾಶಿ_ಶಬ್ದ );
        configASSERT( ul_System_ರಾಶಿ[ 12 ] == ಪೋರ್ಟ್_ರಾಶಿ_ಶಬ್ದ );
        configASSERT( ul_System_ರಾಶಿ[ 14 ] == ಪೋರ್ಟ್_ರಾಶಿ_ಶಬ್ದ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು == 1 )

    ತಳ_Type_t x_ಪೋರ್ಟ್_ರಿಜಿಸ್ಟರ್_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_ಸದಿಶ_ಸಂಖ್ಯೆ )
    {
        ತಳ_Type_t xReturn;

        xReturn = prv_Check_Validity_ದ_ಸದಿಶ_ಸಂಖ್ಯೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ );

        ಆದರೆ( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_ಅಡಚಣೆ_Handler_ಕೋಷ್ಟಕ[ ul_ಸದಿಶ_ಸಂಖ್ಯೆ ] = pxHandler;
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Install_ಅಡಚಣೆ_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ಸದಿಶ_ಸಂಖ್ಯೆ )
{
    ತಳ_Type_t xReturn;

    xReturn = prv_Check_Validity_ದ_ಸದಿಶ_ಸಂಖ್ಯೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ );

    ಆದರೆ( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_ಗಣ_ಅಡಚಣೆ_Gate( ( uint8_t ) ul_ಸದಿಶ_ಸಂಖ್ಯೆ, ( ISR_Handler_t ) pxHandler, ಪೋರ್ಟ್_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    ಹಿಂತಿರುಗಿ xReturn;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ತಳ_Type_t prv_Check_Validity_ದ_ಸದಿಶ_ಸಂಖ್ಯೆ( uint32_t ul_ಸದಿಶ_ಸಂಖ್ಯೆ )
{
    ತಳ_Type_t xReturn;

    /* Check validity of vector number. */
    ಆದರೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ >= ಪೋರ್ಟ್_ಅಂಕೆ_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ < ಪೋರ್ಟ್_APIC_MIN_ALLOWABLE_ಸದಿಶ )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ == ಪೋರ್ಟ್_APIC_TIMER_INT_ಸದಿಶ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ == ಪೋರ್ಟ್_APIC_YIELD_INT_ಸದಿಶ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ == ಪೋರ್ಟ್_APIC_LVT_ERROR_ಸದಿಶ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ul_ಸದಿಶ_ಸಂಖ್ಯೆ == ಪೋರ್ಟ್_APIC_SPURIOUS_INT_ಸದಿಶ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#ಆದರೆ ( config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು == 1 )
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( x_ಅಡಚಣೆ_Handler_ಕೋಷ್ಟಕ[ ul_ಸದಿಶ_ಸಂಖ್ಯೆ ] != ಖಾಲಿ )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#ಆದರೆ_ಅಂತ್ಯ  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdPASS;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_Generate_Yield_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    __asm ಅಸ್ಥಿರ ( ಪೋರ್ಟ್_YIELD_ಅಡಚಣೆ );
}
