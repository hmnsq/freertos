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


#وصف_ڪريو پورٽ_INITIAL_FORMAT_ويڪٽر       ( ( ڍير_Type_t ) 0x4000 )

/* Supervisor mode set. */
#وصف_ڪريو پورٽ_INITIAL_حالت_رجسٽر     ( ( ڍير_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#وصف_ڪريو پورٽ_PRESCALE_قدر              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#وصف_ڪريو پورٽ_RTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm فراغ مداخلت ويڪٽر_عدد_VL1swi v_پورٽ_Yield_ISR( فراغ );
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ساكن uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ڍير_Type_t *px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير, TaskFunction_t px_ڪوڊ, فراغ *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_چوٽي_جو_ڍير = (ڍير_Type_t) 0xDEADBEEF;
    px_چوٽي_جو_ڍير--;

    /* Exception stack frame starts with the return address. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( پورٽ_INITIAL_FORMAT_ويڪٽر << 16UL ) | ( پورٽ_INITIAL_حالت_رجسٽر );
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x0; /*FP*/
    px_چوٽي_جو_ڍير -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_چوٽي_جو_ڍير + 8 ) = ( ڍير_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_چوٽي_جو_ڍير + 13 ) = ulOriginalA5;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
خارجي فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prv_تياري_Timer_مداخلت();

    /* Start the first task executing. */
    v_پورٽ_شروعات_پهريون_Task();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = پورٽ_RTC_CLOCK_HZ / config_TICK_شرح_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        افعل
        {
            پورٽ_DISABLE_INTERRUPTS();
            إذا( INTC_FRC == 0UL )
            {
                اكسر;
            }

            پورٽ_ENABLE_INTERRUPTS();

        } طالما( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    ulCriticalNesting--;
    إذا( ulCriticalNesting == 0 )
    {
        پورٽ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield_Handler( فراغ )
{
uint32_t ul_Saved_مداخلت_نقاب;

    ul_Saved_مداخلت_نقاب = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_Saved_مداخلت_نقاب );
}
/*-----------------------------------------------------------*/

فراغ مداخلت ويڪٽر_عدد_Vrtc v_پورٽ_Tick_ISR( فراغ )
{
uint32_t ul_Saved_مداخلت_نقاب;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_نقاب;

    /* Increment the RTOS tick. */
    ul_Saved_مداخلت_نقاب = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
    {
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_Saved_مداخلت_نقاب );
}
