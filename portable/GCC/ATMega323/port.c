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

#ضمن <stdlib.h>
#ضمن <avr/interrupt.h>

#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enables. */
#وصف_ڪريو پورٽ_FLAGS_INT_ENABLED                   ( ( ڍير_Type_t ) 0x80 )

/* Hardware constants for timer 1. */
#وصف_ڪريو پورٽ_CLEAR_COUNTER_ON_ميلاپ              ( ( uint8_t ) 0x08 )
#وصف_ڪريو پورٽ_PRESCALE_64                         ( ( uint8_t ) 0x03 )
#وصف_ڪريو پورٽ_CLOCK_PRESCALER                     ( ( uint32_t ) 64 )
#وصف_ڪريو پورٽ_COMPARE_ميلاپ_A_مداخلت_ENABLE    ( ( uint8_t ) 0x10 )

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

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

#وصف_ڪريو پورٽ_SAVE_CONTEXT()                               \
    asm متطاير ( "push   r0                      \n\t" \
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

#وصف_ڪريو پورٽ_RESTORE_CONTEXT()                            \
    asm متطاير ( "lds    r26, pxCurrentTCB       \n\t" \
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
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    uint16_t us_پتو;

    /* Place a few bytes of known values on the bottom of the stack.
     * This is just useful for debugging. */

    *px_چوٽي_جو_ڍير = 0x11;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x22;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = 0x33;
    px_چوٽي_جو_ڍير--;

    /* Simulate how the stack would look after a call to vPortYield() generated by
     * the compiler. */

    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

    /* The start of the task code will be popped off the stack last, so place
     * it on first. */
    us_پتو = ( uint16_t ) px_ڪوڊ;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* R0 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_FLAGS_INT_ENABLED;
    px_چوٽي_جو_ڍير--;


    /* Now the remaining registers.   The compiler expects R1 to be 0. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* R1 */
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
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x16; /* R16 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x17; /* R17 */
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

    /* Place the parameter on the stack in the expected location. */
    us_پتو = ( uint16_t ) pvParameters;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x26;  /* R26 X */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x27;  /* R27 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x28;  /* R28 Y */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x29;  /* R29 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x30;  /* R30 Z */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x031; /* R31 */
    px_چوٽي_جو_ڍير--;

    /*lint +e950 +e611 +e923 */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Setup the hardware to generate the tick. */
    prv_تياري_Timer_مداخلت();

    /* Restore the context of the first task that is going to run. */
    پورٽ_RESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler.  We will now
     * jump to the start of the task the context of which we have just restored. */
    asm متطاير ( "ret" );

    /* Should not get here. */
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
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
فراغ v_پورٽ_Yield( فراغ ) __attribute__( ( naked ) );
فراغ v_پورٽ_Yield( فراغ )
{
    پورٽ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٽ_RESTORE_CONTEXT();

    asm متطاير ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick.  This must be identical to
 * vPortYield() from the call to vTaskSwitchContext() onwards.  The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
فراغ v_پورٽ_Yield_From_Tick( فراغ ) __attribute__( ( naked ) );
فراغ v_پورٽ_Yield_From_Tick( فراغ )
{
    پورٽ_SAVE_CONTEXT();

    إذا( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    پورٽ_RESTORE_CONTEXT();

    asm متطاير ( "ret" );
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
    uc_هيٺيون_Byte = TIMSK;
    uc_هيٺيون_Byte |= پورٽ_COMPARE_ميلاپ_A_مداخلت_ENABLE;
    TIMSK = uc_هيٺيون_Byte;
}
/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler.  We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick().  The tick
 * count is incremented after the context is saved.
 */
    فراغ TIMER1_COMPA_vect( فراغ ) __attribute__( ( إشارة, naked ) );
    فراغ TIMER1_COMPA_vect( فراغ )
    {
        v_پورٽ_Yield_From_Tick();
        asm متطاير ( "reti" );
    }
#وإلا

/*
 * Tick ISR for the cooperative scheduler.  All this does is increment the
 * tick count.  We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 */
    فراغ TIMER1_COMPA_vect( فراغ ) __attribute__( ( إشارة ) );
    فراغ TIMER1_COMPA_vect( فراغ )
    {
        xTaskIncrementTick();
    }
#جيڪڏهن_پورو /* if configUSE_PREEMPTION == 1 */
