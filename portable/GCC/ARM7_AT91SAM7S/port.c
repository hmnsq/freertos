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
* Implementation of functions defined in portable.h for the ARM7 port.
*
* Components that can be compiled to either ARM or THUMB mode are
* contained in this file.  The ISR routines, which can only be compiled
* to ARM mode are contained in portISR.c.
*----------------------------------------------------------*/

/* Standard includes. */
#अन्तर्भाव <stdlib.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Processor constants. */
#अन्तर्भाव "AT91SAM7X256.h"

/* Constants required to setup the task context. */
#परिभाषय पत्तनम्_INITIAL_SPSR                   ( ( राशिः_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#परिभाषय पत्तनम्_THUMB_बहुलकम्_BIT                 ( ( राशिः_Type_t ) 0x20 )
#परिभाषय पत्तनम्_INSTRUCTION_आकार               ( ( राशिः_Type_t ) 4 )
#परिभाषय पत्तनम्_NO_CRITICAL_SECTION_NESTING    ( ( राशिः_Type_t ) 0 )

/* Constants required to setup the tick ISR. */
#परिभाषय पत्तनम्_ENABLE_TIMER                   ( ( uint8_t ) 0x01 )
#परिभाषय पत्तनम्_PRESCALE_मानम्                 0x00
#परिभाषय पत्तनम्_व्यवधानम्_ON_मेलनम्             ( ( uint32_t ) 0x01 )
#परिभाषय पत्तनम्_RESET_गणनम्_ON_मेलनम्           ( ( uint32_t ) 0x02 )

/* Constants required to setup the PIT. */
#परिभाषय पत्तनम्_PIT_CLOCK_भाजकः              ( ( uint32_t ) 16 )
#परिभाषय पत्तनम्_PIT_गणक_मानम्              ( ( ( configCPU_CLOCK_HZ / पत्तनम्_PIT_CLOCK_भाजकः ) / 1000UL ) * पत्तनम्_TICK_PERIOD_MS )

#परिभाषय पत्तनम्_INT_LEVEL_SENSITIVE            0
#परिभाषय पत्तनम्_PIT_ENABLE                     ( ( uint16_t ) 0x1 << 24 )
#परिभाषय पत्तनम्_PIT_INT_ENABLE                 ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * The scheduler can only be started from ARM mode, so
 * vPortISRStartFirstSTask() is defined in portISR.c.
 */
बाह्य शून्य v_पत्तनम्_ISRStart_First_Task( शून्य );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    राशिः_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_शिखरम्_सम्बन्धि_राशिः;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता + पत्तनम्_INSTRUCTION_आकार;
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00000000;    /* R14 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12121212;    /* R12 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11111111;    /* R11 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10101010;    /* R10 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09090909;    /* R9 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x08080808;    /* R8 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07070707;    /* R7 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06060606;    /* R6 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x05050505;    /* R5 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04040404;    /* R4 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03030303;    /* R3 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x02020202;    /* R2 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x01010101;    /* R1 */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The last thing onto the stack is the status register, which is set for
     * system mode, with interrupts enabled. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_INITIAL_SPSR;

    #यदि_परिभाषितम् THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_शिखरम्_सम्बन्धि_राशिः |= पत्तनम्_THUMB_बहुलकम्_BIT;
    }
    #यदि_अन्तः

    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Some optimisation levels use the stack differently to others.  This
     * means the interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_CRITICAL_SECTION_NESTING;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Start the first task. */
    v_पत्तनम्_ISRStart_First_Task();

    /* Should not get here! */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the timer 0 to generate the tick interrupts at the required frequency.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    AT91PS_PITC pxPIT = AT91_C_आधारः_PITC;

    /* Setup the AIC for PIT interrupts.  The interrupt routine chosen depends
     * on whether the preemptive or cooperative scheduler is being used. */
    #यदि configUSE_PREEMPTION == 0
        बाह्य शून्य( vNonPreemptiveTick ) ( शून्य );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_प्राक्_HIGHEST, पत्तनम्_INT_LEVEL_SENSITIVE, ( शून्य ( * )( शून्य ) )vNonPreemptiveTick );
    #अन्यथा
        बाह्य शून्य( vPreemptiveTick )( शून्य );
        AT91F_AIC_ConfigureIt( AT91C_ID_SYS, AT91_C_AIC_प्राक्_HIGHEST, पत्तनम्_INT_LEVEL_SENSITIVE, ( शून्य ( * )( शून्य ) )vPreemptiveTick );
    #यदि_अन्तः

    /* Configure the PIT period. */
    pxPIT->PITC_PIMR = पत्तनम्_PIT_ENABLE | पत्तनम्_PIT_INT_ENABLE | पत्तनम्_PIT_गणक_मानम्;

    /* Enable the interrupt.  Global interrupts are disabled at this point so
     * this is safe. */
    AT91_C_आधारः_AIC->AIC_IECR = 0x1 << AT91C_ID_SYS;
}
/*-----------------------------------------------------------*/
