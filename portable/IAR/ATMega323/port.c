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

#अन्तर्भाव <stdlib.h>

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR/IAR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#परिभाषय पत्तनम्_FLAGS_INT_ENABLED                   ( ( राशिः_Type_t ) 0x80 )

/* Hardware constants for timer 1. */
#परिभाषय पत्तनम्_CLEAR_गणक_ON_मेलनम्              ( ( uint8_t ) 0x08 )
#परिभाषय पत्तनम्_PRESCALE_64                         ( ( uint8_t ) 0x03 )
#परिभाषय पत्तनम्_CLOCK_PRESCALER                     ( ( uint32_t ) 64 )
#परिभाषय पत्तनम्_COMPARE_मेलनम्_A_व्यवधानम्_ENABLE    ( ( uint8_t ) 0x10 )

/* The number of bytes used on the hardware stack by the task start address. */
#परिभाषय पत्तनम्_अष्टकानि_प्रयुक्तम्_BY_RETURN_स्थानाङ्कः        ( 2 )
/*-----------------------------------------------------------*/

/* Stores the critical section nesting.  This must not be initialised to 0.
 * It will be initialised when a task starts. */
#परिभाषय पत्तनम्_NO_CRITICAL_NESTING    ( ( UBaseType_t ) 0 )
UBaseType_t uxCriticalNesting = 0x50;


/*
 * Perform hardware setup to enable ticks from timer 1, compare match A.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * The IAR compiler does not have full support for inline assembler, so
 * these are defined in the portmacro assembler file.
 */
बाह्य शून्य v_पत्तनम्_Yield_From_Tick( शून्य );
बाह्य शून्य v_पत्तनम्_Start( शून्य );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    uint16_t us_स्थानाङ्कः;
    राशिः_Type_t * px_शिखरम्_सम्बन्धि_Hardware_राशिः;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */

    *px_शिखरम्_सम्बन्धि_राशिः = 0x11;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x22;
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = 0x33;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Remember where the top of the hardware stack is - this is required
     * below. */
    px_शिखरम्_सम्बन्धि_Hardware_राशिः = px_शिखरम्_सम्बन्धि_राशिः;


    /* Simulate how the stack would look after a call to vPortYield(). */

    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */



    /* The IAR compiler requires two stacks per task.  First there is the
     * hardware call stack which uses the AVR stack pointer.  Second there is the
     * software stack (local variables, parameter passing, etc.) which uses the
     * AVR Y register.
     *
     * This function places both stacks within the memory block passed in as the
     * first parameter.  The hardware stack is placed at the bottom of the memory
     * block.  A gap is then left for the hardware stack to grow.  Next the software
     * stack is placed.  The amount of space between the software and hardware
     * stacks is defined by configCALL_STACK_SIZE.
     *
     *
     *
     * The first part of the stack is the hardware stack.  Place the start
     * address of the task on the hardware stack. */
    us_स्थानाङ्कः = ( uint16_t ) px_संहिता;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    us_स्थानाङ्कः >>= 8;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;


    /* Leave enough space for the hardware stack before starting the software
     * stack.  The '- 2' is because we have already used two spaces for the
     * address of the start of the task. */
    px_शिखरम्_सम्बन्धि_राशिः -= ( config_CALL_राशिः_आकार - 2 );



    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00; /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_FLAGS_INT_ENABLED;
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Next place the address of the hardware stack.  This is required so
     * the AVR stack pointer can be restored to point to the hardware stack. */
    px_शिखरम्_सम्बन्धि_Hardware_राशिः -= पत्तनम्_अष्टकानि_प्रयुक्तम्_BY_RETURN_स्थानाङ्कः;
    us_स्थानाङ्कः = ( uint16_t ) px_शिखरम्_सम्बन्धि_Hardware_राशिः;

    /* SPL */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* SPH */
    us_स्थानाङ्कः >>= 8;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;



    /* Now the remaining registers. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x01; /* R1 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x02; /* R2 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03; /* R3 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04; /* R4 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x05; /* R5 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06; /* R6 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07; /* R7 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x08; /* R8 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09; /* R9 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10; /* R10 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11; /* R11 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12; /* R12 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x13; /* R13 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x14; /* R14 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x15; /* R15 */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* Place the parameter on the stack in the expected location. */
    us_स्थानाङ्कः = ( uint16_t ) pvParameters;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    us_स्थानाङ्कः >>= 8;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x18; /* R18 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x19; /* R19 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x20; /* R20 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x21; /* R21 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x22; /* R22 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x23; /* R23 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x24; /* R24 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x25; /* R25 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x26; /* R26 X */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x27; /* R27 */
    px_शिखरम्_सम्बन्धि_राशिः--;

    /* The Y register is not stored as it is used as the software stack and
     * gets saved into the task control block. */

    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x30;  /* R30 Z */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x031; /* R31 */

    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_NO_CRITICAL_NESTING; /* Critical nesting is zero when the task starts. */

    /*lint +e950 +e611 +e923 */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Setup the hardware to generate the tick. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Restore the context of the first task that is going to run.
     * Normally we would just call portRESTORE_CONTEXT() here, but as the IAR
     * compiler does not fully support inline assembler we have to make a call.*/
    v_पत्तनम्_Start();

    /* Should not get here! */
    प्रत्यागम pdTRUE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* It is unlikely that the AVR port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    uint32_t ul_Compare_मेलनम्;
    uint8_t uc_उच्चः_Byte, uc_नीचः_Byte;

    /* Using 16bit timer 1 to generate the tick.  Correct fuses must be
     * selected for the configCPU_CLOCK_HZ clock. */

    ul_Compare_मेलनम् = configCPU_CLOCK_HZ / config_TICK_दरः_HZ;

    /* We only have 16 bits so have to scale to get our required tick rate. */
    ul_Compare_मेलनम् /= पत्तनम्_CLOCK_PRESCALER;

    /* Adjust for correct value. */
    ul_Compare_मेलनम् -= ( uint32_t ) 1;

    /* Setup compare match value for compare match A.  Interrupts are disabled
     * before this is called so we need not worry here. */
    uc_नीचः_Byte = ( uint8_t ) ( ul_Compare_मेलनम् & ( uint32_t ) 0xff );
    ul_Compare_मेलनम् >>= 8;
    uc_उच्चः_Byte = ( uint8_t ) ( ul_Compare_मेलनम् & ( uint32_t ) 0xff );
    OCR1AH = uc_उच्चः_Byte;
    OCR1AL = uc_नीचः_Byte;

    /* Setup clock source and compare match behaviour. */
    uc_नीचः_Byte = पत्तनम्_CLEAR_गणक_ON_मेलनम् | पत्तनम्_PRESCALE_64;
    TCCR1B = uc_नीचः_Byte;

    /* Enable the interrupt - this is okay as interrupt are currently globally
     * disabled. */
    TIMSK |= पत्तनम्_COMPARE_मेलनम्_A_व्यवधानम्_ENABLE;
}
/*-----------------------------------------------------------*/

#यदि configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a __task attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */
    __task शून्य SIG_OUTPUT_COMPARE1A( शून्य )
    {
        v_पत्तनम्_Yield_From_Tick();
        asm ( "reti" );
    }

#अन्यथा

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 *
 * THE INTERRUPT VECTOR IS POPULATED IN portmacro.s90.  DO NOT INSTALL
 * IT HERE USING THE USUAL PRAGMA.
 */
    __interrupt शून्य SIG_OUTPUT_COMPARE1A( शून्य )
    {
        xTaskIncrementTick();
    }
#यदि_अन्तः /* if configUSE_PREEMPTION == 1 */
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    uxCriticalNesting--;

    यदि( uxCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
    {
        पत्तनम्_ENABLE_INTERRUPTS();
    }
}
