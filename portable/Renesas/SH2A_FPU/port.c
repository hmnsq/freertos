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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Library includes. */
#ಅನ್ತರ್ಭಾವ "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOP_REGISTERS_ಗಮ್ಯ_STORE    ( 18 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOP_STORAGE_ಗಾತ್ರ          ( ಪೋರ್ಟ್_FLOP_REGISTERS_ಗಮ್ಯ_STORE * 4 )

#ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 0 )
    #ದೋಷ config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ must be 1 ಗಮ್ಯ use this ಪೋರ್ಟ್.
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
ಬಾಹ್ಯ uint32_t ul_ಪೋರ್ಟ್_Get_GBR( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x11111111UL;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x22222222UL;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x33333333UL;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* SR. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_SR;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* PC. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( uint32_t ) px_ಸಂಕೇತ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* PR. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 15;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* 14. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 14;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R13. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 13;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R12. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 12;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R11. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 11;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R10. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 10;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R9. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 9;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R8. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 8;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R7. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 7;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R6. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 6;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R5. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 5;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R4. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( uint32_t ) pvParameters;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R3. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 3;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R2. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 2;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R1. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 1;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* R0 */
    *px_ತುದಿ_ದ_ರಾಶಿ = 0;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* MACL. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 16;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* MACH. */
    *px_ತುದಿ_ದ_ರಾಶಿ = 17;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* GBR. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ul_ಪೋರ್ಟ್_Get_GBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ ಶೂನ್ಯ v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    v_Application_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( ಪೋರ್ಟ್_ಆರಂಭ_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ pdFAIL;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    int32_t l_ಅಡಚಣೆ_ಮುಖವಾಡ;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    l_ಅಡಚಣೆ_ಮುಖವಾಡ = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    ಗಣ_imask( ಪೋರ್ಟ್_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ );

    trapa( ಪೋರ್ಟ್_YIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    ಗಣ_imask( ( ಪೂರ್ಣಾಂಕ ) l_ಅಡಚಣೆ_ಮುಖವಾಡ );
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಬಳಸುತ್ತದೆ_Floating_ಬಿಂದು( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_ಬಫರ್;
    ತಳ_Type_t xReturn;
    ಬಾಹ್ಯ ಶೂನ್ಯ * ಅಸ್ಥಿರ pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    ಆದರೆ( xTask == ಖಾಲಿ )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_ಬಫರ್ = ( uint32_t * ) pv_ಪೋರ್ಟ್_Malloc( ಪೋರ್ಟ್_FLOP_STORAGE_ಗಾತ್ರ );

    ಆದರೆ( pul_Flop_ಬಫರ್ != ಖಾಲಿ )
    {
        /* Start with the registers in a benign state. */
        memset( ( ಶೂನ್ಯ * ) pul_Flop_ಬಫರ್, 0x00, ಪೋರ್ಟ್_FLOP_STORAGE_ಗಾತ್ರ );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_ಬಫರ್ = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( xTask, ( ಶೂನ್ಯ * ) ( pul_Flop_ಬಫರ್ + ಪೋರ್ಟ್_FLOP_REGISTERS_ಗಮ್ಯ_STORE ) );
        xReturn = pdPASS;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdFAIL;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}
/*-----------------------------------------------------------*/
