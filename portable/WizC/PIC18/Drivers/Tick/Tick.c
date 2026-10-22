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

#అన్తర్భావ <FreeRTOS.h>
#అన్తర్భావ <task.h>

/* IO port constants. */
#నిర్వచించు పోర్టు_బిట్టు_సమితి     (1)
#నిర్వచించు పోర్టు_బిట్టు_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#నిర్వచించు పోర్టు_TIMER_COMPARE_పునాది          ((APROCFREQ/4)/config_TICK_రేటు_HZ)

#ఒకవేళ పోర్టు_TIMER_COMPARE_పునాది   < 0x10000
    #నిర్వచించు పోర్టు_TIMER_COMPARE_విలువ     (పోర్టు_TIMER_COMPARE_పునాది)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS1       (పోర్టు_బిట్టు_CLEAR)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS0       (పోర్టు_బిట్టు_CLEAR)
#లేదావేళ పోర్టు_TIMER_COMPARE_పునాది < 0x20000
    #నిర్వచించు పోర్టు_TIMER_COMPARE_విలువ     (పోర్టు_TIMER_COMPARE_పునాది / 2)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS1       (పోర్టు_బిట్టు_CLEAR)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS0       (పోర్టు_బిట్టు_సమితి)
#లేదావేళ పోర్టు_TIMER_COMPARE_పునాది < 0x40000
    #నిర్వచించు పోర్టు_TIMER_COMPARE_విలువ     (పోర్టు_TIMER_COMPARE_పునాది / 4)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS1       (పోర్టు_బిట్టు_సమితి)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS0       (పోర్టు_బిట్టు_CLEAR)
#లేదావేళ పోర్టు_TIMER_COMPARE_పునాది < 0x80000
    #నిర్వచించు పోర్టు_TIMER_COMPARE_విలువ     (పోర్టు_TIMER_COMPARE_పునాది / 8)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS1       (పోర్టు_బిట్టు_సమితి)
    #నిర్వచించు పోర్టు_TIMER_COMPARE_PS0       (పోర్టు_బిట్టు_సమితి)
#లేకపోతే
    #దోషం "TickRate out of range"
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
శూన్య పోర్టు_అమరిక_Tick( శూన్య )
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
    CCPR1H = ( uint8_t ) ( ( పోర్టు_TIMER_COMPARE_విలువ >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( పోర్టు_TIMER_COMPARE_విలువ & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = పోర్టు_బిట్టు_సమితి;
    bCCP1M2     = పోర్టు_బిట్టు_CLEAR;
    bCCP1M1     = పోర్టు_బిట్టు_సమితి;
    bCCP1M0     = పోర్టు_బిట్టు_సమితి;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = పోర్టు_బిట్టు_సమితి;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = పోర్టు_బిట్టు_CLEAR;
    bPEIE       = పోర్టు_బిట్టు_సమితి;

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
    bRD16       = పోర్టు_బిట్టు_సమితి;              // 16-bit
    bT1CKPS1    = పోర్టు_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = పోర్టు_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = పోర్టు_బిట్టు_సమితి;              // Oscillator enable
    bT1SYNC     = పోర్టు_బిట్టు_సమితి;              // No external clock sync
    bTMR1CS     = పోర్టు_బిట్టు_CLEAR;            // Internal clock

    bTMR1ON     = పోర్టు_బిట్టు_సమితి;              // Start timer1
}
