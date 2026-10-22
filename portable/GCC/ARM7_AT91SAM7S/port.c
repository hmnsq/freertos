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
#تعریف_کرو پورٹ_INITIAL_SPSR                   ( ( ڈھیر_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کرو پورٹ_THUMB_منوال_ثنائی_ہندسہ                 ( ( ڈھیر_Type_t ) 0x20 )
#تعریف_کرو پورٹ_INSTRUCTION_ناپ               ( ( ڈھیر_Type_t ) 4 )
#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( ڈھیر_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#تعریف_کرو پورٹ_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#تعریف_کرو پورٹ_PRESCALE_قدر                 0x00
#تعریف_کرو پورٹ_رکاوٹ_ON_میل             ( ( uint32_t ) 0x01 )
#تعریف_کرو پورٹ_RESET_گنتی_ON_میل           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#تعریف_کرو پورٹ_PIT_CLOCK_مقسوم_علیہ              ( ( uint32_t ) 16 )
#تعریف_کرو پورٹ_PIT_COUNTER_قدر              ( ( ( configCPU_CLOCK_HZ / پورٹ_PIT_CLOCK_مقسوم_علیہ ) / 1000UL ) * پورٹ_TICK_PERIOD_MS )

#تعریف_کرو پورٹ_INT_LEVEL_SENSITIVE            0
#تعریف_کرو پورٹ_PIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#تعریف_کرو پورٹ_PIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
خارجي فراغ v_پورٹ_ISRStart_پہلا_Task( فراغ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    ڈھیر_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_چوٹی_دا_ڈھیر;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوٹی_دا_ڈھیر--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ + پورٹ_INSTRUCTION_ناپ;
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00000000;    /* R14 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;    /* R12 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;    /* R11 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;    /* R10 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;    /* R9 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;    /* R8 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;    /* R7 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;    /* R6 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;    /* R5 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;    /* R4 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;    /* R3 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;    /* R2 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;    /* R1 */
    px_چوٹی_دا_ڈھیر--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */
    px_چوٹی_دا_ڈھیر--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_INITIAL_SPSR;

    #جے_تعریف_شدہ THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_چوٹی_دا_ڈھیر |= پورٹ_THUMB_منوال_ثنائی_ہندسہ;
    }
    #جے_انت

    px_چوٹی_دا_ڈھیر--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_چوٹی_دا_ڈھیر = پورٹ_NO_CRITICAL_SECTION_NESTING;

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_رکاوٹ();

    /* Start the first task. */
    v_پورٹ_ISRStart_پہلا_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    AT91PS_PITC pxPIT = AT91_C_ادھار_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #إذا configUSE_PREEMPTION == 0
        خارجي فراغ( vNonPreemptiveTick ) ( فراغ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_پہلوں_HIGHEST, پورٹ_INT_LEVEL_SENSITIVE, ( فراغ ( * )( فراغ ) )vNonPreemptiveTick );
    #وإلا
        خارجي فراغ( vPreemptiveTick )( فراغ );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_پہلوں_HIGHEST, پورٹ_INT_LEVEL_SENSITIVE, ( فراغ ( * )( فراغ ) )vPreemptiveTick );
    #جے_انت

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = پورٹ_PIT_ENABLE | پورٹ_PIT_INT_ENABLE | پورٹ_PIT_COUNTER_قدر;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91_C_ادھار_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
