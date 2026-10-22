/*
 * SPDX-FileCopyrightText: 2020 Amazon.com, Inc. or its affiliates
 * SPDX-FileCopyrightText: 2015-2019 Cadence Design Systems, Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2016-2022 Espressif Systems (Shanghai) CO LTD
 */

/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
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
 * 1 tab == 4 spaces!
 */

/*
 * Copyright (c) 2015-2019 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xtensa/config/core.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "xtensa_rtos.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_idf_version.h"

#ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
    #ਅਨ੍ਤਰ੍ਭਾਵ "rom/ets_sys.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_panic.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_crosscore_int.h"
#ਨਹੀਂਤਾਂ
    #ਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_S3
        #ਅਨ੍ਤਰ੍ਭਾਵ "esp32s3/rom/ets_sys.h"
    #ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_S2
        #ਅਨ੍ਤਰ੍ਭਾਵ "esp32s2/rom/ets_sys.h"
    #ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32
        #ਅਨ੍ਤਰ੍ਭਾਵ "esp32/rom/ets_sys.h"
    #ਜੇ_ਅੰਤ
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_private/panic_reason.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_debug_helpers.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_private/crosscore_int.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_log.h"
#ਜੇ_ਅੰਤ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#ਅਨ੍ਤਰ੍ਭਾਵ "soc/cpu.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "esp_heap_caps.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "esp_intr_alloc.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "port_systick.h"

/* Defined in xtensa_context.S */
ਬਾਹਰੀ ਖਾਲੀ _xt_coproc_init( ਖਾਲੀ );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ ਪੋਰਟ_x_Scheduler_Running[ ਪੋਰਟ_ਅੰਕ_PROCESSORS ];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting[ ਪੋਰਟ_ਅੰਕ_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
ਖਾਲੀ _xt_user_exit( ਖਾਲੀ );

#ਜੇ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_Task_Wrapper( TaskFunction_t px_ਕੋਡ,
                                  ਖਾਲੀ * pvParameters )
    {
        px_ਕੋਡ( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        ਅੱਖਰ * pcTaskName = pcTaskGetTaskName( ਨਿਰਾ );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#ਜੇ_ਅੰਤ /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#ਜੇ ਪੋਰਟ_USING_MPU_WRAPPERS
    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters,
                                         ਅਧਾਰ_Type_t x_ਲੜੀਵਾਰ_Privileged )
#ਨਹੀਂਤਾਂ
    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters )
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */
{
    ਢੇਰ_Type_t * sp;
    ਢੇਰ_Type_t * tp;
    Xt_Exc_ਚੌਖਟਾ * ਚੌਖਟਾ_2;

    #ਜੇ XCHAL_CP_ਅੰਕ > 0
        uint32_t * p;
    #ਜੇ_ਅੰਤ

    uint32_t * threadptr;
    ਖਾਲੀ * task_thread_local_ਸ਼ੁਰੂ;
    ਬਾਹਰੀ ਪੂਰਨ thread_local_ਸ਼ੁਰੂ, thread_local_ਸਿਰਾ, flash_rodata_ਸ਼ੁਰੂ, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &thread_local_ਸਿਰਾ - ( uint8_t * ) &thread_local_ਸ਼ੁਰੂ;

    thread_local_sz = ALIGNUP( 0x10, thread_local_sz );

    /* Initialize task's stack so that we have the following structure at the top:
     *
     *  ----LOW ADDRESSES ----------------------------------------HIGH ADDRESSES----------
     *   task stack | interrupt stack frame | thread local vars | co-processor save area |
     *  ----------------------------------------------------------------------------------
     |                                                                    |
     |              SP                                                             pxTopOfStack
     |
     |  All parts are aligned to 16 byte boundary.
     */

    /* Create interrupt stack frame aligned to 16 byte boundary */
    sp = ( ਢੇਰ_Type_t * ) ( ( ( UBaseType_t ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ - XT_CP_ਮਾਪ - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    ਲਈ( tp = sp; tp <= px_ਸਿਖਰ_ਦਾ_ਢੇਰ; ++tp )
    {
        *tp = 0;
    }

    ਚੌਖਟਾ_2 = ( Xt_Exc_ਚੌਖਟਾ * ) sp;

    /* Explicitly initialize certain saved registers */
    #ਜੇ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        ਚੌਖਟਾ_2->pc = ( UBaseType_t ) v_ਪੋਰਟ_Task_Wrapper; /* task wrapper                       */
    #ਨਹੀਂਤਾਂ
        ਚੌਖਟਾ_2->pc = ( UBaseType_t ) px_ਕੋਡ;           /* task entrypoint                    */
    #ਜੇ_ਅੰਤ
    ਚੌਖਟਾ_2->a0 = 0;                                    /* to terminate GDB backtrace     */
    ਚੌਖਟਾ_2->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    ਚੌਖਟਾ_2->ਬਾਹਰ_ਨਿਕਲੋ = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __XTENSA_CALL0_ABI__
        #ਜੇ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            ਚੌਖਟਾ_2->a2 = ( UBaseType_t ) px_ਕੋਡ;
            ਚੌਖਟਾ_2->a3 = ( UBaseType_t ) pvParameters;
        #ਨਹੀਂਤਾਂ
            ਚੌਖਟਾ_2->a2 = ( UBaseType_t ) pvParameters;
        #ਜੇ_ਅੰਤ
        ਚੌਖਟਾ_2->ps = PS_UM | PS_EXCM;
    #ਨਹੀਂਤਾਂ
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #ਜੇ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            ਚੌਖਟਾ_2->a6 = ( UBaseType_t ) px_ਕੋਡ;
            ਚੌਖਟਾ_2->a7 = ( UBaseType_t ) pvParameters;
        #ਨਹੀਂਤਾਂ
            ਚੌਖਟਾ_2->a6 = ( UBaseType_t ) pvParameters;
        #ਜੇ_ਅੰਤ
        ਚੌਖਟਾ_2->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #ਜੇ_ਅੰਤ /* ifdef __XTENSA_CALL0_ABI__ */

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        ਚੌਖਟਾ_2->vpri = 0xFFFFFFFF;
    #ਜੇ_ਅੰਤ

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_ਸ਼ੁਰੂ = ( ਖਾਲੀ * ) ( ( ( uint32_t ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ - XT_CP_ਮਾਪ - thread_local_sz ) & ~0xf );
    ਸਮ੍ਰਿਤੀ_ਨਕਲ( task_thread_local_ਸ਼ੁਰੂ, &thread_local_ਸ਼ੁਰੂ, thread_local_sz );
    threadptr = ( uint32_t * ) ( sp + XT_STK_EXTRA );

    /* Calculate THREADPTR value.
     * The generated code will add THREADPTR value to a constant value determined at link time,
     * to get the address of the TLS variable.
     * The constant value is calculated by the linker as follows
     * (search for 'tpoff' in elf32-xtensa.c in BFD):
     *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
     * where TCB_SIZE is hardcoded to 8.
     */
    ਅਚਲ uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    ਅਚਲ uint32_t tcb_ਮਾਪ = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ਅਚਲ uint32_t ਅਧਾਰ = ( tcb_ਮਾਪ + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_ਸ਼ੁਰੂ - ( ( uint32_t ) &thread_local_ਸ਼ੁਰੂ - ( uint32_t ) &flash_rodata_ਸ਼ੁਰੂ ) - ਅਧਾਰ;

    #ਜੇ XCHAL_CP_ਅੰਕ > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ - XT_CP_ਮਾਪ ) & ~0xf );
        configASSERT( ( uint32_t ) p >= ਚੌਖਟਾ_2->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_ਕੁੱਲ_SA_ALIGN - 1 ) & -XCHAL_ਕੁੱਲ_SA_ALIGN;
    #ਜੇ_ਅੰਤ

    ਵਾਪਸ sp;
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #ਜੇ XCHAL_CP_ਅੰਕ > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #ਜੇ_ਅੰਤ

    /* Setup the hardware to generate the tick */
    v_ਪੋਰਟ_ਤਿਆਰੀ_Timer();

    /* NOTE: For ESP32-S3, vPortSetupTimer allocates an interrupt for the
     * systimer which is used as the source for FreeRTOS systick.
     *
     * The behaviour of portEXIT_CRITICAL is different in FreeRTOS and ESP-IDF -
     * the former enables the interrupts no matter what the state was at the beginning
     * of the call while the latter restores the interrupt state to what was at the
     * beginning of the call.
     *
     * This resulted in the interrupts being enabled before the _frxt_dispatch call,
     * who was unable to switch context to the queued tasks.
     */
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਪੋਰਟ_x_Scheduler_Running[ x_ਪੋਰਟ_Get_Core_ID() ] = 1;

    /* Cannot be directly called from C; never returns */
    __asm__ ਅਸਥਿਰ ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    ਵਾਪਸ pdTRUE;
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield_Other_Core( ਅਧਾਰ_Type_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#ਜੇ ਪੋਰਟ_USING_MPU_WRAPPERS
    ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                    ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                    config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ )
    {
        #ਜੇ XCHAL_CP_ਅੰਕ > 0
            xMPUSettings->coproc_area = ( ਢੇਰ_Type_t * ) ( ( uint32_t ) ( px_Bottom_ਦਾ_ਢੇਰ + ux_ਢੇਰ_ਡੂੰਘਾਈ - 1 ) );
            xMPUSettings->coproc_area = ( ਢੇਰ_Type_t * ) ( ( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );
            xMPUSettings->coproc_area = ( ਢੇਰ_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_ਮਾਪ ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #ਜੇ_ਅੰਤ
    }

    ਖਾਲੀ v_ਪੋਰਟ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#ਜੇ_ਅੰਤ /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਵਿੱਚ_Isr_Context()
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ;
    ਅਧਾਰ_Type_t ret;

    irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
    ret = ( ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting[ x_ਪੋਰਟ_Get_Core_ID() ] != 0 );
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
    ਵਾਪਸ ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
ਅਧਾਰ_Type_t IRAM_ATTR x_ਪੋਰਟ_Interrupted_From_ISRContext()
{
    ਵਾਪਸ( ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting[ x_ਪੋਰਟ_Get_Core_ID() ] != 0 );
}

ਖਾਲੀ IRAM_ATTR v_ਪੋਰਟ_Evaluate_Yield_From_ISR( ਪੂਰਨ argc,
                                          ... )
{
    ਅਧਾਰ_Type_t xYield;
    va_list ap;

    va_ਸ਼ੁਰੂ( ap, argc );

    ਜੇ( argc )
    {
        xYield = ( ਅਧਾਰ_Type_t ) va_arg( ap, ਪੂਰਨ );
        va_ਸਿਰਾ( ap );
    }
    ਨਹੀਂਤਾਂ
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_ਸਿਰਾ( ap );
        trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
        frxt_ਤਿਆਰੀ_switch();
        ਵਾਪਸ;
    }

    /*Yield exists, so need evaluate it first then switch: */
    ਜੇ( xYield == pdTRUE )
    {
        trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
        frxt_ਤਿਆਰੀ_switch();
    }
}

ਖਾਲੀ v_ਪੋਰਟ_Assert_If_ਵਿੱਚ_ISR()
{
    ਜੇ( x_ਪੋਰਟ_ਵਿੱਚ_Isr_Context() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", x_ਪੋਰਟ_Get_Core_ID(), ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting[ x_ਪੋਰਟ_Get_Core_ID() ] );
    }

    configASSERT( !x_ਪੋਰਟ_ਵਿੱਚ_Isr_Context() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
ਖਾਲੀ v_ਪੋਰਟ_CPUInitialize_Mutex( ਪੋਰਟ_MUX_TYPE * mux )
{
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->ਆਖਰੀ_Locked_Fn = "(never locked)";
        mux->ਆਖਰੀ_Locked_ਸਤਰ = -1;
    #ਜੇ_ਅੰਤ
    mux->owner = ਪੋਰਟ_MUX_FREE_VAL;
    mux->ਗਿਣਤੀ_2 = 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
    ਖਾਲੀ v_ਪੋਰਟ_CPUAcquire_Mutex( ਪੋਰਟ_MUX_TYPE * mux,
                               ਅਚਲ ਅੱਖਰ * fnName,
                               ਪੂਰਨ ਸਤਰ )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( mux, ਪੋਰਟ_MUX_NO_TIMEOUT, fnName, ਸਤਰ );
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
    }

    bool v_ਪੋਰਟ_CPUAcquire_Mutex_Timeout( ਪੋਰਟ_MUX_TYPE * mux,
                                      ਪੂਰਨ timeout_ਚੱਕਰਾਂ,
                                      ਅਚਲ ਅੱਖਰ * fnName,
                                      ਪੂਰਨ ਸਤਰ )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
        bool ਨਤੀਜਾ = v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_ਚੱਕਰਾਂ, fnName, ਸਤਰ );

        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
        ਵਾਪਸ ਨਤੀਜਾ;
    }

#ਨਹੀਂਤਾਂ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    ਖਾਲੀ v_ਪੋਰਟ_CPUAcquire_Mutex( ਪੋਰਟ_MUX_TYPE * mux )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( mux, ਪੋਰਟ_MUX_NO_TIMEOUT );
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
    }

    bool v_ਪੋਰਟ_CPUAcquire_Mutex_Timeout( ਪੋਰਟ_MUX_TYPE * mux,
                                      ਪੂਰਨ timeout_ਚੱਕਰਾਂ )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
        bool ਨਤੀਜਾ = v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_ਚੱਕਰਾਂ );

        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
        ਵਾਪਸ ਨਤੀਜਾ;
    }
#ਜੇ_ਅੰਤ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
    ਖਾਲੀ v_ਪੋਰਟ_CPURelease_Mutex( ਪੋਰਟ_MUX_TYPE * mux,
                               ਅਚਲ ਅੱਖਰ * fnName,
                               ਪੂਰਨ ਸਤਰ )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled( mux, fnName, ਸਤਰ );
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
    }
#ਨਹੀਂਤਾਂ
    ਖਾਲੀ v_ਪੋਰਟ_CPURelease_Mutex( ਪੋਰਟ_MUX_TYPE * mux )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ irq_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

        v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled( mux );
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( irq_ਸਥਿਤੀ );
    }
#ਜੇ_ਅੰਤ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_WATCH_AREA_ਮਾਪ       ( 32 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_WATCH_ਬਿੰਦੂ_ਸੰਖਿਆ    ( SOC_CPU_WATCHPOINTS_ਅੰਕ - 1 )

ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_ਢੇਰ_Watchpoint( ਖਾਲੀ * px_ਢੇਰ_ਸ਼ੁਰੂ )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    ਪੂਰਨ addr = ( ਪੂਰਨ ) px_ਢੇਰ_ਸ਼ੁਰੂ;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_ਸੈੱਟ_watchpoint( ਢੇਰ_WATCH_ਬਿੰਦੂ_ਸੰਖਿਆ, ( ਅੱਖਰ * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )

    #ਜੇ defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        ਸਥਿਰ ਪੋਰਟ_MUX_TYPE extram_mux = ਪੋਰਟ_MUX_INITIALIZER_UNLOCKED;

        ਖਾਲੀ ux_ਪੋਰਟ_Compare_ਸੈੱਟ_Extram( ਅਸਥਿਰ uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * ਸੈੱਟ )
        {
            uint32_t prev;

            uint32_t oldlevel = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

            #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, ਪੋਰਟ_MUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #ਨਹੀਂਤਾਂ
                v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, ਪੋਰਟ_MUX_NO_TIMEOUT );
            #ਜੇ_ਅੰਤ
            prev = *addr;

            ਜੇ( prev == compare )
            {
                *addr = *ਸੈੱਟ;
            }

            *ਸੈੱਟ = prev;
            #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled( &extram_mux, __FUNCTION__, __LINE__ );
            #ਨਹੀਂਤਾਂ
                v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled( &extram_mux );
            #ਜੇ_ਅੰਤ

            ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( oldlevel );
        }
    #ਜੇ_ਅੰਤ //defined(CONFIG_SPIRAM_SUPPORT)

#ਜੇ_ਅੰਤ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t x_ਪੋਰਟ_Get_Tick_ਦਰ_Hz( ਖਾਲੀ )
{
    ਵਾਪਸ ( uint32_t ) config_TICK_ਦਰ_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ਜੇ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_ਬਹੁਲਕ
    #ਗਲਤੀ "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#ਜੇ_ਅੰਤ

ਬਾਹਰੀ ਖਾਲੀ esp_startup_ਸ਼ੁਰੂ_app_common( ਖਾਲੀ );

ਖਾਲੀ esp_startup_ਸ਼ੁਰੂ_app( ਖਾਲੀ )
{
    #ਜੇ !CONFIG_ESP_INT_WDT
        #ਜੇ CONFIG_ESP32_ECO3_CACHE_ਤਾਲਾ_FIX
            ਪ੍ਰਤਿਜ੍ਞਾ( !soc_has_cache_ਤਾਲਾ_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #ਜੇ_ਅੰਤ
    #ਜੇ_ਅੰਤ

    esp_startup_ਸ਼ੁਰੂ_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    v_Task_ਸ਼ੁਰੂ_Scheduler();
}
