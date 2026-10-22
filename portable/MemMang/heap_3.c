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
 * Implementation of pvPortMalloc() and vPortFree() that relies on the
 * compilers own malloc() and free() implementations.
 *
 * This file can only be used if the linker is configured to to generate
 * a heap memory area.
 *
 * See heap_1.c, heap_2.c and heap_4.c for alternative implementations, and the
 * memory management pages of https://www.FreeRTOS.org for more information.
 */

#अन्तर्भाव <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 0 )
    #दोषः This file must not be प्रयुक्तम् यदि config_SUPPORT_DYNAMIC_आवण्टनम् is 0
#यदि_अन्तः

/*-----------------------------------------------------------*/

शून्य * pv_पत्तनम्_Malloc( size_t x_Wanted_आकार )
{
    शून्य * pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = स्मृतिं_देहि( x_Wanted_आकार );
        traceMALLOC( pvReturn, x_Wanted_आकार );
    }
    ( शून्य ) xTaskResumeAll();

    #यदि ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        यदि( pvReturn == रिक्त )
        {
            vApplicationMallocFailedHook();
        }
    }
    #यदि_अन्तः

    प्रत्यागम pvReturn;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Free( शून्य * pv )
{
    यदि( pv != रिक्त )
    {
        vTaskSuspendAll();
        {
            मुक्त( pv );
            traceFREE( pv, 0 );
        }
        ( शून्य ) xTaskResumeAll();
    }
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
शून्य v_पत्तनम्_Heap_Reset_State( शून्य )
{
    /* No state needs to be re-initialised in heap_3. */
}
/*-----------------------------------------------------------*/
