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
#شامل <stdlib.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Hardware specific definitions. */
#شامل "AT91R40008.h"
#شامل "pio.h"
#شامل "aic.h"
#شامل "tc.h"

/* Constants required to setup the task context. */
#تعریف_کرو پورٹ_INITIAL_SPSR                   ( ( ڈھیر_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#تعریف_کرو پورٹ_THUMB_منوال_ثنائی_ہندسہ                 ( ( ڈھیر_Type_t ) 0x20 )
#تعریف_کرو پورٹ_INSTRUCTION_سائز               ( ( ڈھیر_Type_t ) 4 )
#تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( ڈھیر_Type_t ) 0 )
#تعریف_کرو پورٹ_TICK_ترجیح_6                ( 6 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
خارجی خالی v_پورٹ_ISRStart_پہلا_Task( خالی );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    ڈھیر_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_چوٹی_کا_ڈھیر;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوٹی_کا_ڈھیر--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز + پورٹ_INSTRUCTION_سائز;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;    /* R12 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;    /* R11 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;    /* R10 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;    /* R9 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;    /* R8 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;    /* R7 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;    /* R6 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;    /* R5 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;    /* R4 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;    /* R3 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;    /* R2 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;    /* R1 */
    px_چوٹی_کا_ڈھیر--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */
    px_چوٹی_کا_ڈھیر--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_INITIAL_SPSR;

    #اگر_تعریف_شدہ THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_چوٹی_کا_ڈھیر |= پورٹ_THUMB_منوال_ثنائی_ہندسہ;
    }
    #اگر_ختم

    px_چوٹی_کا_ڈھیر--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_چوٹی_کا_ڈھیر = پورٹ_NO_CRITICAL_SECTION_NESTING;

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخلت();

    /* Start the first task. */
    v_پورٹ_ISRStart_پہلا_Task();

    /* Should not get here! */
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the tick timer to generate the tick interrupts at the required frequency.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    متلون uint32_t ulDummy;

    /* Enable clock to the tick timer... */
    AT91_C_بنیاد_PS->PS_PCER = پورٹ_TIMER_CLK_ENABLE_ثنائی_ہندسہ;

    /* Stop the tick timer... */
    پورٹ_TIMER_REG_بنیاد_PTR->TC_CCR = TC_CLKDIS;

    /* Start with tick timer interrupts disabled... */
    پورٹ_TIMER_REG_بنیاد_PTR->TC_IDR = 0xFFFFFFFF;

    /* Clear any pending tick timer interrupts... */
    ulDummy = پورٹ_TIMER_REG_بنیاد_PTR->TC_SR;

    /* Store interrupt handler function address in tick timer vector register...
     * The ISR installed depends on whether the preemptive or cooperative
     * scheduler is being used. */
    #اگر configUSE_PREEMPTION == 1
    {
        خارجی خالی( vPreemptiveTick )( خالی );
        AT91_C_بنیاد_AIC->AIC_SVR[ پورٹ_TIMER_AIC_CHANNEL ] = ( uint32_t ) vPreemptiveTick;
    }
    #ورنہ // else use cooperative scheduler
    {
        خارجی خالی( vNonPreemptiveTick )( خالی );
        AT91_C_بنیاد_AIC->AIC_SVR[ پورٹ_TIMER_AIC_CHANNEL ] = ( uint32_t ) vNonPreemptiveTick;
    }
    #اگر_ختم

    /* Tick timer interrupt level-sensitive, priority 6... */
    AT91_C_بنیاد_AIC->AIC_SMR[ پورٹ_TIMER_AIC_CHANNEL ] = AIC_SRCTYPE_INT_LEVEL_SENSITIVE | پورٹ_TICK_ترجیح_6;

    /* Enable the tick timer interrupt...
     *
     * First at timer level */
    پورٹ_TIMER_REG_بنیاد_PTR->TC_IER = TC_CPCS;

    /* Then at the AIC level. */
    AT91_C_بنیاد_AIC->AIC_IECR = ( 1 << پورٹ_TIMER_AIC_CHANNEL );

    /* Calculate timer compare value to achieve the desired tick rate... */
    اگر( ( configCPU_CLOCK_HZ / ( config_TICK_شرح_HZ * 2 ) ) <= 0xFFFF )
    {
        /* The tick rate is fast enough for us to use the faster timer input
         * clock (main clock / 2). */
        پورٹ_TIMER_REG_بنیاد_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK2 | TC_مدت_NONE | TC_CPCTRG;
        پورٹ_TIMER_REG_بنیاد_PTR->TC_RC = configCPU_CLOCK_HZ / ( config_TICK_شرح_HZ * 2 );
    }
    ورنہ
    {
        /* We must use a slower timer input clock (main clock / 8) because the
         * tick rate is too slow for the faster input clock. */
        پورٹ_TIMER_REG_بنیاد_PTR->TC_CMR = TC_WAVE | TC_CLKS_MCK8 | TC_مدت_NONE | TC_CPCTRG;
        پورٹ_TIMER_REG_بنیاد_PTR->TC_RC = configCPU_CLOCK_HZ / ( config_TICK_شرح_HZ * 8 );
    }

    /* Start tick timer... */
    پورٹ_TIMER_REG_بنیاد_PTR->TC_CCR = TC_SWTRG | TC_CLKEN;
}
/*-----------------------------------------------------------*/
