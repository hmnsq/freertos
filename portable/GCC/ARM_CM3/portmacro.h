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
    ബാഹ്യ "C" {
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
#define portCHAR          അക്ഷരം
#define portFLOAT         ദശാംശം
#define portDOUBLE        ഇരട്ട
#define portLONG          long
#define portSHORT         short
#define port_അട്ടി_TYPE    uint32_t
#define portBASE_TYPE     long

തരനിർവചനം port_അട്ടി_TYPE   അട്ടി_Type_t;
തരനിർവചനം long             BaseType_t;
തരനിർവചനം unsigned long    UBaseType_t;

#എങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_അട്ടി_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8
#define portDONT_DISCARD      __attribute__( ( used ) )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
#define portYIELD()                                     \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm അസ്ഥിര ( "dsb" ::: "memory" );                     \
        __asm അസ്ഥിര ( "isb" );                                  \
    }

#define portNVIC_INT_CTRL_REG     ( *( ( അസ്ഥിര uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    ചെയ്യുക                                           \
    {                                            \
        എങ്കിൽ( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        അല്ലെങ്കിൽ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ആകുമ്പോൾ( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
ബാഹ്യ ശൂന്യം vPortEnterCritical( ശൂന്യം );
ബാഹ്യ ശൂന്യം vPortExitCritical( ശൂന്യം );
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulPortRaiseBASEPRI()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortSetBASEPRI( x )
#define portDISABLE_INTERRUPTS()                  vPortRaiseBASEPRI()
#define portENABLE_INTERRUPTS()                   vPortSetBASEPRI( 0 )
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )
/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    ബാഹ്യ ശൂന്യം vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#എങ്കിൽ configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
    __attribute__( ( always_inline ) ) സ്ഥിതം വരിയിൽ uint8_t uc_Port_എണ്ണം_Leading_Zeros( uint32_t ulBitmap )
    {
        uint8_t ucReturn;

        __asm അസ്ഥിര ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) : "memory" );

        തിരികെ ucReturn;
    }

/* Check the configuration. */
    #എങ്കിൽ ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_മുകൾ_Priority, uxReadyPriorities )    ux_മുകൾ_Priority = ( 31UL - ( uint32_t ) uc_Port_എണ്ണം_Leading_Zeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

#എങ്കിൽ ( configASSERT_DEFINED == 1 )
    ശൂന്യം vPortValidateInterruptPriority( ശൂന്യം );
    #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#endif

/* portNOP() is not required by this port. */
#define portNOP()

#define portINLINE              __inline

#ifndef portFORCE_INLINE
    #define portFORCE_INLINE    വരിയിൽ __attribute__( ( always_inline ) )
#endif

/*-----------------------------------------------------------*/

portFORCE_INLINE സ്ഥിതം BaseType_t xPortIsInsideInterrupt( ശൂന്യം )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm അസ്ഥിര ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    എങ്കിൽ( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    അല്ലെങ്കിൽ
    {
        xReturn = pdTRUE;
    }

    തിരികെ xReturn;
}

/*-----------------------------------------------------------*/

portFORCE_INLINE സ്ഥിതം ശൂന്യം vPortRaiseBASEPRI( ശൂന്യം )
{
    uint32_t ulNewBASEPRI;

    __asm അസ്ഥിര
    (
        "   mov %0, %1                                              \n" \
        "   msr basepri, %0                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulNewBASEPRI ) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) : "memory"
    );
}

/*-----------------------------------------------------------*/

portFORCE_INLINE സ്ഥിതം uint32_t ulPortRaiseBASEPRI( ശൂന്യം )
{
    uint32_t ulOriginalBASEPRI, ulNewBASEPRI;

    __asm അസ്ഥിര
    (
        "   mrs %0, basepri                                         \n" \
        "   mov %1, %2                                              \n" \
        "   msr basepri, %1                                         \n" \
        "   isb                                                     \n" \
        "   dsb                                                     \n" \
        : "=r" ( ulOriginalBASEPRI ), "=r" ( ulNewBASEPRI ) : "i" ( configMAX_SYSCALL_INTERRUPT_PRIORITY ) : "memory"
    );

    /* This return will not be reached but is necessary to prevent compiler
     * warnings. */
    തിരികെ ulOriginalBASEPRI;
}
/*-----------------------------------------------------------*/

portFORCE_INLINE സ്ഥിതം ശൂന്യം vPortSetBASEPRI( uint32_t ul_New_Mask_മൂല്യം )
{
    __asm അസ്ഥിര
    (
        "   msr basepri, %0 " ::"r" ( ul_New_Mask_മൂല്യം ) : "memory"
    );
}
/*-----------------------------------------------------------*/

#define portMEMORY_BARRIER()    __asm അസ്ഥിര ( "" ::: "memory" )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
