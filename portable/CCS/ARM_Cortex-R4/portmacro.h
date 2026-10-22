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

#که_نه_تعریف_شوی __PORTMACRO_H__
#تعریف_کړه __PORTMACRO_H__

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
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE   اوږد

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع اوږد بنسټ_Type_t;
تعريفنوع بینښه اوږد UBaseType_t;

#إذا (config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه)
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY (TickType_t) 0xFFFF
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY (TickType_t) 0xFFFFFFFFF

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC 1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای


/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH    (-1)
#تعریف_کړه پورټ_TICK_PERIOD_MS    ((TickType_t) 1000 / config_TICK_شرح_HZ)
#تعریف_کړه پورټ_BYTE_ALIGNMENT  8

/* Critical section handling. */
خارجي فراغ v_پورټ_Enter_Critical(فراغ);
خارجي فراغ v_پورټ_Exit_Critical(فراغ);
#تعریف_کړه پورټ_ENTER_CRITICAL()        v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()         v_پورټ_Exit_Critical()
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    asm( " CPSID I" )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     asm( " CPSIE I" )

/* Scheduler utilities. */
#لارښوونه SWI_ALIAS( v_پورټ_Yield, 0 )
خارجي فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()                 v_پورټ_Yield()
#تعریف_کړه پورټ_SYS_SSIR1_REG           ( * ( ( متطاير uint32_t * ) 0xFFFFFFB0 ) )
#تعریف_کړه پورټ_SYS_SSIR1_SSKEY         ( 0x7500UL )
#تعریف_کړه پورټ_YIELD_WITHIN_API()      { پورټ_SYS_SSIR1_REG = پورټ_SYS_SSIR1_SSKEY;  asm( " DSB " ); asm( " ISB " ); }
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )     افعل { إذا( x != pdFALSE ) { پورټ_SYS_SSIR1_REG = پورټ_SYS_SSIR1_SSKEY;  ( فراغ ) پورټ_SYS_SSIR1_REG; } } طالما( 0 )

#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION 1
#د_که_پای

/* Architecture specific optimisations. */
#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

    /*-----------------------------------------------------------*/

    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities ) ux_سر_لومړیتوب = ( 31 - __clz( ( uxReadyPriorities ) ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION(vFunction, pvParameters)       فراغ vFunction(فراغ *pvParameters)
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO(vFunction, pvParameters) فراغ vFunction(فراغ *pvParameters)

#د_که_پای /* __PORTMACRO_H__ */
