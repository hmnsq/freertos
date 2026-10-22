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

/* System include files */
#ਅਨ੍ਤਰ੍ਭਾਵ <xc.h>

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR        ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT       ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE      ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG        ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT       ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE  uint32_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE   ਲੰਮਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ UBaseType_t;

#ਜੇ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC 1
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT          8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH            -1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IPL_ਖਿਸਕਾਓ               ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ALL_IPL_ਬਿੱਟ            ( 0x7FUL << ਪੋਰਟ_IPL_ਖਿਸਕਾਓ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SW0_ਦੋਆਧਾਰੀ_ਅੰਕ                 ( 0x01 << 8 )

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#ਜੇ ( configASSERT_DEFINED == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                                            \
    {                                                                           \
    uint32_t ul_ਸਥਿਤੀ;                                                          \
                                                                                \
        /* Mask interrupts at and below the kernel interrupt priority. */       \
        ul_ਸਥਿਤੀ = CP0_GET_ਸਥਿਤੀ();                                           \
                                                                                \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */    \
        ਜੇ( ( ( ul_ਸਥਿਤੀ & ਪੋਰਟ_ALL_IPL_ਬਿੱਟ ) >> ਪੋਰਟ_IPL_ਖਿਸਕਾਓ ) < config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) \
        {                                                                       \
            ul_ਸਥਿਤੀ &= ~ਪੋਰਟ_ALL_IPL_ਬਿੱਟ;                                      \
            CP0_ਸੈੱਟ_ਸਥਿਤੀ( ( ul_ਸਥਿਤੀ | ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_IPL_ਖਿਸਕਾਓ ) ) ); \
        }                                                                       \
    }
#ਨਹੀਂਤਾਂ /* configASSERT */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                                        \
    {                                                                       \
    uint32_t ul_ਸਥਿਤੀ;                                                      \
                                                                            \
        /* Mask interrupts at and below the kernel interrupt priority. */   \
        ul_ਸਥਿਤੀ = CP0_GET_ਸਥਿਤੀ();                                       \
        ul_ਸਥਿਤੀ &= ~ਪੋਰਟ_ALL_IPL_ਬਿੱਟ;                                      \
        CP0_ਸੈੱਟ_ਸਥਿਤੀ( ( ul_ਸਥਿਤੀ | ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_IPL_ਖਿਸਕਾਓ ) ) ); \
    }
#ਜੇ_ਅੰਤ /* configASSERT */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                                         \
{                                                                       \
uint32_t ul_ਸਥਿਤੀ;                                                      \
                                                                        \
    /* Unmask all interrupts. */                                        \
    ul_ਸਥਿਤੀ = CP0_GET_ਸਥਿਤੀ();                                       \
    ul_ਸਥਿਤੀ &= ~ਪੋਰਟ_ALL_IPL_ਬਿੱਟ;                                      \
    CP0_ਸੈੱਟ_ਸਥਿਤੀ( ul_ਸਥਿਤੀ );                                        \
}


ਬਾਹਰੀ ਖਾਲੀ vTaskEnterCritical( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ vTaskExitCritical( ਖਾਲੀ );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਚ_TCB 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()        vTaskEnterCritical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()         vTaskExitCritical()

ਬਾਹਰੀ UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR();
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( UBaseType_t );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR() ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ ) v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ux_Saved_ਸਥਿਤੀ_ਰਜਿਸਟਰ )

#ਜੇ ( __mips_hard_float == 0 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    #ਗਲਤੀ configUSE_TASK_FPU_SUPPORT can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when the part supports a hardware FPU module.
#ਜੇ_ਅੰਤ

#ਜੇ ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_ਵਰਤਦਾ_FLOATING_ਬਿੰਦੂ() v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU()
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION 1
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ਜੇ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 difference priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ

    /* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

    /*-----------------------------------------------------------*/

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities ) ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31UL - _clz( ( uxReadyPriorities ) ) )

#ਜੇ_ਅੰਤ /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                             \
{                                               \
uint32_t ulCause;                               \
                                                \
    /* Trigger software interrupt. */           \
    ulCause = _CP0_GET_CAUSE();                 \
    ulCause |= ਪੋਰਟ_SW0_ਦੋਆਧਾਰੀ_ਅੰਕ;                     \
    CP0_ਸੈੱਟ_CAUSE( ulCause );                  \
}

ਬਾਹਰੀ ਅਸਥਿਰ UBaseType_t ux_ਰੁਕਾਵਟ_Nesting;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਵਿੱਚ_ISR() configASSERT( ux_ਰੁਕਾਵਟ_Nesting == 0 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()   __asm ਅਸਥਿਰ ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) ਖਾਲੀ vFunction( ਖਾਲੀ *pvParameters ) __attribute__((noreturn))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters ) ਖਾਲੀ vFunction( ਖਾਲੀ *pvParameters )
/*-----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired ) \
    ਕਰੋ                                           \
    {                                            \
        ਜੇ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();        \
            ਪੋਰਟ_YIELD();                         \
        }                                        \
        ਨਹੀਂਤਾਂ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ਜਦੋਂ( 0 )

/* Required by the kernel aware debugger. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __DEBUG
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_REMOVE_STATIC_QUALIFIER
#ਜੇ_ਅੰਤ

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
