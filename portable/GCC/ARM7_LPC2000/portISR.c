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
 *  Changes from V2.5.2
 *
 + The critical section management functions have been changed.  These no
 +    longer modify the stack and are safe to use at all optimisation levels.
 +    The functions are now also the same for both ARM and THUMB modes.
 +
 +  Changes from V2.6.0
 +
 + Removed the 'static' from the definition of vNonPreemptiveTick() to
 +    allow the demo to link when using the cooperative scheduler.
 +
 +  Changes from V3.2.4
 +
 + The assembler statements are now included in a single asm block rather
 +    than each line having its own asm block.
 */


/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"

/* Constants required to handle interrupts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_ಹೊಂದಿಕೆ_ISR_ಬಿಟ್    ( ( uint8_t ) 0x01 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_VIC_ಅಡಚಣೆ    ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/*-----------------------------------------------------------*/

/* ISR to handle manual context switches (from a call to taskYIELD()). */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Processor( ಶೂನ್ಯ ) __attribute__( ( ಅಡಚಣೆ( "SWI" ), naked ) );

/*
 * The scheduler can only be started from ARM mode, hence the inclusion of this
 * function here.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ISRStart_ಮೊದಲ_Task( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ISRStart_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
    /* Simply start the scheduler.  This is included here as it can only be
     * called from ARM mode. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
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
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Processor( ಶೂನ್ಯ )
{
    /* Within an IRQ ISR the link register has an offset from the true return
     * address, but an SWI ISR does not.  Add the offset manually so the same
     * ISR return code can be used in both cases. */
    __asm ಅಸ್ಥಿರ ( "ADD       LR, LR, #4" );

    /* Perform the context switch.  First save the context of the current task. */
    ಪೋರ್ಟ್_SAVE_CONTEXT();

    /* Find the highest priority task that is ready to run. */
    __asm ಅಸ್ಥಿರ ( "bl vTaskSwitchContext" );

    /* Restore the context of the new task. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * The ISR used for the scheduler tick.
 */
ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ ) __attribute__( ( naked ) );
ಶೂನ್ಯ vTickISR( ಶೂನ್ಯ )
{
    /* Save the context of the interrupted task. */
    ಪೋರ್ಟ್_SAVE_CONTEXT();

    /* Increment the RTOS tick count, then look for the highest priority
     * task that is ready to run. */
    __asm ಅಸ್ಥಿರ
    (
        "   bl xTaskIncrementTick   \t\n" \
        "   cmp r0, #0              \t\n" \
        "   beq SkipContextSwitch   \t\n" \
        "   bl vTaskSwitchContext   \t\n" \
        "SkipContextSwitch:         \t\n"
    );

    /* Ready for the next interrupt. */
    T0_IR = ಪೋರ್ಟ್_TIMER_ಹೊಂದಿಕೆ_ISR_ಬಿಟ್;
    VICVectAddr = ಪೋರ್ಟ್_CLEAR_VIC_ಅಡಚಣೆ;

    /* Restore the context of the new task. */
    ಪೋರ್ಟ್_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions here to
 * ensure a switch to ARM mode.  When THUMB_INTERWORK is not defined then
 * the utilities are defined as macros in portmacro.h - as per other ports.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ THUMB_INTERWORK

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Disable_Interrupts_From_Thumb( ಶೂನ್ಯ ) __attribute__( ( naked ) );
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_Interrupts_From_Thumb( ಶೂನ್ಯ ) __attribute__( ( naked ) );

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Disable_Interrupts_From_Thumb( ಶೂನ್ಯ )
    {
        __asm ಅಸ್ಥಿರ (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "ORR    R0, R0, #0xC0   \n\t" /* Disable IRQ, FIQ.                        */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_Interrupts_From_Thumb( ಶೂನ್ಯ )
    {
        __asm ಅಸ್ಥಿರ (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.                         */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

#ಆದರೆ_ಅಂತ್ಯ /* THUMB_INTERWORK */

/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();                          */
    __asm ಅಸ್ಥಿರ (
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

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            /* Enable interrupts as per portEXIT_CRITICAL().                    */
            __asm ಅಸ್ಥಿರ (
                "STMDB  SP!, {R0}       \n\t" /* Push R0.                     */
                "MRS    R0, CPSR        \n\t" /* Get CPSR.                    */
                "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.             */
                "MSR    CPSR, R0        \n\t" /* Write back modified value.   */
                "LDMIA  SP!, {R0}" );         /* Pop R0.                      */
        }
    }
}
