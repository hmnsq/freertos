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

#اگر CONFIG_IDF_ہدف_ESP32
    #شامل "esp32/spiram.h"
#وگرنہ_اگر CONFIG_IDF_ہدف_ESP32_S2
    #شامل "esp32s2/spiram.h"
#وگرنہ_اگر CONFIG_IDF_ہدف_ESP32_S3
    #شامل "esp32s3/spiram.h"
#وگرنہ_اگر CONFIG_IDF_ہدف_ESP32_C3 || CONFIG_IDF_ہدف_ESP32_H2
/* SPIRAM is not supported on ESP32-C3 */
#اگر_ختم

#اگر CONFIG_SPIRAM_MALLOC_RESERVE_اندرونی
    ساکن ثابت حرف * لیبل = "cpu_start";
#اگر_ختم

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
متلون غیرعلامتی پورٹ_x_Scheduler_Running[ پورٹ_عدد_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#اگر CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_منوال
    #غلطی "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#اگر_ختم

ساکن خالی main_task( خالی * دلائل );

#اگر_تعریف_شدہ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    خالی esp_gdbstub_init( خالی );
#اگر_ختم // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

خارجی خالی app_main( خالی );

خالی esp_startup_آغاز_app_common( خالی )
{
    #اگر CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #اگر_ختم

    esp_crosscore_int_init();

    #اگر_تعریف_شدہ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #اگر_ختم // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    پورٹ_بنیاد_TYPE res = x_Task_Create_Pinned_مقصد_Core( &main_task, "main",
                                                 ESP_TASK_MAIN_ڈھیر, تہی,
                                                 ESP_TASK_MAIN_PRIO, تہی, ESP_TASK_MAIN_CORE );
    أكد( res == pdTRUE );
    ( خالی ) res;
}

#اگر !CONFIG_FREERTOS_UNICORE
    ساکن متلون bool s_other_cpu_startup_مکمل = false;
    ساکن bool other_cpu_startup_idle_hook_cb( خالی )
    {
        s_other_cpu_startup_مکمل = true;
        واپس true;
    }
#اگر_ختم

ساکن خالی main_task( خالی * دلائل )
{
    #اگر !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_رجسٹر_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_پورٹ_Get_Core_ID() );

        جب( !s_other_cpu_startup_مکمل )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_پورٹ_Get_Core_ID() );
    #اگر_ختم

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    ڈھیر_caps_enable_nonos_ڈھیر_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #اگر CONFIG_SPIRAM_MALLOC_RESERVE_اندرونی
        اگر( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_اندرونی );

            اگر( r != ESP_OK )
            {
                ESP_EARLY_LOGE( لیبل, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #اگر_ختم /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #اگر_تعریف_شدہ CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #وگرنہ_اگر CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #اگر_ختم

    /*Add IDLE 0 to task wdt */
    #اگر_تعریف_شدہ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        اگر( idle_0 != تہی )
        {
            ESP_ERROR_CHECK( esp_task_wdt_جوڑو( idle_0 ) );
        }
    #اگر_ختم
    /*Add IDLE 1 to task wdt */
    #اگر_تعریف_شدہ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        اگر( idle_1 != تہی )
        {
            ESP_ERROR_CHECK( esp_task_wdt_جوڑو( idle_1 ) );
        }
    #اگر_ختم

    app_main();
    vTaskDelete( تہی );
}

/* -------------------- Heap Related ----------------------- */

bool x_پورٹ_Check_Valid_TCBMem( ثابت خالی * ptr )
{
    واپس esp_ptr_اندرونی( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ڈھیر_Mem( ثابت خالی * ptr )
{
    #اگر_تعریف_شدہ CONFIG_SPIRAM_ALLOW_ڈھیر_EXTERNAL_حافظہ
        واپس esp_ptr_byte_accessible( ptr );
    #ورنہ
        واپس esp_ptr_اندرونی( ptr ) && esp_ptr_byte_accessible( ptr );
    #اگر_ختم
}
