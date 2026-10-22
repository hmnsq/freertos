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
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <errno.h>

/* Altera includes. */
#ಅನ್ತರ್ಭಾವ "sys/alt_irq.h"
#ಅನ್ತರ್ಭಾವ "sys/alt_exceptions.h"
#ಅನ್ತರ್ಭಾವ "altera_avalon_timer_regs.h"
#ಅನ್ತರ್ಭಾವ "priv/alt_irq_table.h"

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Interrupts are enabled. */
#define portINITIAL_ESTATUS    ( ರಾಶಿ_Type_t ) 0x01

ಪೂರ್ಣಾಙ್ಕ _alt_ic_isr_register( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          ಶೂನ್ಯ * isr_context,
                          ಶೂನ್ಯ * flags );
/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ );

/*
 * Call back for the alarm function.
 */
ಶೂನ್ಯ vPortSysTickHandler( ಶೂನ್ಯ * context );

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvReadGp( uint32_t * ul_ಮೌಲ್ಯ )
{
    asm ( "stw gp, (%0)" ::"r" ( ul_ಮೌಲ್ಯ ) );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    ರಾಶಿ_Type_t * pxFramePointer = px_ತುದಿ_Of_ರಾಶಿ - 1;
    ರಾಶಿ_Type_t xGlobalPointer;

    prvReadGp( &xGlobalPointer );

    /* End of stack marker. */
    *px_ತುದಿ_Of_ರಾಶಿ = 0xdeadbeef;
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxFramePointer;
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = xGlobalPointer;

    /* Space for R23 to R16. */
    px_ತುದಿ_Of_ರಾಶಿ -= 9;

    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxCode;
    px_ತುದಿ_Of_ರಾಶಿ--;

    *px_ತುದಿ_Of_ರಾಶಿ = portINITIAL_ESTATUS;

    /* Space for R15 to R5. */
    px_ತುದಿ_Of_ರಾಶಿ -= 12;

    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;

    /* Space for R3 to R1, muldiv and RA. */
    px_ತುದಿ_Of_ರಾಶಿ -= 5;

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prvSetupTimerInterrupt();

    /* Start the first task. */
    asm ಚಞ್ಚಲ ( " movia r2, restore_sp_from_pxCurrentTCB        \n"
                   " jmp r2                                          " );

    /* Should not get here! */
    ಪ್ರತ್ಯಾಗಮ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the NIOS2 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    /* Try to register the interrupt handler. */
    ಯದಿ( -EINVAL == _alt_ic_isr_register( SYS_CLK_IRQ_INTERRUPT_CONTROLLER_ID, SYS_CLK_IRQ, vPortSysTickHandler, 0x0, 0x0 ) )
    {
        /* Failed to install the Interrupt Handler. */
        asm ( "break" );
    }
    ಅನ್ಯಥಾ
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

ಶೂನ್ಯ vPortSysTickHandler( ಶೂನ್ಯ * context )
{
    /* Increment the kernel tick. */
    ಯದಿ( xTaskIncrementTick() != pdFALSE )
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
ಪೂರ್ಣಾಙ್ಕ _alt_ic_isr_register( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          ಶೂನ್ಯ * isr_context,
                          ಶೂನ್ಯ * flags )
{
    ಪೂರ್ಣಾಙ್ಕ rc = -EINVAL;
    alt_irq_context status;
    ಪೂರ್ಣಾಙ್ಕ id = irq; /* IRQ interpreted as the interrupt ID. */

    ಯದಿ( id < ALT_NIRQ )
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

    ಪ್ರತ್ಯಾಗಮ rc;
}
/*-----------------------------------------------------------*/
