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
#جے_بنا_تعریف PORTHARDWARE_H
#تعریف_کرو PORTHARDWARE_H

#جے_بنا_تعریف __IAR_SYSTEMS_ASM__
    #ضمن <ioavr.h>
#جے_انت
#ضمن "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMER_INSTANCE == 0 )

    #تعریف_کرو TICK_INT_vect    TCB0_INT_vect
    #تعریف_کرو INT_FLAGS        TCB0_INTFLAGS
    #تعریف_کرو INT_نقاب         TCB_CAPT_bm

    #تعریف_کرو TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 1 )

    #تعریف_کرو TICK_INT_vect    TCB1_INT_vect
    #تعریف_کرو INT_FLAGS        TCB1_INTFLAGS
    #تعریف_کرو INT_نقاب         TCB_CAPT_bm

    #تعریف_کرو TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 2 )

    #تعریف_کرو TICK_INT_vect    TCB2_INT_vect
    #تعریف_کرو INT_FLAGS        TCB2_INTFLAGS
    #تعریف_کرو INT_نقاب         TCB_CAPT_bm

    #تعریف_کرو TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 3 )

    #تعریف_کرو TICK_INT_vect    TCB3_INT_vect
    #تعریف_کرو INT_FLAGS        TCB3_INTFLAGS
    #تعریف_کرو INT_نقاب         TCB_CAPT_bm

    #تعریف_کرو TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 4 )

    #تعریف_کرو TICK_INT_vect    TCB4_INT_vect
    #تعریف_کرو INT_FLAGS        TCB4_INTFLAGS
    #تعریف_کرو INT_نقاب         TCB_CAPT_bm

    #تعریف_کرو TICK_init()                                      \
    {                                                        \
        TCB4.CCMP = configCPU_CLOCK_HZ / config_TICK_شرح_HZ; \
        TCB4.INTCTRL = TCB_CAPT_bm;                          \
        TCB4.CTRLA = TCB_ENABLE_bm;                          \
    }

#وإلاإذا ( configUSE_TIMER_INSTANCE == 5 )

    #تعریف_کرو TICK_INT_vect    RTC_CNT_vect
    #تعریف_کرو INT_FLAGS        RTC_INTFLAGS
    #تعریف_کرو INT_نقاب         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #تعریف_کرو RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #تعریف_کرو TICK_init()                                        \
    {                                                          \
        طالما( RTC.حالت_2 > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.فی_3 = RTC_PERIOD_HZ( config_TICK_شرح_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#وإلا /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #تعریف_رد TICK_INT_vect
    #تعریف_رد INT_FLAGS
    #تعریف_رد INT_نقاب
    #تعریف_رد TICK_init()
    #غلطی Invalid timer setting.
#جے_انت /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#جے_انت /* PORTHARDWARE_H */
