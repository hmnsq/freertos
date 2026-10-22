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
#ضمن <string.h>
#ضمن <errno.h>

/* Altera includes. */
#ضمن "sys/alt_irq.h"
#ضمن "sys/alt_exceptions.h"
#ضمن "altera_avalon_timer_regs.h"
#ضمن "priv/alt_irq_table.h"

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Interrupts are enabled. */
#define portINITIAL_ESTATUS    ( دۆۋە_Type_t ) 0x01

صحيح _alt_ic_isr_register( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          فراغ * isr_context,
                          فراغ * flags );
/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
ساكن فراغ prvSetupTimerInterrupt( فراغ );

/*
 * Call back for the alarm function.
 */
فراغ vPortSysTickHandler( فراغ * context );

/*-----------------------------------------------------------*/

ساكن فراغ prvReadGp( uint32_t * ul_قىممەت )
{
    asm ( "stw gp, (%0)" ::"r" ( ul_قىممەت ) );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
دۆۋە_Type_t * px_Port_Initialise_دۆۋە( دۆۋە_Type_t * px_چوققا_Of_دۆۋە,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    دۆۋە_Type_t * pxFramePointer = px_چوققا_Of_دۆۋە - 1;
    دۆۋە_Type_t xGlobalPointer;

    prvReadGp( &xGlobalPointer );

    /* End of stack marker. */
    *px_چوققا_Of_دۆۋە = 0xdeadbeef;
    px_چوققا_Of_دۆۋە--;

    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) pxFramePointer;
    px_چوققا_Of_دۆۋە--;

    *px_چوققا_Of_دۆۋە = xGlobalPointer;

    /* Space for R23 to R16. */
    px_چوققا_Of_دۆۋە -= 9;

    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) pxCode;
    px_چوققا_Of_دۆۋە--;

    *px_چوققا_Of_دۆۋە = portINITIAL_ESTATUS;

    /* Space for R15 to R5. */
    px_چوققا_Of_دۆۋە -= 12;

    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) pvParameters;

    /* Space for R3 to R1, muldiv and RA. */
    px_چوققا_Of_دۆۋە -= 5;

    أرجع px_چوققا_Of_دۆۋە;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    asm متطاير ( " movia r2, restore_sp_from_pxCurrentTCB        \n"
                   " jmp r2                                          " );

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    /* It is unlikely that the NIOS2 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prvSetupTimerInterrupt( فراغ )
{
    /* Try to register the interrupt handler. */
    إذا( -EINVAL == _alt_ic_isr_register( SYS_CLK_IRQ_INTERRUPT_CONTROLLER_ID, SYS_CLK_IRQ, vPortSysTickHandler, 0x0, 0x0 ) )
    {
        /* Failed to install the Interrupt Handler. */
        asm ( "break" );
    }
    وإلا
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

فراغ vPortSysTickHandler( فراغ * context )
{
    /* Increment the kernel tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
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
صحيح _alt_ic_isr_register( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          فراغ * isr_context,
                          فراغ * flags )
{
    صحيح rc = -EINVAL;
    alt_irq_context status;
    صحيح id = irq; /* IRQ interpreted as the interrupt ID. */

    إذا( id < ALT_NIRQ )
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

    أرجع rc;
}
/*-----------------------------------------------------------*/
