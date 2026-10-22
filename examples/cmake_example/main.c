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
#समावेश <FreeRTOS.h>
#समावेश <task.h>
#समावेश <queue.h>
#समावेश <timers.h>
#समावेश <semphr.h>

/* Standard includes. */
#समावेश <stdio.h>

/*-----------------------------------------------------------*/

अटल व्योम exampleTask( व्योम * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

अटल व्योम exampleTask( व्योम * parameters )
{
    /* Unused parameters. */
    ( व्योम ) parameters;

    क्रम( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

पूर्णांक मुख्य( व्योम )
{
    अटल StaticTask_t exampleTaskTCB;
    अटल ढेर_Type_t example_Task_ढेर[ config_MINIMAL_ढेर_आकार ];

    ( व्योम ) म_लिखो( "Example FreeRTOS Project\n" );

    ( व्योम ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_MINIMAL_ढेर_आकार,
                                शून्य,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_ढेर[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    vTaskStartScheduler();

    क्रम( ; ; )
    {
        /* Should not reach here. */
    }

    वापस 0;
}
/*-----------------------------------------------------------*/

#अगर ( config_CHECK_FOR_ढेर_OVERFLOW > 0 )

    व्योम v_Application_ढेर_Overflow_Hook( TaskHandle_t xTask,
                                        अक्षर * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( व्योम ) xTask;
        ( व्योम ) pcTaskName;
    }

#पूर्ण_अगर /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
