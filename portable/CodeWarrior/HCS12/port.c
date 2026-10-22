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
#ضمن "FreeRTOS.h"
#ضمن "task.h"


/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the HCS12 port.
 *----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ );

/* Interrupt service routines have to be in non-banked memory - as does the
scheduler startup function. */
#ہدایت کوڈ_SEG __NEAR_SEG NON_BANKED

    /* Manual context switch function.  This is the SWI ISR. */
    فراغ رکاوٹ v_پورٹ_Yield( فراغ );

    /* Tick context switch function.  This is the timer ISR. */
    فراغ رکاوٹ v_پورٹ_Tick_رکاوٹ( فراغ );

    /* Simply called by xPortStartScheduler().  xPortStartScheduler() does not
    start the scheduler directly because the header file containing the
    xPortStartScheduler() prototype is part of the common kernel code, and
    therefore cannot use the CODE_SEG pragma. */
    ساكن ادھار_Type_t x_Banked_شروع_Scheduler( فراغ );

#ہدایت کوڈ_SEG DEFAULT

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
critical section should not be left (i.e. interrupts should not be re-enabled)
until the nesting depth reaches 0.  This variable simply tracks the nesting
depth.  Each task maintains its own critical nesting depth variable so
uxCriticalNesting is saved and restored from the task stack during a context
switch. */
متطاير UBaseType_t uxCriticalNesting = 0xff;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_دا_ڈھیر, TaskFunction_t px_کوڈ, فراغ *pvParameters )
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
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) *( ((ڈھیر_Type_t *) (&px_کوڈ) ) + 1 );
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) *( ((ڈھیر_Type_t *) (&px_کوڈ) ) + 0 );
    px_چوٹی_دا_ڈھیر--;

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xff;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xee;
    px_چوٹی_دا_ڈھیر--;

    /* X register */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xdd;
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0xcc;
    px_چوٹی_دا_ڈھیر--;

    /* A register contains parameter high byte. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) *( ((ڈھیر_Type_t *) (&pvParameters) ) + 0 );
    px_چوٹی_دا_ڈھیر--;

    /* B register contains parameter low byte. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) *( ((ڈھیر_Type_t *) (&pvParameters) ) + 1 );
    px_چوٹی_دا_ڈھیر--;

    /* CCR: Note that when the task starts interrupts will be enabled since
    "I" bit of CCR is cleared */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00;
    px_چوٹی_دا_ڈھیر--;

    #جے_تعریف_شدہ BANKED_MODEL
        /* The page of the task. */
        *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) ( ( صحيح ) px_کوڈ );
        px_چوٹی_دا_ڈھیر--;
    #جے_انت

    /* Finally the critical nesting depth is initialised with 0 (not within
    a critical section). */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) 0x00;

    أرجع px_چوٹی_دا_ڈھیر;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    Tick_Timer_سیٹ_Freq_Hz( config_TICK_شرح_HZ );
    TickTimer_Enable();
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* xPortStartScheduler() does not start the scheduler directly because
    the header file containing the xPortStartScheduler() prototype is part
    of the common kernel code, and therefore cannot use the CODE_SEG pragma.
    Instead it simply calls the locally defined xBankedStartScheduler() -
    which does use the CODE_SEG pragma. */

    أرجع x_Banked_شروع_Scheduler();
}
/*-----------------------------------------------------------*/

#ہدایت کوڈ_SEG __NEAR_SEG NON_BANKED

ساكن ادھار_Type_t x_Banked_شروع_Scheduler( فراغ )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
    disabled when this function is called. */
    prv_تیاری_Timer_رکاوٹ();

    /* Restore the context of the first task. */
    پورٹ_RESTORE_CONTEXT();

    /* Simulate the end of an interrupt to start the scheduler off. */
    __asm( "rti" );

    /* Should not get here! */
    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are both interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
فراغ رکاوٹ v_پورٹ_Yield( فراغ )
{
    پورٹ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٹ_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
فراغ رکاوٹ v_پورٹ_Tick_رکاوٹ( فراغ )
{
    #إذا configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        پورٹ_SAVE_CONTEXT();

        /* Increment the tick ... */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        TFLG1 = 1;

        /* Restore the context of a task - which may be a different task
        to that interrupted. */
        پورٹ_RESTORE_CONTEXT();
    }
    #وإلا
    {
        xTaskIncrementTick();
        TFLG1 = 1;
    }
    #جے_انت
}

#ہدایت کوڈ_SEG DEFAULT
