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

#ਅਨ੍ਤਰ੍ਭਾਵ <FreeRTOS.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <task.h>

/* IO port constants. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ     (1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ          ((APROCFREQ/4)/config_TICK_ਦਰ_HZ)

#ਜੇ ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ   < 0x10000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_ਮੁੱਲ     (ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS1       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS0       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR)
#ਜਾਂਜੇ ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ < 0x20000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_ਮੁੱਲ     (ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ / 2)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS1       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS0       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ)
#ਜਾਂਜੇ ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ < 0x40000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_ਮੁੱਲ     (ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ / 4)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS1       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS0       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR)
#ਜਾਂਜੇ ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ < 0x80000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_ਮੁੱਲ     (ਪੋਰਟ_TIMER_COMPARE_ਅਧਾਰ / 8)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS1       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_COMPARE_PS0       (ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ)
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ "TickRate out of range"
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
ਖਾਲੀ ਪੋਰਟ_ਤਿਆਰੀ_Tick( ਖਾਲੀ )
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
    CCPR1H = ( uint8_t ) ( ( ਪੋਰਟ_TIMER_COMPARE_ਮੁੱਲ >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( ਪੋਰਟ_TIMER_COMPARE_ਮੁੱਲ & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;
    bCCP1M2     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR;
    bCCP1M1     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;
    bCCP1M0     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR;
    bPEIE       = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;

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
    bRD16       = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;              // 16-bit
    bT1CKPS1    = ਪੋਰਟ_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = ਪੋਰਟ_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;              // Oscillator enable
    bT1SYNC     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;              // No external clock sync
    bTMR1CS     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_CLEAR;            // Internal clock

    bTMR1ON     = ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ;              // Start timer1
}
