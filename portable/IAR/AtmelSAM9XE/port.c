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
* Implementation of functions defined in portable.h for the Atmel ARM7 port.
*----------------------------------------------------------*/


/* Standard includes. */
#अन्तर्भाव <stdlib.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Hardware includes. */
#अन्तर्भाव <board.h>
#अन्तर्भाव <pio/pio.h>
#अन्तर्भाव <pio/pio_it.h>
#अन्तर्भाव <pit/pit.h>
#अन्तर्भाव <aic/aic.h>
#अन्तर्भाव <tc/tc.h>
#अन्तर्भाव <utility/led.h>
#अन्तर्भाव <utility/trace.h>

/*-----------------------------------------------------------*/

/* Constants required to setup the initial stack. */
#define portINITIAL_SPSR           ( ( राशिः_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT         ( ( राशिः_Type_t ) 0x20 )
#define portINSTRUCTION_SIZE       ( ( राशिः_Type_t ) 4 )

/* Constants required to setup the PIT. */
#define port1MHz_IN_Hz             ( 1000000ul )
#define port1SECOND_IN_uS          ( 1000000.0 )

/* Constants required to handle critical sections. */
#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )


#define portINT_LEVEL_SENSITIVE    0
#define portPIT_ENABLE             ( ( uint16_t ) 0x1 << 24 )
#define portPIT_INT_ENABLE         ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
स्थिर शून्य prvSetupTimerInterrupt( शून्य );

/* The PIT interrupt handler - the RTOS tick. */
स्थिर शून्य vPortTickISR( शून्य );

/* ulCriticalNesting will get set to zero when the first task starts.  It
 * cannot be initialised to 0 as this will cause interrupts to be enabled
 * during the kernel initialisation process. */
uint32_t ulCriticalNesting = ( uint32_t ) 9999;

/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
राशिः_Type_t * px_Port_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_Of_राशिः,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    राशिः_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_शिखरम्_Of_राशिः;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_शिखरम्_Of_राशिः--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pxCode + portINSTRUCTION_SIZE;
    px_शिखरम्_Of_राशिः--;

    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x12121212;    /* R12 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x11111111;    /* R11 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x10101010;    /* R10 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x09090909;    /* R9 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x08080808;    /* R8 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x07070707;    /* R7 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x06060606;    /* R6 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x05050505;    /* R5 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x04040404;    /* R4 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x03030303;    /* R3 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x02020202;    /* R2 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x01010101;    /* R1 */
    px_शिखरम्_Of_राशिः--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pvParameters; /* R0 */
    px_शिखरम्_Of_राशिः--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) portINITIAL_SPSR;

    #ifdef THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_शिखरम्_Of_राशिः |= portTHUMB_MODE_BIT;
    }
    #endif

    px_शिखरम्_Of_राशिः--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_शिखरम्_Of_राशिः = portNO_CRITICAL_NESTING;

    पटिनिवत्त px_शिखरम्_Of_राशिः;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    बाह्य शून्य vPortStartFirstTask( शून्य );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    vPortStartFirstTask();

    /* Should not get here! */
    पटिनिवत्त 0;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

स्थिर __arm शून्य vPortTickISR( शून्य )
{
    चञ्चल uint32_t ulDummy;

    /* Increment the tick count - which may wake some tasks but as the
     * preemptive scheduler is not being used any woken task is not given
     * processor time no matter what its priority. */
    सचे( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the PIT interrupt. */
    ulDummy = AT91C_BASE_PITC->PITC_PIVR;

    /* To remove compiler warning. */
    ( शून्य ) ulDummy;

    /* The AIC is cleared in the asm wrapper, outside of this function. */
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSetupTimerInterrupt( शून्य )
{
    ध्रुव uint32_t ulPeriodIn_uS = ( 1.0 / ( द्विगुण ) configTICK_RATE_HZ ) * port1SECOND_IN_uS;

    /* Setup the PIT for the required frequency. */
    PIT_Init( ulPeriodIn_uS, BOARD_MCK / port1MHz_IN_Hz );

    /* Setup the PIT interrupt. */
    AIC_DisableIT( AT91C_ID_SYS );
    AIC_ConfigureIT( AT91C_ID_SYS, AT91C_AIC_PRIOR_LOWEST, vPortTickISR );
    AIC_EnableIT( AT91C_ID_SYS );
    PIT_EnableIT();
}
/*-----------------------------------------------------------*/

शून्य vPortEnterCritical( शून्य )
{
    /* Disable interrupts first! */
    __disable_irq();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य vPortExitCritical( शून्य )
{
    सचे( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        सचे( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            __enable_irq();
        }
    }
}
/*-----------------------------------------------------------*/
