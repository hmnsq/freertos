/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ضمن "FreeRTOS.h"
#ضمن "task.h"

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    أرجع pdTRUE;
}

فراغ v_پورت_انتها_Scheduler( فراغ )
{
}

پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    ( فراغ ) px_بالاترین_از_پشته;
    ( فراغ ) pvParameters;
    ( فراغ ) * px_کد;

    أرجع عدم;
}

فراغ v_پورت_Yield( فراغ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #إذا ( config_عدد_از_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #وإلا
    {
        vTaskSwitchContext( پورت_GET_CORE_ID() );
    }
    #پایان_اگر

    /* Start executing the task we have just switched to. */
}

ساكن فراغ prvTickISR( فراغ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #إذا ( config_عدد_از_CORES == 1 )
    {
        /* Maintain the tick count. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #وإلا
    {
        UBaseType_t ul_قبلی_ماسک;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_قبلی_ماسک = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( پورت_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_قبلی_ماسک );
    }
    #پایان_اگر /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
