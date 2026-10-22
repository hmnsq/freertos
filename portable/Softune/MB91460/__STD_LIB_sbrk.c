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

/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*                 (C) Fujitsu Microelectronics Europe GmbH                  */
/*---------------------------------------------------------------------------
  __STD_LIB_sbrk.C
  - Used by heap_3.c for memory allocation and deletion.

/*---------------------------------------------------------------------------*/

#ضمن "FreeRTOSConfig.h"
#ضمن <stdlib.h>

    ساكن  دراز         brk_siz  =  0;
    تعريفنوع صحيح          _heep_t;
    #تعریف_کن ROUNDUP(s)   (((s)+حجم(_heep_t)-1)&~(حجم(_heep_t)-1))
    ساكن  _heep_t      _heep[ROUNDUP(config_مجموع_انباشته_اندازه)/حجم(_heep_t)];
    #تعریف_کن              heep_اندازه      ROUNDUP(config_مجموع_انباشته_اندازه)

    خارجي  حرف  *sbrk(صحيح  اندازه)
    {
       إذا  (brk_siz  +  اندازه  >  heep_اندازه  ||  brk_siz  +  اندازه  <  0)

          أرجع((حرف*)-1);
       brk_siz  +=  اندازه;
       أرجع(  (حرف*)_heep  +  brk_siz  -  اندازه);
    }
