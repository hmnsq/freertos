/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#अन्तर्भाव <string.h>
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "portmacro.h"
#अन्तर्भाव "esp_system.h"
#अन्तर्भाव "esp_heap_caps_init.h"
#अन्तर्भाव "esp_int_wdt.h"
#अन्तर्भाव "esp_task_wdt.h"
#अन्तर्भाव "esp_task.h"
#अन्तर्भाव "esp_private/crosscore_int.h"
#अन्तर्भाव "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#अन्तर्भाव "esp_log.h"
#अन्तर्भाव "soc/soc_memory_types.h"
#अन्तर्भाव "soc/dport_access.h"
#अन्तर्भाव "sdkconfig.h"
#अन्तर्भाव "esp_freertos_hooks.h"

#यदि CONFIG_IDF_TARGET_ESP32
    #अन्तर्भाव "esp32/spiram.h"
#अथवायदि CONFIG_IDF_TARGET_ESP32S2
    #अन्तर्भाव "esp32s2/spiram.h"
#अथवायदि CONFIG_IDF_TARGET_ESP32S3
    #अन्तर्भाव "esp32s3/spiram.h"
#अथवायदि CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#endif

#यदि CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    स्थिर अचर वर्ण * TAG = "cpu_start";
#endif

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
चञ्चल अचिन्हित port_xSchedulerRunning[ port_अङ्क_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#यदि CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #error "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#endif

स्थिर शून्य main_task( शून्य * args );

#ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    शून्य esp_gdbstub_init( शून्य );
#endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

बाह्य शून्य app_main( शून्य );

शून्य esp_startup_start_app_common( शून्य )
{
    #यदि CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #endif

    esp_crosscore_int_init();

    #ifdef CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #endif // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_थाक, रिक्त,
                                                 ESP_TASK_MAIN_PRIO, रिक्त, ESP_TASK_MAIN_CORE );
    प्रतिज्ञा( res == pdTRUE );
    ( शून्य ) res;
}

#यदि !CONFIG_FREERTOS_UNICORE
    स्थिर चञ्चल bool s_other_cpu_startup_done = false;
    स्थिर bool other_cpu_startup_idle_hook_cb( शून्य )
    {
        s_other_cpu_startup_done = true;
        फर्काऊ true;
    }
#endif

स्थिर शून्य main_task( शून्य * args )
{
    #यदि !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        जबसम्म( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #endif

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_थाक_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #यदि CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        यदि( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            यदि( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                पात();
            }
        }
    #endif /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ifdef CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #अथवायदि CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #endif

    /*Add IDLE 0 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        यदि( idle_0 != रिक्त )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #endif
    /*Add IDLE 1 to task wdt */
    #ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        यदि( idle_1 != रिक्त )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #endif

    app_main();
    vTaskDelete( रिक्त );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( अचर शून्य * ptr )
{
    फर्काऊ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_थाक_Mem( अचर शून्य * ptr )
{
    #ifdef CONFIG_SPIRAM_ALLOW_थाक_EXTERNAL_MEMORY
        फर्काऊ esp_ptr_byte_accessible( ptr );
    #अन्यथा
        फर्काऊ esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #endif
}
