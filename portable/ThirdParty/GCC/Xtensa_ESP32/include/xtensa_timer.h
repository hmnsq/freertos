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

#جے_بنا_تعریف XTENSA_TIMER_H
#تعریف_کرو XTENSA_TIMER_H

#جے_تعریف_شدہ __ASSEMBLER__
    #ضمن    <xtensa/coreasm.h>
#جے_انت

#ضمن    <xtensa/corebits.h>
#ضمن    <xtensa/config/system.h>

#ضمن    "xtensa_rtos.h" /* in case this wasn't included directly */

#ضمن    "FreeRTOSConfig.h"

/*
 * Select timer to use for periodic tick, and determine its interrupt number
 * and priority. User may specify a timer by defining XT_TIMER_INDEX with -D,
 * in which case its validity is checked (it must exist in this core and must
 * not be on a high priority interrupt - an error will be reported in invalid).
 * Otherwise select the first low or medium priority interrupt timer available.
 */
#إذا XCHAL_عدد_TIMERS == 0

    #غلطی "This Xtensa configuration is unsupported, it has no timers."

#وإلا

    #جے_بنا_تعریف XT_TIMER_اشاریہ
        #إذا XCHAL_TIMER3_رکاوٹ != XTHAL_TIMER_UNCONFIGURED
            #إذا XCHAL_INT_LEVEL( XCHAL_TIMER3_رکاوٹ ) <= XCHAL_EXCM_LEVEL
                #تعریف_رد  XT_TIMER_اشاریہ
                #تعریف_کرو XT_TIMER_اشاریہ    3
            #جے_انت
        #جے_انت
        #إذا XCHAL_TIMER2_رکاوٹ != XTHAL_TIMER_UNCONFIGURED
            #إذا XCHAL_INT_LEVEL( XCHAL_TIMER2_رکاوٹ ) <= XCHAL_EXCM_LEVEL
                #تعریف_رد  XT_TIMER_اشاریہ
                #تعریف_کرو XT_TIMER_اشاریہ    2
            #جے_انت
        #جے_انت
        #إذا XCHAL_TIMER1_رکاوٹ != XTHAL_TIMER_UNCONFIGURED
            #إذا XCHAL_INT_LEVEL( XCHAL_TIMER1_رکاوٹ ) <= XCHAL_EXCM_LEVEL
                #تعریف_رد  XT_TIMER_اشاریہ
                #تعریف_کرو XT_TIMER_اشاریہ    1
            #جے_انت
        #جے_انت
        #إذا XCHAL_TIMER0_رکاوٹ != XTHAL_TIMER_UNCONFIGURED
            #إذا XCHAL_INT_LEVEL( XCHAL_TIMER0_رکاوٹ ) <= XCHAL_EXCM_LEVEL
                #تعریف_رد  XT_TIMER_اشاریہ
                #تعریف_کرو XT_TIMER_اشاریہ    0
            #جے_انت
        #جے_انت
    #جے_انت /* ifndef XT_TIMER_INDEX */
    #جے_بنا_تعریف XT_TIMER_اشاریہ
        #غلطی "There is no suitable timer in this Xtensa configuration."
    #جے_انت

    #تعریف_کرو XT_CCOMPARE        ( CCOMPARE + XT_TIMER_اشاریہ )
    #تعریف_کرو XT_TIMER_INTNUM    XCHAL_TIMER_رکاوٹ( XT_TIMER_اشاریہ )
    #تعریف_کرو XT_TIMER_INTPRI    XCHAL_INT_LEVEL( XT_TIMER_INTNUM )
    #تعریف_کرو XT_TIMER_INTEN     ( 1 << XT_TIMER_INTNUM )

    #إذا XT_TIMER_INTNUM == XTHAL_TIMER_UNCONFIGURED
        #غلطی "The timer selected by XT_TIMER_INDEX does not exist in this core."
    #وإلاإذا XT_TIMER_INTPRI > XCHAL_EXCM_LEVEL
        #غلطی "The timer interrupt cannot be high priority (use medium or low)."
    #جے_انت

#جے_انت /* XCHAL_NUM_TIMERS */

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
#إذا defined( XT_SIMULATOR ) && !defined( XT_CLOCK_FREQ )
    #تعریف_کرو XT_CLOCK_FREQ    configCPU_CLOCK_HZ
#جے_انت

#إذا !defined( XT_CLOCK_FREQ ) && !defined( XT_BOARD )
    #غلطی "XT_CLOCK_FREQ must be defined for the target platform."
#جے_انت

/*
 * Default number of timer "ticks" per second (default 100 for 10ms tick).
 * RTOS may define this in its own way (if applicable) in xtensa_rtos.h.
 * User may redefine this to an optimal value for the application, either by
 * editing this here or in xtensa_rtos.h, or compiling with xt-xcc option
 * "-DXT_TICK_PER_SEC=<value>" where <value> is a suitable number.
 */
#جے_بنا_تعریف XT_TICK_فی_SEC
    #تعریف_کرو XT_TICK_فی_SEC    config_TICK_شرح_HZ    /* 10 ms tick = 100 ticks per second */
#جے_انت

/*
 * Derivation of clock divisor for timer tick and interrupt (one per tick).
 */
#جے_تعریف_شدہ XT_CLOCK_FREQ
    #تعریف_کرو XT_TICK_مقسوم_علیہ    ( XT_CLOCK_FREQ / XT_TICK_فی_SEC )
#جے_انت

#جے_بنا_تعریف __ASSEMBLER__
    خارجي بنانشانی xt_tick_مقسوم_علیہ;
    خارجي فراغ xt_tick_مقسوم_علیہ_init( فراغ );
#جے_انت

#جے_انت /* XTENSA_TIMER_H */
