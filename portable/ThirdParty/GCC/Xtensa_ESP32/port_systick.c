/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "soc/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_intr_alloc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_err.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "esp_log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sdkconfig.h"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_SYSTICK_ਵਰਤਦਾ_SYSTIMER
    #ਅਨ੍ਤਰ੍ਭਾਵ "soc/periph_defs.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "soc/system_reg.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "hal/systimer_hal.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "hal/systimer_ll.h"
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_PM_TRACE
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_private/pm_trace.h"
#ਜੇ_ਅੰਤ //CONFIG_PM_TRACE

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ );

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_SYSTICK_ਵਰਤਦਾ_CCOUNT
    ਬਾਹਰੀ ਖਾਲੀ _frxt_tick_timer_init( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ xt_tick_ਭਾਜਕ_init( ਖਾਲੀ );

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_CORETIMER_0
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SYSTICK_INTR_ID    ( ETS_ਅੰਦਰੂਨੀ_TIMER0_INTR_ਸਰੋਤ + ETS_ਅੰਦਰੂਨੀ_INTR_ਸਰੋਤ_OFF )
    #ਜੇ_ਅੰਤ
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_CORETIMER_1
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SYSTICK_INTR_ID    ( ETS_ਅੰਦਰੂਨੀ_TIMER1_INTR_ਸਰੋਤ + ETS_ਅੰਦਰੂਨੀ_INTR_ਸਰੋਤ_OFF )
    #ਜੇ_ਅੰਤ

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer( ਖਾਲੀ )
    {
        /* Init the tick divisor value */
        xt_tick_ਭਾਜਕ_init();

        _frxt_tick_timer_init();
    }


#ਜਾਂਜੇ CONFIG_FREERTOS_SYSTICK_ਵਰਤਦਾ_SYSTIMER

    _Static_assert( SOC_CPU_CORES_ਅੰਕ <= SOC_SYSTIMER_ALARM_ਅੰਕ - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    ਖਾਲੀ SysTickIsrHandler( ਖਾਲੀ * arg );

    ਸਥਿਰ uint32_t s_handled_systicks[ ਪੋਰਟ_ਅੰਕ_PROCESSORS ] = { 0 };

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_ਕਿਨਾਰਾ_INTR_ਸਰੋਤ )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer( ਖਾਲੀ )
    {
        ਬਿਨਾਨਿਸ਼ਾਨੀ cpuid = x_ਪੋਰਟ_Get_Core_ID();

        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ level = ESP_INTR_FLAG_LEVEL3;
        #ਨਹੀਂਤਾਂ
            ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ level = ESP_INTR_FLAG_LEVEL1;
        #ਜੇ_ਅੰਤ
        /* Systimer HAL layer object */
        ਸਥਿਰ systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_ਕਿਨਾਰਾ_INTR_ਸਰੋਤ + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, ਨਿਰਾ ) );

        ਜੇ( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_ਸੈੱਟ_counter_ਮੁੱਲ( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0 );
            systimer_ll_apply_counter_ਮੁੱਲ( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK );

            ਲਈ( cpuid = 0; cpuid < SOC_CPU_CORES_ਅੰਕ; cpuid++ )
            {
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, false );
            }

            ਲਈ( cpuid = 0; cpuid < ਪੋਰਟ_ਅੰਕ_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_counter( &systimer_hal, alarm_id, SYSTIMER_LL_COUNTER_OS_TICK );
                systimer_hal_ਸੈੱਟ_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_ਬਹੁਲਕ( &systimer_hal, alarm_id, SYSTIMER_ALARM_ਬਹੁਲਕ_PERIOD );
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, true );

                ਜੇ( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_counter( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK );
                    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_counter_ਮੁੱਲ_advance( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #ਜੇ_ਅੰਤ
                }
            }
        }
        ਨਹੀਂਤਾਂ
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
    IRAM_ATTR ਖਾਲੀ SysTickIsrHandler( ਖਾਲੀ * arg )
    {
        uint32_t cpuid = x_ਪੋਰਟ_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #ਜੇ_ਅੰਤ

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        ਕਰੋ
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_counter_ਮੁੱਲ( systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            ਜੇ( diff > 0 )
            {
                ਜੇ( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                ਨਹੀਂਤਾਂ
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                ਕਰੋ
                {
                    x_ਪੋਰਟ_Sys_Tick_Handler();
                } ਜਦੋਂ( --diff );
            }
        } ਜਦੋਂ( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #ਜੇ_ਅੰਤ
    }

#ਜੇ_ਅੰਤ // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    ਅਧਾਰ_Type_t ret = xTaskIncrementTick();

    ਜੇ( ret != pdFALSE )
    {
        trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
        ਪੋਰਟ_YIELD_FROM_ISR();
    }
    ਨਹੀਂਤਾਂ
    {
        traceISR_EXIT();
    }

    ਵਾਪਸ ret;
}
