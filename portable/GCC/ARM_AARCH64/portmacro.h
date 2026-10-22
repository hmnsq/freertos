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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    size_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع پورٹ_ادھار_TYPE    ادھار_Type_t;
تعريفنوع uint64_t         UBaseType_t;

تعريفنوع uint64_t         TickType_t;
#تعریف_کرو پورٹ_MAX_DELAY              ( ( TickType_t ) 0xffffffffffffffff )

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH         ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT       16
#تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        خارجي uint64_t ull_پورٹ_Yield_Required;    \
                                                 \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            ull_پورٹ_Yield_Required = pdTRUE;       \
        }                                        \
    }

#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
#إذا defined( GUEST )
    #تعریف_کرو پورٹ_YIELD()            __asm متطاير ( "SVC 0" ::: "memory" )
#وإلا
    #تعریف_کرو پورٹ_YIELD()            __asm متطاير ( "SMC 0" ::: "memory" )
#جے_انت

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
خارجي UBaseType_t ux_پورٹ_سیٹ_رکاوٹ_نقاب( فراغ );
خارجي فراغ v_پورٹ_Clear_رکاوٹ_نقاب( UBaseType_t ux_New_نقاب_قدر );
خارجي فراغ v_پورٹ_Install_Free_RTOSVector_جدول( فراغ );

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                       \
    __asm متطاير ( "MSR DAIFSET, #2" ::: "memory" ); \
    __asm متطاير ( "DSB SY" );                       \
    __asm متطاير ( "ISB SY" );

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                        \
    __asm متطاير ( "MSR DAIFCLR, #2" ::: "memory" ); \
    __asm متطاير ( "DSB SY" );                       \
    __asm متطاير ( "ISB SY" );


/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#تعریف_کرو پورٹ_ENTER_CRITICAL()                      v_پورٹ_Enter_Critical();
#تعریف_کرو پورٹ_EXIT_CRITICAL()                       v_پورٹ_Exit_Critical();
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ux_پورٹ_سیٹ_رکاوٹ_نقاب()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_پورٹ_Clear_رکاوٹ_نقاب( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
فراغ FreeRTOS_Tick_Handler( فراغ );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU context
 * by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )
    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ );
#وإلا
    /* Each task has an FPU context already, so define this function away to
     * nothing to prevent it from being called accidentally. */
    #تعریف_کرو v_پورٹ_Task_ورتدا_FPU()
#جے_انت
#تعریف_کرو پورٹ_TASK_ورتدا_FLOATING_نقطہ()    v_پورٹ_Task_ورتدا_FPU()

#تعریف_کرو پورٹ_سبھ_توں_نیواں_رکاوٹ_ترجیح           ( ( ( uint32_t ) config_UNIQUE_رکاوٹ_PRIORITIES ) - 1UL )
#تعریف_کرو پورٹ_سبھ_توں_نیواں_USABLE_رکاوٹ_ترجیح    ( پورٹ_سبھ_توں_نیواں_رکاوٹ_ترجیح - 1UL )

/* Architecture specific optimisations. */
#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31 - __builtin_clz( uxReadyPriorities ) )

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ v_پورٹ_Validate_رکاوٹ_ترجیح( فراغ );
    #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    v_پورٹ_Validate_رکاوٹ_ترجیح()
#جے_انت /* configASSERT */

#تعریف_کرو پورٹ_NOP()                                         __asm متطاير ( "NOP" )
#تعریف_کرو پورٹ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#إذا config_UNIQUE_رکاوٹ_PRIORITIES == 16
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            4
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    3
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 32
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            3
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    2
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 64
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            2
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    1
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 128
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            1
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#وإلاإذا config_UNIQUE_رکاوٹ_PRIORITIES == 256
    #تعریف_کرو پورٹ_ترجیح_کھسکاؤ            0
    #تعریف_کرو پورٹ_MAX_ثنائی_نقطہ_قدر    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #غلطی Invalid config_UNIQUE_رکاوٹ_PRIORITIES setting.  config_UNIQUE_رکاوٹ_PRIORITIES must be سیٹ منزل the نمبر دا unique priorities implemented by the نشانہ hardware
#جے_انت /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#تعریف_کرو پورٹ_ICCPMR_ترجیح_نقاب_وتھ                      ( 0x04 )
#تعریف_کرو پورٹ_ICCIAR_رکاوٹ_ACKNOWLEDGE_وتھ              ( 0x0C )
#تعریف_کرو پورٹ_ICCEOIR_سرا_دا_رکاوٹ_وتھ                  ( 0x10 )
#تعریف_کرو پورٹ_ICCBPR_ثنائی_نقطہ_وتھ                       ( 0x08 )
#تعریف_کرو پورٹ_ICCRPR_RUNNING_ترجیح_وتھ                   ( 0x14 )

#تعریف_کرو پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ       ( config_رکاوٹ_CONTROLLER_ادھار_پتہ + config_رکاوٹ_CONTROLLER_CPU_INTERFACE_وتھ )
#تعریف_کرو پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر                    ( *( ( متطاير uint32_t * ) ( پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCPMR_ترجیح_نقاب_وتھ ) ) )
#تعریف_کرو پورٹ_ICCIAR_رکاوٹ_ACKNOWLEDGE_رجسٹر_پتہ    ( پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCIAR_رکاوٹ_ACKNOWLEDGE_وتھ )
#تعریف_کرو پورٹ_ICCEOIR_سرا_دا_رکاوٹ_رجسٹر_پتہ        ( پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCEOIR_سرا_دا_رکاوٹ_وتھ )
#تعریف_کرو پورٹ_ICCPMR_ترجیح_نقاب_رجسٹر_پتہ            ( پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCPMR_ترجیح_نقاب_وتھ )
#تعریف_کرو پورٹ_ICCBPR_ثنائی_نقطہ_رجسٹر                     ( *( ( ثابت متطاير uint32_t * ) ( پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCBPR_ثنائی_نقطہ_وتھ ) ) )
#تعریف_کرو پورٹ_ICCRPR_RUNNING_ترجیح_رجسٹر                 ( *( ( ثابت متطاير uint32_t * ) ( پورٹ_رکاوٹ_CONTROLLER_CPU_INTERFACE_پتہ + پورٹ_ICCRPR_RUNNING_ترجیح_وتھ ) ) )

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
