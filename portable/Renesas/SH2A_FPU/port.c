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
* Implementation of functions defined in portable.h for the SH2A port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Library includes. */
#شامل "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#تعریف_کرو پورٹ_INITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#تعریف_کرو پورٹ_FLOP_REGISTERS_مقصد_STORE    ( 18 )
#تعریف_کرو پورٹ_FLOP_STORAGE_سائز          ( پورٹ_FLOP_REGISTERS_مقصد_STORE * 4 )

#اگر ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #غلطی config_SUPPORT_DYNAMIC_تخصیص must be 1 مقصد use this پورٹ.
#اگر_ختم

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
خالی v_پورٹ_Yield( خالی );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
خارجی خالی v_پورٹ_آغاز_پہلا_Task( خالی );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
خارجی uint32_t ul_پورٹ_Get_GBR( خالی );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_چوٹی_کا_ڈھیر = 0x11111111UL;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x22222222UL;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x33333333UL;
    px_چوٹی_کا_ڈھیر--;

    /* SR. */
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_SR;
    px_چوٹی_کا_ڈھیر--;

    /* PC. */
    *px_چوٹی_کا_ڈھیر = ( uint32_t ) px_رمز;
    px_چوٹی_کا_ڈھیر--;

    /* PR. */
    *px_چوٹی_کا_ڈھیر = 15;
    px_چوٹی_کا_ڈھیر--;

    /* 14. */
    *px_چوٹی_کا_ڈھیر = 14;
    px_چوٹی_کا_ڈھیر--;

    /* R13. */
    *px_چوٹی_کا_ڈھیر = 13;
    px_چوٹی_کا_ڈھیر--;

    /* R12. */
    *px_چوٹی_کا_ڈھیر = 12;
    px_چوٹی_کا_ڈھیر--;

    /* R11. */
    *px_چوٹی_کا_ڈھیر = 11;
    px_چوٹی_کا_ڈھیر--;

    /* R10. */
    *px_چوٹی_کا_ڈھیر = 10;
    px_چوٹی_کا_ڈھیر--;

    /* R9. */
    *px_چوٹی_کا_ڈھیر = 9;
    px_چوٹی_کا_ڈھیر--;

    /* R8. */
    *px_چوٹی_کا_ڈھیر = 8;
    px_چوٹی_کا_ڈھیر--;

    /* R7. */
    *px_چوٹی_کا_ڈھیر = 7;
    px_چوٹی_کا_ڈھیر--;

    /* R6. */
    *px_چوٹی_کا_ڈھیر = 6;
    px_چوٹی_کا_ڈھیر--;

    /* R5. */
    *px_چوٹی_کا_ڈھیر = 5;
    px_چوٹی_کا_ڈھیر--;

    /* R4. */
    *px_چوٹی_کا_ڈھیر = ( uint32_t ) pvParameters;
    px_چوٹی_کا_ڈھیر--;

    /* R3. */
    *px_چوٹی_کا_ڈھیر = 3;
    px_چوٹی_کا_ڈھیر--;

    /* R2. */
    *px_چوٹی_کا_ڈھیر = 2;
    px_چوٹی_کا_ڈھیر--;

    /* R1. */
    *px_چوٹی_کا_ڈھیر = 1;
    px_چوٹی_کا_ڈھیر--;

    /* R0 */
    *px_چوٹی_کا_ڈھیر = 0;
    px_چوٹی_کا_ڈھیر--;

    /* MACL. */
    *px_چوٹی_کا_ڈھیر = 16;
    px_چوٹی_کا_ڈھیر--;

    /* MACH. */
    *px_چوٹی_کا_ڈھیر = 17;
    px_چوٹی_کا_ڈھیر--;

    /* GBR. */
    *px_چوٹی_کا_ڈھیر = ul_پورٹ_Get_GBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    خارجی خالی v_Application_تیاری_Timer_مداخلت( خالی );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    v_Application_تیاری_Timer_مداخلت();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( پورٹ_آغاز_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    واپس pdFAIL;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield( خالی )
{
    int32_t l_مداخلت_نقاب;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    l_مداخلت_نقاب = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    سیٹ_imask( پورٹ_KERNEL_مداخلت_ترجیح );

    trapa( پورٹ_YIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    سیٹ_imask( ( صحیح ) l_مداخلت_نقاب );
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_استعمال_کرتا_Floating_نقطہ( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_بفر;
    بنیاد_Type_t xReturn;
    خارجی خالی * متلون pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    اگر( xTask == تہی )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_بفر = ( uint32_t * ) pv_پورٹ_Malloc( پورٹ_FLOP_STORAGE_سائز );

    اگر( pul_Flop_بفر != تہی )
    {
        /* Start with the registers in a benign state. */
        memset( ( خالی * ) pul_Flop_بفر, 0x00, پورٹ_FLOP_STORAGE_سائز );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_بفر = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        v_Task_سیٹ_Application_Task_لیبل( xTask, ( خالی * ) ( pul_Flop_بفر + پورٹ_FLOP_REGISTERS_مقصد_STORE ) );
        xReturn = pdPASS;
    }
    ورنہ
    {
        xReturn = pdFAIL;
    }

    واپس xReturn;
}
/*-----------------------------------------------------------*/
