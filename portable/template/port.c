/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#شامل "FreeRTOS.h"
#شامل "task.h"

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    واپس pdTRUE;
}

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
}

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    ( خالی ) px_چوٹی_کا_ڈھیر;
    ( خالی ) pvParameters;
    ( خالی ) * px_رمز;

    واپس تہی;
}

خالی v_پورٹ_Yield( خالی )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #اگر ( config_نمبر_کا_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #ورنہ
    {
        vTaskSwitchContext( پورٹ_GET_CORE_ID() );
    }
    #اگر_ختم

    /* Start executing the task we have just switched to. */
}

ساکن خالی prvTickISR( خالی )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #اگر ( config_نمبر_کا_CORES == 1 )
    {
        /* Maintain the tick count. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #ورنہ
    {
        UBaseType_t ul_پچھلا_نقاب;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_پچھلا_نقاب = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( پورٹ_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_پچھلا_نقاب );
    }
    #اگر_ختم /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
