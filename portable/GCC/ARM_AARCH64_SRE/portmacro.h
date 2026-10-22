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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    size_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع پورت_پایه_TYPE    پایه_Type_t;
تعريفنوع uint64_t         UBaseType_t;

تعريفنوع uint64_t         TickType_t;
#تعریف_کن پورت_MAX_DELAY              ( ( TickType_t ) 0xffffffffffffffff )

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_پشته_GROWTH         ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT       16
#تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        خارجي uint64_t ull_پورت_Yield_Required;    \
                                                 \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            ull_پورت_Yield_Required = pdTRUE;       \
        }                                        \
    }

#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
#إذا defined( GUEST )
    #تعریف_کن پورت_YIELD()            __asm متطاير ( "SVC 0" ::: "memory" )
#وإلا
    #تعریف_کن پورت_YIELD()            __asm متطاير ( "SMC 0" ::: "memory" )
#پایان_اگر

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

خارجي فراغ v_پورت_Enter_Critical( فراغ );
خارجي فراغ v_پورت_Exit_Critical( فراغ );
خارجي UBaseType_t ux_پورت_مجموعه_وقفه_ماسک( فراغ );
خارجي فراغ v_پورت_Clear_وقفه_ماسک( UBaseType_t ux_New_ماسک_مقدار );
خارجي فراغ v_پورت_Install_Free_RTOSVector_جدول( فراغ );

#تعریف_کن پورت_DISABLE_INTERRUPTS()                       \
    __asm متطاير ( "MSR DAIFSET, #2" ::: "memory" ); \
    __asm متطاير ( "DSB SY" );                       \
    __asm متطاير ( "ISB SY" );

#تعریف_کن پورت_ENABLE_INTERRUPTS()                        \
    __asm متطاير ( "MSR DAIFCLR, #2" ::: "memory" ); \
    __asm متطاير ( "DSB SY" );                       \
    __asm متطاير ( "ISB SY" );


/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#تعریف_کن پورت_ENTER_CRITICAL()                      v_پورت_Enter_Critical();
#تعریف_کن پورت_EXIT_CRITICAL()                       v_پورت_Exit_Critical();
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ux_پورت_مجموعه_وقفه_ماسک()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_پورت_Clear_وقفه_ماسک( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
فراغ FreeRTOS_Tick_Handler( فراغ );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )
    فراغ v_پورت_Task_استفاده_میکند_FPU( فراغ );
#وإلا
    /* Each task has an FPU context already, so define this function away to
    * nothing to prevent it from being called accidentally. */
    #تعریف_کن v_پورت_Task_استفاده_میکند_FPU()
#پایان_اگر
#تعریف_کن پورت_TASK_استفاده_میکند_FLOATING_نقطه()    v_پورت_Task_استفاده_میکند_FPU()

#تعریف_کن پورت_پایینترین_وقفه_اولویت           ( ( ( uint32_t ) config_UNIQUE_وقفه_PRIORITIES ) - 1UL )
#تعریف_کن پورت_پایینترین_USABLE_وقفه_اولویت    ( پورت_پایینترین_وقفه_اولویت - 1UL )

/* Architecture specific optimisations. */
#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
#پایان_اگر

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31 - __builtin_clz( uxReadyPriorities ) )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورت_Validate_وقفه_اولویت( فراغ );
    #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    v_پورت_Validate_وقفه_اولویت()
#پایان_اگر /* configASSERT */

#تعریف_کن پورت_NOP()                                         __asm متطاير ( "NOP" )
#تعریف_کن پورت_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_وقفه_PRIORITIES == 16
    #تعریف_کن پورت_اولویت_لغزش            4
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    3
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 32
    #تعریف_کن پورت_اولویت_لغزش            3
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    2
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 64
    #تعریف_کن پورت_اولویت_لغزش            2
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    1
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 128
    #تعریف_کن پورت_اولویت_لغزش            1
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    0
#وإلاإذا config_UNIQUE_وقفه_PRIORITIES == 256
    #تعریف_کن پورت_اولویت_لغزش            0
    #تعریف_کن پورت_MAX_دودویی_نقطه_مقدار    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #خطا Invalid config_UNIQUE_وقفه_PRIORITIES setting.  config_UNIQUE_وقفه_PRIORITIES must be مجموعه مقصد the عدد از unique priorities implemented by the هدف hardware
#پایان_اگر /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
