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

#ifndef __SECURE_CONTEXT_H__
#define __SECURE_CONTEXT_H__

/* Standard includes. */
#ضمن <stdint.h>

/* FreeRTOS includes. */
#ضمن "FreeRTOSConfig.h"

/**
 * @brief PSP value when no secure context is loaded.
 */
#define securecontext_NO_تيندنن              0x0

/**
 * @brief Invalid context ID.
 */
#define securecontextINVALID_CONTEXT_ID    0UL
/*-----------------------------------------------------------*/

/**
 * @brief Structure to represent a secure context.
 *
 * @note Since stack grows down, pucStackStart is the highest address while
 * pucStackLimit is the first address of the allocated memory.
 */
تعريفنوع بنية SecureContext
{
    uint8_t * puc_Current_تيندنن_Pointer; /**< Current value of stack pointer (PSP). */
    uint8_t * puc_تيندنن_Limit;          /**< Last location of the stack memory (PSPLIM). */
    uint8_t * puc_تيندنن_Start;          /**< First location of the stack memory. */
    فراغ * pvTaskHandle;              /**< Task handle of the task this context is associated with. */
} SecureContext_t;
/*-----------------------------------------------------------*/

/**
 * @brief Opaque handle for a secure context.
 */
تعريفنوع uint32_t SecureContextHandle_t;
/*-----------------------------------------------------------*/

/**
 * @brief Initializes the secure context management system.
 *
 * PSP is set to NULL and therefore a task must allocate and load a context
 * before calling any secure side function in the thread mode.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 */
فراغ SecureContext_Init( فراغ );

/**
 * @brief Allocates a context on the secure side.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] ulSecureStackSize Size of the stack to allocate on secure side.
 * @param[in] ulIsTaskPrivileged 1 if the calling task is privileged, 0 otherwise.
 *
 * @return Opaque context handle if context is successfully allocated, NULL
 * otherwise.
 */
#إذا ( configENABLE_MPU == 1 )
    SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_تيندنن_Size,
                                                         uint32_t ulIsTaskPrivileged,
                                                         فراغ * pvTaskHandle );
#وإلا /* configENABLE_MPU */
    SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_تيندنن_Size,
                                                         فراغ * pvTaskHandle );
#endif /* configENABLE_MPU */

/**
 * @brief Frees the given context.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] xSecureContextHandle Context handle corresponding to the
 * context to be freed.
 */
فراغ SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                فراغ * pvTaskHandle );

/**
 * @brief Loads the given context.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] xSecureContextHandle Context handle corresponding to the context
 * to be loaded.
 */
فراغ SecureContext_LoadContext( SecureContextHandle_t xSecureContextHandle,
                                فراغ * pvTaskHandle );

/**
 * @brief Saves the given context.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] xSecureContextHandle Context handle corresponding to the context
 * to be saved.
 */
فراغ SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                فراغ * pvTaskHandle );

#endif /* __SECURE_CONTEXT_H__ */
