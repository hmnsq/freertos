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

#شامل <stdlib.h>
#شامل <string.h>
#شامل <xtensa/config/core.h>

#شامل "xtensa_rtos.h"
#شامل "esp_idf_version.h"

#اگر ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
    #شامل "rom/ets_sys.h"
    #شامل "esp_panic.h"
    #شامل "esp_crosscore_int.h"
#ورنہ
    #اگر CONFIG_IDF_ہدف_ESP32_S3
        #شامل "esp32s3/rom/ets_sys.h"
    #وگرنہ_اگر CONFIG_IDF_ہدف_ESP32_S2
        #شامل "esp32s2/rom/ets_sys.h"
    #وگرنہ_اگر CONFIG_IDF_ہدف_ESP32
        #شامل "esp32/rom/ets_sys.h"
    #اگر_ختم
    #شامل "esp_private/panic_reason.h"
    #شامل "esp_debug_helpers.h"
    #شامل "esp_private/crosscore_int.h"
    #شامل "esp_log.h"
#اگر_ختم /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#شامل "soc/cpu.h"

#شامل "FreeRTOS.h"
#شامل "task.h"

#شامل "esp_heap_caps.h"

#شامل "esp_intr_alloc.h"

#شامل "port_systick.h"

/* Defined in xtensa_context.S */
خارجی خالی _xt_coproc_init( خالی );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

خارجی متلون صحیح پورٹ_x_Scheduler_Running[ پورٹ_عدد_PROCESSORS ];
غیرعلامتی پورٹ_مداخلت_Nesting[ پورٹ_عدد_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
خالی _xt_user_exit( خالی );

#اگر CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    ساکن خالی v_پورٹ_Task_Wrapper( TaskFunction_t px_رمز,
                                  خالی * pvParameters )
    {
        px_رمز( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        حرف * pcTaskName = pcTaskGetTaskName( تہی );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#اگر_ختم /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#اگر پورٹ_USING_MPU_WRAPPERS
    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                         TaskFunction_t px_رمز,
                                         خالی * pvParameters,
                                         بنیاد_Type_t x_تسلسل_Privileged )
#ورنہ
    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                         TaskFunction_t px_رمز,
                                         خالی * pvParameters )
#اگر_ختم
/* *INDENT-ON* */
{
    ڈھیر_Type_t * sp;
    ڈھیر_Type_t * tp;
    Xt_Exc_چوکھٹا * چوکھٹا_2;

    #اگر XCHAL_CP_عدد > 0
        uint32_t * p;
    #اگر_ختم

    uint32_t * threadptr;
    خالی * task_thread_local_آغاز;
    خارجی صحیح thread_local_آغاز, thread_local_انتہا, flash_rodata_آغاز, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &thread_local_انتہا - ( uint8_t * ) &thread_local_آغاز;

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
    sp = ( ڈھیر_Type_t * ) ( ( ( UBaseType_t ) px_چوٹی_کا_ڈھیر - XT_CP_سائز - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    برائے( tp = sp; tp <= px_چوٹی_کا_ڈھیر; ++tp )
    {
        *tp = 0;
    }

    چوکھٹا_2 = ( Xt_Exc_چوکھٹا * ) sp;

    /* Explicitly initialize certain saved registers */
    #اگر CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        چوکھٹا_2->pc = ( UBaseType_t ) v_پورٹ_Task_Wrapper; /* task wrapper                       */
    #ورنہ
        چوکھٹا_2->pc = ( UBaseType_t ) px_رمز;           /* task entrypoint                    */
    #اگر_ختم
    چوکھٹا_2->a0 = 0;                                    /* to terminate GDB backtrace     */
    چوکھٹا_2->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    چوکھٹا_2->باہر_نکلو = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #اگر_تعریف_شدہ __XTENSA_CALL0_ABI__
        #اگر CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            چوکھٹا_2->a2 = ( UBaseType_t ) px_رمز;
            چوکھٹا_2->a3 = ( UBaseType_t ) pvParameters;
        #ورنہ
            چوکھٹا_2->a2 = ( UBaseType_t ) pvParameters;
        #اگر_ختم
        چوکھٹا_2->ps = PS_UM | PS_EXCM;
    #ورنہ
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #اگر CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            چوکھٹا_2->a6 = ( UBaseType_t ) px_رمز;
            چوکھٹا_2->a7 = ( UBaseType_t ) pvParameters;
        #ورنہ
            چوکھٹا_2->a6 = ( UBaseType_t ) pvParameters;
        #اگر_ختم
        چوکھٹا_2->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #اگر_ختم /* ifdef __XTENSA_CALL0_ABI__ */

    #اگر_تعریف_شدہ XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        چوکھٹا_2->vpri = 0xFFFFFFFF;
    #اگر_ختم

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_آغاز = ( خالی * ) ( ( ( uint32_t ) px_چوٹی_کا_ڈھیر - XT_CP_سائز - thread_local_sz ) & ~0xf );
    حافظہ_نقل( task_thread_local_آغاز, &thread_local_آغاز, thread_local_sz );
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
    ثابت uint32_t tcb_سائز = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ثابت uint32_t بنیاد = ( tcb_سائز + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_آغاز - ( ( uint32_t ) &thread_local_آغاز - ( uint32_t ) &flash_rodata_آغاز ) - بنیاد;

    #اگر XCHAL_CP_عدد > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_چوٹی_کا_ڈھیر - XT_CP_سائز ) & ~0xf );
        configASSERT( ( uint32_t ) p >= چوکھٹا_2->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_کل_SA_ALIGN - 1 ) & -XCHAL_کل_SA_ALIGN;
    #اگر_ختم

    واپس sp;
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #اگر XCHAL_CP_عدد > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #اگر_ختم

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
    __asm__ متلون ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    واپس pdTRUE;
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield_Other_Core( بنیاد_Type_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#اگر پورٹ_USING_MPU_WRAPPERS
    خالی v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت ساخت x_حافظہ_REGION * ثابت xRegions,
                                    ڈھیر_Type_t * px_Bottom_کا_ڈھیر,
                                    config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی )
    {
        #اگر XCHAL_CP_عدد > 0
            xMPUSettings->coproc_area = ( ڈھیر_Type_t * ) ( ( uint32_t ) ( px_Bottom_کا_ڈھیر + ux_ڈھیر_گہرائی - 1 ) );
            xMPUSettings->coproc_area = ( ڈھیر_Type_t * ) ( ( ( پورٹ_اشارہ_گر_سائز_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( پورٹ_اشارہ_گر_سائز_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب ) ) );
            xMPUSettings->coproc_area = ( ڈھیر_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_سائز ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #اگر_ختم
    }

    خالی v_پورٹ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#اگر_ختم /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
بنیاد_Type_t x_پورٹ_اندر_Isr_Context()
{
    غیرعلامتی صحیح irq_حالت;
    بنیاد_Type_t ret;

    irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
    ret = ( پورٹ_مداخلت_Nesting[ x_پورٹ_Get_Core_ID() ] != 0 );
    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    واپس ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
بنیاد_Type_t IRAM_ATTR x_پورٹ_Interrupted_From_ISRContext()
{
    واپس( پورٹ_مداخلت_Nesting[ x_پورٹ_Get_Core_ID() ] != 0 );
}

خالی IRAM_ATTR v_پورٹ_Evaluate_Yield_From_ISR( صحیح argc,
                                          ... )
{
    بنیاد_Type_t xYield;
    va_list ap;

    va_آغاز( ap, argc );

    اگر( argc )
    {
        xYield = ( بنیاد_Type_t ) va_arg( ap, صحیح );
        va_انتہا( ap );
    }
    ورنہ
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_انتہا( ap );
        trace_ISR_EXIT_مقصد_SCHEDULER();
        frxt_تیاری_switch();
        واپس;
    }

    /*Yield exists, so need evaluate it first then switch: */
    اگر( xYield == pdTRUE )
    {
        trace_ISR_EXIT_مقصد_SCHEDULER();
        frxt_تیاری_switch();
    }
}

خالی v_پورٹ_Assert_If_اندر_ISR()
{
    اگر( x_پورٹ_اندر_Isr_Context() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", x_پورٹ_Get_Core_ID(), پورٹ_مداخلت_Nesting[ x_پورٹ_Get_Core_ID() ] );
    }

    configASSERT( !x_پورٹ_اندر_Isr_Context() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
خالی v_پورٹ_CPUInitialize_Mutex( پورٹ_MUX_TYPE * mux )
{
    #اگر_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->آخری_Locked_Fn = "(never locked)";
        mux->آخری_Locked_سطر = -1;
    #اگر_ختم
    mux->owner = پورٹ_MUX_FREE_VAL;
    mux->گنتی = 0;
}

#شامل "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#اگر_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
    خالی v_پورٹ_CPUAcquire_Mutex( پورٹ_MUX_TYPE * mux,
                               ثابت حرف * fnName,
                               صحیح سطر )
    {
        غیرعلامتی صحیح irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

        v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, پورٹ_MUX_NO_TIMEOUT, fnName, سطر );
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }

    bool v_پورٹ_CPUAcquire_Mutex_Timeout( پورٹ_MUX_TYPE * mux,
                                      صحیح timeout_ادوار,
                                      ثابت حرف * fnName,
                                      صحیح سطر )
    {
        غیرعلامتی صحیح irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
        bool نتیجہ = v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_ادوار, fnName, سطر );

        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
        واپس نتیجہ;
    }

#ورنہ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    خالی v_پورٹ_CPUAcquire_Mutex( پورٹ_MUX_TYPE * mux )
    {
        غیرعلامتی صحیح irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

        v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, پورٹ_MUX_NO_TIMEOUT );
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }

    bool v_پورٹ_CPUAcquire_Mutex_Timeout( پورٹ_MUX_TYPE * mux,
                                      صحیح timeout_ادوار )
    {
        غیرعلامتی صحیح irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
        bool نتیجہ = v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_ادوار );

        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
        واپس نتیجہ;
    }
#اگر_ختم /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#اگر_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
    خالی v_پورٹ_CPURelease_Mutex( پورٹ_MUX_TYPE * mux,
                               ثابت حرف * fnName,
                               صحیح سطر )
    {
        غیرعلامتی صحیح irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

        v_پورٹ_CPURelease_Mutex_Ints_Disabled( mux, fnName, سطر );
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }
#ورنہ
    خالی v_پورٹ_CPURelease_Mutex( پورٹ_MUX_TYPE * mux )
    {
        غیرعلامتی صحیح irq_حالت = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

        v_پورٹ_CPURelease_Mutex_Ints_Disabled( mux );
        پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( irq_حالت );
    }
#اگر_ختم /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#تعریف_کرو ڈھیر_WATCH_AREA_سائز       ( 32 )
#تعریف_کرو ڈھیر_WATCH_نقطہ_نمبر    ( SOC_CPU_WATCHPOINTS_عدد - 1 )

خالی v_پورٹ_سیٹ_ڈھیر_Watchpoint( خالی * px_ڈھیر_آغاز )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    صحیح addr = ( صحیح ) px_ڈھیر_آغاز;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_سیٹ_watchpoint( ڈھیر_WATCH_نقطہ_نمبر, ( حرف * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#اگر ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )

    #اگر defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        ساکن پورٹ_MUX_TYPE extram_mux = پورٹ_MUX_INITIALIZER_UNLOCKED;

        خالی ux_پورٹ_Compare_سیٹ_Extram( متلون uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * سیٹ )
        {
            uint32_t پچھلا_2;

            uint32_t oldlevel = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();

            #اگر_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, پورٹ_MUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #ورنہ
                v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, پورٹ_MUX_NO_TIMEOUT );
            #اگر_ختم
            پچھلا_2 = *addr;

            اگر( پچھلا_2 == compare )
            {
                *addr = *سیٹ;
            }

            *سیٹ = پچھلا_2;
            #اگر_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_پورٹ_CPURelease_Mutex_Ints_Disabled( &extram_mux, __FUNCTION__, __LINE__ );
            #ورنہ
                v_پورٹ_CPURelease_Mutex_Ints_Disabled( &extram_mux );
            #اگر_ختم

            پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( oldlevel );
        }
    #اگر_ختم //defined(CONFIG_SPIRAM_SUPPORT)

#اگر_ختم /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t x_پورٹ_Get_Tick_شرح_Hz( خالی )
{
    واپس ( uint32_t ) config_TICK_شرح_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#اگر CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_منوال
    #غلطی "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#اگر_ختم

خارجی خالی esp_startup_آغاز_app_common( خالی );

خالی esp_startup_آغاز_app( خالی )
{
    #اگر !CONFIG_ESP_INT_WDT
        #اگر CONFIG_ESP32_ECO3_CACHE_تالا_FIX
            أكد( !soc_has_cache_تالا_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #اگر_ختم
    #اگر_ختم

    esp_startup_آغاز_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    v_Task_آغاز_Scheduler();
}
