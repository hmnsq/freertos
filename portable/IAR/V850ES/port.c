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

/* Standard includes. */
#समावेश <stdlib.h>

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"

/* Critical nesting should be initialised to a non zero value so interrupts don't
 * accidentally get enabled before the scheduler is started. */
#घोषणा portINITIAL_CRITICAL_NESTING    ( ( ढेर_Type_t ) 10 )

/* The PSW value assigned to tasks when they start to run for the first time. */
#घोषणा portPSW                         ( ( ढेर_Type_t ) 0x00000000 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
प्रकार व्योम TCB_t;
बाह्य अस्थिर TCB_t * अस्थिर pxCurrentTCB;

/* Keeps track of the nesting level of critical sections. */
अस्थिर ढेर_Type_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/

/* Sets up the timer to generate the tick interrupt. */
अटल व्योम prvSetupTimerInterrupt( व्योम );

/*-----------------------------------------------------------*/
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;     /* Task function start address */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;     /* Task function start address */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portPSW;                    /* Initial PSW value */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x20202020; /* Initial Value of R20 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x21212121; /* Initial Value of R21 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x22222222; /* Initial Value of R22 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x23232323; /* Initial Value of R23 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x24242424; /* Initial Value of R24 */
    px_शीर्ष_Of_ढेर--;
    #अगर ( __DATA_MODEL__ == 0 ) || ( __DATA_MODEL__ == 1 )
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x25252525; /* Initial Value of R25 */
        px_शीर्ष_Of_ढेर--;
    #पूर्ण_अगर /* configDATA_MODE */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x26262626; /* Initial Value of R26 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x27272727; /* Initial Value of R27 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x28282828; /* Initial Value of R28 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x29292929; /* Initial Value of R29 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x30303030; /* Initial Value of R30 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x19191919; /* Initial Value of R19 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x18181818; /* Initial Value of R18 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x17171717; /* Initial Value of R17 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x16161616; /* Initial Value of R16 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x15151515; /* Initial Value of R15 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x14141414; /* Initial Value of R14 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x13131313; /* Initial Value of R13 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x12121212; /* Initial Value of R12 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x11111111; /* Initial Value of R11 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x10101010; /* Initial Value of R10 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x99999999; /* Initial Value of R09 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x88888888; /* Initial Value of R08 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x77777777; /* Initial Value of R07 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x66666666; /* Initial Value of R06 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x55555555; /* Initial Value of R05 */
    px_शीर्ष_Of_ढेर--;
    #अगर __DATA_MODEL__ == 0 || __DATA_MODEL__ == 1
        *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x44444444; /* Initial Value of R04 */
        px_शीर्ष_Of_ढेर--;
    #पूर्ण_अगर /* configDATA_MODE */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x22222222;   /* Initial Value of R02 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters; /* R1 is expected to hold the function parameter*/
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portNO_CRITICAL_SECTION_NESTING;

    /*
     * Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task.
     */
    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run. */
    vPortStart();

    /* Should not get here as the tasks are now running! */
    वापस pdTRUE;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* It is unlikely that the V850ES/Fx3 port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Hardware initialisation to generate the RTOS tick.  This uses
 */
अटल व्योम prvSetupTimerInterrupt( व्योम )
{
    TM0CE = 0;    /* TMM0 operation disable */
    TM0EQMK0 = 1; /* INTTM0EQ0 interrupt disable */
    TM0EQIF0 = 0; /* clear INTTM0EQ0 interrupt flag */

    #अगर_घोषित __IAR_V850ES_Fx3__
    {
        TM0CMP0 = ( ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) / 2 ) - 1 ); /* divided by 2 because peripherals only run at CPU_CLOCK/2 */
    }
    #अन्यथा
    {
        TM0CMP0 = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ );
    }
    #पूर्ण_अगर

    TM0EQIC0 &= 0xF8;
    TM0CTL0 = 0x00;
    TM0EQIF0 = 0; /* clear INTTM0EQ0 interrupt flag */
    TM0EQMK0 = 0; /* INTTM0EQ0 interrupt enable */
    TM0CE = 1;    /* TMM0 operation enable */
}
/*-----------------------------------------------------------*/
