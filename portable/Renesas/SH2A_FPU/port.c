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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Library includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOP_REGISTERS_ਮੰਜ਼ਿਲ_STORE    ( 18 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOP_STORAGE_ਮਾਪ          ( ਪੋਰਟ_FLOP_REGISTERS_ਮੰਜ਼ਿਲ_STORE * 4 )

#ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 0 )
    #ਗਲਤੀ config_SUPPORT_DYNAMIC_ਵੰਡ must be 1 ਮੰਜ਼ਿਲ use this ਪੋਰਟ.
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
ਬਾਹਰੀ uint32_t ul_ਪੋਰਟ_Get_GBR( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x11111111UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x22222222UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x33333333UL;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* SR. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_SR;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* PC. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint32_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* PR. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 15;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* 14. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 14;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R13. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 13;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R12. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 12;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R11. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 11;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R10. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 10;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R9. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 9;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R8. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 8;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R7. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 7;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R6. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 6;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R5. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 5;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R4. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( uint32_t ) pvParameters;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R3. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 3;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R2. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 2;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R1. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 1;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* R0 */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* MACL. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 16;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* MACH. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 17;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* GBR. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ul_ਪੋਰਟ_Get_GBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    v_Application_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( ਪੋਰਟ_ਸ਼ੁਰੂ_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    ਵਾਪਸ pdFAIL;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    int32_t l_ਰੁਕਾਵਟ_ਨਕਾਬ;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    l_ਰੁਕਾਵਟ_ਨਕਾਬ = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    ਸੈੱਟ_imask( ਪੋਰਟ_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ );

    trapa( ਪੋਰਟ_YIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    ਸੈੱਟ_imask( ( ਪੂਰਨ ) l_ਰੁਕਾਵਟ_ਨਕਾਬ );
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਵਰਤਦਾ_Floating_ਬਿੰਦੂ( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_ਬਫਰ;
    ਅਧਾਰ_Type_t xReturn;
    ਬਾਹਰੀ ਖਾਲੀ * ਅਸਥਿਰ pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    ਜੇ( xTask == ਨਿਰਾ )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_ਬਫਰ = ( uint32_t * ) pv_ਪੋਰਟ_Malloc( ਪੋਰਟ_FLOP_STORAGE_ਮਾਪ );

    ਜੇ( pul_Flop_ਬਫਰ != ਨਿਰਾ )
    {
        /* Start with the registers in a benign state. */
        memset( ( ਖਾਲੀ * ) pul_Flop_ਬਫਰ, 0x00, ਪੋਰਟ_FLOP_STORAGE_ਮਾਪ );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_ਬਫਰ = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( xTask, ( ਖਾਲੀ * ) ( pul_Flop_ਬਫਰ + ਪੋਰਟ_FLOP_REGISTERS_ਮੰਜ਼ਿਲ_STORE ) );
        xReturn = pdPASS;
    }
    ਨਹੀਂਤਾਂ
    {
        xReturn = pdFAIL;
    }

    ਵਾਪਸ xReturn;
}
/*-----------------------------------------------------------*/
