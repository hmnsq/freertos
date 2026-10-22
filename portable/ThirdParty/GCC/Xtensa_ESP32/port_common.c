/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portmacro.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_heap_caps_init.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_int_wdt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_task_wdt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_private/crosscore_int.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "soc/soc_memory_types.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "soc/dport_access.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sdkconfig.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_freertos_hooks.h"

#ਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp32/spiram.h"
#ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_S2
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp32s2/spiram.h"
#ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_S3
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp32s3/spiram.h"
#ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_C3 || CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_H2
/* SPIRAM is not supported on ESP32-C3 */
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_SPIRAM_MALLOC_RESERVE_ਅੰਦਰੂਨੀ
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਟੈਗ = "cpu_start";
#ਜੇ_ਅੰਤ

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੋਰਟ_x_Scheduler_Running[ ਪੋਰਟ_ਅੰਕ_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ਜੇ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_ਬਹੁਲਕ
    #ਗਲਤੀ "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ main_task( ਖਾਲੀ * ਦਲੀਲਾਂ );

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    ਖਾਲੀ esp_gdbstub_init( ਖਾਲੀ );
#ਜੇ_ਅੰਤ // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

ਬਾਹਰੀ ਖਾਲੀ app_main( ਖਾਲੀ );

ਖਾਲੀ esp_startup_ਸ਼ੁਰੂ_app_common( ਖਾਲੀ )
{
    #ਜੇ CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #ਜੇ_ਅੰਤ

    esp_crosscore_int_init();

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #ਜੇ_ਅੰਤ // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    ਪੋਰਟ_ਅਧਾਰ_TYPE res = x_Task_Create_Pinned_ਮੰਜ਼ਿਲ_Core( &main_task, "main",
                                                 ESP_TASK_MAIN_ਢੇਰ, ਨਿਰਾ,
                                                 ESP_TASK_MAIN_PRIO, ਨਿਰਾ, ESP_TASK_MAIN_CORE );
    ਪ੍ਰਤਿਜ੍ਞਾ( res == pdTRUE );
    ( ਖਾਲੀ ) res;
}

#ਜੇ !CONFIG_FREERTOS_UNICORE
    ਸਥਿਰ ਅਸਥਿਰ bool s_other_cpu_startup_ਪੂਰਾ = false;
    ਸਥਿਰ bool other_cpu_startup_idle_hook_cb( ਖਾਲੀ )
    {
        s_other_cpu_startup_ਪੂਰਾ = true;
        ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ main_task( ਖਾਲੀ * ਦਲੀਲਾਂ )
{
    #ਜੇ !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_ਰਜਿਸਟਰ_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_ਪੋਰਟ_Get_Core_ID() );

        ਜਦੋਂ( !s_other_cpu_startup_ਪੂਰਾ )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_ਪੋਰਟ_Get_Core_ID() );
    #ਜੇ_ਅੰਤ

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    ਢੇਰ_caps_enable_nonos_ਢੇਰ_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #ਜੇ CONFIG_SPIRAM_MALLOC_RESERVE_ਅੰਦਰੂਨੀ
        ਜੇ( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_ਅੰਦਰੂਨੀ );

            ਜੇ( r != ESP_OK )
            {
                ESP_EARLY_LOGE( ਟੈਗ, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #ਜੇ_ਅੰਤ /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #ਜਾਂਜੇ CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #ਜੇ_ਅੰਤ

    /*Add IDLE 0 to task wdt */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        ਜੇ( idle_0 != ਨਿਰਾ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_ਜੋੜੋ( idle_0 ) );
        }
    #ਜੇ_ਅੰਤ
    /*Add IDLE 1 to task wdt */
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        ਜੇ( idle_1 != ਨਿਰਾ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_ਜੋੜੋ( idle_1 ) );
        }
    #ਜੇ_ਅੰਤ

    app_main();
    vTaskDelete( ਨਿਰਾ );
}

/* -------------------- Heap Related ----------------------- */

bool x_ਪੋਰਟ_Check_Valid_TCBMem( ਅਚਲ ਖਾਲੀ * ptr )
{
    ਵਾਪਸ esp_ptr_ਅੰਦਰੂਨੀ( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ਢੇਰ_Mem( ਅਚਲ ਖਾਲੀ * ptr )
{
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_SPIRAM_ALLOW_ਢੇਰ_EXTERNAL_ਸਮ੍ਰਿਤੀ
        ਵਾਪਸ esp_ptr_byte_accessible( ptr );
    #ਨਹੀਂਤਾਂ
        ਵਾਪਸ esp_ptr_ਅੰਦਰੂਨੀ( ptr ) && esp_ptr_byte_accessible( ptr );
    #ਜੇ_ਅੰਤ
}
