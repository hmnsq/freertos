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

#که_نه_تعریف_شوی معلومات_MODEL_H
#تعریف_کړه معلومات_MODEL_H

#إذا __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #تعریف_کړه pushm_x    pushm.w
    #تعریف_کړه popm_x     popm.w
    #تعریف_کړه ټېل_x     ټېل.w
    #تعریف_کړه راوباسه_x      راوباسه.w
    #تعریف_کړه mov_x      mov.w
    #تعریف_کړه cmp_x      cmp.w
#د_که_پای

#إذا __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #تعریف_کړه pushm_x    pushm.a
    #تعریف_کړه popm_x     popm.a
    #تعریف_کړه ټېل_x     pushx.a
    #تعریف_کړه راوباسه_x      popx.a
    #تعریف_کړه mov_x      mov.w
    #تعریف_کړه cmp_x      cmp.w
#د_که_پای

#إذا __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #تعریف_کړه pushm_x    pushm.a
    #تعریف_کړه popm_x     popm.a
    #تعریف_کړه ټېل_x     pushx.a
    #تعریف_کړه راوباسه_x      popx.a
    #تعریف_کړه mov_x      movx.a
    #تعریف_کړه cmp_x      cmpx.a
#د_که_پای

#که_نه_تعریف_شوی pushm_x
    #تېروتنه The assembler options must define one د the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#د_که_پای

#د_که_پای /* DATA_MODEL_H */
