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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

#ضمن "xexception_l.h"

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* This port uses the critical nesting count from the TCB rather than
 * maintaining a separate value and then saving this value in the task stack. */
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    1

/* Interrupt control macros. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    XExc_mDisableExceptions( XEXC_NON_CRITICAL );
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     XExc_mEnableExceptions( XEXC_NON_CRITICAL );

/*-----------------------------------------------------------*/

/* Critical section macros. */
فراغ vTaskEnterCritical( فراغ );
فراغ vTaskExitCritical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کړه پورټ_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/

/* Task utilities. */
فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()             asm متطاير ( "SC \n\t NOP" )
#تعریف_کړه پورټ_YIELD_FROM_ISR()    vTaskSwitchContext()

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT    8
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_NOP()    asm متطاير ( "NOP" )

/* There are 32 * 32bit floating point registers, plus the FPSCR to save. */
#تعریف_کړه پورټ_NO_FLOP_REGISTERS_منزل_SAVE    ( 32 + 1 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Port specific interrupt handling functions. */
فراغ v_پورټ_تیاری_مداخله_Controller( فراغ );
بنسټ_Type_t x_پورټ_Install_مداخله_Handler( uint8_t uc_مداخله_ID,
                                         XInterruptHandler pxHandler,
                                         فراغ * pv_Call_شا_Ref );

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
