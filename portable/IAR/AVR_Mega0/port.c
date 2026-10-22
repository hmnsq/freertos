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

#شامل <stdlib.h>
#شامل "porthardware.h"
#شامل "FreeRTOS.h"
#شامل "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#تعریف_کرو پورٹ_FLAGS_INT_ENABLED    ( ( ڈھیر_Type_t ) 0x80 )

/*-----------------------------------------------------------*/


#تعریف_کرو پورٹ_بائٹیں_مستعمل_BY_RETURN_پتہ    2
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING             ( ( UBaseType_t ) 0 )

/* Stores the critical section nesting.  This must not be initialised to 0.
 * It will be initialised when a task starts. */
UBaseType_t uxCriticalNesting = 0x50;

/*
 * Setup timer to generate a tick interrupt.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*
 * The IAR compiler does not have full support for inline assembler, so
 * these are defined in the portmacro assembler file.
 */
خارجی خالی v_پورٹ_Yield_From_Tick( خالی );
خارجی خالی v_پورٹ_آغاز( خالی );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    uint16_t us_پتہ;
    ڈھیر_Type_t * px_چوٹی_کا_Hardware_ڈھیر;

    /* Simulate how the stack would look after a call to vPortYield(). */

    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

    /* The IAR compiler requires two stacks per task.  First there is the
     * hardware call stack which uses the AVR stack pointer.  Second there is the
     * software stack (local variables, parameter passing, etc.) which uses the
     * AVR Y register.
     * This function places both stacks within the memory block passed in as the
     * first parameter.  The hardware stack is placed at the bottom of the memory
     * block.  A gap is then left for the hardware stack to grow.  Next the software
     * stack is placed.  The amount of space between the software and hardware
     * stacks is defined by configCALL_STACK_SIZE.
     * The first part of the stack is the hardware stack.  Place the start
     * address of the task on the hardware stack. */

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */
    /**pxTopOfStack = 0x11; */
    /*pxTopOfStack--; */
    /**pxTopOfStack = 0x22; */
    /*pxTopOfStack--; */
    /**pxTopOfStack = 0x33; */
    /*pxTopOfStack--; */

    /* Remember where the top of the hardware stack is - this is required
     * below. */
    px_چوٹی_کا_Hardware_ڈھیر = px_چوٹی_کا_ڈھیر;

    us_پتہ = ( uint16_t ) px_رمز;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    us_پتہ >>= 8;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    /* Leave enough space for the hardware stack before starting the software
     * stack.  The '- 2' is because we have already used two spaces for the
     * address of the start of the task. */
    px_چوٹی_کا_ڈھیر -= ( config_CALL_ڈھیر_سائز - 2 );

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00; /* R0 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_FLAGS_INT_ENABLED;
    px_چوٹی_کا_ڈھیر--;

    /* Next place the address of the hardware stack.  This is required so
     * the AVR stack pointer can be restored to point to the hardware stack. */
    px_چوٹی_کا_Hardware_ڈھیر -= پورٹ_بائٹیں_مستعمل_BY_RETURN_پتہ;
    us_پتہ = ( uint16_t ) px_چوٹی_کا_Hardware_ڈھیر;

    /* SPL */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    /* SPH */
    us_پتہ >>= 8;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    /* Now the remaining registers. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x01; /* R1 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x02; /* R2 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03; /* R3 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04; /* R4 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x05; /* R5 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06; /* R6 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07; /* R7 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08; /* R8 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09; /* R9 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10; /* R10 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11; /* R11 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12; /* R12 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x13; /* R13 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x14; /* R14 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x15; /* R15 */
    px_چوٹی_کا_ڈھیر--;

    /* Place the parameter on the stack in the expected location. */
    us_پتہ = ( uint16_t ) pvParameters;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    us_پتہ >>= 8;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x18; /* R18 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x19; /* R19 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x20; /* R20 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x21; /* R21 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x22; /* R22 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x23; /* R23 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x24; /* R24 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x25; /* R25 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x26; /* R26 X */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x27; /* R27 */
    px_چوٹی_کا_ڈھیر--;

    /* The Y register is not stored as it is used as the software stack and
     * gets saved into the task control block. */

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x30;  /* R30 Z */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x031; /* R31 */

    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_NO_CRITICAL_NESTING; /* Critical nesting is zero when the task starts. */

    /*lint +e950 +e611 +e923 */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Setup the hardware to generate the tick. */
    prv_تیاری_Timer_مداخلت();

    /* Restore the context of the first task that is going to run.
     * Normally we would just call portRESTORE_CONTEXT() here, but as the IAR
     * compiler does not fully support inline assembler we have to make a call.*/
    v_پورٹ_آغاز();

    /* Should not get here. */
    واپس pdTRUE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* vPortEndScheduler is not implemented in this port. */
}

/*-----------------------------------------------------------*/

/*
 * Setup timer to generate a tick interrupt.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    TICK_init();
}

/*-----------------------------------------------------------*/

#اگر configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */

    __task خالی TICK_INT( خالی )
    {
        v_پورٹ_Yield_From_Tick();
        asm ( "reti" );
    }
#ورنہ

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 */

    __interrupt خالی TICK_INT( خالی )
    {
        /* Clear tick interrupt flag. */
        INT_FLAGS = INT_نقاب;

        xTaskIncrementTick();
    }
#اگر_ختم /* if configUSE_PREEMPTION == 1 */

/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    uxCriticalNesting--;

    اگر( uxCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
