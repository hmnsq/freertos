/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ضمن <string.h>
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portmacro.h"
#ضمن "esp_system.h"
#ضمن "esp_heap_caps_init.h"
#ضمن "esp_int_wdt.h"
#ضمن "esp_task_wdt.h"
#ضمن "esp_task.h"
#ضمن "esp_private/crosscore_int.h"
#ضمن "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#ضمن "esp_log.h"
#ضمن "soc/soc_memory_types.h"
#ضمن "soc/dport_access.h"
#ضمن "sdkconfig.h"
#ضمن "esp_freertos_hooks.h"

#إذا CONFIG_IDF_هدف_ESP32
    #ضمن "esp32/spiram.h"
#وإلاإذا CONFIG_IDF_هدف_ESP32_S2
    #ضمن "esp32s2/spiram.h"
#وإلاإذا CONFIG_IDF_هدف_ESP32_S3
    #ضمن "esp32s3/spiram.h"
#وإلاإذا CONFIG_IDF_هدف_ESP32_C3 || CONFIG_IDF_هدف_ESP32_H2
/* SPIRAM is not supported on ESP32-C3 */
#پایان_اگر

#إذا CONFIG_SPIRAM_MALLOC_RESERVE_داخلی
    ساكن ثابت حرف * برچسب = "cpu_start";
#پایان_اگر

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
متطاير بیعلامت پورت_x_Scheduler_Running[ پورت_رقم_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#إذا CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_نما
    #خطا "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#پایان_اگر

ساكن فراغ main_task( فراغ * آرگومانها );

#اگر_تعریف_شده CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    فراغ esp_gdbstub_init( فراغ );
#پایان_اگر // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

خارجي فراغ app_main( فراغ );

فراغ esp_startup_شروع_app_common( فراغ )
{
    #إذا CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #پایان_اگر

    esp_crosscore_int_init();

    #اگر_تعریف_شده CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #پایان_اگر // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    پورت_پایه_TYPE res = x_Task_Create_Pinned_مقصد_Core( &main_task, "main",
                                                 ESP_TASK_MAIN_پشته, عدم,
                                                 ESP_TASK_MAIN_PRIO, عدم, ESP_TASK_MAIN_CORE );
    أكد( res == pdTRUE );
    ( فراغ ) res;
}

#إذا !CONFIG_FREERTOS_UNICORE
    ساكن متطاير bool s_other_cpu_startup_انجامشده = false;
    ساكن bool other_cpu_startup_idle_hook_cb( فراغ )
    {
        s_other_cpu_startup_انجامشده = true;
        أرجع true;
    }
#پایان_اگر

ساكن فراغ main_task( فراغ * آرگومانها )
{
    #إذا !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_ثبات_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_پورت_Get_Core_ID() );

        طالما( !s_other_cpu_startup_انجامشده )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_پورت_Get_Core_ID() );
    #پایان_اگر

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    انباشته_caps_enable_nonos_پشته_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #إذا CONFIG_SPIRAM_MALLOC_RESERVE_داخلی
        إذا( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_داخلی );

            إذا( r != ESP_OK )
            {
                ESP_EARLY_LOGE( برچسب, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #پایان_اگر /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #اگر_تعریف_شده CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #وإلاإذا CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #پایان_اگر

    /*Add IDLE 0 to task wdt */
    #اگر_تعریف_شده CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        إذا( idle_0 != عدم )
        {
            ESP_ERROR_CHECK( esp_task_wdt_جمع_کن( idle_0 ) );
        }
    #پایان_اگر
    /*Add IDLE 1 to task wdt */
    #اگر_تعریف_شده CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        إذا( idle_1 != عدم )
        {
            ESP_ERROR_CHECK( esp_task_wdt_جمع_کن( idle_1 ) );
        }
    #پایان_اگر

    app_main();
    vTaskDelete( عدم );
}

/* -------------------- Heap Related ----------------------- */

bool x_پورت_Check_Valid_TCBMem( ثابت فراغ * ptr )
{
    أرجع esp_ptr_داخلی( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_پشته_Mem( ثابت فراغ * ptr )
{
    #اگر_تعریف_شده CONFIG_SPIRAM_ALLOW_پشته_EXTERNAL_حافظه
        أرجع esp_ptr_byte_accessible( ptr );
    #وإلا
        أرجع esp_ptr_داخلی( ptr ) && esp_ptr_byte_accessible( ptr );
    #پایان_اگر
}
