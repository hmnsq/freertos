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
#تعریف_کن پورت_بیت_مجموعه     (1)
#تعریف_کن پورت_بیت_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#تعریف_کن پورت_TIMER_COMPARE_پایه          ((APROCFREQ/4)/config_TICK_نرخ_HZ)

#إذا پورت_TIMER_COMPARE_پایه   < 0x10000
    #تعریف_کن پورت_TIMER_COMPARE_مقدار     (پورت_TIMER_COMPARE_پایه)
    #تعریف_کن پورت_TIMER_COMPARE_PS1       (پورت_بیت_CLEAR)
    #تعریف_کن پورت_TIMER_COMPARE_PS0       (پورت_بیت_CLEAR)
#وإلاإذا پورت_TIMER_COMPARE_پایه < 0x20000
    #تعریف_کن پورت_TIMER_COMPARE_مقدار     (پورت_TIMER_COMPARE_پایه / 2)
    #تعریف_کن پورت_TIMER_COMPARE_PS1       (پورت_بیت_CLEAR)
    #تعریف_کن پورت_TIMER_COMPARE_PS0       (پورت_بیت_مجموعه)
#وإلاإذا پورت_TIMER_COMPARE_پایه < 0x40000
    #تعریف_کن پورت_TIMER_COMPARE_مقدار     (پورت_TIMER_COMPARE_پایه / 4)
    #تعریف_کن پورت_TIMER_COMPARE_PS1       (پورت_بیت_مجموعه)
    #تعریف_کن پورت_TIMER_COMPARE_PS0       (پورت_بیت_CLEAR)
#وإلاإذا پورت_TIMER_COMPARE_پایه < 0x80000
    #تعریف_کن پورت_TIMER_COMPARE_مقدار     (پورت_TIMER_COMPARE_پایه / 8)
    #تعریف_کن پورت_TIMER_COMPARE_PS1       (پورت_بیت_مجموعه)
    #تعریف_کن پورت_TIMER_COMPARE_PS0       (پورت_بیت_مجموعه)
#وإلا
    #خطا "TickRate out of range"
#پایان_اگر

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
فراغ پورت_راهاندازی_Tick( فراغ )
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
    CCPR1H = ( uint8_t ) ( ( پورت_TIMER_COMPARE_مقدار >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( پورت_TIMER_COMPARE_مقدار & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = پورت_بیت_مجموعه;
    bCCP1M2     = پورت_بیت_CLEAR;
    bCCP1M1     = پورت_بیت_مجموعه;
    bCCP1M0     = پورت_بیت_مجموعه;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = پورت_بیت_مجموعه;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = پورت_بیت_CLEAR;
    bPEIE       = پورت_بیت_مجموعه;

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
    bRD16       = پورت_بیت_مجموعه;              // 16-bit
    bT1CKPS1    = پورت_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = پورت_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = پورت_بیت_مجموعه;              // Oscillator enable
    bT1SYNC     = پورت_بیت_مجموعه;              // No external clock sync
    bTMR1CS     = پورت_بیت_CLEAR;            // Internal clock

    bTMR1ON     = پورت_بیت_مجموعه;              // Start timer1
}
