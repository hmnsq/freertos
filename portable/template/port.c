/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#समावेश "FreeRTOS.h"
#समावेश "task.h"

BaseType_t xPortStartScheduler( व्योम )
{
    वापस pdTRUE;
}

व्योम vPortEndScheduler( व्योम )
{
}

ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    ( व्योम ) px_शीर्ष_Of_ढेर;
    ( व्योम ) pvParameters;
    ( व्योम ) * pxCode;

    वापस शून्य;
}

व्योम vPortYield( व्योम )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #अगर ( config_संख्या_OF_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #अन्यथा
    {
        vTaskSwitchContext( portGET_CORE_ID() );
    }
    #पूर्ण_अगर

    /* Start executing the task we have just switched to. */
}

अटल व्योम prvTickISR( व्योम )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #अगर ( config_संख्या_OF_CORES == 1 )
    {
        /* Maintain the tick count. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #अन्यथा
    {
        UBaseType_t ulPreviousMask;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ulPreviousMask = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( portGET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ulPreviousMask );
    }
    #पूर्ण_अगर /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
