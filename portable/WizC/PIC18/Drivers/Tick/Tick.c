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
#تعریف_کړه پورټ_بټ_سېټ     (1)
#تعریف_کړه پورټ_بټ_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#تعریف_کړه پورټ_TIMER_COMPARE_بنسټ          ((APROCFREQ/4)/config_TICK_شرح_HZ)

#إذا پورټ_TIMER_COMPARE_بنسټ   < 0x10000
    #تعریف_کړه پورټ_TIMER_COMPARE_ارزښت     (پورټ_TIMER_COMPARE_بنسټ)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS1       (پورټ_بټ_CLEAR)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS0       (پورټ_بټ_CLEAR)
#وإلاإذا پورټ_TIMER_COMPARE_بنسټ < 0x20000
    #تعریف_کړه پورټ_TIMER_COMPARE_ارزښت     (پورټ_TIMER_COMPARE_بنسټ / 2)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS1       (پورټ_بټ_CLEAR)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS0       (پورټ_بټ_سېټ)
#وإلاإذا پورټ_TIMER_COMPARE_بنسټ < 0x40000
    #تعریف_کړه پورټ_TIMER_COMPARE_ارزښت     (پورټ_TIMER_COMPARE_بنسټ / 4)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS1       (پورټ_بټ_سېټ)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS0       (پورټ_بټ_CLEAR)
#وإلاإذا پورټ_TIMER_COMPARE_بنسټ < 0x80000
    #تعریف_کړه پورټ_TIMER_COMPARE_ارزښت     (پورټ_TIMER_COMPARE_بنسټ / 8)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS1       (پورټ_بټ_سېټ)
    #تعریف_کړه پورټ_TIMER_COMPARE_PS0       (پورټ_بټ_سېټ)
#وإلا
    #تېروتنه "TickRate out of range"
#د_که_پای

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
فراغ پورټ_تیاری_Tick( فراغ )
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
    CCPR1H = ( uint8_t ) ( ( پورټ_TIMER_COMPARE_ارزښت >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( پورټ_TIMER_COMPARE_ارزښت & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = پورټ_بټ_سېټ;
    bCCP1M2     = پورټ_بټ_CLEAR;
    bCCP1M1     = پورټ_بټ_سېټ;
    bCCP1M0     = پورټ_بټ_سېټ;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = پورټ_بټ_سېټ;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = پورټ_بټ_CLEAR;
    bPEIE       = پورټ_بټ_سېټ;

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
    bRD16       = پورټ_بټ_سېټ;              // 16-bit
    bT1CKPS1    = پورټ_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = پورټ_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = پورټ_بټ_سېټ;              // Oscillator enable
    bT1SYNC     = پورټ_بټ_سېټ;              // No external clock sync
    bTMR1CS     = پورټ_بټ_CLEAR;            // Internal clock

    bTMR1ON     = پورټ_بټ_سېټ;              // Start timer1
}
