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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS किंवा
 * IMPLIED, INCLUDING BUT नाही LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE आणि NONINFRINGEMENT. मध्ये NO EVENT SHALL THE AUTHORS किंवा
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES किंवा OTHER LIABILITY, WHETHER
 * मध्ये AN ACTION OF CONTRACT, TORT किंवा OTHERWISE, ARISING FROM, OUT OF किंवा मध्ये
 * CONNECTION WITH THE SOFTWARE किंवा THE USE किंवा OTHER DEALINGS मध्ये THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include "FreeRTOSConfig.h"
#include "ISR_Support.h"

    .वैश्विक    _vPortYield
    .वैश्विक    _vPortStartFirstTask
    .वैश्विक    _vPortTickISR

    .extern    _vTaskSwitchContext
    .extern    _xTaskIncrementTick

    .text
    .align 2

/* FreeRTOS yield handler.  This is installed as the BRK software interrupt
handler. */
_vPortYield:
    /* Save the context of the current task. */
    portSAVE_CONTEXT
    /* Call the scheduler to select the next task. */
    बोलवा      !!_vTaskSwitchContext
    /* Restore the context of the next task to run. */
    portRESTORE_CONTEXT
    retb


/* Starts the scheduler by restoring the context of the task that will execute
first. */
    .align 2
_vPortStartFirstTask:
    /* Restore the context of whichever task will execute first. */
    portRESTORE_CONTEXT
    /* An interrupt stack frame is used so the task is started using RETI. */
    reti

/* FreeRTOS tick handler.  This is installed as the interval timer interrupt
handler. */
    .align 2
_vPortTickISR:

    /* Save the context of the currently executing task. */
    portSAVE_CONTEXT
    /* Call the RTOS tick function. */
    बोलवा      !!_xTaskIncrementTick
#if configUSE_PREEMPTION == 1
    /* Select the next task to run. */
    बोलवा      !!_vTaskSwitchContext
#endif
    /* Retore the context of whichever task will run next. */
    portRESTORE_CONTEXT
    reti

    .end
