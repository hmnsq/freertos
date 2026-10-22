/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Synopsys, Inc. or its affiliates.  All Rights Reserved.
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

#ifndef ARC_FREERTOS_EXCEPTIONS_H
#define ARC_FREERTOS_EXCEPTIONS_H

/*
 * here, all arc cpu exceptions share the same entry, also for all interrupt
 * exceptions
 */
ಬಾಹ್ಯ ಶೂನ್ಯ exc_entry_cpu( ಶೂನ್ಯ ); /* cpu exception entry for freertos */
ಬಾಹ್ಯ ಶೂನ್ಯ exc_entry_int( ಶೂನ್ಯ ); /* int exception entry for freertos */

/* task dispatch functions in .s */
ಬಾಹ್ಯ ಶೂನ್ಯ start_r( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ start_dispatch();
ಬಾಹ್ಯ ಶೂನ್ಯ dispatch();

ಬಾಹ್ಯ ಶೂನ್ಯ freertos_exc_init( ಶೂನ್ಯ );

#endif /* ARC_FREERTOS_EXCEPTIONS_H */
