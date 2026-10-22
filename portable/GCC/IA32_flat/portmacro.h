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
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

تعريفنوع uint32_t         TickType_t;
#وصف_ڪريو پورٽ_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#وصف_ڪريو پورٽ_APIC_TIMER_INT_ويڪٽر       ( 0x21 )
#وصف_ڪريو پورٽ_APIC_YIELD_INT_ويڪٽر       ( 0x20 )

/* Build yield interrupt instruction. */
#وصف_ڪريو پورٽ_YIELD_مداخلت             "int $0x20"

/* APIC register addresses. */
#وصف_ڪريو پورٽ_APIC_EOI                    ( *( ( متطاير uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#وصف_ڪريو پورٽ_APIC_ENABLE_ٻٽو_انگ             ( 1UL << 8UL )
#وصف_ڪريو پورٽ_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#وصف_ڪريو پورٽ_APIC_DISABLE                ( 1UL << 16UL )
#وصف_ڪريو پورٽ_APIC_NMI                    ( 4 << 8 )
#وصف_ڪريو پورٽ_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#وصف_ڪريو پورٽ_APIC_ID_رجسٽر            ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x20UL ) ) )
#وصف_ڪريو پورٽ_APIC_SPURIOUS_INT           ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0xF0UL ) ) )
#وصف_ڪريو پورٽ_APIC_LVT_TIMER              ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x320UL ) ) )
#وصف_ڪريو پورٽ_APIC_TIMER_INITIAL_ڳڻپ    ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x380UL ) ) )
#وصف_ڪريو پورٽ_APIC_TIMER_CURRENT_ڳڻپ    ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x390UL ) ) )
#وصف_ڪريو پورٽ_APIC_TASK_ترجيح          ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x80UL ) ) )
#وصف_ڪريو پورٽ_APIC_LVT_ERROR              ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x370UL ) ) )
#وصف_ڪريو پورٽ_APIC_ERROR_حالت           ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x280UL ) ) )
#وصف_ڪريو پورٽ_APIC_LDR                    ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0xD0UL ) ) )
#وصف_ڪريو پورٽ_APIC_TMRDIV                 ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x3E0UL ) ) )
#وصف_ڪريو پورٽ_APIC_LVT_PERF               ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x340UL ) ) )
#وصف_ڪريو پورٽ_APIC_LVT_LINT0              ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x350UL ) ) )
#وصف_ڪريو پورٽ_APIC_LVT_LINT1              ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#وصف_ڪريو پورٽ_YIELD()                                  \
    {                                                \
        خارجي متطاير uint32_t ulCriticalNesting;  \
        خارجي متطاير uint32_t ul_پورٽ_Yield_Pending; \
        إذا( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_پورٽ_Yield_Pending = pdTRUE;             \
        }                                            \
        وإلا                                         \
        {                                            \
            __asm متطاير ( پورٽ_YIELD_مداخلت );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        خارجي متطاير uint32_t ul_پورٽ_Yield_Pending; \
        إذا( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_پورٽ_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         ul_پورٽ_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٽ_Clear_مداخلت_نقاب( x )

خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
خارجي uint32_t ul_پورٽ_سيٽ_مداخلت_نقاب( فراغ );
خارجي فراغ v_پورٽ_Clear_مداخلت_نقاب( uint32_t ul_New_نقاب_قدر );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#وصف_ڪريو پورٽ_ENTER_CRITICAL()        v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()         v_پورٽ_Exit_Critical()
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    __asm متطاير ( "cli" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     __asm متطاير ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Architecture specific optimisations. */
#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities ) \
    __asm متطاير ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_چوٽي_ترجيح ) : "rm" ( uxReadyPriorities ) : "cc" )

    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#وصف_ڪريو پورٽ_NOP()    __asm متطاير ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#وصف_ڪريو پورٽ_انگ_VECTORS     256
#وصف_ڪريو پورٽ_MAX_ترجيح    15
تعريفنوع فراغ ( * ISR_Handler_t ) ( فراغ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#جيڪڏهن_وصف_نه_ٿيل configSUPPORT_FPU
    #وصف_ڪريو configSUPPORT_FPU    0
#جيڪڏهن_پورو

#إذا configSUPPORT_FPU == 1
    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ );
    #وصف_ڪريو پورٽ_TASK_استعمال_ڪري_FLOATING_نقطو()    v_پورٽ_Task_استعمال_ڪري_FPU()
#جيڪڏهن_پورو

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
بنياد_Type_t x_پورٽ_رجسٽر_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_ويڪٽر_عدد );
بنياد_Type_t x_پورٽ_Install_مداخلت_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ويڪٽر_عدد );

#جيڪڏهن_وصف_نه_ٿيل config_APIC_بنياد

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #وصف_ڪريو config_APIC_بنياد    0xFEE00000UL
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION

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
    #warning config_USE_پورٽ_OPTIMISED_TASK_SELECTION was not defined اندريون FreeRTOSConfig.h and has been defaulted منزل 1
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_USE_COMMON_مداخلت_داخلا_نقطو

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
    #warning config_USE_COMMON_مداخلت_داخلا_نقطو was not defined اندريون FreeRTOSConfig.h and has been defaulted منزل 1.
    #وصف_ڪريو config_USE_COMMON_مداخلت_داخلا_نقطو    1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_ISR_ڍير_سائيز

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #غلطي config_ISR_ڍير_سائيز was not defined اندريون FreeRTOSConfig.h.
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_MAX_API_CALL_مداخلت_ترجيح

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_مداخلت_ترجيح was not defined اندريون FreeRTOSConfig.h and has been defaulted منزل 10
    #وصف_ڪريو config_MAX_API_CALL_مداخلت_ترجيح    10
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined اندريون FreeRTOSConfig.h and has been defaulted منزل 0
    #وصف_ڪريو configSUPPORT_FPU    0
#جيڪڏهن_پورو

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#وصف_ڪريو پورٽ_APIC_ترجيح_سرڪايو        ( 4UL )
#وصف_ڪريو پورٽ_APIC_MAX_SUB_ترجيح      ( 0x0fUL )
#وصف_ڪريو پورٽ_MAX_API_CALL_ترجيح      ( ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_APIC_ترجيح_سرڪايو ) | پورٽ_APIC_MAX_SUB_ترجيح )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#وصف_ڪريو پورٽ_APIC_PROCESSOR_ترجيح    ( *( ( متطاير uint32_t * ) ( config_APIC_بنياد + 0xA0UL ) ) )
#وصف_ڪريو پورٽ_ASSERT_IF_مداخلت_ترجيح_INVALID()    configASSERT( ( پورٽ_APIC_PROCESSOR_ترجيح ) <= ( پورٽ_MAX_API_CALL_ترجيح ) )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
