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
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Library includes. */
#ضمن "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#تعریف_کړه پورټ_INITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#تعریف_کړه پورټ_FLOP_REGISTERS_منزل_STORE    ( 18 )
#تعریف_کړه پورټ_FLOP_STORAGE_اندازه          ( پورټ_FLOP_REGISTERS_منزل_STORE * 4 )

#إذا ( config_SUPPORT_DYNAMIC_ویش == 0 )
    #تېروتنه config_SUPPORT_DYNAMIC_ویش must be 1 منزل use this پورټ.
#د_که_پای

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
فراغ v_پورټ_Yield( فراغ );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
خارجي uint32_t ul_پورټ_Get_GBR( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_سر_د_ډېری = 0x11111111UL;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x22222222UL;
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = 0x33333333UL;
    px_سر_د_ډېری--;

    /* SR. */
    *px_سر_د_ډېری = پورټ_INITIAL_SR;
    px_سر_د_ډېری--;

    /* PC. */
    *px_سر_د_ډېری = ( uint32_t ) px_کوډ;
    px_سر_د_ډېری--;

    /* PR. */
    *px_سر_د_ډېری = 15;
    px_سر_د_ډېری--;

    /* 14. */
    *px_سر_د_ډېری = 14;
    px_سر_د_ډېری--;

    /* R13. */
    *px_سر_د_ډېری = 13;
    px_سر_د_ډېری--;

    /* R12. */
    *px_سر_د_ډېری = 12;
    px_سر_د_ډېری--;

    /* R11. */
    *px_سر_د_ډېری = 11;
    px_سر_د_ډېری--;

    /* R10. */
    *px_سر_د_ډېری = 10;
    px_سر_د_ډېری--;

    /* R9. */
    *px_سر_د_ډېری = 9;
    px_سر_د_ډېری--;

    /* R8. */
    *px_سر_د_ډېری = 8;
    px_سر_د_ډېری--;

    /* R7. */
    *px_سر_د_ډېری = 7;
    px_سر_د_ډېری--;

    /* R6. */
    *px_سر_د_ډېری = 6;
    px_سر_د_ډېری--;

    /* R5. */
    *px_سر_د_ډېری = 5;
    px_سر_د_ډېری--;

    /* R4. */
    *px_سر_د_ډېری = ( uint32_t ) pvParameters;
    px_سر_د_ډېری--;

    /* R3. */
    *px_سر_د_ډېری = 3;
    px_سر_د_ډېری--;

    /* R2. */
    *px_سر_د_ډېری = 2;
    px_سر_د_ډېری--;

    /* R1. */
    *px_سر_د_ډېری = 1;
    px_سر_د_ډېری--;

    /* R0 */
    *px_سر_د_ډېری = 0;
    px_سر_د_ډېری--;

    /* MACL. */
    *px_سر_د_ډېری = 16;
    px_سر_د_ډېری--;

    /* MACH. */
    *px_سر_د_ډېری = 17;
    px_سر_د_ډېری--;

    /* GBR. */
    *px_سر_د_ډېری = ul_پورټ_Get_GBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ v_Application_تیاری_Timer_مداخله( فراغ );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    v_Application_تیاری_Timer_مداخله();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( پورټ_پیل_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield( فراغ )
{
    int32_t l_مداخله_ماسک;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    l_مداخله_ماسک = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    سېټ_imask( پورټ_KERNEL_مداخله_لومړیتوب );

    trapa( پورټ_YIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    سېټ_imask( ( صحيح ) l_مداخله_ماسک );
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_کاروي_Floating_ټکی( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_بفر;
    بنسټ_Type_t xReturn;
    خارجي فراغ * متطاير pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    إذا( xTask == عدم )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_بفر = ( uint32_t * ) pv_پورټ_Malloc( پورټ_FLOP_STORAGE_اندازه );

    إذا( pul_Flop_بفر != عدم )
    {
        /* Start with the registers in a benign state. */
        memset( ( فراغ * ) pul_Flop_بفر, 0x00, پورټ_FLOP_STORAGE_اندازه );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_بفر = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        v_Task_سېټ_Application_Task_نښان( xTask, ( فراغ * ) ( pul_Flop_بفر + پورټ_FLOP_REGISTERS_منزل_STORE ) );
        xReturn = pdPASS;
    }
    وإلا
    {
        xReturn = pdFAIL;
    }

    أرجع xReturn;
}
/*-----------------------------------------------------------*/
