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
#جيڪڏهن_وصف_نه_ٿيل PORTHARDWARE_H
#وصف_ڪريو PORTHARDWARE_H

#جيڪڏهن_وصف_نه_ٿيل __IAR_SYSTEMS_ASM__
    #ضمن <ioavr.h>
#جيڪڏهن_پورو
#ضمن "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMER_INSTANCE == 0 )

    #وصف_ڪريو TICK_INT_vect    TCB0_INT_vect
    #وصف_ڪريو INT_FLAGS        TCB0_INTFLAGS
    #وصف_ڪريو INT_نقاب         TCB_CAPT_bm

    #وصف_ڪريو TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 1 )

    #وصف_ڪريو TICK_INT_vect    TCB1_INT_vect
    #وصف_ڪريو INT_FLAGS        TCB1_INTFLAGS
    #وصف_ڪريو INT_نقاب         TCB_CAPT_bm

    #وصف_ڪريو TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 2 )

    #وصف_ڪريو TICK_INT_vect    TCB2_INT_vect
    #وصف_ڪريو INT_FLAGS        TCB2_INTFLAGS
    #وصف_ڪريو INT_نقاب         TCB_CAPT_bm

    #وصف_ڪريو TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 3 )

    #وصف_ڪريو TICK_INT_vect    TCB3_INT_vect
    #وصف_ڪريو INT_FLAGS        TCB3_INTFLAGS
    #وصف_ڪريو INT_نقاب         TCB_CAPT_bm

    #وصف_ڪريو TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 4 )

    #وصف_ڪريو TICK_INT_vect    TCB4_INT_vect
    #وصف_ڪريو INT_FLAGS        TCB4_INTFLAGS
    #وصف_ڪريو INT_نقاب         TCB_CAPT_bm

    #وصف_ڪريو TICK_init()                                      \
    {                                                        \
        TCB4.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB4.INTCTRL = TCB_CAPT_bm;                          \
        TCB4.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 5 )

    #وصف_ڪريو TICK_INT_vect    RTC_CNT_vect
    #وصف_ڪريو INT_FLAGS        RTC_INTFLAGS
    #وصف_ڪريو INT_نقاب         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #وصف_ڪريو RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #وصف_ڪريو TICK_init()                                        \
    {                                                          \
        طالما( RTC.حالت_2 > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.في_4 = RTC_PERIOD_HZ( config_TICK_شرح_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#وإلا /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #وصف_رد TICK_INT_vect
    #وصف_رد INT_FLAGS
    #وصف_رد INT_نقاب
    #وصف_رد TICK_init()
    #غلطي Invalid timer setting.
#جيڪڏهن_پورو /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* PORTHARDWARE_H */
