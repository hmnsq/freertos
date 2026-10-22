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

#إذا ( config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1 )
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت
#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( config_ISR_ڈھیر_ناپ < ( config_اقل_ڈھیر_ناپ * 2 ) )
    #warning config_ISR_ڈھیر_ناپ is probably too small!
#جے_انت /* ( configISR_STACK_SIZE < configMINIMAL_STACK_SIZE * 2 ) */

#إذا ( ( config_MAX_API_CALL_رکاوٹ_ترجیح > پورٹ_MAX_ترجیح ) || ( config_MAX_API_CALL_رکاوٹ_ترجیح < 2 ) )
    #غلطی config_MAX_API_CALL_رکاوٹ_ترجیح must be between 2 and 15
#جے_انت

#إذا ( ( configSUPPORT_FPU == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 0 ) )
    #غلطی config_SUPPORT_DYNAMIC_ونڈ must be سیٹ منزل 1 منزل use this پورٹ with an FPU
#جے_انت

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#تعریف_کرو پورٹ_NO_FLOATING_نقطہ_CONTEXT    ( ( ڈھیر_Type_t ) 0 )

/* Only the IF bit is set so tasks start with interrupts enabled. */
#تعریف_کرو پورٹ_INITIAL_EFLAGS               ( 0x200UL )

/* Error interrupts are at the highest priority vectors. */
#تعریف_کرو پورٹ_APIC_LVT_ERROR_سمتیہ        ( 0xfe )
#تعریف_کرو پورٹ_APIC_SPURIOUS_INT_سمتیہ     ( 0xff )

/* EFLAGS bits. */
#تعریف_کرو پورٹ_EFLAGS_IF                    ( 0x200UL )

/* FPU context size if FSAVE is used. */
#تعریف_کرو پورٹ_FPU_CONTEXT_ناپ_بائٹاں       108

/* The expected size of each entry in the IDT.  Used to check structure packing
 * is set correctly. */
#تعریف_کرو پورٹ_EXPECTED_IDT_اندراج_ناپ      8

/* Default flags setting for entries in the IDT. */
#تعریف_کرو پورٹ_IDT_FLAGS                    ( 0x8E )

/* This is the lowest possible ISR vector available to application code. */
#تعریف_کرو پورٹ_APIC_MIN_ALLOWABLE_سمتیہ    ( 0x20 )

/* If configASSERT() is defined then the system stack is filled with this value
 * to allow for a crude stack overflow check. */
#تعریف_کرو پورٹ_ڈھیر_لفظ                   ( 0xecececec )
/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.
 */
خارجي فراغ v_پورٹ_شروع_پہلا_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Complete one descriptor in the IDT.
 */
ساكن فراغ prv_سیٹ_رکاوٹ_Gate( uint8_t uc_نمبر,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags );

/*
 * The default handler installed in each IDT position.
 */
خارجي فراغ v_پورٹ_Central_رکاوٹ_Wrapper( فراغ );

/*
 * Handler for portYIELD().
 */
خارجي فراغ v_پورٹ_Yield_Call( فراغ );

/*
 * Configure the APIC to generate the RTOS tick.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/*
 * Tick interrupt handler.
 */
خارجي فراغ v_پورٹ_Timer_Handler( فراغ );

/*
 * Check an interrupt vector is not too high, too low, in use by FreeRTOS, or
 * already in use by the application.
 */
ساكن ادھار_Type_t prv_Check_Validity_دا_سمتیہ_نمبر( uint32_t ul_سمتیہ_نمبر );

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
    uint16_t us_جدول_حد_بندی;
    uint32_t ul_جدول_ادھار; /* The address of the first entry in xInterruptDescriptorTable. */
}
__attribute__( ( __packed__ ) );
تعريفنوع بنية IDTPointer IDTPointer_t;

/* The IDT itself. */
ساكن __attribute__( ( aligned( 32 ) ) ) IDTEntry_t x_رکاوٹ_Descriptor_جدول[ پورٹ_عدد_VECTORS ];

#إذا ( config_USE_COMMON_رکاوٹ_اندراج_نقطہ == 1 )

/* A table in which application defined interrupt handlers are stored.  These
 * are called by the central interrupt handler if a common interrupt entry
 * point it used. */
ساكن ISR_Handler_t x_رکاوٹ_Handler_جدول[ پورٹ_عدد_VECTORS ] = { عدم };

#جے_انت /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

#إذا ( configSUPPORT_FPU == 1 )

/* Saved as part of the task context.  If pucPortTaskFPUContextBuffer is NULL
 * then the task does not have an FPU context.  If pucPortTaskFPUContextBuffer is
 * not NULL then it points to a buffer into which the FPU context can be saved. */
    uint8_t * puc_پورٹ_Task_FPUContext_بفر __attribute__( ( ورتیا ) ) = pdFALSE;

#جے_انت /* configSUPPORT_FPU */

/* The stack used by interrupt handlers. */
ساكن uint32_t ul_System_ڈھیر[ config_ISR_ڈھیر_ناپ ] __attribute__( ( ورتیا ) ) = { 0 };

/* Don't use the very top of the system stack so the return address
 * appears as 0 if the debugger tries to unwind the stack. */
متطاير uint32_t ul_چوٹی_دا_System_ڈھیر __attribute__( ( ورتیا ) ) = ( uint32_t ) &( ul_System_ڈھیر[ config_ISR_ڈھیر_ناپ - 5 ] );

/* If a yield is requested from an interrupt or from a critical section then
 * the yield is not performed immediately, and ulPortYieldPending is set to pdTRUE
 * instead to indicate the yield should be performed at the end of the interrupt
 * when the critical section is exited. */
متطاير uint32_t ul_پورٹ_Yield_Pending __attribute__( ( ورتیا ) ) = pdFALSE;

/* Counts the interrupt nesting depth.  Used to know when to switch to the
 * interrupt/system stack and when to save/restore a complete context. */
متطاير uint32_t ul_رکاوٹ_Nesting __attribute__( ( ورتیا ) ) = 0;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    uint32_t ul_کوڈ_Segment;

    /* Setup the initial stack as expected by the portFREERTOS_INTERRUPT_EXIT macro. */

    *px_چوٹی_دا_ڈھیر = 0x00;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x00;
    px_چوٹی_دا_ڈھیر--;

    /* Parameters first. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
    px_چوٹی_دا_ڈھیر--;

    /* There is nothing to return to so assert if attempting to use the return
     * address. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) prvTaskExitError;
    px_چوٹی_دا_ڈھیر--;

    /* iret used to start the task pops up to here. */
    *px_چوٹی_دا_ڈھیر = پورٹ_INITIAL_EFLAGS;
    px_چوٹی_دا_ڈھیر--;

    /* CS */
    __asm متطاير ( "movl %%cs, %0" : "=r" ( ul_کوڈ_Segment ) );
    *px_چوٹی_دا_ڈھیر = ul_کوڈ_Segment;
    px_چوٹی_دا_ڈھیر--;

    /* First instruction in the task. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;
    px_چوٹی_دا_ڈھیر--;

    /* General purpose registers as expected by a POPA instruction. */
    *px_چوٹی_دا_ڈھیر = 0xEA;
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = 0xEC;
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = 0xED1; /* EDX */
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = 0xEB1; /* EBX */
    px_چوٹی_دا_ڈھیر--;

    /* Hole for ESP. */
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = 0x00; /* EBP */
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = 0xE5; /* ESI */
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = 0xeeeeeeee; /* EDI */

    #إذا ( configSUPPORT_FPU == 1 )
    {
        px_چوٹی_دا_ڈھیر--;

        /* Buffer for FPU context, which is initialised to NULL as tasks are not
         * created with an FPU context. */
        *px_چوٹی_دا_ڈھیر = پورٹ_NO_FLOATING_نقطہ_CONTEXT;
    }
    #جے_انت /* configSUPPORT_FPU */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سیٹ_رکاوٹ_Gate( uint8_t uc_نمبر,
                                 ISR_Handler_t pxHandlerFunction,
                                 uint8_t ucFlags )
{
    uint16_t us_کوڈ_Segment;
    uint32_t ul_ادھار = ( uint32_t ) pxHandlerFunction;

    x_رکاوٹ_Descriptor_جدول[ uc_نمبر ].usISRLow = ( uint16_t ) ( ul_ادھار & USHRT_MAX );
    x_رکاوٹ_Descriptor_جدول[ uc_نمبر ].usISRHigh = ( uint16_t ) ( ( ul_ادھار >> 16UL ) & USHRT_MAX );

    /* When the flat model is used the CS will never change. */
    __asm متطاير ( "mov %%cs, %0" : "=r" ( us_کوڈ_Segment ) );
    x_رکاوٹ_Descriptor_جدول[ uc_نمبر ].usSegmentSelector = us_کوڈ_Segment;
    x_رکاوٹ_Descriptor_جدول[ uc_نمبر ].ucZero = 0;
    x_رکاوٹ_Descriptor_جدول[ uc_نمبر ].ucFlags = ucFlags;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_تیاری_IDT( فراغ )
{
    uint32_t ul_عدد;
    IDTPointer_t xIDT;

    #إذا ( config_USE_COMMON_رکاوٹ_اندراج_نقطہ == 1 )
    {
        لكل( ul_عدد = 0; ul_عدد < پورٹ_عدد_VECTORS; ul_عدد++ )
        {
            /* If a handler has not already been installed on this vector. */
            إذا( ( x_رکاوٹ_Descriptor_جدول[ ul_عدد ].usISRLow == 0x00 ) && ( x_رکاوٹ_Descriptor_جدول[ ul_عدد ].usISRHigh == 0x00 ) )
            {
                prv_سیٹ_رکاوٹ_Gate( ( uint8_t ) ul_عدد, v_پورٹ_Central_رکاوٹ_Wrapper, پورٹ_IDT_FLAGS );
            }
        }
    }
    #جے_انت /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */

    /* Set IDT address. */
    xIDT.ul_جدول_ادھار = ( uint32_t ) x_رکاوٹ_Descriptor_جدول;
    xIDT.us_جدول_حد_بندی = حجم( x_رکاوٹ_Descriptor_جدول ) - 1;

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
    پورٹ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    خارجي فراغ v_پورٹ_APICError_Handler_Wrapper( فراغ );
    خارجي فراغ v_پورٹ_APICSpurious_Handler( فراغ );

    /* Initialise LAPIC to a well known state. */
    پورٹ_APIC_LDR = 0xFFFFFFFF;
    پورٹ_APIC_LDR = ( ( پورٹ_APIC_LDR & 0x00FFFFFF ) | 0x00000001 );
    پورٹ_APIC_LVT_TIMER = پورٹ_APIC_DISABLE;
    پورٹ_APIC_LVT_PERF = پورٹ_APIC_NMI;
    پورٹ_APIC_LVT_LINT0 = پورٹ_APIC_DISABLE;
    پورٹ_APIC_LVT_LINT1 = پورٹ_APIC_DISABLE;
    پورٹ_APIC_TASK_ترجیح = 0;

    /* Install APIC timer ISR vector. */
    prv_سیٹ_رکاوٹ_Gate( ( uint8_t ) پورٹ_APIC_TIMER_INT_سمتیہ, v_پورٹ_Timer_Handler, پورٹ_IDT_FLAGS );

    /* Install API error handler. */
    prv_سیٹ_رکاوٹ_Gate( ( uint8_t ) پورٹ_APIC_LVT_ERROR_سمتیہ, v_پورٹ_APICError_Handler_Wrapper, پورٹ_IDT_FLAGS );

    /* Install Yield handler. */
    prv_سیٹ_رکاوٹ_Gate( ( uint8_t ) پورٹ_APIC_YIELD_INT_سمتیہ, v_پورٹ_Yield_Call, پورٹ_IDT_FLAGS );

    /* Install spurious interrupt vector. */
    prv_سیٹ_رکاوٹ_Gate( ( uint8_t ) پورٹ_APIC_SPURIOUS_INT_سمتیہ, v_پورٹ_APICSpurious_Handler, پورٹ_IDT_FLAGS );

    /* Enable the APIC, mapping the spurious interrupt at the same time. */
    پورٹ_APIC_SPURIOUS_INT = پورٹ_APIC_SPURIOUS_INT_سمتیہ | پورٹ_APIC_ENABLE_ثنائی_ہندسہ;

    /* Set timer error vector. */
    پورٹ_APIC_LVT_ERROR = پورٹ_APIC_LVT_ERROR_سمتیہ;

    /* Set the interrupt frequency. */
    پورٹ_APIC_TMRDIV = پورٹ_APIC_DIV_16;
    پورٹ_APIC_TIMER_INITIAL_گنتی = ( ( configCPU_CLOCK_HZ >> 4UL ) / config_TICK_شرح_HZ ) - 1UL;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    ادھار_Type_t x_لفظ;

    /* Some versions of GCC require the -mno-ms-bitfields command line option
     * for packing to work. */
    configASSERT( حجم( بنية IDTEntry ) == پورٹ_EXPECTED_IDT_اندراج_ناپ );

    /* Fill part of the system stack with a known value to help detect stack
     * overflow.  A few zeros are left so GDB doesn't get confused unwinding
     * the stack. */
    لكل( x_لفظ = 0; x_لفظ < config_ISR_ڈھیر_ناپ - 20; x_لفظ++ )
    {
        ul_System_ڈھیر[ x_لفظ ] = پورٹ_ڈھیر_لفظ;
    }

    /* Initialise Interrupt Descriptor Table (IDT). */
    v_پورٹ_تیاری_IDT();

    /* Initialise LAPIC and install system handlers. */
    prv_تیاری_Timer_رکاوٹ();

    /* Make sure the stack used by interrupts is aligned. */
    ul_چوٹی_دا_System_ڈھیر &= ~پورٹ_BYTE_ALIGNMENT_نقاب;

    ulCriticalNesting = 0;

    /* Enable LAPIC Counter.*/
    پورٹ_APIC_LVT_TIMER = پورٹ_APIC_TIMER_PERIODIC | پورٹ_APIC_TIMER_INT_سمتیہ;

    /* Sometimes needed. */
    پورٹ_APIC_TMRDIV = پورٹ_APIC_DIV_16;

    /* Should not return from the following function as the scheduler will then
     * be executing the tasks. */
    v_پورٹ_شروع_پہلا_Task();

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0 )
    {
        #إذا ( config_MAX_API_CALL_رکاوٹ_ترجیح == پورٹ_MAX_ترجیح )
        {
            __asm متطاير ( "cli" );
        }
        #وإلا
        {
            پورٹ_APIC_TASK_ترجیح = پورٹ_MAX_API_CALL_ترجیح;
            configASSERT( پورٹ_APIC_TASK_ترجیح == پورٹ_MAX_API_CALL_ترجیح );
        }
        #جے_انت
    }

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            #إذا ( config_MAX_API_CALL_رکاوٹ_ترجیح == پورٹ_MAX_ترجیح )
            {
                __asm متطاير ( "sti" );
            }
            #وإلا
            {
                پورٹ_APIC_TASK_ترجیح = 0;
            }
            #جے_انت

            /* If a yield was pended from within the critical section then
             * perform the yield now. */
            إذا( ul_پورٹ_Yield_Pending != pdFALSE )
            {
                ul_پورٹ_Yield_Pending = pdFALSE;
                __asm متطاير ( پورٹ_YIELD_رکاوٹ );
            }
        }
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٹ_سیٹ_رکاوٹ_نقاب( فراغ )
{
    متطاير uint32_t ul_Original_نقاب;

    /* Set mask to max syscall priority. */
    #إذا ( config_MAX_API_CALL_رکاوٹ_ترجیح == پورٹ_MAX_ترجیح )
    {
        /* Return whether interrupts were already enabled or not.  Pop adjusts
         * the stack first. */
        __asm متطاير ( "pushf      \t\n"
                         "pop %0     \t\n"
                         "cli            "
                         : "=rm" ( ul_Original_نقاب )::"memory" );

        ul_Original_نقاب &= پورٹ_EFLAGS_IF;
    }
    #وإلا
    {
        /* Return original mask. */
        ul_Original_نقاب = پورٹ_APIC_TASK_ترجیح;
        پورٹ_APIC_TASK_ترجیح = پورٹ_MAX_API_CALL_ترجیح;
        configASSERT( پورٹ_APIC_TASK_ترجیح == پورٹ_MAX_API_CALL_ترجیح );
    }
    #جے_انت /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */

    أرجع ul_Original_نقاب;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Clear_رکاوٹ_نقاب( uint32_t ul_New_نقاب_قدر )
{
    #إذا ( config_MAX_API_CALL_رکاوٹ_ترجیح == پورٹ_MAX_ترجیح )
    {
        إذا( ul_New_نقاب_قدر != pdFALSE )
        {
            __asm متطاير ( "sti" );
        }
    }
    #وإلا
    {
        پورٹ_APIC_TASK_ترجیح = ul_New_نقاب_قدر;
        configASSERT( پورٹ_APIC_TASK_ترجیح == ul_New_نقاب_قدر );
    }
    #جے_انت /* if ( configMAX_API_CALL_INTERRUPT_PRIORITY == portMAX_PRIORITY ) */
}
/*-----------------------------------------------------------*/

#إذا ( configSUPPORT_FPU == 1 )

    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ )
    {
        /* A task is registering the fact that it needs an FPU context.  Allocate a
         * buffer into which the context can be saved. */
        puc_پورٹ_Task_FPUContext_بفر = ( uint8_t * ) pv_پورٹ_Malloc( پورٹ_FPU_CONTEXT_ناپ_بائٹاں );
        configASSERT( puc_پورٹ_Task_FPUContext_بفر );

        /* Initialise the floating point registers. */
        __asm متطاير ( "fninit" );
    }

#جے_انت /* configSUPPORT_FPU */
/*-----------------------------------------------------------*/

فراغ v_پورٹ_APICError_Handler( فراغ )
{
/* Variable to hold the APIC error status for viewing in the debugger. */
    متطاير uint32_t ul_Error_حالت = 0;

    پورٹ_APIC_ERROR_حالت = 0;
    ul_Error_حالت = پورٹ_APIC_ERROR_حالت;
    ( فراغ ) ul_Error_حالت;

    /* Force an assert. */
    configASSERT( ulCriticalNesting == ~0UL );
}
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_رکاوٹ_اندراج_نقطہ == 1 )

    فراغ v_پورٹ_Central_رکاوٹ_Handler( uint32_t ul_سمتیہ )
    {
        إذا( ul_سمتیہ < پورٹ_عدد_VECTORS )
        {
            إذا( x_رکاوٹ_Handler_جدول[ ul_سمتیہ ] != عدم )
            {
                ( x_رکاوٹ_Handler_جدول[ ul_سمتیہ ] )();
            }
        }

        /* Check for a system stack overflow. */
        configASSERT( ul_System_ڈھیر[ 10 ] == پورٹ_ڈھیر_لفظ );
        configASSERT( ul_System_ڈھیر[ 12 ] == پورٹ_ڈھیر_لفظ );
        configASSERT( ul_System_ڈھیر[ 14 ] == پورٹ_ڈھیر_لفظ );
    }

#جے_انت /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

#إذا ( config_USE_COMMON_رکاوٹ_اندراج_نقطہ == 1 )

    ادھار_Type_t x_پورٹ_رجسٹر_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                               uint32_t ul_سمتیہ_نمبر )
    {
        ادھار_Type_t xReturn;

        xReturn = prv_Check_Validity_دا_سمتیہ_نمبر( ul_سمتیہ_نمبر );

        إذا( xReturn != pdFAIL )
        {
            /* Save the handler passed in by the application in the vector number
             * passed in.  The addresses are then called from the central interrupt
             * handler. */
            x_رکاوٹ_Handler_جدول[ ul_سمتیہ_نمبر ] = pxHandler;
        }

        أرجع xReturn;
    }

#جے_انت /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_Install_رکاوٹ_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_سمتیہ_نمبر )
{
    ادھار_Type_t xReturn;

    xReturn = prv_Check_Validity_دا_سمتیہ_نمبر( ul_سمتیہ_نمبر );

    إذا( xReturn != pdFAIL )
    {
        taskENTER_CRITICAL();
        {
            /* Update the IDT to include the application defined handler. */
            prv_سیٹ_رکاوٹ_Gate( ( uint8_t ) ul_سمتیہ_نمبر, ( ISR_Handler_t ) pxHandler, پورٹ_IDT_FLAGS );
        }
        taskEXIT_CRITICAL();
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

ساكن ادھار_Type_t prv_Check_Validity_دا_سمتیہ_نمبر( uint32_t ul_سمتیہ_نمبر )
{
    ادھار_Type_t xReturn;

    /* Check validity of vector number. */
    إذا( ul_سمتیہ_نمبر >= پورٹ_عدد_VECTORS )
    {
        /* Too high. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_سمتیہ_نمبر < پورٹ_APIC_MIN_ALLOWABLE_سمتیہ )
    {
        /* Too low. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_سمتیہ_نمبر == پورٹ_APIC_TIMER_INT_سمتیہ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_سمتیہ_نمبر == پورٹ_APIC_YIELD_INT_سمتیہ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_سمتیہ_نمبر == پورٹ_APIC_LVT_ERROR_سمتیہ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
    وإلا إذا( ul_سمتیہ_نمبر == پورٹ_APIC_SPURIOUS_INT_سمتیہ )
    {
        /* In use by FreeRTOS. */
        xReturn = pdFAIL;
    }
#إذا ( config_USE_COMMON_رکاوٹ_اندراج_نقطہ == 1 )
    وإلا إذا( x_رکاوٹ_Handler_جدول[ ul_سمتیہ_نمبر ] != عدم )
    {
        /* Already in use by the application. */
        xReturn = pdFAIL;
    }
#جے_انت  /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
    وإلا
    {
        xReturn = pdPASS;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/

فراغ v_Generate_Yield_رکاوٹ( فراغ )
{
    __asm متطاير ( پورٹ_YIELD_رکاوٹ );
}
