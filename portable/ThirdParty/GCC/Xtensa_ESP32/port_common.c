/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"
#અન્તર્ભાવ "portmacro.h"
#અન્તર્ભાવ "esp_system.h"
#અન્તર્ભાવ "esp_heap_caps_init.h"
#અન્તર્ભાવ "esp_int_wdt.h"
#અન્તર્ભાવ "esp_task_wdt.h"
#અન્તર્ભાવ "esp_task.h"
#અન્તર્ભાવ "esp_private/crosscore_int.h"
#અન્તર્ભાવ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#અન્તર્ભાવ "esp_log.h"
#અન્તર્ભાવ "soc/soc_memory_types.h"
#અન્તર્ભાવ "soc/dport_access.h"
#અન્તર્ભાવ "sdkconfig.h"
#અન્તર્ભાવ "esp_freertos_hooks.h"

#જો CONFIG_IDF_TARGET_ESP32
    #અન્તર્ભાવ "esp32/spiram.h"
#અથવાજો CONFIG_IDF_TARGET_ESP32S2
    #અન્તર્ભાવ "esp32s2/spiram.h"
#અથવાજો CONFIG_IDF_TARGET_ESP32S3
    #અન્તર્ભાવ "esp32s3/spiram.h"
#અથવાજો CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#જો CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    સ્થિર અચલ અક્ષર * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
અસ્થિર unsigned port_xSchedulerRunning[ port_અંક_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#જો CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

સ્થિર શૂન્ય main_task( શૂન્ય * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    શૂન્ય esp_gdbstub_init( શૂન્ય );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

બાહ્ય શૂન્ય app_main( શૂન્ય );

શૂન્ય esp_startup_start_app_common( શૂન્ય )
{
    #જો CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_ઢગલો, ખાલી,
                                                 ESP_TASK_MAIN_PRIO, ખાલી, ESP_TASK_MAIN_CORE );
    પ્રતિજ્ઞા( res == pdTRUE );
    ( શૂન્ય ) res;
}

#જો !CONFIG_FREERTOS_UNICORE
    સ્થિર અસ્થિર bool s_other_cpu_startup_done = false;
    સ્થિર bool other_cpu_startup_idle_hook_cb( શૂન્ય )
    {
        s_other_cpu_startup_done = true;
        પાછા true;
    }
#endif

સ્થિર શૂન્ય main_task( શૂન્ય * args )
{
    #જો !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        જ્યારે( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_ઢગલો_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #જો CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        જો( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            જો( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #અથવાજો CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        જો( idle_0 != ખાલી )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        જો( idle_1 != ખાલી )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( ખાલી );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( અચલ શૂન્ય * ptr )
{
    પાછા esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ઢગલો_Mem( અચલ શૂન્ય * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_ઢગલો_EXTERNAL_MEMORY
        પાછા esp_ptr_byte_accessible( ptr );
    #નહીંતર
        પાછા esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
