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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ             ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ    UBaseType_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t         TickType_t;
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH      ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_TIMER_INT_ಸದಿಶ       ( 0x21 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_YIELD_INT_ಸದಿಶ       ( 0x20 )

/* Build yield interrupt instruction. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_ಅಡಚಣೆ             "int $0x20"

/* APIC register addresses. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_EOI                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_ENABLE_ಬಿಟ್             ( 1UL << 8UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_DISABLE                ( 1UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_NMI                    ( 4 << 8 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_ID_ರಿಜಿಸ್ಟರ್            ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x20UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_SPURIOUS_INT           ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0xF0UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LVT_TIMER              ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x320UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_TIMER_INITIAL_ಎಣಿಕೆ    ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x380UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_TIMER_CURRENT_ಎಣಿಕೆ    ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x390UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_TASK_ಆದ್ಯತೆ          ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x80UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LVT_ERROR              ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x370UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_ERROR_ಸ್ಥಿತಿ           ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x280UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LDR                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0xD0UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_TMRDIV                 ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x3E0UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LVT_PERF               ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x340UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LVT_LINT0              ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x350UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_LVT_LINT1              ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                                  \
    {                                                \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint32_t ulCriticalNesting;  \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_Yield_Pending; \
        ಆದರೆ( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_ಪೋರ್ಟ್_Yield_Pending = pdTRUE;             \
        }                                            \
        ಇಲ್ಲದಿದ್ದರೆ                                         \
        {                                            \
            __asm ಅಸ್ಥಿರ ( ಪೋರ್ಟ್_YIELD_ಅಡಚಣೆ );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_Yield_Pending; \
        ಆದರೆ( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_ಪೋರ್ಟ್_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( x )

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ uint32_t ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( uint32_t ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()        v_ಪೋರ್ಟ್_Enter_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()         v_ಪೋರ್ಟ್_Exit_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    __asm ಅಸ್ಥಿರ ( "cli" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     __asm ಅಸ್ಥಿರ ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/* Architecture specific optimisations. */
#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities ) \
    __asm ಅಸ್ಥಿರ ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_ತುದಿ_ಆದ್ಯತೆ ) : "rm" ( uxReadyPriorities ) : "cc" )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()    __asm ಅಸ್ಥಿರ ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಂಕೆ_VECTORS     256
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ಆದ್ಯತೆ    15
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ ( * ISR_Handler_t ) ( ಶೂನ್ಯ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSUPPORT_FPU
    #ವ್ಯಾಖ್ಯಾನಿಸು configSUPPORT_FPU    0
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ configSUPPORT_FPU == 1
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_ಬಳಸುತ್ತದೆ_FLOATING_ಬಿಂದು()    v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU()
#ಆದರೆ_ಅಂತ್ಯ

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
ತಳ_Type_t x_ಪೋರ್ಟ್_ರಿಜಿಸ್ಟರ್_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_ಸದಿಶ_ಸಂಖ್ಯೆ );
ತಳ_Type_t x_ಪೋರ್ಟ್_Install_ಅಡಚಣೆ_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_ಸದಿಶ_ಸಂಖ್ಯೆ );

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_APIC_ತಳ

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #ವ್ಯಾಖ್ಯಾನಿಸು config_APIC_ತಳ    0xFEE00000UL
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION

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
    #warning config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION was not defined ಒಳ FreeRTOSConfig.h and has been defaulted ಗಮ್ಯ 1
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು

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
    #warning config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು was not defined ಒಳ FreeRTOSConfig.h and has been defaulted ಗಮ್ಯ 1.
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_COMMON_ಅಡಚಣೆ_ನಮೂದು_ಬಿಂದು    1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ISR_ರಾಶಿ_ಗಾತ್ರ

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #ದೋಷ config_ISR_ರಾಶಿ_ಗಾತ್ರ was not defined ಒಳ FreeRTOSConfig.h.
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ was not defined ಒಳ FreeRTOSConfig.h and has been defaulted ಗಮ್ಯ 10
    #ವ್ಯಾಖ್ಯಾನಿಸು config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ    10
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined ಒಳ FreeRTOSConfig.h and has been defaulted ಗಮ್ಯ 0
    #ವ್ಯಾಖ್ಯಾನಿಸು configSUPPORT_FPU    0
#ಆದರೆ_ಅಂತ್ಯ

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_ಆದ್ಯತೆ_ಸರಿಸು        ( 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_MAX_SUB_ಆದ್ಯತೆ      ( 0x0fUL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_API_CALL_ಆದ್ಯತೆ      ( ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_APIC_ಆದ್ಯತೆ_ಸರಿಸು ) | ಪೋರ್ಟ್_APIC_MAX_SUB_ಆದ್ಯತೆ )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APIC_PROCESSOR_ಆದ್ಯತೆ    ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( config_APIC_ತಳ + 0xA0UL ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಅಡಚಣೆ_ಆದ್ಯತೆ_INVALID()    configASSERT( ( ಪೋರ್ಟ್_APIC_PROCESSOR_ಆದ್ಯತೆ ) <= ( ಪೋರ್ಟ್_MAX_API_CALL_ಆದ್ಯತೆ ) )

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
