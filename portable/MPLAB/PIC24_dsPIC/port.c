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
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

/* Hardware specifics. */
#define portBIT_SET 1
#define portTIMER_PRESCALE 8
#define portINITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#ifndef configKERNEL_INTERRUPT_PRIORITY
    #define configKERNEL_INTERRUPT_PRIORITY 1
#endif

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#ifndef configTICK_INTERRUPT_HANDLER
    #define configTICK_INTERRUPT_HANDLER _T1Interrupt
#endif /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#define portUNUSED_PR_BITS  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#எனில் configKERNEL_INTERRUPT_PRIORITY != 1
    #error If configKERNEL_INTERRUPT_PRIORITY is not 1 then the #32 in the following macros needs changing to equal the portINTERRUPT_BITS மதிப்பு, which is ( configKERNEL_INTERRUPT_PRIORITY << 5 )
#endif

#எனில் defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #ifdef __HAS_EDS__
        #define portRESTORE_CONTEXT()                                                                                       \
                    asm நிலையற்ற(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
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
    #இல்லையெனில் /* __HAS_EDS__ */
        #define portRESTORE_CONTEXT()                                                                                       \
            asm நிலையற்ற(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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
        #endif /* __HAS_EDS__ */
#endif /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#எனில் defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #define portRESTORE_CONTEXT()                                                                                       \
        asm நிலையற்ற(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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

#endif /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#ifndef portRESTORE_CONTEXT
    #error Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#endif

/*
 * Setup the timer used to generate the tick interrupt.
 */
வெறுமை vApplicationSetupTickTimerInterrupt( வெறுமை );

/*
 * See header file for description.
 */
அடுக்கு_Type_t *px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t *px_உச்சி_Of_அடுக்கு, TaskFunction_t pxCode, வெறுமை *pvParameters )
{
uint16_t usCode;
UBaseType_t i;

மாறிலி அடுக்கு_Type_t x_Initial_அடுக்கு[] =
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
    #எனில் defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
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
    #endif
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    usCode = ( uint16_t ) pxCode;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) usCode;
    px_உச்சி_Of_அடுக்கு++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) 0;
    px_உச்சி_Of_அடுக்கு++;

    /* Status register with interrupts enabled. */
    *px_உச்சி_Of_அடுக்கு = portINITIAL_SR;
    px_உச்சி_Of_அடுக்கு++;

    /* Parameters are passed in W0. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pvParameters;
    px_உச்சி_Of_அடுக்கு++;

    க்கு( i = 0; i < ( அளவு( x_Initial_அடுக்கு ) / அளவு( அடுக்கு_Type_t ) ); i++ )
    {
        *px_உச்சி_Of_அடுக்கு = x_Initial_அடுக்கு[ i ];
        px_உச்சி_Of_அடுக்கு++;
    }

    *px_உச்சி_Of_அடுக்கு = CORCON;
    px_உச்சி_Of_அடுக்கு++;

    #எனில் defined(__HAS_EDS__)
        *px_உச்சி_Of_அடுக்கு = DSRPAG;
        px_உச்சி_Of_அடுக்கு++;
        *px_உச்சி_Of_அடுக்கு = DSWPAG;
        px_உச்சி_Of_அடுக்கு++;
    #இல்லையெனில் /* __HAS_EDS__ */
        *px_உச்சி_Of_அடுக்கு = PSVPAG;
        px_உச்சி_Of_அடுக்கு++;
    #endif /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_உச்சி_Of_அடுக்கு = 0x00;
    px_உச்சி_Of_அடுக்கு++;

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    /* Setup a timer for the tick ISR. */
    vApplicationSetupTickTimerInterrupt();

    /* Restore the context of the first task to run. */
    portRESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    asm நிலையற்ற ( "return" );

    /* Should not reach here. */
    திரும்பு pdTRUE;
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) வெறுமை vApplicationSetupTickTimerInterrupt( வெறுமை )
{
மாறிலி uint32_t ulCompareMatch = ( ( configCPU_CLOCK_HZ / portTIMER_PRESCALE ) / configTICK_RATE_HZ ) - 1;

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

வெறுமை vPortEnterCritical( வெறுமை )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

வெறுமை vPortExitCritical( வெறுமை )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    எனில்( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

வெறுமை __attribute__((__interrupt__, auto_psv)) configTICK_INTERRUPT_HANDLER( வெறுமை )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    எனில்( xTaskIncrementTick() != pdFALSE )
    {
        portYIELD();
    }
}
/*-----------------------------------------------------------*/
