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

#अन्तर्भाव <avr/io.h>
#अन्तर्भाव <avr/interrupt.h>
#अन्तर्भाव <avr/wdt.h>

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the AVR port.
*----------------------------------------------------------*/

/* Start tasks with interrupts enabled. */
#परिभाषय पत्तनम्_FLAGS_INT_ENABLED    ( ( राशिः_Type_t ) 0x80 )

#यदि defined( पत्तनम्_USE_WDTO )
    #warning "Watchdog Timer used for scheduler."
    #परिभाषय पत्तनम्_SCHEDULER_ISR    WDT_vect

#नोचेद्यदि defined( पत्तनम्_USE_TIMER0 )
/* Hardware constants for Timer0. */
    #warning "Timer0 used for scheduler."
    #परिभाषय पत्तनम्_SCHEDULER_ISR                       TIMER0_COMPA_vect
    #परिभाषय पत्तनम्_CLEAR_गणक_ON_मेलनम्              ( ( uint8_t ) _BV( WGM01 ) )
    #परिभाषय पत्तनम्_PRESCALE_1024                       ( ( uint8_t ) ( _BV( CS02 ) | _BV( CS00 ) ) )
    #परिभाषय पत्तनम्_CLOCK_PRESCALER                     ( ( uint32_t ) 1024 )
    #परिभाषय पत्तनम्_COMPARE_मेलनम्_A_व्यवधानम्_ENABLE    ( ( uint8_t ) _BV( OCIE0A ) )
    #परिभाषय पत्तनम्_OCRL                                OCR0A
    #परिभाषय पत्तनम्_TCCRa                               TCCR0A
    #परिभाषय पत्तनम्_TCCRb                               TCCR0B
    #परिभाषय पत्तनम्_TIMSK                               TIMSK0
    #परिभाषय पत्तनम्_TIFR                                TIFR0

#अन्यथा /* if defined( portUSE_WDTO ) */
    #दोषः "No Timer defined for scheduler"
#यदि_अन्तः /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
प्रकारनिर्देश शून्य TCB_t;
बाह्य चञ्चल TCB_t * चञ्चल pxCurrentTCB;

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

#यदि defined( पत्तनम्_USE_WDTO )

    स्थिर __inline__
    __attribute__( ( __always_inline__ ) )
    शून्य wdt_व्यवधानम्_enable( ध्रुव uint8_t मानम् )
    {
        यदि( _SFR_IO_REG_P( _WD_CONTROL_REG ) )
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
                "r" ( ( uint8_t ) ( _BV( _WD_CHANGE_BIT ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( मानम् & 0x08 ? WD_PS3_आवरणम् : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | ( मानम् & 0x07 ) ) )
                : "r0"
                );
        }
        अन्यथा
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
                "r" ( ( uint8_t ) ( _BV( _WD_CHANGE_BIT ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( मानम् & 0x08 ? WD_PS3_आवरणम् : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | ( मानम् & 0x07 ) ) )
                : "r0"
                );
        }
    }
#यदि_अन्तः /* if defined( portUSE_WDTO ) */

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

#यदि defined( पत्तनम्_USE_WDTO )

    स्थिर __inline__
    __attribute__( ( __always_inline__ ) )
    शून्य wdt_व्यवधानम्_reset_enable( ध्रुव uint8_t मानम् )
    {
        यदि( _SFR_IO_REG_P( _WD_CONTROL_REG ) )
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
                "r" ( ( uint8_t ) ( _BV( _WD_CHANGE_BIT ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( मानम् & 0x08 ? WD_PS3_आवरणम् : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | _BV( WDE ) | ( मानम् & 0x07 ) ) )
                : "r0"
                );
        }
        अन्यथा
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
                "r" ( ( uint8_t ) ( _BV( _WD_CHANGE_BIT ) | _BV( WDE ) ) ),
                "r" ( ( uint8_t ) ( ( मानम् & 0x08 ? WD_PS3_आवरणम् : 0x00 ) |
                                    _BV( WDIF ) | _BV( WDIE ) | _BV( WDE ) | ( मानम् & 0x07 ) ) )
                : "r0"
                );
        }
    }
#यदि_अन्तः /* if defined( portUSE_WDTO ) */

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
#यदि defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ )
/* 3-Byte PC Save  with RAMPZ */
    #परिभाषय पत्तनम्_SAVE_CONTEXT()                                                   \
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
#नोचेद्यदि defined( __AVR_HAVE_RAMPZ__ )
/* 2-Byte PC Save  with RAMPZ */
    #परिभाषय पत्तनम्_SAVE_CONTEXT()                                                   \
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
#अन्यथा /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/* 2-Byte PC Save */
    #परिभाषय पत्तनम्_SAVE_CONTEXT()                                                   \
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
#यदि_अन्तः /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */

/*
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer.
 */
#यदि defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ )
/* 3-Byte PC Restore with RAMPZ */
    #परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                \
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
#नोचेद्यदि defined( __AVR_HAVE_RAMPZ__ )
/* 2-Byte PC Restore with RAMPZ */
    #परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                \
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
#अन्यथा /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/* 2-Byte PC Restore */
    #परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                \
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
#यदि_अन्तः /* if defined( __AVR_3_BYTE_PC__ ) && defined( __AVR_HAVE_RAMPZ__ ) */
/*-----------------------------------------------------------*/

/*
 * Perform hardware setup to enable ticks from relevant Timer.
 */
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    uint16_t us_स्थानाङ्कः;

    /* Simulate how the stack would look after a call to vPortYield() generated by
     * the compiler. */

    /* The start of the task code will be popped off the stack last, so place
     * it on first. */
    us_स्थानाङ्कः = ( uint16_t ) px_संहिता;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    us_स्थानाङ्कः >>= 8;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    #यदि defined( __AVR_3_BYTE_PC__ )

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
        *px_शिखरम्_सम्बन्धि_राशिः = 0;
        px_शिखरम्_सम्बन्धि_राशिः--;
    #यदि_अन्तः

    /* Next simulate the stack as if after a call to portSAVE_CONTEXT().
     *  portSAVE_CONTEXT places the flags on the stack immediately after r0
     *  to ensure the interrupts get disabled as soon as possible, and so ensuring
     *  the stack use is minimal should a context switch interrupt occur. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00; /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_FLAGS_INT_ENABLED;
    px_शिखरम्_सम्बन्धि_राशिः--;

    #यदि defined( __AVR_3_BYTE_PC__ )

        /* If we have an ATmega256x, we are also saving the EIND register.
         * We should default to 0.
         */
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00; /* EIND */
        px_शिखरम्_सम्बन्धि_राशिः--;
    #यदि_अन्तः

    #यदि defined( __AVR_HAVE_RAMPZ__ )

        /* We are saving the RAMPZ register.
         * We should default to 0.
         */
        *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00; /* RAMPZ */
        px_शिखरम्_सम्बन्धि_राशिः--;
    #यदि_अन्तः

    /* Now the remaining registers. The compiler expects R1 to be 0. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x00; /* R1 */

    /* Leave R2 - R23 untouched */
    px_शिखरम्_सम्बन्धि_राशिः -= 23;

    /* Place the parameter on the stack in the expected location. */
    us_स्थानाङ्कः = ( uint16_t ) pvParameters;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );
    px_शिखरम्_सम्बन्धि_राशिः--;

    us_स्थानाङ्कः >>= 8;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) ( us_स्थानाङ्कः & ( uint16_t ) 0x00ff );

    /* Leave register R26 - R31 untouched */
    px_शिखरम्_सम्बन्धि_राशिः -= 7;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Setup the relevant timer hardware to generate the tick. */
    prv_सज्जता_Timer_व्यवधानम्();

    /* Restore the context of the first task that is going to run. */
    पत्तनम्_RESTORE_CONTEXT();

    /* Simulate a function call end as generated by the compiler. We will now
     * jump to the start of the task the context of which we have just restored. */
    __asm__ __volatile__ ( "ret" );

    /* Should not get here. */
    प्रत्यागम pdTRUE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* It is unlikely that the ATmega port will get stopped. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch. The first thing we do is save the registers so we
 * can use a naked attribute.
 */
शून्य v_पत्तनम्_Yield( शून्य ) __attribute__( ( hot, flatten, naked ) );
शून्य v_पत्तनम्_Yield( शून्य )
{
    पत्तनम्_SAVE_CONTEXT();
    vTaskSwitchContext();
    पत्तनम्_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch callable from ISRs. The first thing we do is save
 * the registers so we can use a naked attribute.
 */
शून्य v_पत्तनम्_Yield_From_ISR( शून्य ) __attribute__( ( hot, flatten, naked ) );
शून्य v_पत्तनम्_Yield_From_ISR( शून्य )
{
    पत्तनम्_SAVE_CONTEXT();
    vTaskSwitchContext();
    पत्तनम्_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "reti" );
}
/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick. This must be identical to
 * vPortYield() from the call to vTaskSwitchContext() onwards. The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
शून्य v_पत्तनम्_Yield_From_Tick( शून्य ) __attribute__( ( hot, flatten, naked ) );
शून्य v_पत्तनम्_Yield_From_Tick( शून्य )
{
    पत्तनम्_SAVE_CONTEXT();

    यदि( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    पत्तनम्_RESTORE_CONTEXT();

    __asm__ __volatile__ ( "ret" );
}
/*-----------------------------------------------------------*/

#यदि defined( पत्तनम्_USE_WDTO )

/*
 * Setup WDT to generate a tick interrupt.
 */
    शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
    {
        /* reset watchdog */
        wdt_reset();

        /* set up WDT Interrupt (rather than the WDT Reset). */
        wdt_व्यवधानम्_enable( पत्तनम्_USE_WDTO );
    }

#नोचेद्यदि defined( पत्तनम्_USE_TIMER0 )

/*
 * Setup Timer0 compare match A to generate a tick interrupt.
 */
    स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
    {
        uint32_t ul_Compare_मेलनम्;
        uint8_t uc_नीचः_Byte;

        /* Using 8bit Timer0 to generate the tick. Correct fuses must be
         * selected for the configCPU_CLOCK_HZ clock.*/

        ul_Compare_मेलनम् = configCPU_CLOCK_HZ / config_TICK_दरः_HZ;

        /* We only have 8 bits so have to scale 1024 to get our required tick rate. */
        ul_Compare_मेलनम् /= पत्तनम्_CLOCK_PRESCALER;

        /* Adjust for correct value. */
        ul_Compare_मेलनम् -= ( uint32_t ) 1;

        /* Setup compare match value for compare match A. Interrupts are disabled
         * before this is called so we need not worry here. */
        uc_नीचः_Byte = ( uint8_t ) ( ul_Compare_मेलनम् & ( uint32_t ) 0xff );
        पत्तनम्_OCRL = uc_नीचः_Byte;

        /* Setup clock source and compare match behaviour. */
        पत्तनम्_TCCRa = पत्तनम्_CLEAR_गणक_ON_मेलनम्;
        पत्तनम्_TCCRb = पत्तनम्_PRESCALE_1024;


        /* Enable the interrupt - this is okay as interrupt are currently globally disabled. */
        uc_नीचः_Byte = पत्तनम्_TIMSK;
        uc_नीचः_Byte |= पत्तनम्_COMPARE_मेलनम्_A_व्यवधानम्_ENABLE;
        पत्तनम्_TIMSK = uc_नीचः_Byte;
    }

#यदि_अन्तः /* if defined( portUSE_WDTO ) */

/*-----------------------------------------------------------*/

#यदि configUSE_PREEMPTION == 1

/*
 * Tick ISR for preemptive scheduler. We can use a naked attribute as
 * the context is saved at the start of vPortYieldFromTick(). The tick
 * count is incremented after the context is saved.
 *
 * use ISR_NOBLOCK where there is an important timer running, that should preempt the scheduler.
 *
 */
    ISR( पत्तनम्_SCHEDULER_ISR, ISR_NAKED ) __attribute__( ( hot, flatten ) );

/*  ISR(portSCHEDULER_ISR, ISR_NAKED ISR_NOBLOCK) __attribute__ ((hot, flatten));
 */
    ISR( पत्तनम्_SCHEDULER_ISR )
    {
        v_पत्तनम्_Yield_From_Tick();
        __asm__ __volatile__ ( "reti" );
    }
#अन्यथा /* if configUSE_PREEMPTION == 1 */

/*
 * Tick ISR for the cooperative scheduler. All this does is increment the
 * tick count. We don't need to switch context, this can only be done by
 * manual calls to taskYIELD();
 *
 * use ISR_NOBLOCK where there is an important timer running, that should preempt the scheduler.
 */
    ISR( पत्तनम्_SCHEDULER_ISR ) __attribute__( ( hot, flatten ) );

/*  ISR(portSCHEDULER_ISR, ISR_NOBLOCK) __attribute__ ((hot, flatten));
 */
    ISR( पत्तनम्_SCHEDULER_ISR )
    {
        xTaskIncrementTick();
    }
#यदि_अन्तः /* if configUSE_PREEMPTION == 1 */
