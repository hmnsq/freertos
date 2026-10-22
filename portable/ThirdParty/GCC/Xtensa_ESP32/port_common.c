/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#समावेश <string.h>
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "portmacro.h"
#समावेश "esp_system.h"
#समावेश "esp_heap_caps_init.h"
#समावेश "esp_int_wdt.h"
#समावेश "esp_task_wdt.h"
#समावेश "esp_task.h"
#समावेश "esp_private/crosscore_int.h"
#समावेश "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#समावेश "esp_log.h"
#समावेश "soc/soc_memory_types.h"
#समावेश "soc/dport_access.h"
#समावेश "sdkconfig.h"
#समावेश "esp_freertos_hooks.h"

#अगर CONFIG_IDF_TARGET_ESP32
    #समावेश "esp32/spiram.h"
#या_अगर CONFIG_IDF_TARGET_ESP32S2
    #समावेश "esp32s2/spiram.h"
#या_अगर CONFIG_IDF_TARGET_ESP32S3
    #समावेश "esp32s3/spiram.h"
#या_अगर CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/* SPIRAM is not supported on ESP32-C3 */
#पूर्ण_अगर

#अगर CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
    अटल स्थिर अक्षर * TAG = "cpu_start";
#पूर्ण_अगर

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
अस्थिर अचिन्हित port_xSchedulerRunning[ port_अंक_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#अगर CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
    #त्रुटि "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#पूर्ण_अगर

अटल व्योम main_task( व्योम * args );

#अगर_घोषित CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    व्योम esp_gdbstub_init( व्योम );
#पूर्ण_अगर // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

बाह्य व्योम app_main( व्योम );

व्योम esp_startup_start_app_common( व्योम )
{
    #अगर CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #पूर्ण_अगर

    esp_crosscore_int_init();

    #अगर_घोषित CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #पूर्ण_अगर // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    portBASE_TYPE res = xTaskCreatePinnedToCore( &main_task, "main",
                                                 ESP_TASK_MAIN_ढेर, शून्य,
                                                 ESP_TASK_MAIN_PRIO, शून्य, ESP_TASK_MAIN_CORE );
    निश्चित( res == pdTRUE );
    ( व्योम ) res;
}

#अगर !CONFIG_FREERTOS_UNICORE
    अटल अस्थिर bool s_other_cpu_startup_done = false;
    अटल bool other_cpu_startup_idle_hook_cb( व्योम )
    {
        s_other_cpu_startup_done = true;
        वापस true;
    }
#पूर्ण_अगर

अटल व्योम main_task( व्योम * args )
{
    #अगर !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_register_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );

        जबतक( !s_other_cpu_startup_done )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !xPortGetCoreID() );
    #पूर्ण_अगर

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    heap_caps_enable_nonos_ढेर_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #अगर CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL
        अगर( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL );

            अगर( r != ESP_OK )
            {
                ESP_EARLY_LOGE( TAG, "Could not reserve internal/DMA pool (error 0x%x)", r );
                पात();
            }
        }
    #पूर्ण_अगर /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #अगर_घोषित CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #या_अगर CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #पूर्ण_अगर

    /*Add IDLE 0 to task wdt */
    #अगर_घोषित CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        अगर( idle_0 != शून्य )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_0 ) );
        }
    #पूर्ण_अगर
    /*Add IDLE 1 to task wdt */
    #अगर_घोषित CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        अगर( idle_1 != शून्य )
        {
            ESP_ERROR_CHECK( esp_task_wdt_add( idle_1 ) );
        }
    #पूर्ण_अगर

    app_main();
    vTaskDelete( शून्य );
}

/* -------------------- Heap Related ----------------------- */

bool xPortCheckValidTCBMem( स्थिर व्योम * ptr )
{
    वापस esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ढेर_Mem( स्थिर व्योम * ptr )
{
    #अगर_घोषित CONFIG_SPIRAM_ALLOW_ढेर_EXTERNAL_MEMORY
        वापस esp_ptr_byte_accessible( ptr );
    #अन्यथा
        वापस esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr );
    #पूर्ण_अगर
}
