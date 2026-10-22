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
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Processor constants. */
#ضمن "AT91SAM7X256.h"

/* Constants required to setup the task context. */
#تعریف_کړه پورټ_INITIAL_SPSR                   ( ( ډېری_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کړه پورټ_THUMB_ډېرپېښ_بټ                 ( ( ډېری_Type_t ) 0x20 )
#تعریف_کړه پورټ_INSTRUCTION_اندازه               ( ( ډېری_Type_t ) 4 )
#تعریف_کړه پورټ_NO_CRITICAL_SECTION_NESTING    ( ( ډېری_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#تعریف_کړه پورټ_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#تعریف_کړه پورټ_PRESCALE_ارزښت                 0x00
#تعریف_کړه پورټ_مداخله_ON_سمون             ( ( uint32_t ) 0x01 )
#تعریف_کړه پورټ_RESET_شمېر_ON_سمون           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#تعریف_کړه پورټ_PIT_CLOCK_وېشونکی              ( ( uint32_t ) 16 )
#تعریف_کړه پورټ_PIT_COUNTER_ارزښت              ( ( ( configCPU_CLOCK_HZ / پورټ_PIT_CLOCK_وېشونکی ) / 1000UL ) * پورټ_TICK_PERIOD_MS )

#تعریف_کړه پورټ_INT_LEVEL_SENSITIVE            0
#تعریف_کړه پورټ_PIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#تعریف_کړه پورټ_PIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
خارجي فراغ v_پورټ_ISRStart_لومړی_Task( فراغ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    ډېری_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_سر_د_ډېری;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_سر_د_ډېری--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ + پورټ_INSTRUCTION_اندازه;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x00000000;    /* R14 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12121212;    /* R12 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11111111;    /* R11 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10101010;    /* R10 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09090909;    /* R9 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x08080808;    /* R8 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07070707;    /* R7 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06060606;    /* R6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x05050505;    /* R5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04040404;    /* R4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03030303;    /* R3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x02020202;    /* R2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x01010101;    /* R1 */
    px_سر_د_ډېری--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */
    px_سر_د_ډېری--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_INITIAL_SPSR;

    #که_تعریف_شوی THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_سر_د_ډېری |= پورټ_THUMB_ډېرپېښ_بټ;
    }
    #د_که_پای

    px_سر_د_ډېری--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_سر_د_ډېری = پورټ_NO_CRITICAL_SECTION_NESTING;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخله();

    /* Start the first task. */
    v_پورټ_ISRStart_لومړی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    AT91PS_PITC pxPIT = AT91_C_بنسټ_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #إذا configUSE_PREEMPTION == 0
        خارجي فراغ( vNonPreemptiveTick ) ( فراغ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_مخکینی_HIGHEST, پورټ_INT_LEVEL_SENSITIVE, ( فراغ ( * )( فراغ ) )vNonPreemptiveTick );
    #وإلا
        خارجي فراغ( vPreemptiveTick )( فراغ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_مخکینی_HIGHEST, پورټ_INT_LEVEL_SENSITIVE, ( فراغ ( * )( فراغ ) )vPreemptiveTick );
    #د_که_پای

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = پورټ_PIT_ENABLE | پورټ_PIT_INT_ENABLE | پورټ_PIT_COUNTER_ارزښت;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91_C_بنسټ_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
