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
#تعریف_کړه پورټ_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#تعریف_کړه پورټ_APIC_TIMER_INT_ویکټور       ( 0x21 )
#تعریف_کړه پورټ_APIC_YIELD_INT_ویکټور       ( 0x20 )

/* Build yield interrupt instruction. */
#تعریف_کړه پورټ_YIELD_مداخله             "int $0x20"

/* APIC register addresses. */
#تعریف_کړه پورټ_APIC_EOI                    ( *( ( متطاير uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#تعریف_کړه پورټ_APIC_ENABLE_بټ             ( 1UL << 8UL )
#تعریف_کړه پورټ_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#تعریف_کړه پورټ_APIC_DISABLE                ( 1UL << 16UL )
#تعریف_کړه پورټ_APIC_NMI                    ( 4 << 8 )
#تعریف_کړه پورټ_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#تعریف_کړه پورټ_APIC_ID_ثبتوونکی            ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x20UL ) ) )
#تعریف_کړه پورټ_APIC_SPURIOUS_INT           ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0xF0UL ) ) )
#تعریف_کړه پورټ_APIC_LVT_TIMER              ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x320UL ) ) )
#تعریف_کړه پورټ_APIC_TIMER_INITIAL_شمېر    ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x380UL ) ) )
#تعریف_کړه پورټ_APIC_TIMER_CURRENT_شمېر    ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x390UL ) ) )
#تعریف_کړه پورټ_APIC_TASK_لومړیتوب          ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x80UL ) ) )
#تعریف_کړه پورټ_APIC_LVT_ERROR              ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x370UL ) ) )
#تعریف_کړه پورټ_APIC_ERROR_حالت           ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x280UL ) ) )
#تعریف_کړه پورټ_APIC_LDR                    ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0xD0UL ) ) )
#تعریف_کړه پورټ_APIC_TMRDIV                 ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x3E0UL ) ) )
#تعریف_کړه پورټ_APIC_LVT_PERF               ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x340UL ) ) )
#تعریف_کړه پورټ_APIC_LVT_LINT0              ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x350UL ) ) )
#تعریف_کړه پورټ_APIC_LVT_LINT1              ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#تعریف_کړه پورټ_YIELD()                                  \
    {                                                \
        خارجي متطاير uint32_t ulCriticalNesting;  \
        خارجي متطاير uint32_t ul_پورټ_Yield_Pending; \
        إذا( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_پورټ_Yield_Pending = pdTRUE;             \
        }                                            \
        وإلا                                         \
        {                                            \
            __asm متطاير ( پورټ_YIELD_مداخله );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        خارجي متطاير uint32_t ul_پورټ_Yield_Pending; \
        إذا( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_پورټ_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         ul_پورټ_سېټ_مداخله_ماسک()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    v_پورټ_Clear_مداخله_ماسک( x )

خارجي فراغ v_پورټ_Enter_Critical( فراغ );
خارجي فراغ v_پورټ_Exit_Critical( فراغ );
خارجي uint32_t ul_پورټ_سېټ_مداخله_ماسک( فراغ );
خارجي فراغ v_پورټ_Clear_مداخله_ماسک( uint32_t ul_New_ماسک_ارزښت );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#تعریف_کړه پورټ_ENTER_CRITICAL()        v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()         v_پورټ_Exit_Critical()
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    __asm متطاير ( "cli" )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     __asm متطاير ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Architecture specific optimisations. */
#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities ) \
    __asm متطاير ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_سر_لومړیتوب ) : "rm" ( uxReadyPriorities ) : "cc" )

    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#تعریف_کړه پورټ_NOP()    __asm متطاير ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#تعریف_کړه پورټ_عدد_VECTORS     256
#تعریف_کړه پورټ_MAX_لومړیتوب    15
تعريفنوع فراغ ( * ISR_Handler_t ) ( فراغ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#که_نه_تعریف_شوی configSUPPORT_FPU
    #تعریف_کړه configSUPPORT_FPU    0
#د_که_پای

#إذا configSUPPORT_FPU == 1
    فراغ v_پورټ_Task_کاروي_FPU( فراغ );
    #تعریف_کړه پورټ_TASK_کاروي_FLOATING_ټکی()    v_پورټ_Task_کاروي_FPU()
#د_که_پای

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
بنسټ_Type_t x_پورټ_ثبتوونکی_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_ویکټور_شمېره );
بنسټ_Type_t x_پورټ_Install_مداخله_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ویکټور_شمېره );

#که_نه_تعریف_شوی config_APIC_بنسټ

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #تعریف_کړه config_APIC_بنسټ    0xFEE00000UL
#د_که_پای

#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION

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
    #warning config_USE_پورټ_OPTIMISED_TASK_SELECTION was not defined دننه FreeRTOSConfig.h and has been defaulted منزل 1
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
#د_که_پای

#که_نه_تعریف_شوی config_USE_COMMON_مداخله_ثبت_ټکی

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
    #warning config_USE_COMMON_مداخله_ثبت_ټکی was not defined دننه FreeRTOSConfig.h and has been defaulted منزل 1.
    #تعریف_کړه config_USE_COMMON_مداخله_ثبت_ټکی    1
#د_که_پای

#که_نه_تعریف_شوی config_ISR_ډېری_اندازه

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #تېروتنه config_ISR_ډېری_اندازه was not defined دننه FreeRTOSConfig.h.
#د_که_پای

#که_نه_تعریف_شوی config_MAX_API_CALL_مداخله_لومړیتوب

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_مداخله_لومړیتوب was not defined دننه FreeRTOSConfig.h and has been defaulted منزل 10
    #تعریف_کړه config_MAX_API_CALL_مداخله_لومړیتوب    10
#د_که_پای

#که_نه_تعریف_شوی configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined دننه FreeRTOSConfig.h and has been defaulted منزل 0
    #تعریف_کړه configSUPPORT_FPU    0
#د_که_پای

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#تعریف_کړه پورټ_APIC_لومړیتوب_ښويدنه        ( 4UL )
#تعریف_کړه پورټ_APIC_MAX_SUB_لومړیتوب      ( 0x0fUL )
#تعریف_کړه پورټ_MAX_API_CALL_لومړیتوب      ( ( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_APIC_لومړیتوب_ښويدنه ) | پورټ_APIC_MAX_SUB_لومړیتوب )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#تعریف_کړه پورټ_APIC_PROCESSOR_لومړیتوب    ( *( ( متطاير uint32_t * ) ( config_APIC_بنسټ + 0xA0UL ) ) )
#تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID()    configASSERT( ( پورټ_APIC_PROCESSOR_لومړیتوب ) <= ( پورټ_MAX_API_CALL_لومړیتوب ) )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
