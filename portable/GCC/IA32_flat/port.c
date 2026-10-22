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

#إذا ( config_USE_پورت_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر
#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( config_ISR_پشته_اندازه < ( config_کمینه_پشته_اندازه * 2 ) )
    #warning config_ISR_پشته_اندازه is probably too small!
#پایان_اگر /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#إذا ( ( config_MAX_API_CALL_وقفه_اولویت > پورت_MAX_اولویت ) || ( config_MAX_API_CALL_وقفه_اولویت < 2 ) )
    #خطا config_MAX_API_CALL_وقفه_اولویت must be between 2 and 15
#پایان_اگر

#إذا ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 0 ) )
    #خطا config_SUPPORT_DYNAMIC_تخصیص must be مجموعه مقصد 1 مقصد use this پورت with an FPU
#پایان_اگر

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کن پورت_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کن پورت_NO_FLOATING_نقطه_CONTEXT    ( ( پشته_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#تعریف_کن پورت_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#تعریف_کن پورت_APIC_LVT_ERROR_وکتور        ( 0xfe )
#تعریف_کن پورت_APIC_SPURIOUS_INT_وکتور     ( 0xff )

/* EFLAGS bits. */
#تعریف_کن پورت_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#تعریف_کن پورت_FPU_CONTEXT_اندازه_بایتها       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#تعریف_کن پورت_EXPECTED_IDT_مدخل_اندازه      8

/* Default flags setting for entries in the IDT. */
#تعریف_کن پورت_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#تعریف_کن پورت_APIC_MIN_ALLOWABLE_وکتور    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#تعریف_کن پورت_پشته_کلمه                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
خارجي فراغ v_پورت_شروع_اولی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Complete one descriptor in the IDT.
 */
ساكن فراغ prv_مجموعه_وقفه_Gate( uint8_t uc_عدد,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
خارجي فراغ v_پورت_Central_وقفه_Wrapper( فراغ );

/*
 * Handler for portYIELD().
 */
خارجي فراغ v_پورت_Yield_Call( فراغ );

/*
 * Configure the APIC to generate the RTOS tick.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

/*
 * Tick interrupt handler.
 */
خارجي فراغ v_پورت_Timer_Handler( فراغ );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
ساكن پایه_Type_t prv_Check_Validity_از_وکتور_عدد( uint32_t ul_وکتور_عدد );

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
    uint32_t ul_جدول_پایه; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
تعريفنوع بنية IDTPointer IDTPointer_t;

/* The IDT itself. */
ساكن __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_وقفه_Descriptor_جدول[ پورت_رقم_VECTORS ];

#إذا ( config_USE_COMMON_وقفه_مدخل_نقطه == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
ساكن ISR_Handler_t x_وقفه_Handler_جدول[ پورت_رقم_VECTORS ] = { عدم };

#پایان_اگر /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#إذا ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_پورت_Task_FPUContext_میانگیر __attribute__( ( استفاده_شده ) ) = pdFALSE;

#پایان_اگر /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
ساكن uint32_t ul_System_پشته[ config_ISR_پشته_اندازه ] __attribute__( ( استفاده_شده ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
متطاير uint32_t ul_بالاترین_از_System_پشته __attribute__( ( استفاده_شده ) ) = ( uint32_t ) &( ul_System_پشته[ config_ISR_پشته_اندازه - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
متطاير uint32_t ul_پورت_Yield_Pending __attribute__( ( استفاده_شده ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
متطاير uint32_t ul_وقفه_Nesting __attribute__( ( استفاده_شده ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    uint32_t ul_کد_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_بالاترین_از_پشته = 0x00;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = 0x00;
    px_بالاترین_از_پشته--;

    /* Parameters first. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;
    px_بالاترین_از_پشته--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) prvTaskExitError;
    px_بالاترین_از_پشته--;

    /* iret used to start the task pops up to here. */
    *px_بالاترین_از_پشته = پورت_INITIAL_EFLAGS;
    px_بالاترین_از_پشته--;

    /* CS */
    __asm متطاير ( "movl %%cs, %0" : "=r" ( ul_کد_Segment ) );
    *px_بالاترین_از_پشته = ul_کد_Segment;
    px_بالاترین_از_پشته--;

    /* First instruction in the task. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;
    px_بالاترین_از_پشته--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_بالاترین_از_پشته = 0xEA;
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = 0xEC;
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = 0xED1; /* EDX */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = 0xEB1; /* EBX */
    px_بالاترین_از_پشته--;

    /* Hole for ESP. */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = 0x00; /* EBP */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = 0xE5; /* ESI */
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = 0xeeeeeeee; /* EDI */

    #إذا ( configSUPPORT_FPU == 1 )
    {
        px_بالاترین_از_پشته--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_بالاترین_از_پشته = پورت_NO_FLOATING_نقطه_CONTEXT;
    }
    #پایان_اگر /* configSUPPORT_FPU */

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_مجموعه_وقفه_Gate( uint8_t uc_عدد,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_کد_Segment;
    uint32_t ul_پایه = ( uint32_t ) pxHandlerFunction;

    x_وقفه_Descriptor_جدول[ uc_عدد ].usISRLow = ( uint16_t ) ( ul_پایه & USHRT_MAX );
    x_وقفه_Descriptor_جدول[ uc_عدد ].usISRHigh = ( uint16_t ) ( ( ul_پایه >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm متطاير ( "mov %%cs, %0" : "=r" ( us_کد_Segment ) );
    x_وقفه_Descriptor_جدول[ uc_عدد ].usSegmentSelector = us_کد_Segment;
    x_وقفه_Descriptor_جدول[ uc_عدد ].ucZero = 0;
    x_وقفه_Descriptor_جدول[ uc_عدد ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_راهاندازی_IDT( فراغ )
{
    uint32_t ul_رقم;
    IDTPointer_t xIDT;

    #إذا ( config_USE_COMMON_وقفه_مدخل_نقطه == 1 )
    {
        لكل( ul_رقم = 0; ul_رقم < پورت_رقم_VECTORS; ul_رقم++ )
        {
            /* If a handler has not already been installed on this vector. */
            إذا( ( x_وقفه_Descriptor_جدول[ ul_رقم ].usISRLow == 0x00 ) && ( x_وقفه_Descriptor_جدول[ ul_رقم ].usISRHigh == 0x00 ) )
            {
                prv_مجموعه_وقفه_Gate( ( uint8_t ) ul_رقم, v_پورت_Central_وقفه_Wrapper, پورت_IDT_FLAGS );
            }
        }
    }
    #پایان_اگر /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_جدول_پایه = ( uint32_t ) x_وقفه_Descriptor_جدول;
    xIDT.us_جدول_حد = حجم( x_وقفه_Descriptor_جدول ) - 1;

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
    پورت_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    خارجي فراغ v_پورت_APICError_Handler_Wrapper( فراغ );
    خارجي فراغ v_پورت_APICSpurious_Handler( فراغ );

    /* Initialise LAPIC to a well known state. */
    پورت_APIC_LDR = 0xFFFFFFFF;
    پورت_APIC_LDR = ( ( پورت_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    پورت_APIC_LVT_TIMER = پورت_APIC_DISABLE;
    پورت_APIC_LVT_PERF = پورت_APIC_NMI;
    پورت_APIC_LVT_LINT0 = پورت_APIC_DISABLE;
    پورت_APIC_LVT_LINT1 = پورت_APIC_DISABLE;
    پورت_APIC_TASK_اولویت = 0;

    /* Install APIC timer ISR vector. */
    prv_مجموعه_وقفه_Gate( ( uint8_t ) پورت_APIC_TIMER_INT_وکتور, v_پورت_Timer_Handler, پورت_IDT_FLAGS );

    /* Install API error handler. */
    prv_مجموعه_وقفه_Gate( ( uint8_t ) پورت_APIC_LVT_ERROR_وکتور, v_پورت_APICError_Handler_Wrapper, پورت_IDT_FLAGS );

    /* Install Yield handler. */
    prv_مجموعه_وقفه_Gate( ( uint8_t ) پورت_APIC_YIELD_INT_وکتور, v_پورت_Yield_Call, پورت_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_مجموعه_وقفه_Gate( ( uint8_t ) پورت_APIC_SPURIOUS_INT_وکتور, v_پورت_APICSpurious_Handler, پورت_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    پورت_APIC_SPURIOUS_INT = پورت_APIC_SPURIOUS_INT_وکتور | پورت_APIC_ENABLE_بیت;

    /* Set timer error vector. */
    پورت_APIC_LVT_ERROR = پورت_APIC_LVT_ERROR_وکتور;

    /* Set the interrupt frequency. */
    پورت_APIC_TMRDIV = پورت_APIC_DIV_16;
    پورت_APIC_TIMER_INITIAL_شمار = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_نرخ_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    پایه_Type_t x_کلمه;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( حجم( بنية IDTEntry ) == پورت_EXPECTED_IDT_مدخل_اندازه );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    لكل( x_کلمه = 0; x_کلمه < config_ISR_پشته_اندازه - 20; x_کلمه++ )
    {
        ul_System_پشته[ x_کلمه ] = پورت_پشته_کلمه;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_پورت_راهاندازی_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_راهاندازی_Timer_وقفه();

    /* Make sure the stack used by interrupts is aligned. */
    ul_بالاترین_از_System_پشته &= ~پورت_BYTE_ALIGNMENT_ماسک;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    پورت_APIC_LVT_TIMER = پورت_APIC_TIMER_PERIODIC | پورت_APIC_TIMER_INT_وکتور;

    /* Sometimes needed. */
    پورت_APIC_TMRDIV = پورت_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_پورت_شروع_اولی_Task();

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0 )
    {
        #إذا ( config_MAX_API_CALL_وقفه_اولویت == پورت_MAX_اولویت )
        {
            __asm متطاير ( "cli" );
        }
        #وإلا
        {
            پورت_APIC_TASK_اولویت = پورت_MAX_API_CALL_اولویت;
            configASSERT( پورت_APIC_TASK_اولویت == پورت_MAX_API_CALL_اولویت );
        }
        #پایان_اگر
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورت_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورت_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #إذا ( config_MAX_API_CALL_وقفه_اولویت == پورت_MAX_اولویت )
            {
                __asm متطاير ( "sti" );
            }
            #وإلا
            {
                پورت_APIC_TASK_اولویت = 0;
            }
            #پایان_اگر

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            إذا( ul_پورت_Yield_Pending != pdFALSE )
            {
                ul_پورت_Yield_Pending = pdFALSE;
                __asm متطاير ( پورت_YIELD_وقفه );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورت_مجموعه_وقفه_ماسک( فراغ )
{
    متطاير uint32_t ul_Original_ماسک;

    /* Set mask to max syscall priority. */
    #إذا ( config_MAX_API_CALL_وقفه_اولویت == پورت_MAX_اولویت )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm متطاير ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_ماسک )::"memory" );

        ul_Original_ماسک &= پورت_EFLAGS_IF;
    }
    #وإلا
    {
        /* Return original mask. */
        ul_Original_ماسک = پورت_APIC_TASK_اولویت;
        پورت_APIC_TASK_اولویت = پورت_MAX_API_CALL_اولویت;
        configASSERT( پورت_APIC_TASK_اولویت == پورت_MAX_API_CALL_اولویت );
    }
    #پایان_اگر /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    أرجع ul_Original_ماسک;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Clear_وقفه_ماسک( uint32_t ul_New_ماسک_مقدار )
{
    #إذا ( config_MAX_API_CALL_وقفه_اولویت == پورت_MAX_اولویت )
    {
        إذا( ul_New_ماسک_مقدار != pdFALSE )
        {
            __asm متطاير ( "sti" );
        }
    }
    #وإلا
    {
        پورت_APIC_TASK_اولویت = ul_New_ماسک_مقدار;
        configASSERT( پورت_APIC_TASK_اولویت == ul_New_ماسک_مقدار );
    }
    #پایان_اگر /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#إذا ( configSUPPORT_FPU == 1 )

    فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_پورت_Task_FPUContext_میانگیر = ( uint8_t * ) pv_پورت_Malloc( پورت_FPU_CONTEXT_اندازه_بایتها );
        configASSERT( puc_پورت_Task_FPUContext_میانگیر );

        /* Initialise the floating point registers. */
        __asm متطاير ( "fninit" );
    }

#پایان_اگر /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

فراغ v_پورت_APICError_Handler( فراغ )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    متطاير uint32_t ul_Error_وضعیت = 0;

    پورت_APIC_ERROR_وضعیت = 0;
    ul_Error_وضعیت = پورت_APIC_ERROR_وضعیت;
    ( فراغ ) ul_Error_وضعیت;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_وقفه_مدخل_نقطه == 1 )

    فراغ v_پورت_Central_وقفه_Handler( uint32_t ul_وکتور )
    {
        إذا( ul_وکتور < پورت_رقم_VECTORS )
        {
            إذا( x_وقفه_Handler_جدول[ ul_وکتور ] != عدم )
            {
                ( x_وقفه_Handler_جدول[ ul_وکتور ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_پشته[ 10 ] == پورت_پشته_کلمه );
        configASSERT( ul_System_پشته[ 12 ] == پورت_پشته_کلمه );
        configASSERT( ul_System_پشته[ 14 ] == پورت_پشته_کلمه );
    }

#پایان_اگر /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_وقفه_مدخل_نقطه == 1 )

    پایه_Type_t x_پورت_ثبات_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_وکتور_عدد )
    {
        پایه_Type_t xReturn;

        xReturn = prv_Check_Validity_از_وکتور_عدد( ul_وکتور_عدد );

        إذا( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_وقفه_Handler_جدول[ ul_وکتور_عدد ] = pxHandler;
        }

        أرجع xReturn;
    }

#پایان_اگر /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_Install_وقفه_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_وکتور_عدد )
{
    پایه_Type_t xReturn;

    xReturn = prv_Check_Validity_از_وکتور_عدد( ul_وکتور_عدد );

    إذا( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_مجموعه_وقفه_Gate( ( uint8_t ) ul_وکتور_عدد, ( ISR_Handler_t ) pxHandler, پورت_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

ساكن پایه_Type_t prv_Check_Validity_از_وکتور_عدد( uint32_t ul_وکتور_عدد )
{
    پایه_Type_t xReturn;

    /* Check validity of vector number. */
    إذا( ul_وکتور_عدد >= پورت_رقم_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_وکتور_عدد < پورت_APIC_MIN_ALLOWABLE_وکتور )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_وکتور_عدد == پورت_APIC_TIMER_INT_وکتور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_وکتور_عدد == پورت_APIC_YIELD_INT_وکتور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_وکتور_عدد == پورت_APIC_LVT_ERROR_وکتور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_وکتور_عدد == پورت_APIC_SPURIOUS_INT_وکتور )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#إذا ( config_USE_COMMON_وقفه_مدخل_نقطه == 1 )
    وإلا إذا( x_وقفه_Handler_جدول[ ul_وکتور_عدد ] != عدم )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#پایان_اگر  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    وإلا
    {
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

فراغ v_Generate_Yield_وقفه( فراغ )
{
    __asm متطاير ( پورت_YIELD_وقفه );
}
