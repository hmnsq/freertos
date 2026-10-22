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


#అన్తర్భావ <stdlib.h>

#అన్తర్భావ <avr/io.h>
#అన్తర్భావ <avr/interrupt.h>
#అన్తర్భావ <avr/wdt.h>

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enabled. */
#నిర్వచించు పోర్టు_FLAGS_INT_ENABLED    ( ( దొంతర_Type_t ) 0x80 )

#ఒకవేళ defined( పోర్టు_USE_WDTO )
    #warning "Watchdog Timer used for scheduler."
    #నిర్వచించు పోర్టు_SCHEDULER_ISR    WDT_vect

#లేదావేళ defined( పోర్టు_USE_TIMER0 )
/* Hardware constants for Timer0. */
    #warning "Timer0 used for scheduler."
    #నిర్వచించు పోర్టు_SCHEDULER_ISR                       TIMER0_COMPA_vect
    #నిర్వచించు పోర్టు_CLEAR_COUNTER_ON_సరిపోలిక              ( ( uint8_t ) _BV( WGM01 ) )
    #నిర్వచించు పోర్టు_PRESCALE_1024                       ( ( uint8_t ) ( _BV( CS02 ) | _BV( CS00 ) ) )
    #నిర్వచించు పోర్టు_CLOCK_PRESCALER                     ( ( uint32_t ) 1024 )
    #నిర్వచించు పోర్టు_COMPARE_సరిపోలిక_A_అంతరాయం_ENABLE    ( ( uint8_t ) _BV( OCIE0A ) )
    #నిర్వచించు పోర్టు_OCRL                                OCR0A
    #నిర్వచించు పోర్టు_TCCRa                               TCCR0A
    #నిర్వచించు పోర్టు_TCCRb                               TCCR0B
    #నిర్వచించు పోర్టు_TIMSK                               TIMSK0
    #నిర్వచించు పోర్టు_TIFR                                TIFR0

#లేకపోతే /* if defined( portUSE_WDTO ) */
    #దోషం "No Timer defined for scheduler"
#అయితే_ముగింపు /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
రకనిర్వచనం శూన్య TCB_t;
బాహ్య అస్థిర TCB_t * అస్థిర pxCurrentTCB;

/*-----------------------------------------------------------*/

/**
 *  Enable the watchdog timer, configuring it for expire after
 *  (value) timeout (which is a combination of the WDP0
 *  through WDP3 bits).
 *
 *  This function is derived from <avr/wdt.h> but enables only
 *  the interrupt bit (WDIE), rather than the reset bit (WDE).
 *
 *  Can't find it documented but the WDT, once enabled,
 *  rolls over and fires a new interrupt each time.
 *
 *  See also the symbolic constants WDTO_15MS et al.
 *
 *  Updated to match avr-libc 2.0.0
 */

#ఒకవేళ defined( పోర్టు_USE_WDTO )

    స్థిర __inline__
    __attribute__( ( __always_inline__ ) )
    శూన్య wdt_అంతరాయం_enable( స్థిరరాశి uint8_t విలువ )
    {
        ఒకవేళ( _SFR_IO_REG_P( _WD_CONTROL_REG ) )
        {
            __asm__ __volatile__ (
                "in __tmp_reg__,__SREG__"   "\n\t"
                "cli"                       "\n\t"
                "wdr"                       "\n\t"
                "out %0, %1"                "\n\t"
                "out __SREG__,__tmp_reg__"  "\n\t"
                "out %0, %2"                "\n\t"
                : /* no outputs */
                : "I" ( _SFR_IO_ADDR( _WD_CONTROL_REG ) ),
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_బిట్టు ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( విలువ & 0x08 ? WD_PS3_ముసుగు : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | ( విలువ & 0x07 ) ) )
                : "r0"
                );
        }
        లేకపోతే
        {
            __asm__ __volatile__ (
                "in __tmp_reg__,__SREG__"   "\n\t"
                "cli"                       "\n\t"
                "wdr"                       "\n\t"
                "sts %0, %1"                "\n\t"
                "out __SREG__,__tmp_reg__"  "\n\t"
                "sts %0, %2"                "\n\t"
                : /* no outputs */
                : "n" ( _SFR_MEM_ADDR( _WD_CONTROL_REG ) ),
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_బిట్టు ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( విలువ & 0x08 ? WD_PS3_ముసుగు : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | ( విలువ & 0x07 ) ) )
                : "r0"
                );
        }
    }
#అయితే_ముగింపు /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

/**
 *  Enable the watchdog timer, configuring it for expire after
 *  (value) timeout (which is a combination of the WDP0
 *  through WDP3 bits).
 *
 *  This function is derived from <avr/wdt.h> but enables both
 *  the reset bit (WDE), and the interrupt bit (WDIE).
 *
 *  This will ensure that if the interrupt is not serviced
 *  before the second timeout, the AVR will reset.
 *
 *  Servicing the interrupt automatically clears it,
 *  and ensures the AVR does not reset.
 *
 *  Can't find it documented but the WDT, once enabled,
 *  rolls over and fires a new interrupt each time.
 *
 *  See also the symbolic constants WDTO_15MS et al.
 *
 *  Updated to match avr-libc 2.0.0
 */

#ఒకవేళ defined( పోర్టు_USE_WDTO )

    స్థిర __inline__
    __attribute__( ( __always_inline__ ) )
    శూన్య wdt_అంతరాయం_reset_enable( స్థిరరాశి uint8_t విలువ )
    {
        ఒకవేళ( _SFR_IO_REG_P( _WD_CONTROL_REG ) )
        {
            __asm__ __volatile__ (
                "in __tmp_reg__,__SREG__"   "\n\t"
                "cli"                       "\n\t"
                "wdr"                       "\n\t"
                "out %0, %1"                "\n\t"
                "out __SREG__,__tmp_reg__"  "\n\t"
                "out %0, %2"                "\n\t"
                : /* no outputs */
                : "I" ( _SFR_IO_ADDR( _WD_CONTROL_REG ) ),
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_బిట్టు ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( విలువ & 0x08 ? WD_PS3_ముసుగు : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | _BV( WDE ) | ( విలువ & 0x07 ) ) )
                : "r0"
                );
        }
        లేకపోతే
        {
            __asm__ __volatile__ (
                "in __tmp_reg__,__SREG__"   "\n\t"
                "cli"                       "\n\t"
                "wdr"                       "\n\t"
                "sts %0, %1"                "\n\t"
                "out __SREG__,__tmp_reg__"  "\n\t"
                "sts %0, %2"                "\n\t"
                : /* no outputs */
                : "n" ( _SFR_MEM_ADDR( _WD_CONTROL_REG ) ),
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_బిట్టు ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( విలువ & 0x08 ? WD_PS3_ముసుగు : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | _BV( WDE ) | ( విలువ & 0x07 ) ) )
                : "r0"
                );
        }
    }
#అయితే_ముగింపు /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

/*
 * Macro to save all the general purpose registers, the save the stack pointer
 * into the TCB.
 *
 * The first thing we do is save the flags then disable interrupts. This is to
 * guard our stack against having a context switch interrupt after we have already
 * pushed the registers onto the stack - causing the 32 registers to be on the
 * stack twice.
 *
 * r1 is set to zero (__zero_reg__) as the compiler expects it to be thus, however
 * some of the math routines make use of R1.
 *
 * r0 is set to __tmp_reg__ as the compiler expects it to be thus.
 *
 * #if defined(__AVR_HAVE_RAMPZ__)
 * #define __RAMPZ__ 0x3B
 * #endif
 *
 * #if defined(__AVR_3_BYTE_PC__)
 * #define __EIND__ 0x3C
 * #endif
 *
 * The interrupts will have been disabled during the call to portSAVE_CONTEXT()
 * so we need not worry about reading/writing to the stack pointer.
 */
#ఒకవేళ defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ )
/* 3-Byte PC Save  with RAMPZ */
    #నిర్వచించు పోర్టు_SAVE_CONTEXT()                                                   \
    __asm__ __volatile__ ( "push   __tmp_reg__                             \n\t" \
                           "in     __tmp_reg__, __SREG__                   \n\t" \
                           "cli                                            \n\t" \
                           "push   __tmp_reg__                             \n\t" \
                           "in     __tmp_reg__, 0x3B                       \n\t" \
                           "push   __tmp_reg__                             \n\t" \
                           "in     __tmp_reg__, 0x3C                       \n\t" \
                           "push   __tmp_reg__                             \n\t" \
                           "push   __zero_reg__                            \n\t" \
                           "clr    __zero_reg__                            \n\t" \
                           "push   r2                                      \n\t" \
                           "push   r3                                      \n\t" \
                           "push   r4                                      \n\t" \
                           "push   r5                                      \n\t" \
                           "push   r6                                      \n\t" \
                           "push   r7                                      \n\t" \
                           "push   r8                                      \n\t" \
                           "push   r9                                      \n\t" \
                           "push   r10                                     \n\t" \
                           "push   r11                                     \n\t" \
                           "push   r12                                     \n\t" \
                           "push   r13                                     \n\t" \
                           "push   r14                                     \n\t" \
                           "push   r15                                     \n\t" \
                           "push   r16                                     \n\t" \
                           "push   r17                                     \n\t" \
                           "push   r18                                     \n\t" \
                           "push   r19                                     \n\t" \
                           "push   r20                                     \n\t" \
                           "push   r21                                     \n\t" \
                           "push   r22                                     \n\t" \
                           "push   r23                                     \n\t" \
                           "push   r24                                     \n\t" \
                           "push   r25                                     \n\t" \
                           "push   r26                                     \n\t" \
                           "push   r27                                     \n\t" \
                           "push   r28                                     \n\t" \
                           "push   r29                                     \n\t" \
                           "push   r30                                     \n\t" \
                           "push   r31                                     \n\t" \
                           "lds    r26, pxCurrentTCB                       \n\t" \
                           "lds    r27, pxCurrentTCB + 1                   \n\t" \
                           "in     __tmp_reg__, __SP_L__                   \n\t" \
                           "st     x+, __tmp_reg__                         \n\t" \
                           "in     __tmp_reg__, __SP_H__                   \n\t" \
                           "st     x+, __tmp_reg__                         \n\t" \
                           );
#లేదావేళ defined( __AVR_HAVE_RAMPZ__ )
/* 2-Byte PC Save  with RAMPZ */
    #నిర్వచించు పోర్టు_SAVE_CONTEXT()                                                   \
    __asm__ __volatile__ ( "push   __tmp_reg__                             \n\t" \
                           "in     __tmp_reg__, __SREG__                   \n\t" \
                           "cli                                            \n\t" \
                           "push   __tmp_reg__                             \n\t" \
                           "in     __tmp_reg__, 0x3B                       \n\t" \
                           "push   __tmp_reg__                             \n\t" \
                           "push   __zero_reg__                            \n\t" \
                           "clr    __zero_reg__                            \n\t" \
                           "push   r2                                      \n\t" \
                           "push   r3                                      \n\t" \
                           "push   r4                                      \n\t" \
                           "push   r5                                      \n\t" \
                           "push   r6                                      \n\t" \
                           "push   r7                                      \n\t" \
                           "push   r8                                      \n\t" \
                           "push   r9                                      \n\t" \
                           "push   r10                                     \n\t" \
                           "push   r11                                     \n\t" \
                           "push   r12                                     \n\t" \
                           "push   r13                                     \n\t" \
                           "push   r14                                     \n\t" \
                           "push   r15                                     \n\t" \
                           "push   r16                                     \n\t" \
                           "push   r17                                     \n\t" \
                           "push   r18                                     \n\t" \
                           "push   r19                                     \n\t" \
                           "push   r20                                     \n\t" \
                           "push   r21                                     \n\t" \
                           "push   r22                                     \n\t" \
                           "push   r23                                     \n\t" \
                           "push   r24                                     \n\t" \
                           "push   r25                                     \n\t" \
                           "push   r26                                     \n\t" \
                           "push   r27                                     \n\t" \
                           "push   r28                                     \n\t" \
                           "push   r29                                     \n\t" \
                           "push   r30                                     \n\t" \
                           "push   r31                                     \n\t" \
                           "lds    r26, pxCurrentTCB                       \n\t" \
                           "lds    r27, pxCurrentTCB + 1                   \n\t" \
                           "in     __tmp_reg__, __SP_L__                   \n\t" \
                           "st     x+, __tmp_reg__                         \n\t" \
                           "in     __tmp_reg__, __SP_H__                   \n\t" \
                           "st     x+, __tmp_reg__                         \n\t" \
                           );
#లేకపోతే /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/* 2-Byte PC Save */
    #నిర్వచించు పోర్టు_SAVE_CONTEXT()                                                   \
    __asm__ __volatile__ ( "push   __tmp_reg__                             \n\t" \
                           "in     __tmp_reg__, __SREG__                   \n\t" \
                           "cli                                            \n\t" \
                           "push   __tmp_reg__                             \n\t" \
                           "push   __zero_reg__                            \n\t" \
                           "clr    __zero_reg__                            \n\t" \
                           "push   r2                                      \n\t" \
                           "push   r3                                      \n\t" \
                           "push   r4                                      \n\t" \
                           "push   r5                                      \n\t" \
                           "push   r6                                      \n\t" \
                           "push   r7                                      \n\t" \
                           "push   r8                                      \n\t" \
                           "push   r9                                      \n\t" \
                           "push   r10                                     \n\t" \
                           "push   r11                                     \n\t" \
                           "push   r12                                     \n\t" \
                           "push   r13                                     \n\t" \
                           "push   r14                                     \n\t" \
                           "push   r15                                     \n\t" \
                           "push   r16                                     \n\t" \
                           "push   r17                                     \n\t" \
                           "push   r18                                     \n\t" \
                           "push   r19                                     \n\t" \
                           "push   r20                                     \n\t" \
                           "push   r21                                     \n\t" \
                           "push   r22                                     \n\t" \
                           "push   r23                                     \n\t" \
                           "push   r24                                     \n\t" \
                           "push   r25                                     \n\t" \
                           "push   r26                                     \n\t" \
                           "push   r27                                     \n\t" \
                           "push   r28                                     \n\t" \
                           "push   r29                                     \n\t" \
                           "push   r30                                     \n\t" \
                           "push   r31                                     \n\t" \
                           "lds    r26, pxCurrentTCB                       \n\t" \
                           "lds    r27, pxCurrentTCB + 1                   \n\t" \
                           "in     __tmp_reg__, __SP_L__                   \n\t" \
                           "st     x+, __tmp_reg__                         \n\t" \
                           "in     __tmp_reg__, __SP_H__                   \n\t" \
                           "st     x+, __tmp_reg__                         \n\t" \
                           );
#అయితే_ముగింపు /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */

/*
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer.
 */
#ఒకవేళ defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ )
/* 3-Byte PC Restore with RAMPZ */
    #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                \
    __asm__ __volatile__ ( "lds    r26, pxCurrentTCB                       \n\t" \
                           "lds    r27, pxCurrentTCB + 1                   \n\t" \
                           "ld     r28, x+                                 \n\t" \
                           "out    __SP_L__, r28                           \n\t" \
                           "ld     r29, x+                                 \n\t" \
                           "out    __SP_H__, r29                           \n\t" \
                           "pop    r31                                     \n\t" \
                           "pop    r30                                     \n\t" \
                           "pop    r29                                     \n\t" \
                           "pop    r28                                     \n\t" \
                           "pop    r27                                     \n\t" \
                           "pop    r26                                     \n\t" \
                           "pop    r25                                     \n\t" \
                           "pop    r24                                     \n\t" \
                           "pop    r23                                     \n\t" \
                           "pop    r22                                     \n\t" \
                           "pop    r21                                     \n\t" \
                           "pop    r20                                     \n\t" \
                           "pop    r19                                     \n\t" \
                           "pop    r18                                     \n\t" \
                           "pop    r17                                     \n\t" \
                           "pop    r16                                     \n\t" \
                           "pop    r15                                     \n\t" \
                           "pop    r14                                     \n\t" \
                           "pop    r13                                     \n\t" \
                           "pop    r12                                     \n\t" \
                           "pop    r11                                     \n\t" \
                           "pop    r10                                     \n\t" \
                           "pop    r9                                      \n\t" \
                           "pop    r8                                      \n\t" \
                           "pop    r7                                      \n\t" \
                           "pop    r6                                      \n\t" \
                           "pop    r5                                      \n\t" \
                           "pop    r4                                      \n\t" \
                           "pop    r3                                      \n\t" \
                           "pop    r2                                      \n\t" \
                           "pop    __zero_reg__                            \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           "out    0x3C, __tmp_reg__                       \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           "out    0x3B, __tmp_reg__                       \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           "out    __SREG__, __tmp_reg__                   \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           );
#లేదావేళ defined( __AVR_HAVE_RAMPZ__ )
/* 2-Byte PC Restore with RAMPZ */
    #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                \
    __asm__ __volatile__ ( "lds    r26, pxCurrentTCB                       \n\t" \
                           "lds    r27, pxCurrentTCB + 1                   \n\t" \
                           "ld     r28, x+                                 \n\t" \
                           "out    __SP_L__, r28                           \n\t" \
                           "ld     r29, x+                                 \n\t" \
                           "out    __SP_H__, r29                           \n\t" \
                           "pop    r31                                     \n\t" \
                           "pop    r30                                     \n\t" \
                           "pop    r29                                     \n\t" \
                           "pop    r28                                     \n\t" \
                           "pop    r27                                     \n\t" \
                           "pop    r26                                     \n\t" \
                           "pop    r25                                     \n\t" \
                           "pop    r24                                     \n\t" \
                           "pop    r23                                     \n\t" \
                           "pop    r22                                     \n\t" \
                           "pop    r21                                     \n\t" \
                           "pop    r20                                     \n\t" \
                           "pop    r19                                     \n\t" \
                           "pop    r18                                     \n\t" \
                           "pop    r17                                     \n\t" \
                           "pop    r16                                     \n\t" \
                           "pop    r15                                     \n\t" \
                           "pop    r14                                     \n\t" \
                           "pop    r13                                     \n\t" \
                           "pop    r12                                     \n\t" \
                           "pop    r11                                     \n\t" \
                           "pop    r10                                     \n\t" \
                           "pop    r9                                      \n\t" \
                           "pop    r8                                      \n\t" \
                           "pop    r7                                      \n\t" \
                           "pop    r6                                      \n\t" \
                           "pop    r5                                      \n\t" \
                           "pop    r4                                      \n\t" \
                           "pop    r3                                      \n\t" \
                           "pop    r2                                      \n\t" \
                           "pop    __zero_reg__                            \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           "out    0x3B, __tmp_reg__                       \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           "out    __SREG__, __tmp_reg__                   \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           );
#లేకపోతే /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/* 2-Byte PC Restore */
    #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                \
    __asm__ __volatile__ ( "lds    r26, pxCurrentTCB                       \n\t" \
                           "lds    r27, pxCurrentTCB + 1                   \n\t" \
                           "ld     r28, x+                                 \n\t" \
                           "out    __SP_L__, r28                           \n\t" \
                           "ld     r29, x+                                 \n\t" \
                           "out    __SP_H__, r29                           \n\t" \
                           "pop    r31                                     \n\t" \
                           "pop    r30                                     \n\t" \
                           "pop    r29                                     \n\t" \
                           "pop    r28                                     \n\t" \
                           "pop    r27                                     \n\t" \
                           "pop    r26                                     \n\t" \
                           "pop    r25                                     \n\t" \
                           "pop    r24                                     \n\t" \
                           "pop    r23                                     \n\t" \
                           "pop    r22                                     \n\t" \
                           "pop    r21                                     \n\t" \
                           "pop    r20                                     \n\t" \
                           "pop    r19                                     \n\t" \
                           "pop    r18                                     \n\t" \
                           "pop    r17                                     \n\t" \
                           "pop    r16                                     \n\t" \
                           "pop    r15                                     \n\t" \
                           "pop    r14                                     \n\t" \
                           "pop    r13                                     \n\t" \
                           "pop    r12                                     \n\t" \
                           "pop    r11                                     \n\t" \
                           "pop    r10                                     \n\t" \
                           "pop    r9                                      \n\t" \
                           "pop    r8                                      \n\t" \
                           "pop    r7                                      \n\t" \
                           "pop    r6                                      \n\t" \
                           "pop    r5                                      \n\t" \
                           "pop    r4                                      \n\t" \
                           "pop    r3                                      \n\t" \
                           "pop    r2                                      \n\t" \
                           "pop    __zero_reg__                            \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           "out    __SREG__, __tmp_reg__                   \n\t" \
                           "pop    __tmp_reg__                             \n\t" \
                           );
#అయితే_ముగింపు /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/*-----------------------------------------------------------*/

/*
 * Perform hardware setup to enable ticks from relevant Timer.
 */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    uint16_t us_చిరునామా;

    /* Simulate how the stack would look after a call to vPortYield() generated by
     * the compiler. */

    /* The start of the task code will be popped off the stack last, so place
     * it on first. */
    us_చిరునామా = ( uint16_t ) px_సంకేతం;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( us_చిరునామా & ( uint16_t ) 0x00ff );
    px_శిఖరం_యొక్క_దొంతర--;

    us_చిరునామా >>= 8;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( us_చిరునామా & ( uint16_t ) 0x00ff );
    px_శిఖరం_యొక్క_దొంతర--;

    #ఒకవేళ defined( __AVR_3_BYTE_PC__ )

        /* The AVR ATmega2560/ATmega2561 have 256KBytes of program memory and a 17-bit
         * program counter. When a code address is stored on the stack, it takes 3 bytes
         * instead of 2 for the other ATmega* chips.
         *
         * Store 0 as the top byte since we force all task routines to the bottom 128K
         * of flash. We do this by using the .lowtext label in the linker script.
         *
         * In order to do this properly, we would need to get a full 3-byte pointer to
         * pxCode. That requires a change to GCC. Not likely to happen any time soon.
         */
        *px_శిఖరం_యొక్క_దొంతర = 0;
        px_శిఖరం_యొక్క_దొంతర--;
    #అయితే_ముగింపు

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00; /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_FLAGS_INT_ENABLED;
    px_శిఖరం_యొక్క_దొంతర--;

    #ఒకవేళ defined( __AVR_3_BYTE_PC__ )

        /* If we have an ATmega256x, we are also saving the EIND register.
         * We should default to 0.
         */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00; /* EIND */
        px_శిఖరం_యొక్క_దొంతర--;
    #అయితే_ముగింపు

    #ఒకవేళ defined( __AVR_HAVE_RAMPZ__ )

        /* We are saving the RAMPZ register.
         * We should default to 0.
         */
        *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00; /* RAMPZ */
        px_శిఖరం_యొక్క_దొంతర--;
    #అయితే_ముగింపు

    /* Now the remaining registers. The compiler expects R1 to be 0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x00; /* R1 */

    /* Leave R2 - R23 untouched */
    px_శిఖరం_యొక్క_దొంతర -= 23;

    /* Place the parameter on the stack in the expected location. */
    us_చిరునామా = ( uint16_t ) pvParameters;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( us_చిరునామా & ( uint16_t ) 0x00ff );
    px_శిఖరం_యొక్క_దొంతర--;

    us_చిరునామా >>= 8;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ( us_చిరునామా & ( uint16_t ) 0x00ff );

    /* Leave register R26 - R31 untouched */
    px_శిఖరం_యొక్క_దొంతర -= 7;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Setup the relevant timer hardware to generate the tick. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Restore the context of the first task that is going to run. */
    పోర్టు_RESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler. We will now
     * jump to the start of the task the context of which we have just restored. */
    __asm__ __volatile__ ( "ret" );

    /* Should not get here. */
    తిరిగి pdTRUE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the ATmega port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch. The first thing we do is save the registers so we
 * can use a naked attribute.
 */
శూన్య v_పోర్టు_Yield( శూన్య ) __attribute__( ( hot, flatten, naked ) );
శూన్య v_పోర్టు_Yield( శూన్య )
{
    పోర్టు_SAVE_CONTEXT();
    vTaskSwitchContext();
    పోర్టు_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch callable from ISRs. The first thing we do is save
 * the registers so we can use a naked attribute.
 */
శూన్య v_పోర్టు_Yield_From_ISR( శూన్య ) __attribute__( ( hot, flatten, naked ) );
శూన్య v_పోర్టు_Yield_From_ISR( శూన్య )
{
    పోర్టు_SAVE_CONTEXT();
    vTaskSwitchContext();
    పోర్టు_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "reti" );
}
/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick. This must be identical to
 * vPortYield() from the call to vTaskSwitchContext() onwards. The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
శూన్య v_పోర్టు_Yield_From_Tick( శూన్య ) __attribute__( ( hot, flatten, naked ) );
శూన్య v_పోర్టు_Yield_From_Tick( శూన్య )
{
    పోర్టు_SAVE_CONTEXT();

    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    పోర్టు_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "ret" );
}
/*-----------------------------------------------------------*/

#ఒకవేళ defined( పోర్టు_USE_WDTO )

/*
 * Setup WDT to generate a tick interrupt.
 */
    శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
    {
        /* reset watchdog */
        wdt_reset();

        /* set up WDT Interrupt (rather than the WDT Reset). */
        wdt_అంతరాయం_enable( పోర్టు_USE_WDTO );
    }

#లేదావేళ defined( పోర్టు_USE_TIMER0 )

/*
 * Setup Timer0 compare match A to generate a tick interrupt.
 */
    స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
    {
        uint32_t ul_Compare_సరిపోలిక;
        uint8_t uc_దిగువ_Byte;

        /* Using 8bit Timer0 to generate the tick. Correct fuses must be
         * selected for the configCPU_CLOCK_HZ clock.*/

        ul_Compare_సరిపోలిక = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ;

        /* We only have 8 bits so have to scale 1024 to get our required tick rate. */
        ul_Compare_సరిపోలిక /= పోర్టు_CLOCK_PRESCALER;

        /* Adjust for correct value. */
        ul_Compare_సరిపోలిక -= ( uint32_t ) 1;

        /* Setup compare match value for compare match A. Interrupts are disabled
         * before this is called so we need not worry here. */
        uc_దిగువ_Byte = ( uint8_t ) ( ul_Compare_సరిపోలిక & ( uint32_t ) 0xff );
        పోర్టు_OCRL = uc_దిగువ_Byte;

        /* Setup clock source and compare match behaviour. */
        పోర్టు_TCCRa = పోర్టు_CLEAR_COUNTER_ON_సరిపోలిక;
        పోర్టు_TCCRb = పోర్టు_PRESCALE_1024;


        /* Enable the interrupt - this is okay as interrupt are currently globally disabled. */
        uc_దిగువ_Byte = పోర్టు_TIMSK;
        uc_దిగువ_Byte |= పోర్టు_COMPARE_సరిపోలిక_A_అంతరాయం_ENABLE;
        పోర్టు_TIMSK = uc_దిగువ_Byte;
    }

#అయితే_ముగింపు /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

#ఒకవేళ configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler. We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick(). The tick
 * count is incremented after the context is saved.
 *
 * use ISR_NOBLOCK where there is an important timer running, that should preempt the scheduler.
 *
 */
    ISR( పోర్టు_SCHEDULER_ISR, ISR_NAKED ) __attribute__( ( hot, flatten ) );

/*  ISR(portSCHEDULER_ISR, ISR_NAKED ISR_NOBLOCK) __attribute__ ((hot, flatten));
 */
    ISR( పోర్టు_SCHEDULER_ISR )
    {
        v_పోర్టు_Yield_From_Tick();
        __asm__ __volatile__ ( "reti" );
    }
#లేకపోతే /* if configUSE_PREEMPTION == 1 */

/*
 * Tick ISR for the cooperative scheduler. All this does is increment the
 * tick count. We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 *
 * use ISR_NOBLOCK where there is an important timer running, that should preempt the scheduler.
 */
    ISR( పోర్టు_SCHEDULER_ISR ) __attribute__( ( hot, flatten ) );

/*  ISR(portSCHEDULER_ISR, ISR_NOBLOCK) __attribute__ ((hot, flatten));
 */
    ISR( పోర్టు_SCHEDULER_ISR )
    {
        xTaskIncrementTick();
    }
#అయితే_ముగింపు /* if configUSE_PREEMPTION == 1 */
