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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_FORMAT_ਸਦਿਸ਼       ( ( ਢੇਰ_Type_t ) 0x4000 )

/* Supervisor mode set. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_ਸਥਿਤੀ_ਰਜਿਸਟਰ     ( ( ਢੇਰ_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRESCALE_ਮੁੱਲ              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm ਖਾਲੀ ਰੁਕਾਵਟ ਸਦਿਸ਼_ਸੰਖਿਆ_VL1swi v_ਪੋਰਟ_Yield_ISR( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ਸਥਿਰ uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) 0xDEADBEEF;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Exception stack frame starts with the return address. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਪੋਰਟ_INITIAL_FORMAT_ਸਦਿਸ਼ << 16UL ) | ( ਪੋਰਟ_INITIAL_ਸਥਿਤੀ_ਰਜਿਸਟਰ );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0; /*FP*/
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_ਸਿਖਰ_ਦਾ_ਢੇਰ + 8 ) = ( ਢੇਰ_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_ਸਿਖਰ_ਦਾ_ਢੇਰ + 13 ) = ulOriginalA5;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Start the first task executing. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = ਪੋਰਟ_RTC_CLOCK_HZ / config_TICK_ਦਰ_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        ਕਰੋ
        {
            ਪੋਰਟ_DISABLE_INTERRUPTS();
            ਜੇ( INTC_FRC == 0UL )
            {
                ਰੋਕੋ;
            }

            ਪੋਰਟ_ENABLE_INTERRUPTS();

        } ਜਦੋਂ( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ulCriticalNesting--;
    ਜੇ( ulCriticalNesting == 0 )
    {
        ਪੋਰਟ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield_Handler( ਖਾਲੀ )
{
uint32_t ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ;

    ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ ਰੁਕਾਵਟ ਸਦਿਸ਼_ਸੰਖਿਆ_Vrtc v_ਪੋਰਟ_Tick_ISR( ਖਾਲੀ )
{
uint32_t ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_ਨਕਾਬ;

    /* Increment the RTOS tick. */
    ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
    {
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ );
}
