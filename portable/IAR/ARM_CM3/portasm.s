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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS أو
 * IMPLIED, INCLUDING BUT ليس LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE و NONINFRINGEMENT. في NO EVENT SHALL THE AUTHORS أو
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES أو OTHER LIABILITY, WHETHER
 * في AN ACTION OF CONTRACT, TORT أو OTHERWISE, ARISING FROM, OUT OF أو في
 * CONNECTION WITH THE SOFTWARE أو THE USE أو OTHER DEALINGS في THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include <FreeRTOSConfig.h>

    RSEG    CODE:CODE(2)
    thumb

    خارجي pxCurrentTCB
    خارجي vTaskSwitchContext

    عام x_پورٹ_Pend_SVHandler
    عام v_پورٹ_SVCHandler
    عام vPortStartFirstTask



/*-----------------------------------------------------------*/

x_پورٹ_Pend_SVHandler:
    mrs r0, psp
    isb
    ldr r3, =pxCurrentTCB           /* Get the location of the current TCB. */
    ldr r2, [r3]

    stmdb r0!, {r4-r11}             /* Save the remaining registers. */
    str r0, [r2]                    /* Save the new top of stack into the first member of the TCB. */

    stmdb sp!, {r3, r14}
    mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
    msr basepri, r0
    dsb
    isb
    bl vTaskSwitchContext
    mov r0, #0
    msr basepri, r0
    ldmia sp!, {r3, r14}

    ldr r1, [r3]
    ldr r0, [r1]                    /* The first item in pxCurrentTCB is the task top of stack. */
    ldmia r0!, {r4-r11}             /* Pop the registers. */
    msr psp, r0
    isb
    bx r14


/*-----------------------------------------------------------*/

v_پورٹ_SVCHandler:
    /* Get the location of the current TCB. */
    ldr r3, =pxCurrentTCB
    ldr r1, [r3]
    ldr r0, [r1]
    /* Pop the core registers. */
    ldmia r0!, {r4-r11}
    msr psp, r0
    isb
    mov r0, #0
    msr basepri, r0
    orr r14, r14, #13
    bx r14

/*-----------------------------------------------------------*/

vPortStartFirstTask
    /* Use the NVIC offset register to locate the stack. */
    ldr r0, =0xE000ED08
    ldr r0, [r0]
    ldr r0, [r0]
    /* Set the msp back to the start of the stack. */
    msr msp, r0
    /* Call SVC to start the first task, ensuring interrupts are enabled. */
    cpsie i
    cpsie f
    dsb
    isb
    svc 0

    انته
