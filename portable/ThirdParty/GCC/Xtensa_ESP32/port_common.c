/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"
#ଅନ୍ତର୍ଭାଵ "portmacro.h"
#ଅନ୍ତର୍ଭାଵ "esp_system.h"
#ଅନ୍ତର୍ଭାଵ "esp_heap_caps_init.h"
#ଅନ୍ତର୍ଭାଵ "esp_int_wdt.h"
#ଅନ୍ତର୍ଭାଵ "esp_task_wdt.h"
#ଅନ୍ତର୍ଭାଵ "esp_task.h"
#ଅନ୍ତର୍ଭାଵ "esp_private/crosscore_int.h"
#ଅନ୍ତର୍ଭାଵ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#ଅନ୍ତର୍ଭାଵ "esp_log.h"
#ଅନ୍ତର୍ଭାଵ "soc/soc_memory_types.h"
#ଅନ୍ତର୍ଭାଵ "soc/dport_access.h"
#ଅନ୍ତର୍ଭାଵ "sdkconfig.h"
#ଅନ୍ତର୍ଭାଵ "esp_freertos_hooks.h"

#ଯଦି CONFIG_IDF_TARGET_ESP32
    #ଅନ୍ତର୍ଭାଵ "esp32/spiram.h"
#ନଚେତଯଦି CONFIG_IDF_TARGET_ESP32S2
    #ଅନ୍ତର୍ଭାଵ "esp32s2/spiram.h"
#ନଚେତଯଦି CONFIG_IDF_TARGET_ESP32S3
    #ଅନ୍ତର୍ଭାଵ "esp32s3/spiram.h"
#ନଚେତଯଦି CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#ଯଦି CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
ଅସ୍ଥିର unsigned port_xSchedulerRunning[ port_ଅଙ୍କ_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ଯଦି CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

ସ୍ଥିର ଶୂନ୍ୟ main_task( ଶୂନ୍ୟ * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    ଶୂନ୍ୟ esp_gdbstub_init( ଶୂନ୍ୟ );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

ବାହ୍ୟ ଶୂନ୍ୟ app_main( ଶୂନ୍ୟ );

ଶୂନ୍ୟ esp_startup_start_app_common( ଶୂନ୍ୟ )
{
    #ଯଦି CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_ଗଦା, ଖାଲି,
                                                 ESP_TASK_MAIN_PRIO, ଖାଲି, ESP_TASK_MAIN_CORE );
    ପ୍ରତିଜ୍ଞା( res == pdTRUE );
    ( ଶୂନ୍ୟ ) res;
}

#ଯଦି !CONFIG_FREERTOS_UNICORE
    ସ୍ଥିର ଅସ୍ଥିର bool s_other_cpu_startup_done = false;
    ସ୍ଥିର bool other_cpu_startup_idle_hook_cb( ଶୂନ୍ୟ )
    {
        s_other_cpu_startup_done = true;
        ଫେରନ୍ତୁ true;
    }
#endif

ସ୍ଥିର ଶୂନ୍ୟ main_task( ଶୂନ୍ୟ * args )
{
    #ଯଦି !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        ଯେତେବେଳେ( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_ଗଦା_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #ଯଦି CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        ଯଦି( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            ଯଦି( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #ନଚେତଯଦି CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        ଯଦି( idle_0 != ଖାଲି )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        ଯଦି( idle_1 != ଖାଲି )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( ଖାଲି );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( ଅଚଳ ଶୂନ୍ୟ * ptr )
{
    ଫେରନ୍ତୁ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ଗଦା_Mem( ଅଚଳ ଶୂନ୍ୟ * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_ଗଦା_EXTERNAL_MEMORY
        ଫେରନ୍ତୁ esp_ptr_byte_accessible( ptr );
    #ଅନ୍ୟଥା
        ଫେରନ୍ତୁ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
