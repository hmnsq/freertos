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

#నిర్వచితం_కాకపోతే XTENSA_TIMER_H
#నిర్వచించు XTENSA_TIMER_H

#నిర్వచితమైతే __ASSEMBLER__
    #అన్తర్భావ    <xtensa/coreasm.h>
#అయితే_ముగింపు

#అన్తర్భావ    <xtensa/corebits.h>
#అన్తర్భావ    <xtensa/config/system.h>

#అన్తర్భావ    "xtensa_rtos.h" /* in case this wasn't included directly */

#అన్తర్భావ    "FreeRTOSConfig.h"

/*
 * Select timer to use for periodic tick, and determine its interrupt number
 * and priority. User may specify a timer by defining XT_TIMER_INDEX with -D,
 * in which case its validity is checked (it must exist in this core and must
 * not be on a high priority interrupt - an error will be reported in invalid).
 * Otherwise select the first low or medium priority interrupt timer available.
 */
#ఒకవేళ XCHAL_అంకె_TIMERS == 0

    #దోషం "This Xtensa configuration is unsupported, it has no timers."

#లేకపోతే

    #నిర్వచితం_కాకపోతే XT_TIMER_సూచీ
        #ఒకవేళ XCHAL_TIMER3_అంతరాయం != XTHAL_TIMER_UNCONFIGURED
            #ఒకవేళ XCHAL_INT_LEVEL( XCHAL_TIMER3_అంతరాయం ) <= XCHAL_EXCM_LEVEL
                #నిర్వచనం_రద్దు  XT_TIMER_సూచీ
                #నిర్వచించు XT_TIMER_సూచీ    3
            #అయితే_ముగింపు
        #అయితే_ముగింపు
        #ఒకవేళ XCHAL_TIMER2_అంతరాయం != XTHAL_TIMER_UNCONFIGURED
            #ఒకవేళ XCHAL_INT_LEVEL( XCHAL_TIMER2_అంతరాయం ) <= XCHAL_EXCM_LEVEL
                #నిర్వచనం_రద్దు  XT_TIMER_సూచీ
                #నిర్వచించు XT_TIMER_సూచీ    2
            #అయితే_ముగింపు
        #అయితే_ముగింపు
        #ఒకవేళ XCHAL_TIMER1_అంతరాయం != XTHAL_TIMER_UNCONFIGURED
            #ఒకవేళ XCHAL_INT_LEVEL( XCHAL_TIMER1_అంతరాయం ) <= XCHAL_EXCM_LEVEL
                #నిర్వచనం_రద్దు  XT_TIMER_సూచీ
                #నిర్వచించు XT_TIMER_సూచీ    1
            #అయితే_ముగింపు
        #అయితే_ముగింపు
        #ఒకవేళ XCHAL_TIMER0_అంతరాయం != XTHAL_TIMER_UNCONFIGURED
            #ఒకవేళ XCHAL_INT_LEVEL( XCHAL_TIMER0_అంతరాయం ) <= XCHAL_EXCM_LEVEL
                #నిర్వచనం_రద్దు  XT_TIMER_సూచీ
                #నిర్వచించు XT_TIMER_సూచీ    0
            #అయితే_ముగింపు
        #అయితే_ముగింపు
    #అయితే_ముగింపు /* ifndef XT_TIMER_INDEX */
    #నిర్వచితం_కాకపోతే XT_TIMER_సూచీ
        #దోషం "There is no suitable timer in this Xtensa configuration."
    #అయితే_ముగింపు

    #నిర్వచించు XT_CCOMPARE        ( CCOMPARE + XT_TIMER_సూచీ )
    #నిర్వచించు XT_TIMER_INTNUM    XCHAL_TIMER_అంతరాయం( XT_TIMER_సూచీ )
    #నిర్వచించు XT_TIMER_INTPRI    XCHAL_INT_LEVEL( XT_TIMER_INTNUM )
    #నిర్వచించు XT_TIMER_INTEN     ( 1 << XT_TIMER_INTNUM )

    #ఒకవేళ XT_TIMER_INTNUM == XTHAL_TIMER_UNCONFIGURED
        #దోషం "The timer selected by XT_TIMER_INDEX does not exist in this core."
    #లేదావేళ XT_TIMER_INTPRI > XCHAL_EXCM_LEVEL
        #దోషం "The timer interrupt cannot be high priority (use medium or low)."
    #అయితే_ముగింపు

#అయితే_ముగింపు /* XCHAL_NUM_TIMERS */

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
#ఒకవేళ defined( XT_SIMULATOR ) && !defined( XT_CLOCK_FREQ )
    #నిర్వచించు XT_CLOCK_FREQ    configCPU_CLOCK_HZ
#అయితే_ముగింపు

#ఒకవేళ !defined( XT_CLOCK_FREQ ) && !defined( XT_BOARD )
    #దోషం "XT_CLOCK_FREQ must be defined for the target platform."
#అయితే_ముగింపు

/*
 * Default number of timer "ticks" per second (default 100 for 10ms tick).
 * RTOS may define this in its own way (if applicable) in xtensa_rtos.h.
 * User may redefine this to an optimal value for the application, either by
 * editing this here or in xtensa_rtos.h, or compiling with xt-xcc option
 * "-DXT_TICK_PER_SEC=<value>" where <value> is a suitable number.
 */
#నిర్వచితం_కాకపోతే XT_TICK_చొప్పున_SEC
    #నిర్వచించు XT_TICK_చొప్పున_SEC    config_TICK_రేటు_HZ    /* 10 ms tick = 100 ticks per second */
#అయితే_ముగింపు

/*
 * Derivation of clock divisor for timer tick and interrupt (one per tick).
 */
#నిర్వచితమైతే XT_CLOCK_FREQ
    #నిర్వచించు XT_TICK_భాజకం    ( XT_CLOCK_FREQ / XT_TICK_చొప్పున_SEC )
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే __ASSEMBLER__
    బాహ్య గుర్తులేని xt_tick_భాజకం;
    బాహ్య శూన్య xt_tick_భాజకం_init( శూన్య );
#అయితే_ముగింపు

#అయితే_ముగింపు /* XTENSA_TIMER_H */
