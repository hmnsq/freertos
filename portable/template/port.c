/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ضمن "FreeRTOS.h"
#ضمن "task.h"

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    أرجع pdTRUE;
}

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
}

ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    ( فراغ ) px_سر_د_ډېری;
    ( فراغ ) pvParameters;
    ( فراغ ) * px_کوډ;

    أرجع عدم;
}

فراغ v_پورټ_Yield( فراغ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #إذا ( config_شمېره_د_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #وإلا
    {
        vTaskSwitchContext( پورټ_GET_CORE_ID() );
    }
    #د_که_پای

    /* Start executing the task we have just switched to. */
}

ساكن فراغ prvTickISR( فراغ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #إذا ( config_شمېره_د_CORES == 1 )
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
        UBaseType_t ul_پخوانی_ماسک;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_پخوانی_ماسک = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( پورټ_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_پخوانی_ماسک );
    }
    #د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
