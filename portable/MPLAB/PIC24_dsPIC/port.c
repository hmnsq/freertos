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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੈੱਟ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_PRESCALE 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ 1
#ਜੇ_ਅੰਤ

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_TICK_ਰੁਕਾਵਟ_HANDLER
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TICK_ਰੁਕਾਵਟ_HANDLER T1_ਰੁਕਾਵਟ
#ਜੇ_ਅੰਤ /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਣਵਰਤਿਆ_PR_ਬਿੱਟ  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#ਜੇ config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ != 1
    #ਗਲਤੀ If config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ is not 1 then the #32 ਵਿੱਚ_2 the following macros needs changing ਮੰਜ਼ਿਲ equal the ਪੋਰਟ_ਰੁਕਾਵਟ_ਬਿੱਟ ਮੁੱਲ, which is ( config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 5 )
#ਜੇ_ਅੰਤ

#ਜੇ defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __HAS_EDS__
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT()                                                                                       \
                    asm ਅਸਥਿਰ(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
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
    #ਨਹੀਂਤਾਂ /* __HAS_EDS__ */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT()                                                                                       \
            asm ਅਸਥਿਰ(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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
        #ਜੇ_ਅੰਤ /* __HAS_EDS__ */
#ਜੇ_ਅੰਤ /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#ਜੇ defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT()                                                                                       \
        asm ਅਸਥਿਰ(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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

#ਜੇ_ਅੰਤ /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_RESTORE_CONTEXT
    #ਗਲਤੀ Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#ਜੇ_ਅੰਤ

/*
 * Setup the timer used to generate the tick interrupt.
 */
ਖਾਲੀ v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * See header file for description.
 */
ਢੇਰ_Type_t *px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t *px_ਸਿਖਰ_ਦਾ_ਢੇਰ, TaskFunction_t px_ਕੋਡ, ਖਾਲੀ *pvParameters )
{
uint16_t us_ਕੋਡ;
UBaseType_t i;

ਅਚਲ ਢੇਰ_Type_t x_Initial_ਢੇਰ[] =
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
    #ਜੇ defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
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
    #ਜੇ_ਅੰਤ
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    us_ਕੋਡ = ( uint16_t ) px_ਕੋਡ;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) us_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

    /* Status register with interrupts enabled. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_SR;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

    /* Parameters are passed in W0. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

    ਲਈ( i = 0; i < ( ਆਕਾਰ( x_Initial_ਢੇਰ ) / ਆਕਾਰ( ਢੇਰ_Type_t ) ); i++ )
    {
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = x_Initial_ਢੇਰ[ i ];
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
    }

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = CORCON;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

    #ਜੇ defined(__HAS_EDS__)
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = DSRPAG;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = DSWPAG;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
    #ਨਹੀਂਤਾਂ /* __HAS_EDS__ */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = PSVPAG;
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;
    #ਜੇ_ਅੰਤ /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x00;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ++;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Setup a timer for the tick ISR. */
    v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ();

    /* Restore the context of the first task to run. */
    ਪੋਰਟ_RESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    asm ਅਸਥਿਰ ( "return" );

    /* Should not reach here. */
    ਵਾਪਸ pdTRUE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) ਖਾਲੀ v_Application_ਤਿਆਰੀ_Tick_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
ਅਚਲ uint32_t ul_Compare_ਮੇਲ = ( ( configCPU_CLOCK_HZ / ਪੋਰਟ_TIMER_PRESCALE ) / config_TICK_ਦਰ_HZ ) - 1;

    /* Prescale of 8. */
    T1CON = 0;
    TMR1 = 0;

    PR1 = ( uint16_t ) ul_Compare_ਮੇਲ;

    /* Setup timer 1 interrupt priority. */
    IPC0bits.T1IP = config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ;

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

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    ਜੇ( uxCriticalNesting == 0 )
    {
        ਪੋਰਟ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ __attribute__((__interrupt__, auto_psv)) config_TICK_ਰੁਕਾਵਟ_HANDLER( ਖਾਲੀ )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        ਪੋਰਟ_YIELD();
    }
}
/*-----------------------------------------------------------*/
