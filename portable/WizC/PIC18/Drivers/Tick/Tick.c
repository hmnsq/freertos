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

#ಅನ್ತರ್ಭಾವ <FreeRTOS.h>
#ಅನ್ತರ್ಭಾವ <task.h>

/* IO port constants. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ     (1)
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬಿಟ್_CLEAR   (0)

/*
 * Hardware setup for the tick.
 * We use a compare match on timer1. Depending on MPU-frequency
 * and requested tickrate, a prescaled value with a matching
 * prescaler are determined.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ          ((APROCFREQ/4)/config_TICK_ದರ_HZ)

#ಆದರೆ ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ   < 0x10000
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_ಮೌಲ್ಯ     (ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS1       (ಪೋರ್ಟ್_ಬಿಟ್_CLEAR)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS0       (ಪೋರ್ಟ್_ಬಿಟ್_CLEAR)
#ಅಥವಾಆದರೆ ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ < 0x20000
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_ಮೌಲ್ಯ     (ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ / 2)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS1       (ಪೋರ್ಟ್_ಬಿಟ್_CLEAR)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS0       (ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ)
#ಅಥವಾಆದರೆ ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ < 0x40000
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_ಮೌಲ್ಯ     (ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ / 4)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS1       (ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS0       (ಪೋರ್ಟ್_ಬಿಟ್_CLEAR)
#ಅಥವಾಆದರೆ ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ < 0x80000
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_ಮೌಲ್ಯ     (ಪೋರ್ಟ್_TIMER_COMPARE_ತಳ / 8)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS1       (ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ)
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_COMPARE_PS0       (ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ)
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ "TickRate out of range"
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
ಶೂನ್ಯ ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Tick( ಶೂನ್ಯ )
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
    CCPR1H = ( uint8_t ) ( ( ಪೋರ್ಟ್_TIMER_COMPARE_ಮೌಲ್ಯ >> 8 ) & 0xff );
    CCPR1L = ( uint8_t )   ( ಪೋರ್ಟ್_TIMER_COMPARE_ಮೌಲ್ಯ & 0xff );

    /*
     * Set Compare Special Event Trigger Mode
     */
    bCCP1M3     = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;
    bCCP1M2     = ಪೋರ್ಟ್_ಬಿಟ್_CLEAR;
    bCCP1M1     = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;
    bCCP1M0     = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;

    /*
     * Enable CCP1 interrupt
     */
    bCCP1IE     = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;

    /*
     * We are only going to use the global interrupt bit, so disable
     * interruptpriorities and enable peripheral interrupts.
     */
    bIPEN       = ಪೋರ್ಟ್_ಬಿಟ್_CLEAR;
    bPEIE       = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;

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
    bRD16       = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;              // 16-bit
    bT1CKPS1    = ಪೋರ್ಟ್_TIMER_COMPARE_PS1;    // prescaler
    bT1CKPS0    = ಪೋರ್ಟ್_TIMER_COMPARE_PS0;    // prescaler
    bT1OSCEN    = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;              // Oscillator enable
    bT1SYNC     = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;              // No external clock sync
    bTMR1CS     = ಪೋರ್ಟ್_ಬಿಟ್_CLEAR;            // Internal clock

    bTMR1ON     = ಪೋರ್ಟ್_ಬಿಟ್_ಗಣ;              // Start timer1
}
