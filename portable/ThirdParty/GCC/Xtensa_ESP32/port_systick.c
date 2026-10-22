/*
 * SPDX-FileCopyrightText: 2017-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश "soc/cpu.h"
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "esp_intr_alloc.h"
#समावेश "esp_err.h"
#समावेश "esp_log.h"
#समावेश "sdkconfig.h"
#अगर_घोषित CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
    #समावेश "soc/periph_defs.h"
    #समावेश "soc/system_reg.h"
    #समावेश "hal/systimer_hal.h"
    #समावेश "hal/systimer_ll.h"
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_TRACE
    #समावेश "esp_private/pm_trace.h"
#पूर्ण_अगर //CONFIG_PM_TRACE

BaseType_t xPortSysTickHandler( व्योम );

#अगर_घोषित CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
    बाह्य व्योम _frxt_tick_timer_init( व्योम );
    बाह्य व्योम xt_tick_भाजक_init( व्योम );

    #अगर_घोषित CONFIG_FREERTOS_CORETIMER_0
        #घोषणा SYSTICK_INTR_ID    ( ETS_INTERNAL_TIMER0_INTR_SOURCE + ETS_INTERNAL_INTR_SOURCE_OFF )
    #पूर्ण_अगर
    #अगर_घोषित CONFIG_FREERTOS_CORETIMER_1
        #घोषणा SYSTICK_INTR_ID    ( ETS_INTERNAL_TIMER1_INTR_SOURCE + ETS_INTERNAL_INTR_SOURCE_OFF )
    #पूर्ण_अगर

/**
 * @brief Initialize CCONT timer to generate the tick interrupt
 *
 */
    व्योम vPortSetupTimer( व्योम )
    {
        /* Init the tick divisor value */
        xt_tick_भाजक_init();

        _frxt_tick_timer_init();
    }


#या_अगर CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER

    _Static_assert( SOC_CPU_CORES_अंक <= SOC_SYSTIMER_ALARM_अंक - 1, "the number of cores must match the number of core alarms in SYSTIMER" );

    व्योम SysTickIsrHandler( व्योम * arg );

    अटल uint32_t s_handled_systicks[ port_अंक_PROCESSORS ] = { 0 };

    #घोषणा SYSTICK_INTR_ID    ( ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE )

/**
 * @brief Set up the systimer peripheral to generate the tick interrupt
 *
 * Both timer alarms are configured in periodic mode.
 * It is done at the same time so SysTicks for both CPUs occur at the same time or very close.
 * Shifts a time of triggering interrupts for core 0 and core 1.
 */
    व्योम vPortSetupTimer( व्योम )
    {
        अचिन्हित cpuid = xPortGetCoreID();

        #अगर_घोषित CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL3
            स्थिर अचिन्हित level = ESP_INTR_FLAG_LEVEL3;
        #अन्यथा
            स्थिर अचिन्हित level = ESP_INTR_FLAG_LEVEL1;
        #पूर्ण_अगर
        /* Systimer HAL layer object */
        अटल systimer_hal_context_t systimer_hal;
        /* set system timer interrupt vector */
        ESP_ERROR_CHECK( esp_intr_alloc( ETS_SYSTIMER_TARGET0_EDGE_INTR_SOURCE + cpuid, ESP_INTR_FLAG_IRAM | level, SysTickIsrHandler, &systimer_hal, शून्य ) );

        अगर( cpuid == 0 )
        {
            systimer_hal_init( &systimer_hal );
            systimer_ll_set_गणक_मूल्य( systimer_hal.dev, SYSTIMER_LL_गणक_OS_TICK, 0 );
            systimer_ll_apply_गणक_मूल्य( systimer_hal.dev, SYSTIMER_LL_गणक_OS_TICK );

            क्रम( cpuid = 0; cpuid < SOC_CPU_CORES_अंक; cpuid++ )
            {
                systimer_hal_गणक_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK, cpuid, false );
            }

            क्रम( cpuid = 0; cpuid < port_अंक_PROCESSORS; ++cpuid )
            {
                uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

                /* configure the timer */
                systimer_hal_connect_alarm_गणक( &systimer_hal, alarm_id, SYSTIMER_LL_गणक_OS_TICK );
                systimer_hal_set_alarm_period( &systimer_hal, alarm_id, 1000000UL / CONFIG_FREERTOS_HZ );
                systimer_hal_select_alarm_mode( &systimer_hal, alarm_id, SYSTIMER_ALARM_MODE_PERIOD );
                systimer_hal_गणक_can_stall_by_cpu( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK, cpuid, true );

                अगर( cpuid == 0 )
                {
                    systimer_hal_enable_alarm_int( &systimer_hal, alarm_id );
                    systimer_hal_enable_गणक( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK );
                    #अगर_अघोषित CONFIG_FREERTOS_UNICORE
                        /* SysTick of core 0 and core 1 are shifted by half of period */
                        systimer_hal_गणक_मूल्य_advance( &systimer_hal, SYSTIMER_LL_गणक_OS_TICK, 1000000UL / CONFIG_FREERTOS_HZ / 2 );
                    #पूर्ण_अगर
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
    IRAM_ATTR व्योम SysTickIsrHandler( व्योम * arg )
    {
        uint32_t cpuid = xPortGetCoreID();
        systimer_hal_context_t * systimer_hal = ( systimer_hal_context_t * ) arg;

        #अगर_घोषित CONFIG_PM_TRACE
            ESP_PM_TRACE_ENTER( TICK, cpuid );
        #पूर्ण_अगर

        uint32_t alarm_id = SYSTIMER_LL_ALARM_OS_TICK_CORE0 + cpuid;

        करो
        {
            systimer_ll_clear_alarm_int( systimer_hal->dev, alarm_id );

            uint32_t diff = systimer_hal_get_गणक_मूल्य( systimer_hal, SYSTIMER_LL_गणक_OS_TICK ) / systimer_ll_get_alarm_period( systimer_hal->dev, alarm_id ) - s_handled_systicks[ cpuid ];

            अगर( diff > 0 )
            {
                अगर( s_handled_systicks[ cpuid ] == 0 )
                {
                    s_handled_systicks[ cpuid ] = diff;
                    diff = 1;
                }
                अन्यथा
                {
                    s_handled_systicks[ cpuid ] += diff;
                }

                करो
                {
                    xPortSysTickHandler();
                } जबतक( --diff );
            }
        } जबतक( systimer_ll_is_alarm_int_fired( systimer_hal->dev, alarm_id ) );

        #अगर_घोषित CONFIG_PM_TRACE
            ESP_PM_TRACE_EXIT( TICK, cpuid );
        #पूर्ण_अगर
    }

#पूर्ण_अगर // CONFIG_FREERTOS_SYSTICK_USES_CCOUNT

/**
 * @brief Handler of SysTick
 *
 * The function is called from:
 *  - _frxt_timer_int for xtensa with CONFIG_FREERTOS_SYSTICK_USES_CCOUNT
 *  - SysTickIsrHandler for xtensa with CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER
 *  - SysTickIsrHandler for riscv
 */
BaseType_t xPortSysTickHandler( व्योम )
{
    portbenchmarkIntLatency();
    traceISR_ENTER( SYSTICK_INTR_ID );
    BaseType_t ret = xTaskIncrementTick();

    अगर( ret != pdFALSE )
    {
        traceISR_EXIT_TO_SCHEDULER();
        portYIELD_FROM_ISR();
    }
    अन्यथा
    {
        traceISR_EXIT();
    }

    वापस ret;
}
