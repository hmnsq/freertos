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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    size_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع پورٽ_بنياد_TYPE    بنياد_Type_t;
تعريفنوع uint64_t         UBaseType_t;

تعريفنوع uint64_t         TickType_t;
#وصف_ڪريو پورٽ_MAX_DELAY              ( ( TickType_t ) 0xffffffffffffffff )

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH         ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT       16
#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        خارجي uint64_t ull_پورٽ_Yield_Required;    \
                                                 \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            ull_پورٽ_Yield_Required = pdTRUE;       \
        }                                        \
    }

#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
#إذا defined( GUEST )
    #وصف_ڪريو پورٽ_YIELD()            __asm متطاير ( "SVC 0" ::: "memory" )
#وإلا
    #وصف_ڪريو پورٽ_YIELD()            __asm متطاير ( "SMC 0" ::: "memory" )
#جيڪڏهن_پورو

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
خارجي UBaseType_t ux_پورٽ_سيٽ_مداخلت_نقاب( فراغ );
خارجي فراغ v_پورٽ_Clear_مداخلت_نقاب( UBaseType_t ux_New_نقاب_قدر );
خارجي فراغ v_پورٽ_Install_Free_RTOSVector_جدول( فراغ );

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                       \
    __asm متطاير ( "MSR DAIFSET, #2" ::: "memory" ); \
    __asm متطاير ( "DSB SY" );                       \
    __asm متطاير ( "ISB SY" );

#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                        \
    __asm متطاير ( "MSR DAIFCLR, #2" ::: "memory" ); \
    __asm متطاير ( "DSB SY" );                       \
    __asm متطاير ( "ISB SY" );


/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                      v_پورٽ_Enter_Critical();
#وصف_ڪريو پورٽ_EXIT_CRITICAL()                       v_پورٽ_Exit_Critical();
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         ux_پورٽ_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٽ_Clear_مداخلت_نقاب( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
فراغ FreeRTOS_Tick_Handler( فراغ );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )
    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ );
#وإلا
    /* Each task has an FPU context already, so define this function away to
     * nothing to prevent it from being called accidentally. */
    #وصف_ڪريو v_پورٽ_Task_استعمال_ڪري_FPU()
#جيڪڏهن_پورو
#وصف_ڪريو پورٽ_TASK_استعمال_ڪري_FLOATING_نقطو()    v_پورٽ_Task_استعمال_ڪري_FPU()

#وصف_ڪريو پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح           ( ( ( uint32_t ) config_UNIQUE_مداخلت_PRIORITIES ) - 1UL )
#وصف_ڪريو پورٽ_سڀ_کان_هيٺ_USABLE_مداخلت_ترجيح    ( پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح - 1UL )

/* Architecture specific optimisations. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/*-----------------------------------------------------------*/

    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31 - __builtin_clz( uxReadyPriorities ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ );
    #وصف_ڪريو پورٽ_ASSERT_IF_مداخلت_ترجيح_INVALID()    v_پورٽ_Validate_مداخلت_ترجيح()
#جيڪڏهن_پورو /* configASSERT */

#وصف_ڪريو پورٽ_NOP()                                         __asm متطاير ( "NOP" )
#وصف_ڪريو پورٽ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_مداخلت_PRIORITIES == 16
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            4
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    3
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 32
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            3
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    2
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 64
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            2
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    1
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 128
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            1
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    0
#وإلاإذا config_UNIQUE_مداخلت_PRIORITIES == 256
    #وصف_ڪريو پورٽ_ترجيح_سرڪايو            0
    #وصف_ڪريو پورٽ_MAX_ٻٽو_نقطو_قدر    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #غلطي Invalid config_UNIQUE_مداخلت_PRIORITIES setting.  config_UNIQUE_مداخلت_PRIORITIES must be سيٽ منزل the عدد جو unique priorities implemented by the هدف hardware
#جيڪڏهن_پورو /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#وصف_ڪريو پورٽ_ICCPMR_ترجيح_نقاب_وٿي                      ( 0x04 )
#وصف_ڪريو پورٽ_ICCIAR_مداخلت_ACKNOWLEDGE_وٿي              ( 0x0C )
#وصف_ڪريو پورٽ_ICCEOIR_پڇاڙي_جو_مداخلت_وٿي                  ( 0x10 )
#وصف_ڪريو پورٽ_ICCBPR_ٻٽو_نقطو_وٿي                       ( 0x08 )
#وصف_ڪريو پورٽ_ICCRPR_RUNNING_ترجيح_وٿي                   ( 0x14 )

#وصف_ڪريو پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو       ( config_مداخلت_CONTROLLER_بنياد_پتو + config_مداخلت_CONTROLLER_CPU_INTERFACE_وٿي )
#وصف_ڪريو پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر                    ( *( ( متطاير uint32_t * ) ( پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو + پورٽ_ICCPMR_ترجيح_نقاب_وٿي ) ) )
#وصف_ڪريو پورٽ_ICCIAR_مداخلت_ACKNOWLEDGE_رجسٽر_پتو    ( پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو + پورٽ_ICCIAR_مداخلت_ACKNOWLEDGE_وٿي )
#وصف_ڪريو پورٽ_ICCEOIR_پڇاڙي_جو_مداخلت_رجسٽر_پتو        ( پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو + پورٽ_ICCEOIR_پڇاڙي_جو_مداخلت_وٿي )
#وصف_ڪريو پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر_پتو            ( پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو + پورٽ_ICCPMR_ترجيح_نقاب_وٿي )
#وصف_ڪريو پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر                     ( *( ( ثابت متطاير uint32_t * ) ( پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو + پورٽ_ICCBPR_ٻٽو_نقطو_وٿي ) ) )
#وصف_ڪريو پورٽ_ICCRPR_RUNNING_ترجيح_رجسٽر                 ( *( ( ثابت متطاير uint32_t * ) ( پورٽ_مداخلت_CONTROLLER_CPU_INTERFACE_پتو + پورٽ_ICCRPR_RUNNING_ترجيح_وٿي ) ) )

#وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
