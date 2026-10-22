/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#شامل <stdlib.h>
#شامل <string.h>
#شامل "soc/cpu.h"
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "esp_intr_alloc.h"
#شامل "esp_err.h"
#شامل "esp_log.h"
#شامل "sdkconfig.h"
#اگر_تعریف_شدہ CONFIG_FREERTOS_SYSTICK_استعمال_کرتا_SYSTIMER
    #شامل "soc/periph_defs.h"
    #شامل "soc/system_reg.h"
    #شامل "hal/systimer_hal.h"
    #شامل "hal/systimer_ll.h"
#اگر_ختم

#اگر_تعریف_شدہ CONFIG_PM_TRACE
    #شامل "esp_private/pm_trace.h"
#اگر_ختم //CONFIG_PM_TRACE

بنیاد_Type_t x_پورٹ_Sys_Tick_Handler( خالی );

#اگر_تعریف_شدہ CONFIG_FREERTOS_SYSTICK_استعمال_کرتا_CCOUNT
    خارجی خالی _frxt_tick_timer_init( خالی );
    خارجی خالی xt_tick_مقسوم_علیہ_init( خالی );

    #اگر_تعریف_شدہ CONFIG_FREERTOS_CORETIMER_0
        #تعریف_کرو SYSTICK_INTR_ID    ( ETS_اندرونی_TIMER0_INTR_ماخذ + ETS_اندرونی_INTR_ماخذ_OFF )
    #اگر_ختم
    #اگر_تعریف_شدہ CONFIG_FREERTOS_CORETIMER_1
        #تعریف_کرو SYSTICK_INTR_ID    ( ETS_اندرونی_TIMER1_INTR_ماخذ + ETS_اندرونی_INTR_ماخذ_OFF )
    #اگر_ختم

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    خالی v_پورٹ_تیاری_Timer( خالی )
    {
        /* Init the tick divisor value */
        xt_tick_مقسوم_علیہ_init();

        _frxt_tick_timer_init();
    }


#وگرنہ_اگر CONFIG_FREERTOS_SYSTICK_استعمال_کرتا_SYSTIMER

    _Static_assert( SOC_CPU_CORES_عدد <= SOC_SYSTIMER_ALARM_عدد - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    خالی SysTickIsrHandler( خالی * arg );

    ساکن uint32_t s_handled_systicks[ پورٹ_عدد_PROCESSORS ] = { 0 };

    #تعریف_کرو SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_کنارہ_INTR_ماخذ )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    خالی v_پورٹ_تیاری_Timer( خالی )
    {
        غیرعلامتی cpuid = x_پورٹ_Get_Core_ID();

        #اگر_تعریف_شدہ CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ثابت غیرعلامتی level = ESP_INTR_FLAG_LEVEL3;
        #ورنہ
            ثابت غیرعلامتی level = ESP_INTR_FLAG_LEVEL1;
        #اگر_ختم
        /* Systimer HAL layer object */
        ساکن systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_کنارہ_INTR_ماخذ + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, تہی ) );

        اگر( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_سیٹ_شمار_قدر( systimer_hal.dev, SYSTIMER_LL_شمار_OS_TICK, 0 );
            systimer_ll_apply_شمار_قدر( systimer_hal.dev, SYSTIMER_LL_شمار_OS_TICK );

            برائے( cpuid = 0; cpuid < SOC_CPU_CORES_عدد; cpuid++ )
            {
                systimer_hal_شمار_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_شمار_OS_TICK, cpuid, false );
            }

            برائے( cpuid = 0; cpuid < پورٹ_عدد_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_شمار( &systimer_hal, alarm_id, SYSTIMER_LL_شمار_OS_TICK );
                systimer_hal_سیٹ_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_منوال( &systimer_hal, alarm_id, SYSTIMER_ALARM_منوال_PERIOD );
                systimer_hal_شمار_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_شمار_OS_TICK, cpuid, true );

                اگر( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_شمار( &systimer_hal, SYSTIMER_LL_شمار_OS_TICK );
                    #اگر_غیر_تعریف_شدہ CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_شمار_قدر_advance( &systimer_hal, SYSTIMER_LL_شمار_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #اگر_ختم
                }
            }
        }
        ورنہ
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
    IRAM_ATTR خالی SysTickIsrHandler( خالی * arg )
    {
        uint32_t cpuid = x_پورٹ_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #اگر_تعریف_شدہ CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #اگر_ختم

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        کرو
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_شمار_قدر( systimer_hal, SYSTIMER_LL_شمار_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            اگر( diff > 0 )
            {
                اگر( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                ورنہ
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                کرو
                {
                    x_پورٹ_Sys_Tick_Handler();
                } جب( --diff );
            }
        } جب( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #اگر_تعریف_شدہ CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #اگر_ختم
    }

#اگر_ختم // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
بنیاد_Type_t x_پورٹ_Sys_Tick_Handler( خالی )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    بنیاد_Type_t ret = xTaskIncrementTick();

    اگر( ret != pdFALSE )
    {
        trace_ISR_EXIT_مقصد_SCHEDULER();
        پورٹ_YIELD_FROM_ISR();
    }
    ورنہ
    {
        traceISR_EXIT();
    }

    واپس ret;
}
