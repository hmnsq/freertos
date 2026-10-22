/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#అన్తర్భావ <string.h>
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "portmacro.h"
#అన్తర్భావ "esp_system.h"
#అన్తర్భావ "esp_heap_caps_init.h"
#అన్తర్భావ "esp_int_wdt.h"
#అన్తర్భావ "esp_task_wdt.h"
#అన్తర్భావ "esp_task.h"
#అన్తర్భావ "esp_private/crosscore_int.h"
#అన్తర్భావ "esp_private/startup_internal.h" /* Required by g_spiram_ok. [refactor-todo] for g_spiram_ok */
#అన్తర్భావ "esp_log.h"
#అన్తర్భావ "soc/soc_memory_types.h"
#అన్తర్భావ "soc/dport_access.h"
#అన్తర్భావ "sdkconfig.h"
#అన్తర్భావ "esp_freertos_hooks.h"

#ఒకవేళ CONFIG_IDF_లక్ష్యం_ESP32
    #అన్తర్భావ "esp32/spiram.h"
#లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32_S2
    #అన్తర్భావ "esp32s2/spiram.h"
#లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32_S3
    #అన్తర్భావ "esp32s3/spiram.h"
#లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32_C3 || CONFIG_IDF_లక్ష్యం_ESP32_H2
/* SPIRAM is not supported on ESP32-C3 */
#అయితే_ముగింపు

#ఒకవేళ CONFIG_SPIRAM_MALLOC_RESERVE_అంతర్గత
    స్థిర స్థిరరాశి అక్షరం * ట్యాగ్ = "cpu_start";
#అయితే_ముగింపు

/* Architecture-agnostic parts of the FreeRTOS ESP-IDF port layer can go here.
 *
 * The actual call flow will be to call esp_startup_start_app() in <ARCH>/port.c,
 * which will then call esp_startup_start_app_common()
 */

/* Duplicate of inaccessible xSchedulerRunning; needed at startup to avoid counting nesting */
అస్థిర గుర్తులేని పోర్టు_x_Scheduler_Running[ పోర్టు_అంకె_PROCESSORS ] = { 0 };

/* For now, running FreeRTOS on one core and a bare metal on the other (or other OSes) */
/* is not supported. For now CONFIG_FREERTOS_UNICORE and CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE */
/* should mirror each other's values. */
/* */
/* And since this should be true, we can just check for CONFIG_FREERTOS_UNICORE. */
#ఒకవేళ CONFIG_FREERTOS_UNICORE != CONFIG_ESP_SYSTEM_SINGLE_CORE_బహుళకం
    #దోషం "FreeRTOS and system configuration mismatch regarding the use of multiple cores."
#అయితే_ముగింపు

స్థిర శూన్య main_task( శూన్య * వాదనలు );

#నిర్వచితమైతే CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
    శూన్య esp_gdbstub_init( శూన్య );
#అయితే_ముగింపు // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

బాహ్య శూన్య app_main( శూన్య );

శూన్య esp_startup_ప్రారంభం_app_common( శూన్య )
{
    #ఒకవేళ CONFIG_ESP_INT_WDT
        esp_int_wdt_init();
        /*Initialize the interrupt watch dog for CPU0. */
        esp_int_wdt_cpu_init();
    #అయితే_ముగింపు

    esp_crosscore_int_init();

    #నిర్వచితమైతే CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME
        esp_gdbstub_init();
    #అయితే_ముగింపు // CONFIG_ESP_SYSTEM_GDBSTUB_RUNTIME

    పోర్టు_పునాది_TYPE res = x_Task_Create_Pinned_గమ్యం_Core( &main_task, "main",
                                                 ESP_TASK_MAIN_దొంతర, ఖాళీ,
                                                 ESP_TASK_MAIN_PRIO, ఖాళీ, ESP_TASK_MAIN_CORE );
    ప్రతిజ్ఞా( res == pdTRUE );
    ( శూన్య ) res;
}

#ఒకవేళ !CONFIG_FREERTOS_UNICORE
    స్థిర అస్థిర bool s_other_cpu_startup_పూర్తి = false;
    స్థిర bool other_cpu_startup_idle_hook_cb( శూన్య )
    {
        s_other_cpu_startup_పూర్తి = true;
        తిరిగి true;
    }
#అయితే_ముగింపు

స్థిర శూన్య main_task( శూన్య * వాదనలు )
{
    #ఒకవేళ !CONFIG_FREERTOS_UNICORE
        /* Wait for FreeRTOS initialization to finish on other core, before replacing its startup stack */
        esp_రిజిస్టరు_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_పోర్టు_Get_Core_ID() );

        అయితే( !s_other_cpu_startup_పూర్తి )
        {
        }
        esp_deregister_freertos_idle_hook_for_cpu( other_cpu_startup_idle_hook_cb, !x_పోర్టు_Get_Core_ID() );
    #అయితే_ముగింపు

    /* [refactor-todo] check if there is a way to move the following block to esp_system startup */
    కుప్ప_caps_enable_nonos_దొంతర_heaps();

    /* Now we have startup stack RAM available for heap, enable any DMA pool memory */
    #ఒకవేళ CONFIG_SPIRAM_MALLOC_RESERVE_అంతర్గత
        ఒకవేళ( g_spiram_ok )
        {
            esp_err_t r = esp_spiram_reserve_dma_pool( CONFIG_SPIRAM_MALLOC_RESERVE_అంతర్గత );

            ఒకవేళ( r != ESP_OK )
            {
                ESP_EARLY_LOGE( ట్యాగ్, "Could not reserve internal/DMA pool (error 0x%x)", r );
                abort();
            }
        }
    #అయితే_ముగింపు /* if CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL */

    /*Initialize task wdt if configured to do so */
    #నిర్వచితమైతే CONFIG_ESP_TASK_WDT_PANIC
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, true ) );
    #లేదావేళ CONFIG_ESP_TASK_WDT
        ESP_ERROR_CHECK( esp_task_wdt_init( CONFIG_ESP_TASK_WDT_TIMEOUT_S, false ) );
    #అయితే_ముగింపు

    /*Add IDLE 0 to task wdt */
    #నిర్వచితమైతే CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
        TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU( 0 );

        ఒకవేళ( idle_0 != ఖాళీ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_కూడు( idle_0 ) );
        }
    #అయితే_ముగింపు
    /*Add IDLE 1 to task wdt */
    #నిర్వచితమైతే CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
        TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU( 1 );

        ఒకవేళ( idle_1 != ఖాళీ )
        {
            ESP_ERROR_CHECK( esp_task_wdt_కూడు( idle_1 ) );
        }
    #అయితే_ముగింపు

    app_main();
    vTaskDelete( ఖాళీ );
}

/* -------------------- Heap Related ----------------------- */

bool x_పోర్టు_Check_Valid_TCBMem( స్థిరరాశి శూన్య * ptr )
{
    తిరిగి esp_ptr_అంతర్గత( ptr ) && esp_ptr_byte_accessible( ptr );
}

bool x_Portcheck_Valid_దొంతర_Mem( స్థిరరాశి శూన్య * ptr )
{
    #నిర్వచితమైతే CONFIG_SPIRAM_ALLOW_దొంతర_EXTERNAL_జ్ఞాపకం
        తిరిగి esp_ptr_byte_accessible( ptr );
    #లేకపోతే
        తిరిగి esp_ptr_అంతర్గత( ptr ) && esp_ptr_byte_accessible( ptr );
    #అయితే_ముగింపు
}
