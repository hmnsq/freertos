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

/*
 *  Changes from V2.5.2
 *
 + usCriticalNesting now has a volatile qualifier.
 */

/* Standard includes. */
#ضمن <stdlib.h>
#ضمن <signal.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the MSP430 port.
*----------------------------------------------------------*/

/* Constants required for hardware setup.  The tick ISR runs off the ACLK,
 * not the MCLK. */
#تعریف_کرو پورٹ_ACLK_FREQUENCY_HZ           ( ( TickType_t ) 32768 )
#تعریف_کرو پورٹ_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )
#تعریف_کرو پورٹ_FLAGS_INT_ENABLED           ( ( ڈھیر_Type_t ) 0x08 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/* Most ports implement critical sections by placing the interrupt flags on
 * the stack before disabling interrupts.  Exiting the critical section is then
 * simply a case of popping the flags from the stack.  As mspgcc does not use
 * a frame pointer this cannot be done as modifying the stack will clobber all
 * the stack variables.  Instead each task maintains a count of the critical
 * section nesting depth.  Each time a critical section is entered the count is
 * incremented.  Each time a critical section is left the count is decremented -
 * with interrupts only being re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as this will cause problems during the startup
 * sequence. */
متطاير uint16_t usCriticalNesting = پورٹ_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/

/*
 * Macro to save a task context to the task stack.  This simply pushes all the
 * general purpose msp430 registers onto the stack, followed by the
 * usCriticalNesting value used by the task.  Finally the resultant stack
 * pointer value is saved into the task control block so it can be retrieved
 * the next time the task executes.
 */
#تعریف_کرو پورٹ_SAVE_CONTEXT()                               \
    asm متطاير ( "push   r4                      \n\t" \
                   "push   r5                      \n\t" \
                   "push   r6                      \n\t" \
                   "push   r7                      \n\t" \
                   "push   r8                      \n\t" \
                   "push   r9                      \n\t" \
                   "push   r10                     \n\t" \
                   "push   r11                     \n\t" \
                   "push   r12                     \n\t" \
                   "push   r13                     \n\t" \
                   "push   r14                     \n\t" \
                   "push   r15                     \n\t" \
                   "mov.w  usCriticalNesting, r14  \n\t" \
                   "push   r14                     \n\t" \
                   "mov.w  pxCurrentTCB, r12       \n\t" \
                   "mov.w  r1, @r12                \n\t" \
                   );

/*
 * Macro to restore a task context from the task stack.  This is effectively
 * the reverse of portSAVE_CONTEXT().  First the stack pointer value is
 * loaded from the task control block.  Next the value for usCriticalNesting
 * used by the task is retrieved from the stack - followed by the value of all
 * the general purpose msp430 registers.
 *
 * The bic instruction ensures there are no low power bits set in the status
 * register that is about to be popped from the stack.
 */
#تعریف_کرو پورٹ_RESTORE_CONTEXT()                            \
    asm متطاير ( "mov.w  pxCurrentTCB, r12       \n\t" \
                   "mov.w  @r12, r1                \n\t" \
                   "pop    r15                     \n\t" \
                   "mov.w  r15, usCriticalNesting  \n\t" \
                   "pop    r15                     \n\t" \
                   "pop    r14                     \n\t" \
                   "pop    r13                     \n\t" \
                   "pop    r12                     \n\t" \
                   "pop    r11                     \n\t" \
                   "pop    r10                     \n\t" \
                   "pop    r9                      \n\t" \
                   "pop    r8                      \n\t" \
                   "pop    r7                      \n\t" \
                   "pop    r6                      \n\t" \
                   "pop    r5                      \n\t" \
                   "pop    r4                      \n\t" \
                   "bic    #(0xf0),0(r1)           \n\t" \
                   "reti                           \n\t" \
                   );
/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.  This uses timer 0, but
 * could have alternatively used the watchdog timer or timer 1.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /*
     *  Place a few bytes of known values on the bottom of the stack.
     *  This is just useful for debugging and can be included if required.
     *
     * pxTopOfStack = ( StackType_t ) 0x1111;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x2222;
     *  pxTopOfStack--;
     * pxTopOfStack = ( StackType_t ) 0x3333;
     *  pxTopOfStack--;
     */

    /* The msp430 automatically pushes the PC then SR onto the stack before
     * executing an ISR.  We want the stack to look just as if this has happened
     * so place a pointer to the start of the task on the stack first - followed
     * by the flags we want the task to use when it starts up. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = پورٹ_FLAGS_INT_ENABLED;
    px_چوٹی_دا_ڈھیر--;

    /* Next the general purpose registers. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x4444;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x5555;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x6666;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x7777;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x8888;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x9999;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xaaaa;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xbbbb;
    px_چوٹی_دا_ڈھیر--;
#جے_تعریف_شدہ __MSPGCC__
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xcccc;
#وإلا
    /* The MSP430 EABI expects the function parameter in R12. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
#جے_انت
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xdddd;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xeeee;
    px_چوٹی_دا_ڈھیر--;
#جے_تعریف_شدہ __MSPGCC__
    /* The mspgcc ABI expects the function parameter in R15. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
#وإلا
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xffff;
#جے_انت
    px_چوٹی_دا_ڈھیر--;

    /* The code generated by the mspgcc compiler does not maintain separate
     * stack and frame pointers. The portENTER_CRITICAL macro cannot therefore
     * use the stack as per other ports.  Instead a variable is used to keep
     * track of the critical section nesting.  This variable has to be stored
     * as part of the task context and is initially set to zero. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_تیاری_Timer_رکاوٹ();

    /* Restore the context of the first task that is going to run. */
    پورٹ_RESTORE_CONTEXT();

    /* Should not get here as the tasks are now running! */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* It is unlikely that the MSP430 port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch called by portYIELD or taskYIELD.
 *
 * The first thing we do is save the registers so we can use a naked attribute.
 */
فراغ v_پورٹ_Yield( فراغ ) __attribute__( ( naked ) );
فراغ v_پورٹ_Yield( فراغ )
{
    /* We want the stack of the task being saved to look exactly as if the task
     * was saved during a pre-emptive RTOS tick ISR.  Before calling an ISR the
     * msp430 places the status register onto the stack.  As this is a function
     * call and not an ISR we have to do this manually. */
    asm متطاير ( "push    r2" );
    _DINT();

    /* Save the context of the current task. */
    پورٹ_SAVE_CONTEXT();

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Restore the context of the new task. */
    پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.  This uses timer 0
 * but could alternatively use the watchdog timer or timer 1.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    /* Ensure the timer is stopped. */
    TACTL = 0;

    /* Run the timer of the ACLK. */
    TACTL = TASSEL_1;

    /* Clear everything to start with. */
    TACTL |= TACLR;

    /* Set the compare match value according to the tick rate we want. */
    TACCR0 = پورٹ_ACLK_FREQUENCY_HZ / config_TICK_شرح_HZ;

    /* Enable the interrupts. */
    TACCTL0 = CCIE;

    /* Start up clean. */
    TACTL |= TACLR;

    /* Up mode. */
    TACTL |= MC_1;
}
/*-----------------------------------------------------------*/

/*
 * The interrupt service routine used depends on whether the pre-emptive
 * scheduler is being used or not.
 */

#إذا configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */
    رکاوٹ( TIMERA0_سمتیہ ) فراغ prvTickISR( فراغ ) __attribute__( ( naked ) );
    رکاوٹ( TIMERA0_سمتیہ ) فراغ prvTickISR( فراغ )
    {
        /* Save the context of the interrupted task. */
        پورٹ_SAVE_CONTEXT();

        /* Increment the tick count then switch to the highest priority task
         * that is ready to run. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        /* Restore the context of the new task. */
        پورٹ_RESTORE_CONTEXT();
    }

#وإلا /* if configUSE_PREEMPTION == 1 */

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 */
    رکاوٹ( TIMERA0_سمتیہ ) فراغ prvTickISR( فراغ );
    رکاوٹ( TIMERA0_سمتیہ ) فراغ prvTickISR( فراغ )
    {
        xTaskIncrementTick();
    }
#جے_انت /* if configUSE_PREEMPTION == 1 */
