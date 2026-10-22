/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#অন্তর্ভাব <string.h>
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "portmacro.h"
#অন্তর্ভাব "esp_system.h"
#অন্তর্ভাব "esp_heap_caps_init.h"
#অন্তর্ভাব "esp_int_wdt.h"
#অন্তর্ভাব "esp_task_wdt.h"
#অন্তর্ভাব "esp_task.h"
#অন্তর্ভাব "esp_private/crosscore_int.h"
#অন্তর্ভাব "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#অন্তর্ভাব "esp_log.h"
#অন্তর্ভাব "soc/soc_memory_types.h"
#অন্তর্ভাব "soc/dport_access.h"
#অন্তর্ভাব "sdkconfig.h"
#অন্তর্ভাব "esp_freertos_hooks.h"

#যদি CONFIG_IDF_TARGET_ESP32
    #অন্তর্ভাব "esp32/spiram.h"
#নতুবা_যদি CONFIG_IDF_TARGET_ESP32S2
    #অন্তর্ভাব "esp32s2/spiram.h"
#নতুবা_যদি CONFIG_IDF_TARGET_ESP32S3
    #অন্তর্ভাব "esp32s3/spiram.h"
#নতুবা_যদি CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#যদি CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    স্থির ধ্রুবক অক্ষর * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
অস্থির unsigned port_xSchedulerRunning[ port_অঙ্ক_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#যদি CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

স্থির শূন্য main_task( শূন্য * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    শূন্য esp_gdbstub_init( শূন্য );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

বাহ্যিক শূন্য app_main( শূন্য );

শূন্য esp_startup_start_app_common( শূন্য )
{
    #যদি CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_স্তূপ, ফাঁকা,
                                                 ESP_TASK_MAIN_PRIO, ফাঁকা, ESP_TASK_MAIN_CORE );
    প্রতিজ্ঞা( res == pdTRUE );
    ( শূন্য ) res;
}

#যদি !CONFIG_FREERTOS_UNICORE
    স্থির অস্থির bool s_other_cpu_startup_done = false;
    স্থির bool other_cpu_startup_idle_hook_cb( শূন্য )
    {
        s_other_cpu_startup_done = true;
        ফেরত true;
    }
#endif

স্থির শূন্য main_task( শূন্য * args )
{
    #যদি !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        যখন( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_স্তূপ_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #যদি CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        যদি( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            যদি( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #নতুবা_যদি CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        যদি( idle_0 != ফাঁকা )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        যদি( idle_1 != ফাঁকা )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( ফাঁকা );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( ধ্রুবক শূন্য * ptr )
{
    ফেরত esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_স্তূপ_Mem( ধ্রুবক শূন্য * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_স্তূপ_EXTERNAL_MEMORY
        ফেরত esp_ptr_byte_accessible( ptr );
    #অন্যথা
        ফেরত esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
