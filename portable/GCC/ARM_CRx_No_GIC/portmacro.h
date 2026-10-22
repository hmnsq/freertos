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

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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

تعريفنوع uint32_t         TickType_t;
#تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        خارجي متطاير uint32_t ul_پورټ_Yield_Required; \
                                                      \
        إذا( xSwitchRequired != pdFALSE )              \
        {                                             \
            ul_پورټ_Yield_Required = pdTRUE;             \
        }                                             \
    }

#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )

فراغ v_پورټ_Yield( فراغ );

#تعریف_کړه پورټ_YIELD()     v_پورټ_Yield();

/*-----------------------------------------------------------*/

/*
 * Critical section management.
 */

خارجي فراغ v_پورټ_Enter_Critical( فراغ );
خارجي فراغ v_پورټ_Exit_Critical( فراغ );
خارجي فراغ v_پورټ_Enable_Interrupts( فراغ );
خارجي فراغ v_پورټ_Disable_Interrupts( فراغ );
خارجي uint32_t ul_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ );

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#تعریف_کړه پورټ_ENTER_CRITICAL()                    v_پورټ_Enter_Critical();
#تعریف_کړه پورټ_EXIT_CRITICAL()                     v_پورټ_Exit_Critical();
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                 v_پورټ_Enable_Interrupts();
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                v_پورټ_Disable_Interrupts();
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()       ul_پورټ_سېټ_مداخله_ماسک_From_ISR();
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )  افعل { إذا( x == 0 ) پورټ_ENABLE_INTERRUPTS(); } طالما( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Tickless idle/low power functionality. */
#که_نه_تعریف_شوی پورټ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت );
    #تعریف_کړه پورټ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وخت )    v_پورټ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وخت )
#د_که_پای

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
فراغ FreeRTOS_Tick_Handler( فراغ );

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_پورټ_شمېر_Leading_Zeros( UBaseType_t ulBitmap );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU
 * context by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )
    فراغ v_پورټ_Task_کاروي_FPU( فراغ );
#وإلا
    /* Each task has an FPU context already, so define this function as a
     * no-op. */
    #تعریف_کړه v_پورټ_Task_کاروي_FPU()
#د_که_پای
#تعریف_کړه پورټ_TASK_کاروي_FLOATING_ټکی()    v_پورټ_Task_کاروي_FPU()

#تعریف_کړه پورټ_ټیټ_ترین_مداخله_لومړیتوب           ( ( ( uint32_t ) config_UNIQUE_مداخله_PRIORITIES ) - 1UL )
#تعریف_کړه پورټ_ټیټ_ترین_USABLE_مداخله_لومړیتوب    ( پورټ_ټیټ_ترین_مداخله_لومړیتوب - 1UL )

/* Architecture specific optimisations. */
#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

    /* Store, clear and get the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )  ux_سر_لومړیتوب = ( 31UL - ul_پورټ_شمېر_Leading_Zeros( ( ux_سر_Ready_لومړیتوب ) ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#تعریف_کړه پورټ_NOP()               __asm متطاير ( "NOP" )
#تعریف_کړه پورټ_INLINE              __inline
#تعریف_کړه پورټ_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
