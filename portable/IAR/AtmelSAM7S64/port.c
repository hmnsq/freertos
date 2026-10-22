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
* Implementation of functions defined in portable.h for the Atmel ARM7 port.
*----------------------------------------------------------*/


/* Standard includes. */
#ಅನ್ತರ್ಭಾವ <stdlib.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to setup the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR           ( ( ರಾಶಿ_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್         ( ( ರಾಶಿ_Type_t ) 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INSTRUCTION_ಗಾತ್ರ       ( ( ರಾಶಿ_Type_t ) 4 )

/* Constants required to setup the PIT. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_CLOCK_ಭಾಜಕ      ( ( uint32_t ) 16 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_COUNTER_ಮೌಲ್ಯ      ( ( ( configCPU_CLOCK_HZ / ಪೋರ್ಟ್_PIT_CLOCK_ಭಾಜಕ ) / 1000UL ) * ಪೋರ್ಟ್_TICK_PERIOD_MS )

/* Constants required to handle critical sections. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )


#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INT_LEVEL_SENSITIVE    0
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_ENABLE             ( ( uint16_t ) 0x1 << 24 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PIT_INT_ENABLE         ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

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

    /* The status register is set for system mode, with interrupts enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_INITIAL_SPSR;

    ಆದರೆ( ( ( uint32_t ) px_ಸಂಕೇತ & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Start the first task. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

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

#ಆದರೆ configUSE_PREEMPTION == 0

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
    ಸ್ಥಿರ __arm __irq ಶೂನ್ಯ v_ಪೋರ್ಟ್_Non_Preemptive_Tick( ಶೂನ್ಯ );
    ಸ್ಥಿರ __arm __irq ಶೂನ್ಯ v_ಪೋರ್ಟ್_Non_Preemptive_Tick( ಶೂನ್ಯ )
    {
        uint32_t ulDummy;

        /* Increment the tick count - which may wake some tasks but as the
         * preemptive scheduler is not being used any woken task is not given
         * processor time no matter what its priority. */
        xTaskIncrementTick();

        /* Clear the PIT interrupt. */
        ulDummy = AT91_C_ತಳ_PITC->PITC_PIVR;

        /* End the interrupt in the AIC. */
        AT91_C_ತಳ_AIC->AIC_EOICR = ulDummy;
    }

#ಇಲ್ಲದಿದ್ದರೆ /* if configUSE_PREEMPTION == 0 */

/* Currently the IAR port requires the preemptive tick function to be
 * defined in an asm file. */

#ಆದರೆ_ಅಂತ್ಯ /* if configUSE_PREEMPTION == 0 */

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    AT91PS_PITC pxPIT = AT91_C_ತಳ_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #ಆದರೆ configUSE_PREEMPTION == 0
        AT91F_AIC_ConfigureIt( AT91_C_ತಳ_AIC, AT91C_ID_SYS, AT91_C_AIC_ಪೂರ್ವ_HIGHEST, ಪೋರ್ಟ್_INT_LEVEL_SENSITIVE, ( ಶೂನ್ಯ ( * )( ಶೂನ್ಯ ) )v_ಪೋರ್ಟ್_Non_Preemptive_Tick );
    #ಇಲ್ಲದಿದ್ದರೆ
        ಬಾಹ್ಯ ಶೂನ್ಯ( v_ಪೋರ್ಟ್_Preemptive_Tick )( ಶೂನ್ಯ );
        AT91F_AIC_ConfigureIt( AT91_C_ತಳ_AIC, AT91C_ID_SYS, AT91_C_AIC_ಪೂರ್ವ_HIGHEST, ಪೋರ್ಟ್_INT_LEVEL_SENSITIVE, ( ಶೂನ್ಯ ( * )( ಶೂನ್ಯ ) )v_ಪೋರ್ಟ್_Preemptive_Tick );
    #ಆದರೆ_ಅಂತ್ಯ

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = ಪೋರ್ಟ್_PIT_ENABLE | ಪೋರ್ಟ್_PIT_INT_ENABLE | ಪೋರ್ಟ್_PIT_COUNTER_ಮೌಲ್ಯ;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91F_AIC_EnableIt( AT91_C_ತಳ_AIC, AT91C_ID_SYS );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Disable interrupts first! */
    __disable_interrupt();

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
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
