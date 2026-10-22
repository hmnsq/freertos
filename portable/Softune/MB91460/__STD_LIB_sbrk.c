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

#অন্তর্ভাব "FreeRTOSConfig.h"
#অন্তর্ভাব <stdlib.h>

    স্থির  long         brk_siz  =  0;
    প্রকারলেখ পূর্ণসংখ্যা          _heep_t;
    #define ROUNDUP(s)   (((s)+আকার(_heep_t)-1)&~(আকার(_heep_t)-1))
    স্থির  _heep_t      _heep[ROUNDUP(config_যোগ_HEAP_আকার)/আকার(_heep_t)];
    #define              heep_আকার      ROUNDUP(config_যোগ_HEAP_আকার)

    বাহ্যিক  অক্ষর  *sbrk(পূর্ণসংখ্যা  আকার_2)
    {
       যদি  (brk_siz  +  আকার_2  >  heep_আকার  ||  brk_siz  +  আকার_2  <  0)

          ফেরত((অক্ষর*)-1);
       brk_siz  +=  আকার_2;
       ফেরত(  (অক্ষর*)_heep  +  brk_siz  -  আকার_2);
    }
