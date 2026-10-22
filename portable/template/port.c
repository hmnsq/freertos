/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    प्रत्यागम pdTRUE;
}

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
}

राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    ( शून्य ) px_शिखरम्_सम्बन्धि_राशिः;
    ( शून्य ) pvParameters;
    ( शून्य ) * px_संहिता;

    प्रत्यागम रिक्त;
}

शून्य v_पत्तनम्_Yield( शून्य )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #अन्यथा
    {
        vTaskSwitchContext( पत्तनम्_GET_CORE_ID() );
    }
    #यदि_अन्तः

    /* Start executing the task we have just switched to. */
}

स्थिर शून्य prvTickISR( शून्य )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    {
        /* Maintain the tick count. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #अन्यथा
    {
        UBaseType_t ul_Previous_आवरणम्;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_Previous_आवरणम् = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( पत्तनम्_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_Previous_आवरणम् );
    }
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
