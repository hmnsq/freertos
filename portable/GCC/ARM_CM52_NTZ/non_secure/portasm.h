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

#నిర్వచితం_కాకపోతే __PORT_ASM_H__
#నిర్వచించు __PORT_ASM_H__

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"

/* MPU wrappers includes. */
#అన్తర్భావ "mpu_wrappers.h"

/**
 * @brief Restore the context of the first task so that the first task starts
 * executing.
 */
శూన్య v_Restore_Context_యొక్క_మొదటి_Task( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
పునాది_Type_t xIsPrivileged( శూన్య ) __attribute__( ( naked ) );

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
శూన్య vRaisePrivilege( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
శూన్య vResetPrivilege( శూన్య ) __attribute__( ( naked ) );

/**
 * @brief Starts the first task.
 */
శూన్య v_ప్రారంభం_మొదటి_Task( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Disables interrupts.
 */
uint32_t ul_సమితి_అంతరాయం_ముసుగు( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Enables interrupts.
 */
శూన్య v_Clear_అంతరాయం_ముసుగు( uint32_t ul_ముసుగు ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief PendSV Exception handler.
 */
శూన్య PendSV_Handler( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief SVC Handler.
 */
శూన్య SVC_Handler( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Allocate a Secure context for the calling task.
 *
 * @param[in] ulSecureStackSize The size of the stack to be allocated on the
 * secure side for the calling task.
 */
శూన్య v_పోర్టు_Allocate_Secure_Context( uint32_t ul_Secure_దొంతర_కొలత ) __attribute__( ( naked ) );

/**
 * @brief Free the task's secure context.
 *
 * @param[in] pulTCB Pointer to the Task Control Block (TCB) of the task.
 */
శూన్య v_పోర్టు_Free_Secure_Context( uint32_t * pulTCB ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* __PORT_ASM_H__ */
