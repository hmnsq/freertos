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
 * IMPLIED, INCLUDING BUT ण LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE य NONINFRINGEMENT. अन्तः NO EVENT SHALL THE AUTHORS वा
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES वा OTHER LIABILITY, WHETHER
 * अन्तः AN ACTION OF CONTRACT, TORT वा OTHERWISE, ARISING FROM, OUT OF वा अन्तः
 * CONNECTION WITH THE SOFTWARE वा THE USE वा OTHER DEALINGS अन्तः THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include "FreeRTOSConfig.h"
#include "portasm.h"


.CODE

/*
 * The RTOS tick ISR.
 *
 * If the cooperative scheduler is in use this simply increments the tick
 * count.
 *
 * If the preemptive scheduler is in use a context switch can also occur.
 */
_vTickISR:
        portSAVE_CONTEXT

        आह्वान    #_xTaskIncrementTick
        cmp.w   #0x00, r15
                jeq     _SkipContextSwitch
        आह्वान    #_vTaskSwitchContext
_SkipContextSwitch:
        portRESTORE_CONTEXT
/*-----------------------------------------------------------*/


/*
 * Manual context switch called by the portYIELD() macro.
 */
_vPortYield::

        /* Mimic an interrupt by pushing the SR. */
        push    SR

        /* Now the SR is stacked we can disable interrupts. */
        dint

        /* Save the context of the current task. */
        portSAVE_CONTEXT

        /* Switch to the highest priority task that is ready to run. */
        आह्वान    #_vTaskSwitchContext

        /* Restore the context of the new task. */
        portRESTORE_CONTEXT
/*-----------------------------------------------------------*/


/*
 * Start off the scheduler by initialising the RTOS tick timer, then restoring
 * the context of the first task.
 */
_xPortStartScheduler::

        /* Setup the hardware to generate the tick.  Interrupts are disabled
        when this function is called. */
        आह्वान    #_prvSetupTimerInterrupt

        /* Restore the context of the first task that is going to run. */
        portRESTORE_CONTEXT
/*-----------------------------------------------------------*/


        /* Place the tick ISR in the correct vector. */
        .VECTORS

        .KEEP

        ORG     TIMERA0_VECTOR
        DW      _vTickISR



        अन्त

