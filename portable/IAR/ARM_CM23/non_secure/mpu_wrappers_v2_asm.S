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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS वा
 * IMPLIED, INCLUDING BUT न LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE च NONINFRINGEMENT. अन्तः NO EVENT SHALL THE AUTHORS वा
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES वा OTHER LIABILITY, WHETHER
 * अन्तः AN ACTION OF CONTRACT, TORT वा OTHERWISE, ARISING FROM, OUT OF वा अन्तः
 * CONNECTION WITH THE SOFTWARE वा THE USE वा OTHER DEALINGS अन्तः THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


    SECTION freertos_system_calls:CODE:NOROOT(2)
    THUMB
/*-----------------------------------------------------------*/

#include "FreeRTOSConfig.h"
#include "mpu_syscall_numbers.h"

#ifndef configUSE_MPU_WRAPPERS_V1
    #define configUSE_MPU_WRAPPERS_V1 0
#endif

/*-----------------------------------------------------------*/

#if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    सार्वजनिक MPU_xTaskDelayUntil
MPU_xTaskDelayUntil:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskDelayUntil_Unpriv
    MPU_xTaskDelayUntil_Priv:
        b MPU_xTaskDelayUntilImpl
    MPU_xTaskDelayUntil_Unpriv:
        svc #SYSTEM_CALL_xTaskDelayUntil
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskAbortDelay
MPU_xTaskAbortDelay:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskAbortDelay_Unpriv
    MPU_xTaskAbortDelay_Priv:
        b MPU_xTaskAbortDelayImpl
    MPU_xTaskAbortDelay_Unpriv:
        svc #SYSTEM_CALL_xTaskAbortDelay
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskDelay
MPU_vTaskDelay:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskDelay_Unpriv
    MPU_vTaskDelay_Priv:
        b MPU_vTaskDelayImpl
    MPU_vTaskDelay_Unpriv:
        svc #SYSTEM_CALL_vTaskDelay
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxTaskPriorityGet
MPU_uxTaskPriorityGet:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxTaskPriorityGet_Unpriv
    MPU_uxTaskPriorityGet_Priv:
        b MPU_uxTaskPriorityGetImpl
    MPU_uxTaskPriorityGet_Unpriv:
        svc #SYSTEM_CALL_uxTaskPriorityGet
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_eTaskGetState
MPU_eTaskGetState:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_eTaskGetState_Unpriv
    MPU_eTaskGetState_Priv:
        b MPU_eTaskGetStateImpl
    MPU_eTaskGetState_Unpriv:
        svc #SYSTEM_CALL_eTaskGetState
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskGetInfo
MPU_vTaskGetInfo:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskGetInfo_Unpriv
    MPU_vTaskGetInfo_Priv:
        b MPU_vTaskGetInfoImpl
    MPU_vTaskGetInfo_Unpriv:
        svc #SYSTEM_CALL_vTaskGetInfo
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGetIdleTaskHandle
MPU_xTaskGetIdleTaskHandle:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
    MPU_xTaskGetIdleTaskHandle_Priv:
        b MPU_xTaskGetIdleTaskHandleImpl
    MPU_xTaskGetIdleTaskHandle_Unpriv:
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskSuspend
MPU_vTaskSuspend:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskSuspend_Unpriv
    MPU_vTaskSuspend_Priv:
        b MPU_vTaskSuspendImpl
    MPU_vTaskSuspend_Unpriv:
        svc #SYSTEM_CALL_vTaskSuspend
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskResume
MPU_vTaskResume:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskResume_Unpriv
    MPU_vTaskResume_Priv:
        b MPU_vTaskResumeImpl
    MPU_vTaskResume_Unpriv:
        svc #SYSTEM_CALL_vTaskResume
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGetTickCount
MPU_xTaskGetTickCount:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGetTickCount_Unpriv
    MPU_xTaskGetTickCount_Priv:
        b MPU_xTaskGetTickCountImpl
    MPU_xTaskGetTickCount_Unpriv:
        svc #SYSTEM_CALL_xTaskGetTickCount
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxTaskGetNumberOfTasks
MPU_uxTaskGetNumberOfTasks:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxTaskGetNumberOfTasks_Unpriv
    MPU_uxTaskGetNumberOfTasks_Priv:
        b MPU_uxTaskGetNumberOfTasksImpl
    MPU_uxTaskGetNumberOfTasks_Unpriv:
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_ulTaskGetRunTimeCounter
MPU_ulTaskGetRunTimeCounter:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_ulTaskGetRunTimeCounter_Unpriv
    MPU_ulTaskGetRunTimeCounter_Priv:
        b MPU_ulTaskGetRunTimeCounterImpl
    MPU_ulTaskGetRunTimeCounter_Unpriv:
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_ulTaskGetRunTimePercent
MPU_ulTaskGetRunTimePercent:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_ulTaskGetRunTimePercent_Unpriv
    MPU_ulTaskGetRunTimePercent_Priv:
        b MPU_ulTaskGetRunTimePercentImpl
    MPU_ulTaskGetRunTimePercent_Unpriv:
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_ulTaskGetIdleRunTimePercent
MPU_ulTaskGetIdleRunTimePercent:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_ulTaskGetIdleRunTimePercent_Unpriv
    MPU_ulTaskGetIdleRunTimePercent_Priv:
        b MPU_ulTaskGetIdleRunTimePercentImpl
    MPU_ulTaskGetIdleRunTimePercent_Unpriv:
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_ulTaskGetIdleRunTimeCounter
MPU_ulTaskGetIdleRunTimeCounter:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_ulTaskGetIdleRunTimeCounter_Unpriv
    MPU_ulTaskGetIdleRunTimeCounter_Priv:
        b MPU_ulTaskGetIdleRunTimeCounterImpl
    MPU_ulTaskGetIdleRunTimeCounter_Unpriv:
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskSetApplicationTaskTag
MPU_vTaskSetApplicationTaskTag:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskSetApplicationTaskTag_Unpriv
    MPU_vTaskSetApplicationTaskTag_Priv:
        b MPU_vTaskSetApplicationTaskTagImpl
    MPU_vTaskSetApplicationTaskTag_Unpriv:
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGetApplicationTaskTag
MPU_xTaskGetApplicationTaskTag:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGetApplicationTaskTag_Unpriv
    MPU_xTaskGetApplicationTaskTag_Priv:
        b MPU_xTaskGetApplicationTaskTagImpl
    MPU_xTaskGetApplicationTaskTag_Unpriv:
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskSetThreadLocalStoragePointer
MPU_vTaskSetThreadLocalStoragePointer:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskSetThreadLocalStoragePointer_Unpriv
    MPU_vTaskSetThreadLocalStoragePointer_Priv:
        b MPU_vTaskSetThreadLocalStoragePointerImpl
    MPU_vTaskSetThreadLocalStoragePointer_Unpriv:
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_pvTaskGetThreadLocalStoragePointer
MPU_pvTaskGetThreadLocalStoragePointer:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
    MPU_pvTaskGetThreadLocalStoragePointer_Priv:
        b MPU_pvTaskGetThreadLocalStoragePointerImpl
    MPU_pvTaskGetThreadLocalStoragePointer_Unpriv:
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxTaskGetSystemState
MPU_uxTaskGetSystemState:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxTaskGetSystemState_Unpriv
    MPU_uxTaskGetSystemState_Priv:
        b MPU_uxTaskGetSystemStateImpl
    MPU_uxTaskGetSystemState_Unpriv:
        svc #SYSTEM_CALL_uxTaskGetSystemState
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxTaskGetStackHighWaterMark
MPU_uxTaskGetStackHighWaterMark:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxTaskGetStackHighWaterMark_Unpriv
    MPU_uxTaskGetStackHighWaterMark_Priv:
        b MPU_uxTaskGetStackHighWaterMarkImpl
    MPU_uxTaskGetStackHighWaterMark_Unpriv:
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxTaskGetStackHighWaterMark2
MPU_uxTaskGetStackHighWaterMark2:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxTaskGetStackHighWaterMark2_Unpriv
    MPU_uxTaskGetStackHighWaterMark2_Priv:
        b MPU_uxTaskGetStackHighWaterMark2Impl
    MPU_uxTaskGetStackHighWaterMark2_Unpriv:
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGetCurrentTaskHandle
MPU_xTaskGetCurrentTaskHandle:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
    MPU_xTaskGetCurrentTaskHandle_Priv:
        b MPU_xTaskGetCurrentTaskHandleImpl
    MPU_xTaskGetCurrentTaskHandle_Unpriv:
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGetSchedulerState
MPU_xTaskGetSchedulerState:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGetSchedulerState_Unpriv
    MPU_xTaskGetSchedulerState_Priv:
        b MPU_xTaskGetSchedulerStateImpl
    MPU_xTaskGetSchedulerState_Unpriv:
        svc #SYSTEM_CALL_xTaskGetSchedulerState
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTaskSetTimeOutState
MPU_vTaskSetTimeOutState:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTaskSetTimeOutState_Unpriv
    MPU_vTaskSetTimeOutState_Priv:
        b MPU_vTaskSetTimeOutStateImpl
    MPU_vTaskSetTimeOutState_Unpriv:
        svc #SYSTEM_CALL_vTaskSetTimeOutState
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskCheckForTimeOut
MPU_xTaskCheckForTimeOut:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskCheckForTimeOut_Unpriv
    MPU_xTaskCheckForTimeOut_Priv:
        b MPU_xTaskCheckForTimeOutImpl
    MPU_xTaskCheckForTimeOut_Unpriv:
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGenericNotifyEntry
MPU_xTaskGenericNotifyEntry:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGenericNotify_Unpriv
    MPU_xTaskGenericNotify_Priv:
        b MPU_xTaskGenericNotifyImpl
    MPU_xTaskGenericNotify_Unpriv:
        svc #SYSTEM_CALL_xTaskGenericNotify
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGenericNotifyWaitEntry
MPU_xTaskGenericNotifyWaitEntry:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGenericNotifyWait_Unpriv
    MPU_xTaskGenericNotifyWait_Priv:
        b MPU_xTaskGenericNotifyWaitImpl
    MPU_xTaskGenericNotifyWait_Unpriv:
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_ulTaskGenericNotifyTake
MPU_ulTaskGenericNotifyTake:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
    MPU_ulTaskGenericNotifyTake_Priv:
        b MPU_ulTaskGenericNotifyTakeImpl
    MPU_ulTaskGenericNotifyTake_Unpriv:
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTaskGenericNotifyStateClear
MPU_xTaskGenericNotifyStateClear:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
    MPU_xTaskGenericNotifyStateClear_Priv:
        b MPU_xTaskGenericNotifyStateClearImpl
    MPU_xTaskGenericNotifyStateClear_Unpriv:
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_ulTaskGenericNotifyValueClear
MPU_ulTaskGenericNotifyValueClear:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_ulTaskGenericNotifyValueClear_Unpriv
    MPU_ulTaskGenericNotifyValueClear_Priv:
        b MPU_ulTaskGenericNotifyValueClearImpl
    MPU_ulTaskGenericNotifyValueClear_Unpriv:
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueGenericSend
MPU_xQueueGenericSend:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueGenericSend_Unpriv
    MPU_xQueueGenericSend_Priv:
        b MPU_xQueueGenericSendImpl
    MPU_xQueueGenericSend_Unpriv:
        svc #SYSTEM_CALL_xQueueGenericSend
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxQueueMessagesWaiting
MPU_uxQueueMessagesWaiting:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxQueueMessagesWaiting_Unpriv
    MPU_uxQueueMessagesWaiting_Priv:
        b MPU_uxQueueMessagesWaitingImpl
    MPU_uxQueueMessagesWaiting_Unpriv:
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxQueueSpacesAvailable
MPU_uxQueueSpacesAvailable:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxQueueSpacesAvailable_Unpriv
    MPU_uxQueueSpacesAvailable_Priv:
        b MPU_uxQueueSpacesAvailableImpl
    MPU_uxQueueSpacesAvailable_Unpriv:
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueReceive
MPU_xQueueReceive:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueReceive_Unpriv
    MPU_xQueueReceive_Priv:
        b MPU_xQueueReceiveImpl
    MPU_xQueueReceive_Unpriv:
        svc #SYSTEM_CALL_xQueueReceive
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueuePeek
MPU_xQueuePeek:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueuePeek_Unpriv
    MPU_xQueuePeek_Priv:
        b MPU_xQueuePeekImpl
    MPU_xQueuePeek_Unpriv:
        svc #SYSTEM_CALL_xQueuePeek
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueSemaphoreTake
MPU_xQueueSemaphoreTake:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueSemaphoreTake_Unpriv
    MPU_xQueueSemaphoreTake_Priv:
        b MPU_xQueueSemaphoreTakeImpl
    MPU_xQueueSemaphoreTake_Unpriv:
        svc #SYSTEM_CALL_xQueueSemaphoreTake
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueGetMutexHolder
MPU_xQueueGetMutexHolder:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueGetMutexHolder_Unpriv
    MPU_xQueueGetMutexHolder_Priv:
        b MPU_xQueueGetMutexHolderImpl
    MPU_xQueueGetMutexHolder_Unpriv:
        svc #SYSTEM_CALL_xQueueGetMutexHolder
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueTakeMutexRecursive
MPU_xQueueTakeMutexRecursive:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueTakeMutexRecursive_Unpriv
    MPU_xQueueTakeMutexRecursive_Priv:
        b MPU_xQueueTakeMutexRecursiveImpl
    MPU_xQueueTakeMutexRecursive_Unpriv:
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueGiveMutexRecursive
MPU_xQueueGiveMutexRecursive:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueGiveMutexRecursive_Unpriv
    MPU_xQueueGiveMutexRecursive_Priv:
        b MPU_xQueueGiveMutexRecursiveImpl
    MPU_xQueueGiveMutexRecursive_Unpriv:
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueSelectFromSet
MPU_xQueueSelectFromSet:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueSelectFromSet_Unpriv
    MPU_xQueueSelectFromSet_Priv:
        b MPU_xQueueSelectFromSetImpl
    MPU_xQueueSelectFromSet_Unpriv:
        svc #SYSTEM_CALL_xQueueSelectFromSet
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xQueueAddToSet
MPU_xQueueAddToSet:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xQueueAddToSet_Unpriv
    MPU_xQueueAddToSet_Priv:
        b MPU_xQueueAddToSetImpl
    MPU_xQueueAddToSet_Unpriv:
        svc #SYSTEM_CALL_xQueueAddToSet
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vQueueAddToRegistry
MPU_vQueueAddToRegistry:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vQueueAddToRegistry_Unpriv
    MPU_vQueueAddToRegistry_Priv:
        b MPU_vQueueAddToRegistryImpl
    MPU_vQueueAddToRegistry_Unpriv:
        svc #SYSTEM_CALL_vQueueAddToRegistry
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vQueueUnregisterQueue
MPU_vQueueUnregisterQueue:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vQueueUnregisterQueue_Unpriv
    MPU_vQueueUnregisterQueue_Priv:
        b MPU_vQueueUnregisterQueueImpl
    MPU_vQueueUnregisterQueue_Unpriv:
        svc #SYSTEM_CALL_vQueueUnregisterQueue
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_pcQueueGetName
MPU_pcQueueGetName:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_pcQueueGetName_Unpriv
    MPU_pcQueueGetName_Priv:
        b MPU_pcQueueGetNameImpl
    MPU_pcQueueGetName_Unpriv:
        svc #SYSTEM_CALL_pcQueueGetName
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_pvTimerGetTimerID
MPU_pvTimerGetTimerID:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_pvTimerGetTimerID_Unpriv
    MPU_pvTimerGetTimerID_Priv:
        b MPU_pvTimerGetTimerIDImpl
    MPU_pvTimerGetTimerID_Unpriv:
        svc #SYSTEM_CALL_pvTimerGetTimerID
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTimerSetTimerID
MPU_vTimerSetTimerID:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTimerSetTimerID_Unpriv
    MPU_vTimerSetTimerID_Priv:
        b MPU_vTimerSetTimerIDImpl
    MPU_vTimerSetTimerID_Unpriv:
        svc #SYSTEM_CALL_vTimerSetTimerID
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTimerIsTimerActive
MPU_xTimerIsTimerActive:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTimerIsTimerActive_Unpriv
    MPU_xTimerIsTimerActive_Priv:
        b MPU_xTimerIsTimerActiveImpl
    MPU_xTimerIsTimerActive_Unpriv:
        svc #SYSTEM_CALL_xTimerIsTimerActive
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTimerGetTimerDaemonTaskHandle
MPU_xTimerGetTimerDaemonTaskHandle:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
    MPU_xTimerGetTimerDaemonTaskHandle_Priv:
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
    MPU_xTimerGetTimerDaemonTaskHandle_Unpriv:
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTimerGenericCommandFromTaskEntry
MPU_xTimerGenericCommandFromTaskEntry:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
    MPU_xTimerGenericCommandFromTask_Priv:
        b MPU_xTimerGenericCommandFromTaskImpl
    MPU_xTimerGenericCommandFromTask_Unpriv:
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_pcTimerGetName
MPU_pcTimerGetName:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_pcTimerGetName_Unpriv
    MPU_pcTimerGetName_Priv:
        b MPU_pcTimerGetNameImpl
    MPU_pcTimerGetName_Unpriv:
        svc #SYSTEM_CALL_pcTimerGetName
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vTimerSetReloadMode
MPU_vTimerSetReloadMode:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vTimerSetReloadMode_Unpriv
    MPU_vTimerSetReloadMode_Priv:
        b MPU_vTimerSetReloadModeImpl
    MPU_vTimerSetReloadMode_Unpriv:
        svc #SYSTEM_CALL_vTimerSetReloadMode
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTimerGetReloadMode
MPU_xTimerGetReloadMode:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTimerGetReloadMode_Unpriv
    MPU_xTimerGetReloadMode_Priv:
        b MPU_xTimerGetReloadModeImpl
    MPU_xTimerGetReloadMode_Unpriv:
        svc #SYSTEM_CALL_xTimerGetReloadMode
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxTimerGetReloadMode
MPU_uxTimerGetReloadMode:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxTimerGetReloadMode_Unpriv
    MPU_uxTimerGetReloadMode_Priv:
        b MPU_uxTimerGetReloadModeImpl
    MPU_uxTimerGetReloadMode_Unpriv:
        svc #SYSTEM_CALL_uxTimerGetReloadMode
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTimerGetPeriod
MPU_xTimerGetPeriod:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTimerGetPeriod_Unpriv
    MPU_xTimerGetPeriod_Priv:
        b MPU_xTimerGetPeriodImpl
    MPU_xTimerGetPeriod_Unpriv:
        svc #SYSTEM_CALL_xTimerGetPeriod
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xTimerGetExpiryTime
MPU_xTimerGetExpiryTime:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xTimerGetExpiryTime_Unpriv
    MPU_xTimerGetExpiryTime_Priv:
        b MPU_xTimerGetExpiryTimeImpl
    MPU_xTimerGetExpiryTime_Unpriv:
        svc #SYSTEM_CALL_xTimerGetExpiryTime
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xEventGroupWaitBitsEntry
MPU_xEventGroupWaitBitsEntry:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xEventGroupWaitBits_Unpriv
    MPU_xEventGroupWaitBits_Priv:
        b MPU_xEventGroupWaitBitsImpl
    MPU_xEventGroupWaitBits_Unpriv:
        svc #SYSTEM_CALL_xEventGroupWaitBits
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xEventGroupClearBits
MPU_xEventGroupClearBits:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xEventGroupClearBits_Unpriv
    MPU_xEventGroupClearBits_Priv:
        b MPU_xEventGroupClearBitsImpl
    MPU_xEventGroupClearBits_Unpriv:
        svc #SYSTEM_CALL_xEventGroupClearBits
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xEventGroupSetBits
MPU_xEventGroupSetBits:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xEventGroupSetBits_Unpriv
    MPU_xEventGroupSetBits_Priv:
        b MPU_xEventGroupSetBitsImpl
    MPU_xEventGroupSetBits_Unpriv:
        svc #SYSTEM_CALL_xEventGroupSetBits
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xEventGroupSync
MPU_xEventGroupSync:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xEventGroupSync_Unpriv
    MPU_xEventGroupSync_Priv:
        b MPU_xEventGroupSyncImpl
    MPU_xEventGroupSync_Unpriv:
        svc #SYSTEM_CALL_xEventGroupSync
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_uxEventGroupGetNumber
MPU_uxEventGroupGetNumber:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_uxEventGroupGetNumber_Unpriv
    MPU_uxEventGroupGetNumber_Priv:
        b MPU_uxEventGroupGetNumberImpl
    MPU_uxEventGroupGetNumber_Unpriv:
        svc #SYSTEM_CALL_uxEventGroupGetNumber
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_vEventGroupSetNumber
MPU_vEventGroupSetNumber:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_vEventGroupSetNumber_Unpriv
    MPU_vEventGroupSetNumber_Priv:
        b MPU_vEventGroupSetNumberImpl
    MPU_vEventGroupSetNumber_Unpriv:
        svc #SYSTEM_CALL_vEventGroupSetNumber
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferSend
MPU_xStreamBufferSend:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferSend_Unpriv
    MPU_xStreamBufferSend_Priv:
        b MPU_xStreamBufferSendImpl
    MPU_xStreamBufferSend_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferSend
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferReceive
MPU_xStreamBufferReceive:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferReceive_Unpriv
    MPU_xStreamBufferReceive_Priv:
        b MPU_xStreamBufferReceiveImpl
    MPU_xStreamBufferReceive_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferReceive
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferIsFull
MPU_xStreamBufferIsFull:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferIsFull_Unpriv
    MPU_xStreamBufferIsFull_Priv:
        b MPU_xStreamBufferIsFullImpl
    MPU_xStreamBufferIsFull_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferIsFull
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferIsEmpty
MPU_xStreamBufferIsEmpty:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferIsEmpty_Unpriv
    MPU_xStreamBufferIsEmpty_Priv:
        b MPU_xStreamBufferIsEmptyImpl
    MPU_xStreamBufferIsEmpty_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferSpacesAvailable
MPU_xStreamBufferSpacesAvailable:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferSpacesAvailable_Unpriv
    MPU_xStreamBufferSpacesAvailable_Priv:
        b MPU_xStreamBufferSpacesAvailableImpl
    MPU_xStreamBufferSpacesAvailable_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferBytesAvailable
MPU_xStreamBufferBytesAvailable:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferBytesAvailable_Unpriv
    MPU_xStreamBufferBytesAvailable_Priv:
        b MPU_xStreamBufferBytesAvailableImpl
    MPU_xStreamBufferBytesAvailable_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferSetTriggerLevel
MPU_xStreamBufferSetTriggerLevel:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferSetTriggerLevel_Unpriv
    MPU_xStreamBufferSetTriggerLevel_Priv:
        b MPU_xStreamBufferSetTriggerLevelImpl
    MPU_xStreamBufferSetTriggerLevel_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
/*-----------------------------------------------------------*/

    सार्वजनिक MPU_xStreamBufferNextMessageLengthBytes
MPU_xStreamBufferNextMessageLengthBytes:
    निक्षिप {r0, r1}
    mrs r0, control
    movs r1, #1
    tst r0, r1
    उद्धर {r0, r1}
    bne MPU_xStreamBufferNextMessageLengthBytes_Unpriv
    MPU_xStreamBufferNextMessageLengthBytes_Priv:
        b MPU_xStreamBufferNextMessageLengthBytesImpl
    MPU_xStreamBufferNextMessageLengthBytes_Unpriv:
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
/*-----------------------------------------------------------*/

/* Default weak implementations in case one is not available from
 * mpu_wrappers because of config options. */

    PUBWEAK MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntilImpl:
    b MPU_xTaskDelayUntilImpl

    PUBWEAK MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelayImpl:
    b MPU_xTaskAbortDelayImpl

    PUBWEAK MPU_vTaskDelayImpl
MPU_vTaskDelayImpl:
    b MPU_vTaskDelayImpl

    PUBWEAK MPU_uxTaskPriorityGetImpl
MPU_uxTaskPriorityGetImpl:
    b MPU_uxTaskPriorityGetImpl

    PUBWEAK MPU_eTaskGetStateImpl
MPU_eTaskGetStateImpl:
    b MPU_eTaskGetStateImpl

    PUBWEAK MPU_vTaskGetInfoImpl
MPU_vTaskGetInfoImpl:
    b MPU_vTaskGetInfoImpl

    PUBWEAK MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandleImpl:
    b MPU_xTaskGetIdleTaskHandleImpl

    PUBWEAK MPU_vTaskSuspendImpl
MPU_vTaskSuspendImpl:
    b MPU_vTaskSuspendImpl

    PUBWEAK MPU_vTaskResumeImpl
MPU_vTaskResumeImpl:
    b MPU_vTaskResumeImpl

    PUBWEAK MPU_xTaskGetTickCountImpl
MPU_xTaskGetTickCountImpl:
    b MPU_xTaskGetTickCountImpl

    PUBWEAK MPU_uxTaskGetNumberOfTasksImpl
MPU_uxTaskGetNumberOfTasksImpl:
    b MPU_uxTaskGetNumberOfTasksImpl

    PUBWEAK MPU_ulTaskGetRunTimeCounterImpl
MPU_ulTaskGetRunTimeCounterImpl:
    b MPU_ulTaskGetRunTimeCounterImpl

    PUBWEAK MPU_ulTaskGetRunTimePercentImpl
MPU_ulTaskGetRunTimePercentImpl:
    b MPU_ulTaskGetRunTimePercentImpl

    PUBWEAK MPU_ulTaskGetIdleRunTimePercentImpl
MPU_ulTaskGetIdleRunTimePercentImpl:
    b MPU_ulTaskGetIdleRunTimePercentImpl

    PUBWEAK MPU_ulTaskGetIdleRunTimeCounterImpl
MPU_ulTaskGetIdleRunTimeCounterImpl:
    b MPU_ulTaskGetIdleRunTimeCounterImpl

    PUBWEAK MPU_vTaskSetApplicationTaskTagImpl
MPU_vTaskSetApplicationTaskTagImpl:
    b MPU_vTaskSetApplicationTaskTagImpl

    PUBWEAK MPU_xTaskGetApplicationTaskTagImpl
MPU_xTaskGetApplicationTaskTagImpl:
    b MPU_xTaskGetApplicationTaskTagImpl

    PUBWEAK MPU_vTaskSetThreadLocalStoragePointerImpl
MPU_vTaskSetThreadLocalStoragePointerImpl:
    b MPU_vTaskSetThreadLocalStoragePointerImpl

    PUBWEAK MPU_pvTaskGetThreadLocalStoragePointerImpl
MPU_pvTaskGetThreadLocalStoragePointerImpl:
    b MPU_pvTaskGetThreadLocalStoragePointerImpl

    PUBWEAK MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemStateImpl:
    b MPU_uxTaskGetSystemStateImpl

    PUBWEAK MPU_uxTaskGetStackHighWaterMarkImpl
MPU_uxTaskGetStackHighWaterMarkImpl:
    b MPU_uxTaskGetStackHighWaterMarkImpl

    PUBWEAK MPU_uxTaskGetStackHighWaterMark2Impl
MPU_uxTaskGetStackHighWaterMark2Impl:
    b MPU_uxTaskGetStackHighWaterMark2Impl

    PUBWEAK MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandleImpl:
    b MPU_xTaskGetCurrentTaskHandleImpl

    PUBWEAK MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerStateImpl:
    b MPU_xTaskGetSchedulerStateImpl

    PUBWEAK MPU_vTaskSetTimeOutStateImpl
MPU_vTaskSetTimeOutStateImpl:
    b MPU_vTaskSetTimeOutStateImpl

    PUBWEAK MPU_xTaskCheckForTimeOutImpl
MPU_xTaskCheckForTimeOutImpl:
    b MPU_xTaskCheckForTimeOutImpl

    PUBWEAK MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotifyImpl:
    b MPU_xTaskGenericNotifyImpl

    PUBWEAK MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWaitImpl:
    b MPU_xTaskGenericNotifyWaitImpl

    PUBWEAK MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTakeImpl:
    b MPU_ulTaskGenericNotifyTakeImpl

    PUBWEAK MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClearImpl:
    b MPU_xTaskGenericNotifyStateClearImpl

    PUBWEAK MPU_ulTaskGenericNotifyValueClearImpl
MPU_ulTaskGenericNotifyValueClearImpl:
    b MPU_ulTaskGenericNotifyValueClearImpl

    PUBWEAK MPU_xQueueGenericSendImpl
MPU_xQueueGenericSendImpl:
    b MPU_xQueueGenericSendImpl

    PUBWEAK MPU_uxQueueMessagesWaitingImpl
MPU_uxQueueMessagesWaitingImpl:
    b MPU_uxQueueMessagesWaitingImpl

    PUBWEAK MPU_uxQueueSpacesAvailableImpl
MPU_uxQueueSpacesAvailableImpl:
    b MPU_uxQueueSpacesAvailableImpl

    PUBWEAK MPU_xQueueReceiveImpl
MPU_xQueueReceiveImpl:
    b MPU_xQueueReceiveImpl

    PUBWEAK MPU_xQueuePeekImpl
MPU_xQueuePeekImpl:
    b MPU_xQueuePeekImpl

    PUBWEAK MPU_xQueueSemaphoreTakeImpl
MPU_xQueueSemaphoreTakeImpl:
    b MPU_xQueueSemaphoreTakeImpl

    PUBWEAK MPU_xQueueGetMutexHolderImpl
MPU_xQueueGetMutexHolderImpl:
    b MPU_xQueueGetMutexHolderImpl

    PUBWEAK MPU_xQueueTakeMutexRecursiveImpl
MPU_xQueueTakeMutexRecursiveImpl:
    b MPU_xQueueTakeMutexRecursiveImpl

    PUBWEAK MPU_xQueueGiveMutexRecursiveImpl
MPU_xQueueGiveMutexRecursiveImpl:
    b MPU_xQueueGiveMutexRecursiveImpl

    PUBWEAK MPU_xQueueSelectFromSetImpl
MPU_xQueueSelectFromSetImpl:
    b MPU_xQueueSelectFromSetImpl

    PUBWEAK MPU_xQueueAddToSetImpl
MPU_xQueueAddToSetImpl:
    b MPU_xQueueAddToSetImpl

    PUBWEAK MPU_vQueueAddToRegistryImpl
MPU_vQueueAddToRegistryImpl:
    b MPU_vQueueAddToRegistryImpl

    PUBWEAK MPU_vQueueUnregisterQueueImpl
MPU_vQueueUnregisterQueueImpl:
    b MPU_vQueueUnregisterQueueImpl

    PUBWEAK MPU_pcQueueGetNameImpl
MPU_pcQueueGetNameImpl:
    b MPU_pcQueueGetNameImpl

    PUBWEAK MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerIDImpl:
    b MPU_pvTimerGetTimerIDImpl

    PUBWEAK MPU_vTimerSetTimerIDImpl
MPU_vTimerSetTimerIDImpl:
    b MPU_vTimerSetTimerIDImpl

    PUBWEAK MPU_xTimerIsTimerActiveImpl
MPU_xTimerIsTimerActiveImpl:
    b MPU_xTimerIsTimerActiveImpl

    PUBWEAK MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandleImpl:
    b MPU_xTimerGetTimerDaemonTaskHandleImpl

    PUBWEAK MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTaskImpl:
    b MPU_xTimerGenericCommandFromTaskImpl

    PUBWEAK MPU_pcTimerGetNameImpl
MPU_pcTimerGetNameImpl:
    b MPU_pcTimerGetNameImpl

    PUBWEAK MPU_vTimerSetReloadModeImpl
MPU_vTimerSetReloadModeImpl:
    b MPU_vTimerSetReloadModeImpl

    PUBWEAK MPU_xTimerGetReloadModeImpl
MPU_xTimerGetReloadModeImpl:
    b MPU_xTimerGetReloadModeImpl

    PUBWEAK MPU_uxTimerGetReloadModeImpl
MPU_uxTimerGetReloadModeImpl:
    b MPU_uxTimerGetReloadModeImpl

    PUBWEAK MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriodImpl:
    b MPU_xTimerGetPeriodImpl

    PUBWEAK MPU_xTimerGetExpiryTimeImpl
MPU_xTimerGetExpiryTimeImpl:
    b MPU_xTimerGetExpiryTimeImpl

    PUBWEAK MPU_xEventGroupWaitBitsImpl
MPU_xEventGroupWaitBitsImpl:
    b MPU_xEventGroupWaitBitsImpl

    PUBWEAK MPU_xEventGroupClearBitsImpl
MPU_xEventGroupClearBitsImpl:
    b MPU_xEventGroupClearBitsImpl

    PUBWEAK MPU_xEventGroupSetBitsImpl
MPU_xEventGroupSetBitsImpl:
    b MPU_xEventGroupSetBitsImpl

    PUBWEAK MPU_xEventGroupSyncImpl
MPU_xEventGroupSyncImpl:
    b MPU_xEventGroupSyncImpl

    PUBWEAK MPU_uxEventGroupGetNumberImpl
MPU_uxEventGroupGetNumberImpl:
    b MPU_uxEventGroupGetNumberImpl

    PUBWEAK MPU_vEventGroupSetNumberImpl
MPU_vEventGroupSetNumberImpl:
    b MPU_vEventGroupSetNumberImpl

    PUBWEAK MPU_xStreamBufferSendImpl
MPU_xStreamBufferSendImpl:
    b MPU_xStreamBufferSendImpl

    PUBWEAK MPU_xStreamBufferReceiveImpl
MPU_xStreamBufferReceiveImpl:
    b MPU_xStreamBufferReceiveImpl

    PUBWEAK MPU_xStreamBufferIsFullImpl
MPU_xStreamBufferIsFullImpl:
    b MPU_xStreamBufferIsFullImpl

    PUBWEAK MPU_xStreamBufferIsEmptyImpl
MPU_xStreamBufferIsEmptyImpl:
    b MPU_xStreamBufferIsEmptyImpl

    PUBWEAK MPU_xStreamBufferSpacesAvailableImpl
MPU_xStreamBufferSpacesAvailableImpl:
    b MPU_xStreamBufferSpacesAvailableImpl

    PUBWEAK MPU_xStreamBufferBytesAvailableImpl
MPU_xStreamBufferBytesAvailableImpl:
    b MPU_xStreamBufferBytesAvailableImpl

    PUBWEAK MPU_xStreamBufferSetTriggerLevelImpl
MPU_xStreamBufferSetTriggerLevelImpl:
    b MPU_xStreamBufferSetTriggerLevelImpl

    PUBWEAK MPU_xStreamBufferNextMessageLengthBytesImpl
MPU_xStreamBufferNextMessageLengthBytesImpl:
    b MPU_xStreamBufferNextMessageLengthBytesImpl

/*-----------------------------------------------------------*/

#endif /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

    अन्त
