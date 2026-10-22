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

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the ST STR71x ARM7
* port.
*----------------------------------------------------------*/

/* Library includes. */
#ضمن "wdg.h"
#ضمن "eic.h"

/* Standard includes. */
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to setup the initial stack. */
#define portINITIAL_SPSR           ( ( ڈھیر_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT         ( ( ڈھیر_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE       ( ( ڈھیر_Type_t ) 4 )

/* Constants required to handle critical sections. */
#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )

#define portMICROS_PER_SECOND      1000000

/*-----------------------------------------------------------*/

/* Setup the watchdog to generate the tick interrupts. */
ساكن فراغ prvSetupTimerInterrupt( فراغ );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/* Tick interrupt routines for cooperative and preemptive operation
 * respectively.  The preemptive version is not defined as __irq as it is called
 * from an asm wrapper function. */
__arm __irq فراغ vPortNonPreemptiveTick( فراغ );
فراغ vPortPreemptiveTick( فراغ );

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
ڈھیر_Type_t * px_Port_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_Of_ڈھیر,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    ڈھیر_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_چوٹی_Of_ڈھیر;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوٹی_Of_ڈھیر--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_چوٹی_Of_ڈھیر--;

    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x12121212;    /* R12 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x11111111;    /* R11 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x10101010;    /* R10 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x09090909;    /* R9 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x08080808;    /* R8 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x07070707;    /* R7 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x06060606;    /* R6 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x05050505;    /* R5 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x04040404;    /* R4 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x03030303;    /* R3 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x02020202;    /* R2 */
    px_چوٹی_Of_ڈھیر--;
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) 0x01010101;    /* R1 */
    px_چوٹی_Of_ڈھیر--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */
    px_چوٹی_Of_ڈھیر--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_چوٹی_Of_ڈھیر = ( ڈھیر_Type_t ) portINITIAL_SPSR;

    إذا( ( ( uint32_t ) pxCode & 0x01UL ) != 0x00UL )
    {
        /* We want the task to start in thumb mode. */
        *px_چوٹی_Of_ڈھیر |= portTHUMB_MODE_BIT;
    }

    px_چوٹی_Of_ڈھیر--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_چوٹی_Of_ڈھیر = portNO_CRITICAL_NESTING;

    أرجع px_چوٹی_Of_ڈھیر;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    خارجي فراغ vPortStartFirstTask( فراغ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */
__arm __irq فراغ vPortNonPreemptiveTick( فراغ )
{
    /* Increment the tick count - which may wake some tasks but as the
     * preemptive scheduler is not being used any woken task is not given
     * processor time no matter what its priority. */
    xTaskIncrementTick();

    /* Clear the interrupt in the watchdog and EIC. */
    WDG->SR = 0x0000;
    portCLEAR_EIC();
}
/*-----------------------------------------------------------*/

/* This function is called from an asm wrapper, so does not require the __irq
 * keyword. */
فراغ vPortPreemptiveTick( فراغ )
{
    /* Increment the tick counter. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        /* Select a new task to execute. */
        vTaskSwitchContext();
    }

    /* Clear the interrupt in the watchdog and EIC. */
    WDG->SR = 0x0000;
    portCLEAR_EIC();
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSetupTimerInterrupt( فراغ )
{
    /* Set the watchdog up to generate a periodic tick. */
    WDG_ECITConfig( DISABLE );
    WDG_CntOnOffConfig( DISABLE );
    WDG_Period_قدر_Config( portMICROS_PER_SECOND / configTICK_RATE_HZ );

    /* Setup the tick interrupt in the EIC. */
    EIC_IRQChannelPriorityConfig( WDG_IRQChannel, 1 );
    EIC_IRQChannelConfig( WDG_IRQChannel, ENABLE );
    EIC_IRQConfig( ENABLE );
    WDG_ECITConfig( ENABLE );

    /* Start the timer - interrupts are actually disabled at this point so
     * it is safe to do this here. */
    WDG_CntOnOffConfig( ENABLE );
}
/*-----------------------------------------------------------*/

__arm __interwork فراغ vPortEnterCritical( فراغ )
{
    /* Disable interrupts first! */
    __disable_interrupt();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__arm __interwork فراغ vPortExitCritical( فراغ )
{
    إذا( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            __enable_interrupt();
        }
    }
}
/*-----------------------------------------------------------*/
