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
#اگر_تعریف_شده CONFIG_FREERTOS_SYSTICK_استفاده_میکند_SYSTIMER
    #ضمن "soc/periph_defs.h"
    #ضمن "soc/system_reg.h"
    #ضمن "hal/systimer_hal.h"
    #ضمن "hal/systimer_ll.h"
#پایان_اگر

#اگر_تعریف_شده CONFIG_PM_TRACE
    #ضمن "esp_private/pm_trace.h"
#پایان_اگر //CONFIG_PM_TRACE

پایه_Type_t x_پورت_Sys_Tick_Handler( فراغ );

#اگر_تعریف_شده CONFIG_FREERTOS_SYSTICK_استفاده_میکند_CCOUNT
    خارجي فراغ _frxt_tick_timer_init( فراغ );
    خارجي فراغ xt_tick_مقسوم_علیه_init( فراغ );

    #اگر_تعریف_شده CONFIG_FREERTOS_CORETIMER_0
        #تعریف_کن SYSTICK_INTR_ID    ( ETS_داخلی_TIMER0_INTR_منبع + ETS_داخلی_INTR_منبع_OFF )
    #پایان_اگر
    #اگر_تعریف_شده CONFIG_FREERTOS_CORETIMER_1
        #تعریف_کن SYSTICK_INTR_ID    ( ETS_داخلی_TIMER1_INTR_منبع + ETS_داخلی_INTR_منبع_OFF )
    #پایان_اگر

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    فراغ v_پورت_راهاندازی_Timer( فراغ )
    {
        /* Init the tick divisor value */
        xt_tick_مقسوم_علیه_init();

        _frxt_tick_timer_init();
    }


#وإلاإذا CONFIG_FREERTOS_SYSTICK_استفاده_میکند_SYSTIMER

    _Static_assert( SOC_CPU_CORES_رقم <= SOC_SYSTIMER_ALARM_رقم - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    فراغ SysTickIsrHandler( فراغ * arg );

    ساكن uint32_t s_handled_systicks[ پورت_رقم_PROCESSORS ] = { 0 };

    #تعریف_کن SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_یال_INTR_منبع )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    فراغ v_پورت_راهاندازی_Timer( فراغ )
    {
        بیعلامت cpuid = x_پورت_Get_Core_ID();

        #اگر_تعریف_شده CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            ثابت بیعلامت level = ESP_INTR_FLAG_LEVEL3;
        #وإلا
            ثابت بیعلامت level = ESP_INTR_FLAG_LEVEL1;
        #پایان_اگر
        /* Systimer HAL layer object */
        ساكن systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_یال_INTR_منبع + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, عدم ) );

        إذا( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_مجموعه_counter_مقدار( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK, 0 );
            systimer_ll_apply_counter_مقدار( systimer_hal.dev, SYSTIMER_LL_COUNTER_OS_TICK );

            لكل( cpuid = 0; cpuid < SOC_CPU_CORES_رقم; cpuid++ )
            {
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, false );
            }

            لكل( cpuid = 0; cpuid < پورت_رقم_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_counter( &systimer_hal, alarm_id, SYSTIMER_LL_COUNTER_OS_TICK );
                systimer_hal_مجموعه_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_نما( &systimer_hal, alarm_id, SYSTIMER_ALARM_نما_PERIOD );
                systimer_hal_counter_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, cpuid, true );

                إذا( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_counter( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK );
                    #اگر_تعریف_نشده CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_counter_مقدار_advance( &systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #پایان_اگر
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
        uint32_t cpuid = x_پورت_Get_Core_ID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #اگر_تعریف_شده CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #پایان_اگر

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        افعل
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_counter_مقدار( systimer_hal, SYSTIMER_LL_COUNTER_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

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
                    x_پورت_Sys_Tick_Handler();
                } طالما( --diff );
            }
        } طالما( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #اگر_تعریف_شده CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #پایان_اگر
    }

#پایان_اگر // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
پایه_Type_t x_پورت_Sys_Tick_Handler( فراغ )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    پایه_Type_t ret = xTaskIncrementTick();

    إذا( ret != pdFALSE )
    {
        trace_ISR_EXIT_مقصد_SCHEDULER();
        پورت_YIELD_FROM_ISR();
    }
    وإلا
    {
        traceISR_EXIT();
    }

    أرجع ret;
}
