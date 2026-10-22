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
* Implementation of functions defined in portable.h for the ARM7 port.
*
* Components that can be compiled to either ARM or THUMB mode are
* contained in this file.  The ISR routines, which can only be compiled
* to ARM mode are contained in portISR.c.
*----------------------------------------------------------*/

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Processor constants. */
#ਅਨ੍ਤਰ੍ਭਾਵ "AT91SAM7X256.h"

/* Constants required to setup the task context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SPSR                   ( ( ਢੇਰ_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ                 ( ( ਢੇਰ_Type_t ) 0x20 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INSTRUCTION_ਮਾਪ               ( ( ਢੇਰ_Type_t ) 4 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING    ( ( ਢੇਰ_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRESCALE_ਮੁੱਲ                 0x00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_ON_ਮੇਲ             ( ( uint32_t ) 0x01 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_ਗਿਣਤੀ_ON_ਮੇਲ           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PIT_CLOCK_ਭਾਜਕ              ( ( uint32_t ) 16 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PIT_COUNTER_ਮੁੱਲ              ( ( ( configCPU_CLOCK_HZ / ਪੋਰਟ_PIT_CLOCK_ਭਾਜਕ ) / 1000UL ) * ਪੋਰਟ_TICK_PERIOD_MS )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INT_LEVEL_SENSITIVE            0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ISRStart_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ਢੇਰ_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_ਸਿਖਰ_ਦਾ_ਢੇਰ;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ + ਪੋਰਟ_INSTRUCTION_ਮਾਪ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00000000;    /* R14 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212;    /* R12 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111;    /* R11 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010;    /* R10 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909;    /* R9 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808;    /* R8 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707;    /* R7 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606;    /* R6 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505;    /* R5 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404;    /* R4 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303;    /* R3 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202;    /* R2 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101;    /* R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_INITIAL_SPSR;

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ |= ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }
    #ਜੇ_ਅੰਤ

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Start the first task. */
    v_ਪੋਰਟ_ISRStart_ਪਹਿਲਾ_Task();

    /* Should not get here! */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    AT91PS_PITC pxPIT = AT91_C_ਅਧਾਰ_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #ਜੇ configUSE_PREEMPTION == 0
        ਬਾਹਰੀ ਖਾਲੀ( vNonPreemptiveTick ) ( ਖਾਲੀ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_ਪੂਰਵ_HIGHEST, ਪੋਰਟ_INT_LEVEL_SENSITIVE, ( ਖਾਲੀ ( * )( ਖਾਲੀ ) )vNonPreemptiveTick );
    #ਨਹੀਂਤਾਂ
        ਬਾਹਰੀ ਖਾਲੀ( vPreemptiveTick )( ਖਾਲੀ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_ਪੂਰਵ_HIGHEST, ਪੋਰਟ_INT_LEVEL_SENSITIVE, ( ਖਾਲੀ ( * )( ਖਾਲੀ ) )vPreemptiveTick );
    #ਜੇ_ਅੰਤ

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = ਪੋਰਟ_PIT_ENABLE | ਪੋਰਟ_PIT_INT_ENABLE | ਪੋਰਟ_PIT_COUNTER_ਮੁੱਲ;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91_C_ਅਧਾਰ_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
