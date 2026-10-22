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
#ضمن "porthardware.h"
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#تعریف_کن پورت_FLAGS_INT_ENABLED    ( ( پشته_Type_t ) 0x80 )

/*-----------------------------------------------------------*/


#تعریف_کن پورت_بایتها_استفاده_شده_BY_RETURN_آدرس    2
#تعریف_کن پورت_NO_CRITICAL_NESTING             ( ( UBaseType_t ) 0 )

/* Stores the critical section nesting.  This must not be initialised to 0.
 * It will be initialised when a task starts. */
UBaseType_t uxCriticalNesting = 0x50;

/*
 * Setup timer to generate a tick interrupt.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ );

/*
 * The IAR compiler does not have full support for inline assembler, so
 * these are defined in the portmacro assembler file.
 */
خارجي فراغ v_پورت_Yield_From_Tick( فراغ );
خارجي فراغ v_پورت_شروع( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    uint16_t us_آدرس;
    پشته_Type_t * px_بالاترین_از_Hardware_پشته;

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
    px_بالاترین_از_Hardware_پشته = px_بالاترین_از_پشته;

    us_آدرس = ( uint16_t ) px_کد;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( us_آدرس & ( uint16_t ) 0x00ff );
    px_بالاترین_از_پشته--;

    us_آدرس >>= 8;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( us_آدرس & ( uint16_t ) 0x00ff );
    px_بالاترین_از_پشته--;

    /* Leave enough space for the hardware stack before starting the software
     * stack.  The '- 2' is because we have already used two spaces for the
     * address of the start of the task. */
    px_بالاترین_از_پشته -= ( config_CALL_پشته_اندازه - 2 );

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00; /* R0 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_FLAGS_INT_ENABLED;
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x00; /* RAMPZ */
    px_بالاترین_از_پشته--;

    /* Next place the address of the hardware stack.  This is required so
     * the AVR stack pointer can be restored to point to the hardware stack. */
    px_بالاترین_از_Hardware_پشته -= پورت_بایتها_استفاده_شده_BY_RETURN_آدرس;
    us_آدرس = ( uint16_t ) px_بالاترین_از_Hardware_پشته;

    /* SPL */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( us_آدرس & ( uint16_t ) 0x00ff );
    px_بالاترین_از_پشته--;

    /* SPH */
    us_آدرس >>= 8;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( us_آدرس & ( uint16_t ) 0x00ff );
    px_بالاترین_از_پشته--;

    /* Now the remaining registers. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x01; /* R1 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x02; /* R2 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03; /* R3 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04; /* R4 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x05; /* R5 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06; /* R6 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07; /* R7 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08; /* R8 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09; /* R9 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10; /* R10 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11; /* R11 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12; /* R12 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x13; /* R13 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x14; /* R14 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x15; /* R15 */
    px_بالاترین_از_پشته--;

    /* Place the parameter on the stack in the expected location. */
    us_آدرس = ( uint16_t ) pvParameters;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( us_آدرس & ( uint16_t ) 0x00ff );
    px_بالاترین_از_پشته--;

    us_آدرس >>= 8;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) ( us_آدرس & ( uint16_t ) 0x00ff );
    px_بالاترین_از_پشته--;

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x18; /* R18 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x19; /* R19 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x20; /* R20 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x21; /* R21 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x22; /* R22 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x23; /* R23 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x24; /* R24 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x25; /* R25 */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x26; /* R26 X */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x27; /* R27 */
    px_بالاترین_از_پشته--;

    /* The Y register is not stored as it is used as the software stack and
     * gets saved into the task control block. */

    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x30;  /* R30 Z */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x031; /* R31 */

    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = پورت_NO_CRITICAL_NESTING; /* Critical nesting is zero when the task starts. */

    /*lint +e950 +e611 +e923 */

    أرجع px_بالاترین_از_پشته;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* Setup the hardware to generate the tick. */
    prv_راهاندازی_Timer_وقفه();

    /* Restore the context of the first task that is going to run.
     * Normally we would just call portRESTORE_CONTEXT() here, but as the IAR
     * compiler does not fully support inline assembler we have to make a call.*/
    v_پورت_شروع();

    /* Should not get here. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* vPortEndScheduler is not implemented in this port. */
}

/*-----------------------------------------------------------*/

/*
 * Setup timer to generate a tick interrupt.
 */
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    TICK_init();
}

/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */

    __task فراغ TICK_INT( فراغ )
    {
        v_پورت_Yield_From_Tick();
        asm ( "reti" );
    }
#وإلا

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 */

    __interrupt فراغ TICK_INT( فراغ )
    {
        /* Clear tick interrupt flag. */
        INT_FLAGS = INT_ماسک;

        xTaskIncrementTick();
    }
#پایان_اگر /* if configUSE_PREEMPTION == 1 */

/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    پورت_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}

/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    uxCriticalNesting--;

    إذا( uxCriticalNesting == پورت_NO_CRITICAL_NESTING )
    {
        پورت_ENABLE_INTERRUPTS();
    }
}
