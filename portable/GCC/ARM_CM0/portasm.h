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

#यदि_अपरिभाषितम् __PORT_ASM_H__
#परिभाषय __PORT_ASM_H__

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"

/* MPU wrappers includes. */
#अन्तर्भाव "mpu_wrappers.h"

/**
 * @brief Restore the context of the first task so that the first task starts
 * executing.
 */
शून्य v_Restore_Context_सम्बन्धि_First_Task( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
आधारः_Type_t xIsPrivileged( शून्य ) __attribute__( ( naked ) );

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
शून्य vRaisePrivilege( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 *
 * Bit 0 of the CONTROL register defines the privilege level of Thread Mode.
 *  Bit[0] = 0 --> The processor is running privileged
 *  Bit[0] = 1 --> The processor is running unprivileged.
 */
शून्य vResetPrivilege( शून्य ) __attribute__( ( naked ) );

/**
 * @brief Starts the first task.
 */
शून्य vStartFirstTask( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Disables interrupts.
 */
uint32_t ul_समुच्चयः_व्यवधानम्_आवरणम्( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief Enables interrupts.
 */
शून्य v_Clear_व्यवधानम्_आवरणम्( uint32_t ul_आवरणम् ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief PendSV Exception handler.
 */
शून्य PendSV_Handler( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

/**
 * @brief SVC Handler.
 */
शून्य SVC_Handler( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* __PORT_ASM_H__ */
