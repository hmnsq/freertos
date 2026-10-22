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
#અન્તર્ભાવ <FreeRTOS.h>
#અન્તર્ભાવ <task.h>
#અન્તર્ભાવ <queue.h>
#અન્તર્ભાવ <timers.h>
#અન્તર્ભાવ <semphr.h>

/* Standard includes. */
#અન્તર્ભાવ <stdio.h>

/*-----------------------------------------------------------*/

સ્થિર શૂન્ય exampleTask( શૂન્ય * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

સ્થિર શૂન્ય exampleTask( શૂન્ય * parameters )
{
    /* Unused parameters. */
    ( શૂન્ય ) parameters;

    માટે( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

પૂર્ણાંક મુખ્ય( શૂન્ય )
{
    સ્થિર StaticTask_t exampleTaskTCB;
    સ્થિર ઢગલો_Type_t example_Task_ઢગલો[ config_MINIMAL_ઢગલો_SIZE ];

    ( શૂન્ય ) printf( "Example FreeRTOS Project\n" );

    ( શૂન્ય ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_MINIMAL_ઢગલો_SIZE,
                                ખાલી,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_ઢગલો[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    vTaskStartScheduler();

    માટે( ; ; )
    {
        /* Should not reach here. */
    }

    પાછા 0;
}
/*-----------------------------------------------------------*/

#જો ( config_CHECK_FOR_ઢગલો_OVERFLOW > 0 )

    શૂન્ય v_Application_ઢગલો_Overflow_Hook( TaskHandle_t xTask,
                                        અક્ષર * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( શૂન્ય ) xTask;
        ( શૂન્ય ) pcTaskName;
    }

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
