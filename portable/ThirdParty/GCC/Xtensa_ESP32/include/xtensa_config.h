/*
 * SPDX-FileCopyrightText: 2015-2019 Cadence Design Systems, Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2016-2022 Espressif Systems (Shanghai) CO LTD
 */

/*
 * Copyright (c) 2015-2019 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*******************************************************************************
*
*  Configuration-specific information for Xtensa build. This file must be
*  included in FreeRTOSConfig.h to properly set up the config-dependent
*  parameters correctly.
*
*  NOTE: To enable thread-safe C library support, XT_USE_THREAD_SAFE_CLIB must
*  be defined to be > 0 somewhere above or on the command line.
*
*******************************************************************************/

#यदि_अपरिभाषितम् XTENSA_CONFIG_H
#परिभाषय XTENSA_CONFIG_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

#अन्तर्भाव <xtensa/hal.h>
#अन्तर्भाव <xtensa/config/core.h>
#अन्तर्भाव <xtensa/config/system.h> /* required for XSHAL_CLIB */

#अन्तर्भाव "xtensa_context.h"


/*-----------------------------------------------------------------------------
 *                                 STACK REQUIREMENTS
 *
 * This section defines the minimum stack size, and the extra space required to
 * be allocated for saving coprocessor state and/or C library state information
 * (if thread safety is enabled for the C library). The sizes are in bytes.
 *
 * Stack sizes for individual tasks should be derived from these minima based on
 * the maximum call depth of the task and the maximum level of interrupt nesting.
 * A minimum stack size is defined by XT_STACK_MIN_SIZE. This minimum is based
 * on the requirement for a task that calls nothing else but can be interrupted.
 * This assumes that interrupt handlers do not call more than a few levels deep.
 * If this is not true, i.e. one or more interrupt handlers make deep calls then
 * the minimum must be increased.
 *
 * If the Xtensa processor configuration includes coprocessors, then space is
 * allocated to save the coprocessor state on the stack.
 *
 * If thread safety is enabled for the C runtime library, (XT_USE_THREAD_SAFE_CLIB
 * is defined) then space is allocated to save the C library context in the TCB.
 *
 * Allocating insufficient stack space is a common source of hard-to-find errors.
 * During development, it is best to enable the FreeRTOS stack checking features.
 *
 * Usage:
 *
 * XT_USE_THREAD_SAFE_CLIB -- Define this to a nonzero value to enable thread-safe
 *                            use of the C library. This will require extra stack
 *                            space to be allocated for tasks that use the C library
 *                            reentrant functions. See below for more information.
 *
 * NOTE: The Xtensa toolchain supports multiple C libraries and not all of them
 * support thread safety. Check your core configuration to see which C library
 * was chosen for your system.
 *
 * XT_STACK_MIN_SIZE       -- The minimum stack size for any task. It is recommended
 *                            that you do not use a stack smaller than this for any
 *                            task. In case you want to use stacks smaller than this
 *                            size, you must verify that the smaller size(s) will work
 *                            under all operating conditions.
 *
 * XT_STACK_EXTRA          -- The amount of extra stack space to allocate for a task
 *                            that does not make C library reentrant calls. Add this
 *                            to the amount of stack space required by the task itself.
 *
 * XT_STACK_EXTRA_CLIB     -- The amount of space to allocate for C library state.
 *
 *  -----------------------------------------------------------------------------*/

/* Extra space required for interrupt/exception hooks. */
#यदि_परिभाषितम् XT_INTEXC_HOOKS
    #यदि_परिभाषितम् __XTENSA_CALL0_ABI__
        #परिभाषय STK_INTEXC_EXTRA     0x200
    #अन्यथा
        #परिभाषय STK_INTEXC_EXTRA     0x180
    #यदि_अन्तः
#अन्यथा
    #परिभाषय STK_INTEXC_EXTRA         0
#यदि_अन्तः

#परिभाषय XT_CLIB_CONTEXT_AREA_आकार    0

/*------------------------------------------------------------------------------
 *  Extra size -- interrupt frame plus coprocessor save area plus hook space.
 *  NOTE: Make sure XT_INTEXC_HOOKS is undefined unless you really need the hooks.
 *  ------------------------------------------------------------------------------*/
#यदि_परिभाषितम् __XTENSA_CALL0_ABI__
    #परिभाषय XT_XTRA_आकार    ( XT_STK_FRMSZ + STK_INTEXC_EXTRA + 0x10 + XT_CP_आकार )
#अन्यथा
    #परिभाषय XT_XTRA_आकार    ( XT_STK_FRMSZ + STK_INTEXC_EXTRA + 0x20 + XT_CP_आकार )
#यदि_अन्तः

/*------------------------------------------------------------------------------
 *  Space allocated for user code -- function calls and local variables.
 *  NOTE: This number can be adjusted to suit your needs. You must verify that the
 *  amount of space you reserve is adequate for the worst-case conditions in your
 *  application.
 *  NOTE: The windowed ABI requires more stack, since space has to be reserved
 *  for spilling register windows.
 *  ------------------------------------------------------------------------------*/
#यदि_परिभाषितम् __XTENSA_CALL0_ABI__
    #परिभाषय XT_USER_आकार    0x200
#अन्यथा
    #परिभाषय XT_USER_आकार    0x400
#यदि_अन्तः

/* Minimum recommended stack size. */
#परिभाषय XT_राशिः_MIN_आकार      ( ( XT_XTRA_आकार + XT_USER_आकार ) / परिमाण( अचिह्नित वर्ण ) )

/* OS overhead with and without C library thread context. */
#परिभाषय XT_राशिः_EXTRA         ( XT_XTRA_आकार )
#परिभाषय XT_राशिः_EXTRA_CLIB    ( XT_XTRA_आकार + XT_CLIB_CONTEXT_AREA_आकार )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* XTENSA_CONFIG_H */
