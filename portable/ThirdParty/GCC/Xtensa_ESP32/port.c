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

#إذا ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
    #ضمن "rom/ets_sys.h"
    #ضمن "esp_panic.h"
    #ضمن "esp_crosscore_int.h"
#وإلا
    #إذا CONFIG_IDF_نشانہ_ESP32_S3
        #ضمن "esp32s3/rom/ets_sys.h"
    #وإلاإذا CONFIG_IDF_نشانہ_ESP32_S2
        #ضمن "esp32s2/rom/ets_sys.h"
    #وإلاإذا CONFIG_IDF_نشانہ_ESP32
        #ضمن "esp32/rom/ets_sys.h"
    #جے_انت
    #ضمن "esp_private/panic_reason.h"
    #ضمن "esp_debug_helpers.h"
    #ضمن "esp_private/crosscore_int.h"
    #ضمن "esp_log.h"
#جے_انت /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
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

خارجي متطاير صحيح پورٹ_x_Scheduler_Running[ پورٹ_عدد_PROCESSORS ];
بنانشانی پورٹ_رکاوٹ_Nesting[ پورٹ_عدد_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
فراغ _xt_user_exit( فراغ );

#إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    ساكن فراغ v_پورٹ_Task_Wrapper( TaskFunction_t px_کوڈ,
                                  فراغ * pvParameters )
    {
        px_کوڈ( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        حرف * pcTaskName = pcTaskGetTaskName( عدم );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#جے_انت /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#إذا پورٹ_USING_MPU_WRAPPERS
    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                         TaskFunction_t px_کوڈ,
                                         فراغ * pvParameters,
                                         ادھار_Type_t x_لگاتار_Privileged )
#وإلا
    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                         TaskFunction_t px_کوڈ,
                                         فراغ * pvParameters )
#جے_انت
/* *INDENT-ON* */
{
    ڈھیر_Type_t * sp;
    ڈھیر_Type_t * tp;
    Xt_Exc_چوکھٹا * چوکھٹا_2;

    #إذا XCHAL_CP_عدد > 0
        uint32_t * p;
    #جے_انت

    uint32_t * threadptr;
    فراغ * task_thread_local_شروع;
    خارجي صحيح thread_local_شروع, thread_local_سرا, flash_rodata_شروع, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &thread_local_سرا - ( uint8_t * ) &thread_local_شروع;

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
    sp = ( ڈھیر_Type_t * ) ( ( ( UBaseType_t ) px_چوٹی_دا_ڈھیر - XT_CP_ناپ - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    لكل( tp = sp; tp <= px_چوٹی_دا_ڈھیر; ++tp )
    {
        *tp = 0;
    }

    چوکھٹا_2 = ( Xt_Exc_چوکھٹا * ) sp;

    /* Explicitly initialize certain saved registers */
    #إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        چوکھٹا_2->pc = ( UBaseType_t ) v_پورٹ_Task_Wrapper; /* task wrapper                       */
    #وإلا
        چوکھٹا_2->pc = ( UBaseType_t ) px_کوڈ;           /* task entrypoint                    */
    #جے_انت
    چوکھٹا_2->a0 = 0;                                    /* to terminate GDB backtrace     */
    چوکھٹا_2->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    چوکھٹا_2->باہر_نکلو = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #جے_تعریف_شدہ __XTENSA_CALL0_ABI__
        #إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            چوکھٹا_2->a2 = ( UBaseType_t ) px_کوڈ;
            چوکھٹا_2->a3 = ( UBaseType_t ) pvParameters;
        #وإلا
            چوکھٹا_2->a2 = ( UBaseType_t ) pvParameters;
        #جے_انت
        چوکھٹا_2->ps = PS_UM | PS_EXCM;
    #وإلا
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #إذا CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            چوکھٹا_2->a6 = ( UBaseType_t ) px_کوڈ;
            چوکھٹا_2->a7 = ( UBaseType_t ) pvParameters;
        #وإلا
            چوکھٹا_2->a6 = ( UBaseType_t ) pvParameters;
        #جے_انت
        چوکھٹا_2->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #جے_انت /* ifdef __XTENSA_CALL0_ABI__ */

    #جے_تعریف_شدہ XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        چوکھٹا_2->vpri = 0xFFFFFFFF;
    #جے_انت

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_شروع = ( فراغ * ) ( ( ( uint32_t ) px_چوٹی_دا_ڈھیر - XT_CP_ناپ - thread_local_sz ) & ~0xf );
    حافظہ_نقل( task_thread_local_شروع, &thread_local_شروع, thread_local_sz );
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
    ثابت uint32_t tcb_ناپ = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ثابت uint32_t ادھار = ( tcb_ناپ + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_شروع - ( ( uint32_t ) &thread_local_شروع - ( uint32_t ) &flash_rodata_شروع ) - ادھار;

    #إذا XCHAL_CP_عدد > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_چوٹی_دا_ڈھیر - XT_CP_ناپ ) & ~0xf );
        configASSERT( ( uint32_t ) p >= چوکھٹا_2->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_کل_SA_ALIGN - 1 ) & -XCHAL_کل_SA_ALIGN;
    #جے_انت

    أرجع sp;
}

/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    پورٹ_DISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #إذا XCHAL_CP_عدد > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #جے_انت

    /* Setup the hardware to generate the tick */
    v_پورٹ_تیاری_Timer();

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
    پورٹ_DISABLE_INTERRUPTS();

    پورٹ_x_Scheduler_Running[ x_پورٹ_Get_Core_ID() ] = 1;

    /* Cannot be directly called from C; never returns */
    __asm__ متطاير ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    أرجع pdTRUE;
}

/*-----------------------------------------------------------*/

فراغ v_پورٹ_Yield_Other_Core( ادھار_Type_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#إذا پورٹ_USING_MPU_WRAPPERS
    فراغ v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_حافظہ_REGION * ثابت xRegions,
                                    ڈھیر_Type_t * px_Bottom_دا_ڈھیر,
                                    config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی )
    {
        #إذا XCHAL_CP_عدد > 0
            xMPUSettings->coproc_area = ( ڈھیر_Type_t * ) ( ( uint32_t ) ( px_Bottom_دا_ڈھیر + ux_ڈھیر_ڈونگھائی - 1 ) );
            xMPUSettings->coproc_area = ( ڈھیر_Type_t * ) ( ( ( پورٹ_اشارہ_گر_ناپ_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( پورٹ_اشارہ_گر_ناپ_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب ) ) );
            xMPUSettings->coproc_area = ( ڈھیر_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_ناپ ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #جے_انت
    }

    فراغ v_پورٹ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#جے_انت /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
ادھار_Type_t x_پورٹ_وچ_Isr_Context()
{
    بنانشانی صحيح irq_حالت;
    ادھار_Type_t ret;

    irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
    ret = ( پورٹ_رکاوٹ_Nesting[ x_پورٹ_Get_Core_ID() ] != 0 );
    پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
    أرجع ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
ادھار_Type_t IRAM_ATTR x_پورٹ_Interrupted_From_ISRContext()
{
    أرجع( پورٹ_رکاوٹ_Nesting[ x_پورٹ_Get_Core_ID() ] != 0 );
}

فراغ IRAM_ATTR v_پورٹ_Evaluate_Yield_From_ISR( صحيح argc,
                                          ... )
{
    ادھار_Type_t xYield;
    va_list ap;

    va_شروع( ap, argc );

    إذا( argc )
    {
        xYield = ( ادھار_Type_t ) va_arg( ap, صحيح );
        va_سرا( ap );
    }
    وإلا
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_سرا( ap );
        trace_ISR_EXIT_منزل_SCHEDULER();
        frxt_تیاری_switch();
        أرجع;
    }

    /*Yield exists, so need evaluate it first then switch: */
    إذا( xYield == pdTRUE )
    {
        trace_ISR_EXIT_منزل_SCHEDULER();
        frxt_تیاری_switch();
    }
}

فراغ v_پورٹ_Assert_If_وچ_ISR()
{
    إذا( x_پورٹ_وچ_Isr_Context() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", x_پورٹ_Get_Core_ID(), پورٹ_رکاوٹ_Nesting[ x_پورٹ_Get_Core_ID() ] );
    }

    configASSERT( !x_پورٹ_وچ_Isr_Context() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
فراغ v_پورٹ_CPUInitialize_Mutex( پورٹ_MUX_TYPE * mux )
{
    #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->آخری_Locked_Fn = "(never locked)";
        mux->آخری_Locked_سطر = -1;
    #جے_انت
    mux->owner = پورٹ_MUX_FREE_VAL;
    mux->گنتی = 0;
}

#ضمن "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
    فراغ v_پورٹ_CPUAcquire_Mutex( پورٹ_MUX_TYPE * mux,
                               ثابت حرف * fnName,
                               صحيح سطر )
    {
        بنانشانی صحيح irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();

        v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, پورٹ_MUX_NO_TIMEOUT, fnName, سطر );
        پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
    }

    bool v_پورٹ_CPUAcquire_Mutex_Timeout( پورٹ_MUX_TYPE * mux,
                                      صحيح timeout_چکراں,
                                      ثابت حرف * fnName,
                                      صحيح سطر )
    {
        بنانشانی صحيح irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
        bool نتیجہ = v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_چکراں, fnName, سطر );

        پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
        أرجع نتیجہ;
    }

#وإلا /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    فراغ v_پورٹ_CPUAcquire_Mutex( پورٹ_MUX_TYPE * mux )
    {
        بنانشانی صحيح irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();

        v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, پورٹ_MUX_NO_TIMEOUT );
        پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
    }

    bool v_پورٹ_CPUAcquire_Mutex_Timeout( پورٹ_MUX_TYPE * mux,
                                      صحيح timeout_چکراں )
    {
        بنانشانی صحيح irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();
        bool نتیجہ = v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_چکراں );

        پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
        أرجع نتیجہ;
    }
#جے_انت /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
    فراغ v_پورٹ_CPURelease_Mutex( پورٹ_MUX_TYPE * mux,
                               ثابت حرف * fnName,
                               صحيح سطر )
    {
        بنانشانی صحيح irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();

        v_پورٹ_CPURelease_Mutex_Ints_Disabled( mux, fnName, سطر );
        پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
    }
#وإلا
    فراغ v_پورٹ_CPURelease_Mutex( پورٹ_MUX_TYPE * mux )
    {
        بنانشانی صحيح irq_حالت = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();

        v_پورٹ_CPURelease_Mutex_Ints_Disabled( mux );
        پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( irq_حالت );
    }
#جے_انت /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#تعریف_کرو ڈھیر_WATCH_AREA_ناپ       ( 32 )
#تعریف_کرو ڈھیر_WATCH_نقطہ_نمبر    ( SOC_CPU_WATCHPOINTS_عدد - 1 )

فراغ v_پورٹ_سیٹ_ڈھیر_Watchpoint( فراغ * px_ڈھیر_شروع )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    صحيح addr = ( صحيح ) px_ڈھیر_شروع;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_سیٹ_watchpoint( ڈھیر_WATCH_نقطہ_نمبر, ( حرف * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#إذا ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )

    #إذا defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        ساكن پورٹ_MUX_TYPE extram_mux = پورٹ_MUX_INITIALIZER_UNLOCKED;

        فراغ ux_پورٹ_Compare_سیٹ_Extram( متطاير uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * سیٹ )
        {
            uint32_t prev;

            uint32_t oldlevel = پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR();

            #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, پورٹ_MUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #وإلا
                v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, پورٹ_MUX_NO_TIMEOUT );
            #جے_انت
            prev = *addr;

            إذا( prev == compare )
            {
                *addr = *سیٹ;
            }

            *سیٹ = prev;
            #جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_پورٹ_CPURelease_Mutex_Ints_Disabled( &extram_mux, __FUNCTION__, __LINE__ );
            #وإلا
                v_پورٹ_CPURelease_Mutex_Ints_Disabled( &extram_mux );
            #جے_انت

            پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( oldlevel );
        }
    #جے_انت //defined(CONFIG_SPIRAM_SUPPORT)

#جے_انت /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t x_پورٹ_Get_Tick_شرح_Hz( فراغ )
{
    أرجع ( uint32_t ) config_TICK_شرح_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#إذا CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_منوال
    #غلطی "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#جے_انت

خارجي فراغ esp_startup_شروع_app_common( فراغ );

فراغ esp_startup_شروع_app( فراغ )
{
    #إذا !CONFIG_ESP_INT_WDT
        #إذا CONFIG_ESP32_ECO3_CACHE_جندرا_FIX
            أكد( !soc_has_cache_جندرا_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #جے_انت
    #جے_انت

    esp_startup_شروع_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    v_Task_شروع_Scheduler();
}
