/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "portmacro.h"
#ಅನ್ತರ್ಭಾವ "esp_system.h"
#ಅನ್ತರ್ಭಾವ "esp_heap_caps_init.h"
#ಅನ್ತರ್ಭಾವ "esp_int_wdt.h"
#ಅನ್ತರ್ಭಾವ "esp_task_wdt.h"
#ಅನ್ತರ್ಭಾವ "esp_task.h"
#ಅನ್ತರ್ಭಾವ "esp_private/crosscore_int.h"
#ಅನ್ತರ್ಭಾವ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#ಅನ್ತರ್ಭಾವ "esp_log.h"
#ಅನ್ತರ್ಭಾವ "soc/soc_memory_types.h"
#ಅನ್ತರ್ಭಾವ "soc/dport_access.h"
#ಅನ್ತರ್ಭಾವ "sdkconfig.h"
#ಅನ್ತರ್ಭಾವ "esp_freertos_hooks.h"

#ಯದಿ CONFIG_IDF_TARGET_ESP32
    #ಅನ್ತರ್ಭಾವ "esp32/spiram.h"
#ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32S2
    #ಅನ್ತರ್ಭಾವ "esp32s2/spiram.h"
#ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32S3
    #ಅನ್ತರ್ಭಾವ "esp32s3/spiram.h"
#ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#ಯದಿ CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
ಚಞ್ಚಲ unsigned port_xSchedulerRunning[ port_ಅಂಕೆ_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ಯದಿ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

ಸ್ಥಿರ ಶೂನ್ಯ main_task( ಶೂನ್ಯ * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    ಶೂನ್ಯ esp_gdbstub_init( ಶೂನ್ಯ );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

ಬಾಹ್ಯ ಶೂನ್ಯ app_main( ಶೂನ್ಯ );

ಶೂನ್ಯ esp_startup_start_app_common( ಶೂನ್ಯ )
{
    #ಯದಿ CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_ರಾಶಿ, ರಿಕ್ತ,
                                                 ESP_TASK_MAIN_PRIO, ರಿಕ್ತ, ESP_TASK_MAIN_CORE );
    ಪ್ರತಿಜ್ಞಾ( res == pdTRUE );
    ( ಶೂನ್ಯ ) res;
}

#ಯದಿ !CONFIG_FREERTOS_UNICORE
    ಸ್ಥಿರ ಚಞ್ಚಲ bool s_other_cpu_startup_done = false;
    ಸ್ಥಿರ bool other_cpu_startup_idle_hook_cb( ಶೂನ್ಯ )
    {
        s_other_cpu_startup_done = true;
        ಪ್ರತ್ಯಾಗಮ true;
    }
#endif

ಸ್ಥಿರ ಶೂನ್ಯ main_task( ಶೂನ್ಯ * args )
{
    #ಯದಿ !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        ಯಾವತ್( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_ರಾಶಿ_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #ಯದಿ CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        ಯದಿ( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            ಯದಿ( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #ನೋಚೇದ್ಯದಿ CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        ಯದಿ( idle_0 != ರಿಕ್ತ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        ಯದಿ( idle_1 != ರಿಕ್ತ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( ರಿಕ್ತ );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( ಧ್ರುವ ಶೂನ್ಯ * ptr )
{
    ಪ್ರತ್ಯಾಗಮ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ರಾಶಿ_Mem( ಧ್ರುವ ಶೂನ್ಯ * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_ರಾಶಿ_EXTERNAL_MEMORY
        ಪ್ರತ್ಯಾಗಮ esp_ptr_byte_accessible( ptr );
    #ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
