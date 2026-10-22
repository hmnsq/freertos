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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Hardware specifics. */
#परिभाषय पत्तनम्_BIT_समुच्चयः 1
#परिभाषय पत्तनम्_TIMER_PRESCALE 8
#परिभाषय पत्तनम्_INITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#यदि_अपरिभाषितम् config_KERNEL_व्यवधानम्_प्राथमिकता
    #परिभाषय config_KERNEL_व्यवधानम्_प्राथमिकता 1
#यदि_अन्तः

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#यदि_अपरिभाषितम् config_TICK_व्यवधानम्_HANDLER
    #परिभाषय config_TICK_व्यवधानम्_HANDLER T1_व्यवधानम्
#यदि_अन्तः /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#परिभाषय पत्तनम्_अप्रयुक्तम्_PR_द्वयङ्काः  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#यदि config_KERNEL_व्यवधानम्_प्राथमिकता != 1
    #दोषः If config_KERNEL_व्यवधानम्_प्राथमिकता is not 1 then the #32 अन्तर् the following macros needs changing गन्तव्यम् equal the पत्तनम्_व्यवधानम्_द्वयङ्काः मानम्, which is ( config_KERNEL_व्यवधानम्_प्राथमिकता << 5 )
#यदि_अन्तः

#यदि defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #यदि_परिभाषितम् __HAS_EDS__
        #परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                                                       \
                    asm चञ्चल(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
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
    #अन्यथा /* __HAS_EDS__ */
        #परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                                                       \
            asm चञ्चल(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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
        #यदि_अन्तः /* __HAS_EDS__ */
#यदि_अन्तः /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#यदि defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #परिभाषय पत्तनम्_RESTORE_CONTEXT()                                                                                       \
        asm चञ्चल(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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

#यदि_अन्तः /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#यदि_अपरिभाषितम् पत्तनम्_RESTORE_CONTEXT
    #दोषः Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#यदि_अन्तः

/*
 * Setup the timer used to generate the tick interrupt.
 */
शून्य v_Application_सज्जता_Tick_Timer_व्यवधानम्( शून्य );

/*
 * See header file for description.
 */
राशिः_Type_t *px_पत्तनम्_Initialise_राशिः( राशिः_Type_t *px_शिखरम्_सम्बन्धि_राशिः, TaskFunction_t px_संहिता, शून्य *pvParameters )
{
uint16_t us_संहिता;
UBaseType_t i;

ध्रुव राशिः_Type_t x_Initial_राशिः[] =
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
    #यदि defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
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
    #यदि_अन्तः
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    us_संहिता = ( uint16_t ) px_संहिता;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) us_संहिता;
    px_शिखरम्_सम्बन्धि_राशिः++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0;
    px_शिखरम्_सम्बन्धि_राशिः++;

    /* Status register with interrupts enabled. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_SR;
    px_शिखरम्_सम्बन्धि_राशिः++;

    /* Parameters are passed in W0. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;
    px_शिखरम्_सम्बन्धि_राशिः++;

    प्रति( i = 0; i < ( परिमाण( x_Initial_राशिः ) / परिमाण( राशिः_Type_t ) ); i++ )
    {
        *px_शिखरम्_सम्बन्धि_राशिः = x_Initial_राशिः[ i ];
        px_शिखरम्_सम्बन्धि_राशिः++;
    }

    *px_शिखरम्_सम्बन्धि_राशिः = CORCON;
    px_शिखरम्_सम्बन्धि_राशिः++;

    #यदि defined(__HAS_EDS__)
        *px_शिखरम्_सम्बन्धि_राशिः = DSRPAG;
        px_शिखरम्_सम्बन्धि_राशिः++;
        *px_शिखरम्_सम्बन्धि_राशिः = DSWPAG;
        px_शिखरम्_सम्बन्धि_राशिः++;
    #अन्यथा /* __HAS_EDS__ */
        *px_शिखरम्_सम्बन्धि_राशिः = PSVPAG;
        px_शिखरम्_सम्बन्धि_राशिः++;
    #यदि_अन्तः /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_शिखरम्_सम्बन्धि_राशिः = 0x00;
    px_शिखरम्_सम्बन्धि_राशिः++;

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    /* Setup a timer for the tick ISR. */
    v_Application_सज्जता_Tick_Timer_व्यवधानम्();

    /* Restore the context of the first task to run. */
    पत्तनम्_RESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    asm चञ्चल ( "return" );

    /* Should not reach here. */
    प्रत्यागम pdTRUE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) शून्य v_Application_सज्जता_Tick_Timer_व्यवधानम्( शून्य )
{
ध्रुव uint32_t ul_Compare_मेलनम् = ( ( configCPU_CLOCK_HZ / पत्तनम्_TIMER_PRESCALE ) / config_TICK_दरः_HZ ) - 1;

    /* Prescale of 8. */
    T1CON = 0;
    TMR1 = 0;

    PR1 = ( uint16_t ) ul_Compare_मेलनम्;

    /* Setup timer 1 interrupt priority. */
    IPC0bits.T1IP = config_KERNEL_व्यवधानम्_प्राथमिकता;

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

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    यदि( uxCriticalNesting == 0 )
    {
        पत्तनम्_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

शून्य __attribute__((__interrupt__, auto_psv)) config_TICK_व्यवधानम्_HANDLER( शून्य )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    यदि( xTaskIncrementTick() != pdFALSE )
    {
        पत्तनम्_YIELD();
    }
}
/*-----------------------------------------------------------*/
