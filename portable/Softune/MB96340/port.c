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

#অন্তর্ভাৱ "FreeRTOS.h"
#অন্তর্ভাৱ "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the 16FX port.
 *----------------------------------------------------------*/

/*
 * Get current value of DPR and ADB registers
 */
স্তূপ_Type_t xGet_DPR_ADB_bank( শূন্য );

/*
 * Get current value of DTB and PCB registers
 */
স্তূপ_Type_t xGet_DTB_PCB_bank( শূন্য );

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses RLT0, but
 * can be done using any given RLT.
 */
স্থির শূন্য prvSetupRLT0Interrupt( শূন্য );

/*-----------------------------------------------------------*/

/*
 * We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type.
 */
প্রকারনির্দেশ শূন্য TCB_t;
বাহ্য চঞ্চল TCB_t * চঞ্চল pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * Macro to save a task context to the task stack. This macro  copies the
 * saved context (AH:AL, DPR:ADB, DTB:PCB , PC and PS) from  the   system
 * stack to task stack pointed by user stack pointer ( USP  for SMALL and
 * MEDIUM memory model amd USB:USP for COMPACT  and LARGE memory model ),
 * then  it pushes the general purpose registers RW0-RW7  on  to the task
 * stack. Finally the  resultant  stack  pointer  value is saved into the
 * task  control  block  so  it  can  be retrieved the next time the task
 * executes.
 */
#যদি( ( configMEMMODEL == portSMALL ) || ( configMEMMODEL == portMEDIUM ) )

    #define portSAVE_CONTEXT()                                          \
            {   __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" PUSHW (RW0,RW1,RW2,RW3,RW4,RW5,RW6,RW7) ");     \
                __asm(" MOVW A, _pxCurrentTCB ");                       \
                __asm(" MOVW A, SP ");                                  \
                __asm(" SWAPW ");                                       \
                __asm(" MOVW @AL, AH ");                                \
                __asm(" OR   CCR,#H'20 ");                              \
            }

/*
 * Macro to restore a task context from the task stack. This is
 * effectively the reverse of SAVE_CONTEXT(). First the stack pointer
 * value (USP for SMALL and MEDIUM memory model amd USB:USP for COMPACT
 * and LARGE memory model ) is loaded from the task  control block. Next
 * the value of all the general purpose registers RW0-RW7 is retrieved.
 * Finally it copies of the context ( AH:AL, DPR:ADB, DTB:PCB, PC and PS)
 * of the task to be executed upon RETI from user stack to system stack.
 */

    #define portRESTORE_CONTEXT()                                       \
            {   __asm(" MOVW A, _pxCurrentTCB ");                       \
                __asm(" MOVW A, @A ");                                  \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" MOVW SP, A ");                                  \
                __asm(" POPW (RW0,RW1,RW2,RW3,RW4,RW5,RW6,RW7) ");      \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
            }

#নোচেদ্যদি( ( configMEMMODEL == portCOMPACT ) || ( configMEMMODEL == portLARGE ) )

    #define portSAVE_CONTEXT()                                          \
            {   __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" PUSHW (RW0,RW1,RW2,RW3,RW4,RW5,RW6,RW7) ");     \
                __asm(" MOVL A, _pxCurrentTCB ");                       \
                __asm(" MOVL RL2, A ");                                 \
                __asm(" MOVW A, SP ");                                  \
                __asm(" MOVW @RL2+0, A ");                              \
                __asm(" MOV A, USB ");                                  \
                __asm(" MOV @RL2+2, A ");                               \
            }

    #define portRESTORE_CONTEXT()                                       \
            {   __asm(" MOVL A, _pxCurrentTCB ");                       \
                __asm(" MOVL RL2, A ");                                 \
                __asm(" MOVW A, @RL2+0 ");                              \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" MOVW SP, A ");                                  \
                __asm(" MOV A, @RL2+2 ");                               \
                __asm(" MOV USB, A ");                                  \
                __asm(" POPW (RW0,RW1,RW2,RW3,RW4,RW5,RW6,RW7) ");      \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
                __asm(" AND  CCR,#H'DF ");                              \
                __asm(" POPW  A ");                                     \
                __asm(" OR   CCR,#H'20 ");                              \
                __asm(" PUSHW  A ");                                    \
            }
#endif

/*-----------------------------------------------------------*/

/*
 * Functions for obtaining the current value  of  DPR:ADB, DTB:PCB bank registers
 */

#pragma asm

        .GLOBAL    _xGet_DPR_ADB_bank
        .GLOBAL    _xGet_DTB_PCB_bank
        .SECTION   CODE, CODE, ALIGN=1

_xGet_DPR_ADB_bank:

    MOV A, DPR
    SWAP
    MOV A, ADB
    ORW A
    #যদি configMEMMODEL == portMEDIUM || configMEMMODEL == portLARGE
        RETP
    #নোচেদ্যদি configMEMMODEL == portSMALL || configMEMMODEL == portCOMPACT
        RET
    #endif


_xGet_DTB_PCB_bank:

    MOV A, DTB
    SWAP
    MOV A, PCB
    ORW A
    #যদি configMEMMODEL == portMEDIUM || configMEMMODEL == portLARGE
        RETP
    #নোচেদ্যদি configMEMMODEL == portSMALL || configMEMMODEL == portCOMPACT
        RET
    #endif

#pragma endasm
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
স্তূপ_Type_t *px_Port_Initialise_স্তূপ( স্তূপ_Type_t *px_শীৰ্ষ_Of_স্তূপ, TaskFunction_t pxCode, শূন্য *pvParameters )
{
    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */
    *px_শীৰ্ষ_Of_স্তূপ = 0x1111;
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = 0x2222;
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = 0x3333;
    px_শীৰ্ষ_Of_স্তূপ--;

    /* Once the task is called the task  would  push  the  pointer to the
    parameter onto the stack. Hence here the pointer would be copied to the stack
    first.  When using the COMPACT or LARGE memory model the pointer would be 24
    bits, and when using the SMALL or MEDIUM memory model the pointer would be 16
    bits. */
    #যদি( ( configMEMMODEL == portCOMPACT ) || ( configMEMMODEL == portLARGE ) )
    {
        *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) ( ( uint32_t ) ( pvParameters ) >> 16 );
        px_শীৰ্ষ_Of_স্তূপ--;
    }
    #endif

    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) ( pvParameters );
    px_শীৰ্ষ_Of_স্তূপ--;

    /* This is redundant push to the stack. This is required in order to introduce
    an offset so that the task accesses a parameter correctly that is passed on to
    the task stack. */
    #যদি( ( configMEMMODEL == portMEDIUM ) || ( configMEMMODEL == portLARGE ) )
    {
        *px_শীৰ্ষ_Of_স্তূপ = ( xGet_DTB_PCB_bank() & 0xff00 ) | ( ( ( int32_t ) ( pxCode ) >> 16 ) & 0xff );
        px_শীৰ্ষ_Of_স্তূপ--;
    }
    #endif

    /* This is redundant push to the stack. This is required in order to introduce
    an offset so the task correctly accesses the parameter passed on the task stack. */
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) ( pxCode );
    px_শীৰ্ষ_Of_স্তূপ--;

    /* PS - User Mode, ILM=7, RB=0, Interrupts enabled,USP */
    *px_শীৰ্ষ_Of_স্তূপ = 0xE0C0;
    px_শীৰ্ষ_Of_স্তূপ--;

    /* PC */
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) ( pxCode );
    px_শীৰ্ষ_Of_স্তূপ--;

    /* DTB | PCB */
    #যদি configMEMMODEL == portSMALL || configMEMMODEL == portCOMPACT
    {
        *px_শীৰ্ষ_Of_স্তূপ = xGet_DTB_PCB_bank();
        px_শীৰ্ষ_Of_স্তূপ--;
    }
    #endif

    /* DTB | PCB, in case of MEDIUM and LARGE memory models, PCB would be used
    along with PC to indicate the start address of the function. */
    #যদি( ( configMEMMODEL == portMEDIUM ) || ( configMEMMODEL == portLARGE ) )
    {
        *px_শীৰ্ষ_Of_স্তূপ = ( xGet_DTB_PCB_bank() & 0xff00 ) | ( ( ( int32_t ) ( pxCode ) >> 16 ) & 0xff );
        px_শীৰ্ষ_Of_স্তূপ--;
    }
    #endif

    /* DPR | ADB  */
    *px_শীৰ্ষ_Of_স্তূপ = xGet_DPR_ADB_bank();
    px_শীৰ্ষ_Of_স্তূপ--;

    /* AL */
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x9999;
    px_শীৰ্ষ_Of_স্তূপ--;

    /* AH */
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0xAAAA;
    px_শীৰ্ষ_Of_স্তূপ--;

    /* Next the general purpose registers. */
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x7777; /* RW7 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x6666; /* RW6 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x5555; /* RW5 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x4444; /* RW4 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x3333; /* RW3 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x2222; /* RW2 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x1111; /* RW1 */
    px_শীৰ্ষ_Of_স্তূপ--;
    *px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x8888; /* RW0 */

    ঘূৰাই px_শীৰ্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSetupRLT0Interrupt( শূন্য )
{
/* The peripheral clock divided by 16 is used by the timer. */
ধ্রুৱ uint16_t us_Reload_মান = ( uint16_t ) ( ( ( configCLKP1_CLOCK_HZ / configTICK_RATE_HZ ) / 16UL ) - 1UL );

    /* set reload value = 34999+1, TICK Interrupt after 10 ms @ 56MHz of CLKP1 */
    TMRLR0 = us_Reload_মান;

    /* prescaler 1:16, reload, interrupt enable, count enable, trigger */
    TMCSR0 = 0x041B;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    /* Setup the hardware to generate the tick. */
    prvSetupRLT0Interrupt();

    /* Restore the context of the first task that is going to run. */
    portRESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler.  We will now
    jump to the start of the task the context of which we have just restored. */
    __asm(" reti ");


    /* Should not get here. */
    ঘূৰাই pdTRUE;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented - unlikely to ever be required as there is nothing to
    return to. */
}

/*-----------------------------------------------------------*/

/*
 * The interrupt service routine used depends on whether the pre-emptive
 * scheduler is being used or not.
 */

#যদি configUSE_PREEMPTION == 1

    /*
     * Tick ISR for preemptive scheduler.  We can use a __nosavereg attribute
     * as the context is to be saved by the portSAVE_CONTEXT() macro, not the
     * compiler generated code.  The tick count is incremented after the context
     * is saved.
     */
    __nosavereg __interrupt শূন্য prvRLT0_TICKISR( শূন্য )
    {
        /* Disable interrupts so that portSAVE_CONTEXT() is not interrupted */
        __DI();

        /* Save the context of the interrupted task. */
        portSAVE_CONTEXT();

        /* Enable interrupts */
        __EI();

        /* Clear RLT0 interrupt flag */
        TMCSR0_UF = 0;

        /* Increment the tick count then switch to the highest priority task
        that is ready to run. */
        যদি( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Disable interrupts so that portRESTORE_CONTEXT() is not interrupted */
        __DI();

        /* Restore the context of the new task. */
        portRESTORE_CONTEXT();

        /* Enable interrupts */
        __EI();
    }

#অন্যথা

    /*
     * Tick ISR for the cooperative scheduler.  All this does is increment the
     * tick count.  We don't need to switch context, this can only be done by
     * manual calls to taskYIELD();
     */
    __interrupt শূন্য prvRLT0_TICKISR( শূন্য )
    {
        /* Clear RLT0 interrupt flag */
        TMCSR0_UF = 0;

        xTaskIncrementTick();
    }

#endif

/*-----------------------------------------------------------*/

/*
 * Manual context switch. We can use a __nosavereg attribute  as the context
 * is to be saved by the portSAVE_CONTEXT() macro, not the compiler generated
 * code.
 */
__nosavereg __interrupt শূন্য vPortYield( শূন্য )
{
    /* Save the context of the interrupted task. */
    portSAVE_CONTEXT();

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Restore the context of the new task. */
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

__nosavereg __interrupt শূন্য vPortYieldDelayed( শূন্য )
{
    /* Disable interrupts so that portSAVE_CONTEXT() is not interrupted */
    __DI();

    /* Save the context of the interrupted task. */
    portSAVE_CONTEXT();

    /* Enable interrupts */
    __EI();

    /* Clear delayed interrupt flag */
    __asm (" CLRB  03A4H:0 ");

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Disable interrupts so that portSAVE_CONTEXT() is not interrupted */
    __DI();

    /* Restore the context of the new task. */
    portRESTORE_CONTEXT();

    /* Enable interrupts */
    __EI();
}
/*-----------------------------------------------------------*/
