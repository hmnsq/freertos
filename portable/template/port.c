/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಹಿಂತಿರುಗಿ pdTRUE;
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
}

ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ( ಶೂನ್ಯ ) px_ತುದಿ_ದ_ರಾಶಿ;
    ( ಶೂನ್ಯ ) pvParameters;
    ( ಶೂನ್ಯ ) * px_ಸಂಕೇತ;

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    /* Save the current Context */

    /* Switch to the highest priority task that is ready to run. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    {
        vTaskSwitchContext();
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        vTaskSwitchContext( ಪೋರ್ಟ್_GET_CORE_ID() );
    }
    #ಆದರೆ_ಅಂತ್ಯ

    /* Start executing the task we have just switched to. */
}

ಸ್ಥಿರ ಶೂನ್ಯ prvTickISR( ಶೂನ್ಯ )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
     * save the context with interrupts enabled. */

    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    {
        /* Maintain the tick count. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext();
        }
    }
    #ಇಲ್ಲದಿದ್ದರೆ
    {
        UBaseType_t ul_ಹಿಂದಿನ_ಮುಖವಾಡ;

        /* Tasks or ISRs running on other cores may still in critical section in
         * multiple cores environment. Incrementing tick needs to performed in
         * critical section. */
        ul_ಹಿಂದಿನ_ಮುಖವಾಡ = taskENTER_CRITICAL_FROM_ISR();

        /* Maintain the tick count. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Switch to the highest priority task that is ready to run. */
            vTaskSwitchContext( ಪೋರ್ಟ್_GET_CORE_ID() );
        }

        taskEXIT_CRITICAL_FROM_ISR( ul_ಹಿಂದಿನ_ಮುಖವಾಡ );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */

    /* start executing the new task */
}
