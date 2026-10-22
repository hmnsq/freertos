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
#அந்தர்பாவ <limits.h>

/* Scheduler includes. */
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

#எனில் ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #எனில் ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif
#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#எனில் ( config_ISR_அடுக்கு_SIZE < ( config_MINIMAL_அடுக்கு_SIZE * 2 ) )
    #warning config_ISR_அடுக்கு_SIZE is probably too small!
#endif /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#எனில் ( ( configMAX_API_CALL_INTERRUPT_PRIORITY > portMAX_PRIORITY ) || ( configMAX_API_CALL_INTERRUPT_PRIORITY < 2 ) )
    #error configMAX_API_CALL_INTERRUPT_PRIORITY must be between 2 and 15
#endif

#எனில் ( ( configSUPPORT_FPU == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 0 ) )
    #error configSUPPORT_DYNAMIC_ALLOCATION must be set to 1 to use this port with an FPU
#endif

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#define portNO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#define portNO_FLOATING_POINT_CONTEXT    ( ( அடுக்கு_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#define portINITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#define portAPIC_LVT_ERROR_VECTOR        ( 0xfe )
#define portAPIC_SPURIOUS_INT_VECTOR     ( 0xff )

/* EFLAGS bits. */
#define portEFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#define portFPU_CONTEXT_SIZE_BYTES       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#define portEXPECTED_IDT_ENTRY_SIZE      8

/* Default flags setting for entries in the IDT. */
#define portIDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#define portAPIC_MIN_ALLOWABLE_VECTOR    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#define port_அடுக்கு_WORD                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
வெளி வெறுமை vPortStartFirstTask( வெறுமை );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
நிலையான வெறுமை prvTaskExitError( வெறுமை );

/*
 * Complete one descriptor in the IDT.
 */
நிலையான வெறுமை prvSetInterruptGate( uint8_t uc_எண்,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
வெளி வெறுமை vPortCentralInterruptWrapper( வெறுமை );

/*
 * Handler for portYIELD().
 */
வெளி வெறுமை vPortYieldCall( வெறுமை );

/*
 * Configure the APIC to generate the RTOS tick.
 */
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை );

/*
 * Tick interrupt handler.
 */
வெளி வெறுமை vPortTimerHandler( வெறுமை );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
நிலையான BaseType_t prv_Check_Validity_Of_Vector_எண்( uint32_t ul_Vector_எண் );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable must be initialised to a non zero value to ensure interrupts don't
 * inadvertently become unmasked before the scheduler starts. It is set to zero
 * before the first task starts executing. */
நிலையற்ற uint32_t ulCriticalNesting = 9999UL;

/* A structure used to map the various fields of an IDT entry into separate
 * structure members. */
கட்டமைப்பு IDTEntry
{
    uint16_t usISRLow;          /* Low 16 bits of handler address. */
    uint16_t usSegmentSelector; /* Flat model means this is not changed. */
    uint8_t ucZero;             /* Must be set to zero. */
    uint8_t ucFlags;            /* Flags for this entry. */
    uint16_t usISRHigh;         /* High 16 bits of handler address. */
}
__attribute__( ( packed ) );
வகைவரை கட்டமைப்பு IDTEntry IDTEntry_t;


/* Use to pass the location of the IDT to the CPU. */
கட்டமைப்பு IDTPointer
{
    uint16_t usTableLimit;
    uint32_t ulTableBase; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
வகைவரை கட்டமைப்பு IDTPointer IDTPointer_t;

/* The IDT itself. */
நிலையான __attribute__( ( aligned( 32 ) ) ) IDTEntry_t xInterruptDescriptorTable[ port_இலக்கம்_VECTORS ];

#எனில் ( configUSE_COMMON_INTERRUPT_ENTRY_POINT == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
நிலையான ISR_Handler_t xInterruptHandlerTable[ port_இலக்கம்_VECTORS ] = { வெற்று };

#endif /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#எனில் ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * pucPortTaskFPUContextBuffer __attribute__( ( used ) ) = pdFALSE;

#endif /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
நிலையான uint32_t ul_System_அடுக்கு[ config_ISR_அடுக்கு_SIZE ] __attribute__( ( used ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
நிலையற்ற uint32_t ul_உச்சி_Of_System_அடுக்கு __attribute__( ( used ) ) = ( uint32_t ) &( ul_System_அடுக்கு[ config_ISR_அடுக்கு_SIZE - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
நிலையற்ற uint32_t ulPortYieldPending __attribute__( ( used ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
நிலையற்ற uint32_t ulInterruptNesting __attribute__( ( used ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    uint32_t ulCodeSegment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_உச்சி_Of_அடுக்கு = 0x00;
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = 0x00;
    px_உச்சி_Of_அடுக்கு--;

    /* Parameters first. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pvParameters;
    px_உச்சி_Of_அடுக்கு--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) prvTaskExitError;
    px_உச்சி_Of_அடுக்கு--;

    /* iret used to start the task pops up to here. */
    *px_உச்சி_Of_அடுக்கு = portINITIAL_EFLAGS;
    px_உச்சி_Of_அடுக்கு--;

    /* CS */
    __asm நிலையற்ற ( "movl %%cs, %0" : "=r" ( ulCodeSegment ) );
    *px_உச்சி_Of_அடுக்கு = ulCodeSegment;
    px_உச்சி_Of_அடுக்கு--;

    /* First instruction in the task. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pxCode;
    px_உச்சி_Of_அடுக்கு--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_உச்சி_Of_அடுக்கு = 0xEA;
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = 0xEC;
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = 0xED1; /* EDX */
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = 0xEB1; /* EBX */
    px_உச்சி_Of_அடுக்கு--;

    /* Hole for ESP. */
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = 0x00; /* EBP */
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = 0xE5; /* ESI */
    px_உச்சி_Of_அடுக்கு--;

    *px_உச்சி_Of_அடுக்கு = 0xeeeeeeee; /* EDI */

    #எனில் ( configSUPPORT_FPU == 1 )
    {
        px_உச்சி_Of_அடுக்கு--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_உச்சி_Of_அடுக்கு = portNO_FLOATING_POINT_CONTEXT;
    }
    #endif /* configSUPPORT_FPU */

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetInterruptGate( uint8_t uc_எண்,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t usCodeSegment;
    uint32_t ulBase = ( uint32_t ) pxHandlerFunction;

    xInterruptDescriptorTable[ uc_எண் ].usISRLow = ( uint16_t ) ( ulBase & USHRT_MAX );
    xInterruptDescriptorTable[ uc_எண் ].usISRHigh = ( uint16_t ) ( ( ulBase >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm நிலையற்ற ( "mov %%cs, %0" : "=r" ( usCodeSegment ) );
    xInterruptDescriptorTable[ uc_எண் ].usSegmentSelector = usCodeSegment;
    xInterruptDescriptorTable[ uc_எண் ].ucZero = 0;
    xInterruptDescriptorTable[ uc_எண் ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

வெறுமை vPortSetupIDT( வெறுமை )
{
    uint32_t ul_இலக்கம்;
    IDTPointer_t xIDT;

    #எனில் ( configUSE_COMMON_INTERRUPT_ENTRY_POINT == 1 )
    {
        க்கு( ul_இலக்கம் = 0; ul_இலக்கம் < port_இலக்கம்_VECTORS; ul_இலக்கம்++ )
        {
            /* If a handler has not already been installed on this vector. */
            எனில்( ( xInterruptDescriptorTable[ ul_இலக்கம் ].usISRLow == 0x00 ) && ( xInterruptDescriptorTable[ ul_இலக்கம் ].usISRHigh == 0x00 ) )
            {
                prvSetInterruptGate( ( uint8_t ) ul_இலக்கம், vPortCentralInterruptWrapper, portIDT_FLAGS );
            }
        }
    }
    #endif /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ulTableBase = ( uint32_t ) xInterruptDescriptorTable;
    xIDT.usTableLimit = அளவு( xInterruptDescriptorTable ) - 1;

    /* Set IDT in CPU. */
    __asm நிலையற்ற ( "lidt %0" ::"m" ( xIDT ) );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvTaskExitError( வெறுமை )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    க்கு( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை )
{
    வெளி வெறுமை vPortAPICErrorHandlerWrapper( வெறுமை );
    வெளி வெறுமை vPortAPICSpuriousHandler( வெறுமை );

    /* Initialise LAPIC to a well known state. */
    portAPIC_LDR = 0xFFFFFFFF;
    portAPIC_LDR = ( ( portAPIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    portAPIC_LVT_TIMER = portAPIC_DISABLE;
    portAPIC_LVT_PERF = portAPIC_NMI;
    portAPIC_LVT_LINT0 = portAPIC_DISABLE;
    portAPIC_LVT_LINT1 = portAPIC_DISABLE;
    portAPIC_TASK_PRIORITY = 0;

    /* Install APIC timer ISR vector. */
    prvSetInterruptGate( ( uint8_t ) portAPIC_TIMER_INT_VECTOR, vPortTimerHandler, portIDT_FLAGS );

    /* Install API error handler. */
    prvSetInterruptGate( ( uint8_t ) portAPIC_LVT_ERROR_VECTOR, vPortAPICErrorHandlerWrapper, portIDT_FLAGS );

    /* Install Yield handler. */
    prvSetInterruptGate( ( uint8_t ) portAPIC_YIELD_INT_VECTOR, vPortYieldCall, portIDT_FLAGS );

    /* Install spurious interrupt vector. */
    prvSetInterruptGate( ( uint8_t ) portAPIC_SPURIOUS_INT_VECTOR, vPortAPICSpuriousHandler, portIDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    portAPIC_SPURIOUS_INT = portAPIC_SPURIOUS_INT_VECTOR | portAPIC_ENABLE_BIT;

    /* Set timer error vector. */
    portAPIC_LVT_ERROR = portAPIC_LVT_ERROR_VECTOR;

    /* Set the interrupt frequency. */
    portAPIC_TMRDIV = portAPIC_DIV_16;
    port_APIC_TIMER_INITIAL_மொத்தம் = ( ( configCPU_CLOCK_HZ >> 4UL ) / configTICK_RATE_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    BaseType_t xWord;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( அளவு( கட்டமைப்பு IDTEntry ) == portEXPECTED_IDT_ENTRY_SIZE );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    க்கு( xWord = 0; xWord < config_ISR_அடுக்கு_SIZE - 20; xWord++ )
    {
        ul_System_அடுக்கு[ xWord ] = port_அடுக்கு_WORD;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    vPortSetupIDT();

    /* Initialise LAPIC and install system handlers. */
    prvSetupTimerInterrupt();

    /* Make sure the stack used by interrupts is aligned. */
    ul_உச்சி_Of_System_அடுக்கு &= ~portBYTE_ALIGNMENT_MASK;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    portAPIC_LVT_TIMER = portAPIC_TIMER_PERIODIC | portAPIC_TIMER_INT_VECTOR;

    /* Sometimes needed. */
    portAPIC_TMRDIV = portAPIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    vPortStartFirstTask();

    திரும்பு 0;
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

வெறுமை vPortEnterCritical( வெறுமை )
{
    எனில்( ulCriticalNesting == 0 )
    {
        #எனில் ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY )
        {
            __asm நிலையற்ற ( "cli" );
        }
        #இல்லையெனில்
        {
            portAPIC_TASK_PRIORITY = portMAX_API_CALL_PRIORITY;
            configASSERT( portAPIC_TASK_PRIORITY == portMAX_API_CALL_PRIORITY );
        }
        #endif
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

வெறுமை vPortExitCritical( வெறுமை )
{
    எனில்( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        எனில்( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #எனில் ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY )
            {
                __asm நிலையற்ற ( "sti" );
            }
            #இல்லையெனில்
            {
                portAPIC_TASK_PRIORITY = 0;
            }
            #endif

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            எனில்( ulPortYieldPending != pdFALSE )
            {
                ulPortYieldPending = pdFALSE;
                __asm நிலையற்ற ( portYIELD_INTERRUPT );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortSetInterruptMask( வெறுமை )
{
    நிலையற்ற uint32_t ulOriginalMask;

    /* Set mask to max syscall priority. */
    #எனில் ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm நிலையற்ற ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ulOriginalMask )::"memory" );

        ulOriginalMask &= portEFLAGS_IF;
    }
    #இல்லையெனில்
    {
        /* Return original mask. */
        ulOriginalMask = portAPIC_TASK_PRIORITY;
        portAPIC_TASK_PRIORITY = portMAX_API_CALL_PRIORITY;
        configASSERT( portAPIC_TASK_PRIORITY == portMAX_API_CALL_PRIORITY );
    }
    #endif /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    திரும்பு ulOriginalMask;
}
/*-----------------------------------------------------------*/

வெறுமை vPortClearInterruptMask( uint32_t ul_New_Mask_மதிப்பு )
{
    #எனில் ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY )
    {
        எனில்( ul_New_Mask_மதிப்பு != pdFALSE )
        {
            __asm நிலையற்ற ( "sti" );
        }
    }
    #இல்லையெனில்
    {
        portAPIC_TASK_PRIORITY = ul_New_Mask_மதிப்பு;
        configASSERT( portAPIC_TASK_PRIORITY == ul_New_Mask_மதிப்பு );
    }
    #endif /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#எனில் ( configSUPPORT_FPU == 1 )

    வெறுமை vPortTaskUsesFPU( வெறுமை )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        pucPortTaskFPUContextBuffer = ( uint8_t * ) pvPortMalloc( portFPU_CONTEXT_SIZE_BYTES );
        configASSERT( pucPortTaskFPUContextBuffer );

        /* Initialise the floating point registers. */
        __asm நிலையற்ற ( "fninit" );
    }

#endif /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

வெறுமை vPortAPICErrorHandler( வெறுமை )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    நிலையற்ற uint32_t ulErrorStatus = 0;

    portAPIC_ERROR_STATUS = 0;
    ulErrorStatus = portAPIC_ERROR_STATUS;
    ( வெறுமை ) ulErrorStatus;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#எனில் ( configUSE_COMMON_INTERRUPT_ENTRY_POINT == 1 )

    வெறுமை vPortCentralInterruptHandler( uint32_t ulVector )
    {
        எனில்( ulVector < port_இலக்கம்_VECTORS )
        {
            எனில்( xInterruptHandlerTable[ ulVector ] != வெற்று )
            {
                ( xInterruptHandlerTable[ ulVector ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_அடுக்கு[ 10 ] == port_அடுக்கு_WORD );
        configASSERT( ul_System_அடுக்கு[ 12 ] == port_அடுக்கு_WORD );
        configASSERT( ul_System_அடுக்கு[ 14 ] == port_அடுக்கு_WORD );
    }

#endif /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#எனில் ( configUSE_COMMON_INTERRUPT_ENTRY_POINT == 1 )

    BaseType_t xPortRegisterCInterruptHandler( ISR_Handler_t pxHandler,
                                               uint32_t ul_Vector_எண் )
    {
        BaseType_t xReturn;

        xReturn = prv_Check_Validity_Of_Vector_எண்( ul_Vector_எண் );

        எனில்( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            xInterruptHandlerTable[ ul_Vector_எண் ] = pxHandler;
        }

        திரும்பு xReturn;
    }

#endif /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

BaseType_t xPortInstallInterruptHandler( ISR_Handler_t pxHandler,
                                         uint32_t ul_Vector_எண் )
{
    BaseType_t xReturn;

    xReturn = prv_Check_Validity_Of_Vector_எண்( ul_Vector_எண் );

    எனில்( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prvSetInterruptGate( ( uint8_t ) ul_Vector_எண், ( ISR_Handler_t ) pxHandler, portIDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    திரும்பு xReturn;
}
/*-----------------------------------------------------------*/

நிலையான BaseType_t prv_Check_Validity_Of_Vector_எண்( uint32_t ul_Vector_எண் )
{
    BaseType_t xReturn;

    /* Check validity of vector number. */
    எனில்( ul_Vector_எண் >= port_இலக்கம்_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    இல்லையெனில் எனில்( ul_Vector_எண் < portAPIC_MIN_ALLOWABLE_VECTOR )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    இல்லையெனில் எனில்( ul_Vector_எண் == portAPIC_TIMER_INT_VECTOR )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    இல்லையெனில் எனில்( ul_Vector_எண் == portAPIC_YIELD_INT_VECTOR )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    இல்லையெனில் எனில்( ul_Vector_எண் == portAPIC_LVT_ERROR_VECTOR )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    இல்லையெனில் எனில்( ul_Vector_எண் == portAPIC_SPURIOUS_INT_VECTOR )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#எனில் ( configUSE_COMMON_INTERRUPT_ENTRY_POINT == 1 )
    இல்லையெனில் எனில்( xInterruptHandlerTable[ ul_Vector_எண் ] != வெற்று )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#endif  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    இல்லையெனில்
    {
        xReturn = pdPASS;
    }

    திரும்பு xReturn;
}
/*-----------------------------------------------------------*/

வெறுமை vGenerateYieldInterrupt( வெறுமை )
{
    __asm நிலையற்ற ( portYIELD_INTERRUPT );
}
