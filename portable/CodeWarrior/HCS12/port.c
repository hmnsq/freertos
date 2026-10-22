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

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"


/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the HCS12 port.
 *----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/* Interrupt service routines have to be in non-banked memory - as does the
scheduler startup function. */
#ਹਦਾਇਤ ਕੋਡ_SEG __NEAR_SEG NON_BANKED

    /* Manual context switch function.  This is the SWI ISR. */
    ਖਾਲੀ ਰੁਕਾਵਟ v_ਪੋਰਟ_Yield( ਖਾਲੀ );

    /* Tick context switch function.  This is the timer ISR. */
    ਖਾਲੀ ਰੁਕਾਵਟ v_ਪੋਰਟ_Tick_ਰੁਕਾਵਟ( ਖਾਲੀ );

    /* Simply called by xPortStartScheduler().  xPortStartScheduler() does not
    start the scheduler directly because the header file containing the
    xPortStartScheduler() prototype is part of the common kernel code, and
    therefore cannot use the CODE_SEG pragma. */
    ਸਥਿਰ ਅਧਾਰ_Type_t x_Banked_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ );

#ਹਦਾਇਤ ਕੋਡ_SEG DEFAULT

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
critical section should not be left (i.e. interrupts should not be re-enabled)
until the nesting depth reaches 0.  This variable simply tracks the nesting
depth.  Each task maintains its own critical nesting depth variable so
uxCriticalNesting is saved and restored from the task stack during a context
switch. */
ਅਸਥਿਰ UBaseType_t uxCriticalNesting = 0xff;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
    /*
        Place a few bytes of known values on the bottom of the stack.
        This can be uncommented to provide useful stack markers when debugging.

        *pxTopOfStack = ( StackType_t ) 0x11;
        pxTopOfStack--;
        *pxTopOfStack = ( StackType_t ) 0x22;
        pxTopOfStack--;
        *pxTopOfStack = ( StackType_t ) 0x33;
        pxTopOfStack--;
    */



    /* Setup the initial stack of the task.  The stack is set exactly as
    expected by the portRESTORE_CONTEXT() macro.  In this case the stack as
    expected by the HCS12 RTI instruction. */


    /* The address of the task function is placed in the stack byte at a time. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) *( ((ਢੇਰ_Type_t *) (&px_ਕੋਡ) ) + 1 );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) *( ((ਢੇਰ_Type_t *) (&px_ਕੋਡ) ) + 0 );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xff;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xee;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* X register */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xdd;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0xcc;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* A register contains parameter high byte. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) *( ((ਢੇਰ_Type_t *) (&pvParameters) ) + 0 );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* B register contains parameter low byte. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) *( ((ਢੇਰ_Type_t *) (&pvParameters) ) + 1 );
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* CCR: Note that when the task starts interrupts will be enabled since
    "I" bit of CCR is cleared */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BANKED_MODEL
        /* The page of the task. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ( ( ਪੂਰਨ ) px_ਕੋਡ );
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    #ਜੇ_ਅੰਤ

    /* Finally the critical nesting depth is initialised with 0 (not within
    a critical section). */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    Tick_Timer_ਸੈੱਟ_Freq_Hz( config_TICK_ਦਰ_HZ );
    TickTimer_Enable();
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* xPortStartScheduler() does not start the scheduler directly because
    the header file containing the xPortStartScheduler() prototype is part
    of the common kernel code, and therefore cannot use the CODE_SEG pragma.
    Instead it simply calls the locally defined xBankedStartScheduler() -
    which does use the CODE_SEG pragma. */

    ਵਾਪਸ x_Banked_ਸ਼ੁਰੂ_Scheduler();
}
/*-----------------------------------------------------------*/

#ਹਦਾਇਤ ਕੋਡ_SEG __NEAR_SEG NON_BANKED

ਸਥਿਰ ਅਧਾਰ_Type_t x_Banked_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
    disabled when this function is called. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Restore the context of the first task. */
    ਪੋਰਟ_RESTORE_CONTEXT();

    /* Simulate the end of an interrupt to start the scheduler off. */
    __asm( "rti" );

    /* Should not get here! */
    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are both interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
ਖਾਲੀ ਰੁਕਾਵਟ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    ਪੋਰਟ_SAVE_CONTEXT();
    vTaskSwitchContext();
    ਪੋਰਟ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
ਖਾਲੀ ਰੁਕਾਵਟ v_ਪੋਰਟ_Tick_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    #ਜੇ configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        ਪੋਰਟ_SAVE_CONTEXT();

        /* Increment the tick ... */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        TFLG1 = 1;

        /* Restore the context of a task - which may be a different task
        to that interrupted. */
        ਪੋਰਟ_RESTORE_CONTEXT();
    }
    #ਨਹੀਂਤਾਂ
    {
        xTaskIncrementTick();
        TFLG1 = 1;
    }
    #ਜੇ_ਅੰਤ
}

#ਹਦਾਇਤ ਕੋਡ_SEG DEFAULT
