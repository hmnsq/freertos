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
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>

/* Altera includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "sys/alt_irq.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sys/alt_exceptions.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "altera_avalon_timer_regs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "priv/alt_irq_table.h"

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Interrupts are enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_ESTATUS    ( ਢੇਰ_Type_t ) 0x01

ਪੂਰਨ alt_ic_isr_ਰਜਿਸਟਰ( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          ਖਾਲੀ * isr_context,
                          ਖਾਲੀ * flags );
/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Call back for the alarm function.
 */
ਖਾਲੀ v_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ * context );

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvReadGp( uint32_t * ul_ਮੁੱਲ )
{
    asm ( "stw gp, (%0)" ::"r" ( ul_ਮੁੱਲ ) );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ਢੇਰ_Type_t * px_ਚੌਖਟਾ_ਸੂਚਕ = px_ਸਿਖਰ_ਦਾ_ਢੇਰ - 1;
    ਢੇਰ_Type_t x_Global_ਸੂਚਕ;

    prvReadGp( &x_Global_ਸੂਚਕ );

    /* End of stack marker. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0xdeadbeef;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਚੌਖਟਾ_ਸੂਚਕ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = x_Global_ਸੂਚਕ;

    /* Space for R23 to R16. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 9;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_ESTATUS;

    /* Space for R15 to R5. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 12;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;

    /* Space for R3 to R1, muldiv and RA. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 5;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Start the first task. */
    asm ਅਸਥਿਰ ( " movia r2, restore_sp_from_pxCurrentTCB        \n"
                   " jmp r2                                          " );

    /* Should not get here! */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the NIOS2 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Try to register the interrupt handler. */
    ਜੇ( -EINVAL == alt_ic_isr_ਰਜਿਸਟਰ( SYS_CLK_IRQ_ਰੁਕਾਵਟ_CONTROLLER_ID, SYS_CLK_IRQ, v_ਪੋਰਟ_Sys_Tick_Handler, 0x0, 0x0 ) )
    {
        /* Failed to install the Interrupt Handler. */
        asm ( "break" );
    }
    ਨਹੀਂਤਾਂ
    {
        /* Configure SysTick to interrupt at the requested rate. */
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_ਅਧਾਰ, ALTERA_AVALON_TIMER_CONTROL_STOP_MSK );
        IOWR_ALTERA_AVALON_TIMER_PERIODL( SYS_CLK_ਅਧਾਰ, ( configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ ) & 0xFFFF );
        IOWR_ALTERA_AVALON_TIMER_PERIODH( SYS_CLK_ਅਧਾਰ, ( configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ ) >> 16 );
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_ਅਧਾਰ, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_ਸ਼ੁਰੂ_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK );
    }

    /* Clear any already pending interrupts generated by the Timer. */
    IOWR_ALTERA_AVALON_TIMER_ਸਥਿਤੀ( SYS_CLK_ਅਧਾਰ, ~ALTERA_AVALON_TIMER_ਸਥਿਤੀ_ਮੰਜ਼ਿਲ_MSK );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ * context )
{
    /* Increment the kernel tick. */
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the interrupt. */
    IOWR_ALTERA_AVALON_TIMER_ਸਥਿਤੀ( SYS_CLK_ਅਧਾਰ, ~ALTERA_AVALON_TIMER_ਸਥਿਤੀ_ਮੰਜ਼ਿਲ_MSK );
}
/*-----------------------------------------------------------*/

/** This function is a re-implementation of the Altera provided function.
 * The function is re-implemented to prevent it from enabling an interrupt
 * when it is registered. Interrupts should only be enabled after the FreeRTOS.org
 * kernel has its scheduler started so that contexts are saved and switched
 * correctly.
 */
ਪੂਰਨ alt_ic_isr_ਰਜਿਸਟਰ( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          ਖਾਲੀ * isr_context,
                          ਖਾਲੀ * flags )
{
    ਪੂਰਨ rc = -EINVAL;
    alt_irq_context status;
    ਪੂਰਨ id = irq; /* IRQ interpreted as the interrupt ID. */

    ਜੇ( id < ALT_NIRQ )
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

    ਵਾਪਸ rc;
}
/*-----------------------------------------------------------*/
