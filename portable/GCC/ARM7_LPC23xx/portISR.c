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

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to handle interrupts. */
#وصف_ڪريو پورٽ_TIMER_ميلاپ_ISR_ٻٽو_انگ    ( ( uint8_t ) 0x01 )
#وصف_ڪريو پورٽ_CLEAR_VIC_مداخلت    ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
متطاير uint32_t ulCriticalNesting = 9999UL;

/*-----------------------------------------------------------*/

/* ISR to handle manual context switches (from a call to taskYIELD()). */
فراغ v_پورٽ_Yield_Processor( فراغ ) __attribute__( ( مداخلت( "SWI" ), naked ) );

/*
 * The scheduler can only be started from ARM mode, hence the inclusion of this
 * function here.
 */
فراغ v_پورٽ_ISRStart_پهريون_Task( فراغ );
/*-----------------------------------------------------------*/

فراغ v_پورٽ_ISRStart_پهريون_Task( فراغ )
{
    /* Simply start the scheduler.  This is included here as it can only be
     * called from ARM mode. */
    پورٽ_RESTORE_CONTEXT();
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
فراغ v_پورٽ_Yield_Processor( فراغ )
{
    /* Within an IRQ ISR the link register has an offset from the true return
     * address, but an SWI ISR does not.  Add the offset manually so the same
     * ISR return code can be used in both cases. */
    __asm متطاير ( "ADD       LR, LR, #4" );

    /* Perform the context switch.  First save the context of the current task. */
    پورٽ_SAVE_CONTEXT();

    /* Find the highest priority task that is ready to run. */
    __asm متطاير ( "bl         vTaskSwitchContext" );

    /* Restore the context of the new task. */
    پورٽ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * The ISR used for the scheduler tick depends on whether the cooperative or
 * the preemptive scheduler is being used.
 */


#إذا configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    فراغ vNonPreemptiveTick( فراغ ) __attribute__( ( مداخلت( "IRQ" ) ) );
    فراغ vNonPreemptiveTick( فراغ )
    {
        xTaskIncrementTick();
        T0IR = 2;
        VICVectAddr = پورٽ_CLEAR_VIC_مداخلت;
    }

#وإلا /* if configUSE_PREEMPTION == 0 */

/* The preemptive scheduler is defined as "naked" as the full context is
 * saved on entry as part of the context switch. */
    فراغ vPreemptiveTick( فراغ ) __attribute__( ( naked ) );
    فراغ vPreemptiveTick( فراغ )
    {
        /* Save the context of the interrupted task. */
        پورٽ_SAVE_CONTEXT();

        /* Increment the RTOS tick count, then look for the highest priority
         * task that is ready to run. */
        __asm متطاير
        (
            "   bl xTaskIncrementTick   \t\n" \
            "   cmp r0, #0              \t\n" \
            "   beq SkipContextSwitch   \t\n" \
            "   bl vTaskSwitchContext   \t\n" \
            "SkipContextSwitch:         \t\n"
        );

        /* Ready for the next interrupt. */
        T0IR = 2;
        VICVectAddr = پورٽ_CLEAR_VIC_مداخلت;

        /* Restore the context of the new task. */
        پورٽ_RESTORE_CONTEXT();
    }

#جيڪڏهن_پورو /* if configUSE_PREEMPTION == 0 */
/*-----------------------------------------------------------*/

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions here to
 * ensure a switch to ARM mode.  When THUMB_INTERWORK is not defined then
 * the utilities are defined as macros in portmacro.h - as per other ports.
 */
#جيڪڏهن_وصف_ٿيل THUMB_INTERWORK

    فراغ v_پورٽ_Disable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );
    فراغ v_پورٽ_Enable_Interrupts_From_Thumb( فراغ ) __attribute__( ( naked ) );

    فراغ v_پورٽ_Disable_Interrupts_From_Thumb( فراغ )
    {
        __asm متطاير (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "ORR    R0, R0, #0xC0   \n\t" /* Disable IRQ, FIQ.                        */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

    فراغ v_پورٽ_Enable_Interrupts_From_Thumb( فراغ )
    {
        __asm متطاير (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.                         */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

#جيڪڏهن_پورو /* THUMB_INTERWORK */

/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
فراغ v_پورٽ_Enter_Critical( فراغ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();                          */
    __asm متطاير (
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

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /* Enable interrupts as per portEXIT_CRITICAL().                    */
            __asm متطاير (
                "STMDB  SP!, {R0}       \n\t" /* Push R0.                     */
                "MRS    R0, CPSR        \n\t" /* Get CPSR.                    */
                "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.             */
                "MSR    CPSR, R0        \n\t" /* Write back modified value.   */
                "LDMIA  SP!, {R0}" );         /* Pop R0.                      */
        }
    }
}
