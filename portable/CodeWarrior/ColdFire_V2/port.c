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

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ਸਥਿਰ uint32_t ulCriticalNesting = 0x9999UL;


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SAVE_CONTEXT()              \
    lea.l       (-60, %sp), %sp;        \
    movem.l     %d0-%fp, (%sp);         \
    move.l      pxCurrentTCB, %a0;      \
    move.l      %sp, (%a0);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT()           \
    move.l      pxCurrentTCB, %a0;      \
    move.l      (%a0), %sp;             \
    movem.l     (%sp), %d0-%fp;         \
    lea.l       %sp@(60), %sp;          \
    rte



/*-----------------------------------------------------------*/

ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = (ਢੇਰ_Type_t) 0xDEADBEEF;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Exception stack frame starts with the return address. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਪੋਰਟ_INITIAL_FORMAT_ਸਦਿਸ਼ << 16UL ) | ( ਪੋਰਟ_INITIAL_ਸਥਿਤੀ_ਰਜਿਸਟਰ );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x0; /*FP*/
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 14; /* A5 to D0. */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    v_Application_ਤਿਆਰੀ_Interrupts();

    /* Start the first task executing. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    ਵਾਪਸ pdFALSE;
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
            ਜੇ( MCF_INTC0_INTFRCH == 0UL )
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
        /* Note this will clear all forced interrupts - this is done for speed. */
        MCF_INTC0_INTFRCL = 0;
        vTaskSwitchContext();
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_Saved_ਰੁਕਾਵਟ_ਨਕਾਬ );
}
/*-----------------------------------------------------------*/
