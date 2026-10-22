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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Library includes. */
#अन्तर्भाव "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#परिभाषय पत्तनम्_INITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#परिभाषय पत्तनम्_FLOP_REGISTERS_गन्तव्यम्_STORE    ( 18 )
#परिभाषय पत्तनम्_FLOP_STORAGE_आकार          ( पत्तनम्_FLOP_REGISTERS_गन्तव्यम्_STORE * 4 )

#यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 0 )
    #दोषः config_SUPPORT_DYNAMIC_आवण्टनम् must be 1 गन्तव्यम् use this पत्तनम्.
#यदि_अन्तः

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
शून्य v_पत्तनम्_Yield( शून्य );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
बाह्य uint32_t ul_पत्तनम्_Get_GBR( शून्य );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_शिखरम्_सम्बन्धि_राशिः = 0x11111111UL;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x22222222UL;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x33333333UL;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* SR. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_SR;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* PC. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( uint32_t ) px_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* PR. */
    *px_शिखरम्_सम्बन्धि_राशिः = 15;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* 14. */
    *px_शिखरम्_सम्बन्धि_राशिः = 14;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R13. */
    *px_शिखरम्_सम्बन्धि_राशिः = 13;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R12. */
    *px_शिखरम्_सम्बन्धि_राशिः = 12;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R11. */
    *px_शिखरम्_सम्बन्धि_राशिः = 11;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R10. */
    *px_शिखरम्_सम्बन्धि_राशिः = 10;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R9. */
    *px_शिखरम्_सम्बन्धि_राशिः = 9;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R8. */
    *px_शिखरम्_सम्बन्धि_राशिः = 8;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R7. */
    *px_शिखरम्_सम्बन्धि_राशिः = 7;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R6. */
    *px_शिखरम्_सम्बन्धि_राशिः = 6;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R5. */
    *px_शिखरम्_सम्बन्धि_राशिः = 5;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R4. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( uint32_t ) pvParameters;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R3. */
    *px_शिखरम्_सम्बन्धि_राशिः = 3;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R2. */
    *px_शिखरम्_सम्बन्धि_राशिः = 2;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R1. */
    *px_शिखरम्_सम्बन्धि_राशिः = 1;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* R0 */
    *px_शिखरम्_सम्बन्धि_राशिः = 0;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* MACL. */
    *px_शिखरम्_सम्बन्धि_राशिः = 16;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* MACH. */
    *px_शिखरम्_सम्बन्धि_राशिः = 17;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* GBR. */
    *px_शिखरम्_सम्बन्धि_राशिः = ul_पत्तनम्_Get_GBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    बाह्य शून्य v_Application_सज्जता_Timer_व्यवधानम्( शून्य );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    v_Application_सज्जता_Timer_व्यवधानम्();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( पत्तनम्_START_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    प्रत्यागम pdFAIL;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield( शून्य )
{
    int32_t l_व्यवधानम्_आवरणम्;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    l_व्यवधानम्_आवरणम् = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    समुच्चयः_imask( पत्तनम्_KERNEL_व्यवधानम्_प्राथमिकता );

    trapa( पत्तनम्_YIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    समुच्चयः_imask( ( पूर्णाङ्क ) l_व्यवधानम्_आवरणम् );
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_उपयुङ्क्ते_Floating_Point( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_बफर;
    आधारः_Type_t xReturn;
    बाह्य शून्य * चञ्चल pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    यदि( xTask == रिक्त )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_बफर = ( uint32_t * ) pv_पत्तनम्_Malloc( पत्तनम्_FLOP_STORAGE_आकार );

    यदि( pul_Flop_बफर != रिक्त )
    {
        /* Start with the registers in a benign state. */
        स्मृतिं_पूरय( ( शून्य * ) pul_Flop_बफर, 0x00, पत्तनम्_FLOP_STORAGE_आकार );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_बफर = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        v_Task_समुच्चयः_Application_Task_चिह्नकम्( xTask, ( शून्य * ) ( pul_Flop_बफर + पत्तनम्_FLOP_REGISTERS_गन्तव्यम्_STORE ) );
        xReturn = pdPASS;
    }
    अन्यथा
    {
        xReturn = pdFAIL;
    }

    प्रत्यागम xReturn;
}
/*-----------------------------------------------------------*/
