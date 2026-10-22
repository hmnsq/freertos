/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"

BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    ଫେରନ୍ତୁ pdTRUE;
}

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
}

ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    ( ଶୂନ୍ୟ ) px_ଶୀର୍ଷ_Of_ଗଦା;
    ( ଶୂନ୍ୟ ) pvParameters;
    ( ଶୂନ୍ୟ ) * pxCode;

    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #ଅନ୍ୟଥା
    {
        vTaskSwitchContext( portGET_CORE_ID() );
    }
    #endif

    /* Start executing the task we have just switched to. */
}

ସ୍ଥିର ଶୂନ୍ୟ prvTickISR( ଶୂନ୍ୟ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES == 1 )
    {
        /* Maintain the tick count. */
        ଯଦି( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #ଅନ୍ୟଥା
    {
        UBaseType_t ulPreviousMask;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ulPreviousMask = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        ଯଦି( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( portGET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ulPreviousMask );
    }
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
