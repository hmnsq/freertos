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
* Implementation of functions defined in portable.h for the NIOS2 port.
*----------------------------------------------------------*/

/* Standard Includes. */
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <errno.h>

/* Altera includes. */
#ଅନ୍ତର୍ଭାଵ "sys/alt_irq.h"
#ଅନ୍ତର୍ଭାଵ "sys/alt_exceptions.h"
#ଅନ୍ତର୍ଭାଵ "altera_avalon_timer_regs.h"
#ଅନ୍ତର୍ଭାଵ "priv/alt_irq_table.h"

/* Scheduler includes. */
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

/* Interrupts are enabled. */
#define portINITIAL_ESTATUS    ( ଗଦା_Type_t ) 0x01

ପୂର୍ଣ୍ଣସଂଖ୍ୟା _alt_ic_isr_register( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          ଶୂନ୍ୟ * isr_context,
                          ଶୂନ୍ୟ * flags );
/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );

/*
 * Call back for the alarm function.
 */
ଶୂନ୍ୟ vPortSysTickHandler( ଶୂନ୍ୟ * context );

/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvReadGp( uint32_t * ul_ମୂଲ୍ୟ )
{
    asm ( "stw gp, (%0)" ::"r" ( ul_ମୂଲ୍ୟ ) );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    ଗଦା_Type_t * pxFramePointer = px_ଶୀର୍ଷ_Of_ଗଦା - 1;
    ଗଦା_Type_t xGlobalPointer;

    prvReadGp( &xGlobalPointer );

    /* End of stack marker. */
    *px_ଶୀର୍ଷ_Of_ଗଦା = 0xdeadbeef;
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pxFramePointer;
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    *px_ଶୀର୍ଷ_Of_ଗଦା = xGlobalPointer;

    /* Space for R23 to R16. */
    px_ଶୀର୍ଷ_Of_ଗଦା -= 9;

    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pxCode;
    px_ଶୀର୍ଷ_Of_ଗଦା--;

    *px_ଶୀର୍ଷ_Of_ଗଦା = portINITIAL_ESTATUS;

    /* Space for R15 to R5. */
    px_ଶୀର୍ଷ_Of_ଗଦା -= 12;

    *px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t ) pvParameters;

    /* Space for R3 to R1, muldiv and RA. */
    px_ଶୀର୍ଷ_Of_ଗଦା -= 5;

    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    asm ଅସ୍ଥିର ( " movia r2, restore_sp_from_pxCurrentTCB        \n"
                   " jmp r2                                          " );

    /* Should not get here! */
    ଫେରନ୍ତୁ 0;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    /* It is unlikely that the NIOS2 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
    /* Try to register the interrupt handler. */
    ଯଦି( -EINVAL == _alt_ic_isr_register( SYS_CLK_IRQ_INTERRUPT_CONTROLLER_ID, SYS_CLK_IRQ, vPortSysTickHandler, 0x0, 0x0 ) )
    {
        /* Failed to install the Interrupt Handler. */
        asm ( "break" );
    }
    ଅନ୍ୟଥା
    {
        /* Configure SysTick to interrupt at the requested rate. */
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_BASE, ALTERA_AVALON_TIMER_CONTROL_STOP_MSK );
        IOWR_ALTERA_AVALON_TIMER_PERIODL( SYS_CLK_BASE, ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) & 0xFFFF );
        IOWR_ALTERA_AVALON_TIMER_PERIODH( SYS_CLK_BASE, ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) >> 16 );
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_BASE, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK );
    }

    /* Clear any already pending interrupts generated by the Timer. */
    IOWR_ALTERA_AVALON_TIMER_STATUS( SYS_CLK_BASE, ~ALTERA_AVALON_TIMER_STATUS_TO_MSK );
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortSysTickHandler( ଶୂନ୍ୟ * context )
{
    /* Increment the kernel tick. */
    ଯଦି( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the interrupt. */
    IOWR_ALTERA_AVALON_TIMER_STATUS( SYS_CLK_BASE, ~ALTERA_AVALON_TIMER_STATUS_TO_MSK );
}
/*-----------------------------------------------------------*/

/** This function is a re-implementation of the Altera provided function.
 * The function is re-implemented to prevent it from enabling an interrupt
 * when it is registered. Interrupts should only be enabled after the FreeRTOS.org
 * kernel has its scheduler started so that contexts are saved and switched
 * correctly.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା _alt_ic_isr_register( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          ଶୂନ୍ୟ * isr_context,
                          ଶୂନ୍ୟ * flags )
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rc = -EINVAL;
    alt_irq_context status;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା id = irq; /* IRQ interpreted as the interrupt ID. */

    ଯଦି( id < ALT_NIRQ )
    {
        /*
         * interrupts are disabled while the handler tables are updated to ensure
         * that an interrupt doesn't occur while the tables are in an inconsistent
         * state.
         */

        status = alt_irq_disable_all();

        alt_irq[ id ].handler = isr;
        alt_irq[ id ].context = isr_context;

        rc = ( isr ) ? alt_ic_irq_enable( ic_id, id ) : alt_ic_irq_disable( ic_id, id );

        /* alt_irq_enable_all(status); This line is removed to prevent the interrupt from being immediately enabled. */
    }

    ଫେରନ୍ତୁ rc;
}
/*-----------------------------------------------------------*/
