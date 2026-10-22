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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ             ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ    UBaseType_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t         TickType_t;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffffffffUL

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        ਬਾਹਰੀ uint32_t ul_ਪੋਰਟ_Yield_Required;     \
                                                 \
        ਜੇ( xSwitchRequired != pdFALSE )         \
        {                                        \
            ul_ਪੋਰਟ_Yield_Required = pdTRUE;        \
        }                                        \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                __asm ਅਸਥਿਰ ( "SWI 0" ::: "memory" );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );
ਬਾਹਰੀ uint32_t ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( uint32_t ul_New_ਨਕਾਬ_ਮੁੱਲ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Install_Free_RTOSVector_ਸਾਰਣੀ( ਖਾਲੀ );

/*
 * These macros do not globally disable/enable interrupts. They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                      v_ਪੋਰਟ_Enter_Critical();
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                       v_ਪੋਰਟ_Exit_Critical();
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                  ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                   v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( x )

/*-----------------------------------------------------------*/

/*
 * Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/*
 * Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick.
 */
ਖਾਲੀ FreeRTOS_Tick_Handler( ਖਾਲੀ );

/*
 * If configUSE_TASK_FPU_SUPPORT is set to 1, then tasks are created without an
 * FPU context and must call vPortTaskUsesFPU() to allocate an FPU context
 * prior to any FPU instructions. If configUSE_TASK_FPU_SUPPORT is set to 2,
 * then all tasks have an FPU context allocated by default.
 */
#ਜੇ ( configUSE_TASK_FPU_SUPPORT == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_ਵਰਤਦਾ_FLOATING_ਬਿੰਦੂ()    v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU()
#ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT == 2 )

/*
 * Each task has an FPU context already, so define this function away to
 * prevent it being called accidentally.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_ਵਰਤਦਾ_FLOATING_ਬਿੰਦੂ()
#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_ਰੁਕਾਵਟ_ਤਰਜੀਹ           ( ( ( uint32_t ) config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES ) - 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_USABLE_ਰੁਕਾਵਟ_ਤਰਜੀਹ    ( ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_ਰੁਕਾਵਟ_ਤਰਜੀਹ - 1UL )

/* Architecture specific optimisations. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

/*-----------------------------------------------------------*/

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31 - __builtin_clz( uxReadyPriorities ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ਜੇ ( configASSERT_DEFINED == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਰੁਕਾਵਟ_ਤਰਜੀਹ_INVALID()    v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ()
#ਜੇ_ਅੰਤ /* configASSERT */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()                                         __asm ਅਸਥਿਰ ( "NOP" )


/*
 * The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller.
 */
#ਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 16
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            4
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    3
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 32
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            3
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    2
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            2
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    1
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 128
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    0
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 256
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            0
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    0
#ਨਹੀਂਤਾਂ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #ਗਲਤੀ Invalid config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES setting.  config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES must be ਸੈੱਟ ਮੰਜ਼ਿਲ the ਸੰਖਿਆ ਦਾ unique priorities implemented by the ਨਿਸ਼ਾਨਾ hardware
#ਜੇ_ਅੰਤ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਵਿੱਥ                      ( 0x04 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCIAR_ਰੁਕਾਵਟ_ACKNOWLEDGE_ਵਿੱਥ              ( 0x0C )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCEOIR_ਸਿਰਾ_ਦਾ_ਰੁਕਾਵਟ_ਵਿੱਥ                  ( 0x10 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCBPR_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਵਿੱਥ                       ( 0x08 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCRPR_RUNNING_ਤਰਜੀਹ_ਵਿੱਥ                   ( 0x14 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ       ( config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ + config_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਵਿੱਥ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ                    ( *( ( ਅਸਥਿਰ uint32_t * ) ( ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ + ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਵਿੱਥ ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCIAR_ਰੁਕਾਵਟ_ACKNOWLEDGE_ਰਜਿਸਟਰ_ਪਤਾ    ( ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ + ਪੋਰਟ_ICCIAR_ਰੁਕਾਵਟ_ACKNOWLEDGE_ਵਿੱਥ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCEOIR_ਸਿਰਾ_ਦਾ_ਰੁਕਾਵਟ_ਰਜਿਸਟਰ_ਪਤਾ        ( ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ + ਪੋਰਟ_ICCEOIR_ਸਿਰਾ_ਦਾ_ਰੁਕਾਵਟ_ਵਿੱਥ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ_ਪਤਾ            ( ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ + ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਵਿੱਥ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCBPR_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਰਜਿਸਟਰ                     ( *( ( ਅਚਲ ਅਸਥਿਰ uint32_t * ) ( ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ + ਪੋਰਟ_ICCBPR_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਵਿੱਥ ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ICCRPR_RUNNING_ਤਰਜੀਹ_ਰਜਿਸਟਰ                 ( *( ( ਅਚਲ ਅਸਥਿਰ uint32_t * ) ( ਪੋਰਟ_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਪਤਾ + ਪੋਰਟ_ICCRPR_RUNNING_ਤਰਜੀਹ_ਵਿੱਥ ) ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()    __asm ਅਸਥਿਰ ( "" ::: "memory" )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    } /* extern C */
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
