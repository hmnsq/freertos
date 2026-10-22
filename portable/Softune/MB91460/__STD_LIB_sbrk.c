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

#അന്തര്ഭാവ "FreeRTOSConfig.h"
#അന്തര്ഭാവ <stdlib.h>

    സ്ഥിതം  long         brk_siz  =  0;
    തരനിർവചനം പൂർണ്ണസംഖ്യ          _heep_t;
    #define ROUNDUP(s)   (((s)+വലുപ്പം(_heep_t)-1)&~(വലുപ്പം(_heep_t)-1))
    സ്ഥിതം  _heep_t      _heep[ROUNDUP(configTOTAL_HEAP_SIZE)/വലുപ്പം(_heep_t)];
    #define              _heep_size      ROUNDUP(configTOTAL_HEAP_SIZE)

    ബാഹ്യ  അക്ഷരം  *sbrk(പൂർണ്ണസംഖ്യ  size)
    {
       എങ്കിൽ  (brk_siz  +  size  >  _heep_size  ||  brk_siz  +  size  <  0)

          തിരികെ((അക്ഷരം*)-1);
       brk_siz  +=  size;
       തിരികെ(  (അക്ഷരം*)_heep  +  brk_siz  -  size);
    }
