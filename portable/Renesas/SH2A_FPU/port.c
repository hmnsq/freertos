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
#समावेश "FreeRTOS.h"
#समावेश "task.h"

/* Library includes. */
#समावेश "string.h"

/*-----------------------------------------------------------*/

/* The SR assigned to a newly created task.  The only important thing in this
 * value is for all interrupts to be enabled. */
#घोषणा portINITIAL_SR                 ( 0UL )

/* Dimensions the array into which the floating point context is saved.
 * Allocate enough space for FPR0 to FPR15, FPUL and FPSCR, each of which is 4
 * bytes big.  If this number is changed then the 72 in portasm.src also needs
 * changing. */
#घोषणा portFLOP_REGISTERS_TO_STORE    ( 18 )
#घोषणा port_FLOP_STORAGE_आकार          ( portFLOP_REGISTERS_TO_STORE * 4 )

#अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #त्रुटि configSUPPORT_DYNAMIC_ALLOCATION must be 1 to use this port.
#पूर्ण_अगर

/*-----------------------------------------------------------*/

/*
 * The TRAPA handler used to force a context switch.
 */
व्योम vPortYield( व्योम );

/*
 * Function to start the first task executing - defined in portasm.src.
 */
बाह्य व्योम vPortStartFirstTask( व्योम );

/*
 * Obtains the current GBR value - defined in portasm.src.
 */
बाह्य uint32_t ulPortGetGBR( व्योम );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /* Mark the end of the stack - used for debugging only and can be removed. */
    *px_शीर्ष_Of_ढेर = 0x11111111UL;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x22222222UL;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x33333333UL;
    px_शीर्ष_Of_ढेर--;

    /* SR. */
    *px_शीर्ष_Of_ढेर = portINITIAL_SR;
    px_शीर्ष_Of_ढेर--;

    /* PC. */
    *px_शीर्ष_Of_ढेर = ( uint32_t ) pxCode;
    px_शीर्ष_Of_ढेर--;

    /* PR. */
    *px_शीर्ष_Of_ढेर = 15;
    px_शीर्ष_Of_ढेर--;

    /* 14. */
    *px_शीर्ष_Of_ढेर = 14;
    px_शीर्ष_Of_ढेर--;

    /* R13. */
    *px_शीर्ष_Of_ढेर = 13;
    px_शीर्ष_Of_ढेर--;

    /* R12. */
    *px_शीर्ष_Of_ढेर = 12;
    px_शीर्ष_Of_ढेर--;

    /* R11. */
    *px_शीर्ष_Of_ढेर = 11;
    px_शीर्ष_Of_ढेर--;

    /* R10. */
    *px_शीर्ष_Of_ढेर = 10;
    px_शीर्ष_Of_ढेर--;

    /* R9. */
    *px_शीर्ष_Of_ढेर = 9;
    px_शीर्ष_Of_ढेर--;

    /* R8. */
    *px_शीर्ष_Of_ढेर = 8;
    px_शीर्ष_Of_ढेर--;

    /* R7. */
    *px_शीर्ष_Of_ढेर = 7;
    px_शीर्ष_Of_ढेर--;

    /* R6. */
    *px_शीर्ष_Of_ढेर = 6;
    px_शीर्ष_Of_ढेर--;

    /* R5. */
    *px_शीर्ष_Of_ढेर = 5;
    px_शीर्ष_Of_ढेर--;

    /* R4. */
    *px_शीर्ष_Of_ढेर = ( uint32_t ) pvParameters;
    px_शीर्ष_Of_ढेर--;

    /* R3. */
    *px_शीर्ष_Of_ढेर = 3;
    px_शीर्ष_Of_ढेर--;

    /* R2. */
    *px_शीर्ष_Of_ढेर = 2;
    px_शीर्ष_Of_ढेर--;

    /* R1. */
    *px_शीर्ष_Of_ढेर = 1;
    px_शीर्ष_Of_ढेर--;

    /* R0 */
    *px_शीर्ष_Of_ढेर = 0;
    px_शीर्ष_Of_ढेर--;

    /* MACL. */
    *px_शीर्ष_Of_ढेर = 16;
    px_शीर्ष_Of_ढेर--;

    /* MACH. */
    *px_शीर्ष_Of_ढेर = 17;
    px_शीर्ष_Of_ढेर--;

    /* GBR. */
    *px_शीर्ष_Of_ढेर = ulPortGetGBR();

    /* GBR = global base register.
    * VBR = vector base register.
    * TBR = jump table base register.
    * R15 is the stack pointer. */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    बाह्य व्योम vApplicationSetupTimerInterrupt( व्योम );

    /* Call an application function to set up the timer that will generate the
     * tick interrupt.  This way the application can decide which peripheral to
     * use.  A demo application is provided to show a suitable example. */
    vApplicationSetupTimerInterrupt();

    /* Start the first task.  This will only restore the standard registers and
     * not the flop registers.  This does not really matter though because the only
     * flop register that is initialised to a particular value is fpscr, and it is
     * only initialised to the current value, which will still be the current value
     * when the first task starts executing. */
    trapa( portSTART_SCHEDULER_TRAP_NO );

    /* Should not get here. */
    वापस pdFAIL;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented as there is nothing to return to. */
}
/*-----------------------------------------------------------*/

व्योम vPortYield( व्योम )
{
    int32_t lInterruptMask;

    /* Ensure the yield trap runs at the same priority as the other interrupts
     * that can cause a context switch. */
    lInterruptMask = get_imask();

    /* taskYIELD() can only be called from a task, not an interrupt, so the
     * current interrupt mask can only be 0 or portKERNEL_INTERRUPT_PRIORITY and
     * the mask can be set without risk of accidentally lowering the mask value. */
    set_imask( portKERNEL_INTERRUPT_PRIORITY );

    trapa( portYIELD_TRAP_NO );

    /* Restore the interrupt mask to whatever it was previously (when the
     * function was entered). */
    set_imask( ( पूर्णांक ) lInterruptMask );
}
/*-----------------------------------------------------------*/

BaseType_t xPortUsesFloatingPoint( TaskHandle_t xTask )
{
    uint32_t * pul_Flop_बफर;
    BaseType_t xReturn;
    बाह्य व्योम * अस्थिर pxCurrentTCB;

    /* This function tells the kernel that the task referenced by xTask is
     * going to use the floating point registers and therefore requires the
     * floating point registers saved as part of its context. */

    /* Passing NULL as xTask is used to indicate that the calling task is the
     * subject task - so pxCurrentTCB is the task handle. */
    अगर( xTask == शून्य )
    {
        xTask = ( TaskHandle_t ) pxCurrentTCB;
    }

    /* Allocate a buffer large enough to hold all the flop registers. */
    pul_Flop_बफर = ( uint32_t * ) pvPortMalloc( port_FLOP_STORAGE_आकार );

    अगर( pul_Flop_बफर != शून्य )
    {
        /* Start with the registers in a benign state. */
        स_रखो( ( व्योम * ) pul_Flop_बफर, 0x00, port_FLOP_STORAGE_आकार );

        /* The first thing to get saved in the buffer is the FPSCR value -
         * initialise this to the current FPSCR value. */
        *pul_Flop_बफर = get_fpscr();

        /* Use the task tag to point to the flop buffer.  Pass pointer to just
         * above the buffer because the flop save routine uses a pre-decrement. */
        vTaskSetApplicationTaskTag( xTask, ( व्योम * ) ( pul_Flop_बफर + portFLOP_REGISTERS_TO_STORE ) );
        xReturn = pdPASS;
    }
    अन्यथा
    {
        xReturn = pdFAIL;
    }

    वापस xReturn;
}
/*-----------------------------------------------------------*/
