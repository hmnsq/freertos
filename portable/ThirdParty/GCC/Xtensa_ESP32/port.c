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

#ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
    #ಅನ್ತರ್ಭಾವ "rom/ets_sys.h"
    #ಅನ್ತರ್ಭಾವ "esp_panic.h"
    #ಅನ್ತರ್ಭಾವ "esp_crosscore_int.h"
#ಇಲ್ಲದಿದ್ದರೆ
    #ಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_S3
        #ಅನ್ತರ್ಭಾವ "esp32s3/rom/ets_sys.h"
    #ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_S2
        #ಅನ್ತರ್ಭಾವ "esp32s2/rom/ets_sys.h"
    #ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32
        #ಅನ್ತರ್ಭಾವ "esp32/rom/ets_sys.h"
    #ಆದರೆ_ಅಂತ್ಯ
    #ಅನ್ತರ್ಭಾವ "esp_private/panic_reason.h"
    #ಅನ್ತರ್ಭಾವ "esp_debug_helpers.h"
    #ಅನ್ತರ್ಭಾವ "esp_private/crosscore_int.h"
    #ಅನ್ತರ್ಭಾವ "esp_log.h"
#ಆದರೆ_ಅಂತ್ಯ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */
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

ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಪೋರ್ಟ್_x_Scheduler_Running[ ಪೋರ್ಟ್_ಅಂಕೆ_PROCESSORS ];
ಚಿಹ್ನೆರಹಿತ ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting[ ಪೋರ್ಟ್_ಅಂಕೆ_PROCESSORS ] = { 0 }; /* Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit */

/*-----------------------------------------------------------*/

/* User exception dispatcher when exiting */
ಶೂನ್ಯ _xt_user_exit( ಶೂನ್ಯ );

#ಆದರೆ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
/* Wrapper to allow task functions to return (increases stack overhead by 16 bytes) */
    ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_Wrapper( TaskFunction_t px_ಸಂಕೇತ,
                                  ಶೂನ್ಯ * pvParameters )
    {
        px_ಸಂಕೇತ( pvParameters );
        /*FreeRTOS tasks should not return. Log the task name and abort. */
        ಅಕ್ಷರ * pcTaskName = pcTaskGetTaskName( ಖಾಲಿ );
        ESP_LOGE( "FreeRTOS", "FreeRTOS Task \"%s\" should not return, Aborting now!", pcTaskName );
        abort();
    }
#ಆದರೆ_ಅಂತ್ಯ /* if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER */

/*
 * Stack initialization
 */
/* *INDENT-OFF* */
#ಆದರೆ ಪೋರ್ಟ್_USING_MPU_WRAPPERS
    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters,
                                         ತಳ_Type_t x_ಸತತ_Privileged )
#ಇಲ್ಲದಿದ್ದರೆ
    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters )
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */
{
    ರಾಶಿ_Type_t * sp;
    ರಾಶಿ_Type_t * tp;
    Xt_Exc_ಚೌಕಟ್ಟು * ಚೌಕಟ್ಟು_2;

    #ಆದರೆ XCHAL_CP_ಅಂಕೆ > 0
        uint32_t * p;
    #ಆದರೆ_ಅಂತ್ಯ

    uint32_t * threadptr;
    ಶೂನ್ಯ * task_thread_local_ಆರಂಭ;
    ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ thread_local_ಆರಂಭ, thread_local_ಕೊನೆ, flash_rodata_ಆರಂಭ, _flash_rodata_align;

    /* TODO: check that TLS area fits the stack */
    uint32_t thread_local_sz = ( uint8_t * ) &thread_local_ಕೊನೆ - ( uint8_t * ) &thread_local_ಆರಂಭ;

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
    sp = ( ರಾಶಿ_Type_t * ) ( ( ( UBaseType_t ) px_ತುದಿ_ದ_ರಾಶಿ - XT_CP_ಗಾತ್ರ - thread_local_sz - XT_STK_FRMSZ ) & ~0xf );

    /* Clear the entire frame (do not use memset() because we don't depend on C library) */
    ಗಾಗಿ( tp = sp; tp <= px_ತುದಿ_ದ_ರಾಶಿ; ++tp )
    {
        *tp = 0;
    }

    ಚೌಕಟ್ಟು_2 = ( Xt_Exc_ಚೌಕಟ್ಟು * ) sp;

    /* Explicitly initialize certain saved registers */
    #ಆದರೆ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
        ಚೌಕಟ್ಟು_2->pc = ( UBaseType_t ) v_ಪೋರ್ಟ್_Task_Wrapper; /* task wrapper                       */
    #ಇಲ್ಲದಿದ್ದರೆ
        ಚೌಕಟ್ಟು_2->pc = ( UBaseType_t ) px_ಸಂಕೇತ;           /* task entrypoint                    */
    #ಆದರೆ_ಅಂತ್ಯ
    ಚೌಕಟ್ಟು_2->a0 = 0;                                    /* to terminate GDB backtrace     */
    ಚೌಕಟ್ಟು_2->a1 = ( UBaseType_t ) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
    ಚೌಕಟ್ಟು_2->ನಿರ್ಗಮಿಸು = ( UBaseType_t ) _xt_user_exit;      /* user exception exit dispatcher */

    /* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
    /* Also set entry point argument parameter. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __XTENSA_CALL0_ABI__
        #ಆದರೆ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            ಚೌಕಟ್ಟು_2->a2 = ( UBaseType_t ) px_ಸಂಕೇತ;
            ಚೌಕಟ್ಟು_2->a3 = ( UBaseType_t ) pvParameters;
        #ಇಲ್ಲದಿದ್ದರೆ
            ಚೌಕಟ್ಟು_2->a2 = ( UBaseType_t ) pvParameters;
        #ಆದರೆ_ಅಂತ್ಯ
        ಚೌಕಟ್ಟು_2->ps = PS_UM | PS_EXCM;
    #ಇಲ್ಲದಿದ್ದರೆ
        /* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
        #ಆದರೆ CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
            ಚೌಕಟ್ಟು_2->a6 = ( UBaseType_t ) px_ಸಂಕೇತ;
            ಚೌಕಟ್ಟು_2->a7 = ( UBaseType_t ) pvParameters;
        #ಇಲ್ಲದಿದ್ದರೆ
            ಚೌಕಟ್ಟು_2->a6 = ( UBaseType_t ) pvParameters;
        #ಆದರೆ_ಅಂತ್ಯ
        ಚೌಕಟ್ಟು_2->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC( 1 );
    #ಆದರೆ_ಅಂತ್ಯ /* ifdef __XTENSA_CALL0_ABI__ */

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XT_USE_SWPRI
        /* Set the initial virtual priority mask value to all 1's. */
        ಚೌಕಟ್ಟು_2->vpri = 0xFFFFFFFF;
    #ಆದರೆ_ಅಂತ್ಯ

    /* Init threadptr register and set up TLS run-time area. */
    task_thread_local_ಆರಂಭ = ( ಶೂನ್ಯ * ) ( ( ( uint32_t ) px_ತುದಿ_ದ_ರಾಶಿ - XT_CP_ಗಾತ್ರ - thread_local_sz ) & ~0xf );
    ಸ್ಮರಣೆ_ನಕಲು( task_thread_local_ಆರಂಭ, &thread_local_ಆರಂಭ, thread_local_sz );
    threadptr = ( uint32_t * ) ( sp + XT_STK_EXTRA );

    /* Calculate THREADPTR value.
     * The generated code will add THREADPTR value to a constant value determined at link time,
     * to get the address of the TLS variable.
     * The constant value is calculated by the linker as follows
     * (search for 'tpoff' in elf32-xtensa.c in BFD):
     *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
     * where TCB_SIZE is hardcoded to 8.
     */
    ಸ್ಥಿರಾಂಕ uint32_t tls_section_alignment = ( uint32_t ) &_flash_rodata_align; /* ALIGN value of .flash.rodata section */
    ಸ್ಥಿರಾಂಕ uint32_t tcb_ಗಾತ್ರ = 8;                                              /* Unrelated to FreeRTOS, this is the constant from BFD */
    ಸ್ಥಿರಾಂಕ uint32_t ತಳ = ( tcb_ಗಾತ್ರ + tls_section_alignment - 1 ) & ( ~( tls_section_alignment - 1 ) );
    *threadptr = ( uint32_t ) task_thread_local_ಆರಂಭ - ( ( uint32_t ) &thread_local_ಆರಂಭ - ( uint32_t ) &flash_rodata_ಆರಂಭ ) - ತಳ;

    #ಆದರೆ XCHAL_CP_ಅಂಕೆ > 0
        /* Init the coprocessor save area (see xtensa_context.h) */

        /* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
         * //p = (uint32_t *) xMPUSettings->coproc_area;
         */
        p = ( uint32_t * ) ( ( ( uint32_t ) px_ತುದಿ_ದ_ರಾಶಿ - XT_CP_ಗಾತ್ರ ) & ~0xf );
        configASSERT( ( uint32_t ) p >= ಚೌಕಟ್ಟು_2->a1 );
        p[ 0 ] = 0;
        p[ 1 ] = 0;
        p[ 2 ] = ( ( ( uint32_t ) p ) + 12 + XCHAL_ಒಟ್ಟು_SA_ALIGN - 1 ) & -XCHAL_ಒಟ್ಟು_SA_ALIGN;
    #ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ sp;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* It is unlikely that the Xtensa port will get stopped.  If required simply
     * disable the tick interrupt here. */
    abort();
}

/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    /* Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored */

    #ಆದರೆ XCHAL_CP_ಅಂಕೆ > 0
        /* Initialize co-processor management for tasks. Leave CPENABLE alone. */
        _xt_coproc_init();
    #ಆದರೆ_ಅಂತ್ಯ

    /* Setup the hardware to generate the tick */
    v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer();

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
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಪೋರ್ಟ್_x_Scheduler_Running[ x_ಪೋರ್ಟ್_Get_Core_ID() ] = 1;

    /* Cannot be directly called from C; never returns */
    __asm__ ಅಸ್ಥಿರ ( "call0    _frxt_dispatch\n" );

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ pdTRUE;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Other_Core( ತಳ_Type_t coreid )
{
    esp_crosscore_int_send_yield( coreid );
}

/*-----------------------------------------------------------*/

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#ಆದರೆ ಪೋರ್ಟ್_USING_MPU_WRAPPERS
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                    ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                    config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ )
    {
        #ಆದರೆ XCHAL_CP_ಅಂಕೆ > 0
            xMPUSettings->coproc_area = ( ರಾಶಿ_Type_t * ) ( ( uint32_t ) ( px_Bottom_ದ_ರಾಶಿ + ux_ರಾಶಿ_ಆಳ - 1 ) );
            xMPUSettings->coproc_area = ( ರಾಶಿ_Type_t * ) ( ( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );
            xMPUSettings->coproc_area = ( ರಾಶಿ_Type_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_ಗಾತ್ರ ) & ~0xf );

            /* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
             * clear the stack area after we return. This is done in pxPortInitialiseStack().
             */
        #ಆದರೆ_ಅಂತ್ಯ
    }

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings )
    {
        /* If task has live floating point registers somewhere, release them */
        _xt_coproc_release( xMPUSettings->coproc_area );
    }

#ಆದರೆ_ಅಂತ್ಯ /* if portUSING_MPU_WRAPPERS */

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಒಳ_Isr_Context()
{
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ;
    ತಳ_Type_t ret;

    irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    ret = ( ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting[ x_ಪೋರ್ಟ್_Get_Core_ID() ] != 0 );
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
    ಹಿಂತಿರುಗಿ ret;
}

/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
ತಳ_Type_t IRAM_ATTR x_ಪೋರ್ಟ್_Interrupted_From_ISRContext()
{
    ಹಿಂತಿರುಗಿ( ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting[ x_ಪೋರ್ಟ್_Get_Core_ID() ] != 0 );
}

ಶೂನ್ಯ IRAM_ATTR v_ಪೋರ್ಟ್_Evaluate_Yield_From_ISR( ಪೂರ್ಣಾಂಕ argc,
                                          ... )
{
    ತಳ_Type_t xYield;
    va_list ap;

    va_ಆರಂಭ( ap, argc );

    ಆದರೆ( argc )
    {
        xYield = ( ತಳ_Type_t ) va_arg( ap, ಪೂರ್ಣಾಂಕ );
        va_ಕೊನೆ( ap );
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        /*it is a empty parameter vPortYieldFromISR macro call: */
        va_ಕೊನೆ( ap );
        trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
        frxt_ಸಿದ್ಧತೆ_switch();
        ಹಿಂತಿರುಗಿ;
    }

    /*Yield exists, so need evaluate it first then switch: */
    ಆದರೆ( xYield == pdTRUE )
    {
        trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
        frxt_ಸಿದ್ಧತೆ_switch();
    }
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Assert_If_ಒಳ_ISR()
{
    ಆದರೆ( x_ಪೋರ್ಟ್_ಒಳ_Isr_Context() )
    {
        esp_rom_printf( "core=%d port_interruptNesting=%d\n\n", x_ಪೋರ್ಟ್_Get_Core_ID(), ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting[ x_ಪೋರ್ಟ್_Get_Core_ID() ] );
    }

    configASSERT( !x_ಪೋರ್ಟ್_ಒಳ_Isr_Context() );
}

/*
 * For kernel use: Initialize a per-CPU mux. Mux will be initialized unlocked.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPUInitialize_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux )
{
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
        esp_rom_printf( "Initializing mux %p\n", mux );
        mux->ಕೊನೆಯ_Locked_Fn = "(never locked)";
        mux->ಕೊನೆಯ_Locked_ಸಾಲು = -1;
    #ಆದರೆ_ಅಂತ್ಯ
    mux->owner = ಪೋರ್ಟ್_MUX_FREE_VAL;
    mux->ಎಣಿಕೆ_2 = 0;
}

#ಅನ್ತರ್ಭಾವ "portmux_impl.h"

/*
 * For kernel use: Acquire a per-CPU mux. Spinlocks, so don't hold on to these muxes for too long.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPUAcquire_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux,
                               ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName,
                               ಪೂರ್ಣಾಂಕ ಸಾಲು )
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( mux, ಪೋರ್ಟ್_MUX_NO_TIMEOUT, fnName, ಸಾಲು );
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
    }

    bool v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Timeout( ಪೋರ್ಟ್_MUX_TYPE * mux,
                                      ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName,
                                      ಪೂರ್ಣಾಂಕ ಸಾಲು )
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
        bool ಫಲಿತಾಂಶ = v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_ಚಕ್ರಗಳು, fnName, ಸಾಲು );

        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

#ಇಲ್ಲದಿದ್ದರೆ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPUAcquire_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux )
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( mux, ಪೋರ್ಟ್_MUX_NO_TIMEOUT );
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
    }

    bool v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Timeout( ಪೋರ್ಟ್_MUX_TYPE * mux,
                                      ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು )
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
        bool ಫಲಿತಾಂಶ = v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( mux, timeout_ಚಕ್ರಗಳು );

        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }
#ಆದರೆ_ಅಂತ್ಯ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */


/*
 * For kernel use: Release a per-CPU mux
 *
 * Mux must be already locked by this core
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPURelease_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux,
                               ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName,
                               ಪೂರ್ಣಾಂಕ ಸಾಲು )
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled( mux, fnName, ಸಾಲು );
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPURelease_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux )
    {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ irq_ಸ್ಥಿತಿ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

        v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled( mux );
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( irq_ಸ್ಥಿತಿ );
    }
#ಆದರೆ_ಅಂತ್ಯ /* ifdef CONFIG_FREERTOS_PORTMUX_DEBUG */

#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_WATCH_AREA_ಗಾತ್ರ       ( 32 )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_WATCH_ಬಿಂದು_ಸಂಖ್ಯೆ    ( SOC_CPU_WATCHPOINTS_ಅಂಕೆ - 1 )

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಗಣ_ರಾಶಿ_Watchpoint( ಶೂನ್ಯ * px_ರಾಶಿ_ಆರಂಭ )
{
    /*Set watchpoint 1 to watch the last 32 bytes of the stack. */
    /*Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because */
    /*the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32 */
    /*bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most */
    /*28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes. */
    /*This way, we make sure we trigger before/when the stack canary is corrupted, not after. */
    ಪೂರ್ಣಾಂಕ addr = ( ಪೂರ್ಣಾಂಕ ) px_ರಾಶಿ_ಆರಂಭ;

    addr = ( addr + 31 ) & ( ~31 );
    esp_cpu_ಗಣ_watchpoint( ರಾಶಿ_WATCH_ಬಿಂದು_ಸಂಖ್ಯೆ, ( ಅಕ್ಷರ * ) addr, 32, ESP_WATCHPOINT_STORE );
}

#ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )

    #ಆದರೆ defined( CONFIG_SPIRAM_SUPPORT )

/*
 * Compare & set (S32C1) does not work in external RAM. Instead, this routine uses a mux (in internal memory) to fake it.
 */
        ಸ್ಥಿರ ಪೋರ್ಟ್_MUX_TYPE extram_mux = ಪೋರ್ಟ್_MUX_INITIALIZER_UNLOCKED;

        ಶೂನ್ಯ ux_ಪೋರ್ಟ್_Compare_ಗಣ_Extram( ಅಸ್ಥಿರ uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * ಗಣ )
        {
            uint32_t prev;

            uint32_t oldlevel = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

            #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, ಪೋರ್ಟ್_MUX_NO_TIMEOUT, __FUNCTION__, __LINE__ );
            #ಇಲ್ಲದಿದ್ದರೆ
                v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( &extram_mux, ಪೋರ್ಟ್_MUX_NO_TIMEOUT );
            #ಆದರೆ_ಅಂತ್ಯ
            prev = *addr;

            ಆದರೆ( prev == compare )
            {
                *addr = *ಗಣ;
            }

            *ಗಣ = prev;
            #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
                v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled( &extram_mux, __FUNCTION__, __LINE__ );
            #ಇಲ್ಲದಿದ್ದರೆ
                v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled( &extram_mux );
            #ಆದರೆ_ಅಂತ್ಯ

            ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( oldlevel );
        }
    #ಆದರೆ_ಅಂತ್ಯ //defined(CONFIG_SPIRAM_SUPPORT)

#ಆದರೆ_ಅಂತ್ಯ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */


uint32_t x_ಪೋರ್ಟ್_Get_Tick_ದರ_Hz( ಶೂನ್ಯ )
{
    ಹಿಂತಿರುಗಿ ( uint32_t ) config_TICK_ದರ_HZ;
}

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ಆದರೆ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_ಬಹುಲಕ
    #ದೋಷ "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ ಶೂನ್ಯ esp_startup_ಆರಂಭ_app_common( ಶೂನ್ಯ );

ಶೂನ್ಯ esp_startup_ಆರಂಭ_app( ಶೂನ್ಯ )
{
    #ಆದರೆ !CONFIG_ESP_INT_WDT
        #ಆದರೆ CONFIG_ESP32_ECO3_CACHE_ಬೀಗ_FIX
            ಪ್ರತಿಜ್ಞಾ( !soc_has_cache_ಬೀಗ_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!" );
        #ಆದರೆ_ಅಂತ್ಯ
    #ಆದರೆ_ಅಂತ್ಯ

    esp_startup_ಆರಂಭ_app_common();

    ESP_LOGI( "cpu_start", "Starting scheduler on PRO CPU." );
    v_Task_ಆರಂಭ_Scheduler();
}
