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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"


/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the HCS12 port.
 *----------------------------------------------------------*/


/*
 * Configure a timer to generate the RTOS tick at the frequency specified
 * within FreeRTOSConfig.h.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/* Interrupt service routines have to be in non-banked memory - as does the
scheduler startup function. */
#निर्देशः संहिता_SEG __NEAR_SEG NON_BANKED

    /* Manual context switch function.  This is the SWI ISR. */
    शून्य व्यवधानम् v_पत्तनम्_Yield( शून्य );

    /* Tick context switch function.  This is the timer ISR. */
    शून्य व्यवधानम् v_पत्तनम्_Tick_व्यवधानम्( शून्य );

    /* Simply called by xPortStartScheduler().  xPortStartScheduler() does not
    start the scheduler directly because the header file containing the
    xPortStartScheduler() prototype is part of the common kernel code, and
    therefore cannot use the CODE_SEG pragma. */
    स्थिर आधारः_Type_t xBankedStartScheduler( शून्य );

#निर्देशः संहिता_SEG DEFAULT

/* Calls to portENTER_CRITICAL() can be nested.  When they are nested the
critical section should not be left (i.e. interrupts should not be re-enabled)
until the nesting depth reaches 0.  This variable simply tracks the nesting
depth.  Each task maintains its own critical nesting depth variable so
uxCriticalNesting is saved and restored from the task stack during a context
switch. */
चञ्चल UBaseType_t uxCriticalNesting = 0xff;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t *px_पत्तनम्_Initialise_राशिः( राशिः_Type_t *px_शिखरम्_सम्बन्धि_राशिः, TaskFunction_t px_संहिता, शून्य *pvParameters )
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
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) *( ((राशिः_Type_t *) (&px_संहिता) ) + 1 );
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) *( ((राशिः_Type_t *) (&px_संहिता) ) + 0 );
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next are all the registers that form part of the task context. */

    /* Y register */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xff;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xee;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* X register */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xdd;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0xcc;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* A register contains parameter high byte. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) *( ((राशिः_Type_t *) (&pvParameters) ) + 0 );
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* B register contains parameter low byte. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) *( ((राशिः_Type_t *) (&pvParameters) ) + 1 );
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* CCR: Note that when the task starts interrupts will be enabled since
    "I" bit of CCR is cleared */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00;
    px_शिखरम्_सम्बन्धि_राशिः--;

    #यदि_परिभाषितम् BANKED_MODEL
        /* The page of the task. */
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( ( पूर्णाङ्क ) px_संहिता );
        px_शिखरम्_सम्बन्धि_राशिः--;
    #यदि_अन्तः

    /* Finally the critical nesting depth is initialised with 0 (not within
    a critical section). */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* It is unlikely that the HCS12 port will get stopped. */
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    Tick_Timer_समुच्चयः_Freq_Hz( config_TICK_दरः_HZ );
    TickTimer_Enable();
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* xPortStartScheduler() does not start the scheduler directly because
    the header file containing the xPortStartScheduler() prototype is part
    of the common kernel code, and therefore cannot use the CODE_SEG pragma.
    Instead it simply calls the locally defined xBankedStartScheduler() -
    which does use the CODE_SEG pragma. */

    प्रत्यागम xBankedStartScheduler();
}
/*-----------------------------------------------------------*/

#निर्देशः संहिता_SEG __NEAR_SEG NON_BANKED

स्थिर आधारः_Type_t xBankedStartScheduler( शून्य )
{
    /* Configure the timer that will generate the RTOS tick.  Interrupts are
    disabled when this function is called. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Restore the context of the first task. */
    पत्तनम्_RESTORE_CONTEXT();

    /* Simulate the end of an interrupt to start the scheduler off. */
    __asm( "rti" );

    /* Should not get here! */
    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

/*
 * Context switch functions.  These are both interrupt service routines.
 */

/*
 * Manual context switch forced by calling portYIELD().  This is the SWI
 * handler.
 */
शून्य व्यवधानम् v_पत्तनम्_Yield( शून्य )
{
    पत्तनम्_SAVE_CONTEXT();
    vTaskSwitchContext();
    पत्तनम्_RESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * RTOS tick interrupt service routine.  If the cooperative scheduler is
 * being used then this simply increments the tick count.  If the
 * preemptive scheduler is being used a context switch can occur.
 */
शून्य व्यवधानम् v_पत्तनम्_Tick_व्यवधानम्( शून्य )
{
    #यदि configUSE_PREEMPTION == 1
    {
        /* A context switch might happen so save the context. */
        पत्तनम्_SAVE_CONTEXT();

        /* Increment the tick ... */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            vTaskSwitchContext();
        }

        TFLG1 = 1;

        /* Restore the context of a task - which may be a different task
        to that interrupted. */
        पत्तनम्_RESTORE_CONTEXT();
    }
    #अन्यथा
    {
        xTaskIncrementTick();
        TFLG1 = 1;
    }
    #यदि_अन्तः
}

#निर्देशः संहिता_SEG DEFAULT
