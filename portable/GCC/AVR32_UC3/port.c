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
#ضمن <sys/cpu.h>
#ضمن <sys/usart.h>
#ضمن <malloc.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* AVR32 UC3 includes. */
#ضمن <avr32/io.h>
#ضمن "gpio.h"
#إذا ( configTICK_USE_TC == 1 )
    #ضمن "tc.h"
#جيڪڏهن_پورو


/* Constants required to setup the task context. */
#وصف_ڪريو پورٽ_INITIAL_SR             ( ( ڍير_Type_t ) 0x00400000 ) /* AVR32 : [M2:M0]=001 I1M=0 I0M=0, GM=0 */
#وصف_ڪريو پورٽ_INSTRUCTION_سائيز       ( ( ڍير_Type_t ) 0 )

/* Each task maintains its own critical nesting variable. */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
متطاير uint32_t ulCriticalNesting = 9999UL;

#إذا ( configTICK_USE_TC == 0 )
    ساكن فراغ prv_وقت_جدول_ايندڙ_Tick( فراغ );
#وإلا
    ساكن فراغ prvClearTcInt( فراغ );
#جيڪڏهن_پورو

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );

/*-----------------------------------------------------------*/

/*
 * Low-level initialization routine called during startup, before the main
 * function.
 * This version comes in replacement to the default one provided by Newlib.
 * Newlib's _init_startup only calls init_exceptions, but Newlib's exception
 * vectors are not compatible with the SCALL management in the current FreeRTOS
 * port. More low-level initializations are besides added here.
 */
فراغ _init_startup( فراغ )
{
    /* Import the Exception Vector Base Address. */
    خارجي فراغ _evba;

    #إذا config_ڍير_INIT
        خارجي فراغ __heap_start__;
        خارجي فراغ __heap_end__;
        بنياد_Type_t * pxMem;
    #جيڪڏهن_پورو

    /* Load the Exception Vector Base Address in the corresponding system register. */
    سيٽ_system_رجسٽر( AVR32_EVBA, ( صحيح ) &_evba );

    /* Enable exceptions. */
    ENABLE_ALL_EXCEPTIONS();

    /* Initialize interrupt handling. */
    INTC_init_interrupts();

    #إذا config_ڍير_INIT
        /* Initialize the heap used by malloc. */
        لكل( pxMem = &__heap_start__; pxMem < ( بنياد_Type_t * ) &__heap_end__; )
        {
            *pxMem++ = 0xA5A5A5A5;
        }
    #جيڪڏهن_پورو

    /* Give the used CPU clock frequency to Newlib, so it can work properly. */
    سيٽ_cpu_hz( configCPU_CLOCK_HZ );

    /* Code section present if and only if the debug trace is activated. */
    #إذا configDBG
    {
        ساكن ثابت gpio_map_t DBG_USART_GPIO_MAP =
        {
            { configDBG_USART_RX_PIN, configDBG_USART_RX_FUNCTION },
            { configDBG_USART_TX_PIN, configDBG_USART_TX_FUNCTION }
        };

        /* Initialize the USART used for the debug trace with the configured parameters. */
        سيٽ_usart_بنياد( ( فراغ * ) configDBG_USART );
        gpio_enable_module( DBG_USART_GPIO_MAP,
                            حجم( DBG_USART_GPIO_MAP ) / حجم( DBG_USART_GPIO_MAP[ 0 ] ) );
        usart_init( configDBG_USART_BAUDRATE );
    }
    #جيڪڏهن_پورو /* if configDBG */
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
فراغ __malloc_lock( بنية _reent * ptr )
{
    vTaskSuspendAll();
}

/*
 * Unlock routine called by Newlib on malloc / realloc / free exit to guarantee
 * a safe section as memory allocation management uses global data.
 * See the aforementioned details.
 */
فراغ __malloc_unlock( بنية _reent * ptr )
{
    xTaskResumeAll();
}
/*-----------------------------------------------------------*/

/* Added as there is no such function in FreeRTOS. */
فراغ * pv_پورٽ_Realloc( فراغ * pv,
                      size_t x_Wanted_سائيز )
{
    فراغ * pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = realloc( pv, x_Wanted_سائيز );
    }
    xTaskResumeAll();

    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

/* The cooperative scheduler requires a normal IRQ service routine to
 * simply increment the system tick. */

/* The preemptive scheduler is defined as "naked" as the full context is saved
 * on entry as part of the context switch. */
__attribute__( ( __naked__ ) ) ساكن فراغ vTick( فراغ )
{
    /* Save the context of the interrupted task. */
    پورٽ_SAVE_CONTEXT_OS_INT();

    #إذا ( configTICK_USE_TC == 1 )
        /* Clear the interrupt flag. */
        prvClearTcInt();
    #وإلا

        /* Schedule the COUNT&COMPARE match interrupt in (configCPU_CLOCK_HZ/configTICK_RATE_HZ)
         * clock cycles from now. */
        prv_وقت_جدول_ايندڙ_Tick();
    #جيڪڏهن_پورو

    /* Because FreeRTOS is not supposed to run with nested interrupts, put all OS
     * calls in a critical section . */
    پورٽ_ENTER_CRITICAL();
    xTaskIncrementTick();
    پورٽ_EXIT_CRITICAL();

    /* Restore the context of the "elected task". */
    پورٽ_RESTORE_CONTEXT_OS_INT();
}
/*-----------------------------------------------------------*/

__attribute__( ( __naked__ ) ) فراغ SCALLYield( فراغ )
{
    /* Save the context of the interrupted task. */
    پورٽ_SAVE_CONTEXT_SCALL();
    vTaskSwitchContext();
    پورٽ_RESTORE_CONTEXT_SCALL();
}
/*-----------------------------------------------------------*/

/* The code generated by the GCC compiler uses the stack in different ways at
 * different optimisation levels.  The interrupt flags can therefore not always
 * be saved to the stack.  Instead the critical section nesting level is stored
 * in a variable, which is then saved as part of the stack context. */
__attribute__( ( __noinline__ ) ) فراغ v_پورٽ_Enter_Critical( فراغ )
{
    /* Disable interrupts */
    پورٽ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

__attribute__( ( __noinline__ ) ) فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /* Enable all interrupt/exception. */
            پورٽ_ENABLE_INTERRUPTS();
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
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts, it will expect to find the function parameter in R12. */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x08080808;                    /* R8 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x09090909;                    /* R9 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x0A0A0A0A;                    /* R10 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x0B0B0B0B;                    /* R11 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) pvParameters;                  /* R12 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0xDEADBEEF;                    /* R14/LR */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) px_ڪوڊ + پورٽ_INSTRUCTION_سائيز; /* R15/PC */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) پورٽ_INITIAL_SR;                /* SR */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0xFF0000FF;                    /* R0 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x01010101;                    /* R1 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x02020202;                    /* R2 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x03030303;                    /* R3 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x04040404;                    /* R4 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x05050505;                    /* R5 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x06060606;                    /* R6 */
    *px_چوٽي_جو_ڍير-- = ( ڍير_Type_t ) 0x07070707;                    /* R7 */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_NO_CRITICAL_NESTING;         /* ulCriticalNesting */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_تياري_Timer_مداخلت();

    /* Start the first task. */
    پورٽ_RESTORE_CONTEXT();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the AVR32 port will require this function as there
     * is nothing to return to.  */
}
/*-----------------------------------------------------------*/

/* Schedule the COUNT&COMPARE match interrupt in (configCPU_CLOCK_HZ/configTICK_RATE_HZ)
 * clock cycles from now. */
#إذا ( configTICK_USE_TC == 0 )
    ساكن فراغ prv_وقت_جدول_پهريون_Tick( فراغ )
    {
        uint32_t l_چڪرن;

        l_چڪرن = Get_system_رجسٽر( AVR32_ڳڻپ );
        l_چڪرن += ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );

        /* If lCycles ends up to be 0, make it 1 so that the COMPARE and exception */
        /* generation feature does not get disabled. */
        إذا( 0 == l_چڪرن )
        {
            l_چڪرن++;
        }

        سيٽ_system_رجسٽر( AVR32_COMPARE, l_چڪرن );
    }

    __attribute__( ( __noinline__ ) ) ساكن فراغ prv_وقت_جدول_ايندڙ_Tick( فراغ )
    {
        uint32_t l_چڪرن, l_ڳڻپ;

        l_چڪرن = Get_system_رجسٽر( AVR32_COMPARE );
        l_چڪرن += ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );

        /* If lCycles ends up to be 0, make it 1 so that the COMPARE and exception */
        /* generation feature does not get disabled. */
        إذا( 0 == l_چڪرن )
        {
            l_چڪرن++;
        }

        l_ڳڻپ = Get_system_رجسٽر( AVR32_ڳڻپ );

        إذا( l_چڪرن < l_ڳڻپ )
        { /* We missed a tick, recover for the next. */
            l_چڪرن += ( configCPU_CLOCK_HZ / config_TICK_شرح_HZ );
        }

        سيٽ_system_رجسٽر( AVR32_COMPARE, l_چڪرن );
    }
#وإلا /* if ( configTICK_USE_TC == 0 ) */
    __attribute__( ( __noinline__ ) ) ساكن فراغ prvClearTcInt( فراغ )
    {
        AVR32_TC.channel[ configTICK_TC_CHANNEL ].sr;
    }
#جيڪڏهن_پورو /* if ( configTICK_USE_TC == 0 ) */
/*-----------------------------------------------------------*/

/* Setup the timer to generate the tick interrupts. */
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    #إذا ( configTICK_USE_TC == 1 )
        متطاير avr32_tc_t * tc = &AVR32_TC;

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

            .wavsel  = TC_WAVEFORM_SEL_مٿي_گهڻائي_RC_TRIGGER, /* Waveform selection: Up mode without automatic trigger on RC compare. */
            .enetrg  = FALSE,                              /* External event trigger enable. */
            .eevt    = 0,                                  /* External event selection. */
            .eevtedg = TC_SEL_NO_ڪنارو,                     /* External event edge selection. */
            .cpcdis  = FALSE,                              /* Counter disable when RC compare. */
            .cpcstop = FALSE,                              /* Counter clock stopped with RC compare. */

            .مدو_2   = FALSE,                              /* Burst signal selection. */
            .clki    = FALSE,                              /* Clock inversion. */
            .tcclks  = TC_CLOCK_ذريعو_TC2                 /* Internal source clock 2. */
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
    #جيڪڏهن_پورو /* if ( configTICK_USE_TC == 1 ) */

    /* Disable all interrupt/exception. */
    پورٽ_DISABLE_INTERRUPTS();

    /* Register the compare interrupt handler to the interrupt controller and
     * enable the compare interrupt. */

    #إذا ( configTICK_USE_TC == 1 )
    {
        INTC_رجسٽر_مداخلت( &vTick, configTICK_TC_IRQ, INT0 );

        /* Initialize the timer/counter. */
        tc_init_waveform( tc, &waveform_opt );

        /* Set the compare triggers.
         * Remember TC counter is 16-bits, so counting second is not possible!
         * That's why we configure it to count ms. */
        tc_write_rc( tc, configTICK_TC_CHANNEL, ( configPBA_CLOCK_HZ / 4 ) / config_TICK_شرح_HZ );

        tc_configure_interrupts( tc, configTICK_TC_CHANNEL, &tc_مداخلت );

        /* Start the timer/counter. */
        tc_شروعات( tc, configTICK_TC_CHANNEL );
    }
    #وإلا /* if ( configTICK_USE_TC == 1 ) */
    {
        INTC_رجسٽر_مداخلت( &vTick, AVR32_CORE_COMPARE_IRQ, INT0 );
        prv_وقت_جدول_پهريون_Tick();
    }
    #جيڪڏهن_پورو /* if ( configTICK_USE_TC == 1 ) */
}
