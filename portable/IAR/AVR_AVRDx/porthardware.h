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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTHARDWARE_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTHARDWARE_H

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __IAR_SYSTEMS_ASM__
    #ಅನ್ತರ್ಭಾವ <ioavr.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"

/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMER_INSTANCE == 0 )

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_INT_vect    TCB0_INT_vect
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_FLAGS        TCB0_INTFLAGS
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_ಮುಖವಾಡ         TCB_CAPT_bm

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_init()                                      \
    {                                                        \
        TCB0.CCMP = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ; \
        TCB0.INTCTRL = TCB_CAPT_bm;                          \
        TCB0.CTRLA = TCB_ENABLE_bm;                          \
    }

#ಅಥವಾಆದರೆ ( configUSE_TIMER_INSTANCE == 1 )

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_INT_vect    TCB1_INT_vect
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_FLAGS        TCB1_INTFLAGS
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_ಮುಖವಾಡ         TCB_CAPT_bm

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_init()                                      \
    {                                                        \
        TCB1.CCMP = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ; \
        TCB1.INTCTRL = TCB_CAPT_bm;                          \
        TCB1.CTRLA = TCB_ENABLE_bm;                          \
    }

#ಅಥವಾಆದರೆ ( configUSE_TIMER_INSTANCE == 2 )

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_INT_vect    TCB2_INT_vect
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_FLAGS        TCB2_INTFLAGS
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_ಮುಖವಾಡ         TCB_CAPT_bm

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_init()                                      \
    {                                                        \
        TCB2.CCMP = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ; \
        TCB2.INTCTRL = TCB_CAPT_bm;                          \
        TCB2.CTRLA = TCB_ENABLE_bm;                          \
    }

#ಅಥವಾಆದರೆ ( configUSE_TIMER_INSTANCE == 3 )

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_INT_vect    TCB3_INT_vect
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_FLAGS        TCB3_INTFLAGS
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_ಮುಖವಾಡ         TCB_CAPT_bm

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_init()                                      \
    {                                                        \
        TCB3.CCMP = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ; \
        TCB3.INTCTRL = TCB_CAPT_bm;                          \
        TCB3.CTRLA = TCB_ENABLE_bm;                          \
    }

#ಅಥವಾಆದರೆ ( configUSE_TIMER_INSTANCE == 4 )

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_INT_vect    TCB4_INT_vect
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_FLAGS        TCB4_INTFLAGS
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_ಮುಖವಾಡ         TCB_CAPT_bm

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_init()                                      \
    {                                                        \
        TCB4.CCMP = configCPU_CLOCK_HZ / config_TICK_ದರ_HZ; \
        TCB4.INTCTRL = TCB_CAPT_bm;                          \
        TCB4.CTRLA = TCB_ENABLE_bm;                          \
    }

#ಅಥವಾಆದರೆ ( configUSE_TIMER_INSTANCE == 5 )

    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_INT_vect    RTC_CNT_vect
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_FLAGS        RTC_INTFLAGS
    #ವ್ಯಾಖ್ಯಾನಿಸು INT_ಮುಖವಾಡ         RTC_OVF_bm

/* Hertz to period for RTC setup */
    #ವ್ಯಾಖ್ಯಾನಿಸು RTC_PERIOD_HZ( x )    ( 32768 * ( ( 1.0 / x ) ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು TICK_init()                                        \
    {                                                          \
        ಆಗ( RTC.ಸ್ಥಿತಿ_3 > 0 ) {; }                           \
        RTC.CTRLA = RTC_PRESCALER_DIV1_gc | 1 << RTC_RTCEN_bp; \
        RTC.ಪ್ರತಿ_3 = RTC_PERIOD_HZ( config_TICK_ದರ_HZ );         \
        RTC.INTCTRL |= 1 << RTC_OVF_bp;                        \
    }

#ಇಲ್ಲದಿದ್ದರೆ /* if ( configUSE_TIMER_INSTANCE == 0 ) */
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು TICK_INT_vect
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು INT_FLAGS
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು INT_ಮುಖವಾಡ
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು TICK_init()
    #ದೋಷ Invalid timer setting.
#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMER_INSTANCE == 0 ) */

/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* PORTHARDWARE_H */
