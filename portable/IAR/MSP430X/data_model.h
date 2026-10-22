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

#اگر_تعریف_نشده داده_MODEL_H
#تعریف_کن داده_MODEL_H

#إذا __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #تعریف_کن pushm_x    pushm.w
    #تعریف_کن popm_x     popm.w
    #تعریف_کن افزودن_x     افزودن.w
    #تعریف_کن برداشت_x      برداشت.w
    #تعریف_کن mov_x      mov.w
    #تعریف_کن cmp_x      cmp.w
#پایان_اگر

#إذا __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #تعریف_کن pushm_x    pushm.a
    #تعریف_کن popm_x     popm.a
    #تعریف_کن افزودن_x     pushx.a
    #تعریف_کن برداشت_x      popx.a
    #تعریف_کن mov_x      mov.w
    #تعریف_کن cmp_x      cmp.w
#پایان_اگر

#إذا __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #تعریف_کن pushm_x    pushm.a
    #تعریف_کن popm_x     popm.a
    #تعریف_کن افزودن_x     pushx.a
    #تعریف_کن برداشت_x      popx.a
    #تعریف_کن mov_x      movx.a
    #تعریف_کن cmp_x      cmpx.a
#پایان_اگر

#اگر_تعریف_نشده pushm_x
    #خطا The assembler options must define one از the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#پایان_اگر

#پایان_اگر /* DATA_MODEL_H */
