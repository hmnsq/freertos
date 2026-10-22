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

#ضمن <FreeRTOS.h>
#ضمن <task.h>

/* IO port constants. */
#وصف_ڪريو پورٽ_ٻٽو_انگ_سيٽ     (1)
#وصف_ڪريو پورٽ_ٻٽو_انگ_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#وصف_ڪريو پورٽ_TIMER_COMPARE_بنياد          ((APROCFREQ/4)/config_TICK_شرح_HZ)

#إذا پورٽ_TIMER_COMPARE_بنياد   < 0x10000
    #وصف_ڪريو پورٽ_TIMER_COMPARE_قدر     (پورٽ_TIMER_COMPARE_بنياد)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS1       (پورٽ_ٻٽو_انگ_CLEAR)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS0       (پورٽ_ٻٽو_انگ_CLEAR)
#وإلاإذا پورٽ_TIMER_COMPARE_بنياد < 0x20000
    #وصف_ڪريو پورٽ_TIMER_COMPARE_قدر     (پورٽ_TIMER_COMPARE_بنياد / 2)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS1       (پورٽ_ٻٽو_انگ_CLEAR)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS0       (پورٽ_ٻٽو_انگ_سيٽ)
#وإلاإذا پورٽ_TIMER_COMPARE_بنياد < 0x40000
    #وصف_ڪريو پورٽ_TIMER_COMPARE_قدر     (پورٽ_TIMER_COMPARE_بنياد / 4)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS1       (پورٽ_ٻٽو_انگ_سيٽ)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS0       (پورٽ_ٻٽو_انگ_CLEAR)
#وإلاإذا پورٽ_TIMER_COMPARE_بنياد < 0x80000
    #وصف_ڪريو پورٽ_TIMER_COMPARE_قدر     (پورٽ_TIMER_COMPARE_بنياد / 8)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS1       (پورٽ_ٻٽو_انگ_سيٽ)
    #وصف_ڪريو پورٽ_TIMER_COMPARE_PS0       (پورٽ_ٻٽو_انگ_سيٽ)
#وإلا
    #غلطي "TickRate out of range"
#جيڪڏهن_پورو

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
فراغ پورٽ_تياري_Tick( فراغ )
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
    CCPR1H = ( uint8_t ) ( ( پورٽ_TIMER_COMPARE_قدر >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( پورٽ_TIMER_COMPARE_قدر & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = پورٽ_ٻٽو_انگ_سيٽ;
    bCCP1M2     = پورٽ_ٻٽو_انگ_CLEAR;
    bCCP1M1     = پورٽ_ٻٽو_انگ_سيٽ;
    bCCP1M0     = پورٽ_ٻٽو_انگ_سيٽ;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = پورٽ_ٻٽو_انگ_سيٽ;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = پورٽ_ٻٽو_انگ_CLEAR;
    bPEIE       = پورٽ_ٻٽو_انگ_سيٽ;

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
    bRD16       = پورٽ_ٻٽو_انگ_سيٽ;              // 16-bit
    bT1CKPS1    = پورٽ_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = پورٽ_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = پورٽ_ٻٽو_انگ_سيٽ;              // Oscillator enable
    bT1SYNC     = پورٽ_ٻٽو_انگ_سيٽ;              // No external clock sync
    bTMR1CS     = پورٽ_ٻٽو_انگ_CLEAR;            // Internal clock

    bTMR1ON     = پورٽ_ٻٽو_انگ_سيٽ;              // Start timer1
}
