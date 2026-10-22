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
#شامل <FreeRTOS.h>
#شامل <task.h>
#شامل <queue.h>
#شامل <timers.h>
#شامل <semphr.h>

/* Standard includes. */
#شامل <stdio.h>

/*-----------------------------------------------------------*/

ساکن خالی exampleTask( خالی * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

ساکن خالی exampleTask( خالی * parameters )
{
    /* Unused parameters. */
    ( خالی ) parameters;

    برائے( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

صحیح مین( خالی )
{
    ساکن StaticTask_t exampleTaskTCB;
    ساکن ڈھیر_Type_t example_Task_ڈھیر[ config_اقل_ڈھیر_سائز ];

    ( خالی ) لکھو( "Example FreeRTOS Project\n" );

    ( خالی ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_اقل_ڈھیر_سائز,
                                تہی,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_ڈھیر[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    v_Task_آغاز_Scheduler();

    برائے( ; ; )
    {
        /* Should not reach here. */
    }

    واپس 0;
}
/*-----------------------------------------------------------*/

#اگر ( config_CHECK_FOR_ڈھیر_حد_سے_تجاوز > 0 )

    خالی v_Application_ڈھیر_حد_سے_تجاوز_Hook( TaskHandle_t xTask,
                                        حرف * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( خالی ) xTask;
        ( خالی ) pcTaskName;
    }

#اگر_ختم /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
