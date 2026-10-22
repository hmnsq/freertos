/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "soc/cpu.h"
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "esp_intr_alloc.h"
#ಅನ್ತರ್ಭಾವ "esp_err.h"
#ಅನ್ತರ್ಭಾವ "esp_log.h"
#ಅನ್ತರ್ಭಾವ "sdkconfig.h"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_SYSTICK_ಬಳಸುತ್ತದೆ_SYSTIMER
    #ಅನ್ತರ್ಭಾವ "soc/periph_defs.h"
    #ಅನ್ತರ್ಭಾವ "soc/system_reg.h"
    #ಅನ್ತರ್ಭಾವ "hal/systimer_hal.h"
    #ಅನ್ತರ್ಭಾವ "hal/systimer_ll.h"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_PM_TRACE
    #ಅನ್ತರ್ಭಾವ "esp_private/pm_trace.h"
#ಆದರೆ_ಅಂತ್ಯ //CONFIG_PM_TRACE

ತಳ_Type_t x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_SYSTICK_ಬಳಸುತ್ತದೆ_CCOUNT
    ಬಾಹ್ಯ ಶೂನ್ಯ _frxt_tick_timer_init( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ xt_tick_ಭಾಜಕ_init( ಶೂನ್ಯ );

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_CORETIMER_0
        #ವ್ಯಾಖ್ಯಾನಿಸು SYSTICK_INTR_ID    ( ETS_ಆಂತರಿಕ_TIMER0_INTR_ಮೂಲ + ETS_ಆಂತರಿಕ_INTR_ಮೂಲ_OFF )
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_CORETIMER_1
        #ವ್ಯಾಖ್ಯಾನಿಸು SYSTICK_INTR_ID    ( ETS_ಆಂತರಿಕ_TIMER1_INTR_ಮೂಲ + ETS_ಆಂತರಿಕ_INTR_ಮೂಲ_OFF )
    #ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer( ಶೂನ್ಯ )
    {
        /* Init the tick divisor value */
        xt_tick_ಭಾಜಕ_init();

        _frxt_tick_timer_init();
    }


#ಅಥವಾಆದರೆ CONFIG_FREERTOS_SYSTICK_ಬಳಸುತ್ತದೆ_SYSTIMER

    _Static_assert( SOC_CPU_CORES_ಅಂಕೆ <= SOC_SYSTIMER_ALARM_ಅಂಕೆ - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    ಶೂನ್ಯ SysTickIsrHandler( ಶೂನ್ಯ * arg );

    ಸ್ಥಿರ uint32_t s_handled_systicks[ ಪೋರ್ಟ್_ಅಂಕೆ_PROCESSORS ] = { 0 };

    #ವ್ಯಾಖ್ಯಾನಿಸು SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_ಅಂಚು_INTR_ಮೂಲ )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer( ಶೂನ್ಯ )
    {
        ಚಿಹ್ನೆರಹಿತ cpuid = x_ಪೋರ್ಟ್_Get_Core_ID();

        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ level = ESP_INTR_FLAG_LEVEL3;
        #ಇಲ್ಲದಿದ್ದರೆ
            ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ level = ESP_INTR_FLAG_LEVEL1;
        #ಆದರೆ_ಅಂತ್ಯ
        /* Systimer HAL layer object */
        ಸ್ಥಿರ systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_ಅಂಚು_INTR_ಮೂಲ + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, ಖಾಲಿ ) );

        ಆದರೆ( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_ಗಣ_counter_ಮೌಲ್ಯ( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0 );
            systimer_ll_apply_counter_ಮೌಲ್ಯ( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK );

            ಗಾಗಿ( cpuid = 0; cpuid < SOC_CPU_CORES_ಅಂಕೆ; cpuid++ )
            {
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, false );
            }

            ಗಾಗಿ( cpuid = 0; cpuid < ಪೋರ್ಟ್_ಅಂಕೆ_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_counter( &systimer_hal, alarm_id, SYSTIMER_LL_COUNTER_OS_TICK );
                systimer_hal_ಗಣ_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_ಬಹುಲಕ( &systimer_hal, alarm_id, SYSTIMER_ALARM_ಬಹುಲಕ_PERIOD );
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, true );

                ಆದರೆ( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_counter( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK );
                    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_counter_ಮೌಲ್ಯ_advance( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #ಆದರೆ_ಅಂತ್ಯ
                }
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
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
    IRAM_ATTR ಶೂನ್ಯ SysTickIsrHandler( ಶೂನ್ಯ * arg )
    {
        uint32_t cpuid = x_ಪೋರ್ಟ್_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #ಆದರೆ_ಅಂತ್ಯ

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        ಮಾಡು
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_counter_ಮೌಲ್ಯ( systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            ಆದರೆ( diff > 0 )
            {
                ಆದರೆ( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                ಮಾಡು
                {
                    x_ಪೋರ್ಟ್_Sys_Tick_Handler();
                } ಆಗ( --diff );
            }
        } ಆಗ( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #ಆದರೆ_ಅಂತ್ಯ
    }

#ಆದರೆ_ಅಂತ್ಯ // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    ತಳ_Type_t ret = xTaskIncrementTick();

    ಆದರೆ( ret != pdFALSE )
    {
        trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
        ಪೋರ್ಟ್_YIELD_FROM_ISR();
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        traceISR_EXIT();
    }

    ಹಿಂತಿರುಗಿ ret;
}
