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

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <xtensa/config/core.h>

#ಅನ್ತರ್ಭಾವ "xtensa_rtos.h"
#ಅನ್ತರ್ಭಾವ "esp_idf_version.h"

#ಯದಿ ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
    #ಅನ್ತರ್ಭಾವ "rom/ets_sys.h"
    #ಅನ್ತರ್ಭಾವ "esp_panic.h"
    #ಅನ್ತರ್ಭಾವ "esp_crosscore_int.h"
#ಅನ್ಯಥಾ
    #ಯದಿ CONFIG_IDF_TARGET_ESP32S3
        #ಅನ್ತರ್ಭಾವ "esp32s3/rom/ets_sys.h"
    #ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32S2
        #ಅನ್ತರ್ಭಾವ "esp32s2/rom/ets_sys.h"
    #ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32
        #ಅನ್ತರ್ಭಾವ "esp32/rom/ets_sys.h"
    #endif
    #ಅನ್ತರ್ಭಾವ "esp_private/panic_reason.h"
    #ಅನ್ತರ್ಭಾವ "esp_debug_helpers.h"
    #ಅನ್ತರ್ಭಾವ "esp_private/crosscore_int.h"
    #ಅನ್ತರ್ಭಾವ "esp_log.h"
#endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
#ಅನ್ತರ್ಭಾವ "soc/cpu.h"

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ಅನ್ತರ್ಭಾವ "esp_heap_caps.h"

#ಅನ್ತರ್ಭಾವ "esp_intr_alloc.h"

#ಅನ್ತರ್ಭಾವ "port_systick.h"

/* Defined in xtensa_context.S */
ಬಾಹ್ಯ ಶೂನ್ಯ _xt_coproc_init( ಶೂನ್ಯ );

_Static_assert( tskNO_AFFINITY == CONFIG_FREERTOS_NO_AFFINITY, "incorrect tskNO_AFFINITY value" );

/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ಚಞ್ಚಲ ಪೂರ್ಣಾಙ್ಕ port_xSchedulerRunning[ port_ಅಂಕೆ_PROCESSORS ];
unsigned port_interruptNesting[ port_ಅಂಕೆ_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
ಶೂನ್ಯ _xt_user_exit( ಶೂನ್ಯ );

#ಯದಿ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    ಸ್ಥಿರ ಶೂನ್ಯ vPortTaskWrapper( TaskFunction_t pxCode,
                                  ಶೂನ್ಯ * pvParameters )
    {
        pxCode( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        ವರ್ಣ * pcTaskName = pcTaskGetTaskName( ರಿಕ್ತ );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#endif /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#ಯದಿ portUSING_MPU_WRAPPERS
    ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                         TaskFunction_t pxCode,
                                         ಶೂನ್ಯ * pvParameters,
                                         BaseType_t xRunPrivileged )
#ಅನ್ಯಥಾ
    ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                         TaskFunction_t pxCode,
                                         ಶೂನ್ಯ * pvParameters )
#endif
/* *INDENT-ON* */
{
    ರಾಶಿ_Type_t * sp;
    ರಾಶಿ_Type_t * tp;
    XtExcFrame * frame;

    #ಯದಿ XCHAL_CP_ಅಂಕೆ > 0
        uint32_t * p;
    #endif

    uint32_t * threadptr;
    ಶೂನ್ಯ * task_thread_local_start;
    ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ _thread_local_start, _thread_local_end, _flash_rodata_start, _flash_rodata_align;

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
    sp = ( ರಾಶಿ_Type_t * ) ( ( ( UBaseType_t ) px_ತುದಿ_Of_ರಾಶಿ - XT_CP_SIZE - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    ಪ್ರತಿ( tp = sp; tp <= px_ತುದಿ_Of_ರಾಶಿ; ++tp )
    {
        *tp = 0;
    }

    frame = ( XtExcFrame * ) sp;

    /* Explicitly initialize certain saved registers */
    #ಯದಿ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        frame->pc = ( UBaseType_t ) vPortTaskWrapper; /* task wrapper                       */
    #ಅನ್ಯಥಾ
        frame->pc = ( UBaseType_t ) pxCode;           /* task entrypoint                    */
    #endif
    frame->a0 = 0;                                    /* to terminate GDB backtrace     */
    frame->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    frame->exit = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #ifdef __XTENSA_CALL0_ABI__
        #ಯದಿ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a2 = ( UBaseType_t ) pxCode;
            frame->a3 = ( UBaseType_t ) pvParameters;
        #ಅನ್ಯಥಾ
            frame->a2 = ( UBaseType_t ) pvParameters;
        #endif
        frame->ps = PS_UM | PS_EXCM;
    #ಅನ್ಯಥಾ
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #ಯದಿ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            frame->a6 = ( UBaseType_t ) pxCode;
            frame->a7 = ( UBaseType_t ) pvParameters;
        #ಅನ್ಯಥಾ
            frame->a6 = ( UBaseType_t ) pvParameters;
        #endif
        frame->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #endif /* ifdef __XTENSA_CALL0_ABI__ */

    #ifdef XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        frame->vpri = 0xFFFFFFFF;
    #endif

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_start = ( ಶೂನ್ಯ * ) ( ( ( uint32_t ) px_ತುದಿ_Of_ರಾಶಿ - XT_CP_SIZE - thread_local_sz ) & ~0xf );
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
    ಧ್ರುವ uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    ಧ್ರುವ uint32_t tcb_size = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ಧ್ರುವ uint32_t base = ( tcb_size + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_start - ( ( uint32_t ) &_thread_local_start - ( uint32_t ) &_flash_rodata_start ) - base;

    #ಯದಿ XCHAL_CP_ಅಂಕೆ > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_ತುದಿ_Of_ರಾಶಿ - XT_CP_SIZE ) & ~0xf );
        configASSERT( ( uint32_t ) p >= frame->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_TOTAL_SA_ALIGN - 1 ) & -XCHAL_TOTAL_SA_ALIGN;
    #endif

    ಪ್ರತ್ಯಾಗಮ sp;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    portDISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #ಯದಿ XCHAL_CP_ಅಂಕೆ > 0
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
    __asm__ ಚಞ್ಚಲ ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    ಪ್ರತ್ಯಾಗಮ pdTRUE;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortYieldOtherCore( BaseType_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#ಯದಿ portUSING_MPU_WRAPPERS
    ಶೂನ್ಯ vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ಧ್ರುವ ಸಂರಚನಾ xMEMORY_REGION * ಧ್ರುವ xRegions,
                                    ರಾಶಿ_Type_t * px_Bottom_Of_ರಾಶಿ,
                                    config_ರಾಶಿ_DEPTH_TYPE ux_ರಾಶಿ_Depth )
    {
        #ಯದಿ XCHAL_CP_ಅಂಕೆ > 0
            xMPUSettings->coproc_area = ( ರಾಶಿ_Type_t * ) ( ( uint32_t ) ( px_Bottom_Of_ರಾಶಿ + ux_ರಾಶಿ_Depth - 1 ) );
            xMPUSettings->coproc_area = ( ರಾಶಿ_Type_t * ) ( ( ( portPOINTER_SIZE_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
            xMPUSettings->coproc_area = ( ರಾಶಿ_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_SIZE ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #endif
    }

    ಶೂನ್ಯ vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings )
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
    unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus;
    BaseType_t ret;

    irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    ret = ( port_interruptNesting[ xPortGetCoreID() ] != 0 );
    portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    ಪ್ರತ್ಯಾಗಮ ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
BaseType_t IRAM_ATTR xPortInterruptedFromISRContext()
{
    ಪ್ರತ್ಯಾಗಮ( port_interruptNesting[ xPortGetCoreID() ] != 0 );
}

ಶೂನ್ಯ IRAM_ATTR vPortEvaluateYieldFromISR( ಪೂರ್ಣಾಙ್ಕ argc,
                                          ... )
{
    BaseType_t xYield;
    va_list ap;

    va_start( ap, argc );

    ಯದಿ( argc )
    {
        xYield = ( BaseType_t ) va_arg( ap, ಪೂರ್ಣಾಙ್ಕ );
        va_end( ap );
    }
    ಅನ್ಯಥಾ
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_end( ap );
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
        ಪ್ರತ್ಯಾಗಮ;
    }

    /*Yield exists, so need evaluate it first then switch: */
    ಯದಿ( xYield == pdTRUE )
    {
        traceISR_EXIT_TO_SCHEDULER();
        _frxt_setup_switch();
    }
}

ಶೂನ್ಯ vPortAssertIfInISR()
{
    ಯದಿ( xPortInIsrContext() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", xPortGetCoreID(), port_interruptNesting[ xPortGetCoreID() ] );
    }

    configASSERT( !xPortInIsrContext() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
ಶೂನ್ಯ vPortCPUInitializeMutex( portMUX_TYPE * mux )
{
    #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->lastLockedFn = "(never locked)";
        mux->last_Locked_ಸಾಲು = -1;
    #endif
    mux->owner = portMUX_FREE_VAL;
    mux->ಎಣಿಕೆ = 0;
}

#ಅನ್ತರ್ಭಾವ "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    ಶೂನ್ಯ vPortCPUAcquireMutex( portMUX_TYPE * mux,
                               ಧ್ರುವ ವರ್ಣ * fnName,
                               ಪೂರ್ಣಾಙ್ಕ ಸಾಲು )
    {
        unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT, fnName, ಸಾಲು );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      ಪೂರ್ಣಾಙ್ಕ timeout_cycles,
                                      ಧ್ರುವ ವರ್ಣ * fnName,
                                      ಪೂರ್ಣಾಙ್ಕ ಸಾಲು )
    {
        unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool result = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles, fnName, ಸಾಲು );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        ಪ್ರತ್ಯಾಗಮ result;
    }

#ಅನ್ಯಥಾ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    ಶೂನ್ಯ vPortCPUAcquireMutex( portMUX_TYPE * mux )
    {
        unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUAcquireMutexIntsDisabled( mux, portMUX_NO_TIMEOUT );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }

    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      ಪೂರ್ಣಾಙ್ಕ timeout_cycles )
    {
        unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        bool result = vPortCPUAcquireMutexIntsDisabled( mux, timeout_cycles );

        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
        ಪ್ರತ್ಯಾಗಮ result;
    }
#endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    ಶೂನ್ಯ vPortCPUReleaseMutex( portMUX_TYPE * mux,
                               ಧ್ರುವ ವರ್ಣ * fnName,
                               ಪೂರ್ಣಾಙ್ಕ ಸಾಲು )
    {
        unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux, fnName, ಸಾಲು );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#ಅನ್ಯಥಾ
    ಶೂನ್ಯ vPortCPUReleaseMutex( portMUX_TYPE * mux )
    {
        unsigned ಪೂರ್ಣಾಙ್ಕ irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();

        vPortCPUReleaseMutexIntsDisabled( mux );
        portCLEAR_INTERRUPT_MASK_FROM_ISR( irqStatus );
    }
#endif /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#define ರಾಶಿ_WATCH_AREA_SIZE       ( 32 )
#define ರಾಶಿ_WATCH_POINT_ಸಂಖ್ಯೆ    ( SOC_CPU_WATCHPOINTS_ಅಂಕೆ - 1 )

ಶೂನ್ಯ v_Port_Set_ರಾಶಿ_Watchpoint( ಶೂನ್ಯ * px_ರಾಶಿ_Start )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    ಪೂರ್ಣಾಙ್ಕ addr = ( ಪೂರ್ಣಾಙ್ಕ ) px_ರಾಶಿ_Start;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_set_watchpoint( ರಾಶಿ_WATCH_POINT_ಸಂಖ್ಯೆ, ( ವರ್ಣ * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#ಯದಿ ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

    #ಯದಿ defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        ಸ್ಥಿರ portMUX_TYPE extram_mux = portMUX_INITIALIZER_UNLOCKED;

        ಶೂನ್ಯ uxPortCompareSetExtram( ಚಞ್ಚಲ uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set )
        {
            uint32_t prev;

            uint32_t oldlevel = portSET_INTERRUPT_MASK_FROM_ISR();

            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #ಅನ್ಯಥಾ
                vPortCPUAcquireMutexIntsDisabled( &extram_mux, portMUX_NO_TIMEOUT );
            #endif
            prev = *addr;

            ಯದಿ( prev == compare )
            {
                *addr = *set;
            }

            *set = prev;
            #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
                vPortCPUReleaseMutexIntsDisabled( &extram_mux, __FUNCTION__, __LINE__ );
            #ಅನ್ಯಥಾ
                vPortCPUReleaseMutexIntsDisabled( &extram_mux );
            #endif

            portCLEAR_INTERRUPT_MASK_FROM_ISR( oldlevel );
        }
    #endif //defined(CONFIG_SPIRAM_SUPPORT)

#endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t xPortGetTickRateHz( ಶೂನ್ಯ )
{
    ಪ್ರತ್ಯಾಗಮ ( uint32_t ) configTICK_RATE_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ಯದಿ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

ಬಾಹ್ಯ ಶೂನ್ಯ esp_startup_start_app_common( ಶೂನ್ಯ );

ಶೂನ್ಯ esp_startup_start_app( ಶೂನ್ಯ )
{
    #ಯದಿ !CONFIG_ESP_INT_WDT
        #ಯದಿ CONFIG_ESP32_ECO3_CACHE_LOCK_FIX
            ಪ್ರತಿಜ್ಞಾ( !soc_has_cache_lock_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #endif
    #endif

    esp_startup_start_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    vTaskStartScheduler();
}
