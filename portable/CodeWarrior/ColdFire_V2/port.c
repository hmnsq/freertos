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
#شامل "FreeRTOS.h"
#شامل "task.h"


#تعریف_کرو پورٹ_INITIAL_FORMAT_سمتیہ       ( ( ڈھیر_Type_t ) 0x4000 )

/* Supervisor mode set. */
#تعریف_کرو پورٹ_INITIAL_حالت_رجسٹر     ( ( ڈھیر_Type_t ) 0x2000)

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
will be set to 0 prior to the first task being started. */
ساکن uint32_t ulCriticalNesting = 0x9999UL;


#تعریف_کرو پورٹ_SAVE_CONTEXT()              \
    lea.l       (-60, %sp), %sp;        \
    movem.l     %d0-%fp, (%sp);         \
    move.l      pxCurrentTCB, %a0;      \
    move.l      %sp, (%a0);

#تعریف_کرو پورٹ_RESTORE_CONTEXT()           \
    move.l      pxCurrentTCB, %a0;      \
    move.l      (%a0), %sp;             \
    movem.l     (%sp), %d0-%fp;         \
    lea.l       %sp@(60), %sp;          \
    rte



/*-----------------------------------------------------------*/

ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر, TaskFunction_t px_رمز, خالی *pvParameters )
{
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = (ڈھیر_Type_t) 0xDEADBEEF;
    px_چوٹی_کا_ڈھیر--;

    /* Exception stack frame starts with the return address. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( پورٹ_INITIAL_FORMAT_سمتیہ << 16UL ) | ( پورٹ_INITIAL_حالت_رجسٹر );
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x0; /*FP*/
    px_چوٹی_کا_ڈھیر -= 14; /* A5 to D0. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
خارجی خالی v_پورٹ_آغاز_پہلا_Task( خالی );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    v_Application_تیاری_Interrupts();

    /* Start the first task executing. */
    v_پورٹ_آغاز_پہلا_Task();

    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    اگر( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
        critical section being entered. */
        کرو
        {
            پورٹ_DISABLE_INTERRUPTS();
            اگر( MCF_INTC0_INTFRCH == 0UL )
            {
                توڑو;
            }

            پورٹ_ENABLE_INTERRUPTS();

        } جب( 1 );
    }
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    ulCriticalNesting--;
    اگر( ulCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield_Handler( خالی )
{
uint32_t ul_Saved_مداخلت_نقاب;

    ul_Saved_مداخلت_نقاب = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
        /* Note this will clear all forced interrupts - this is done for speed. */
        MCF_INTC0_INTFRCL = 0;
        vTaskSwitchContext();
    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_Saved_مداخلت_نقاب );
}
/*-----------------------------------------------------------*/
