/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"
#അന്തര്ഭാവ "portmacro.h"
#അന്തര്ഭാവ "esp_system.h"
#അന്തര്ഭാവ "esp_heap_caps_init.h"
#അന്തര്ഭാവ "esp_int_wdt.h"
#അന്തര്ഭാവ "esp_task_wdt.h"
#അന്തര്ഭാവ "esp_task.h"
#അന്തര്ഭാവ "esp_private/crosscore_int.h"
#അന്തര്ഭാവ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#അന്തര്ഭാവ "esp_log.h"
#അന്തര്ഭാവ "soc/soc_memory_types.h"
#അന്തര്ഭാവ "soc/dport_access.h"
#അന്തര്ഭാവ "sdkconfig.h"
#അന്തര്ഭാവ "esp_freertos_hooks.h"

#എങ്കിൽ CONFIG_IDF_TARGET_ESP32
    #അന്തര്ഭാവ "esp32/spiram.h"
#അല്ലെങ്കിലെങ്കിൽ CONFIG_IDF_TARGET_ESP32S2
    #അന്തര്ഭാവ "esp32s2/spiram.h"
#അല്ലെങ്കിലെങ്കിൽ CONFIG_IDF_TARGET_ESP32S3
    #അന്തര്ഭാവ "esp32s3/spiram.h"
#അല്ലെങ്കിലെങ്കിൽ CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#എങ്കിൽ CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    സ്ഥിതം സ്ഥിരം അക്ഷരം * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
അസ്ഥിര unsigned port_xSchedulerRunning[ port_അക്കം_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#എങ്കിൽ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

സ്ഥിതം ശൂന്യം main_task( ശൂന്യം * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    ശൂന്യം esp_gdbstub_init( ശൂന്യം );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

ബാഹ്യ ശൂന്യം app_main( ശൂന്യം );

ശൂന്യം esp_startup_start_app_common( ശൂന്യം )
{
    #എങ്കിൽ CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_അട്ടി, ശൂന്യ,
                                                 ESP_TASK_MAIN_PRIO, ശൂന്യ, ESP_TASK_MAIN_CORE );
    പ്രതിജ്ഞാ( res == pdTRUE );
    ( ശൂന്യം ) res;
}

#എങ്കിൽ !CONFIG_FREERTOS_UNICORE
    സ്ഥിതം അസ്ഥിര bool s_other_cpu_startup_done = false;
    സ്ഥിതം bool other_cpu_startup_idle_hook_cb( ശൂന്യം )
    {
        s_other_cpu_startup_done = true;
        തിരികെ true;
    }
#endif

സ്ഥിതം ശൂന്യം main_task( ശൂന്യം * args )
{
    #എങ്കിൽ !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        ആകുമ്പോൾ( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_അട്ടി_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #എങ്കിൽ CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        എങ്കിൽ( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            എങ്കിൽ( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #അല്ലെങ്കിലെങ്കിൽ CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        എങ്കിൽ( idle_0 != ശൂന്യ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        എങ്കിൽ( idle_1 != ശൂന്യ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( ശൂന്യ );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( സ്ഥിരം ശൂന്യം * ptr )
{
    തിരികെ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_അട്ടി_Mem( സ്ഥിരം ശൂന്യം * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_അട്ടി_EXTERNAL_MEMORY
        തിരികെ esp_ptr_byte_accessible( ptr );
    #അല്ലെങ്കിൽ
        തിരികെ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
