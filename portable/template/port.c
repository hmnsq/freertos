/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ضمن "FreeRTOS.h"
#ضمن "task.h"

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    أرجع pdTRUE;
}

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
}

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    ( فراغ ) px_چوٹی_دا_ڈھیر;
    ( فراغ ) pvParameters;
    ( فراغ ) * px_کوڈ;

    أرجع عدم;
}

فراغ v_پورٹ_Yield( فراغ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #إذا ( config_نمبر_دا_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #وإلا
    {
        vTaskSwitchContext( پورٹ_GET_CORE_ID() );
    }
    #جے_انت

    /* Start executing the task we have just switched to. */
}

ساكن فراغ prvTickISR( فراغ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #إذا ( config_نمبر_دا_CORES == 1 )
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
        UBaseType_t ul_پچھلا_نقاب;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_پچھلا_نقاب = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( پورٹ_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_پچھلا_نقاب );
    }
    #جے_انت /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
