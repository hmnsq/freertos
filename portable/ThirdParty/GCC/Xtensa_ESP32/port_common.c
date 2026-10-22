/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#அந்தர்பாவ <string.h>
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"
#அந்தர்பாவ "portmacro.h"
#அந்தர்பாவ "esp_system.h"
#அந்தர்பாவ "esp_heap_caps_init.h"
#அந்தர்பாவ "esp_int_wdt.h"
#அந்தர்பாவ "esp_task_wdt.h"
#அந்தர்பாவ "esp_task.h"
#அந்தர்பாவ "esp_private/crosscore_int.h"
#அந்தர்பாவ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#அந்தர்பாவ "esp_log.h"
#அந்தர்பாவ "soc/soc_memory_types.h"
#அந்தர்பாவ "soc/dport_access.h"
#அந்தர்பாவ "sdkconfig.h"
#அந்தர்பாவ "esp_freertos_hooks.h"

#எனில் CONFIG_IDF_TARGET_ESP32
    #அந்தர்பாவ "esp32/spiram.h"
#அல்லதெனில் CONFIG_IDF_TARGET_ESP32S2
    #அந்தர்பாவ "esp32s2/spiram.h"
#அல்லதெனில் CONFIG_IDF_TARGET_ESP32S3
    #அந்தர்பாவ "esp32s3/spiram.h"
#அல்லதெனில் CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#எனில் CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    நிலையான மாறிலி எழுத்து * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
நிலையற்ற unsigned port_xSchedulerRunning[ port_இலக்கம்_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#எனில் CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

நிலையான வெறுமை main_task( வெறுமை * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    வெறுமை esp_gdbstub_init( வெறுமை );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

வெளி வெறுமை app_main( வெறுமை );

வெறுமை esp_startup_start_app_common( வெறுமை )
{
    #எனில் CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_அடுக்கு, வெற்று,
                                                 ESP_TASK_MAIN_PRIO, வெற்று, ESP_TASK_MAIN_CORE );
    ப்ரதிஜ்ஞா( res == pdTRUE );
    ( வெறுமை ) res;
}

#எனில் !CONFIG_FREERTOS_UNICORE
    நிலையான நிலையற்ற bool s_other_cpu_startup_done = false;
    நிலையான bool other_cpu_startup_idle_hook_cb( வெறுமை )
    {
        s_other_cpu_startup_done = true;
        திரும்பு true;
    }
#endif

நிலையான வெறுமை main_task( வெறுமை * args )
{
    #எனில் !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        போது( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_அடுக்கு_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #எனில் CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        எனில்( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            எனில்( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #அல்லதெனில் CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        எனில்( idle_0 != வெற்று )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        எனில்( idle_1 != வெற்று )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( வெற்று );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( மாறிலி வெறுமை * ptr )
{
    திரும்பு esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_அடுக்கு_Mem( மாறிலி வெறுமை * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_அடுக்கு_EXTERNAL_MEMORY
        திரும்பு esp_ptr_byte_accessible( ptr );
    #இல்லையெனில்
        திரும்பு esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
