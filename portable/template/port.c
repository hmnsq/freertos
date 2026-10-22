/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    തിരികെ pdTRUE;
}

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
}

അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    ( ശൂന്യം ) px_മുകൾ_Of_അട്ടി;
    ( ശൂന്യം ) pvParameters;
    ( ശൂന്യം ) * pxCode;

    തിരികെ ശൂന്യ;
}

ശൂന്യം vPortYield( ശൂന്യം )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #അല്ലെങ്കിൽ
    {
        vTaskSwitchContext( portGET_CORE_ID() );
    }
    #endif

    /* Start executing the task we have just switched to. */
}

സ്ഥിതം ശൂന്യം prvTickISR( ശൂന്യം )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #എങ്കിൽ ( config_സംഖ്യ_OF_CORES == 1 )
    {
        /* Maintain the tick count. */
        എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #അല്ലെങ്കിൽ
    {
        UBaseType_t ulPreviousMask;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ulPreviousMask = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( portGET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ulPreviousMask );
    }
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
