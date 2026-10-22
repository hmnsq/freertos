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
#समावेश "FreeRTOS.h"
#समावेश "task.h"

/* Hardware specifics. */
#घोषणा portBIT_SET 1
#घोषणा portTIMER_PRESCALE 8
#घोषणा portINITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#अगर_अघोषित configKERNEL_INTERRUPT_PRIORITY
    #घोषणा configKERNEL_INTERRUPT_PRIORITY 1
#पूर्ण_अगर

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#अगर_अघोषित configTICK_INTERRUPT_HANDLER
    #घोषणा configTICK_INTERRUPT_HANDLER _T1Interrupt
#पूर्ण_अगर /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#घोषणा portUNUSED_PR_BITS  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#अगर configKERNEL_INTERRUPT_PRIORITY != 1
    #त्रुटि If configKERNEL_INTERRUPT_PRIORITY is not 1 then the #32 in the following macros needs changing to equal the portINTERRUPT_BITS मूल्य, which is ( configKERNEL_INTERRUPT_PRIORITY << 5 )
#पूर्ण_अगर

#अगर defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #अगर_घोषित __HAS_EDS__
        #घोषणा portRESTORE_CONTEXT()                                                                                       \
                    यंत्र अस्थिर(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
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
        #घोषणा portRESTORE_CONTEXT()                                                                                       \
            यंत्र अस्थिर(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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
        #पूर्ण_अगर /* __HAS_EDS__ */
#पूर्ण_अगर /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#अगर defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #घोषणा portRESTORE_CONTEXT()                                                                                       \
        यंत्र अस्थिर(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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

#पूर्ण_अगर /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#अगर_अघोषित portRESTORE_CONTEXT
    #त्रुटि Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#पूर्ण_अगर

/*
 * Setup the timer used to generate the tick interrupt.
 */
व्योम vApplicationSetupTickTimerInterrupt( व्योम );

/*
 * See header file for description.
 */
ढेर_Type_t *px_Port_Initialise_ढेर( ढेर_Type_t *px_शीर्ष_Of_ढेर, TaskFunction_t pxCode, व्योम *pvParameters )
{
uint16_t usCode;
UBaseType_t i;

स्थिर ढेर_Type_t x_Initial_ढेर[] =
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
    #अगर defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
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
    #पूर्ण_अगर
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    usCode = ( uint16_t ) pxCode;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) usCode;
    px_शीर्ष_Of_ढेर++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0;
    px_शीर्ष_Of_ढेर++;

    /* Status register with interrupts enabled. */
    *px_शीर्ष_Of_ढेर = portINITIAL_SR;
    px_शीर्ष_Of_ढेर++;

    /* Parameters are passed in W0. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters;
    px_शीर्ष_Of_ढेर++;

    क्रम( i = 0; i < ( माप( x_Initial_ढेर ) / माप( ढेर_Type_t ) ); i++ )
    {
        *px_शीर्ष_Of_ढेर = x_Initial_ढेर[ i ];
        px_शीर्ष_Of_ढेर++;
    }

    *px_शीर्ष_Of_ढेर = CORCON;
    px_शीर्ष_Of_ढेर++;

    #अगर defined(__HAS_EDS__)
        *px_शीर्ष_Of_ढेर = DSRPAG;
        px_शीर्ष_Of_ढेर++;
        *px_शीर्ष_Of_ढेर = DSWPAG;
        px_शीर्ष_Of_ढेर++;
    #अन्यथा /* __HAS_EDS__ */
        *px_शीर्ष_Of_ढेर = PSVPAG;
        px_शीर्ष_Of_ढेर++;
    #पूर्ण_अगर /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_शीर्ष_Of_ढेर = 0x00;
    px_शीर्ष_Of_ढेर++;

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    /* Setup a timer for the tick ISR. */
    vApplicationSetupTickTimerInterrupt();

    /* Restore the context of the first task to run. */
    portRESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    यंत्र अस्थिर ( "return" );

    /* Should not reach here. */
    वापस pdTRUE;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) व्योम vApplicationSetupTickTimerInterrupt( व्योम )
{
स्थिर uint32_t ulCompareMatch = ( ( configCPU_CLOCK_HZ / portTIMER_PRESCALE ) / configTICK_RATE_HZ ) - 1;

    /* Prescale of 8. */
    T1CON = 0;
    TMR1 = 0;

    PR1 = ( uint16_t ) ulCompareMatch;

    /* Setup timer 1 interrupt priority. */
    IPC0bits.T1IP = configKERNEL_INTERRUPT_PRIORITY;

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

व्योम vPortEnterCritical( व्योम )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    अगर( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

व्योम __attribute__((__interrupt__, auto_psv)) configTICK_INTERRUPT_HANDLER( व्योम )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    अगर( xTaskIncrementTick() != pdFALSE )
    {
        portYIELD();
    }
}
/*-----------------------------------------------------------*/
