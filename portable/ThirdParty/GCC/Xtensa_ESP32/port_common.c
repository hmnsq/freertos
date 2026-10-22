/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#شامل <string.h>
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "portmacro.h"
#شامل "esp_system.h"
#شامل "esp_heap_caps_init.h"
#شامل "esp_int_wdt.h"
#شامل "esp_task_wdt.h"
#شامل "esp_task.h"
#شامل "esp_private/crosscore_int.h"
#شامل "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#شامل "esp_log.h"
#شامل "soc/soc_memory_types.h"
#شامل "soc/dport_access.h"
#شامل "sdkconfig.h"
#شامل "esp_freertos_hooks.h"

#اگر CONFIG_IDF_TARGET_ESP32
    #شامل "esp32/spiram.h"
#وگرنهاگر CONFIG_IDF_TARGET_ESP32S2
    #شامل "esp32s2/spiram.h"
#وگرنهاگر CONFIG_IDF_TARGET_ESP32S3
    #شامل "esp32s3/spiram.h"
#وگرنهاگر CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#اگر CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    ایستا ثابت نویسه * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
فرار unsigned port_xSchedulerRunning[ port_رقم_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#اگر CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

ایستا تهی main_task( تهی * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    تهی esp_gdbstub_init( تهی );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

بیرونی تهی app_main( تهی );

تهی esp_startup_start_app_common( تهی )
{
    #اگر CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_پشته, پوچ,
                                                 ESP_TASK_MAIN_PRIO, پوچ, ESP_TASK_MAIN_CORE );
    أكد( res == pdTRUE );
    ( تهی ) res;
}

#اگر !CONFIG_FREERTOS_UNICORE
    ایستا فرار bool s_other_cpu_startup_done = false;
    ایستا bool other_cpu_startup_idle_hook_cb( تهی )
    {
        s_other_cpu_startup_done = true;
        بازگشت true;
    }
#endif

ایستا تهی main_task( تهی * args )
{
    #اگر !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        وقتی( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_پشته_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #اگر CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        اگر( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            اگر( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #وگرنهاگر CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        اگر( idle_0 != پوچ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        اگر( idle_1 != پوچ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( پوچ );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( ثابت تهی * ptr )
{
    بازگشت esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_پشته_Mem( ثابت تهی * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_پشته_EXTERNAL_MEMORY
        بازگشت esp_ptr_byte_accessible( ptr );
    #وگرنه
        بازگشت esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
