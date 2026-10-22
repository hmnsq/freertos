/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن "soc/cpu.h"
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "esp_intr_alloc.h"
#ضمن "esp_err.h"
#ضمن "esp_log.h"
#ضمن "sdkconfig.h"
#جے_تعریف_شدہ CONFIG_FREERTOS_SYSTICK_ورتدا_SYSTIMER
    #ضمن "soc/periph_defs.h"
    #ضمن "soc/system_reg.h"
    #ضمن "hal/systimer_hal.h"
    #ضمن "hal/systimer_ll.h"
#جے_انت

#جے_تعریف_شدہ CONFIG_PM_TRACE
    #ضمن "esp_private/pm_trace.h"
#جے_انت //CONFIG_PM_TRACE

ادھار_Type_t x_پورٹ_Sys_Tick_Handler( فراغ );

#جے_تعریف_شدہ CONFIG_FREERTOS_SYSTICK_ورتدا_CCOUNT
    خارجي فراغ _frxt_tick_timer_init( فراغ );
    خارجي فراغ xt_tick_مقسوم_علیہ_init( فراغ );

    #جے_تعریف_شدہ CONFIG_FREERTOS_CORETIMER_0
        #تعریف_کرو SYSTICK_INTR_ID    ( ETS_اندرونی_TIMER0_INTR_سروت + ETS_اندرونی_INTR_سروت_OFF )
    #جے_انت
    #جے_تعریف_شدہ CONFIG_FREERTOS_CORETIMER_1
        #تعریف_کرو SYSTICK_INTR_ID    ( ETS_اندرونی_TIMER1_INTR_سروت + ETS_اندرونی_INTR_سروت_OFF )
    #جے_انت

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    فراغ v_پورٹ_تیاری_Timer( فراغ )
    {
        /* Init the tick divisor value */
        xt_tick_مقسوم_علیہ_init();

        _frxt_tick_timer_init();
    }


#وإلاإذا CONFIG_FREERTOS_SYSTICK_ورتدا_SYSTIMER

    _Static_assert( SOC_CPU_CORES_عدد <= SOC_SYSTIMER_ALARM_عدد - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    فراغ SysTickIsrHandler( فراغ * arg );

    ساكن uint32_t s_handled_systicks[ پورٹ_عدد_PROCESSORS ] = { 0 };

    #تعریف_کرو SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_کنارا_INTR_سروت )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    فراغ v_پورٹ_تیاری_Timer( فراغ )
    {
        بنانشانی cpuid = x_پورٹ_Get_Core_ID();

        #جے_تعریف_شدہ CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ثابت بنانشانی level = ESP_INTR_FLAG_LEVEL3;
        #وإلا
            ثابت بنانشانی level = ESP_INTR_FLAG_LEVEL1;
        #جے_انت
        /* Systimer HAL layer object */
        ساكن systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_کنارا_INTR_سروت + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, عدم ) );

        إذا( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_سیٹ_counter_قدر( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0 );
            systimer_ll_apply_counter_قدر( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK );

            لكل( cpuid = 0; cpuid < SOC_CPU_CORES_عدد; cpuid++ )
            {
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, false );
            }

            لكل( cpuid = 0; cpuid < پورٹ_عدد_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_counter( &systimer_hal, alarm_id, SYSTIMER_LL_COUNTER_OS_TICK );
                systimer_hal_سیٹ_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_منوال( &systimer_hal, alarm_id, SYSTIMER_ALARM_منوال_PERIOD );
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, true );

                إذا( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_counter( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK );
                    #جے_بنا_تعریف CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_counter_قدر_advance( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #جے_انت
                }
            }
        }
        وإلا
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
    IRAM_ATTR فراغ SysTickIsrHandler( فراغ * arg )
    {
        uint32_t cpuid = x_پورٹ_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #جے_تعریف_شدہ CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #جے_انت

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        افعل
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_counter_قدر( systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            إذا( diff > 0 )
            {
                إذا( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                وإلا
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                افعل
                {
                    x_پورٹ_Sys_Tick_Handler();
                } طالما( --diff );
            }
        } طالما( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #جے_تعریف_شدہ CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #جے_انت
    }

#جے_انت // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
ادھار_Type_t x_پورٹ_Sys_Tick_Handler( فراغ )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    ادھار_Type_t ret = xTaskIncrementTick();

    إذا( ret != pdFALSE )
    {
        trace_ISR_EXIT_منزل_SCHEDULER();
        پورٹ_YIELD_FROM_ISR();
    }
    وإلا
    {
        traceISR_EXIT();
    }

    أرجع ret;
}
