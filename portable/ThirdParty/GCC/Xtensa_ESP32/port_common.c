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

#إذا CONFIG_IDF_نشانہ_ESP32
    #ضمن "esp32/spiram.h"
#وإلاإذا CONFIG_IDF_نشانہ_ESP32_S2
    #ضمن "esp32s2/spiram.h"
#وإلاإذا CONFIG_IDF_نشانہ_ESP32_S3
    #ضمن "esp32s3/spiram.h"
#وإلاإذا CONFIG_IDF_نشانہ_ESP32_C3 || CONFIG_IDF_نشانہ_ESP32_H2
/* SPIRAM is not supported on ESP32-C3 */
#جے_انت

#إذا CONFIG_SPIRAM_MALLOC_RESERVE_اندرونی
    ساكن ثابت حرف * ٹیگ = "cpu_start";
#جے_انت

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
متطاير بنانشانی پورٹ_x_Scheduler_Running[ پورٹ_عدد_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#إذا CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_منوال
    #غلطی "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#جے_انت

ساكن فراغ main_task( فراغ * دلیلاں );

#جے_تعریف_شدہ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    فراغ esp_gdbstub_init( فراغ );
#جے_انت // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

خارجي فراغ app_main( فراغ );

فراغ esp_startup_شروع_app_common( فراغ )
{
    #إذا CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #جے_انت

    esp_crosscore_int_init();

    #جے_تعریف_شدہ CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #جے_انت // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    پورٹ_ادھار_TYPE res = x_Task_Create_Pinned_منزل_Core( &main_task, "main",
                                                 ESP_TASK_MAIN_ڈھیر, عدم,
                                                 ESP_TASK_MAIN_PRIO, عدم, ESP_TASK_MAIN_CORE );
    أكد( res == pdTRUE );
    ( فراغ ) res;
}

#إذا !CONFIG_FREERTOS_UNICORE
    ساكن متطاير bool s_other_cpu_startup_پورا = false;
    ساكن bool other_cpu_startup_idle_hook_cb( فراغ )
    {
        s_other_cpu_startup_پورا = true;
        أرجع true;
    }
#جے_انت

ساكن فراغ main_task( فراغ * دلیلاں )
{
    #إذا !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_رجسٹر_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_پورٹ_Get_Core_ID() );

        طالما( !s_other_cpu_startup_پورا )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_پورٹ_Get_Core_ID() );
    #جے_انت

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    ڈھیر_caps_enable_nonos_ڈھیر_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #إذا CONFIG_SPIRAM_MALLOC_RESERVE_اندرونی
        إذا( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_اندرونی );

            إذا( r != ESP_OK )
            {
                ESP_EARLY_LOGE( ٹیگ, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #جے_انت /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #جے_تعریف_شدہ CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #وإلاإذا CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #جے_انت

    /*Add IDLE 0 to task wdt */
    #جے_تعریف_شدہ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        إذا( idle_0 != عدم )
        {
            ESP_ERROR_CHECK( esp_task_wdt_جوڑو( idle_0 ) );
        }
    #جے_انت
    /*Add IDLE 1 to task wdt */
    #جے_تعریف_شدہ CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        إذا( idle_1 != عدم )
        {
            ESP_ERROR_CHECK( esp_task_wdt_جوڑو( idle_1 ) );
        }
    #جے_انت

    app_main();
    vTaskDelete( عدم );
}

/* -------------------- Heap Related ----------------------- */

bool x_پورٹ_Check_Valid_TCBMem( ثابت فراغ * ptr )
{
    أرجع esp_ptr_اندرونی( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_ڈھیر_Mem( ثابت فراغ * ptr )
{
    #جے_تعریف_شدہ CONFIG_SPIRAM_ALLOW_ڈھیر_EXTERNAL_حافظہ
        أرجع esp_ptr_byte_accessible( ptr );
    #وإلا
        أرجع esp_ptr_اندرونی( ptr ) && esp_ptr_byte_accessible( ptr );
    #جے_انت
}
