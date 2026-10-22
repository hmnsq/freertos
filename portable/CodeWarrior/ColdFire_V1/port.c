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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"


#परिभाषय पत्तनम्_INITIAL_FORMAT_सदिशम्       ( ( राशिः_Type_t ) 0x4000 )

/* Supervisor mode set. */
#परिभाषय पत्तनम्_INITIAL_स्थितिः_पञ्जिकाकोशः     ( ( राशिः_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#परिभाषय पत्तनम्_PRESCALE_मानम्              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#परिभाषय पत्तनम्_RTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm शून्य व्यवधानम् सदिशम्_सङ्ख्या_VL1swi v_पत्तनम्_Yield_ISR( शून्य );
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
स्थिर uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

राशिः_Type_t *px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः, TaskFunction_t px_संहिता, शून्य *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_शिखरम्_सम्बन्धि_राशिः = (राशिः_Type_t) 0xDEADBEEF;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Exception stack frame starts with the return address. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = ( पत्तनम्_INITIAL_FORMAT_सदिशम् << 16UL ) | ( पत्तनम्_INITIAL_स्थितिः_पञ्जिकाकोशः );
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x0; /*FP*/
    px_शिखरम्_सम्बन्धि_राशिः -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_शिखरम्_सम्बन्धि_राशिः + 8 ) = ( राशिः_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_शिखरम्_सम्बन्धि_राशिः + 13 ) = ulOriginalA5;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Start the first task executing. */
    v_पत्तनम्_Start_First_Task();

    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = पत्तनम्_RTC_CLOCK_HZ / config_TICK_दरः_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    यदि( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        कुरु
        {
            पत्तनम्_DISABLE_INTERRUPTS();
            यदि( INTC_FRC == 0UL )
            {
                भङ्ग;
            }

            पत्तनम्_ENABLE_INTERRUPTS();

        } यावत्( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    ulCriticalNesting--;
    यदि( ulCriticalNesting == 0 )
    {
        पत्तनम्_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield_Handler( शून्य )
{
uint32_t ul_Saved_व्यवधानम्_आवरणम्;

    ul_Saved_व्यवधानम्_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Saved_व्यवधानम्_आवरणम् );
}
/*-----------------------------------------------------------*/

शून्य व्यवधानम् सदिशम्_सङ्ख्या_Vrtc v_पत्तनम्_Tick_ISR( शून्य )
{
uint32_t ul_Saved_व्यवधानम्_आवरणम्;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_आवरणम्;

    /* Increment the RTOS tick. */
    ul_Saved_व्यवधानम्_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    {
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Saved_व्यवधानम्_आवरणम् );
}
