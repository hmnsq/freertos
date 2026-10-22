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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XTENSA_TIMER_H
#ವ್ಯಾಖ್ಯಾನಿಸು XTENSA_TIMER_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ASSEMBLER__
    #ಅನ್ತರ್ಭಾವ    <xtensa/coreasm.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ    <xtensa/corebits.h>
#ಅನ್ತರ್ಭಾವ    <xtensa/config/system.h>

#ಅನ್ತರ್ಭಾವ    "xtensa_rtos.h" /* in case this wasn't included directly */

#ಅನ್ತರ್ಭಾವ    "FreeRTOSConfig.h"

/*
 * Select timer to use for periodic tick, and determine its interrupt number
 * and priority. User may specify a timer by defining XT_TIMER_INDEX with -D,
 * in which case its validity is checked (it must exist in this core and must
 * not be on a high priority interrupt - an error will be reported in invalid).
 * Otherwise select the first low or medium priority interrupt timer available.
 */
#ಆದರೆ XCHAL_ಅಂಕೆ_TIMERS == 0

    #ದೋಷ "This Xtensa configuration is unsupported, it has no timers."

#ಇಲ್ಲದಿದ್ದರೆ

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XT_TIMER_ಸೂಚ್ಯಂಕ
        #ಆದರೆ XCHAL_TIMER3_ಅಡಚಣೆ != XTHAL_TIMER_UNCONFIGURED
            #ಆದರೆ XCHAL_INT_LEVEL( XCHAL_TIMER3_ಅಡಚಣೆ ) <= XCHAL_EXCM_LEVEL
                #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  XT_TIMER_ಸೂಚ್ಯಂಕ
                #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_ಸೂಚ್ಯಂಕ    3
            #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ XCHAL_TIMER2_ಅಡಚಣೆ != XTHAL_TIMER_UNCONFIGURED
            #ಆದರೆ XCHAL_INT_LEVEL( XCHAL_TIMER2_ಅಡಚಣೆ ) <= XCHAL_EXCM_LEVEL
                #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  XT_TIMER_ಸೂಚ್ಯಂಕ
                #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_ಸೂಚ್ಯಂಕ    2
            #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ XCHAL_TIMER1_ಅಡಚಣೆ != XTHAL_TIMER_UNCONFIGURED
            #ಆದರೆ XCHAL_INT_LEVEL( XCHAL_TIMER1_ಅಡಚಣೆ ) <= XCHAL_EXCM_LEVEL
                #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  XT_TIMER_ಸೂಚ್ಯಂಕ
                #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_ಸೂಚ್ಯಂಕ    1
            #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ XCHAL_TIMER0_ಅಡಚಣೆ != XTHAL_TIMER_UNCONFIGURED
            #ಆದರೆ XCHAL_INT_LEVEL( XCHAL_TIMER0_ಅಡಚಣೆ ) <= XCHAL_EXCM_LEVEL
                #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  XT_TIMER_ಸೂಚ್ಯಂಕ
                #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_ಸೂಚ್ಯಂಕ    0
            #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ_ಅಂತ್ಯ
    #ಆದರೆ_ಅಂತ್ಯ /* ifndef XT_TIMER_INDEX */
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XT_TIMER_ಸೂಚ್ಯಂಕ
        #ದೋಷ "There is no suitable timer in this Xtensa configuration."
    #ಆದರೆ_ಅಂತ್ಯ

    #ವ್ಯಾಖ್ಯಾನಿಸು XT_CCOMPARE        ( CCOMPARE + XT_TIMER_ಸೂಚ್ಯಂಕ )
    #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_INTNUM    XCHAL_TIMER_ಅಡಚಣೆ( XT_TIMER_ಸೂಚ್ಯಂಕ )
    #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_INTPRI    XCHAL_INT_LEVEL( XT_TIMER_INTNUM )
    #ವ್ಯಾಖ್ಯಾನಿಸು XT_TIMER_INTEN     ( 1 << XT_TIMER_INTNUM )

    #ಆದರೆ XT_TIMER_INTNUM == XTHAL_TIMER_UNCONFIGURED
        #ದೋಷ "The timer selected by XT_TIMER_INDEX does not exist in this core."
    #ಅಥವಾಆದರೆ XT_TIMER_INTPRI > XCHAL_EXCM_LEVEL
        #ದೋಷ "The timer interrupt cannot be high priority (use medium or low)."
    #ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* XCHAL_NUM_TIMERS */

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
#ಆದರೆ defined( XT_SIMULATOR ) && !defined( XT_CLOCK_FREQ )
    #ವ್ಯಾಖ್ಯಾನಿಸು XT_CLOCK_FREQ    configCPU_CLOCK_HZ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined( XT_CLOCK_FREQ ) && !defined( XT_BOARD )
    #ದೋಷ "XT_CLOCK_FREQ must be defined for the target platform."
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Default number of timer "ticks" per second (default 100 for 10ms tick).
 * RTOS may define this in its own way (if applicable) in xtensa_rtos.h.
 * User may redefine this to an optimal value for the application, either by
 * editing this here or in xtensa_rtos.h, or compiling with xt-xcc option
 * "-DXT_TICK_PER_SEC=<value>" where <value> is a suitable number.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XT_TICK_ಪ್ರತಿ_SEC
    #ವ್ಯಾಖ್ಯಾನಿಸು XT_TICK_ಪ್ರತಿ_SEC    config_TICK_ದರ_HZ    /* 10 ms tick = 100 ticks per second */
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Derivation of clock divisor for timer tick and interrupt (one per tick).
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XT_CLOCK_FREQ
    #ವ್ಯಾಖ್ಯಾನಿಸು XT_TICK_ಭಾಜಕ    ( XT_CLOCK_FREQ / XT_TICK_ಪ್ರತಿ_SEC )
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ASSEMBLER__
    ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ xt_tick_ಭಾಜಕ;
    ಬಾಹ್ಯ ಶೂನ್ಯ xt_tick_ಭಾಜಕ_init( ಶೂನ್ಯ );
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* XTENSA_TIMER_H */
