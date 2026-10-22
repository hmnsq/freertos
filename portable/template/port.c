/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਵਾਪਸ pdTRUE;
}

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
}

ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ( ਖਾਲੀ ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    ( ਖਾਲੀ ) pvParameters;
    ( ਖਾਲੀ ) * px_ਕੋਡ;

    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #ਨਹੀਂਤਾਂ
    {
        vTaskSwitchContext( ਪੋਰਟ_GET_CORE_ID() );
    }
    #ਜੇ_ਅੰਤ

    /* Start executing the task we have just switched to. */
}

ਸਥਿਰ ਖਾਲੀ prvTickISR( ਖਾਲੀ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    {
        /* Maintain the tick count. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #ਨਹੀਂਤਾਂ
    {
        UBaseType_t ul_ਪਿਛਲਾ_ਨਕਾਬ;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_ਪਿਛਲਾ_ਨਕਾਬ = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( ਪੋਰਟ_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_ਪਿਛਲਾ_ਨਕਾਬ );
    }
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
