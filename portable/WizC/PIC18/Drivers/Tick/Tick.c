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

/*
Changes from V3.0.0
    + ISRcode is pulled inline and portTICKisr() is therefore
      deleted from this file.

    + Prescaler logic for Timer1 added to allow for a wider
      range of TickRates.

Changes from V3.0.1
*/

#अन्तर्भाव <FreeRTOS.h>
#अन्तर्भाव <task.h>

/* IO port constants. */
#परिभाषय पत्तनम्_BIT_समुच्चयः     (1)
#परिभाषय पत्तनम्_BIT_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#परिभाषय पत्तनम्_TIMER_COMPARE_आधारः          ((APROCFREQ/4)/config_TICK_दरः_HZ)

#यदि पत्तनम्_TIMER_COMPARE_आधारः   < 0x10000
    #परिभाषय पत्तनम्_TIMER_COMPARE_मानम्     (पत्तनम्_TIMER_COMPARE_आधारः)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS1       (पत्तनम्_BIT_CLEAR)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS0       (पत्तनम्_BIT_CLEAR)
#नोचेद्यदि पत्तनम्_TIMER_COMPARE_आधारः < 0x20000
    #परिभाषय पत्तनम्_TIMER_COMPARE_मानम्     (पत्तनम्_TIMER_COMPARE_आधारः / 2)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS1       (पत्तनम्_BIT_CLEAR)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS0       (पत्तनम्_BIT_समुच्चयः)
#नोचेद्यदि पत्तनम्_TIMER_COMPARE_आधारः < 0x40000
    #परिभाषय पत्तनम्_TIMER_COMPARE_मानम्     (पत्तनम्_TIMER_COMPARE_आधारः / 4)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS1       (पत्तनम्_BIT_समुच्चयः)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS0       (पत्तनम्_BIT_CLEAR)
#नोचेद्यदि पत्तनम्_TIMER_COMPARE_आधारः < 0x80000
    #परिभाषय पत्तनम्_TIMER_COMPARE_मानम्     (पत्तनम्_TIMER_COMPARE_आधारः / 8)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS1       (पत्तनम्_BIT_समुच्चयः)
    #परिभाषय पत्तनम्_TIMER_COMPARE_PS0       (पत्तनम्_BIT_समुच्चयः)
#अन्यथा
    #दोषः "TickRate out of range"
#यदि_अन्तः

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
शून्य पत्तनम्_सज्जता_Tick( शून्य )
{
    /*
     * Interrupts are disabled when this function is called.
     */

    /*
     * Setup CCP1
     * Provide the tick interrupt using a compare match on timer1.
     */

    /*
     * Set the compare match value.
     */
    CCPR1H = ( uint8_t ) ( ( पत्तनम्_TIMER_COMPARE_मानम् >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( पत्तनम्_TIMER_COMPARE_मानम् & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = पत्तनम्_BIT_समुच्चयः;
    bCCP1M2     = पत्तनम्_BIT_CLEAR;
    bCCP1M1     = पत्तनम्_BIT_समुच्चयः;
    bCCP1M0     = पत्तनम्_BIT_समुच्चयः;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = पत्तनम्_BIT_समुच्चयः;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = पत्तनम्_BIT_CLEAR;
    bPEIE       = पत्तनम्_BIT_समुच्चयः;

    /*
     * Set up timer1
     * It will produce the system tick.
     */

    /*
     * Clear the time count
     */
    TMR1H = ( uint8_t ) 0x00;
    TMR1L = ( uint8_t ) 0x00;

    /*
     * Setup the timer
     */
    bRD16       = पत्तनम्_BIT_समुच्चयः;              // 16-bit
    bT1CKPS1    = पत्तनम्_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = पत्तनम्_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = पत्तनम्_BIT_समुच्चयः;              // Oscillator enable
    bT1SYNC     = पत्तनम्_BIT_समुच्चयः;              // No external clock sync
    bTMR1CS     = पत्तनम्_BIT_CLEAR;            // Internal clock

    bTMR1ON     = पत्तनम्_BIT_समुच्चयः;              // Start timer1
}
