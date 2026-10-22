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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __SECURE_HEAP_H__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __SECURE_HEAP_H__

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/**
 * @brief Allocates memory from heap.
 *
 * @param[in] xWantedSize The size of the memory to be allocated.
 *
 * @return Pointer to the memory region if the allocation is successful, NULL
 * otherwise.
 */
ਖਾਲੀ * pv_ਪੋਰਟ_Malloc( size_t x_Wanted_ਮਾਪ );

/**
 * @brief Frees the previously allocated memory.
 *
 * @param[in] pv Pointer to the memory to be freed.
 */
ਖਾਲੀ v_ਪੋਰਟ_Free( ਖਾਲੀ * pv );

/**
 * @brief Get the free heap size.
 *
 * @return Free heap size.
 */
size_t x_ਪੋਰਟ_Get_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ );

/**
 * @brief Get the minimum ever free heap size.
 *
 * @return Minimum ever free heap size.
 */
size_t x_ਪੋਰਟ_Get_Minimum_Ever_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ );

#ਜੇ_ਅੰਤ /* __SECURE_HEAP_H__ */
