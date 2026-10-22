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

#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <xtensa/config/core.h>

#ضمن "xtensa_rtos.h"
#ضمن "esp_idf_version.h"

#إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
    #ضمن "rom/ets_sys.h"
    #ضمن "esp_panic.h"
    #ضمن "esp_crosscore_int.h"
#وإلا
    #إذا CONFIG_IDF_هدف_ESP32_S3
        #ضمن "esp32s3/rom/ets_sys.h"
    #وإلاإذا CONFIG_IDF_هدف_ESP32_S2
        #ضمن "esp32s2/rom/ets_sys.h"
    #وإلاإذا CONFIG_IDF_هدف_ESP32
        #ضمن "esp32/rom/ets_sys.h"
    #جيڪڏهن_پورو
    #ضمن "esp_private/panic_reason.h"
    #ضمن "esp_debug_helpers.h"
    #ضمن "esp_private/crosscore_int.h"
    #ضمن "esp_log.h"
#جيڪڏهن_پورو /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#ضمن "soc/cpu.h"

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#ضمن "esp_heap_caps.h"

#ضمن "esp_intr_alloc.h"

#ضمن "port_systick.h"

/* Defined in xtensa_context.S */
خارجي فراغ _xt_coproc_init( فراغ );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

خارجي متطاير صحيح پورٽ_x_Scheduler_Running[ پورٽ_انگ_PROCESSORS ];
بنانشان پورٽ_مداخلت_Nesting[ پورٽ_انگ_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
فراغ _xt_user_exit( فراغ );

#إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    ساكن فراغ v_پورٽ_Task_Wrapper( TaskFunction_t px_ڪوڊ,
                                  فراغ * pvParameters )
    {
        px_ڪوڊ( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        حرف * pcTaskName = pcTaskGetTaskName( عدم );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#جيڪڏهن_پورو /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#إذا پورٽ_USING_MPU_WRAPPERS
    ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                         TaskFunction_t px_ڪوڊ,
                                         فراغ * pvParameters,
                                         بنياد_Type_t x_لاڳيتو_Privileged )
#وإلا
    ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                         TaskFunction_t px_ڪوڊ,
                                         فراغ * pvParameters )
#جيڪڏهن_پورو
/* *INDENT-ON* */
{
    ڍير_Type_t * sp;
    ڍير_Type_t * tp;
    Xt_Exc_چوکٺو * چوکٺو_2;

    #إذا XCHAL_CP_انگ > 0
        uint32_t * p;
    #جيڪڏهن_پورو

    uint32_t * threadptr;
    فراغ * task_thread_local_شروعات;
    خارجي صحيح thread_local_شروعات, thread_local_پڇاڙي, flash_rodata_شروعات, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &thread_local_پڇاڙي - ( uint8_t * ) &thread_local_شروعات;

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
    sp = ( ڍير_Type_t * ) ( ( ( UBaseType_t ) px_چوٽي_جو_ڍير - XT_CP_سائيز - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    لكل( tp = sp; tp <= px_چوٽي_جو_ڍير; ++tp )
    {
        *tp = 0;
    }

    چوکٺو_2 = ( Xt_Exc_چوکٺو * ) sp;

    /* Explicitly initialize certain saved registers */
    #إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        چوکٺو_2->pc = ( UBaseType_t ) v_پورٽ_Task_Wrapper; /* task wrapper                       */
    #وإلا
        چوکٺو_2->pc = ( UBaseType_t ) px_ڪوڊ;           /* task entrypoint                    */
    #جيڪڏهن_پورو
    چوکٺو_2->a0 = 0;                                    /* to terminate GDB backtrace     */
    چوکٺو_2->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    چوکٺو_2->ٻاهر_نڪرو = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #جيڪڏهن_وصف_ٿيل __XTENSA_CALL0_ABI__
        #إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            چوکٺو_2->a2 = ( UBaseType_t ) px_ڪوڊ;
            چوکٺو_2->a3 = ( UBaseType_t ) pvParameters;
        #وإلا
            چوکٺو_2->a2 = ( UBaseType_t ) pvParameters;
        #جيڪڏهن_پورو
        چوکٺو_2->ps = PS_UM | PS_EXCM;
    #وإلا
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            چوکٺو_2->a6 = ( UBaseType_t ) px_ڪوڊ;
            چوکٺو_2->a7 = ( UBaseType_t ) pvParameters;
        #وإلا
            چوکٺو_2->a6 = ( UBaseType_t ) pvParameters;
        #جيڪڏهن_پورو
        چوکٺو_2->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #جيڪڏهن_پورو /* ifdef __XTENSA_CALL0_ABI__ */

    #جيڪڏهن_وصف_ٿيل XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        چوکٺو_2->vpri = 0xFFFFFFFF;
    #جيڪڏهن_پورو

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_شروعات = ( فراغ * ) ( ( ( uint32_t ) px_چوٽي_جو_ڍير - XT_CP_سائيز - thread_local_sz ) & ~0xf );
    يادگيري_نقل( task_thread_local_شروعات, &thread_local_شروعات, thread_local_sz );
    threadptr = ( uint32_t * ) ( sp + XT_STK_EXTRA );

    /* Calculate THREADPTR value.
     * The generated code will add THREADPTR value to a constant value determined at link time,
     * to get the address of the TLS variable.
     * The constant value is calculated by the linker as follows
     * (search for 'tpoff' in elf32-xtensa.c in BFD):
     *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
     * where TCB_SIZE is hardcoded to 8.
     */
    ثابت uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    ثابت uint32_t tcb_سائيز = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ثابت uint32_t بنياد = ( tcb_سائيز + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_شروعات - ( ( uint32_t ) &thread_local_شروعات - ( uint32_t ) &flash_rodata_شروعات ) - بنياد;

    #إذا XCHAL_CP_انگ > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_چوٽي_جو_ڍير - XT_CP_سائيز ) & ~0xf );
        configASSERT( ( uint32_t ) p >= چوکٺو_2->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_ڪل_SA_ALIGN - 1 ) & -XCHAL_ڪل_SA_ALIGN;
    #جيڪڏهن_پورو

    أرجع sp;
}

/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #إذا XCHAL_CP_انگ > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #جيڪڏهن_پورو

    /* Setup the hardware to generate the tick */
    v_پورٽ_تياري_Timer();

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
    پورٽ_DISABLE_INTERRUPTS();

    پورٽ_x_Scheduler_Running[ x_پورٽ_Get_Core_ID() ] = 1;

    /* Cannot be directly called from C; never returns */
    __asm__ متطاير ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    أرجع pdTRUE;
}

/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield_Other_Core( بنياد_Type_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#إذا پورٽ_USING_MPU_WRAPPERS
    فراغ v_پورٽ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_يادگيري_REGION * ثابت xRegions,
                                    ڍير_Type_t * px_Bottom_جو_ڍير,
                                    config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي )
    {
        #إذا XCHAL_CP_انگ > 0
            xMPUSettings->coproc_area = ( ڍير_Type_t * ) ( ( uint32_t ) ( px_Bottom_جو_ڍير + ux_ڍير_اونهائي - 1 ) );
            xMPUSettings->coproc_area = ( ڍير_Type_t * ) ( ( ( پورٽ_اشارو_سائيز_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( پورٽ_اشارو_سائيز_TYPE ) پورٽ_BYTE_ALIGNMENT_نقاب ) ) );
            xMPUSettings->coproc_area = ( ڍير_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_سائيز ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #جيڪڏهن_پورو
    }

    فراغ v_پورٽ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#جيڪڏهن_پورو /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
بنياد_Type_t x_پورٽ_اندريون_Isr_Context()
{
    بنانشان صحيح irq_حالت;
    بنياد_Type_t ret;

    irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
    ret = ( پورٽ_مداخلت_Nesting[ x_پورٽ_Get_Core_ID() ] != 0 );
    پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    أرجع ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
بنياد_Type_t IRAM_ATTR x_پورٽ_Interrupted_From_ISRContext()
{
    أرجع( پورٽ_مداخلت_Nesting[ x_پورٽ_Get_Core_ID() ] != 0 );
}

فراغ IRAM_ATTR v_پورٽ_Evaluate_Yield_From_ISR( صحيح argc,
                                          ... )
{
    بنياد_Type_t xYield;
    va_list ap;

    va_شروعات( ap, argc );

    إذا( argc )
    {
        xYield = ( بنياد_Type_t ) va_arg( ap, صحيح );
        va_پڇاڙي( ap );
    }
    وإلا
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_پڇاڙي( ap );
        trace_ISR_EXIT_منزل_SCHEDULER();
        frxt_تياري_switch();
        أرجع;
    }

    /*Yield exists, so need evaluate it first then switch: */
    إذا( xYield == pdTRUE )
    {
        trace_ISR_EXIT_منزل_SCHEDULER();
        frxt_تياري_switch();
    }
}

فراغ v_پورٽ_Assert_If_اندريون_ISR()
{
    إذا( x_پورٽ_اندريون_Isr_Context() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", x_پورٽ_Get_Core_ID(), پورٽ_مداخلت_Nesting[ x_پورٽ_Get_Core_ID() ] );
    }

    configASSERT( !x_پورٽ_اندريون_Isr_Context() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
فراغ v_پورٽ_CPUInitialize_Mutex( پورٽ_MUX_TYPE * mux )
{
    #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->آخري_Locked_Fn = "(never locked)";
        mux->آخري_Locked_سٽ = -1;
    #جيڪڏهن_پورو
    mux->owner = پورٽ_MUX_FREE_VAL;
    mux->ڳڻپ = 0;
}

#ضمن "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
    فراغ v_پورٽ_CPUAcquire_Mutex( پورٽ_MUX_TYPE * mux,
                               ثابت حرف * fnName,
                               صحيح سٽ )
    {
        بنانشان صحيح irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

        v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( mux, پورٽ_MUX_NO_TIMEOUT, fnName, سٽ );
        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }

    bool v_پورٽ_CPUAcquire_Mutex_Timeout( پورٽ_MUX_TYPE * mux,
                                      صحيح timeout_چڪرن,
                                      ثابت حرف * fnName,
                                      صحيح سٽ )
    {
        بنانشان صحيح irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
        bool نتيجو = v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_چڪرن, fnName, سٽ );

        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
        أرجع نتيجو;
    }

#وإلا /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    فراغ v_پورٽ_CPUAcquire_Mutex( پورٽ_MUX_TYPE * mux )
    {
        بنانشان صحيح irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

        v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( mux, پورٽ_MUX_NO_TIMEOUT );
        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }

    bool v_پورٽ_CPUAcquire_Mutex_Timeout( پورٽ_MUX_TYPE * mux,
                                      صحيح timeout_چڪرن )
    {
        بنانشان صحيح irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
        bool نتيجو = v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_چڪرن );

        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
        أرجع نتيجو;
    }
#جيڪڏهن_پورو /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
    فراغ v_پورٽ_CPURelease_Mutex( پورٽ_MUX_TYPE * mux,
                               ثابت حرف * fnName,
                               صحيح سٽ )
    {
        بنانشان صحيح irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

        v_پورٽ_CPURelease_Mutex_Ints_Disabled( mux, fnName, سٽ );
        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }
#وإلا
    فراغ v_پورٽ_CPURelease_Mutex( پورٽ_MUX_TYPE * mux )
    {
        بنانشان صحيح irq_حالت = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

        v_پورٽ_CPURelease_Mutex_Ints_Disabled( mux );
        پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }
#جيڪڏهن_پورو /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#وصف_ڪريو ڍير_WATCH_AREA_سائيز       ( 32 )
#وصف_ڪريو ڍير_WATCH_نقطو_عدد    ( SOC_CPU_WATCHPOINTS_انگ - 1 )

فراغ v_پورٽ_سيٽ_ڍير_Watchpoint( فراغ * px_ڍير_شروعات )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    صحيح addr = ( صحيح ) px_ڍير_شروعات;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_سيٽ_watchpoint( ڍير_WATCH_نقطو_عدد, ( حرف * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )

    #إذا defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        ساكن پورٽ_MUX_TYPE extram_mux = پورٽ_MUX_INITIALIZER_UNLOCKED;

        فراغ ux_پورٽ_Compare_سيٽ_Extram( متطاير uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * سيٽ )
        {
            uint32_t prev;

            uint32_t oldlevel = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();

            #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, پورٽ_MUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #وإلا
                v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, پورٽ_MUX_NO_TIMEOUT );
            #جيڪڏهن_پورو
            prev = *addr;

            إذا( prev == compare )
            {
                *addr = *سيٽ;
            }

            *سيٽ = prev;
            #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
                v_پورٽ_CPURelease_Mutex_Ints_Disabled( &extram_mux, __FUNCTION__, __LINE__ );
            #وإلا
                v_پورٽ_CPURelease_Mutex_Ints_Disabled( &extram_mux );
            #جيڪڏهن_پورو

            پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( oldlevel );
        }
    #جيڪڏهن_پورو //defined(CONFIG_SPIRAM_SUPPORT)

#جيڪڏهن_پورو /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t x_پورٽ_Get_Tick_شرح_Hz( فراغ )
{
    أرجع ( uint32_t ) config_TICK_شرح_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#إذا CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_گهڻائي
    #غلطي "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#جيڪڏهن_پورو

خارجي فراغ esp_startup_شروعات_app_common( فراغ );

فراغ esp_startup_شروعات_app( فراغ )
{
    #إذا !CONFIG_ESP_INT_WDT
        #إذا CONFIG_ESP32_ECO3_CACHE_تالو_FIX
            أكد( !soc_has_cache_تالو_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #جيڪڏهن_پورو
    #جيڪڏهن_پورو

    esp_startup_شروعات_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    v_Task_شروعات_Scheduler();
}
