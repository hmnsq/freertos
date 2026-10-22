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

#ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"
#ಅನ್ತರ್ಭಾವ <stdlib.h>

    ಸ್ಥಿರ  long         brk_siz  =  0;
    ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ          _heep_t;
    #define ROUNDUP(s)   (((s)+ಪರಿಮಾಣ(_heep_t)-1)&~(ಪರಿಮಾಣ(_heep_t)-1))
    ಸ್ಥಿರ  _heep_t      _heep[ROUNDUP(configTOTAL_HEAP_SIZE)/ಪರಿಮಾಣ(_heep_t)];
    #define              _heep_size      ROUNDUP(configTOTAL_HEAP_SIZE)

    ಬಾಹ್ಯ  ವರ್ಣ  *sbrk(ಪೂರ್ಣಾಙ್ಕ  size)
    {
       ಯದಿ  (brk_siz  +  size  >  _heep_size  ||  brk_siz  +  size  <  0)

          ಪ್ರತ್ಯಾಗಮ((ವರ್ಣ*)-1);
       brk_siz  +=  size;
       ಪ್ರತ್ಯಾಗಮ(  (ವರ್ಣ*)_heep  +  brk_siz  -  size);
    }
