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

#समावेश "FreeRTOS.h"
#समावेश "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the 16FX port.
 *----------------------------------------------------------*/

/*
 * Get current value of DPR and ADB registers
 */
ढेर_Type_t xGet_DPR_ADB_bank( व्योम );

/*
 * Get current value of DTB and PCB registers
 */
ढेर_Type_t xGet_DTB_PCB_bank( व्योम );

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses RLT0, but
 * can be done using any given RLT.
 */
अटल व्योम prvSetupRLT0Interrupt( व्योम );

/*-----------------------------------------------------------*/

/*
 * We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type.
 */
प्रकार व्योम TCB_t;
बाह्य अस्थिर TCB_t * अस्थिर pxCurrentTCB;

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
#अगर( ( configMEMMODEL == portSMALL ) || ( configMEMMODEL == portMEDIUM ) )

    #घोषणा portSAVE_CONTEXT()                                          \
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

    #घोषणा portRESTORE_CONTEXT()                                       \
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

#या_अगर( ( configMEMMODEL == portCOMPACT ) || ( configMEMMODEL == portLARGE ) )

    #घोषणा portSAVE_CONTEXT()                                          \
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

    #घोषणा portRESTORE_CONTEXT()                                       \
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
#पूर्ण_अगर

/*-----------------------------------------------------------*/

/*
 * Functions for obtaining the current value  of  DPR:ADB, DTB:PCB bank registers
 */

#आशय यंत्र

        .GLOBAL    _xGet_DPR_ADB_bank
        .GLOBAL    _xGet_DTB_PCB_bank
        .SECTION   CODE, CODE, ALIGN=1

_xGet_DPR_ADB_bank:

    MOV A, DPR
    SWAP
    MOV A, ADB
    ORW A
    #अगर configMEMMODEL == portMEDIUM || configMEMMODEL == portLARGE
        RETP
    #या_अगर configMEMMODEL == portSMALL || configMEMMODEL == portCOMPACT
        RET
    #पूर्ण_अगर


_xGet_DTB_PCB_bank:

    MOV A, DTB
    SWAP
    MOV A, PCB
    ORW A
    #अगर configMEMMODEL == portMEDIUM || configMEMMODEL == portLARGE
        RETP
    #या_अगर configMEMMODEL == portSMALL || configMEMMODEL == portCOMPACT
        RET
    #पूर्ण_अगर

#आशय endasm
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ढेर_Type_t *px_Port_Initialise_ढेर( ढेर_Type_t *px_शीर्ष_Of_ढेर, TaskFunction_t pxCode, व्योम *pvParameters )
{
    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */
    *px_शीर्ष_Of_ढेर = 0x1111;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2222;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x3333;
    px_शीर्ष_Of_ढेर--;

    /* Once the task is called the task  would  push  the  pointer to the
    parameter onto the stack. Hence here the pointer would be copied to the stack
    first.  When using the COMPACT or LARGE memory model the pointer would be 24
    bits, and when using the SMALL or MEDIUM memory model the pointer would be 16
    bits. */
    #अगर( ( configMEMMODEL == portCOMPACT ) || ( configMEMMODEL == portLARGE ) )
    {
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( ( uint32_t ) ( pvParameters ) >> 16 );
        px_शीर्ष_Of_ढेर--;
    }
    #पूर्ण_अगर

    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( pvParameters );
    px_शीर्ष_Of_ढेर--;

    /* This is redundant push to the stack. This is required in order to introduce
    an offset so that the task accesses a parameter correctly that is passed on to
    the task stack. */
    #अगर( ( configMEMMODEL == portMEDIUM ) || ( configMEMMODEL == portLARGE ) )
    {
        *px_शीर्ष_Of_ढेर = ( xGet_DTB_PCB_bank() & 0xff00 ) | ( ( ( int32_t ) ( pxCode ) >> 16 ) & 0xff );
        px_शीर्ष_Of_ढेर--;
    }
    #पूर्ण_अगर

    /* This is redundant push to the stack. This is required in order to introduce
    an offset so the task correctly accesses the parameter passed on the task stack. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( pxCode );
    px_शीर्ष_Of_ढेर--;

    /* PS - User Mode, ILM=7, RB=0, Interrupts enabled,USP */
    *px_शीर्ष_Of_ढेर = 0xE0C0;
    px_शीर्ष_Of_ढेर--;

    /* PC */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) ( pxCode );
    px_शीर्ष_Of_ढेर--;

    /* DTB | PCB */
    #अगर configMEMMODEL == portSMALL || configMEMMODEL == portCOMPACT
    {
        *px_शीर्ष_Of_ढेर = xGet_DTB_PCB_bank();
        px_शीर्ष_Of_ढेर--;
    }
    #पूर्ण_अगर

    /* DTB | PCB, in case of MEDIUM and LARGE memory models, PCB would be used
    along with PC to indicate the start address of the function. */
    #अगर( ( configMEMMODEL == portMEDIUM ) || ( configMEMMODEL == portLARGE ) )
    {
        *px_शीर्ष_Of_ढेर = ( xGet_DTB_PCB_bank() & 0xff00 ) | ( ( ( int32_t ) ( pxCode ) >> 16 ) & 0xff );
        px_शीर्ष_Of_ढेर--;
    }
    #पूर्ण_अगर

    /* DPR | ADB  */
    *px_शीर्ष_Of_ढेर = xGet_DPR_ADB_bank();
    px_शीर्ष_Of_ढेर--;

    /* AL */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x9999;
    px_शीर्ष_Of_ढेर--;

    /* AH */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0xAAAA;
    px_शीर्ष_Of_ढेर--;

    /* Next the general purpose registers. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x7777; /* RW7 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x6666; /* RW6 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x5555; /* RW5 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x4444; /* RW4 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x3333; /* RW3 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x2222; /* RW2 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x1111; /* RW1 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x8888; /* RW0 */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetupRLT0Interrupt( व्योम )
{
/* The peripheral clock divided by 16 is used by the timer. */
स्थिर uint16_t us_Reload_मूल्य = ( uint16_t ) ( ( ( configCLKP1_CLOCK_HZ / configTICK_RATE_HZ ) / 16UL ) - 1UL );

    /* set reload value = 34999+1, TICK Interrupt after 10 ms @ 56MHz of CLKP1 */
    TMRLR0 = us_Reload_मूल्य;

    /* prescaler 1:16, reload, interrupt enable, count enable, trigger */
    TMCSR0 = 0x041B;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    /* Setup the hardware to generate the tick. */
    prvSetupRLT0Interrupt();

    /* Restore the context of the first task that is going to run. */
    portRESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler.  We will now
    jump to the start of the task the context of which we have just restored. */
    __asm(" reti ");


    /* Should not get here. */
    वापस pdTRUE;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented - unlikely to ever be required as there is nothing to
    return to. */
}

/*-----------------------------------------------------------*/

/*
 * The interrupt service routine used depends on whether the pre-emptive
 * scheduler is being used or not.
 */

#अगर configUSE_PREEMPTION == 1

    /*
     * Tick ISR for preemptive scheduler.  We can use a __nosavereg attribute
     * as the context is to be saved by the portSAVE_CONTEXT() macro, not the
     * compiler generated code.  The tick count is incremented after the context
     * is saved.
     */
    __nosavereg __interrupt व्योम prvRLT0_TICKISR( व्योम )
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
        अगर( xTaskIncrementTick() != pdFALSE )
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

#अन्यथा

    /*
     * Tick ISR for the cooperative scheduler.  All this does is increment the
     * tick count.  We don't need to switch context, this can only be done by
     * manual calls to taskYIELD();
     */
    __interrupt व्योम prvRLT0_TICKISR( व्योम )
    {
        /* Clear RLT0 interrupt flag */
        TMCSR0_UF = 0;

        xTaskIncrementTick();
    }

#पूर्ण_अगर

/*-----------------------------------------------------------*/

/*
 * Manual context switch. We can use a __nosavereg attribute  as the context
 * is to be saved by the portSAVE_CONTEXT() macro, not the compiler generated
 * code.
 */
__nosavereg __interrupt व्योम vPortYield( व्योम )
{
    /* Save the context of the interrupted task. */
    portSAVE_CONTEXT();

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Restore the context of the new task. */
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

__nosavereg __interrupt व्योम vPortYieldDelayed( व्योम )
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
