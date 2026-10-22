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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    বাহ্য "C" {
#endif
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
#define portCHAR        বর্ণ
#define portFLOAT       ভিন্ন
#define portDOUBLE      দ্বিগুণ
#define portLONG        long
#define portSHORT       short
#define port_স্তূপ_TYPE  uint32_t
#define portBASE_TYPE   long

প্রকারনির্দেশ port_স্তূপ_TYPE স্তূপ_Type_t;
প্রকারনির্দেশ long BaseType_t;
প্রকারনির্দেশ unsigned long UBaseType_t;

#যদি( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারনির্দেশ uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    প্রকারনির্দেশ uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT  8
#define port_স্তূপ_GROWTH    -1
#define portTICK_PERIOD_MS  ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portIPL_SHIFT       ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#define portALL_IPL_BITS    ( 0x7FUL << portIPL_SHIFT )
#define portSW0_BIT         ( 0x01 << 8 )

/* Interrupt priority conversion */
#define portIPL_TO_CODE( ipl_সংখ্যা )    ( ( ipl_সংখ্যা >> 1 ) & 0x03ul )
#define portCODE_TO_IPL( iplCode )      ( ( iplCode << 1 ) | 0x01ul )

/*-----------------------------------------------------------*/

স্থির অন্তঃস্থ uint32_t ulPortGetCP0Status( শূন্য )
{
uint32_t rv;

    __asm চঞ্চল(
            "\n\t"
            "mfc0 %0,$12,0      \n\t"
            : "=r" ( rv ) :: );

    প্রত্যাগম rv;
}
/*-----------------------------------------------------------*/

স্থির অন্তঃস্থ শূন্য vPortSetCP0Status( uint32_t new_status)
{
    ( শূন্য ) new_status;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$12,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_status ) : );
}
/*-----------------------------------------------------------*/

স্থির অন্তঃস্থ uint32_t ulPortGetCP0Cause( শূন্য )
{
uint32_t rv;

    __asm চঞ্চল(
            "\n\t"
            "mfc0 %0,$13,0      \n\t"
            : "=r" ( rv ) :: );

    প্রত্যাগম rv;
}
/*-----------------------------------------------------------*/

স্থির অন্তঃস্থ শূন্য vPortSetCP0Cause( uint32_t new_cause )
{
    ( শূন্য ) new_cause;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$13,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_cause ) : );
}
/*-----------------------------------------------------------*/

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#যদি ( configASSERT_DEFINED == 1 )
    #define portDISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ulStatus;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ulStatus = ulPortGetCP0Status();                                                                        \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */                                    \
        যদি( ( ( ulStatus & portALL_IPL_BITS ) >> portIPL_SHIFT ) < configMAX_SYSCALL_INTERRUPT_PRIORITY )       \
        {                                                                                                       \
            ulStatus &= ~portALL_IPL_BITS;                                                                      \
            vPortSetCP0Status( ( ulStatus | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) ) );      \
        }                                                                                                       \
    }
#অন্যথা /* configASSERT */
    #define portDISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ulStatus;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ulStatus = ulPortGetCP0Status();                                                                        \
        ulStatus &= ~portALL_IPL_BITS;                                                                          \
        vPortSetCP0Status( ( ulStatus | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) ) );          \
    }
#endif /* configASSERT */

#define portENABLE_INTERRUPTS()             \
{                                           \
uint32_t ulStatus;                          \
    /* Unmask all interrupts. */            \
    ulStatus = ulPortGetCP0Status();        \
    ulStatus &= ~portALL_IPL_BITS;          \
    vPortSetCP0Status( ulStatus );          \
}


বাহ্য শূন্য vTaskEnterCritical( শূন্য );
বাহ্য শূন্য vTaskExitCritical( শূন্য );
#define portCRITICAL_NESTING_IN_TCB 1
#define portENTER_CRITICAL()        vTaskEnterCritical()
#define portEXIT_CRITICAL()         vTaskExitCritical()

বাহ্য UBaseType_t uxPortSetInterruptMaskFromISR();
বাহ্য শূন্য vPortClearInterruptMaskFromISR( UBaseType_t );
#define portSET_INTERRUPT_MASK_FROM_ISR() uxPortSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedStatusRegister ) vPortClearInterruptMaskFromISR( uxSavedStatusRegister )

#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#endif

#যদি configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #যদি( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

    /* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

    /*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_শীর্ষ_Priority, uxReadyPriorities ) ux_শীর্ষ_Priority = ( 31 - _clz( ( uxReadyPriorities ) ) )

#endif /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#define portYIELD()                         \
{                                           \
uint32_t ulCause;                           \
    /* Trigger software interrupt. */       \
    ulCause = ulPortGetCP0Cause();          \
    ulCause |= portSW0_BIT;                 \
    vPortSetCP0Cause( ulCause );            \
}

বাহ্য চঞ্চল UBaseType_t uxInterruptNesting;
#define portASSERT_IF_IN_ISR() configASSERT( uxInterruptNesting == 0 )

#define portNOP() __asm চঞ্চল ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters ) __attribute__((noreturn))
#define portTASK_FUNCTION( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    কুরু                                           \
    {                                            \
        যদি( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        অন্যথা                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } যাবত্( 0 )

/* Required by the kernel aware debugger. */
#ifdef __DEBUG
    #define portREMOVE_STATIC_QUALIFIER
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
