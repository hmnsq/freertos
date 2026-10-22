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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Library includes. */
#అన్తర్భావ "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#నిర్వచించు పోర్టు_INITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#నిర్వచించు పోర్టు_FLOP_REGISTERS_గమ్యం_STORE    ( 18 )
#నిర్వచించు పోర్టు_FLOP_STORAGE_కొలత          ( పోర్టు_FLOP_REGISTERS_గమ్యం_STORE * 4 )

#ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 0 )
    #దోషం config_SUPPORT_DYNAMIC_కేటాయింపు must be 1 గమ్యం use this పోర్టు.
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
శూన్య v_పోర్టు_Yield( శూన్య );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
బాహ్య uint32_t ul_పోర్టు_Get_GBR( శూన్య );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_శిఖరం_యొక్క_దొంతర = 0x11111111UL;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x22222222UL;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x33333333UL;
    px_శిఖరం_యొక్క_దొంతర--;

    /* SR. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_SR;
    px_శిఖరం_యొక్క_దొంతర--;

    /* PC. */
    *px_శిఖరం_యొక్క_దొంతర = ( uint32_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    /* PR. */
    *px_శిఖరం_యొక్క_దొంతర = 15;
    px_శిఖరం_యొక్క_దొంతర--;

    /* 14. */
    *px_శిఖరం_యొక్క_దొంతర = 14;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R13. */
    *px_శిఖరం_యొక్క_దొంతర = 13;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R12. */
    *px_శిఖరం_యొక్క_దొంతర = 12;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R11. */
    *px_శిఖరం_యొక్క_దొంతర = 11;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R10. */
    *px_శిఖరం_యొక్క_దొంతర = 10;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R9. */
    *px_శిఖరం_యొక్క_దొంతర = 9;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R8. */
    *px_శిఖరం_యొక్క_దొంతర = 8;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R7. */
    *px_శిఖరం_యొక్క_దొంతర = 7;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R6. */
    *px_శిఖరం_యొక్క_దొంతర = 6;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R5. */
    *px_శిఖరం_యొక్క_దొంతర = 5;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R4. */
    *px_శిఖరం_యొక్క_దొంతర = ( uint32_t ) pvParameters;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R3. */
    *px_శిఖరం_యొక్క_దొంతర = 3;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R2. */
    *px_శిఖరం_యొక్క_దొంతర = 2;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R1. */
    *px_శిఖరం_యొక్క_దొంతర = 1;
    px_శిఖరం_యొక్క_దొంతర--;

    /* R0 */
    *px_శిఖరం_యొక్క_దొంతర = 0;
    px_శిఖరం_యొక్క_దొంతర--;

    /* MACL. */
    *px_శిఖరం_యొక్క_దొంతర = 16;
    px_శిఖరం_యొక్క_దొంతర--;

    /* MACH. */
    *px_శిఖరం_యొక్క_దొంతర = 17;
    px_శిఖరం_యొక్క_దొంతర--;

    /* GBR. */
    *px_శిఖరం_యొక్క_దొంతర = ul_పోర్టు_Get_GBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    బాహ్య శూన్య v_Application_అమరిక_Timer_అంతరాయం( శూన్య );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    v_Application_అమరిక_Timer_అంతరాయం();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( పోర్టు_ప్రారంభం_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    తిరిగి pdFAIL;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య )
{
    int32_t l_అంతరాయం_ముసుగు;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    l_అంతరాయం_ముసుగు = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    సమితి_imask( పోర్టు_KERNEL_అంతరాయం_ప్రాధాన్యత );

    trapa( పోర్టు_YIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    సమితి_imask( ( పూర్ణాంకం ) l_అంతరాయం_ముసుగు );
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ఉపయోగిస్తుంది_Floating_బిందువు( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_బఫరు;
    పునాది_Type_t xReturn;
    బాహ్య శూన్య * అస్థిర pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    ఒకవేళ( xTask == ఖాళీ )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_బఫరు = ( uint32_t * ) pv_పోర్టు_Malloc( పోర్టు_FLOP_STORAGE_కొలత );

    ఒకవేళ( pul_Flop_బఫరు != ఖాళీ )
    {
        /* Start with the registers in a benign state. */
        memset( ( శూన్య * ) pul_Flop_బఫరు, 0x00, పోర్టు_FLOP_STORAGE_కొలత );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_బఫరు = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        v_Task_సమితి_Application_Task_ట్యాగ్( xTask, ( శూన్య * ) ( pul_Flop_బఫరు + పోర్టు_FLOP_REGISTERS_గమ్యం_STORE ) );
        xReturn = pdPASS;
    }
    లేకపోతే
    {
        xReturn = pdFAIL;
    }

    తిరిగి xReturn;
}
/*-----------------------------------------------------------*/
