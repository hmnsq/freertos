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

/**
 * \file
 * \brief   exception processing for freertos
 */

/* #include "embARC.h" */

#ਅਨ੍ਤਰ੍ਭਾਵ "arc_freertos_exceptions.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNU__
    ਬਾਹਰੀ ਖਾਲੀ gnu_printf_ਤਿਆਰੀ( ਖਾਲੀ );
#ਜੇ_ਅੰਤ

/**
 * \brief  freertos related cpu exception initialization, all the interrupts handled by freertos must be not
 * fast irqs. If fiq is needed, please install the default firq_exc_entry or your own fast irq entry into
 * the specific interrupt exception.
 */
ਖਾਲੀ freertos_exc_init( ਖਾਲੀ )
{
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNU__
        gnu_printf_ਤਿਆਰੀ();
    #ਜੇ_ਅੰਤ
}
