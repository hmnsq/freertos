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
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    uint32_t
#घोषणा portBASE_TYPE     दीर्घ

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार दीर्घ             BaseType_t;
प्रकार अचिन्हित दीर्घ    UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH          ( -1 )
#घोषणा portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT        8

/* Constants used with memory barrier intrinsics. */
#घोषणा portSY_FULL_READ_WRITE    ( 15 )

/*-----------------------------------------------------------*/

/* Scheduler utilities. */
#घोषणा portYIELD()                                     \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __dsb( portSY_FULL_READ_WRITE );                           \
        __isb( portSY_FULL_READ_WRITE );                           \
    }
/*-----------------------------------------------------------*/

#घोषणा portNVIC_INT_CTRL_REG     ( *( ( अस्थिर uint32_t * ) 0xe000ed04 ) )
#घोषणा portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
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
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );

#घोषणा portDISABLE_INTERRUPTS()                  vPortRaiseBASEPRI()
#घोषणा portENABLE_INTERRUPTS()                   vPortSetBASEPRI( 0 )
#घोषणा portENTER_CRITICAL()                      vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()                       vPortExitCritical()
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulPortRaiseBASEPRI()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortSetBASEPRI( x )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#अगर_अघोषित portSUPPRESS_TICKS_AND_SLEEP
    बाह्य व्योम vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #घोषणा portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Port specific optimisations. */
#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

/* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#पूर्ण_अगर /* taskRECORD_READY_PRIORITY */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/

#अगर ( configASSERT_DEFINED == 1 )
    व्योम vPortValidateInterruptPriority( व्योम );
    #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#पूर्ण_अगर

/* portNOP() is not required by this port. */
#घोषणा portNOP()

#घोषणा portINLINE              __inline

#अगर_अघोषित portFORCE_INLINE
    #घोषणा portFORCE_INLINE    __forceinline
#पूर्ण_अगर

/*-----------------------------------------------------------*/

अटल portFORCE_INLINE व्योम vPortSetBASEPRI( uint32_t ulBASEPRI )
{
    __asm
    {
        /* Barrier instructions are not used as this function is only used to
         * lower the BASEPRI value. */
/* *INDENT-OFF* */
            msr basepri, ulBASEPRI
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

अटल portFORCE_INLINE व्योम vPortRaiseBASEPRI( व्योम )
{
    uint32_t ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
            msr basepri, ulNewBASEPRI
            dsb
            isb
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

अटल portFORCE_INLINE व्योम vPortClearBASEPRIFromISR( व्योम )
{
    __asm
    {
        /* Set BASEPRI to 0 so no interrupts are masked.  This function is only
         * used to lower the mask in an interrupt, so memory barriers are not
         * used. */
/* *INDENT-OFF* */
            msr basepri, # 0
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

अटल portFORCE_INLINE uint32_t ulPortRaiseBASEPRI( व्योम )
{
    uint32_t ulReturn, ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
            mrs ulReturn, basepri
            msr basepri, ulNewBASEPRI
            dsb
            isb
/* *INDENT-ON* */
    }

    वापस ulReturn;
}
/*-----------------------------------------------------------*/

अटल portFORCE_INLINE BaseType_t xPortIsInsideInterrupt( व्योम )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
/* *INDENT-OFF* */
            mrs ulCurrentInterrupt, ipsr
/* *INDENT-ON* */
    }

    अगर( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    वापस xReturn;
}


/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
