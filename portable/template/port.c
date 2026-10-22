/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    తిరిగి pdTRUE;
}

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
}

దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    ( శూన్య ) px_శిఖరం_యొక్క_దొంతర;
    ( శూన్య ) pvParameters;
    ( శూన్య ) * px_సంకేతం;

    తిరిగి ఖాళీ;
}

శూన్య v_పోర్టు_Yield( శూన్య )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #లేకపోతే
    {
        vTaskSwitchContext( పోర్టు_GET_CORE_ID() );
    }
    #అయితే_ముగింపు

    /* Start executing the task we have just switched to. */
}

స్థిర శూన్య prvTickISR( శూన్య )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    {
        /* Maintain the tick count. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #లేకపోతే
    {
        UBaseType_t ul_మునుపటి_ముసుగు;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_మునుపటి_ముసుగు = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( పోర్టు_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_మునుపటి_ముసుగు );
    }
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
