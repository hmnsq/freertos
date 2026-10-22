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

    ಸ್ಥಿರ  ದೀರ್ಘ         brk_siz  =  0;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ          _heep_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ROUNDUP(s)   (((s)+ಗಾತ್ರ(_heep_t)-1)&~(ಗಾತ್ರ(_heep_t)-1))
    ಸ್ಥಿರ  _heep_t      _heep[ROUNDUP(config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ)/ಗಾತ್ರ(_heep_t)];
    #ವ್ಯಾಖ್ಯಾನಿಸು              heep_ಗಾತ್ರ      ROUNDUP(config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ)

    ಬಾಹ್ಯ  ಅಕ್ಷರ  *sbrk(ಪೂರ್ಣಾಂಕ  ಗಾತ್ರ_2)
    {
       ಆದರೆ  (brk_siz  +  ಗಾತ್ರ_2  >  heep_ಗಾತ್ರ  ||  brk_siz  +  ಗಾತ್ರ_2  <  0)

          ಹಿಂತಿರುಗಿ((ಅಕ್ಷರ*)-1);
       brk_siz  +=  ಗಾತ್ರ_2;
       ಹಿಂತಿರುಗಿ(  (ಅಕ್ಷರ*)_heep  +  brk_siz  -  ಗಾತ್ರ_2);
    }
