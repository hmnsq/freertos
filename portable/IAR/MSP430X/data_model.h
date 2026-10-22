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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ದತ್ತಾಂಶ_MODEL_H
#ವ್ಯಾಖ್ಯಾನಿಸು ದತ್ತಾಂಶ_MODEL_H

#ಆದರೆ __DATA_MODEL__ == __DATA_MODEL_SMALL__
    #ವ್ಯಾಖ್ಯಾನಿಸು pushm_x    pushm.w
    #ವ್ಯಾಖ್ಯಾನಿಸು popm_x     popm.w
    #ವ್ಯಾಖ್ಯಾನಿಸು ತಳ್ಳು_x     ತಳ್ಳು.w
    #ವ್ಯಾಖ್ಯಾನಿಸು ತೆಗೆ_x      ತೆಗೆ_2.w
    #ವ್ಯಾಖ್ಯಾನಿಸು mov_x      mov.w
    #ವ್ಯಾಖ್ಯಾನಿಸು cmp_x      cmp.w
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ __DATA_MODEL__ == __DATA_MODEL_MEDIUM__
    #ವ್ಯಾಖ್ಯಾನಿಸು pushm_x    pushm.a
    #ವ್ಯಾಖ್ಯಾನಿಸು popm_x     popm.a
    #ವ್ಯಾಖ್ಯಾನಿಸು ತಳ್ಳು_x     pushx.a
    #ವ್ಯಾಖ್ಯಾನಿಸು ತೆಗೆ_x      popx.a
    #ವ್ಯಾಖ್ಯಾನಿಸು mov_x      mov.w
    #ವ್ಯಾಖ್ಯಾನಿಸು cmp_x      cmp.w
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ __DATA_MODEL__ == __DATA_MODEL_LARGE__
    #ವ್ಯಾಖ್ಯಾನಿಸು pushm_x    pushm.a
    #ವ್ಯಾಖ್ಯಾನಿಸು popm_x     popm.a
    #ವ್ಯಾಖ್ಯಾನಿಸು ತಳ್ಳು_x     pushx.a
    #ವ್ಯಾಖ್ಯಾನಿಸು ತೆಗೆ_x      popx.a
    #ವ್ಯಾಖ್ಯಾನಿಸು mov_x      movx.a
    #ವ್ಯಾಖ್ಯಾನಿಸು cmp_x      cmpx.a
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ pushm_x
    #ದೋಷ The assembler options must define one ದ the following symbols: __DATA_MODEL_SMALL__, __DATA_MODEL_MEDIUM__, or __DATA_MODEL_LARGE__
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* DATA_MODEL_H */
