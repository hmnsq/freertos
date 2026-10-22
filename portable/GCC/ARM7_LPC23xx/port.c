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

/* Constants required to setup the task context. */
#تعریف_کن پورت_INITIAL_SPSR                   ( ( پشته_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کن پورت_THUMB_نما_بیت                 ( ( پشته_Type_t ) 0x20 )
#تعریف_کن پورت_INSTRUCTION_اندازه               ( ( پشته_Type_t ) 4 )
#تعریف_کن پورت_NO_CRITICAL_SECTION_NESTING    ( ( پشته_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#تعریف_کن پورت_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#تعریف_کن پورت_PRESCALE_مقدار                 0x00
#تعریف_کن پورت_وقفه_ON_تطابق             ( ( uint32_t ) 0x01 )
#تعریف_کن پورت_RESET_شمار_ON_تطابق           ( ( uint32_t ) 0x02 )

/* Constants required to setup the VIC for the tick ISR. */
#تعریف_کن پورت_TIMER_VIC_CHANNEL              ( ( uint32_t ) 0x0004 )
#تعریف_کن پورت_TIMER_VIC_CHANNEL_بیت          ( ( uint32_t ) 0x0010 )
#تعریف_کن پورت_TIMER_VIC_ENABLE               ( ( uint32_t ) 0x0020 )

/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
خارجي فراغ v_پورت_ISRStart_اولی_Task( فراغ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    پشته_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_بالاترین_از_پشته;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_بالاترین_از_پشته--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد + پورت_INSTRUCTION_اندازه;
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00000000;    /* R14 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12121212;    /* R12 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11111111;    /* R11 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10101010;    /* R10 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09090909;    /* R9 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08080808;    /* R8 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07070707;    /* R7 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06060606;    /* R6 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x05050505;    /* R5 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04040404;    /* R4 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03030303;    /* R3 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x02020202;    /* R2 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x01010101;    /* R1 */
    px_بالاترین_از_پشته--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R0 */
    px_بالاترین_از_پشته--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_کد & 0x01UL ) != 0x00 )
    {
        /* We want the task to start in thumb mode. */
        *px_بالاترین_از_پشته |= پورت_THUMB_نما_بیت;
    }

    px_بالاترین_از_پشته--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_بالاترین_از_پشته = پورت_NO_CRITICAL_SECTION_NESTING;

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_راهاندازی_Timer_وقفه();

    /* Start the first task. */
    v_پورت_ISRStart_اولی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    uint32_t ul_Compare_تطابق;

    PCLKSEL0 = ( PCLKSEL0 & ( ~( 0x3 << 2 ) ) ) | ( 0x01 << 2 );
    T0TCR = 2;  /* Stop and reset the timer */
    T0CTCR = 0; /* Timer mode               */

    /* A 1ms tick does not require the use of the timer prescale.  This is
     * defaulted to zero but can be used if necessary. */
    T0PR = پورت_PRESCALE_مقدار;

    /* Calculate the match value required for our wanted tick rate. */
    ul_Compare_تطابق = configCPU_CLOCK_HZ / config_TICK_نرخ_HZ;

    /* Protect against divide by zero.  Using an if() statement still results
     * in a warning - hence the #if. */
    #إذا پورت_PRESCALE_مقدار != 0
    {
        ul_Compare_تطابق /= ( پورت_PRESCALE_مقدار + 1 );
    }
    #پایان_اگر
    T0MR1 = ul_Compare_تطابق;

    /* Generate tick with timer 0 compare match. */
    T0MCR = ( 3 << 3 ); /* Reset timer on match and generate interrupt */

    /* Setup the VIC for the timer. */
    VICIntEnable = 0x00000010;

    /* The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #إذا configUSE_PREEMPTION == 1
    {
        خارجي فراغ( vPreemptiveTick )( فراغ );
        VICVectAddr4 = ( int32_t ) vPreemptiveTick;
    }
    #وإلا
    {
        خارجي فراغ( vNonPreemptiveTick )( فراغ );
        VICVectAddr4 = ( int32_t ) vNonPreemptiveTick;
    }
    #پایان_اگر

    VICVectCntl4 = 1;

    /* Start the timer - interrupts are disabled when this function is called
     * so it is okay to do this here. */
    T0TCR = پورت_ENABLE_TIMER;
}
/*-----------------------------------------------------------*/
