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

/* Kernel includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"


#تعریف_کرو پورٹ_INITIAL_FORMAT_سمتیہ       ( ( ڈھیر_Type_t ) 0x4000 )

/* Supervisor mode set. */
#تعریف_کرو پورٹ_INITIAL_حالت_رجسٹر     ( ( ڈھیر_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#تعریف_کرو پورٹ_PRESCALE_قدر              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#تعریف_کرو پورٹ_RTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm فراغ رکاوٹ سمتیہ_نمبر_VL1swi v_پورٹ_Yield_ISR( فراغ );
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ساكن uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر, TaskFunction_t px_کوڈ, فراغ *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_چوٹی_دا_ڈھیر = (ڈھیر_Type_t) 0xDEADBEEF;
    px_چوٹی_دا_ڈھیر--;

    /* Exception stack frame starts with the return address. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = ( پورٹ_INITIAL_FORMAT_سمتیہ << 16UL ) | ( پورٹ_INITIAL_حالت_رجسٹر );
    px_چوٹی_دا_ڈھیر--;

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x0; /*FP*/
    px_چوٹی_دا_ڈھیر -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_چوٹی_دا_ڈھیر + 8 ) = ( ڈھیر_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_چوٹی_دا_ڈھیر + 13 ) = ulOriginalA5;

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
خارجي فراغ v_پورٹ_شروع_پہلا_Task( فراغ );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prv_تیاری_Timer_رکاوٹ();

    /* Start the first task executing. */
    v_پورٹ_شروع_پہلا_Task();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = پورٹ_RTC_CLOCK_HZ / config_TICK_شرح_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        افعل
        {
            پورٹ_DISABLE_INTERRUPTS();
            إذا( INTC_FRC == 0UL )
            {
                اكسر;
            }

            پورٹ_ENABLE_INTERRUPTS();

        } طالما( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    ulCriticalNesting--;
    إذا( ulCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Yield_Handler( فراغ )
{
uint32_t ul_Saved_رکاوٹ_نقاب;

    ul_Saved_رکاوٹ_نقاب = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ul_Saved_رکاوٹ_نقاب );
}
/*-----------------------------------------------------------*/

فراغ رکاوٹ سمتیہ_نمبر_Vrtc v_پورٹ_Tick_ISR( فراغ )
{
uint32_t ul_Saved_رکاوٹ_نقاب;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_نقاب;

    /* Increment the RTOS tick. */
    ul_Saved_رکاوٹ_نقاب = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ul_Saved_رکاوٹ_نقاب );
}
