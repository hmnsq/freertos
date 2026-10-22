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

/*
Changes from V3.0.0

Changes from V3.0.1

Changes from V4.0.1
    Uselib pragma added for Croutine.c
*/

/*
 * The installation script will automatically prepend this file to the default FreeRTOS.h.
 */

#నిర్వచితం_కాకపోతే WIZC_FREERTOS_H
#నిర్వచించు WIZC_FREERTOS_H

#సూచన noheap
#సూచన wizcpp expandnl   on
#సూచన wizcpp searchpath "$__PATHNAME__/libFreeRTOS/Include/"
#సూచన wizcpp uselib     "$__PATHNAME__/libFreeRTOS/Modules/Croutine.c"
#సూచన wizcpp uselib     "$__PATHNAME__/libFreeRTOS/Modules/Tasks.c"
#సూచన wizcpp uselib     "$__PATHNAME__/libFreeRTOS/Modules/Queue.c"
#సూచన wizcpp uselib     "$__PATHNAME__/libFreeRTOS/Modules/List.c"
#సూచన wizcpp uselib     "$__PATHNAME__/libFreeRTOS/Modules/Port.c"

#అయితే_ముగింపు  /* WIZC_FREERTOS_H */
