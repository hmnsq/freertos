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

#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <xtensa/config/core.h>

#அந்தர்பாவ "xtensa_rtos.h"
#அந்தர்பாவ "esp_idf_version.h"

#எனில் ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
    #அந்தர்பாவ "rom/ets_sys.h"
    #அந்தர்பாவ "esp_panic.h"
    #அந்தர்பாவ "esp_crosscore_int.h"
#இல்லையெனில்
    #எனில் CONFIG_IDF_TARGET_ESP32S3
        #அந்தர்பாவ "esp32s3/rom/ets_sys.h"
    #அல்லதெனில் CONFIG_IDF_TARGET_ESP32S2
        #அந்தர்பாவ "esp32s2/rom/ets_sys.h"
    #அல்லதெனில் CONFIG_IDF_TARGET_ESP32
        #அந்தர்பாவ "esp32/rom/ets_sys.h"
    #endif
    #அந்தர்பாவ "esp_private/panic_reason.h"
    #அந்தர்பாவ "esp_debug_helpers.h"
    #அந்தர்பாவ "esp_private/crosscore_int.h"
    #அந்தர்பாவ "esp_log.h"
#endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#அந்தர்பாவ "soc/cpu.h"

#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

#அந்தர்பாவ "esp_heap_caps.h"

#அந்தர்பாவ "esp_intr_alloc.h"

#அந்தர்பாவ "port_systick.h"

/* Defined in xtensa_context.S */
வெளி வெறுமை _xt_coproc_init( வெறுமை );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

வெளி நிலையற்ற முழு port_xSchedulerRunning[ port_இலக்கம்_PROCESSORS ];
unsigned port_interruptNesting[ port_இலக்கம்_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
வெறுமை _xt_user_exit( வெறுமை );

#எனில் CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    நிலையான வெறுமை vPortTaskWrapper( TaskFunction_t pxCode,
                                  வெறுமை * pvParameters )
    {
        pxCode( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        எழுத்து * pcTaskName = pcTaskGetTaskName( வெற்று );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#endif /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#எனில் portUSING_MPU_WRAPPERS
    அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                         TaskFunction_t pxCode,
                                         வெறுமை * pvParameters,
                                         BaseType_t xRunPrivileged )
#இல்லையெனில்
    அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                         TaskFunction_t pxCode,
                                         வெறுமை * pvParameters )
#endif
/* *INDENT-ON* */
{
    அடுக்கு_Type_t * sp;
    அடுக்கு_Type_t * tp;
    XtExcFrame * frame;

    #எனில் XCHAL_CP_இலக்கம் > 0
        uint32_t * p;
    #endif

    uint32_t * threadptr;
    வெறுமை * task_thread_local_start;
    வெளி முழு _thread_local_start, _thread_local_end, _flash_rodata_start, _flash_rodata_align;

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
    sp = ( அடுக்கு_Type_t * ) ( ( ( UBaseType_t ) px_உச்சி_Of_அடுக்கு - XT_CP_SIZE - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    க்கு( tp = sp; tp <= px_உச்சி_Of_அடுக்கு; ++tp )
    {
        *tp = 0;
    }

    frame = ( XtExcFrame * ) sp;

    /* Explicitly initialize certain saved registers */
    #எனில் CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        frame->pc = ( UBaseType_t ) vPortTaskWrapper; /* task wrapper                       */
    #இல்லையெனில்
        frame->pc = ( UBaseType_t ) pxCode;           /* task entrypoint                    */
    #endif
    frame->a0 = 0;                                    /* to terminate GDB backtrace     */
    frame->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    frame->exit = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #ifdef __XTENSA_CALL0_ABI__
        #எனில் CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a2 = ( UBaseType_t ) pxCode;
            frame->a3 = ( UBaseType_t ) pvParameters;
        #இல்லையெனில்
            frame->a2 = ( UBaseType_t ) pvParameters;
        #endif
        frame->ps = PS_UM | PS_EXCM;
    #இல்லையெனில்
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #எனில் CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a6 = ( UBaseType_t ) pxCode;
            frame->a7 = ( UBaseType_t ) pvParameters;
        #இல்லையெனில்
            frame->a6 = ( UBaseType_t ) pvParameters;
        #endif
        frame->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #endif /* ifdef __XTENSA_CALL0_ABI__ */

    #ifdef XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        frame->vpri = 0xFFFFFFFF;
    #endif

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_start = ( வெறுமை * ) ( ( ( uint32_t ) px_உச்சி_Of_அடுக்கு - XT_CP_SIZE - thread_local_sz ) & ~0xf );
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
    மாறிலி uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    மாறிலி uint32_t tcb_size = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    மாறிலி uint32_t base = ( tcb_size + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_start - ( ( uint32_t ) &_thread_local_start - ( uint32_t ) &_flash_rodata_start ) - base;

    #எனில் XCHAL_CP_இலக்கம் > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_உச்சி_Of_அடுக்கு - XT_CP_SIZE ) & ~0xf );
        configASSERT( ( uint32_t ) p >= frame->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_TOTAL_SA_ALIGN - 1 ) & -XCHAL_TOTAL_SA_ALIGN;
    #endif

    திரும்பு sp;
}

/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( வெறுமை )
{
    portDISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #எனில் XCHAL_CP_இலக்கம் > 0
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
    __asm__ நிலையற்ற ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    திரும்பு pdTRUE;
}

/*-----------------------------------------------------------*/

வெறுமை vPortYieldOtherCore( BaseType_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#எனில் portUSING_MPU_WRAPPERS
    வெறுமை vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    மாறிலி கட்டமைப்பு xMEMORY_REGION * மாறிலி xRegions,
                                    அடுக்கு_Type_t * px_Bottom_Of_அடுக்கு,
                                    config_அடுக்கு_DEPTH_TYPE ux_அடுக்கு_Depth )
    {
        #எனில் XCHAL_CP_இலக்கம் > 0
            xMPUSettings->coproc_area = ( அடுக்கு_Type_t * ) ( ( uint32_t ) ( px_Bottom_Of_அடுக்கு + ux_அடுக்கு_Depth - 1 ) );
            xMPUSettings->coproc_area = ( அடுக்கு_Type_t * ) ( ( ( portPOINTER_SIZE_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
            xMPUSettings->coproc_area = ( அடுக்கு_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_SIZE ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #endif
    }

    வெறுமை vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings )
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
    unsigned முழு irqStatus;
    BaseType_t ret;

    irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    ret = ( port_interruptNesting[ xPortGetCoreID() ] != 0 );
    portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    திரும்பு ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
BaseType_t IRAM_ATTR xPortInterruptedFromISRContext()
{
    திரும்பு( port_interruptNesting[ xPortGetCoreID() ] != 0 );
}

வெறுமை IRAM_ATTR vPortEvaluateYieldFromISR( முழு argc,
                                          ... )
{
    BaseType_t xYield;
    va_list ap;

    va_start( ap, argc );

    எனில்( argc )
    {
        xYield = ( BaseType_t ) va_arg( ap, முழு );
        va_end( ap );
    }
    இல்லையெனில்
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_end( ap );
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
        திரும்பு;
    }

    /*Yield exists, so need evaluate it first then switch: */
    எனில்( xYield == pdTRUE )
    {
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
    }
}

வெறுமை vPortAssertIfInISR()
{
    எனில்( xPortInIsrContext() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", xPortGetCoreID(), port_interruptNesting[ xPortGetCoreID() ] );
    }

    configASSERT( !xPortInIsrContext() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
வெறுமை vPortCPUInitializeMutex( portMUX_TYPE * mux )
{
    #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->lastLockedFn = "(never locked)";
        mux->last_Locked_வரி = -1;
    #endif
    mux->owner = portMUX_FREE_VAL;
    mux->மொத்தம் = 0;
}

#அந்தர்பாவ "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    வெறுமை vPortCPUAcquireMutex( portMUX_TYPE * mux,
                               மாறிலி எழுத்து * fnName,
                               முழு வரி )
    {
        unsigned முழு irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT, fnName, வரி );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      முழு timeout_cycles,
                                      மாறிலி எழுத்து * fnName,
                                      முழு வரி )
    {
        unsigned முழு irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool result = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles, fnName, வரி );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        திரும்பு result;
    }

#இல்லையெனில் /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    வெறுமை vPortCPUAcquireMutex( portMUX_TYPE * mux )
    {
        unsigned முழு irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      முழு timeout_cycles )
    {
        unsigned முழு irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool result = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        திரும்பு result;
    }
#endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    வெறுமை vPortCPUReleaseMutex( portMUX_TYPE * mux,
                               மாறிலி எழுத்து * fnName,
                               முழு வரி )
    {
        unsigned முழு irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux, fnName, வரி );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#இல்லையெனில்
    வெறுமை vPortCPUReleaseMutex( portMUX_TYPE * mux )
    {
        unsigned முழு irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#define அடுக்கு_WATCH_AREA_SIZE       ( 32 )
#define அடுக்கு_WATCH_POINT_எண்    ( SOC_CPU_WATCHPOINTS_இலக்கம் - 1 )

வெறுமை v_Port_Set_அடுக்கு_Watchpoint( வெறுமை * px_அடுக்கு_Start )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    முழு addr = ( முழு ) px_அடுக்கு_Start;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_set_watchpoint( அடுக்கு_WATCH_POINT_எண், ( எழுத்து * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#எனில் ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

    #எனில் defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        நிலையான portMUX_TYPE extram_mux = portMUX_INITIALIZER_UNLOCKED;

        வெறுமை uxPortCompareSetExtram( நிலையற்ற uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set )
        {
            uint32_t prev;

            uint32_t oldlevel = portSET_INTERRUPT_MASK_FROM_ISR();

            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #இல்லையெனில்
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT );
            #endif
            prev = *addr;

            எனில்( prev == compare )
            {
                *addr = *set;
            }

            *set = prev;
            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUReleaseMutexIntsDisabled( &extram_mux, __FUNCTION__, __LINE__ );
            #இல்லையெனில்
                vPortCPUReleaseMutexIntsDisabled( &extram_mux );
            #endif

            portCLEAR_INTERRUPT_MASK_FROM_ISR( oldlevel );
        }
    #endif //defined(CONFIG_SPIRAM_SUPPORT)

#endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t xPortGetTickRateHz( வெறுமை )
{
    திரும்பு ( uint32_t ) configTICK_RATE_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#எனில் CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

வெளி வெறுமை esp_startup_start_app_common( வெறுமை );

வெறுமை esp_startup_start_app( வெறுமை )
{
    #எனில் !CONFIG_ESP_INT_WDT
        #எனில் CONFIG_ESP32_ECO3_CACHE_LOCK_FIX
            ப்ரதிஜ்ஞா( !soc_has_cache_lock_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #endif
    #endif

    esp_startup_start_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    vTaskStartScheduler();
}
