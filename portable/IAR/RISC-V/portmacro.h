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

#समावेश "intrinsics.h"

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
#अगर __riscv_xlen == 64
    #घोषणा port_ढेर_TYPE           uint64_t
    #घोषणा portBASE_TYPE            int64_t
    #घोषणा portUBASE_TYPE           uint64_t
    #घोषणा portMAX_DELAY            ( TickType_t ) 0xffffffffffffffffUL
    #घोषणा port_POINTER_आकार_TYPE    uint64_t
#या_अगर __riscv_xlen == 32
    #घोषणा port_ढेर_TYPE           uint32_t
    #घोषणा portBASE_TYPE            int32_t
    #घोषणा portUBASE_TYPE           uint32_t
    #घोषणा portMAX_DELAY            ( TickType_t ) 0xffffffffUL
#अन्यथा /* if __riscv_xlen == 64 */
    #त्रुटि "Assembler did not define __riscv_xlen"
#पूर्ण_अगर /* if __riscv_xlen == 64 */

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार portBASE_TYPE    BaseType_t;
प्रकार portUBASE_TYPE   UBaseType_t;
प्रकार portUBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#घोषणा portCHAR                   अक्षर
#घोषणा portFLOAT                  भग्न
#घोषणा portDOUBLE                 द्विगुन
#घोषणा portLONG                   दीर्घ
#घोषणा portSHORT                  लघु

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#घोषणा portTICK_TYPE_IS_ATOMIC    1
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH          ( -1 )
#घोषणा portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#अगर_घोषित __riscv_32e
    #घोषणा portBYTE_ALIGNMENT    8         /* RV32E uses RISC-V EABI with reduced stack alignment requirements. */
#अन्यथा
    #घोषणा portBYTE_ALIGNMENT    16
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
बाह्य व्योम vTaskSwitchContext( व्योम );
#घोषणा portYIELD()                __asm अस्थिर ( "ecall" );
#घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
    करो                                           \
    {                                            \
        अगर( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            vTaskSwitchContext();                \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } जबतक( 0 )
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#घोषणा portCRITICAL_NESTING_IN_TCB    0

#घोषणा portDISABLE_INTERRUPTS()                                   __disable_interrupt()
#घोषणा portENABLE_INTERRUPTS()                                    __enable_interrupt()

बाह्य माप_प्रकार xCriticalNesting;
#घोषणा portENTER_CRITICAL()      \
    {                             \
        portDISABLE_INTERRUPTS(); \
        xCriticalNesting++;       \
    }

#घोषणा portEXIT_CRITICAL()          \
    {                                \
        xCriticalNesting--;          \
        अगर( xCriticalNesting == 0 )  \
        {                            \
            portENABLE_INTERRUPTS(); \
        }                            \
    }

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#अगर ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )

    #त्रुटि "configUSE_PORT_OPTIMISED_TASK_SELECTION cannot yet be used in the IAR RISC-V port, the CLZ instruction needs to be emulated."

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. These are
 * not necessary for to use this port.  They are defined so the common demo
 * files (which build with all the ports) will build. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/*-----------------------------------------------------------*/

#घोषणा portNOP()    __asm अस्थिर ( " nop " )
#घोषणा portINLINE              __inline

#अगर_अघोषित portFORCE_INLINE
    #घोषणा portFORCE_INLINE    अंतरभूत __attribute__( ( always_inline ) )
#पूर्ण_अगर

#घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#आशय diag_suppress=Pa082

/* configCLINT_BASE_ADDRESS is a legacy definition that was replaced by the
 * configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS definitions.  For
 * backward compatibility derive the newer definitions from the old if the old
 * definition is found. */
#अगर defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 )

/* Legacy case where configCLINT_BASE_ADDRESS was defined as 0 to indicate
 * there was no CLINT.  Equivalent now is to set the MTIME and MTIMECMP
 * addresses to 0. */
    #घोषणा configMTIME_BASE_ADDRESS       ( 0 )
    #घोषणा configMTIMECMP_BASE_ADDRESS    ( 0 )
#या_अगर defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS )

/* Legacy case where configCLINT_BASE_ADDRESS was set to the base address of
 * the CLINT.  Equivalent now is to derive the MTIME and MTIMECMP addresses
 * from the CLINT address. */
    #घोषणा configMTIME_BASE_ADDRESS       ( ( configCLINT_BASE_ADDRESS ) + 0xBFF8UL )
    #घोषणा configMTIMECMP_BASE_ADDRESS    ( ( configCLINT_BASE_ADDRESS ) + 0x4000UL )
#या_अगर !defined( configMTIME_BASE_ADDRESS ) || !defined( configMTIMECMP_BASE_ADDRESS )
    #त्रुटि "configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  Set them to zero if there is no MTIME (machine time) clock.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#पूर्ण_अगर /* if defined( configCLINT_BASE_ADDRESS ) && !defined( configMTIME_BASE_ADDRESS ) && ( configCLINT_BASE_ADDRESS == 0 ) */

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
