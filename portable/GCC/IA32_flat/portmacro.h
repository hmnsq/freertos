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
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع لما             ادھار_Type_t;
تعريفنوع بنانشانی لما    UBaseType_t;

تعريفنوع uint32_t         TickType_t;
#تعریف_کرو پورٹ_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#تعریف_کرو پورٹ_APIC_TIMER_INT_سمتیہ       ( 0x21 )
#تعریف_کرو پورٹ_APIC_YIELD_INT_سمتیہ       ( 0x20 )

/* Build yield interrupt instruction. */
#تعریف_کرو پورٹ_YIELD_رکاوٹ             "int $0x20"

/* APIC register addresses. */
#تعریف_کرو پورٹ_APIC_EOI                    ( *( ( متطاير uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#تعریف_کرو پورٹ_APIC_ENABLE_ثنائی_ہندسہ             ( 1UL << 8UL )
#تعریف_کرو پورٹ_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#تعریف_کرو پورٹ_APIC_DISABLE                ( 1UL << 16UL )
#تعریف_کرو پورٹ_APIC_NMI                    ( 4 << 8 )
#تعریف_کرو پورٹ_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#تعریف_کرو پورٹ_APIC_ID_رجسٹر            ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x20UL ) ) )
#تعریف_کرو پورٹ_APIC_SPURIOUS_INT           ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0xF0UL ) ) )
#تعریف_کرو پورٹ_APIC_LVT_TIMER              ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x320UL ) ) )
#تعریف_کرو پورٹ_APIC_TIMER_INITIAL_گنتی    ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x380UL ) ) )
#تعریف_کرو پورٹ_APIC_TIMER_CURRENT_گنتی    ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x390UL ) ) )
#تعریف_کرو پورٹ_APIC_TASK_ترجیح          ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x80UL ) ) )
#تعریف_کرو پورٹ_APIC_LVT_ERROR              ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x370UL ) ) )
#تعریف_کرو پورٹ_APIC_ERROR_حالت           ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x280UL ) ) )
#تعریف_کرو پورٹ_APIC_LDR                    ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0xD0UL ) ) )
#تعریف_کرو پورٹ_APIC_TMRDIV                 ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x3E0UL ) ) )
#تعریف_کرو پورٹ_APIC_LVT_PERF               ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x340UL ) ) )
#تعریف_کرو پورٹ_APIC_LVT_LINT0              ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x350UL ) ) )
#تعریف_کرو پورٹ_APIC_LVT_LINT1              ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#تعریف_کرو پورٹ_YIELD()                                  \
    {                                                \
        خارجي متطاير uint32_t ulCriticalNesting;  \
        خارجي متطاير uint32_t ul_پورٹ_Yield_Pending; \
        إذا( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_پورٹ_Yield_Pending = pdTRUE;             \
        }                                            \
        وإلا                                         \
        {                                            \
            __asm متطاير ( پورٹ_YIELD_رکاوٹ );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        خارجي متطاير uint32_t ul_پورٹ_Yield_Pending; \
        إذا( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_پورٹ_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ul_پورٹ_سیٹ_رکاوٹ_نقاب()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_پورٹ_Clear_رکاوٹ_نقاب( x )

خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
خارجي uint32_t ul_پورٹ_سیٹ_رکاوٹ_نقاب( فراغ );
خارجي فراغ v_پورٹ_Clear_رکاوٹ_نقاب( uint32_t ul_New_نقاب_قدر );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#تعریف_کرو پورٹ_ENTER_CRITICAL()        v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()         v_پورٹ_Exit_Critical()
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm متطاير ( "cli" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm متطاير ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Architecture specific optimisations. */
#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities ) \
    __asm متطاير ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_چوٹی_ترجیح ) : "rm" ( uxReadyPriorities ) : "cc" )

    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#تعریف_کرو پورٹ_NOP()    __asm متطاير ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#تعریف_کرو پورٹ_عدد_VECTORS     256
#تعریف_کرو پورٹ_MAX_ترجیح    15
تعريفنوع فراغ ( * ISR_Handler_t ) ( فراغ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#جے_بنا_تعریف configSUPPORT_FPU
    #تعریف_کرو configSUPPORT_FPU    0
#جے_انت

#إذا configSUPPORT_FPU == 1
    فراغ v_پورٹ_Task_ورتدا_FPU( فراغ );
    #تعریف_کرو پورٹ_TASK_ورتدا_FLOATING_نقطہ()    v_پورٹ_Task_ورتدا_FPU()
#جے_انت

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
ادھار_Type_t x_پورٹ_رجسٹر_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_سمتیہ_نمبر );
ادھار_Type_t x_پورٹ_Install_رکاوٹ_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_سمتیہ_نمبر );

#جے_بنا_تعریف config_APIC_ادھار

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #تعریف_کرو config_APIC_ادھار    0xFEE00000UL
#جے_انت

#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION

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
    #warning config_USE_پورٹ_OPTIMISED_TASK_SELECTION was not defined وچ FreeRTOSConfig.h and has been defaulted منزل 1
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#جے_انت

#جے_بنا_تعریف config_USE_COMMON_رکاوٹ_اندراج_نقطہ

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
    #warning config_USE_COMMON_رکاوٹ_اندراج_نقطہ was not defined وچ FreeRTOSConfig.h and has been defaulted منزل 1.
    #تعریف_کرو config_USE_COMMON_رکاوٹ_اندراج_نقطہ    1
#جے_انت

#جے_بنا_تعریف config_ISR_ڈھیر_ناپ

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #غلطی config_ISR_ڈھیر_ناپ was not defined وچ FreeRTOSConfig.h.
#جے_انت

#جے_بنا_تعریف config_MAX_API_CALL_رکاوٹ_ترجیح

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_رکاوٹ_ترجیح was not defined وچ FreeRTOSConfig.h and has been defaulted منزل 10
    #تعریف_کرو config_MAX_API_CALL_رکاوٹ_ترجیح    10
#جے_انت

#جے_بنا_تعریف configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined وچ FreeRTOSConfig.h and has been defaulted منزل 0
    #تعریف_کرو configSUPPORT_FPU    0
#جے_انت

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#تعریف_کرو پورٹ_APIC_ترجیح_کھسکاؤ        ( 4UL )
#تعریف_کرو پورٹ_APIC_MAX_SUB_ترجیح      ( 0x0fUL )
#تعریف_کرو پورٹ_MAX_API_CALL_ترجیح      ( ( config_MAX_API_CALL_رکاوٹ_ترجیح << پورٹ_APIC_ترجیح_کھسکاؤ ) | پورٹ_APIC_MAX_SUB_ترجیح )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#تعریف_کرو پورٹ_APIC_PROCESSOR_ترجیح    ( *( ( متطاير uint32_t * ) ( config_APIC_ادھار + 0xA0UL ) ) )
#تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID()    configASSERT( ( پورٹ_APIC_PROCESSOR_ترجیح ) <= ( پورٹ_MAX_API_CALL_ترجیح ) )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
