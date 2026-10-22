/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "soc/cpu.h"
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "esp_intr_alloc.h"
#अन्तर्भाव "esp_err.h"
#अन्तर्भाव "esp_log.h"
#अन्तर्भाव "sdkconfig.h"
#यदि_परिभाषितम् CONFIG_FREERTOS_SYSTICK_उपयुङ्क्ते_SYSTIMER
    #अन्तर्भाव "soc/periph_defs.h"
    #अन्तर्भाव "soc/system_reg.h"
    #अन्तर्भाव "hal/systimer_hal.h"
    #अन्तर्भाव "hal/systimer_ll.h"
#यदि_अन्तः

#यदि_परिभाषितम् CONFIG_PM_TRACE
    #अन्तर्भाव "esp_private/pm_trace.h"
#यदि_अन्तः //CONFIG_PM_TRACE

आधारः_Type_t x_पत्तनम्_Sys_Tick_Handler( शून्य );

#यदि_परिभाषितम् CONFIG_FREERTOS_SYSTICK_उपयुङ्क्ते_CCOUNT
    बाह्य शून्य _frxt_tick_timer_init( शून्य );
    बाह्य शून्य xt_tick_भाजकः_init( शून्य );

    #यदि_परिभाषितम् CONFIG_FREERTOS_CORETIMER_0
        #परिभाषय SYSTICK_INTR_ID    ( ETS_आन्तरिकम्_TIMER0_INTR_SOURCE + ETS_आन्तरिकम्_INTR_SOURCE_OFF )
    #यदि_अन्तः
    #यदि_परिभाषितम् CONFIG_FREERTOS_CORETIMER_1
        #परिभाषय SYSTICK_INTR_ID    ( ETS_आन्तरिकम्_TIMER1_INTR_SOURCE + ETS_आन्तरिकम्_INTR_SOURCE_OFF )
    #यदि_अन्तः

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    शून्य v_पत्तनम्_सज्जता_Timer( शून्य )
    {
        /* Init the tick divisor value */
        xt_tick_भाजकः_init();

        _frxt_tick_timer_init();
    }


#नोचेद्यदि CONFIG_FREERTOS_SYSTICK_उपयुङ्क्ते_SYSTIMER

    _Static_assert( SOC_CPU_CORES_अङ्कः <= SOC_SYSTIMER_ALARM_अङ्कः - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    शून्य SysTickIsrHandler( शून्य * arg );

    स्थिर uint32_t s_handled_systicks[ पत्तनम्_अङ्कः_PROCESSORS ] = { 0 };

    #परिभाषय SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    शून्य v_पत्तनम्_सज्जता_Timer( शून्य )
    {
        अचिह्नित cpuid = x_पत्तनम्_Get_Core_ID();

        #यदि_परिभाषितम् CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ध्रुव अचिह्नित level = ESP_INTR_FLAG_LEVEL3;
        #अन्यथा
            ध्रुव अचिह्नित level = ESP_INTR_FLAG_LEVEL1;
        #यदि_अन्तः
        /* Systimer HAL layer object */
        स्थिर systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, रिक्त ) );

        यदि( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_समुच्चयः_गणक_मानम्( systimer_hal.dev, SYSTIMER_LL_गणक_OS_TICK, 0 );
            systimer_ll_apply_गणक_मानम्( systimer_hal.dev, SYSTIMER_LL_गणक_OS_TICK );

            प्रति( cpuid = 0; cpuid < SOC_CPU_CORES_अङ्कः; cpuid++ )
            {
                systimer_hal_गणक_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK, cpuid, false );
            }

            प्रति( cpuid = 0; cpuid < पत्तनम्_अङ्कः_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_गणक( &systimer_hal, alarm_id, SYSTIMER_LL_गणक_OS_TICK );
                systimer_hal_समुच्चयः_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_बहुलकम्( &systimer_hal, alarm_id, SYSTIMER_ALARM_बहुलकम्_PERIOD );
                systimer_hal_गणक_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK, cpuid, true );

                यदि( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_गणक( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK );
                    #यदि_अपरिभाषितम् CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_गणक_मानम्_advance( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #यदि_अन्तः
                }
            }
        }
        अन्यथा
        {
            uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;
            systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
        }
    }

/**
 * @brief Systimer interrupt handler.
 *
 * The Systimer interrupt for SysTick works in periodic mode no need to calc the next alarm.
 * If a timer interrupt is ever serviced more than one tick late, it is necessary to process multiple ticks.
 */
    IRAM_ATTR शून्य SysTickIsrHandler( शून्य * arg )
    {
        uint32_t cpuid = x_पत्तनम्_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #यदि_परिभाषितम् CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #यदि_अन्तः

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        कुरु
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_गणक_मानम्( systimer_hal, SYSTIMER_LL_गणक_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            यदि( diff > 0 )
            {
                यदि( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                अन्यथा
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                कुरु
                {
                    x_पत्तनम्_Sys_Tick_Handler();
                } यावत्( --diff );
            }
        } यावत्( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #यदि_परिभाषितम् CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #यदि_अन्तः
    }

#यदि_अन्तः // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
आधारः_Type_t x_पत्तनम्_Sys_Tick_Handler( शून्य )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    आधारः_Type_t ret = xTaskIncrementTick();

    यदि( ret != pdFALSE )
    {
        trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
        पत्तनम्_YIELD_FROM_ISR();
    }
    अन्यथा
    {
        traceISR_EXIT();
    }

    प्रत्यागम ret;
}
