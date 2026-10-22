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
#ਅਨ੍ਤਰ੍ਭਾਵ <FreeRTOS.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <task.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <queue.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <timers.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <semphr.h>

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ exampleTask( ਖਾਲੀ * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ exampleTask( ਖਾਲੀ * parameters )
{
    /* Unused parameters. */
    ( ਖਾਲੀ ) parameters;

    ਲਈ( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

ਪੂਰਨ ਮੁੱਖ( ਖਾਲੀ )
{
    ਸਥਿਰ StaticTask_t exampleTaskTCB;
    ਸਥਿਰ ਢੇਰ_Type_t example_Task_ਢੇਰ[ config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ ];

    ( ਖਾਲੀ ) ਲਿਖੋ( "Example FreeRTOS Project\n" );

    ( ਖਾਲੀ ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ,
                                ਨਿਰਾ,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_ਢੇਰ[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    v_Task_ਸ਼ੁਰੂ_Scheduler();

    ਲਈ( ; ; )
    {
        /* Should not reach here. */
    }

    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

#ਜੇ ( config_CHECK_FOR_ਢੇਰ_ਉਛਾਲ > 0 )

    ਖਾਲੀ v_Application_ਢੇਰ_ਉਛਾਲ_Hook( TaskHandle_t xTask,
                                        ਅੱਖਰ * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( ਖਾਲੀ ) xTask;
        ( ਖਾਲੀ ) pcTaskName;
    }

#ਜੇ_ਅੰਤ /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
