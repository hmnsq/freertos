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
#شامل <string.h>
#شامل <errno.h>

/* Altera includes. */
#شامل "sys/alt_irq.h"
#شامل "sys/alt_exceptions.h"
#شامل "altera_avalon_timer_regs.h"
#شامل "priv/alt_irq_table.h"

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* Interrupts are enabled. */
#تعریف_کرو پورٹ_INITIAL_ESTATUS    ( ڈھیر_Type_t ) 0x01

صحیح alt_ic_isr_رجسٹر( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          خالی * isr_context,
                          خالی * flags );
/*-----------------------------------------------------------*/

/*
 * Setup the timer to generate the tick interrupts.
 */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*
 * Call back for the alarm function.
 */
خالی v_پورٹ_Sys_Tick_Handler( خالی * context );

/*-----------------------------------------------------------*/

ساکن خالی prvReadGp( uint32_t * ul_قدر )
{
    asm ( "stw gp, (%0)" ::"r" ( ul_قدر ) );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    ڈھیر_Type_t * px_چوکھٹا_اشارہ_گر = px_چوٹی_کا_ڈھیر - 1;
    ڈھیر_Type_t x_Global_اشارہ_گر;

    prvReadGp( &x_Global_اشارہ_گر );

    /* End of stack marker. */
    *px_چوٹی_کا_ڈھیر = 0xdeadbeef;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_چوکھٹا_اشارہ_گر;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = x_Global_اشارہ_گر;

    /* Space for R23 to R16. */
    px_چوٹی_کا_ڈھیر -= 9;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;
    px_چوٹی_کا_ڈھیر--;

    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_ESTATUS;

    /* Space for R15 to R5. */
    px_چوٹی_کا_ڈھیر -= 12;

    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;

    /* Space for R3 to R1, muldiv and RA. */
    px_چوٹی_کا_ڈھیر -= 5;

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخلت();

    /* Start the first task. */
    asm متلون ( " movia r2, restore_sp_from_pxCurrentTCB        \n"
                   " jmp r2                                          " );

    /* Should not get here! */
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the NIOS2 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
خالی prv_تیاری_Timer_مداخلت( خالی )
{
    /* Try to register the interrupt handler. */
    اگر( -EINVAL == alt_ic_isr_رجسٹر( SYS_CLK_IRQ_مداخلت_CONTROLLER_ID, SYS_CLK_IRQ, v_پورٹ_Sys_Tick_Handler, 0x0, 0x0 ) )
    {
        /* Failed to install the Interrupt Handler. */
        asm ( "break" );
    }
    ورنہ
    {
        /* Configure SysTick to interrupt at the requested rate. */
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_بنیاد, ALTERA_AVALON_TIMER_CONTROL_STOP_MSK );
        IOWR_ALTERA_AVALON_TIMER_PERIODL( SYS_CLK_بنیاد, ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) & 0xFFFF );
        IOWR_ALTERA_AVALON_TIMER_PERIODH( SYS_CLK_بنیاد, ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ ) >> 16 );
        IOWR_ALTERA_AVALON_TIMER_CONTROL( SYS_CLK_بنیاد, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_آغاز_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK );
    }

    /* Clear any already pending interrupts generated by the Timer. */
    IOWR_ALTERA_AVALON_TIMER_حالت( SYS_CLK_بنیاد, ~ALTERA_AVALON_TIMER_حالت_مقصد_MSK );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Sys_Tick_Handler( خالی * context )
{
    /* Increment the kernel tick. */
    اگر( xTaskIncrementTick() != pdFALSE )
    {
        vTaskSwitchContext();
    }

    /* Clear the interrupt. */
    IOWR_ALTERA_AVALON_TIMER_حالت( SYS_CLK_بنیاد, ~ALTERA_AVALON_TIMER_حالت_مقصد_MSK );
}
/*-----------------------------------------------------------*/

/** This function is a re-implementation of the Altera provided function.
 * The function is re-implemented to prevent it from enabling an interrupt
 * when it is registered. Interrupts should only be enabled after the FreeRTOS.org
 * kernel has its scheduler started so that contexts are saved and switched
 * correctly.
 */
صحیح alt_ic_isr_رجسٹر( alt_u32 ic_id,
                          alt_u32 irq,
                          alt_isr_func isr,
                          خالی * isr_context,
                          خالی * flags )
{
    صحیح rc = -EINVAL;
    alt_irq_context status;
    صحیح id = irq; /* IRQ interpreted as the interrupt ID. */

    اگر( id < ALT_NIRQ )
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

    واپس rc;
}
/*-----------------------------------------------------------*/
