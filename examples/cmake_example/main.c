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
#ଅନ୍ତର୍ଭାଵ <FreeRTOS.h>
#ଅନ୍ତର୍ଭାଵ <task.h>
#ଅନ୍ତର୍ଭାଵ <queue.h>
#ଅନ୍ତର୍ଭାଵ <timers.h>
#ଅନ୍ତର୍ଭାଵ <semphr.h>

/* Standard includes. */
#ଅନ୍ତର୍ଭାଵ <stdio.h>

/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ exampleTask( ଶୂନ୍ୟ * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ exampleTask( ଶୂନ୍ୟ * parameters )
{
    /* Unused parameters. */
    ( ଶୂନ୍ୟ ) parameters;

    ପାଇଁ( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ( ଶୂନ୍ୟ )
{
    ସ୍ଥିର StaticTask_t exampleTaskTCB;
    ସ୍ଥିର ଗଦା_Type_t example_Task_ଗଦା[ config_MINIMAL_ଗଦା_SIZE ];

    ( ଶୂନ୍ୟ ) printf( "Example FreeRTOS Project\n" );

    ( ଶୂନ୍ୟ ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_MINIMAL_ଗଦା_SIZE,
                                ଖାଲି,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_ଗଦା[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    vTaskStartScheduler();

    ପାଇଁ( ; ; )
    {
        /* Should not reach here. */
    }

    ଫେରନ୍ତୁ 0;
}
/*-----------------------------------------------------------*/

#ଯଦି ( config_CHECK_FOR_ଗଦା_OVERFLOW > 0 )

    ଶୂନ୍ୟ v_Application_ଗଦା_Overflow_Hook( TaskHandle_t xTask,
                                        ଅକ୍ଷର * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( ଶୂନ୍ୟ ) xTask;
        ( ଶୂନ୍ୟ ) pcTaskName;
    }

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
