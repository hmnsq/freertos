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

#यदि_अपरिभाषितम् दत्त_MODEL_H
#परिभाषय दत्त_MODEL_H

#यदि __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #परिभाषय pushm_x    pushm.w
    #परिभाषय popm_x     popm.w
    #परिभाषय प्रक्षिप_x     प्रक्षिप.w
    #परिभाषय निष्कासय_x      निष्कासय.w
    #परिभाषय mov_x      mov.w
    #परिभाषय cmp_x      cmp.w
#यदि_अन्तः

#यदि __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #परिभाषय pushm_x    pushm.a
    #परिभाषय popm_x     popm.a
    #परिभाषय प्रक्षिप_x     pushx.a
    #परिभाषय निष्कासय_x      popx.a
    #परिभाषय mov_x      mov.w
    #परिभाषय cmp_x      cmp.w
#यदि_अन्तः

#यदि __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #परिभाषय pushm_x    pushm.a
    #परिभाषय popm_x     popm.a
    #परिभाषय प्रक्षिप_x     pushx.a
    #परिभाषय निष्कासय_x      popx.a
    #परिभाषय mov_x      movx.a
    #परिभाषय cmp_x      cmpx.a
#यदि_अन्तः

#यदि_अपरिभाषितम् pushm_x
    #दोषः The assembler options must define one सम्बन्धि the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#यदि_अन्तः

#यदि_अन्तः /* DATA_MODEL_H */
