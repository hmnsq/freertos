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

#شامل <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#شامل "FreeRTOS.h"
#شامل "task.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#اگر ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #غلطی This file must not be مستعمل اگر config_SUPPORT_DYNAMIC_تخصیص is 0
#اگر_ختم

/*-----------------------------------------------------------*/

خالی * pv_پورٹ_Malloc( size_t x_Wanted_سائز )
{
    خالی * pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = حافظہ_دو( x_Wanted_سائز );
        traceMALLOC( pvReturn, x_Wanted_سائز );
    }
    ( خالی ) xTaskResumeAll();

    #اگر ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        اگر( pvReturn == تہی )
        {
            vApplicationMallocFailedHook();
        }
    }
    #اگر_ختم

    واپس pvReturn;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Free( خالی * pv )
{
    اگر( pv != تہی )
    {
        vTaskSuspendAll();
        {
            آزاد( pv );
            traceFREE( pv, 0 );
        }
        ( خالی ) xTaskResumeAll();
    }
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
خالی v_پورٹ_ڈھیر_Reset_State( خالی )
{
    /* No state needs to be re-initialised in heap_3. */
}
/*-----------------------------------------------------------*/
