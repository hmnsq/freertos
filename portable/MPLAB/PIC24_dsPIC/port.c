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
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Hardware specifics. */
#నిర్వచించు పోర్టు_బిట్టు_సమితి 1
#నిర్వచించు పోర్టు_TIMER_PRESCALE 8
#నిర్వచించు పోర్టు_INITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#నిర్వచితం_కాకపోతే config_KERNEL_అంతరాయం_ప్రాధాన్యత
    #నిర్వచించు config_KERNEL_అంతరాయం_ప్రాధాన్యత 1
#అయితే_ముగింపు

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#నిర్వచితం_కాకపోతే config_TICK_అంతరాయం_HANDLER
    #నిర్వచించు config_TICK_అంతరాయం_HANDLER T1_అంతరాయం
#అయితే_ముగింపు /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#నిర్వచించు పోర్టు_వాడని_PR_బిట్లు  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#ఒకవేళ config_KERNEL_అంతరాయం_ప్రాధాన్యత != 1
    #దోషం If config_KERNEL_అంతరాయం_ప్రాధాన్యత is not 1 then the #32 లోపల the following macros needs changing గమ్యం equal the పోర్టు_అంతరాయం_బిట్లు విలువ, which is ( config_KERNEL_అంతరాయం_ప్రాధాన్యత << 5 )
#అయితే_ముగింపు

#ఒకవేళ defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #నిర్వచితమైతే __HAS_EDS__
        #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                                                       \
                    asm అస్థిర(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
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
    #లేకపోతే /* __HAS_EDS__ */
        #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                                                       \
            asm అస్థిర(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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
        #అయితే_ముగింపు /* __HAS_EDS__ */
#అయితే_ముగింపు /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#ఒకవేళ defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                                                       \
        asm అస్థిర(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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

#అయితే_ముగింపు /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#నిర్వచితం_కాకపోతే పోర్టు_RESTORE_CONTEXT
    #దోషం Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#అయితే_ముగింపు

/*
 * Setup the timer used to generate the tick interrupt.
 */
శూన్య v_Application_అమరిక_Tick_Timer_అంతరాయం( శూన్య );

/*
 * See header file for description.
 */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
uint16_t us_సంకేతం;
UBaseType_t i;

స్థిరరాశి దొంతర_Type_t x_Initial_దొంతర[] =
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
    #ఒకవేళ defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
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
    #అయితే_ముగింపు
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    us_సంకేతం = ( uint16_t ) px_సంకేతం;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) us_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0;
    px_శిఖరం_యొక్క_దొంతర++;

    /* Status register with interrupts enabled. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_SR;
    px_శిఖరం_యొక్క_దొంతర++;

    /* Parameters are passed in W0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;
    px_శిఖరం_యొక్క_దొంతర++;

    కొరకు( i = 0; i < ( పరిమాణం( x_Initial_దొంతర ) / పరిమాణం( దొంతర_Type_t ) ); i++ )
    {
        *px_శిఖరం_యొక్క_దొంతర = x_Initial_దొంతర[ i ];
        px_శిఖరం_యొక్క_దొంతర++;
    }

    *px_శిఖరం_యొక్క_దొంతర = CORCON;
    px_శిఖరం_యొక్క_దొంతర++;

    #ఒకవేళ defined(__HAS_EDS__)
        *px_శిఖరం_యొక్క_దొంతర = DSRPAG;
        px_శిఖరం_యొక్క_దొంతర++;
        *px_శిఖరం_యొక్క_దొంతర = DSWPAG;
        px_శిఖరం_యొక్క_దొంతర++;
    #లేకపోతే /* __HAS_EDS__ */
        *px_శిఖరం_యొక్క_దొంతర = PSVPAG;
        px_శిఖరం_యొక్క_దొంతర++;
    #అయితే_ముగింపు /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_శిఖరం_యొక్క_దొంతర = 0x00;
    px_శిఖరం_యొక్క_దొంతర++;

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Setup a timer for the tick ISR. */
    v_Application_అమరిక_Tick_Timer_అంతరాయం();

    /* Restore the context of the first task to run. */
    పోర్టు_RESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    asm అస్థిర ( "return" );

    /* Should not reach here. */
    తిరిగి pdTRUE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) శూన్య v_Application_అమరిక_Tick_Timer_అంతరాయం( శూన్య )
{
స్థిరరాశి uint32_t ul_Compare_సరిపోలిక = ( ( configCPU_CLOCK_HZ / పోర్టు_TIMER_PRESCALE ) / config_TICK_రేటు_HZ ) - 1;

    /* Prescale of 8. */
    T1CON = 0;
    TMR1 = 0;

    PR1 = ( uint16_t ) ul_Compare_సరిపోలిక;

    /* Setup timer 1 interrupt priority. */
    IPC0bits.T1IP = config_KERNEL_అంతరాయం_ప్రాధాన్యత;

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

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    ఒకవేళ( uxCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

శూన్య __attribute__((__interrupt__, auto_psv)) config_TICK_అంతరాయం_HANDLER( శూన్య )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        పోర్టు_YIELD();
    }
}
/*-----------------------------------------------------------*/
