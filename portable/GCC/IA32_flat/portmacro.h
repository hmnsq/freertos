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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_TIMER_INT_ਸਦਿਸ਼       ( 0x21 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_YIELD_INT_ਸਦਿਸ਼       ( 0x20 )

/* Build yield interrupt instruction. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_ਰੁਕਾਵਟ             "int $0x20"

/* APIC register addresses. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_EOI                    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ             ( 1UL << 8UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_DISABLE                ( 1UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_NMI                    ( 4 << 8 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_ID_ਰਜਿਸਟਰ            ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x20UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_SPURIOUS_INT           ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0xF0UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LVT_TIMER              ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x320UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_TIMER_INITIAL_ਗਿਣਤੀ    ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x380UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_TIMER_CURRENT_ਗਿਣਤੀ    ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x390UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_TASK_ਤਰਜੀਹ          ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x80UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LVT_ERROR              ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x370UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_ERROR_ਸਥਿਤੀ           ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x280UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LDR                    ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0xD0UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_TMRDIV                 ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x3E0UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LVT_PERF               ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x340UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LVT_LINT0              ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x350UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_LVT_LINT1              ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                                  \
    {                                                \
        ਬਾਹਰੀ ਅਸਥਿਰ uint32_t ulCriticalNesting;  \
        ਬਾਹਰੀ ਅਸਥਿਰ uint32_t ul_ਪੋਰਟ_Yield_Pending; \
        ਜੇ( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_ਪੋਰਟ_Yield_Pending = pdTRUE;             \
        }                                            \
        ਨਹੀਂਤਾਂ                                         \
        {                                            \
            __asm ਅਸਥਿਰ ( ਪੋਰਟ_YIELD_ਰੁਕਾਵਟ );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        ਬਾਹਰੀ ਅਸਥਿਰ uint32_t ul_ਪੋਰਟ_Yield_Pending; \
        ਜੇ( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_ਪੋਰਟ_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( x )

ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );
ਬਾਹਰੀ uint32_t ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( uint32_t ul_New_ਨਕਾਬ_ਮੁੱਲ );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()        v_ਪੋਰਟ_Enter_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()         v_ਪੋਰਟ_Exit_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    __asm ਅਸਥਿਰ ( "cli" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     __asm ਅਸਥਿਰ ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/* Architecture specific optimisations. */
#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities ) \
    __asm ਅਸਥਿਰ ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_ਸਿਖਰ_ਤਰਜੀਹ ) : "rm" ( uxReadyPriorities ) : "cc" )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()    __asm ਅਸਥਿਰ ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅੰਕ_VECTORS     256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਤਰਜੀਹ    15
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ ( * ISR_Handler_t ) ( ਖਾਲੀ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSUPPORT_FPU
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSUPPORT_FPU    0
#ਜੇ_ਅੰਤ

#ਜੇ configSUPPORT_FPU == 1
    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_ਵਰਤਦਾ_FLOATING_ਬਿੰਦੂ()    v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU()
#ਜੇ_ਅੰਤ

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਰਜਿਸਟਰ_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_ਸਦਿਸ਼_ਸੰਖਿਆ );
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Install_ਰੁਕਾਵਟ_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ਸਦਿਸ਼_ਸੰਖਿਆ );

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_APIC_ਅਧਾਰ

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_APIC_ਅਧਾਰ    0xFEE00000UL
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION

/* The FreeRTOS scheduling algorithm selects the task that will enter the
 * Running state.  configUSE_PORT_OPTIMISED_TASK_SELECTION is used to set how
 * that is done.
 *
 * If configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 0 then the task to
 * enter the Running state is selected using a portable algorithm written in
 * C.  This is the slowest method, but the algorithm does not restrict the
 * maximum number of unique RTOS task priorities that are available.
 *
 * If configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 1 then the task to
 * enter the Running state is selected using a single assembly instruction.
 * This is the fastest method, but restricts the maximum number of unique RTOS
 * task priorities to 32 (the same task priority can be assigned to any number
 * of RTOS tasks). */
    #warning config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION was not defined ਵਿੱਚ_2 FreeRTOSConfig.h and has been defaulted ਮੰਜ਼ਿਲ 1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ

/* There are two ways of implementing interrupt handlers:
 *
 *  1) As standard C functions -
 *
 *  This method can only be used if configUSE_COMMON_INTERRUPT_ENTRY_POINT
 *  is set to 1.  The C function is installed using
 *  xPortRegisterCInterruptHandler().
 *
 *  This is the simplest of the two methods but incurs a slightly longer
 *  interrupt entry time.
 *
 *  2) By using an assembly stub that wraps the handler in the FreeRTOS
 *     portFREERTOS_INTERRUPT_ENTRY and portFREERTOS_INTERRUPT_EXIT macros.
 *
 *  This method can always be used.  It is slightly more complex than
 *  method 1 but benefits from a faster interrupt entry time. */
    #warning config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ was not defined ਵਿੱਚ_2 FreeRTOSConfig.h and has been defaulted ਮੰਜ਼ਿਲ 1.
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_COMMON_ਰੁਕਾਵਟ_ਇੰਦਰਾਜ_ਬਿੰਦੂ    1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ISR_ਢੇਰ_ਮਾਪ

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #ਗਲਤੀ config_ISR_ਢੇਰ_ਮਾਪ was not defined ਵਿੱਚ_2 FreeRTOSConfig.h.
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ was not defined ਵਿੱਚ_2 FreeRTOSConfig.h and has been defaulted ਮੰਜ਼ਿਲ 10
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ    10
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined ਵਿੱਚ_2 FreeRTOSConfig.h and has been defaulted ਮੰਜ਼ਿਲ 0
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSUPPORT_FPU    0
#ਜੇ_ਅੰਤ

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_ਤਰਜੀਹ_ਖਿਸਕਾਓ        ( 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_MAX_SUB_ਤਰਜੀਹ      ( 0x0fUL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_API_CALL_ਤਰਜੀਹ      ( ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_APIC_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) | ਪੋਰਟ_APIC_MAX_SUB_ਤਰਜੀਹ )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APIC_PROCESSOR_ਤਰਜੀਹ    ( *( ( ਅਸਥਿਰ uint32_t * ) ( config_APIC_ਅਧਾਰ + 0xA0UL ) ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਰੁਕਾਵਟ_ਤਰਜੀਹ_INVALID()    configASSERT( ( ਪੋਰਟ_APIC_PROCESSOR_ਤਰਜੀਹ ) <= ( ਪੋਰਟ_MAX_API_CALL_ਤਰਜੀਹ ) )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
