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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"


#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_FORMAT_ಸದಿಶ       ( ( ರಾಶಿ_Type_t ) 0x4000 )

/* Supervisor mode set. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್     ( ( ರಾಶಿ_Type_t ) 0x2000)

/* The clock prescale into the timer peripheral. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRESCALE_ಮೌಲ್ಯ              ( ( uint8_t ) 10 )

/* The clock frequency into the RTC. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTC_CLOCK_HZ                ( ( uint32_t ) 1000 )

asm ಶೂನ್ಯ ಅಡಚಣೆ ಸದಿಶ_ಸಂಖ್ಯೆ_VL1swi v_ಪೋರ್ಟ್_Yield_ISR( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ಸ್ಥಿರ uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ರಾಶಿ_Type_t *px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ, TaskFunction_t px_ಸಂಕೇತ, ಶೂನ್ಯ *pvParameters )
{

uint32_t ulOriginalA5;

    __asm{ MOVE.L A5, ulOriginalA5 };


    *px_ತುದಿ_ದ_ರಾಶಿ = (ರಾಶಿ_Type_t) 0xDEADBEEF;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Exception stack frame starts with the return address. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ಪೋರ್ಟ್_INITIAL_FORMAT_ಸದಿಶ << 16UL ) | ( ಪೋರ್ಟ್_INITIAL_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ );
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x0; /*FP*/
    px_ತುದಿ_ದ_ರಾಶಿ -= 14; /* A5 to D0. */

    /* Parameter in A0. */
    *( px_ತುದಿ_ದ_ರಾಶಿ + 8 ) = ( ರಾಶಿ_Type_t ) pvParameters;

    /* A5 must be maintained as it is reserved by the compiler. */
    *( px_ತುದಿ_ದ_ರಾಶಿ + 13 ) = ulOriginalA5;

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

    ulCriticalNesting = 0UL;

    /* Configure a timer to generate the tick interrupt. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Start the first task executing. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Prescale by 1 - ie no prescale. */
    RTCSC |= 8;

    /* Compare match value. */
    RTCMOD = ಪೋರ್ಟ್_RTC_CLOCK_HZ / config_TICK_ದರ_HZ;

    /* Enable the RTC to generate interrupts - interrupts are already disabled
    when this code executes. */
    RTCSC_RTIE = 1;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        ಮಾಡು
        {
            ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
            ಆದರೆ( INTC_FRC == 0UL )
            {
                ನಿಲ್ಲಿಸು;
            }

            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();

        } ಆಗ( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ulCriticalNesting--;
    ಆದರೆ( ulCriticalNesting == 0 )
    {
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Handler( ಶೂನ್ಯ )
{
uint32_t ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ;

    ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    {
        /* Note this will clear all forced interrupts - this is done for speed. */
        INTC_CFRC = 0x3E;
        vTaskSwitchContext();
    }
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ ಅಡಚಣೆ ಸದಿಶ_ಸಂಖ್ಯೆ_Vrtc v_ಪೋರ್ಟ್_Tick_ISR( ಶೂನ್ಯ )
{
uint32_t ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ;

    /* Clear the interrupt. */
    RTCSC |= RTCSC_RTIF_ಮುಖವಾಡ;

    /* Increment the RTOS tick. */
    ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            taskYIELD();
        }
    }
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ul_Saved_ಅಡಚಣೆ_ಮುಖವಾಡ );
}
