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
#నిర్వచితం_కాకపోతే PORTHARDWARE_H
#నిర్వచించు PORTHARDWARE_H

#నిర్వచితం_కాకపోతే __IAR_SYSTEMS_ASM__
    #అన్తర్భావ <ioavr.h>
#అయితే_ముగింపు
#అన్తర్భావ "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMER_INSTANCE == 0 )

    #నిర్వచించు TICK_INT_vect    TCB0_INT_vect
    #నిర్వచించు INT_FLAGS        TCB0_INTFLAGS
    #నిర్వచించు INT_ముసుగు         TCB_CAPT_bm

    #నిర్వచించు TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#లేదావేళ ( configUSE_TIMER_INSTANCE == 1 )

    #నిర్వచించు TICK_INT_vect    TCB1_INT_vect
    #నిర్వచించు INT_FLAGS        TCB1_INTFLAGS
    #నిర్వచించు INT_ముసుగు         TCB_CAPT_bm

    #నిర్వచించు TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#లేదావేళ ( configUSE_TIMER_INSTANCE == 2 )

    #నిర్వచించు TICK_INT_vect    TCB2_INT_vect
    #నిర్వచించు INT_FLAGS        TCB2_INTFLAGS
    #నిర్వచించు INT_ముసుగు         TCB_CAPT_bm

    #నిర్వచించు TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#లేదావేళ ( configUSE_TIMER_INSTANCE == 3 )

    #నిర్వచించు TICK_INT_vect    TCB3_INT_vect
    #నిర్వచించు INT_FLAGS        TCB3_INTFLAGS
    #నిర్వచించు INT_ముసుగు         TCB_CAPT_bm

    #నిర్వచించు TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#లేదావేళ ( configUSE_TIMER_INSTANCE == 4 )

    #నిర్వచించు TICK_INT_vect    RTC_CNT_vect
    #నిర్వచించు INT_FLAGS        RTC_INTFLAGS
    #నిర్వచించు INT_ముసుగు         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #నిర్వచించు RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #నిర్వచించు TICK_init()                                        \
    {                                                          \
        అయితే( RTC.స్థితి_3 > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.చొప్పున_3 = RTC_PERIOD_HZ( config_TICK_రేటు_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#లేకపోతే /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #నిర్వచనం_రద్దు TICK_INT_vect
    #నిర్వచనం_రద్దు INT_FLAGS
    #నిర్వచనం_రద్దు INT_ముసుగు
    #నిర్వచనం_రద్దు TICK_init()
    #దోషం Invalid timer setting.
#అయితే_ముగింపు /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* PORTHARDWARE_H */
