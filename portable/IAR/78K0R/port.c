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
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* The critical nesting value is initialised to a non zero value to ensure
 * interrupts don't accidentally become enabled before the scheduler is started. */
#وصف_ڪريو پورٽ_INITIAL_CRITICAL_NESTING    ( ( uint16_t ) 10 )

/* Initial PSW value allocated to a newly created task.
 *   1100011000000000
 *   ||||||||-------------- Fill byte
 *   |||||||--------------- Carry Flag cleared
 *   |||||----------------- In-service priority Flags set to low level
 *   ||||------------------ Register bank Select 0 Flag cleared
 *   |||------------------- Auxiliary Carry Flag cleared
 *   ||-------------------- Register bank Select 1 Flag cleared
 *   |--------------------- Zero Flag set
 *   ---------------------- Global Interrupt Flag set (enabled)
 */
#وصف_ڪريو پورٽ_PSW                         ( 0xc6UL )

/* We require the address of the pxCurrentTCB variable, but don't want to know
 * any details of its type. */
تعريفنوع فراغ TCB_t;
خارجي متطاير TCB_t * متطاير pxCurrentTCB;

/* Most ports implement critical sections by placing the interrupt flags on
 * the stack before disabling interrupts.  Exiting the critical section is then
 * simply a case of popping the flags from the stack.  As 78K0 IAR does not use
 * a frame pointer this cannot be done as modifying the stack will clobber all
 * the stack variables.  Instead each task maintains a count of the critical
 * section nesting depth.  Each time a critical section is entered the count is
 * incremented.  Each time a critical section is left the count is decremented -
 * with interrupts only being re-enabled if the count is zero.
 *
 * usCriticalNesting will get set to zero when the scheduler starts, but must
 * not be initialised to zero as this will cause problems during the startup
 * sequence. */
متطاير uint16_t usCriticalNesting = پورٽ_INITIAL_CRITICAL_NESTING;
/*-----------------------------------------------------------*/

/*
 * Sets up the periodic ISR used for the RTOS tick.
 */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See the header file portable.h.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    uint32_t * pulLocal;

    #إذا config_يادگيري_گهڻائي == 1
    {
        /* Parameters are passed in on the stack, and written using a 32bit value
         * hence a space is left for the second two bytes. */
        px_چوٽي_جو_ڍير--;

        /* Write in the parameter value. */
        pulLocal = ( uint32_t * ) px_چوٽي_جو_ڍير;
        *pulLocal = ( uint32_t ) pvParameters;
        px_چوٽي_جو_ڍير--;

        /* These values are just spacers.  The return address of the function
         * would normally be written here. */
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xcdcd;
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xcdcd;
        px_چوٽي_جو_ڍير--;

        /* The start address / PSW value is also written in as a 32bit value,
         * so leave a space for the second two bytes. */
        px_چوٽي_جو_ڍير--;

        /* Task function start address combined with the PSW. */
        pulLocal = ( uint32_t * ) px_چوٽي_جو_ڍير;
        *pulLocal = ( ( ( uint32_t ) px_ڪوڊ ) | ( پورٽ_PSW << 24UL ) );
        px_چوٽي_جو_ڍير--;

        /* An initial value for the AX register. */
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x1111;
        px_چوٽي_جو_ڍير--;
    }
    #وإلا /* if configMEMORY_MODE == 1 */
    {
        /* Task function address is written to the stack first.  As it is
         * written as a 32bit value a space is left on the stack for the second
         * two bytes. */
        px_چوٽي_جو_ڍير--;

        /* Task function start address combined with the PSW. */
        pulLocal = ( uint32_t * ) px_چوٽي_جو_ڍير;
        *pulLocal = ( ( ( uint32_t ) px_ڪوڊ ) | ( پورٽ_PSW << 24UL ) );
        px_چوٽي_جو_ڍير--;

        /* The parameter is passed in AX. */
        *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;
        px_چوٽي_جو_ڍير--;
    }
    #جيڪڏهن_پورو /* if configMEMORY_MODE == 1 */

    /* An initial value for the HL register. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x2222;
    px_چوٽي_جو_ڍير--;

    /* CS and ES registers. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x0F00;
    px_چوٽي_جو_ڍير--;

    /* Finally the remaining general purpose registers DE and BC */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xDEDE;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0xBCBC;
    px_چوٽي_جو_ڍير--;

    /* Finally the critical section nesting count is set to zero when the task
     * first starts. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_NO_CRITICAL_SECTION_NESTING;

    /* Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task. */
    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
     * this function is called. */
    prv_تياري_Timer_مداخلت();

    /* Restore the context of the first task that is going to run. */
    v_پورٽ_شروعات();

    /* Should not get here as the tasks are now running! */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the 78K0R port will get stopped.  If required simply
     * disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    /* Setup channel 5 of the TAU to generate the tick interrupt. */

    /* First the Timer Array Unit has to be enabled. */
    TAU0EN = 1;

    /* To configure the Timer Array Unit all Channels have to first be stopped. */
    TT0 = 0xff;

    /* Interrupt of Timer Array Unit Channel 5 is disabled to set the interrupt
     * priority. */
    TMMK05 = 1;

    /* Clear Timer Array Unit Channel 5 interrupt flag. */
    TMIF05 = 0;

    /* Set Timer Array Unit Channel 5 interrupt priority */
    TMPR005 = 0;
    TMPR105 = 0;

    /* Set Timer Array Unit Channel 5 Mode as interval timer. */
    TMR05 = 0x0000;

    /* Set the compare match value according to the tick rate we want. */
    TDR05 = ( TickType_t ) ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );

    /* Set Timer Array Unit Channel 5 output mode */
    TOM0 &= ~0x0020;

    /* Set Timer Array Unit Channel 5 output level */
    TOL0 &= ~0x0020;

    /* Set Timer Array Unit Channel 5 output enable */
    TOE0 &= ~0x0020;

    /* Interrupt of Timer Array Unit Channel 5 enabled */
    TMMK05 = 0;

    /* Start Timer Array Unit Channel 5.*/
    TS0 |= 0x0020;
}
/*-----------------------------------------------------------*/
