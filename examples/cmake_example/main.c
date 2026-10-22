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
#অন্তর্ভাব <FreeRTOS.h>
#অন্তর্ভাব <task.h>
#অন্তর্ভাব <queue.h>
#অন্তর্ভাব <timers.h>
#অন্তর্ভাব <semphr.h>

/* Standard includes. */
#অন্তর্ভাব <stdio.h>

/*-----------------------------------------------------------*/

স্থির শূন্য exampleTask( শূন্য * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

স্থির শূন্য exampleTask( শূন্য * parameters )
{
    /* Unused parameters. */
    ( শূন্য ) parameters;

    জন্য( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

পূর্ণসংখ্যা প্রধান( শূন্য )
{
    স্থির StaticTask_t exampleTaskTCB;
    স্থির স্তূপ_Type_t example_Task_স্তূপ[ config_MINIMAL_স্তূপ_আকার ];

    ( শূন্য ) printf( "Example FreeRTOS Project\n" );

    ( শূন্য ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_MINIMAL_স্তূপ_আকার,
                                ফাঁকা,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_স্তূপ[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    vTaskStartScheduler();

    জন্য( ; ; )
    {
        /* Should not reach here. */
    }

    ফেরত 0;
}
/*-----------------------------------------------------------*/

#যদি ( config_CHECK_FOR_স্তূপ_OVERFLOW > 0 )

    শূন্য v_Application_স্তূপ_Overflow_Hook( TaskHandle_t xTask,
                                        অক্ষর * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( শূন্য ) xTask;
        ( শূন্য ) pcTaskName;
    }

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
