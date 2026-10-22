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

#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <xtensa/config/core.h>

#समावेश "xtensa_rtos.h"
#समावेश "esp_idf_version.h"

#अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
    #समावेश "rom/ets_sys.h"
    #समावेश "esp_panic.h"
    #समावेश "esp_crosscore_int.h"
#अन्यथा
    #अगर CONFIG_IDF_TARGET_ESP32S3
        #समावेश "esp32s3/rom/ets_sys.h"
    #या_अगर CONFIG_IDF_TARGET_ESP32S2
        #समावेश "esp32s2/rom/ets_sys.h"
    #या_अगर CONFIG_IDF_TARGET_ESP32
        #समावेश "esp32/rom/ets_sys.h"
    #पूर्ण_अगर
    #समावेश "esp_private/panic_reason.h"
    #समावेश "esp_debug_helpers.h"
    #समावेश "esp_private/crosscore_int.h"
    #समावेश "esp_log.h"
#पूर्ण_अगर /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#समावेश "soc/cpu.h"

#समावेश "FreeRTOS.h"
#समावेश "task.h"

#समावेश "esp_heap_caps.h"

#समावेश "esp_intr_alloc.h"

#समावेश "port_systick.h"

/* Defined in xtensa_context.S */
बाह्य व्योम _xt_coproc_init( व्योम );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

बाह्य अस्थिर पूर्णांक port_xSchedulerRunning[ port_अंक_PROCESSORS ];
अचिन्हित port_interruptNesting[ port_अंक_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
व्योम _xt_user_exit( व्योम );

#अगर CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    अटल व्योम vPortTaskWrapper( TaskFunction_t pxCode,
                                  व्योम * pvParameters )
    {
        pxCode( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        अक्षर * pcTaskName = pcTaskGetTaskName( शून्य );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        पात();
    }
#पूर्ण_अगर /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#अगर portUSING_MPU_WRAPPERS
    ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                         TaskFunction_t pxCode,
                                         व्योम * pvParameters,
                                         BaseType_t xRunPrivileged )
#अन्यथा
    ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                         TaskFunction_t pxCode,
                                         व्योम * pvParameters )
#पूर्ण_अगर
/* *INDENT-ON* */
{
    ढेर_Type_t * sp;
    ढेर_Type_t * tp;
    XtExcFrame * frame;

    #अगर XCHAL_CP_अंक > 0
        uint32_t * p;
    #पूर्ण_अगर

    uint32_t * threadptr;
    व्योम * task_thread_local_start;
    बाह्य पूर्णांक _thread_local_start, _thread_local_end, _flash_rodata_start, _flash_rodata_align;

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
    sp = ( ढेर_Type_t * ) ( ( ( UBaseType_t ) px_शीर्ष_Of_ढेर - XT_CP_आकार - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    क्रम( tp = sp; tp <= px_शीर्ष_Of_ढेर; ++tp )
    {
        *tp = 0;
    }

    frame = ( XtExcFrame * ) sp;

    /* Explicitly initialize certain saved registers */
    #अगर CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        frame->pc = ( UBaseType_t ) vPortTaskWrapper; /* task wrapper                       */
    #अन्यथा
        frame->pc = ( UBaseType_t ) pxCode;           /* task entrypoint                    */
    #पूर्ण_अगर
    frame->a0 = 0;                                    /* to terminate GDB backtrace     */
    frame->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    frame->निकास = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #अगर_घोषित __XTENSA_CALL0_ABI__
        #अगर CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a2 = ( UBaseType_t ) pxCode;
            frame->a3 = ( UBaseType_t ) pvParameters;
        #अन्यथा
            frame->a2 = ( UBaseType_t ) pvParameters;
        #पूर्ण_अगर
        frame->ps = PS_UM | PS_EXCM;
    #अन्यथा
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #अगर CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a6 = ( UBaseType_t ) pxCode;
            frame->a7 = ( UBaseType_t ) pvParameters;
        #अन्यथा
            frame->a6 = ( UBaseType_t ) pvParameters;
        #पूर्ण_अगर
        frame->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #पूर्ण_अगर /* ifdef __XTENSA_CALL0_ABI__ */

    #अगर_घोषित XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        frame->vpri = 0xFFFFFFFF;
    #पूर्ण_अगर

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_start = ( व्योम * ) ( ( ( uint32_t ) px_शीर्ष_Of_ढेर - XT_CP_आकार - thread_local_sz ) & ~0xf );
    स_नकल( task_thread_local_start, &_thread_local_start, thread_local_sz );
    threadptr = ( uint32_t * ) ( sp + XT_STK_EXTRA );

    /* Calculate THREADPTR value.
     * The generated code will add THREADPTR value to a constant value determined at link time,
     * to get the address of the TLS variable.
     * The constant value is calculated by the linker as follows
     * (search for 'tpoff' in elf32-xtensa.c in BFD):
     *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
     * where TCB_SIZE is hardcoded to 8.
     */
    स्थिर uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    स्थिर uint32_t tcb_आकार = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    स्थिर uint32_t base = ( tcb_आकार + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_start - ( ( uint32_t ) &_thread_local_start - ( uint32_t ) &_flash_rodata_start ) - base;

    #अगर XCHAL_CP_अंक > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_शीर्ष_Of_ढेर - XT_CP_आकार ) & ~0xf );
        configASSERT( ( uint32_t ) p >= frame->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_योग_SA_ALIGN - 1 ) & -XCHAL_योग_SA_ALIGN;
    #पूर्ण_अगर

    वापस sp;
}

/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    पात();
}

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    portDISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #अगर XCHAL_CP_अंक > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #पूर्ण_अगर

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
    __asm__ अस्थिर ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    वापस pdTRUE;
}

/*-----------------------------------------------------------*/

व्योम vPortYieldOtherCore( BaseType_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#अगर portUSING_MPU_WRAPPERS
    व्योम vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    स्थिर काष्ठा xMEMORY_REGION * स्थिर xRegions,
                                    ढेर_Type_t * px_Bottom_Of_ढेर,
                                    config_ढेर_DEPTH_TYPE ux_ढेर_Depth )
    {
        #अगर XCHAL_CP_अंक > 0
            xMPUSettings->coproc_area = ( ढेर_Type_t * ) ( ( uint32_t ) ( px_Bottom_Of_ढेर + ux_ढेर_Depth - 1 ) );
            xMPUSettings->coproc_area = ( ढेर_Type_t * ) ( ( ( port_POINTER_आकार_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( port_POINTER_आकार_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
            xMPUSettings->coproc_area = ( ढेर_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_आकार ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #पूर्ण_अगर
    }

    व्योम vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#पूर्ण_अगर /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
BaseType_t xPortInIsrContext()
{
    अचिन्हित पूर्णांक irqStatus;
    BaseType_t ret;

    irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    ret = ( port_interruptNesting[ xPortGetCoreID() ] != 0 );
    portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    वापस ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
BaseType_t IRAM_ATTR xPortInterruptedFromISRContext()
{
    वापस( port_interruptNesting[ xPortGetCoreID() ] != 0 );
}

व्योम IRAM_ATTR vPortEvaluateYieldFromISR( पूर्णांक argc,
                                          ... )
{
    BaseType_t xYield;
    बहु_सूची ap;

    बहु_शुरू( ap, argc );

    अगर( argc )
    {
        xYield = ( BaseType_t ) बहु_तर्क( ap, पूर्णांक );
        बहु_पूर्ण( ap );
    }
    अन्यथा
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        बहु_पूर्ण( ap );
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
        वापस;
    }

    /*Yield exists, so need evaluate it first then switch: */
    अगर( xYield == pdTRUE )
    {
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
    }
}

व्योम vPortAssertIfInISR()
{
    अगर( xPortInIsrContext() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", xPortGetCoreID(), port_interruptNesting[ xPortGetCoreID() ] );
    }

    configASSERT( !xPortInIsrContext() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
व्योम vPortCPUInitializeMutex( portMUX_TYPE * mux )
{
    #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->lastLockedFn = "(never locked)";
        mux->last_Locked_पंक्ति = -1;
    #पूर्ण_अगर
    mux->owner = portMUX_FREE_VAL;
    mux->गिनती = 0;
}

#समावेश "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
    व्योम vPortCPUAcquireMutex( portMUX_TYPE * mux,
                               स्थिर अक्षर * fnName,
                               पूर्णांक पंक्ति )
    {
        अचिन्हित पूर्णांक irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT, fnName, पंक्ति );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      पूर्णांक timeout_cycles,
                                      स्थिर अक्षर * fnName,
                                      पूर्णांक पंक्ति )
    {
        अचिन्हित पूर्णांक irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool परिणाम = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles, fnName, पंक्ति );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        वापस परिणाम;
    }

#अन्यथा /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    व्योम vPortCPUAcquireMutex( portMUX_TYPE * mux )
    {
        अचिन्हित पूर्णांक irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      पूर्णांक timeout_cycles )
    {
        अचिन्हित पूर्णांक irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool परिणाम = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        वापस परिणाम;
    }
#पूर्ण_अगर /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
    व्योम vPortCPUReleaseMutex( portMUX_TYPE * mux,
                               स्थिर अक्षर * fnName,
                               पूर्णांक पंक्ति )
    {
        अचिन्हित पूर्णांक irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux, fnName, पंक्ति );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#अन्यथा
    व्योम vPortCPUReleaseMutex( portMUX_TYPE * mux )
    {
        अचिन्हित पूर्णांक irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#पूर्ण_अगर /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#घोषणा ढेर_WATCH_AREA_आकार       ( 32 )
#घोषणा ढेर_WATCH_POINT_संख्या    ( SOC_CPU_WATCHPOINTS_अंक - 1 )

व्योम v_Port_Set_ढेर_Watchpoint( व्योम * px_ढेर_Start )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    पूर्णांक addr = ( पूर्णांक ) px_ढेर_Start;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_set_watchpoint( ढेर_WATCH_POINT_संख्या, ( अक्षर * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

    #अगर defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        अटल portMUX_TYPE extram_mux = portMUX_INITIALIZER_UNLOCKED;

        व्योम uxPortCompareSetExtram( अस्थिर uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set )
        {
            uint32_t पूर्व;

            uint32_t oldlevel = portSET_INTERRUPT_MASK_FROM_ISR();

            #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #अन्यथा
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT );
            #पूर्ण_अगर
            पूर्व = *addr;

            अगर( पूर्व == compare )
            {
                *addr = *set;
            }

            *set = पूर्व;
            #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUReleaseMutexIntsDisabled( &extram_mux, __FUNCTION__, __LINE__ );
            #अन्यथा
                vPortCPUReleaseMutexIntsDisabled( &extram_mux );
            #पूर्ण_अगर

            portCLEAR_INTERRUPT_MASK_FROM_ISR( oldlevel );
        }
    #पूर्ण_अगर //defined(CONFIG_SPIRAM_SUPPORT)

#पूर्ण_अगर /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t xPortGetTickRateHz( व्योम )
{
    वापस ( uint32_t ) configTICK_RATE_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#अगर CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #त्रुटि "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#पूर्ण_अगर

बाह्य व्योम esp_startup_start_app_common( व्योम );

व्योम esp_startup_start_app( व्योम )
{
    #अगर !CONFIG_ESP_INT_WDT
        #अगर CONFIG_ESP32_ECO3_CACHE_LOCK_FIX
            निश्चित( !soc_has_cache_lock_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #पूर्ण_अगर
    #पूर्ण_अगर

    esp_startup_start_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    vTaskStartScheduler();
}
