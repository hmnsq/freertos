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

#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the 16FX port.
 *----------------------------------------------------------*/

/*
 * Get current value of DPR and ADB registers
 */
ڈھیر_Type_t xGet_DPR_ADB_bank( فراغ );

/*
 * Get current value of DTB and PCB registers
 */
ڈھیر_Type_t xGet_DTB_PCB_bank( فراغ );

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses RLT0, but
 * can be done using any given RLT.
 */
ساكن فراغ prv_تیاری_RLT0_رکاوٹ( فراغ );

/*-----------------------------------------------------------*/

/*
 * We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type.
 */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

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
#إذا( ( configMEMMODEL == پورٹ_SMALL ) || ( configMEMMODEL == پورٹ_MEDIUM ) )

    #تعریف_کرو پورٹ_SAVE_CONTEXT()                                          \
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

    #تعریف_کرو پورٹ_RESTORE_CONTEXT()                                       \
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

#وإلاإذا( ( configMEMMODEL == پورٹ_COMPACT ) || ( configMEMMODEL == پورٹ_LARGE ) )

    #تعریف_کرو پورٹ_SAVE_CONTEXT()                                          \
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

    #تعریف_کرو پورٹ_RESTORE_CONTEXT()                                       \
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
#جے_انت

/*-----------------------------------------------------------*/

/*
 * Functions for obtaining the current value  of  DPR:ADB, DTB:PCB bank registers
 */

#ہدایت asm

        .GLOBAL    _xGet_DPR_ADB_bank
        .GLOBAL    _xGet_DTB_PCB_bank
        .SECTION   کوڈ_3, کوڈ_3, ALIGN=1

_xGet_DPR_ADB_bank:

    MOV A, DPR
    وٹاندرا
    MOV A, ADB
    ORW A
    #إذا configMEMMODEL == پورٹ_MEDIUM || configMEMMODEL == پورٹ_LARGE
        RETP
    #وإلاإذا configMEMMODEL == پورٹ_SMALL || configMEMMODEL == پورٹ_COMPACT
        RET
    #جے_انت


_xGet_DTB_PCB_bank:

    MOV A, DTB
    وٹاندرا
    MOV A, PCB
    ORW A
    #إذا configMEMMODEL == پورٹ_MEDIUM || configMEMMODEL == پورٹ_LARGE
        RETP
    #وإلاإذا configMEMMODEL == پورٹ_SMALL || configMEMMODEL == پورٹ_COMPACT
        RET
    #جے_انت

#ہدایت endasm
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_دا_ڈھیر, TaskFunction_t px_کوڈ, فراغ *pvParameters )
{
    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */
    *px_چوٹی_دا_ڈھیر = 0x1111;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x2222;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = 0x3333;
    px_چوٹی_دا_ڈھیر--;

    /* Once the task is called the task  would  push  the  pointer to the
    parameter onto the stack. Hence here the pointer would be copied to the stack
    first.  When using the COMPACT or LARGE memory model the pointer would be 24
    bits, and when using the SMALL or MEDIUM memory model the pointer would be 16
    bits. */
    #إذا( ( configMEMMODEL == پورٹ_COMPACT ) || ( configMEMMODEL == پورٹ_LARGE ) )
    {
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( ( uint32_t ) ( pvParameters ) >> 16 );
        px_چوٹی_دا_ڈھیر--;
    }
    #جے_انت

    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( pvParameters );
    px_چوٹی_دا_ڈھیر--;

    /* This is redundant push to the stack. This is required in order to introduce
    an offset so that the task accesses a parameter correctly that is passed on to
    the task stack. */
    #إذا( ( configMEMMODEL == پورٹ_MEDIUM ) || ( configMEMMODEL == پورٹ_LARGE ) )
    {
        *px_چوٹی_دا_ڈھیر = ( xGet_DTB_PCB_bank() & 0xff00 ) | ( ( ( int32_t ) ( px_کوڈ ) >> 16 ) & 0xff );
        px_چوٹی_دا_ڈھیر--;
    }
    #جے_انت

    /* This is redundant push to the stack. This is required in order to introduce
    an offset so the task correctly accesses the parameter passed on the task stack. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( px_کوڈ );
    px_چوٹی_دا_ڈھیر--;

    /* PS - User Mode, ILM=7, RB=0, Interrupts enabled,USP */
    *px_چوٹی_دا_ڈھیر = 0xE0C0;
    px_چوٹی_دا_ڈھیر--;

    /* PC */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( px_کوڈ );
    px_چوٹی_دا_ڈھیر--;

    /* DTB | PCB */
    #إذا configMEMMODEL == پورٹ_SMALL || configMEMMODEL == پورٹ_COMPACT
    {
        *px_چوٹی_دا_ڈھیر = xGet_DTB_PCB_bank();
        px_چوٹی_دا_ڈھیر--;
    }
    #جے_انت

    /* DTB | PCB, in case of MEDIUM and LARGE memory models, PCB would be used
    along with PC to indicate the start address of the function. */
    #إذا( ( configMEMMODEL == پورٹ_MEDIUM ) || ( configMEMMODEL == پورٹ_LARGE ) )
    {
        *px_چوٹی_دا_ڈھیر = ( xGet_DTB_PCB_bank() & 0xff00 ) | ( ( ( int32_t ) ( px_کوڈ ) >> 16 ) & 0xff );
        px_چوٹی_دا_ڈھیر--;
    }
    #جے_انت

    /* DPR | ADB  */
    *px_چوٹی_دا_ڈھیر = xGet_DPR_ADB_bank();
    px_چوٹی_دا_ڈھیر--;

    /* AL */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x9999;
    px_چوٹی_دا_ڈھیر--;

    /* AH */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xAAAA;
    px_چوٹی_دا_ڈھیر--;

    /* Next the general purpose registers. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x7777; /* RW7 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x6666; /* RW6 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x5555; /* RW5 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x4444; /* RW4 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x3333; /* RW3 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x2222; /* RW2 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x1111; /* RW1 */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x8888; /* RW0 */

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_RLT0_رکاوٹ( فراغ )
{
/* The peripheral clock divided by 16 is used by the timer. */
ثابت uint16_t us_Reload_قدر = ( uint16_t ) ( ( ( configCLKP1_CLOCK_HZ / config_TICK_شرح_HZ ) / 16UL ) - 1UL );

    /* set reload value = 34999+1, TICK Interrupt after 10 ms @ 56MHz of CLKP1 */
    TMRLR0 = us_Reload_قدر;

    /* prescaler 1:16, reload, interrupt enable, count enable, trigger */
    TMCSR0 = 0x041B;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* Setup the hardware to generate the tick. */
    prv_تیاری_RLT0_رکاوٹ();

    /* Restore the context of the first task that is going to run. */
    پورٹ_RESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler.  We will now
    jump to the start of the task the context of which we have just restored. */
    __asm(" reti ");


    /* Should not get here. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented - unlikely to ever be required as there is nothing to
    return to. */
}

/*-----------------------------------------------------------*/

/*
 * The interrupt service routine used depends on whether the pre-emptive
 * scheduler is being used or not.
 */

#إذا configUSE_PREEMPTION == 1

    /*
     * Tick ISR for preemptive scheduler.  We can use a __nosavereg attribute
     * as the context is to be saved by the portSAVE_CONTEXT() macro, not the
     * compiler generated code.  The tick count is incremented after the context
     * is saved.
     */
    __nosavereg __interrupt فراغ prvRLT0_TICKISR( فراغ )
    {
        /* Disable interrupts so that portSAVE_CONTEXT() is not interrupted */
        __DI();

        /* Save the context of the interrupted task. */
        پورٹ_SAVE_CONTEXT();

        /* Enable interrupts */
        __EI();

        /* Clear RLT0 interrupt flag */
        TMCSR0_UF = 0;

        /* Increment the tick count then switch to the highest priority task
        that is ready to run. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Disable interrupts so that portRESTORE_CONTEXT() is not interrupted */
        __DI();

        /* Restore the context of the new task. */
        پورٹ_RESTORE_CONTEXT();

        /* Enable interrupts */
        __EI();
    }

#وإلا

    /*
     * Tick ISR for the cooperative scheduler.  All this does is increment the
     * tick count.  We don't need to switch context, this can only be done by
     * manual calls to taskYIELD();
     */
    __interrupt فراغ prvRLT0_TICKISR( فراغ )
    {
        /* Clear RLT0 interrupt flag */
        TMCSR0_UF = 0;

        xTaskIncrementTick();
    }

#جے_انت

/*-----------------------------------------------------------*/

/*
 * Manual context switch. We can use a __nosavereg attribute  as the context
 * is to be saved by the portSAVE_CONTEXT() macro, not the compiler generated
 * code.
 */
__nosavereg __interrupt فراغ v_پورٹ_Yield( فراغ )
{
    /* Save the context of the interrupted task. */
    پورٹ_SAVE_CONTEXT();

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Restore the context of the new task. */
    پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

__nosavereg __interrupt فراغ v_پورٹ_Yield_Delayed_2( فراغ )
{
    /* Disable interrupts so that portSAVE_CONTEXT() is not interrupted */
    __DI();

    /* Save the context of the interrupted task. */
    پورٹ_SAVE_CONTEXT();

    /* Enable interrupts */
    __EI();

    /* Clear delayed interrupt flag */
    __asm (" CLRB  03A4H:0 ");

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Disable interrupts so that portSAVE_CONTEXT() is not interrupted */
    __DI();

    /* Restore the context of the new task. */
    پورٹ_RESTORE_CONTEXT();

    /* Enable interrupts */
    __EI();
}
/*-----------------------------------------------------------*/
