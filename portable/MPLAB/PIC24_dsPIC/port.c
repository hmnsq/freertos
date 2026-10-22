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
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Hardware specifics. */
#تعریف_کرو پورٹ_ثنائی_ہندسہ_سیٹ 1
#تعریف_کرو پورٹ_TIMER_PRESCALE 8
#تعریف_کرو پورٹ_INITIAL_SR  0

/* Defined for backward compatibility with project created prior to
FreeRTOS.org V4.3.0. */
#اگر_غیر_تعریف_شدہ config_KERNEL_مداخلت_ترجیح
    #تعریف_کرو config_KERNEL_مداخلت_ترجیح 1
#اگر_ختم

/* Use _T1Interrupt as the interrupt handler name if the application writer has
not provided their own. */
#اگر_غیر_تعریف_شدہ config_TICK_مداخلت_HANDLER
    #تعریف_کرو config_TICK_مداخلت_HANDLER T1_مداخلت
#اگر_ختم /* configTICK_INTERRUPT_HANDLER */

/* The program counter is only 23 bits. */
#تعریف_کرو پورٹ_غیر_مستعمل_PR_بٹ  0x7f

/* Records the nesting depth of calls to portENTER_CRITICAL(). */
UBaseType_t uxCriticalNesting = 0xef;

#اگر config_KERNEL_مداخلت_ترجیح != 1
    #غلطی If config_KERNEL_مداخلت_ترجیح is not 1 then the #32 اندر the following macros needs changing مقصد equal the پورٹ_مداخلت_بٹ قدر, which is ( config_KERNEL_مداخلت_ترجیح << 5 )
#اگر_ختم

#اگر defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ )

    #اگر_تعریف_شدہ __HAS_EDS__
        #تعریف_کرو پورٹ_RESTORE_CONTEXT()                                                                                       \
                    asm متلون(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */       \
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
    #ورنہ /* __HAS_EDS__ */
        #تعریف_کرو پورٹ_RESTORE_CONTEXT()                                                                                       \
            asm متلون(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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
        #اگر_ختم /* __HAS_EDS__ */
#اگر_ختم /* defined( __PIC24E__ ) || defined ( __PIC24F__ ) || defined( __PIC24FK__ ) || defined( __PIC24H__ ) */

#اگر defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

    #تعریف_کرو پورٹ_RESTORE_CONTEXT()                                                                                       \
        asm متلون(   "MOV    _pxCurrentTCB, W0       \n" /* Restore the stack pointer for the task. */               \
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

#اگر_ختم /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */

#اگر_غیر_تعریف_شدہ پورٹ_RESTORE_CONTEXT
    #غلطی Unrecognised device selected

    /* Note:  dsPIC parts with EDS are not supported as there is no easy way to
    recover the hardware stacked copies for DOCOUNT, DOHIGH, DOLOW. */
#اگر_ختم

/*
 * Setup the timer used to generate the tick interrupt.
 */
خالی v_Application_تیاری_Tick_Timer_مداخلت( خالی );

/*
 * See header file for description.
 */
ڈھیر_Type_t *px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t *px_چوٹی_کا_ڈھیر, TaskFunction_t px_رمز, خالی *pvParameters )
{
uint16_t us_رمز;
UBaseType_t i;

ثابت ڈھیر_Type_t x_Initial_ڈھیر[] =
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
    #اگر defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )
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
    #اگر_ختم
};

    /* Setup the stack as if a yield had occurred.

    Save the low bytes of the program counter. */
    us_رمز = ( uint16_t ) px_رمز;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) us_رمز;
    px_چوٹی_کا_ڈھیر++;

    /* Save the high byte of the program counter.  This will always be zero
    here as it is passed in a 16bit pointer.  If the address is greater than
    16 bits then the pointer will point to a jump table. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0;
    px_چوٹی_کا_ڈھیر++;

    /* Status register with interrupts enabled. */
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_SR;
    px_چوٹی_کا_ڈھیر++;

    /* Parameters are passed in W0. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;
    px_چوٹی_کا_ڈھیر++;

    برائے( i = 0; i < ( حجم( x_Initial_ڈھیر ) / حجم( ڈھیر_Type_t ) ); i++ )
    {
        *px_چوٹی_کا_ڈھیر = x_Initial_ڈھیر[ i ];
        px_چوٹی_کا_ڈھیر++;
    }

    *px_چوٹی_کا_ڈھیر = CORCON;
    px_چوٹی_کا_ڈھیر++;

    #اگر defined(__HAS_EDS__)
        *px_چوٹی_کا_ڈھیر = DSRPAG;
        px_چوٹی_کا_ڈھیر++;
        *px_چوٹی_کا_ڈھیر = DSWPAG;
        px_چوٹی_کا_ڈھیر++;
    #ورنہ /* __HAS_EDS__ */
        *px_چوٹی_کا_ڈھیر = PSVPAG;
        px_چوٹی_کا_ڈھیر++;
    #اگر_ختم /* __HAS_EDS__ */

    /* Finally the critical nesting depth. */
    *px_چوٹی_کا_ڈھیر = 0x00;
    px_چوٹی_کا_ڈھیر++;

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Setup a timer for the tick ISR. */
    v_Application_تیاری_Tick_Timer_مداخلت();

    /* Restore the context of the first task to run. */
    پورٹ_RESTORE_CONTEXT();

    /* Simulate the end of the yield function. */
    asm متلون ( "return" );

    /* Should not reach here. */
    واپس pdTRUE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
__attribute__(( weak )) خالی v_Application_تیاری_Tick_Timer_مداخلت( خالی )
{
ثابت uint32_t ul_Compare_مطابقت = ( ( configCPU_CLOCK_HZ / پورٹ_TIMER_PRESCALE ) / config_TICK_شرح_HZ ) - 1;

    /* Prescale of 8. */
    T1CON = 0;
    TMR1 = 0;

    PR1 = ( uint16_t ) ul_Compare_مطابقت;

    /* Setup timer 1 interrupt priority. */
    IPC0bits.T1IP = config_KERNEL_مداخلت_ترجیح;

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

خالی v_پورٹ_Enter_Critical( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    اگر( uxCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

خالی __attribute__((__interrupt__, auto_psv)) config_TICK_مداخلت_HANDLER( خالی )
{
    /* Clear the timer interrupt. */
    IFS0bits.T1IF = 0;

    اگر( xTaskIncrementTick() != pdFALSE )
    {
        پورٹ_YIELD();
    }
}
/*-----------------------------------------------------------*/
