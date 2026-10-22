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

#अगर_अघोषित __PORT_ASM_H__
#घोषणा __PORT_ASM_H__

/* Scheduler includes. */
#समावेश "FreeRTOS.h"

/* MPU wrappers includes. */
#समावेश "mpu_wrappers.h"

/**
 * @brief Restore the context of the first task so that the first task starts
 * executing.
 */
व्योम vRestoreContextOfFirstTask( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
BaseType_t xIsPrivileged( व्योम ) __attribute__( ( naked ) );

/**
 * @brief Raises the privilege level by clearing the bit 0 of the CONTROL
 * register.
 *
 * @note This is a privileged function and should only be called from the kernel
 * code.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
व्योम vRaisePrivilege( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
व्योम vResetPrivilege( व्योम ) __attribute__( ( naked ) );

/**
 * @brief Starts the first task.
 */
व्योम vStartFirstTask( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Disables interrupts.
 */
uint32_t ulSetInterruptMask( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Enables interrupts.
 */
व्योम vClearInterruptMask( uint32_t ulMask ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief PendSV Exception handler.
 */
व्योम PendSV_Handler( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief SVC Handler.
 */
व्योम SVC_Handler( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* __PORT_ASM_H__ */
