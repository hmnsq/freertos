/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT AND BSD-3-Clause
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

/*This file has been prepared for Doxygen automatic documentation generation.*/

/*! \file *********************************************************************
 *
 * \brief FreeRTOS port source for AVR32 UC3.
 *
 * - Compiler:           IAR EWAVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation (Now Microchip):
 *                                        https://www.microchip.com \n
 *                       Support and FAQ: https://www.microchip.com/support/
 *
 *****************************************************************************/

/*
 * Copyright (c) 2007, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* AVR32 UC3 includes. */
#అన్తర్భావ <avr32/io.h>
#అన్తర్భావ <intrinsics.h>
#అన్తర్భావ "gpio.h"

#ఒకవేళ configDBG
    #అన్తర్భావ "usart.h"
#అయితే_ముగింపు

#ఒకవేళ ( configTICK_USE_TC == 1 )
    #అన్తర్భావ "tc.h"
#అయితే_ముగింపు


/* Constants required to setup the task context. */
#నిర్వచించు పోర్టు_INITIAL_SR             ( ( దొంతర_Type_t ) 0x00400000 ) /* AVR32 : [M2:M0]=001 I1M=0 I0M=0, GM=0 */
#నిర్వచించు పోర్టు_INSTRUCTION_కొలత       ( ( దొంతర_Type_t ) 0 )

/* Each task maintains its own critical nesting variable. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
అస్థిర uint32_t ulCriticalNesting = 9999UL;

#ఒకవేళ ( configTICK_USE_TC == 0 )
    స్థిర శూన్య prv_కాలపట్టిక_తదుపరి_Tick( శూన్య );
#లేకపోతే
    స్థిర శూన్య prvClearTcInt( శూన్య );
#అయితే_ముగింపు

/* Setup the timer to generate the tick interrupts. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );

/*-----------------------------------------------------------*/

/*
 * Low-level initialization routine called during startup, before the main
 * function.
 */
పూర్ణాంకం __low_level_init( శూన్య )
{
    #ఒకవేళ config_కుప్ప_INIT
    #సూచన segment = "HEAP"
        పునాది_Type_t * pxMem;
    #అయితే_ముగింపు

    /* Enable exceptions. */
    ENABLE_ALL_EXCEPTIONS();

    /* Initialize interrupt handling. */
    INTC_init_interrupts();

    #ఒకవేళ config_కుప్ప_INIT
    {
        /* Initialize the heap used by malloc. */
        కొరకు( pxMem = __segment_begin( "HEAP" ); pxMem < ( పునాది_Type_t * ) __segment_end( "HEAP" ); )
        {
            *pxMem++ = 0xA5A5A5A5;
        }
    }
    #అయితే_ముగింపు

    /* Code section present if and only if the debug trace is activated. */
    #ఒకవేళ configDBG
    {
        స్థిర స్థిరరాశి gpio_map_t DBG_USART_GPIO_MAP =
        {
            { configDBG_USART_RX_PIN, configDBG_USART_RX_FUNCTION },
            { configDBG_USART_TX_PIN, configDBG_USART_TX_FUNCTION }
        };

        స్థిర స్థిరరాశి usart_options_t DBG_USART_OPTIONS =
        {
            .baudrate    = configDBG_USART_BAUDRATE,
            .charlength  = 8,
            .paritytype  = USART_NO_PARITY,
            .stopbits    = USART_1_STOPBIT,
            .channelmode = USART_సాధారణ_CHMODE
        };

        /* Initialize the USART used for the debug trace with the configured parameters. */
        బాహ్య అస్థిర avr32_usart_t * అస్థిర stdio_usart_పునాది;
        stdio_usart_పునాది = configDBG_USART;
        gpio_enable_module( DBG_USART_GPIO_MAP,
                            పరిమాణం( DBG_USART_GPIO_MAP ) / పరిమాణం( DBG_USART_GPIO_MAP[ 0 ] ) );
        usart_init_rs232( configDBG_USART, &DBG_USART_OPTIONS, configCPU_CLOCK_HZ );
    }
    #అయితే_ముగింపు /* if configDBG */

    /* Request initialization of data segments. */
    తిరిగి 1;
}
/*-----------------------------------------------------------*/

/* Added as there is no such function in FreeRTOS. */
శూన్య * pv_పోర్టు_Realloc( శూన్య * pv,
                      size_t x_Wanted_కొలత )
{
    శూన్య * pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = realloc( pv, x_Wanted_కొలత );
    }
    xTaskResumeAll();

    తిరిగి pvReturn;
}
/*-----------------------------------------------------------*/

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */

/* The preemptive scheduler is defined as "naked" as the full context is saved
 * on entry as part of the context switch. */
#సూచన shadow_registers = నిండిన_2 /* Naked. */
స్థిర శూన్య vTick( శూన్య )
{
    /* Save the context of the interrupted task. */
    పోర్టు_SAVE_CONTEXT_OS_INT();

    #ఒకవేళ ( configTICK_USE_TC == 1 )
        /* Clear the interrupt flag. */
        prvClearTcInt();
    #లేకపోతే

        /* Schedule the COUNT&COMPARE match interrupt in (configCPU_CLOCK_HZ/configTICK_RATE_HZ)
         * clock cycles from now. */
        prv_కాలపట్టిక_తదుపరి_Tick();
    #అయితే_ముగింపు

    /* Because FreeRTOS is not supposed to run with nested interrupts, put all OS
     * calls in a critical section . */
    పోర్టు_ENTER_CRITICAL();
    xTaskIncrementTick();
    పోర్టు_EXIT_CRITICAL();

    /* Restore the context of the "elected task". */
    పోర్టు_RESTORE_CONTEXT_OS_INT();
}
/*-----------------------------------------------------------*/

#సూచన shadow_registers = నిండిన_2 /* Naked. */
శూన్య SCALLYield( శూన్య )
{
    /* Save the context of the interrupted task. */
    పోర్టు_SAVE_CONTEXT_SCALL();
    vTaskSwitchContext();
    పోర్టు_RESTORE_CONTEXT_SCALL();
}
/*-----------------------------------------------------------*/

/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
#సూచన optimize = no_inline
శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Disable interrupts */
    పోర్టు_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

#సూచన optimize = no_inline
శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Enable all interrupt/exception. */
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * Initialise the stack of a task to look exactly as if a call to
 * portSAVE_CONTEXT had been called.
 *
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts, it will expect to find the function parameter in R12. */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x08080808;                    /* R8 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x09090909;                    /* R9 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x0A0A0A0A;                    /* R10 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x0B0B0B0B;                    /* R11 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) pvParameters;                  /* R12 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0xDEADBEEF;                    /* R14/LR */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) px_సంకేతం + పోర్టు_INSTRUCTION_కొలత; /* R15/PC */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) పోర్టు_INITIAL_SR;                /* SR */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0xFF0000FF;                    /* R0 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x01010101;                    /* R1 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x02020202;                    /* R2 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x03030303;                    /* R3 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x04040404;                    /* R4 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x05050505;                    /* R5 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x06060606;                    /* R6 */
    *px_శిఖరం_యొక్క_దొంతర-- = ( దొంతర_Type_t ) 0x07070707;                    /* R7 */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_NO_CRITICAL_NESTING;         /* ulCriticalNesting */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /* Start the first task. */
    పోర్టు_RESTORE_CONTEXT();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the AVR32 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* Schedule the COUNT&COMPARE match interrupt in (configCPU_CLOCK_HZ/configTICK_RATE_HZ)
 * clock cycles from now. */
#ఒకవేళ ( configTICK_USE_TC == 0 )
    స్థిర శూన్య prv_కాలపట్టిక_మొదటి_Tick( శూన్య )
    {
        uint32_t l_చక్రాలు;

        l_చక్రాలు = Get_system_రిజిస్టరు( AVR32_లెక్క );
        l_చక్రాలు += ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ );

        /* If lCycles ends up to be 0, make it 1 so that the COMPARE and exception */
        /* generation feature does not get disabled. */
        ఒకవేళ( 0 == l_చక్రాలు )
        {
            l_చక్రాలు++;
        }

        సమితి_system_రిజిస్టరు( AVR32_COMPARE, l_చక్రాలు );
    }

    #సూచన optimize = no_inline
    స్థిర శూన్య prv_కాలపట్టిక_తదుపరి_Tick( శూన్య )
    {
        uint32_t l_చక్రాలు, l_లెక్క;

        l_చక్రాలు = Get_system_రిజిస్టరు( AVR32_COMPARE );
        l_చక్రాలు += ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ );

        /* If lCycles ends up to be 0, make it 1 so that the COMPARE and exception */
        /* generation feature does not get disabled. */
        ఒకవేళ( 0 == l_చక్రాలు )
        {
            l_చక్రాలు++;
        }

        l_లెక్క = Get_system_రిజిస్టరు( AVR32_లెక్క );

        ఒకవేళ( l_చక్రాలు < l_లెక్క )
        { /* We missed a tick, recover for the next. */
            l_చక్రాలు += ( configCPU_CLOCK_HZ / config_TICK_రేటు_HZ );
        }

        సమితి_system_రిజిస్టరు( AVR32_COMPARE, l_చక్రాలు );
    }
#లేకపోతే /* if ( configTICK_USE_TC == 0 ) */
    #సూచన optimize = no_inline
    స్థిర శూన్య prvClearTcInt( శూన్య )
    {
        AVR32_TC.channel[ configTICK_TC_CHANNEL ].sr;
    }
#అయితే_ముగింపు /* if ( configTICK_USE_TC == 0 ) */
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    #ఒకవేళ ( configTICK_USE_TC == 1 )
        అస్థిర avr32_tc_t * tc = &AVR32_TC;

        /* Options for waveform generation. */
        tc_waveform_opt_t waveform_opt =
        {
            .channel = configTICK_TC_CHANNEL,              /* Channel selection. */

            .bswtrg  = TC_EVT_EFFECT_NOOP,                 /* Software trigger effect on TIOB. */
            .beevt   = TC_EVT_EFFECT_NOOP,                 /* External event effect on TIOB. */
            .bcpc    = TC_EVT_EFFECT_NOOP,                 /* RC compare effect on TIOB. */
            .bcpb    = TC_EVT_EFFECT_NOOP,                 /* RB compare effect on TIOB. */

            .aswtrg  = TC_EVT_EFFECT_NOOP,                 /* Software trigger effect on TIOA. */
            .aeevt   = TC_EVT_EFFECT_NOOP,                 /* External event effect on TIOA. */
            .acpc    = TC_EVT_EFFECT_NOOP,                 /* RC compare effect on TIOA: toggle. */
            .acpa    = TC_EVT_EFFECT_NOOP,                 /* RA compare effect on TIOA: toggle (other possibilities are none, set and clear). */

            .wavsel  = TC_WAVEFORM_SEL_పైకి_బహుళకం_RC_TRIGGER, /* Waveform selection: Up mode without automatic trigger on RC compare. */
            .enetrg  = FALSE,                              /* External event trigger enable. */
            .eevt    = 0,                                  /* External event selection. */
            .eevtedg = TC_SEL_NO_అంచు,                     /* External event edge selection. */
            .cpcdis  = FALSE,                              /* Counter disable when RC compare. */
            .cpcstop = FALSE,                              /* Counter clock stopped with RC compare. */

            .వ్యవధి_2   = FALSE,                              /* Burst signal selection. */
            .clki    = FALSE,                              /* Clock inversion. */
            .tcclks  = TC_CLOCK_ఆధారం_TC2                 /* Internal source clock 2. */
        };

        tc_అంతరాయం_t tc_అంతరాయం =
        {
            .etrgs = 0,
            .ldrbs = 0,
            .ldras = 0,
            .cpcs  = 1,
            .cpbs  = 0,
            .cpas  = 0,
            .lovrs = 0,
            .covfs = 0,
        };
    #అయితే_ముగింపు /* if ( configTICK_USE_TC == 1 ) */

    /* Disable all interrupt/exception. */
    పోర్టు_DISABLE_INTERRUPTS();

    /* Register the compare interrupt handler to the interrupt controller and
     * enable the compare interrupt. */

    #ఒకవేళ ( configTICK_USE_TC == 1 )
    {
        INTC_రిజిస్టరు_అంతరాయం( ( __int_handler ) & vTick, configTICK_TC_IRQ, INT0 );

        /* Initialize the timer/counter. */
        tc_init_waveform( tc, &waveform_opt );

        /* Set the compare triggers.
         * Remember TC counter is 16-bits, so counting second is not possible!
         * That's why we configure it to count ms. */
        tc_write_rc( tc, configTICK_TC_CHANNEL, ( configPBA_CLOCK_HZ / 4 ) / config_TICK_రేటు_HZ );

        tc_configure_interrupts( tc, configTICK_TC_CHANNEL, &tc_అంతరాయం );

        /* Start the timer/counter. */
        tc_ప్రారంభం( tc, configTICK_TC_CHANNEL );
    }
    #లేకపోతే /* if ( configTICK_USE_TC == 1 ) */
    {
        INTC_రిజిస్టరు_అంతరాయం( ( __int_handler ) & vTick, AVR32_CORE_COMPARE_IRQ, INT0 );
        prv_కాలపట్టిక_మొదటి_Tick();
    }
    #అయితే_ముగింపు /* if ( configTICK_USE_TC == 1 ) */
}
