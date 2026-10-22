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
 *
 * Changes from V2.6.0
 *
 + AVR port - Replaced the inb() and outb() functions with direct memory
 +    access.  This allows the port to be built with the 20050414 build of
 +    WinAVR.
 */

#شامل <stdlib.h>
#شامل <avr/interrupt.h>

#شامل "FreeRTOS.h"
#شامل "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#تعریف_کرو پورٹ_FLAGS_INT_ENABLED                   ( ( ڈھیر_Type_t ) 0x80 )

/* Hardware constants for timer 1. */
#تعریف_کرو پورٹ_CLEAR_شمار_ON_مطابقت              ( ( uint8_t ) 0x08 )
#تعریف_کرو پورٹ_PRESCALE_64                         ( ( uint8_t ) 0x03 )
#تعریف_کرو پورٹ_CLOCK_PRESCALER                     ( ( uint32_t ) 64 )
#تعریف_کرو پورٹ_COMPARE_مطابقت_A_مداخلت_ENABLE    ( ( uint8_t ) 0x10 )

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
قسمتعریف خالی TCB_t;
خارجی متلون TCB_t * متلون pxCurrentTCB;

/*-----------------------------------------------------------*/

/*
 * Macro to save all the general purpose registers, the save the stack pointer
 * into the TCB.
 *
 * The first thing we do is save the flags then disable interrupts.  This is to
 * guard our stack against having a context switch interrupt after we have already
 * pushed the registers onto the stack - causing the 32 registers to be on the
 * stack twice.
 *
 * r1 is set to zero as the compiler expects it to be thus, however some
 * of the math routines make use of R1.
 *
 * The interrupts will have been disabled during the call to portSAVE_CONTEXT()
 * so we need not worry about reading/writing to the stack pointer.
 */

#تعریف_کرو پورٹ_SAVE_CONTEXT()                               \
    asm متلون ( "push   r0                      \n\t" \
                   "in     r0, __SREG__            \n\t" \
                   "cli                            \n\t" \
                   "push   r0                      \n\t" \
                   "push   r1                      \n\t" \
                   "clr    r1                      \n\t" \
                   "push   r2                      \n\t" \
                   "push   r3                      \n\t" \
                   "push   r4                      \n\t" \
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
                   "push   r16                     \n\t" \
                   "push   r17                     \n\t" \
                   "push   r18                     \n\t" \
                   "push   r19                     \n\t" \
                   "push   r20                     \n\t" \
                   "push   r21                     \n\t" \
                   "push   r22                     \n\t" \
                   "push   r23                     \n\t" \
                   "push   r24                     \n\t" \
                   "push   r25                     \n\t" \
                   "push   r26                     \n\t" \
                   "push   r27                     \n\t" \
                   "push   r28                     \n\t" \
                   "push   r29                     \n\t" \
                   "push   r30                     \n\t" \
                   "push   r31                     \n\t" \
                   "lds    r26, pxCurrentTCB       \n\t" \
                   "lds    r27, pxCurrentTCB + 1   \n\t" \
                   "in     r0, 0x3d                \n\t" \
                   "st     x+, r0                  \n\t" \
                   "in     r0, 0x3e                \n\t" \
                   "st     x+, r0                  \n\t" \
                   );

/*
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer.
 */

#تعریف_کرو پورٹ_RESTORE_CONTEXT()                            \
    asm متلون ( "lds    r26, pxCurrentTCB       \n\t" \
                   "lds    r27, pxCurrentTCB + 1   \n\t" \
                   "ld     r28, x+                 \n\t" \
                   "out    __SP_L__, r28           \n\t" \
                   "ld     r29, x+                 \n\t" \
                   "out    __SP_H__, r29           \n\t" \
                   "pop    r31                     \n\t" \
                   "pop    r30                     \n\t" \
                   "pop    r29                     \n\t" \
                   "pop    r28                     \n\t" \
                   "pop    r27                     \n\t" \
                   "pop    r26                     \n\t" \
                   "pop    r25                     \n\t" \
                   "pop    r24                     \n\t" \
                   "pop    r23                     \n\t" \
                   "pop    r22                     \n\t" \
                   "pop    r21                     \n\t" \
                   "pop    r20                     \n\t" \
                   "pop    r19                     \n\t" \
                   "pop    r18                     \n\t" \
                   "pop    r17                     \n\t" \
                   "pop    r16                     \n\t" \
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
                   "pop    r3                      \n\t" \
                   "pop    r2                      \n\t" \
                   "pop    r1                      \n\t" \
                   "pop    r0                      \n\t" \
                   "out    __SREG__, r0            \n\t" \
                   "pop    r0                      \n\t" \
                   );

/*-----------------------------------------------------------*/

/*
 * Perform hardware setup to enable ticks from timer 1, compare match A.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    uint16_t us_پتہ;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */

    *px_چوٹی_کا_ڈھیر = 0x11;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x22;
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = 0x33;
    px_چوٹی_کا_ڈھیر--;

    /* Simulate how the stack would look after a call to vPortYield() generated by
     * the compiler. */

    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

    /* The start of the task code will be popped off the stack last, so place
     * it on first. */
    us_پتہ = ( uint16_t ) px_رمز;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    us_پتہ >>= 8;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00; /* R0 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = پورٹ_FLAGS_INT_ENABLED;
    px_چوٹی_کا_ڈھیر--;


    /* Now the remaining registers.   The compiler expects R1 to be 0. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x00; /* R1 */
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
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x16; /* R16 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x17; /* R17 */
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

    /* Place the parameter on the stack in the expected location. */
    us_پتہ = ( uint16_t ) pvParameters;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    us_پتہ >>= 8;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) ( us_پتہ & ( uint16_t ) 0x00ff );
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x26;  /* R26 X */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x27;  /* R27 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x28;  /* R28 Y */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x29;  /* R29 */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x30;  /* R30 Z */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x031; /* R31 */
    px_چوٹی_کا_ڈھیر--;

    /*lint +e950 +e611 +e923 */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Setup the hardware to generate the tick. */
    prv_تیاری_Timer_مداخلت();

    /* Restore the context of the first task that is going to run. */
    پورٹ_RESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler.  We will now
     * jump to the start of the task the context of which we have just restored. */
    asm متلون ( "ret" );

    /* Should not get here. */
    واپس pdTRUE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the AVR port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
خالی v_پورٹ_Yield( خالی ) __attribute__( ( naked ) );
خالی v_پورٹ_Yield( خالی )
{
    پورٹ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٹ_RESTORE_CONTEXT();

    asm متلون ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick.  This must be identical to
 * vPortYield() from the call to vTaskSwitchContext() onwards.  The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
خالی v_پورٹ_Yield_From_Tick( خالی ) __attribute__( ( naked ) );
خالی v_پورٹ_Yield_From_Tick( خالی )
{
    پورٹ_SAVE_CONTEXT();

    اگر( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    پورٹ_RESTORE_CONTEXT();

    asm متلون ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    uint32_t ul_Compare_مطابقت;
    uint8_t uc_بلند_Byte, uc_کم_Byte;

    /* Using 16bit timer 1 to generate the tick.  Correct fuses must be
     * selected for the configCPU_CLOCK_HZ clock. */

    ul_Compare_مطابقت = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

    /* We only have 16 bits so have to scale to get our required tick rate. */
    ul_Compare_مطابقت /= پورٹ_CLOCK_PRESCALER;

    /* Adjust for correct value. */
    ul_Compare_مطابقت -= ( uint32_t ) 1;

    /* Setup compare match value for compare match A.  Interrupts are disabled
     * before this is called so we need not worry here. */
    uc_کم_Byte = ( uint8_t ) ( ul_Compare_مطابقت & ( uint32_t ) 0xff );
    ul_Compare_مطابقت >>= 8;
    uc_بلند_Byte = ( uint8_t ) ( ul_Compare_مطابقت & ( uint32_t ) 0xff );
    OCR1AH = uc_بلند_Byte;
    OCR1AL = uc_کم_Byte;

    /* Setup clock source and compare match behaviour. */
    uc_کم_Byte = پورٹ_CLEAR_شمار_ON_مطابقت | پورٹ_PRESCALE_64;
    TCCR1B = uc_کم_Byte;

    /* Enable the interrupt - this is okay as interrupt are currently globally
     * disabled. */
    uc_کم_Byte = TIMSK;
    uc_کم_Byte |= پورٹ_COMPARE_مطابقت_A_مداخلت_ENABLE;
    TIMSK = uc_کم_Byte;
}
/*-----------------------------------------------------------*/

#اگر configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */
    خالی TIMER1_COMPA_vect( خالی ) __attribute__( ( اشارہ, naked ) );
    خالی TIMER1_COMPA_vect( خالی )
    {
        v_پورٹ_Yield_From_Tick();
        asm متلون ( "reti" );
    }
#ورنہ

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 */
    خالی TIMER1_COMPA_vect( خالی ) __attribute__( ( اشارہ ) );
    خالی TIMER1_COMPA_vect( خالی )
    {
        xTaskIncrementTick();
    }
#اگر_ختم /* if configUSE_PREEMPTION == 1 */
