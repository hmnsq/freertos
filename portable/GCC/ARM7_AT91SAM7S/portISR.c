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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ಅನ್ತರ್ಭಾವ "AT91SAM7X256.h"

/* Constants required to handle interrupts. */
#define portTIMER_MATCH_ISR_BIT    ( ( uint8_t ) 0x01 )
#define portCLEAR_VIC_INTERRUPT    ( ( uint32_t ) 0 )

/* Constants required to handle critical sections. */
#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
ಚಞ್ಚಲ uint32_t ulCriticalNesting = 9999UL;

/*-----------------------------------------------------------*/

/* ISR to handle manual context switches (from a call to taskYIELD()). */
ಶೂನ್ಯ vPortYieldProcessor( ಶೂನ್ಯ ) __attribute__( ( interrupt( "SWI" ), naked ) );

/*
 * The scheduler can only be started from ARM mode, hence the inclusion of this
 * function here.
 */
ಶೂನ್ಯ vPortISRStartFirstTask( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortISRStartFirstTask( ಶೂನ್ಯ )
{
    /* Simply start the scheduler.  This is included here as it can only be
     * called from ARM mode. */
    portRESTORE_CONTEXT();
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
ಶೂನ್ಯ vPortYieldProcessor( ಶೂನ್ಯ )
{
    /* Within an IRQ ISR the link register has an offset from the true return
     * address, but an SWI ISR does not.  Add the offset manually so the same
     * ISR return code can be used in both cases. */
    __asm ಚಞ್ಚಲ ( "ADD       LR, LR, #4" );

    /* Perform the context switch.  First save the context of the current task. */
    portSAVE_CONTEXT();

    /* Find the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Restore the context of the new task. */
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * The ISR used for the scheduler tick depends on whether the cooperative or
 * the preemptive scheduler is being used.
 */

#ಯದಿ configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    ಶೂನ್ಯ vNonPreemptiveTick( ಶೂನ್ಯ ) __attribute__( ( interrupt( "IRQ" ) ) );
    ಶೂನ್ಯ vNonPreemptiveTick( ಶೂನ್ಯ )
    {
        uint32_t ulDummy;

        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Clear the PIT interrupt. */
        ulDummy = AT91C_BASE_PITC->PITC_PIVR;

        /* End the interrupt in the AIC. */
        AT91C_BASE_AIC->AIC_EOICR = ulDummy;
    }

#ಅನ್ಯಥಾ /* if configUSE_PREEMPTION == 0 */

/* The preemptive scheduler is defined as "naked" as the full context is
 * saved on entry as part of the context switch. */
    ಶೂನ್ಯ vPreemptiveTick( ಶೂನ್ಯ ) __attribute__( ( naked ) );
    ಶೂನ್ಯ vPreemptiveTick( ಶೂನ್ಯ )
    {
        /* Save the context of the current task. */
        portSAVE_CONTEXT();

        /* Increment the tick count - this may wake a task. */
        ಯದಿ( xTaskIncrementTick() != pdFALSE )
        {
            /* Find the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }

        /* End the interrupt in the AIC. */
        AT91C_BASE_AIC->AIC_EOICR = AT91C_BASE_PITC->PITC_PIVR;

        portRESTORE_CONTEXT();
    }

#endif /* if configUSE_PREEMPTION == 0 */
/*-----------------------------------------------------------*/

/*
 * The interrupt management utilities can only be called from ARM mode.  When
 * THUMB_INTERWORK is defined the utilities are defined as functions here to
 * ensure a switch to ARM mode.  When THUMB_INTERWORK is not defined then
 * the utilities are defined as macros in portmacro.h - as per other ports.
 */
ಶೂನ್ಯ vPortDisableInterruptsFromThumb( ಶೂನ್ಯ ) __attribute__( ( naked ) );
ಶೂನ್ಯ vPortEnableInterruptsFromThumb( ಶೂನ್ಯ ) __attribute__( ( naked ) );

ಶೂನ್ಯ vPortDisableInterruptsFromThumb( ಶೂನ್ಯ )
{
    __asm ಚಞ್ಚಲ (
        "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
        "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
        "ORR    R0, R0, #0xC0   \n\t" /* Disable IRQ, FIQ.                        */
        "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
        "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
        "BX     R14" );               /* Return back to thumb.                    */
}

ಶೂನ್ಯ vPortEnableInterruptsFromThumb( ಶೂನ್ಯ )
{
    __asm ಚಞ್ಚಲ (
        "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
        "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
        "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.                         */
        "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
        "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
        "BX     R14" );               /* Return back to thumb.                    */
}


/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();                          */
    __asm ಚಞ್ಚಲ (
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

ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ )
{
    ಯದಿ( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        ಯದಿ( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Enable interrupts as per portEXIT_CRITICAL().                    */
            __asm ಚಞ್ಚಲ (
                "STMDB  SP!, {R0}       \n\t" /* Push R0.                     */
                "MRS    R0, CPSR        \n\t" /* Get CPSR.                    */
                "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.             */
                "MSR    CPSR, R0        \n\t" /* Write back modified value.   */
                "LDMIA  SP!, {R0}" );         /* Pop R0.                      */
        }
    }
}
