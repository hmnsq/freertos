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

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <xtensa/config/core.h>

#అన్తర్భావ "xtensa_rtos.h"
#అన్తర్భావ "esp_idf_version.h"

#ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
    #అన్తర్భావ "rom/ets_sys.h"
    #అన్తర్భావ "esp_panic.h"
    #అన్తర్భావ "esp_crosscore_int.h"
#లేకపోతే
    #ఒకవేళ CONFIG_IDF_లక్ష్యం_ESP32_S3
        #అన్తర్భావ "esp32s3/rom/ets_sys.h"
    #లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32_S2
        #అన్తర్భావ "esp32s2/rom/ets_sys.h"
    #లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32
        #అన్తర్భావ "esp32/rom/ets_sys.h"
    #అయితే_ముగింపు
    #అన్తర్భావ "esp_private/panic_reason.h"
    #అన్తర్భావ "esp_debug_helpers.h"
    #అన్తర్భావ "esp_private/crosscore_int.h"
    #అన్తర్భావ "esp_log.h"
#అయితే_ముగింపు /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#అన్తర్భావ "soc/cpu.h"

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#అన్తర్భావ "esp_heap_caps.h"

#అన్తర్భావ "esp_intr_alloc.h"

#అన్తర్భావ "port_systick.h"

/* Defined in xtensa_context.S */
బాహ్య శూన్య _xt_coproc_init( శూన్య );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

బాహ్య అస్థిర పూర్ణాంకం పోర్టు_x_Scheduler_Running[ పోర్టు_అంకె_PROCESSORS ];
గుర్తులేని పోర్టు_అంతరాయం_Nesting[ పోర్టు_అంకె_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
శూన్య _xt_user_exit( శూన్య );

#ఒకవేళ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    స్థిర శూన్య v_పోర్టు_Task_Wrapper( TaskFunction_t px_సంకేతం,
                                  శూన్య * pvParameters )
    {
        px_సంకేతం( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        అక్షరం * pcTaskName = pcTaskGetTaskName( ఖాళీ );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#అయితే_ముగింపు /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#ఒకవేళ పోర్టు_USING_MPU_WRAPPERS
    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters,
                                         పునాది_Type_t x_నిరంతరం_Privileged )
#లేకపోతే
    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters )
#అయితే_ముగింపు
/* *INDENT-ON* */
{
    దొంతర_Type_t * sp;
    దొంతర_Type_t * tp;
    Xt_Exc_చట్రం * చట్రం_2;

    #ఒకవేళ XCHAL_CP_అంకె > 0
        uint32_t * p;
    #అయితే_ముగింపు

    uint32_t * threadptr;
    శూన్య * task_thread_local_ప్రారంభం;
    బాహ్య పూర్ణాంకం thread_local_ప్రారంభం, thread_local_చివర, flash_rodata_ప్రారంభం, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &thread_local_చివర - ( uint8_t * ) &thread_local_ప్రారంభం;

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
    sp = ( దొంతర_Type_t * ) ( ( ( UBaseType_t ) px_శిఖరం_యొక్క_దొంతర - XT_CP_కొలత - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    కొరకు( tp = sp; tp <= px_శిఖరం_యొక్క_దొంతర; ++tp )
    {
        *tp = 0;
    }

    చట్రం_2 = ( Xt_Exc_చట్రం * ) sp;

    /* Explicitly initialize certain saved registers */
    #ఒకవేళ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        చట్రం_2->pc = ( UBaseType_t ) v_పోర్టు_Task_Wrapper; /* task wrapper                       */
    #లేకపోతే
        చట్రం_2->pc = ( UBaseType_t ) px_సంకేతం;           /* task entrypoint                    */
    #అయితే_ముగింపు
    చట్రం_2->a0 = 0;                                    /* to terminate GDB backtrace     */
    చట్రం_2->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    చట్రం_2->నిష్క్రమించు = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #నిర్వచితమైతే __XTENSA_CALL0_ABI__
        #ఒకవేళ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            చట్రం_2->a2 = ( UBaseType_t ) px_సంకేతం;
            చట్రం_2->a3 = ( UBaseType_t ) pvParameters;
        #లేకపోతే
            చట్రం_2->a2 = ( UBaseType_t ) pvParameters;
        #అయితే_ముగింపు
        చట్రం_2->ps = PS_UM | PS_EXCM;
    #లేకపోతే
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #ఒకవేళ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            చట్రం_2->a6 = ( UBaseType_t ) px_సంకేతం;
            చట్రం_2->a7 = ( UBaseType_t ) pvParameters;
        #లేకపోతే
            చట్రం_2->a6 = ( UBaseType_t ) pvParameters;
        #అయితే_ముగింపు
        చట్రం_2->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #అయితే_ముగింపు /* ifdef __XTENSA_CALL0_ABI__ */

    #నిర్వచితమైతే XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        చట్రం_2->vpri = 0xFFFFFFFF;
    #అయితే_ముగింపు

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_ప్రారంభం = ( శూన్య * ) ( ( ( uint32_t ) px_శిఖరం_యొక్క_దొంతర - XT_CP_కొలత - thread_local_sz ) & ~0xf );
    జ్ఞాపకం_నకలు( task_thread_local_ప్రారంభం, &thread_local_ప్రారంభం, thread_local_sz );
    threadptr = ( uint32_t * ) ( sp + XT_STK_EXTRA );

    /* Calculate THREADPTR value.
     * The generated code will add THREADPTR value to a constant value determined at link time,
     * to get the address of the TLS variable.
     * The constant value is calculated by the linker as follows
     * (search for 'tpoff' in elf32-xtensa.c in BFD):
     *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
     * where TCB_SIZE is hardcoded to 8.
     */
    స్థిరరాశి uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    స్థిరరాశి uint32_t tcb_కొలత = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    స్థిరరాశి uint32_t పునాది = ( tcb_కొలత + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_ప్రారంభం - ( ( uint32_t ) &thread_local_ప్రారంభం - ( uint32_t ) &flash_rodata_ప్రారంభం ) - పునాది;

    #ఒకవేళ XCHAL_CP_అంకె > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_శిఖరం_యొక్క_దొంతర - XT_CP_కొలత ) & ~0xf );
        configASSERT( ( uint32_t ) p >= చట్రం_2->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_మొత్తం_SA_ALIGN - 1 ) & -XCHAL_మొత్తం_SA_ALIGN;
    #అయితే_ముగింపు

    తిరిగి sp;
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #ఒకవేళ XCHAL_CP_అంకె > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #అయితే_ముగింపు

    /* Setup the hardware to generate the tick */
    v_పోర్టు_అమరిక_Timer();

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
    పోర్టు_DISABLE_INTERRUPTS();

    పోర్టు_x_Scheduler_Running[ x_పోర్టు_Get_Core_ID() ] = 1;

    /* Cannot be directly called from C; never returns */
    __asm__ అస్థిర ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    తిరిగి pdTRUE;
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield_Other_Core( పునాది_Type_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#ఒకవేళ పోర్టు_USING_MPU_WRAPPERS
    శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                    దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                    config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు )
    {
        #ఒకవేళ XCHAL_CP_అంకె > 0
            xMPUSettings->coproc_area = ( దొంతర_Type_t * ) ( ( uint32_t ) ( px_Bottom_యొక్క_దొంతర + ux_దొంతర_లోతు - 1 ) );
            xMPUSettings->coproc_area = ( దొంతర_Type_t * ) ( ( ( పోర్టు_సూచిక_కొలత_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( పోర్టు_సూచిక_కొలత_TYPE ) పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );
            xMPUSettings->coproc_area = ( దొంతర_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_కొలత ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #అయితే_ముగింపు
    }

    శూన్య v_పోర్టు_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#అయితే_ముగింపు /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
పునాది_Type_t x_పోర్టు_లోపల_Isr_Context()
{
    గుర్తులేని పూర్ణాంకం irq_స్థితి;
    పునాది_Type_t ret;

    irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    ret = ( పోర్టు_అంతరాయం_Nesting[ x_పోర్టు_Get_Core_ID() ] != 0 );
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
    తిరిగి ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
పునాది_Type_t IRAM_ATTR x_పోర్టు_Interrupted_From_ISRContext()
{
    తిరిగి( పోర్టు_అంతరాయం_Nesting[ x_పోర్టు_Get_Core_ID() ] != 0 );
}

శూన్య IRAM_ATTR v_పోర్టు_Evaluate_Yield_From_ISR( పూర్ణాంకం argc,
                                          ... )
{
    పునాది_Type_t xYield;
    va_list ap;

    va_ప్రారంభం( ap, argc );

    ఒకవేళ( argc )
    {
        xYield = ( పునాది_Type_t ) va_arg( ap, పూర్ణాంకం );
        va_చివర( ap );
    }
    లేకపోతే
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_చివర( ap );
        trace_ISR_EXIT_గమ్యం_SCHEDULER();
        frxt_అమరిక_switch();
        తిరిగి;
    }

    /*Yield exists, so need evaluate it first then switch: */
    ఒకవేళ( xYield == pdTRUE )
    {
        trace_ISR_EXIT_గమ్యం_SCHEDULER();
        frxt_అమరిక_switch();
    }
}

శూన్య v_పోర్టు_Assert_If_లోపల_ISR()
{
    ఒకవేళ( x_పోర్టు_లోపల_Isr_Context() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", x_పోర్టు_Get_Core_ID(), పోర్టు_అంతరాయం_Nesting[ x_పోర్టు_Get_Core_ID() ] );
    }

    configASSERT( !x_పోర్టు_లోపల_Isr_Context() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
శూన్య v_పోర్టు_CPUInitialize_Mutex( పోర్టు_MUX_TYPE * mux )
{
    #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->చివరి_Locked_Fn = "(never locked)";
        mux->చివరి_Locked_పంక్తి = -1;
    #అయితే_ముగింపు
    mux->owner = పోర్టు_MUX_FREE_VAL;
    mux->లెక్క = 0;
}

#అన్తర్భావ "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
    శూన్య v_పోర్టు_CPUAcquire_Mutex( పోర్టు_MUX_TYPE * mux,
                               స్థిరరాశి అక్షరం * fnName,
                               పూర్ణాంకం పంక్తి )
    {
        గుర్తులేని పూర్ణాంకం irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( mux, పోర్టు_MUX_NO_TIMEOUT, fnName, పంక్తి );
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
    }

    bool v_పోర్టు_CPUAcquire_Mutex_Timeout( పోర్టు_MUX_TYPE * mux,
                                      పూర్ణాంకం timeout_చక్రాలు,
                                      స్థిరరాశి అక్షరం * fnName,
                                      పూర్ణాంకం పంక్తి )
    {
        గుర్తులేని పూర్ణాంకం irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
        bool ఫలితం = v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_చక్రాలు, fnName, పంక్తి );

        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
        తిరిగి ఫలితం;
    }

#లేకపోతే /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    శూన్య v_పోర్టు_CPUAcquire_Mutex( పోర్టు_MUX_TYPE * mux )
    {
        గుర్తులేని పూర్ణాంకం irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( mux, పోర్టు_MUX_NO_TIMEOUT );
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
    }

    bool v_పోర్టు_CPUAcquire_Mutex_Timeout( పోర్టు_MUX_TYPE * mux,
                                      పూర్ణాంకం timeout_చక్రాలు )
    {
        గుర్తులేని పూర్ణాంకం irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
        bool ఫలితం = v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_చక్రాలు );

        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
        తిరిగి ఫలితం;
    }
#అయితే_ముగింపు /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
    శూన్య v_పోర్టు_CPURelease_Mutex( పోర్టు_MUX_TYPE * mux,
                               స్థిరరాశి అక్షరం * fnName,
                               పూర్ణాంకం పంక్తి )
    {
        గుర్తులేని పూర్ణాంకం irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        v_పోర్టు_CPURelease_Mutex_Ints_Disabled( mux, fnName, పంక్తి );
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
    }
#లేకపోతే
    శూన్య v_పోర్టు_CPURelease_Mutex( పోర్టు_MUX_TYPE * mux )
    {
        గుర్తులేని పూర్ణాంకం irq_స్థితి = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

        v_పోర్టు_CPURelease_Mutex_Ints_Disabled( mux );
        పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( irq_స్థితి );
    }
#అయితే_ముగింపు /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#నిర్వచించు దొంతర_WATCH_AREA_కొలత       ( 32 )
#నిర్వచించు దొంతర_WATCH_బిందువు_సంఖ్య    ( SOC_CPU_WATCHPOINTS_అంకె - 1 )

శూన్య v_పోర్టు_సమితి_దొంతర_Watchpoint( శూన్య * px_దొంతర_ప్రారంభం )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    పూర్ణాంకం addr = ( పూర్ణాంకం ) px_దొంతర_ప్రారంభం;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_సమితి_watchpoint( దొంతర_WATCH_బిందువు_సంఖ్య, ( అక్షరం * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )

    #ఒకవేళ defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        స్థిర పోర్టు_MUX_TYPE extram_mux = పోర్టు_MUX_INITIALIZER_UNLOCKED;

        శూన్య ux_పోర్టు_Compare_సమితి_Extram( అస్థిర uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * సమితి )
        {
            uint32_t prev;

            uint32_t oldlevel = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();

            #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, పోర్టు_MUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #లేకపోతే
                v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, పోర్టు_MUX_NO_TIMEOUT );
            #అయితే_ముగింపు
            prev = *addr;

            ఒకవేళ( prev == compare )
            {
                *addr = *సమితి;
            }

            *సమితి = prev;
            #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
                v_పోర్టు_CPURelease_Mutex_Ints_Disabled( &extram_mux, __FUNCTION__, __LINE__ );
            #లేకపోతే
                v_పోర్టు_CPURelease_Mutex_Ints_Disabled( &extram_mux );
            #అయితే_ముగింపు

            పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( oldlevel );
        }
    #అయితే_ముగింపు //defined(CONFIG_SPIRAM_SUPPORT)

#అయితే_ముగింపు /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t x_పోర్టు_Get_Tick_రేటు_Hz( శూన్య )
{
    తిరిగి ( uint32_t ) config_TICK_రేటు_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ఒకవేళ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_బహుళకం
    #దోషం "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#అయితే_ముగింపు

బాహ్య శూన్య esp_startup_ప్రారంభం_app_common( శూన్య );

శూన్య esp_startup_ప్రారంభం_app( శూన్య )
{
    #ఒకవేళ !CONFIG_ESP_INT_WDT
        #ఒకవేళ CONFIG_ESP32_ECO3_CACHE_తాళం_FIX
            ప్రతిజ్ఞా( !soc_has_cache_తాళం_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #అయితే_ముగింపు
    #అయితే_ముగింపు

    esp_startup_ప్రారంభం_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    v_Task_ప్రారంభం_Scheduler();
}
