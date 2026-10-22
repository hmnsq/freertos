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

#ضمن <stdlib.h>

#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR/IAR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#وصف_ڪريو پورٽ_FLAGS_INT_ENABLED                   ( ( ڍير_Type_t ) 0x80 )

/* Hardware constants for timer 1. */
#وصف_ڪريو پورٽ_CLEAR_COUNTER_ON_ميلاپ              ( ( uint8_t ) 0x08 )
#وصف_ڪريو پورٽ_PRESCALE_64                         ( ( uint8_t ) 0x03 )
#وصف_ڪريو پورٽ_CLOCK_PRESCALER                     ( ( uint32_t ) 64 )
#وصف_ڪريو پورٽ_COMPARE_ميلاپ_A_مداخلت_ENABLE    ( ( uint8_t ) 0x10 )

/* The number of bytes used on the hardware stack by the task start address. */
#وصف_ڪريو پورٽ_بائيٽون_استعمال_ٿيل_BY_RETURN_پتو        ( 2 )
/*-----------------------------------------------------------*/

/* Stores the critical section nesting.  This must not be initialised to 0.
 * It will be initialised when a task starts. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING    ( ( UBaseType_t ) 0 )
UBaseType_t uxCriticalNesting = 0x50;


/*
 * Perform hardware setup to enable ticks from timer 1, compare match A.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*
 * The IAR compiler does not have full support for inline assembler, so
 * these are defined in the portmacro assembler file.
 */
خارجي فراغ v_پورٽ_Yield_From_Tick( فراغ );
خارجي فراغ v_پورٽ_شروعات( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    uint16_t us_پتو;
    ڍير_Type_t * px_چوٽي_جو_Hardware_ڍير;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */

    *px_چوٽي_جو_ڍير = 0x11;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x22;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x33;
    px_چوٽي_جو_ڍير--;

    /* Remember where the top of the hardware stack is - this is required
     * below. */
    px_چوٽي_جو_Hardware_ڍير = px_چوٽي_جو_ڍير;


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
    us_پتو = ( uint16_t ) px_ڪوڊ;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;


    /* Leave enough space for the hardware stack before starting the software
     * stack.  The '- 2' is because we have already used two spaces for the
     * address of the start of the task. */
    px_چوٽي_جو_ڍير -= ( config_CALL_ڍير_سائيز - 2 );



    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* R0 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_FLAGS_INT_ENABLED;
    px_چوٽي_جو_ڍير--;

    /* Next place the address of the hardware stack.  This is required so
     * the AVR stack pointer can be restored to point to the hardware stack. */
    px_چوٽي_جو_Hardware_ڍير -= پورٽ_بائيٽون_استعمال_ٿيل_BY_RETURN_پتو;
    us_پتو = ( uint16_t ) px_چوٽي_جو_Hardware_ڍير;

    /* SPL */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    /* SPH */
    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;



    /* Now the remaining registers. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x01; /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x02; /* R2 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03; /* R3 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04; /* R4 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x05; /* R5 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06; /* R6 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07; /* R7 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08; /* R8 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09; /* R9 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10; /* R10 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11; /* R11 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12; /* R12 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x13; /* R13 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x14; /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x15; /* R15 */
    px_چوٽي_جو_ڍير--;

    /* Place the parameter on the stack in the expected location. */
    us_پتو = ( uint16_t ) pvParameters;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x18; /* R18 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x19; /* R19 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x20; /* R20 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x21; /* R21 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x22; /* R22 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x23; /* R23 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x24; /* R24 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x25; /* R25 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x26; /* R26 X */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x27; /* R27 */
    px_چوٽي_جو_ڍير--;

    /* The Y register is not stored as it is used as the software stack and
     * gets saved into the task control block. */

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x30;  /* R30 Z */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x031; /* R31 */

    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_NESTING; /* Critical nesting is zero when the task starts. */

    /*lint +e950 +e611 +e923 */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Setup the hardware to generate the tick. */
    prv_تياري_Timer_مداخلت();

    /* Restore the context of the first task that is going to run.
     * Normally we would just call portRESTORE_CONTEXT() here, but as the IAR
     * compiler does not fully support inline assembler we have to make a call.*/
    v_پورٽ_شروعات();

    /* Should not get here! */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the AVR port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    uint32_t ul_Compare_ميلاپ;
    uint8_t uc_مٿاهون_Byte, uc_هيٺيون_Byte;

    /* Using 16bit timer 1 to generate the tick.  Correct fuses must be
     * selected for the configCPU_CLOCK_HZ clock. */

    ul_Compare_ميلاپ = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

    /* We only have 16 bits so have to scale to get our required tick rate. */
    ul_Compare_ميلاپ /= پورٽ_CLOCK_PRESCALER;

    /* Adjust for correct value. */
    ul_Compare_ميلاپ -= ( uint32_t ) 1;

    /* Setup compare match value for compare match A.  Interrupts are disabled
     * before this is called so we need not worry here. */
    uc_هيٺيون_Byte = ( uint8_t ) ( ul_Compare_ميلاپ & ( uint32_t ) 0xff );
    ul_Compare_ميلاپ >>= 8;
    uc_مٿاهون_Byte = ( uint8_t ) ( ul_Compare_ميلاپ & ( uint32_t ) 0xff );
    OCR1AH = uc_مٿاهون_Byte;
    OCR1AL = uc_هيٺيون_Byte;

    /* Setup clock source and compare match behaviour. */
    uc_هيٺيون_Byte = پورٽ_CLEAR_COUNTER_ON_ميلاپ | پورٽ_PRESCALE_64;
    TCCR1B = uc_هيٺيون_Byte;

    /* Enable the interrupt - this is okay as interrupt are currently globally
     * disabled. */
    TIMSK |= پورٽ_COMPARE_ميلاپ_A_مداخلت_ENABLE;
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a __task attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */
    __task فراغ SIG_OUTPUT_COMPARE1A( فراغ )
    {
        v_پورٽ_Yield_From_Tick();
        asm ( "reti" );
    }

#وإلا

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 *
 * THE INTERRUPT VECTOR IS POPULATED IN portmacro.s90.  DO NOT INSTALL
 * IT HERE USING THE USUAL PRAGMA.
 */
    __interrupt فراغ SIG_OUTPUT_COMPARE1A( فراغ )
    {
        xTaskIncrementTick();
    }
#جيڪڏهن_پورو /* if configUSE_PREEMPTION == 1 */
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    uxCriticalNesting--;

    إذا( uxCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
    {
        پورٽ_ENABLE_INTERRUPTS();
    }
}
