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

#ضمن <avr/io.h>
#ضمن <avr/interrupt.h>
#ضمن <avr/wdt.h>

#ضمن "FreeRTOS.h"
#ضمن "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enabled. */
#وصف_ڪريو پورٽ_FLAGS_INT_ENABLED    ( ( ڍير_Type_t ) 0x80 )

#إذا defined( پورٽ_USE_WDTO )
    #warning "Watchdog Timer used for scheduler."
    #وصف_ڪريو پورٽ_SCHEDULER_ISR    WDT_vect

#وإلاإذا defined( پورٽ_USE_TIMER0 )
/* Hardware constants for Timer0. */
    #warning "Timer0 used for scheduler."
    #وصف_ڪريو پورٽ_SCHEDULER_ISR                       TIMER0_COMPA_vect
    #وصف_ڪريو پورٽ_CLEAR_COUNTER_ON_ميلاپ              ( ( uint8_t ) _BV( WGM01 ) )
    #وصف_ڪريو پورٽ_PRESCALE_1024                       ( ( uint8_t ) ( _BV( CS02 ) | _BV( CS00 ) ) )
    #وصف_ڪريو پورٽ_CLOCK_PRESCALER                     ( ( uint32_t ) 1024 )
    #وصف_ڪريو پورٽ_COMPARE_ميلاپ_A_مداخلت_ENABLE    ( ( uint8_t ) _BV( OCIE0A ) )
    #وصف_ڪريو پورٽ_OCRL                                OCR0A
    #وصف_ڪريو پورٽ_TCCRa                               TCCR0A
    #وصف_ڪريو پورٽ_TCCRb                               TCCR0B
    #وصف_ڪريو پورٽ_TIMSK                               TIMSK0
    #وصف_ڪريو پورٽ_TIFR                                TIFR0

#وإلا /* if defined( portUSE_WDTO ) */
    #غلطي "No Timer defined for scheduler"
#جيڪڏهن_پورو /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

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

#إذا defined( پورٽ_USE_WDTO )

    ساكن __inline__
    __attribute__( ( __always_inline__ ) )
    فراغ wdt_مداخلت_enable( ثابت uint8_t قدر )
    {
        إذا( _SFR_IO_REG_P( _WD_CONTROL_REG ) )
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
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_ٻٽو_انگ ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( قدر & 0x08 ? WD_PS3_نقاب : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | ( قدر & 0x07 ) ) )
                : "r0"
                );
        }
        وإلا
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
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_ٻٽو_انگ ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( قدر & 0x08 ? WD_PS3_نقاب : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | ( قدر & 0x07 ) ) )
                : "r0"
                );
        }
    }
#جيڪڏهن_پورو /* if defined( portUSE_WDTO ) */

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

#إذا defined( پورٽ_USE_WDTO )

    ساكن __inline__
    __attribute__( ( __always_inline__ ) )
    فراغ wdt_مداخلت_reset_enable( ثابت uint8_t قدر )
    {
        إذا( _SFR_IO_REG_P( _WD_CONTROL_REG ) )
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
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_ٻٽو_انگ ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( قدر & 0x08 ? WD_PS3_نقاب : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | _BV( WDE ) | ( قدر & 0x07 ) ) )
                : "r0"
                );
        }
        وإلا
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
                "r" ( ( uint8_t ) ( _BV( WD_CHANGE_ٻٽو_انگ ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( قدر & 0x08 ? WD_PS3_نقاب : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | _BV( WDE ) | ( قدر & 0x07 ) ) )
                : "r0"
                );
        }
    }
#جيڪڏهن_پورو /* if defined( portUSE_WDTO ) */

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
#إذا defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ )
/* 3-Byte PC Save  with RAMPZ */
    #وصف_ڪريو پورٽ_SAVE_CONTEXT()                                                   \
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
#وإلاإذا defined( __AVR_HAVE_RAMPZ__ )
/* 2-Byte PC Save  with RAMPZ */
    #وصف_ڪريو پورٽ_SAVE_CONTEXT()                                                   \
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
#وإلا /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/* 2-Byte PC Save */
    #وصف_ڪريو پورٽ_SAVE_CONTEXT()                                                   \
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
#جيڪڏهن_پورو /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */

/*
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer.
 */
#إذا defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ )
/* 3-Byte PC Restore with RAMPZ */
    #وصف_ڪريو پورٽ_RESTORE_CONTEXT()                                                \
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
#وإلاإذا defined( __AVR_HAVE_RAMPZ__ )
/* 2-Byte PC Restore with RAMPZ */
    #وصف_ڪريو پورٽ_RESTORE_CONTEXT()                                                \
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
#وإلا /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/* 2-Byte PC Restore */
    #وصف_ڪريو پورٽ_RESTORE_CONTEXT()                                                \
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
#جيڪڏهن_پورو /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/*-----------------------------------------------------------*/

/*
 * Perform hardware setup to enable ticks from relevant Timer.
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

    /* Simulate how the stack would look after a call to vPortYield() generated by
     * the compiler. */

    /* The start of the task code will be popped off the stack last, so place
     * it on first. */
    us_پتو = ( uint16_t ) px_ڪوڊ;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    #إذا defined( __AVR_3_BYTE_PC__ )

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
        *px_چوٽي_جو_ڍير = 0;
        px_چوٽي_جو_ڍير--;
    #جيڪڏهن_پورو

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* R0 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_FLAGS_INT_ENABLED;
    px_چوٽي_جو_ڍير--;

    #إذا defined( __AVR_3_BYTE_PC__ )

        /* If we have an ATmega256x, we are also saving the EIND register.
         * We should default to 0.
         */
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* EIND */
        px_چوٽي_جو_ڍير--;
    #جيڪڏهن_پورو

    #إذا defined( __AVR_HAVE_RAMPZ__ )

        /* We are saving the RAMPZ register.
         * We should default to 0.
         */
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* RAMPZ */
        px_چوٽي_جو_ڍير--;
    #جيڪڏهن_پورو

    /* Now the remaining registers. The compiler expects R1 to be 0. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x00; /* R1 */

    /* Leave R2 - R23 untouched */
    px_چوٽي_جو_ڍير -= 23;

    /* Place the parameter on the stack in the expected location. */
    us_پتو = ( uint16_t ) pvParameters;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );
    px_چوٽي_جو_ڍير--;

    us_پتو >>= 8;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) ( us_پتو & ( uint16_t ) 0x00ff );

    /* Leave register R26 - R31 untouched */
    px_چوٽي_جو_ڍير -= 7;

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Setup the relevant timer hardware to generate the tick. */
    prv_تياري_Timer_مداخلت();

    /* Restore the context of the first task that is going to run. */
    پورٽ_RESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler. We will now
     * jump to the start of the task the context of which we have just restored. */
    __asm__ __volatile__ ( "ret" );

    /* Should not get here. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the ATmega port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch. The first thing we do is save the registers so we
 * can use a naked attribute.
 */
فراغ v_پورٽ_Yield( فراغ ) __attribute__( ( hot, flatten, naked ) );
فراغ v_پورٽ_Yield( فراغ )
{
    پورٽ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٽ_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch callable from ISRs. The first thing we do is save
 * the registers so we can use a naked attribute.
 */
فراغ v_پورٽ_Yield_From_ISR( فراغ ) __attribute__( ( hot, flatten, naked ) );
فراغ v_پورٽ_Yield_From_ISR( فراغ )
{
    پورٽ_SAVE_CONTEXT();
    vTaskSwitchContext();
    پورٽ_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "reti" );
}
/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick. This must be identical to
 * vPortYield() from the call to vTaskSwitchContext() onwards. The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
فراغ v_پورٽ_Yield_From_Tick( فراغ ) __attribute__( ( hot, flatten, naked ) );
فراغ v_پورٽ_Yield_From_Tick( فراغ )
{
    پورٽ_SAVE_CONTEXT();

    إذا( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    پورٽ_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "ret" );
}
/*-----------------------------------------------------------*/

#إذا defined( پورٽ_USE_WDTO )

/*
 * Setup WDT to generate a tick interrupt.
 */
    فراغ prv_تياري_Timer_مداخلت( فراغ )
    {
        /* reset watchdog */
        wdt_reset();

        /* set up WDT Interrupt (rather than the WDT Reset). */
        wdt_مداخلت_enable( پورٽ_USE_WDTO );
    }

#وإلاإذا defined( پورٽ_USE_TIMER0 )

/*
 * Setup Timer0 compare match A to generate a tick interrupt.
 */
    ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
    {
        uint32_t ul_Compare_ميلاپ;
        uint8_t uc_هيٺيون_Byte;

        /* Using 8bit Timer0 to generate the tick. Correct fuses must be
         * selected for the configCPU_CLOCK_HZ clock.*/

        ul_Compare_ميلاپ = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

        /* We only have 8 bits so have to scale 1024 to get our required tick rate. */
        ul_Compare_ميلاپ /= پورٽ_CLOCK_PRESCALER;

        /* Adjust for correct value. */
        ul_Compare_ميلاپ -= ( uint32_t ) 1;

        /* Setup compare match value for compare match A. Interrupts are disabled
         * before this is called so we need not worry here. */
        uc_هيٺيون_Byte = ( uint8_t ) ( ul_Compare_ميلاپ & ( uint32_t ) 0xff );
        پورٽ_OCRL = uc_هيٺيون_Byte;

        /* Setup clock source and compare match behaviour. */
        پورٽ_TCCRa = پورٽ_CLEAR_COUNTER_ON_ميلاپ;
        پورٽ_TCCRb = پورٽ_PRESCALE_1024;


        /* Enable the interrupt - this is okay as interrupt are currently globally disabled. */
        uc_هيٺيون_Byte = پورٽ_TIMSK;
        uc_هيٺيون_Byte |= پورٽ_COMPARE_ميلاپ_A_مداخلت_ENABLE;
        پورٽ_TIMSK = uc_هيٺيون_Byte;
    }

#جيڪڏهن_پورو /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

#إذا configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler. We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick(). The tick
 * count is incremented after the context is saved.
 *
 * use ISR_NOBLOCK where there is an important timer running, that should preempt the scheduler.
 *
 */
    ISR( پورٽ_SCHEDULER_ISR, ISR_NAKED ) __attribute__( ( hot, flatten ) );

/*  ISR(portSCHEDULER_ISR, ISR_NAKED ISR_NOBLOCK) __attribute__ ((hot, flatten));
 */
    ISR( پورٽ_SCHEDULER_ISR )
    {
        v_پورٽ_Yield_From_Tick();
        __asm__ __volatile__ ( "reti" );
    }
#وإلا /* if configUSE_PREEMPTION == 1 */

/*
 * Tick ISR for the cooperative scheduler. All this does is increment the
 * tick count. We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 *
 * use ISR_NOBLOCK where there is an important timer running, that should preempt the scheduler.
 */
    ISR( پورٽ_SCHEDULER_ISR ) __attribute__( ( hot, flatten ) );

/*  ISR(portSCHEDULER_ISR, ISR_NOBLOCK) __attribute__ ((hot, flatten));
 */
    ISR( پورٽ_SCHEDULER_ISR )
    {
        xTaskIncrementTick();
    }
#جيڪڏهن_پورو /* if configUSE_PREEMPTION == 1 */
