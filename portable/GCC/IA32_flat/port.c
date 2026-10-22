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
#ضمن <limits.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#إذا ( config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 difference priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( config_ISR_ڍير_سائيز < ( config_گهٽتر_ڍير_سائيز * 2 ) )
    #warning config_ISR_ڍير_سائيز is probably too small!
#جيڪڏهن_پورو /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#إذا ( ( config_MAX_API_CALL_مداخلت_ترجيح > پورٽ_MAX_ترجيح ) || ( config_MAX_API_CALL_مداخلت_ترجيح < 2 ) )
    #غلطي config_MAX_API_CALL_مداخلت_ترجيح must be between 2 and 15
#جيڪڏهن_پورو

#إذا ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 0 ) )
    #غلطي config_SUPPORT_DYNAMIC_ورهاست must be سيٽ منزل 1 منزل use this پورٽ with an FPU
#جيڪڏهن_پورو

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#وصف_ڪريو پورٽ_NO_FLOATING_نقطو_CONTEXT    ( ( ڍير_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#وصف_ڪريو پورٽ_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#وصف_ڪريو پورٽ_APIC_LVT_ERROR_ويڪٽر        ( 0xfe )
#وصف_ڪريو پورٽ_APIC_SPURIOUS_INT_ويڪٽر     ( 0xff )

/* EFLAGS bits. */
#وصف_ڪريو پورٽ_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#وصف_ڪريو پورٽ_FPU_CONTEXT_سائيز_بائيٽون       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#وصف_ڪريو پورٽ_EXPECTED_IDT_داخلا_سائيز      8

/* Default flags setting for entries in the IDT. */
#وصف_ڪريو پورٽ_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#وصف_ڪريو پورٽ_APIC_MIN_ALLOWABLE_ويڪٽر    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#وصف_ڪريو پورٽ_ڍير_لفظ                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Complete one descriptor in the IDT.
 */
ساكن فراغ prv_سيٽ_مداخلت_Gate( uint8_t uc_عدد,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
خارجي فراغ v_پورٽ_Central_مداخلت_Wrapper( فراغ );

/*
 * Handler for portYIELD().
 */
خارجي فراغ v_پورٽ_Yield_Call( فراغ );

/*
 * Configure the APIC to generate the RTOS tick.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*
 * Tick interrupt handler.
 */
خارجي فراغ v_پورٽ_Timer_Handler( فراغ );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
ساكن بنياد_Type_t prv_Check_Validity_جو_ويڪٽر_عدد( uint32_t ul_ويڪٽر_عدد );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable must be initialised to a non zero value to ensure interrupts don't
 * inadvertently become unmasked before the scheduler starts. It is set to zero
 * before the first task starts executing. */
متطاير uint32_t ulCriticalNesting = 9999UL;

/* A structure used to map the various fields of an IDT entry into separate
 * structure members. */
بنية IDTEntry
{
    uint16_t usISRLow;          /* Low 16 bits of handler address. */
    uint16_t usSegmentSelector; /* Flat model means this is not changed. */
    uint8_t ucZero;             /* Must be set to zero. */
    uint8_t ucFlags;            /* Flags for this entry. */
    uint16_t usISRHigh;         /* High 16 bits of handler address. */
}
__attribute__( ( packed ) );
تعريفنوع بنية IDTEntry IDTEntry_t;


/* Use to pass the location of the IDT to the CPU. */
بنية IDTPointer
{
    uint16_t us_جدول_حد_بندي;
    uint32_t ul_جدول_بنياد; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
تعريفنوع بنية IDTPointer IDTPointer_t;

/* The IDT itself. */
ساكن __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_مداخلت_Descriptor_جدول[ پورٽ_انگ_VECTORS ];

#إذا ( config_USE_COMMON_مداخلت_داخلا_نقطو == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
ساكن ISR_Handler_t x_مداخلت_Handler_جدول[ پورٽ_انگ_VECTORS ] = { عدم };

#جيڪڏهن_پورو /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#إذا ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_پورٽ_Task_FPUContext_بفر __attribute__( ( استعمال_ٿيل ) ) = pdFALSE;

#جيڪڏهن_پورو /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
ساكن uint32_t ul_System_ڍير[ config_ISR_ڍير_سائيز ] __attribute__( ( استعمال_ٿيل ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
متطاير uint32_t ul_چوٽي_جو_System_ڍير __attribute__( ( استعمال_ٿيل ) ) = ( uint32_t ) &( ul_System_ڍير[ config_ISR_ڍير_سائيز - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
متطاير uint32_t ul_پورٽ_Yield_Pending __attribute__( ( استعمال_ٿيل ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
متطاير uint32_t ul_مداخلت_Nesting __attribute__( ( استعمال_ٿيل ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    uint32_t ul_ڪوڊ_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_چوٽي_جو_ڍير = 0x00;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x00;
    px_چوٽي_جو_ڍير--;

    /* Parameters first. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;
    px_چوٽي_جو_ڍير--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) prvTaskExitError;
    px_چوٽي_جو_ڍير--;

    /* iret used to start the task pops up to here. */
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_EFLAGS;
    px_چوٽي_جو_ڍير--;

    /* CS */
    __asm متطاير ( "movl %%cs, %0" : "=r" ( ul_ڪوڊ_Segment ) );
    *px_چوٽي_جو_ڍير = ul_ڪوڊ_Segment;
    px_چوٽي_جو_ڍير--;

    /* First instruction in the task. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;
    px_چوٽي_جو_ڍير--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_چوٽي_جو_ڍير = 0xEA;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = 0xEC;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = 0xED1; /* EDX */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = 0xEB1; /* EBX */
    px_چوٽي_جو_ڍير--;

    /* Hole for ESP. */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = 0x00; /* EBP */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = 0xE5; /* ESI */
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = 0xeeeeeeee; /* EDI */

    #إذا ( configSUPPORT_FPU == 1 )
    {
        px_چوٽي_جو_ڍير--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_چوٽي_جو_ڍير = پورٽ_NO_FLOATING_نقطو_CONTEXT;
    }
    #جيڪڏهن_پورو /* configSUPPORT_FPU */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سيٽ_مداخلت_Gate( uint8_t uc_عدد,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_ڪوڊ_Segment;
    uint32_t ul_بنياد = ( uint32_t ) pxHandlerFunction;

    x_مداخلت_Descriptor_جدول[ uc_عدد ].usISRLow = ( uint16_t ) ( ul_بنياد & USHRT_MAX );
    x_مداخلت_Descriptor_جدول[ uc_عدد ].usISRHigh = ( uint16_t ) ( ( ul_بنياد >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm متطاير ( "mov %%cs, %0" : "=r" ( us_ڪوڊ_Segment ) );
    x_مداخلت_Descriptor_جدول[ uc_عدد ].usSegmentSelector = us_ڪوڊ_Segment;
    x_مداخلت_Descriptor_جدول[ uc_عدد ].ucZero = 0;
    x_مداخلت_Descriptor_جدول[ uc_عدد ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_تياري_IDT( فراغ )
{
    uint32_t ul_انگ;
    IDTPointer_t xIDT;

    #إذا ( config_USE_COMMON_مداخلت_داخلا_نقطو == 1 )
    {
        لكل( ul_انگ = 0; ul_انگ < پورٽ_انگ_VECTORS; ul_انگ++ )
        {
            /* If a handler has not already been installed on this vector. */
            إذا( ( x_مداخلت_Descriptor_جدول[ ul_انگ ].usISRLow == 0x00 ) && ( x_مداخلت_Descriptor_جدول[ ul_انگ ].usISRHigh == 0x00 ) )
            {
                prv_سيٽ_مداخلت_Gate( ( uint8_t ) ul_انگ, v_پورٽ_Central_مداخلت_Wrapper, پورٽ_IDT_FLAGS );
            }
        }
    }
    #جيڪڏهن_پورو /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_جدول_بنياد = ( uint32_t ) x_مداخلت_Descriptor_جدول;
    xIDT.us_جدول_حد_بندي = حجم( x_مداخلت_Descriptor_جدول ) - 1;

    /* Set IDT in CPU. */
    __asm متطاير ( "lidt %0" ::"m" ( xIDT ) );
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
    configASSERT( ulCriticalNesting == ~0UL );
    پورٽ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    خارجي فراغ v_پورٽ_APICError_Handler_Wrapper( فراغ );
    خارجي فراغ v_پورٽ_APICSpurious_Handler( فراغ );

    /* Initialise LAPIC to a well known state. */
    پورٽ_APIC_LDR = 0xFFFFFFFF;
    پورٽ_APIC_LDR = ( ( پورٽ_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    پورٽ_APIC_LVT_TIMER = پورٽ_APIC_DISABLE;
    پورٽ_APIC_LVT_PERF = پورٽ_APIC_NMI;
    پورٽ_APIC_LVT_LINT0 = پورٽ_APIC_DISABLE;
    پورٽ_APIC_LVT_LINT1 = پورٽ_APIC_DISABLE;
    پورٽ_APIC_TASK_ترجيح = 0;

    /* Install APIC timer ISR vector. */
    prv_سيٽ_مداخلت_Gate( ( uint8_t ) پورٽ_APIC_TIMER_INT_ويڪٽر, v_پورٽ_Timer_Handler, پورٽ_IDT_FLAGS );

    /* Install API error handler. */
    prv_سيٽ_مداخلت_Gate( ( uint8_t ) پورٽ_APIC_LVT_ERROR_ويڪٽر, v_پورٽ_APICError_Handler_Wrapper, پورٽ_IDT_FLAGS );

    /* Install Yield handler. */
    prv_سيٽ_مداخلت_Gate( ( uint8_t ) پورٽ_APIC_YIELD_INT_ويڪٽر, v_پورٽ_Yield_Call, پورٽ_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_سيٽ_مداخلت_Gate( ( uint8_t ) پورٽ_APIC_SPURIOUS_INT_ويڪٽر, v_پورٽ_APICSpurious_Handler, پورٽ_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    پورٽ_APIC_SPURIOUS_INT = پورٽ_APIC_SPURIOUS_INT_ويڪٽر | پورٽ_APIC_ENABLE_ٻٽو_انگ;

    /* Set timer error vector. */
    پورٽ_APIC_LVT_ERROR = پورٽ_APIC_LVT_ERROR_ويڪٽر;

    /* Set the interrupt frequency. */
    پورٽ_APIC_TMRDIV = پورٽ_APIC_DIV_16;
    پورٽ_APIC_TIMER_INITIAL_ڳڻپ = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_شرح_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    بنياد_Type_t x_لفظ;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( حجم( بنية IDTEntry ) == پورٽ_EXPECTED_IDT_داخلا_سائيز );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    لكل( x_لفظ = 0; x_لفظ < config_ISR_ڍير_سائيز - 20; x_لفظ++ )
    {
        ul_System_ڍير[ x_لفظ ] = پورٽ_ڍير_لفظ;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_پورٽ_تياري_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_تياري_Timer_مداخلت();

    /* Make sure the stack used by interrupts is aligned. */
    ul_چوٽي_جو_System_ڍير &= ~پورٽ_BYTE_ALIGNMENT_نقاب;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    پورٽ_APIC_LVT_TIMER = پورٽ_APIC_TIMER_PERIODIC | پورٽ_APIC_TIMER_INT_ويڪٽر;

    /* Sometimes needed. */
    پورٽ_APIC_TMRDIV = پورٽ_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_پورٽ_شروعات_پهريون_Task();

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0 )
    {
        #إذا ( config_MAX_API_CALL_مداخلت_ترجيح == پورٽ_MAX_ترجيح )
        {
            __asm متطاير ( "cli" );
        }
        #وإلا
        {
            پورٽ_APIC_TASK_ترجيح = پورٽ_MAX_API_CALL_ترجيح;
            configASSERT( پورٽ_APIC_TASK_ترجيح == پورٽ_MAX_API_CALL_ترجيح );
        }
        #جيڪڏهن_پورو
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #إذا ( config_MAX_API_CALL_مداخلت_ترجيح == پورٽ_MAX_ترجيح )
            {
                __asm متطاير ( "sti" );
            }
            #وإلا
            {
                پورٽ_APIC_TASK_ترجيح = 0;
            }
            #جيڪڏهن_پورو

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            إذا( ul_پورٽ_Yield_Pending != pdFALSE )
            {
                ul_پورٽ_Yield_Pending = pdFALSE;
                __asm متطاير ( پورٽ_YIELD_مداخلت );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٽ_سيٽ_مداخلت_نقاب( فراغ )
{
    متطاير uint32_t ul_Original_نقاب;

    /* Set mask to max syscall priority. */
    #إذا ( config_MAX_API_CALL_مداخلت_ترجيح == پورٽ_MAX_ترجيح )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm متطاير ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_نقاب )::"memory" );

        ul_Original_نقاب &= پورٽ_EFLAGS_IF;
    }
    #وإلا
    {
        /* Return original mask. */
        ul_Original_نقاب = پورٽ_APIC_TASK_ترجيح;
        پورٽ_APIC_TASK_ترجيح = پورٽ_MAX_API_CALL_ترجيح;
        configASSERT( پورٽ_APIC_TASK_ترجيح == پورٽ_MAX_API_CALL_ترجيح );
    }
    #جيڪڏهن_پورو /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    أرجع ul_Original_نقاب;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب( uint32_t ul_New_نقاب_قدر )
{
    #إذا ( config_MAX_API_CALL_مداخلت_ترجيح == پورٽ_MAX_ترجيح )
    {
        إذا( ul_New_نقاب_قدر != pdFALSE )
        {
            __asm متطاير ( "sti" );
        }
    }
    #وإلا
    {
        پورٽ_APIC_TASK_ترجيح = ul_New_نقاب_قدر;
        configASSERT( پورٽ_APIC_TASK_ترجيح == ul_New_نقاب_قدر );
    }
    #جيڪڏهن_پورو /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#إذا ( configSUPPORT_FPU == 1 )

    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_پورٽ_Task_FPUContext_بفر = ( uint8_t * ) pv_پورٽ_Malloc( پورٽ_FPU_CONTEXT_سائيز_بائيٽون );
        configASSERT( puc_پورٽ_Task_FPUContext_بفر );

        /* Initialise the floating point registers. */
        __asm متطاير ( "fninit" );
    }

#جيڪڏهن_پورو /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

فراغ v_پورٽ_APICError_Handler( فراغ )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    متطاير uint32_t ul_Error_حالت = 0;

    پورٽ_APIC_ERROR_حالت = 0;
    ul_Error_حالت = پورٽ_APIC_ERROR_حالت;
    ( فراغ ) ul_Error_حالت;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_مداخلت_داخلا_نقطو == 1 )

    فراغ v_پورٽ_Central_مداخلت_Handler( uint32_t ul_ويڪٽر )
    {
        إذا( ul_ويڪٽر < پورٽ_انگ_VECTORS )
        {
            إذا( x_مداخلت_Handler_جدول[ ul_ويڪٽر ] != عدم )
            {
                ( x_مداخلت_Handler_جدول[ ul_ويڪٽر ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_ڍير[ 10 ] == پورٽ_ڍير_لفظ );
        configASSERT( ul_System_ڍير[ 12 ] == پورٽ_ڍير_لفظ );
        configASSERT( ul_System_ڍير[ 14 ] == پورٽ_ڍير_لفظ );
    }

#جيڪڏهن_پورو /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_مداخلت_داخلا_نقطو == 1 )

    بنياد_Type_t x_پورٽ_رجسٽر_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_ويڪٽر_عدد )
    {
        بنياد_Type_t xReturn;

        xReturn = prv_Check_Validity_جو_ويڪٽر_عدد( ul_ويڪٽر_عدد );

        إذا( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_مداخلت_Handler_جدول[ ul_ويڪٽر_عدد ] = pxHandler;
        }

        أرجع xReturn;
    }

#جيڪڏهن_پورو /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_Install_مداخلت_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ويڪٽر_عدد )
{
    بنياد_Type_t xReturn;

    xReturn = prv_Check_Validity_جو_ويڪٽر_عدد( ul_ويڪٽر_عدد );

    إذا( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_سيٽ_مداخلت_Gate( ( uint8_t ) ul_ويڪٽر_عدد, ( ISR_Handler_t ) pxHandler, پورٽ_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

ساكن بنياد_Type_t prv_Check_Validity_جو_ويڪٽر_عدد( uint32_t ul_ويڪٽر_عدد )
{
    بنياد_Type_t xReturn;

    /* Check validity of vector number. */
    إذا( ul_ويڪٽر_عدد >= پورٽ_انگ_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ويڪٽر_عدد < پورٽ_APIC_MIN_ALLOWABLE_ويڪٽر )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ويڪٽر_عدد == پورٽ_APIC_TIMER_INT_ويڪٽر )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ويڪٽر_عدد == پورٽ_APIC_YIELD_INT_ويڪٽر )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ويڪٽر_عدد == پورٽ_APIC_LVT_ERROR_ويڪٽر )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ويڪٽر_عدد == پورٽ_APIC_SPURIOUS_INT_ويڪٽر )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#إذا ( config_USE_COMMON_مداخلت_داخلا_نقطو == 1 )
    وإلا إذا( x_مداخلت_Handler_جدول[ ul_ويڪٽر_عدد ] != عدم )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#جيڪڏهن_پورو  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    وإلا
    {
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

فراغ v_Generate_Yield_مداخلت( فراغ )
{
    __asm متطاير ( پورٽ_YIELD_مداخلت );
}
