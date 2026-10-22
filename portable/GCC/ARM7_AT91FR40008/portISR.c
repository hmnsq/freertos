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
* Components that can be compiled to either ARM or THUMB mode are
* contained in port.c  The ISR routines, which can only be compiled
* to ARM mode, are contained in this file.
*----------------------------------------------------------*/

/*
 *  Changes from V3.2.4
 *
 + The assembler statements are now included in a single asm block rather
 +    than each line having its own asm block.
 */


/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Constants required to handle interrupts. */
#تعریف_کرو پورٹ_CLEAR_AIC_مداخلت    ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
متلون uint32_t ulCriticalNesting = 9999UL;

/*-----------------------------------------------------------*/

/* ISR to handle manual context switches (from a call to taskYIELD()). */
خالی v_پورٹ_Yield_Processor( خالی ) __attribute__( ( مداخلت( "SWI" ), naked ) );

/*
 * The scheduler can only be started from ARM mode, hence the inclusion of this
 * function here.
 */
خالی v_پورٹ_ISRStart_پہلا_Task( خالی );
/*-----------------------------------------------------------*/

خالی v_پورٹ_ISRStart_پہلا_Task( خالی )
{
    /* Simply start the scheduler.  This is included here as it can only be
     * called from ARM mode. */
    پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * Called by portYIELD() or taskYIELD() to manually force a context switch.
 *
 * When a context switch is performed from the task level the saved task
 * context is made to look as if it occurred from within the tick ISR.  This
 * way the same restore context function can be used when restoring the context
 * saved from the ISR or that saved from a call to vPortYieldProcessor.
 */
خالی v_پورٹ_Yield_Processor( خالی )
{
    /* Within an IRQ ISR the link register has an offset from the true return
     * address, but an SWI ISR does not.  Add the offset manually so the same
     * ISR return code can be used in both cases. */
    asm متلون ( "ADD     LR, LR, #4" );

    /* Perform the context switch.  First save the context of the current task. */
    پورٹ_SAVE_CONTEXT();

    /* Find the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Restore the context of the new task. */
    پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * The ISR used for the scheduler tick depends on whether the cooperative or
 * the preemptive scheduler is being used.
 */

#اگر configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    خالی vNonPreemptiveTick( خالی ) __attribute__( ( مداخلت( "IRQ" ) ) );
    خالی vNonPreemptiveTick( خالی )
    {
        ساکن متلون uint32_t ulDummy;

        /* Clear tick timer interrupt indication. */
        ulDummy = پورٹ_TIMER_REG_بنیاد_PTR->TC_SR;

        xTaskIncrementTick();

        /* Acknowledge the interrupt at AIC level... */
        AT91_C_بنیاد_AIC->AIC_EOICR = پورٹ_CLEAR_AIC_مداخلت;
    }

#ورنہ /* else preemption is turned on */

/* The preemptive scheduler is defined as "naked" as the full context is
 * saved on entry as part of the context switch. */
    خالی vPreemptiveTick( خالی ) __attribute__( ( naked ) );
    خالی vPreemptiveTick( خالی )
    {
        /* Save the context of the interrupted task. */
        پورٹ_SAVE_CONTEXT();

        /* WARNING - Do not use local (stack) variables here.  Use globals
         *           if you must! */
        ساکن متلون uint32_t ulDummy;

        /* Clear tick timer interrupt indication. */
        ulDummy = پورٹ_TIMER_REG_بنیاد_PTR->TC_SR;

        /* Increment the RTOS tick count, then look for the highest priority
         * task that is ready to run. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Acknowledge the interrupt at AIC level... */
        AT91_C_بنیاد_AIC->AIC_EOICR = پورٹ_CLEAR_AIC_مداخلت;

        /* Restore the context of the new task. */
        پورٹ_RESTORE_CONTEXT();
    }

#اگر_ختم /* if configUSE_PREEMPTION == 0 */
/*-----------------------------------------------------------*/

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions here to
 * ensure a switch to ARM mode.  When THUMB_INTERWORK is not defined then
 * the utilities are defined as macros in portmacro.h - as per other ports.
 */
#اگر_تعریف_شدہ THUMB_INTERWORK

    خالی v_پورٹ_Disable_Interrupts_From_Thumb( خالی ) __attribute__( ( naked ) );
    خالی v_پورٹ_Enable_Interrupts_From_Thumb( خالی ) __attribute__( ( naked ) );

    خالی v_پورٹ_Disable_Interrupts_From_Thumb( خالی )
    {
        asm متلون (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "ORR    R0, R0, #0xC0   \n\t" /* Disable IRQ, FIQ.                        */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

    خالی v_پورٹ_Enable_Interrupts_From_Thumb( خالی )
    {
        asm متلون (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.                         */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

#اگر_ختم /* THUMB_INTERWORK */

/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
خالی v_پورٹ_Enter_Critical( خالی )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();                          */
    asm متلون (
        "STMDB  SP!, {R0}           \n\t" /* Push R0.                             */
        "MRS    R0, CPSR            \n\t" /* Get CPSR.                            */
        "ORR    R0, R0, #0xC0       \n\t" /* Disable IRQ, FIQ.                    */
        "MSR    CPSR, R0            \n\t" /* Write back modified value.           */
        "LDMIA  SP!, {R0}" );             /* Pop R0.                              */

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}

خالی v_پورٹ_Exit_Critical( خالی )
{
    اگر( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Enable interrupts as per portEXIT_CRITICAL().                */
            asm متلون (
                "STMDB  SP!, {R0}       \n\t" /* Push R0.                     */
                "MRS    R0, CPSR        \n\t" /* Get CPSR.                    */
                "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.             */
                "MSR    CPSR, R0        \n\t" /* Write back modified value.   */
                "LDMIA  SP!, {R0}" );         /* Pop R0.                      */
        }
    }
}
