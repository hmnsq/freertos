/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ "soc/cpu.h"
#অন্তর্ভাৱ "FreeRTOS.h"
#অন্তর্ভাৱ "task.h"
#অন্তর্ভাৱ "esp_intr_alloc.h"
#অন্তর্ভাৱ "esp_err.h"
#অন্তর্ভাৱ "esp_log.h"
#অন্তর্ভাৱ "sdkconfig.h"
#ifdef CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
    #অন্তর্ভাৱ "soc/periph_defs.h"
    #অন্তর্ভাৱ "soc/system_reg.h"
    #অন্তর্ভাৱ "hal/systimer_hal.h"
    #অন্তর্ভাৱ "hal/systimer_ll.h"
#endif

#ifdef CONFIG_PM_TRACE
    #অন্তর্ভাৱ "esp_private/pm_trace.h"
#endif //CONFIG_PM_TRACE

BaseType_t xPortSysTickHandler( শূন্য );

#ifdef CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
    বাহ্য শূন্য _frxt_tick_timer_init( শূন্য );
    বাহ্য শূন্য xt_tick_ভাজক_init( শূন্য );

    #ifdef CONFIG_FREERTOS_CORETIMER_0
        #define SYSTICK_INTR_ID    ( ETS_INTERNAL_TIMER0_INTR_SOURCE + ETS_INTERNAL_INTR_SOURCE_OFF )
    #endif
    #ifdef CONFIG_FREERTOS_CORETIMER_1
        #define SYSTICK_INTR_ID    ( ETS_INTERNAL_TIMER1_INTR_SOURCE + ETS_INTERNAL_INTR_SOURCE_OFF )
    #endif

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    শূন্য vPortSetupTimer( শূন্য )
    {
        /* Init the tick divisor value */
        xt_tick_ভাজক_init();

        _frxt_tick_timer_init();
    }


#নোচেদ্যদি CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER

    _Static_assert( SOC_CPU_CORES_অঙ্ক <= SOC_SYSTIMER_ALARM_অঙ্ক - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    শূন্য SysTickIsrHandler( শূন্য * arg );

    স্থির uint32_t s_handled_systicks[ port_অঙ্ক_PROCESSORS ] = { 0 };

    #define SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    শূন্য vPortSetupTimer( শূন্য )
    {
        unsigned cpuid = xPortGetCoreID();

        #ifdef CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ধ্রুৱ unsigned level = ESP_INTR_FLAG_LEVEL3;
        #অন্যথা
            ধ্রুৱ unsigned level = ESP_INTR_FLAG_LEVEL1;
        #endif
        /* Systimer HAL layer object */
        স্থির systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, রিক্ত ) );

        যদি( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_set_counter_মান( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0 );
            systimer_ll_apply_counter_মান( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK );

            বাবে( cpuid = 0; cpuid < SOC_CPU_CORES_অঙ্ক; cpuid++ )
            {
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, false );
            }

            বাবে( cpuid = 0; cpuid < port_অঙ্ক_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_counter( &systimer_hal, alarm_id, SYSTIMER_LL_COUNTER_OS_TICK );
                systimer_hal_set_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_mode( &systimer_hal, alarm_id, SYSTIMER_ALARM_MODE_PERIOD );
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, true );

                যদি( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_counter( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK );
                    #ifndef CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_counter_মান_advance( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #endif
                }
            }
        }
        অন্যথা
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
    IRAM_ATTR শূন্য SysTickIsrHandler( শূন্য * arg )
    {
        uint32_t cpuid = xPortGetCoreID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #ifdef CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #endif

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        কৰা
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_counter_মান( systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            যদি( diff > 0 )
            {
                যদি( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                অন্যথা
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                কৰা
                {
                    xPortSysTickHandler();
                } যেতিয়ালৈ( --diff );
            }
        } যেতিয়ালৈ( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #ifdef CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #endif
    }

#endif // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
BaseType_t xPortSysTickHandler( শূন্য )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    BaseType_t ret = xTaskIncrementTick();

    যদি( ret != pdFALSE )
    {
        traceISR_EXIT_TO_SCHEDULER();
        portYIELD_FROM_ISR();
    }
    অন্যথা
    {
        traceISR_EXIT();
    }

    ঘূৰাই ret;
}
