/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ "soc/cpu.h"
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "esp_intr_alloc.h"
#అన్తర్భావ "esp_err.h"
#అన్తర్భావ "esp_log.h"
#అన్తర్భావ "sdkconfig.h"
#నిర్వచితమైతే CONFIG_FREERTOS_SYSTICK_ఉపయోగిస్తుంది_SYSTIMER
    #అన్తర్భావ "soc/periph_defs.h"
    #అన్తర్భావ "soc/system_reg.h"
    #అన్తర్భావ "hal/systimer_hal.h"
    #అన్తర్భావ "hal/systimer_ll.h"
#అయితే_ముగింపు

#నిర్వచితమైతే CONFIG_PM_TRACE
    #అన్తర్భావ "esp_private/pm_trace.h"
#అయితే_ముగింపు //CONFIG_PM_TRACE

పునాది_Type_t x_పోర్టు_Sys_Tick_Handler( శూన్య );

#నిర్వచితమైతే CONFIG_FREERTOS_SYSTICK_ఉపయోగిస్తుంది_CCOUNT
    బాహ్య శూన్య _frxt_tick_timer_init( శూన్య );
    బాహ్య శూన్య xt_tick_భాజకం_init( శూన్య );

    #నిర్వచితమైతే CONFIG_FREERTOS_CORETIMER_0
        #నిర్వచించు SYSTICK_INTR_ID    ( ETS_అంతర్గత_TIMER0_INTR_ఆధారం + ETS_అంతర్గత_INTR_ఆధారం_OFF )
    #అయితే_ముగింపు
    #నిర్వచితమైతే CONFIG_FREERTOS_CORETIMER_1
        #నిర్వచించు SYSTICK_INTR_ID    ( ETS_అంతర్గత_TIMER1_INTR_ఆధారం + ETS_అంతర్గత_INTR_ఆధారం_OFF )
    #అయితే_ముగింపు

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    శూన్య v_పోర్టు_అమరిక_Timer( శూన్య )
    {
        /* Init the tick divisor value */
        xt_tick_భాజకం_init();

        _frxt_tick_timer_init();
    }


#లేదావేళ CONFIG_FREERTOS_SYSTICK_ఉపయోగిస్తుంది_SYSTIMER

    _Static_assert( SOC_CPU_CORES_అంకె <= SOC_SYSTIMER_ALARM_అంకె - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    శూన్య SysTickIsrHandler( శూన్య * arg );

    స్థిర uint32_t s_handled_systicks[ పోర్టు_అంకె_PROCESSORS ] = { 0 };

    #నిర్వచించు SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_అంచు_INTR_ఆధారం )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    శూన్య v_పోర్టు_అమరిక_Timer( శూన్య )
    {
        గుర్తులేని cpuid = x_పోర్టు_Get_Core_ID();

        #నిర్వచితమైతే CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            స్థిరరాశి గుర్తులేని level = ESP_INTR_FLAG_LEVEL3;
        #లేకపోతే
            స్థిరరాశి గుర్తులేని level = ESP_INTR_FLAG_LEVEL1;
        #అయితే_ముగింపు
        /* Systimer HAL layer object */
        స్థిర systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_అంచు_INTR_ఆధారం + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, ఖాళీ ) );

        ఒకవేళ( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_సమితి_counter_విలువ( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0 );
            systimer_ll_apply_counter_విలువ( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK );

            కొరకు( cpuid = 0; cpuid < SOC_CPU_CORES_అంకె; cpuid++ )
            {
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, false );
            }

            కొరకు( cpuid = 0; cpuid < పోర్టు_అంకె_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_counter( &systimer_hal, alarm_id, SYSTIMER_LL_COUNTER_OS_TICK );
                systimer_hal_సమితి_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_బహుళకం( &systimer_hal, alarm_id, SYSTIMER_ALARM_బహుళకం_PERIOD );
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, true );

                ఒకవేళ( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_counter( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK );
                    #నిర్వచితం_కాకపోతే CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_counter_విలువ_advance( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #అయితే_ముగింపు
                }
            }
        }
        లేకపోతే
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
    IRAM_ATTR శూన్య SysTickIsrHandler( శూన్య * arg )
    {
        uint32_t cpuid = x_పోర్టు_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #నిర్వచితమైతే CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #అయితే_ముగింపు

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        చేయి
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_counter_విలువ( systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            ఒకవేళ( diff > 0 )
            {
                ఒకవేళ( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                లేకపోతే
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                చేయి
                {
                    x_పోర్టు_Sys_Tick_Handler();
                } అయితే( --diff );
            }
        } అయితే( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #నిర్వచితమైతే CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #అయితే_ముగింపు
    }

#అయితే_ముగింపు // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
పునాది_Type_t x_పోర్టు_Sys_Tick_Handler( శూన్య )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    పునాది_Type_t ret = xTaskIncrementTick();

    ఒకవేళ( ret != pdFALSE )
    {
        trace_ISR_EXIT_గమ్యం_SCHEDULER();
        పోర్టు_YIELD_FROM_ISR();
    }
    లేకపోతే
    {
        traceISR_EXIT();
    }

    తిరిగి ret;
}
