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

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <xtensa/config/core.h>

#অন্তর্ভাব "xtensa_rtos.h"
#অন্তর্ভাব "esp_idf_version.h"

#যদি ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
    #অন্তর্ভাব "rom/ets_sys.h"
    #অন্তর্ভাব "esp_panic.h"
    #অন্তর্ভাব "esp_crosscore_int.h"
#অন্যথা
    #যদি CONFIG_IDF_TARGET_ESP32S3
        #অন্তর্ভাব "esp32s3/rom/ets_sys.h"
    #নতুবা_যদি CONFIG_IDF_TARGET_ESP32S2
        #অন্তর্ভাব "esp32s2/rom/ets_sys.h"
    #নতুবা_যদি CONFIG_IDF_TARGET_ESP32
        #অন্তর্ভাব "esp32/rom/ets_sys.h"
    #endif
    #অন্তর্ভাব "esp_private/panic_reason.h"
    #অন্তর্ভাব "esp_debug_helpers.h"
    #অন্তর্ভাব "esp_private/crosscore_int.h"
    #অন্তর্ভাব "esp_log.h"
#endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#অন্তর্ভাব "soc/cpu.h"

#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

#অন্তর্ভাব "esp_heap_caps.h"

#অন্তর্ভাব "esp_intr_alloc.h"

#অন্তর্ভাব "port_systick.h"

/* Defined in xtensa_context.S */
বাহ্যিক শূন্য _xt_coproc_init( শূন্য );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

বাহ্যিক অস্থির পূর্ণসংখ্যা port_xSchedulerRunning[ port_অঙ্ক_PROCESSORS ];
unsigned port_interruptNesting[ port_অঙ্ক_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
শূন্য _xt_user_exit( শূন্য );

#যদি CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    স্থির শূন্য vPortTaskWrapper( TaskFunction_t pxCode,
                                  শূন্য * pvParameters )
    {
        pxCode( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        অক্ষর * pcTaskName = pcTaskGetTaskName( ফাঁকা );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#endif /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#যদি portUSING_MPU_WRAPPERS
    স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                         TaskFunction_t pxCode,
                                         শূন্য * pvParameters,
                                         BaseType_t xRunPrivileged )
#অন্যথা
    স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                         TaskFunction_t pxCode,
                                         শূন্য * pvParameters )
#endif
/* *INDENT-ON* */
{
    স্তূপ_Type_t * sp;
    স্তূপ_Type_t * tp;
    XtExcFrame * frame;

    #যদি XCHAL_CP_অঙ্ক > 0
        uint32_t * p;
    #endif

    uint32_t * threadptr;
    শূন্য * task_thread_local_start;
    বাহ্যিক পূর্ণসংখ্যা _thread_local_start, _thread_local_end, _flash_rodata_start, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &_thread_local_end - ( uint8_t * ) &_thread_local_start;

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
    sp = ( স্তূপ_Type_t * ) ( ( ( UBaseType_t ) px_শীর্ষ_Of_স্তূপ - XT_CP_আকার - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    জন্য( tp = sp; tp <= px_শীর্ষ_Of_স্তূপ; ++tp )
    {
        *tp = 0;
    }

    frame = ( XtExcFrame * ) sp;

    /* Explicitly initialize certain saved registers */
    #যদি CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        frame->pc = ( UBaseType_t ) vPortTaskWrapper; /* task wrapper                       */
    #অন্যথা
        frame->pc = ( UBaseType_t ) pxCode;           /* task entrypoint                    */
    #endif
    frame->a0 = 0;                                    /* to terminate GDB backtrace     */
    frame->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    frame->exit = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #ifdef __XTENSA_CALL0_ABI__
        #যদি CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a2 = ( UBaseType_t ) pxCode;
            frame->a3 = ( UBaseType_t ) pvParameters;
        #অন্যথা
            frame->a2 = ( UBaseType_t ) pvParameters;
        #endif
        frame->ps = PS_UM | PS_EXCM;
    #অন্যথা
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #যদি CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a6 = ( UBaseType_t ) pxCode;
            frame->a7 = ( UBaseType_t ) pvParameters;
        #অন্যথা
            frame->a6 = ( UBaseType_t ) pvParameters;
        #endif
        frame->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #endif /* ifdef __XTENSA_CALL0_ABI__ */

    #ifdef XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        frame->vpri = 0xFFFFFFFF;
    #endif

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_start = ( শূন্য * ) ( ( ( uint32_t ) px_শীর্ষ_Of_স্তূপ - XT_CP_আকার - thread_local_sz ) & ~0xf );
    memcpy( task_thread_local_start, &_thread_local_start, thread_local_sz );
    threadptr = ( uint32_t * ) ( sp + XT_STK_EXTRA );

    /* Calculate THREADPTR value.
     * The generated code will add THREADPTR value to a constant value determined at link time,
     * to get the address of the TLS variable.
     * The constant value is calculated by the linker as follows
     * (search for 'tpoff' in elf32-xtensa.c in BFD):
     *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
     * where TCB_SIZE is hardcoded to 8.
     */
    ধ্রুবক uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    ধ্রুবক uint32_t tcb_আকার = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ধ্রুবক uint32_t base = ( tcb_আকার + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_start - ( ( uint32_t ) &_thread_local_start - ( uint32_t ) &_flash_rodata_start ) - base;

    #যদি XCHAL_CP_অঙ্ক > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_শীর্ষ_Of_স্তূপ - XT_CP_আকার ) & ~0xf );
        configASSERT( ( uint32_t ) p >= frame->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_যোগ_SA_ALIGN - 1 ) & -XCHAL_যোগ_SA_ALIGN;
    #endif

    ফেরত sp;
}

/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    portDISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #যদি XCHAL_CP_অঙ্ক > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #endif

    /* Setup the hardware to generate the tick */
    vPortSetupTimer();

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
    portDISABLE_INTERRUPTS();

    port_xSchedulerRunning[ xPortGetCoreID() ] = 1;

    /* Cannot be directly called from C; never returns */
    __asm__ অস্থির ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    ফেরত pdTRUE;
}

/*-----------------------------------------------------------*/

শূন্য vPortYieldOtherCore( BaseType_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#যদি portUSING_MPU_WRAPPERS
    শূন্য vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ধ্রুবক কাঠামো xMEMORY_REGION * ধ্রুবক xRegions,
                                    স্তূপ_Type_t * px_Bottom_Of_স্তূপ,
                                    config_স্তূপ_DEPTH_TYPE ux_স্তূপ_Depth )
    {
        #যদি XCHAL_CP_অঙ্ক > 0
            xMPUSettings->coproc_area = ( স্তূপ_Type_t * ) ( ( uint32_t ) ( px_Bottom_Of_স্তূপ + ux_স্তূপ_Depth - 1 ) );
            xMPUSettings->coproc_area = ( স্তূপ_Type_t * ) ( ( ( port_POINTER_আকার_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( port_POINTER_আকার_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
            xMPUSettings->coproc_area = ( স্তূপ_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_আকার ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #endif
    }

    শূন্য vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#endif /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
BaseType_t xPortInIsrContext()
{
    unsigned পূর্ণসংখ্যা irqStatus;
    BaseType_t ret;

    irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    ret = ( port_interruptNesting[ xPortGetCoreID() ] != 0 );
    portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    ফেরত ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
BaseType_t IRAM_ATTR xPortInterruptedFromISRContext()
{
    ফেরত( port_interruptNesting[ xPortGetCoreID() ] != 0 );
}

শূন্য IRAM_ATTR vPortEvaluateYieldFromISR( পূর্ণসংখ্যা argc,
                                          ... )
{
    BaseType_t xYield;
    va_list ap;

    va_start( ap, argc );

    যদি( argc )
    {
        xYield = ( BaseType_t ) va_arg( ap, পূর্ণসংখ্যা );
        va_end( ap );
    }
    অন্যথা
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_end( ap );
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
        ফেরত;
    }

    /*Yield exists, so need evaluate it first then switch: */
    যদি( xYield == pdTRUE )
    {
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
    }
}

শূন্য vPortAssertIfInISR()
{
    যদি( xPortInIsrContext() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", xPortGetCoreID(), port_interruptNesting[ xPortGetCoreID() ] );
    }

    configASSERT( !xPortInIsrContext() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
শূন্য vPortCPUInitializeMutex( portMUX_TYPE * mux )
{
    #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->lastLockedFn = "(never locked)";
        mux->last_Locked_সারি = -1;
    #endif
    mux->owner = portMUX_FREE_VAL;
    mux->গুনতি = 0;
}

#অন্তর্ভাব "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    শূন্য vPortCPUAcquireMutex( portMUX_TYPE * mux,
                               ধ্রুবক অক্ষর * fnName,
                               পূর্ণসংখ্যা সারি )
    {
        unsigned পূর্ণসংখ্যা irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT, fnName, সারি );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      পূর্ণসংখ্যা timeout_cycles,
                                      ধ্রুবক অক্ষর * fnName,
                                      পূর্ণসংখ্যা সারি )
    {
        unsigned পূর্ণসংখ্যা irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool ফলাফল = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles, fnName, সারি );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        ফেরত ফলাফল;
    }

#অন্যথা /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    শূন্য vPortCPUAcquireMutex( portMUX_TYPE * mux )
    {
        unsigned পূর্ণসংখ্যা irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      পূর্ণসংখ্যা timeout_cycles )
    {
        unsigned পূর্ণসংখ্যা irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool ফলাফল = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        ফেরত ফলাফল;
    }
#endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    শূন্য vPortCPUReleaseMutex( portMUX_TYPE * mux,
                               ধ্রুবক অক্ষর * fnName,
                               পূর্ণসংখ্যা সারি )
    {
        unsigned পূর্ণসংখ্যা irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux, fnName, সারি );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#অন্যথা
    শূন্য vPortCPUReleaseMutex( portMUX_TYPE * mux )
    {
        unsigned পূর্ণসংখ্যা irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#define স্তূপ_WATCH_AREA_আকার       ( 32 )
#define স্তূপ_WATCH_POINT_সংখ্যা    ( SOC_CPU_WATCHPOINTS_অঙ্ক - 1 )

শূন্য v_Port_Set_স্তূপ_Watchpoint( শূন্য * px_স্তূপ_Start )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    পূর্ণসংখ্যা addr = ( পূর্ণসংখ্যা ) px_স্তূপ_Start;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_set_watchpoint( স্তূপ_WATCH_POINT_সংখ্যা, ( অক্ষর * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#যদি ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

    #যদি defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        স্থির portMUX_TYPE extram_mux = portMUX_INITIALIZER_UNLOCKED;

        শূন্য uxPortCompareSetExtram( অস্থির uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set )
        {
            uint32_t পূর্ব;

            uint32_t oldlevel = portSET_INTERRUPT_MASK_FROM_ISR();

            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #অন্যথা
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT );
            #endif
            পূর্ব = *addr;

            যদি( পূর্ব == compare )
            {
                *addr = *set;
            }

            *set = পূর্ব;
            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUReleaseMutexIntsDisabled( &extram_mux, __FUNCTION__, __LINE__ );
            #অন্যথা
                vPortCPUReleaseMutexIntsDisabled( &extram_mux );
            #endif

            portCLEAR_INTERRUPT_MASK_FROM_ISR( oldlevel );
        }
    #endif //defined(CONFIG_SPIRAM_SUPPORT)

#endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t xPortGetTickRateHz( শূন্য )
{
    ফেরত ( uint32_t ) configTICK_RATE_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#যদি CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

বাহ্যিক শূন্য esp_startup_start_app_common( শূন্য );

শূন্য esp_startup_start_app( শূন্য )
{
    #যদি !CONFIG_ESP_INT_WDT
        #যদি CONFIG_ESP32_ECO3_CACHE_LOCK_FIX
            প্রতিজ্ঞা( !soc_has_cache_lock_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #endif
    #endif

    esp_startup_start_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    vTaskStartScheduler();
}
