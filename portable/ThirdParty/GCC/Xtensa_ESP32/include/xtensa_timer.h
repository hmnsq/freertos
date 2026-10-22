/*
 * SPDX-FileCopyrightText: 2015-2019 Cadence Design Systems, Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2016-2022 Espressif Systems (Shanghai) CO LTD
 */

/*
 * Copyright (c) 2015-2019 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*******************************************************************************
*
*       XTENSA INFORMATION FOR RTOS TICK TIMER AND CLOCK FREQUENCY
*
*  This header contains definitions and macros for use primarily by Xtensa
*  RTOS assembly coded source files. It includes and uses the Xtensa hardware
*  abstraction layer (HAL) to deal with config specifics. It may also be
*  included in C source files.
*
*  User may edit to modify timer selection and to specify clock frequency and
*  tick duration to match timer interrupt to the real-time tick duration.
*
*  If the RTOS has no timer interrupt, then there is no tick timer and the
*  clock frequency is irrelevant, so all of these macros are left undefined
*  and the Xtensa core configuration need not have a timer.
*
*******************************************************************************/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XTENSA_TIMER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XTENSA_TIMER_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__
    #ਅਨ੍ਤਰ੍ਭਾਵ    <xtensa/coreasm.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ    <xtensa/corebits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ    <xtensa/config/system.h>

#ਅਨ੍ਤਰ੍ਭਾਵ    "xtensa_rtos.h" /* in case this wasn't included directly */

#ਅਨ੍ਤਰ੍ਭਾਵ    "FreeRTOSConfig.h"

/*
 * Select timer to use for periodic tick, and determine its interrupt number
 * and priority. User may specify a timer by defining XT_TIMER_INDEX with -D,
 * in which case its validity is checked (it must exist in this core and must
 * not be on a high priority interrupt - an error will be reported in invalid).
 * Otherwise select the first low or medium priority interrupt timer available.
 */
#ਜੇ XCHAL_ਅੰਕ_TIMERS == 0

    #ਗਲਤੀ "This Xtensa configuration is unsupported, it has no timers."

#ਨਹੀਂਤਾਂ

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XT_TIMER_ਸੂਚਕਾਂਕ
        #ਜੇ XCHAL_TIMER3_ਰੁਕਾਵਟ != XTHAL_TIMER_UNCONFIGURED
            #ਜੇ XCHAL_INT_LEVEL( XCHAL_TIMER3_ਰੁਕਾਵਟ ) <= XCHAL_EXCM_LEVEL
                #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  XT_TIMER_ਸੂਚਕਾਂਕ
                #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_ਸੂਚਕਾਂਕ    3
            #ਜੇ_ਅੰਤ
        #ਜੇ_ਅੰਤ
        #ਜੇ XCHAL_TIMER2_ਰੁਕਾਵਟ != XTHAL_TIMER_UNCONFIGURED
            #ਜੇ XCHAL_INT_LEVEL( XCHAL_TIMER2_ਰੁਕਾਵਟ ) <= XCHAL_EXCM_LEVEL
                #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  XT_TIMER_ਸੂਚਕਾਂਕ
                #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_ਸੂਚਕਾਂਕ    2
            #ਜੇ_ਅੰਤ
        #ਜੇ_ਅੰਤ
        #ਜੇ XCHAL_TIMER1_ਰੁਕਾਵਟ != XTHAL_TIMER_UNCONFIGURED
            #ਜੇ XCHAL_INT_LEVEL( XCHAL_TIMER1_ਰੁਕਾਵਟ ) <= XCHAL_EXCM_LEVEL
                #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  XT_TIMER_ਸੂਚਕਾਂਕ
                #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_ਸੂਚਕਾਂਕ    1
            #ਜੇ_ਅੰਤ
        #ਜੇ_ਅੰਤ
        #ਜੇ XCHAL_TIMER0_ਰੁਕਾਵਟ != XTHAL_TIMER_UNCONFIGURED
            #ਜੇ XCHAL_INT_LEVEL( XCHAL_TIMER0_ਰੁਕਾਵਟ ) <= XCHAL_EXCM_LEVEL
                #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  XT_TIMER_ਸੂਚਕਾਂਕ
                #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_ਸੂਚਕਾਂਕ    0
            #ਜੇ_ਅੰਤ
        #ਜੇ_ਅੰਤ
    #ਜੇ_ਅੰਤ /* ifndef XT_TIMER_INDEX */
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XT_TIMER_ਸੂਚਕਾਂਕ
        #ਗਲਤੀ "There is no suitable timer in this Xtensa configuration."
    #ਜੇ_ਅੰਤ

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_CCOMPARE        ( CCOMPARE + XT_TIMER_ਸੂਚਕਾਂਕ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_INTNUM    XCHAL_TIMER_ਰੁਕਾਵਟ( XT_TIMER_ਸੂਚਕਾਂਕ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_INTPRI    XCHAL_INT_LEVEL( XT_TIMER_INTNUM )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_INTEN     ( 1 << XT_TIMER_INTNUM )

    #ਜੇ XT_TIMER_INTNUM == XTHAL_TIMER_UNCONFIGURED
        #ਗਲਤੀ "The timer selected by XT_TIMER_INDEX does not exist in this core."
    #ਜਾਂਜੇ XT_TIMER_INTPRI > XCHAL_EXCM_LEVEL
        #ਗਲਤੀ "The timer interrupt cannot be high priority (use medium or low)."
    #ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* XCHAL_NUM_TIMERS */

/*
 * Set processor clock frequency, used to determine clock divisor for timer tick.
 * User should BE SURE TO ADJUST THIS for the Xtensa platform being used.
 * If using a supported board via the board-independent API defined in xtbsp.h,
 * this may be left undefined and frequency and tick divisor will be computed
 * and cached during run-time initialization.
 *
 * NOTE ON SIMULATOR:
 * Under the Xtensa instruction set simulator, the frequency can only be estimated
 * because it depends on the speed of the host and the version of the simulator.
 * Also because it runs much slower than hardware, it is not possible to achieve
 * real-time performance for most applications under the simulator. A frequency
 * too low does not allow enough time between timer interrupts, starving threads.
 * To obtain a more convenient but non-real-time tick duration on the simulator,
 * compile with xt-xcc option "-DXT_SIMULATOR".
 * Adjust this frequency to taste (it's not real-time anyway!).
 */
#ਜੇ defined( XT_SIMULATOR ) && !defined( XT_CLOCK_FREQ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_CLOCK_FREQ    configCPU_CLOCK_HZ
#ਜੇ_ਅੰਤ

#ਜੇ !defined( XT_CLOCK_FREQ ) && !defined( XT_BOARD )
    #ਗਲਤੀ "XT_CLOCK_FREQ must be defined for the target platform."
#ਜੇ_ਅੰਤ

/*
 * Default number of timer "ticks" per second (default 100 for 10ms tick).
 * RTOS may define this in its own way (if applicable) in xtensa_rtos.h.
 * User may redefine this to an optimal value for the application, either by
 * editing this here or in xtensa_rtos.h, or compiling with xt-xcc option
 * "-DXT_TICK_PER_SEC=<value>" where <value> is a suitable number.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XT_TICK_ਪ੍ਰਤੀ_SEC
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TICK_ਪ੍ਰਤੀ_SEC    config_TICK_ਦਰ_HZ    /* 10 ms tick = 100 ticks per second */
#ਜੇ_ਅੰਤ

/*
 * Derivation of clock divisor for timer tick and interrupt (one per tick).
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XT_CLOCK_FREQ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TICK_ਭਾਜਕ    ( XT_CLOCK_FREQ / XT_TICK_ਪ੍ਰਤੀ_SEC )
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__
    ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ xt_tick_ਭਾਜਕ;
    ਬਾਹਰੀ ਖਾਲੀ xt_tick_ਭਾਜਕ_init( ਖਾਲੀ );
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* XTENSA_TIMER_H */
