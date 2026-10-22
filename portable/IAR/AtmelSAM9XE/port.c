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
#ضمن <stdlib.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Hardware includes. */
#ضمن <board.h>
#ضمن <pio/pio.h>
#ضمن <pio/pio_it.h>
#ضمن <pit/pit.h>
#ضمن <aic/aic.h>
#ضمن <tc/tc.h>
#ضمن <utility/led.h>
#ضمن <utility/trace.h>

/*-----------------------------------------------------------*/

/* Constants required to setup the initial stack. */
#تعریف_کړه پورټ_INITIAL_SPSR           ( ( ډېری_Type_t ) 0x1f )      /* System mode, ARM mode, interrupts enabled. */
#تعریف_کړه پورټ_THUMB_ډېرپېښ_بټ         ( ( ډېری_Type_t ) 0x20 )
#تعریف_کړه پورټ_INSTRUCTION_اندازه       ( ( ډېری_Type_t ) 4 )

/* Constants required to setup the PIT. */
#تعریف_کړه port1_MHz_دننه_Hz             ( 1000000ul )
#تعریف_کړه port1_دوهم_دننه_u_S          ( 1000000.0 )

/* Constants required to handle critical sections. */
#تعریف_کړه پورټ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )


#تعریف_کړه پورټ_INT_LEVEL_SENSITIVE    0
#تعریف_کړه پورټ_PIT_ENABLE             ( ( uint16_t ) 0x1 << 24 )
#تعریف_کړه پورټ_PIT_INT_ENABLE         ( ( uint16_t ) 0x1 << 25 )
/*-----------------------------------------------------------*/

/* Setup the PIT to generate the tick interrupts. */
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );

/* The PIT interrupt handler - the RTOS tick. */
ساكن فراغ v_پورټ_Tick_ISR( فراغ );

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
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    ډېری_Type_t * pxOriginalTOS;

    pxOriginalTOS = px_سر_د_ډېری;

    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_سر_د_ډېری--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First on the stack is the return address - which in this case is the
     * start of the task.  The offset is added to make the return address appear
     * as it would within an IRQ ISR. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ + پورټ_INSTRUCTION_اندازه;
    px_سر_د_ډېری--;

    *px_سر_د_ډېری = ( ډېری_Type_t ) 0xaaaaaaaa;    /* R14 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) pxOriginalTOS; /* Stack used when task starts goes in R13. */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12121212;    /* R12 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11111111;    /* R11 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10101010;    /* R10 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09090909;    /* R9 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x08080808;    /* R8 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07070707;    /* R7 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06060606;    /* R6 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x05050505;    /* R5 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04040404;    /* R4 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03030303;    /* R3 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x02020202;    /* R2 */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) 0x01010101;    /* R1 */
    px_سر_د_ډېری--;

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */
    px_سر_د_ډېری--;

    /* The status register is set for system mode, with interrupts enabled. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_INITIAL_SPSR;

    #که_تعریف_شوی THUMB_INTERWORK
    {
        /* We want the task to start in thumb mode. */
        *px_سر_د_ډېری |= پورټ_THUMB_ډېرپېښ_بټ;
    }
    #د_که_پای

    px_سر_د_ډېری--;

    /* Interrupt flags cannot always be stored on the stack and will
     * instead be stored in a variable, which is then saved as part of the
     * tasks context. */
    *px_سر_د_ډېری = پورټ_NO_CRITICAL_NESTING;

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخله();

    /* Start the first task. */
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* It is unlikely that the ARM port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

ساكن __arm فراغ v_پورټ_Tick_ISR( فراغ )
{
    متطاير uint32_t ulDummy;

    /* Increment the tick count - which may wake some tasks but as the
     * preemptive scheduler is not being used any woken task is not given
     * processor time no matter what its priority. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the PIT interrupt. */
    ulDummy = AT91_C_بنسټ_PITC->PITC_PIVR;

    /* To remove compiler warning. */
    ( فراغ ) ulDummy;

    /* The AIC is cleared in the asm wrapper, outside of this function. */
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    ثابت uint32_t ul_Period_دننه_u_S = ( 1.0 / ( مزدوج ) config_TICK_شرح_HZ ) * port1_دوهم_دننه_u_S;

    /* Setup the PIT for the required frequency. */
    PIT_Init( ul_Period_دننه_u_S, BOARD_MCK / port1_MHz_دننه_Hz );

    /* Setup the PIT interrupt. */
    AIC_DisableIT( AT91C_ID_SYS );
    AIC_ConfigureIT( AT91C_ID_SYS, AT91_C_AIC_مخکینی_ټیټ_ترین, v_پورټ_Tick_ISR );
    AIC_EnableIT( AT91C_ID_SYS );
    PIT_EnableIT();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    /* Disable interrupts first! */
    __disable_irq();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورټ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as we are leaving a critical section. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then interrupts should be
         * re-enabled. */
        إذا( ulCriticalNesting == پورټ_NO_CRITICAL_NESTING )
        {
            __enable_irq();
        }
    }
}
/*-----------------------------------------------------------*/
