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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTHARDWARE_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTHARDWARE_H

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __IAR_SYSTEMS_ASM__
    #ਅਨ੍ਤਰ੍ਭਾਵ <ioavr.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMER_INSTANCE == 0 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_INT_vect    TCB0_INT_vect
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_FLAGS        TCB0_INTFLAGS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_ਨਕਾਬ         TCB_CAPT_bm

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#ਜਾਂਜੇ ( configUSE_TIMER_INSTANCE == 1 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_INT_vect    TCB1_INT_vect
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_FLAGS        TCB1_INTFLAGS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_ਨਕਾਬ         TCB_CAPT_bm

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#ਜਾਂਜੇ ( configUSE_TIMER_INSTANCE == 2 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_INT_vect    TCB2_INT_vect
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_FLAGS        TCB2_INTFLAGS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_ਨਕਾਬ         TCB_CAPT_bm

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#ਜਾਂਜੇ ( configUSE_TIMER_INSTANCE == 3 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_INT_vect    TCB3_INT_vect
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_FLAGS        TCB3_INTFLAGS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_ਨਕਾਬ         TCB_CAPT_bm

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#ਜਾਂਜੇ ( configUSE_TIMER_INSTANCE == 4 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_INT_vect    TCB4_INT_vect
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_FLAGS        TCB4_INTFLAGS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_ਨਕਾਬ         TCB_CAPT_bm

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_init()                                      \
    {                                                        \
        TCB4.CCMP = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ; \
        TCB4.INTCTRL = TCB_CAPT_bm;                          \
        TCB4.CTRLA = TCB_ENABLE_bm;                          \
    }

#ਜਾਂਜੇ ( configUSE_TIMER_INSTANCE == 5 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_INT_vect    RTC_CNT_vect
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_FLAGS        RTC_INTFLAGS
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT_ਨਕਾਬ         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TICK_init()                                        \
    {                                                          \
        ਜਦੋਂ( RTC.ਸਥਿਤੀ_2 > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.ਪ੍ਰਤੀ_3 = RTC_PERIOD_HZ( config_TICK_ਦਰ_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#ਨਹੀਂਤਾਂ /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ TICK_INT_vect
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ INT_FLAGS
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ INT_ਨਕਾਬ
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ TICK_init()
    #ਗਲਤੀ Invalid timer setting.
#ਜੇ_ਅੰਤ /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* PORTHARDWARE_H */
