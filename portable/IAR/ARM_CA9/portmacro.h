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

/* IAR includes. */
#که_تعریف_شوی __ICCARM__

    #ضمن <intrinsics.h>

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
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

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
    #تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired ) \
    {                                                \
        خارجي uint32_t ul_پورټ_Yield_Required;         \
                                                     \
        إذا( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_پورټ_Yield_Required = pdTRUE;            \
        }                                            \
    }

    #تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
    #تعریف_کړه پورټ_YIELD()                __asm( "SWI 0" );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    خارجي فراغ v_پورټ_Enter_Critical( فراغ );
    خارجي فراغ v_پورټ_Exit_Critical( فراغ );
    خارجي uint32_t ul_پورټ_سېټ_مداخله_ماسک( فراغ );
    خارجي فراغ v_پورټ_Clear_مداخله_ماسک( uint32_t ul_New_ماسک_ارزښت );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #تعریف_کړه پورټ_ENTER_CRITICAL()                      v_پورټ_Enter_Critical();
    #تعریف_کړه پورټ_EXIT_CRITICAL()                       v_پورټ_Exit_Critical();
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                  ul_پورټ_سېټ_مداخله_ماسک()
    #تعریف_کړه پورټ_ENABLE_INTERRUPTS()                   v_پورټ_Clear_مداخله_ماسک( 0 )
    #تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         ul_پورټ_سېټ_مداخله_ماسک()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    v_پورټ_Clear_مداخله_ماسک( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
    فراغ FreeRTOS_Tick_Handler( فراغ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    فراغ v_پورټ_Task_کاروي_FPU( فراغ );
    #تعریف_کړه پورټ_TASK_کاروي_FLOATING_ټکی()    v_پورټ_Task_کاروي_FPU()

    #تعریف_کړه پورټ_ټیټ_ترین_مداخله_لومړیتوب           ( ( ( uint32_t ) config_UNIQUE_مداخله_PRIORITIES ) - 1UL )
    #تعریف_کړه پورټ_ټیټ_ترین_USABLE_مداخله_لومړیتوب    ( پورټ_ټیټ_ترین_مداخله_لومړیتوب - 1UL )

/* Architecture specific optimisations. */
    #که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
        #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
    #د_که_پای

    #إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
        #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
        #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

        #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31 - __CLZ( uxReadyPriorities ) )

    #د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #إذا ( configASSERT_DEFINED == 1 )
        فراغ v_پورټ_Validate_مداخله_لومړیتوب( فراغ );
        #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    v_پورټ_Validate_مداخله_لومړیتوب()
    #د_که_پای /* configASSERT */

    #تعریف_کړه پورټ_NOP()                                         __asm متطاير ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #لارښوونه diag_suppress=Pe191
    #لارښوونه diag_suppress=Pa082

#د_که_پای /* __ICCARM__ */


/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_مداخله_PRIORITIES == 16
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            4
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    3
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 32
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            3
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    2
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 64
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            2
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    1
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 128
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            1
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    0
#وإلاإذا config_UNIQUE_مداخله_PRIORITIES == 256
    #تعریف_کړه پورټ_لومړیتوب_ښويدنه            0
    #تعریف_کړه پورټ_MAX_دوګونی_ټکی_ارزښت    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #تېروتنه Invalid config_UNIQUE_مداخله_PRIORITIES setting.  config_UNIQUE_مداخله_PRIORITIES must be سېټ منزل the شمېره د unique priorities implemented by the موخه hardware
#د_که_پای /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#تعریف_کړه پورټ_ICCPMR_لومړیتوب_ماسک_دننه_واټن                      ( 0x04 )
#تعریف_کړه پورټ_ICCIAR_مداخله_ACKNOWLEDGE_دننه_واټن              ( 0x0C )
#تعریف_کړه پورټ_ICCEOIR_پای_ټکی_د_مداخله_دننه_واټن                  ( 0x10 )
#تعریف_کړه پورټ_ICCBPR_دوګونی_ټکی_دننه_واټن                       ( 0x08 )
#تعریف_کړه پورټ_ICCRPR_RUNNING_لومړیتوب_دننه_واټن                   ( 0x14 )

#تعریف_کړه پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته       ( config_مداخله_CONTROLLER_بنسټ_پته + config_مداخله_CONTROLLER_CPU_INTERFACE_دننه_واټن )
#تعریف_کړه پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی                    ( *( ( متطاير uint32_t * ) ( پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته + پورټ_ICCPMR_لومړیتوب_ماسک_دننه_واټن ) ) )
#تعریف_کړه پورټ_ICCIAR_مداخله_ACKNOWLEDGE_ثبتوونکی_پته    ( پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته + پورټ_ICCIAR_مداخله_ACKNOWLEDGE_دننه_واټن )
#تعریف_کړه پورټ_ICCEOIR_پای_ټکی_د_مداخله_ثبتوونکی_پته        ( پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته + پورټ_ICCEOIR_پای_ټکی_د_مداخله_دننه_واټن )
#تعریف_کړه پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی_پته            ( پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته + پورټ_ICCPMR_لومړیتوب_ماسک_دننه_واټن )
#تعریف_کړه پورټ_ICCBPR_دوګونی_ټکی_ثبتوونکی                     ( *( ( ثابت متطاير uint32_t * ) ( پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته + پورټ_ICCBPR_دوګونی_ټکی_دننه_واټن ) ) )
#تعریف_کړه پورټ_ICCRPR_RUNNING_لومړیتوب_ثبتوونکی                 ( *( ( ثابت متطاير uint32_t * ) ( پورټ_مداخله_CONTROLLER_CPU_INTERFACE_پته + پورټ_ICCRPR_RUNNING_لومړیتوب_دننه_واټن ) ) )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
