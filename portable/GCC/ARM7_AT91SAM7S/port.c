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
#وصف_ڪريو پورٽ_INITIAL_SPSR                   ( ( ڍير_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#وصف_ڪريو پورٽ_THUMB_گهڻائي_ٻٽو_انگ                 ( ( ڍير_Type_t ) 0x20 )
#وصف_ڪريو پورٽ_INSTRUCTION_سائيز               ( ( ڍير_Type_t ) 4 )
#وصف_ڪريو پورٽ_NO_CRITICAL_SECTION_NESTING    ( ( ڍير_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#وصف_ڪريو پورٽ_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#وصف_ڪريو پورٽ_PRESCALE_قدر                 0x00
#وصف_ڪريو پورٽ_مداخلت_ON_ميلاپ             ( ( uint32_t ) 0x01 )
#وصف_ڪريو پورٽ_RESET_ڳڻپ_ON_ميلاپ           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#وصف_ڪريو پورٽ_PIT_CLOCK_ورهائيندڙ              ( ( uint32_t ) 16 )
#وصف_ڪريو پورٽ_PIT_COUNTER_قدر              ( ( ( configCPU_CLOCK_HZ / پورٽ_PIT_CLOCK_ورهائيندڙ ) / 1000UL ) * پورٽ_TICK_PERIOD_MS )

#وصف_ڪريو پورٽ_INT_LEVEL_SENSITIVE            0
#وصف_ڪريو پورٽ_PIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#وصف_ڪريو پورٽ_PIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
خارجي فراغ v_پورٽ_ISRStart_پهريون_Task( فراغ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    ڍير_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_چوٽي_جو_ڍير;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوٽي_جو_ڍير--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ + پورٽ_INSTRUCTION_سائيز;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00000000;    /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12121212;    /* R12 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11111111;    /* R11 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10101010;    /* R10 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09090909;    /* R9 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08080808;    /* R8 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07070707;    /* R7 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06060606;    /* R6 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x05050505;    /* R5 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04040404;    /* R4 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03030303;    /* R3 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x02020202;    /* R2 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x01010101;    /* R1 */
    px_چوٽي_جو_ڍير--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters; /* R0 */
    px_چوٽي_جو_ڍير--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_INITIAL_SPSR;

    #جيڪڏهن_وصف_ٿيل THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_چوٽي_جو_ڍير |= پورٽ_THUMB_گهڻائي_ٻٽو_انگ;
    }
    #جيڪڏهن_پورو

    px_چوٽي_جو_ڍير--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_SECTION_NESTING;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تياري_Timer_مداخلت();

    /* Start the first task. */
    v_پورٽ_ISRStart_پهريون_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    AT91PS_PITC pxPIT = AT91_C_بنياد_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #إذا configUSE_PREEMPTION == 0
        خارجي فراغ( vNonPreemptiveTick ) ( فراغ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_اڳواٽ_HIGHEST, پورٽ_INT_LEVEL_SENSITIVE, ( فراغ ( * )( فراغ ) )vNonPreemptiveTick );
    #وإلا
        خارجي فراغ( vPreemptiveTick )( فراغ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_اڳواٽ_HIGHEST, پورٽ_INT_LEVEL_SENSITIVE, ( فراغ ( * )( فراغ ) )vPreemptiveTick );
    #جيڪڏهن_پورو

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = پورٽ_PIT_ENABLE | پورٽ_PIT_INT_ENABLE | پورٽ_PIT_COUNTER_قدر;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91_C_بنياد_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
