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
 * - Compiler:           GNU GCC for AVR32
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

/* Standard includes. */
#شامل <sys/cpu.h>
#شامل <sys/usart.h>
#شامل <malloc.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* AVR32 UC3 includes. */
#شامل <avr32/io.h>
#شامل "gpio.h"
#اگر ( configTICK_USE_TC == 1 )
    #شامل "tc.h"
#اگر_ختم


/* Constants required to setup the task context. */
#تعریف_کرو پورٹ_INITIAL_SR             ( ( ڈھیر_Type_t ) 0x00400000 ) /* AVR32 : [M2:M0]=001 I1M=0 I0M=0, GM=0 */
#تعریف_کرو پورٹ_INSTRUCTION_سائز       ( ( ڈھیر_Type_t ) 0 )

/* Each task maintains its own critical nesting variable. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
متلون uint32_t ulCriticalNesting = 9999UL;

#اگر ( configTICK_USE_TC == 0 )
    ساکن خالی prv_جدول_وقت_اگلا_Tick( خالی );
#ورنہ
    ساکن خالی prvClearTcInt( خالی );
#اگر_ختم

/* Setup the timer to generate the tick interrupts. */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );

/*-----------------------------------------------------------*/

/*
 * Low-level initialization routine called during startup, before the main
 * function.
 * This version comes in replacement to the default one provided by Newlib.
 * Newlib's _init_startup only calls init_exceptions, but Newlib's exception
 * vectors are not compatible with the SCALL management in the current FreeRTOS
 * port. More low-level initializations are besides added here.
 */
خالی _init_startup( خالی )
{
    /* Import the Exception Vector Base Address. */
    خارجی خالی _evba;

    #اگر config_ڈھیر_INIT
        خارجی خالی __heap_start__;
        خارجی خالی __heap_end__;
        بنیاد_Type_t * pxMem;
    #اگر_ختم

    /* Load the Exception Vector Base Address in the corresponding system register. */
    سیٹ_system_رجسٹر( AVR32_EVBA, ( صحیح ) &_evba );

    /* Enable exceptions. */
    ENABLE_ALL_EXCEPTIONS();

    /* Initialize interrupt handling. */
    INTC_init_interrupts();

    #اگر config_ڈھیر_INIT
        /* Initialize the heap used by malloc. */
        برائے( pxMem = &__heap_start__; pxMem < ( بنیاد_Type_t * ) &__heap_end__; )
        {
            *pxMem++ = 0xA5A5A5A5;
        }
    #اگر_ختم

    /* Give the used CPU clock frequency to Newlib, so it can work properly. */
    سیٹ_cpu_hz( configCPU_CLOCK_HZ );

    /* Code section present if and only if the debug trace is activated. */
    #اگر configDBG
    {
        ساکن ثابت gpio_map_t DBG_USART_GPIO_MAP =
        {
            { configDBG_USART_RX_PIN, configDBG_USART_RX_FUNCTION },
            { configDBG_USART_TX_PIN, configDBG_USART_TX_FUNCTION }
        };

        /* Initialize the USART used for the debug trace with the configured parameters. */
        سیٹ_usart_بنیاد( ( خالی * ) configDBG_USART );
        gpio_enable_module( DBG_USART_GPIO_MAP,
                            حجم( DBG_USART_GPIO_MAP ) / حجم( DBG_USART_GPIO_MAP[ 0 ] ) );
        usart_init( configDBG_USART_BAUDRATE );
    }
    #اگر_ختم /* if configDBG */
}
/*-----------------------------------------------------------*/

/*
 * malloc, realloc and free are meant to be called through respectively
 * pvPortMalloc, pvPortRealloc and vPortFree.
 * The latter functions call the former ones from within sections where tasks
 * are suspended, so the latter functions are task-safe. __malloc_lock and
 * __malloc_unlock use the same mechanism to also keep the former functions
 * task-safe as they may be called directly from Newlib's functions.
 * However, all these functions are interrupt-unsafe and SHALL THEREFORE NOT BE
 * CALLED FROM WITHIN AN INTERRUPT, because __malloc_lock and __malloc_unlock do
 * not call portENTER_CRITICAL and portEXIT_CRITICAL in order not to disable
 * interrupts during memory allocation management as this may be a very time-
 * consuming process.
 */

/*
 * Lock routine called by Newlib on malloc / realloc / free entry to guarantee a
 * safe section as memory allocation management uses global data.
 * See the aforementioned details.
 */
خالی __malloc_lock( ساخت _reent * ptr )
{
    vTaskSuspendAll();
}

/*
 * Unlock routine called by Newlib on malloc / realloc / free exit to guarantee
 * a safe section as memory allocation management uses global data.
 * See the aforementioned details.
 */
خالی __malloc_unlock( ساخت _reent * ptr )
{
    xTaskResumeAll();
}
/*-----------------------------------------------------------*/

/* Added as there is no such function in FreeRTOS. */
خالی * pv_پورٹ_Realloc( خالی * pv,
                      size_t x_Wanted_سائز )
{
    خالی * pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = realloc( pv, x_Wanted_سائز );
    }
    xTaskResumeAll();

    واپس pvReturn;
}
/*-----------------------------------------------------------*/

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */

/* The preemptive scheduler is defined as "naked" as the full context is saved
 * on entry as part of the context switch. */
__attribute__( ( __naked__ ) ) ساکن خالی vTick( خالی )
{
    /* Save the context of the interrupted task. */
    پورٹ_SAVE_CONTEXT_OS_INT();

    #اگر ( configTICK_USE_TC == 1 )
        /* Clear the interrupt flag. */
        prvClearTcInt();
    #ورنہ

        /* Schedule the COUNT&COMPARE match interrupt in (configCPU_CLOCK_HZ/configTICK_RATE_HZ)
         * clock cycles from now. */
        prv_جدول_وقت_اگلا_Tick();
    #اگر_ختم

    /* Because FreeRTOS is not supposed to run with nested interrupts, put all OS
     * calls in a critical section . */
    پورٹ_ENTER_CRITICAL();
    xTaskIncrementTick();
    پورٹ_EXIT_CRITICAL();

    /* Restore the context of the "elected task". */
    پورٹ_RESTORE_CONTEXT_OS_INT();
}
/*-----------------------------------------------------------*/

__attribute__( ( __naked__ ) ) خالی SCALLYield( خالی )
{
    /* Save the context of the interrupted task. */
    پورٹ_SAVE_CONTEXT_SCALL();
    vTaskSwitchContext();
    پورٹ_RESTORE_CONTEXT_SCALL();
}
/*-----------------------------------------------------------*/

/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
__attribute__( ( __noinline__ ) ) خالی v_پورٹ_Enter_Critical( خالی )
{
    /* Disable interrupts */
    پورٹ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__attribute__( ( __noinline__ ) ) خالی v_پورٹ_Exit_Critical( خالی )
{
    اگر( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            /* Enable all interrupt/exception. */
            پورٹ_ENABLE_INTERRUPTS();
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
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts, it will expect to find the function parameter in R12. */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x08080808;                    /* R8 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x09090909;                    /* R9 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x0A0A0A0A;                    /* R10 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x0B0B0B0B;                    /* R11 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) pvParameters;                  /* R12 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0xDEADBEEF;                    /* R14/LR */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) px_رمز + پورٹ_INSTRUCTION_سائز; /* R15/PC */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) پورٹ_INITIAL_SR;                /* SR */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0xFF0000FF;                    /* R0 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x01010101;                    /* R1 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x02020202;                    /* R2 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x03030303;                    /* R3 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x04040404;                    /* R4 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x05050505;                    /* R5 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x06060606;                    /* R6 */
    *px_چوٹی_کا_ڈھیر-- = ( ڈھیر_Type_t ) 0x07070707;                    /* R7 */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_NO_CRITICAL_NESTING;         /* ulCriticalNesting */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تیاری_Timer_مداخلت();

    /* Start the first task. */
    پورٹ_RESTORE_CONTEXT();

    /* Should not get here! */
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the AVR32 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* Schedule the COUNT&COMPARE match interrupt in (configCPU_CLOCK_HZ/configTICK_RATE_HZ)
 * clock cycles from now. */
#اگر ( configTICK_USE_TC == 0 )
    ساکن خالی prv_جدول_وقت_پہلا_Tick( خالی )
    {
        uint32_t l_ادوار;

        l_ادوار = Get_system_رجسٹر( AVR32_گنتی );
        l_ادوار += ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );

        /* If lCycles ends up to be 0, make it 1 so that the COMPARE and exception */
        /* generation feature does not get disabled. */
        اگر( 0 == l_ادوار )
        {
            l_ادوار++;
        }

        سیٹ_system_رجسٹر( AVR32_COMPARE, l_ادوار );
    }

    __attribute__( ( __noinline__ ) ) ساکن خالی prv_جدول_وقت_اگلا_Tick( خالی )
    {
        uint32_t l_ادوار, l_گنتی;

        l_ادوار = Get_system_رجسٹر( AVR32_COMPARE );
        l_ادوار += ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );

        /* If lCycles ends up to be 0, make it 1 so that the COMPARE and exception */
        /* generation feature does not get disabled. */
        اگر( 0 == l_ادوار )
        {
            l_ادوار++;
        }

        l_گنتی = Get_system_رجسٹر( AVR32_گنتی );

        اگر( l_ادوار < l_گنتی )
        { /* We missed a tick, recover for the next. */
            l_ادوار += ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );
        }

        سیٹ_system_رجسٹر( AVR32_COMPARE, l_ادوار );
    }
#ورنہ /* if ( configTICK_USE_TC == 0 ) */
    __attribute__( ( __noinline__ ) ) ساکن خالی prvClearTcInt( خالی )
    {
        AVR32_TC.channel[ configTICK_TC_CHANNEL ].sr;
    }
#اگر_ختم /* if ( configTICK_USE_TC == 0 ) */
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساکن خالی prv_تیاری_Timer_مداخلت( خالی )
{
    #اگر ( configTICK_USE_TC == 1 )
        متلون avr32_tc_t * tc = &AVR32_TC;

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

            .wavsel  = TC_WAVEFORM_SEL_اوپر_منوال_RC_TRIGGER, /* Waveform selection: Up mode without automatic trigger on RC compare. */
            .enetrg  = FALSE,                              /* External event trigger enable. */
            .eevt    = 0,                                  /* External event selection. */
            .eevtedg = TC_SEL_NO_کنارہ,                     /* External event edge selection. */
            .cpcdis  = FALSE,                              /* Counter disable when RC compare. */
            .cpcstop = FALSE,                              /* Counter clock stopped with RC compare. */

            .مدت_2   = FALSE,                              /* Burst signal selection. */
            .clki    = FALSE,                              /* Clock inversion. */
            .tcclks  = TC_CLOCK_ماخذ_TC2                 /* Internal source clock 2. */
        };

        tc_مداخلت_t tc_مداخلت =
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
    #اگر_ختم /* if ( configTICK_USE_TC == 1 ) */

    /* Disable all interrupt/exception. */
    پورٹ_DISABLE_INTERRUPTS();

    /* Register the compare interrupt handler to the interrupt controller and
     * enable the compare interrupt. */

    #اگر ( configTICK_USE_TC == 1 )
    {
        INTC_رجسٹر_مداخلت( &vTick, configTICK_TC_IRQ, INT0 );

        /* Initialize the timer/counter. */
        tc_init_waveform( tc, &waveform_opt );

        /* Set the compare triggers.
         * Remember TC counter is 16-bits, so counting second is not possible!
         * That's why we configure it to count ms. */
        tc_write_rc( tc, configTICK_TC_CHANNEL, ( configPBA_CLOCK_HZ / 4 ) / config_TICK_شرح_HZ );

        tc_configure_interrupts( tc, configTICK_TC_CHANNEL, &tc_مداخلت );

        /* Start the timer/counter. */
        tc_آغاز( tc, configTICK_TC_CHANNEL );
    }
    #ورنہ /* if ( configTICK_USE_TC == 1 ) */
    {
        INTC_رجسٹر_مداخلت( &vTick, AVR32_CORE_COMPARE_IRQ, INT0 );
        prv_جدول_وقت_پہلا_Tick();
    }
    #اگر_ختم /* if ( configTICK_USE_TC == 1 ) */
}
