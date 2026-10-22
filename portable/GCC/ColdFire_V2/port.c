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

#تعریف_کړه پورټ_INITIAL_FORMAT_ویکټور      ( ( ډېری_Type_t ) 0x4000 )

/* Supervisor mode set. */
#تعریف_کړه پورټ_INITIAL_حالت_ثبتوونکی    ( ( ډېری_Type_t ) 0x2000 )

/* Used to keep track of the number of nested calls to taskENTER_CRITICAL().  This
 * will be set to 0 prior to the first task being started. */
ساكن uint32_t ulCriticalNesting = 0x9999UL;

/*-----------------------------------------------------------*/

ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xDEADBEEF;
    px_سر_د_ډېری--;

    /* Exception stack frame starts with the return address. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( پورټ_INITIAL_FORMAT_ویکټور << 16UL ) | ( پورټ_INITIAL_حالت_ثبتوونکی );
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x0; /*FP*/
    px_سر_د_ډېری -= 14;                  /* A5 to D0. */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

    ulCriticalNesting = 0UL;

    /* Configure the interrupts used by this port. */
    v_Application_تیاری_Interrupts();

    /* Start the first task executing. */
    v_پورټ_پیل_لومړی_Task();

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    إذا( ulCriticalNesting == 0UL )
    {
        /* Guard against context switches being pended simultaneously with a
         * critical section being entered. */
        افعل
        {
            پورټ_DISABLE_INTERRUPTS();

            إذا( MCF_INTC0_INTFRCL == 0UL )
            {
                اكسر;
            }

            پورټ_ENABLE_INTERRUPTS();
        } طالما( 1 );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield_Handler( فراغ )
{
    uint32_t ul_Saved_مداخله_ماسک;

    ul_Saved_مداخله_ماسک = پورټ_سېټ_مداخله_ماسک_FROM_ISR();
    /* Note this will clear all forced interrupts - this is done for speed. */
    MCF_INTC0_INTFRCL = 0;
    vTaskSwitchContext();
    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ul_Saved_مداخله_ماسک );
}
