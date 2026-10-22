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
* Implementation of functions defined in portable.h for the Atmel AT91R40008
* port.
*
* Components that can be compiled to either ARM or THUMB mode are
* contained in this file.  The ISR routines, which can only be compiled
* to ARM mode are contained in portISR.c.
*----------------------------------------------------------*/

/* Standard includes. */
#ಅನ್ತರ್ಭಾವ <stdlib.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Hardware specific definitions. */
#ಅನ್ತರ್ಭಾವ "AT91R40008.h"
#ಅನ್ತರ್ಭಾವ "pio.h"
#ಅನ್ತರ್ಭಾವ "aic.h"
#ಅನ್ತರ್ಭಾವ "tc.h"

/* Constants required to setup the task context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR                   ( ( ರಾಶಿ_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್                 ( ( ರಾಶಿ_Type_t ) 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ               ( ( ರಾಶಿ_Type_t ) 4 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING    ( ( ರಾಶಿ_Type_t ) 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_ಆದ್ಯತೆ_6                ( 6 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ISRStart_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ರಾಶಿ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_ತುದಿ_ದ_ರಾಶಿ;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ + ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212;    /* R12 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;    /* R11 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010;    /* R10 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909;    /* R9 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808;    /* R8 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707;    /* R7 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606;    /* R6 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505;    /* R5 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404;    /* R4 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303;    /* R3 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202;    /* R2 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101;    /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_INITIAL_SPSR;

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Start the first task. */
    v_ಪೋರ್ಟ್_ISRStart_ಮೊದಲ_Task();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the tick timer to generate the tick interrupts at the required frequency.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    ಅಸ್ಥಿರ uint32_t ulDummy;

    /* Enable clock to the tick timer... */
    AT91_C_ತಳ_PS->PS_PCER = ಪೋರ್ಟ್_TIMER_CLK_ENABLE_ಬಿಟ್;

    /* Stop the tick timer... */
    ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_CCR = TC_CLKDIS;

    /* Start with tick timer interrupts disabled... */
    ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_IDR = 0xFFFFFFFF;

    /* Clear any pending tick timer interrupts... */
    ulDummy = ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_SR;

    /* Store interrupt handler function address in tick timer vector register...
     * The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #ಆದರೆ configUSE_PREEMPTION == 1
    {
        ಬಾಹ್ಯ ಶೂನ್ಯ( vPreemptiveTick )( ಶೂನ್ಯ );
        AT91_C_ತಳ_AIC->AIC_SVR[ ಪೋರ್ಟ್_TIMER_AIC_CHANNEL ] = ( uint32_t ) vPreemptiveTick;
    }
    #ಇಲ್ಲದಿದ್ದರೆ // else use cooperative scheduler
    {
        ಬಾಹ್ಯ ಶೂನ್ಯ( vNonPreemptiveTick )( ಶೂನ್ಯ );
        AT91_C_ತಳ_AIC->AIC_SVR[ ಪೋರ್ಟ್_TIMER_AIC_CHANNEL ] = ( uint32_t ) vNonPreemptiveTick;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    /* Tick timer interrupt level-sensitive, priority 6... */
    AT91_C_ತಳ_AIC->AIC_SMR[ ಪೋರ್ಟ್_TIMER_AIC_CHANNEL ] = AIC_SRCTYPE_INT_LEVEL_SENSITIVE | ಪೋರ್ಟ್_TICK_ಆದ್ಯತೆ_6;

    /* Enable the tick timer interrupt...
     *
     * First at timer level */
    ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_IER = TC_CPCS;

    /* Then at the AIC level. */
    AT91_C_ತಳ_AIC->AIC_IECR = ( 1 << ಪೋರ್ಟ್_TIMER_AIC_CHANNEL );

    /* Calculate timer compare value to achieve the desired tick rate... */
    ಆದರೆ( ( configCPU_CLOCK_HZ / ( config_TICK_ದರ_HZ * 2 ) ) <= 0xFFFF )
    {
        /* The tick rate is fast enough for us to use the faster timer input
         * clock (main clock / 2). */
        ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK2 | TC_ಅವಧಿ_NONE | TC_CPCTRG;
        ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_RC = configCPU_CLOCK_HZ / ( config_TICK_ದರ_HZ * 2 );
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        /* We must use a slower timer input clock (main clock / 8) because the
         * tick rate is too slow for the faster input clock. */
        ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK8 | TC_ಅವಧಿ_NONE | TC_CPCTRG;
        ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_RC = configCPU_CLOCK_HZ / ( config_TICK_ದರ_HZ * 8 );
    }

    /* Start tick timer... */
    ಪೋರ್ಟ್_TIMER_REG_ತಳ_PTR->TC_CCR = TC_SWTRG | TC_CLKEN;
}
/*-----------------------------------------------------------*/
