/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ضمن "FreeRTOS.h"
#ضمن "task.h"

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    أرجع pdTRUE;
}

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
}

ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    ( فراغ ) px_چوٽي_جو_ڍير;
    ( فراغ ) pvParameters;
    ( فراغ ) * px_ڪوڊ;

    أرجع عدم;
}

فراغ v_پورٽ_Yield( فراغ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #إذا ( config_عدد_جو_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #وإلا
    {
        vTaskSwitchContext( پورٽ_GET_CORE_ID() );
    }
    #جيڪڏهن_پورو

    /* Start executing the task we have just switched to. */
}

ساكن فراغ prvTickISR( فراغ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #إذا ( config_عدد_جو_CORES == 1 )
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
        UBaseType_t ul_اڳيون_نقاب;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_اڳيون_نقاب = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( پورٽ_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_اڳيون_نقاب );
    }
    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
