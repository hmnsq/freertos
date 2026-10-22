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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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
#घोषणा portCHAR        अक्षर
#घोषणा portFLOAT       भग्न
#घोषणा portDOUBLE      द्विगुन
#घोषणा portLONG        दीर्घ
#घोषणा portSHORT       लघु
#घोषणा port_ढेर_TYPE  uint32_t
#घोषणा portBASE_TYPE   दीर्घ

प्रकार port_ढेर_TYPE ढेर_Type_t;
प्रकार दीर्घ BaseType_t;
प्रकार अचिन्हित दीर्घ UBaseType_t;

#अगर( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t TickType_t;
    #घोषणा portMAX_DELAY ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t             TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#घोषणा portBYTE_ALIGNMENT  8
#घोषणा port_ढेर_GROWTH    -1
#घोषणा portTICK_PERIOD_MS  ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#घोषणा portIPL_SHIFT       ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#घोषणा portALL_IPL_BITS    ( 0x7FUL << portIPL_SHIFT )
#घोषणा portSW0_BIT         ( 0x01 << 8 )

/* Interrupt priority conversion */
#घोषणा portIPL_TO_CODE( ipl_संख्या )    ( ( ipl_संख्या >> 1 ) & 0x03ul )
#घोषणा portCODE_TO_IPL( iplCode )      ( ( iplCode << 1 ) | 0x01ul )

/*-----------------------------------------------------------*/

अटल अंतरभूत uint32_t ulPortGetCP0Status( व्योम )
{
uint32_t rv;

    __asm अस्थिर(
            "\n\t"
            "mfc0 %0,$12,0      \n\t"
            : "=r" ( rv ) :: );

    वापस rv;
}
/*-----------------------------------------------------------*/

अटल अंतरभूत व्योम vPortSetCP0Status( uint32_t new_status)
{
    ( व्योम ) new_status;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$12,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_status ) : );
}
/*-----------------------------------------------------------*/

अटल अंतरभूत uint32_t ulPortGetCP0Cause( व्योम )
{
uint32_t rv;

    __asm अस्थिर(
            "\n\t"
            "mfc0 %0,$13,0      \n\t"
            : "=r" ( rv ) :: );

    वापस rv;
}
/*-----------------------------------------------------------*/

अटल अंतरभूत व्योम vPortSetCP0Cause( uint32_t new_cause )
{
    ( व्योम ) new_cause;

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
#अगर ( configASSERT_DEFINED == 1 )
    #घोषणा portDISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ulStatus;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ulStatus = ulPortGetCP0Status();                                                                        \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */                                    \
        अगर( ( ( ulStatus & portALL_IPL_BITS ) >> portIPL_SHIFT ) < configMAX_SYSCALL_INTERRUPT_PRIORITY )       \
        {                                                                                                       \
            ulStatus &= ~portALL_IPL_BITS;                                                                      \
            vPortSetCP0Status( ( ulStatus | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) ) );      \
        }                                                                                                       \
    }
#अन्यथा /* configASSERT */
    #घोषणा portDISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ulStatus;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ulStatus = ulPortGetCP0Status();                                                                        \
        ulStatus &= ~portALL_IPL_BITS;                                                                          \
        vPortSetCP0Status( ( ulStatus | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) ) );          \
    }
#पूर्ण_अगर /* configASSERT */

#घोषणा portENABLE_INTERRUPTS()             \
{                                           \
uint32_t ulStatus;                          \
    /* Unmask all interrupts. */            \
    ulStatus = ulPortGetCP0Status();        \
    ulStatus &= ~portALL_IPL_BITS;          \
    vPortSetCP0Status( ulStatus );          \
}


बाह्य व्योम vTaskEnterCritical( व्योम );
बाह्य व्योम vTaskExitCritical( व्योम );
#घोषणा portCRITICAL_NESTING_IN_TCB 1
#घोषणा portENTER_CRITICAL()        vTaskEnterCritical()
#घोषणा portEXIT_CRITICAL()         vTaskExitCritical()

बाह्य UBaseType_t uxPortSetInterruptMaskFromISR();
बाह्य व्योम vPortClearInterruptMaskFromISR( UBaseType_t );
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR() uxPortSetInterruptMaskFromISR()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedStatusRegister ) vPortClearInterruptMaskFromISR( uxSavedStatusRegister )

#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #अगर( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

    /* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

    /*-----------------------------------------------------------*/

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities ) ux_शीर्ष_Priority = ( 31 - _clz( ( uxReadyPriorities ) ) )

#पूर्ण_अगर /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#घोषणा portYIELD()                         \
{                                           \
uint32_t ulCause;                           \
    /* Trigger software interrupt. */       \
    ulCause = ulPortGetCP0Cause();          \
    ulCause |= portSW0_BIT;                 \
    vPortSetCP0Cause( ulCause );            \
}

बाह्य अस्थिर UBaseType_t uxInterruptNesting;
#घोषणा portASSERT_IF_IN_ISR() configASSERT( uxInterruptNesting == 0 )

#घोषणा portNOP() __asm अस्थिर ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters ) __attribute__((noreturn))
#घोषणा portTASK_FUNCTION( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )
/*-----------------------------------------------------------*/

#घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
    करो                                           \
    {                                            \
        अगर( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } जबतक( 0 )

/* Required by the kernel aware debugger. */
#अगर_घोषित __DEBUG
    #घोषणा portREMOVE_STATIC_QUALIFIER
#पूर्ण_अगर

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
