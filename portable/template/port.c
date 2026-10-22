/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ضمن "FreeRTOS.h"
#ضمن "task.h"

BaseType_t xPortStartScheduler( فراغ )
{
    أرجع pdTRUE;
}

فراغ vPortEndScheduler( فراغ )
{
}

StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    ( فراغ ) pxTopOfStack;
    ( فراغ ) pvParameters;
    ( فراغ ) * pxCode;

    أرجع عدم;
}

فراغ vPortYield( فراغ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #𐤀𐤌 ( configNUMBER_OF_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #وإلا
    {
        vTaskSwitchContext( portGET_CORE_ID() );
    }
    #endif

    /* Start executing the task we have just switched to. */
}

ساكن فراغ prvTickISR( فراغ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #𐤀𐤌 ( configNUMBER_OF_CORES == 1 )
    {
        /* Maintain the tick count. */
        𐤀𐤌( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #وإلا
    {
        UBaseType_t ulPreviousMask;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ulPreviousMask = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        𐤀𐤌( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( portGET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ulPreviousMask );
    }
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
