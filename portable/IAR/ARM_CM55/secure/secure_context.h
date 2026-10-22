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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __SECURE_CONTEXT_H__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __SECURE_CONTEXT_H__

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/* FreeRTOS includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOSConfig.h"

/**
 * @brief PSP value when no secure context is loaded.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ securecontext_NO_ਢੇਰ              0x0

/**
 * @brief Invalid context ID.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ securecontextINVALID_CONTEXT_ID    0UL
/*-----------------------------------------------------------*/

/**
 * @brief Structure to represent a secure context.
 *
 * @note Since stack grows down, pucStackStart is the highest address while
 * pucStackLimit is the first address of the allocated memory.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SecureContext
{
    uint8_t * puc_Current_ਢੇਰ_ਸੂਚਕ; /**< Current value of stack pointer (PSP). */
    uint8_t * puc_ਢੇਰ_ਹੱਦਬੰਦੀ;          /**< Last location of the stack memory (PSPLIM). */
    uint8_t * puc_ਢੇਰ_ਸ਼ੁਰੂ;          /**< First location of the stack memory. */
    ਖਾਲੀ * pvTaskHandle;              /**< Task handle of the task this context is associated with. */
} SecureContext_t;
/*-----------------------------------------------------------*/

/**
 * @brief Opaque handle for a secure context.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t SecureContextHandle_t;
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
ਖਾਲੀ SecureContext_Init( ਖਾਲੀ );

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
#ਜੇ ( configENABLE_MPU == 1 )
    SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ਢੇਰ_ਮਾਪ,
                                                         uint32_t ulIsTaskPrivileged,
                                                         ਖਾਲੀ * pvTaskHandle );
#ਨਹੀਂਤਾਂ /* configENABLE_MPU */
    SecureContextHandle_t SecureContext_AllocateContext( uint32_t ul_Secure_ਢੇਰ_ਮਾਪ,
                                                         ਖਾਲੀ * pvTaskHandle );
#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/**
 * @brief Frees the given context.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] xSecureContextHandle Context handle corresponding to the
 * context to be freed.
 */
ਖਾਲੀ SecureContext_FreeContext( SecureContextHandle_t xSecureContextHandle,
                                ਖਾਲੀ * pvTaskHandle );

/**
 * @brief Loads the given context.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] xSecureContextHandle Context handle corresponding to the context
 * to be loaded.
 */
ਖਾਲੀ Secure_Context_ਲੱਦੋ_Context( SecureContextHandle_t xSecureContextHandle,
                                ਖਾਲੀ * pvTaskHandle );

/**
 * @brief Saves the given context.
 *
 * @note This function must be called in the handler mode. It is no-op if called
 * in the thread mode.
 *
 * @param[in] xSecureContextHandle Context handle corresponding to the context
 * to be saved.
 */
ਖਾਲੀ SecureContext_SaveContext( SecureContextHandle_t xSecureContextHandle,
                                ਖਾਲੀ * pvTaskHandle );

#ਜੇ_ਅੰਤ /* __SECURE_CONTEXT_H__ */
