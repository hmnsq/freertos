/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"

BaseType_t xPortStartScheduler( வெறுமை )
{
    திரும்பு pdTRUE;
}

வெறுமை vPortEndScheduler( வெறுமை )
{
}

அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    ( வெறுமை ) px_உச்சி_Of_அடுக்கு;
    ( வெறுமை ) pvParameters;
    ( வெறுமை ) * pxCode;

    திரும்பு வெற்று;
}

வெறுமை vPortYield( வெறுமை )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #எனில் ( config_எண்_OF_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #இல்லையெனில்
    {
        vTaskSwitchContext( portGET_CORE_ID() );
    }
    #endif

    /* Start executing the task we have just switched to. */
}

நிலையான வெறுமை prvTickISR( வெறுமை )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #எனில் ( config_எண்_OF_CORES == 1 )
    {
        /* Maintain the tick count. */
        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #இல்லையெனில்
    {
        UBaseType_t ulPreviousMask;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ulPreviousMask = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( portGET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ulPreviousMask );
    }
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
