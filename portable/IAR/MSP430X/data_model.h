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

#నిర్వచితం_కాకపోతే దత్తాంశం_MODEL_H
#నిర్వచించు దత్తాంశం_MODEL_H

#ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #నిర్వచించు pushm_x    pushm.w
    #నిర్వచించు popm_x     popm.w
    #నిర్వచించు నెట్టు_x     నెట్టు.w
    #నిర్వచించు తీయి_x      తీయి.w
    #నిర్వచించు mov_x      mov.w
    #నిర్వచించు cmp_x      cmp.w
#అయితే_ముగింపు

#ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #నిర్వచించు pushm_x    pushm.a
    #నిర్వచించు popm_x     popm.a
    #నిర్వచించు నెట్టు_x     pushx.a
    #నిర్వచించు తీయి_x      popx.a
    #నిర్వచించు mov_x      mov.w
    #నిర్వచించు cmp_x      cmp.w
#అయితే_ముగింపు

#ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #నిర్వచించు pushm_x    pushm.a
    #నిర్వచించు popm_x     popm.a
    #నిర్వచించు నెట్టు_x     pushx.a
    #నిర్వచించు తీయి_x      popx.a
    #నిర్వచించు mov_x      movx.a
    #నిర్వచించు cmp_x      cmpx.a
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే pushm_x
    #దోషం The assembler options must define one యొక్క the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#అయితే_ముగింపు

#అయితే_ముగింపు /* DATA_MODEL_H */
