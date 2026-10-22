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
#அந்தர்பாவ <FreeRTOS.h>
#அந்தர்பாவ <task.h>
#அந்தர்பாவ <queue.h>
#அந்தர்பாவ <timers.h>
#அந்தர்பாவ <semphr.h>

/* Standard includes. */
#அந்தர்பாவ <stdio.h>

/*-----------------------------------------------------------*/

நிலையான வெறுமை exampleTask( வெறுமை * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

நிலையான வெறுமை exampleTask( வெறுமை * parameters )
{
    /* Unused parameters. */
    ( வெறுமை ) parameters;

    க்கு( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

முழு முதன்மை( வெறுமை )
{
    நிலையான StaticTask_t exampleTaskTCB;
    நிலையான அடுக்கு_Type_t example_Task_அடுக்கு[ config_MINIMAL_அடுக்கு_SIZE ];

    ( வெறுமை ) printf( "Example FreeRTOS Project\n" );

    ( வெறுமை ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_MINIMAL_அடுக்கு_SIZE,
                                வெற்று,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_அடுக்கு[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    vTaskStartScheduler();

    க்கு( ; ; )
    {
        /* Should not reach here. */
    }

    திரும்பு 0;
}
/*-----------------------------------------------------------*/

#எனில் ( config_CHECK_FOR_அடுக்கு_OVERFLOW > 0 )

    வெறுமை v_Application_அடுக்கு_Overflow_Hook( TaskHandle_t xTask,
                                        எழுத்து * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( வெறுமை ) xTask;
        ( வெறுமை ) pcTaskName;
    }

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
