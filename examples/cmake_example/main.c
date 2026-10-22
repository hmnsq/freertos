/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * This is a simple main that will start the FreeRTOS-Kernel and run a periodic task
 * that only delays if compiled with the template port, this project will do nothing.
 * For more information on getting started please look here:
 * https://www.freertos.org/Documentation/01-FreeRTOS-quick-start/01-Beginners-guide/02-Quick-start-guide
 */

/* FreeRTOS includes. */
#ಅನ್ತರ್ಭಾವ <FreeRTOS.h>
#ಅನ್ತರ್ಭಾವ <task.h>
#ಅನ್ತರ್ಭಾವ <queue.h>
#ಅನ್ತರ್ಭಾವ <timers.h>
#ಅನ್ತರ್ಭಾವ <semphr.h>

/* Standard includes. */
#ಅನ್ತರ್ಭಾವ <stdio.h>

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ exampleTask( ಶೂನ್ಯ * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ exampleTask( ಶೂನ್ಯ * parameters )
{
    /* Unused parameters. */
    ( ಶೂನ್ಯ ) parameters;

    ಗಾಗಿ( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ( ಶೂನ್ಯ )
{
    ಸ್ಥಿರ StaticTask_t exampleTaskTCB;
    ಸ್ಥಿರ ರಾಶಿ_Type_t example_Task_ರಾಶಿ[ config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ ];

    ( ಶೂನ್ಯ ) ಬರೆ( "Example FreeRTOS Project\n" );

    ( ಶೂನ್ಯ ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ,
                                ಖಾಲಿ,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_ರಾಶಿ[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    v_Task_ಆರಂಭ_Scheduler();

    ಗಾಗಿ( ; ; )
    {
        /* Should not reach here. */
    }

    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_CHECK_FOR_ರಾಶಿ_ಅತಿಪ್ರವಾಹ > 0 )

    ಶೂನ್ಯ v_Application_ರಾಶಿ_ಅತಿಪ್ರವಾಹ_Hook( TaskHandle_t xTask,
                                        ಅಕ್ಷರ * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( ಶೂನ್ಯ ) xTask;
        ( ಶೂನ್ಯ ) pcTaskName;
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
