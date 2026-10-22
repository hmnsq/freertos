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

#شامل <FreeRTOS.h>
#شامل <task.h>

/* IO port constants. */
#تعریف_کرو پورٹ_ثنائی_ہندسہ_سیٹ     (1)
#تعریف_کرو پورٹ_ثنائی_ہندسہ_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#تعریف_کرو پورٹ_TIMER_COMPARE_بنیاد          ((APROCFREQ/4)/config_TICK_شرح_HZ)

#اگر پورٹ_TIMER_COMPARE_بنیاد   < 0x10000
    #تعریف_کرو پورٹ_TIMER_COMPARE_قدر     (پورٹ_TIMER_COMPARE_بنیاد)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS1       (پورٹ_ثنائی_ہندسہ_CLEAR)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS0       (پورٹ_ثنائی_ہندسہ_CLEAR)
#وگرنہ_اگر پورٹ_TIMER_COMPARE_بنیاد < 0x20000
    #تعریف_کرو پورٹ_TIMER_COMPARE_قدر     (پورٹ_TIMER_COMPARE_بنیاد / 2)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS1       (پورٹ_ثنائی_ہندسہ_CLEAR)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS0       (پورٹ_ثنائی_ہندسہ_سیٹ)
#وگرنہ_اگر پورٹ_TIMER_COMPARE_بنیاد < 0x40000
    #تعریف_کرو پورٹ_TIMER_COMPARE_قدر     (پورٹ_TIMER_COMPARE_بنیاد / 4)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS1       (پورٹ_ثنائی_ہندسہ_سیٹ)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS0       (پورٹ_ثنائی_ہندسہ_CLEAR)
#وگرنہ_اگر پورٹ_TIMER_COMPARE_بنیاد < 0x80000
    #تعریف_کرو پورٹ_TIMER_COMPARE_قدر     (پورٹ_TIMER_COMPARE_بنیاد / 8)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS1       (پورٹ_ثنائی_ہندسہ_سیٹ)
    #تعریف_کرو پورٹ_TIMER_COMPARE_PS0       (پورٹ_ثنائی_ہندسہ_سیٹ)
#ورنہ
    #غلطی "TickRate out of range"
#اگر_ختم

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
خالی پورٹ_تیاری_Tick( خالی )
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
    CCPR1H = ( uint8_t ) ( ( پورٹ_TIMER_COMPARE_قدر >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( پورٹ_TIMER_COMPARE_قدر & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = پورٹ_ثنائی_ہندسہ_سیٹ;
    bCCP1M2     = پورٹ_ثنائی_ہندسہ_CLEAR;
    bCCP1M1     = پورٹ_ثنائی_ہندسہ_سیٹ;
    bCCP1M0     = پورٹ_ثنائی_ہندسہ_سیٹ;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = پورٹ_ثنائی_ہندسہ_سیٹ;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = پورٹ_ثنائی_ہندسہ_CLEAR;
    bPEIE       = پورٹ_ثنائی_ہندسہ_سیٹ;

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
    bRD16       = پورٹ_ثنائی_ہندسہ_سیٹ;              // 16-bit
    bT1CKPS1    = پورٹ_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = پورٹ_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = پورٹ_ثنائی_ہندسہ_سیٹ;              // Oscillator enable
    bT1SYNC     = پورٹ_ثنائی_ہندسہ_سیٹ;              // No external clock sync
    bTMR1CS     = پورٹ_ثنائی_ہندسہ_CLEAR;            // Internal clock

    bTMR1ON     = پورٹ_ثنائی_ہندسہ_سیٹ;              // Start timer1
}
