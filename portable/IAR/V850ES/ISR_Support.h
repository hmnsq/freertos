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

EXTERN pxCurrentTCB
EXTERN usCriticalNesting

#అన్తర్భావ "FreeRTOSConfig.h"

;
Context save and restore macro definitions
;

పోర్టు_SAVE_CONTEXT MACRO

    కూడు - 0x0C, sp;
prepare దొంతర గమ్యం save necessary విలువలు
st.w lp, 8[ sp ];
store LP గమ్యం దొంతర
    stsr    0, r31
    st.w lp, 4[ sp ];
store EIPC గమ్యం దొంతర
    stsr    1, lp
    st.w lp, 0[ sp ];
store EIPSW గమ్యం దొంతర
#ఒకవేళ config_దత్తాంశం_బహుళకం == 1; Using the Tiny దత్తాంశం_2 model
prepare {
    r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30
}, 76, sp;
save general purpose registers
sst.w r19, 72[ ep ]
sst.w r18, 68[ ep ]
sst.w r17, 64[ ep ]
sst.w r16, 60[ ep ]
sst.w r15, 56[ ep ]
sst.w r14, 52[ ep ]
sst.w r13, 48[ ep ]
sst.w r12, 44[ ep ]
sst.w r11, 40[ ep ]
sst.w r10, 36[ ep ]
sst.w r9, 32[ ep ]
sst.w r8, 28[ ep ]
sst.w r7, 24[ ep ]
sst.w r6, 20[ ep ]
sst.w r5, 16[ ep ]
sst.w r4, 12[ ep ]
#లేకపోతే; Using the Small / Large దత్తాంశం_2 model
prepare {
    r20, r21, r22, r23, r24, r26, r27, r28, r29, r30
}, 72, sp;
save general purpose registers
sst.w r19, 68[ ep ]
sst.w r18, 64[ ep ]
sst.w r17, 60[ ep ]
sst.w r16, 56[ ep ]
sst.w r15, 52[ ep ]
sst.w r14, 48[ ep ]
sst.w r13, 44[ ep ]
sst.w r12, 40[ ep ]
sst.w r11, 36[ ep ]
sst.w r10, 32[ ep ]
sst.w r9, 28[ ep ]
sst.w r8, 24[ ep ]
sst.w r7, 20[ ep ]
sst.w r6, 16[ ep ]
sst.w r5, 12[ ep ]
#అయితే_ముగింపు /* configDATA_MODE */
sst.w r2, 8[ ep ]
sst.w r1, 4[ ep ]
MOVHI hi1( usCriticalNesting ), r0, r1;
save usCriticalNesting విలువ గమ్యం దొంతర
ld.w lw1( usCriticalNesting )[ r1 ], r2
sst.w r2, 0[ ep ]
MOVHI hi1( pxCurrentTCB ), r0, r1;
save SP గమ్యం శిఖరం_2 యొక్క current TCB
ld.w lw1( pxCurrentTCB )[ r1 ], r2
st.w sp, 0[ r2 ]
ENDM


పోర్టు_RESTORE_CONTEXT MACRO

MOVHI hi1( pxCurrentTCB ), r0, r1;
get Stackpointer చిరునామా_2
ld.w lw1( pxCurrentTCB )[ r1 ], sp
MOV sp, r1
ld.w    0[ r1 ], sp;
ఎక్కించు_2 stackpointer
MOV sp, ep;
సమితి దొంతర సూచిక_3 గమ్యం element సూచిక_3
sld.w   0[ ep ], r1;
ఎక్కించు_2 usCriticalNesting విలువ from దొంతర
MOVHI hi1( usCriticalNesting ), r0, r2
st.w r1, lw1( usCriticalNesting )[ r2 ]
sld.w   4[ ep ], r1;
restore general purpose registers
sld.w   8[ ep ], r2
#ఒకవేళ config_దత్తాంశం_బహుళకం == 1; Using Tiny దత్తాంశం_2 model
    sld.w   12[ ep ], r4
    sld.w   16[ ep ], r5
    sld.w   20[ ep ], r6
    sld.w   24[ ep ], r7
    sld.w   28[ ep ], r8
    sld.w   32[ ep ], r9
    sld.w   36[ ep ], r10
    sld.w   40[ ep ], r11
    sld.w   44[ ep ], r12
    sld.w   48[ ep ], r13
    sld.w   52[ ep ], r14
    sld.w   56[ ep ], r15
    sld.w   60[ ep ], r16
    sld.w   64[ ep ], r17
    sld.w   68[ ep ], r18
    sld.w   72[ ep ], r19
    dispose 76, {
        r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30
    }
#లేకపోతే; Using Small / Large దత్తాంశం_2 model
    sld.w   12[ ep ], r5
    sld.w   16[ ep ], r6
    sld.w   20[ ep ], r7
    sld.w   24[ ep ], r8
    sld.w   28[ ep ], r9
    sld.w   32[ ep ], r10
    sld.w   36[ ep ], r11
    sld.w   40[ ep ], r12
    sld.w   44[ ep ], r13
    sld.w   48[ ep ], r14
    sld.w   52[ ep ], r15
    sld.w   56[ ep ], r16
    sld.w   60[ ep ], r17
    sld.w   64[ ep ], r18
    sld.w   68[ ep ], r19
    dispose 72, {
        r20, r21, r22, r23, r24, r26, r27, r28, r29, r30
    }
#అయితే_ముగింపు /* configDATA_MODE */
ld.w    0[ sp ], lp;
restore EIPSW from దొంతర
ldsr lp, 1
ld.w    4[ sp ], lp;
restore EIPC from దొంతర
ldsr lp, 0
ld.w    8[ sp ], lp;
restore LP from దొంతర
    కూడు     0x0C, sp;
సమితి SP గమ్యం కుడి position

RETI

ENDM
