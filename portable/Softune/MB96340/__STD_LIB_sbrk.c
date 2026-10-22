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

#అన్తర్భావ "FreeRTOSConfig.h"
#అన్తర్భావ <stdlib.h>

    స్థిర  దీర్ఘ         brk_siz  =  0;
    రకనిర్వచనం పూర్ణాంకం          _heep_t;
    #నిర్వచించు ROUNDUP(s)   (((s)+పరిమాణం(_heep_t)-1)&~(పరిమాణం(_heep_t)-1))
    స్థిర  _heep_t      _heep[ROUNDUP(config_మొత్తం_కుప్ప_కొలత)/పరిమాణం(_heep_t)];
    #నిర్వచించు              heep_కొలత      ROUNDUP(config_మొత్తం_కుప్ప_కొలత)

    బాహ్య  అక్షరం  *sbrk(పూర్ణాంకం  కొలత)
    {
       ఒకవేళ  (brk_siz  +  కొలత  >  heep_కొలత  ||  brk_siz  +  కొలత  <  0)

          తిరిగి((అక్షరం*)-1);
       brk_siz  +=  కొలత;
       తిరిగి(  (అక్షరం*)_heep  +  brk_siz  -  కొలత);
    }
