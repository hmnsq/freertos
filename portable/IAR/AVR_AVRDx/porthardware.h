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
#यदि_अपरिभाषितम् PORTHARDWARE_H
#परिभाषय PORTHARDWARE_H

#यदि_अपरिभाषितम् __IAR_SYSTEMS_ASM__
    #अन्तर्भाव <ioavr.h>
#यदि_अन्तः
#अन्तर्भाव "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMER_INSTANCE == 0 )

    #परिभाषय TICK_INT_vect    TCB0_INT_vect
    #परिभाषय INT_FLAGS        TCB0_INTFLAGS
    #परिभाषय INT_आवरणम्         TCB_CAPT_bm

    #परिभाषय TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / config_TICK_दरः_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#नोचेद्यदि ( configUSE_TIMER_INSTANCE == 1 )

    #परिभाषय TICK_INT_vect    TCB1_INT_vect
    #परिभाषय INT_FLAGS        TCB1_INTFLAGS
    #परिभाषय INT_आवरणम्         TCB_CAPT_bm

    #परिभाषय TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / config_TICK_दरः_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#नोचेद्यदि ( configUSE_TIMER_INSTANCE == 2 )

    #परिभाषय TICK_INT_vect    TCB2_INT_vect
    #परिभाषय INT_FLAGS        TCB2_INTFLAGS
    #परिभाषय INT_आवरणम्         TCB_CAPT_bm

    #परिभाषय TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / config_TICK_दरः_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#नोचेद्यदि ( configUSE_TIMER_INSTANCE == 3 )

    #परिभाषय TICK_INT_vect    TCB3_INT_vect
    #परिभाषय INT_FLAGS        TCB3_INTFLAGS
    #परिभाषय INT_आवरणम्         TCB_CAPT_bm

    #परिभाषय TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / config_TICK_दरः_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#नोचेद्यदि ( configUSE_TIMER_INSTANCE == 4 )

    #परिभाषय TICK_INT_vect    TCB4_INT_vect
    #परिभाषय INT_FLAGS        TCB4_INTFLAGS
    #परिभाषय INT_आवरणम्         TCB_CAPT_bm

    #परिभाषय TICK_init()                                      \
    {                                                        \
        TCB4.CCMP = configCPU_CLOCK_HZ / config_TICK_दरः_HZ; \
        TCB4.INTCTRL = TCB_CAPT_bm;                          \
        TCB4.CTRLA = TCB_ENABLE_bm;                          \
    }

#नोचेद्यदि ( configUSE_TIMER_INSTANCE == 5 )

    #परिभाषय TICK_INT_vect    RTC_CNT_vect
    #परिभाषय INT_FLAGS        RTC_INTFLAGS
    #परिभाषय INT_आवरणम्         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #परिभाषय RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #परिभाषय TICK_init()                                        \
    {                                                          \
        यावत्( RTC.स्थितिः_2 > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.प्रत्येकम्_3 = RTC_PERIOD_HZ( config_TICK_दरः_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#अन्यथा /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #अपरिभाषय TICK_INT_vect
    #अपरिभाषय INT_FLAGS
    #अपरिभाषय INT_आवरणम्
    #अपरिभाषय TICK_init()
    #दोषः Invalid timer setting.
#यदि_अन्तः /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#यदि_अन्तः /* PORTHARDWARE_H */
