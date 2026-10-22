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

#إذا ( config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای
#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( config_ISR_ډېری_اندازه < ( config_اصغري_ډېری_اندازه * 2 ) )
    #warning config_ISR_ډېری_اندازه is probably too small!
#د_که_پای /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#إذا ( ( config_MAX_API_CALL_مداخله_لومړیتوب > پورټ_MAX_لومړیتوب ) || ( config_MAX_API_CALL_مداخله_لومړیتوب < 2 ) )
    #تېروتنه config_MAX_API_CALL_مداخله_لومړیتوب must be between 2 and 15
#د_که_پای

#إذا ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 0 ) )
    #تېروتنه config_SUPPORT_DYNAMIC_ویش must be سېټ منزل 1 منزل use this پورټ with an FPU
#د_که_پای

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کړه پورټ_NO_FLOATING_ټکی_CONTEXT    ( ( ډېری_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#تعریف_کړه پورټ_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#تعریف_کړه پورټ_APIC_LVT_ERROR_ویکټور        ( 0xfe )
#تعریف_کړه پورټ_APIC_SPURIOUS_INT_ویکټور     ( 0xff )

/* EFLAGS bits. */
#تعریف_کړه پورټ_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#تعریف_کړه پورټ_FPU_CONTEXT_اندازه_بایټونه       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#تعریف_کړه پورټ_EXPECTED_IDT_ثبت_اندازه      8

/* Default flags setting for entries in the IDT. */
#تعریف_کړه پورټ_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#تعریف_کړه پورټ_APIC_MIN_ALLOWABLE_ویکټور    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#تعریف_کړه پورټ_ډېری_کلمه                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Complete one descriptor in the IDT.
 */
ساكن فراغ prv_سېټ_مداخله_Gate( uint8_t uc_شمېره,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
خارجي فراغ v_پورټ_Central_مداخله_Wrapper( فراغ );

/*
 * Handler for portYIELD().
 */
خارجي فراغ v_پورټ_Yield_Call( فراغ );

/*
 * Configure the APIC to generate the RTOS tick.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/*
 * Tick interrupt handler.
 */
خارجي فراغ v_پورټ_Timer_Handler( فراغ );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
ساكن بنسټ_Type_t prv_Check_Validity_د_ویکټور_شمېره( uint32_t ul_ویکټور_شمېره );

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
    uint16_t us_جدول_حد;
    uint32_t ul_جدول_بنسټ; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
تعريفنوع بنية IDTPointer IDTPointer_t;

/* The IDT itself. */
ساكن __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_مداخله_Descriptor_جدول[ پورټ_عدد_VECTORS ];

#إذا ( config_USE_COMMON_مداخله_ثبت_ټکی == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
ساكن ISR_Handler_t x_مداخله_Handler_جدول[ پورټ_عدد_VECTORS ] = { عدم };

#د_که_پای /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#إذا ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_پورټ_Task_FPUContext_بفر __attribute__( ( کارول_شوی ) ) = pdFALSE;

#د_که_پای /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
ساكن uint32_t ul_System_ډېری[ config_ISR_ډېری_اندازه ] __attribute__( ( کارول_شوی ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
متطاير uint32_t ul_سر_د_System_ډېری __attribute__( ( کارول_شوی ) ) = ( uint32_t ) &( ul_System_ډېری[ config_ISR_ډېری_اندازه - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
متطاير uint32_t ul_پورټ_Yield_Pending __attribute__( ( کارول_شوی ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
متطاير uint32_t ul_مداخله_Nesting __attribute__( ( کارول_شوی ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    uint32_t ul_کوډ_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_سر_د_ډېری = 0x00;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x00;
    px_سر_د_ډېری--;

    /* Parameters first. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;
    px_سر_د_ډېری--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) prvTaskExitError;
    px_سر_د_ډېری--;

    /* iret used to start the task pops up to here. */
    *px_سر_د_ډېری = پورټ_INITIAL_EFLAGS;
    px_سر_د_ډېری--;

    /* CS */
    __asm متطاير ( "movl %%cs, %0" : "=r" ( ul_کوډ_Segment ) );
    *px_سر_د_ډېری = ul_کوډ_Segment;
    px_سر_د_ډېری--;

    /* First instruction in the task. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;
    px_سر_د_ډېری--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_سر_د_ډېری = 0xEA;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = 0xEC;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = 0xED1; /* EDX */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = 0xEB1; /* EBX */
    px_سر_د_ډېری--;

    /* Hole for ESP. */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = 0x00; /* EBP */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = 0xE5; /* ESI */
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = 0xeeeeeeee; /* EDI */

    #إذا ( configSUPPORT_FPU == 1 )
    {
        px_سر_د_ډېری--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_سر_د_ډېری = پورټ_NO_FLOATING_ټکی_CONTEXT;
    }
    #د_که_پای /* configSUPPORT_FPU */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سېټ_مداخله_Gate( uint8_t uc_شمېره,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_کوډ_Segment;
    uint32_t ul_بنسټ = ( uint32_t ) pxHandlerFunction;

    x_مداخله_Descriptor_جدول[ uc_شمېره ].usISRLow = ( uint16_t ) ( ul_بنسټ & USHRT_MAX );
    x_مداخله_Descriptor_جدول[ uc_شمېره ].usISRHigh = ( uint16_t ) ( ( ul_بنسټ >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm متطاير ( "mov %%cs, %0" : "=r" ( us_کوډ_Segment ) );
    x_مداخله_Descriptor_جدول[ uc_شمېره ].usSegmentSelector = us_کوډ_Segment;
    x_مداخله_Descriptor_جدول[ uc_شمېره ].ucZero = 0;
    x_مداخله_Descriptor_جدول[ uc_شمېره ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_تیاری_IDT( فراغ )
{
    uint32_t ul_عدد;
    IDTPointer_t xIDT;

    #إذا ( config_USE_COMMON_مداخله_ثبت_ټکی == 1 )
    {
        لكل( ul_عدد = 0; ul_عدد < پورټ_عدد_VECTORS; ul_عدد++ )
        {
            /* If a handler has not already been installed on this vector. */
            إذا( ( x_مداخله_Descriptor_جدول[ ul_عدد ].usISRLow == 0x00 ) && ( x_مداخله_Descriptor_جدول[ ul_عدد ].usISRHigh == 0x00 ) )
            {
                prv_سېټ_مداخله_Gate( ( uint8_t ) ul_عدد, v_پورټ_Central_مداخله_Wrapper, پورټ_IDT_FLAGS );
            }
        }
    }
    #د_که_پای /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_جدول_بنسټ = ( uint32_t ) x_مداخله_Descriptor_جدول;
    xIDT.us_جدول_حد = حجم( x_مداخله_Descriptor_جدول ) - 1;

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
    پورټ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    خارجي فراغ v_پورټ_APICError_Handler_Wrapper( فراغ );
    خارجي فراغ v_پورټ_APICSpurious_Handler( فراغ );

    /* Initialise LAPIC to a well known state. */
    پورټ_APIC_LDR = 0xFFFFFFFF;
    پورټ_APIC_LDR = ( ( پورټ_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    پورټ_APIC_LVT_TIMER = پورټ_APIC_DISABLE;
    پورټ_APIC_LVT_PERF = پورټ_APIC_NMI;
    پورټ_APIC_LVT_LINT0 = پورټ_APIC_DISABLE;
    پورټ_APIC_LVT_LINT1 = پورټ_APIC_DISABLE;
    پورټ_APIC_TASK_لومړیتوب = 0;

    /* Install APIC timer ISR vector. */
    prv_سېټ_مداخله_Gate( ( uint8_t ) پورټ_APIC_TIMER_INT_ویکټور, v_پورټ_Timer_Handler, پورټ_IDT_FLAGS );

    /* Install API error handler. */
    prv_سېټ_مداخله_Gate( ( uint8_t ) پورټ_APIC_LVT_ERROR_ویکټور, v_پورټ_APICError_Handler_Wrapper, پورټ_IDT_FLAGS );

    /* Install Yield handler. */
    prv_سېټ_مداخله_Gate( ( uint8_t ) پورټ_APIC_YIELD_INT_ویکټور, v_پورټ_Yield_Call, پورټ_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_سېټ_مداخله_Gate( ( uint8_t ) پورټ_APIC_SPURIOUS_INT_ویکټور, v_پورټ_APICSpurious_Handler, پورټ_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    پورټ_APIC_SPURIOUS_INT = پورټ_APIC_SPURIOUS_INT_ویکټور | پورټ_APIC_ENABLE_بټ;

    /* Set timer error vector. */
    پورټ_APIC_LVT_ERROR = پورټ_APIC_LVT_ERROR_ویکټور;

    /* Set the interrupt frequency. */
    پورټ_APIC_TMRDIV = پورټ_APIC_DIV_16;
    پورټ_APIC_TIMER_INITIAL_شمېر = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_شرح_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    بنسټ_Type_t x_کلمه;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( حجم( بنية IDTEntry ) == پورټ_EXPECTED_IDT_ثبت_اندازه );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    لكل( x_کلمه = 0; x_کلمه < config_ISR_ډېری_اندازه - 20; x_کلمه++ )
    {
        ul_System_ډېری[ x_کلمه ] = پورټ_ډېری_کلمه;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_پورټ_تیاری_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_تیاری_Timer_مداخله();

    /* Make sure the stack used by interrupts is aligned. */
    ul_سر_د_System_ډېری &= ~پورټ_BYTE_ALIGNMENT_ماسک;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    پورټ_APIC_LVT_TIMER = پورټ_APIC_TIMER_PERIODIC | پورټ_APIC_TIMER_INT_ویکټور;

    /* Sometimes needed. */
    پورټ_APIC_TMRDIV = پورټ_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_پورټ_پیل_لومړی_Task();

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0 )
    {
        #إذا ( config_MAX_API_CALL_مداخله_لومړیتوب == پورټ_MAX_لومړیتوب )
        {
            __asm متطاير ( "cli" );
        }
        #وإلا
        {
            پورټ_APIC_TASK_لومړیتوب = پورټ_MAX_API_CALL_لومړیتوب;
            configASSERT( پورټ_APIC_TASK_لومړیتوب == پورټ_MAX_API_CALL_لومړیتوب );
        }
        #د_که_پای
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورټ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورټ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #إذا ( config_MAX_API_CALL_مداخله_لومړیتوب == پورټ_MAX_لومړیتوب )
            {
                __asm متطاير ( "sti" );
            }
            #وإلا
            {
                پورټ_APIC_TASK_لومړیتوب = 0;
            }
            #د_که_پای

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            إذا( ul_پورټ_Yield_Pending != pdFALSE )
            {
                ul_پورټ_Yield_Pending = pdFALSE;
                __asm متطاير ( پورټ_YIELD_مداخله );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورټ_سېټ_مداخله_ماسک( فراغ )
{
    متطاير uint32_t ul_Original_ماسک;

    /* Set mask to max syscall priority. */
    #إذا ( config_MAX_API_CALL_مداخله_لومړیتوب == پورټ_MAX_لومړیتوب )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm متطاير ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_ماسک )::"memory" );

        ul_Original_ماسک &= پورټ_EFLAGS_IF;
    }
    #وإلا
    {
        /* Return original mask. */
        ul_Original_ماسک = پورټ_APIC_TASK_لومړیتوب;
        پورټ_APIC_TASK_لومړیتوب = پورټ_MAX_API_CALL_لومړیتوب;
        configASSERT( پورټ_APIC_TASK_لومړیتوب == پورټ_MAX_API_CALL_لومړیتوب );
    }
    #د_که_پای /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    أرجع ul_Original_ماسک;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک( uint32_t ul_New_ماسک_ارزښت )
{
    #إذا ( config_MAX_API_CALL_مداخله_لومړیتوب == پورټ_MAX_لومړیتوب )
    {
        إذا( ul_New_ماسک_ارزښت != pdFALSE )
        {
            __asm متطاير ( "sti" );
        }
    }
    #وإلا
    {
        پورټ_APIC_TASK_لومړیتوب = ul_New_ماسک_ارزښت;
        configASSERT( پورټ_APIC_TASK_لومړیتوب == ul_New_ماسک_ارزښت );
    }
    #د_که_پای /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#إذا ( configSUPPORT_FPU == 1 )

    فراغ v_پورټ_Task_کاروي_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_پورټ_Task_FPUContext_بفر = ( uint8_t * ) pv_پورټ_Malloc( پورټ_FPU_CONTEXT_اندازه_بایټونه );
        configASSERT( puc_پورټ_Task_FPUContext_بفر );

        /* Initialise the floating point registers. */
        __asm متطاير ( "fninit" );
    }

#د_که_پای /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

فراغ v_پورټ_APICError_Handler( فراغ )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    متطاير uint32_t ul_Error_حالت = 0;

    پورټ_APIC_ERROR_حالت = 0;
    ul_Error_حالت = پورټ_APIC_ERROR_حالت;
    ( فراغ ) ul_Error_حالت;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_مداخله_ثبت_ټکی == 1 )

    فراغ v_پورټ_Central_مداخله_Handler( uint32_t ul_ویکټور )
    {
        إذا( ul_ویکټور < پورټ_عدد_VECTORS )
        {
            إذا( x_مداخله_Handler_جدول[ ul_ویکټور ] != عدم )
            {
                ( x_مداخله_Handler_جدول[ ul_ویکټور ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_ډېری[ 10 ] == پورټ_ډېری_کلمه );
        configASSERT( ul_System_ډېری[ 12 ] == پورټ_ډېری_کلمه );
        configASSERT( ul_System_ډېری[ 14 ] == پورټ_ډېری_کلمه );
    }

#د_که_پای /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_مداخله_ثبت_ټکی == 1 )

    بنسټ_Type_t x_پورټ_ثبتوونکی_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_ویکټور_شمېره )
    {
        بنسټ_Type_t xReturn;

        xReturn = prv_Check_Validity_د_ویکټور_شمېره( ul_ویکټور_شمېره );

        إذا( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_مداخله_Handler_جدول[ ul_ویکټور_شمېره ] = pxHandler;
        }

        أرجع xReturn;
    }

#د_که_پای /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_Install_مداخله_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ویکټور_شمېره )
{
    بنسټ_Type_t xReturn;

    xReturn = prv_Check_Validity_د_ویکټور_شمېره( ul_ویکټور_شمېره );

    إذا( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_سېټ_مداخله_Gate( ( uint8_t ) ul_ویکټور_شمېره, ( ISR_Handler_t ) pxHandler, پورټ_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

ساكن بنسټ_Type_t prv_Check_Validity_د_ویکټور_شمېره( uint32_t ul_ویکټور_شمېره )
{
    بنسټ_Type_t xReturn;

    /* Check validity of vector number. */
    إذا( ul_ویکټور_شمېره >= پورټ_عدد_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ویکټور_شمېره < پورټ_APIC_MIN_ALLOWABLE_ویکټور )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ویکټور_شمېره == پورټ_APIC_TIMER_INT_ویکټور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ویکټور_شمېره == پورټ_APIC_YIELD_INT_ویکټور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ویکټور_شمېره == پورټ_APIC_LVT_ERROR_ویکټور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_ویکټور_شمېره == پورټ_APIC_SPURIOUS_INT_ویکټور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#إذا ( config_USE_COMMON_مداخله_ثبت_ټکی == 1 )
    وإلا إذا( x_مداخله_Handler_جدول[ ul_ویکټور_شمېره ] != عدم )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#د_که_پای  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    وإلا
    {
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

فراغ v_Generate_Yield_مداخله( فراغ )
{
    __asm متطاير ( پورټ_YIELD_مداخله );
}
