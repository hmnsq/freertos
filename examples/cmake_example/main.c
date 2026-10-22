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
#अन्तर्भाव <FreeRTOS.h>
#अन्तर्भाव <task.h>
#अन्तर्भाव <queue.h>
#अन्तर्भाव <timers.h>
#अन्तर्भाव <semphr.h>

/* Standard includes. */
#अन्तर्भाव <stdio.h>

/*-----------------------------------------------------------*/

स्थिर शून्य exampleTask( शून्य * parameters ) __attribute__( ( noreturn ) );

/*-----------------------------------------------------------*/

स्थिर शून्य exampleTask( शून्य * parameters )
{
    /* Unused parameters. */
    ( शून्य ) parameters;

    प्रति( ; ; )
    {
        /* Example Task Code */
        vTaskDelay( 100 ); /* delay 100 ticks */
    }
}
/*-----------------------------------------------------------*/

पूर्णाङ्क मुख्यम्( शून्य )
{
    स्थिर StaticTask_t exampleTaskTCB;
    स्थिर राशिः_Type_t example_Task_राशिः[ config_अल्पिष्ठम्_राशिः_आकार ];

    ( शून्य ) प्रारूप_लिख( "Example FreeRTOS Project\n" );

    ( शून्य ) xTaskCreateStatic( &exampleTask,
                                "example",
                                config_अल्पिष्ठम्_राशिः_आकार,
                                रिक्त,
                                configMAX_PRIORITIES - 1U,
                                &( example_Task_राशिः[ 0 ] ),
                                &( exampleTaskTCB ) );

    /* Start the scheduler. */
    vTaskStartScheduler();

    प्रति( ; ; )
    {
        /* Should not reach here. */
    }

    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

#यदि ( config_CHECK_FOR_राशिः_अतिप्रवाहः > 0 )

    शून्य v_Application_राशिः_अतिप्रवाहः_Hook( TaskHandle_t xTask,
                                        वर्ण * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( शून्य ) xTask;
        ( शून्य ) pcTaskName;
    }

#यदि_अन्तः /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
