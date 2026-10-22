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
#अगर_अघोषित PORTHARDWARE_H
#घोषणा PORTHARDWARE_H

#अगर_अघोषित __IAR_SYSTEMS_ASM__
    #समावेश <ioavr.h>
#पूर्ण_अगर
#समावेश "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#अगर ( configUSE_TIMER_INSTANCE == 0 )

    #घोषणा TICK_INT_vect    TCB0_INT_vect
    #घोषणा INT_FLAGS        TCB0_INTFLAGS
    #घोषणा INT_MASK         TCB_CAPT_bm

    #घोषणा TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / configTICK_RATE_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#या_अगर ( configUSE_TIMER_INSTANCE == 1 )

    #घोषणा TICK_INT_vect    TCB1_INT_vect
    #घोषणा INT_FLAGS        TCB1_INTFLAGS
    #घोषणा INT_MASK         TCB_CAPT_bm

    #घोषणा TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / configTICK_RATE_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#या_अगर ( configUSE_TIMER_INSTANCE == 2 )

    #घोषणा TICK_INT_vect    TCB2_INT_vect
    #घोषणा INT_FLAGS        TCB2_INTFLAGS
    #घोषणा INT_MASK         TCB_CAPT_bm

    #घोषणा TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / configTICK_RATE_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#या_अगर ( configUSE_TIMER_INSTANCE == 3 )

    #घोषणा TICK_INT_vect    TCB3_INT_vect
    #घोषणा INT_FLAGS        TCB3_INTFLAGS
    #घोषणा INT_MASK         TCB_CAPT_bm

    #घोषणा TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / configTICK_RATE_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#या_अगर ( configUSE_TIMER_INSTANCE == 4 )

    #घोषणा TICK_INT_vect    TCB4_INT_vect
    #घोषणा INT_FLAGS        TCB4_INTFLAGS
    #घोषणा INT_MASK         TCB_CAPT_bm

    #घोषणा TICK_init()                                      \
    {                                                        \
        TCB4.CCMP = configCPU_CLOCK_HZ / configTICK_RATE_HZ; \
        TCB4.INTCTRL = TCB_CAPT_bm;                          \
        TCB4.CTRLA = TCB_ENABLE_bm;                          \
    }

#या_अगर ( configUSE_TIMER_INSTANCE == 5 )

    #घोषणा TICK_INT_vect    RTC_CNT_vect
    #घोषणा INT_FLAGS        RTC_INTFLAGS
    #घोषणा INT_MASK         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #घोषणा RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #घोषणा TICK_init()                                        \
    {                                                          \
        जबतक( RTC.STATUS > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.PER = RTC_PERIOD_HZ( configTICK_RATE_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#अन्यथा /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #अघोषित TICK_INT_vect
    #अघोषित INT_FLAGS
    #अघोषित INT_MASK
    #अघोषित TICK_init()
    #त्रुटि Invalid timer setting.
#पूर्ण_अगर /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#पूर्ण_अगर /* PORTHARDWARE_H */
