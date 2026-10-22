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

#ಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32
    #ಅನ್ತರ್ಭಾವ "esp32/spiram.h"
#ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_S2
    #ಅನ್ತರ್ಭಾವ "esp32s2/spiram.h"
#ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_S3
    #ಅನ್ತರ್ಭಾವ "esp32s3/spiram.h"
#ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_C3 || CONFIG_IDF_ಗುರಿ_ESP32_H2
/* SPIRAM is not supported on ESP32-C3 */
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_SPIRAM_MALLOC_RESERVE_ಆಂತರಿಕ
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಟ್ಯಾಗ್ = "cpu_start";
#ಆದರೆ_ಅಂತ್ಯ

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೋರ್ಟ್_x_Scheduler_Running[ ಪೋರ್ಟ್_ಅಂಕೆ_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ಆದರೆ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_ಬಹುಲಕ
    #ದೋಷ "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ main_task( ಶೂನ್ಯ * ವಾದಗಳು );

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    ಶೂನ್ಯ esp_gdbstub_init( ಶೂನ್ಯ );
#ಆದರೆ_ಅಂತ್ಯ // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

ಬಾಹ್ಯ ಶೂನ್ಯ app_main( ಶೂನ್ಯ );

ಶೂನ್ಯ esp_startup_ಆರಂಭ_app_common( ಶೂನ್ಯ )
{
    #ಆದರೆ CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #ಆದರೆ_ಅಂತ್ಯ

    esp_crosscore_int_init();

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #ಆದರೆ_ಅಂತ್ಯ // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    ಪೋರ್ಟ್_ತಳ_TYPE res = x_Task_Create_Pinned_ಗಮ್ಯ_Core( &main_task, "main",
                                                 ESP_TASK_MAIN_ರಾಶಿ, ಖಾಲಿ,
                                                 ESP_TASK_MAIN_PRIO, ಖಾಲಿ, ESP_TASK_MAIN_CORE );
    ಪ್ರತಿಜ್ಞಾ( res == pdTRUE );
    ( ಶೂನ್ಯ ) res;
}

#ಆದರೆ !CONFIG_FREERTOS_UNICORE
    ಸ್ಥಿರ ಅಸ್ಥಿರ bool s_other_cpu_startup_ಮುಗಿದ = false;
    ಸ್ಥಿರ bool other_cpu_startup_idle_hook_cb( ಶೂನ್ಯ )
    {
        s_other_cpu_startup_ಮುಗಿದ = true;
        ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ main_task( ಶೂನ್ಯ * ವಾದಗಳು )
{
    #ಆದರೆ !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_ರಿಜಿಸ್ಟರ್_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_ಪೋರ್ಟ್_Get_Core_ID() );

        ಆಗ( !s_other_cpu_startup_ಮುಗಿದ )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_ಪೋರ್ಟ್_Get_Core_ID() );
    #ಆದರೆ_ಅಂತ್ಯ

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    ರಾಶಿ_caps_enable_nonos_ರಾಶಿ_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #ಆದರೆ CONFIG_SPIRAM_MALLOC_RESERVE_ಆಂತರಿಕ
        ಆದರೆ( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_ಆಂತರಿಕ );

            ಆದರೆ( r != ESP_OK )
            {
                ESP_EARLY_LOGE( ಟ್ಯಾಗ್, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #ಅಥವಾಆದರೆ CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #ಆದರೆ_ಅಂತ್ಯ

    /*Add IDLE 0 to task wdt */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        ಆದರೆ( idle_0 != ಖಾಲಿ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_ಕೂಡಿಸು( idle_0 ) );
        }
    #ಆದರೆ_ಅಂತ್ಯ
    /*Add IDLE 1 to task wdt */
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        ಆದರೆ( idle_1 != ಖಾಲಿ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_ಕೂಡಿಸು( idle_1 ) );
        }
    #ಆದರೆ_ಅಂತ್ಯ

    app_main();
    vTaskDelete( ಖಾಲಿ );
}

/* -------------------- Heap Related ----------------------- */

bool x_ಪೋರ್ಟ್_Check_Valid_TCBMem( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ptr )
{
    ಹಿಂತಿರುಗಿ esp_ptr_ಆಂತರಿಕ( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ರಾಶಿ_Mem( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ptr )
{
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_SPIRAM_ALLOW_ರಾಶಿ_EXTERNAL_ಸ್ಮರಣೆ
        ಹಿಂತಿರುಗಿ esp_ptr_byte_accessible( ptr );
    #ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ esp_ptr_ಆಂತರಿಕ( ptr ) && esp_ptr_byte_accessible( ptr );
    #ಆದರೆ_ಅಂತ್ಯ
}
