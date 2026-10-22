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
 */

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to handle critical sections. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/*-----------------------------------------------------------*/

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
    asm ಅಸ್ಥಿರ (                                                        \
        "LDR        R0, =pxCurrentTCB                               \n\t" \
        "LDR        R0, [R0]                                        \n\t" \
        "LDR        LR, [R0]                                        \n\t" \
                                                                          \
        /* The critical nesting depth is the first item on the stack. */  \
        /* Load it into the ulCriticalNesting variable. */                \
        "LDR        R0, =ulCriticalNesting                          \n\t" \
        "LDMFD  LR!, {R1}                                           \n\t" \
        "STR        R1, [R0]                                        \n\t" \
                                                                          \
        /* Get the SPSR from the stack. */                                \
        "LDMFD  LR!, {R0}                                           \n\t" \
        "MSR        SPSR, R0                                        \n\t" \
                                                                          \
        /* Restore all system mode registers for the task. */             \
        "LDMFD  LR, {R0-R14}^                                       \n\t" \
        "NOP                                                        \n\t" \
                                                                          \
        /* Restore the return address. */                                 \
        "LDR        LR, [LR, #+60]                                  \n\t" \
                                                                          \
        /* And return - correcting the offset in the LR to obtain the */  \
        /* correct address. */                                            \
        "SUBS PC, LR, #4                                            \n\t" \
        );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ )
{
    /* Increment the RTOS tick count, then look for the highest priority
     * task that is ready to run. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Ready for the next interrupt. */
    TB_Clear_ITPending_ಬಿಟ್( TB_IT_Update );
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
        asm ಅಸ್ಥಿರ (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "ORR    R0, R0, #0xC0   \n\t" /* Disable IRQ, FIQ.                        */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_Interrupts_From_Thumb( ಶೂನ್ಯ )
    {
        asm ಅಸ್ಥಿರ (
            "STMDB  SP!, {R0}       \n\t" /* Push R0.                                 */
            "MRS    R0, CPSR        \n\t" /* Get CPSR.                                */
            "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.                         */
            "MSR    CPSR, R0        \n\t" /* Write back modified value.               */
            "LDMIA  SP!, {R0}       \n\t" /* Pop R0.                                  */
            "BX     R14" );               /* Return back to thumb.                    */
    }

#ಆದರೆ_ಅಂತ್ಯ /* THUMB_INTERWORK */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();                          */
    asm ಅಸ್ಥಿರ (
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
/*-----------------------------------------------------------*/

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
            asm ಅಸ್ಥಿರ (
                "STMDB  SP!, {R0}       \n\t" /* Push R0.                     */
                "MRS    R0, CPSR        \n\t" /* Get CPSR.                    */
                "BIC    R0, R0, #0xC0   \n\t" /* Enable IRQ, FIQ.             */
                "MSR    CPSR, R0        \n\t" /* Write back modified value.   */
                "LDMIA  SP!, {R0}" );         /* Pop R0.                      */
        }
    }
}
