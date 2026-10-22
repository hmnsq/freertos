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
    Changes from V4.2.1

    + Introduced the configKERNEL_INTERRUPT_PRIORITY definition.
*/

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the PIC24 port.
 *----------------------------------------------------------*/

/* Scheduler include files. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Hardware specifics. */
#تعریف_کړه پورټ_بټ_سېټ 1
#تعریف_کړه پورټ_TIMER_PRESCALE 8
#تعریف_کړه پورټ_INITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#که_نه_تعریف_شوی config_KERNEL_مداخله_لومړیتوب
    #تعریف_کړه config_KERNEL_مداخله_لومړیتوب 1
#د_که_پای

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#که_نه_تعریف_شوی config_TICK_مداخله_HANDLER
    #تعریف_کړه config_TICK_مداخله_HANDLER T1_مداخله
#د_که_پای /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#تعریف_کړه پورټ_ناکارول_شوی_PR_بټونه  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#إذا config_KERNEL_مداخله_لومړیتوب != 1
    #تېروتنه If config_KERNEL_مداخله_لومړیتوب is not 1 then the #32 دننه the following macros needs changing منزل equal the پورټ_مداخله_بټونه ارزښت, which is ( config_KERNEL_مداخله_لومړیتوب << 5 )
#د_که_پای

#إذا defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #که_تعریف_شوی __HAS_EDS__
        #تعریف_کړه پورټ_RESTORE_CONTEXT()                                                                                       \
                    asm متطاير(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
                            "MOV    [W0], W15               \n"                                                             \
                            "POP    W0                      \n" /* Restore the critical nesting counter for the task. */    \
                            "MOV    W0, _uxCriticalNesting  \n"                                                             \
                            "POP    DSWPAG                  \n"                                                             \
                            "POP    DSRPAG                  \n"                                                             \
                            "POP    CORCON                  \n"                                                             \
                            "POP    TBLPAG                  \n"                                                             \
                            "POP    RCOUNT                  \n" /* Restore the registers from the stack. */                 \
                            "POP    W14                     \n"                                                             \
                            "POP.D  W12                     \n"                                                             \
                            "POP.D  W10                     \n"                                                             \
                            "POP.D  W8                      \n"                                                             \
                            "POP.D  W6                      \n"                                                             \
                            "POP.D  W4                      \n"                                                             \
                            "POP.D  W2                      \n"                                                             \
                            "POP.D  W0                      \n"                                                             \
                            "POP    SR                        " );
    #وإلا /* __HAS_EDS__ */
        #تعریف_کړه پورټ_RESTORE_CONTEXT()                                                                                       \
            asm متطاير(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
                            "MOV    [W0], W15               \n"                                                             \
                            "POP    W0                      \n" /* Restore the critical nesting counter for the task. */    \
                            "MOV    W0, _uxCriticalNesting  \n"                                                             \
                            "POP    PSVPAG                  \n"                                                             \
                            "POP    CORCON                  \n"                                                             \
                            "POP    TBLPAG                  \n"                                                             \
                            "POP    RCOUNT                  \n" /* Restore the registers from the stack. */                 \
                            "POP    W14                     \n"                                                             \
                            "POP.D  W12                     \n"                                                             \
                            "POP.D  W10                     \n"                                                             \
                            "POP.D  W8                      \n"                                                             \
                            "POP.D  W6                      \n"                                                             \
                            "POP.D  W4                      \n"                                                             \
                            "POP.D  W2                      \n"                                                             \
                            "POP.D  W0                      \n"                                                             \
                            "POP    SR                        " );
        #د_که_پای /* __HAS_EDS__ */
#د_که_پای /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#إذا defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #تعریف_کړه پورټ_RESTORE_CONTEXT()                                                                                       \
        asm متطاير(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
                        "MOV    [W0], W15               \n"                                                             \
                        "POP    W0                      \n" /* Restore the critical nesting counter for the task. */    \
                        "MOV    W0, _uxCriticalNesting  \n"                                                             \
                        "POP    PSVPAG                  \n"                                                             \
                        "POP    CORCON                  \n"                                                             \
                        "POP    DOENDH                  \n"                                                             \
                        "POP    DOENDL                  \n"                                                             \
                        "POP    DOSTARTH                \n"                                                             \
                        "POP    DOSTARTL                \n"                                                             \
                        "POP    DCOUNT                  \n"                                                             \
                        "POP    ACCBU                   \n"                                                             \
                        "POP    ACCBH                   \n"                                                             \
                        "POP    ACCBL                   \n"                                                             \
                        "POP    ACCAU                   \n"                                                             \
                        "POP    ACCAH                   \n"                                                             \
                        "POP    ACCAL                   \n"                                                             \
                        "POP    TBLPAG                  \n"                                                             \
                        "POP    RCOUNT                  \n" /* Restore the registers from the stack. */                 \
                        "POP    W14                     \n"                                                             \
                        "POP.D  W12                     \n"                                                             \
                        "POP.D  W10                     \n"                                                             \
                        "POP.D  W8                      \n"                                                             \
                        "POP.D  W6                      \n"                                                             \
                        "POP.D  W4                      \n"                                                             \
                        "POP.D  W2                      \n"                                                             \
                        "POP.D  W0                      \n"                                                             \
                        "POP    SR                        " );

#د_که_پای /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#که_نه_تعریف_شوی پورټ_RESTORE_CONTEXT
    #تېروتنه Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#د_که_پای

/*
 * Setup the timer used to generate the tick interrupt.
 */
فراغ v_Application_تیاری_Tick_Timer_مداخله( فراغ );

/*
 * See header file for description.
 */
ډېری_Type_t *px_پورټ_Initialise_ډېری( ډېری_Type_t *px_سر_د_ډېری, TaskFunction_t px_کوډ, فراغ *pvParameters )
{
uint16_t us_کوډ;
UBaseType_t i;

ثابت ډېری_Type_t x_Initial_ډېری[] =
{
    0x1111, /* W1 */
    0x2222, /* W2 */
    0x3333, /* W3 */
    0x4444, /* W4 */
    0x5555, /* W5 */
    0x6666, /* W6 */
    0x7777, /* W7 */
    0x8888, /* W8 */
    0x9999, /* W9 */
    0xaaaa, /* W10 */
    0xbbbb, /* W11 */
    0xcccc, /* W12 */
    0xdddd, /* W13 */
    0xeeee, /* W14 */
    0xcdce, /* RCOUNT */
    0xabac, /* TBLPAG */

    /* dsPIC specific registers. */
    #إذا defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
        0x0202, /* ACCAL */
        0x0303, /* ACCAH */
        0x0404, /* ACCAU */
        0x0505, /* ACCBL */
        0x0606, /* ACCBH */
        0x0707, /* ACCBU */
        0x0808, /* DCOUNT */
        0x090a, /* DOSTARTL */
        0x1010, /* DOSTARTH */
        0x1110, /* DOENDL */
        0x1212, /* DOENDH */
    #د_که_پای
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    us_کوډ = ( uint16_t ) px_کوډ;
    *px_سر_د_ډېری = ( ډېری_Type_t ) us_کوډ;
    px_سر_د_ډېری++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0;
    px_سر_د_ډېری++;

    /* Status register with interrupts enabled. */
    *px_سر_د_ډېری = پورټ_INITIAL_SR;
    px_سر_د_ډېری++;

    /* Parameters are passed in W0. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;
    px_سر_د_ډېری++;

    لكل( i = 0; i < ( حجم( x_Initial_ډېری ) / حجم( ډېری_Type_t ) ); i++ )
    {
        *px_سر_د_ډېری = x_Initial_ډېری[ i ];
        px_سر_د_ډېری++;
    }

    *px_سر_د_ډېری = CORCON;
    px_سر_د_ډېری++;

    #إذا defined(__HAS_EDS__)
        *px_سر_د_ډېری = DSRPAG;
        px_سر_د_ډېری++;
        *px_سر_د_ډېری = DSWPAG;
        px_سر_د_ډېری++;
    #وإلا /* __HAS_EDS__ */
        *px_سر_د_ډېری = PSVPAG;
        px_سر_د_ډېری++;
    #د_که_پای /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_سر_د_ډېری = 0x00;
    px_سر_د_ډېری++;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    /* Setup a timer for the tick ISR. */
    v_Application_تیاری_Tick_Timer_مداخله();

    /* Restore the context of the first task to run. */
    پورټ_RESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    asm متطاير ( "return" );

    /* Should not reach here. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) فراغ v_Application_تیاری_Tick_Timer_مداخله( فراغ )
{
ثابت uint32_t ul_Compare_سمون = ( ( configCPU_CLOCK_HZ / پورټ_TIMER_PRESCALE ) / config_TICK_شرح_HZ ) - 1;

    /* Prescale of 8. */
    T1CON = 0;
    TMR1 = 0;

    PR1 = ( uint16_t ) ul_Compare_سمون;

    /* Setup timer 1 interrupt priority. */
    IPC0bits.T1IP = config_KERNEL_مداخله_لومړیتوب;

    /* Clear the interrupt as a starting condition. */
    IFS0bits.T1IF = 0;

    /* Enable the interrupt. */
    IEC0bits.T1IE = 1;

    /* Setup the prescale value. */
    T1CONbits.TCKPS0 = 1;
    T1CONbits.TCKPS1 = 0;

    /* Start the timer. */
    T1CONbits.TON = 1;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    پورټ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    إذا( uxCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ __attribute__((__interrupt__, auto_psv)) config_TICK_مداخله_HANDLER( فراغ )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    إذا( xTaskIncrementTick() != pdFALSE )
    {
        پورټ_YIELD();
    }
}
/*-----------------------------------------------------------*/
