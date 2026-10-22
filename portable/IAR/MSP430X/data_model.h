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

#جے_بنا_تعریف انکڑے_MODEL_H
#تعریف_کرو انکڑے_MODEL_H

#إذا __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #تعریف_کرو pushm_x    pushm.w
    #تعریف_کرو popm_x     popm.w
    #تعریف_کرو ڈالو_x     ڈالو.w
    #تعریف_کرو نکالو_x      نکالو.w
    #تعریف_کرو mov_x      mov.w
    #تعریف_کرو cmp_x      cmp.w
#جے_انت

#إذا __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #تعریف_کرو pushm_x    pushm.a
    #تعریف_کرو popm_x     popm.a
    #تعریف_کرو ڈالو_x     pushx.a
    #تعریف_کرو نکالو_x      popx.a
    #تعریف_کرو mov_x      mov.w
    #تعریف_کرو cmp_x      cmp.w
#جے_انت

#إذا __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #تعریف_کرو pushm_x    pushm.a
    #تعریف_کرو popm_x     popm.a
    #تعریف_کرو ڈالو_x     pushx.a
    #تعریف_کرو نکالو_x      popx.a
    #تعریف_کرو mov_x      movx.a
    #تعریف_کرو cmp_x      cmpx.a
#جے_انت

#جے_بنا_تعریف pushm_x
    #غلطی The assembler options must define one دا the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#جے_انت

#جے_انت /* DATA_MODEL_H */
