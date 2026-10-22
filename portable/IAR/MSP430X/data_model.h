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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਅੰਕੜੇ_MODEL_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅੰਕੜੇ_MODEL_H

#ਜੇ __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pushm_x    pushm.w
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ popm_x     popm.w
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਧੱਕੋ_x     ਧੱਕੋ.w
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੱਢੋ_x      ਕੱਢੋ.w
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ mov_x      mov.w
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ cmp_x      cmp.w
#ਜੇ_ਅੰਤ

#ਜੇ __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pushm_x    pushm.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ popm_x     popm.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਧੱਕੋ_x     pushx.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੱਢੋ_x      popx.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ mov_x      mov.w
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ cmp_x      cmp.w
#ਜੇ_ਅੰਤ

#ਜੇ __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pushm_x    pushm.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ popm_x     popm.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਧੱਕੋ_x     pushx.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੱਢੋ_x      popx.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ mov_x      movx.a
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ cmp_x      cmpx.a
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ pushm_x
    #ਗਲਤੀ The assembler options must define one ਦਾ the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* DATA_MODEL_H */
