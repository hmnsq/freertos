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
#అన్తర్భావ <FreeRTOS.h>
#అన్తర్భావ <task.h>
#అన్తర్భావ <queue.h>
#అన్తర్భావ <timers.h>
#అన్తర్భావ <semphr.h>

/* Standard includes. */
#అన్తర్భావ <stdio.h>

/*-----------------------------------------------------------*/

స్థిర శూన్య exampleTask( శూన్య * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

స్థిర శూన్య exampleTask( శూన్య * parameters )
{
    /* Unused parameters. */
    ( శూన్య ) parameters;

    కొరకు( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

పూర్ణాంకం ప్రధాన( శూన్య )
{
    స్థిర StaticTask_t exampleTaskTCB;
    స్థిర దొంతర_Type_t example_Task_దొంతర[ config_కనీస_దొంతర_కొలత ];

    ( శూన్య ) రాయి( "Example FreeRTOS Project\n" );

    ( శూన్య ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_కనీస_దొంతర_కొలత,
                                ఖాళీ,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_దొంతర[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    v_Task_ప్రారంభం_Scheduler();

    కొరకు( ; ; )
    {
        /* Should not reach here. */
    }

    తిరిగి 0;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_CHECK_FOR_దొంతర_అధికప్రవాహం > 0 )

    శూన్య v_Application_దొంతర_అధికప్రవాహం_Hook( TaskHandle_t xTask,
                                        అక్షరం * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( శూన్య ) xTask;
        ( శూన్య ) pcTaskName;
    }

#అయితే_ముగింపు /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
